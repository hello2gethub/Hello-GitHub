#include "led.h"


// ��ʼ��PA1��PA2
//-----------------------------------------------------------------------------------------
void LED_Init_JX(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;					// ����GPIO_InitTypeDef�ͽṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// ʹ��GPIOA�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;	// LED1--PA1��LED2--PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		// IO���ٶ�Ϊ10MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);				// PA1��PA2�����
	
}
//-----------------------------------------------------------------------------------------
