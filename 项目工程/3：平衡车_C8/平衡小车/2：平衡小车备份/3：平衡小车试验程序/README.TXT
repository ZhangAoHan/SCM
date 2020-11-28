平衡小车实验步骤：
1：控制电机，输出PWM
2：加直立环、速度环，能达到稳定的效果
3：蓝牙简单遥控
4：加转向环，能转向
5：OLED屏显示
6：进一步优化
7：能原地转圈




/*OLED显示函数例程*/
void OLED_Display_Speed(int x,int y)
{
	OLED_ShowChar(0,0,'a',16);  // x*y 8=6*8  16=8*16   y=y*8
	OLED_ShowNum(8,2,10,2,16);
	OLED_ShowString(16,4,"my",16);
	OLED_ShowCHinese(24,6,3); 
	OLED_ShowString(0,0,"L",16);
	OLED_ShowChar(8,0,':',16);
	OLED_ShowNum(16,0,x,14,16);
	
	OLED_ShowString(0,2,"R",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,y,14,16);
	
}
void OLED_Display(int x,int y)
{
	OLED_ShowCHinese(0,0,14);
	OLED_ShowCHinese(16,0,15);
	OLED_ShowCHinese(32,0,16);
	OLED_ShowChar(120,0,' ',16);
	
	OLED_ShowString(0,2,"L",16);
	OLED_ShowChar(8,2,':',16);
	OLED_ShowNum(16,2,x,6,16);
	
	OLED_ShowString(64,2,"R",16);
	OLED_ShowChar(72,2,':',16);
	OLED_ShowNum(80,2,y,6,16);
}