/*********************************************************************************************************************************
* AUTHOR           	  				VERSION									DATE 						DESCRIPTION 	   	 	 *
* Adel Salah El-Din	  				1.0.0 								6 June,2023					- Initial Creation			 *
**********************************************************************************************************************************/
/**********************************************************************************************************************************
* ! Title      	: USART Driver                                                        						                      *
* ! File Name	: USART_APP.c                                                       							               	  *
* ! Description : This file has the USART functions Implementations 										    	          	  *
* ! Compiler  	: GNU ARM cross Compiler                                            							                  *
* ! Target 	  	: STM32F401 (M-4) Micro-Controller                                         							              *
* ! Layer 	  	: MCAL -Driver Layer-                  						                            			  		      *
**********************************************************************************************************************************/

/**************************************************** Library Inclusions *********************************************************/

/************************************************** Lower Layer Inclusions *******************************************************/

/************************************************** Self Layer Inclusions ********************************************************/

/************************************************** Self Files Inclusions ********************************************************/
#include "USART.h"
/************************************************** Global Variables **************************************************************/
static void (*USARTx_CallBack[3])(void)={NULL,NULL,NULL};

/************************************************** CR1-Registers BITS ***********************************************************/
#define SBK_BIT					    0
#define RWU_BIT					    1
#define RE_BIT					    2
#define TE_BIT					    3
#define IDLEIE_BIT					4
#define RXNEIE_BIT					5
#define TCIE_BIT					6
#define TXEIE_BIT					7
#define PEIE_BIT					8
#define PS_BIT					    9
#define PCE_BIT					    10
#define WAKE_BIT					11
#define M_BIT					    12
#define UE_BIT					    13
#define OVER8_BIT					15
/************************************************** CR2-Registers BITS ****************************************************************/
#define STOP_BITS				    12
#define CLKEN_BIT					11
#define CPOL_BIT				    10
#define CPHA_BIT				    9
/************************************************** Status-Registers BITS ****************************************************************/
#define RXNE 						5
#define TC 							6
#define TXE 						7
/************************************************** ENABLE-DISABLE ********************************************************************/
#define ENABLE				    	1
#define DISABLE				    	0
/************************************************** YES-NO ****************************************************************************/
#define YES							1
#define NO							0
/************************************************** PARITY TYPE **********************************************************************/
#define EVEN						0
#define ODD							1
/************************************************** OVERSAMPLING *********************************************************************/
#define OVER_SAMPLE_8				1
#define OVER_SAMPLE_16				0
/************************************************** DATA LENGHT **********************************************************************/
#define WORD_LENGHT_D8				0
#define WORD_LENGHT_D9				1
/************************************************** STOP BITS ************************************************************************/
#define STOP0_5						1
#define STOP1						0
#define STOP2						2
#define STOP1_5						3
/************************************************** CLK POLARITY ****************************************************************/
#define CLK_LOW_VALUE				0
#define CLK_HIGH_VALUE				1
/************************************************** CLK PHASE ****************************************************************/
#define FirstCLK_FirstCapture		0
#define SecondCLK_FirstCapture		1
/*******************************************************************************************************************************/
/************************************************Data Types*********************************************************************/
/*******************************************************************************************************************************/


typedef enum{
	USART_OK,
	USART_ERROR,
	USART_Timeout
}USART_State;

/***********************************************************************************************************************************/
/************************************************static functions prototypes********************************************************/
/***********************************************************************************************************************************/

static USART_State USART_WaitOnFlagTimeout(u32 USART,u32 Flag,u32 TimeOut);


/***********************************************************************************************************************************/
/***********************************************interface functions implementation**************************************************/
/***********************************************************************************************************************************/


Error_t MUSART_voidInit(u32 USART)
{
	if(USART==USART_1)
	{
		USART1->CR1 =((T_EN << TE_BIT)   	   | (R_EN << RE_BIT)          	 | (PARITY_EN << PCE_BIT) 	 |
						(PEINT_EN << PEIE_BIT) | (TX_INT_EN << TXEIE_BIT)    | (RX_INT_EN << RXNEIE_BIT) |
						(TCINT_EN << TCIE_BIT) | (IDLE_INT_EN << IDLEIE_BIT))|
						(WORD_LENGHT << M_BIT) | (OVER_SAMPLE << OVER8_BIT)	 | (PARITY_SELECTION<<PS_BIT)|(SEND_BREAK<<SBK_BIT)|(RECEIVE_WAKEUP<<WAKE_BIT);

		USART1->CR2 =((CLK_EN << CLKEN_BIT) | (STOP_BIT << STOP_BITS) | (CLK_POLARITY << CPOL_BIT) | (CLK_PHASE << CPHA_BIT));
		USART1->BRR = BUDE_RATE;
		USART1->SR  = 0x0;
		USART1->CR1 |= (USART_EN << UE_BIT);
		return NoError;
	}
	else if(USART==USART_2)
	{
		USART2->CR1 =((T_EN << TE_BIT)   	   | (R_EN << RE_BIT)            | (PARITY_EN << PCE_BIT)    |
						(PEINT_EN << PEIE_BIT) | (TX_INT_EN << TXEIE_BIT)    | (RX_INT_EN << RXNEIE_BIT) |
						(TCINT_EN << TCIE_BIT) | (IDLE_INT_EN << IDLEIE_BIT))|
						(WORD_LENGHT << M_BIT) | (OVER_SAMPLE << OVER8_BIT)	 | (PARITY_SELECTION<<PS_BIT)|(SEND_BREAK<<SBK_BIT)|(RECEIVE_WAKEUP<<WAKE_BIT);

		USART2->CR2 =((CLK_EN << CLKEN_BIT) | (STOP_BIT << STOP_BITS) | (CLK_POLARITY << CPOL_BIT) | (CLK_PHASE << CPHA_BIT));
		USART2->BRR = BUDE_RATE;
		USART2->CR1 |= (USART_EN << UE_BIT);
		return NoError;
	}
	else if(USART==USART_6)
	{
		USART6->CR1 =((T_EN << TE_BIT)   	   | (R_EN << RE_BIT)            | (PARITY_EN << PCE_BIT)    |
						(PEINT_EN << PEIE_BIT) | (TX_INT_EN << TXEIE_BIT)    | (RX_INT_EN << RXNEIE_BIT) |
						(TCINT_EN << TCIE_BIT) | (IDLE_INT_EN << IDLEIE_BIT))|
						(WORD_LENGHT << M_BIT) | (OVER_SAMPLE << OVER8_BIT)	 | (PARITY_SELECTION<<PS_BIT)|(SEND_BREAK<<SBK_BIT)|(RECEIVE_WAKEUP<<WAKE_BIT);

		USART6 ->CR2 =((CLK_EN << CLKEN_BIT) | (STOP_BIT << STOP_BITS) | (CLK_POLARITY << CPOL_BIT) | (CLK_PHASE << CPHA_BIT));
		USART6 ->BRR = BUDE_RATE;
		USART6->CR1 |= (USART_EN << UE_BIT);
		return NoError;
	}
	else
		return Error;
}


Error_t MUSART_Error_tSendByteSync(u32 USART,u8 Data_Byte,u32 TimeOut)
{
	switch (USART)
	{
	case USART_1:
				/*wait until the Data Register is empty*/
				USART_WaitOnFlagTimeout(USART,TXE,TimeOut);
				USART1->DR = Data_Byte;
				/*wait until the Data Transmission completed*/
				USART_WaitOnFlagTimeout(USART,TC,TimeOut);
				/*Clear the flag*/
				USART1->SR &= ~(1<<TC);
				break;
	case USART_2:
				/*wait until the Data Register is empty*/
				USART_WaitOnFlagTimeout(USART,TXE,TimeOut);
				USART2->DR = Data_Byte;
				/*wait until the Data Transmission completed*/
				USART_WaitOnFlagTimeout(USART,TC,TimeOut);
				/*Clear the flag*/
				USART2->SR &= ~(1<<TC);
				break;
	case USART_6:
				/*wait until the Data Register is empty*/
				USART_WaitOnFlagTimeout(USART,TXE,TimeOut);
				USART6->DR = Data_Byte;
				/*wait until the Data Transmission completed*/
				USART_WaitOnFlagTimeout(USART,TC,TimeOut);
				/*Clear the flag*/
				USART6->SR &= ~(1<<TC);
				break;
	default: return Error;
	}
	return NoError;
}


u8 MUSART_u8ReceiveByteSync(u32 USART,u32 TimeOut)
{
	/*wait until receiving is complete*/
	if(USART_WaitOnFlagTimeout(USART,RXNE,TimeOut)==USART_OK)
	{
		if     (USART==USART_1) return ((USART1->DR) & 0xFF);
		else if(USART==USART_2) return ((USART2->DR) & 0xFF);
		else if(USART==USART_6) return ((USART6->DR) & 0xFF);
		else 					{/*return nothing*/};
	}
	return USART_ERROR;
}


Error_t MUSART_Error_tSendStringSync(u32 USART,u8 *Send_Strg,u32 TimeOut)
{
	while ((*Send_Strg) != '\0')
	{
		MUSART_Error_tSendByteSync(USART,(*Send_Strg),TimeOut);
		Send_Strg++;
	}
	return NoError;
}


void MUSART_voidReceiveStringSync(u32 USART,char Receive_Strg[],u32 Lenght,u32 TimeOut)
{	u32 Iterator;
	u32 temp;
	for(Iterator=0;Iterator<=Lenght;Iterator++)
	{
		temp =MUSART_u8ReceiveByteSync(USART,TimeOut);
		if(temp =='\r')
			Receive_Strg[Iterator] = '\0';
		else if(Iterator<Lenght-1)
			Receive_Strg[Iterator] = temp;
	}
}


/**********************************************************************************************************************************/
/**************************************************CALL BACK FUNCTIONS*************************************************************/
/**********************************************************************************************************************************/

void USARTx_voidSetCallBack(u32 USART,void (*ptr)(void))
{
	if (ptr!= NULL)
	{
		switch(USART)
		{
		case USART_1: USARTx_CallBack[0]=ptr; break;
		case USART_2: USARTx_CallBack[1]=ptr; break;
		case USART_6: USARTx_CallBack[2]=ptr; break;
		default     : /*Error*/				  break;
		}
	}
	else
	{
		/*DO NOTHING*/
	}
}

/**********************************************************************************************************************************/
/**************************************************IRQs Handlers*******************************************************************/
/**********************************************************************************************************************************/

void USART1_IRQHandler(void)
{
	if(USARTx_CallBack[0]!=NULL)
	{
		USARTx_CallBack[0]();
		USART1->SR =0;
	}
}

void USART2_IRQHandler(void)
{
	if(USARTx_CallBack[1]!=NULL)
	{
		USARTx_CallBack[1]();
		USART2->SR =0;
	}
}

void USART6_IRQHandler(void)
{
	if(USARTx_CallBack[2]!=NULL)
	{
		USARTx_CallBack[2]();
		USART6->SR =0;
	}
}


/***********************************************************************************************************************************/
/*************************************************static functions implementations**************************************************/
/***********************************************************************************************************************************/


static USART_State USART_WaitOnFlagTimeout(u32 USART,u32 Flag,u32 TimeOut)
{
	u32 Local_TimeOut_Counter=0;
	if(USART==USART_1)
	{
		if(Flag==TXE)
		{
			while( (((USART1->SR >> TXE )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==RXNE)
		{
			while( (((USART1->SR >> RXNE )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==TC)
		{
			while( (((USART1->SR >> TC )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else
		{
			return USART_ERROR;
		}
		return USART_OK;
	}
	if(USART==USART_2)
	{
		if(Flag==TXE)
		{
			while( (((USART2->SR >> TXE )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==RXNE)
		{
			while( (((USART2->SR >> RXNE )&1) ==0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==TC)
		{
			while( (((USART2->SR >> TC )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else
		{
			return USART_ERROR;
		}
		return USART_OK;
	}
	if(USART==USART_6)
	{
		if(Flag==TXE)
		{
			while( (((USART6->SR >> TXE )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==RXNE)
		{
			while( (((USART6->SR >> RXNE )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else if(Flag==TC)
		{
			while( (((USART6->SR >> TC )&1) == 0) && (TimeOut>Local_TimeOut_Counter))
			{
				Local_TimeOut_Counter++;
			}
			if(TimeOut<Local_TimeOut_Counter)
				return USART_Timeout;
		}
		else
		{
			return USART_ERROR;
		}
		return USART_OK;
	}
	else
	{
		return USART_ERROR;
	}
}
