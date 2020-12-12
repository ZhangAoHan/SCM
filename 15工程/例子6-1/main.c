#include "stdio.h"               //预处理命令，调用库函数
#include "reg51.h"               //预处理命令，调用库函数
int max(int a, int b)            //定义max函数，a，b为形式参数
{                                //{ }为函数的边界
	if(a>b)                        //如果a大于b条件成立
		return a;                    //将a作为返回值返回到主程序调用处
	else                           //否则，a小于等于b条件成立
		return b;                    //将b作为返回值返回到主程序调用处
}
main()                           //主函数
{
 int i,j,k,l;                    //声明数据类型i,j,k
 SCON= 0x52;                     /*8051单片机串口初始化*/
 TMOD = 0x20;   
 TCON = 0x69;    
 TH1 = 0xF3;     
 scanf("%d %d",&i,&j);           //输入变量i和j的值
 l=i+j;                          //变量i和变量j的值求和，送给l
 k=max(i,j);                     //调用max函数，求取最大值k
 printf("i + j =%d\n",l);        //输出l的值
 printf("max value is %d\n",k);  //打印k的值
 while(1);                       //无限循环
}                                //程序结束