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
//��ʼ����
//�����������ȼ�
#define START_TASK_PRIO     3
//���������ջ�Ĵ�С
#define START_STK_SIZE      512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO			4
//���������ջ��С
#define LED0_STK_SIZE			128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *p_arg);

//��������
//�����������ȼ�
#define WAVE_TASK_PRIO			5
//���������ջ��С
#define WAVE_STK_SIZE			128
//������ƿ�
OS_TCB WAVETaskTCB;
//�����ջ
CPU_STK WAVE_TASK_STK[WAVE_STK_SIZE];
//������
void wave_task(void *p_arg);

//lcd12864����
//�����������ȼ�
#define LCD_TASK_PRIO			6
//���������ջ��С
#define LCD_STK_SIZE			128
//������ƿ�
OS_TCB LCDTaskTCB;
//�����ջ
CPU_STK LCD_TASK_STK[LCD_STK_SIZE];
//������
void lcd_task(void *p_arg);

//��������
//�����������ȼ�
#define MOTOR_TASK_PRIO			7
//���������ջ��С
#define MOTOR_STK_SIZE			128
//������ƿ�
OS_TCB MOTORTaskTCB;
//�����ջ
CPU_STK MOTOR_TASK_STK[WAVE_STK_SIZE];
//������
void motor_task(void *p_arg);

//24C02����
//�����������ȼ�
#define C2402_TASK_PRIO			8
//���������ջ��С
#define C2402_STK_SIZE			128
//������ƿ�
OS_TCB C2402TaskTCB;
//�����ջ
CPU_STK C2402_TASK_STK[WAVE_STK_SIZE];
//������
void c2402_task(void *p_arg);

OS_SEM wave_sem; //����һ���ź��������ݳ����������ź�
/* printff�ض������ض��򴮿�1 ---------------------------------------------------------*/
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
  delay_init(180);                                       //΢�뼶���ݵ�����
  /* Initialize all configured peripherals */
  MX_GPIO_Init();                                        //GPIO�ĳ�ʼ������
  MX_DMA_Init();                                         //DMAͨ��������
//  MX_USART2_UART_Init();                                 //����2������  for RFID��дģ��
  MX_USART3_UART_Init();                                 //����3������  for wifiģ��
//  MX_TIM13_Init();                                       //��ʱ��13��������PWM��
//  MX_TIM14_Init();                                       //��ʱ��14��������PWM��
//	MX_TIM3_Init();
  MX_ADC1_Init();                                        //ADC��ʼ������
  IIC_Init_2();                                          //ģ��iic for wave��ʼ��
	IIC_Init();                                            //ģ��iic for 24c02��ʼ��
  /* Initialize interrupts */
  MX_NVIC_Init();                                       //�ж����ȼ�������
  Show_Static();
	OSInit(&err);                                           //UCOS��ʼ��
	OS_CRITICAL_ENTER();
	
	OSTaskCreate((OS_TCB*  )&StartTaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"start task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )start_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )START_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&START_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )START_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )START_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	OS_CRITICAL_EXIT(); //�˳��ٽ��� 
  OSStart(&err);      //����ucosIII
  while(1);									
}

void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg=p_arg;
	
  CPU_Init();
#if OS_CFG_STAT_TASK_EN>0u
	 OSStatTaskCPUUsageInit(&err);            //ͳ������
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN              //ʹ�ܣ������жϹر�
	    CPU_IntDisMeasMaxCurReset();
#endif
	
#if OS_CFG_SCHED_ROUND_ROBIN_EN
	 OSSchedRoundRobinCfg(DEF_ENABLED,10,&err);
#endif
	
	 OS_CRITICAL_ENTER();                     //�����ٽ���
	 OSSemCreate((OS_SEM*   )&wave_sem,
	             (CPU_CHAR* )"wave_sem",
	             (OS_SEM_CTR)1,
							 (OS_ERR*   )&err);
	 OSTaskCreate((OS_TCB*  )&Led0TaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"led0 task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )led0_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )LED0_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&LED0_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )LED0_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )LED0_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	 OSTaskCreate((OS_TCB*  )&WAVETaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"wave task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )wave_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )WAVE_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&WAVE_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )WAVE_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )WAVE_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
	 OSTaskCreate((OS_TCB*  )&LCDTaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"lcd task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )lcd_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )LCD_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&LCD_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )LCD_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )LCD_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
   OSTaskCreate((OS_TCB*  )&MOTORTaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"motor task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )motor_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )MOTOR_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&MOTOR_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )MOTOR_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )MOTOR_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);
   OSTaskCreate((OS_TCB*  )&C2402TaskTCB,                   //������ƿ�
									(CPU_CHAR*      )"c2402 task",                         //���ݸ��������Ĳ���
									(OS_TASK_PTR    )c2402_task,             //�����ջջ��
									(void*          )0,                      //�������ȼ�
									(OS_PRIO        )C2402_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(CPU_STK*       )&C2402_TASK_STK[0],        //�����ջջ��
									(CPU_STK_SIZE   )C2402_STK_SIZE/10,            //�����ջ��С
									(CPU_STK_SIZE   )C2402_STK_SIZE,                         //�û�����Ĵ洢��
									(OS_MSG_QTY     )0,                      //����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
                  (OS_TICK        )0,
									(void*          )0,
									(OS_OPT         )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR|OS_OPT_TASK_SAVE_FP,
									(OS_ERR*        )&err);									
	OS_CRITICAL_EXIT();
  OSTaskDel((OS_TCB*)0,&err);									
}

//LED0����
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

//WAVE����
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

//motor����
void motor_task(void *p_arg)
{	 	
	OS_ERR err;
	while(1)
	{		
   OSSemPend(&wave_sem,0,OS_OPT_PEND_BLOCKING,0,&err);
	 printf("a\r\n");
	}
}

//24c02����
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

//lcd����
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
