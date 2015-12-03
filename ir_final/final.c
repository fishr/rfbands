#include <sdcc-lib.h>
#include <stdint.h>

#define VUINT *(volatile uint8_t *)
#define SYSCFG_RMPCR1 (VUINT (0x509E))

#define USART1_SR (VUINT (0x5230))
#define USART1_DR (VUINT (0x5231))
#define USART1_BRR1 (VUINT (0x5232))
#define USART1_BRR2 (VUINT (0x5233))
#define USART1_CR1 (VUINT (0x5234))
#define USART1_CR2 (VUINT (0x5235))
#define USART1_CR3 (VUINT (0x5236))
#define USART1_CR4 (VUINT (0x5237))
#define USART1_CR5 (VUINT (0x5238))
#define USART1_PSCR (VUINT (0x523A))

#define USART_RXNE 1<<5
#define USART_REN 1<<2
#define USART_RIEN 1<<5

#define PA_ODR (VUINT (0x5000))
#define PA_DDR (VUINT (0x5002))
#define PA_CR1 (VUINT (0x5003))
#define PA_CR2 (VUINT (0x5004))
#define PB_ODR (VUINT (0x5005))
#define PB_DDR (VUINT (0x5007))
#define PB_CR1 (VUINT (0x5008))
#define PC_ODR (VUINT (0x500A))
#define PC_DDR (VUINT (0x500C))
#define PC_CR1 (VUINT (0x500D))
#define PD_ODR (VUINT (0x500F))
#define PD_DDR (VUINT (0x5011))
#define PD_CR1 (VUINT (0x5012))

#define CLK_CKDIVR (VUINT (0x50C0))
#define CLK_PCKENR1 (VUINT (0x50C3))
#define PCKEN_TIM2 1<<0
#define PCKEN_TIM3 1<<1
#define PCKEN_USART1 1<<5

#define TIM_CR1 0x00
#define TIM_CR2 0x01
#define TIM_IER 0x05
#define TIM_SR1 0x06
#define TIM_CCMR1 0x09
#define TIM_CCMR2 0x0A
#define TIM_CNTRH 0x0C
#define TIM_CNTRL 0x0D
#define TIM_PSCR 0x0E
#define TIM_ARRH 0x0F
#define TIM_ARRL 0x10
#define TIM_CCR1H 0x11
#define TIM_CCR1L 0x12
#define TIM_CCR2H 0x13
#define TIM_CCR2L 0x14

#define TIM_CR1_CEN 1<<0
#define TIM_IER_UIE 1<<0
#define TIM_IER_CC1IE 1<<1
#define TIM_IER_CC2IE 1<<2
#define TIM_SR1_UIF 1<<0
#define TIM_SR1_CC1IF 1<<1
#define TIM_SR1_CC2IF 1<<2

#define TIM2_OFF 0x5250
#define TIM2_CR1 (VUINT (TIM2_OFF + TIM_CR1))
#define TIM2_CR2 (VUINT (TIM2_OFF + TIM_CR2))
#define TIM2_IER (VUINT (TIM2_OFF + TIM_IER))
#define TIM2_SR1 (VUINT (TIM2_OFF + TIM_SR1))
#define TIM2_CNTRH (VUINT (TIM2_OFF + TIM_CNTRH))
#define TIM2_CNTRL (VUINT (TIM2_OFF + TIM_CNTRL))
#define TIM2_PSCR (VUINT (TIM2_OFF + TIM_PSCR))
#define TIM2_CCMR1 (VUINT (TIM2_OFF + TIM_CCMR1))
#define TIM2_CCMR2 (VUINT (TIM2_OFF + TIM_CCMR2))
#define TIM2_CCR1H (VUINT (TIM2_OFF + TIM_CCR1H))
#define TIM2_CCR1L (VUINT (TIM2_OFF + TIM_CCR1L))
#define TIM2_CCR2H (VUINT (TIM2_OFF + TIM_CCR2H))
#define TIM2_CCR2L (VUINT (TIM2_OFF + TIM_CCR2L))
#define TIM2_ARRH (VUINT (TIM2_OFF + TIM_ARRH))
#define TIM2_ARRL (VUINT (TIM2_OFF + TIM_ARRL))

#define TIM3_OFF 0x5280
#define TIM3_CR1 (VUINT (TIM3_OFF + TIM_CR1))
#define TIM3_CR2 (VUINT (TIM3_OFF + TIM_CR2))
#define TIM3_IER (VUINT (TIM3_OFF + TIM_IER))
#define TIM3_SR1 (VUINT (TIM3_OFF + TIM_SR1))
#define TIM3_CNTRH (VUINT (TIM3_OFF + TIM_CNTRH))
#define TIM3_CNTRL (VUINT (TIM3_OFF + TIM_CNTRL))
#define TIM3_PSCR (VUINT (TIM3_OFF + TIM_PSCR))
#define TIM3_CCMR1 (VUINT (TIM3_OFF + TIM_CCMR1))
#define TIM3_CCMR2 (VUINT (TIM3_OFF + TIM_CCMR2))
#define TIM3_CCR1H (VUINT (TIM3_OFF + TIM_CCR1H))
#define TIM3_CCR1L (VUINT (TIM3_OFF + TIM_CCR1L))
#define TIM3_CCR2H (VUINT (TIM3_OFF + TIM_CCR2H))
#define TIM3_CCR2L (VUINT (TIM3_OFF + TIM_CCR2L))
#define TIM3_ARRH (VUINT (TIM3_OFF + TIM_ARRH))
#define TIM3_ARRL (VUINT (TIM3_OFF + TIM_ARRL))


volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

volatile uint16_t global_clock=0;

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
    TIM2_SR1=status & ~TIM_SR1_CC1IF;
    //turn off led
            PB_ODR |= 0x48;
  }else if(status & TIM_SR1_CC2IF){
    TIM2_SR1=status & ~TIM_SR1_CC2IF;
            PB_ODR |= 0x12;
  }
}
  
void tim3cc_isr(void) __interrupt 22
{
  uint8_t status = TIM3_SR1;
  if(status & TIM_SR1_CC1IF){
    TIM3_SR1=status & ~TIM_SR1_CC1IF;
            PB_ODR |= 0x24;
  }
}

void main(){  

    CLK_CKDIVR = 0x00;
    CLK_PCKENR1 |= PCKEN_USART1|PCKEN_TIM2|PCKEN_TIM3;
    
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



    while(1){
        __asm
        sim
        __endasm;

        if(serial_data_ready_flag){
            rval=serial_data[0];
            gval=serial_data[1];
            bval=serial_data[2];
        
    
            //red
            TIM2_CCR1H=rval>>1;
            TIM2_CCR1L=rval<<7;
            //green
            TIM2_CCR2H=gval>>1;
            TIM2_CCR2L=gval<<7;
            //blue
            TIM3_CCR1H=bval>>1;
            TIM3_CCR1L=bval<<7;
        }
 
        __asm
        rim
        wfi
        __endasm;
    }
}
