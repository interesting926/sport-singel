/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm8s.h"



#define Software_Ver "V0.01"


#define	LoByte(w)	((u8)(w))
#define	HiByte(w)	((u8)(((u16)(w) >> 8) & 0xFF))

#define	Abs(a,b)		(((a) > (b)) ? (a-b) : (b-a))
#define	Max(a,b)		(((a) > (b)) ? (a) : (b))
#define	Min(a,b)		(((a) < (b)) ? (a) : (b))


extern u8 INT_FLG;

#define Disable()	disableInterrupts();
#define Enable()	if(INT_FLG==1) enableInterrupts()


extern char const Product_Info[];











#endif

