#include "stm32f10x.h"                  // Device header



uint16_t Timer_GetTIM_CNT(void)
{
	return TIM_GetCounter(TIM2);
}

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
	TIM_Cmd(TIM2, ENABLE);	
}



