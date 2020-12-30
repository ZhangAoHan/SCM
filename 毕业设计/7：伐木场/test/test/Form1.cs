using AForge.Video;
using AForge.Video.DirectShow;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;


/* www.cnblogs.com/Brambling/p/6854731.html */


namespace test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private FilterInfoCollection videoDevices;
        private VideoCaptureDevice videoSource;
        public int selectedDeviceIndex = 0;

        public SerialPort ComDevice = new SerialPort();

        public List<SE> db = new List<SE>();
        public List<R> record = new List<R>();
        public bool door_flag;

        string WD ;
        string SD;
        string DJ;
        string FC;
        string XY;
        string HY;
        string USER1;
        string USER2;
        string USER3;
        string MSR;
        int msr_1=0;
        int people;
        int people1;
        //Microsoft.Office.Interop.Excel.Application excel
        public class SE
        {

        }

        public class R
        {

        }

        private void comboBox1_Click(object sender, EventArgs e)  //自动搜索可用串口
        {
            string[] str = SerialPort.GetPortNames();
            ckh.Items.Clear();
            //MessageBox.Show("cnmua", "Error");
            if (str.Count() <= 0)
            {
                MessageBox.Show("本机没有串口！", "Error");
                return;
            }
            foreach (string s in System.IO.Ports.SerialPort.GetPortNames())
            {//获取有多少个COM口  
                ckh.Items.Add(s);
            }

            ckh.SelectedIndex = 0;
        }

        private void btn1_Click(object sender, EventArgs e)
        {

            string COM_Number = this.ckh.Text;
            int BaudRate = Convert.ToInt32(this.btlh.Text);
            int DataBit = Convert.ToInt32(this.sjwh.Text);
            int StopBit = Convert.ToInt32(this.tzwh.Text);

            if (!serialPort1.IsOpen) //如果串口处于关闭状态
            {
                serialPort1.PortName = COM_Number;  //向串口写入配置信息
                serialPort1.BaudRate = BaudRate;
                serialPort1.DataBits = DataBit;
                try                                //尝试打开串口
                {
                    serialPort1.Open();
                    btn1.Text = "关闭串口";   //按下了打开串口按键
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
                    serialPort1.Close();
                    btn1.Text = "打开串口";
                    ckh.Enabled = true; //控件开放交互
                    btldd.Enabled = true;
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



    

        private void Form1_Load(object sender, EventArgs e)
        {

         //   label3.Text = WD;
           // label14.Text = SD;
 
        }
        private void del_btn_Click(object sender, EventArgs e)  //删除接收到的数据
        {
        }





        private void timer1_Tick(object sender, EventArgs e)
        {


            clock.Text = DateTime.Now.ToString();
            label3.Text = WD;
            label14.Text = SD;
            label10.Text = DJ;
            label11.Text = FC;
            label12.Text = XY;
            label13.Text = HY;
            if (people == 1)
            {
                switch (people1)
                {
                    case 1: label23.Text = USER1; label19.Text = "张先生"; label30.Text= DateTime.Now.ToString(); people1 = 0; break;
                    case 2: label23.Text = USER2; label19.Text = "王先生"; label30.Text= DateTime.Now.ToString(); people1 = 0; break;
                    case 3: label23.Text = USER3; label19.Text = "李先生"; label30.Text= DateTime.Now.ToString(); people1 = 0; break;
                }
            }
            else if (people == 2)
            {
                switch (people1)
                {
                    case 1: label24.Text = USER1; label20.Text = "张先生"; label29.Text = DateTime.Now.ToString(); people1 = 0; break;
                    case 2: label24.Text = USER2; label20.Text = "王先生"; label29.Text = DateTime.Now.ToString(); people1 = 0; break;
                    case 3: label24.Text = USER3; label20.Text = "李先生"; label29.Text = DateTime.Now.ToString(); people1 = 0; break;
                }
            }
            else if (people == 3)
            {
                switch (people1)
                {
                    case 1: label25.Text = USER1; label21.Text = "张先生"; label28.Text = DateTime.Now.ToString(); people1 = 0; break;
                    case 2: label25.Text = USER2; label21.Text = "王先生"; label28.Text = DateTime.Now.ToString(); people1 = 0; break;
                    case 3: label25.Text = USER3; label21.Text = "李先生"; label28.Text = DateTime.Now.ToString(); people1 = 0; break;
                }
            }
            if (people > 3) people = 0;


        }

        private void add_btn_Click(object sender, EventArgs e)
        {
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }


        private void button1_Click(object sender, EventArgs e)
        {

            try
            {
   
            videoSource = new VideoCaptureDevice(videoDevices[selectedDeviceIndex].MonikerString);//连接摄像头。

            videoSource.VideoResolution = videoSource.VideoCapabilities[selectedDeviceIndex];
                if ((videoSource.VideoResolution.FrameSize.Width > 458) | (videoSource.VideoResolution.FrameSize.Height > 266))
                {
                    videoSourcePlayer1.Width = 458;
                    videoSourcePlayer1.Height = 266;

                }
                else if ((videoSource.VideoResolution.FrameSize.Width < (458/1.5)) | (videoSource.VideoResolution.FrameSize.Height > (266/1.5)))
                {
                    videoSourcePlayer1.Width = (videoSource.VideoResolution.FrameSize.Width)*2;
                    videoSourcePlayer1.Height = (videoSource.VideoResolution.FrameSize.Height)*2;

                }

                else
                {
                    videoSourcePlayer1.Width = videoSource.VideoResolution.FrameSize.Width;
                    videoSourcePlayer1.Height = videoSource.VideoResolution.FrameSize.Height;

                }

           videoSourcePlayer1.VideoSource = videoSource;
            // set NewFrame event handler
            videoSourcePlayer1.Start();
                button1.Enabled = false;
                button2.Enabled = true;

                comboBox4.Enabled = false;
            }
            catch(Exception)
            {
                MessageBox.Show("没有找到摄像头"+selectedDeviceIndex,"error");
            }


        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {

            selectedDeviceIndex = comboBox4.SelectedIndex;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            videoSource.Stop();
            videoSourcePlayer1.Stop();
            button1.Enabled = true;
            button2.Enabled = false;
            comboBox4.Enabled = true;
        }

        private void comboBox4_Click(object sender, EventArgs e)
        {
            videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
           int i=0;
            
            //selectedDeviceIndex = 0;
            comboBox4.Items.Clear();
            foreach (var videoDevice in videoDevices)
            {
                comboBox4.Items.Add("摄像头"+i);
                i++;
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                videoSourcePlayer1.Stop();
                videoSource.Stop();

            }
            catch (Exception)
            { }

        }


        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void clock_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {



        }

        //接收下位机发送的数据
        public delegate void RevData(string dataRe);  //创建委托
        public delegate void RevPram(byte[] buffer);

        /*更新串口发来的数据
--------------------------------------------------------*/
        private void UpdateTextbox(string dataRe)               //显示串口
        {
         //  if (this.textBox2.Text.Length > 250)              //刷新窗口
             //  this.textBox2.Text = "";
            //this.textBox2.Text += dataRe;
        }

        private void serialPort1_DataReceived_1(object sender, SerialDataReceivedEventArgs e)
        {
              string dataRe=null;
            //  string pramRe;
     
           char[] date = null;
            byte[] byteRead = new byte[serialPort1.BytesToRead];   //BytesToRead获取接收缓冲区中数据的字节数。
          //  RevData receivedata = new RevData(UpdateTextbox);    //实例化委托
            serialPort1.Read(byteRead, 0, byteRead.Length);         //串口缓冲区存入数组中
          //  pramRe = System.Text.Encoding.Default.GetString(byteRead);
            dataRe = System.Text.Encoding.Default.GetString(byteRead);

          
            //  textBox2.Invoke(receivedata, dataRe);
            date = dataRe.ToCharArray();
            //  textBox2.Invoke(receivedata, date);
         
            if (date [0]=='a')   //表示完成一次接收
            {
                WD = null;
                SD = null;
                dataRe = Encoding.Default.GetString(byteRead);
                //textBox2.Text = dataRe;
                string[] split = dataRe.Split(new Char[] { 'a', 'c'});
                //string[] data = dataRe.Split('c');
                // WD = date[0].ToString();
                // SD = date[1].ToString();
                WD = split[1];
                SD = split[2];
                //  label10.Text= split[3];
                //   label11.Text = split[4];
                //   label12.Text = split[5];
                ///   label13.Text = split[6];
                //   label23.Text = split[7];
                //   label24.Text = split[8];
                //  label25.Text = split[9];
                split = null;
            }
            if (date[0] == 'b')
            {
                DJ = null;
               dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'b' });
                   DJ= split[1];
                   split = null;
                //  label11.Text = split[2];
                ///  label12.Text = split[3];
                //  label13.Text = split[4];
                //   label23.Text = split[5];
                //   label24.Text = split[6];
                // label25.Text = split[7];
            }
            if (date[0] == 'd')
            {
                FC = null;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'd' });
               FC = split[1];
                split = null;
            }
            if (date[0] == 'e')
            {
                XY= null;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'e' });
                XY = split[1];
                split = null;
            }
            if (date[0] == 'f')
            {
                HY = null;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'f' });
                HY = split[1];
                split = null;
            }
            if (date[0] == 'g')
            {
                USER1 = null;
                people++;
                people1 = 1;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'g' });
                USER1 = split[1];
                split = null;
            }
            else if (date[0] == 'h')
            {
                USER2 = null;
                people++;
                people1 = 2;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'h' });
                USER2 = split[1];
                split = null;
            }
            else if (date[0] == 'i')
            {
                USER3 = null;
                people++;
                people1 = 3;
                dataRe = Encoding.Default.GetString(byteRead);
                string[] split = dataRe.Split(new Char[] { 'i' });
                USER3 = split[1];
                split = null;
            }






        }
    }
}
