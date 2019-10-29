/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include	"main.h"
#include "stm8s.h"
#include	"timer.h"
#include	"string.h"
#include	"lcd.h"

u8 INT_FLG;





char const Product_Info[]={"\
************************************************************\r\n\
Company: Forlinux Technoly Electronics Co.,LTD.\r\n\
Project: GFamily Software\r\n\
Author: Fuqiaobin\r\n\
Date:	2017.12.30\r\n\
************************************************************\r\n"};

/*******************************************************************************
* Function Name  : SysClock_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void SysClock_Init(void)
{
	CLK_DeInit();
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);	/* Fmaster =16MHz */
	CLK_HSICmd(ENABLE);
}
/*******************************************************************************
* Function Name  : Hard_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void Hard_Init(void)
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);
	GPIO_DeInit(GPIOF);
	GPIO_DeInit(GPIOG);
	MP3_Port_Init();
	GPIO_Init(Beep_Port, Beep_Pin, GPIO_MODE_OUT_OD_HIZ_FAST);
	GPIO_Init(Led1_Port,Led1_Pin,GPIO_MODE_OUT_PP_LOW_FAST);	//开漏输出
	GPIO_Init(Led2_Port,Led2_Pin,GPIO_MODE_OUT_PP_LOW_FAST);	//开漏输出
	Set_Led1_On();Set_Led2_On();
	Beep_Ring(150);
}
/*******************************************************************************
* Function Name  : Exti_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void Exti_Init(void)
{
	GPIO_Init(RPM1_Port,RPM1_Pin,GPIO_MODE_IN_PU_IT);	//开漏输出
	GPIO_Init(RPM2_Port,RPM2_Pin,GPIO_MODE_IN_PU_NO_IT);	//开漏输出
	
	EXTI_DeInit();
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);	//下降沿触发
	//EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_RISE_ONLY);	//上升沿触发
	ITC_SetSoftwarePriority(ITC_IRQ_PORTB,ITC_PRIORITYLEVEL_3);	//优先级
	//ITC_SetSoftwarePriority(ITC_IRQ_PORTC,ITC_PRIORITYLEVEL_2);	//优先级
}

void Soft_Init(void)
{
	display.b_enable=1;
	rpm.timeout=Timeout_Max;
	rpm.calorie=0;
	rpm.filter=0;
	rpm.int_flg=0;
	rpm.timeout=Timeout_Max;
	rpm.start_flg=0;
	rpm.upload_flg=0;
	rpm.cnt=0;
}


/*******************************************************************************
* Function Name  : SysClock_Init
* Description    : 初始化
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/

void main(void)
{
	disableInterrupts();INT_FLG=0;
	SysClock_Init();
	delay_ms(300);
	Hard_Init();
	Uart_Init();
	Timer_Init();
	Exti_Init();
	LCD_Init();
	MP3_Init();
	Soft_Init();
	//Print_System_Info();
	enableInterrupts();INT_FLG=1;
	while (1)
	{
		Function();
	}
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
		delay_ms(1000);
		printf("Wrong parameters value: file %s on line %d\r\n", file, (u16)line);
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
