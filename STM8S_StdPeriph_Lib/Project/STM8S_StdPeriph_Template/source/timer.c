/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/

#include	"timer.h"
#include	"string.h"


_IR_REV_DEF_    ir;


/*******************************************************************************
* Function Name  : delay
* Description    :
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void delay_us(u16 dus)
{
	u16 nops;
	nops=(dus*5)/2;
  while(nops--);
}
/*******************************************************************************
* Function Name  : delay
* Description    :
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void delay_ms(u16 dms)
{
	  while(dms--)
	  {
	    delay_us(1333);
	  }
}
/*********************************************************
* Function Name  : Timer_Init
* Description    : ��ʱ����ʼ��
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Timer_Init(void)
{
	Timer1_Config();	//����������׼��ʱ
	Timer2_Config();	//10ms��ʱ��
	//Timer3_Config();	//������׽RPM��ʱ����
	//Timer4_Config();
}
/*********************************************************
* Function Name  : Timer1_Config
* Description    : ��ʱ����ʼ��
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
/*
void Timer1_Config(void)	//pwm���
{
	//TIM1����38K�����ز� 
	TIM1_DeInit();
	//TIM1_Period = 4095
	//TIM1_Prescaler = 0
	//TIM1_CounterMode = TIM1_COUNTERMODE_UP
	//TIM1_RepetitionCounter = 0
	
	TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, Freq_38K, 0); 	//38KHZ�ĺ����ز�
	// Channel 1, 2,3 and 4 Configuration in PWM mode //
	
	TIM1_OCMode = TIM1_OCMODE_PWM2
	TIM1_OutputState = TIM1_OUTPUTSTATE_ENABLE
	TIM1_OutputNState = TIM1_OUTPUTNSTATE_ENABLE
	TIM1_Pulse = CCR1_Val
	TIM1_OCPolarity = TIM1_OCPOLARITY_LOW
	TIM1_OCNPolarity = TIM1_OCNPOLARITY_HIGH
	TIM1_OCIdleState = TIM1_OCIDLESTATE_SET
	TIM1_OCNIdleState = TIM1_OCIDLESTATE_RESET
	
	TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
	CCR1_Val, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
	TIM1_OCNIDLESTATE_RESET); 
	
	//TIM1_Pulse = CCR2_Val
	TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, CCR2_Val,
	TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
	TIM1_OCNIDLESTATE_RESET);

	//TIM1_Pulse = CCR3_Val//
	TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
	CCR3_Val, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
	TIM1_OCNIDLESTATE_RESET);

	//TIM1_Pulse = CCR4_Val//
	TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, CCR4_Val, TIM1_OCPOLARITY_LOW,
	TIM1_OCIDLESTATE_SET);
		
	// TIM1 counter enable //
	TIM1_Cmd(ENABLE);
	// TIM1 Main Output Enable //
	TIM1_CtrlPWMOutputs(DISABLE);

}
*/
void Timer1_Config(void)	//��׽��ʱ���ⲿ�жϲ�׽���ⶨʱ
{
	TIM1_DeInit();
	TIM1_PrescalerConfig(16,TIM1_PSCRELOADMODE_IMMEDIATE);	// 1us
	TIM1_SetCounter(0);
	TIM1_SetAutoreload(0xffff);
	TIM1_ClearFlag(TIM1_FLAG_UPDATE);
	TIM1_Cmd(ENABLE);
}

void Delay_Tus(u16 tus)//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM1_PrescalerConfig(16,TIM1_PSCRELOADMODE_UPDATE);	//ÿһus
	TIM1_SetCounter(65535-tus);
	TIM1_Cmd(ENABLE);
	do
	{
		state=TIM1_GetFlagStatus(TIM1_FLAG_UPDATE);
	}while(state==RESET);
	TIM1_ClearFlag(TIM1_FLAG_UPDATE);
}

void Delay_Tms(u16 tms)//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM1_PrescalerConfig(16384,TIM1_PSCRELOADMODE_UPDATE);	//ÿһms
	TIM1_SetCounter(65535-tms);
	TIM1_Cmd(ENABLE);
	do
	{
		state=TIM1_GetFlagStatus(TIM1_FLAG_UPDATE);
	}while(state==RESET);
	TIM1_ClearFlag(TIM1_FLAG_UPDATE);
}

/*********************************************************
* Function Name  : Timer2_Config
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
//TIM2��Ϊʱ��
void Timer2_Config(void)
{
	TIM2_DeInit();
	TIM2_TimeBaseInit(TIM2_PRESCALER_16,10000);//10ms
	TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);
	TIM2_SetAutoreload(10000);
	TIM2_Cmd(ENABLE);	//������ʱ��2
}
/*	//pwm
uint16_t CCR1_Val = 500;
uint16_t CCR2_Val = 250;
uint16_t CCR3_Val = 125;

static void TIM2_Config(void)
{
  // Time base configuration //
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 999);

  // PWM1 Mode configuration: Channel1 // 
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,CCR1_Val, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);

  // PWM1 Mode configuration: Channel2 // 
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,CCR2_Val, TIM2_OCPOLARITY_HIGH);
  TIM2_OC2PreloadConfig(ENABLE);

  // PWM1 Mode configuration: Channel3 //         
  TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,CCR3_Val, TIM2_OCPOLARITY_HIGH);
  TIM2_OC3PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  // TIM2 enable counter //
  TIM2_Cmd(ENABLE);
}

*/
/*
void Timer2_Config(void)	//��׽��ʱ���ⲿ�жϲ�׽���ⶨʱ
{
	TIM2_DeInit();
	TIM2_PrescalerConfig(TIM2_PRESCALER_16,TIM2_PSCRELOADMODE_IMMEDIATE);	// 1us
	TIM2_SetCounter(0);
	TIM2_SetAutoreload(0xffff);
	TIM2_ClearFlag(TIM2_FLAG_UPDATE);
	TIM2_Cmd(ENABLE);
}
*/
/*
void Delay_Tus(u16 tus)//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM2_PrescalerConfig(16,TIM2_PSCRELOADMODE_UPDATE);	//ÿһus
	TIM2_SetCounter(65535-tus);
	TIM2_Cmd(ENABLE);
	do
	{
		state=TIM2_GetFlagStatus(TIM2_FLAG_UPDATE);
	}while(state==RESET);
	TIM2_ClearFlag(TIM2_FLAG_UPDATE);
}

void Delay_Tms(u16 tms)		//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM2_PrescalerConfig(16384,TIM2_PSCRELOADMODE_UPDATE);	//ÿһms
	TIM2_SetCounter(65535-tms);
	TIM2_Cmd(ENABLE);
	do
	{
		state=TIM2_GetFlagStatus(TIM2_FLAG_UPDATE);
	}while(state==RESET);
	TIM2_ClearFlag(TIM2_FLAG_UPDATE);
}
*/


/*********************************************************
* Function Name  : Timer3_Config
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
/*
void Timer3_Config(void)	//��׼��ʱ
{
	TIM3_DeInit();
	TIM3_ITConfig(TIM3_IT_UPDATE,DISABLE);
	TIM3_Cmd(DISABLE);
}
*/
/*
void Timer3_Config(void)	//��׽��ʱ���ⲿ�жϲ�׽���ⶨʱ
{
	TIM3_DeInit();
	TIM3_PrescalerConfig(TIM3_PRESCALER_16384,TIM3_PSCRELOADMODE_IMMEDIATE);	// 1ms
	TIM3_SetCounter(0);
	TIM3_SetAutoreload(0xffff);
	TIM3_ClearFlag(TIM3_FLAG_UPDATE);
	TIM3_Cmd(ENABLE);
}
*/
/*
void Delay_Tus(u16 tus)	//ʹ�ö�ʱ��3��Ϊ��ʱ//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM3_PrescalerConfig(TIM3_PRESCALER_16,TIM3_PSCRELOADMODE_UPDATE);	//ÿһus
	TIM3_SetCounter(65535-tus);
	TIM3_Cmd(ENABLE);
	do
	{
		state=TIM3_GetFlagStatus(TIM3_FLAG_UPDATE);
	}while(state==RESET);
	TIM3_ClearFlag(TIM3_FLAG_UPDATE);
}

void Delay_Tms(u16 tms)//ʹ�ö�ʱ��3��Ϊ��ʱ//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus state;
	TIM3_PrescalerConfig(TIM3_PRESCALER_16384,TIM3_PSCRELOADMODE_UPDATE);	//ÿһms
	TIM3_SetCounter(65535-tms);
	TIM3_Cmd(ENABLE);
	do
	{
		state=TIM3_GetFlagStatus(TIM3_FLAG_UPDATE);
	}while(state==RESET);
	TIM3_ClearFlag(TIM3_FLAG_UPDATE);
}

*/

/*********************************************************
* Function Name  : Timer4_Config
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
/*
void Timer4_Config(void)	//��׼��ʱ
{
	TIM4_DeInit();
	TIM4_ITConfig(TIM4_IT_UPDATE,DISABLE);
	TIM4_Cmd(DISABLE);
}

void Delay_Tus(u16 tus)	//��Ҫ����2047us//�ٶ�ϵͳʱ��Ϊ16M
{
	FlagStatus bitstatus = RESET;
	if(tus>2047) tus=2047;
	TIM4_TimeBaseInit(TIM4_PRESCALER_128,(u8)(tus/8));
	TIM4_SetCounter(0);
	TIM4_Cmd(ENABLE);
	do
	{
		bitstatus=TIM4_GetFlagStatus(TIM4_FLAG_UPDATE);
	}while(bitstatus==RESET);	//�ȴ���ʱ��
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
}
*/
/*********************************************************
* Function Name  : IR_Rev_Handler
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
/*
void IR_Rev_Handler(void)
{
	//--------����ң���жϲ������------------
	static u16 time_count=0;
	if(GPIO_ReadInputPin(Rev_DATA_Port,Rev_DATA_Pin)==RESET)	//�ж��Ƿ���ж�
	{
		if(TIM3_GetFlagStatus(TIM3_FLAG_UPDATE)==SET)
		{
			time_count=0xFFFF;		//�жϸ�ֵ
		}
		else
		{
			time_count=TIM3_GetCounter(); //��ȡ����
		}
		TIM3_SetCounter(0); //��0
		TIM3_ClearFlag(TIM3_FLAG_UPDATE); //���ж�
		if(ir.rev_ok==0)
		{
			if(Abs(time_count,Header_Int_Time)<Header_Torr_Time)	//ͷ��
			{
				ir.bits=0;
				memset(ir.codes,0,8);
			}
			else if(Abs(time_count,BIT1_Int_Time)<BIT1_Torr_Time) 	 //λ1
			{
				ir.codes[ir.bits]=1;//��1
				ir.bits++;
			}
			else if(Abs(time_count,BIT0_Int_Time)<BIT0_Torr_Time) 	 //λ0
			{
				ir.codes[ir.bits]=0;	//����
				ir.bits++;
			}
			else		//ʱ�����
			{
				ir.bits=0;
				memset(ir.codes,0,8);
			}
			if(ir.bits>=4)
			{
				ir.rev_ok=1;	//���ճɹ�
				ir.bits=0;
			}
		}
	}
}
*/

/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
