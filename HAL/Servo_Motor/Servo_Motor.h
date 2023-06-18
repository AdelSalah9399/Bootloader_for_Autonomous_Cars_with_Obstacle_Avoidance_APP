#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

/*********************includes*********************/
#include "Servo_Motor_Config.h"

/*@reference SERVO_ANGLE_DEFINE*/
#define Angle_0 			(u16)50
#define Angle_90			(u16)75
#define Angle_180			(u16)100


/*********************APIs supported by HAL Servo_Motor driver*********************/

/*
 * @Function    - HServo_Init
 * @Brief       - Initializes servo motor pins according to specified parameters in the config file
 * @Arguments   - None
 * @Return      - None
 * @Notes       - None
 */
void HServo_Init(void);

/*
 * @Function    - HServo_Rotate
 * @Brief       - Rotates the servo motor shaft by a specific angle
 * @Arguments   - Angle: the angle to be rotated by the servo motor
 * @Return      - None
 * @Notes       - The angles represent the duty cycle for thr PWM function in the range of [0, 1000]
 */
void HServo_Rotate(u16 Angle);


#endif
