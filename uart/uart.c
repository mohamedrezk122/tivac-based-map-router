#include "uart.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
/*
A function that sets up port E. It enables UART5 for port E.
Enable UART For port E steps:
1. Enable clock for UART5 in port E
2. Enable clock for port E GPIO pins
3. Disable UART5
4. Configure its UART5 registers
5. Configure port E GPIO pins' registers
*/
void setupUART5() {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5; // Enable clock for UART5
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // Enable clock for port E GPIO pins
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0); // Wait until port E clock is connected

    // Enable commiting changes
    GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY; // Unlock port E for changes
    GPIO_PORTE_CR_R = 0x3F; // Allow commiting changes to all pins of port E

    // Configure UART5
    UART5_CTL_R &= ~UART_CTL_UARTEN;    // Disable the UART
    UART5_IBRD_R = 104; // Setup the BaudRate to be 9600
    UART5_FBRD_R = 11;  // Setup the BaudRate to be 9600
    UART5_CC_R |= UART_CC_CS_SYSCLK; // Connect system clock to UART5
    UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // Word length 8, Enable FIFO, No parity
    UART5_CTL_R = (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);  // Enable UART5, RX, TX

    // Configure GPIO pins of port E (PE5 -> Tx and PE4 -> Rx)
    GPIO_PORTE_DEN_R = 0x3F;    // Digial enable all pins
    GPIO_PORTE_AMSEL_R = 0; // Disable analog mode
    GPIO_PORTE_AFSEL_R = 0x30;  // Enable alternative funcion for PE4 and PE5
    GPIO_PORTE_PCTL_R |= (GPIO_PCTL_PE5_U5TX | GPIO_PCTL_PE4_U5RX); // PE4 and PE5 act as UART pins

}

/*
A function that send character through UART5.
*/
void sendUART5(uint8_t character) {
    while((UART5_FR_R & UART_FR_TXFF) != 0);    // wait until the transmitter buffer isn't full
    UART5_DR_R = character;
}

char receiveUART5() {
    while ((UART5_FR_R & UART_FR_RXFE) != 0);   // wait till you recieve data
    return (unsigned char)UART5_DR_R;
}

void setupUART1() {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; // Enable clock for UART1
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; // Enable clock for portC GPIO pins
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R2) == 0); // Wait until portC clock is connected

    // Enable commiting changes
    GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY; // Unlock portC for changes
    GPIO_PORTC_CR_R = 0xFF; // Allow commiting changes to all pins of portC
    
    // Configure UART1
    UART1_CTL_R &= ~UART_CTL_UARTEN;    // Disable the UART
    UART1_IBRD_R = 104; // Setup the BaudRate to be 9600
    UART1_FBRD_R = 11;  // Setup the BaudRate to be 9600
    UART1_CC_R |= UART_CC_CS_SYSCLK; // Connect system clock to UART1
    UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // Word length 8, Enable FIFO, No parity
    UART1_CTL_R = (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);  // Enable UART1, RX, TX

    // Configure GPIO pins of portC (PC5 -> Tx and PC4 -> Rx)
    GPIO_PORTC_DEN_R = 0xFF;    // Digial enable all pins
    GPIO_PORTC_AMSEL_R = 0; // Disable analog mode
    GPIO_PORTC_AFSEL_R = 0x30;  // Enable alternative funcion for PC4 and PC5
    GPIO_PORTC_DIR_R = 0x20;
    GPIO_PORTC_PCTL_R |= (GPIO_PCTL_PC5_U1TX | GPIO_PCTL_PC4_U1RX); // PC4 and PC5 act as UART pins

}

/*
A function that send character through UART1.
*/
void sendUART1(uint8_t character) {
    while((UART1_FR_R & UART_FR_TXFF) != 0);    // wait until the transmitter buffer isn't full
    UART1_DR_R = character;
}

char receiveUART1() {
    while ((UART1_FR_R & UART_FR_RXFE) != 0);   // wait till you recieve data
    return (unsigned char)UART1_DR_R;
}