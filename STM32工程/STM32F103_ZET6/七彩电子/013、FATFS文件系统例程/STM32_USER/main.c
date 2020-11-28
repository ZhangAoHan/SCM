/*  main.c  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "w25qxx.h"
#include "string.h"
#include "ff.h"
#include "sdio_sdcard.h"
#include "beep.h"




/***********************************************************************/
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/***********************************************************************/
 
 
 
 




//FatFs��������
FATFS fs; 
FIL fsrc;


const char f_path[]={"test.txt"};
const char test_txt[]={"̫��M3-STM32F103������SD��FATFS����ʵ�����\r\n��������ͨ��FATFSд���!\r\n"};
u8 test_buf[200];
u32 count=0;
u16 i=0;




int main(void)
{
	u8 t=0,r=0;
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	//Beep_Init();
	USART1_Init(115200);//����1��ʼ��
	
	//��ʱ1��
	delay_ms(1000);
	
	printf("̫��M3-STM32F103������SD��FATFSʵ�鿪ʼ !\r\n");
	delay_ms(1000);
	
	Start:
	//��ʼ��ʼ��SD��
	while( SD_OK != SD_Init() ){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("SD ����ʼ��ʧ�� !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nSD ����ʼ���ɹ� !\r\n");
	printf("SD������: %dM\r\n",(u32)SDCardInfo.CardCapacity/1024/1024);
	
	delay_ms(1000);
	
	//��ʼ��ʼ���ļ�ϵͳ
	while(FR_OK != f_mount(&fs,"0:",1)){
		delay_ms(30);
		t++;
		if(t%10==0){
			//BEEP_TOGGLE();
			LED_TOGGLE(LED1);
		}
		if(t>30){
			t=0;
			printf("FatFs ����ʧ�� !\r\n");
		}
	}
	//BEEP_OFF();
	printf("\r\nFatFs ���سɹ� !\r\n");
	
	delay_ms(1000);
	
	//��ʼ�����ļ�
	r=f_open(&fsrc,f_path,FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	if(FR_OK != r){
		printf("\r\n�����ļ�ʧ�� !\r\n");
		goto Start;
	}
	printf("\r\n�����ļ��ɹ� !\r\n");
	
	delay_ms(1000);
	
	//��ʼд������
	r=f_write(&fsrc,test_txt,strlen((const char*)test_txt),&count);
	//д��������ϣ��ر��ļ�
	f_close(&fsrc);
	if(FR_OK != r){
		printf("�ļ�д��ʧ�� !\r\n");
		goto Start;
	}
	printf("FATFSд��%d���ֽ� !\r\n",count);
	
	delay_ms(1000);
	
	//���´��ļ���׼����ȡ����
	r=f_open(&fsrc,f_path,FA_READ|FA_WRITE);
	if(FR_OK != r){
		printf("���´��ļ�ʧ�� !\r\n");
		goto Start;
	}
	printf("\r\n�����ļ��ɹ� !\r\n");
	
	delay_ms(1000);
	
	//��ʼ��ȡ����
	r=f_read(&fsrc,test_buf,strlen((const char*)test_txt),&count);//	
	f_close(&fsrc);
	if(FR_OK != r){
		printf("��ȡ�ļ�ʧ�� !\r\n");
		goto Start;
	}
	printf("\r\n��ȡ�ļ��ɹ� !��ȡ������%d�ֽ����ݣ�\r\n\r\n%s",count,test_buf);

	delay_ms(1000);
	//�������
	printf("\r\n\r\n������� !\r\n");
	while(1)
	{
		delay_ms(500);
		LED_TOGGLE(LED0);
	}
}




