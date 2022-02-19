
#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include <util/delay.h>
#include "../../MCAL/GPIO/GPIO.h"

#define  LCD_MODE		_8_BITMODE
#define  _4_BITMODE			0
#define  _8_BITMODE			1
/*********************pin config*************************/
#define  LCD_PORT    PB
#define  RS			 D5
#define  RW			 D6
#define  EN			 D7
#define  ROW1_COMMAND		0X80 //return home 0b10000000
#define  ROW2_COMMAND		0XC0 //DDRAM is 80 location and 16 of them unused so they used for general ram and so
						       	// we add 64 location on return home command to down to row no 2
/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80






void LCD_Init();
void LCD_Clear();
void LCD_WriteCmd(uint8 cmd);
void LCD_WriteData(uint8 data);
void LCD_WriteNumber(uint32 num);
void LCD_WriteNumIn2Dig(uint8 num);
void LCD_WriteString(uint8 *str);
void LCD_WriteInRowCol(uint8 row,uint8 col);
void LCD_Write_MultiPages(uint8 *str,uint16 delay);
void LCD_floatToString(float32 data);
void LCD_moveCursor(uint8 row,uint8 col);

#endif /* HAL_LCD_LCD_H_ */
