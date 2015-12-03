#include <sdcc-lib.h>
#include <stdint.h>
#include <stdlib.h>

#include "serial.h"
#include "hsv2rgb.h"

#ifndef KRESGE_ROW
#error "must define KRESGE_ROW to program"
#endif
#ifndef RANDOM_SEED
#error "Must define RANDOM_SEED to program"
#endif

void testHSV(void);
void case5(void);
void setRGB(uint8_t r, uint8_t g, uint8_t b);
void setRGBStruct(HsvColor *hsv);

