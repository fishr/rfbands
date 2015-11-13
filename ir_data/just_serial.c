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
#define PCKEN_USART1 1<<5

#define TIM_CR1 0X00
#define TIM_CR2 0x01
#define TIM_CNTRH 0x0C
#define TIM_CNTRL 0x0D
#define TIM_PSCR 0x0E

#define TIM_CR1_CEN 1<<0

#define TIM2_OFF 0x5250
#define TIM2_CR1 (VUINT (TIM2_OFF + TIM_CR1))
#define TIM2_CR2 (VUINT (TIM2_OFF + TIM_CR2))
#define TIM2_CNTRH (VUINT (TIM2_OFF + TIM_CNTRH))
#define TIM2_CNTRL (VUINT (TIM2_OFF + TIM_CNTRL))
#define TIM2_PSCR (VUINT (TIM2_OFF + TIM_PSCR))

volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

uint8_t time_val;

void usart_isr(void) __interrupt 28
{
    uint8_t val = 0;
    if(USART1_SR & USART_RXNE){
       val = USART1_DR;
    }else{
        val = USART1_DR;
        return;
    }

    if(val==0){
        rval=0;
        gval=0;
        bval=0;
    }else if(val<=64){
        rval=val-1;
    }else if(val<=128){
        gval=val-65;
    }else if(val<=192){
        bval=val-129;
    }else{
        rval=0;
        gval=0;
        bval=0;
    }
}


void main(){  

    CLK_CKDIVR = 0x00;
    CLK_PCKENR1 |= PCKEN_USART1|PCKEN_TIM2;

    TIM2_PSCR = 0x07;
    TIM2_CR1 = TIM_CR1_CEN;

    //usart
    PA_DDR &= ~0x08;
    PA_CR1 |= 0x08;
    PA_CR2 &= ~0x08;

    //leds
    PB_DDR |= 0x7E;
    PB_ODR |= 0x7E;

    SYSCFG_RMPCR1 |= 0x10;

    USART1_BRR2 = 0x35;
    USART1_BRR1 = 0x41;

    USART1_CR2 |= USART_REN|USART_RIEN;

    __asm
    rim
    __endasm;


    while(1){
        time_val = TIM2_CNTRL>>2;
        if(time_val>=bval){
            PB_ODR |= 0x24;
        }else{
            PB_ODR &= ~0x24;
        }
        if(time_val>=rval){
            PB_ODR |= 0x48;
        }else{
            PB_ODR &= ~0x48;
        }
        if(time_val>=gval){
            PB_ODR |= 0x12;
        }else{
            PB_ODR &= ~0x12;
        }
    }
}
