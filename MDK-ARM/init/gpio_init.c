#include "all.h"


void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

  /*Motor��������ʹ�ܺͷ�����Ƶ�gpio����PC4��PC6ʹ��  PC5��PC7 �������*/
  GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
//	/*���ⷴ��GPIO�ڵĶ��壨ǰ�ã�PB0-PB4 PB14 */
//	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_14;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/*���ⷴ��GPIO�ڵĶ��壨���ã�PE2-6*/ 
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
  /*�����ķ���GPIO�ڶ���PG2���� PG3ֹͣ*/
  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

//  /*�����ƵĶ���*/
//	GPIO_InitStruct.Pin = GPIO_PIN_13;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
//	/*��ȫ���ߵ����Ŷ���*/
//	GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*LCD�ӿڶ���  PH13--RS/CS  PH14--RW/SID PH15--E/SCLK  PI8--RST*/
	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_8;  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	
	/*�̵����Ŀ��ƿڣ������������Ƹ˺͵��������*/
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12;  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_15;  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/*���Ƶ�Դ�Ŀ�*/
	GPIO_InitStruct.Pin = GPIO_PIN_6;  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_9;  
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4,  GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,  GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6,  GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);	
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6,  GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,  GPIO_PIN_SET);
}


