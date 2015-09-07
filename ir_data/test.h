// IR is on PC4, which uses EXTI4(0x8038), and EXTI_CR2(0x50A1), EXTI_SR1(0x50A3)
// the lowest two bits of EXTI_CR2 should be set to one of the following:
//00: Falling edge and low level
//01: Rising edge only
//10: Falling edge only
//11: Rising and falling edge
//EXTI_SR1 1<<4 should be set to clear the pending interrupt in the routine
//PC_CR2 1<<4 should be set to enable EXTI
//PC_DDR 1<<4 should be cleared
//PC_CR1 1<<4 should be cleared

#include <sdcc-lib.h>
#include <stdint.h>
#include "io.h"
#include "serial.h"

#ifndef TEST_H
#define TEST_H


#endif /*TEST_H*/
