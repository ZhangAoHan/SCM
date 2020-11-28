 /*************************************************************************/
#define uchar unsigned char
#define uint unsigned int
code uchar ershi1_code[24]={ 
0x05,0x14,0x03,0x18,
0x05,0x14,0x04,0x13,
0x05,0x14,0x05,0x15,
0x06,0x16,0x07,0x16,
0x07,0x16,0x08,0x17,
0x07,0x16,0x06,0x15,}


code uchar ershi2_code[]={}
/**************************************************************************
* ����: void ershi( uchar * clock_time )
* ����: ����BCD���������ݣ� ���BCD��������( 1901 - 2099 )
* ��ڲ���: c_flag:���������ͱ�־  clock_time: ʱ�ӵ�ַ
* ���ڲ���: ��
* ˵��: c_flag = 0 :21���� c_flag = 1 :19���� 
*****************************************************************************/
void  Ershi( uchar * clock_time )
{
  // bit flag_month, flag_year;
   uchar year, month, day, month_point; //���� �� �� ��
   uchar temp1, temp2, temp3;
  // uint calendar_address; //����ũ����ַ
  // uint day_number;
  // uchar clock_moon[3]; //��������


   clock_time += 3; //ָ����
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ����
   clock_time ++; //ָ����
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCDת��ʮ���� 

   temp1=ershi1_code[(month-1)*2+1]      //�ҳ����µڶ�����������С��
   //temp2=(month-1)/4;
   temp2=ershi2_code[year*3+(month-1)/4];     //�ҳ����µĽ�����Ӧ���ֽ�
   temp3=(month-1)%4;
   temp2=temp2<<(temp3*2+1)&0x80;
   temp1=temp1+temp2>>7;                // ��������µڶ�������������
   if(day>=temp1)
    {temp1=month*2-1;}
	else 
	  {
	       temp1=ershi1_code[(month-1)*2];	//�ҳ����µ�һ����������С��
		    temp2=ershi2_code[year*3+(month-1)/4];     //�ҳ����µĽ�����Ӧ���ֽ�
           temp3=(month-1)%4;
           temp2=temp2<<(temp3*2)&0x80;
           temp1=temp1+temp2>>7; 
		   if(day>=temp1)
		     temp1=month*2-2;
			temp1=month*2-3;
		 }
LCD_ERSHI(temp1);
}
