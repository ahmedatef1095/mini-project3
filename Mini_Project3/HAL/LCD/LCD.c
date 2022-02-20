
#include "LCD.h"
#include<util/delay.h>
#include "../../MCAL/GPIO/GPIO.h"


//**************Init LCD***************//
void LCD_init()
{
#if (LCD_MODE ==LCD_4_BIT_MODE )

	GPIO_setupPortDirection(LCD_DATA_PORT,0x0F);         // set LCD data port as OUTPUT
	GPIO_setupPinDirection(LCD_RS,OUTPUT);              // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_setupPinDirection(LCD_RW,OUTPUT);              // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_setupPinDirection(LCD_EN,OUTPUT);	             // set LCD signals (RS, RW, E) as OUTPUT

	_delay_ms(50);                //VDD rises to 4.5 v
	LCD_sendCmd(0x02);          //row 1 shifted by 4to the right(function set 1)
	_delay_ms(1);
	LCD_sendCmd(0x28);         //row 2 oring with row 3 after shifted by 4 to right(function set 2)
	_delay_ms(1);
	LCD_sendCmd(0x0c);        //row 1 oring with row 2 after shifted by 4 to right(display on off)
	_delay_ms(1);
	LCD_sendCmd(0x01);          //row 1 oring with row 2 after shifted by 4 to right(clear lcd)
	_delay_ms(2);
	LCD_sendCmd(0x06);          //row 1 oring with row 2 after shifted by 4 to right(mode set)
	_delay_ms(2);


#elif(LCD_MODE == LCD_8_BIT_MODE )

	GPIO_setupPortDirection(LCD_DATA_PORT,0xFF);        // set LCD data port as OUTPUT
	GPIO_setupPinDirection(LCD_RS_PIN,OUTPUT);    // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_setupPinDirection(LCD_RW_PIN,OUTPUT);    // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_setupPinDirection(LCD_EN_PIN,OUTPUT);	   // set LCD signals (RS, RW, E) as OUTPUT

	_delay_ms(30);                //VDD rises to 4.5 v
	LCD_sendCmd(LCD_TWO_LINES_EIGHT_BITS_MODE);     // initialization in 8bit mode of 16X2 LCD
	_delay_ms(1);
	LCD_sendCmd(LCD_CLEAR_COMMAND);          // make clear LCD
	_delay_ms(2);
	LCD_sendCmd(LCD_CURSOR_INCREMENT);          // make increment in cursor
	_delay_ms(1);
	LCD_sendCmd(LCD_CURSOR_OFF);            // display on, cursor off
	_delay_ms(10);
	
#endif
}


//**************sending command on LCD***************//

void LCD_sendCmd(uint8 cmd)
{   
#if (LCD_MODE ==_4_BITMODE )
	/*clear RS and RW */
	GPIO_writePin(RS,LOW);   // RS sets 0
	GPIO_writePin(RW,LOW);   // RW sets 0
	/*Write cmd at data port */
	/*first Write MSB 4bits*/
	GPIO_writePort(LCD_DATA_PORT,cmd>>4);
	GPIO_writePin(EN,HIGH);              // make enable from HIGH to LOW
	_delay_ms(1);						//delay for 50 usec
	GPIO_writePin(EN,LOW);              // make enable from HIGH to LOW
	_delay_ms(2);                     //After every instruction

	/*write LSB 4bits second*/
	GPIO_WritePort(LCD_DATA_PORT,cmd);
	GPIO_writePin(EN,HIGH);              // make enable from HIGH to LOW
	_delay_ms(1);                        //delay for 50 usec
	GPIO_writePin(EN,LOW);              // make enable from HIGH to LOW
	_delay_ms(2);                       //After every instruction


#elif(LCD_MODE ==LCD_8_BIT_MODE )
	GPIO_writePin(LCD_RS_PIN,LOW);   // RS sets 0
	GPIO_writePin(LCD_RW_PIN,LOW);   // RW sets 0
	
	GPIO_writePort(LCD_DATA_PORT,cmd);      // data lines are set to send command
	
	GPIO_writePin(LCD_EN_PIN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PIN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);
#endif
}



//*****************write data on LCD*****************//

void LCD_writeChar(uint8 data)
{   	
#if(LCD_MODE ==LCD_4_BIT_MODE)

	GPIO_writePin(RS,HIGH);   // RS sets 1
	GPIO_writePin(RW,LOW);   // RW sets 0
	/*first Write MSB 4bits*/
	GPIO_WritePort(LCD_DATA_PORT,data>>4);    //data lines are set to send command
	GPIO_writePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_writePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);

	/*Second Write MSB 4bits*/
	GPIO_WritePort(LCD_DATA_PORT,data);    //data lines are set to send command
	GPIO_writePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_writePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);


#elif(LCD_MODE ==LCD_8_BIT_MODE )
	GPIO_writePin(LCD_RS_PIN,HIGH);   // RS sets 1
	GPIO_writePin(LCD_RW_PIN,LOW);   // RW sets 0
	
	GPIO_writePort(LCD_DATA_PORT,data);      // data lines are set to send command
	
	GPIO_writePin(LCD_EN_PIN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_writePin(LCD_EN_PIN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);
#endif
}
void LCD_WriteNumber(uint32 num)

{
	uint8 str[16]; //no. of pixels on lcd
	uint8 i=0,j;
	if(num==0)
	{
		LCD_writeChar('0');
	}
	while(num)
	{
		str[i]=(num%10)+'0';
		i++;
		num/=10;
	}
	for(j=i;j>0;j--)
	{
		LCD_writeChar(str[j-1]);
	}
}


/*Function to write a string at LCD from address zero */
void LCD_displayString(const uint8 *str)
{
	uint8 index =0,line =1;
	while(str[index] > '\0')
	{
		if(index < 16 && line ==1)
		{
			LCD_writeChar(str[index]);
			index++;
		}
		
		else if (index== 16 && line ==1)
		{
			LCD_sendCmd(0xC0);          // move cursor to the start of 2nd line
			line++;
		}
		else if (index < 32 && line ==2)
		{
			LCD_writeChar(str[index]);
			index++;
		}
	
	}
	
}
/*function to write a multi pages at LCD with delay between pages*/
void LCD_writeMultiPages(uint8 *str,uint16 delay)
	{
		uint8 index =0,page=0,line =1;
		while(str[index] > '\0')
		{
			if(index < (16+page)&&line ==1)
			{
				LCD_writeChar(str[index]);
				index++;	
			}
			
			else if ((index== (16+page)) && line ==1)
			{
				LCD_sendCmd(0xC0);          // move cursor to the start of 2nd line
				line++; 
			}
			else if ((index < (32+page)) && line ==2)
			{
				LCD_writeChar(str[index]);
				index++;
			}
		     
		   else if ((index == (32+page)) && line ==2)
		   {
			   _delay_ms(delay);
			   LCD_sendCmd(0x01);          // make clear LCD
			   line--;
			   page+=32;
		   }
		
		}
	   
}

void LCD_clear(void)
{

	LCD_sendCmd(LCD_CLEAR_COMMAND);          // make clear LCD
	
}
void LCD_writeNumIn2Dig(uint8 num)
{
	if(num>99)
	{
		num=num%100;
	}
	uint8 num_cpy;
	num_cpy=num/10;
	LCD_WriteNumber(num_cpy);
	num_cpy=num%10;
	LCD_WriteNumber(num_cpy);
}

void LCD_displayFloat(float32 data)
{
   uint8 buff[16]; /* String to hold the ascii result */
   //4 is mininum width, 3 is precision; float value is copied onto buff
   dtostrf(data, 4, 1, buff);
   LCD_displayString(buff); /* Display the string */
}


void LCD_moveCursor(uint8 row,uint8 col)
{
	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			LCD_sendCmd(LCD_SET_CURSOR_ROW0+col);
				break;
		case 1:
			LCD_sendCmd(LCD_SET_CURSOR_ROW0+col);
				break;
		case 2:
			LCD_sendCmd(LCD_SET_CURSOR_ROW0+col);
				break;
		case 3:
			LCD_sendCmd(LCD_SET_CURSOR_ROW0+col);
				break;
	}

}

