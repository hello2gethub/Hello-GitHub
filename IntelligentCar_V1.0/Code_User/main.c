/**
  ************************************************************************************************
  * @file    main.c
  * @author  ��ɳѧԺ-����ڡ�������
  * @version V1.0
  * @date    2022-6-7
  * @brief   ����С��
  *************************************************************************************************
  * Ӳ��ƽ̨: STM32F103ZET6ϵͳ�� + ESP-01S wifiģ�� + TCRT5000����ģ��*5 + L9110S���������
  * QQ��1599077792 | 1935261033
  * ���Ŷ��������ޣ���������������©������ӭ���ָ����
  *************************************************************************************************
  */ 
  
  /*----------------	����ӿ� ---------------------*/
  
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
  
  ���ϣ��������ң�
  OUT	->	PA1��PA2��PA3
  
  Ѱ�����������ң�
  DO	->	PB3��PB5
  
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
	const char *topics[] = {"Topic/sub"};				//������������
	
	unsigned char *dataPtr = NULL;						//�������ݰ�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//NVIC����2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	delay_Init();										// ��ʱ��ʼ��
	
	LED_Init_JX() ;										// ��ʼ��LED
	KEY_Init();											//������ʼ��
	
	Usart1_Init(115200); 								//debug ����1
	Usart2_Init(115200); 								// ESP8266ͨ�Ŵ���3
	
	TIM1_PWM_Init_JX();									// TIM1_PWM��ʼ��
	TIM4_PWM_Init_JX();									// TIM4_PWM��ʼ��
	
	Trail_Input_Init_JX();								// ����Ѱ����ʼ��
	Elude_Input_Init_JX();								// ������ϳ�ʼ��
	
	UsartPrintf(USART_DEBUG, " ��ʼ���ɹ���\r\n");
	
	ESP8266_Init();										//��ʼ��ESP8266
	while(OneNet_DevLink())								//����Emqx������
		delay_ms(500);
	OneNet_Subscribe(topics,1);							//��������Topic/sub
	
	
	while(1)
	{	
		dataPtr = ESP8266_GetIPD(3);					//����ӵ���Ϣ��dataPtr��Ϊ��
		if(dataPtr != NULL)								//��Ϊ������ú���ִ�н������ݰ��������ָ��
			OneNet_RevPro(dataPtr);
		delay_ms(10);		 
	}
	
}

