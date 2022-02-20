
#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/std_types.h"

/* LCD Configuration*/
#define  LCD_MODE		                LCD_8_BIT_MODE
#define  LCD_4_BIT_MODE			            0
#define  LCD_8_BIT_MODE                     1

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTC_ID


/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_CURSOR_INCREMENT           0x06
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_ROW0		  	   0X80 //return home Row0
#define LCD_SET_CURSOR_ROW1	      	   0XC0 //Row1
#define LCD_SET_CURSOR_ROW2	     	   0X90 //Row2
#define LCD_SET_CURSOR_ROW3			   0XD0 //Row3


void LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCmd(uint8 command);

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayChar(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const uint8 *Str);


void LCD_displayNumber(uint32 num);
/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */


void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(uint32 data);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clear();


#endif /* HAL_LCD_LCD_H_ */
