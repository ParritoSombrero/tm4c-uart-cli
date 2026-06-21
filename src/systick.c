#include "systick.h"

// 1. Program the value in the STRELOAD register.
// 2. Clear the STCURRENT register by writing to it with any value.
// 3. Configure the STCTRL register for the required operation.


void systick_setup() {
    SYSTICK_STRELOAD_R = 16000;
    SYSTICK_STCURRENT_R = 0;
    SYSTICK_STCTRL_R = 0x05;
}

void systick_delay(uint32_t ms) { 
    uint32_t i;

    for (i = 0; i < ms; i++) {
        SYSTICK_STCURRENT_R = 0;
        while ((SYSTICK_STCTRL_R & (1 << 16)) == 0);
    }
}
