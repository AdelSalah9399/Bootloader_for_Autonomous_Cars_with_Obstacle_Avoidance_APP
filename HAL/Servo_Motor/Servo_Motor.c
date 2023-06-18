/*********************includes*********************/
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "Servo_Motor.h"

void HServo_Init(void)
{
	/*Initialize the timer chanels connected to servo control pin according to the config file*/
	MTIMER3_Init(Servo_ControlChanel);
}

void HServo_Rotate(u16 Angle)
{
	/*set the servo control pin to be driven by PWM signal of frequency = Servo_Frequency, and duty cycle corresponding to the desired angle*/
	MTimer_GeneratePWM(TIMER3, Servo_ControlChanel, Servo_Frequency, Angle);
}
