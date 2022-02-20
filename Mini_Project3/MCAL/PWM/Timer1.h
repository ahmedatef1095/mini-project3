
#ifndef MCAL_TIMERS_TIMER1_H_
#define MCAL_TIMERS_TIMER1_H_


#include "../../LIB/std_types.h"

typedef enum
{
	T1_NORMAL_MODE=0,
	T1_PHASE_PWM_8,
	T1_PHASE_PWM_9,
	T1_PHASE_PWM_10,
	T1_CTC_OCR1A,
	T1_FAST_PWM_8,
	T1_FAST_PWM_9,
	T1_FAST_PWM_10,
	T1_PHASE_AND_FRQ_ICR1,
	T1_PHASE_AND_FRQ_OCR1A,
	T1_PHASE_PWM_ICR1,
	T1_PHASE_PWM_OCR1A,
	T1_CTC_ICR1,
	T1_FAST_PWM_ICR1=14,  //13 reserved
	T1_FAST_PWM_OCR1A
}T1_MODE;

typedef enum
{
	OC1_DISCONNECTED=0,
	OC1_TOGGLE_AT_COMPARE,
	OC1_NON_INVERTING,
	OC1_INVERTING
}OC1_MODE;


typedef enum
{
	T1_STOP=0,                   //No Clock Source
	T1_PRESCALLER_1,
	T1_PRESCALLER_8,
	T1_PRESCALLER_64,
	T1_PRESCALLER_256,
	T1_PRESCALLER_1024,
	T0_EXTClK_FALLING,            //External CLock T1 Pin Falling
	T0_EXTClK_RISING,             //External CLock T1 Pin Rising
}T1_CLK_SELECT;

void T1_Init (T1_MODE Timerer_mode,OC1_MODE OC1A_mode,OC1_MODE OC1B_mode);
void T1_Set_Clk(T1_CLK_SELECT clk_select);
void T1_OCA_Interrupt_Enable(void);
void T1_OCA_Interrupt_Disable(void);

void T1_OCR1A_SetCallBack(void(*fptr)(void));

void T1_Set_TCNT1(uint16 TCNT1_Val);
void T1_Set_OCR1A(uint16 freq);


#endif
