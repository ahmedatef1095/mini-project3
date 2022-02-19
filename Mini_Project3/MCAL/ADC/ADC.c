
#include "ADC.h"
#include <avr\io.h>
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
volatile uint16 g_adcResult = 0;

void ADC_init()
{
	/*ADC Vref Source*/
#if(ADC_VREF == VREF_AREF )
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
#elif(ADC_VREF == VREF_AVCC )
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
#elif(ADC_VREF == VREF_2.56V )
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
#endif

/*ADC Adjusted*/
#if(ADC_Adjusted ==ADC_Right_Adjusted )
		CLR_BIT(ADMUX,ADLAR);
#elif(ADC_Adjusted ==ADC_Left_Adjusted )
		SET_BIT(ADMUX,ADLAR);
#endif

/*Analog Channel and Gain Selection Bits*/
/*select Channel*/

	/*select PreScaler*/

	ADCSRA |=ADC_PRESCALLER;
	/*ADC AUTO TRIGGER SOURCE*/
	SFIOR |= (ADC_AUTO_TRIGGER_SOURCE);
	//ADC_Enable
	SET_BIT(ADCSRA,ADEN);
}



uint16 ADC_readChannel(uint8 channel)
{

	ADMUX = (ADMUX & 0XE0) | (channel & 0x07); /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(GET_BIT(ADCSRA,ADIF) == 0); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}

/*
void ADC_StartConversion(ADC_Channel ch)
{
	
	if(ADC_BUSY_FLAG==0)
	{
		ADMUX=ADMUX&0XE0;//to clear first five bits which connected to channel
		ADMUX=ADMUX|ch;
		SET_BIT(ADCSRA,ADSC);
		ADC_BUSY_FLAG=1;
	}
	
}

uint16 ADC_GetRead(void)
{
	while(GET_BIT(ADCSRA,ADSC));
	ADC_BUSY_FLAG=0;
	return ADC;
}

//with no block if adc finish conversion it return 1 or return 0 if it don't finish yet,,
uint8 ADC_GetReadNoBlock(uint16*pdata)
{
	uint8 status=0;
	if(GET_BIT(ADCSRA,ADSC)==0)
	{
		*pdata=ADC;
		ADC_BUSY_FLAG=0;
		status=1;
	}
	return status;
}

uint8 static volatile ADC_Flag=0;
uint16 static ADC_Val=0;
ADC_Status ADC_GETRead_UsingInterrupt(ADC_Channel ch,uint16 *dig_val)
{
	uint8 static ADC_Read_Change=0,Interrupt_Flag=0;
	ADC_Status status=ADC_NOT_FINISH;
	if(ADC_Read_Change==0)
	{
		if (Interrupt_Flag==0)
		{
			ADC_InterruptEnable();//should be in initialization
			Interrupt_Flag=1;
		}
		ADMUX=ADMUX&0XE0;
		ADMUX=ADMUX|ch;
		SET_BIT(ADCSRA,ADSC);
		ADC_Read_Change=1;
	}
	
	if(ADC_Flag==1)
	{
		ADC_Read_Change=0;
		*dig_val=ADC_Val;
		ADC_Flag=0;
		status=ADC_FINISH;
	}
	return status;
}

ISR(ADC_vect)
{
	if(GET_BIT(ADCSRA,ADIF)==1)
	{
		ADC_Val=ADC;
		ADC_Flag=1;
	}
}



void (*ADC_CallbackPtr)(void) = NULL;



void ADC_INT_Enable(void)
{
	SET_BIT(ADCSRA,ADIE);
}

void ADC_INT_Disable(void)
{
	CLR_BIT(ADCSRA,ADIE);
}



void ADC_SetCallback (void(*FuncPtr)())
{
	ADC_CallbackPtr = FuncPtr;
}
void __vector_16() __attribute__((signal,used));
void __vector_16()
{
	if(ADC_CallbackPtr !=NULL)
	ADC_CallbackPtr();

}
*/
