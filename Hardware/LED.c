#include "stm32f10x.h"                  // Device header
#include "LED.h"

uint8_t LED_Mode;

uint16_t LED1_count;

/**
* 功能：函数的初始化
* 参数： 无
* 返回值： 无
*/

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4);

}


/**
* 功能：写入LED1
* 参数： LED_State
* 返回值： 无
*/
void Set_LED1(uint8_t LED)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)LED);
}


/**
* 功能：写入LED2
* 参数： LED_State
* 返回值： 无
*/
void Set_LED2(uint8_t LED)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)LED);
}



/**
* 功能：关闭LED3
* 参数： 无
* 返回值： 无
*/
void LED3_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


/**
* 功能：开启LED3
* 参数： 无
* 返回值： 无
*/
void LED3_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}


/**
* 功能：翻转LED1
* 参数： 无
* 返回值： 无
*/
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1))
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
}


/**
* 功能：翻转LED2
* 参数： 无
* 返回值： 无
*/
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2))
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
}

/**
* 功能：读取LED灯
* 参数： 引脚
* 返回值： 1或0
*/

uint8_t Get_LED_Output(uint16_t Pin)
{
	return (GPIO_ReadInputDataBit(GPIOA,Pin));
}



void LED_SetMode(uint8_t Mode)
{
	if(Mode != LED_Mode)
	{
		LED_Mode = Mode;
		LED1_count  =0;
	}
}

void LED_Tick(void)
{
	
	if(LED_Mode == 0)
	{
		Set_LED1(1);
	}
	
	else if (LED_Mode == 1)
	{
		Set_LED1(0);
	}
	
	else if(LED_Mode == 2)
	{
		LED1_count++;
		LED1_count %= 1000;
		
		if(LED1_count < 500)
		{
			Set_LED1(0);
		}
		else
		{
			Set_LED1(1);
		}
	}
	else if (LED_Mode == 3)
	{
		LED1_count ++;
		LED1_count %= 100;
		
		if (LED1_count < 50)
		{
			Set_LED1(0);
		}
		else
		{
			Set_LED1(1);
		}
	}
	
}
