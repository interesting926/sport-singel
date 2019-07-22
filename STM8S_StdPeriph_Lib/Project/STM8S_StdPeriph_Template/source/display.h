/*-----------------------------------------------
  项目：鱼缸控制器程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2014.7.1
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef		_DISPLAY_H_
#define		_DISPLAY_H_

#include "stm8s.h"
#include    "stdio.h"
#include	"lcd.h"
#include	"function.h"
#include	"uart.h"

typedef union
{
	struct
	{
		u8 bit0:1;
		u8 bit1:1;
		u8 bit2:1;
		u8 bit3:1;
		u8 bit4:1;
		u8 bit5:1;
		u8 bit6:1;
		u8 bit7:1;
	}flg;
	u8 value;
}_LCD_Map_Def_;



extern void LCD_Update_CGRAM(void);
extern void LCD_Clear_All(void);
extern void LCD_Set_BitVal(u16 addr , u8 bitval);
extern void Set_Calorie_Display(u16 cal);
extern void Set_TIME_Display(u16 time,u8 second);
extern void Set_Count_Display(u16 cnt);



#endif
