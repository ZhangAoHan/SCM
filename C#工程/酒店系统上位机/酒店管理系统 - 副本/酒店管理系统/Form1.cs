using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace 酒店管理系统
{
    public partial class form : Form
    {
        public class MY
        {
            public static string ti1, ti2, ti3, ti4;
        }
        public form()
        {
            InitializeComponent();
        }

        private void dkck_Click(object sender, EventArgs e)
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

        private void label19_Click(object sender, EventArgs e)
        {

        }

        private void money_Load(object sender, EventArgs e)
        {

            time.Text = DateTime.Now.ToString(); //保证打开时就显示时间
            pictureBox2.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\eba9ac5526bd0305.octet-stream");
        }

        private void 当前时间_Tick(object sender, EventArgs e)
        {
            time.Text = DateTime.Now.ToString();
        }


  
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收事件
        {

            

        }        


        private void money_Click(object sender, EventArgs e)
        {


            if (serialPort.IsOpen)
            {
                if (money1.Text != "")
                {
                    home1money.Text = money1.Text;
                    string send = money1.Text;
                    serialPort.Write("1");
                    serialPort.WriteLine(send);
              
                    money1.Text = "";
                }

                if (money2.Text != "")
                {
                    home2money.Text = money2.Text;
                    string send = money2.Text;
                    serialPort.Write("2");
                    serialPort.WriteLine(send);
        
                    money2.Text = "";
                }

                if (money3.Text != "")
                {
                    home3money.Text = money3.Text;
                    string send = money3.Text;
                    serialPort.Write("3");
                    serialPort.WriteLine(send);
                
                    money3.Text = "";
                }

                if (money4.Text != "")
                {
                    home4money.Text = money4.Text;
                    string send = money4.Text;
                    serialPort.Write("4");
                    serialPort.WriteLine(send);
             
                    money4.Text = "";
                }
                MessageBox.Show("修改完成", "正确提示");
        }
            else
            {
                MessageBox.Show("修改失败,请先打开串口", "错误提示");
            }
}

        private void receivebegin_CheckedChanged(object sender, EventArgs e)
        {



        }
       
 
        private void receivetimer_Tick(object sender, EventArgs e)
        {

 
        }
        //接收下位机发送的数据
        public delegate void RevData(string dataRe);  //创建委托
        private void serialPort_DataReceived_1(object sender, SerialDataReceivedEventArgs e)
        {
            System.Threading.Thread.Sleep(50);
            string dataRe;
            byte[] byteRead = new byte[serialPort.BytesToRead];   //BytesToRead获取接收缓冲区中数据的字节数。
            RevData receivedata = new RevData(UpdateTextbox);    //实例化委托
            serialPort.Read(byteRead, 0, byteRead.Length);         //串口缓冲区存入数组中      
            dataRe = System.Text.Encoding.Default.GetString(byteRead);
            receivebox.Invoke(receivedata, dataRe);  

            if (dataRe == "9")  //串口屏发送数据失败
            {
                MessageBox.Show("串口屏发送数据失败，请重新发送", "错误提示");
            }
            else
                MessageBox.Show("有顾客自主预定房间，请接待", "预房提醒");
        }
        /*更新串口发来的数据
--------------------------------------------------------*/
        private void UpdateTextbox(string dataRe)               //显示串口
        {
            if (this.receivebox.Text.Length > 250)              //刷新窗口
                this.receivebox.Text = "";
            this.receivebox.Text += dataRe;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\标准.jpg");
            if (zt1.Text == "已预约" && yytime1.Text != "")
            {
                yytime.Text = yytime1.Text;
                usetime.Text = MY.ti1;
            }
            else
            {
                yytime.Text = "0";
                usetime.Text = "未预约";
            }
        }

        private void home2_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\标准房1.jpg");
            if (zt2.Text == "已预约" && yytime2.Text != "")
            {
                yytime.Text = yytime2.Text;
                usetime.Text = MY.ti2;
            }
            else
            {
                yytime.Text = "0";
                usetime.Text = "未预约";
            }
        }

        private void home3_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\电脑房.jpg");
            if (zt3.Text == "已预约" && yytime3.Text != "")
            {
                yytime.Text = yytime3.Text;
                usetime.Text = MY.ti3;
            }
            else
            {
                yytime.Text = "0";
                usetime.Text = "未预约";
            }
        }

        private void home4_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(@"D:\单片机学习文档\单片机工程总地址\上位机工程\酒店管理系统上位机\酒店管理系统\酒店客房图片\豪华房.jpg");
            if (zt4.Text == "已预约" && yytime4.Text != "")
            {
                yytime.Text = yytime4.Text;
                usetime.Text = MY.ti4;
            }
            else
            {
                yytime.Text = "0";
                usetime.Text = "未预约";
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
        
            if (zt1.Text == "空")
            {

                if (yytime1.Text != "")
                {
                    if (serialPort.IsOpen)
                    {
                        zt1.Text = "已预约";
                        yytime1.Enabled = false;
                        MY.ti1 = DateTime.Now.ToString();
                        serialPort.WriteLine("51");   //代表1号房已预约                
                        MessageBox.Show("1号房已预约成功并开始计时", "修改完成");
                    }
                }
                else
                    MessageBox.Show("请输入预约时间", "错误提示");
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (zt2.Text == "空")
            {
 
                if (yytime2.Text != "")
                {
                    if (serialPort.IsOpen)
                    {
                        zt2.Text = "已预约";
                        yytime2.Enabled = false;
                        MY.ti2 = DateTime.Now.ToString();
                        serialPort.WriteLine("52");   //代表1号房已预约
                        MessageBox.Show("2号房已预约成功并开始计时", "修改完成");
                    }
                }
                else
                    MessageBox.Show("请输入预约时间", "错误提示");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (zt3.Text == "空")
            {

                if (yytime3.Text != "")
                {
                    if (serialPort.IsOpen)
                    {
                        zt3.Text = "已预约";
                        yytime3.Enabled = false;
                        MY.ti3 = DateTime.Now.ToString();
                        serialPort.WriteLine("53");   //代表1号房已预约
                        MessageBox.Show("3号房已预约成功并开始计时", "修改完成");
                    }
                }
                else
                    MessageBox.Show("请输入预约时间", "错误提示");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (zt4.Text == "空")
            {

                if (yytime4.Text != "")
                {
                    if (serialPort.IsOpen)
                    {
                        zt4.Text = "已预约";
                        yytime4.Enabled = false;
                        MY.ti4 = DateTime.Now.ToString();
                        serialPort.WriteLine("54");   //代表1号房已预约
                        MessageBox.Show("4号房已预约成功并开始计时", "修改完成");
                    }
                }
                else
                    MessageBox.Show("请输入预约时间", "错误提示");
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (zt1.Text == "已预约")
            {
                zt1.Text = "空";
                yytime1.Text = "";
                yytime1.Enabled = true;
                if (serialPort.IsOpen)
                {
                    serialPort.WriteLine("61");   //代表1号房已退房
                    MessageBox.Show("1号房已退房成功", "修改完成");
                }
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (zt2.Text == "已预约")
            {
                zt2.Text = "空";
                yytime2.Text = "";
                yytime2.Enabled = true;
                if (serialPort.IsOpen)
                {
                    serialPort.WriteLine("62");   //代表1号房已退房
                    MessageBox.Show("2号房已退房成功", "修改完成");
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (zt3.Text == "已预约")
            {
                zt3.Text = "空";
                yytime3.Text = "";
                yytime3.Enabled = true;
                if (serialPort.IsOpen)
                {
                    serialPort.WriteLine("63");   //代表1号房已退房
                    MessageBox.Show("3号房已退房成功", "修改完成");
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (zt4.Text == "已预约")
            {
                zt4.Text = "空";
                yytime4.Text = "";
                yytime4.Enabled = true;
                if (serialPort.IsOpen)
                {
                    serialPort.WriteLine("64");   //代表1号房已退房
                    MessageBox.Show("4号房已退房成功", "修改完成");
                }
            }
        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label26_Click(object sender, EventArgs e)
        {

        }

        private void home1usetime_Tick(object sender, EventArgs e)
        {

        }

        private void button9_Click(object sender, EventArgs e)
        {
            receivebox.Text = "";
        }

    }
}
