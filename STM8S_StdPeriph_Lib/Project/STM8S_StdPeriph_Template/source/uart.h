/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef		_UART_H_
#define		_UART_H_

#include	"main.h"
#include	"function.h"
#include	"stm8s_uart2.h"
#include	"stdio.h"


#define c_dbg_print     printf

//串口使能
//#define USING_UART1
#define USING_UART2
//#define USING_UART3
//#define USING_UART4
#define USING_DUART	//模拟串口


//消息打印用哪个串口
//#define UART1_DBG_PRINT
#define UART2_DBG_PRINT
//#define UART3_DBG_PRINT
//#define UART4_DBG_PRINT
//#define DUART_DBG_PRINT



//串口波特率设定

#define UART2_BAUDRATE	9600




//设置串口相邻两个字节最大时间

#define UART2_BYTE_MAX_TIME	2


//设置接收缓冲最大长度
#define UART2_MAX_RECV_LEN	32
#define UART2_MAX_SEND_LEN	32

#define	BLE_RST_Port		GPIOC
#define	BLE_RST_Pin			GPIO_PIN_7
#define BLE_RST_Low()		GPIO_WriteLow(BLE_RST_Port,BLE_RST_Pin)
#define BLE_RST_High()		GPIO_WriteHigh(BLE_RST_Port,BLE_RST_Pin)

#define	BLE_WAKUP_Port		GPIOC
#define	BLE_WAKUP_Pin			GPIO_PIN_6
#define BLE_WAKUP_Low()		GPIO_WriteLow(BLE_WAKUP_Port,BLE_WAKUP_Pin)
#define BLE_WAKUP_High()		GPIO_WriteHigh(BLE_WAKUP_Port,BLE_WAKUP_Pin)

#define	BLE_CONNECT_Port		GPIOC
#define	BLE_CONNECT_Pin			GPIO_PIN_5
#define BLE_CONNECT_Low()		GPIO_WriteLow(BLE_CONNECT_Port,BLE_CONNECT_Pin)
#define BLE_CONNECT_High()		GPIO_WriteHigh(BLE_CONNECT_Port,BLE_CONNECT_Pin)


typedef struct
{
	u8 rev_flg:1;	//接收数据的标志
	u8 length;		//接收到数据的长度
	u8 time_cnt;	//计时接收
	u8 rbuf[UART2_MAX_RECV_LEN];
	u8 sbuf[UART2_MAX_SEND_LEN];
}_UART2_CTRL_DEF;



extern _UART2_CTRL_DEF uart2;




extern void Uart_Init(void);
extern void Uart_Time_Handler(void);
extern void Print_System_Info(void);

#ifdef	USING_UART2
extern void Uart2_Init(void);
extern void Uart2_SendByte(u8 c);
extern void Uart2_Send_N_bytes(u8 *buf,u8 len);
extern void Uart2_Send_Hex(u8 Byte_HEX);
extern void Uart2_Send_Dec(u8 Byte_Dec);
extern void Uart2_Send_IntDec(u16 Int_dec);
extern void Uart2_dbg_print(char *str);
extern void Uart2_Time_Handler(void);
extern void Uart2_Receive_Data(u8 rdata);

#endif










#endif


