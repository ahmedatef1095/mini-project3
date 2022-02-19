
#include "Timer1.h"
#include <avr\io.h>
#include "../../LIB/macros.h"
static void (*PTF_OC1A)(void)=NULL;

void T1_Init(T1_MODE mode,OC1_MODE mode_OC1A,OC1_MODE mode_OC1B)
{
	uint8 temp_TCCR1A=0,temp_TCCR1B=0;
	
	temp_TCCR1A	|=	(mode_OC1A<<6)|(mode_OC1B<<4);
	temp_TCCR1A	|=	(mode & 0x3);
	temp_TCCR1B	|=	((mode>>2)& 0x3) << 3;

	TCCR1A = temp_TCCR1A;
	TCCR1B = temp_TCCR1B;
}

void T1_Set_Clk(T1_CLK_SELECT clk_select)
{
	TCCR1B=(TCCR1B&0xF8)|(clk_select & 0x07);
}

void T1_OCA_Interrupt_Enable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}

void T1_OCA_Interrupt_Disable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}



void T1_OCR1A_SetCallBack(void(*fptr)(void))
{
	PTF_OC1A=fptr;
}

void __vector_6() __attribute__((signal,used));
void __vector_6()
{
	if(PTF_OC1A!=NULL)
	{
		PTF_OC1A();
	}
}

void T1_Set_TCNT1(uint16 TCNT1_Val)
{
	TCNT1=TCNT1_Val;
}
void T1_Set_OCR1A(uint16 freq)
{

	OCR1A=(F_CPU/(64*freq))-1;

}

