/**
  ******************************************************************************
  * @file    main.c
  * @author  �Ʋ���
  * @version V1.0.0
  * @date    2018-06-19
  * @brief   C������ں������������񣬳�ʼ������
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
//	ҡͷͼ��3ɫ
//		DMX512ͨ��˵��
//	  13ͨ��ģʽ:
//		CH1:X����޼���ת  0:�����  1~127:��ת���ٶ���������  128~255:��ת���ٶ��ɿ쵽�� ���ȼ�����ͨ��2
//		CH2:X���λ��      0~255:��Ӧ0~540��
//		CH3:Y���λ��      0~255:��Ӧ0~180��(ʵ�ʲ�ֹ180��)
//		CH4:ͼ�����       0~255:��Ӧ��ͬͼ��
//		CH5:����ٶ�       0~255:�ɿ쵽��
//		CH6:�ܵ���
//		CH7:��
//		CH8:��
//		CH9:��
//		CH10:Ƶ��
//		CH11:�깦��
//		CH12:�깦���ٶ�
//		CH13:��λ >=200����5��
//		
//	����->�ӻ���
//		CH1:�ܵ���
//		CH2:��
//		CH3:��
//		CH4:��
//		CH5:��
//		CH6:Ƶ��
//		CH7:X����ֵ�
//		CH8:X���ϸ��
//		CH9:X����ٶ�
//		CH10:Y����ֵ�
//		CH11:Y���ϸ��
//		CH12:Y����ٶ�
//		CH13:ͼ������ֵ�
//		CH14:ͼ�����ϸ��
//		CH15:ͼ������ٶ�
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
//  * @brief  ��ʼ�����������񽫴����ﴴ��
//  * @param  *pvParameters:
//  * @retval ��
//  */
//void vTask_StartTask(void *pvParameters)
//{
//	uint8_t t=0;
//	TickType_t xLastWakeTime;
//	const TickType_t xFrequency = 5;
//	
//	taskENTER_CRITICAL();	//�����ٽ���
//	
///**************** ����������� ****************/
//	xTaskCreate(vTask_Motor,
//	            "vTask Motor",
//	            80,
//	            NULL,
//	            4,
//	            &xHandleTask_Motor);
//	
//	taskEXIT_CRITICAL();	//�˳��ٽ���
//	
//	xLastWakeTime = xTaskGetTickCount();
//	for(;;)
//	{
//		t += xFrequency;
//		if(t >= 10) {		 //10ms
//			t -= 10;		//���¼�ʱ
//			BSP_KEY_Scan();	//ɨ�谴��
//			if(BSP_KEY_GetPresFlag()!=0) {	//�а�������
//				/* ֪ͨ�˵������а������� */
//				if(xHandleTask_DispKeyMenu!=NULL) {
//					xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_Key, eSetBits);
//				}
//			}
//		}
//		BSP_Disp_Scan();	//ɨ����ʾ
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
//  * @brief  �������
//  * @param  *pvParameters:
//  * @retval ��
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
//	Menu_ReadMemory();	//�Ӵ洢����ȡ�˵�ֵ
//	
//	timeout = 4*1000;	//4�볬ʱ
//	do{
//		status  = BSP_Motor_PosReset(&M1pid);
//		status |= BSP_Motor_PosReset(&M2pid);
//		if(status==0) {	//ȫ����λ���
//			break;
//		}
//		vTaskDelay(1);
//	}while(timeout--);
//	
//	taskENTER_CRITICAL();	//�����ٽ���
///******** �����λ��ɣ�������������׼������ϵͳ ********/
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
//	taskEXIT_CRITICAL();	//�˳��ٽ���
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
//  * @brief  ��ʾ���������˵�����
//  * @param  *pvParameters:
//  * @retval ��
//  */
//void vTask_DispKeyMenu(void *pvParameters)
//{
//	uint8_t MenuCmd;
//	uint32_t ulValue;
//	BaseType_t xResult;
//	
//	Menu_Init();	//�˵���ʼ��
//	for(;;)
//	{
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, portMAX_DELAY);
//		
//		if(xResult==pdTRUE)		//�¼���־
//		{
//			if(ulValue & Menu_Event_Key)
//			{
//				MenuCmd = 0x00; 				//0x00:��������
//			}
//			else if(ulValue & Menu_Event_DmxReady)
//			{
//				MenuCmd = MENU_CMD_DMX_READY; 	//0x00:DMX512��������
//			}
//			else if(ulValue & Menu_Event_DmxNoReady)
//			{
//				MenuCmd = MENU_CMD_DMX_NOREADY;	//0x00:DMX512�Ͽ�����
//			}
//			Menu_Display(MenuCmd);
//		}
//	}
//}

///**
//  * @brief  ��������
//  * @param  *pvParameters:
//  * @retval ��
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
//	OldTick    = xTaskGetTickCount();	//��ǰϵͳʱ��
//	FunMenuOld = APP_ALLOFF;
//	for(;;)
//	{
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, 100);
//		
//		if(xResult==pdTRUE)		//�¼���־
//		{
//			if((ulValue&Command_Event_MENU) || (ulValue&Command_Event_DMX512_END))	//�˵���������DMX512�յ�����
//			{
//				if(ulValue&Command_Event_DMX512_END) {
//					if(menu.Menu==MENU_A0) {
//						timeout=0;									//��ʱ����
//						BSP_DispPointStatus(SMG_Bits_4, ENABLE);	//����С����
//						BSP_DispRefurbish();						//ˢ����ʾ
//						Fun_DMX512_Control(dmx512.RxBuff);			//DMX512����
//					}else{
//						if(menu.ValMem.AD_Value==1 && menu.Menu!=MENU_AD &&	//"ADYE"
//						   menu.Menu<=MENU_MAIN_MAX) 						//���˵�
//						{
//							DmxReadyCount++;								//������1
//							if(DmxReadyCount >= 2) {						//���������յ�Ready�ź�
//								DmxReadyFlag = 1;
//							}
//						}
//					}
//				}else if(ulValue&Command_Event_MENU) {
//					if(menu.Menu!=MENU_A0) {
//						if(menu.Menu<=MENU_MAIN_MAX) {
//							Fun_MainMenu_Control();			//���˵����ܿ���
//						}else{
//							Fun_HideMenu_Control();			//���ز˵����ܿ���
//						}
//					}
//					DmxReadyCount = 0;						//�������£����¼���
//					DmxReadyFlag  = 0;						//������־����
//				}
//			}
//			else if(ulValue & Command_Event_Fun)	//Ӧ�ò����������
//			{
//				/* ��APP���ݸ��µ�Ӳ���㣬���������� */
//				laser.R_Bridge     = AppData.R_Bridge;
//				laser.G_Bridge     = AppData.G_Bridge;
//				laser.B_Bridge     = AppData.B_Bridge;
//				laser.W_Bridge     = AppData.W_Bridge;
//				laser.FlashSpeed   = AppData.FlashSpeed;
//				laser.TotalBridge  = AppData.TotalBridge;
//				/* ���µ��λ�� */
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
//				/* ֪ͨ�������Ҫ�ı�λ�� */
//				xTaskNotify(xHandleTask_Motor, 0x00000001, eSetBits);
//				/* ֪ͨ����������Ҫ�ı伤��״̬��ͬ�·����ݵ��ӻ� */
//				xTaskNotify(xHandleTask_Laser, 0x00000001, eSetBits);
//			}
//		}
//		
//		NowTick = xTaskGetTickCount();		//��ǰϵͳʱ��
//		if(NowTick-OldTick >= 100) {		//0.1��
//			OldTick += 100;
//			
//			if(DmxReadyFlag==1) {	//DMX512������
//				/* ֪ͨ�˵���DMX512�źž��� */
//				xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_DmxReady, eSetBits);
//			}
//			
//			if(menu.Menu==MENU_A0) {
//				if(timeout<250) {
//					timeout++;
//				}
//				if(timeout>=12){
//					if(timeout==30) {
//						/* ֪ͨ�˵���DMX512�źŶϿ� */
//						xTaskNotify(xHandleTask_DispKeyMenu, Menu_Event_DmxNoReady, eSetBits);
//					}
//					app.FunMenu = APP_ALLOFF;
//					BSP_DispPointStatus(SMG_Bits_4, DISABLE);	//�ر�С����
//					BSP_DispRefurbish();						//ˢ����ʾ
//				}
//			}
//		}
//		
//		if(FunMenuOld != app.FunMenu)	//���ܸı���
//		{
//			FunMenuOld = app.FunMenu;
//			app.Running = 0;			//�˳���ǰ����
//		}
//	}
//}

///**
//  * @brief  ��������
//  * @param  *pvParameters:
//  * @retval ��
//  */
//void vTask_FunProg(void *pvParameters)
//{
//	/* ���ܳ�ʼ�� */
//	FunProg_Init();
//	
//	for(;;)
//	{
//		/* ���ܴ��� */
//		FunProg_Display();
//	}
//}

///**
//  * @brief  ��������
//  * @param  *pvParameters:
//  * @retval ��
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
//		if(laser.FlashSpeed == 0)	//�ر�Ƶ��
//		{
//			/* ֪ͨBSP���񣬿��� */
//			xTaskNotify(xHandleTask_BSP, 0x00000001, eSetBits);
//			/* ÿ��10ms����һ�� */
//			xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, 10);
//			
//			if(xResult) {
//				
//			}
//		}
//		else
//		{
//			/* ���ε�Ƶ���ٶ� */
//			FlashSpeedOld = laser.FlashSpeed;
//			/* ֪ͨBSP���񣬿��� */
//			xTaskNotify(xHandleTask_BSP, 0x00000001, eSetBits);
//			/* ����30ms */
//			vTaskDelay(30);
//			/* ֪ͨBSP���񣬱չ� */
//			xTaskNotify(xHandleTask_BSP, 0x00000002, eSetBits);
//			/* �չ�40ms */
//			vTaskDelay(40);
//			
//			FlashDelayLen = (uint16_t)(255-FlashSpeedOld)*4;	//�����ʱ1020ms
//			
//			while(FlashDelayLen)	/* �ȴ���ʱ��� */
//			{
//				if(FlashDelayLen >= 10) {
//					/* ֪ͨBSP���񣬱չ� */
//					xTaskNotify(xHandleTask_BSP, 0x00000002, eSetBits);
//					/* ��ʱ20ms */
//					vTaskDelay(10);
//					/* ʣ�����ʱ */
//					FlashDelayLen -= 10;
//					
//					if(laser.FlashSpeed == 0) {	/* �ر�Ƶ��������ѭ�� */
//						break;
//					}else{
//						if(laser.FlashSpeed > FlashSpeedOld)	/* Ƶ���ٶȱ�� */
//						{
//							/* �ٶȸ��º���ʱ */
//							temp = (uint16_t)(255-laser.FlashSpeed)*4;
//							
//							if(FlashDelayLen > temp){
//								/* ʹ�ý϶̵���ʱ */
//								FlashDelayLen = temp;
//							}
//						}
//					}
//				}else{
//					/* ʣ����ʱ */
//					vTaskDelay(FlashDelayLen);
//					break;
//				}
//			}
//		}
//	}
//}

///**
//  * @brief  BSP���񣬸���������
//  * @param  *pvParameters:
//  * @retval ��
//  */
//void vTask_BSP(void *pvParameters)
//{
//	uint32_t ulValue;
//	BaseType_t xResult;
//	
//	for(;;)
//	{
//		/* ���޵ȴ� */
//		xResult = xTaskNotifyWait(0x00000000, 0xFFFFFFFF, &ulValue, portMAX_DELAY);
//		
//		if(xResult==pdTRUE)		//�¼���־
//		{
//			if(ulValue & 0x00000003)
//			{
//				if(ulValue & 0x00000001)	//����
//				{
//					/* �������� */
//					BSP_Laser_OUT();
//					/* �ӻ����� */
//					if(menu.Menu<=MENU_MAIN_MAX && menu.Menu!=MENU_A0 && menu.Menu !=MENU_CH) {
//						dmx512.TxBuff[DMX512_CH1] = AppData.TotalBridge;
//						dmx512.TxBuff[DMX512_CH2] = AppData.R_Bridge;
//						dmx512.TxBuff[DMX512_CH3] = AppData.G_Bridge;
//						dmx512.TxBuff[DMX512_CH4] = AppData.B_Bridge;
//						dmx512.TxBuff[DMX512_CH5] = AppData.W_Bridge;
//						dmx512.TxBuff[DMX512_CH6] = 0;
//					}
//				}
//				else if(ulValue & 0x00000002)	//�չ�
//				{
//					/* �����չ� */
//					BSP_Laser_OFF();
//					/* �ӻ����� */
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
//				/* ���˵�������ģʽ���������ݵ��ӻ� */
//				if(menu.Menu<=MENU_MAIN_MAX && menu.Menu!=MENU_A0 && menu.Menu !=MENU_CH) {
//					/* �ӻ����λ�� */
//					dmx512.TxBuff[DMX512_CH7]  = AppData.X_Tune;
//					dmx512.TxBuff[DMX512_CH8]  = AppData.X_Fine;
//					dmx512.TxBuff[DMX512_CH9]  = AppData.X_Speed;
//					dmx512.TxBuff[DMX512_CH10] = AppData.Y_Tune;
//					dmx512.TxBuff[DMX512_CH11] = AppData.Y_Fine;
//					dmx512.TxBuff[DMX512_CH12] = AppData.Y_Speed;
//					dmx512.TxBuff[DMX512_CH13] = AppData.F_Tune;
//					dmx512.TxBuff[DMX512_CH14] = AppData.F_Fine;
//					dmx512.TxBuff[DMX512_CH15] = AppData.F_Speed;
//					/* �������ݵ��ӻ� */
//					BSP_DMX512_TransmitData(0x36);
//				}
//			}
//		}
//	}
//}

extern const uint16_t SinTable[1024];
extern const uint16_t CosTable[1024];

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint16_t index;
	uint32_t position=0;
	
	__set_PRIMASK(1);	//�ر������ж�
	SysTick_Init(48);	//��ʼ��SysTick
	BSP_Motor_Init();	//�����ʼ��
	while(1)
    {
		index = position%128;
		switch(index>>5)	//4������
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
  * @brief  SysTick�жϻص�����
  * @param  ��
  * @retval ��
  */
void SysTick_Handler_User(void)
{
	
}
