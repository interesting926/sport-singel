/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/

#include "function.h"
#include	"timer.h"
#include	"display.h"



_DISPLAY_CTRL_DEF_ display;		//��ʾ����
_TIME_CTRL_DEF_ timer;
_RPM_STRUCT_CTRL_ rpm;
MP3_TYPE_DEF mp3;



void Beep_Ring(u8 dely)
{
	Set_Beep_ON();
	delay_ms(dely);
	Set_Beep_OFF();
}

void MP3_Port_Init(void)
{
	GPIO_Init(MP3_DATA_PORT,MP3_DATA_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(MP3_BUSY_PORT,MP3_BUSY_PIN,GPIO_MODE_IN_PU_NO_IT);
	MP3_DATA_HIG();
}

void MP3_Init(void)
{
	mp3.QueueSize=0;
	mp3.QueueIndex=0;
	mp3.status = mp3_stop;
	mp3.queue_play=0;
	MUSIC_PLAY_CONTENT(17);
}

void MUSIC_Write_Cmd(u16 cmd)
{
	u8 i;
	static u8 LowByte,HighByte;
	HighByte=cmd>>8;
	LowByte=cmd&0xff;
	
	Disable();
	MP3_DATA_LOW();
	Delay_Tus(5000);
	for(i=0;i<8;i++)
	{
		if(HighByte&0x01)
		{
			MP3_DATA_HIG();
			Delay_Tus(600);
			MP3_DATA_LOW();
			Delay_Tus(200);
		}
		else
		{
			MP3_DATA_HIG();
			Delay_Tus(200);
			MP3_DATA_LOW();
			Delay_Tus(600);
		}
		HighByte>>=1;
	}
	MP3_DATA_HIG();
	Delay_Tus(2000);
	MP3_DATA_LOW();
	Delay_Tus(5000);
	for(i=0;i<8;i++)
	{
		if(LowByte&0x01)
		{
			MP3_DATA_HIG();
			Delay_Tus(600);
			MP3_DATA_LOW();
			Delay_Tus(200);
		}
		else
		{
			MP3_DATA_HIG();
			Delay_Tus(200);
			MP3_DATA_LOW();
			Delay_Tus(600);
		}
		LowByte>>=1;
	}
	MP3_DATA_HIG();
	Enable();
}



void MUSIC_START_PLAY(void)
{
		mp3.QueueIndex=0;
		mp3.ChangeNow=1;	//��������
		mp3.queue_play=1;
		c_dbg_print("[MP3] Start Play!\r\n");
}

void MUSIC_PLAY_CONTENT(u8 num)
{
		mp3.queue[0]=num;
		mp3.QueueSize=1;
		mp3.QueueIndex=0;
		mp3.ChangeNow=1;	//��������
		mp3.queue_play=1; 			
		c_dbg_print("[MP3] Play content:%d!\r\n",num);
}
void MUSIC_STOP_PLAY(void)
{
		mp3.status = mp3_stop;
		mp3.queue_play=0;
		c_dbg_print("[MP3] STOP\r\n");
}

void MUSIC_CLEAR_QUEUE(void)
{
		mp3.QueueSize=0;
		mp3.ChangeNow=0;
		mp3.QueueIndex=0;
		mp3.status = mp3_stop;
		mp3.queue_play=0;
		c_dbg_print("[MP3] CLEAR\r\n");
}

void MUSIC_SET_VOLUMN(u8 vol)
{
	//c_dbg_print("[MP3] Volumn:%d!\r\n",vol);
	MUSIC_Write_Cmd(0xFFE0+vol);//��������
	delay_ms(200);
}

void MUSIC_ADD_CONTENT(u8 num)
{
	mp3.queue[mp3.QueueSize++]=num;
}

void MUSIC_ADD_NUMBER_CONTNET(u16 num)
{
	switch(num)
	{
		case 0:	MUSIC_ADD_CONTENT(0);break;
		case 1:	MUSIC_ADD_CONTENT(1);break;
		case 2:	MUSIC_ADD_CONTENT(2);break;
		case 3:	MUSIC_ADD_CONTENT(3);break;
		case 4:	MUSIC_ADD_CONTENT(4);break;
		case 5:	MUSIC_ADD_CONTENT(5);break;
		case 6:	MUSIC_ADD_CONTENT(6);break;
		case 7:	MUSIC_ADD_CONTENT(7);break;
		case 8:	MUSIC_ADD_CONTENT(8);break;
		case 9:	MUSIC_ADD_CONTENT(9);break;
		case 10: MUSIC_ADD_CONTENT(10);break;
		case 100: MUSIC_ADD_CONTENT(11);break;
		case 1000: MUSIC_ADD_CONTENT(12);break;
	}

}


void MUSIC_ADD_INT_CONTENT(u16 num)
{
	u8 qian,bai,shi,ge;
	qian = (num/1000)%10;
	bai = (num/100)%10;
	shi = (num/10)%10;
	ge = (num/1)%10;
	if(num<10)
	{
		MUSIC_ADD_NUMBER_CONTNET(ge);
	}
	else if(num==10)
	{
		MUSIC_ADD_NUMBER_CONTNET(10);
	}
	else if(num<=19)
	{
		MUSIC_ADD_NUMBER_CONTNET(10);
		if(ge)	MUSIC_ADD_NUMBER_CONTNET(ge);
	}
	else if(num<=99) 
	{
		MUSIC_ADD_NUMBER_CONTNET(shi);
		MUSIC_ADD_NUMBER_CONTNET(10);
		if(ge)
		MUSIC_ADD_NUMBER_CONTNET(ge);
	}
	else if(num<=999)
	{
		MUSIC_ADD_NUMBER_CONTNET(bai);	//��λ
		MUSIC_ADD_NUMBER_CONTNET(100);	//��
		if(num%100)
		{
			MUSIC_ADD_NUMBER_CONTNET(shi);	//ʮλ
			if(shi)
			{
				MUSIC_ADD_NUMBER_CONTNET(10);	//ʮ
				if(ge)
				{
					MUSIC_ADD_NUMBER_CONTNET(ge);	//��λ
				}
			}
			else
			{
				MUSIC_ADD_NUMBER_CONTNET(ge);	//��λ
			}
		}
	}
	else if(num<=9999)
	{
		MUSIC_ADD_NUMBER_CONTNET(qian);
		MUSIC_ADD_NUMBER_CONTNET(1000);
		if(num%1000)
		{
			MUSIC_ADD_NUMBER_CONTNET(bai);	//��λ
			if(bai)
			{
				MUSIC_ADD_NUMBER_CONTNET(100);	//��
			}
			if(num%100)
			{
				if(shi)
				{
					MUSIC_ADD_NUMBER_CONTNET(shi);	//ʮλ
					MUSIC_ADD_NUMBER_CONTNET(10);	//ʮ
					if(ge)
					{
						MUSIC_ADD_NUMBER_CONTNET(ge);	//��λ
					}
				}
				else
				{	
					if(bai)	MUSIC_ADD_NUMBER_CONTNET(shi);	//ʮλ
					MUSIC_ADD_NUMBER_CONTNET(ge);	//��λ
				}
			}
		}
	}	
}


void Music_Play_Handler(void)
{
		if(mp3.queue_play)//�����ʼ���Ŷ����������
		{
			if(mp3.QueueIndex < mp3.QueueSize)	//����δ���������Ϣ
			{
				if((mp3.status == mp3_stop) || mp3.ChangeNow) //��������һ�׻���ǿ���и�
				{
					c_dbg_print("[MP3]:%d,%d/%d",mp3.queue[mp3.QueueIndex],mp3.QueueIndex+1,mp3.QueueSize);
					MUSIC_Write_Cmd(mp3.queue[mp3.QueueIndex]);
					mp3.ChangeNow=0;
					mp3.QueueIndex++;
					mp3.status = mp3_playing;
					mp3.busy=0;mp3.dely=20;
				} 			
			}
			else if(mp3.status == mp3_stop)
			{
				mp3.queue_play=0;
			}
			if(mp3.status == mp3_playing)//������
			{
				if(mp3.busy==0)
				{
					if(MP3_BUSY()==RESET)	
					{
						if(mp3.dely==0)
						{
							mp3.busy=1;mp3.dely=20;c_dbg_print("<"); //���ŷ�æ
						}
					}
					else
					{
						mp3.dely=20;
					}
				}
				else
				{
					if(MP3_BUSY()!=RESET)
					{
						if(mp3.dely==0)
						{
							mp3.busy=0;mp3.status = mp3_stop;c_dbg_print(">\r\n");//�������
			}
					}
					else
					{
						mp3.dely=20;
					}
				}
		}
	}
}



void LED_Time_Handler(void)
{
	static u8 time=0;
	time++;
	if(time>50)
	{
		time = 0;
		Set_Led2_Tog();
	}
}

void System_Timeticket(void)
{
	if(rpm.start_flg)
	{
		timer.micros++;				//����
		if(timer.micros>100)	//1S
		{
			timer.micros = 0;	//��������
			timer.total_time++;	//����������
			timer.second_flg=1;
		}
	}
}


void RPM_Timeticket(void)
{
	if(rpm.filter) rpm.filter--;
	if(rpm.timeout) rpm.timeout--;
	if(rpm.delay_cnt) rpm.delay_cnt--;
	if(rpm.time_cnt) rpm.time_cnt--;
	if(mp3.dely) mp3.dely--;
}

u8 Get_Buffer_Checksum(u8 *buff,u8 len)
{
	u8 i,sum;
	sum = 0;
	for(i=0;i<len;i++)
	{
		sum = sum + buff[i];
	}
	return sum;
}

void Uart_BLE_Handler(void)
{
	if(uart2.rev_flg==1)
		{
			//if(Get_Buffer_Checksum(&uart2.rbuf[2],uart2.length-3)==uart2.rbuf[uart2.length-1])
			{
				switch(uart2.rbuf[6]) //�����ֽ�
				{
					case 0xD0:	//����ָ��
					{
						display.b_enable=1;
						
						uart2.sbuf[0]=0xAA;
						uart2.sbuf[1]=0x06;
						uart2.sbuf[2]=0x00;
						uart2.sbuf[3]=0x02;
						uart2.sbuf[4]=0x00;
						uart2.sbuf[5]=Device_ID;
						uart2.sbuf[6]=0xD0;
						uart2.sbuf[7]=Get_Buffer_Checksum(&uart2.sbuf[2],5);
						Uart2_Send_N_bytes((u8 *)uart2.sbuf,8);
						c_dbg_print("[BLE]: ***********ACK*********\r\n");
					}break;
					case 0xD1:	//����ֹͣ
					{
						if(uart2.rbuf[7]==0x00) //ֹͣ����
						{
							Beep_Ring(150);
							rpm.start_flg=0;
							rpm.upload_flg = 0;
							uart2.sbuf[0]=0xAA;
							uart2.sbuf[1]=0x07;
							uart2.sbuf[2]=0x00;
							uart2.sbuf[3]=0x02;
							uart2.sbuf[4]=0x00;
							uart2.sbuf[5]=Device_ID;
							uart2.sbuf[6]=0xD1;
							uart2.sbuf[7]=0x01; //OK
							uart2.sbuf[8]=Get_Buffer_Checksum(&uart2.sbuf[2],6);
							Uart2_Send_N_bytes((u8 *)uart2.sbuf,9);
							c_dbg_print("[BLE]: ***********Stop*********\r\n");
						}
						else if(uart2.rbuf[7]==0x01) //��ʼ����
						{
							Beep_Ring(150);
							rpm.total_cnts=0;
							rpm.calorie=0;
							timer.total_time=0;
							rpm.start_flg=1;
							display.b_enable=1;
							rpm.upload_flg = 1;
							MUSIC_PLAY_CONTENT(17);	//��ӭʹ��
							uart2.sbuf[0]=0xAA;
							uart2.sbuf[1]=0x07;
							uart2.sbuf[2]=0x00;
							uart2.sbuf[3]=0x02;
							uart2.sbuf[4]=0x00;
							uart2.sbuf[5]=Device_ID;
							uart2.sbuf[6]=0xD1;
							uart2.sbuf[7]=0x01; //OK
							uart2.sbuf[8]=Get_Buffer_Checksum(&uart2.sbuf[2],6);
							Uart2_Send_N_bytes((u8 *)uart2.sbuf,9);
							c_dbg_print("[BLE]: ***********Start*********\r\n");
						}
					}break;
					case 0xD2:
					{
						uart2.sbuf[0]=0xAA;
						uart2.sbuf[1]=13;
						uart2.sbuf[2]=0xFF;
						uart2.sbuf[3]=0x02;
						uart2.sbuf[4]=0x00;
						uart2.sbuf[5]=Device_ID;
						uart2.sbuf[6]=0xD2;
						uart2.sbuf[7]=rpm.total_cnts>>8;
						uart2.sbuf[8]=rpm.total_cnts;
						uart2.sbuf[9]=timer.total_time>>8;
						uart2.sbuf[10]=timer.total_time;
						uart2.sbuf[11]=rpm.calorie>>8;
						uart2.sbuf[12]=rpm.calorie;
						uart2.sbuf[13]=Get_Buffer_Checksum(&uart2.sbuf[2],11);
						Uart2_Send_N_bytes(uart2.sbuf,14);
						c_dbg_print("[BLE-R]cnt:%d,time:%d,cal:%d\r\n",rpm.total_cnts,timer.total_time,rpm.calorie);
					}break;
					case 0xD5:
                    {
                        if(uart2.rbuf[7]<8)
                        {
                        	MUSIC_SET_VOLUMN(uart2.rbuf[7]*2);
                            MUSIC_Write_Cmd(0);                            
                        }
                        
                    }break;
					
					
					
					
					
				}
				rpm.timeout=Timeout_Max;	//1����
				rpm.time_cnt=TimeCnt_Max;	//5����
			}
			uart2.rev_flg=0;
			uart2.length=0;
			uart2.time_cnt=0;
		}

}

void RPM_Loop_Handler(void)
{
	if(rpm.int_flg==1)
		{
			rpm.int_flg=0;
			if(rpm.filter==0)
			{
				rpm.filter=20;
				rpm.total_cnts++;
				
				Beep_Ring(10);

				if(rpm.start_flg==0)
				{
					rpm.total_cnts=1;
					rpm.calorie=0;
					timer.total_time=0;
					rpm.start_flg=1;

				}
			}
			display.b_enable=1;
			rpm.calorie=rpm.total_cnts/17;
			rpm.state=1;
			rpm.timeout=Timeout_Max;	//1����
			rpm.time_cnt=TimeCnt_Max;	//5����
		}
		if(rpm.time_cnt==0)
		{
			if(rpm.start_flg==1)
			{
				rpm.start_flg=0;
				//�ڴ˲����ɼ�
				MUSIC_CLEAR_QUEUE();
				MUSIC_ADD_CONTENT(18);//�� �����˶�ʱ��Ϊ
				if(timer.total_time>=60)
				{
					MUSIC_ADD_INT_CONTENT(timer.total_time/60);
					MUSIC_ADD_CONTENT(13);//��
					MUSIC_ADD_INT_CONTENT(timer.total_time%60);	//ʱ��
					MUSIC_ADD_CONTENT(14);//��
				}
				else
				{
				MUSIC_ADD_INT_CONTENT(timer.total_time);	//ʱ��
				MUSIC_ADD_CONTENT(14);//��
				}
				MUSIC_ADD_CONTENT(20);//����Ϊ
				MUSIC_ADD_INT_CONTENT(rpm.total_cnts);	//����
				MUSIC_ADD_CONTENT(15);//��
				MUSIC_ADD_CONTENT(21);//��·��
				MUSIC_ADD_INT_CONTENT(rpm.calorie);
				MUSIC_ADD_CONTENT(22);//��ӭ�´�ʹ��
				MUSIC_START_PLAY();				
			}
		}
		if(rpm.timeout==0)
		{
			if(rpm.state==1)
			{
				rpm.state=0;
				uart2.sbuf[0]=0xAA;
				uart2.sbuf[1]=07;
				uart2.sbuf[2]=0x00;
				uart2.sbuf[3]=0x02;
				uart2.sbuf[4]=0x00;
				uart2.sbuf[5]=Device_ID;
				uart2.sbuf[6]=0xD3;
				uart2.sbuf[7]=0x00;
				uart2.sbuf[8]=Get_Buffer_Checksum(&uart2.sbuf[2],6);
				Uart2_Send_N_bytes(uart2.sbuf,9);
				delay_ms(500);
				BLE_RST_Low();
				delay_ms(150);
				BLE_RST_High();
			}
			rpm.total_cnts=0;
			rpm.calorie=0;
			timer.total_time=0;
			display.b_enable=0;
			rpm.upload_flg=0;
		}
		if(rpm.delay_cnt==0)
		{
			rpm.delay_cnt=50;
			if(rpm.upload_flg==1)
			{
				uart2.sbuf[0]=0xAA;
				uart2.sbuf[1]=13;
				uart2.sbuf[2]=0xFF;
				uart2.sbuf[3]=0x02;
				uart2.sbuf[4]=0x00;
				uart2.sbuf[5]=Device_ID;
				uart2.sbuf[6]=0xD2;
				uart2.sbuf[7]=rpm.total_cnts>>8;
				uart2.sbuf[8]=rpm.total_cnts;
				uart2.sbuf[9]=timer.total_time>>8;
				uart2.sbuf[10]=timer.total_time;
				uart2.sbuf[11]=rpm.calorie>>8;
				uart2.sbuf[12]=rpm.calorie;
				uart2.sbuf[13]=Get_Buffer_Checksum(&uart2.sbuf[2],11);
				Uart2_Send_N_bytes(uart2.sbuf,14);
				c_dbg_print("[BLE-A]cnt:%d,time:%d,cal:%d\r\n",rpm.total_cnts,timer.total_time,rpm.calorie);
			}
		}


}


void Flash_Display_RAM(void)
{
    if(display.blink_cnt==0)
    {
        display.blink_cnt=50;
        display.blink_val=~display.blink_val;
    }
    LCD_Clear_All();
    if(display.b_enable)
    {
		Set_TIME_Display(timer.total_time,display.blink_val);
		Set_Count_Display(rpm.total_cnts);
	    Set_Calorie_Display(rpm.calorie);  
    }
	if(display.timer==0)	//�̶�ˢ����ʾ
	{
		display.timer=10;
		LCD_Update_CGRAM();
	}
}


void Function(void)
{
	Music_Play_Handler();
	Uart_BLE_Handler();
	RPM_Loop_Handler();
	Flash_Display_RAM();
}

