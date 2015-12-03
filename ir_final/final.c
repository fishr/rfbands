#ifdef RANDOM_SEED
#include "final.h"
#endif //RANDOM_SEED

volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

volatile uint16_t global_clock=0;

  int random_num=0;

void tim2ov_isr(void) __interrupt 19
{
  uint8_t status = TIM2_SR1;
  if(status & TIM_SR1_UIF){
    TIM2_SR1=status & ~TIM_SR1_UIF;
    //all off
            PB_ODR &= ~0x7E;
    global_clock++;
    /*clock testing code
    if(global_clock%100==0){
      rval=rval>>1;
      bval=bval>>1;
      gval=gval>>1;
    }*/
  }
}
  
void tim2cc_isr(void) __interrupt 20
{
  uint8_t status = TIM2_SR1;
  if(status & TIM_SR1_CC1IF){
  //clear flag
    //Red
    TIM2_SR1=status & ~TIM_SR1_CC1IF;
    //turn off led
            PB_ODR |= 0x48;
  }else if(status & TIM_SR1_CC2IF){
    //Green
    TIM2_SR1=status & ~TIM_SR1_CC2IF;
            PB_ODR |= 0x24;
  }
}
  
void tim3cc_isr(void) __interrupt 22
{
  //Blue
  uint8_t status = TIM3_SR1;
  if(status & TIM_SR1_CC1IF){
    TIM3_SR1=status & ~TIM_SR1_CC1IF;
            PB_ODR |= 0x12;
  }
}

void main(){  

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

    srand(RANDOM_SEED);
    
    while(1){
        __asm
        sim
        __endasm;

        if(serial_data_ready_flag){
	    if(serial_cmd==0){
                rval=serial_data[0];
                gval=serial_data[1];
                bval=serial_data[2];
            
       }
}
random_num = rand();
	if(random_num>20000){
		rval=200;
}else if(random_num<10000){
                rval=0;
}
    
            //red
            TIM2_CCR1H=rval>>1;
            TIM2_CCR1L=rval<<7;
            //green
            TIM2_CCR2H=gval>>1;
            TIM2_CCR2L=gval<<7;
            //blue
            TIM3_CCR1H=bval>>1;
            TIM3_CCR1L=bval<<7;
        
 
        __asm
        rim
        wfi
        __endasm;
    }
}

