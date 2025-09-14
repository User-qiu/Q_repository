#include "stm32f10x.h"


/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}


/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
}

/*

	课堂代码如下

*/


uint32_t _xus;//表示1us所需要的次数
uint32_t _xms;//表示1ms所需要的次数
// Clk_Src表示时钟频率

void delay_init2(uint32_t Clk_Src)
{
	SysTick->CTRL &= ~(0x05);//外部时钟源（为配置时钟源的8分频），关闭定时器
	_xus = Clk_Src / 8;
	_xms = _xus * 1000;//1ms=1000us
}

void delay_us(uint32_t nus)
{
	SysTick->LOAD = _xus * nus;//1us需要的时间
	SysTick->CTRL |= (0x01<<0);//开启计数器
	while((SysTick->CTRL&(1<16))==0);//计数完毕跳出循环
	SysTick->CTRL &= ~(0x01<<0);//关闭计数器
	SysTick->VAL = 0;//当前计数值置0
}

void delay_ms(uint32_t nms)
{
	SysTick->LOAD = _xus * nms;//1us需要的时间
	SysTick->CTRL |= (0x01<<0);//开启计数器
	while((SysTick->CTRL&(1<16))==0);//计数完毕跳出循环
	SysTick->CTRL &= ~(0x01<<0);//关闭计数器
	SysTick->VAL = 0;//当前计数值置0
}

void delay_s(uint32_t ns)
{
	while(ns--)
	{
		delay_ms(1000);
	}
}
