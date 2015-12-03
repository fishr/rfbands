#include "final.h"


volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

volatile uint16_t global_clock=0;

int random_num=0;
uint8_t breathing=0;

void tim2ov_isr(void) __interrupt 19
{
  uint8_t status = TIM2_SR1;
  if(status & TIM_SR1_UIF){
    TIM2_SR1=status & ~TIM_SR1_UIF;
    //all off
            PB_ODR &= ~0x7E;
    global_clock++;
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
                    breathing=0;
                    setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    break;
                case 1:  //ROW SET
                    breathing=0;
                    if(serial_data[3]!=KRESGE_ROW){
                        setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    }
                    break;
               case 3:  //RANDoM TWINKLE BREATHING
                    breathing = 1;
                    //ifclock()<last_time
                        //handle overflow
                    break;
                case 4:  //random color random twinkling breathing
                    //TODO
                    break;
                case 5:  //random color of given brightness
                    //use the 15 bit number we get from rand, lower 8 for hue, upper 7 for saturation (with the 8th bit always set)
                    case5();

       }
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

void testHSV(){
HsvColor hsvc = {(uint8_t)(0x00FF&(random_num++)), 0xFF, 0xFF};
setRGBStruct(&hsvc);
 
}

void case5(){
    uint8_t brightness = serial_data[0];
    uint16_t colorseed=rand();
    HsvColor hue={(uint8_t)(0x00FF&colorseed), (uint8_t) (((0x7F00)>>8)|0x80), brightness};
    setRGBStruct(&hue);
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
