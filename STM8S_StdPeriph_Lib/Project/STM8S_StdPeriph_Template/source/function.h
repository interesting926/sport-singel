/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_



#include "stm8s.h"

#define	MP3_DATA_PORT	GPIOC               //
#define	MP3_DATA_PIN	GPIO_PIN_3
#define MP3_DATA_LOW() GPIO_WriteLow(MP3_DATA_PORT,MP3_DATA_PIN)
#define MP3_DATA_HIG() GPIO_WriteHigh(MP3_DATA_PORT,MP3_DATA_PIN)

#define	MP3_BUSY_PORT	GPIOC               //
#define	MP3_BUSY_PIN	GPIO_PIN_2
#define MP3_BUSY() 		GPIO_ReadInputPin(MP3_BUSY_PORT,MP3_BUSY_PIN)

#define	Led1_Port	GPIOB               //LED
#define	Led1_Pin	GPIO_PIN_3

#define	Set_Led1_Off()	GPIO_WriteLow(Led1_Port,Led1_Pin)
#define	Set_Led1_On()		GPIO_WriteHigh(Led1_Port,Led1_Pin)
#define	Set_Led1_Tog()		GPIO_WriteReverse(Led1_Port,Led1_Pin)

#define	Led2_Port	GPIOB               //LED
#define	Led2_Pin	GPIO_PIN_2

#define	Set_Led2_Off()	GPIO_WriteLow(Led2_Port,Led2_Pin)
#define	Set_Led2_On()		GPIO_WriteHigh(Led2_Port,Led2_Pin)	
#define	Set_Led2_Tog()		GPIO_WriteReverse(Led2_Port,Led2_Pin)

#define	Beep_Port	GPIOD
#define	Beep_Pin	GPIO_PIN_4

#define	Set_Beep_OFF()		GPIO_WriteHigh(Beep_Port,Beep_Pin)
#define	Set_Beep_ON()		GPIO_WriteLow(Beep_Port,Beep_Pin)

#define	RPM1_Port	GPIOB               //LED
#define	RPM1_Pin	GPIO_PIN_0
#define	RPM2_Port	GPIOB               //LED
#define	RPM2_Pin	GPIO_PIN_1

#define Timeout_Max         6000     //60s,超时进入假睡眠
#define TimeCnt_Max				500				//5s,无动作报数
#define Device_ID	0xff
extern void LED_Time_Handler(void);

#define mp3_replay 3
#define mp3_playing 1	//单曲播放中
#define mp3_pause 2 	//单曲暂停
#define mp3_stop 0	//单曲完毕

typedef struct 
{	
	u8 dely;
	u8 volumn;
	u8 status,busy;
	u8 queue[50];
	u8 QueueIndex,QueueSize,queue_play,ChangeNow;
}MP3_TYPE_DEF;



typedef struct
{
	u8   b_enable:1;     //是否允许显示
	u16 timer;		// 以固定的频率进行显示
	u8 blink:1;	//是否需要闪烁
	u8 blink_val:1;    //当前闪烁的状态
	u8 blink_cnt;	//闪烁的次数
	u8 mode;			//
}_DISPLAY_CTRL_DEF_;


typedef struct
{
	u8 int_flg:1;	//1ms
	u16 micros;	//50ms
	u8 second_flg:1;	// 1s 
	u8 second;	//s
	u8 minute;	//minute
	u16  total_time;		//用于测试开始计时,以秒为单位
}_TIME_CTRL_DEF_;

typedef struct
{
	u16 calorie;
	u16 total_cnts;		//总次数
	u8 start_flg:1;		//开始计时
	u8 int_flg:1;    //中断标志
	u8 upload_flg:1;
	u16 time_cnt;	//计时
	u16 timeout;	//超时待机
	u8 state:1;
	u8 filter;
	u8 delay_cnt;
	u8 cnt;
}_RPM_STRUCT_CTRL_;		//RPM测试控制参数


extern _DISPLAY_CTRL_DEF_ display;		//显示控制
extern _RPM_STRUCT_CTRL_ rpm;
extern MP3_TYPE_DEF mp3;

extern void Beep_Ring(u8 dely);
extern void Display_Time_Handler(void);
extern void System_Timeticket(void);
extern void RPM_Timeticket(void);
extern void Function(void);
extern void Flash_Display_RAM(void);
extern void MP3_Port_Init(void);
extern void MP3_Init(void);


extern void MUSIC_PLAY_CONTENT(u8 num);
extern void MUSIC_SET_VOLUMN(u8 vol);




#endif