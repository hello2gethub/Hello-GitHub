#include "trail.h"
#include "MotorDrive.h"
#include "delay.h"

u8 S_Trail_Input = 0 ;		// 三个寻迹模块的返回值


// 红外寻迹初始化(将PB3、PB4、PB5初始化为上拉输入)
// Trail -- PB3
// Trai2 -- PB4
// Trai3 -- PB5
//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// 使能GPIOB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			// GPIOB时钟使能
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// 复用时钟使能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);			// 将PB3、PB4释放为通用GPIO口
	
	// 寻迹：Trail--PB3、PB4、PB5端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	// Trail--PB3、PB4、PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// 输入模式不需要设端口速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// 初始化PB3、PB4、PB5
	
}
//----------------------------------------------------------------------------------------------


// 黑线寻迹函数
// S_Trail_Input的低三位分别对应[PB5、PB4、PB3]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
//----------------------------------------------------
void Trail_black_line(void)
{
	S_Trail_Input = 0 ;
	
	S_Trail_Input = (((u8)GPIOB->IDR) & 0x38)>>3;
}
//----------------------------------------------------

void XJ(void)
{
		u16 C_Not_Find_Black = 0 ;			// 未发现黑线计时

		u8  F_Not_Find_Black_STOP = 0 ;		// 长时间未发现黑线标志位
		Trail_black_line();		// 黑线检测函数
		
		// 未发现黑线
		//-------------------------------------------------------	
		if( S_Trail_Input == Not_Find_Black_Line )	
		{
			if( F_Not_Find_Black_STOP == 1 )	// 判断是否长时间未发现黑线	
				Car_Stop(CAR_FLAMEOUT);			// 停车
			
			else										
				Car_forward(60);				// 前进
		}
		//-------------------------------------------------------
		
		
		// 发现黑线
		//---------------------------------------------------------------------------------------------------
		else 
		{
			C_Not_Find_Black = 0;			// 清除“未发现黑线计时”,计时在定时器中断函数中
			
			F_Not_Find_Black_STOP = 0 ;		// 清除“长时间未发现黑线标志位”	
			
			
			// 两侧都没发现黑线
			//----------------------------------------------
			if(S_Trail_Input != Left_Find_Black_Line && S_Trail_Input != Left_Middle_Find_Black_Line && S_Trail_Input != Right_Find_Black_Line && S_Trail_Input != Right_Middle_Find_Black_Line )
			{
				Car_forward(60);	// 前进
			}
		
			// 左侧发现黑线
			//----------------------------------------------
			else if( S_Trail_Input == Left_Find_Black_Line || S_Trail_Input == Left_Middle_Find_Black_Line )
			{
				Car_Turn_Left(60);	// 左转
			}
			
			// 右侧发现黑线
			//----------------------------------------------
			else if( S_Trail_Input == Right_Find_Black_Line || S_Trail_Input == Right_Middle_Find_Black_Line )
			{
				Car_Turn_Right(60);	// 右转
			}
			
			// 其他情况
			//----------------------------------------------
			else 
			{
				Car_Stop(CAR_FLAMEOUT);	// 熄火
			}
		}
}
