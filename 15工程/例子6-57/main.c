#include "stdio.h"
#include "reg51.h"
struct student{
             char name[30];
             char gender;
             int age;
             long int num;
          };
xdata struct student stu[2];
void main()
{
	 int i;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
  for(i=0;i<2;i++)
	 {
		 printf("please input stu[%d].name\n",i);
		 scanf("%s",stu[i].name);
		 getchar();
		 printf("please input stu[%d].gender\n",i);
		 scanf("%c",&stu[i].gender);
		 putchar('\n');
		 printf("please input stu[%d].age\n",i);
		 scanf("%d",&stu[i].age);
		 printf("please input stu[%d].num\n",i);
		 scanf("%ld",&stu[i].num);
	 } 
	 putchar('\n');
	 for(i=0;i<2;i++)
	 {
		 printf("the following students information is:\n");
		 printf("stu[%d].name=%s, ",i,stu[i].name);
		 printf("stu[%d].gender=%c, ",i,stu[i].gender);
		 printf("std[%d].age=%d, ",i,stu[i].age);
		 printf("std[%d].num=%ld, ",i,stu[i].num);
		 putchar('\n');
	 } 
	 while(1);
}