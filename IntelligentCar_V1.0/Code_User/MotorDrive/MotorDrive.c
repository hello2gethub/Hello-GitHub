#include "MotorDrive.h"

// 左前轮
//**************************************
// 左前轮=前转(速度 = speed%)
//------------------------------------
void Motor_LF_forward(u8 speed)
{
	PA9_Out_PP;
	PA_out(9) = 0;

	PA8_AF_PP;
	TIM_SetCompare1(TIM1, speed);
}
//------------------------------------

// 左前轮=后转(速度 = -speed%)
//------------------------------------
void Motor_LF_backward(u8 speed)
{
	PA8_Out_PP;
	PA_out(8) = 0;

	PA9_AF_PP;
	TIM_SetCompare2(TIM1, speed);
}
//------------------------------------


// 左前轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//------------------------------------
void Motor_LF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PA8_Out_PP;
		PA_out(8) = 0;
	
		PA9_Out_PP;
		PA_out(9) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PA8_Out_PP;
		PA_out(8) = 1;
	
		PA9_Out_PP;
		PA_out(9) = 1;
	}
}
//------------------------------------
//**************************************


// 左后轮
//**************************************
// 左后轮=前转(速度 = speed%)
//----------------------------------
void Motor_LB_forward(u8 speed)
{
	PA11_Out_PP;
	PA_out(11) = 0;
	
	PA10_AF_PP;
	TIM_SetCompare3(TIM1, speed);
}
//----------------------------------

// 左后轮=后转(速度 = -speed%)
//----------------------------------
void Motor_LB_backward(u8 speed)
{
	PA10_Out_PP;
	PA_out(10) = 0;
	
	PA11_AF_PP;
	TIM_SetCompare4(TIM1, speed);
}
//----------------------------------


// 左后轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//----------------------------------
void Motor_LB_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PA10_Out_PP;
		PA_out(10) = 0;
	
		PA11_Out_PP;
		PA_out(11) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PA10_Out_PP;
		PA_out(10) = 1;
	
		PA11_Out_PP;
		PA_out(11) = 1;
	}
}
//----------------------------------
//**************************************


// 右前轮
//**************************************
// 右前轮=前转(速度 = speed%)
//----------------------------------
void Motor_RF_forward(u8 speed)
{
	PB7_Out_PP;
	PB_out(7) = 0;
	
	PB6_AF_PP;
	TIM_SetCompare1(TIM4, speed);
	
}
//----------------------------------

// 右前轮=后转(速度 = -speed%)
//----------------------------------
void Motor_RF_backward(u8 speed)
{
	PB6_Out_PP;
	PB_out(6) = 0;
	
	PB7_AF_PP;
	TIM_SetCompare2(TIM4, speed);
	
}
//----------------------------------


// 右前轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//----------------------------------
void Motor_RF_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PB6_Out_PP;
		PB_out(6) = 0;
	
		PB7_Out_PP;
		PB_out(7) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PB6_Out_PP;
		PB_out(6) = 1;
	
		PB7_Out_PP;
		PB_out(7) = 1;
	}
}
//----------------------------------
//**************************************



// 右后轮
//**************************************
// 右后轮=前转(速度 = speed%)
//----------------------------------
void Motor_RB_forward(u8 speed)
{
	PB9_Out_PP;
	PB_out(9) = 0;
	
	PB8_AF_PP;
	TIM_SetCompare3(TIM4, speed);
	
}
//----------------------------------

// 右后轮=后转(速度 = -speed%)
//----------------------------------
void Motor_RB_backward(u8 speed)
{
	PB8_Out_PP;
	PB_out(8) = 0;
	
	PB9_AF_PP;
	TIM_SetCompare4(TIM4, speed);
	
}
//----------------------------------


// 右前轮=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//----------------------------------
void Motor_RB_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		PB8_Out_PP;
		PB_out(8) = 0;
	
		PB9_Out_PP;
		PB_out(9) = 0;
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		PB8_Out_PP;
		PB_out(8) = 1;
	
		PB9_Out_PP;
		PB_out(9) = 1;
	}
}
//----------------------------------
//**************************************




// 小车运动情况
//**************************************
// 小车=停止(熄火/刹车)
// Wheel_STOP = 0：熄火	1：刹车
//---------------------------------
void Car_Stop(u8 Wheel_STOP)
{
	if( Wheel_STOP == 0 )	// 熄火
	{
		Motor_LF_Stop(0);
		Motor_LB_Stop(0);
		Motor_RF_Stop(0);
		Motor_RB_Stop(0);
	}
	
	else//if(Wheel_STOP==1)	// 刹车
	{
		Motor_LF_Stop(1);
		Motor_LB_Stop(1);
		Motor_RF_Stop(1);
		Motor_RB_Stop(1);
	}
}
//---------------------------------


// 小车向后(速度 = speed%)
//---------------------------------
void Car_backward(u8 speed)
{
	Motor_LF_forward(speed);
	Motor_LB_forward(speed);
			
	Motor_RF_forward(speed);
	Motor_RB_forward(speed);
}
//---------------------------------


// 小车向前(速度 = -speed%)
//---------------------------------
void Car_forward(u8 speed)
{
	Motor_LF_backward(speed);
	Motor_LB_backward(speed);
					
	Motor_RF_backward(speed-10);
	Motor_RB_backward(speed-10);
}
//---------------------------------



// 小车左转
// 左侧车轮向后转(速度 = -speed%)
// 右侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Left(u8 speed)
{
	Motor_LF_backward(speed);
	Motor_LB_backward(speed);
			
	Motor_RF_forward(speed);
	Motor_RB_forward(speed);
}
//---------------------------------


// 小车右转
// 右侧车轮向后转(速度 = -speed%)
// 左侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Right(u8 speed)
{
	Motor_LF_forward(speed);
	Motor_LB_forward(speed);
			
	Motor_RF_backward(speed);
	Motor_RB_backward(speed);
}
//---------------------------------

