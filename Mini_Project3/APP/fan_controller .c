 /******************************************************************************
 *
 * File Name: fan_controller .c
 *
 * Description:  Fan Controller system
 *
 *  Created on: Feb 23, 2022
 *   Author: Ahmed Atef
 *
 *******************************************************************************/
#include <util/delay.h>
#include "../hal/lcd/lcd.h"
#include "../hal/lm35/lm35.h"
#include "../HAL/DcMotor/dcmotor.h"

#define OUT_OF_RANGE_TEMOERATURE        200

int main()
{	
	/*setup the LCD Display*/
	LCD_init();
	/*setup the LM35 Sensor*/
	LM35_init();
	/*setup DcMotror*/
	DcMotor_init();
	/**/

	/*set prev_temp to out of range temperature to display initial sensor temperature*/
	uint8 current_temp=0,prev_temp=OUT_OF_RANGE_TEMOERATURE;

	while (1)
	{
		current_temp = LM35_getTemperature() ;  /*monitor the temperature*/

		if(current_temp == prev_temp)		 /*check  temperature change*/
		{
			/*Do Nothing*/
		}

		else
		{
			/*Fan is OFF*/
			if(current_temp < 30 )
			{
				/*display Mode*/
				LCD_moveCursor(0,3);
				LCD_displayString("FAN is OFF");
				LCD_moveCursor(1,3);
				LCD_displayString("Temp =    C ");
				LCD_moveCursor(1,10);
				LCD_displayNumber(current_temp);

				/*turn off the fan*/
				DcMotor_rotate(DcMotor_STOP,0);

				/*set prev_temp equal current_temp */
				prev_temp =current_temp;
			}

			/*Fan is ON */
			else
			{
				/*display Mode*/
				LCD_moveCursor(0,3);
				LCD_displayString("FAN is ON ");
				LCD_moveCursor(1,3);
				LCD_displayString("Temp =    C ");
				LCD_moveCursor(1,10);
				LCD_displayNumber(current_temp);

				/*set prev_temp equal current_temp */
				prev_temp =current_temp;

				/*turn on the fan with 25% of its maximum speed.*/
				if((current_temp >= 30) && (current_temp < 60))
					DcMotor_rotate(DcMotor_CLOCKWISE,25);

				/*turn on the fan with 50% of its maximum speed.*/
				else if((current_temp >= 60) && (current_temp < 90))
					DcMotor_rotate(DcMotor_CLOCKWISE,50);

				/*turn on the fan with 75% of its maximum speed.*/
				else if((current_temp >= 90) && (current_temp < 120))
					DcMotor_rotate(DcMotor_CLOCKWISE,75);

				/*turn on the fan with 100% of its maximum speed.*/
				else if(current_temp >= 120)
					DcMotor_rotate(DcMotor_CLOCKWISE,100);
			}
		}

	}
}


					


