#include "io.h"

void initAll(){

    CLK_CKDIVR = 0x00;
    CLK_PCKENR1 |= CLK_PCKENR1_TIM2|CLK_PCKENR1_TIM3|CLK_PCKENR1_USART1;

    //usart
    PA_DDR &= ~0x08;
    PA_CR1 |= 0x08;
    PA_CR2 &= ~0x08;

    //leds
    PB_DDR |= 0x7E;
    PB_CR1 |= 0x7E;
    PB_ODR |= 0x7E;

    //given 16MHz master clock, 4MHz timer clock (pscr =2 means divide by 2^2), a reload of 32787 gives 122Hz overflows
    TIM2_PSCR = 0x02;
    TIM2_ARRH = 0x80;
    TIM2_ARRL = 0x13;
    TIM2_IER = TIM_IER_UIE|TIM_IER_CC1IE|TIM_IER_CC2IE;
    TIM2_CCMR1 = 0x00;
    TIM2_CCMR2 = 0x00;

    TIM3_PSCR = 0x02;
    TIM3_ARRH = 0x80;
    TIM3_ARRL = 0x13;
    TIM3_IER = TIM_IER_CC1IE;
    TIM3_CCMR1 = 0x00;

    TIM2_CR1 = TIM_CR1_CEN;
    TIM3_CR1 = TIM_CR1_CEN;

    SYSCFG_RMPCR1 |= 0x10;

    USART1_BRR2 = 0x35;
    USART1_BRR1 = 0x41;

    USART1_CR2 |= USART_REN|USART_RIEN;

}
