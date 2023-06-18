#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/*********************includes*********************/
#include "../STM32F401C8T6/STM32F401C8T6.h"

/****************************************MNVIC_voidSetInterruptPrioretyGroupingStyle(inputs)******************************************/
#define GROUP_16__SUBGROUP_0     0x05FA0000
#define GROUP_8__SUBGROUP_2      0x05FA0400
#define GROUP_4__SUBGROUP_4      0x05FA0500
#define GROUP_2__SUBGROUP_4      0x05FA0600
#define GROUP_0__SUBGROUP_16     0x05FA0700

/*  Pri-grouping style configuration     */
#define PRI_GROUPING_STYLE  GROUP_8__SUBGROUP_2


/****************************************MNVIC_voidSetPeripheralInterruptPriorety(inputs)******************************************/
#define GROUP_0    0
#define GROUP_1    1
#define GROUP_2    2
#define GROUP_3    3
#define GROUP_4    4
#define GROUP_5    5
#define GROUP_6    6
#define GROUP_7    7
#define GROUP_8    8
#define GROUP_9    9
#define GROUP_10   10
#define GROUP_11   11
#define GROUP_12   12
#define GROUP_13   13
#define GROUP_14   14
#define GROUP_15   15

#define SUB_GROUP_0    0
#define SUB_GROUP_1    1
#define SUB_GROUP_2    2
#define SUB_GROUP_3    3
#define SUB_GROUP_4    4
#define SUB_GROUP_5    5
#define SUB_GROUP_6    6
#define SUB_GROUP_7    7
#define SUB_GROUP_8    8
#define SUB_GROUP_9    9
#define SUB_GROUP_10   10
#define SUB_GROUP_11   11
#define SUB_GROUP_12   12
#define SUB_GROUP_13   13
#define SUB_GROUP_14   14
#define SUB_GROUP_15   15

/****************************************MNVIC_Error_tSetPeripheralInterruptEnableState(inputs)******************************************/
#define INTERRUPT_ENABLE    0
#define INTERRUPT_DISABLE   1



/*************************************** Functions Prototypes **************************************/

/***************************************************************************************************
* Function Name         : MNVIC_SetPrioretyGroupingStyle                                           *
* Input Parameters(in)  : None                                                                     *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Setting pri-grouping style                                               *
***************************************************************************************************/
void MNVIC_voidSetInterruptPrioretyGroupingStyle(void);
/***************************************************************************************************
* Function Name         : MNVIC_SetPeripheralPriorety                                              *
* Input Parameters(in)  : Peripheral ID - Group priority index - Subgroup priority index           *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Setting peripheral interrupt priority                                    *
***************************************************************************************************/
void MNVIC_voidSetPeripheralInterruptPriorety(u8 Peripheral_ID,u8 Group_Priorety,u8 SubGroup_Priorety);
/***************************************************************************************************
* Function Name         : MNVIC_SetPeripheralPriorety                                              *
* Input Parameters(in)  : Peripheral ID - Group priority index - Subgroup priority index           *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Setting peripheral interrupt priority                                    *
***************************************************************************************************/
Error_t MNVIC_Error_tSetPeripheralInterruptEnableState(u8 Interrupt_State,u8 Peripheral_ID);
/***************************************************************************************************
* Function Name         : MNVIC_Error_tSetPeripheralPendingEnableState                             *
* Input Parameters(in)  : Peripheral ID - Group priority index - Subgroup priority index           *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Setting peripheral pending state                                         *
***************************************************************************************************/
Error_t MNVIC_Error_tSetPeripheralPendingState(u8 Interrupt_State,u8 Peripheral_ID);
/***************************************************************************************************
* Function Name         : MNVIC_u8GetPeripheralActiveState                               	   	   *
* Input Parameters(in)  : u8 Peripheral_ID         											   	   *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Reading Active state of peripheral                                       *
***************************************************************************************************/
u8 MNVIC_u8GetPeripheralActiveState(u8 Peripheral_ID);
/***************************************************************************************************
* Function Name         : NVIC_u8GetPeripheralActiveState                               	   	   *
* Input Parameters(in)  : u8 Peripheral_ID         											  	   *
* Output Parameter(out) : None                                                                     *
* Return value          : None                                                                     *
* Functionality         : Reading Active state of peripheral                                       *
***************************************************************************************************/
Error_t NVIC_SWTriggerInterrupt(u8 Peripheral_ID);




#endif /* NVIC_NVIC_INTERFACE_H_ */
