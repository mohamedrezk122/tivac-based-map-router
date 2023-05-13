#include "../inc/uart.h"

// Initialize UART2
void uart2_init() {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2; // Enable clock for UART2
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; // Enable clock for port D GPIO pins
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R3) == 0); // Wait until port D clock is connected

    // Enable commiting changes
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY; // Unlock port E for changes
    GPIO_PORTD_CR_R = 0xC0; // Allow commiting changes to UART2 Pins of Port D

    // Configure UART5
    UART2_CTL_R &= ~UART_CTL_UARTEN;    // Disable the UART
    UART2_IBRD_R = 104; // Setup the BaudRate to be 9600
    UART2_FBRD_R = 11;  // Setup the BaudRate to be 9600
    UART2_CC_R |= UART_CC_CS_SYSCLK; // Connect system clock to UART2
    UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // Word length 8, Enable FIFO, No parity
    UART2_CTL_R = (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);  // Enable UART2, RX, TX

    // Configure GPIO pins of port D (PD7 -> Tx and PD6 -> Rx)
    GPIO_PORTD_DEN_R = 0xC0;    // Digial enable UART2 Pins
    GPIO_PORTD_AMSEL_R = 0; // Disable analog mode
    GPIO_PORTD_AFSEL_R = 0xC0;  // Enable alternative funcion for PD6 and PD7
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) | (GPIO_PCTL_PD6_U2RX | GPIO_PCTL_PD7_U2TX); // PD5 and PD6 act as UART pins

}

/*
A function that send character through UART2.
*/
void uart2_send(uint8_t character) {
    while((UART2_FR_R & UART_FR_TXFF) != 0);    // wait until the transmitter buffer isn't full
    UART2_DR_R = character;
}

/*
Sends string over UART2.
Takes:
char * string: pointer to string (char array) to send over UART.
*/
void uart2_send_string(char * string) {
    while(*string) {
        uart2_send(*string);
        string++;
    }
}

/*
A function that receives character from UART2
*/
char uart2_receive() {
    while ((UART2_FR_R & UART_FR_RXFE) != 0);   // wait till you recieve data
    return (unsigned char)(UART2_DR_R & 0xFF);
}

/*
A function that receives string over UART2.
Takes:
1. char * string: pointer to character array, where to store the received characters
2. uint32_t len: length of array where to store characters
*/
void uart2_receive_string(char * string, uint32_t len) {    // Not complete
    char received;
    int i;
    for(i = 0; i < len; i++) {
        received = uart2_receive();
        string[i] = received;
    }
}

/*
A function that sets up port E. It enables UART5 for port E.
Enable UART For port E steps:
1. Enable clock for UART5 in port E
2. Enable clock for port E GPIO pins
3. Disable UART5
4. Configure its UART5 registers
5. Configure port E GPIO pins' registers
*/
void uart5_init() {
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
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0x00FFFF) | (GPIO_PCTL_PE5_U5TX | GPIO_PCTL_PE4_U5RX); // PE4 and PE5 act as UART pins
    // GPIO_PORTE_PCTL_R |= (GPIO_PCTL_PE5_U5TX | GPIO_PCTL_PE4_U5RX); // PE4 and PE5 act as UART pins

}

/*
A function that send character through UART5.
*/
void uart5_send(uint8_t character) {
    while((UART5_FR_R & UART_FR_TXFF) != 0);    // wait until the transmitter buffer isn't full
    UART5_DR_R = character;
}

/*
Sends string over UART5.
Takes:
char * string: pointer to string (char array) to send over UART.
*/
void uart5_send_string(char * string) {
    while(*string) {
        uart5_send(*string);
        string++;
    }
}

/*
A function that receives character from UART5
*/
char uart5_receive() {
    while ((UART5_FR_R & UART_FR_RXFE) != 0);   // wait till you recieve data
    return (unsigned char)(UART5_DR_R & 0xFF);
}

/*
A function that receives string over UART5.
Takes:
1. char * string: pointer to character array, where to store the received characters
2. uint32_t len: length of array where to store characters
*/
void uart5_receive_string(char * string, uint32_t len) {    // Not complete
    char received;
    int i;
    for(i = 0; i < len; i++) {
        received = uart5_receive();
        string[i] = received;
    }
}
