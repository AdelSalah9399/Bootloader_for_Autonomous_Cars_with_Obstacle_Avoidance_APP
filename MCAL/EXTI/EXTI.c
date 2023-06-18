#include "EXTI.h"

static PtrFun EXTI0CallBackFun;
static PtrFun EXTI1CallBackFun;


void MEXTI_LineInterruptMusk(u8 EXTI_lineNumber, u8 EXTI_State)
{
    switch (EXTI_State)
    {
        case EXTI_StateEnable:      EXTI->IMR |=  EXTI_lineNumber; break;
        case EXTI_StateDisable:     EXTI->IMR &= ~EXTI_lineNumber; break;
    }
}

void MEXTI_LineEventMusk(u8 EXTI_lineNumber, u8 EXTI_State)
{
    switch (EXTI_State)
    {
        case EXTI_StateEnable:      EXTI->EMR |=  EXTI_lineNumber; break;
        case EXTI_StateDisable:     EXTI->EMR &= ~EXTI_lineNumber; break;
    }
}

void MEXTI_LineTriggerMode(u8 EXTI_lineNumber, u8 EXTI_Mode)
{
    switch (EXTI_Mode)
    {
        case EXTI_ModeRE:   EXTI->RTSR |=  EXTI_lineNumber; EXTI->FTSR &= ~EXTI_lineNumber; break;
        case EXTI_ModeFE:   EXTI->RTSR &= ~EXTI_lineNumber; EXTI->FTSR |=  EXTI_lineNumber; break;
        case EXTI_ModeRF:   EXTI->RTSR |=  EXTI_lineNumber; EXTI->FTSR |=  EXTI_lineNumber; break;
    }
}

void MEXTI_LineSwTrigger(u8 EXTI_lineNumber)
{
    EXTI->SWIER |= EXTI_lineNumber;
}

void MEXTIxSource(u8 EXTIx, u8 EXITsrc)
{
    u16 temp = SYSCFG->EXTICR1;
    temp &= ~(0xF << EXTIx);
    temp |= (EXITsrc << EXTIx);
}

void MEXTI0_SetCallbackFun(PtrFun ptr)
{
    if (ptr != NULL)
    {
        EXTI0CallBackFun = ptr;

    }
}

void MEXTI1_SetCallbackFun(PtrFun ptr)
{
    if (ptr != NULL)
    {
        EXTI1CallBackFun = ptr;

    }
}

void EXTI0_IRQHandler(void)
{
    EXTI0CallBackFun();
    EXTI->PR |= 1;
}

void EXTI1_IRQHandler(void)
{
    EXTI0CallBackFun();
    EXTI->PR |= 2;
}
