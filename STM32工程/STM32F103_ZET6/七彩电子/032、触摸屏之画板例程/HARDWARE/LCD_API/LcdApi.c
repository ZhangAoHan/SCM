/*    LcdApi.c   */

/* -----------------------------������ͷ�ļ� ---------------------------------*/

#include "LcdApi.h"
#include "HanziFont.h"
#include "LcdBsp.h"
#include "string.h"





//code �ַ�ָ�뿪ʼ
//���ֿ��в��ҳ���ģ
//code �ַ����Ŀ�ʼ��ַ,GBK��
//mat  ���ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С	
//size:�����С
void Get_HzMat(unsigned char *code,u8* mat,u8 size)
{
	u32 i=0;
	u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
	switch(size)	{
		case 12:
			for (i=0;i<(sizeof(codeGB_12)/sizeof(typFNT_GB12));i++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
				if ((codeGB_12[i].Index[0]==code[0])&&(codeGB_12[i].Index[1]==code[1])){
					memcpy(mat,(u8*)&codeGB_12[i].Msk[0],csize);
					return;
				}
			}
			memset(mat,0,csize);
			break;
		case 16:
			for (i=0;i<(sizeof(codeGB_16)/sizeof(typFNT_GB16));i++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
				if ((codeGB_16[i].Index[0]==code[0])&&(codeGB_16[i].Index[1]==code[1])){
					memcpy(mat,(u8*)&codeGB_16[i].Msk[0],csize);
					return;
				}
			}
			memset(mat,0,csize);
			break;
		case 24:
			for (i=0;i<(sizeof(codeGB_24)/sizeof(typFNT_GB24));i++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
				if ((codeGB_24[i].Index[0]==code[0])&&(codeGB_24[i].Index[1]==code[1])){
					memcpy(mat,(u8*)&codeGB_24[i].Msk[0],csize);
					return;
				}
			}
			memset(mat,0,csize);
			break;
	}
}

//��ʾһ��ָ����С�ĺ���
//x,y :���ֵ�����
//font:����GBK��
//size:�����С
//mode:0,������ʾ,1,������ʾ	   
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{

	u8 temp,t,t1;
	u16 y0=y;
	u8 dzk[72];   
	u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	if(size!=12&&size!=16&&size!=24)return;	//��֧�ֵ�size
	Get_HzMat(font,dzk,size);	//�õ���Ӧ��С�ĵ������� 
	for(t=0;t<csize;t++){	
		temp=dzk[t];			//�õ���������
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR); 
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}
//��ָ��λ�ÿ�ʼ��ʾһ���ַ���	    
//֧���Զ�����
//(x,y):��ʼ����
//width,height:����
//str  :�ַ���
//size :�����С
//mode:0,�ǵ��ӷ�ʽ;1,���ӷ�ʽ    	   		   
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode)
{
	u16 x0=x;
	u16 y0=y;
	u8 bHz=0;     //�ַ���������
	while(*str!=0)//����δ����
	{ 
		if(!bHz){
			if(*str>0x80){
				bHz=1;//���� 
			}
			else  {            //�ַ�
				if(x>(x0+width-size/2)){	//����
					y+=size;
					x=x0;	   
				}							    
				if(y>(y0+height-size)){
					break;//Խ�緵��
				}
				if(*str==13){ //���з���
					y+=size;
					x=x0;
					str++; 
				}  
				else {
					LCD_ShowChar(x,y,*str,size,mode);//��Ч����д��
				}
				str++; 
				x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
			}
		}
		else{ //����
			bHz=0;//�к��ֿ�    
			if(x>(x0+width-size)){//����
				y+=size;
				x=x0;		  
			}
			if(y>(y0+height-size)){
				break;//Խ�緵��
			}
			Show_Font(x,y,str,size,mode); //��ʾ�������,������ʾ 
			str+=2; 
			x+=size;//��һ������ƫ��
		}
	}
}




























