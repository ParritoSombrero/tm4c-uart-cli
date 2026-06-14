#include "uart.h"

void uart_init(void) {
    SYSCTL_RCGCUART_R |= (1 << 0);

    volatile int delay;
    for (delay = 0; delay < 1000; delay++) {}

    UART0_CTL_R &= ~(1 << 0);

    UART0_IBRD_R = 8;
    UART0_FBRD_R = 44;

    UART0_LCRH_R = (0x3 << 5) | (1 << 4);
    
    UART0_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);

    
}

void uart_out(const char *s) {
    while(*s) {
        while(UART0_FR_R & (1 << 5));
        
        UART0_DR_R = *s++;
    }
}

char uart_getc(void)
{
    while (UART0_FR_R & (1 << 4));

    return (char)UART0_DR_R;
}
