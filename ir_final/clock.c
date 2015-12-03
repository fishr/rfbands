#include "clock.h"


void init_clock(){
	CLK_PCKENR1 |= CLK_PCKENR1_TIM2;// Enable clock to timer

    // Configure timer
    // overflows to 65535 in ROUGHLY half a second
    TIM2_PSCR = 0x07;
    // enable timer
    TIM2_CR1 |= TIM_CR1_CEN;
}

unsigned int clock(void)
{
    unsigned char h = TIM2_CNTRH;
    unsigned char l = TIM2_CNTRL;
    return((unsigned int)(h) << 8 | l);
}
