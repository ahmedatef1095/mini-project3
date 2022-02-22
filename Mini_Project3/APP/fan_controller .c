#include "../HAL/LCD/lcd.h"
#include "../HAL/LM35/lm35.h"
#include "../HAL/DcMotor/DcMotor.h"

int main()
{	
	LM35_init();
	LCD_init();
	DcMotor_init();

	uint8 current_temp=0,prev_temp=200;

	while (1)
	{
		current_temp =LM35_getTemperature();

		if(current_temp !=prev_temp)
		{
			if(current_temp < 30 )
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
			else
			{
				LCD_moveCursor(0,3);
				LCD_displayString("FAN is ON ");
				LCD_moveCursor(1,3);
				LCD_displayString("Temp =    C ");
				LCD_moveCursor(1,10);
				LCD_displayNumber(current_temp);
				prev_temp =current_temp;

				if((current_temp >= 30) && (current_temp < 60))
					DcMotor_rotate(DcMotor_CLOCKWISE,25);

				else if((current_temp >= 60) && (current_temp < 90))
					DcMotor_rotate(DcMotor_CLOCKWISE,50);

				else if((current_temp >= 90) && (current_temp < 120))
					DcMotor_rotate(DcMotor_CLOCKWISE,75);

				else if(current_temp >= 120)
					DcMotor_rotate(DcMotor_CLOCKWISE,100);

			}
		}
	}
}


					


