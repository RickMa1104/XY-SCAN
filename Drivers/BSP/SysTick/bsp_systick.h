

#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H


#include "bsp_hw_config.h"


void SysTick_Init(uint16_t sysclk);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);


#endif
