/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "main.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}


extern void xPortSysTickHandler( void );
extern void SysTick_Handler_User(void);
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{
		/* FreeRTOS节拍 */
		xPortSysTickHandler();
	}
	
	/* 用户SysTick回调函数 */
	SysTick_Handler_User();
}


/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @brief  EXTI4_15中断服务函数
  * @param  无
  * @retval 无
  */
void EXTI4_15_IRQHandler(void)
{
	M1M2_HALL_COM_IRQHandler();
}

/**
  * @brief  EXTI2_3中断服务函数
  * @param  无
  * @retval 无
  */
void EXTI2_3_IRQHandler(void)
{
//	SOUND_IRQ_Handler();
}





/**
  * @brief  定时器6中断服务函数
  * @param  无
  * @retval 无
  */
void TIM6_DAC_IRQHandler(void)
{
	MOTOR_COM_TIM_IRQHandler();
}

/**
  * @brief  串口1中断服务函数
  * @param  无
  * @retval 无
  */
void USART1_IRQHandler(void)
{
//	DMX512_USART_IRQHandler();
}

/**
  * @brief  DMX1_Channel2_3 中断服务函数
  * @param  无
  * @retval 无
  */
void DMA1_Channel2_3_IRQHandler(void)
{
//	DMX512_DMA_IRQHandler();
}

/**
  * @brief  定时器14中断服务函数
  * @param  无
  * @retval 无
  */
void TIM14_IRQHandler(void)
{
//	LASER_TIM_IRQHandler();
}



/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
