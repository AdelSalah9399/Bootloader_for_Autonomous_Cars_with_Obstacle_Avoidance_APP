#ifndef TIMER_H_
#define TIMER_H_

/*********************includes*********************/
#include "../STM32F401C8T6/STM32F401C8T6.h"

#define  Timer_Clk       		 16000000UL              /*!<Timer Clock value      		                */
#define  ARR_Value       		 1000               	 /*!<ARR register value      		                */
#define  Max_Duty       		 1000                    /*!<Duty cycle must be between 0, Max_Duty         */

#define Chanel_1				 0
#define Chanel_2				 1
#define Chanel_3				 2
#define Chanel_4				 3


#define  TIMER_CR1_ARPE          (u32)0x0080             /*!<Auto-reload preload enable                    */
#define  TIMER_CR1_DIR           (u32)0x0010             /*!<Direction                                     */
#define  TIMER_CR1_CMS           (u32)0x0060             /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIMER_CR2_MMS_2         (u32)0x0040             /*!<Bit 2                                         */
#define  TIMER_SMCR_MSM          (u32)0x0080             /*!<Master/slave mode                             */

#define  TIMER_CCMR1_CC1S        (u32)0x0003             /*!<Capture/Compare 1 Selection                   */
#define  TIMER_CCMR1_CC2S        (u32)0x0300             /*!<Capture/Compare 2 Selection                   */
#define  TIMER_CCMR2_CC3S        (u32)0x0003             /*!<Capture/Compare 3 Selection                   */
#define  TIMER_CCMR2_CC4S        (u32)0x0300             /*!<Capture/Compare 4 Selection                   */

#define  TIMER_CCMR1_OC1PE       BIT3_MASK               /*!<Output Compare 1 Preload enable               */
#define  TIMER_CCMR1_OC2PE       BIT11_MASK              /*!<Output Compare 2 Preload enable               */
#define  TIMER_CCMR2_OC3PE       BIT3_MASK               /*!<Output Compare 3 Preload enable               */
#define  TIMER_CCMR2_OC4PE       BIT11_MASK              /*!<Output Compare 4 Preload enable               */

#define  TIMER_CCMR1_OC1M_PWM1   (u32)0x0060             /*!<Output Compare 1 PWM1 mode					   */
#define  TIMER_CCMR1_OC2M_PWM1   (u32)0x6000             /*!<Output Compare 1 PWM1 mode					   */
#define  TIMER_CCMR2_OC3M_PWM1   (u32)0x0060             /*!<Output Compare 1 PWM1 mode					   */
#define  TIMER_CCMR2_OC4M_PWM1   (u32)0x6000             /*!<Output Compare 1 PWM1 mode					   */

#define  TIMER_CCER_CC1P         (u32)0x0002             /*!<Capture/Compare 1 output Polarity             */
#define  TIMER_EGR_UG            (u32)0x0001             /*!<Update Generation                             */
#define  TIMER_CCER_CC1E         (u32)0x0001             /*!<Capture/Compare 1 output enable               */
#define  TIMER_BDTR_MOE          (u32)0x8000             /*!<Main Output enable                            */
#define  TIMER_CR1_CEN           (u32)0x0001             /*!<Counter enable                                */
#define  TIMER_CCER_CC1E         (u32)0x0001             /*!<Counter enable                                */


/*********************APIs supported by MCAL TIMER driver*********************/

/*
 * @Function    - MTIMER3_Init
 * @Brief       - Initalizes Timer3 Chanelx correspondibg GPIO pin
 * @Arguments   - Chanel: the chanel of Timer3 to be initialized
 * @Return      - None
 * @Notes       - None
 */
void MTIMER3_Init(u8 Chanel);


/*
 * @Function    - MTimer_GeneratePWM
 * @Brief       - Generates a PWM signal at the given frequency and duty cycle on a specified pin
 * @Arguments   - Timer: the timer instance to be configured in thr PWM mode
 * 				- Frequency: the frequency of the output PWM signal
 * 				- Duty: the duty cycle of the output PWM signal
 * 				- GPIOx (x can be from A..H): select the GPIO peripheral instance
 * 				- PinNumber: The number of the pin to be configured as PWM pin
 * @Return      - None
 * @Notes       - The duty cycle must be a number between 0 and Max_Duty
 */
void MTimer_GeneratePWM(TIMER_t* Timer, u8 Chanel, u32 Frequency, u16 Duty);


#endif
