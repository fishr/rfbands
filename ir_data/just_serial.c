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
#define PC_ODR (VUINT (0x500A))
#define PC_DDR (VUINT (0x500C))
#define PC_CR1 (VUINT (0x500D))
#define PD_ODR (VUINT (0x500F))
#define PD_DDR (VUINT (0x5011))
#define PD_CR1 (VUINT (0x5012))

#define CLK_CKDIVR (VUINT (0x50C0))
#define CLK_PCKENR1 (VUINT (0x50C3))
#define PCKEN_USART1 1<<5

volatile uint8_t val=0;

void usart_isr(void) __interrupt 28
{
    if(USART1_SR & USART_RXNE){
        val = USART1_DR;
    }else{
        uint8_t throwaway = USART1_DR;
    }
}


void main(){  

    CLK_CKDIVR = 0x00;
    CLK_PCKENR1 |= PCKEN_USART1;

    PA_DDR &= ~0x08;
    PA_CR1 |= 0x08;
    PA_CR2 &= ~0x08;

    PD_DDR |= 0x01;
    PD_CR1 |= 0x01;
    PD_ODR |= 0x01;

    PC_DDR |= 0x60;
    PC_CR1 |= 0x60;
    PC_ODR |= 0x60;

    SYSCFG_RMPCR1 |= 0x10;

    USART1_BRR2 = 0x35;
    USART1_BRR1 = 0x41;

    USART1_CR2 |= USART_REN|USART_RIEN;

    __asm
    rim
    __endasm;

    while(1){
        switch(val%8){
            case 7:
                PD_ODR &= ~0x01;
                PC_ODR &= ~0x60;
                break;
            case 6:
                PD_ODR |= 0x01;
                PC_ODR &= ~0x60;
                break;
            case 5:
                PD_ODR &= ~0x01;
                PC_ODR |= 0x20;
                PC_ODR &= ~0x40;
                break;
            case 4:
                PD_ODR |= 0x01;
                PC_ODR |= 0x20;
                PC_ODR &= ~0x40;
                break;   
            case 3:
                PD_ODR &= ~0x01;
                PC_ODR &= ~0x20;
                PC_ODR |= 0x40;
                break;
            case 2:
                PD_ODR |= 0x01;
                PC_ODR &= ~0x20;
                PC_ODR |= 0x40;
                break;
            case 1:
                PD_ODR &= ~0x01;
                PC_ODR |= 0x20;
                PC_ODR |= 0x40;
                break;
            default:
                PD_ODR |= 0x01;
                PC_ODR |= 0x20;
                PC_ODR |= 0x40;
                break;
        }
    }
}
