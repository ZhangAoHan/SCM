/*************************************************************************
*实例名称：频率计
*实例说明：实现0~9000hz频率计的统计
*作者：yd
*时间：09.06.20
*************************************************************************/
#include "target.h"
#include "led.h"
uchar displayBuff[4]={'0','0','0','0'}; //数码管显示缓冲区,千,百,十,个
const uchar displayMode=0x00;           //后四位分别对应缓冲区中每位的数据类型,1为任意字符显示,0为数字显示
void main()
{
  uint get_fre;
  target_init();
  init_led();
  sei();
  while(1)
  {
    get_fre=get_fre_number();
	if(get_fre/1000<0x0A)
	{
	  displayBuff[0]=get_fre/1000+'0';            //计算频率千位,放在缓冲区第0位
	}
	displayBuff[1]=(get_fre/100)%10+'0';          //计算频率百位,放在缓冲区第1位
    displayBuff[2]=(get_fre%100)/10+'0';          //计算频率十位,放在缓冲区第2位
	displayBuff[3]=get_fre%10+'0';		          //计算频率个位,放在缓冲区第3位
    ledSweepDisplay(displayBuff,displayMode,0x04);//循环显示数码管缓冲区中数据
  }

}