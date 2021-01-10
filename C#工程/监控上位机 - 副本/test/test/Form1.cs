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
        int Bz = 1;   //定义标志位，用于判断收到的数据类型
        int XH = 0;
        int Sj = 0;
        private FilterInfoCollection videoDevices;
        private VideoCaptureDevice videoSource;
        public int selectedDeviceIndex = 0;

        public SerialPort ComDevice = new SerialPort();

        public List<SE> db = new List<SE>();
        public List<R> record = new List<R>();
        public bool door_flag;

        //Microsoft.Office.Interop.Excel.Application excel
        public class SE
        {
            public string No { get; set; }
            public string Name { get; set; }
            //public int Age { get; set; }
            //public char Sex { get; set; }
            //public string Prof { get; set; }

            //public string Sign { get; set; }

        }

        public class R
        {
            public string Name { get; set; }
            public string Re { get; set; }
            //public int Age { get; set; }
            //public char Sex { get; set; }
            //public string Prof { get; set; }

            //public string Sign { get; set; }

        }

        private void comboBox1_Click(object sender, EventArgs e)  //自动搜索可用串口
        {
            string[] str = SerialPort.GetPortNames();
            comboBox1.Items.Clear();
            //MessageBox.Show("cnmua", "Error");
            if (str.Count() <= 0)
            {
                MessageBox.Show("本机没有串口！", "Error");
                return;
            }
            foreach (string s in System.IO.Ports.SerialPort.GetPortNames())
            {//获取有多少个COM口  
                comboBox1.Items.Add(s);
            }

            comboBox1.SelectedIndex = 0;
        }

        private void btn1_Click(object sender, EventArgs e)
        {
            string[] str = SerialPort.GetPortNames();

            //MessageBox.Show("cnmua", "Error");
            if (str.Count() <= 0)  //检测串口是否存在
            {
                MessageBox.Show("本机没有串口！", "Error");
                return;
            }
            if (ComDevice.IsOpen == false)
            {
                try
                {
                    ComDevice.PortName = comboBox1.SelectedItem.ToString();
                    ComDevice.BaudRate = Convert.ToInt32(comboBox2.SelectedItem.ToString());
                    ComDevice.Parity = Parity.None;
                    ComDevice.DataBits = Convert.ToInt32("8");
                    ComDevice.StopBits = StopBits.One;

                    comboBox1.Enabled = false;
                    comboBox2.Enabled = false;
                    ComDevice.DtrEnable = true;
                    ComDevice.RtsEnable = true;

                    ComDevice.Open();
                    btn1.Text = "关闭串口";
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("Error:" + ex.Message, "Error");
                    //tmSend.Enabled = false;
                    return;
                }

            }
            else
            {

                ComDevice.Close();
                ComDevice.Dispose();
                btn1.Text = "打开串口";
                comboBox1.Enabled = true;
                comboBox2.Enabled = true;

                //tmSend.Enabled = false;

            }





        }


     
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            byte[] byteRead = new byte[ComDevice.BytesToRead];    //BytesToRead:sp1接收的字符个数
            try
            {
                Byte[] receivedData = new Byte[ComDevice.BytesToRead];        //创建接收字节数组
                ComDevice.Read(receivedData, 0, receivedData.Length);         //读取数据
                //string text = sp1.Read();   //Encoding.ASCII.GetString(receivedData);
                ComDevice.DiscardInBuffer();                                  //清空SerialPort控件的Buffer
                //这是用以显示字符串
                    string strRcv = null;
                    for (int i = 0; i < receivedData.Length; i++)
                    {
                        strRcv += ((char)Convert.ToInt32(receivedData[i]));
                    }
                    switch (XH)
                    {
                        case 0: textBox1.Text = null; textBox1.Text = strRcv + "\r\n"; XH = 1; break;
                        case 1: textBox2.Text = null; textBox2.Text = strRcv + "\r\n"; XH = 0; break;
                    }
                   
  //                  if (Bz == 1)
    //                {
   //                     switch (Sj)
 //                       {
   //                         case 1: textBox1.Text += strRcv + "\r\n"; Bz = 0; break;
    //                        case 2: textBox1.Text += strRcv + "\r\n"; Bz = 0; break;
    //                    }
       //             }
        ///            switch (strRcv)
         //           {
         //               case "0xF1": Bz = 1; Sj = 1; textBox1.Text = null; strRcv = null; break;
         //               case "0xF2": Bz = 1; Sj = 2; textBox2.Text = null; strRcv = null; break;
           //         }
     //               switch (XH)
      //              {
       //                 case 0: textBox1.Text = null; textBox1.Text = strRcv + "\r\n"; XH = 1; break;
         //           }

                }
               // string strRcv = null;
                //int decNum = 0;//存储十进制
             //   for (int i = 0; i < receivedData.Length; i++) //窗体显示
              //  {

               //     strRcv += receivedData[i].ToString("X2");  //16进制显示
              //  }

             //   txtReceive.Text += strRcv + "\r\n";
          //  }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "出错提示");
              
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;    //这个类中我们不检查跨线程的调用是否合法(因为.net 2.0以后加强了安全机制,，不允许在winform中直接跨线程访问控件的属性)
            ComDevice.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
            ComDevice.DtrEnable = true;
            ComDevice.RtsEnable = true;
            //设置数据读取超时为1秒
            ComDevice.ReadTimeout = 1000;


            db.Add(new SE() { No = "7C963104", Name = "旺财" });
            db.Add(new SE() { No = "734501CE", Name = "招福" });


            dgv2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgv2.ReadOnly = true;
            dgv2.DataSource = new BindingList<SE>(db);



            dgv2.Columns[0].HeaderCell.Value = "卡号";
            dgv2.Columns[1].HeaderCell.Value = "人员";
            dgv2.Columns[1].Width = 60;
            dgv2.Columns[0].Width = 78;
            dgv2.AllowUserToResizeColumns = false;
            dgv2.AllowUserToResizeRows = false;

            button1.Enabled = true;
            button2.Enabled = false;

        }
        private void del_btn_Click(object sender, EventArgs e)  //删除接收到的数据
        {
            try
            {
                var a = dgv2.CurrentCell.RowIndex;
                SE b = db[a];
                db.RemoveAt(a);

                dgv2.DataSource = new BindingList<SE>(db);
            }
            catch (Exception)
            {
                MessageBox.Show("不能为空！", "error");
            }
        }





        private void timer1_Tick(object sender, EventArgs e)
        {
            clock.Text = DateTime.Now.ToString();
        }

        private void add_btn_Click(object sender, EventArgs e)
        {
            var frm_Add = new Add();
            frm_Add.ShowDialog();
            try
            {
                db.Add(new SE() { No = frm_Add._id, Name = frm_Add._name });
                dgv2.DataSource = new BindingList<SE>(db);
            }
            catch (Exception)
            {
                MessageBox.Show("不能为空！", "error");
            }
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
    }
}
