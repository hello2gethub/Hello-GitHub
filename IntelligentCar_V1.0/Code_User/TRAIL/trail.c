#include "trail.h"
#include "MotorDrive.h"
#include "delay.h"

u8 S_Trail_Input = 0 ;		// ����Ѱ��ģ��ķ���ֵ


// ����Ѱ����ʼ��(��PB3��PB4��PB5��ʼ��Ϊ��������)
// Trail -- PB3
// Trai2 -- PB4
// Trai3 -- PB5
//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// ʹ��GPIOB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			// GPIOBʱ��ʹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			// ����ʱ��ʹ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);			// ��PB3��PB4�ͷ�Ϊͨ��GPIO��
	
	// Ѱ����Trail--PB3��PB4��PB5�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	// Trail--PB3��PB4��PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// ��������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				// ����ģʽ����Ҫ��˿��ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// ��ʼ��PB3��PB4��PB5
	
}
//----------------------------------------------------------------------------------------------


// ����Ѱ������
// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB5��PB4��PB3]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//----------------------------------------------------
void Trail_black_line(void)
{
	S_Trail_Input = 0 ;
	
	S_Trail_Input = (((u8)GPIOB->IDR) & 0x38)>>3;
}
//----------------------------------------------------

void XJ(void)
{
		u16 C_Not_Find_Black = 0 ;			// δ���ֺ��߼�ʱ

		u8  F_Not_Find_Black_STOP = 0 ;		// ��ʱ��δ���ֺ��߱�־λ
		Trail_black_line();		// ���߼�⺯��
		
		// δ���ֺ���
		//-------------------------------------------------------	
		if( S_Trail_Input == Not_Find_Black_Line )	
		{
			if( F_Not_Find_Black_STOP == 1 )	// �ж��Ƿ�ʱ��δ���ֺ���	
				Car_Stop(CAR_FLAMEOUT);			// ͣ��
			
			else										
				Car_forward(60);				// ǰ��
		}
		//-------------------------------------------------------
		
		
		// ���ֺ���
		//---------------------------------------------------------------------------------------------------
		else 
		{
			C_Not_Find_Black = 0;			// �����δ���ֺ��߼�ʱ��,��ʱ�ڶ�ʱ���жϺ�����
			
			F_Not_Find_Black_STOP = 0 ;		// �������ʱ��δ���ֺ��߱�־λ��	
			
			
			// ���඼û���ֺ���
			//----------------------------------------------
			if(S_Trail_Input != Left_Find_Black_Line && S_Trail_Input != Left_Middle_Find_Black_Line && S_Trail_Input != Right_Find_Black_Line && S_Trail_Input != Right_Middle_Find_Black_Line )
			{
				Car_forward(60);	// ǰ��
			}
		
			// ��෢�ֺ���
			//----------------------------------------------
			else if( S_Trail_Input == Left_Find_Black_Line || S_Trail_Input == Left_Middle_Find_Black_Line )
			{
				Car_Turn_Left(60);	// ��ת
			}
			
			// �Ҳ෢�ֺ���
			//----------------------------------------------
			else if( S_Trail_Input == Right_Find_Black_Line || S_Trail_Input == Right_Middle_Find_Black_Line )
			{
				Car_Turn_Right(60);	// ��ת
			}
			
			// �������
			//----------------------------------------------
			else 
			{
				Car_Stop(CAR_FLAMEOUT);	// Ϩ��
			}
		}
}
