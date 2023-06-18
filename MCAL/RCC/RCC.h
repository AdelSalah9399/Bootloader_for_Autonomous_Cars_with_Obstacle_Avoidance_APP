#ifndef RCC_H_
#define RCC_H_

/*********************includes*********************/
#include "../STM32F401C8T6/STM32F401C8T6.h"


/**************************************************************************************************************************************
* Function :Set clock status arguments                                                                                               *
* MACRO		: 	To Select The Clock Status To The System															         		 *
* Clock Options	:	CLK_HSI			/	 CLK_HSE	/	 CLK_PLL	/																 *
* Status options: 	STATUS_ENABLE /	STATUS_DISABLE		  									       		 							 *
**************************************************************************************************************************************/
#define CLK_HSI								BIT0_MASK
#define CLK_HSE 							BIT16_MASK
#define CLK_PLL 							BIT24_MASK
#define STATUS_ENABLE 						1
#define STATUS_DISABLE 						0
/*****************************************************Function: PLL configuration arguments********************************************/
#define PLL_SRC_SEL					        22
#define PLL_SRC_HSI						    0xFFBFFFFF
#define PLL_SRC_HSE						    0X00400000

/*****************************************************Function :MRCC_voidInit*******************************************************/
/**************************************************************************************************************************************
* MACRO		: 	To Select The Clock Source To The System															         		  *
* options	:	CLK_HSI			/	 CLK_HSE	/	 CLK_PLL	/					  									       		  *
**************************************************************************************************************************************/
#define CLK_SOURCE 							CLK_HSE
/**************************************************************************************************************************************
* MACRO		: 	To Select The Clock Source To The PLL																         		  *
* options	:	PLL_SRC_HSI		/	 PLL_SRC_HSE		/				 															  *
**************************************************************************************************************************************/
#define PLL_SOURCE 							PLL_SRC_HSI
/*************************************************************************************************************************************/



/**************************************************************************************************************************************
* Function: Check clock ready arguments
* MACRO		: 	To Select check the ready status of the clock source															      *
* Clock Ready Options	:	CLK_RDY_HSI			/	 CLK_RDY_HSE	/	 CLK_RDY_PLL	/						   					  *
* Check Options: 	CLK_SOURCE_NOT_READY /	CLK_SOURCE_READY		  									       		 			      *
**************************************************************************************************************************************/
#define CLK_RDY_HSI 						1
#define CLK_RDY_HSE 						17
#define CLK_RDY_PLL 						25
#define CLK_SOURCE_NOT_READY    		  	0
#define CLK_SOURCE_READY    			  	1
#define CLK_SOURCE_READY_TIME_OUT 			50000
/*****************************************************Masking values of M,N,P,Q *******************************************************/
#define PLLM_MASK					        0xFFFFFFC0
#define PLLN_MASK					        0xFFFF803F
#define PLLQ_MASK					        0xF0FFFFFF
#define PLLP_MASK					        0xFFFCFFFF
#define PLLM_startBIT						0
#define PLLN_startBIT						6
#define PLLP_startBIT						16
#define PLLQ_starBIT						24
/*****************************************************PLLP Division Options***********************************************************/
#define PLLP_2							    0
#define PLLP_4							    1
#define PLLP_6							    2
#define PLLP_8							    3


/**************************************************************************************************************************************
* MACRO		: 	To Select The Clock Source To The System															         		  *
* options	:	sys_clk_HSI		/	 sys_clk_HSE	/	 sys_clk_PLL					  									          *
**************************************************************************************************************************************/
#define sys_clk_HSI						    0x00000000
#define sys_clk_HSE						    0x00000001
#define sys_clk_PLL						    0x00000010
#define CFGR_SW_BITS_MASK		    		0xFFFFFFFC
/*****************************************************Selected Bus of Peripheral***************************************************/
#define Bus_AHB1  						    1
#define Bus_AHB2  						    2
#define Bus_AHB 							4
#define Bus_APB1 						    10
#define Bus_APB2 						    13
/*****************************************************AHB1 Peripherals*************************************************************/
 #define AHB1_GPIOA	                        0
 #define AHB1_GPIOB	                        1
 #define AHB1_GPIOC	                        2
 #define AHB1_GPIOD	                        3
 #define AHB1_GPIOE	                        4
 #define AHB1_GPIOH	                        7
 #define AHB1_CRC	                        12
 #define AHB1_DMA1	                        21
 #define AHB1_DMA2	                        22
/*****************************************************AHB2 Peripherals*************************************************************/
#define AHB2_OTGFS	                        7
/*****************************************************APB1 Peripherals*************************************************************/
#define APB1_TIM2	                        0
#define APB1_TIM3	                        1
#define APB1_TIM4	                        2
#define APB1_TIM5	                        3
#define APB1_WWDG	                        11
#define APB1_SPI2	                        14
#define APB1_SPI3	                        15
#define APB1_USART2                         17
#define APB1_I2C1	                        21
#define APB1_I2C2	                        22
#define APB1_I2C3	                        23
/*****************************************************APB2 Peripherals*************************************************************/
#define APB2_TIM0	                        0
#define APB2_USART1                         4
#define APB2_USART6                         5
#define APB2_ADC1	                        8
#define APB2_SDIO 	                        11
#define APB2_SPI1	                        12
#define APB2_SPI4	                        13
#define APB2_SYSCFG	                        14
#define APB2_TIM9 	                        16
#define APB2_TIM10	                        17
#define APB2_TIM11	                        18
/**********************************************************AHB PRESCALER*********************************************************/
#define PRESCALER_AHB_2					    0x8
#define PRESCALER_AHB_4					    0x9
#define PRESCALER_AHB_8					    0xA
#define PRESCALER_AHB_16				    0xB
#define PRESCALER_AHB_64				    0xC
#define PRESCALER_AHB_128				    0xD
#define PRESCALER_AHB_256				    0xE
#define PRESCALER_AHB_512				    0xF
/**************************************************APB PRESCALER**********************************************************/
#define PRESCALER_APB_2						0x4
#define PRESCALER_APB_4						0x5
#define PRESCALER_APB_8						0x6
#define PRESCALER_APB_16					0x7
/*************************************************************************************************************************/
#define RCC_CFGR_Prescaller_BITS_MASK		0xFFFFC00F

/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: MRCC_voidInit																				                      *
* Parameters (in)	: None																							                  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To Initialize All The Configuration to The Clock Source 										          *
**************************************************************************************************************************************/
void MRCC_voidInit(void);
/**************************************************************************************************************************************
* Function Name		: MRCC_voidSetClkStatus																		                      *
* Parameters (in)	: u8 CLK, u8 STATUS											                     						  *
* Parameters (out)	: None																						                      *
* Return value		: Error_t																						                      *
* Description		: Function To Enable Or Disable Clock Sources												                      *
**************************************************************************************************************************************/
Error_t MRCC_voidSetCLKSatus(u32 CLK, u8 STATUS);
/**************************************************************************************************************************************
* Function Name		: MRCC_voidSetClkSource																		                      *
* Parameters (in)	: u8 sys_clk																	                     			  *
* Parameters (out)	: None																						                      *
* Return value		: Error_t																						                      *
* Description		: Function To Set the  Clock Sources To the System											                      *
**************************************************************************************************************************************/
Error_t MRCC_voidSetClkSource(u32 sys_clk);
/**************************************************************************************************************************************
* Function Name		: MRCC_u8CheckClkSourceReady																                      *
* Parameters (in)	: u8 CLK_RDY 																	                  			  *
* Parameters (out)	: None																						                      *
* Return value		: u8 ReturnStatus 															    	                          *
* Description		: Function To Check That the  Clock Sources is Ready										                      *
**************************************************************************************************************************************/
u8 MRCC_u8CheckClkSourceReady(u8 CLK_RDY);
/**************************************************************************************************************************************
* Function Name		: MRCC_voidSetPLLConfig																                      		  *
* Parameters (in)	: u8 PLL_SRC, u8 PLLM, u16 PLLN, u8 PLLP, u8 PLLQ 												  *				                  			  *
* Parameters (out)	: None																						                      *
* Return value		: Error_t 															    	                          			  *
* Description		: Function To configure the PLL Clock																			  *
* Wrong Configuration	: PLLM Invalid Values : >2 & <64	PLLN Invalid Values :>191 & <432		PLLQ Invalid Values : >2 & <16	  *					                      *
**************************************************************************************************************************************/
Error_t MRCC_voidSetPLLConfig(u32 PLL_SRC, u8 PLLM, u16 PLLN, u8 PLLP, u8 PLLQ);
/**************************************************************************************************************************************
* Function Name		: MRCC_voidSetPeripheralStaus															                          *
* Parameters (in)	: u8 Bus, u8 Peripheral, u8 STATUS 																	  *
* Parameters (out)	: None																						                      *
* Return value		: ReturnStatus 															    	                         		  *
* Description		: Function To set the peripheral status													                          *
**************************************************************************************************************************************/
Error_t MRCC_voidSetPeripheralStaus(u8 Bus, u8 Peripheral, u8 STATUS);
/**************************************************************************************************************************************
* Function Name		: MRCC_voidSetBusPrescaler															                          *
* Parameters (in)	: u8 Bus, u8 Prescaler																	  *
* Parameters (out)	: None																						                      *
* Return value		: None 															    	                         		  *
* Description		: Function To set the bus prescalar													                          *
**************************************************************************************************************************************/
void MRCC_voidSetBusPrescaler(u8 Bus, u8 PRESCALER);


#endif /* RCC_INTERFACE_H_ */
