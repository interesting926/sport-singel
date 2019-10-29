/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/
#include	"stm8s.h"
#include	"main.h"
#include	"uart.h"
#include	"debug.h"
#include	"stm8s_uart1.h"
#include	"stm8s_uart2.h"
#include	"stm8s_uart3.h"
#include	"stm8s_uart4.h"

u8 const HEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


/*********************************************************
* Function Name  : Uart2_Init
* Description    : ����2��ʼ���������ڴ�ӡ��Ϣ
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
#ifdef	USING_UART2
_UART2_CTRL_DEF uart2;

void Uart2_Init(void)
{
	uart2.length=0;
	uart2.rev_flg=0;
	uart2.time_cnt=0;

	GPIO_Init(BLE_RST_Port,BLE_RST_Pin,GPIO_MODE_OUT_OD_HIZ_FAST);
	GPIO_Init(BLE_WAKUP_Port,BLE_WAKUP_Pin,GPIO_MODE_OUT_OD_LOW_FAST);
	GPIO_Init(BLE_CONNECT_Port,BLE_CONNECT_Pin,GPIO_MODE_IN_FL_NO_IT);

	GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_OD_HIZ_FAST);	//TXD
	GPIO_Init(GPIOD,GPIO_PIN_6,GPIO_MODE_IN_FL_NO_IT);	//RXD

	UART2_DeInit();
	UART2_Init((u32)UART2_BAUDRATE, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO,UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
	UART2_ITConfig(UART2_IT_RXNE_OR,ENABLE);
	UART2_Cmd(ENABLE);
}
void Uart2_SendByte(u8 c)
{
	while ((UART2->SR&UART2_SR_TXE)==RESET);
	UART2_SendData8((u8)c);
}

void Uart2_Send_N_bytes(u8 *buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart2_SendByte(buf[i]);
	}
}

void Uart2_Send_Hex(u8 Byte_HEX)
{
	Uart2_SendByte(HEX[Byte_HEX/16]);
	Uart2_SendByte(HEX[Byte_HEX%16]);
}
void Uart2_Send_Dec(u8 Byte_Dec)
{
	Uart2_SendByte(HEX[(Byte_Dec/100)%10]);
	Uart2_SendByte(HEX[(Byte_Dec/10)%10]);
	Uart2_SendByte(HEX[(Byte_Dec/1)%10]);
}
void Uart2_Send_IntDec(u16 Int_dec)
{
	Uart2_SendByte(HEX[(Int_dec/10000)%10]);
	Uart2_SendByte(HEX[(Int_dec/1000)%10]);
	Uart2_SendByte(HEX[(Int_dec/100)%10]);
	Uart2_SendByte(HEX[(Int_dec/10)%10]);
	Uart2_SendByte(HEX[(Int_dec/1)%10]);
}

void Uart2_dbg_print(char *str)
{
	while(*str)
	{
		Uart2_SendByte(*str++);
	}
}

void Uart2_Time_Handler(void)		//�жϽ��ճ�ʱ
{
	if(uart2.time_cnt)
	{
			uart2.time_cnt--;
			if(uart2.time_cnt==0)
			{
				uart2.rev_flg=1;	//��������ʱ�ޣ����Ϊ���ճɹ�
			}
	}
}

void Uart2_Receive_Data(u8 rdata)
{
	if(uart2.rev_flg==0)
	{
		if(uart2.length<UART2_MAX_RECV_LEN)
		{
			uart2.time_cnt=UART2_BYTE_MAX_TIME;	//���㳬ʱ
			uart2.rbuf[uart2.length++]=rdata;	//��������
		}
		else
		{
			uart2.rev_flg=1;	//�������ݽ��յĳ��ȣ�ǿ�Ʊ��
		}
	}
}
#endif

/****************************************************************
* Function Name  : None
* Description    :None
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/

#ifdef	UART2_DBG_PRINT
int putchar(int c)	//ʹ�ô���2��Ϊ��ӡ��
{
	while ((UART2->SR&UART2_SR_TXE)==RESET);
	UART2_SendData8((u8)c);
	return (c);
}
#endif
#ifdef DUART_DBG_PRINT
int putchar(int c)	//ʹ�����⴮����Ϊ��ӡ��
{
	Uart_Send_Byte((u8)c);
	return (c);
}
#endif



/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Uart_Init(void)
{
#ifdef USING_UART2
	Uart2_Init();
#endif
#ifdef USING_DUART
	Uart_Debug_Init();		//������ڲ�����ʱ������ʹ�ô�ģ�⴮�ڽ�����Ϣ��ӡ
#endif
}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Uart_Time_Handler(void)
{
#ifdef	USING_UART2
	Uart2_Time_Handler();
#endif
}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Print_System_Info(void)
{

}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
