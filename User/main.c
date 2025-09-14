#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "LED.h"

uint8_t KeyNum;
uint8_t FlashFlag;

uint16_t i;

int main(void)
{

	OLED_Init();
	LED_Init();
	Key_Init();
	Timer_Init();
	
	while(1)
	{
		KeyNum = Key_GetNum();
		
		if(KeyNum == 2)
		{
			FlashFlag++;
			LED_SetMode(FlashFlag);
			FlashFlag %= 4;
		}
		
		OLED_ShowNum(1,1,i++,5);
		OLED_ShowNum(2,1,FlashFlag,3);
	}
}


void TIM2_IRQHandler(void)
{
	Key_Tick();
	LED_Tick();
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}
