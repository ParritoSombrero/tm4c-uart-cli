#include <stdint.h>
#include <string.h>
#include "gpio.h"
#include "uart.h"
#include "commands.h"

void main(void) {
    gpio_init();
    uart_init();

    char buffer[32];
    int index = 0;

    while(1) {
        char c = uart_getc();
        uart_putc(c);

        if (c == 127) {
            if (index > 0) {
                index--; }
        } else if (c == '\r') {
            uart_out("\r\n");
            buffer[index] = '\0';
            handle_command(buffer);
            index = 0;
        } else {
            if (index < sizeof(buffer) - 1)
            {   
                buffer[index++] = c;
            }
        }
    }
}
