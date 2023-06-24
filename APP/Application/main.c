#include "Bootloader_GP/MCAL/TIMER/TIMER.h"
#include "Bootloader_GP/MCAL/RCC/RCC.h"
#include "Bootloader_GP/HAL/DC_Motor/DC_Motor.h"
#include "Bootloader_GP/HAL/Servo_Motor/Servo_Motor.h"
#include "Bootloader_GP/HAL/UltraSonic/UltraSonic.h"

/*Time delay for each system component*/
#define Delay_Initial			100
#define Delay_Forward			50
#define Delay_Backward			150
#define Delay_Servo			200
#define Delay_LR			500

/*Motor speed in the range of [0, 1000]*/
#define Motor_Speed			1000

/*Angles definition for servo motor rotation*/
#define Angle_Left			120
#define Angle_Right			20
#define Angle_Forward			60

/*Mininmum distance to avoid objects*/
#define Obstacle_Distance		40

/*Delay macro*/
#define delay(time)			for (u32 i = 0; i < 10000 * time; i++)


void main()
{
	/*Initialize system clock*/
	MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
	MRCC_voidSetClkSource(sys_clk_HSI);

	/*Initialize the DC motors*/
	HMotor_Init();

	/*Initialize the servo motor*/
	HServo_Init();
	HServo_Rotate(Angle_Forward);

	/*Initialize the ultrasonic sensor*/
	HUltraSonic_voidInit();

	/*Define left distance and right distance variables*/
	v_f32 Distance_Left = 0.0, Distance_Right = 0.0;


	while(1)
	{
		/*Move forward at the beginning*/
		HMotor_Move(Direction_Forward, Motor_Speed);
		delay(Delay_Initial);

		/*Move forward as long as the front distance is less than the allowance*/
		while (HUltraSonic_floatGetDistance() > Obstacle_Distance)
		{
			delay(Delay_Forward);
		}

		/*In case there is an obstacle, take a step backward then stop*/
		HMotor_Move(Direction_Backward, Motor_Speed);
		delay(Delay_Backward);
		HMotor_Move(Direction_Stop, 0);

		/*Rotate the sensor left and right using the servo motor to see which distance is smaller*/
		HServo_Rotate(Angle_Left);
		delay(Delay_Servo);
		Distance_Left = HUltraSonic_floatGetDistance();
		HServo_Rotate(Angle_Right);
		delay(Delay_Servo);
		Distance_Right = HUltraSonic_floatGetDistance();

		/*Return the sensor to the idle position*/
		HServo_Rotate(Angle_Forward);

		/*If the left distance is smaller, turn right then continue moving forward again*/
		if (Distance_Left < Distance_Right)
		{
			HMotor_Move(Direction_Right, Motor_Speed);
			delay(Delay_LR);
		}

		/*If the right distance is smaller, turn left then continue moving forward again*/
		else
		{
			HMotor_Move(Direction_Left, Motor_Speed);
			delay(Delay_LR);
		}
	}
}
