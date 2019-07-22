/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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

#define Header_Int_Time     (u16)(3000) //ͷʱ��
#define Header_Torr_Time     (u16)(500) //ͷ�����ݴ�ʱ��

#define BIT1_Int_Time     (u16)(2000)    //λ1ʱ��
#define BIT1_Torr_Time     (u16)(500)    //λ1�ݴ�ʱ��

#define BIT0_Int_Time     (u16)(1000)    //λ0ʱ��
#define BIT0_Torr_Time     (u16)(500)    //λ0�ݴ�ʱ��

#define Stop_Int_Time     (u16)(47448)   //�������ݣ�����


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
		u8 custom_code;  //�ͻ���
		u8 _custom_code; //�ͻ��뷴��
		u8 data_code; 	 //������
		u8 _data_code;		//�����뷴��
		u8 bits;			//����λ��
		u8 codes[32]; 		//���յ�����,�ܹ�32λ
		u8 rev_ok:1;		 //���ճɹ�һ֡��
}_IR_REV_DEF_;			//������տ���


extern	 _IR_REV_DEF_ 	 ir;								 //������տ���



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
