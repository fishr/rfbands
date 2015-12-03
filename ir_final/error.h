//File should contain error handling information and routines

#include "clock.h"
#include "io.h"

#ifndef ERROR_H
#define ERROR_H

void error_block(void);

#define ERROR_COMM() error_block()
#define ERROR_NO_CMD()

#endif //ERROR_H
