/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#define _C_MAIN_
#include "all.h"
//起始任务
//设置任务优先级
#define START_TASK_PRIO     3
//设置任务堆栈的大小
#define START_STK_SIZE      512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO			4
//设置任务堆栈大小
#define LED0_STK_SIZE			128
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *p_arg);

//串口任务
//设置任务优先级
#define WAVE_TASK_PRIO			5
//设置任务堆栈大小
#define WAVE_STK_SIZE			128
//任务控制块
OS_TCB WAVETaskTCB;
//任务堆栈
CPU_STK WAVE_TASK_STK[WAVE_STK_SIZE];
//任务函数
void wave_task(void *p_arg);

//lcd12864任务
//设置任务优先级
#define LCD_TASK_PRIO			6
//设置任务堆栈大小
#define LCD_STK_SIZE			128
//任务控制块
OS_TCB LCDTaskTCB;
//任务堆栈
CPU_STK LCD_TASK_STK[LCD_STK_SIZE];
//任务函数
void lcd_task(void *p_arg);

//串口任务
//设置任务优先级
#define MOTOR_TASK_PRIO			7
//设置任务堆栈大小
#define MOTOR_STK_SIZE			128
//任务控制块
OS_TCB MOTORTaskTCB;
//任务堆栈
CPU_STK MOTOR_TASK_STK[WAVE_STK_SIZE];
//任务函数
void motor_task(void *p_arg);

//24C02任务
//设置任务优先级
#define C2402_TASK_PRIO			8
//设置任务堆栈大小
#define C2402_STK_SIZE			128
//任务控制块
OS_TCB C2402TaskTCB;
//任务堆栈
CPU_STK C2402_TASK_STK[WAVE_STK_SIZE];
//任务函数
void c2402_task(void *p_arg);

OS_SEM wave_sem; //定义一个信号量，传递超声波控制信号
/* printff重定向函数重定向串口1 ---------------------------------------------------------*/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
HAL_UART_Transmit(&huart3 , (uint8_t *)&ch, 1, 0xFFFF);
return ch;
} 

int main(void)
{
/* MCU Configuration----------------------------------------------------------*/
  OS_ERR err;
	CPU_SR_ALLOC();
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
  delay_init(180);                                       //微秒级数据的配置
  /* Initialize all configured peripherals */
  MX_GPIO_Init();                                        //GPIO的初始化配置
  MX_DMA_Init();                                         //DMA通道的配置
//  MX_USART2_UART_Init();                                 //串口2的配置  for RFID读写模块
  MX_USART3_UART_Init();                                 //串口3的配置  for wifi模块
//  MX_TIM13_Init();                                       //定时器13产生左轮PWM波
//  MX_TIM14_Init();                                       //定时器14产生右轮PWM波
//	MX_TIM3_Init();
  MX_ADC1_Init();                                        //ADC初始化设置
  IIC_Init_2();                                          //模拟iic for wave初始化
	IIC_Init();                                            //模拟iic for 24c02初始化
  /* Initialize interrupts */
  MX_NVIC_Init();                                       //中断优先级的设置
  Show_Static();
	OSInit(&err);                                           //UCOS初始化
	OS_CRITICAL_ENTER();
	
	OSTaskCreate((OS_TCB*  )&StartTaskTCB,                   //任务控制块
									(CPU_CHAR*      )"start task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )start_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )START_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&START_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )START_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )START_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	OS_CRITICAL_EXIT(); //退出临界区 
  OSStart(&err);      //开启ucosIII
  while(1);									
}

void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg=p_arg;
	
  CPU_Init();
#if OS_CFG_STAT_TASK_EN>0u
	 OSStatTaskCPUUsageInit(&err);            //统计任务
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN              //使能，测量中断关闭
	    CPU_IntDisMeasMaxCurReset();
#endif
	
#if OS_CFG_SCHED_ROUND_ROBIN_EN
	 OSSchedRoundRobinCfg(DEF_ENABLED,10,&err);
#endif
	
	 OS_CRITICAL_ENTER();                     //进入临界区
	 OSSemCreate((OS_SEM*   )&wave_sem,
	             (CPU_CHAR* )"wave_sem",
	             (OS_SEM_CTR)1,
							 (OS_ERR*   )&err);
	 OSTaskCreate((OS_TCB*  )&Led0TaskTCB,                   //任务控制块
									(CPU_CHAR*      )"led0 task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )led0_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )LED0_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&LED0_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )LED0_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )LED0_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	 OSTaskCreate((OS_TCB*  )&WAVETaskTCB,                   //任务控制块
									(CPU_CHAR*      )"wave task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )wave_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )WAVE_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&WAVE_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )WAVE_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )WAVE_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	 OSTaskCreate((OS_TCB*  )&LCDTaskTCB,                   //任务控制块
									(CPU_CHAR*      )"lcd task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )lcd_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )LCD_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&LCD_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )LCD_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )LCD_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
   OSTaskCreate((OS_TCB*  )&MOTORTaskTCB,                   //任务控制块
									(CPU_CHAR*      )"motor task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )motor_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )MOTOR_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&MOTOR_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )MOTOR_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )MOTOR_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
   OSTaskCreate((OS_TCB*  )&C2402TaskTCB,                   //任务控制块
									(CPU_CHAR*      )"c2402 task",                         //传递给任务函数的参数
									(OS_TASK_PTR    )c2402_task,             //任务堆栈栈顶
									(void*          )0,                      //任务优先级
									(OS_PRIO        )C2402_TASK_PRIO,           //任务ID，这里设置为和优先级一样
									(CPU_STK*       )&C2402_TASK_STK[0],        //任务堆栈栈底
									(CPU_STK_SIZE   )C2402_STK_SIZE/10,            //任务堆栈大小
									(CPU_STK_SIZE   )C2402_STK_SIZE,                         //用户补充的存储区
									(OS_MSG_QTY     )0,                      //任务选项,为了保险起见，所有任务都保存浮点寄存器的值
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);									
	OS_CRITICAL_EXIT();
  OSTaskDel((OS_TCB*)0,&err);									
}

//LED0任务
void led0_task(void *p_arg)
{	 	
	p_arg=p_arg;
	while(1)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2,  GPIO_PIN_SET);
		delay_ms(80);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2,  GPIO_PIN_RESET);
		delay_ms(920);
	}
}

//WAVE任务
void wave_task(void *p_arg)
{	 
	OS_ERR err;
  int wave=0;	
	while(1)
	{		
		wave=Wave_test();
		printf("%d\r\n",wave);
		if(wave==2)
		{
		 	OSSemPost(&wave_sem,OS_OPT_POST_1,&err);
		}
		delay_ms(100);
	}
}

//motor任务
void motor_task(void *p_arg)
{	 	
	OS_ERR err;
	while(1)
	{		
   OSSemPend(&wave_sem,0,OS_OPT_PEND_BLOCKING,0,&err);
	 printf("a\r\n");
	}
}

//24c02任务
void c2402_task(void *p_arg)
{
	OS_ERR err;
  CPU_SR_ALLOC();	
	while(1)
	{
  OS_CRITICAL_ENTER();		
  Eeprom_Read();
	Send_Id();
	OS_CRITICAL_EXIT();
	delay_ms(100);
  OSTaskDel((OS_TCB*)0,&err);			
	}
}

//lcd任务
void lcd_task(void *p_arg)
{	  
	CPU_SR_ALLOC();
	while(1)
	{
		OS_CRITICAL_ENTER();
		Voltage_Test();
		OS_CRITICAL_EXIT();
		delay_ms(2000);
	}
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
