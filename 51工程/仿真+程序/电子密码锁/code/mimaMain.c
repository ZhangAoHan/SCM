/***********************************************
*ʵ������:����������
*ʵ��˵��:ʵ����λ��������úͽ���
*����:yd
*ʱ��:09.06.17
***********************************************/
#include "target.h"
uchar setPassword[5]={0x01,0x02,0x03,0x04,0x05};  //ԭʼ����12345
uchar passwordCount;
uchar inputPassword[5]={0x00,0x00,0x00,0x00,0x00};
uchar displayFramCount;	 //��ʾ�������,0x01~0x05
void main()
{
  uchar  i;
  uchar  keyValueRead;
  uchar  framTwoLine;  //�ڶ��������м�¼ѡ������������
  target_init();
  displayFramCount=0x01;
  passwordCount=0x00;
  framTwoLine=0x01;   //�ڶ���������ʾ��һ��
  while(1)
  {
    switch(displayFramCount)
	{
	  case 0x01:
	  {
	    displayFramOne();
	   	break;
	  }
	  case 0x02:
	  {
	    if(framTwoLine==0x01)
	      displayFramTwo(0);
		else
		  displayFramTwo(1);
	    break;
	  }
	  case 0x03:
	  {
	    displayFramThree();
	    break;
	  }
	  case 0x04:
	  {
	    displayFramFour();
	    break;
	  }
	  case 0x05:
	  {
	    displayFramFive();
	   	break;
	  }
	  default: break;
	}
	displayFramCount|=0x80;  //displayFramCount���λ��1��ʾ��������ʾ
	keyValueRead=get_key_value();
    switch(keyValueRead)
	{
	  case KEY_ONE:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x01;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_TWO:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x02;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_THREE:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x03;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_FOUR:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x04;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_FIVE:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x05;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_SIX:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x06;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_SEVEN:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x07;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_EIGHT:
	   {
	     if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x08;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_NINE:
	   {
	    if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x09;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_ZERO:
	   {
	    if((displayFramCount&0x80)&&(((displayFramCount&0x7f)==0x03)||((displayFramCount&0x7f)==0x04)))
		 {
		   if(passwordCount<0x05)
		   {
		     inputPassword[passwordCount]=0x00;
			 passwordCount++;
		   }
		 }
	     break;
	   }
	  case KEY_TRUE: //ȷ�ϼ�
	   {
	     if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //���ý���������������
		 {
		   displayFramCount=0x03;  //���ܻ���������ʱ��Ҫ�������������
		 }
		 if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x03))  //��������ȷ��
		 {
		   if(passwordCount==0x05)
		   {
		     for(i=0;i<5;i++)
			 {
			   if(framTwoLine==0x01)
			   {
			     displayFramCount=0x05;
			   }
			   else 
			   {
			     if(framTwoLine==0x02)
				 {
				   displayFramCount=0x04;
				 }
			   }
			   
			   if(inputPassword[i]!=setPassword[i])
			   {
			     displayFramCount=0x01;
				 break; 
			   }
			 }
			 passwordCount=0x00;
		   }
		 }
		 if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x04))  //��������ȷ��
		 {
		   if(passwordCount==0x05)
		   for(i=0;i<5;i++)
		   {
		    setPassword[i]=inputPassword[i];
		   }
		   displayFramCount=0x01;
		 }
		 break;
	   }
	  case KEY_CLEAR:    //�����������
	   {
	     displayFramCount=0x01;
		 passwordCount=0x00;
	     break;
	   }
	  case KEY_SET:	    //�����������������ý���
	   {
	     if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x01))
		 {
		   displayFramCount=0x02;
		 }
		 passwordCount=0x00; 
	     break;
	   }
	  case KEY_UP:
	   {
	     if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //���ý���������ѡ����
		 {
		     framTwoLine=0x01;
			 displayFramCount=0x02;     
		 }
	     break; 
	   }
	  case KEY_DOWN:
	   {
	    if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //���ý���������ѡ����
		{
		   framTwoLine=0x02;
		   displayFramCount=0x02;
		}
	     break;
	   }
	}
   if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x03))  //��������棬��ʱ��ʾ****
   {
     displayMima(inputPassword,passwordCount,0x01);
   }
   if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x04))  //����������棬��ʱ��ʾ���õ�����
   {
     displayMima(inputPassword,passwordCount,0x02);
   }
  }
}