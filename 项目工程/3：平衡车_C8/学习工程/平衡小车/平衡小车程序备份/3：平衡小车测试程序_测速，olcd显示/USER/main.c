#include "sys.h"

	u8 res;         //�������ձ���
	
void Bluetooth(void);
void Olcd_Display(void);
void Speed(void); 
 int main(void)
 {	
	 //ϵͳ��ʼ��
	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	  		//��ʱ��ʼ��
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600	
	 
	 //OLCD��ʼ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear() ;   //����
	 
	   //6050��ʼ��
	 	//IIC_Init();                  //6050_iic��ʼ��	
     //	DMP_Init();                  //6050_DMP��ʼ��
     	//MPU6050_initialize();        //6050_��ʼ��
	 
	 //���pwm��ʼ��
		Timer_init(7199,0);   //����Ƶ��pwmƵ��Ϊ72M/7200=10K hz  ��pwm��������Ϊ7200����ʱ��3�ڲ�����ȽϼĴ���װ��ֵ��900�Ƚ�
		MOTO_PWM_init();
     	Mortor_init();
		TIM2_init(65535);     //����Ƶ��72M/65536=900us��һ���ٶ�
		TIM4_init(65535);
	 
	 
	while(1)
	{
//	Read_DMP();                  //��6050��ֵ
	Motor_PWM(5500,5500) ;      //PWM����Ϊ6900.��ֵԽ��Խ����
	Speed();
//    Olcd_Display();
	}
 }
 
void Bluetooth()          //�������պ���
{
	switch(res)
	{
		case 0x00:  led=0;   break;
		case 0x01:  led=1;   break;
	}
}
void Olcd_Display()
{
	//128*64  x=0-127  y=0-7(ÿ��yռ8��)   
		OLED_Clear();                                //���������������������ʾ���ݻ��໥���ǣ�
		OLED_ShowCHinese(0,0,14);                 //��ʾ���ֺ��� �ţ�������x,y,C��X��Y�����ֵ����꣨ÿ������ռ16*16,��x��y����C�����ֵ������
	    OLED_ShowCHinese(16,2,15);  //��
	    OLED_ShowCHinese(32,4,16);  //��
		delay_ms(3000);
		OLED_Clear() ; 
		OLED_ShowString(6,3,"0.96' OLED TEST",SIZE);    //��ʾ�ַ�������  ������x,y,"�ַ���",s��  x,yΪ�ַ�����ʼ���꣨��x��y��ÿ���ַ�ռ8*16��s=16����6*8��s=SIZE=8����
		delay_ms(3000);
		OLED_Clear() ; 
		OLED_ShowNum(0,2,100,3,16);//��ʾ����  ������x,y,num,len,size��  lenΪ���ֵ���Чλ������len�������־�ȷ�ֽ⣩  munΪ���֣�
		delay_ms(3000);
		OLED_Clear() ; 
	   OLED_ShowChar(48,6,'1',16);//��ʾASCII�ַ�	������x,y,���ַ���,size��  ע�⣺�ַ��õ����ţ��ַ�����˫����   
		delay_ms(3000);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
//		delay_ms(3000);
}
void Speed_Show(u16 left,u16 right,u16 tms)
{
	OLED_Clear(); 
	OLED_ShowString(0,0,"Left",16);
	OLED_ShowChar(32,0,':',16);
	OLED_ShowNum(40,0,left,8,16);
	OLED_ShowString(0,2,"RIGHT",16);
	OLED_ShowChar(40,2,':',16);
	OLED_ShowNum(48,2,right,8,16);
	delay_ms(tms);
}
void Speed()              //���ٲ���ʾ
{
	u16 s_left,s_right;
	s_left=Read_val(2);
	s_right=Read_val(4);
	Speed_Show(s_left,s_right,100);
}





