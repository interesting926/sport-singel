/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/

#ifndef		_DEBUG_H_
#define		_DEBUG_H_

#include "stm8s.h"


#define Uart_Txd_Port   GPIOC
#define Uart_Txd_Pin	GPIO_PIN_4
#define Set_TXD_High()   (Uart_Txd_Port->ODR |= (uint8_t)Uart_Txd_Pin);
#define Set_TXD_Low()    (Uart_Txd_Port->ODR &= (uint8_t)(~Uart_Txd_Pin))

extern u8 const DBHEX[];

extern void Uart_Debug_Test(void);
extern void Uart_Debug_Init(void);
extern void Uart_Send_Byte(u8 send_dat);
extern void Uart_Send_Hex(u8 Byte_HEX);
extern void Uart_Send_IntHex(u16 Byte_HEX);
extern void Uart_Send_Dec(u8 Byte_Dec);
extern void Uart_Send_IntDec(u16 Int_dec);
extern void Uart_Send_N_bytes(u8 * buff,u8 len);
extern void Uart_Send_N_Hexs(u8 * buff,u8 len);
extern void Uart_dbg_print(char *str);




#endif
