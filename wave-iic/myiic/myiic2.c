#ifndef _C_MYIIC2_
#define _C_MYIIC2_
#include "all.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//IIC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//IIC��ʼ��
void IIC_Init_2(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOHʱ��
    
    //PH4,5��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    IIC_SDA_2=1;
    IIC_SCL_2=1;  
}

//����IIC��ʼ�ź�
void IIC_Start_2(void)
{
	SDA_OUT_2();                              //sda�����
	IIC_SDA_2=1;	  	  
	IIC_SCL_2=1;
	delay_us(10);
 	IIC_SDA_2=0;                              //START:when CLK is high,DATA change form high to low 
	delay_us(10);
	IIC_SCL_2=0;                              //ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_2(void)
{
	SDA_OUT_2();                              //sda�����
	IIC_SCL_2=1;
	IIC_SDA_2=0;                              //STOP:when CLK is high DATA change form low to high
 	delay_us(10); 
	IIC_SDA_2=1;                              //����I2C���߽����ź�
	delay_us(10);
  IIC_SCL_2=0;	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_2(void)
{
	u8 ucErrTime=0;
	SDA_IN_2();                               //SDA����Ϊ����  
	IIC_SDA_2=1;delay_us(6);	   
	IIC_SCL_2=1;delay_us(6);	 
	while(READ_SDA_2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_2();
			return 1;
		}
	}
	IIC_SCL_2=0;                              //ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=0;
	delay_us(10);
	IIC_SCL_2=1;
	delay_us(10);
	IIC_SCL_2=0;
}
//������ACKӦ��		    
void IIC_NAck_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=1;
	delay_us(10);
	IIC_SCL_2=1;
	delay_us(10);
	IIC_SCL_2=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_2(u8 txd)
{                        
    u8 t;   
	  SDA_OUT_2(); 	    
    IIC_SCL_2=0;                           //����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA_2=(txd&0x80)>>7;
        txd<<=1; 	  
		    delay_us(10);                      //��TEA5767��������ʱ���Ǳ����
		    IIC_SCL_2=1;
		    delay_us(10); 
		    IIC_SCL_2=0;	
		    delay_us(10);
    }
    IIC_SDA_2=1;		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_2(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_2();                              //SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_2=0; 
        delay_us(10);
		IIC_SCL_2=1;
        receive<<=1;
        if(READ_SDA_2)receive++;   
		delay_us(5); 
    }					 
    if (!ack)
        IIC_NAck_2();                      //����nACK
    else
        IIC_Ack_2();                       //����ACK   
    return receive;
}

#endif
