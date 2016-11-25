#ifndef _C_USART_
#define _C_USART_
#include "all.h"


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//����Ǵ���1
	{
				if(aRxBuffer_1[0]==0x2a)   //*��ͷ ��ʼ����
				{
					flag_usart_1=1;
				  packflag_1=0;
				}
				if(aRxBuffer_1[0]==0x23)      //#��βpackflag��ʾ�������
				{
//					Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
//					USART_RX_STA_1++;
				  flag_usart_1=0;
				  packflag_1=1;
				}
				if(flag_usart_1==1)
				{
				  Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
					USART_RX_STA_1++;
					if(USART_RX_STA_1>(USART_REC_LEN_1-1))
					{
						flag_usart_1=0;//�������ݴ���,���¿�ʼ����	
					  USART_RX_STA_1=0;
					}
				}			
	} 
	 else if(huart->Instance==USART2)        //RFID
	{
	     if(aRxBuffer_2[0]==0xaa)   //0XAA��ͷ ��ʼ����
				{
					flag_usart_2=1;
				  packflag_2=0;
					USART_RX_STA_2=0;
				}
				if(aRxBuffer_2[0]==0x55)      //0X55��βpackflag��ʾ�������
				{
				  flag_usart_2=0;
				  packflag_2=1;
				}
				if(flag_usart_2==1)
				{
				  Rx_buff_2[USART_RX_STA_2&0X3FFF]=aRxBuffer_2[0] ;
					USART_RX_STA_2++;
					if(USART_RX_STA_2>(USART_REC_LEN_2-1))
					{flag_usart_2=0;//�������ݴ���,���¿�ʼ����	
						USART_RX_STA_2=0;
					}
				}			
	}
	else if(huart->Instance==USART3)                 //wifi
	{
	     if(aRxBuffer_3[0]==0x2a)   //*��ͷ ��ʼ����
				{
					flag_usart_3=1;
				  packflag_3=0;
				}
				if(aRxBuffer_3[0]==0x23)      //#��βpackflag��ʾ�������
				{
//					Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
//					USART_RX_STA_1++;
				  flag_usart_3=0;
				  packflag_3=1;
				}
				if(flag_usart_3==1)
				{
				  Rx_buff_3[USART_RX_STA_3&0X3FFF]=aRxBuffer_3[0] ;
					USART_RX_STA_3++;
					if(USART_RX_STA_3>(USART_REC_LEN_3-1))
					{flag_usart_3=0;//�������ݴ���,���¿�ʼ����	
				   USART_RX_STA_3=0;
					}			
			}
	}
}

void USART1_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart1);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer_1, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntExit();  											 
#endif
} 

void USART2_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart2);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart2, (u8 *)aRxBuffer_2, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntExit();  											 
#endif
} 

void USART3_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart3);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer_3, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntExit();  											 
#endif
} 	

void Uart_test(void)            //����1�����Ӻ���
{	
   	  if(packflag_2==1)            //���ڻ������ݱ�־λ
		{					   
			len=USART_RX_STA_2&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\nthe news is:\r\n");
			HAL_UART_Transmit(&huart2,(uint8_t*)Rx_buff_2,len,1000);	//���ͽ��յ�������
			while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			packflag_2=0;                                              //
			USART_RX_STA_2=0; 
		}else
		{
			times++;
			if(times%200==0)printf("please input char \r\n");  
			delay_ms(10); 
    }
}

int Uart_Store(void)                 //ת�溯����Rx_buff_22��������õĵ�ͼ
{
 int k=0;                       
 if(packflag_3==1)
 {
	 if((Rx_buff_3[1]=='W')&&(Rx_buff_3[2]=='A')&&(Rx_buff_3[3]=='Y'))           //��⵽��ͼ��Ϣ
		 {
				len=USART_RX_STA_3&0x3fff;
				for(k=0;k<=len;k++)
				 {
					Rx_buff_33[k]=Rx_buff_3[k];
				 }
				 packflag_3=0;
				 USART_RX_STA_3=0;
				 n=(Rx_buff_33[6]-'0')*10+(Rx_buff_33[7]-'0');
				 Uart_Analyse();
				return 1;
     }
 }
 return 0;
}	


void Uart_Analyse(void)
{
	 int i=0;
	 int j=0;
	 Track_buff=(int **)malloc(n*sizeof(int*));
	 for(i=0;i<n;i++)
	 {
	 Track_buff[i]=(int *)malloc(6*sizeof(int));//ÿ6��Ϊһ��RFID��Ϣ
	 } 
   for(i=0;i<n;i++)
	 {
	   for(j=0;j<6;j++)
		 {
		  Track_buff[i][j]=Rx_buff_33[i*6+8+j];
		 }
	 }
}

void free_array(void)
{	
	  int i=0;
		for(i=0;i<n;i++) 
		{ 
		free(Track_buff[i]);   //�ͷŶ�ά����
		} 
		free(Track_buff);      //�ͷ�һά����
}


#endif
