/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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

