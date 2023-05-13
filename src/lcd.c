
#include "../inc/lcd.h"


void lcd_send_nibble(unsigned char data , unsigned char control){

    data &= 0xF0 ; 
    control &= 0x0F ; 
    GPIO_PORTB_DATA_R = data | control ; // reset pins to zero
    GPIO_PORTB_DATA_R = data | control | EN  ; // set pins to value
    delay_us(0);
    GPIO_PORTB_DATA_R =  data | control  ; 
    GPIO_PORTB_DATA_R =  0x00 ; // sending a high to low pulse to lcd  

}

void lcd_write_command(unsigned char command){

    // commands are 8-bit , and we r sending them 4 by 4 
    lcd_send_nibble(command & 0xF0 , 0) ;   // sends the upper nibble 
    lcd_send_nibble(command <<   4 , 0) ;   // sends the lower nibble 

    if (command < 4)
        delay_ms(2); // delay to accommodate the clock difference 
    else
        delay_us(40);
}

void lcd_print(char *string) {
    volatile int i = 0;
    while( *(string+i) != '\0'){
        lcd_write_char(*(string+i)); // write character by character until null char
        i++ ; 
    }
}

void lcd_set_cursor( unsigned int row , unsigned  int  col){

    unsigned int command = 0x00 ;

    if (row == 0) 
        command = CURSOR_START_1ST_LINE ;
    else if ( row == 1)
        command = CURSOR_START_2ND_LINE ;

    lcd_write_command(command + col % 16 );
}


void lcd_clean(){
    lcd_write_command(CLEAR_DISPLAY);
}

void lcd_write_char(unsigned char character){

    lcd_send_nibble(character & 0xF0 , RS) ; // send the upper nibble 
    lcd_send_nibble(character << 4   , RS) ; // send the lower nibble
    delay_us(40);
}

void lcd_init(void){

    SYSCTL_RCGCGPIO_R |= 0x02 ;  // enable clock for portB 
    delay_ms(10);                // delay until clock stablize
    GPIO_PORTB_DIR_R = 0xFF  ;   // set all pins as output 
    GPIO_PORTB_DEN_R = 0xFF ;   // set all pins as digital 

    // lcd initializations
    lcd_write_command(FUNC_SET_4BIT_2LINE);
    lcd_write_command(SHIFT_CURSOR_RIGHT);
    lcd_write_command(CLEAR_DISPLAY); 
    lcd_write_command(DISPLAY_ON_CURSOR_BLINK); 

}

// int main(void){

//     char* str = "Hello there !" ;
//     char* str2 = "chill" ;
//     lcd_init() ; 
//     lcd_clean();
//     lcd_set_cursor(0,0);
//     delay_ms(500);
//     lcd_print(str);
//     lcd_set_cursor(1,5);
//     delay_ms(500);
//     lcd_print(str2);
//     delay_ms(500);
// }