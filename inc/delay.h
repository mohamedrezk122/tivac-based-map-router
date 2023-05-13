#ifndef __DELAY_H__
#define __DELAY_H__

#include "tm4c123gh6pm.h"
#include "stdint.h"

void delay_ms(int n);
void delay_us(int n);
void systick_init(void) ;
void wait_1ms(void); 
void delay(int t);

#endif