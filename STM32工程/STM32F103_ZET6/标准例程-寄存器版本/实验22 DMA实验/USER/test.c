#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h" 
#include "key.h" 
#include "dma.h" 	 
//ALIENTEKս��STM32������ ʵ��22
//DMA ʵ�� 
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  

#define SEND_BUF_SIZE 8200	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
const u8 TEXT_TO_SEND[]={"ALIENTEK WarShip STM32F1 DMA ����ʵ��"};	 

int main(void)
{	
	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;			//����
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ115200
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DMA TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/15");	
 	LCD_ShowString(30,130,200,16,16,"KEY0:Start");
	//��ʾ��ʾ��Ϣ	
	j=sizeof(TEXT_TO_SEND);	   
	for(i=0;i<SEND_BUF_SIZE;i++)//������ݵ�SendBuff
    {
		if(t>=j)//���뻻�з�
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}    	   
    }		 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)//KEY0����
		{
			LCD_ShowString(30,150,200,16,16,"Start Transimit....");
			LCD_ShowString(30,170,200,16,16,"   %");//��ʾ�ٷֺ�
			printf("\r\nDMA DATA:\r\n"); 	    
		    USART1->CR3=1<<7;           //ʹ�ܴ���1��DMA����       
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		    while(1)
		    {
				if(DMA1->ISR&(1<<13))//�ȴ�ͨ��4�������
				{
					DMA1->IFCR|=1<<13;//���ͨ��4������ɱ�־
					break; 
		        }
				pro=DMA1_Channel4->CNDTR;//�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/SEND_BUF_SIZE;//�õ��ٷֱ�	  
				pro*=100;      //����100��
				LCD_ShowNum(30,170,pro,3,16);	  
		    }			    
			LCD_ShowNum(30,170,100,3,16);//��ʾ100%	  
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");//��ʾ�������
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}


