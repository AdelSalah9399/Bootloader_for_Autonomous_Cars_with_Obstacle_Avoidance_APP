/*
 * Parse.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Muham
 */
/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						      DESCRIPTION 		   			      *
* 1.0.0 					BOOTLOADER Development team    		22 JUN,2023					      Initial Creation	                  *
**************************************************************************************************************************************/

/**************************************************************************************************************************************
* ! Title      	: Parse SWC                                           							                     		 	      *
* ! File Name	: parse.c                                   		                   						                      	  *
* ! Description : This file has the implementation of Parsing functions  					  						                  *
* ! Compiler  	: GNU ARM cross Compiler                                            							                      *
* ! Target 	  	: STM32F401cc Micro-Controller                                         							                      *
* ! Layer 	  	: APP 	                  						                                         							  *
**************************************************************************************************************************************/
/**************************************************** Defines  ************************************************************************/
#define FLASH_START_ADDRESS				0x08000000
#define BUFFER_SIZE						100
/**************************************************** Library Inclusions *************************************************************/
#include "MCAL/STM32F401C8T6/STM32F401C8T6.h"
//#include "../Common/BIT_MATH.h"
//#include "../Common/STD_TYPES.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include "MCAL/FLASH/FLASH.h"
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/

/***************************************************** Global Variables **************************************************************/

u16 DataBuffer[BUFFER_SIZE] = {0};
u32 Address = FLASH_START_ADDRESS;

/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
 * Function Name	: ASCIIToHex																				                      *
 * Parameters (in)	: Char_ASCII																					                  *
 * Parameters (out)	: None																						                      *
 * Return value		: uint8																						                      *
 * Description		: Function To convert ASCII to Hex									                      						  *
 **************************************************************************************************************************************/

u8 ASCIIToHex(u8 Char_ASCII)
{
	u8 Result;
	if(Char_ASCII >= '0' && Char_ASCII <= '9')
	{
		Result = Char_ASCII - '0';
	}
	else
	{
		/* if the number from A to F sub ASCII of 7 '55' */
		Result = Char_ASCII - '7';
	}
	return Result;
}

/**************************************************************************************************************************************
 * Function Name	: ParseData																				                          *
 * Parameters (in)	: None																						                      *
 * Parameters (out)	: RecordBuffer																	                     			  *
 * Return value		: None																						                      *
 * Description		: Function To parse data									                                                      *
 **************************************************************************************************************************************/
void ParseData(u8 * RecordBuffer)
{
	u8  CharCount   = 0;
	u8  LoopCounter = 0;
	u16 Data= 0;

	/* Extracting the Character Count of Record Digit 1 and Digit 2 					*
	 * Note: Digit 0 is ':" 															*/
	CharCount = (ASCIIToHex(RecordBuffer[1]) * 16) + (ASCIIToHex(RecordBuffer[2]));

	/* Make Sure the Lower Address are Cleared*/
	Address = Address & 0xFFFF0000;

	/* Extracting the Address  of Record from : (Digit 3 to Digit 6) --> Lower 16 bits of Address 	 *
	 * Note: Digit 3 is the MSB shifted to the left by 12  											 */
	Address = Address | (ASCIIToHex(RecordBuffer[3]) << 12) | (ASCIIToHex(RecordBuffer[4]) << 8) | (ASCIIToHex(RecordBuffer[5]) << 4) | (ASCIIToHex(RecordBuffer[6]));

	/* Extracting the Data of Record 16 bits starting from Digit 9 to Digit 12 */
	/* Note : "CharCount/2" because we record 2 Bytes every count not 1 Byte */
	for (LoopCounter = 0; LoopCounter < ((CharCount/2)); LoopCounter++)
	{

		Data = 	(ASCIIToHex(RecordBuffer[(LoopCounter * 4) + 9]) << 4) |
				(ASCIIToHex(RecordBuffer[(LoopCounter * 4) +10])) 	   |
				(ASCIIToHex(RecordBuffer[(LoopCounter * 4) +11]) << 12)|
				(ASCIIToHex(RecordBuffer[(LoopCounter * 4) +12]) << 8);

		/* Assigning the Data in the Data Array*/
		DataBuffer[LoopCounter] =  Data;
	}

	/* Flashing the Data into the Application Section */
	MFLASH_voidWrite(Address, DataBuffer, (CharCount/2) );
}

/**************************************************************************************************************************************
 * Function Name	: Parser_voidParseRecord																				          *
 * Parameters (in)	: RecordBuffer																                         			  *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To parse record								                                                          *
 **************************************************************************************************************************************/
void Parser_voidParseRecord( v_u8 * RecordBuffer)
{

	switch(RecordBuffer[8])
	{
	case '0' :

		/* Data Record */
		ParseData(RecordBuffer);

		break;

	case '1' :
		func();
		/* End of Hex  Record */
		break;

	case '4' :
		/* Upper Address Record */
		break;
	}
}
