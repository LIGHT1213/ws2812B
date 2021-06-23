//
// Created by light on 2021/4/12.
//

#include "ws2812b.h"
#include "tim.h"
uint32_t ledPixelBuff[LedTotalNumer*24+4];
void SetLedColor(ws2812b_t *ws2812,uint8_t ledNumber,uint8_t G,uint8_t R,uint8_t B)
{
    volatile uint8_t result;
    ledPixelBuff[LedTotalNumer*24]=0;
    ledPixelBuff[0]=0;
    ledPixelBuff[1]=0;
    ledPixelBuff[2]=0;
    ws2812->ledNumber=ledNumber;
    ws2812->Green[ledNumber-1]=G;
    ws2812->Red[ledNumber-1]=R;
    ws2812->Blue[ledNumber-1]=B;

    for(int i=0;i<8;i++) {
        result=(ws2812->Green[ledNumber-1]>>(7-i)) & 0x01;
        if(result==1){
            ledPixelBuff[(ledNumber-1)*24+i+3]=T1H;
        } else if(result==0){
            ledPixelBuff[(ledNumber-1)*24+i+3]=T0H;
        }
    }
    for(int i=0;i<8;i++) {
        result=(ws2812->Red[ledNumber-1]>>(7-i)) & 0x01;
        if (result==1) {
            ledPixelBuff[(ledNumber-1)*24+11+i]=T1H;
        } else if (result==0) {
            ledPixelBuff[(ledNumber - 1) * 24 + 11 + i] = T0H;
        }
    }
    for(int i=0;i<8;i++) {
        result=(ws2812->Blue[ledNumber-1]>>(7-i)) & 0x01;
        if (result==1) {
            ledPixelBuff[(ledNumber-1)*24+19+i]=T1H;
        } else if (result==0) {
            ledPixelBuff[(ledNumber-1)*24+19+i]=T0H;
        }
    }
    //HAL_TIM_PWM_Start_DMA(&htim1,TIM_CHANNEL_1,(uint32_t*)&temp,1);
}
void Ws2812bUpdate(void)
{
    HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_4,ledPixelBuff,LedTotalNumer*24+4);
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim3)
        HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_4);
}