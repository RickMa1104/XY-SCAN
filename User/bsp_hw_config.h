/******************************************************************************
* 文件名：bsp_hw_config.h
* 功  能：库配置头文件
* 作  者：唐昌生
* 日  期：2018-02-26
* 备  注：
******************************************************************************/


#ifndef __BSP_HW_CONFIG_H
#define __BSP_HW_CONFIG_H


#include "stm32f0xx.h"
#include "stdio.h"


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"


#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */


#define LEDDrivers_Event_OUT		0x0001		//LED输出事件
#define LEDDrivers_Event_InitSalve	0x0002		//初始化从机

#define LEDFlash_Event_SALVE		0x0001		//主机要求从机立马更新

#define APPProgram_Event_UPDATE		0x0001		//更新更能

#define Command_Event_MENU			0x0001		//菜单事件
#define Command_Event_Fun			0x0002		//功能执行
#define Command_Event_DMX512_END	0x0004		//DMX512接收完成事件

#define Menu_Event_Key				0x0001		//按键按下
#define Menu_Event_DmxReady			0x0002		//DMX512信号就绪
#define Menu_Event_DmxNoReady		0x0004		//DMX512信号断开

/* 任务句柄声明 */
extern TaskHandle_t xHandleTask_Command;




#endif
