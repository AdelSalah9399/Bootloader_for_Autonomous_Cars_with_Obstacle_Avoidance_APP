#ifndef _DC_MOTOR_H_
#define _DC_MOTOR_H_

/*********************includes*********************/
#include "DC_Motor_Config.h"

/*********************includes*********************/
#define Direction_Stop          (u8)0
#define Direction_Forward       (u8)1
#define Direction_Backward      (u8)2
#define Direction_Right         (u8)3
#define Direction_Left          (u8)4


/*********************APIs supported by HAL Servo_Motor driver*********************/

/*
 * @Function    - HMotor_Init
 * @Brief       - Initializes DC motor pins according to specified parameters in the config file
 * @Arguments   - None
 * @Return      - None
 * @Notes       - None
 */
void HMotor_Init(void);

/*
 * @Function    - HMotor_Move
 * @Brief       - Moves the DC motors by a certain speed in a specified direction
 * @Arguments   - Direction: the direction of motion of the car
 * 				- Speed: the speed of rotation of the motors
 * @Return      - None
 * @Notes       - The speeds represent the duty cycle for thr PWM function in the range of [0, 1000]
 */
void HMotor_Move(u8 Direction, u16 Speed);


#endif
