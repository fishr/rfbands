
#include <sdcc-lib.h>
#include <stdint.h>

#ifndef IO_H
#define IO_H

#define STM8L05X
//#define STM8L15X

#ifdef STM8L05X

#define CLK_SPEED 16000000

#define VUINT *(volatile uint8_t *)
#define REG_OFF (0x5000)

#define EXTI_CR2 (VUINT (0x50A1))
#define EXTI_SR1 (VUINT (0x50A3))

#define IO_ODR 0x0
#define IO_IDR 0x1
#define IO_DDR 0x2
#define IO_CR1 0x3
#define IO_CR2 0x4

#define PORT_A (REG_OFF + 0x0)
#define PA_ODR (VUINT (PORT_A + IO_ODR))
#define PA_IDR (VUINT (PORT_A + IO_IDR))
#define PA_DDR (VUINT (PORT_A + IO_DDR))
#define PA_CR1 (VUINT (PORT_A + IO_CR1))
#define PA_CR2 (VUINT (PORT_A + IO_CR2))

#define PORT_B (REG_OFF + 0x5)
#define PB_ODR (VUINT (PORT_B + IO_ODR))
#define PB_IDR (VUINT (PORT_B + IO_IDR))
#define PB_DDR (VUINT (PORT_B + IO_DDR))
#define PB_CR1 (VUINT (PORT_B + IO_CR1))
#define PB_CR2 (VUINT (PORT_B + IO_CR2))

#define PORT_C (REG_OFF + 0x0A)
#define PC_ODR (VUINT (PORT_C + IO_ODR))
#define PC_IDR (VUINT (PORT_C + IO_IDR))
#define PC_DDR (VUINT (PORT_C + IO_DDR))
#define PC_CR1 (VUINT (PORT_C + IO_CR1))
#define PC_CR2 (VUINT (PORT_C + IO_CR2))

#define PORT_D (REG_OFF + 0x0F)
#define PD_ODR (VUINT (PORT_D + IO_ODR))
#define PD_IDR (VUINT (PORT_D + IO_IDR))
#define PD_DDR (VUINT (PORT_D + IO_DDR))
#define PD_CR1 (VUINT (PORT_D + IO_CR1))
#define PD_CR2 (VUINT (PORT_D + IO_CR2))

#define CLK_OFF (REG_OFF + 0x0C0)
#define CLK_CKDIVR (VUINT (CLK_OFF + 0x0))
#define CLK_PCKENR1 (VUINT (CLK_OFF + 0x3))
#define CLK_PCKENR1_TIM2 1<<0

#define SYSCFG_RMPCR1 (VUINT (0x509E))

//usart descriptions on p 529
#define USART_SR 0x00
#define USART_DR 0x01
#define USART_BRR1 0x02
#define USART_BRR2 0x03
#define USART_CR1 0x04
#define USART_CR2 0x05
#define USART_CR3 0x06
#define USART_CR4 0x07
#define USART_CR5 0x08
#define USART_PSCR 0x0A

#define USART_REN 1<<2
#define USART_RIEN 1<<5
#define USART_PS 1<<1
#define USART_PCEN 1<<2
#define USART_M 1<<4
#define USART_R8 1<<7
#define USART_PE 1<<0
#define USART_RXNE 1<<5
#define PCKEN_USART1 1<<5

#define USART1_OFF 0x5230
#define USART1_SR (VUINT (USART1_OFF + USART_SR))
#define USART1_DR (VUINT (USART1_OFF + USART_DR))
#define USART1_BRR1 (VUINT (USART1_OFF + USART_BRR1))
#define USART1_BRR2 (VUINT (USART1_OFF + USART_BRR2))
#define USART1_CR1 (VUINT (USART1_OFF + USART_CR1))
#define USART1_CR2 (VUINT (USART1_OFF + USART_CR2))
#define USART1_CR3 (VUINT (USART1_OFF + USART_CR3))
#define USART1_CR4 (VUINT (USART1_OFF + USART_CR4))
#define USART1_CR5 (VUINT (USART1_OFF + USART_CR5))
#define USART1_PSCR (VUINT (USART1_OFF + USART_PSCR))


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

#define TIM3_OFF 0x5280
#define TIM3_CR1 (VUINT (TIM3_OFF + TIM_CR1))
#define TIM3_CR2 (VUINT (TIM3_OFF + TIM_CR2))
#define TIM3_CNTRH (VUINT (TIM3_OFF + TIM_CNTRH))
#define TIM3_CNTRL (VUINT (TIM3_OFF + TIM_CNTRL))
#define TIM3_PSCR (VUINT (TIM3_OFF + TIM_PSCR))


#endif /*STM8L05X*/
#endif /*IO_H*/

