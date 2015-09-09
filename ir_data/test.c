
#include "test.h"

unsigned int clock(void)
{
    unsigned char h = TIM2_CNTRH;
    unsigned char l = TIM2_CNTRL;
    return((unsigned int)(h) << 8 | l);
}

void main(void)
{
    CLK_CKDIVR = 0x00; // Set the frequency to 16 MHz
	CLK_PCKENR1 |= CLK_PCKENR1_TIM2;// Enable clock to timer

    // Configure timer
    // overflows to 65535 in ROUGHLY half a second
    TIM2_PSCR = 0x07;
    // enable timer
    TIM2_CR1 |= TIM_CR1_CEN;

    // Configure pins
    PD_DDR = 0x01;
    PD_CR1 = 0x01;

    PC_DDR = 0x60;
    PC_CR1 = 0x60;

    init_serial();

	__asm
	rim
	__endasm;

	for(;;){
		if(halt & 0x01){
		    if(clock() <= 32768){
		        PD_ODR &= 0xFE;
			}else{
		    	PD_ODR |= 0x01;
			}
		    if(clock() % 32768 <= 16000){
				PC_ODR &= 0x9F;
			}else{
				PC_ODR |= 0x60;
			}
		}else{
			PC_ODR &= 0xBF;
			PC_ODR |= 0x40;
		}
	}
}
