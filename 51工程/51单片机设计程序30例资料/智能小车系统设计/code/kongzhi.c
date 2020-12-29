/*******************************************************************************
* �ļ����ƣ�kongzhi.c                         
* ˵�������ļ�ΪС�����Ƶ�c�ļ�
* ���ܣ�1.����ϰ��ﴫ������ѯ 
        2.С����״̬����
* �޸ģ� ��
* �汾��1.0.0
* ���ߣ�YuanDong 
* ʱ�䣺2009.7.14 
*******************************************************************************/

#include	<AT89X52.h>
#define     kongzhi_GLOBAL 1
#include	<kongzhi.h>

  uchar      PWM_t,PWM_t0;                //PWM_tΪ������(0~100)ʱ��Ϊ0~10ms
  uchar      time_count;                  //��ʱ����
  uint       number,number1;
  uchar      flag;		//flagΪС��״̬��־,0:ֹͣ,1:ǰ��,2:����
  uchar      flag2;		//flag2ΪС��״̬�ָ��Ĵ���,��С�������ϰ���ֹͣ,�ȵ��ϰ����ų�֮��,С����ֹ֮ͣǰ��״̬�ͼĴ���flag2��
  uchar      flag3;		//flag3ΪС������ֹͣ��ʱ��־,��ʼ��Ϊ0,�ȴ��ϰ��ų�֮��ֵΪ1,��ʼ��ʱ,����֮��ָ�ֹͣǰ���н�״̬
  uchar      flag4;     //--flag4Ϊ���Ź���λ��״̬�ָ��Ĵ���
  uchar      kind = 0;	//������������

/********************************************************
*�������ƣ�void bizhang()
*�������ܣ������ϰ���ʱ�Ĵ�����
*������ڣ���
*�������ڣ���
********************************************************/
void	bizhang()
{	
		zhang_ai = 1;
		if(zhang_ai == 0)
	{	
		flag2=flag;
		flag=0;
		while(zhang_ai == 0)
		{	
		keyboard();
		xunji();
		stop();
		WDT_CONTR=0x3b;
		}
		flag3=1;
	}
}

/********************************************************
*�������ƣ�void stop()
*�������ܣ�����Ŀ���Ŀ��ƺ���
*������ڣ���
*�������ڣ���
********************************************************/
void	stop()
{
		stop_1=1;				  //Ŀ��վ��1
		if(stop_1==0)flag=0;
		stop_2=1;				  //Ŀ��վ��2
		if(stop_2==0)flag=0;	  
		stop_3=1;				  //Ŀ��վ��3
		if(stop_3==0)flag=0;
}
  
/*******************************************************
*�������ƣ�void xunji()
*�������ܣ���ѯ����������������·��״����������Ӧ����
*������ڣ���
*�������ڣ���
********************************************************/
void	xunji()
{		
        uchar	jiekou;
		spy=0xff;
		if(flag==1)
	{
		jiekou=spy&0x0f;
			switch(jiekou)
		{
			/*****��ת*****/
			case 0x0d:kind=1;break;	 //0b0000 1101	 
			case 0x0c:kind=2;break;	 //0b0000 1100		 
			case 0x0e:kind=2;break;	 //0b0000 1110
			/*****��ת*****/
			case 0x0b:kind=3;break;	 //0b0000 1011
			case 0x07:kind=4;break;	 //0b0000 0111
			case 0x03:kind=4;break;	 //0b0000 0011
			case 0x00:flag=0;break;	 //0b0000 0000
			default:kind=0;break;
		}
	}
		spy=0xff;
		if(flag==2)
	{
		jiekou=spy&0xf0;
			switch(jiekou)
		{
			/*****��ת*****/
			case 0xd0:kind=3;break;	 //Ob1101 0000
			case 0xc0:kind=4;break;	 //0b1100 0000
			case 0xe0:kind=4;break;	 //0b1110 0000
			/*****��ת*****/
			case 0xb0:kind=1;break;	 //0b1011 0000
			case 0x70:kind=2;break;	 //0b0111 0000
			case 0x30:kind=2;break;	 //0b0011 0000
			case 0x00:flag=0;break;	 //0b0000 0000
			default:kind=0;break;
		}
	}
}

/*******************************************************
*�������ƣ�void delay()
*�������ܣ�����˲���ȥ����
*������ڣ���
*�������ڣ���
********************************************************/  
void	delay()
{	
	uchar i,k;
	for(i=20;i>0;i--)
	for(k=248;k>0;k--);
}  
/*******************************************************
*�������ƣ�uchar du_lie()
*�������ܣ���ȡ�����µļ��̵���ֵ
*������ڣ���
k
*�������ڣ�����
********************************************************/
uchar	du_lie()
{			
		if((key&0x0f)==0x07){return 0x01;}
		if((key&0x0f)==0x0b){return 0x02;}
		if((key&0x0f)==0x0d){return 0x03;}
		if((key&0x0f)==0x0e){return 0x04;}
		return	0x00;
}
/*******************************************************
*�������ƣ�uchar key_board()
*�������ܣ�����ʶ�����ȡ����
*������ڣ���
*�������ڣ����̵�ʶ����
********************************************************/
uchar	key_board()
{		
		key=0x3f;
		P2_4=0;
		if((key&0x0f)!=0x0f)
	{	delay();
			if((key&0x0f)!=0x0f){return (0x10|du_lie());}
	}	
		key=0x3f;P2_5=0;
		if((key&0x0f)!=0x0f)
	{	delay();
			if((key&0x0f)!=0x0f){return (0x20|du_lie());}
	}			
		return	0x00;
}		
/*******************************************************
*�������ƣ�void keyboard()
*�������ܣ�2*4����ʶ��,���ж�С������״��
*������ڣ���
*�������ڣ���
********************************************************/
void	keyboard()
{
 		switch(key_board())		
		{	case 0x11:{PWM_t=40;PWM_t0=40;break;}
			case 0x12:{flag=2;flag4=2;flag2=flag;break;}
			case 0x13:{flag=1;flag4=1;flag2=flag;break;}
			case 0x14:{flag=0;flag4=0;break;}
			case 0x21:{PWM_t=100;PWM_t0=100;break;}
			case 0x22:{PWM_t=90;PWM_t0=90;break;}
			case 0x23:{PWM_t=70;PWM_t0=70;break;}
			case 0x24:{PWM_t=50;PWM_t0=50;break;}
			default:break;
		}
}


 	
/*******************************************************
*�������ƣ�void timer_init()
*�������ܣ���ʱ����ʼ������
*������ڣ���
*�������ڣ���
********************************************************/
void timer_init()
{
		flag=0;flag3=0;
		key = 0xFF;
	    TMOD = 0x20;						//��ʱ��1Ϊģʽ2(8λ�Զ���װ)
		TF1 = 0;							//���жϱ�־
		TH1 = timer_data;					//��֤��ʱʱ��Ϊ0.1ms 
		TL1 = TH1;
		ET1 = 1;							//����T0�ж�
		TR1 = 1;							//��ʼ����
		EA = 1;							//�ж�����
		ENA = 0;							//�����ֹ
	    PWM_t = PWM_t0;					//���Ź���λ���ٶȻָ�
	    flag = flag4;						//���Ź���λ��С��״̬�ָ�
}
/*******************************************************
*�������ƣ�void IntTime1() interrupt 3 using 2
*�������ܣ���ʱ���жϴ���С�����߿���
*������ڣ���
*�������ڣ���
********************************************************/
void IntTime1()interrupt 3	using	2
{
      time_count++;
	  	if(flag3)number++;
		if(number==6000){number=0;number1++;}
		if(number1==8){flag3=0;number1=0;flag=flag2;}	
	  	if(flag==0)ENA=0;				//С��ֹͣ,flag=0,С��ֹͣ��־
		if(flag==1)						//С��ǰ��,flag=1,С��ǰ����־
	{
		ENA=1;							//PWM�����ʹ��
		DR=0;							//ֱ�����һ�˽ӵ͵�ƽ
		DR2=0;							//ֱ�����һ�˽ӵ͵�ƽ
		if(kind==0)						//û�д�������⵽����,��ֱ��
        {	if(time_count<PWM_t)
        	{PWM=1;PWM2=1;}
        	else
        	{PWM=0;PWM2=0;}
		}
		if(kind==1)						//��ߵ�һ����������⵽����
        {	
			if(time_count<(PWM_t-20))
        	{PWM=1;}
        	else
        	{PWM=0;}			
			if(time_count<PWM_t)
        	{PWM2=1;}
        	else
        	{PWM2=0;}
		}
		if(kind==2)						//��ߵڶ�����������⵽����
        {	
			if(time_count<3)
        	{PWM=1;}
        	else
        	{PWM=0;}			
			if(time_count<PWM_t)
        	{PWM2=1;}
        	else
        	{PWM2=0;}
		}
		if(kind==3)						//�ұߵ�һ����������⵽����
        {	
			if(time_count<(PWM_t-20))
        	{PWM2=1;}
        	else
        	{PWM2=0;}			
			if(time_count<PWM_t)
        	{PWM=1;}
        	else
        	{PWM=0;}
		}
		if(kind==4)						//�ұߵڶ�����������⵽����
        {	
			if(time_count<3)
        	{PWM2=1;}
        	else
        	{PWM2=0;}			
			if(time_count<PWM_t)
        	{PWM=1;}
        	else
        	{PWM=0;}
		}
	}
		if(flag==2)						//С������,flag=2,С�����˱�־
	{
		ENA=1;
		PWM=0;
		PWM2=0;
		if(kind==0)						//û�д�������⵽����,��ֱ��
	    {	if(time_count<PWM_t)
	        	{DR=1;DR2=1;}
	        	else
	        	{DR=0;DR2=0;}
		}
		if(kind==1)						//��ߵ�һ����������⵽����
	    {	
			if(time_count<(PWM_t-20))
	        {DR=1;}
	        else
	        {DR=0;}			
			if(time_count<PWM_t)
	        {DR2=1;}
	        else
	        {DR2=0;}
		}
		if(kind==2)						//��ߵڶ�����������⵽����
	    {	
			if(time_count<3)
	        {DR=1;}
	        else
	        {DR=0;}			
			if(time_count<PWM_t)
	        {DR2=1;}
	        else
	        {DR2=0;}
		}
		if(kind==3)				   		//�ұߵ�һ����������⵽����
	    {	
			if(time_count<(PWM_t-20))
	        {DR2=1;}
	        else
	        {DR2=0;}			
			if(time_count<PWM_t)
	        {DR=1;}
	        else
	        {DR=0;}
		}
		if(kind==4)				  		//�ұߵڶ�����������⵽����
	    {	
			if(time_count<3)
	        {DR2=1;}
	        else
	        {DR2=0;}			
			if(time_count<PWM_t)
	        {DR=1;}
	        else
	        {DR=0;}
		}
	}
      if(time_count >= PWM_T)		  	//ÿ���һ��PWM����������һ����,Ҳ��PWM�����ڳ���
        {
         time_count=0;
        }
}

