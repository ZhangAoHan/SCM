#include "led.h"
#include "key.h"
#include "pwm.h"
static uchar pwmScale;   //pwm占空比,1~99
void main()
{
  uchar keyValue;
  pwm_init();  //初始化pwm,pwm高电平默认值为1
  key_init();
  led_init();
  pwmScale=0x01; //初始化占空比变量，初始值为1
  sei();
  while(1)
  {
    keyValue=get_key_value();
	if(keyValue!=KEY_NULL)
	{
	  if(keyValue==KEY_UP)
	   {
	     if(pwmScale<99)
		   pwmScale++;
	   }
	  if(keyValue==KEY_DOWN)
	   {
	     if(pwmScale>1)
		   pwmScale--;
	   }
	  pwm_set(pwmScale);
      ledWrite(pwmScale%10+'0',0x01,DIGITAL);  //显示占空比个位
	  ledWrite(pwmScale/10+'0',0x02,DIGITAL);  //显示占空比十位
	}
  }
}