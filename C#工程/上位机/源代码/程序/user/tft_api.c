/*---------------------------------------------------------------------------------
	    					STM32 4.3TFT����API v3.1

 ˵��: �������Ǿ����Ĵδ�ĵ������ȶ��汾,�˰汾��ȫ�����֮ǰ�汾��ʾͼ�κ����ֵ�
 	   ʱ���Զ�����������.ϵͳ���ȶ��õ��������ǿ,������3���ֿ�,�ֱ���ASCII�ֿ�
	   16x16���Ҷ����ֿ�,16x16�Զ����ֿ�,�ɹ���ͬ����½���ѡ��,����ʵ��.
	   ��V3.0�濪ʼ����Ӳ����ص��������򵥶�д��TFT_Drive.c�ļ�,��Ӳ���޹ص�Ӧ��
	   ����ӿ�д��TFT_API.c�ļ�,ͬʱ������Ӧ��ͷ�ļ�.ʹ��TFT��ʱ��ֻ��Ҫ��main�ļ�
	   �а���TFT_API.h ����LCD_Init(),LCD_FSMC_Init()�����������ʹ��.
 
 ʱ��: 2013��7��28�� 							BoX��д
 
 �汾: V1.0 ԭ����������,����ͨ��,��API 	    2013-7-27
       V2.0 �İ���������,����API,���ȶ� 		2013-7-28
	   V2.5 �Ľ���Բ�㷨,�����ַ���API,���ȶ� 	2013-8-17
	   V3.0 �Ľ��ȶ���,���Ӵ�С�ֿ���ʾ,�ȶ���  2013-8-18
	   V3.1 Ϊ����ӦUCGUI����ֲ������������ 	2014-2-09
--------------------------------------------------------------------------------*/
#include "tft_api.h"
#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

    /*ѡ����Ҫ���ֿ�*/
// #include "GBK_Large.h" 	//GB2132��׼�����ֿ����6768��������
// #include "GBK_Small.h"	//GBSmall�ֿ����Լ��������ֿ�,С��
 #include "ascii_font.h"	//ASCII�ֿ��ļ�����������ĸ,����

unsigned char LCD_Buffer[LCD_BUFFER_SIZE]; //��ʾ������
/*---------------------------------------------------------
	��������: ��λҺ����
	��������: ��
--------------------------------------------------------*/
void Reset_LCD(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	Software_Delay(0xf);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
}
/*--------------------------------------------------------
 ��    �ܣ�RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
 ��ڲ�����c      BRG ��ɫֵ
 ���ڲ�����RGB ��ɫֵ
 ˵    �����ڲ���������
 ���÷�����
-------------------------------------------------------*/
uint16 BGR_To_RGB(uint16 c)
{
  uint16  r, g, b;
  b = (c>>0)  & 0x1F;
  g = (c>>5)  & 0x3F;
  r = (c>>11) & 0x1F;
  return( (b<<11) + (g<<5) + (r<<0) );
}
/*----------------------------------------------
 ��    �ܣ�ѡ��������
 ��ڲ�����SX����ʼ����,SY����ʼ����,
		   Length����,Wide���,bColor��ɫ
 ����ʾ����LCD_Clear_Select(0,0,480,272,Yellow)
-----------------------------------------------*/
void LCD_Clear_Select(uint16 x,uint16 y,uint16 len,uint16 wide,uint16 bColor)
{                    
    u32 w;
	LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x);
	LCD_WR_Data((len-1)>>8);	    
	LCD_WR_Data((len-1));
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y);
	LCD_WR_Data((wide-1)>>8);	    
	LCD_WR_Data((wide-1));
	LCD_WR_REG(0x002c);
	w= (len-x)*(wide-y);
	while(w--)
	{ 
		LCD_WR_Data(bColor);
	}
} 
/*---------------------
 ��    �ܣ�ȫ������
 ��ڲ�����bColor��ɫ
----------------------*/
void LCD_Clear_All(uint16 bColor)
{                    
    u32 w;
	LCD_WR_REG(0x002A);	
	LCD_WR_Data(0>>8);	    
	LCD_WR_Data(0);
	LCD_WR_Data(479>>8);	    
	LCD_WR_Data(479);
    LCD_WR_REG(0x002B);	
	LCD_WR_Data(0>>8);	    
	LCD_WR_Data(0);
	LCD_WR_Data(272>>8);	    
	LCD_WR_Data(272);
	LCD_WR_REG(0x002C);
	w= 480*272;
	while(w--)
	{ 
		LCD_WR_Data(bColor);
	}
}   
/*-------------------------------------------------------
 �������ܣ���ָ�����껮��
 ��ڲ�����(X0,Y0)���������,(X1,Y1)���յ�����,color��ɫ
--------------------------------------------------------*/ 
void Draw_Point(uint16 x,uint16 y,uint16 Color)
{								       
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    //��ʼ��ַX
	LCD_WR_Data(x);	    			
	LCD_WR_Data((x+1)>>8);	//������ַX
	LCD_WR_Data(x);	    			    
    LCD_WR_REG(0x002B);	
	LCD_WR_Data(y>>8);	    //��ʼ��ַY
	LCD_WR_Data(y);	    			    
	LCD_WR_Data((y)>>8);	//������ַY
	LCD_WR_Data(y);	    			
	LCD_WR_REG(0x2C);
	LCD_WR_Data(Color); 	   	
} 
/*-------------------------------------------------------
 �������ܣ���ȡָ������ɫ
 ��ڲ�����(X,Y)������
 ��дʱ��: 2014-2-9
--------------------------------------------------------*/ 
uint16 Get_Point(uint16 x,uint16 y)
{								       
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002A;
	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002b; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002e; 
	
	return LCD_RD_data();	   	
}
/*-------------------------------------------------------
 �������ܣ���������
 ��ڲ�����(X,Y)������
 ��дʱ��: 2014-2-9
--------------------------------------------------------*/
void Set_Cursor(uint16 x,uint16 y)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002A;
  	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
  	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
  	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002b; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
} 
/*-------------------------------------------------------
 �������ܣ���ָ�����껮��
 ��ڲ�����(X0,Y0)���������,(X1,Y1)���յ�����,color��ɫ
--------------------------------------------------------*/
void Draw_Line(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 color)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int PointX = 0,PointY = 0;
	int incx = 0,incy = 0;
	int distance = 0,xerr = 0,yerr = 0;
	unsigned int i = 0;
	if(dx == 0)		//k=1б��Ϊ1
	{
		PointX = X0;
		if(Y0 < Y1)
		{
			PointY = Y0;
		}
		else
		{
			PointY = Y1;
		}
		for(i = 0;i <= ((Y0<Y1) ? (Y1-Y0) : (Y0-Y1));i++)
		{
		    Draw_Point(PointX,PointY,color);
			PointY++;
		}
		return;
	}
	if(dy == 0)		//k=0б��Ϊ0
	{
		PointY = Y0;
		if(X0 < X1)
			PointX = X0;
		else
			PointX = X1;
		for(i = 0;i <= ((X0<X1) ? (X1-X0) : (X0-X1));i++)
		{
			Draw_Point(PointX,PointY,color);
			PointX++;
		}
		return;
	}
	if(dx > 0)
		incx = 1;
	else if(dx == 0)
		incx = 0;
	else
		incx = -1;

	if(dy > 0)
		incy = 1;
	else if(dy == 0)
		incy = 0;
	else
		incy = -1;

    dx = ((X0>X1) ? (X0-X1) : (X1-X0));
    dy = ((Y0>Y1) ? (Y0-Y1) : (Y1-Y0));

    if(dx>dy) 
		distance=dx;
    else 
		distance=dy;

    PointX = X0;
    PointY = Y0;
    for(i=0;i<=distance+1;i++)
    {
    	Draw_Point(PointX,PointY,color);
        xerr += dx;
        yerr += dy;
        if(xerr>distance)
        {
            xerr -= distance;
            PointX += incx;
        }
        if(yerr>distance)
        {
            yerr -= distance;
            PointY += incy;
        }
    }
}
/*-------------------------------------------------------
 �������ܣ���ָ�����껭ˮƽ����
 ��ڲ�����(X0,Y0)���������,(X1,Y1)���յ�����,color��ɫ,���߼��distance
--------------------------------------------------------*/
void Draw_DottedHLine(u16 X0,u16 Y0,u16 X1,u16 Y1,u16 color,u16 Distance)
{
	u16 _dis,div,i,starx,endx;
	if(Y0 == Y1)
	{
		_dis = ((X0>X1) ? (X0-X1) : (X1-X0)); 
		div = _dis / Distance;
		starx = X0;
		endx  = X0 + Distance;
		for(i=0; i<div; i++)
		{
		 	Draw_Line(starx,Y0,endx,Y0,color);
			starx = endx;
			endx += Distance;
		}	
	}			
}
/*-------------------------------------------------------
 �������ܣ���ָ�����껮��ֱ����
 ��ڲ�����(X0,Y0)���������,(X1,Y1)���յ�����,color��ɫ,���߼��distance
--------------------------------------------------------*/
void Draw_DottedVLine(u16 X0,u16 Y0,u16 X1,u16 Y1,u16 color,u16 Distance)
{
	u16 _dis,div,i,stary,endy;
	if(X0 == X1)
	{
		_dis = ((Y0>Y1) ? (Y0-Y1) : (Y1-Y0)); 
		div = _dis / Distance;
		stary = Y0;
		endy  = Y0 + Distance;
		for(i=0; i<div; i++)
		{
		 	Draw_Line(X0,stary,X0,endy,color);
			stary = endy;
			endy += Distance;
		}	
	}			
}
/*------------------------------------
              ���ƾ��ο�
������������ε���ʼλ��left,top 
          ���εĽ���λ��right,bottom 
 		  ���ο����ɫ  color
------------------------------------*/
void Draw_Rectangle( uint16 left,uint16 top,uint16 right,uint16 bottom,uint32 color)
{
	Draw_Line(left,top,right,top,color);
	Draw_Line(left,top,left,bottom,color);
	Draw_Line(right,top,right,bottom,color);
	Draw_Line(left,bottom,right,bottom,color);
}
/*--------------------------------------
 ��������: ����SIN����
 ��������: y=Asin(wx+cx)  w=2pi/T,ƫ����py
 ����ʾ��: Draw_Sin(40,130,0,100,Yellow)
---------------------------------------*/
void Draw_Sin(uint16 A,uint16 T,uint16 cx,uint16 py,unsigned int color)
{	
	float PI_2 = 6.2832;
	float y;
	unsigned int x;
	for(x=0;x<=480;x++)
	{
		y = A*sin((PI_2/T)*x + cx) + py;
		Draw_Point(x,y,color);
	}
}
/*----------------------------------------
 ��������: �Գƴ�㷨��Բ
 ��������: Բ������(x,y)	Բ�İ뾶 r
		   ��ɫ Color       �Ƿ���� fill
 ����ʾ��: Draw_Circle(100,100,50,Green,0) 
----------------------------------------*/
void Draw_Circle(uint16 cx,uint16 cy,uint16 r,uint16 color,uint8 fill)
{
	uint16 x=0,y=r;
	short int delta,temp;
	
	delta = 3-(r<<1);  //3-r*2
	while(y>x)
	{
		if(fill)
		{
			Draw_Line(cx+x,cy+y,cx-x,cy+y,color);
			Draw_Line(cx+x,cy-y,cx-x,cy-y,color);
			Draw_Line(cx+y,cy+x,cx-y,cy+x,color);
			Draw_Line(cx+y,cy-x,cx-y,cy-x,color);
		}
		else
		{
			Draw_Point(cx+x,cy+y,color);
			Draw_Point(cx-x,cy+y,color);
			Draw_Point(cx+x,cy-y,color);
			Draw_Point(cx-x,cy-y,color);
			Draw_Point(cx+y,cy+x,color);
			Draw_Point(cx-y,cy+x,color);
			Draw_Point(cx+y,cy-x,color);
			Draw_Point(cx-y,cy-x,color);
		}
		x++;
		if(delta >= 0)
		{
			y--;
			temp= (x<<2); //x*4
			temp-=(y<<2); //y*4
			delta += (temp+10);
		}
		else
		{
			delta += ((x<<2)+6); //x*4 + 6
		}
	}
}
/*--------------------------------------------------
 ��    �ܣ���ָ��������ʾһ��8x16�����ASCII�ַ�
 ��ڲ�����(x,y)����
           charColor  �ַ�����ɫ
           bColor    �ַ�������ɫ
 ˵    ������Ҫ����ascii_font.hͷ�ļ�����ʹ��
 ����ʾ����LCD_Write_Char(10,10,'a',Green,Black)
---------------------------------------------------*/
#ifdef ASCII_FONT 
void LCD_Write_Char(uint16 x,uint16 y,uint8 ch,uint16 Color,uint16 bColor)
{       
	#define MAX_CHAR_POSX 464
	#define MAX_CHAR_POSY 262
   	uint16 i=0,j=0;
  	uint8 temp_char = 0;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
	
  	for (i=0; i<16; i++)
  	{
	    /* ASCII_8x16�ֿⶨ����ascii_font.h�� */
	    temp_char = ASCII_8x16[ ((ch-0x20)*16)+i ];
	    for (j=0;j<8;j++)
	    {  
		   if ( (temp_char >> 7-j) & 0x01 == 0x01)
		   {
		     Draw_Point(x+j,y+i,Color); // �ַ���ɫ
		   }
	       else
	       {
	         Draw_Point(x+j,y+i,bColor); // ������ɫ
	       }
    	}
  	}
}  	 
/*------------------------------------------------------
 ����  ����ָ�����괦��ʾ16*16��С��ָ����ɫӢ���ַ���
 ����  : 	- x: ��ʾλ�ú�������	 
         	- y: ��ʾλ���������� 
 			- str: ��ʾ��Ӣ���ַ���
 			- Color: �ַ���ɫ   
 			- bColor: ������ɫ		
------------------------------------------------------*/
void LCD_Write_String(uint16 x,uint16 y,const uint8 *p,uint16 Color,uint16 bColor)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX)
		{
			x = 0;
			y += 12;
		}
        if(y>MAX_CHAR_POSY)
		{
			y=x=0;
			LCD_Clear_All(Black);
		}
        LCD_Write_Char(x,y,*p,Color,bColor);
        x += 8;
        p++;
    }  
}
#endif
/*---------------------------------------------
 ��������ʾ���������ַ�
 ����: (x,y)������ʾ����    str: �����ַ�����ַ
        Color: �ַ���ɫ   	bkColor: ������ɫ     
 ������LCD_Char_CH(200,100,"��",0,0);
 ע�⣺����������1�ĺ����ַ�������ʾ����ض�
       ֻ��ʾ��ǰ��һ������
---------------------------------------------*/    
void LCD_Write_Char_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor)
{
    uint8 i,j;
    uint8 buffer[32];
    uint16 tmp_char = 0;
	uint32 pos;

#ifdef LARGE_CHN_LIB	 //ʹ�ô��ֿ��ʱ�����˶�
    pos = Get_GBKChineseCode(str);  /* �����������GBK_Chinese�е���ʼλ�� */
    for(i=0; i<32; i++)
	{
		buffer[i] = GBK_Large[pos];//��pos��ʼ����ȡ��31λ���ݴ���pBuffer��
		pos++;
	} 
#endif 

#ifdef SMALL_CHN_LIB   //ʹ��С�ֿ��ʱ�����˶�
	pos = Get_GBKSmallCode(str);
	for(i=0; i<32; i++)
	{	
		//��ArrayCode[0]��ʼ����ȡ��31λ���ݴ���buffer��
		buffer[i] = GBKSmall[pos].ArrayCode[i];
	} 
#endif
	   
	for (i=0;i<16;i++)	 //����������ӡ����
    {
        tmp_char = buffer[i*2];
        tmp_char = (tmp_char<<8);
        tmp_char |= buffer[2*i+1];
        for (j=0;j<16;j++)
        {
            if ( (tmp_char >> 15-j) & 0x01 == 0x01)
            {
                Draw_Point(x+j,y+i,Color);
            }
            else
            {
                Draw_Point(x+j,y+i,bColor);
            }
        }
    }
}
/*------------------------------------------------------
 ����  ����ָ�����괦��ʾ16*16��С��ָ����ɫ�����ַ���
 ����  : 	- x: ��ʾλ�ú�������	 
         	- y: ��ʾλ���������� 
 			- str: ��ʾ�������ַ���
 			- Color: �ַ���ɫ   
 			- bColor: ������ɫ		
------------------------------------------------------*/    
void LCD_Write_String_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor)  
{
    while(*str != 0)
    {
	    LCD_Write_Char_CH(x,y,str,Color,bColor);      
        str += 2 ;
        x += 16 ;	
    }
}
/*-------------------------------------------------------
 ��������: ��ȡ������GBK_Chinese�е���ʼλ��
 ��������: �ַ�ָ��c
 �� �� ֵ: uint������
 ����ʾ��: POS = Get_GBKChineseCode(str)
--------------------------------------------------------*/
#ifdef LARGE_CHN_LIB   //���ʹ�ô��ֿ������˶�
uint32 Get_GBKChineseCode(const unsigned char *c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    High8bit = *c;     /* ȡ��8λ���� */
    Low8bit  = *(c+1);  /* ȡ��8λ���� */
    
    pos = ((High8bit - 0xB0)*94 + Low8bit - 0xA1)*2*16;  //���������	
    return pos;  
}
#endif
/*-------------------------------------------------------
 ��������: ��ȡ������GBK_Small�е���ʼλ��
 ��������: �ַ�ָ��c
 �� �� ֵ: uint������
 ����ʾ��: POS = Get_GBKSmallCode(str)
--------------------------------------------------------*/ 
#ifdef SMALL_CHN_LIB  //���ʹ��С�ֿ������˶�
uint32 Get_GBKSmallCode(const uint8 chn[2])
{
	unsigned int i;
	for(i=0; i<WORD_NUMBER; i++)	//WORD_NUMBERΪС�ֿ������,������GBK_Small.h��
	{
		if((GBKSmall[i].InnerCode[0]==chn[0]) && (GBKSmall[i].InnerCode[1]==chn[1]))
			return i;  //���ظ��ֵ�λ��
	}
	return 0;
}
#endif
/*-----------------------------------------------------------------
 ��    �ܣ���ָ�����귶Χ��ʾһ��BMPͼƬ
 ��ڲ�����StartX����ʼ����,StartY����ʼ����
 ˵    ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ  ȡģ���img2LCD
 ����ʾ����Draw_Picture(0,0,0,(u16*)demo);
------------------------------------------------------------------*/
void LCD_Write_Bmp(uint16 x,uint16 y,uint16 lenth,uint16 wide,const uint8 *p)
{      
    uint32 size,temp; 
    //�趨һ��ͼƬ��ռ�Ĵ��ڴ�С 
	
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//��ʼ��ַX
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(((uint16)x+lenth-1)>>8);//������ַX
	LCD_WR_Data(((uint16)x+lenth-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//��ʼ��ַY
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+wide-1)>>8);	    	//������ַY
	LCD_WR_Data((y+wide-1)&0x00ff);
	LCD_WR_REG(0x2c);	 
	temp=(uint32)lenth*wide*2;
	for(size=0;size<temp;size++)
		LCD_WR_Data_8(p[size]); 
}  
/*-----------------------------------------------------------------
 ��    �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
 ��ڲ�����StartX����ʼ����,StartY����ʼ����
 ˵    ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ  ȡģ���img2LCD
 ����ʾ����Draw_Picture(0,0,0,(u16*)demo);
------------------------------------------------------------------*/
void Draw_Picture(uint16 x,uint16 y,uint8 *pic)
{
	unsigned int  i=8, len;	//��ͼ������ĵ�8+1λ��ʼ����
	uint16 temp,length,wide;
	length =((uint16)(pic[2]<<8)+pic[3]);	  	//��ͼ��������ȡ��ͼ��ĳ���
	wide   =((uint16)(pic[4]<<8)+pic[5]);	  	//��ͼ��������ȡ��ͼ��ĸ߶�
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//��ʼ��ַX
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(((uint16)x+length-1)>>8);//������ַX
	LCD_WR_Data(((uint16)x+length-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//��ʼ��ַY
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+wide-1)>>8);	    	//������ַY
	LCD_WR_Data((y+wide-1)&0x00ff);
	LCD_WR_REG(0x2c);		
	len=2*((uint16)(pic[2]<<8)+pic[3])*((uint16)(pic[4]<<8)+pic[5]);   //�����ͼ����ռ���ֽ���  
	while(i<(len+8)) 
	{	
		temp=(uint16)( pic[i]<<8)+pic[i+1];	//16λ����,��Ҫһ�η���2���ֽڵ�����
		LCD_WR_Data(temp);							//��ȡ����16λ��������������ʾ��
		i=i+2;										    //ȡģλ�ü�2����Ϊ��ȡ��һ����������
	}
}       
