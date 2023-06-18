#ifndef STM32F401C8T6_H_
#define STM32F401C8T6_H_

/*********************includes*********************/
#include "../../UTIL/Types.h"


/*********************Base addresses for Memories*********************/
#define FLASH_MEMORY_BASE				0x08000000UL
#define SYSTEM_MEMORY_BASE				0x1FFF0000UL
#define SRAM_MEMORY_BASE				0x20000000UL

#define PERIPHERALS_BASE				0x40000000UL
#define CORTEX_M4_PERIPHERALS_BASE		0xE0000000UL

/*********************Base addresses for Cortex-M4 internal Peripherals*********************/
/*********************NVIC Peripheral*********************/
#define NVIC_BASE    					0xE000E100UL

/*********************Base addresses for AHB2 BUS Peripherals*********************/
/*********************USB OTG FS Peripheral*********************/
#define USB_BASE 						0x50000000UL

/*********************Base addresses for AHB1 BUS Peripherals*********************/
/*********************RCC Peripheral*********************/
#define RCC_BASE 						0x40023800UL
/*********************Flash Peripheral*********************/
#define FLASH_BASE     					0x40023C00

/*********************GPIO Peripheral*********************/
/*Ports A, B are fully included in UQFN48 package (except for PB11)*/
#define GPIOA_BASE						0x40020000UL
#define GPIOB_BASE						0x40020400UL

/*Ports C, H are partially included in UQFN48 package*/
#define GPIOC_BASE						0x40020800UL
#define GPIOH_BASE						0x40021C00UL

/*Ports D, E are not included in UQFN48 package*/
#define GPIOD_BASE						0x40020C00UL
#define GPIOE_BASE						0x40021000UL


/*********************Base addresses for APB2 BUS Peripherals*********************/
/*********************SYSCFG Peripheral*********************/
#define SYSCFG_BASE						0x40013800UL


/*********************EXTI Peripheral*********************/
#define EXTI_BASE						0x40013C00UL

/*********************USART Peripheral*********************/
#define USART1_BASE						0x40011000UL
#define USART2_BASE						0x40004400UL
#define USART6_BASE						0x40011400UL


/*********************Base addresses for APB1 BUS Peripherals*********************/
#define TIM1_BASE						0x40010000UL
#define TIM2_BASE						0x40000000UL
#define TIM3_BASE						0x40000400UL
#define TIM4_BASE						0x40000800UL
#define TIM5_BASE						0x40000C00UL


/*********************Peripheral registers*********************/
/*********************NVIC Peripheral**********************/
typedef struct
{
	v_u32 ISER[8];
	v_u32 Res_1[24];
	v_u32 ICER[8];
	v_u32 Res_2[24];
	v_u32 ISPR[8];
	v_u32 Res_3[24];
	v_u32 ICPR[8];
	v_u32 Res_4[24];
	v_u32 IABR[8];
	v_u32 Res_5[56];
	v_u8  IPR[240];
	v_u32 Res_6[580];
	v_u32 STIR;
}
NVIC_t;

/*********************RCC Peripheral**********************/
typedef struct
{
	v_u32 CR;
	v_u32 PLLCFGR;
	v_u32 CFGR;
	v_u32 CIR;
	v_u32 AHB1RSTR;
	v_u32 AHB2RSTR;
	v_u32 reserved0;
	v_u32 reserved1;
	v_u32 APB1RSTR;
	v_u32 APB2RSTR;
	v_u32 reserved2;
	v_u32 reserved3;
	v_u32 AHB1ENR;
	v_u32 AHB2ENR;
	v_u32 reserved4;
	v_u32 reserved5;
	v_u32 APB1ENR;
	v_u32 APB2ENR;
	v_u32 reserved6;
	v_u32 reserved7;
	v_u32 AHB1LPENR;
	v_u32 AHB2LPENR;
	v_u32 reserved8;
	v_u32 reserved9;
	v_u32 APB1LPENR;
	v_u32 APB2LPENR;
	v_u32 reserved10;
	v_u32 reserved11;
	v_u32 BDCR;
	v_u32 CSR;
	v_u32 reserved12;
	v_u32 reserved13;
	v_u32 SSCGR;
	v_u32 PLLI2SCFGR;
	v_u32 reserved14;
	v_u32 DCKCFGR;
}
RCC_t;

/*********************GPIO Peripheral*********************/
typedef struct
{
	v_u32 MODER;
	v_u32 OTYPER;
	v_u32 OSPEEDR;
	v_u32 PUPDR;
	v_u32 IDR;
	v_u32 ODR;
	v_u32 BSRR;
	v_u32 LCKR;
	v_u32 AFRL;
	v_u32 AFRH;
}
GPIO_t;

/*********************SYSCFG Peripheral*********************/
typedef struct
{
	v_u32 MEMRMP;
	v_u32 PMC;
	v_u32 EXTICR1;
	v_u32 EXTICR2;
	v_u32 EXTICR3;
	v_u32 EXTICR4;
	v_u32 CMPCR;
}
SYSCFG_t;


/*********************Flash Peripheral*********************/
typedef struct
{
	v_u32 FLASH_ACR;
	v_u32 FLASH_KEYR;
	v_u32 FLASH_OPTKEYR;
	v_u32 FLASH_SR;
	v_u32 FLASH_CR;
	v_u32 FLASH_OPTCR;

}FLASH_t;


/*********************EXTI Peripheral*********************/
typedef struct
{
	v_u32 IMR;
	v_u32 EMR;
	v_u32 RTSR;
	v_u32 FTSR;
	v_u32 SWIER;
	v_u32 PR;
}
EXTI_t;

/*********************USART Peripheral*********************/
typedef struct
{
	v_u32 SR;
	v_u32 DR;
	v_u32 BRR;
	v_u32 CR1;
	v_u32 CR2;
	v_u32 CR3;
	v_u32 GTPR;
}
USART_t;

/*********************TIMER Peripheral*********************/
typedef struct
{
	v_u32 CR1;              /*!< TIM control register 1,              Address offset: 0x00 */
	v_u32 CR2;              /*!< TIM control register 2,              Address offset: 0x04 */
	v_u32 SMCR;             /*!< TIM slave mode control register,     Address offset: 0x08 */
	v_u32 DIER;             /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
	v_u32 SR;               /*!< TIM status register,                 Address offset: 0x10 */
	v_u32 EGR;              /*!< TIM event generation register,       Address offset: 0x14 */
	v_u32 CCMR1;            /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
	v_u32 CCMR2;            /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
	v_u32 CCER;             /*!< TIM capture/compare enable register, Address offset: 0x20 */
	v_u32 CNT;              /*!< TIM counter register,                Address offset: 0x24 */
	v_u32 PSC;              /*!< TIM prescaler,                       Address offset: 0x28 */
	v_u32 ARR;              /*!< TIM auto-reload register,            Address offset: 0x2C */
	v_u32 RESERVED0;		/*!< Reserved,							  Address offset: 0x30 */
	v_u32 CCR1;             /*!< TIM capture/compare register 1,      Address offset: 0x34 */
	v_u32 CCR2;             /*!< TIM capture/compare register 2,      Address offset: 0x38 */
	v_u32 CCR3;             /*!< TIM capture/compare register 3,      Address offset: 0x3C */
	v_u32 CCR4;             /*!< TIM capture/compare register 4,      Address offset: 0x40 */
	v_u32 RESERVED1;	    /*!< Reserved,						   	  Address offset: 0x44 */
	v_u32 DCR;              /*!< TIM DMA control register,            Address offset: 0x48 */
	v_u32 DMAR;             /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
	v_u32 OR;               /*!< TIM option register,                 Address offset: 0x50 */
}
TIMER_t;


/*********************Peripheral Instants*********************/
#define NVIC		((NVIC_t*)NVIC_BASE)

#define RCC			((RCC_t*)RCC_BASE)

#define GPIOA		((GPIO_t*)GPIOA_BASE)
#define GPIOB		((GPIO_t*)GPIOB_BASE)
#define GPIOC		((GPIO_t*)GPIOC_BASE)
#define GPIOD		((GPIO_t*)GPIOD_BASE)
#define GPIOE		((GPIO_t*)GPIOE_BASE)
#define GPIOH		((GPIO_t*)GPIOH_BASE)

#define SYSCFG		((SYSCFG_t*)SYSCFG_BASE)

#define FLASH		((FLASH_t*)FLASH_BASE)

#define EXTI		((EXTI_t*)EXTI_BASE)

#define USART1		((USART_t*)USART1_BASE)
#define USART2		((USART_t*)USART2_BASE)
#define USART6		((USART_t*)USART6_BASE)

#define TIMER2		((TIMER_t*)TIM2_BASE)
#define TIMER3		((TIMER_t*)TIM3_BASE)
#define TIMER4		((TIMER_t*)TIM4_BASE)
#define TIMER5		((TIMER_t*)TIM5_BASE)

/*********************interrupt indices*********************/
//#define USART1_IrqNum	37
//#define USART1_IrqNum	38
//#define USART1_IrqNum	71

/*********************clock enable Macros*********************/
#define RCC_GPIOA_CLK_EN()			(RCC->AHB1ENR |= 1 << 0)
#define RCC_GPIOB_CLK_EN()			(RCC->AHB1ENR |= 1 << 1)
#define RCC_GPIOC_CLK_EN()			(RCC->AHB1ENR |= 1 << 2)
#define RCC_GPIOD_CLK_EN()			(RCC->AHB1ENR |= 1 << 3)
#define RCC_GPIOE_CLK_EN()			(RCC->AHB1ENR |= 1 << 4)

#define RCC_SYSCFG_CLK_EN()			(RCC->APB2ENR |= 1 << 14)

#define RCC_USART1_CLK_EN()			(RCC->APB2ENR |= 1 << 4)
#define RCC_USART2_CLK_EN()			(RCC->APB1ENR |= 1 << 17)
#define RCC_USART6_CLK_EN()			(RCC->APB2ENR |= 1 << 5)

/*********************Generic Macros*********************/


#endif
