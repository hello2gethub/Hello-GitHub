/**
  ************************************************************************************************
  * @file    main.c
  * @author  长沙学院-李佳钰、徐振翔
  * @version V1.0
  * @date    2022-6-7
  * @brief   智能小车
  *************************************************************************************************
  * 硬件平台: STM32F103ZET6系统板 + ESP-01S wifi模块 + TCRT5000红外模块*5 + L9110S电机驱动板
  * QQ：1599077792 | 1935261033
  * 本团队能力有限，设计难免有问题和漏洞，欢迎大家指正。
  *************************************************************************************************
  */ 
  
  /*----------------	外设接口 ---------------------*/
  
  /*-------	ESP-01S -----------*
  VCC	->	3V
  GND	->	GND
  RX	->	PB10
  TX	->	PB11
  RST	->	PC7
  EN	->	3V3
  
  *-------	TCRT5000 -----------*
  VCC	->	3V
  GND	->	GND
  
  避障（从左至右）
  OUT	->	PA1、PA2、PA3
  
  寻迹（从左至右）
  DO	->	PB3、PB5
  
  *-------	L9110 -----------*
  VCC	->	5V
  GND	->	GND
  A1	->	PB6
  A2	->	PB7
  B1	->	PA8
  B2	->	PA11
  -----------------------------*/
  
#include "stm32f10x.h"
#include "bit_band.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "pwm.h"
#include "MotorDrive.h"
#include "trail.h"
#include "elude.h"
#include "stdbool.h"
#include "esp8266.h"
#include "usart.h"
#include "cJSON.h"
#include "onenet.h"

int main(void)
{	
	const char *topics[] = {"Topic/sub"};				//订阅主题名字
	
	unsigned char *dataPtr = NULL;						//接收数据包
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//NVIC分组2：2位抢占优先级，2位响应优先级
	
	delay_Init();										// 延时初始化
	
	LED_Init_JX() ;										// 初始化LED
	KEY_Init();											//按键初始化
	
	Usart1_Init(115200); 								//debug 串口1
	Usart2_Init(115200); 								// ESP8266通信串口3
	
	TIM1_PWM_Init_JX();									// TIM1_PWM初始化
	TIM4_PWM_Init_JX();									// TIM4_PWM初始化
	
	Trail_Input_Init_JX();								// 红外寻迹初始化
	Elude_Input_Init_JX();								// 红外避障初始化
	
	UsartPrintf(USART_DEBUG, " 初始化成功！\r\n");
	
	ESP8266_Init();										//初始化ESP8266
	while(OneNet_DevLink())								//接入Emqx服务器
		delay_ms(500);
	OneNet_Subscribe(topics,1);							//订阅主题Topic/sub
	
	
	while(1)
	{	
		dataPtr = ESP8266_GetIPD(3);					//如果接到信息，dataPtr不为空
		if(dataPtr != NULL)								//不为空则调用函数执行解析数据包做出相关指令
			OneNet_RevPro(dataPtr);
		delay_ms(10);		 
	}
	
}

