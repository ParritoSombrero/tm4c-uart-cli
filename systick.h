#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>

#define SYSTICK_BASE 0xE000E000
#define SYSTICK_STRELOAD_R (*((volatile uint32_t*)(SYSTICK_BASE + 0x014)))
#define SYSTICK_STCTRL_R (*((volatile uint32_t*)(SYSTICK_BASE + 0x010)))
#define SYSTICK_STCURRENT_R (*((volatile uint32_t*)(SYSTICK_BASE + 0x018)))

void systick_setup();
void systick_delay(uint32_t ms);

#endif
