#include "commands.h"
#include "gpio.h"
#include "uart.h"
#include <string.h>

void help() {
    uart_out("red - toggles red LED\r\n");
    uart_out("blue - toggles blue LED\r\n");
    uart_out("green - toggles green LED\r\n");
    uart_out("send - sends \"Test\" to the terminal\r\n");
    uart_out("help - shows usage information\r\n");
}

void handle_command(char *cmd) {
    if (strcmp(cmd, "red") == 0) {
                redLEDtoggle();
            } else if (strcmp(cmd, "blue") == 0) {
                blueLEDtoggle();
            } else if (strcmp(cmd, "green") == 0) {
                greenLEDtoggle();
            } else if (strcmp(cmd, "send") == 0) {
                uart_out("Test\r\n");
            } else if (strcmp(cmd, "help") == 0) {
                help();
            }
}
