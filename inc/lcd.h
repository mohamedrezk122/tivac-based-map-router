#ifndef __LCD_H__
#define __LCD_H__


#include "tm4c123gh6pm.h"
#include <stdint.h>


void delay_ms(int n);
void delay_us(int n);
void lcd_init(void);
void lcd_send_nibble(unsigned char , unsigned char );
void lcd_set_cursor(unsigned int , unsigned int  );
void lcd_write_command(unsigned char);
void lcd_write_char(unsigned char);
void lcd_print(char *);
void lcd_clean(void);

/*
RS  -> pB0
RW  -> pB1
EN  -> pB2
DB4 -> pB4
DB5 -> pB5
DB6 -> pB6
DB7 -> pB7
*/

// masks
#define RS  0x01  
#define RW  0x02
#define EN  0x04


// list of commands

#define  CLEAR_DISPLAY            ((unsigned char) 0X01 )
#define  HOME_POSITION            ((unsigned char) 0X02 )
#define  SHIFT_CURSOR_LEFT        ((unsigned char) 0X04 )
#define  SHIFT_CURSOR_RIGHT       ((unsigned char) 0X06 )
#define  SHIFT_DISPLAY_LEFT       ((unsigned char) 0X07 )
#define  SHIFT_DISPLAY_RIGHT      ((unsigned char) 0X05 )
#define  DISPLAY_OFF_CURSOR_OFF   ((unsigned char) 0X08 )
#define  DISPLAY_OFF_CURSOR_ON    ((unsigned char) 0X0A )
#define  DISPLAY_ON_CURSOR_OFF    ((unsigned char) 0X0C )
#define  DISPLAY_ON_CURSOR_ON     ((unsigned char) 0X0E )
#define  DISPLAY_ON_CURSOR_BLINK  ((unsigned char) 0X0F )
#define  FUNC_SET_4BIT_1LINE      ((unsigned char) 0X020)
#define  FUNC_SET_4BIT_2LINE      ((unsigned char) 0X028)
#define  FUNC_SET_8BIT_1LINE      ((unsigned char) 0X030)
#define  FUNC_SET_8BIT_2LINE      ((unsigned char) 0X038)
#define  CURSOR_START_1ST_LINE    ((unsigned char) 0X80 )
#define  CURSOR_START_2ND_LINE    ((unsigned char) 0XC0 )
#define  CURSOR_START_3RD_LINE    ((unsigned char) 0X90 )
#define  CURSOR_START_4TH_LINE    ((unsigned char) 0XD0 )


#endif // __LCD_H__


