using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            //MessageBox.Show("我会不停的弹出","尝尝我的厉害");
            label2.Text = label2.Text.Substring(1) + label2.Text.Substring(0, 1);
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            SoundPlayer sp=new SoundPlayer();
            sp.SoundLocation = @"D:\单片机学习文档\单片机工程总地址\上位机工程\6：定时器控件\WindowsFormsApplication1\WindowsFormsApplication1\MKJ - Time (铃声).mp3";
            label1.Text = DateTime.Now.ToString();
                        if(DateTime.Now.Hour==15&&DateTime.Now.Minute==51&&DateTime.Now.Second==0)
            {
                sp.Play();  //播放音乐
            }
                                    if(DateTime.Now.Hour==15&&DateTime.Now.Minute==51&&DateTime.Now.Second==10)
            {
                sp.Stop();  //播放音乐
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            

            label1.Text = DateTime.Now.ToString();   //保证窗体打开的时候就显示当前时间
        }

    }
}
