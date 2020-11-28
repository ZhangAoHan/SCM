/*************************************************
*实例名称：音乐播放器
*实例功能：通过分解存储音乐节拍数组中的信息,实现音
乐的方波
*作者：yd
*时间：09.06.20
*************************************************/
#include "music.h"
#include "musicCode.h"
void main()
{
  InitialPlayer();	 //播放器初始化
  sei();             //开总中断
  while(1)
  {
	Play(Music_Girl,0,3,360);  //播放第一首歌
	Delay1ms(500);
	Play(Music_Same,0,3,360);  //播放第二首歌
	Delay1ms(500);
	Play(Music_Two,0,3,360);   //播放第二首歌
	Delay1ms(500);
  }
}