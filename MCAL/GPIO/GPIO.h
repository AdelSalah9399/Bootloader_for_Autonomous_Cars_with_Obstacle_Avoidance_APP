#ifndef GPIO_H_
#define GPIO_H_

/*********************includes*********************/
#include "../STM32F401C8T6/STM32F401C8T6.h"


/*********************configuration references*********************/

/*@reference GPIO_PINS_DEFINE*/
#define	PIN0	(u8)0
#define	PIN1	(u8)1
#define	PIN2	(u8)2
#define	PIN3	(u8)3
#define	PIN4	(u8)4
#define	PIN5	(u8)5
#define	PIN6	(u8)6
#define	PIN7	(u8)7
#define	PIN8	(u8)8
#define	PIN9	(u8)9
#define	PIN10	(u8)10
#define	PIN11	(u8)11
#define	PIN12	(u8)12
#define	PIN13	(u8)13
#define	PIN14	(u8)14
#define	PIN15	(u8)15

/*@reference GPIO_MODE_DEFINE*/
#define Mode_InputFloating		(u8)0b0000		/*floating input*/
#define Mode_InputPU			(u8)0b0001		/*input pull up*/
#define Mode_InputPD			(u8)0b0010		/*input pull down*/
#define Mode_OutputPP			(u8)0b0100		/*output push pull*/
#define Mode_OutputOD			(u8)0b0101		/*output open drain*/
#define Mode_OutputAFPP			(u8)0b1000		/*alternate function output push pull*/
#define Mode_OutputAFOD			(u8)0b1001		/*alternate function output open drain*/
#define Mode_InputAnalog		(u8)0b1100		/*analog input*/

/*@reference GPIO_SPEED_DEFINE*/
#define Speed_Low				(u8)0			/*low speed pin mode*/
#define Speed_Medium			(u8)1			/*medium speed pin mode*/
#define Speed_High				(u8)2			/*high speed pin mode*/
#define Speed_VeryHigh			(u8)3			/*very high speed pin mode*/

/*@reference GPIO_STATE_DEFINE*/
#define Pin_Low					(u8)0			/*low logic on the pin*/
#define Pin_High				(u8)1			/*high logic on the pin*/


/*@reference GPIO_ERROR_DEFINE*/
#define NoError					(u8)0			/*no errors encountered*/
#define Error					(u8)1			/*one or more errors encountered*/

/*@reference GPIO_AF_DEFINE*/
#define AF0						(u8)0			/*Alternative function 0*/
#define AF1						(u8)1			/*Alternative function 1*/
#define AF2						(u8)2			/*Alternative function 2*/
#define AF3						(u8)3			/*Alternative function 3*/
#define AF4						(u8)4			/*Alternative function 4*/
#define AF5						(u8)5			/*Alternative function 5*/
#define AF6						(u8)6			/*Alternative function 6*/
#define AF7						(u8)7			/*Alternative function 7*/
#define AF8						(u8)8			/*Alternative function 8*/
#define AF9						(u8)9			/*Alternative function 9*/
#define AF10					(u8)10			/*Alternative function 10*/
#define AF11					(u8)11			/*Alternative function 11*/
#define AF12					(u8)12			/*Alternative function 12*/
#define AF13					(u8)13			/*Alternative function 13*/
#define AF14					(u8)14			/*Alternative function 14*/
#define AF15					(u8)15			/*Alternative function 15*/

/*********************configuration structures*********************/
typedef struct
{
	u8 	PinNumber;			/*specifies GPIO pin to be configured, this parameter must be set based on @reference GPIO_PINS_DEFINE*/
	u8  PinMode;			/*specifies the operation mode for the selected pin, this parameter must be set based on @reference GPIO_MODE_DEFINE*/
	u8	OutputSpeed;		/*specifies the speed for the selected pin, this parameter must be set based on @reference GPIO_SPEED_DEFINE*/
}
GPIO_PinConfig_t;


/*********************APIs supported by MCAL GPIO driver*********************/

/*
 * @Function    - MGPIO_Init
 * @Brief       - Initializes GPIOx PINy according to specified parameters in PinConfig
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinConfig: pointer which contains the information of the selected GPIO pin
 * @Return      - None
 * @Notes       - STM32F401CCU6 has GPIO A, B, C, D, E, H but UQFN48 package has only A, B and parts of C, H exported as external pins from the MCU
 */
void MGPIO_Init(GPIO_t* GPIOx, GPIO_PinConfig_t* PinConfig);

/*
 * @Function    - MGPIO_DeInit
 * @Brief       - Resets all GPIOx registers
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * @Return      - None
 * @Notes       - None
 */
void MGPIO_DeInit(GPIO_t* GPIOx);

/*
 * @Function    - MGPIO_ReadPin
 * @Brief       - Read the input value from a specified GPIO pin
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinNumber: The number of the pin to be read
 * @Return      - The input value to the pin according to @reference GPIO_STATE_DEFINE
 * @Notes       - None
 */
u8 MGPIO_ReadPin(GPIO_t* GPIOx, u8 PinNumber);

/*
 * @Function    - MGPIO_ReadPort
 * @Brief       - Read the input value from a specified GPIO port
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * @Return      - The input value to the port
 * @Notes       - None
 */
u16 MGPIO_ReadPort(GPIO_t* GPIOx);

/*
 * @Function    - MGPIO_WritePin
 * @Brief       - write a value to a specified GPIO pin
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinNumber: the number of the pin to be read
 * 				- PinValue: the value to be written to the pin
 * @Return      - None
 * @Notes       - None
 */
void MGPIO_WritePin(GPIO_t* GPIOx, u8 PinNumber, u8 PinValue);

/*
 * @Function    - MGPIO_WritePort
 * @Brief       - write a value to a specified GPIO port
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PortValue: the value to be written to the port
 * @Return      - None
 * @Notes       - None
 */
void MGPIO_WritePort(GPIO_t* GPIOx, u16 PortValue);

/*
 * @Function    - MGPIO_TogglePin
 * @Brief       - Toggle the value of a specified GPIO pin
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinNumber: The number of the pin to be read
 * @Return      - None
 * @Notes       - None
 */
void MGPIO_TogglePin(GPIO_t* GPIOx, u8 PinNumber);

/*
 * @Function    - MGPIO_SetAlternateFun
 * @Brief       - Set the alternative function of a specified GPIO pin
 * @Arguments   - GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinNumber: The number of the pin to be set as alternative function
 * 				- AF: number of the alternative function to be connected to the pin
 * @Return      - None
 * @Notes       - None
 */
void MGPIO_SetAlternateFun(GPIO_t* GPIOx, u8 PinNumber, u8 AF);


#endif
