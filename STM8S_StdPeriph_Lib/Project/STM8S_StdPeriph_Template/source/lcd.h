/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/
#ifndef		_LCD_H_
#define		_LCD_H_

#include "stm8s.h"
#include "stm8s_gpio.h"
#include	"display.h"
#include	"function.h"

/**********************HT1632����궨��*************************/

#define SYSDIS 		0x00 //0b1000 0000 0000 ����ϵͳ������LCDƫѹ������
#define SYSEN 		0x02 //0b1000 0000 0010 ��ϵͳ����
#define LCDOFF 		0x04 //0b1000 0000 0100 ��LCDƫѹ
#define LCDON 		0x06 //0b1000 0000 0110 ��LCDƫѹ
#define BLINK_OFF	0x10
#define BLINK_ON	0x12
#define SLAVE_MODE	0x20
#define RC_MASTER_MODE	0x30
#define EXT_MASTER_MODE	0x38

#define NMOS_8COMs	0x40
#define NMOS_16COMs	0x48
#define PMOS_8COMs	0x50
#define PMOS_16COMs	0x58

/**********************����ܶ���궨��*************************/

#define	LCD_CS1_Port		GPIOD
#define	LCD_CS1_Pin			GPIO_PIN_0
#define LCD_CS1_Low()		GPIO_WriteLow(LCD_CS1_Port,LCD_CS1_Pin)
#define LCD_CS1_High()	GPIO_WriteHigh(LCD_CS1_Port,LCD_CS1_Pin)

#define	LCD_WR_Port			GPIOD
#define	LCD_WR_Pin			GPIO_PIN_3
#define LCD_WR_Low()		GPIO_WriteLow(LCD_WR_Port,LCD_WR_Pin)
#define LCD_WR_High()		GPIO_WriteHigh(LCD_WR_Port,LCD_WR_Pin)

#define	LCD_DATA_Port		GPIOD
#define	LCD_DATA_Pin		GPIO_PIN_7
#define LCD_DATA_Low()	GPIO_WriteLow(LCD_DATA_Port,LCD_DATA_Pin)
#define LCD_DATA_High()	GPIO_WriteHigh(LCD_DATA_Port,LCD_DATA_Pin)

extern u8 const Ht1632Tab_CLR[];
extern u8 const Ht1632Tab_Set[];


typedef	enum
{
	Select_Chip_1=0,
	Select_Chip_2,
}_LCD_Chip_Select_;


void LCD_Delay(u8 us);
void LCD_Delay_MS(u16 iMs);
extern void LCD_Port_Init(void);
extern void LCD_Select_A_Chip(void);
extern void LCD_DeSelect_Chip(void);
extern void LCD_Write_Data(u8 Data,u8 cnt);
extern void LCD_WrCmd_A(u8 Cmd);
extern void LCD_Set_PWMDuty_A(u8 duty);
extern void LCD_SendByte_A(u8 Addr,u8 Data);
extern void LCD_Send_4Bit_A(u8 Addr,u8 Data);
extern void LCD_WrAllData_A(u8 Addr,u8 *p,u8 cnt);
extern void LCD_Init(void);


#endif