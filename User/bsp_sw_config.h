/******************************************************************************
* 文件名：bsp_software_config.h
* 功  能：软件配置头文件
* 作  者：唐昌生
* 日  期：2018-02-26
* 备  注：
******************************************************************************/


#ifndef __BSP_SW_CONFIG_H
#define __BSP_SW_CONFIG_H


//#include "menu.h"
//#include "FunProg.h"
//#include "command.h"


/* PCB板号 */
static const uint8_t BoardName[4] = " 172";		//YS172
/* 硬件版本号 */
static const uint8_t BoardVersion[4]=" 200";	//V2.00


/* 电流参数(0~255) */
#define IMAX_R		255
#define IMAX_G		255
#define IMAX_B		255
#define IMAX_W		255

/* 声控参数 */
#define IMAX_E		8	//灵敏度		0~10
#define IMAX_C		6	//触发频闪	1~10
#define IMAX_T		32	//亮灯时间	0:常亮  1~50：对应0.1~5.0秒

/* X电机位置参数 */
#define X_OFFSET	235
#define X_MAX		142
/* Y电机位置参数 */
#define Y_OFFSET	0
#define Y_MAX		110
/* 图案电机位置参数 */
#define F_OFFSET	10
#define F_MAX		124

/* DMX512通道 */
#define DMX512_X_DIR			DMX512_CH1		//X电机方向控制  0:回零点  1~127:正转、速度由慢到快  128~255:反转、速度由快到慢
#define DMX512_X_TUNE			DMX512_CH2		//X电机粗调
#define DMX512_X_FINE			DMX512_CH2		//X电机细调
#define DMX512_Y_TUNE			DMX512_CH3		//Y电机粗调
#define DMX512_Y_FINE			DMX512_CH3		//Y电机细调
#define DMX512_F_TUNE			DMX512_CH4		//图案电机粗调
#define DMX512_F_FINE			DMX512_CH4		//图案电机细调
#define DMX512_XYF_SPEED		DMX512_CH5		//XYF电机速度    0~255:由快到慢
#define DMX512_TotalBridge		DMX512_CH6		//总调光
#define DMX512_R_Bridge			DMX512_CH7		//红
#define DMX512_G_Bridge			DMX512_CH8		//绿
#define DMX512_B_Bridge			DMX512_CH9		//蓝
#define DMX512_FlashSpeed		DMX512_CH10		//频闪速度       0:常亮  1~255:速度由慢到快
#define DMX512_PrgFunMode		DMX512_CH11		//宏功能模式
#define DMX512_PrgFunSpeed		DMX512_CH12		//宏功能速度
#define DMX512_ResetChannel		DMX512_CH13		//复位通道       0~200:无效 201~255:持续5秒复位


#endif
