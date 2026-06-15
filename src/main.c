#include <stdint.h>
#include <string.h>
#include "gpio.h"
#include "uart.h"

void main(void) {
    gpio_init();
    uart_init();

    char buffer[32];
    int index = 0;

    while(1) {
        char c = uart_getc();
        uart_putc(c);

        if (c == '\r') {
            uart_out("\r\n");
            buffer[index] = '\0';
            

            if (strcmp(buffer, "red") == 0) {
                redLEDtoggle();
            } else if (strcmp(buffer, "blue") == 0) {
                blueLEDtoggle();
            } else if (strcmp(buffer, "green") == 0) {
                greenLEDtoggle();
            } else if (strcmp(buffer, "send") == 0) {
                uart_out("Test\r\n");
            }
            index = 0;
        } else {
            if (index < sizeof(buffer) - 1)
            {
                buffer[index++] = c;
            }
        }
    }
}
