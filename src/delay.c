#include "../inc/delay.h"

// hardcoded delay 
void delay_ms(int n){  
    
    volatile int i,j;             
    for(i=0;i<n;i++)
        for(j=0;j<3180;j++)   //delay for 1 msec
        {}
}

// hardcoded delay 
void delay_us(int n){

    volatile int i,j;                          
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)   //delay for 1 micro second
        {}
}

    
void systick_init(void) {

    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0x00FFFFFF;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05;
}

void wait_1ms(void) {

    NVIC_ST_RELOAD_R = 16000 - 1;
    NVIC_ST_CURRENT_R = 0;
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void delay(int t) {

    int i = 0;
    for (i=0; i < t; i++)
        wait_1ms();
}
