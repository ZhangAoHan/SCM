#include "24l01.h"
#include "delay.h"
#include "spi.h"
#include "ezio.h"





/*************************** �ļ�˵�� *******************************/
//NRF24L01+ ��������
//�˳����������߲ʹ���̫��M3��STM32F103�����弰���ּ��ݵ�STM32ϵͳ��
//�Ա�����"�߲ʹ��� ̫��M3 STM32������"���򳬸��Լ۱ȿ�������ȡ��������
//ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
/********************************************************************/  



//�汾˵��
/*
 V0.001
 2018.06.21   15:27 ��ʼ�汾

*/








//-----------------------IO �ڶ���-----------------------------------
//NRF24L01_CE
#define NRF24L01_CE_IO   PG8
#define NRF24L01_CE_PORT GPIOG
#define NRF24L01_CE_PIN  GPIO_Pin_8

//NRF24L01_CS
#define NRF24L01_CS_IO    PG7
#define NRF24L01_CS_PORT  GPIOG
#define NRF24L01_CS_PIN   GPIO_Pin_7

//NRF24L01_IRQ
#define NRF24L01_IQR_IO    PG6
#define NRF24L01_IQR_PORT  GPIOG
#define NRF24L01_IQR_PIN   GPIO_Pin_6


//-----------------   IO ��������  -------------------------------------
#define NRF24L01_CS_L() (NRF24L01_CS_PORT->BRR=NRF24L01_CS_PIN)
#define NRF24L01_CS_H() (NRF24L01_CS_PORT->BSRR=NRF24L01_CS_PIN)

#define NRF24L01_CE_L()  (NRF24L01_CE_PORT->BRR=NRF24L01_CE_PIN)
#define NRF24L01_CE_H()  (NRF24L01_CE_PORT->BSRR=NRF24L01_CE_PIN)

#define NRF24L01_IQR_READ()   (((NRF24L01_IQR_PORT->IDR&NRF24L01_IQR_PIN)==0)?(0):(1))

			   	   
//-----------------------   SPI �ӿں����޽�  ------------------------

#define NRF24L01_SPI_Init()     SPI2_Init()
#define NRF24L01_Read_Byte()    SPI2_ReadWriteByte(0xFF)
#define NRF24L01_Write_Byte(x)  SPI2_ReadWriteByte(x)
#define NRF24L01_RW_Byte(x)     SPI2_ReadWriteByte(x)
#define NRF24L01_SPI_SetSpeed_10M()     SPI2_SetSpeed(SPI_BaudRatePrescaler_16) //SPI�ٶ�����,��������ΪС��10M





const u8 NRF_TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x02}; //���͵�ַ,�Է��Ľ��յ�ַ
const u8 NRF_RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x02}; //���յ�ַ,�Է��ķ��͵�ַ





//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{ 
	Pin_ModeSet(NRF24L01_CS_IO,OUTPUT_PP|OUT_H);     //CS ���ų�ʼ��
	Pin_ModeSet(NRF24L01_CE_IO,OUTPUT_PP|OUT_L);  //CE ���ų�ʼ��
	Pin_ModeSet(NRF24L01_IQR_IO,INPUT_PU);           //IQR �ж����ų�ʼ��
	

	NRF24L01_SPI_Init();
	NRF24L01_SPI_SetSpeed_10M();
	SPI_Cmd(SPI2,ENABLE);

	
	delay_ms(10);
	
	NRF24L01_CE_L(); 			//ʹ��24L01
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)NRF_RX_ADDRESS,RX_ADR_WIDTH);	//дRX�ڵ��ַ 
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)NRF_TX_ADDRESS,TX_ADR_WIDTH); 		//дTX�ڵ��ַ  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); 													//ʹ��ͨ��0���Զ�Ӧ�� 
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);											//ʹ��ͨ��0�Ľ��յ�ַ 
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);											//�����Զ��ط����ʱ��:500us;����Զ��ط�����:10�� 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);														//����RFͨ��ΪCHANAL
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); 												//����TX�������,0db����,2Mbps,���������濪��
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//ѡ��ͨ��0����Ч���ݿ�� 
	NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ�շ�����жϿ���,16λCRC,������
	NRF24L01_CE_H();
	
}
//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	//NRF24L01_CE_L();
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	//NRF24L01_CE_H();
	for(i=0;i<5;i++){
		if(buf[i]!=0XA5){
			return 1;//���24L01����	
		}
	}
	return 0;		 //��⵽24L01
}	 	 
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CS_L();                 //ʹ��SPI����
  	status =NRF24L01_RW_Byte(reg);//���ͼĴ����� 
  	NRF24L01_RW_Byte(value);      //д��Ĵ�����ֵ
  	NRF24L01_CS_H();                 //��ֹSPI����	   
  	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CS_L();          //ʹ��SPI����		
  NRF24L01_RW_Byte(reg);   //���ͼĴ�����
  reg_val=NRF24L01_RW_Byte(0XFF);//��ȡ�Ĵ�������
	reg_val=NRF24L01_Read_Byte();//��ȡ�Ĵ�������
  NRF24L01_CS_H();          //��ֹSPI����		    
  return(reg_val);           //����״ֵ̬
}	

//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
	NRF24L01_CS_L();           //ʹ��SPI����
	status=NRF24L01_RW_Byte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)
		pBuf[u8_ctr]=NRF24L01_RW_Byte(0XFF);//��������
	NRF24L01_CS_H();       //�ر�SPI����
	return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CS_L();          //ʹ��SPI����
  	status = NRF24L01_RW_Byte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)NRF24L01_RW_Byte(*pBuf++); //д������	 
  	NRF24L01_CS_H();       //�ر�SPI����
  	return status;          //���ض�����״ֵ̬
}


//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;   
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	NRF24L01_CE_L();
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE_H();//��������
	while(NRF24L01_IQR_READ()!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX){//�ﵽ����ط�����
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;
	if(NRF24L01_IQR_READ()==0){
		sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
		NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
		if(sta&RX_OK){//���յ�����
			NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
			NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
			return 0; 
		}
	}
	return 1;//û�յ��κ�����
}


//NRF24L01 ģʽ�л�
void NRF24L01_Set_Mode(u8 model)
{
	NRF24L01_CE_L();
	if(model==NRF_MODEL_RX){				//RX
		NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ�շ�����жϿ���,16λCRC,������
	}
	else if(model==NRF_MODEL_TX){		//TX
		NRF24L01_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����жϿ���,16λCRC,������
	}
	NRF24L01_CE_H();
}

































