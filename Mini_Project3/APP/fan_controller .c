#include "../HAL/LCD/lcd.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/ADC/adc.h"

#include "../HAL/LM35/lm35.h"
#include "../HAL/DcMotor/DcMotor.h"



int main()
{	
	ADC_ConfigType ADC_channel1={0};
	ADC_channel1.prescaler=ADC_PRESCALLER_8;
	ADC_channel1.ref_volt=VREF_256mV;

	ADC_init(&ADC_channel1);
		DcMotor_init();
		LCD_init();
		/*Push Button*/
		GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_INPUT);

		LCD_displayString("Temp =      C");



	while (1)
	{
		 while(GPIO_readPin(PORTA_ID,PIN0_ID) ==1 )  //Check Push Button
		 {
			 LCD_moveCursor(0,7);
			 LCD_displayString("    ");
			 LCD_moveCursor(0,7);
			 float32 temp = LM35_getTemperature();
			 LCD_displayFloat(temp);
			 DcMotor_rotate(DcMotor_CLOCKWISE,50);
		 }
		 DcMotor_rotate(DcMotor_ANTI_CLOCKWISE,50);
	}
		
		
}


					

	
