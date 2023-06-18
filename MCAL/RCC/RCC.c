#include "RCC.h"

/* Interface Implementation Functions */

Error_t MRCC_voidSetCLKSatus(u32 CLK, u8 STATUS)
{
	Error_t ErrState = NoError;
	/*Switch on the Clock Source which one*/
	switch(CLK)
	{
	case CLK_HSI:
		/*Switch The Status Wanted Enable Or Disable*/
		switch(STATUS)
		{
		case STATUS_ENABLE:

			/*Enable The HSI Clock Source*/
			RCC->CR |=CLK_HSI;
			break;

		case STATUS_DISABLE:

			/*Disable The HSI Clock Source*/
			RCC->CR &=~CLK_HSI;
			break;
		default:
			/* input : status Error*/
			ErrState=Error;
			break;
		}
		break;

		case CLK_HSE:

			/*Switch The Status Wanted Enable Or Disable*/
			switch(STATUS)
			{
			case STATUS_ENABLE:

				/*Enable The HSE Clock Source*/
				RCC->CR |=CLK_HSE;
				break;

			case STATUS_DISABLE:

				/*Disable The HSE Clock Source*/
				RCC->CR &=~ CLK_HSE;
				break;

			default:
				/* input : status Error*/
				ErrState=Error;
				break;
			}
			break;

			case CLK_PLL:

				/*Switch The Status Wanted Enable Or Disable*/
				switch(STATUS)
				{
				case STATUS_ENABLE:

					/*Enable The PLL Clock Source*/
					RCC->CR |=CLK_PLL;
					break;

				case STATUS_DISABLE:
					/*Disable The PLL Clock Source*/
					RCC->CR &=~CLK_PLL;
					break;

				default:
					/* input : status Error*/
					ErrState=Error;
					break;
				}
				break;

				default:
					/* input : Clock source Error */
					ErrState=Error;
					break;
	}
	return ErrState;
}

u8 MRCC_u8CheckClkSourceReady(u8 CLK_RDY)
{
	/*Variable To Store The Return Value That the Clock Source is Ready or Not*/
	u8 ReturnStatus = CLK_SOURCE_READY;
	/*Variable To Store The Time Out Value Of Waiting*/
	u32 TimeOut = 0;

	/*Busy Waiting to The Clock Source To Be Ready*/
	while(((RCC->CR>>CLK_RDY) & 0x01 ) == CLK_SOURCE_NOT_READY)
		// while(GET_BIT(RCC -> CR, CLK_RDY) == CLK_SOURCE_NOT_READY)
	{
		/*Incrementing the Time Out Value*/
		TimeOut++;
		/*Check If The Time Out Or Not*/
		if (TimeOut == CLK_SOURCE_READY_TIME_OUT)
		{
			/*Return That the Clock Source Not Ready*/
			ReturnStatus = CLK_SOURCE_NOT_READY;
			break;
		}
	}

	return ReturnStatus;
}

Error_t MRCC_voidSetClkSource(u32 sys_clk)
{
	Error_t ErrorState=NoError;
	u32 temp;
	switch (sys_clk)
	{
	case sys_clk_HSI:

		/*Set The HSI To be the System Clock Source By Set SW Bits 0b00*/
		temp = RCC -> CFGR ;
		temp &= CFGR_SW_BITS_MASK;
		temp |= sys_clk_HSI;
		RCC -> CFGR = temp;
		break;

	case sys_clk_HSE:

		/*Set The HSE To be the System Clock Source By Set SW Bits 0b01*/
		temp =RCC -> CFGR;
		temp &= CFGR_SW_BITS_MASK;
		temp |= sys_clk_HSE;
		RCC -> CFGR = temp;
		break;

	case sys_clk_PLL:

		/*Set The PLL To be the System Clock Source By Set SW Bits 0b10*/
		temp =RCC -> CFGR;
		temp &= CFGR_SW_BITS_MASK;
		temp |= sys_clk_PLL;
		RCC -> CFGR = temp;
		break;

	default:

		/* Input : Select system clock Error */
		ErrorState=Error;
		break;
	}
	return ErrorState;
}

Error_t MRCC_voidSetPLLConfig(u32 PLL_SRC,u8 PLLM,u16 PLLN,u8 PLLP,u8 PLLQ)
{
	Error_t ErrorState= NoError ;

	switch (PLL_SRC)
	{
		case PLL_SRC_HSI:
			RCC->PLLCFGR &= PLL_SRC_HSI;
			break;
		case PLL_SRC_HSE:
			RCC->PLLCFGR |= PLL_SRC_HSE ;
			break;
		default:
			ErrorState = Error;
			break;
	}

	if((PLLM>=2 && PLLM<=62) && (PLLN >= 192 && PLLN <= 432) && (PLLQ >=2 && PLLQ <=15))
	{

		/* masking of PLLM bits and set the PLLM value */
		u32 temp= RCC->PLLCFGR;
		temp &= PLLM_MASK;
		temp |= PLLM<<PLLM_startBIT ;
		RCC->PLLCFGR= temp;

		/*masking of PLLN bits and set the PLLN value */
		temp =RCC->PLLCFGR;
		temp &= PLLN_MASK;
		temp |= PLLN<<PLLN_startBIT;
		RCC->PLLCFGR=temp;


		/*Masking of PLLP bits and set the PLLP value */
		temp =RCC->PLLCFGR;
		temp &= PLLP_MASK;
		temp |= PLLP<<PLLP_startBIT;
		RCC->PLLCFGR=temp;

		/*Masking of PLLQ bits and set the PLLQ value */
		temp =RCC->PLLCFGR;
		temp &= PLLQ_MASK;
		temp |= PLLQ<<PLLQ_starBIT;
		RCC->PLLCFGR=temp;
	}
	else
	{
		ErrorState = Error ;
	}

	return ErrorState;
}

Error_t MRCC_voidSetPeripheralStaus(u8 Bus,u8 Peripheral,u8 STATUS)
{
	Error_t ErrorState = NoError;
	switch(Bus)
	{
	case Bus_AHB1:
		switch(STATUS)
		{
		case STATUS_ENABLE:
			/* Enable the clock of peripheral on AHB1 Bus */

			RCC->AHB1ENR |= (1<<Peripheral);
			break;

		case STATUS_DISABLE:

			/* Disable the clock of peripheral on AHB1 Bus */
			RCC->AHB1ENR &= ~(1<< Peripheral);
			break;

		default:
			/* Input peripheral of AHB1 bus Error */
			ErrorState = Error ;
			break;
		}
		break;

		case Bus_AHB2:
			switch(STATUS)
			{
			case STATUS_ENABLE:
				/* Enable the clock of peripheral on AHB1 Bus */
				RCC->AHB2ENR |=(1<<Peripheral);
				break;

			case STATUS_DISABLE:
				/* Disable the clock of peripheral on AHB1 Bus */
				RCC->AHB2ENR &= ~ (1<<Peripheral);
				break;

			default:
				/* Input peripheral of AHB1 bus Error */
				ErrorState = Error ;
				break;
			}

			break;

		case Bus_APB1:
			switch(STATUS)
			{
			case STATUS_ENABLE:

				/* Enable the clock of peripheral on AHB1 Bus */
				RCC->APB1ENR |= (1<<Peripheral);
				break;
			case STATUS_DISABLE:

				/* Disable the clock of peripheral on AHB1 Bus */
				RCC->APB1ENR &= ~(1<<Peripheral);
				break;
			default:
				/* Input peripheral of AHB1 bus Error */
				ErrorState = Error ;
				break;
			}

		break;

		case Bus_APB2:
			switch(STATUS)
			{
			case STATUS_ENABLE:
				/* Enable the clock of peripheral on AHB1 Bus */
				RCC->APB2ENR |= (1<<Peripheral);
				break;
			case STATUS_DISABLE:
				/* Disable the clock of peripheral on AHB1 Bus */
				RCC->APB2ENR &= ~ (1<<Peripheral);
				break;
			default:
				/* Input peripheral of AHB1 bus Error */
				ErrorState = Error ;
				break;
			}
			break;

	default :
		/* Input bus Error */
		ErrorState = Error ;
		break;
	}
	return ErrorState;
}

void MRCC_voidSetBusPrescaler(u8 Bus, u8 PRESCALER)
{
	u32 temp = RCC->CFGR;
	temp &=~(0xF<<Bus);
	temp |= PRESCALER << Bus;
	RCC->CFGR=temp;
}

void MRCC_voidInit(void)
{

	/*Checking If The Clock Source Configure To be HSE*/
	 #if CLK_SOURCE == CLK_HSE

		/*Enable The HSE Clock Source*/
			MRCC_voidSetCLKSatus(CLK_HSE, STATUS_ENABLE);

		/*Check That The HSE Clock Source is Ready and Stable*/
		 if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSE) != CLK_SOURCE_NOT_READY)
		 {
			/*Selecting That HSE Is the Clock Source of The System*/
			 MRCC_voidSetClkSource(sys_clk_HSE);
			/*Disable The HSI Clock Source*/
			 MRCC_voidSetCLKSatus(CLK_HSI, STATUS_DISABLE);
			/*Disable The PLL Clock Source*/
			 MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
		 }


	/*Checking If The Clock Source Configure To be HSI*/
  	 #elif CLK_SOURCE == CLK_HSE

		/*Enable The HSI Clock Source*/
		 MRCC_voidSetClkStatus(CLK_HSI, STATUS_ENABLE);

		/*Check That The HSI Clock Source is Ready and Stable*/
		 if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSI) != CLK_SOURCE_NOT_READY)
		 {
			/*Selecting That HSI Is the Clock Source of The System*/
			 MRCC_voidSetClkSource(sys_clk_HSI);
			/*Disable The HSE Clock Source*/
			 MRCC_voidSetClkStatus(CLK_HSE, STATUS_DISABLE);
			/*Disable The PLL Clock Source*/
			 MRCC_voidSetClkStatus(CLK_PLL, STATUS_DISABLE);
		 }


	/*Checking If The Clock Source Configure To be PLL*/
	 #elif CLK_SOURCE == PLL
		/*Checking If The Clock Source of PLL Configure To be HSE_SOURCE*/
		 #if PLL_SOURCE == PLL_SRC_HSE

			/*Enable The HSE Clock Source*/
			 MRCC_voidSetClkStatus(CLK_HSE, STATUS_ENABLE);

			/*Check That The HSE Clock Source is Ready and Stable*/
			 if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSE) != CLK_SOURCE_NOT_READY)
			 {
				/*Selecting That HSI Is the Clock Source of The System*/
				 MRCC_voidSetClkSource(sys_clk_HSI);
				/*Disable The PLL Clock Source To Configure it*/
				 MRCC_voidSetClkStatus(CLK_PLL, DISABLE);


				/*Configure HSI Division Factor and PLL Multiplication Factor, Set HSI as PLL Source*/
				MRCC_SetPLLConfiguration(PLL_MULTIPLICATION_FACTOR, HSE, HSE_DIVISION_FACTOR);
				/*Setting AHB , APB1, APB2 Buses Prescaler*/
				MRCC_voidSetBusesPrescalers(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);


				/*Enable The PLL Clock Source*/
				 MRCC_voidSetClkStatus(CLK_PLL, ENABLE);

				/*Check That The PLL Clock Source is Ready and Stable*/
				if(MRCC_u8CheckClkSourceReady(CLK_RDY_PLL) != CLK_SOURCE_NOT_READY)
				{
					/*Selecting That PLL Is the Clock Source of The System*/
					 MRCC_voidSetClkSource(sys_clk_PLL);
					/*Disable The HSI Clock Source*/
					 MRCC_voidSetClkStatus(CLK_HSI, DISABLE);
				}
			}


		/*Checking If The Clock Source of PLL Configure To be HSI_SOURCE*/
		 #elif PLL_SOURCE == PLL_SRC_HSI

			/*Enable The HSI Clock Source*/
			 MRCC_voidSetClkStatus(HSI, ENABLE);

			/*Check That The HSI Clock Source is Ready and Stable*/
			 if(MRCC_u8CheckClkSourceReady(HSI_RDY) != CLK_SOURCE_NOT_READY)
			 {
				/*Selecting That HSI Is the Clock Source of The System*/
				 MRCC_voidSetClkSource(HSI);
				/*Disable The PLL Clock Source To Configure it*/
				 MRCC_voidSetClkStatus(PLL, DISABLE);


				/*Configure HSI Division Factor and PLL Multiplication Factor, Set HSI as PLL Source*/
				MRCC_SetPLLConfiguration(PLL_MULTIPLICATION_FACTOR, HSI, HSE_DIVISION_FACTOR);
				/*Setting AHB , APB1, APB2 Buses Prescaler*/
				MRCC_voidSetBusesPrescalers(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);


				/*Enable The PLL Clock Source*/
				 MRCC_voidSetClkStatus(PLL, ENABLE);

				/*Check That The PLL Clock Source is Ready and Stable*/
				if(MRCC_u8CheckClkSourceReady(PLL_RDY) != CLK_SOURCE_NOT_READY)
				{
					/*Selecting That PLL Is the Clock Source of The System*/
					 MRCC_voidSetClkSource(PLL);
					/*Disable The HSE Clock Source*/
					 MRCC_voidSetClkStatus(HSE, DISABLE);
				}
			}

		 #else
			/*Printing an Error Message That PLL_SOURCE Configration Error*/
			 #error"PLL_SOURCE Configuration Error"
		 #endif
#else
	/*Printing an Error Message That CLOCK_SOURCE Configration Error*/
	 #error"CLOCK_SOURCE Configuration Error"
 #endif

}


