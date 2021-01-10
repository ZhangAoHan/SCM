/*---------------------------------------------------------------------------------
	    				STM32 4.3TFT�����ײ���������
 
 ˵��: �������Ǿ����Ĵδ�ĵ������ȶ��汾,�˰汾��ȫ�����֮ǰ�汾��ʾͼ�κ����ֵ�
 	   ʱ���Զ�����������.ϵͳ���ȶ��õ��������ǿ,������3���ֿ�,�ֱ���ASCII�ֿ�
	   16x16���Ҷ����ֿ�,16x16�Զ����ֿ�,�ɹ���ͬ����½���ѡ��,����ʵ��.
	   ��V3.0�濪ʼ����Ӳ����ص��������򵥶�д��TFT_Drive.c�ļ�,��Ӳ���޹ص�Ӧ��
	   ����ӿ�д��TFT_API.c�ļ�,ͬʱ������Ӧ��ͷ�ļ�.ʹ��TFT��ʱ��ֻ��Ҫ��main�ļ�
	   �а���TFT_API.h ����LCD_Init(),LCD_FSMC_Init()�����������ʹ��.
 
 ʱ��: 2013��7��28�� 							BoX��д
 
 �汾: V1.0 ԭ����������,����ͨ��,��API 	    2013-7-27
       V2.0 �İ���������,����API,���ȶ� 		2013-7-28
	   V2.5 �Ľ���Բ�㷨,�����ַ���API,���ȶ� 	2013-8-17
	   V3.0 �Ľ��ȶ���,���Ӵ�С�ֿ���ʾ,�ȶ���  2013-8-18
	   V3.1 Ϊ����ӦUCGUI����ֲ������������ 	2014-2-09 
--------------------------------------------------------------------------------*/
#include "tft_drive.h"
#include "stm32f10x.h"
#include "delay.h"

/*---------------------------------------------------------
		������йصĲ���,�����������ڻ������
--------------------------------------------------------*/
unsigned int  HDP=479; //ˮƽ�ֱ���480
unsigned int  VDP=271; //���ֱ���272
unsigned int  HT=531;  //ˮƽ������532
unsigned int  HPS=43;
unsigned int  LPS=8;
unsigned char HPW=1;
unsigned int  VT=288;
unsigned int  VPS=12;
unsigned int  FPS=4;    
unsigned char VPW=10;
 

void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}			 

void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

uint16_t LCD_RD_data(void)
{
	uint16_t a=0;
	
	a = *(__IO uint16_t *) (Bank1_LCD_D);   //�ղ�������Ĳ���ɾ��
	a = *(__IO uint16_t *) (Bank1_LCD_D);   //������ʵ��16λ��������	  
	
	return a;	
}

void LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

void LCD_WR_Data_8(unsigned int val)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}
/*---------------------------------------------------------
	��������: ��SSD1963оƬ��������ʼ������
	��������: ��
--------------------------------------------------------*/
void LCD1963_Init(void)
{	
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    Software_Delay(0xAFFFF);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
	Software_Delay(0xAFFFF);

    LCD_WR_REG(0x00E2);	        //PLL ��Ƶ��120M   PLL=10*36/3=120M
	LCD_WR_Data(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_Data(0x0002);
	LCD_WR_Data(0x0004);
	
	LCD_WR_REG(0x00E0);         
	LCD_WR_Data(0x0001);
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x00E0);
	LCD_WR_Data(0x0003);		// PLL ʹ��  PLL��Ϊʱ��
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x0001);         // �����λ
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x00E6);	        //PLL setting for PCLK, depends on resolution
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x0033);
	LCD_WR_Data(0x0032);

    LCD_WR_REG(0x00B0);	        //����LCDģʽ
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_Data((HT>>8)&0X00FF);  //Set HT
	LCD_WR_Data(HT&0X00FF);
	LCD_WR_Data((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(HPS&0X00FF);
	LCD_WR_Data(HPW);			   //Set HPW
	LCD_WR_Data((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(LPS&0X00FF);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_Data((VT>>8)&0X00FF);   //Set VT
	LCD_WR_Data(VT&0X00FF);
	LCD_WR_Data((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_Data(VPS&0X00FF);
	LCD_WR_Data(VPW);			   //Set VPW
	LCD_WR_Data((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_Data(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_Data(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_Data(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_Data(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036);            //rotation
	LCD_WR_Data(0x0000);


	LCD_WR_REG(0x00F0);             //16λ  565ģʽ
	LCD_WR_Data(0x0003);


	Software_Delay(0xAFFF);

	LCD_Clear_All(Black);
	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_Data(0x0006);
	LCD_WR_Data(0x0080);
	
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x00f0);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00D0);//���ö�̬����������� 
	LCD_WR_Data(0x000D);
}
/*---------------------------------------------------------
	��������: ��STM32��FSMC���߽��г�ʼ��
	��������: ��
--------------------------------------------------------*/
void FSMC_LCD_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTimingInitStructure;	
    GPIO_InitTypeDef GPIO_InitStructure;
	//ʹ��IO��,FSMCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC , ENABLE);
	//PD13->LCD�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	//PE1->REST��λ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	//���ö˿�ΪFSMC�ӿ� FSMC-D0--D15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	  //�������
    GPIO_Init(GPIOD, &GPIO_InitStructure);   
   	//���ö˿�ΪFSMC�ӿ� FSMC-D0--D15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);    
    //FSMC NE1  LCD->CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //FSMC LCD->RS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
    GPIO_Init(GPIOD, &GPIO_InitStructure); 	
    GPIO_SetBits(GPIOD, GPIO_Pin_13);  //LCD������
	//FSMCʱ������,�������Ϊ����������δ�о�
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 0x02;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 0x05;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	/* NOR FLASH��BANK 1*/
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	/* �����ߺ͵�ַ�߲����� */
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	/* FSMC�ڴ�����NOR */
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	/* FSMC�ڴ����ݿ��16λ */
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	/* �첽дģʽ,��ֹͻ��ģʽ */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	/* �ò���ֻ��ͻ��ģʽ����Ч,�ȴ��źż���Ϊ�� */
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	/* ��ֹ�Ƕ���ͻ��ģʽ */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	/* �ò���ֻ��ͻ��ģʽ����Ч,�ڵȴ�״̬֮ǰ�ȴ��źż��� */
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	/* FSMCдʹ�� */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	/* FSMC�ȴ��źŹر� */
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	/* FSMC��չģʽ�ر� */
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	/* ��ֹдͻ�� */
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	//FSMC��дʱ������
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
 	//FSMCдʱ������
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 		
    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
