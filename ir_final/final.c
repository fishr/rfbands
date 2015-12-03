#include "final.h"


volatile uint8_t rval=0;
volatile uint8_t gval=0;
volatile uint8_t bval=0;

volatile uint16_t global_clock=0;

int random_num=0;
uint8_t breathing=0;
uint8_t breath_speed=1;
uint16_t breath_count = 0;
HsvColor holdingColor={0,0,0};
RgbColor conversionColor={0,0,0};

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
            if(serial_cmd==255){
                breathing = 0;
                setBreathSpeed(0);
                clearClock();
                serial_cmd = 0;
                serial_data[0] = 0;
                serial_data[1] = 0;
                serial_data[2] = 0;
                holdingColor.h=0;
                holdingColor.s=0;
                holdingColor.v=0;
            }else if(breathing ==1){
                continue;
            }
            switch(serial_cmd){
                 case 0:  //GLobAL SET
                    setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    break;
                case 1:  //ROW SET
                    if(serial_data[3]!=KRESGE_ROW){
                        setRGB(serial_data[0], serial_data[1], serial_data[2]);
                    }
                    break;
               case 3:  //RANDoM TWINKLE BREATHING
                    if((rand()&0x00FF)<serial_data[3]){
                        breathing = 1;
                        clearClock();
                        breath_count=0;
                        setBreathSpeed(serial_data[4]);
                        conversionColor.r=serial_data[0];
                        conversionColor.g=serial_data[1];
                        conversionColor.b=serial_data[2];
                        RgbToHsv(&conversionColor, &holdingColor);
                    }
                    break;
                case 4:  //random color random twinkling breathing
                    if((rand()&0x00FF)<serial_data[0]){
                        breathing=1;
                        clearClock();
                        breath_count=0;
                        setBreathSpeed(serial_data[1]);
                        randomColor();
                    }
                    break;
                case 5:  //random color of given brightness
                    //use the 15 bit number we get from rand, lower 8 for hue, upper 7 for saturation (with the 8th bit always set)
                    case5();
                    break;

                    
       }
       serial_data_ready_flag=0;
}
            if(breathing){
                holdingColor.v=getBreath();
                setRGBStruct(&holdingColor);
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

void setBreathSpeed(uint8_t val){
    breath_speed=val;
    if(val==0){
        breath_speed=1;
    }
}

void clearClock(){
//realized I'm already stopping interrupts
//__asm
//sim
//__endasm;
global_clock=0;
//__asm
//rim
//__endasm;
}

uint8_t getBreath(){
//something like 100hz on the global clock
//probably need at least 20 steps for transition to look smooth
//1/5th of a second sounds like a nice fast blip
//maybe make it smoother if it lasts longer, so we can do faster if needed
//so minimal blip is 1/10th of a second, 10 counts, 5 up and 5 down
uint8_t val=0;
    if(breath_count<255) {
        val = (uint8_t) breath_count;
        breath_count+=breath_speed;
    }else if(breath_count<(512-breath_speed)){
        val = (uint8_t)(0x00FF&(512-breath_count));
        breath_count+=breath_speed;
    }else{
        breathing=0;
        breath_count=0;
    }
    return val;
}

void testHSV(){
HsvColor hsvc = {(uint8_t)(0x00FF&(random_num++)), 0xFF, 0xFF};
setRGBStruct(&hsvc);
 
}
void randomColor(){
    uint16_t colorseed=rand();
    holdingColor.h=(uint8_t)(0x00FF&colorseed);
    holdingColor.s=(uint8_t) (((0x7F00&colorseed)>>8)|0x80);
    holdingColor.v=100;
}
    
void case5(){
    uint8_t brightness = serial_data[0];
    randomColor();
    holdingColor.v=brightness;
    setRGBStruct(&holdingColor);
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
