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

#ifndef FINAL_H
#define FINAL_H

void randomColor(void);

void setRGB(uint8_t r, uint8_t g, uint8_t b);
void setRGBStruct(HsvColor *hsv);

#endif //FINAL_H
