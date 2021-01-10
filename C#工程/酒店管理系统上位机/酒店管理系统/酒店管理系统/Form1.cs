using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
namespace 酒店管理系统
{
    public partial class 酒店管理系统 : Form
    {
        public 酒店管理系统()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            time.Text = DateTime.Now.ToString(); //保证打开时就显示时间
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void 当前时间_Tick(object sender, EventArgs e)
        {
            time.Text = DateTime.Now.ToString();
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void tabPage2_Click(object sender, EventArgs e)
        {

        }

        private void toolStripContainer1_TopToolStripPanel_Click(object sender, EventArgs e)
        {

        }

        private void home1_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\标准.jpg");
        }

        private void home2_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\标准房1.jpg");
        }

        private void home3_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\电脑房.jpg");
        }

        private void home4_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\豪华房.jpg");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\eba9ac5526bd0305.octet-stream");
        }

        private void time_Click(object sender, EventArgs e)
        {

        }
        /********************************打开串口**********************************
         * *************************************************************************/
        private void button3_Click(object sender, EventArgs e)   //打开串口程序测试正常（需要注意串口号必须正确）
        {
            string COM_Number = this.ckh.Text;
            int BaudRate = Convert.ToInt32(this.btlh.Text);
            int DataBit = Convert.ToInt32(this.sjwh.Text);
            int StopBit = Convert.ToInt32(this.tzwh.Text);

            if (!serialPort.IsOpen) //如果串口处于关闭状态
            {
                serialPort.PortName = COM_Number;  //向串口写入配置信息
                serialPort.BaudRate = BaudRate;
                serialPort.DataBits = DataBit;
                try                                //尝试打开串口
                {
                    serialPort.Open();
                    dkck.Text = "关闭串口";   //按下了打开串口按键
                    ckh.Enabled = false; //控件停止交互
                    btlh.Enabled = false;
                    sjwh.Enabled = false;
                    xywh.Enabled = false;
                    tzwh.Enabled = false;
                }
                catch                              //如果打开串口失败
                {
                    MessageBox.Show("串口打开失败\n请检查串口使用情况", "打开失败", MessageBoxButtons.OK);
                }
            }
            else     //如果串口处于打开状态
            {
                try                                //尝试关闭串口
                {
                    serialPort.Close();
                    dkck.Text = "打开串口";
                    ckh.Enabled = true; //控件开放交互
                    btlh.Enabled = true;
                    sjwh.Enabled = true;
                    xywh.Enabled = true;
                    tzwh.Enabled = true;
                    // cmbStreamCtrl.Enabled = true;
                }
                catch                              //如果打开串口失败
                {
                    MessageBox.Show("串口关闭失败\n请断开所有端口", "关闭失败", MessageBoxButtons.OK);
                }
            }
        }
        /*--------------------------------------------------------
                       接收并处理下位机发来的数据
      --------------------------------------------------------*/
        public delegate void RevData(string dataRe);  //创建委托
        public delegate void RevPram(byte[] buffer);

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收事件
        {
            string pramRe;
            byte[] byteRead = new byte[serialPort.BytesToRead];  //BytesToRead获取接收缓冲区中数据的字节数。
            serialPort.Read(byteRead, 0, byteRead.Length);         //串口缓冲区存入数组中
            pramRe = System.Text.Encoding.Default.GetString(byteRead);

        }
        /**********************************上位机往下位机发送数据****************************
         * *********************************************************************************/
        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Encoding = System.Text.Encoding.GetEncoding("GB2312");
                    serialPort.Write(textBox1.Text);//发送数据
                }
                catch (Exception ex)
                {
                    MessageBox.Show("错误：" + ex.Message);
                }
            }
            else
            {
                MessageBox.Show("请先打开串口！");
            }
            MessageBox.Show("更改价格完成","更改价格");
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
           
            if (serialPort.IsOpen)
            {
                serialPort.Encoding = System.Text.Encoding.GetEncoding("GB2312");
                serialPort.Write(textBox1.Text);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            
            if (serialPort.IsOpen)
            {
                serialPort.Encoding = System.Text.Encoding.GetEncoding("GB2312");
                serialPort.Write(textBoxsend.Text);
                serialPort.WriteLine(textBoxsend.Text);
            }
        }
      
    }
 
}
