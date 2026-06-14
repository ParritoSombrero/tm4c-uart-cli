# tm4c-uart-cli
bare-metal UART command line for TM4C123GXL
## features

-UART0 initialization from registers
-command parsing with a buffer
-LED and TX functionality
-no TivaWare, completely bare metal

## built-in commands
| command | action                  |
|---------|-------------------------|
| red     | turns on red LED        |
| green   | turns on green LED      |
| blue    | turns on blue LED       |
| send    | sends "Test" by default |

## requirements & setup
### hardware

-TM4C123GXL

### applications

-PuTTY or any application capable of handling serial data
-any cortex m development environment, i used code composer studio

### specifications
-baud rate is 115200 & 8N1
