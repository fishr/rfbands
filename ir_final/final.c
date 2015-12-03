#include "final.h"


volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

//volatile uint16_t global_clock=0;

HsvColor holdingColor={0,0,0};
RgbColor conversionColor={0,0,0};

void tim2ov_isr(void) __interrupt 19
{
  uint8_t status = TIM2_SR1;
  if(status & TIM_SR1_UIF){
    TIM2_SR1=status & ~TIM_SR1_UIF;
    //all off
    PB_ODR &= ~0x7E;
  //  global_clock++;
    /*clock testing code
    if(global_clock%100==0){
      rval=rval>>1;
      bval=bval>>1;
      gval=gval>>1;
    }*/
  }
}
  
void tim2cc_isr(void) __interrupt 20
{
  uint8_t status = TIM2_SR1;
  if(status & TIM_SR1_CC1IF){
  //clear flag
    //Red
    TIM2_SR1=status & ~TIM_SR1_CC1IF;
    //turn off led
            PB_ODR |= 0x48;
  }else if(status & TIM_SR1_CC2IF){
    //Green
    TIM2_SR1=status & ~TIM_SR1_CC2IF;
            PB_ODR |= 0x24;
  }
}
  
void tim3cc_isr(void) __interrupt 22
{
  //Blue
  uint8_t status = TIM3_SR1;
  if(status & TIM_SR1_CC1IF){
    TIM3_SR1=status & ~TIM_SR1_CC1IF;
            PB_ODR |= 0x12;
  }
}

void main(){  
    initAll();
    srand(RANDOM_SEED);
    
    while(1){
        __asm
        sim
        __endasm;

        if(serial_data_ready_flag){
            switch(serial_cmd){
                 case 0:  //GLobAL SET
                    setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    break;
                case 1:  //ROW SET
                    if(serial_data[3]==KRESGE_ROW){
                        setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    }
                    break;
               case 2:  //RANDoM TWINKLE set color
                    if((rand()&0x00FF)<=serial_data[3]){
                        conversionColor.r=serial_data[0];
                        conversionColor.g=serial_data[1];
                        conversionColor.b=serial_data[2];
                        RgbToHsv(&conversionColor, &holdingColor);
			setRGBStruct(&holdingColor);
                    }
                    break;
                case 3:  //random color random twinkling 
                    if((rand()&0x00FF)<=serial_data[0]){
                        randomColor();
			setRGBStruct(&holdingColor);
                    }
                    break;
                case 4:  //random color of given brightness
                    //use the 15 bit number we get from rand, lower 8 for hue, upper 7 for saturation (with the 8th bit always set)
                    randomColor();
                    holdingColor.v=serial_data[0];
                    setRGBStruct(&holdingColor);
                    break;
                case 255:
                    serial_cmd = 0;
                    serial_data[0] = 0;
                    serial_data[1] = 0;
                    serial_data[2] = 0;
	            serial_data[3] = 0;
                    holdingColor.h=0;
                    holdingColor.s=0;
                    holdingColor.v=0;
		    setRGBStruct(&holdingColor);
                    break;
       }
       serial_data_ready_flag=0;
}
            //red
            TIM2_CCR1H=rval>>1;
            TIM2_CCR1L=rval<<7;
            //green
            TIM2_CCR2H=gval>>1;
            TIM2_CCR2L=gval<<7;
            //blue
            TIM3_CCR1H=bval>>1;
            TIM3_CCR1L=bval<<7;
        
 
        __asm
        rim
        wfi
        __endasm;
    }
}

void randomColor(){
    uint16_t colorseed=rand();
    holdingColor.h=(uint8_t)(0x00FF&colorseed);
    holdingColor.s=(uint8_t) (((0x7F00&colorseed)>>8)|0x80);
    holdingColor.v=100;
}
    
void setRGB(uint8_t r, uint8_t g, uint8_t b){
    rval=r;
    gval=g;
    bval=b;
}

void setRGBStruct(HsvColor *hsv){
    RgbColor rgb;
    HsvToRgb(hsv,&rgb);
    setRGB(rgb.r, rgb.g, rgb.b);
}
