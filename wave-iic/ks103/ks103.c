#ifndef _C_KS103_
#define _C_KS103_
#include "all.h"
/*模拟iic通信*/
u8 KS103_ReadOneByte(u8 address, u8 reg)
{
  u8 temp=0;
	
	IIC_Start_2();
	IIC_Send_Byte_2(address);            //发送低地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(reg);                //发送高地址
	IIC_Wait_Ack_2();
	IIC_Start_2();
	IIC_Send_Byte_2(address+1);          //进入接收模式
	IIC_Wait_Ack_2();
	
	delay_us(200);
	temp=IIC_Read_Byte_2(0);    
	IIC_Stop_2();                        //产生一个停止条件
	return temp;
}

void KS103_WriteOneByte(u8 address,u8 reg,u8 command)
{
  IIC_Start_2();
	IIC_Send_Byte_2(address);
	while(IIC_Wait_Ack_2());
	IIC_Send_Byte_2(reg);               //发送高地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(command);
	IIC_Wait_Ack_2();
	IIC_Stop_2();              
}

//u16 Wave_test(void)
//{
//	  static u16 range=0;
//		KS103_WriteOneByte(0xe8,0x02,0xb0);
//		delay_ms(80);
//		range=KS103_ReadOneByte(0xe8,0x02);
//		range<<=8; 
//		range+=KS103_ReadOneByte(0xe8,0x03);
//		return range;

//}

//u16 Get_Range(void)
//{		
//		if(only_one==0)
//		{
//			KS103_WriteOneByte(0xe8,0x02,0xb4);	//发送探测命令
//			only_one=1;
//			SCL_IN_2();
//		}
//		else
//		{			
//			if(READ_SCL_2)													
//			{	
//				SCL_OUT_2();
//				
//				range=KS103_ReadOneByte(0xe8,0x02);
//				range<<=8;
//				range+=KS103_ReadOneByte(0xe8,0x03); 
//			}			
//		}
//		return range;  
//}

u16 Get_Range(u8 addr,int index)
{	
  	
		if(only_one[index]==0)
		{
			KS103_WriteOneByte(addr,0x02,0xb4);	//发送探测命令
			
			only_one[index]=1;
			tim3_flag[index]=0;
		}
		else
		{			
			if(tim3_flag[index]>100)
				{
						range[index]=KS103_ReadOneByte(addr,0x02);
						range[index]<<=8;
						range[index]+=KS103_ReadOneByte(addr,0x03); 
						only_one[index]=0;
					
				}			
		}
	   
		return range[index];  
}

int Get_Barrier(u8 addr,int index)
{
	u16 temp_range=Get_Range(addr,index);
	if(temp_range<300)						// 如果很近检测到障碍物返回2
	{
		return 2;
	}
	else if(temp_range<1500)			// 如果较远检测到障碍物返回1
	{
		return 1;
	}
	else												//  大于1500返回0
	{
		return 0;
	}
}
void change_i2c_address(unsigned char addr_old,unsigned char addr_new)
{
  delay_ms(2000);
	KS103_WriteOneByte(addr_old,0x02,0x9a);
	delay_ms(1);
	KS103_WriteOneByte(addr_old,0x02,0x92);
	delay_ms(1);
	KS103_WriteOneByte(addr_old,0x02,0x9e);
	delay_ms(1);
	KS103_WriteOneByte(addr_old,0x02,addr_new);
	delay_ms(500);
}

#endif
