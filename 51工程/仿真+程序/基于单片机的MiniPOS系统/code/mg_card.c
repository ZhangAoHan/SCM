/*******************************************************************************
* �ļ����ƣ�mg_card.c	                        
* ˵�������ļ�Ϊ���п���������
* ���ܣ�ʵ�ֶ����п���ʶ��
* �޸ģ���
* �汾��1.0.0
* ���ߣ�YuanDong
* ʱ�䣺2009.7.26
*******************************************************************************/	
#include <51reg.h>
#include <string.h>
#include <stdio.h>      /*��׼�����������*/


#define	FORWARD	     0x01			//�ſ�����ˢ��
#define	BACK		   	 0x02			//�ſ�����ˢ��
#define	NO_TRACK2		 0x04			//����2�����
#define NO_TRACK3		 0x08			//����3�����

#define  OK			     0x05
#define  STATE		   0x00

#define  SIZE1_DATA_TRK2       	300		//��2ԭʼ����BIT���ȣ�Э�����300
#define  SIZE2_DATA_TRK3       	1000	//��3ԭʼ����BIT���ȣ�Э�����1000
#define  SIZE3_CARD_NUM2       	50		//������(��BITλ����׼ת����������ַ�������
#define  SIZE4_CARD_NUM3       	120		//������(��BITλ����׼ת����������ַ�������

sbit B_CLK1=P3^2;  
sbit B_CLK2=P3^3;
sbit B_DATA1=P2^5;
sbit B_DATA2=P2^6;


struct mgcd_dev    //�ſ����ݽṹ��
{
	unsigned char	data_trk2[SIZE1_DATA_TRK2];  //��2 ԭʼ����    ��2�ŵ����ݱ�������¼����Ϊ40���ַ�40*5=200
	unsigned char	data_trk3[SIZE2_DATA_TRK3];  //��3 ԭʼ����    ��3�ŵ����ݱ�������¼����Ϊ107���ַ�107*5=535
  char card_num2[SIZE3_CARD_NUM2];           //��������Ĺ�2���ݴ洢��card_num2[50]
  char card_num3[SIZE4_CARD_NUM3];         //��������Ĺ�3���ݴ洢��card_num3[50]  
  int  track2_num;       		       				//��¼���ǹ�2���ݼ�¼ռ�õĿռ䳤��  (����֮��ĳ���)
	int  track3_num;	      		    				//��¼���ǹ�3���ݼ�¼ռ�õĿռ䳤�ȣ�����֮��ĳ���)
	unsigned char  result_value;    			  //��¼״̬ΪFORWARD ��BACK �� NO_TRACK2 �� NO_TRACK3 
}g_BrushCard;


static char direction_check(void);   
static unsigned char convert_track(void);
static int convert_forward(char *data, int len, int track);
static int convert_back(char *data,int len, int track);
static char ChangeData(char data);
static void ShowTrack2(char *back_track);
static void ShowTrack3(char *back_track);
static char check(char data);

/*****************************************************************************************
*�������ƣ�convert_track(void)
*�������ܣ�ԭʼ���ݴ���
*��ں�������
*���ں�����g_BrushCard->result_value
*****************************************************************************************/
static unsigned char convert_track(void)  //��ԭʼ���ݽ��д��� �˺�������Ҫ��
{
	int i,trk2;
	unsigned char tmp[300];        //���ݴ�ŵ���ʱ����
	memcpy(tmp,g_BrushCard->data_trk2,300);
	char direction;
	direction = direction_check();				 //��ˢ����������ж�
	trk2=g_BrushCard->track2_num;

	if(direction == FORWARD)
	{
		if(g_BrushCard->track2_num = convert_forward((char *)g_BrushCard->data_trk2, g_BrushCard->track2_num,TRACK2))
			goto justice;
		for(i=0 ;i < trk2+1 ; i++)
		{
			memcpy(g_BrushCard->data_trk2+i,tmp+trk2-1-i,sizeof(unsigned char));
		}	

		if(!(g_BrushCard->track2_num = convert_forward((char *)g_BrushCard->data_trk2, trk2,TRACK2)))
				g_BrushCard->result_value |= NO_TRACK2;
		if(!(g_BrushCard->track3_num = convert_forward((char *)g_BrushCard->data_trk3, g_BrushCard->track3_num,TRACK3)))
			g_BrushCard->result_value |= NO_TRACK3;
	}
	else if(direction == BACK)
	{
		if(!(g_BrushCard->track2_num = convert_back((char *)g_BrushCard->data_trk2, g_BrushCard->track2_num,TRACK2)))
			g_BrushCard->result_value |= NO_TRACK2;

		if(!(g_BrushCard->track3_num = convert_back((char *)g_BrushCard->data_trk3, g_BrushCard->track3_num,TRACK3)))
			g_BrushCard->result_value |= NO_TRACK3;
	}
justice:	if((g_BrushCard->track2_num == 0 && g_BrushCard->track3_num == 0)
	|| g_BrushCard->track2_num > 0x28 || g_BrushCard->track2_num < 0x10
	|| g_BrushCard->track3_num > 0x6B || g_BrushCard->track2_num < 0x12)	//��2����16��40 ,��3����18��107 
	{
		g_BrushCard->state = STATE;		//������ϴ��󷵻�

		return 0;
	}
	else							//���������ȷ����
	{
		g_BrushCard->state = OK;
		ShowTrack2(g_BrushCard->card_num2);
    ShowTrack3(g_BrushCard->card_num3);
	}

	g_BrushCard->result_value |= direction;

	return g_BrushCard->result_value;
}

/*****************************************************************************************
*�������ƣ�direction_check(void)
*�������ܣ�ˢ�������б�
*��ں�������
*���ں�����FORWARD
*****************************************************************************************/
static char direction_check(void)  //�˺�������Ҫ��
{    
	int i = 0,num = 0;
	char ascii_data = 0x00; 
	while(1)
	{
		if(g_BrushCard->data_trk2[num] == 0x00)								//ȥ��ǰ���������
		{
			for(i = 0; i < 5;i++)
			{
				if(g_BrushCard->data_trk2[num++] & TRACK2)  					
					ascii_data |= (0x00<<i); 										
				else
					ascii_data |= (0x01<<i);					 					
			}
			if(ascii_data == 0x0b)  											
				return FORWARD;    
			else
			{
				break;
			}
		}
		num++;																		
	}
	
	num = g_BrushCard->track2_num - 1;  				 //��ˢ
	ascii_data=0x00;
	
	while(1)
	{
		if(g_BrushCard->data_trk2[num] == 0x00)		//ȥ��ǰ���������
		{
			for(i = 0;i < 5;i++)
			{
				if(g_BrushCard->data_trk2[num--] & TRACK2)
					ascii_data |= (0x00<<i);
				else
					ascii_data |= (0x01<<i);
			}
			if(ascii_data == 0x0b)
				return BACK;        
			else
			{
				printf("\nRead card number error!\n");
				break;
			}
		}
		num--;
	}
}

/*****************************************************************************************
*�������ƣ�convert_forward(char *data, int len, int track)
*�������ܣ������������
*��ں�����data  len  track
*���ں�����i
*****************************************************************************************/
static int convert_forward(char *data, int len, int track) //����������ϣ�ԭʼ���ݣ����ȣ�����ţ��˺�������Ҫ��
{ 
	int i = 0,now_postion = 0,real_num = 0;
	char *temp;																			   //��¼��ǰָ����ַ�
	char ascii_data = 0x00, tmp_data[107], track_data;
	
	track_data = track;
	temp = data;
	
	while(1)
	{
		if(*temp&track_data)															//ȥ��ǰ���������
		{
			temp ++;
			now_postion ++;
			if(now_postion > len)
				return 0;
		}
		else
		{
			while(ascii_data != 0x1f)												//ǰһ�����ݲ�Ϊ�������ͼ�����ȡ
			{				
				ascii_data = 0x00;

				for(i = 0;i < 5;i++)
				{
					if(*temp & track_data)
						ascii_data |= (0x00<<i);
					else
						ascii_data |= (0x01<<i);

					temp ++;
				}
				if(ascii_data == 0x00)
					break;

				if(check(ascii_data))
					tmp_data[real_num] = ascii_data;
				else
					return 0;

				real_num ++;
			}
			memset(data,0x00,len);
			if(real_num < 0x10)
				return 0;
			i = 0;
			do	{
					*(data + i) = tmp_data[i];
				}while((tmp_data[i++] != 0x1f)&&(i<120));
          
			return i;
		}
	}
}


/*****************************************************************************************
*�������ƣ�convert_back(char *data,int len, int track)
*�������ܣ������������
*��ں�����data  len  track
*���ں�����i
*****************************************************************************************/
static int convert_back(char *data,int len, int track) //����������� �˺�������Ҫ��
{
	int i = 0,now_postion = 0,real_num = 0;
	char *temp;																		      //��¼��ǰָ����ַ�
	char ascii_data = 0x00, tmp_data[107], track_data;

	track_data = track;
	temp = data + len - 1;
	
	while(1)
	{
		if(*temp&track_data)															//ȥ��ǰ���������
		{
			temp --;
			now_postion ++;
			if(now_postion > len)
				return 0;
		}
		else
		{
			while(ascii_data != 0x1f)
			{				
				ascii_data = 0x00;
				for(i = 0; i < 5; i++)
				{
					if(*temp & track_data)
						ascii_data |= (0x00<<i);
					else
						ascii_data |= (0x01<<i);

					temp --;
				}

				if(ascii_data == 0x00)
					break;

				if(check(ascii_data))
					tmp_data[real_num] = ascii_data;
				else
					return 0;

				real_num ++;
			}
			memset(data,0x00,len);

			if(real_num < 0x10)
				return 0;

			i = 0;
			do{
				*(data + i) = tmp_data[i];
			}while((tmp_data[i++] != 0x1f)&&(i<120));

			return i;

		}
	}
}

/*****************************************************************************************
*�������ƣ�ChangeData(char data)
*�������ܣ�����ת��
*��ں�����data  
*���ں�����data
*****************************************************************************************/
static char ChangeData(char data)  //����ת��	
{  
	data &= (~0x10);
	data = data + 0x30;
	return data;
}

/*****************************************************************************************
*�������ƣ�ShowTrack2(char *back_track)
*�������ܣ�����2�м����ݽ������ת��
*��ں�����back_track
*���ں�������
*****************************************************************************************/
static void ShowTrack2(char *back_track)			//���м����ݽ������ת��
{
	int i = 0;
	
	if(g_BrushCard->data_trk2[0] != 0x0b)
		return;

	for(i = 0; i<g_BrushCard->track2_num; i++)	
	{
		*(back_track + i ) = ChangeData(g_BrushCard->data_trk2[i]);
	}

	*(back_track + i) = '\0';  //���ַ����Ľ�����
   
}		
/*****************************************************************************************
*�������ƣ�ShowTrack3(char *back_track)
*�������ܣ�����3�м����ݽ������ת��
*��ں�����back_track
*���ں�������
*****************************************************************************************/	
static void ShowTrack3(char *back_track)
{
 	int i;
	
	if(g_BrushCard->data_trk3[0] != 0x0b)
		return;

	for(i = 0; i<g_BrushCard->track3_num; i++)
	{
		*(back_track + i ) = ChangeData(g_BrushCard->data_trk3[i]);
	}

	*(back_track + i) = '\0';
}
/*****************************************************************************************
*�������ƣ�check(char data)
*�������ܣ������żУ��������ȷ
*��ں�����data  
*���ں�����OK/0
*****************************************************************************************/											
static char check(char data)		//�����żУ��������ȷ 5λΪһ����ϣ���һλУ�����λ
{
	int num = 0,i = 0;
	
	for(i= 0; i < 8; i++)
	{
		if(data&(0x01 << i))
		num ++;
	}

	if(num%2)
		return OK;
	else
		return 0;
}	

/*****************************************************************************************
*�������ƣ�mgcddata_init(void) 
*�������ܣ������ݽṹ���ʼ��
*��ں�������  
*���ں�������
*****************************************************************************************/
static void mgcddata_init(void)  
{
  uint i;
  for(i=0;i<SIZE1_DATA_TRK2;i++)
     	g_BrushCard->data_trk2[i]=0;   //���ԭʼ���ݳ�ʼ��
  for(i=0;i<SIZE1_DATA_TRK3;i++)
     	g_BrushCard->data_trk3[i]=0;   //����ԭʼ���ݳ�ʼ��
  for(i=0;i<SIZE3_CARD_NUM2 ;i++)  	
      g_BrushCard->card_num2[i]=0;   //������ݳ�ʼ��
  for(i=0;i<SIZE3_CARD_NUM2 ;i++)  	
      g_BrushCard->card_num2[i]=0;   //�������ݳ�ʼ��
      
  g_BrushCard->track2_num = 0;
	g_BrushCard->track3_num = 0;
	g_BrushCard->result_value = 0;
	g_BrushCard->state = 0;
            
}
/*****************************************************************************************
*�������ƣ�mgcd_data2()
*�������ܣ����2�����жϴ���
*��ں�������
*���ں�������
*****************************************************************************************/
static mgcd_data2() interrupt 0 using 2  //�ж�0������,ʹ�õڶ���Ĵ���  
{

  EX0=0; //���ж�0
	
	if(g_BrushCard->track2_num < SIZE1_DATA_TRK2)     //��δ����300������
	{ 
		g_BrushCard->data_trk2[g_BrushCard->track2_num++] = B_DATA2;	 //�����ݿڵ����ݶ������ݴ�
	}
  
  EX0=1; //���ж�0
}
/*****************************************************************************************
*�������ƣ�mgcd_data3()
*�������ܣ����3�����жϴ���
*��ں�������
*���ں�������
*****************************************************************************************/
static mgcd_data3() interrupt 2 using 1  //�ж�1������,ʹ�õڶ���Ĵ���  
{

  EX1=0; //���ж�1
	
	if(g_BrushCard->track3_num < SIZE1_DATA_TRK3)     //��δ����1000������
	{ 
		g_BrushCard->data_trk3[g_BrushCard->track3_num++] = B_DATA3;	 //�����ݿڵ����ݶ������ݴ�
	}
  
  EX1=1; //���ж�1
}

/*****************************************************************************************
*�������ƣ�main(void) 
*�������ܣ��˿ڳ�ʼ��
*��ں�������  
*���ں�������
*****************************************************************************************/
void main(void)     
{
	EA=0;   //��CPU�ж�
	 
  B_DATA1=0;
  B_DATA2=0;

  IT0=0;  //��һ�͵�ƽ�����ж�
  EX0=1;  //�ⲿ�ж�0���� 
  
  IT1=0;  //����͵�ƽ�����ж�
  EX1=1;  //�ⲿ�ж�1���� 
 
  mgcddata_init(void);  

  EA=1;   //��CPU�ж�
	return;
}