#ifndef __GPIO_H__
#define __GPIO_H__


#include "tm4c123gh6pm.h"
#include "stdint.h"

#define SET_BIT(reg,bit)    (reg |=  (1<<bit))
#define GET_BIT(reg,bit)    ((reg>>bit)&1)
#define CLR_BIT(reg,bit)    (reg &= ~(1<<bit))

#define SET(reg,val)        reg |= val
#define CLR(reg,val)        reg &= ~val


#define SW1 0
#define SW2 1

#define RED_LED 0
#define BLUE_LED 1
#define GREEN_LED 2

#define LED_ON 1
#define LED_OFF 0


void portF_init(void);
unsigned int get_switch_value(unsigned char sw);
void set_led_value(unsigned char Color, unsigned char State);
int is_SW1_pressed(void);
int is_SW2_pressed(void);
#endif