#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"


// �궨��
//--------------------------------------------------
#define LED_Green	PA_out(1)	// LED1(LED_Green)
#define LED_Bule	PA_out(2)	// LED2(LED_Bule)



// ��ʼ��PA1��PA2
//--------------------------------------------------
void LED_Init_JX(void);		// PA1��PA2��Ϊ���������



#endif	/* __LED_H */
