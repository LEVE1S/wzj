#include "stm32f10x.h"                  // Device header
void Body_Hw_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPD;	//下拉输入
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
}

uint16_t Body_Hw_GetData(void)
{
	uint16_t tempdata;
	tempdata = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
	return tempdata;
}
