/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  唐昌生
  * @version V3.0.0
  * @date    2018-06-19
  * @brief   SysTick定时器初始化，us级别延时和ms级延时
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "bsp_SysTick.h"


/* us级别延时，时钟分频 */
static volatile uint16_t us_div;


/**
  * @brief  SysTick初始化
  * @param  sysclk:系统时钟(MHz)
  * @retval 无
  */
void SysTick_Init(uint16_t sysclk)
{
	us_div = sysclk;	//分频
	SysTick->VAL = 0;
	SysTick->LOAD = (uint32_t)us_div*1000-1;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |	//时钟源 FCLK
					SysTick_CTRL_TICKINT_Msk   |	//使能中断
					SysTick_CTRL_ENABLE_Msk;		//使能计数器
}

/**
  * @brief  us级别延时
  * @param  nus:延时时长 0~2^32
  * @retval 无
  */
void delay_us(uint32_t nus)
{
	uint32_t WaitTick;
	uint32_t Tick;
	uint32_t OldTick=0;
	uint32_t Count=0;
	
	OldTick = SysTick->VAL;				//当前计数值
	WaitTick = (uint32_t)nus*us_div;	//等待计数值
	
	do{
		Tick = SysTick->VAL;
		if(OldTick != Tick)
		{
			if(Tick > OldTick){	//溢出了
				Count += OldTick+(SysTick->LOAD-Tick);
			}else{
				Count += OldTick-Tick;
			}
			OldTick = Tick;
		}
	}while(Count < WaitTick);
}

/**
  * @brief  ms级别延时
  * @param  nms:延时时长 0~2^32
  * @retval 无
  */
void delay_ms(uint32_t nms)
{
	while(nms--)
	{
		delay_us(1000);
	}
}
