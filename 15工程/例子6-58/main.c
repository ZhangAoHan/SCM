#include "stdio.h"
#include "reg51.h"
struct student{
             char name[30];
             char gender;
             int age;
             long int num;
          };
xdata struct student stu[2],*p;
void main()
{
	 int i;
	SCON= 0x52;
  TMOD = 0x20;
  TCON = 0x69;
  TH1 = 0xF3;
  for(i=0;i<2;i++)
	 {
		 p=&stu[i];
		 printf("please input stu[%d].name\n",i);
		 scanf("%s",p->name);
		 getchar();
		 printf("please input stu[%d].gender\n",i);
		 scanf("%c",&p->gender);
		 putchar('\n');
		 printf("please input stu[%d].age\n",i);
		 scanf("%d",&p->age);
		 printf("please input stu[%d].num\n",i);
		 scanf("%ld",&p->num);
	 } 
	 putchar('\n');
	 for(i=0;i<2;i++)
	 { p=&stu[i];
		 printf("the following students information is:\n");
		 printf("stu[%d].name=%s, ",i,p->name);
		 printf("stu[%d].gender=%c, ",i,p->gender);
		 printf("std[%d].age=%d, ",i,p->age);
		 printf("std[%d].num=%ld, ",i,p->num);
		 putchar('\n');
	 } 
	 while(1);
}