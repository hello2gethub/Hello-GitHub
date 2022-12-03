#include "elude.h"
#include "MotorDrive.h"
#include "delay.h"

u8 S_Elude_Input = 0 ;		// 三个红外避障模块的返回值


// 红外避障初始化(将PA1、PA2、PA3初始化为上拉输入)
// Elude_左 -- PA1
// Elude_中 -- PA2
// Elude_右 -- PA3
//----------------------------------------------------------------------------------------------
void Elude_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			// GPIOB时钟使能
	
	
	// 避障：Elude--PA1、PA2、PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	// Elude--PA1、PA2、PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// 输入模式不需要设端口速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);							// 初始化PA1、PA2、PA3
	
}
//----------------------------------------------------------------------------------------------


// 红外避障检测函数
// S_Elude_Input的低三位分别对应[PA3、PA2、PA1]的状态值
// 未遇到障碍(未接收到红外光)：对应状态 = 1
// 遇到障碍(接收到红外光)：对应状态 = 0
//-------------------------------------------------------------
void Elude_detect_barrier(void)
{
	S_Elude_Input = 0 ;
	
	S_Elude_Input = (((u8)GPIOA->IDR) & 0x0E)>>1;
}
//-------------------------------------------------------------


void BZ(void)
{
	Elude_detect_barrier();	// 红外避障检测
		
		
		// 未发现障碍
		//-------------------------------------------------------	
		if( S_Elude_Input == Not_Find_Barrier )	
		{									
			Car_forward(100);	// 前进
		}
		//-------------------------------------------------------
	
		// 左侧发现障碍
		//----------------------------------------------
		else if( S_Elude_Input == Left_Find_Barrier || S_Elude_Input == Left_Middle_Find_Barrier )
		{
			Car_Turn_Right(200);	//右转
		}
		
		// 右侧发现障碍
		//----------------------------------------------
		else if( S_Elude_Input == Right_Find_Barrier || S_Elude_Input == Right_Middle_Find_Barrier )
		{
			Car_Turn_Left(200);	// 左转
		}
		
		// 中间/全部发现障碍
		//----------------------------------------------
		else if( S_Elude_Input == Middle_Find_Barrier || S_Elude_Input == All_Find_Barrier )
		{
			Car_backward(200);	// 后退
			delay_ms(300);
			Car_Turn_Left(200);	// 左转
			delay_ms(300);
		}
		
		// 其他情况
		//----------------------------------------------
		else // if( S_Elude_Input == Left_Right_Find_Barrier )
		{
			Car_forward(100);	// 前进
		}
}
