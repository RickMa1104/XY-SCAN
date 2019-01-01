/**
  ******************************************************************************
  * @file    bsp_motor.c
  * @author  唐昌生
  * @version V3.1.0
  * @date    2018-06-21
  * @brief   多电机驱动函数
  *
  ******************************************************************************
  * @attention
  *           12V供电：
  *               1、X电机阻值选择16R-20R最佳
  *               2、Y电机阻值选择16R-20R最佳
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "bsp_motor.h"
#include "sin_table.h"
//#include "menu.h"



/**
  * @brief  电机参数配置
  * @param  无
  * @retval 无
  */
static void M_Config(void)
{
	
}

/**
  * @brief  电机驱动初始化
  * @param  无
  * @retval 无
  */
static void BSP_Motor_Driver_Hand(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/* 使能GPIO的时钟 */
	RCC_AHBPeriphClockCmd( M1_AXIS_PWMA_GPIO_CLK | M1_AXIS_PWMB_GPIO_CLK |
	                       M2_AXIS_PWMA_GPIO_CLK | M2_AXIS_PWMB_GPIO_CLK |
						   M3_AXIS_PWMA_GPIO_CLK | M3_AXIS_PWMB_GPIO_CLK |
						   M3_AXIS_PWMC_GPIO_CLK | M3_AXIS_PWMD_GPIO_CLK |
						   M1_HALL_GPIO_CLK, ENABLE);
	/* 使能SYSCFG时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/* 使能定时器时钟 */
	M1_AXIS_TIM_CLOCK_CMD(M1_AXIS_TIM_CLK, ENABLE);
	M3_AXIS_TIM_CLOCK_CMD(M3_AXIS_TIM_CLK, ENABLE);
	MOTOR_COM_TIM_CLOCK_CMD(MOTOR_COM_TIM_CLK, ENABLE);
	
	/* 浮空输入 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* M1_Hall引脚 */
	GPIO_InitStruct.GPIO_Pin = M1_HALL_GPIO_PIN;
	GPIO_Init(M1_HALL_GPIO_PORT, &GPIO_InitStruct);
	/* M2_Hall引脚 */
	GPIO_InitStruct.GPIO_Pin = M2_HALL_GPIO_PIN;
	GPIO_Init(M2_HALL_GPIO_PORT, &GPIO_InitStruct);
	
	/* 推挽复用输出，内部上拉 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* M1_PWMA引脚 */
	GPIO_InitStruct.GPIO_Pin = M1_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M1_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M1_PWMB引脚 */
	GPIO_InitStruct.GPIO_Pin = M1_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M1_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	/* M2_PWMA引脚 */
	GPIO_InitStruct.GPIO_Pin = M2_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M2_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M2_PWMB引脚 */
	GPIO_InitStruct.GPIO_Pin = M2_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M2_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	
	/* M1_PWMA复用配置 */
	GPIO_PinAFConfig(M1_AXIS_PWMA_GPIO_PORT, M1_AXIS_PWMA_SOURCE, M1_AXIS_PWMA_GPIO_AF);
	/* M1_PWMB复用配置 */
	GPIO_PinAFConfig(M1_AXIS_PWMB_GPIO_PORT, M1_AXIS_PWMB_SOURCE, M1_AXIS_PWMB_GPIO_AF);
	/* M2_PWMB复用配置 */
	GPIO_PinAFConfig(M2_AXIS_PWMA_GPIO_PORT, M2_AXIS_PWMA_SOURCE, M2_AXIS_PWMA_GPIO_AF);
	/* M2_PWMB复用配置 */
	GPIO_PinAFConfig(M2_AXIS_PWMB_GPIO_PORT, M2_AXIS_PWMB_SOURCE, M2_AXIS_PWMB_GPIO_AF);
	
	/* 向上计数 */
	TIM_TimeBaseInitStruct.TIM_Prescaler = M1_AXIS_TIM_PSC;
	TIM_TimeBaseInitStruct.TIM_Period = M1_AXIS_TIM_ARR;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/* 初始化M1定时器 */
	TIM_TimeBaseInit(M1_AXIS_TIM_BASE, &TIM_TimeBaseInitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = MOTOR_COM_TIM_PSC;
	TIM_TimeBaseInitStruct.TIM_Period = MOTOR_COM_TIM_ARR;
	/* 初始化COM定时器 */
	TIM_TimeBaseInit(MOTOR_COM_TIM_BASE, &TIM_TimeBaseInitStruct);
	
	/* PWM模式配置 */
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	/* 初始化4个通道 */
	TIM_OC1Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC2Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC3Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC4Init(M1_AXIS_TIM_BASE, &TIM_OCInitStruct);
	
	/* 配置定时器中断 */
	NVIC_InitStruct.NVIC_IRQChannel = MOTOR_COM_TIM_NVIC_Channel;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	/* 清除更新中断标志 */
	TIM_ClearFlag(MOTOR_COM_TIM_BASE, TIM_FLAG_Update);
	/* 开启更新中断 */
	TIM_ITConfig(MOTOR_COM_TIM_BASE, TIM_IT_Update, ENABLE);
	
	if(M1_AXIS_TIM_BASE==TIM1)
	{
		/* 主输出使能 */
		TIM_CtrlPWMOutputs(M1_AXIS_TIM_BASE, ENABLE);
	}
	
	
	
	
	
	
	/* 推挽复用输出，内部上拉 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* M3_PWMA引脚 */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMA_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMA_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWMC引脚 */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMC_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMC_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWMB引脚 */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMB_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMB_GPIO_PORT, &GPIO_InitStruct);
	/* M3_PWME引脚 */
	GPIO_InitStruct.GPIO_Pin = M3_AXIS_PWMD_GPIO_PIN;
	GPIO_Init(M3_AXIS_PWMD_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(M3_AXIS_PWMA_GPIO_PORT, M3_AXIS_PWMA_SOURCE, M3_AXIS_PWMA_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMC_GPIO_PORT, M3_AXIS_PWMC_SOURCE, M3_AXIS_PWMC_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMB_GPIO_PORT, M3_AXIS_PWMB_SOURCE, M3_AXIS_PWMB_GPIO_AF);
	GPIO_PinAFConfig(M3_AXIS_PWMD_GPIO_PORT, M3_AXIS_PWMD_SOURCE, M3_AXIS_PWMD_GPIO_AF);
	
	/* 向上计数 */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_Period = 2400;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/* 初始化M3定时器 */
	TIM_TimeBaseInit(M3_AXIS_TIM_BASE, &TIM_TimeBaseInitStruct);
	
	/* PWM模式配置 */
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	/* 初始化4个通道 */
	TIM_OC1Init(M3_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC2Init(M3_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC3Init(M3_AXIS_TIM_BASE, &TIM_OCInitStruct);
	TIM_OC4Init(M3_AXIS_TIM_BASE, &TIM_OCInitStruct);
	
	/* 初始化4个通道 */
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);
	TIM_OC2Init(TIM1, &TIM_OCInitStruct);
	TIM_OC3Init(TIM1, &TIM_OCInitStruct);
	TIM_OC4Init(TIM1, &TIM_OCInitStruct);
	
	
	/* 使能M1定时器 */
	TIM_Cmd(M1_AXIS_TIM_BASE, ENABLE);
	/* 使能M3定时器 */
	TIM_Cmd(M3_AXIS_TIM_BASE, ENABLE);
	/* 使能COM定时器 */
	TIM_Cmd(MOTOR_COM_TIM_BASE, ENABLE);
}

/**
  * @brief  获取霍尔状态
  * @param  *m:电机句柄
  * @retval 0:正在霍尔位置  1:不在霍尔位置
  */
//static uint8_t M_IsHall(_mpid *m)
//{
//	uint8_t rev=1;
//	
//	if(m->axis==M1_AXIS) {
//		if(M1_HALL_IN==0)rev=0;
//		else rev = 1;
//	}else if(m->axis==M2_AXIS) {
//		if(M2_HALL_IN==0)rev=0;
//		else rev = 1;
//	}
//	return rev;
//}

/**
  * @brief  电机初始化
  * @param  无
  * @retval 无
  */
void BSP_Motor_Init(void)
{
	/* 配置参数 */
	M_Config();
	/* 初始化驱动 */
	BSP_Motor_Driver_Hand();
}

/**
  * @brief  DMX512控制电机位置
  * @param  *m:电机句柄
  * @param  Position:电机位置
  * @param  speed:速度
  * @retval 无
//  */
//void BSP_Motor_Position(_mpid *m, uint32_t Position, uint16_t speed)
//{
//	m->EndPosition = Position + m->OffsetPosition;
//	m->EndSpeed    = speed;
//}

/**
  * @brief  更新最高运行速度
  * @param  *m:电机句柄
  * @retval 无
  */
//void M_UpdateRunSpeed(_mpid *m)
//{
//	uint16_t retryspeed;
//	
//	retryspeed = m->MoveStep/m->DecelLow;		//能够跑的最高速度
//	if(retryspeed < m->EndSpeed) {
//		m->RunSpeed = retryspeed;
//	}else{
//		m->RunSpeed = m->EndSpeed;
//	}
//}

/**
  * @brief  电机定时器公共中断服务函数
  * @param  无
  * @retval 无
  */
void MOTOR_COM_TIM_IRQHandler(void)
{
	if(TIM_GetITStatus(MOTOR_COM_TIM_BASE, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(MOTOR_COM_TIM_BASE, TIM_IT_Update);
		/* 控制电机位置和速度 */
//		M_PositionProc(&M1pid);
//		M_PositionProc(&M2pid);
//		M_PositionProc(&M3pid);
	}
}

/**
  * @brief  霍尔中断服务函数
  * @param  无
  * @retval 无
  */
void M1M2_HALL_COM_IRQHandler(void)
{
	if(EXTI_GetITStatus(M1_HALL_EXTI_Line) != RESET)
	{
		EXTI_ClearITPendingBit(M1_HALL_EXTI_Line);	//清除中断标志
	}
	
	if(EXTI_GetITStatus(M2_HALL_EXTI_Line) != RESET)
	{
		EXTI_ClearITPendingBit(M2_HALL_EXTI_Line);	//清除中断标志
		
	}	
}
