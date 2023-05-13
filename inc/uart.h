#ifndef __UART_H__
#define __UART_H__

// Included Files
#include "stdint.h"
#include "tm4c123gh6pm.h"

// UART2
void uart2_init(void);
void uart2_send(uint8_t character);
void uart2_send_string(char * string);
char uart2_receive(void);
void uart2_receive_string(char * string, uint32_t len); // Not complete


#endif