#include <stdint.h>
#include <string.h>

// define clocks

#define SYSCTL_RCGCGPIO_R (*((volatile uint32_t*)0x400FE608))
#define SYSCTL_RCGCUART_R (*((volatile uint32_t*)0x400FE618))

// define address bases

#define GPIO_PORTA_BASE 0x40004000
#define GPIO_PORTF_BASE 0x40025000
#define UART0_BASE 0x4000C000

// define functions for port A

#define GPIO_DEN (*((volatile uint32_t*)(GPIO_PORTA_BASE + 0x51C)))
#define GPIO_AFSEL (*((volatile uint32_t*)(GPIO_PORTA_BASE + 0x420)))
#define GPIO_PCTL (*((volatile uint32_t*)(GPIO_PORTA_BASE + 0x52C)))

// define functions for port F
#define GPIOF_DEN (*((volatile uint32_t*)(GPIO_PORTF_BASE + 0x51C)))
#define GPIOF_DIR (*((volatile uint32_t*)(GPIO_PORTF_BASE + 0x400)))
#define GPIOF_DATA (*((volatile uint32_t*)(GPIO_PORTF_BASE + 0x3FC)))

// define uart
#define UART0_DR_R (*((volatile uint32_t*)(UART0_BASE + 0x000)))
#define UART0_FR_R (*((volatile uint32_t*)(UART0_BASE + 0x018)))
#define UART0_IBRD_R (*((volatile uint32_t*)(UART0_BASE + 0x024)))
#define UART0_FBRD_R (*((volatile uint32_t*)(UART0_BASE + 0x028)))
#define UART0_LCRH_R (*((volatile uint32_t*)(UART0_BASE + 0x02C)))
#define UART0_CTL_R (*((volatile uint32_t*)(UART0_BASE + 0x030)))

void uartout(const char *s) {
    while(*s) {
        while(UART0_FR_R & (1 << 5));
        
        UART0_DR_R = *s;
        s++;
    }
}

void main(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 5) | (1 << 0);
    SYSCTL_RCGCUART_R |= (1 << 0);

    volatile int delay;
    for (delay=0; delay<10000; delay++) {        
    }

    // set stuff up for port a
    GPIO_DEN |= (1 << 0) | (1 << 1);
    GPIO_AFSEL |= (1 << 0) | (1 << 1);
    GPIO_PCTL &= ~((0xF << 0) | (0xF << 4));
    GPIO_PCTL |= (0x1 << 0) | (0x1 << 4);

    // set stuff up for port f
    GPIOF_DEN |= (1 << 1) | (1 << 2) | (1 << 3);
    GPIOF_DIR |= (1 << 1) | (1 << 2) | (1 << 3);

    // set stuff up for uart
    UART0_CTL_R &= ~(1 << 0);

    UART0_IBRD_R = 8;
    UART0_FBRD_R = 44;

    UART0_LCRH_R = (0x3 << 5);

    UART0_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);

    char buffer[32];
    int index = 0;

    while(1) {
        while (UART0_FR_R & (1 << 4));
        char c = UART0_DR_R;

        if (c == '\r') {
            buffer[index] = '\0';

            // here is where you define your commands

            if (strcmp(buffer, "red") == 0) {
                GPIOF_DATA ^= (1 << 1);
            } else if (strcmp(buffer, "blue") == 0) {
                GPIOF_DATA ^= (1 << 2);
            } else if (strcmp(buffer, "green") == 0) {
                GPIOF_DATA ^= (1 << 3);
            } else if (strcmp(buffer, "send") == 0) {
                uartout("Test");
            }
            index = 0;
        } else {
            buffer[index] = c;
            index++;
        }
    }
}
