

#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H


#include "bsp_hw_config.h"


/* MOTOR时基定时器(多个电机可共用) */
#define MOTOR_COM_TIM_BASE			TIM6
#define MOTOR_COM_TIM_CLK			RCC_APB1Periph_TIM6
#define MOTOR_COM_TIM_CLOCK_CMD		RCC_APB1PeriphClockCmd
#define MOTOR_COM_TIM_PSC			48-1
#define MOTOR_COM_TIM_ARR			128-1
#define MOTOR_COM_TIM_NVIC_Channel	TIM6_DAC_IRQn

/* M1M2使用的定时器 */
#define M1_AXIS_TIM_BASE			TIM1
#define M1_AXIS_TIM_CLK				RCC_APB2Periph_TIM1
#define M1_AXIS_TIM_CLOCK_CMD		RCC_APB2PeriphClockCmd
#define M1_AXIS_TIM_PSC				0
#define M1_AXIS_TIM_ARR				2400-1

/* M3使用的定时器 */
#define M3_AXIS_TIM_BASE			TIM3
#define M3_AXIS_TIM_CLK				RCC_APB1Periph_TIM3
#define M3_AXIS_TIM_CLOCK_CMD		RCC_APB1PeriphClockCmd
#define M3_AXIS_TIM_PSC				0
#define M3_AXIS_TIM_ARR				2400-1

/* M1_PWMA引脚 */
#define M1_AXIS_PWMA_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M1_AXIS_PWMA_GPIO_PORT		GPIOA
#define M1_AXIS_PWMA_GPIO_PIN		GPIO_Pin_8
#define M1_AXIS_PWMA_GPIO_AF		GPIO_AF_2
#define M1_AXIS_PWMA_SOURCE			GPIO_PinSource8
#define M1_AXIS_PWMA				TIM1->CCR1

/* M1_PWMB引脚 */
#define M1_AXIS_PWMB_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M1_AXIS_PWMB_GPIO_PORT		GPIOA
#define M1_AXIS_PWMB_GPIO_PIN		GPIO_Pin_9
#define M1_AXIS_PWMB_GPIO_AF		GPIO_AF_2
#define M1_AXIS_PWMB_SOURCE			GPIO_PinSource9
#define M1_AXIS_PWMB				TIM1->CCR2

/* M2_PWMA引脚 */
#define M2_AXIS_PWMA_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M2_AXIS_PWMA_GPIO_PORT		GPIOA
#define M2_AXIS_PWMA_GPIO_PIN		GPIO_Pin_10
#define M2_AXIS_PWMA_GPIO_AF		GPIO_AF_2
#define M2_AXIS_PWMA_SOURCE			GPIO_PinSource10
#define M2_AXIS_PWMA				TIM1->CCR3

/* M2_PWMB引脚 */
#define M2_AXIS_PWMB_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M2_AXIS_PWMB_GPIO_PORT		GPIOA
#define M2_AXIS_PWMB_GPIO_PIN		GPIO_Pin_11
#define M2_AXIS_PWMB_GPIO_AF		GPIO_AF_2
#define M2_AXIS_PWMB_SOURCE			GPIO_PinSource11
#define M2_AXIS_PWMB				TIM1->CCR4

/* M3_PWMA引脚 */
#define M3_AXIS_PWMA_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M3_AXIS_PWMA_GPIO_PORT		GPIOA
#define M3_AXIS_PWMA_GPIO_PIN		GPIO_Pin_6
#define M3_AXIS_PWMA_GPIO_AF		GPIO_AF_1
#define M3_AXIS_PWMA_SOURCE			GPIO_PinSource6
#define M3_AXIS_PWMA				TIM3->CCR1
/* M3_PWMC引脚 */
#define M3_AXIS_PWMC_GPIO_CLK		RCC_AHBPeriph_GPIOA
#define M3_AXIS_PWMC_GPIO_PORT		GPIOA
#define M3_AXIS_PWMC_GPIO_PIN		GPIO_Pin_7
#define M3_AXIS_PWMC_GPIO_AF		GPIO_AF_1
#define M3_AXIS_PWMC_SOURCE			GPIO_PinSource7
#define M3_AXIS_PWMC				TIM3->CCR2
/* M3_PWMB引脚 */
#define M3_AXIS_PWMB_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define M3_AXIS_PWMB_GPIO_PORT		GPIOB
#define M3_AXIS_PWMB_GPIO_PIN		GPIO_Pin_0
#define M3_AXIS_PWMB_GPIO_AF		GPIO_AF_1
#define M3_AXIS_PWMB_SOURCE			GPIO_PinSource0
#define M3_AXIS_PWMB				TIM3->CCR3
/* M3_PWMD引脚 */
#define M3_AXIS_PWMD_GPIO_CLK		RCC_AHBPeriph_GPIOB
#define M3_AXIS_PWMD_GPIO_PORT		GPIOB
#define M3_AXIS_PWMD_GPIO_PIN		GPIO_Pin_1
#define M3_AXIS_PWMD_GPIO_AF		GPIO_AF_1
#define M3_AXIS_PWMD_SOURCE			GPIO_PinSource1
#define M3_AXIS_PWMD				TIM3->CCR4

/* M1_Hall引脚 */
#define M1_HALL_GPIO_CLK			RCC_AHBPeriph_GPIOB
#define M1_HALL_GPIO_PORT			GPIOB
#define M1_HALL_GPIO_PIN			GPIO_Pin_10
#define M1_HALL_IN					(M1_HALL_GPIO_PORT->IDR&M1_HALL_GPIO_PIN)
#define M1_HALL_EXTI_Line			EXTI_Line10
#define M1_HALL_EXTI_PortSource		EXTI_PortSourceGPIOB
#define M1_HALL_EXTI_PinSource		EXTI_PinSource10

/* M2_Hall引脚 */
#define M2_HALL_GPIO_CLK			RCC_AHBPeriph_GPIOB
#define M2_HALL_GPIO_PORT			GPIOB
#define M2_HALL_GPIO_PIN			GPIO_Pin_11
#define M2_HALL_IN					(M2_HALL_GPIO_PORT->IDR&M2_HALL_GPIO_PIN)
#define M2_HALL_EXTI_Line			EXTI_Line10
#define M2_HALL_EXTI_PortSource		EXTI_PortSourceGPIOB
#define M2_HALL_EXTI_PinSource		EXTI_PinSource11

/* 外部中断4-15，公用中断线 */
#define M1M2_COM_EXTI_NVIC_Channel	EXTI4_15_IRQn


/* 电机方向 */
#define M_MOV_CW		0
#define M_MOV_CCW		1

/* 电机ID号 */
typedef enum
{
	M1_AXIS = 0,
	M2_AXIS = 1,
	M3_AXIS = 2,
	M_AXIS_NUM,	//电机数量
}M_AXIS_ID;


/* 最大位置 */
#define M1_MAX_POS		(uint32_t)(200*1024*1.0)
#define M2_MAX_POS		(uint32_t)(200*1024*1.0)
#define M3_MAX_POS		(uint32_t)(200*1024*1.0)


/* X电机无极旋转，左右偏转位置 */
#define M1_RIGHT_POS	((uint32_t)1024*200)
#define M1_LEFT_POS		((uint32_t)1024*480)

/* X电机无极旋转，上下限 */
#define M1_MAX_LIM		((uint32_t)1024*200*20000)
#define M1_MIN_LIM		((uint32_t)1024*200*10)


/* 电机加减速结构体 */
typedef struct
{
	uint32_t AddStep   : 10;	//最大0x3FF
	uint32_t TotalStep : 22;	//最大0x3FFFFF
}MotorStepType;



/* 外部中断中断服务函数 */
void M1M2_HALL_COM_IRQHandler(void);
/* 电机处理中断服务函数 */
void MOTOR_COM_TIM_IRQHandler(void);


void BSP_Motor_Init(void);

#endif
