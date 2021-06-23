//
// Created by light on 2021/4/12.
//

#ifndef WS2812B_F411_WS2812B_H
#include "main.h"
#define LedTotalNumer 5
#define T0H 19-1
#define T1H 40-1
typedef struct ws2812b
{
    uint8_t ledNumber;
    uint8_t Green[LedTotalNumer];
    uint8_t Red[LedTotalNumer];
    uint8_t Blue[LedTotalNumer];
}ws2812b_t;
extern uint32_t ledPixelBuff[LedTotalNumer*24+4];
void SetLedColor(ws2812b_t *ws2812,uint8_t ledNumber,uint8_t G,uint8_t R,uint8_t B);
void Ws2812bUpdate(void);
#define WS2812B_F411_WS2812B_H

#endif //WS2812B_F411_WS2812B_H
