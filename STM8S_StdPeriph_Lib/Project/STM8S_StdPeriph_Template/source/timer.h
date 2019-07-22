/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef		_TIME_H_
#define		_TIME_H_


#include	"main.h"
#include	"uart.h"
#include	"function.h"
#include	"stm8s_tim2.h"



#define Freq_38K	415
#define CCR1_Val  ((uint16_t)(Freq_38K-101))
#define CCR2_Val  ((uint16_t)153)
#define CCR3_Val  ((uint16_t)102)
#define CCR4_Val  ((uint16_t)2040)

#define Header_Int_Time     (u16)(3000) //头时间
#define Header_Torr_Time     (u16)(500) //头部的容错时间

#define BIT1_Int_Time     (u16)(2000)    //位1时间
#define BIT1_Torr_Time     (u16)(500)    //位1容错时间

#define BIT0_Int_Time     (u16)(1000)    //位0时间
#define BIT0_Torr_Time     (u16)(500)    //位0容错时间

#define Stop_Int_Time     (u16)(47448)   //超长数据，出错


#define Header_OSC_Time     (u16)(9000)
#define Header_IDLE_Time     (u16)(4500)

#define BIT1_OSC_Time     (u16)(562)
#define BIT1_IDLE_Time    (u16)(1688)

#define BIT0_OSC_Time     (u16)(562)
#define BIT0_IDLE_Time    (u16)(562)

#define STOP_OSC_Time     (u16)(562)
#define STOP_IDLE_Time    (u16)(60000)

#define Rev_DATA_Port	GPIOC
#define Rev_DATA_Pin	GPIO_PIN_6


typedef struct
{
		u8 custom_code;  //客户码
		u8 _custom_code; //客户码反码
		u8 data_code; 	 //数据码
		u8 _data_code;		//数据码反码
		u8 bits;			//接收位数
		u8 codes[32]; 		//接收的数据,总共32位
		u8 rev_ok:1;		 //接收成功一帧码
}_IR_REV_DEF_;			//红外接收控制


extern	 _IR_REV_DEF_ 	 ir;								 //红外接收控制



extern void Timer_Init(void);
extern void Timer1_Config(void);
extern void Timer2_Config(void);
extern void Timer3_Config(void);
extern void Timer4_Config(void);

extern void delay_us(u16 dus);
extern void delay_ms(u16 dms);

extern void Delay_Tms(u16 tms);
extern void Delay_Tus(u16 tus);

extern void IR_Rev_Handler(void);
extern void IR_Receive(void);









#endif
