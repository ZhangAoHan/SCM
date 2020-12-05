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
using System.Runtime.InteropServices;
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            
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
                    btl.Enabled = true;
                    sjwh.Enabled = true;
                    xyw.Enabled = true;
                    tzw.Enabled = true;
                    // cmbStreamCtrl.Enabled = true;
                }
                catch                              //如果打开串口失败
                {
                    MessageBox.Show("串口关闭失败\n请断开所有端口", "关闭失败", MessageBoxButtons.OK);
                }
            }
        }

        //接收下位机发送的数据
        public delegate void RevData(string dataRe);  //创建委托
        public delegate void RevPram(byte[] buffer);

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收事件
        {
            
            string dataRe;
            string pramRe;
            byte[] byteRead = new byte[serialPort.BytesToRead];   //BytesToRead获取接收缓冲区中数据的字节数。
            RevData receivedata = new RevData(UpdateTextbox);    //实例化委托
            serialPort.Read(byteRead, 0, byteRead.Length);         //串口缓冲区存入数组中
            pramRe = System.Text.Encoding.Default.GetString(byteRead);
            
            dataRe = System.Text.Encoding.Default.GetString(byteRead);
 

            textBox2.Invoke(receivedata, dataRe);
            
            
        }                        
        /*更新串口发来的数据
       --------------------------------------------------------*/
        private void UpdateTextbox(string dataRe)               //显示串口
        {
            if (this.textBox2.Text.Length > 250)              //刷新窗口
                this.textBox2.Text = "";
            this.textBox2.Text += dataRe;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    label1.Text = "已发送 ：1";
                    textBox1.Text = "1";
                    serialPort.WriteLine(textBox1.Text);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送失败", "Error");
                }
            }
            else
            {
                MessageBox.Show("发送失败","错误提示");
                return;
            }
            textBox1.Text = " ";
           // label1.Text = "已发送 ：01";
           // textBox1.Text = "01";
           // if (textBox1.Text == "")
           // {
              //  MessageBox.Show("发生失败，请重新发送数据", "Error");
           // }
           // else
           // {
              //  serialPort.WriteLine(textBox1.Text);
                //serialPort.Write(textBox1.Text);
           // }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    label1.Text = "已发送 ：0";
                    textBox1.Text = "0";
                    serialPort.WriteLine(textBox1.Text);
                }
                catch (Exception)
                {
                    MessageBox.Show("发送失败", "Error");
                }
            }
            else
            {
                MessageBox.Show("发送失败", "错误提示");
                return;
            }
            textBox1.Text = " ";
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            string dataRe;
            string pramRe;
            byte[] byteRead = new byte[serialPort.BytesToRead];   //BytesToRead获取接收缓冲区中数据的字节数。
            RevData receivedata = new RevData(UpdateTextbox);    //实例化委托
            serialPort.Read(byteRead, 0, byteRead.Length);         //串口缓冲区存入数组中
            pramRe = System.Text.Encoding.Default.GetString(byteRead);

            dataRe = System.Text.Encoding.Default.GetString(byteRead);
            textBox2.Invoke(receivedata, dataRe);
        }

        private void button4_Click(object sender, EventArgs e)
        {
  
        }
    }
}
