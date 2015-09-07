
#include "io.h"
#include "state.h"

#ifndef SERIAL_H
#define SERIAL_H

#define USECS_PER_BIT 320
#define SERIAL_CLK_DIV 1 // serial clk speed is CLK_SPEED/(2^SERIAL_CLK_DIV)
#define CLK_COUNTS_PER_BIT (320/(CLK_SPEED/(1000000*(2^SERIAL_CLK_DIV))))
#define ALLOWED_ERROR 4 // total time is bit-shifted by this for quick division

void init_serial_clock(void);
void init_serial_pin(void);

void serial_servicer(void);

#endif /*SERIAL_H*/
