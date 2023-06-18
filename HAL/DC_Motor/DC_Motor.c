/*********************includes*********************/
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "DC_Motor.h"
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/RCC/RCC.h"

void HMotor_Init(void)
{
	/*Initialize the timer chanels connected to Ena, Enb pins according to the config file*/
	MTIMER3_Init(L298_EnaChanel);
	MTIMER3_Init(L298_EnbChanel);

    /*set In1, In2, In3, In4 pins to be general purpose output push pull*/
    GPIO_PinConfig_t PinConfig = {.PinMode = Mode_OutputPP, .OutputSpeed = Speed_High};

    /*open the clock for In1, In2, In3, In4 port*/
    MRCC_voidSetPeripheralStaus(Bus_AHB1, L298_InPortClk, STATUS_ENABLE);

    /*set the L298 input pins numbers according to the config file*/
    PinConfig.PinNumber = L298_In1Pin;
    MGPIO_Init(L298_InPort, &PinConfig);

    PinConfig.PinNumber = L298_In2Pin;
    MGPIO_Init(L298_InPort, &PinConfig);

    PinConfig.PinNumber = L298_In3Pin;
    MGPIO_Init(L298_InPort, &PinConfig);

    PinConfig.PinNumber = L298_In4Pin;
    MGPIO_Init(L298_InPort, &PinConfig);
}

void HMotor_Move(u8 Direction, u16 Speed)
{
	/*set Ena, Enb pins to be driven by PWM signals of frequency = Motor_Frequency, and duty cycle corresponding to the desired speed*/
	MTimer_GeneratePWM(TIMER3, Chanel_1, Motor_Frequency, Speed);
	MTimer_GeneratePWM(TIMER3, Chanel_2, Motor_Frequency, Speed);

	/*set the direction of rotation of the 4 motors according to the specified motion direction*/
    switch (Direction)
    {
    	/*stop the 4 motors to stop the car*/
        case Direction_Stop:
            MGPIO_WritePin(L298_InPort, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In3Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In4Pin, Pin_Low);
            break;
        /*move the 4 motors in the forward direction to move the car forward*/
        case Direction_Forward:
            MGPIO_WritePin(L298_InPort, L298_In1Pin, Pin_High);
            MGPIO_WritePin(L298_InPort, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In3Pin, Pin_High);
            MGPIO_WritePin(L298_InPort, L298_In4Pin, Pin_Low);
            break;
        /*move the 4 motors in the backward direction to move the car backward*/
        case Direction_Backward:
            MGPIO_WritePin(L298_InPort, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In2Pin, Pin_High);
            MGPIO_WritePin(L298_InPort, L298_In3Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In4Pin, Pin_High);
            break;
        /*move the left motors in the forward direction and stop the right motors to make the car turn right*/
        case Direction_Right:
            MGPIO_WritePin(L298_InPort, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_InPort, L298_In3Pin, Pin_High);
            MGPIO_WritePin(L298_InPort, L298_In4Pin, Pin_Low);
            break;
        /*move the right motors in the forward direction and stop the left motors to make the car turn left*/
        case Direction_Left:
			MGPIO_WritePin(L298_InPort, L298_In1Pin, Pin_High);
			MGPIO_WritePin(L298_InPort, L298_In2Pin, Pin_Low);
			MGPIO_WritePin(L298_InPort, L298_In3Pin, Pin_Low);
			MGPIO_WritePin(L298_InPort, L298_In4Pin, Pin_Low);
			break;
    }
}
