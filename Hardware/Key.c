#include "Key.h"
#include "Delay.h"

uint8_t Key_Num;

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_12;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
}

uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	
	if(Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	
	return 0;
}


uint8_t Key_GetStatus(void)
{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
	{
		return 2;
	}
	return 0;
}

void Key_Tick(void)
{
	static uint8_t Key_Tick;
	static uint8_t Currstate,PrevState;
	
	Key_Tick++;
	if(Key_Tick >= 20)
	{
		Key_Tick = 0;
		
		PrevState = Currstate;
		Currstate = Key_GetStatus();
		
		if(Currstate == 0 && PrevState != 0)
		{
			Key_Num = PrevState;
		}
	}
}

