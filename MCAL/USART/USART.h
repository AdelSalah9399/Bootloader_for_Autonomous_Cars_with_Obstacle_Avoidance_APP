/*********************************************************************************************************************************
* AUTHOR           	  				VERSION									DATE 						DESCRIPTION 	   	 	 *
* Adel Salah El-Din	  				1.0.0 								6 June,2023					- Initial Creation			 *
**********************************************************************************************************************************/
/**********************************************************************************************************************************
* ! Title      	: USART Driver                                                        						                      *
* ! File Name	: USART_Driver.h                                                       							              	  *
* ! Description : This file has the USART functions prototypes and Options Macros for function Arguments      	          		  *
* ! Compiler  	: GNU ARM cross Compiler                                            							                  *
* ! Target 	  	: STM32F401 (M-4) Micro-Controller                                         							              *
* ! Layer 	  	: MCAL -Driver Layer-                  						                            			  		      *
**********************************************************************************************************************************/
#ifndef USART_USART_DRIVER_H_
#define USART_USART_DRIVER_H_
/************************************************includes**************************************************************************/
#include "../STM32F401C8T6/STM32F401C8T6.h"
#include "USART_Config.h"
/************************************************USARTx****************************************************************************/
#define USART_1				1
#define USART_2				2
#define USART_6				6

/***********************************************************************************************************************************/
/************************************************Functions Prototypes***************************************************************/
/***********************************************************************************************************************************/

/***************************************************************************
* Function Name		: MUSART_voidInit
* Parameters (in)	: options from [USART_x]
* Parameters (out)	: NONE
* Return value		: enum Error_t
* Description		: Function used to initialize the selected USART
* Constrains		: you must enable the selected peripheral CLK first
* *************************************************************************/
Error_t MUSART_voidInit(u32 USART);

/***************************************************************************
* Function Name		: MUSART_Error_tSendByte
* Parameters (in)	: options from [USART_x - u8 DATA send ,timeout]
* Parameters (out)	: NONE
* Return value		: enum Error_t
* Description		: Function used to send byte
* Constrains		: NONE
* *************************************************************************/
Error_t MUSART_Error_tSendByteSync(u32 USART,u8 Data_Byte,u32 TimeOut);

/***************************************************************************
* Function Name		: MUSART_u8ReceiveByte
* Parameters (in)	: options from [USART_x , timeout]
* Parameters (out)	: NONE
* Return value		: u8 (received byte)
* Description		: Function used to receive a byte
* Constrains		: NONE
* *************************************************************************/
u8 MUSART_u8ReceiveByteSync(u32 USART,u32 TimeOut);

/***************************************************************************
* Function Name		: MUSART_Error_tSendString
* Parameters (in)	: options from [USART_x - pointer to string - timeout]
* Parameters (out)	: NONE
* Return value		: enum Error_t
* Description		: Function used to Send string
* Constrains		: NONE
* *************************************************************************/
Error_t MUSART_Error_tSendStringSync(u32 USART,u8 *Send_Strg,u32 TimeOut);

/***************************************************************************
* Function Name		: MUSART_voidReceiveStringSync
* Parameters (in)	: options from [USART_x - array of chars - size of array - timeout]
* Parameters (out)	: NONE
* Return value		: void
* Description		: Function used to Receive string
* Constrains		: NONE
* *************************************************************************/
void MUSART_voidReceiveStringSync(u32 USART,char Receive_Strg[],u32 Lenght,u32 TimeOut);

/***************************************************************************
* Function Name		: USARTx_voidSetCallBack
* Parameters (in)	: options from [USART_X - pointer to function]
* Parameters (out)	: pointer to function																						                      *
* Return value		: void
* Description		: CALL BACK FUNCTION
* Constrains		: NONE
* *************************************************************************/
void USARTx_voidSetCallBack(u32 USART,void (*ptr)(void));
/*################################ DONT FORGET Chose the ALF pins ########################################*/

#endif /* USART_USART_DRIVER_H_ */
