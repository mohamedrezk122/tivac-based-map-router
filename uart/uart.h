#ifndef UART_H
#define UART_H
#include "stdint.h"
void setupUART5();
void sendUART5(uint8_t character);
void setupUART1();
void sendUART1(uint8_t character);

#endif