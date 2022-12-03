#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"


// 宏定义
//--------------------------------------------------
#define LED_Green	PA_out(1)	// LED1(LED_Green)
#define LED_Bule	PA_out(2)	// LED2(LED_Bule)



// 初始化PA1、PA2
//--------------------------------------------------
void LED_Init_JX(void);		// PA1、PA2设为推挽输出高



#endif	/* __LED_H */
