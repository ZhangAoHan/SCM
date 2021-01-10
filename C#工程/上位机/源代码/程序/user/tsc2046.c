/*-------------------------------------------------------------------------------------------
 			                   TSC2046��������������������
 ˵��: TSC2046��������,����STM32F103VET6��������Ӧ�ܶ�4.3����Ļ��TSC2046�ܽ���������
 	   ADS7843��ADS7846��TSC2046��XPT2046��AK4182����оƬ������ʹ�ñ�����,�ҹܽż���
	   (16)DCLK --- PA5(SPI1_CLK)
	   (15)CS   --- PB7
	   (14)DIN  --- PA7(SPI1_MOSI)
	   (12)DOUT --- PA6(SPI1_MISO)
	   (11)PEN  --- PB6(IPU)
       
	   �����������ʹ�÷���
	   1).�����ú�stm32f10x_spi.c  tsc2046.c�ļ���ͷ�ļ�,����ϵ����У׼ģʽ��ͷ�ļ�������
	   2).���ŵ���TSC2046_Config()��ʼ��������
	   3).if(PENDIRQ == 0)
		  {
			TP_Read(&Tpx,&Tpy);
			TP_ADtoZB(&Tpx,&Tpy,&X,&Y);	
			Draw_Point(X,Y,Green);			
		  }
		  else...

 �汾: v1.0 2013/10/9 	���ԭʼ�汾,�ṩӲ����������  
 	   v1.1 2013/10/13  ���Ӵ�����У��,�ṩAPI�ӿ�,�ⶨ����ϵ��  
  
 BoX��д   
-------------------------------------------------------------------------------------------*/
#include "TSC2046.h"
#include "delay.h"
#include "stm32f10x.h"
#include "tft_api.h"


/*------------------------------------------------
  ��������:		TSC2046Ӳ������ 
------------------------------------------------*/
void TSC2046_Config(void)
{
	SPI_Config();
}	
/*----------------------------------------
 ��������: STM32 SPI1��������
 ��������: ��
 �� �� ֵ: ��
----------------------------------------*/
void SPI_Config(void)	  //�ܶ��廹��������SPI��������Ҫ���޹صĹص�
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);	//ʹ��APB2����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//��סʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
						   RCC_APB2Periph_GPIOE , ENABLE);
	//A5->SCK  A6->MISO A7->MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   //SPI�ø����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//C4->CS  FLASH��Ƭѡ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//B7->CS  ������Ƭѡ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//A4->CS ��̫��Ƭѡ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//B12->CS VS1003Ƭѡ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	//���������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	        //PENIRQ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//SPI1����
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//2��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//SPI��
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//���ݸ�ʽ8λ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				//ʱ�Ӽ��Ե�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		    //ʱ����λ��1���ش���
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_32; 
															//TSC2046 SPIͨ�����ʲ��ܴ���SYSCLK/32
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//MSB��ǰ
	SPI_InitStructure.SPI_CRCPolynomial = 7;				//CRC����ʽУ��
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);

	GPIO_SetBits(GPIOB,GPIO_Pin_12);//��ֹVS1003Ƭѡ
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	//��ֹ��̫��Ƭѡ
	GPIO_SetBits(GPIOC,GPIO_Pin_4); //��ֹFLASHƬѡ
}
/*----------------------------------------
 ��������: ��SPI����һ�ֽ�����
 ��������: Ҫ���͵�����dat
 �� �� ֵ: ����������������
----------------------------------------*/
uint8 SPI_WriteByte(uint8 dat)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
/*----------------------------------------
 ��������: SPI��ȡһ���ֽ�
 ��������: ��
 �� �� ֵ: ������������һ�ֽ�����
----------------------------------------*/
uint8 SPI_ReadByte(void)
{
	return(SPI_WriteByte(0x00));	//��סMOSI����MISO����Ҳ����
}
/*------------------------------------------------
  ��������:		SPI��ȡTSC2046��X ADֵ 
  ��������ֵ:	uint16 X��ѹֵ
------------------------------------------------*/
uint16 TP_ReadX(void)
{
	uint16 temp;
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);   //CS = 0
	Software_Delay(20);
	SPI_WriteByte(0x90);				//0x90�Ƕ�ȡX����ֵ����
	Software_Delay(20);
	temp = SPI_ReadByte();				//����12λADֵ
	temp <<= 8;
	temp += SPI_ReadByte();				//�������µ�8λADֵ
	Software_Delay(20);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);		//CS = 1;
	temp >>= 3;							//�����12λ����
	return temp;
}
/*------------------------------------------------
  ��������:		SPI��ȡTSC2046��Y ADֵ 
  ��������ֵ:	uint16 Y��ѹֵ
------------------------------------------------*/
uint16 TP_ReadY(void)
{
	uint16 temp;
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);   //CS = 0
	Software_Delay(20);
	SPI_WriteByte(0xD0);
	Software_Delay(20);
	temp = SPI_ReadByte();
	temp <<= 8;
	temp += SPI_ReadByte();
	Software_Delay(20);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);		//CS = 1;
	temp >>= 3;							//�����12λ����
	return temp;
}
/*------------------------------------------------
  ��������:		��ȡTSC2046�Ĵ���ADֵ 
  ��������ֵ:	����ָ����
  �����ӿ�:     ָ��tpx,ָ��tpy 
------------------------------------------------*/
void TP_Read(uint16 *tpx,uint16 *tpy)
{
	float tempx=0,tempy=0;
	uint16 TpBufferX[10];				//���ݻ���
	uint16 TpBufferY[10];
	uint8  i=0;
	do								    //��ȡ10��ADֵ
	{
		*tpx = TP_ReadX();
		*tpy = TP_ReadY();
		if(*tpx>100 && *tpx<4000 && *tpy>100 && *tpy<4000) //ȷ����ȡ��������Ч
		{
			TpBufferX[i] = *tpx;
			TpBufferY[i] = *tpy;
			i++;	
		}
	}while(PENDIRQ==0 && i<10);

	BubbleSort(TpBufferX,10); 	//��������
	BubbleSort(TpBufferY,10);
	for(i=3;i<8;i++)
	{
		tempx += TpBufferX[i];	//ȡ���м�ֵ
		tempy += TpBufferY[i];
	}
	tempx /= 5;				//����ƽ��ֵ
	tempy /= 5;
	*tpx = (uint16)tempx;
	*tpy = (uint16)tempy;
}
/*------------------------------------------------
  ��������:		�Ľ��㷨��ð������ 
  ��������ֵ:	��
  �����ӿ�:     �����׵�ַa,���鳤��n 
  ��д����:		2013��6��6��
------------------------------------------------*/
void BubbleSort(uint16 a[],uint8 n)  //�Ľ��㷨��ð������ 
{
    uint16 i,j,t,flag=0;
    for(i=0;i<n;i++)
    {
        for(j=n-1;j>i;j--)
        {
            if(a[j-1]<a[j])	 //��������
            {
                t=a[j-1];
                a[j-1]=a[j];
                a[j]=t;
                flag=1;
            }
        }
        if(flag==0)
			break;
        else 
			flag=0;
    }
}
/*----------------------------------------
 ��������: AD-->����ֵת��
 ��������: ��
 �� �� ֵ: ������������һ�ֽ�����
----------------------------------------*/
void TP_ADtoZB(uint16 *tpx,uint16 *tpy,uint16 *x,uint16 *y)
{
#ifdef CONSTMODE			   //����ģʽ,����Ҫ��������ϵ��
	*x = ((4096-*tpx)/FACX);   //����ϵ��,��ֵ�;������Ļ�й�ϵ,������ֵ��ʵ��ó��Ľ��.
	*y = ((4096-*tpy)/FACY);   //��ͬ��Ļ�в�ͬ����ϵ��,���ݲ�ͬ��Ļ���е���
#endif

#ifdef ADJMODE				   //У׼ģʽ,�ֶ����ڱ���ϵ��
	*x = ((4096-*tpx)/Kx);	   //���ʹ��У׼�����ֵӦ����7.9-8.1
	*y = ((4096-*tpy)/Ky);	   //���ʹ��У׼�����ֵӦ����14.1����
#endif	
}
/*----------------------------------------
 ��������: ������У׼�ó�����ϵ��
 ��������: ��
 �� �� ֵ: �ı�ȫ�ֱ���Kx,Ky
----------------------------------------*/
#ifdef ADJMODE
void TouchScreenAdjust()
{
	uint8 i,AdjTimes=0;
	uint16 Ax,Ay,Bx,By;
	/* ��Kx,Ky�ı���ϵ������������Χ����һֱУ׼ֱ���������߳���3��Ϊֹ
	 * ������3����Ȼʧ�ܵ�ʱ�������ϵ����ȡĬ��ֵFACX,FACY
	 * �±߽�ֵ��ȷ���Ǹ���ʵ�鷨��õ�
	 */
	while(AdjTimes < 3)	           //���Դ���3��
	{
		AdjTimes++;
		LCD_Write_String(180,200,"Touch First Point   ",Yellow,Black);
		for(i=0; i<20; i++)		   //�����Ͻǵ�A(20,20)��ʾʮ��
	    {							
			Draw_Point(20,10+i,Green);
			Draw_Point(10+i,20,Green);
	    }
		while(1)
		{
			if(PENDIRQ == 0)
			{
				Software_Delay(10000);           //��ʱȥ��
				while(PENDIRQ == 0)
				{
					TP_Read(&Ax,&Ay);
					Software_Delay(10000000);    //��ʱȥ��
				}
				break;
			}
		}
			
		LCD_Write_String(180,200,"Touch Seconed Point",Yellow,Black);
		for(i=0; i<20; i++)		   //�����ĵ�B(240,136)��ʾʮ��
	    {							
			Draw_Point(240,126+i,Green);
			Draw_Point(230+i,136,Green);
	    }
		while(1)
		{
			if(PENDIRQ == 0)
			{
				Software_Delay(10000);           //��ʱȥ��
				while(PENDIRQ == 0)
				{
					TP_Read(&Bx,&By);
					Software_Delay(10000000);   //��ʱȥ��
				}
				break;
			}
		}
		
		Kx = Ax - Bx;			   //����x�����ֵ
		Ky = Ay - By;			   //����y�����ֵ
		Kx = Kx / (240-20);	       //�����ÿ�����صı���ϵ��  
		Ky = Ky / (136-20);	       //�����ÿ�����صı���ϵ��  

		if(Kx<7.85 || Kx>8.05 || Ky<14.00 || Ky>14.15)
		{
			LCD_Write_String(180,230,"Adjuest Failure!",Yellow,Black);
			LCD_Clear_Select(0,0,300,200,Black);
		}
		else
		{				  // ��Kx,Ky�ı���ϵ������������Χ����һֱУ׼ֱ������Ϊֹ
	       break;         // �߽�ֵ��ȷ���Ǹ���ʵ�鷨��õ�               	
		}
	}//End of while
	AdjuestFlag = 1;	  //У׼���־λ��1
	if(AdjTimes >= 3)	  //������3����Ȼʧ�ܵ�ʱ�������ϵ����ȡĬ��ֵFACX,FACY
	{
		Kx = FACX;
		Ky = FACY;
		LCD_Write_String(180,230,"Out of times!   ",Yellow,Black);
	}
	else
	{
		LCD_Write_String(180,230,"Adjuest Success!",Yellow,Black);
	}
}//End of Fun
#endif
