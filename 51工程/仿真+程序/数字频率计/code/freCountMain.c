/*************************************************************************
*ʵ�����ƣ�Ƶ�ʼ�
*ʵ��˵����ʵ��0~9000hzƵ�ʼƵ�ͳ��
*���ߣ�yd
*ʱ�䣺09.06.20
*************************************************************************/
#include "target.h"
#include "led.h"
uchar displayBuff[4]={'0','0','0','0'}; //�������ʾ������,ǧ,��,ʮ,��
const uchar displayMode=0x00;           //����λ�ֱ��Ӧ��������ÿλ����������,1Ϊ�����ַ���ʾ,0Ϊ������ʾ
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
	  displayBuff[0]=get_fre/1000+'0';            //����Ƶ��ǧλ,���ڻ�������0λ
	}
	displayBuff[1]=(get_fre/100)%10+'0';          //����Ƶ�ʰ�λ,���ڻ�������1λ
    displayBuff[2]=(get_fre%100)/10+'0';          //����Ƶ��ʮλ,���ڻ�������2λ
	displayBuff[3]=get_fre%10+'0';		          //����Ƶ�ʸ�λ,���ڻ�������3λ
    ledSweepDisplay(displayBuff,displayMode,0x04);//ѭ����ʾ����ܻ�����������
  }

}