/***********************************************
*实例名称:电子密码锁
*实例说明:实现五位密码的设置和解锁
*作者:yd
*时间:09.06.17
***********************************************/
#include "target.h"
uchar setPassword[5]={0x01,0x02,0x03,0x04,0x05};  //原始密码12345
uchar passwordCount;
uchar inputPassword[5]={0x00,0x00,0x00,0x00,0x00};
uchar displayFramCount;	 //显示界面序号,0x01~0x05
void main()
{
  uchar  i;
  uchar  keyValueRead;
  uchar  framTwoLine;  //第二个界面中记录选择项所在行数
  target_init();
  displayFramCount=0x01;
  passwordCount=0x00;
  framTwoLine=0x01;   //第二界面中显示第一行
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
	displayFramCount|=0x80;  //displayFramCount最高位置1表示界面已显示
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
	  case KEY_TRUE: //确认键
	   {
	     if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //设置界面进入输密码界面
		 {
		   displayFramCount=0x03;  //解密或者输密码时都要进入输密码界面
		 }
		 if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x03))  //输入密码确认
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
		 if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x04))  //设置密码确认
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
	  case KEY_CLEAR:    //返回主界面键
	   {
	     displayFramCount=0x01;
		 passwordCount=0x00;
	     break;
	   }
	  case KEY_SET:	    //由主界面进入参数设置界面
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
	     if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //设置界面中上移选择行
		 {
		     framTwoLine=0x01;
			 displayFramCount=0x02;     
		 }
	     break; 
	   }
	  case KEY_DOWN:
	   {
	    if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x02)) //设置界面中上移选择行
		{
		   framTwoLine=0x02;
		   displayFramCount=0x02;
		}
	     break;
	   }
	}
   if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x03))  //输密码界面，此时显示****
   {
     displayMima(inputPassword,passwordCount,0x01);
   }
   if((displayFramCount&0x80)&&((displayFramCount&0x7f)==0x04))  //设置密码界面，此时显示设置的密码
   {
     displayMima(inputPassword,passwordCount,0x02);
   }
  }
}