#include "control.h"

u8 set=0;
void use_touch(void)
{
//	u8 i;
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)			//´¥ÃþÆÁ±»°´ÏÂ
	{
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(page==1)
			{
				if(tp_dev.x[0]>5&&tp_dev.x[0]<105&&tp_dev.y[0]>175&&tp_dev.y[0]<200)
				{
					page=0;
					set=0;
				}
			}
		}
	}
}


void use_control(void)
{
	if(page==0)
	{
		use_touch();
		if(set==0)
		{
			LCD_Clear(WHITE);
			delay_ms(50);
			use_1_init_display();
			set=1;
		}
		else
		{
			use_1_data_display();
		}
	}

	
		
	
}

