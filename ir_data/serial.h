
#include "io.h"
#include "state.h"
#include "error.h"
#include <stdint.h>

#ifndef SERIAL_H
#define SERIAL_H

/*------------------------DEPRECATED--------------------
#define USECS_PER_BIT 320
#define SERIAL_CLK_DIV 1 // serial clk speed is CLK_SPEED/(2^SERIAL_CLK_DIV)
#define CLK_COUNTS_PER_BIT (320/(CLK_SPEED/(1000000*(2^SERIAL_CLK_DIV))))
#define ALLOWED_ERROR 4 // total time is bit-shifted by this for quick division
------------------------END DEPRECATED------------------*/

#define MAX_SERIAL_BUFF 6
#define BAUD_RATE 1200
#define SERIAL_CLK (CLK_SPEED/BAUD_RATE)
#define SERIAL_CLK_HIGH (((SERIAL_CLK & 0x0F000)>>8)|(SERIAL_CLK & 0x0F))
#define SERIAL_CLK_LOW ((SERIAL_CLK & 0x0FF0)>>4)

#define SERIAL_START_BYTE 55
#define SERIAL_END_BYTE 43
#define SERIAL_DLE 47
#define SERIAL_NULL_INDICATOR 53

#define USART_ERROR 0x0F

volatile extern uint8_t serial_data_ready_flag;
volatile extern uint8_t serial_cmd;
volatile extern uint8_t serial_data[MAX_SERIAL_BUFF];
volatile extern enum comm_state_t comm_state;

void init_serial_clock(void);
void init_serial(void);

void serial_isr(void) __interrupt 28;

#endif /*SERIAL_H*/
