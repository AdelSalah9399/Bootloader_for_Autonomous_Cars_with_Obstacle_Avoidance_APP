#include "TIMER.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"



void MTIMER3_Init(u8 Chanel)
{
	GPIO_t* GPIOx = NULL;
	GPIO_PinConfig_t PinConfig = {.PinMode = Mode_OutputAFPP, .OutputSpeed = Speed_High};
	switch (Chanel)
	{
		case Chanel_1:
			GPIOx = GPIOA;
			PinConfig.PinNumber = PIN6;
			break;
		case Chanel_2:
			GPIOx = GPIOA;
			PinConfig.PinNumber = PIN7;
			break;
		case Chanel_3:
			GPIOx = GPIOB;
			PinConfig.PinNumber = PIN0;
			break;
		case Chanel_4:
			GPIOx = GPIOB;
			PinConfig.PinNumber = PIN1;
			break;
	}
	u8 PwmPort = (GPIOx == GPIOA) ? AHB1_GPIOA : AHB1_GPIOB;
	MRCC_voidSetPeripheralStaus(Bus_AHB1, PwmPort, STATUS_ENABLE);
	MGPIO_Init(GPIOx, &PinConfig);
	MGPIO_SetAlternateFun(GPIOx, PinConfig.PinNumber, AF2);

	/*Enable Timer3 clock to be the same as APB1 clock = 16 MHz*/
	MRCC_voidSetPeripheralStaus(Bus_APB1, APB1_TIM3, STATUS_ENABLE);
}

void MTimer_GeneratePWM(TIMER_t* Timer, u8 Chanel, u32 Frequency, u16 Duty)
{
	/*Set Capture/Compare 1 as output */
	switch (Chanel)
	{
		case Chanel_1: Timer->CCMR1 &= ~TIMER_CCMR1_CC1S;	break;
		case Chanel_2: Timer->CCMR1 &= ~TIMER_CCMR1_CC2S;	break;
		case Chanel_3: Timer->CCMR2 &= ~TIMER_CCMR2_CC3S;	break;
		case Chanel_4: Timer->CCMR2 &= ~TIMER_CCMR2_CC4S;	break;
	}


	/*Configure the output compare channel for PWM mode1*/
	switch (Chanel)
	{
		case Chanel_1: Timer->CCMR1 |= TIMER_CCMR1_OC1M_PWM1;	break;
		case Chanel_2: Timer->CCMR1 |= TIMER_CCMR1_OC2M_PWM1;	break;
		case Chanel_3: Timer->CCMR2 |= TIMER_CCMR2_OC3M_PWM1;	break;
		case Chanel_4: Timer->CCMR2 |= TIMER_CCMR2_OC4M_PWM1;	break;
	}

	/* Output Compare 1 preload enable */
	switch (Chanel)
	{
		case Chanel_1: Timer->CCMR1 |= TIMER_CCMR1_OC1PE;	break;
		case Chanel_2: Timer->CCMR1 |= TIMER_CCMR1_OC2PE;	break;
		case Chanel_3: Timer->CCMR2 |= TIMER_CCMR2_OC3PE;	break;
		case Chanel_4: Timer->CCMR2 |= TIMER_CCMR2_OC4PE;	break;
	}

	/*Set counter direction as up-counter*/
	Timer->CR1 &= ~(TIMER_CR1_DIR | TIMER_CR1_CMS);

	/*Enable Auto-reload preload */
	Timer->CR1 |= TIMER_CR1_ARPE;

	/*Enable output pin for the selected chanel*/
	Timer->CCER |= 1 << (Chanel * 4);

	/*Configure the timer prescaler and period to generate the desired frequency*/
	Timer->ARR = ARR_Value;
	Timer->PSC = Timer_Clk / (Frequency * ARR_Value) - 1;

	/*Set the initial duty cycle*/
	switch (Chanel)
	{
		case Chanel_1: Timer->CCR1 = ARR_Value * Duty / Max_Duty;	break;
		case Chanel_2: Timer->CCR2 = ARR_Value * Duty / Max_Duty;	break;
		case Chanel_3: Timer->CCR3 = ARR_Value * Duty / Max_Duty;	break;
		case Chanel_4: Timer->CCR4 = ARR_Value * Duty / Max_Duty;	break;
	}

	/* Initialize all the registers */
	Timer->EGR |= TIMER_EGR_UG;

	/*Start the counter*/
	Timer->CR1 |= TIMER_CR1_CEN;
}
