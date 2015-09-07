
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
#define CLK_PCKENR1_TIM2 0

#define TIM_CR1 0X00
#define TIM_CR2 0x01
#define TIM_CNTRH 0x0C
#define TIM_CNTRL 0x0D
#define TIM_PSCR 0x0E

#define TIM_CR1_CEN 0

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

