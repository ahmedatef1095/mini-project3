#include "../HAL/LCD/lcd.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/ADC/adc.h"

#include "../HAL/LM35/lm35.h"
#include "../HAL/DcMotor/DcMotor.h"

#include "util/delay.h"

int main()
{	
	ADC_ConfigType ADC_channel1={0};
	ADC_channel1.prescaler=ADC_PRESCALLER_8;
	ADC_channel1.ref_volt=VREF_256mV;
	ADC_init(&ADC_channel1);
	LCD_init();
	DcMotor_init();

	uint8 current_temp=0,prev_temp=0;

	while (1)
	{
		current_temp =LM35_getTemperature();

		if((current_temp < 30) && (current_temp !=prev_temp) )
		{
			LCD_moveCursor(0,3);
			LCD_displayString("FAN is OFF");
			LCD_moveCursor(1,3);
			LCD_displayString("Temp =    C ");
			LCD_moveCursor(1,10);
			LCD_displayNumber(current_temp);
			DcMotor_rotate(DcMotor_STOP,0);
			prev_temp =current_temp;
		}

		else if((current_temp !=prev_temp) && (current_temp >= 30) && (current_temp < 60))
		{
			LCD_moveCursor(0,3);
			LCD_displayString("FAN is ON ");
			LCD_moveCursor(1,3);
			LCD_displayString("Temp =    C ");
			LCD_moveCursor(1,10);
			LCD_displayNumber(current_temp);
			DcMotor_rotate(DcMotor_CLOCKWISE,25);
			prev_temp =current_temp;
		}
		else if((current_temp !=prev_temp) && (current_temp >= 60) && (current_temp < 90))
		{
			LCD_moveCursor(0,3);
			LCD_displayString("FAN is ON ");
			LCD_moveCursor(1,3);
			LCD_displayString("Temp =    C ");
			LCD_moveCursor(1,10);
			LCD_displayNumber(current_temp);
			DcMotor_rotate(DcMotor_CLOCKWISE,50);
			prev_temp =current_temp;
		}
		else if((current_temp !=prev_temp) && (current_temp >= 90) && (current_temp < 120))
		{
			LCD_moveCursor(0,3);
			LCD_displayString("FAN is ON ");
			LCD_moveCursor(1,3);
			LCD_displayString("Temp =     C");
			LCD_moveCursor(1,10);
			LCD_displayNumber(current_temp);
			DcMotor_rotate(DcMotor_CLOCKWISE,75);
			prev_temp =current_temp;
		}

		else if((current_temp !=prev_temp) && (current_temp >= 120))
		{
			LCD_moveCursor(0,3);
			LCD_displayString("FAN is ON ");
			LCD_moveCursor(1,3);
			LCD_displayString("Temp =     C");
			LCD_moveCursor(1,10);
			LCD_displayNumber(current_temp);
			DcMotor_rotate(DcMotor_CLOCKWISE,100);
			prev_temp =current_temp;
		}



	}
		
		
}


					

	
