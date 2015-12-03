#ifndef HSV2RGB_H
#define HSV2RGB_H

//Code courtesy Leszek S on stackoverflow.com

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

void HsvToRgb(HsvColor *hsv, RgbColor *rgb);
void  RgbToHsv(RgbColor *rgb, HsvColor *hsv);

#endif //HSV2RGB_H
