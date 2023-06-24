/**************************************************************************************************************************************
 * LOG:                                                                   							   								  *
 * VERSION					AUTHOR           					DATE 						      DESCRIPTION 		   			      *
 * 1.0.0 					BOOTLOADER Development team    		22 JUN,2023					  Initial Creation	                  *
 **************************************************************************************************************************************/

/**************************************************************************************************************************************
 * ! Title      	: Bootloader_Main SWC                                           							                     		 	      *
 * ! File Name	: main.c                                   		                   						                      	      *
 * ! Description : This file has the implementation of boot loader main application 			  						              *
 * ! Compiler  	: GNU ARM cross Compiler                                            							                      *
 * ! Target 	  	: STM32F401cc Micro-Controller                                         							                  *
 * ! Layer 	  	: APP	                  						                                         							  *
 **************************************************************************************************************************************/
/**************************************************** Defines  ************************************************************************/
#define VECTOR_TABLE_ADDRESS			0x08004000
#define ENTRY_POINT_ADDRESS				0x08004004
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#include<stdint.h>
#include "MCAL/STM32F401C8T6/STM32F401C8T6.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include "MCAL/FLASH/FLASH.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/USART/USART.h"
#include "MCAL/SysTick/SysTick.h"
#include "MCAL/GPIO/GPIO.h"
/***************************************************** Global Variables **************************************************************/
v_u8 recBuffer[100]={0};
v_u8 recCounter=0;
v_u8 timeOutFlag=0;
v_u8 writeRequest=1;
/******************************************************** Typedefs  *************************************************************/
typedef void (*ptrCBK)(void); //define pointer to function type
ptrCBK addrsToCall=0; // create variable from ptrCBK type

/*************************************************************************************************************************************/
/********************************************** SW Interrupt Call Back Function ******************************************************/
/*************************************************************************************************************************************/
void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	/*Setting the Address of Vector table of the Application*/
	SCB_VTOR = VECTOR_TABLE_ADDRESS;
	/*Jumping to the First address in the Entry Point of the application*/
	addrsToCall= *(ptrCBK *)ENTRY_POINT_ADDRESS;
	addrsToCall();
}

/*************************************************************************************************************************************/
/********************************************************* Main Function *************************************************************/
/*************************************************************************************************************************************/
void main()
{

	/*Initialize The RCC Peripheral and all about it*/


	/* Enable HSI clock */
	MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
	/* Check that HSI ready state */
	if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSI) == CLK_SOURCE_READY)
	{
		/*Select HSI as a system clock*/
		MRCC_voidSetClkSource(sys_clk_HSI);
		/*Disable HSE and PLL system clock*/
		MRCC_voidSetCLKSatus(CLK_HSE, STATUS_DISABLE);
		MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
	}
	//:Enable GPIO PORTA
	MRCC_voidSetPeripheralStaus(Bus_AHB1,AHB1_GPIOA , STATUS_ENABLE);
	//:Enable RCC UART
	MRCC_voidSetPeripheralStaus(Bus_APB2,APB2_USART1 , STATUS_ENABLE);

	/*Initialize the GPIO Pins Tx and Rx of the UART*/
	GPIO_PinConfig_t PinConfigTX9=
	{.PinNumber=PIN9,
			.PinMode=Mode_OutputAFPP,
			.OutputSpeed=Speed_Low
	};
	GPIO_PinConfig_t PinConfigRX10=
	{.PinNumber=PIN10,
			.PinMode=Mode_OutputAFPP,
			.OutputSpeed=Speed_Low
	};
	//:Enable GPIO pin_mode pin9 TX AFPP
	MGPIO_Init(GPIOA, & PinConfigTX9);
	MGPIO_SetAlternateFun(GPIOA,PIN9, AF7);
	//:Enable GPIO pin_mode pin10 RX
	MGPIO_Init(GPIOA, & PinConfigRX10);
	MGPIO_SetAlternateFun(GPIOA,PIN10 , AF7);

	//:start the UART with baud rate 9600 ,start TX&RX
	MUSART_voidInit(USART_1);
	//:sysTck_voidInit();
	SysTick_DelayMS(5000);
	SysTick_CallBack(func);
	//start sys_tick timer for 5 seconds and after them jump to Application
	SysTick_Start();

	while(timeOutFlag==0)
	{
		/* to check the status of receiving records from UART */
		u8 recStatus;
		//put the received data in the Record buffer
		recStatus =MUSART_u8ReceiveByteSync(USART_1,5000,&recBuffer[recCounter]);

		/*that means that data received*/
		if (recStatus==1)
		{
			/* Stop the 5 seconds timer counts */
			SysTick_Stop();

			/*waiting the end of the hex line */
			if (recBuffer[recCounter]=='\n')
			{
				/*to start to fill the array from the beginning after writing in flash the received record*/
				recCounter=0;
				/* Erase the flash memory in the fist record only */
				if (writeRequest==1)
				{
					//:Flash erase ();
					MFLASH_voidAreaErase();
					/* Flash erased first record only */
					writeRequest=0;
				}
				/*parse record*/
				Parser_voidParseRecord(recBuffer);
				/*USART Transmit "ok" */
				/*to tell the serial tool to send the second line*/
				MUSART_Error_tSendStringSync(USART_1, "ok" ,5000U);

			}
			else
			{
				/* increment counter of buffer until the end of record -> '\n' */
				recCounter++;
			}

		}
		else
		{
			/*meaning that no update is received
			  waiting until the timer counts reaches 0 then jump to App
			 */
		}
	}

}



// ----------------------------------------------------------------------------
