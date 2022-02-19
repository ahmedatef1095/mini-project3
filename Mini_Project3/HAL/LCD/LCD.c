
#include "LCD.h"



//**************Init LCD***************//
void LCD_Init()
{
#if (LCD_MODE ==_4_BITMODE )

	GPIO_InitPort(LCD_PORT,0x0F);         // set LCD data port as OUTPUT
	GPIO_InitPin(RS,OUTPUT);              // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_InitPin(RW,OUTPUT);              // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_InitPin(EN,OUTPUT);	             // set LCD signals (RS, RW, E) as OUTPUT

	_delay_ms(50);                //VDD rises to 4.5 v
	LCD_WriteCmd(0x02);          //row 1 shifted by 4to the right(function set 1)
	_delay_ms(1);
	LCD_WriteCmd(0x28);         //row 2 oring with row 3 after shifted by 4 to right(function set 2)
	_delay_ms(1);
	LCD_WriteCmd(0x0c);        //row 1 oring with row 2 after shifted by 4 to right(display on off)
	_delay_ms(1);
	LCD_WriteCmd(0x01);          //row 1 oring with row 2 after shifted by 4 to right(clear lcd)
	_delay_ms(2);
	LCD_WriteCmd(0x06);          //row 1 oring with row 2 after shifted by 4 to right(mode set)
	_delay_ms(2);


#elif(LCD_MODE ==_8_BITMODE )
	GPIO_InitPort(LCD_PORT,OUTPUT);        // set LCD data port as OUTPUT
	
	GPIO_InitPin(RS,OUTPUT);    // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_InitPin(RW,OUTPUT);    // set LCD signals (RS, RW, E) as OUTPUT
	GPIO_InitPin(EN,OUTPUT);	   // set LCD signals (RS, RW, E) as OUTPUT

	_delay_ms(30);                //VDD rises to 4.5 v
	LCD_WriteCmd(0x38);           // initialization in 8bit mode of 16X2 LCD
	_delay_ms(1);
	LCD_WriteCmd(0x01);          // make clear LCD
	_delay_ms(1);
	
	_delay_ms(1);
	LCD_WriteCmd(0x06);          // make increment in cursor
	_delay_ms(1);
	//LCD_WriteCmd(0x80);          // �8� go to first line and �0� is for 0th position
	_delay_ms(1);
	LCD_WriteCmd(0x0C);          // display on, cursor off
	_delay_ms(10);
	
	//LCD_WriteCmd(0xC0);          // move cursor to the start of 2nd line
	//LCD_WriteCmd(0x0E);          // make display ON, cursor ON
#endif
}


//**************sending command on LCD***************//

void LCD_WriteCmd(uint8 cmd)
{   
#if (LCD_MODE ==_4_BITMODE )
	/*clear RS and RW */
	GPIO_WritePin(RS,LOW);   // RS sets 0
	GPIO_WritePin(RW,LOW);   // RW sets 0
	/*Write cmd at data port */
	/*first Write MSB 4bits*/
	GPIO_WritePort(LCD_PORT,cmd>>4);
	GPIO_WritePin(EN,HIGH);              // make enable from HIGH to LOW
	_delay_ms(1);						//delay for 50 usec
	GPIO_WritePin(EN,LOW);              // make enable from HIGH to LOW
	_delay_ms(2);                     //After every instruction

	/*write LSB 4bits second*/
	GPIO_WritePort(LCD_PORT,cmd);
	GPIO_WritePin(EN,HIGH);              // make enable from HIGH to LOW
	_delay_ms(1);                        //delay for 50 usec
	GPIO_WritePin(EN,LOW);              // make enable from HIGH to LOW
	_delay_ms(2);                       //After every instruction


#elif(LCD_MODE ==_8_BITMODE )
	GPIO_WritePin(RS,LOW);   // RS sets 0
	GPIO_WritePin(RW,LOW);   // RW sets 0
	
	GPIO_WritePort(LCD_PORT,cmd);      // data lines are set to send command
	
	GPIO_WritePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_WritePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);
#endif
}



//*****************write data on LCD*****************//

void LCD_WriteData(uint8 data)
{   	
#if(LCD_MODE ==_4_BITMODE)

	GPIO_WritePin(RS,HIGH);   // RS sets 1
	GPIO_WritePin(RW,LOW);   // RW sets 0
	/*first Write MSB 4bits*/
	GPIO_WritePort(LCD_PORT,data>>4);    //data lines are set to send command
	GPIO_WritePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_WritePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);

	/*Second Write MSB 4bits*/
	GPIO_WritePort(LCD_PORT,data);    //data lines are set to send command
	GPIO_WritePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_WritePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);


#elif(LCD_MODE ==_8_BITMODE )
	GPIO_WritePin(RS,HIGH);   // RS sets 1
	GPIO_WritePin(RW,LOW);   // RW sets 0
	
	GPIO_WritePort(LCD_PORT,data);      // data lines are set to send command
	
	GPIO_WritePin(EN,HIGH);  // make enable from HIGH to LOW
	_delay_ms(1);
	GPIO_WritePin(EN,LOW);  // make enable from HIGH to LOW
	_delay_ms(2);
#endif
}
void LCD_WriteNumber(uint32 num)

{
	uint8 str[16]; //no. of pixels on lcd
	uint8 i=0,j;
	if(num==0)
	{
		LCD_WriteData('0');
	}
	while(num)
	{
		str[i]=(num%10)+'0';
		i++;
		num/=10;
	}
	for(j=i;j>0;j--)
	{
		LCD_WriteData(str[j-1]);
	}
}

void LCD_WriteInRowCol(uint8 row,uint8 col)
{
	if(row==0)
	{
		LCD_WriteCmd(ROW1_COMMAND+col);
	}
	else if(row==1)
	{
		LCD_WriteCmd(ROW2_COMMAND+col);
	}
}
/*Function to write a string at LCD from address zero */
void LCD_WriteString(uint8 *str)
{
	uint8 index =0,line =1;
	while(str[index] > '\0')
	{
		if(index < 16 && line ==1)
		{
			LCD_WriteData(str[index]);
			index++;
		}
		
		else if (index== 16 && line ==1)
		{
			LCD_WriteCmd(0xC0);          // move cursor to the start of 2nd line
			line++;
		}
		else if (index < 32 && line ==2)
		{
			LCD_WriteData(str[index]);
			index++;
		}
	
	}
	
}
/*function to write a multi pages at LCD with delay between pages*/
void LCD_Write_MultiPages(uint8 *str,uint16 delay)
	{
		uint8 index =0,page=0,line =1;
		while(str[index] > '\0')
		{
			if(index < (16+page)&&line ==1)
			{
				LCD_WriteData(str[index]);
				index++;	
			}
			
			else if ((index== (16+page)) && line ==1)
			{
				LCD_WriteCmd(0xC0);          // move cursor to the start of 2nd line
				line++; 
			}
			else if ((index < (32+page)) && line ==2)
			{
				LCD_WriteData(str[index]);
				index++;
			}
		     
		   else if ((index == (32+page)) && line ==2)
		   {
			   _delay_ms(delay);
			   LCD_WriteCmd(0x01);          // make clear LCD
			   line--;
			   page+=32;
		   }
		
		}
	   
}

void LCD_Clear(void)
{

	LCD_WriteCmd(0x01);          // make clear LCD
	
}
void LCD_WriteNumIn2Dig(uint8 num)
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

void LCD_floatToString(float32 data)
{
   uint8 buff[16]; /* String to hold the ascii result */
   //4 is mininum width, 3 is precision; float value is copied onto buff
   dtostrf(data, 4, 1, buff);
   LCD_WriteString(buff); /* Display the string */
}


void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_WriteCmd(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}
