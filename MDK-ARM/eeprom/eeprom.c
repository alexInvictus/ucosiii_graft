#include "all.h"

void Eeprom_Read(void)
{
  AT24CXX_Read(0,Read_Id,3);
}

void Write_id(void)
{
  AT24CXX_Write(0,(u8*)Id,3); 
}

void Send_Id(void)
{
 HAL_UART_Transmit(&huart3,(u8*)Obj,4,1000);
 HAL_UART_Transmit(&huart3,(u8*)Read_Id,3,1000);
 HAL_UART_Transmit(&huart3,(u8*)GG,1,1000);
}	


