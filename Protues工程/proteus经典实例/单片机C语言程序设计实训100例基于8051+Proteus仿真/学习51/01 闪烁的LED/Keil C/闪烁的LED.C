/****************************************/
/*程序名称：点亮一个P1。0口的发光管*/
/*说   明 ：利用软件延时500ms*/
/*操作类型：位操作                */
/*作者    ：铁手一郎
/*QQ:347999853               */
/***************************************/
#include<reg52.h>
#define uint unsigned int    //宏定义
#define uchar unsigned char  //宏定义
sbit led=P1^0; /*定义P1.0*/
sbit led1=P1^1;/*定义P1.1*/

main()
   
{  
   uint a;
   while(1)
	{   a=50000;
	 	led=0;    /*点亮发光管*/
        while(a--);
		a=50000;
		led=1;
		while(a--);
}

}
