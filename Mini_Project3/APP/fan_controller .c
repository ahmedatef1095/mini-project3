
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LM35/lm35.h"
#include "../HAL/LCD/LCD.h"



int main()
{	
	ADC_ConfigType ADC_channel1={0};
	ADC_channel1.prescaler=ADC_PRESCALLER_8;
	ADC_channel1.ref_volt=VREF_256mV;

	ADC_init(&ADC_channel1);
	LCD_init();
	//LCD_displayString('A');
	LCD_WriteNumber(23);

	while (1)
	{
		//data= USART_Receive_Block();
		//USART_Transmit_Block(data);
	}
		
		
}


					

	
