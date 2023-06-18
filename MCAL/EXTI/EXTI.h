#include "../STM32F401C8T6/STM32F401C8T6.h"


#define EXTI_line0            BIT0_MASK
#define EXTI_line1            BIT1_MASK
#define EXTI_line2            BIT2_MASK
#define EXTI_line3            BIT3_MASK
#define EXTI_line4            BIT4_MASK
#define EXTI_line5            BIT5_MASK
#define EXTI_line6            BIT6_MASK
#define EXTI_line7            BIT7_MASK
#define EXTI_line8            BIT8_MASK
#define EXTI_line9            BIT9_MASK
#define EXTI_line10           BIT10_MASK
#define EXTI_line11           BIT11_MASK
#define EXTI_line12           BIT12_MASK
#define EXTI_line13           BIT13_MASK
#define EXTI_line14           BIT14_MASK
#define EXTI_line15           BIT15_MASK
#define EXTI_line16           BIT16_MASK
#define EXTI_line17           BIT17_MASK
#define EXTI_line18           BIT18_MASK
#define EXTI_line21           BIT21_MASK
#define EXTI_line22           BIT22_MASK

#define EXTI_ModeRE           (u8)0
#define EXTI_ModeFE           (u8)1
#define EXTI_ModeRF           (u8)2

#define EXTI_StateEnable      (u8)1
#define EXTI_StateDisable     (u8)0

#define EXTI0                 (u8)0
#define EXTI1                 (u8)4
#define EXTI2                 (u8)8
#define EXTI3                 (u8)12

#define EXTIsrcA              (u8)0x0
#define EXTIsrcB              (u8)0x1
#define EXTIsrcC              (u8)0x2
#define EXTIsrcD              (u8)0x3
#define EXTIsrcE              (u8)0x4
#define EXTIsrcH              (u8)0x7



void MEXTI_LineInterruptMusk(u8 EXTI_lineNumber, u8 EXTI_State);

void MEXTI_LineEventMusk(u8 EXTI_lineNumber, u8 EXTI_State);

void MEXTI_LineTriggerMode(u8 EXTI_lineNumber, u8 EXTI_Mode);

void MEXTI_LineSwTrigger(u8 EXTI_lineNumber);

void MEXTIxSource(u8 EXTIx, u8 EXITsrc);

void MEXTI0_SetCallbackFun(PtrFun ptr);

void MEXTI1_SetCallbackFun(PtrFun ptr);
