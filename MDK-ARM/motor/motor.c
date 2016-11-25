#ifndef _C_MOTOR_
#define _C_MOTOR_
#include "all.h"

void Motor_Ahead_Wait(void)
{
  switch(Motor_Status)
	{
	  case Setup:
		   	 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);      //�ݶ�ǰ��
         HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);  
		     Set_Acc(200);
		     printf("b");
		     Motor_Status=Run;
		    break;
		case Motor_Acc:
			   
				 Set_Acc(200);                      //�ݶ����ٵ�200
				 Motor_Status=Run;
		
		    break;
		case Run:
         ahead_wave();               
         Find_Rfid();
		    break;
				
		case Arrive:
			   Set_Motor(200,200);
		     Set_Slowdown(200);//����ռ�ձȵķ�ʽ���ݶ�460Ϊstop
         Voltage_Test();
		     free_array();
		     HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
				 HAL_UART_Transmit(&huart3,(u8*)Wt,3,1000);          //�������󷵻ص�ͼ��ָ��
		     Command_State=Store_State;                 //����ȴ����յ�ͼ���Ҵ��ͼ��״̬
		     Motor_Status=Setup;
		     break;
		
		default:
        
		     break;			
	}
}

void Motor_Ahead(void)                                    //��ǰѭ��
{
  switch(Motor_Status)
	{
	  case Setup:
			       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);      //�ݶ�ǰ��
             HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		         Set_Acc(200);
		         Motor_Status=Run;
		    break;
		
		case Motor_Acc:
			   
			       Set_Acc(200);                      //�ݶ����ٵ�200
		         Motor_Status=Run;
		    break;
		case Run:
			       ahead_wave();	
		         Find_Rfid();	 
		    break;
		
		case Left_90:
			       Set_Motor(0,150);
		         delay_ms(Turn_time);
		         Set_Motor(460,460);
		         Motor_Status=Setup;
		    break;
	  
		case Right_90:
			       Set_Motor(150,0);
		         delay_ms(Turn_time);
		         Set_Motor(460,460);
		         Motor_Status=Setup;		
		    break;
		case Arrive:
			       Set_Motor(200,200);
		         Set_Slowdown(200);
						 Voltage_Test();
		         free_array();
		         HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
					   HAL_UART_Transmit(&huart3,(u8*)Bm,3,1000);          //�������󷵻ص�ͼ��ָ��
						 Command_State=Store_State;
						 Motor_Status=Setup;
		    break;
				
		default:
        break;			
	}
}

void Motor_Back(void)                                           //���ص�ѭ������
{
  switch(Motor_Status)
	{
	  case Setup:
			        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);    //�ݶ�����
              HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		          Set_Acc(200);
		          Motor_Status=Run;
		    break;
		
		case Motor_Acc:
			   
			        Set_Acc(200);                      //�ݶ����ٵ�200
		          Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();
		   		    back_wave();		
		    break;
		
		case Left_90:
			        Set_Motor(0,150);
		          delay_ms(Turn_time);
		          Set_Motor(460,460);
		          Motor_Status=Setup;	
		    break;
	  
		case Right_90:
			        Set_Motor(150,0);
		          delay_ms(Turn_time);
		          Set_Motor(460,460);
		          Motor_Status=Setup;			
		    break;
		case Arrive:
						  Set_Motor(200,200);
		          Set_Slowdown(200);
						  Voltage_Test();
		          free_array();
		          HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
					    HAL_UART_Transmit(&huart3,(u8*)Rm,3,1000);          //������������ͼ��ָ��
						  Command_State=Store_State;
						  Motor_Status=Setup;
		    break;			
		default:
        break;			
	}
}

void Motor_Ruku(void)                                           //����ѭ������
{
  switch(Motor_Status)
	{
	  case Setup:
			        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);     //�ݶ�ǰ��
              HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
              Set_Acc(200);		
		          Motor_Status=Run;
		    break;
		
		case Motor_Acc:
			   
			        Set_Acc(200);                                           //�ݶ����ٵ�200
		          Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();
			        back_wave();
		    break;
		
		case Left_90:
			        Set_Motor(0,150);
		          delay_ms(Turn_time);
		          Set_Motor(0,0);
		          Motor_Status=Setup;				
		    break;
	  
		case Right_90:
			        Set_Motor(150,0);
		          delay_ms(Turn_time);
		          Set_Motor(0,0);
		          Motor_Status=Setup;			
		    break;
		
		case Right_180:
			        Set_Motor(150,0);
		          delay_ms(Turn_time);
		          Set_Motor(0,0);
		          Command_State=Run_Ahead_State;
		          Motor_Status=Setup;		
		    break;
		case Arrive:
						  Set_Motor(200,200);
		          Set_Slowdown(200);                           //��200��ʼ����
						  Voltage_Test();
		          free_array();
		          HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
				      HAL_UART_Transmit(&huart3,(u8*)Wt,3,1000);          //�������󷵻ص�ͼ��ָ��
						  Command_State=Store_State;         //�ﵽ��ʼ�㣬���뻺���ͼ��״̬��
						  Motor_Status=Setup;
		    break;
		default:
        break;			
	}
}

void Ahead_Trailing(void)
{
	static int num=0,count1=0,count2=0;
	if((protect_ahead==0)||(protect_back==0))                     //��ⰲȫ����
	{
		num++;
		if(num>2000)
		{
		 if((protect_ahead==0)||(protect_back)==0)
		 {
		    Set_Motor(460,460);//�ر�
			  LED_ON;
		 }
		}
	}
	else
		{
			num=0;
		if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		count1++;
			if(count1>TEST_TIM)
			{			 
				if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
				{
					count2++;
					if(count2>TEST_TIM)
					{
				  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))  //������ֹͣ
				  {
					  Set_Motor(460,460);//�ر�
					  LED_ON;
				  }
				  }
			  }
			}		
		}
	  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 Set_Motor(20,20);//ֱ��
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 	 Set_Motor(30,20);//��Сƫ
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==0)&&(Ahead_Senor_5==1))
		{
		 	Set_Motor(20,30);//��Сƫ
		}
		else if((Ahead_Senor_1==0)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 Set_Motor(40,20);;//�Ҵ�ƫ
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==0))
		{
		Set_Motor(20,40);//���ƫ
		}
}
}

void Back_Trailing(void)
{
	static int num=0,count1=0,count2=0;
	if((protect_ahead==0)||(protect_back==0))               //��ⰲȫ����
	{
		num++;
		if(num>2000)
		{
		 if((protect_ahead==0)||(protect_back)==0)
		 {
		    Set_Motor(460,460);//�ر�
			 LED_ON;
		 }
		}
	}
	else
		{
			num=0;
		if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		count1++;
			if(count1>TEST_TIM)
			{			 
				if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
				{
					count2++;
					if(count2>TEST_TIM)
					{
				  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))     //������ֹͣ
				  {
					  Set_Motor(0,0);//�ر�
					  LED_ON;
				  }
				}
			}
		}
		
		}
	  if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_3==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
      Set_Motor(20,20);//ֱ��
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	Set_Motor(30,20);//��Сƫ
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==0)&&(Back_Senor_5==1))
		{
		 Set_Motor(20,30);//��Сƫ
		}
		else if((Back_Senor_1==0)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	 Set_Motor(40,20);//�Ҵ�ƫ
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==0))
		{
		 	 Set_Motor(20,40);//���ƫ
		}  
}

}
void Answer(void)                                  //�ظ�����λ��RFID��Ϣ
{      
	int i=0;
	if((Rx_buff_22[4]!=Rx_buff_2[4])&&(Rx_buff_22[5]!=Rx_buff_2[5])&&(Rx_buff_22[6]!=Rx_buff_2[6])&&(Rx_buff_22[7]!=Rx_buff_2[7]))
		{
			for(i=0;i<=len;i++)
		 {
			Rx_buff_22[i]=Rx_buff_2[i];
		 }
			USART_RX_STA_2=0;	
			HAL_UART_Transmit(&huart3,(u8*)Loc,4,1000);   //�ϱ�λ��
			HAL_UART_Transmit(&huart3,&Rx_buff_22[4],4,1000);
			HAL_UART_Transmit(&huart3,(u8*)GG,1,1000);
			Find_Rfid_Match();
    }	
}
                                                                                                                                                               
void Find_Rfid(void)
{
		if(data_rec_flag==1)
			{
				HAL_UART_Transmit(&huart2,(u8*)Find_cmd,4,1000);
				data_rec_flag=0;
			}
			
			if(packflag_2==1)
					{
					  if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x10)&&(Rx_buff_2[3]==0x01))		
						{
							// HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,4,1000);							
						}
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x12)&&(Rx_buff_2[3]==0x00))	  //ֹͣ�ɹ�
						{
						 //HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,4,1000);
						   HAL_UART_Transmit(&huart2,(u8*)Read_cmd,11,1000);
						}
						else if(Rx_buff_2[1]==0x15)									                                //���ɹ�
						{
							//HAL_UART_Transmit(&huart1,&Rx_buff_2[4],4,1000);					
							Answer();
							data_rec_flag=1;
						}
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x20)&&(Rx_buff_2[3]==0x80))		//��ʧ��
						{
							data_rec_flag=1;
						}
						else																				//
						{
							//HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,11,1000);
								HAL_UART_Transmit(&huart2,(u8*)Stop_cmd,4,1000);
						}							
						packflag_2=0;
					}			
}

void Find_Rfid_Match(void)
{
   int i=0;
	  for(i=0;i<=n;i++)
	{
	  if((Track_buff[i][0]==Rx_buff_2[4])&&(Track_buff[i][1]==Rx_buff_2[5])&&(Track_buff[i][2]==Rx_buff_2[6])&&(Track_buff[i][3]==Rx_buff_2[7]))
		{
			if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='l'))
			{				 
			   Command_State=Stop_State;     //Stop���´�����ֱ������ת��
				 Motor_Status=Left_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='r'))
			{
			  Command_State=Stop_State;      //Stop���´�����ֱ������ת��
				Motor_Status=Right_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='f'))
			{
			  Command_State=Stop_State;      //Stop���´�������ǰѭ��״̬
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='s'))
			{
				Motor_Status=Arrive;           //�ﵽ��ͼ�յ�
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='p'))
			{
				Command_State=Stop_State;     
				Motor_Status=Right_90;         //ת��180�����л�״̬
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='l'))
			{
			   Motor_Status=Left_90;         //no stop ,just turn left
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='r'))
			{
			  Motor_Status=Right_90;         //no stop ,just turn right
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='f'))
			{
			  //ǰ��
			}
		}
	}	
}

void Stop(void)
{
		Set_Motor(460,460);//�ر�
		Voltage_Test();
}

void Set_Motor(int left,int right)
{
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,left);
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,right);
}

void Set_Acc(int target)               //��0���ٵ�Ŀ���ٶ�
{
	  int i=0;
	  for(i=460;i>target;i--)
	{
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,i); 
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,i);		
		delay_us(100);
	}
}

void Set_Slowdown(int target)          //��Ŀ���ٶȼ��ٵ�0
{
    int i=0;
	  for(i=target;i<460;i++)
	{
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,i);
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,i);		
		delay_us(100);
	}
}

void ahead_wave(void)
{
	int wave=0;
	      wave=Get_Barrier(0xd0,0);
        if(wave_watch==1)
					{					  
              if(wave==1)
							{
							  LED_ON;
								Ahead_Trailing();
								printf("1\n");
							}
              else if(wave==0)
							{							
								LED_OFF;
			          Ahead_Trailing();
								printf("0\n");
							}
              else if(wave==2)
              {
								wave_watch=0;
								printf("2\n");
							}
					}
       else{
				      if(wave==1)
							 {
							  LED_ON;
								Motor_Status=Motor_Acc;
								LED_OFF;
								wave_watch=1;
								printf("3\n");
							 }
              else if(wave==0)
								{							
			          Motor_Status=Motor_Acc;
								LED_OFF;
								wave_watch=1;
								printf("4\n");
							  }
              else if(wave==2)
               {
							  Set_Motor(460,460);
							  LED_ON;
							  wave_watch=0;
								printf("5\n");
							 }
				}			 
}

void back_wave(void)
{
	int wave=0;
	    wave=Get_Barrier(0xe8,1);
        if(wave_watch==1){
              if(wave==1)
							{
							  LED_ON;
								Back_Trailing();
							}
              else if(wave==0)
							{	
                LED_OFF;								
			          Back_Trailing();
							}
              else if(wave==2)   //��2�μ�⵽��ͣ
              {
							LED_ON;
							wave_watch=0;
							}
						}
       else{
				      if(wave==1)
							{
							  LED_ON;
								Motor_Status=Motor_Acc;
								wave_watch=1;
							}
              else if(wave==0){							
			         Motor_Status=Motor_Acc;
								LED_OFF;
								wave_watch=1;
							}
              else if(wave==2)
              {
							  Set_Motor(460,460);
							  LED_ON;
							  wave_watch=0;
							}
				}	
}
#endif
