#include "GPIO.h"


void MGPIO_Init(GPIO_t* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	/*select the pin mode to be: input, general purpose output, alternative function, or analog*/
	u32 temp = GPIOx->MODER;
	temp &= ~(3 << (PinConfig->PinNumber * 2));
	temp |= ((PinConfig->PinMode >> 2) << (PinConfig->PinNumber * 2));
	GPIOx->MODER = temp;

	/*if the pin is to be configured as output, select its output mode and output speed*/
	if (((PinConfig->PinMode >> 2) == 1) || ((PinConfig->PinMode >> 2) == 2))
	{
		/*set the output mode to push-pull or open-drain*/
		switch (PinConfig->PinMode & 1)
		{
			case 0: GPIOx->OTYPER &= ~(1 << PinConfig->PinNumber); break;
			case 1: GPIOx->OTYPER |=  (1 << PinConfig->PinNumber); break;
		}

		/*select the pin's output speed*/
		temp = GPIOx->OSPEEDR;
		temp &= ~(3 << (PinConfig->PinNumber * 2));
		temp |= (PinConfig->OutputSpeed << (PinConfig->PinNumber * 2));
		GPIOx->OSPEEDR = temp;
	}

	/*if the pin is to be configured as input, select its connection to be floating, pull up or pull down*/
	else if ((PinConfig->PinMode >> 2) == 0)
	{
		temp = GPIOx->PUPDR;
		temp &= ~(3 << (PinConfig->PinNumber * 2));
		temp |= ((PinConfig->PinMode & 0x3) << (PinConfig->PinNumber * 2));
		GPIOx->PUPDR = temp;
	}
}

void MGPIO_DeInit(GPIO_t* GPIOx)
{
	switch ((u32)GPIOx)
	{
		case GPIOA_BASE:
			RCC->AHB1RSTR |= 0x1;		/*reset all GPIOA peripheral registers*/
			RCC->AHB1RSTR &= ~0x1;		/*GPIOA peripheral is ready to use after reset*/
			break;
		case GPIOB_BASE:
			RCC->AHB1RSTR |= 0x2;		/*reset all GPIOB peripheral registers*/
			RCC->AHB1RSTR &= ~0x2;		/*GPIOB peripheral is ready to use after reset*/
			break;
		case GPIOC_BASE:
			RCC->AHB1RSTR |= 0x4;		/*reset all GPIOC peripheral registers*/
			RCC->AHB1RSTR &= ~0x4;		/*GPIOC peripheral is ready to use after reset*/
			break;
		case GPIOD_BASE:
			RCC->AHB1RSTR |= 0x8;		/*reset all GPIOD peripheral registers*/
			RCC->AHB1RSTR &= ~0x8;		/*GPIOD peripheral is ready to use after reset*/
			break;
		case GPIOE_BASE:
			RCC->AHB1RSTR |= 0x10;		/*reset all GPIOE peripheral registers*/
			RCC->AHB1RSTR &= ~0x10;		/*GPIOE peripheral is ready to use after reset*/
			break;
	}
}

u8 MGPIO_ReadPin(GPIO_t* GPIOx, u8 PinNumber)
{
	/*if the corresponding bit in IDR register is 1, return high*/
	if (GPIOx->IDR & (1 << PinNumber))
	{
		return Pin_High;
	}
	/*if the corresponding bit in IDR register is 0, return low*/
	else
	{
		return Pin_Low;
	}
}

u16 MGPIO_ReadPort(GPIO_t* GPIOx)
{
	return (u16)(GPIOx->IDR);	/*return the value of IDR register of the selected port*/
}

void MGPIO_WritePin(GPIO_t* GPIOx, u8 PinNumber, u8 PinValue)
{
	switch (PinValue)
	{
		/*set the corresponding bit in the lower half of BSRR register to write high to the specified pin*/
		case Pin_High: GPIOx->BSRR = 1 << PinNumber; break;
		/*set the corresponding bit in the upper half of BSRR register to write low to the specified pin*/
		case Pin_Low: GPIOx->BSRR  = 1 << (PinNumber + 16); break;
	}
}

void MGPIO_WritePort(GPIO_t* GPIOx, u16 PortValue)
{
	/*write the output value to the ODR register*/
	GPIOx->ODR = (u32)PortValue;
}

void MGPIO_TogglePin(GPIO_t* GPIOx, u8 PinNumber)
{
	/*toggle the corresponding in ODR register*/
	GPIOx->ODR ^= (1 << PinNumber);
}

void MGPIO_SetAlternateFun(GPIO_t* GPIOx, u8 PinNumber, u8 AF)
{
	u32* AFR;
	AFR = (PinNumber < PIN8) ? &GPIOx->AFRL : &GPIOx->AFRH;
	*AFR |= AF << ((PinNumber % 8) * 4);
}
