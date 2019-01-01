

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned long ) 48000000 )		//CPU主频  48MHz
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )				//每秒钟时钟周期
#define configMAX_PRIORITIES		( 5 )								//最高优先级为0~4
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 80 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 4 * 1024 ) )
#define configMAX_TASK_NAME_LEN		( 16 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_xTaskGetSchedulerState	1
#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_uxTaskPriorityGet		0
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
//#define INCLUDE_xTimerPendFunctionCall	1

/* 软件定时器 */
#define configUSE_TIMERS				0
#define configTIMER_TASK_PRIORITY	   (2)
#define configTIMER_QUEUE_LENGTH		2
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )


/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         2
#endif


#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			3		//最低优先级中断
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	1		//受FreeRTOS管理的最高优先级


/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 				( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 			( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


/* 错误断言函数 */
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );}


/* FreeRTOS需要使用的中断服务函数 */
#define vPortSVCHandler			SVC_Handler
#define xPortPendSVHandler		PendSV_Handler


#endif
