#include "../inc/gpio.h"

void portF_init(void) {
    // activate clock for portf
    SYSCTL_RCGCGPIO_R |= 0x20 ;
    // wait for clock to stablize
    while((SYSCTL_PRGPIO_R &0x20) == 0 );
    // unlock portf 
    GPIO_PORTF_LOCK_R = 0x4C4F434B ;
    // allow changes to portf 0->4
    GPIO_PORTF_CR_R   = 0x1F ;
    // disable analog on portf 
    GPIO_PORTF_AMSEL_R = 0x00;
    GPIO_PORTF_PCTL_R = 0x00000000 ;
    // pin 0 , pin 4 out and pin 1:3 in
    GPIO_PORTF_DIR_R = 0x0E ;
    // disable alternate functions 
    GPIO_PORTF_AFSEL_R = 0x00 ; 
    // enable digital I/O
    GPIO_PORTF_DEN_R = 0x1F ; 
    // pull up on pin 4 and pin 0
    GPIO_PORTF_PUR_R = 0x11 ; 

}

unsigned int get_switch_value(unsigned char sw) {

    switch (sw) {
    case SW1: return GET_BIT(GPIO_PORTF_DATA_R, 4);
    case SW2: return GET_BIT(GPIO_PORTF_DATA_R, 0);
    default: return 0;
    }

}


int is_SW1_pressed(void){
    return GPIO_PORTF_DATA_R &0x10  ; 
}

int is_SW2_pressed(void){
    return GPIO_PORTF_DATA_R &0x01; 
}

void set_led_value(unsigned char Color, unsigned char State) {

    switch (Color) {

    case RED_LED: switch (State) {
    case LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R, 1); break;
    case LED_ON:  SET_BIT(GPIO_PORTF_DATA_R, 1); break;
    }break;

    case BLUE_LED: switch (State) {
    case LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R, 2); break;
    case LED_ON:  SET_BIT(GPIO_PORTF_DATA_R, 2); break;
    }break;

    case GREEN_LED: switch (State) {
    case LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R, 3); break;
    case LED_ON:  SET_BIT(GPIO_PORTF_DATA_R, 3); break;
    }break;
    }
}