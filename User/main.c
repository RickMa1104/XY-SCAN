/**
  ******************************************************************************
  * @file    main.c
  * @author  唐昌生
  * @version V1.0.0
  * @date    2018-06-19
  * @brief   C程序入口函数，创建任务，初始化外设
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "main.h"


///**
//  ******************************************************************************
//	摇头图案3色
//		DMX512通道说明
//	  13通道模式:
//		CH1:X电机无极旋转  0:回零点  1~127:正转、速度由慢到快  128~255:反转、速度由快到慢 优先级大于通道2
//		CH2:X电机位置      0~255:对应0~540度
//		CH3:Y电机位置      0~255:对应0~180度(实质不止180度)
//		CH4:图案电机       0~255:对应不同图案
//		CH5:电机速度       0~255:由快到慢
//		CH6:总调光
//		CH7:红
//		CH8:绿
//		CH9:蓝
//		CH10:频闪
//		CH11:宏功能
//		CH12:宏功能速度
//		CH13:复位 >=200持续5秒
//		
//	主机->从机：
//		CH1:总调光
//		CH2:红
//		CH3:绿
//		CH4:蓝
//		CH5:白
//		CH6:频闪
//		CH7:X电机粗调
//		CH8:X电机细调
//		CH9:X电机速度
//		CH10:Y电机粗调
//		CH11:Y电机细调
//		CH12:Y电机速度
//		CH13:图案电机粗调
//		CH14:图案电机细调
//		CH15:图案电机速度
//  ******************************************************************************
//  */


///* functions prototypes ------------------------------------------------------*/
//void vTask_StartTask(void *pvParameters);
//TaskHandle_t xHandleTask_StartTask = NULL;

//void vTask_Motor(void *pvParameters);
//TaskHandle_t xHandleTask_Motor = NULL;

//void vTask_DispKeyMenu(void *pvParameters);
//TaskHandle_t xHandleTask_DispKeyMenu = NULL;

//void vTask_Command(void *pvParameters);
//TaskHandle_t xHandleTask_Command = NULL;

//void vTask_FunProg(void *pvParameters);
//TaskHandle_t xHandleTask_FunProg = NULL;

//void vTask_Laser(void *pvParameters);
//TaskHandle_t xHandleTask_Laser = NULL;

//void vTask_BSP(void *pvParameters);
//TaskHandle_t xHandleTask_BSP = NULL;


///* tasks ---------------------------------------------------------------------*/
///**
//  * @brief  起始任务，所有任务将从这里创建
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_StartTask(void *pvParameters)
//{
//	uint8_t t=0;
//	TickType_t xLastWakeTime;
//	const TickType_t xFrequency = 5;
//	
//	taskENTER_CRITICAL();	//进入临界区
//	
///**************** 创建电机任务 ****************/
//	xTaskCreate(vTask_Motor,
//	            "vTask Motor",
//	            80,
//	            NULL,
//	            4,
//	            &xHandleTask_Motor);
//	
//	taskEXIT_CRITICAL();	//退出临界区
//	
//	xLastWakeTime = xTaskGetTickCount();
//	for(;;)
//	{
//		t += xFrequency;
//		if(t >= 10) {		 //10ms
//			t -= 10;		//重新计时
//			BSP_KEY_Scan();	//扫描按键
//			if(BSP_KEY_GetPresFlag()!=0) {	//有按键按下
//				/* 通知菜单任务，有按键按下 */
//				if(xHandleTask_DispKeyMenu!=NULL) {
//					xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_Key, eSetBits);
//				}
//			}
//		}
//		BSP_Disp_Scan();	//扫描显示
//		vTaskDelayUntil(&xLastWakeTime, xFrequency);
//	}
//}

//typedef struct
//{
//	uint32_t X;
//	uint32_t Y;
//}XY_Type;
//const XY_Type XYTable[]={
//{0, 0},
//{0, 7},
//{12,7},
//{12,40},
//{7, 40},
//{4, 37},
//{2, 41},
//{6, 45},
//{12,45},
//{12,50},
//{20,50},
//{20,6},
//{32,6},
//{32,0},
//};

//uint8_t X_Max_Speed;
//uint8_t Y_Max_Speed;

//void X_Set(uint32_t x)
//{
//	x = 1024*4*x;
//	BSP_Motor_Position(&M1pid, x, X_Max_Speed);
//}
//void Y_Set(uint32_t y)
//{
//	y = 1024*4*y;
//	BSP_Motor_Position(&M2pid, y, Y_Max_Speed);
//}

///**
//  * @brief  电机任务
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_Motor(void *pvParameters)
//{
//	uint16_t n,size;
//	uint16_t nextX;
//	uint16_t nextY;
//	uint16_t StepX;
//	uint16_t StepY;
//	
//	uint8_t  status;
//	uint32_t timeout;
//	uint32_t ulValue;
//	BaseType_t xResult;
//	uint32_t X_Position;
//	uint32_t Y_Position;
//	
//	BSP_DispShowStr(SMG_Bits_1, "    ", 4);
//	vTaskDelay(300);
//	BSP_DispShowStr(SMG_Bits_1, "-YS-", 4);
//	vTaskDelay(1200);
//	BSP_DispShowStr(SMG_Bits_1, "RESt", 4);
//	vTaskDelay(300);
//	Menu_ReadMemory();	//从存储器读取菜单值
//	
//	timeout = 4*1000;	//4秒超时
//	do{
//		status  = BSP_Motor_PosReset(&M1pid);
//		status |= BSP_Motor_PosReset(&M2pid);
//		if(status==0) {	//全部复位完成
//			break;
//		}
//		vTaskDelay(1);
//	}while(timeout--);
//	
//	taskENTER_CRITICAL();	//进入临界区
///******** 电机复位完成，创建其他任务，准备进入系统 ********/
//	xTaskCreate(vTask_DispKeyMenu,
//	            "vTask DispKeyMenu",
//	            100,
//	            NULL,
//	            2,
//	            &xHandleTask_DispKeyMenu);
//	
//	xTaskCreate(vTask_Command,
//	            "vTask Command",
//	            100,
//	            NULL,
//	            4,
//	            &xHandleTask_Command);
//				
//	xTaskCreate(vTask_FunProg,
//	            "vTask FunProg",
//	            80,
//	            NULL,
//	            3,
//	            &xHandleTask_FunProg);
//				
//	xTaskCreate(vTask_Laser,
//	            "vTask Laser",
//	            64,
//	            NULL,
//	            2,
//			   &xHandleTask_Laser);
//			
//	xTaskCreate(vTask_BSP,
//	            "vTask BSP",
//	            64,
//	            NULL,
//	            2,
//			   &xHandleTask_BSP);
//			   
//	taskEXIT_CRITICAL();	//退出临界区
//	
//	
//	size = sizeof(XYTable)/sizeof(XY_Type);
//	
//	
//	for(;;)
//	{
//		X_Max_Speed = 50;
//		Y_Max_Speed = 50;
//		X_Set(100);
//		Y_Set(100);
//		vTaskDelay(5000);
//		X_Set(0);
//		Y_Set(0);
//		vTaskDelay(5000);
//		
//		X_Max_Speed = 120;
//		Y_Max_Speed = 120;
//		X_Set(255);
//		Y_Set(255);
//		vTaskDelay(5000);
//		X_Set(0);
//		Y_Set(0);
//		vTaskDelay(5000);
//		
//		X_Max_Speed = 200;
//		Y_Max_Speed = 200;
//		X_Set(255);
//		Y_Set(255);
//		vTaskDelay(3200);
//		X_Set(0);
//		Y_Set(0);
//		vTaskDelay(3200);
//		
//		
//		X_Max_Speed = 255;
//		Y_Max_Speed = 255;
//		X_Set(255);
//		Y_Set(255);
//		vTaskDelay(2400);
//		X_Set(0);
//		Y_Set(0);
//		vTaskDelay(2400);
//		
//		
//		
//		
//		
//		
//		
//		
////		for(n=0; n<size; n++)
////		{
////			X_Set(XYTable[n].X);
////			Y_Set(XYTable[n].Y);
////			
////			if(n==size)nextX=XYTable[0].X;
////			else nextX=XYTable[n+1].X;
////			if(n==size)nextY=XYTable[0].Y;
////			else nextY=XYTable[n+1].Y;
////			
////			if(nextX>XYTable[n].X){
////				StepX = nextX-XYTable[n].X;
////			}else{
////				StepX = XYTable[n].X-nextX;
////			}
////			
////			if(nextY>XYTable[n].Y){
////				StepY = nextY-XYTable[n].Y;
////			}else{
////				StepY = XYTable[n].Y-nextY;
////			}
////			
////			if(StepX>StepY)
////			{
////				vTaskDelay(StepX*2);
////			}
////			else
////			{
////				vTaskDelay(StepY*2);
////			}
////		}

////			X_Set(255);
////			vTaskDelay(250);
////			X_Set(0);
////			vTaskDelay(250);
//		
////		X_Set(XYTable[0].X);
////		Y_Set(XYTable[0].Y);
////		vTaskDelay(13);
////		
////		X_Set(XYTable[1].X);
////		Y_Set(XYTable[1].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[2].X);
////		Y_Set(XYTable[2].Y);
////		vTaskDelay(8);
////		
////		X_Set(XYTable[3].X);
////		Y_Set(XYTable[3].Y);
////		vTaskDelay(12);
////		
////		X_Set(XYTable[4].X);
////		Y_Set(XYTable[4].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[5].X);
////		Y_Set(XYTable[5].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[6].X);
////		Y_Set(XYTable[6].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[7].X);
////		Y_Set(XYTable[7].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[8].X);
////		Y_Set(XYTable[8].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[9].X);
////		Y_Set(XYTable[9].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[10].X);
////		Y_Set(XYTable[10].Y);
////		vTaskDelay(4);
////		
////		X_Set(XYTable[11].X);
////		Y_Set(XYTable[11].Y);
////		vTaskDelay(18);
////		
////		X_Set(XYTable[12].X);
////		Y_Set(XYTable[12].Y);
////		vTaskDelay(8);
////		
////		X_Set(XYTable[13].X);
////		Y_Set(XYTable[13].Y);
////		vTaskDelay(4);
//		
//		
//		
//		
//		
////		X_Position = 128*menu.ValMem.FF_Value;
////		BSP_Motor_Position(&M1pid, X_Position, M1pid.MaxSpeed);
////		vTaskDelay(menu.ValMem.A0_Value);
////		
////		Y_Position = 128*menu.ValMem.FF_Value;
////		BSP_Motor_Position(&M2pid, Y_Position, M2pid.MaxSpeed);
////		vTaskDelay(menu.ValMem.A0_Value);
////		
////		X_Position = 0;
////		BSP_Motor_Position(&M1pid, X_Position, M1pid.MaxSpeed);
////		vTaskDelay(menu.ValMem.A0_Value);
////		
////		Y_Position = 1024*0;
////		BSP_Motor_Position(&M2pid, Y_Position, M2pid.MaxSpeed);
////		vTaskDelay(menu.ValMem.A0_Value);
//	}
//}

///**
//  * @brief  显示、按键、菜单任务
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_DispKeyMenu(void *pvParameters)
//{
//	uint8_t MenuCmd;
//	uint32_t ulValue;
//	BaseType_t xResult;
//	
//	Menu_Init();	//菜单初始化
//	for(;;)
//	{
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, portMAX_DELAY);
//		
//		if(xResult==pdTRUE)		//事件标志
//		{
//			if(ulValue & Menu_Event_Key)
//			{
//				MenuCmd = 0x00; 				//0x00:按键处理
//			}
//			else if(ulValue & Menu_Event_DmxReady)
//			{
//				MenuCmd = MENU_CMD_DMX_READY; 	//0x00:DMX512就绪处理
//			}
//			else if(ulValue & Menu_Event_DmxNoReady)
//			{
//				MenuCmd = MENU_CMD_DMX_NOREADY;	//0x00:DMX512断开处理
//			}
//			Menu_Display(MenuCmd);
//		}
//	}
//}

///**
//  * @brief  命令任务
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_Command(void *pvParameters)
//{
//	uint8_t FunMenuOld;
//	uint32_t ulValue;
//	BaseType_t xResult;
//	uint16_t timeout=0;
//	uint32_t NowTick=0;
//	uint32_t OldTick=0;
//	uint8_t  DmxReadyFlag=0;
//	uint16_t DmxReadyCount=0;
//	
//	OldTick    = xTaskGetTickCount();	//当前系统时钟
//	FunMenuOld = APP_ALLOFF;
//	for(;;)
//	{
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, 100);
//		
//		if(xResult==pdTRUE)		//事件标志
//		{
//			if((ulValue&Command_Event_MENU) || (ulValue&Command_Event_DMX512_END))	//菜单操作，或DMX512收到数据
//			{
//				if(ulValue&Command_Event_DMX512_END) {
//					if(menu.Menu==MENU_A0) {
//						timeout=0;									//超时清零
//						BSP_DispPointStatus(SMG_Bits_4, ENABLE);	//开启小数点
//						BSP_DispRefurbish();						//刷新显示
//						Fun_DMX512_Control(dmx512.RxBuff);			//DMX512控制
//					}else{
//						if(menu.ValMem.AD_Value==1 && menu.Menu!=MENU_AD &&	//"ADYE"
//						   menu.Menu<=MENU_MAIN_MAX) 						//主菜单
//						{
//							DmxReadyCount++;								//就绪加1
//							if(DmxReadyCount >= 2) {						//连续两次收到Ready信号
//								DmxReadyFlag = 1;
//							}
//						}
//					}
//				}else if(ulValue&Command_Event_MENU) {
//					if(menu.Menu!=MENU_A0) {
//						if(menu.Menu<=MENU_MAIN_MAX) {
//							Fun_MainMenu_Control();			//主菜单功能控制
//						}else{
//							Fun_HideMenu_Control();			//隐藏菜单功能控制
//						}
//					}
//					DmxReadyCount = 0;						//按键按下，重新计数
//					DmxReadyFlag  = 0;						//就绪标志清零
//				}
//			}
//			else if(ulValue & Command_Event_Fun)	//应用层更新驱动层
//			{
//				/* 把APP数据更新到硬件层，激光调光更新 */
//				laser.R_Bridge     = AppData.R_Bridge;
//				laser.G_Bridge     = AppData.G_Bridge;
//				laser.B_Bridge     = AppData.B_Bridge;
//				laser.W_Bridge     = AppData.W_Bridge;
//				laser.FlashSpeed   = AppData.FlashSpeed;
//				laser.TotalBridge  = AppData.TotalBridge;
//				/* 更新电机位置 */
//				M1pid.DirControl  = AppData.X_DirControl;
//				M1pid.DmxTune     = AppData.X_Tune;
//				M1pid.DmxFine     = AppData.X_Fine;
//				M1pid.DmxSpeed    = AppData.X_Speed;
//				M2pid.DmxTune     = AppData.Y_Tune;
//				M2pid.DmxFine     = AppData.Y_Fine;;
//				M2pid.DmxSpeed    = AppData.Y_Speed;
//				M3pid.DmxTune     = AppData.F_Tune;
//				M3pid.DmxFine     = AppData.F_Fine;;
//				M3pid.DmxSpeed    = AppData.F_Speed;
//				
//				/* 通知电机，需要改变位置 */
//				xTaskNotify(xHandleTask_Motor, 0x00000001, eSetBits);
//				/* 通知激光任务，需要改变激光状态，同事发数据到从机 */
//				xTaskNotify(xHandleTask_Laser, 0x00000001, eSetBits);
//			}
//		}
//		
//		NowTick = xTaskGetTickCount();		//当前系统时钟
//		if(NowTick-OldTick >= 100) {		//0.1秒
//			OldTick += 100;
//			
//			if(DmxReadyFlag==1) {	//DMX512就绪了
//				/* 通知菜单，DMX512信号就绪 */
//				xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_DmxReady, eSetBits);
//			}
//			
//			if(menu.Menu==MENU_A0) {
//				if(timeout<250) {
//					timeout++;
//				}
//				if(timeout>=12){
//					if(timeout==30) {
//						/* 通知菜单，DMX512信号断开 */
//						xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_DmxNoReady, eSetBits);
//					}
//					app.FunMenu = APP_ALLOFF;
//					BSP_DispPointStatus(SMG_Bits_4, DISABLE);	//关闭小数点
//					BSP_DispRefurbish();						//刷新显示
//				}
//			}
//		}
//		
//		if(FunMenuOld != app.FunMenu)	//功能改变了
//		{
//			FunMenuOld = app.FunMenu;
//			app.Running = 0;			//退出当前功能
//		}
//	}
//}

///**
//  * @brief  功能任务
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_FunProg(void *pvParameters)
//{
//	/* 功能初始化 */
//	FunProg_Init();
//	
//	for(;;)
//	{
//		/* 功能处理 */
//		FunProg_Display();
//	}
//}

///**
//  * @brief  激光任务
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_Laser(void *pvParameters)
//{
//	uint8_t FlashSpeedOld;
//	uint16_t FlashDelayLen;
//	uint16_t temp;
//	uint32_t ulValue;
//	BaseType_t xResult;
//	
//	for(;;)
//	{
//		if(laser.FlashSpeed == 0)	//关闭频闪
//		{
//			/* 通知BSP任务，开光 */
//			xTaskNotify(xHandleTask_BSP, 0x00000001, eSetBits);
//			/* 每隔10ms更新一次 */
//			xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, 10);
//			
//			if(xResult) {
//				
//			}
//		}
//		else
//		{
//			/* 本次的频闪速度 */
//			FlashSpeedOld = laser.FlashSpeed;
//			/* 通知BSP任务，开光 */
//			xTaskNotify(xHandleTask_BSP, 0x00000001, eSetBits);
//			/* 开光30ms */
//			vTaskDelay(30);
//			/* 通知BSP任务，闭光 */
//			xTaskNotify(xHandleTask_BSP, 0x00000002, eSetBits);
//			/* 闭光40ms */
//			vTaskDelay(40);
//			
//			FlashDelayLen = (uint16_t)(255-FlashSpeedOld)*4;	//最大延时1020ms
//			
//			while(FlashDelayLen)	/* 等待延时完成 */
//			{
//				if(FlashDelayLen >= 10) {
//					/* 通知BSP任务，闭光 */
//					xTaskNotify(xHandleTask_BSP, 0x00000002, eSetBits);
//					/* 延时20ms */
//					vTaskDelay(10);
//					/* 剩余的延时 */
//					FlashDelayLen -= 10;
//					
//					if(laser.FlashSpeed == 0) {	/* 关闭频闪，跳出循环 */
//						break;
//					}else{
//						if(laser.FlashSpeed > FlashSpeedOld)	/* 频闪速度变快 */
//						{
//							/* 速度更新后延时 */
//							temp = (uint16_t)(255-laser.FlashSpeed)*4;
//							
//							if(FlashDelayLen > temp){
//								/* 使用较短的延时 */
//								FlashDelayLen = temp;
//							}
//						}
//					}
//				}else{
//					/* 剩余延时 */
//					vTaskDelay(FlashDelayLen);
//					break;
//				}
//			}
//		}
//	}
//}

///**
//  * @brief  BSP任务，更新驱动层
//  * @param  *pvParameters:
//  * @retval 无
//  */
//void vTask_BSP(void *pvParameters)
//{
//	uint32_t ulValue;
//	BaseType_t xResult;
//	
//	for(;;)
//	{
//		/* 无限等待 */
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, portMAX_DELAY);
//		
//		if(xResult==pdTRUE)		//事件标志
//		{
//			if(ulValue & 0x00000003)
//			{
//				if(ulValue & 0x00000001)	//开光
//				{
//					/* 主机开光 */
//					BSP_Laser_OUT();
//					/* 从机数据 */
//					if(menu.Menu<=MENU_MAIN_MAX && menu.Menu!=MENU_A0 && menu.Menu !=MENU_CH) {
//						dmx512.TxBuff[DMX512_CH1] = AppData.TotalBridge;
//						dmx512.TxBuff[DMX512_CH2] = AppData.R_Bridge;
//						dmx512.TxBuff[DMX512_CH3] = AppData.G_Bridge;
//						dmx512.TxBuff[DMX512_CH4] = AppData.B_Bridge;
//						dmx512.TxBuff[DMX512_CH5] = AppData.W_Bridge;
//						dmx512.TxBuff[DMX512_CH6] = 0;
//					}
//				}
//				else if(ulValue & 0x00000002)	//闭光
//				{
//					/* 主机闭光 */
//					BSP_Laser_OFF();
//					/* 从机数据 */
//					if(menu.Menu<=MENU_MAIN_MAX && menu.Menu!=MENU_A0 && menu.Menu !=MENU_CH) {
//						dmx512.TxBuff[DMX512_CH1] = 0;
//						dmx512.TxBuff[DMX512_CH2] = 0;
//						dmx512.TxBuff[DMX512_CH3] = 0;
//						dmx512.TxBuff[DMX512_CH4] = 0;
//						dmx512.TxBuff[DMX512_CH5] = 0;
//						dmx512.TxBuff[DMX512_CH6] = 0;
//					}
//				}
//				
//				/* 主菜单、主机模式，发送数据到从机 */
//				if(menu.Menu<=MENU_MAIN_MAX && menu.Menu!=MENU_A0 && menu.Menu !=MENU_CH) {
//					/* 从机电机位置 */
//					dmx512.TxBuff[DMX512_CH7]  = AppData.X_Tune;
//					dmx512.TxBuff[DMX512_CH8]  = AppData.X_Fine;
//					dmx512.TxBuff[DMX512_CH9]  = AppData.X_Speed;
//					dmx512.TxBuff[DMX512_CH10] = AppData.Y_Tune;
//					dmx512.TxBuff[DMX512_CH11] = AppData.Y_Fine;
//					dmx512.TxBuff[DMX512_CH12] = AppData.Y_Speed;
//					dmx512.TxBuff[DMX512_CH13] = AppData.F_Tune;
//					dmx512.TxBuff[DMX512_CH14] = AppData.F_Fine;
//					dmx512.TxBuff[DMX512_CH15] = AppData.F_Speed;
//					/* 发送数据到从机 */
//					BSP_DMX512_TransmitData(0x36);
//				}
//			}
//		}
//	}
//}

extern const uint16_t SinTable[1024];
extern const uint16_t CosTable[1024];

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	uint16_t index;
	uint32_t position=0;
	
	__set_PRIMASK(1);	//关闭所有中断
	SysTick_Init(48);	//初始化SysTick
	BSP_Motor_Init();	//电机初始化
	while(1)
    {
		index = position%128;
		switch(index>>5)	//4个象限
		{
			case 0:
				M3_AXIS_PWMA = (uint32_t)SinTable[index-0];
				M3_AXIS_PWMB = 0;
				M3_AXIS_PWMC = 0;
				M3_AXIS_PWMD = (uint32_t)CosTable[index-0];
			break;
			
			case 1:
				M3_AXIS_PWMA = (uint32_t)CosTable[index-32];
				M3_AXIS_PWMB = 0;
				M3_AXIS_PWMC = (uint32_t)SinTable[index-32];
				M3_AXIS_PWMD = 0;
			break;
			
			case 2:
				M3_AXIS_PWMA = 0;
				M3_AXIS_PWMB = (uint32_t)SinTable[index-64];
				M3_AXIS_PWMC = (uint32_t)CosTable[index-64];
				M3_AXIS_PWMD = 0;
			break;
			
			case 3:
				M3_AXIS_PWMA = 0;
				M3_AXIS_PWMB = (uint32_t)CosTable[index-96];
				M3_AXIS_PWMC = 0;
				M3_AXIS_PWMD = (uint32_t)SinTable[index-96];
			break;
		}
		position++;
		delay_ms(1);
    }
}

/**
  * @brief  SysTick中断回调函数
  * @param  无
  * @retval 无
  */
void SysTick_Handler_User(void)
{
	
}
