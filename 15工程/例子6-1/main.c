#include "stdio.h"               //Ԥ����������ÿ⺯��
#include "reg51.h"               //Ԥ����������ÿ⺯��
int max(int a, int b)            //����max������a��bΪ��ʽ����
{                                //{ }Ϊ�����ı߽�
	if(a>b)                        //���a����b��������
		return a;                    //��a��Ϊ����ֵ���ص���������ô�
	else                           //����aС�ڵ���b��������
		return b;                    //��b��Ϊ����ֵ���ص���������ô�
}
main()                           //������
{
 int i,j,k,l;                    //������������i,j,k
 SCON= 0x52;                     /*8051��Ƭ�����ڳ�ʼ��*/
 TMOD = 0x20;   
 TCON = 0x69;    
 TH1 = 0xF3;     
 scanf("%d %d",&i,&j);           //�������i��j��ֵ
 l=i+j;                          //����i�ͱ���j��ֵ��ͣ��͸�l
 k=max(i,j);                     //����max��������ȡ���ֵk
 printf("i + j =%d\n",l);        //���l��ֵ
 printf("max value is %d\n",k);  //��ӡk��ֵ
 while(1);                       //����ѭ��
}                                //�������