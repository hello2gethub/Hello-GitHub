#include "led.h"


// 初始化PA1、PA2
//-----------------------------------------------------------------------------------------
void LED_Init_JX(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;					// 定义GPIO_InitTypeDef型结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能GPIOA端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;	// LED1--PA1、LED2--PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		// IO口速度为10MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);				// PA1、PA2输出高
	
}
//-----------------------------------------------------------------------------------------
