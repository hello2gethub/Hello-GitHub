#ifndef	__ELUDE_H
#define __ELUDE_H

#include "stm32f10x.h"


// S_Elude_Infrared_Input的低三位分别对应[PA3、PA2、PA1]的状态值
// 未遇到障碍(未接收到红外光)：对应状态 = 1
// 遇到障碍(接收到红外光)：对应状态 = 0
//--------------------------------------------------------------
extern u8 S_Elude_Input ;		// 三个寻迹模块的返回值
//--------------------------------------------------------------


// 红外避障情况
//-----------------------------------------------------------------
#define		Not_Find_Barrier			0x07	// 未发现障碍
#define		Middle_Find_Barrier			0x05	// 中间发现障碍
#define		Left_Find_Barrier			0x06	// 左边发现障碍
#define		Left_Middle_Find_Barrier	0x04	// 左中侧发现障碍
#define		Right_Find_Barrier			0x03	// 右边发现障碍
#define		Right_Middle_Find_Barrier	0x01	// 右中侧发现障碍

#define		Left_Right_Find_Barrier		0x02	// 左右测发现障碍

#define		All_Find_Barrier			0x00	// 全部发现障碍
//-----------------------------------------------------------------


void Elude_Input_Init_JX(void);		// 红外避障初始化

void Elude_detect_barrier(void);	// 红外避障检测函数

void BZ(void);


#endif	/* __ELUDE_H*/

