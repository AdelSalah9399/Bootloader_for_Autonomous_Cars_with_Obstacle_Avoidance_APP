#ifndef ICU_H_
#define ICU_H_

/*********************includes*********************/
#include "../STM32F401C8T6/STM32F401C8T6.h"

/*********************************************General(inputs)*************************************************/

typedef enum
{
	TIM_1,
	TIM_2,
	TIM_3,
	TIM_4,
	TIM_5,
	TIM_9,
	TIM_10,
	TIM_11,

}TIM_NUMBER_t;

typedef enum
{
	CHANNEL_1=1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4


}CHANNEL_t;




/****************************************TIM_Error_tSetCounterState(inputs)******************************************/

typedef enum
{
	COUNTER_STATE_ENABLE,
	COUNTER_STATE_DISABLE


}COUNTER_STATE_t;




/****************************************TIM_Error_tSetCapture_CompareInterruptState(inputs)******************************************/
typedef enum
{
	CAPTURE_COMPARE_INTERRUPT_ENABLE,
	CAPTURE_COMPARE_INTERRUPT_DISABLE


}CAPTURE_COMPARE_INTERRUPT_State_t;



/****************************************TIM_Error_tSetTriggerInterruptState(inputs)******************************************/
typedef enum
{
	TRIGGER_INTERRUPT_STATE_ENABLE,
	TRIGGER_INTERRUPT_STATE_DISABLE


}TRIGGER_INTERRUPT_STATE_t;


/****************************************TIM_Error_tSetChannelState(inputs)******************************************/
typedef enum
{
	CHANNEL_STATE_OUTPUT_COMPARE,
	CHANNEL_STATE_INPUT_CAPTURE
}CHANNEL_STATE_t;



/****************************************TIM_Error_tSetCapture_CompareState(inputs)******************************************/
typedef enum
{
	CAPTURE_COMPARE_STATE_ENABLE,
	CAPTURE_COMPARE_STATE_DISABLE

}CAPTURE_COMPARE_STATE_t;



/****************************************TIM_Error_tSetInputCaptureEdgeTrigger(inputs)******************************************/
typedef enum
{
	INPUT_CAPTURE_TRIGGER_RISING_EDGE,
	INPUT_CAPTURE_TRIGGER_FALLING_EDGE,
	INPUT_CAPTURE_TRIGGER_RISING_FALLING


}INPUT_CAPTURE_TRIGGER_t;





/*************************************** Functions Prototypes **************************************/

/***************************************************************************************************
* Function Name         : TIM_Error_tSetCounterState                                                 *
* Input Parameters(in)  : (COUNTER_STATE_t) COUNTER_STATE,(TIM_NUMBER_t) TIM                       *
* Output Parameter(out) : None                                                                     *
* Return value          : Error_t (Describes error type)                                             *
* Functionality         : Setting Timer/Counter State(Enable/Disable)                              *
***************************************************************************************************/
Error_t TIM_Error_tSetCounterState(COUNTER_STATE_t COUNTER_STATE,TIM_NUMBER_t TIM);
/*************************************************************************************************************************************
* Function Name         : TIM_Error_tSetCapture_CompareInterruptState                                                                  *
* Input Parameters(in)  : (CAPTURE_COMPARE_INTERRUPT_State_t) CAPTURE_COMPARE_INTERRUPT_State,(TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL *
* Output Parameter(out) : None                                                                                                       *
* Return value          : Error_t (Describes error type)                                                                               *
* Functionality         : Setting Capture/Compare Interrupt state                                                                    *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetCapture_CompareInterruptState(CAPTURE_COMPARE_INTERRUPT_State_t CAPTURE_COMPARE_INTERRUPT_State,TIM_NUMBER_t TIM,CHANNEL_t CHANNEL);
/*************************************************************************************************************************************
* Function Name         : TIM_Error_tSetTriggerInterruptState                                                                          *
* Input Parameters(in)  : (TRIGGER_INTERRUPT_STATE_t) TRIGGER_INTERRUPT_STATE,(TIM_NUMBER_t) TIM                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : Error_t (Describes error type)                                                                               *
* Functionality         : Setting Trigger Interrupt state                                                                            *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetTriggerInterruptState(TRIGGER_INTERRUPT_STATE_t TRIGGER_INTERRUPT_STATE,TIM_NUMBER_t TIM);
/*************************************************************************************************************************************
* Function Name         : TIM_Error_tSetChannelState                                                                                   *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL,(CHANNEL_STATE_t) CHANNEL_STATE                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : Error_t (Describes error type)                                                                               *
* Functionality         : Setting Channel State (Input Capture/Output Compare)                                                       *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetChannelState(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL,CHANNEL_STATE_t CHANNEL_STATE);
/*************************************************************************************************************************************
* Function Name         : TIM_Error_tSetCapture_CompareState                                                                           *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL,(CAPTURE_COMPARE_STATE_t) CAPTURE_COMPARE_STATE                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : Error_t (Describes error type)                                                                               *
* Functionality         : Setting Capture/Compare State(Enable/Disable)                                                              *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetCapture_CompareState(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL,CAPTURE_COMPARE_STATE_t CAPTURE_COMPARE_STATE);
/*************************************************************************************************************************************
* Function Name         : TIM_Error_tSetInputCaptureEdgeTrigger                                                                        *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL,(INPUT_CAPTURE_TRIGGER_t) INPUT_CAPTURE_TRIGGER                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : Error_t (Describes error type)                                                                               *
* Functionality         : Setting Input Capture Edge Trigger(Rising edge,Falling Edge,Rising and Falling edges)                      *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetInputCaptureEdgeTrigger(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL,INPUT_CAPTURE_TRIGGER_t INPUT_CAPTURE_TRIGGER);
/*************************************************************************************************************************************
* Function Name         : TIM_u32GetCaptureValueTIM2_TIM5                                                                       *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL                                                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : (u32) Captured Value of TIM2 and TIM5                                                                 *
* Functionality         : Getting Captured value of TIM2 and TIM5                                                                    *
**************************************************************************************************************************************/
u32 TIM_u32GetCaptureValueTIM2_TIM5(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL);
/*************************************************************************************************************************************
* Function Name         : TIM_u16GetCaptureValue                                                                                *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL                                                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : (u16) Captured Value of other Timers                                                                  *
* Functionality         : Getting Captured value                                                                                     *
**************************************************************************************************************************************/
u16 TIM_u16GetCaptureValue(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL);
/*************************************************************************************************************************************
* Function Name         : TIM_u16GetCaptureValue                                                                                *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL                                                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : (u16) Captured Value of other Timers                                                                  *
* Functionality         : Getting Captured value                                                                                     *
**************************************************************************************************************************************/
Error_t TIM_Error_tSetPrescaler(TIM_NUMBER_t TIM,u16 PRESCALER);
/*************************************************************************************************************************************
* Function Name         : TIM_u16GetCaptureValue                                                                                *
* Input Parameters(in)  : (TIM_NUMBER_t) TIM,(CHANNEL_t) CHANNEL                                                                     *
* Output Parameter(out) : None                                                                                                       *
* Return value          : (u16) Captured Value of other Timers                                                                  *
* Functionality         : Getting Captured value                                                                                     *
**************************************************************************************************************************************/

/*Services Functions*/
Error_t TIM_Error_tSetPreloadValue(TIM_NUMBER_t TIM,u32 PRELOAD);
u8 TIM_u8GetFlag(TIM_NUMBER_t TIM,CHANNEL_t CHANNEL);
void TIM_voidSetCounterValue(TIM_NUMBER_t TIM,u32 COUNTER_VALUE);
void TIM_voidClearCounterFlag(TIM_NUMBER_t TIM);
void TIM_voidSet_EGR_UG(TIM_NUMBER_t TIM);





void delay15us(void);


#endif /* ICU_ICU_INTERFACE_H_ */
