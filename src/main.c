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

        if (c == '\r') {
            buffer[index] = '\0';

            if (strcmp(buffer, "red") == 0) {
                redLEDtoggle();
            } else if (strcmp(buffer, "blue") == 0) {
                blueLEDtoggle();
            } else if (strcmp(buffer, "green") == 0) {
                greenLEDtoggle();
            } else if (strcmp(buffer, "send") == 0) {
                uart_out("Test");
            }
            index = 0;
        } else {
            buffer[index] = c;
            index++;
        }
    }
}
