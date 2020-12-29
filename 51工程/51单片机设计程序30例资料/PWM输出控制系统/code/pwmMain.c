#include "led.h"
#include "key.h"
#include "pwm.h"
static uchar pwmScale;   //pwmռ�ձ�,1~99
void main()
{
  uchar keyValue;
  pwm_init();  //��ʼ��pwm,pwm�ߵ�ƽĬ��ֵΪ1
  key_init();
  led_init();
  pwmScale=0x01; //��ʼ��ռ�ձȱ�������ʼֵΪ1
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
      ledWrite(pwmScale%10+'0',0x01,DIGITAL);  //��ʾռ�ձȸ�λ
	  ledWrite(pwmScale/10+'0',0x02,DIGITAL);  //��ʾռ�ձ�ʮλ
	}
  }
}