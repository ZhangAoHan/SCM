
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

      //  private FilterInfoCollection videoDevices;
     //   private VideoCaptureDevice videoSource;
     //   public int selectedDeviceIndex = 0;

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

        private void comboBox1_Click(object sender, EventArgs e)
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
            if (str.Count() <= 0)
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

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtReceive.Text = "";       //清空文本
        }

        private void txtSend_KeyPress(object sender, KeyPressEventArgs e)
        {
            //正则匹配
            string patten = "[0-9a-fA-F]|\b|0x|0X| "; //“\b”：退格键
            Regex r = new Regex(patten);
            Match m = r.Match(e.KeyChar.ToString());

            if (m.Success)//&&(txtSend.Text.LastIndexOf(" ") != txtSend.Text.Length-1))
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
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
                //    string strRcv = null;
                //    for (int i = 0; i < receivedData.Length; i++ )
                //    {
                //        strRcv += ((char)Convert.ToInt32(receivedData[i])) ;
                //    }
                //    txtReceive.Text += strRcv + "\r\n";             //显示信息
                //}
                string strRcv = null;
                //int decNum = 0;//存储十进制
                for (int i = 0; i < receivedData.Length; i++) //窗体显示
                {

                    strRcv += receivedData[i].ToString("X2");  //16进制显示
                }

                txtReceive.Text += strRcv + "\r\n";
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "出错提示");
                txtSend.Text = "";
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
            dgv1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgv1.ReadOnly = true;
            dgv1.DataSource = new BindingList<R>(record);


            dgv2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgv2.ReadOnly = true;
            dgv2.DataSource = new BindingList<SE>(db);


            dgv1.Columns[0].HeaderCell.Value = "人员";
            dgv1.Columns[1].HeaderCell.Value = "门禁记录";
            dgv1.Columns[0].Width = 60;
            dgv1.Columns[1].Width = 178;
            dgv1.AllowUserToResizeColumns = false;
            dgv1.AllowUserToResizeRows = false;

            dgv2.Columns[0].HeaderCell.Value = "卡号";
            dgv2.Columns[1].HeaderCell.Value = "人员";
            dgv2.Columns[1].Width = 60;
            dgv2.Columns[0].Width = 78;
            dgv2.AllowUserToResizeColumns = false;
            dgv2.AllowUserToResizeRows = false;

            btn1.Enabled = true;
       //     button2.Enabled = false;

        }

        private void Sendbtn_Click(object sender, EventArgs e)
        {
            String strSend = txtSend.Text;

            //处理数字转换
            string sendBuf = strSend;
            string sendnoNull = sendBuf.Trim();
            string sendNOComma = sendnoNull.Replace(',', ' ');    //去掉英文逗号
            string sendNOComma1 = sendNOComma.Replace('，', ' '); //去掉中文逗号
            string strSendNoComma2 = sendNOComma1.Replace("0x", "");   //去掉0x
            strSendNoComma2.Replace("0X", "");   //去掉0X
            string[] strArray = strSendNoComma2.Split(' ');

            int byteBufferLength = strArray.Length;
            for (int i = 0; i < strArray.Length; i++)
            {
                if (strArray[i] == "")
                {
                    byteBufferLength--;
                }
            }
            // int temp = 0;
            byte[] byteBuffer = new byte[byteBufferLength];
            int ii = 0;
            for (int i = 0; i < strArray.Length; i++)        //对获取的字符做相加运算
            {

                Byte[] bytesOfStr = Encoding.Default.GetBytes(strArray[i]);

                int decNum = 0;
                if (strArray[i] == "")
                {
                    //ii--;     //加上此句是错误的，下面的continue以延缓了一个ii，不与i同步
                    continue;
                }
                else
                {
                    decNum = Convert.ToInt32(strArray[i], 16); //atrArray[i] == 12时，temp == 18 
                }

                try    //防止输错，使其只能输入一个字节的字符
                {
                    byteBuffer[ii] = Convert.ToByte(decNum);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("字节越界，请逐个字节输入！", "Error");
                    return;
                }

                ii++;
            }
            ComDevice.Write(byteBuffer, 0, byteBuffer.Length);
        }

        private void del_btn_Click(object sender, EventArgs e)
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

        private void output_btn_Click(object sender, EventArgs e)
        {

        }

        public void door_btn_Click(object sender, EventArgs e)
        {
            door_flag = true;
            //byte[] q = { 0xEA };
            //ComDevice.Write(q, 0, q.Length);
            //record.Add(new R() { Name = "旺财", Re = DateTime.Now.ToString() });

            //dgv1.DataSource = new BindingList<R>(record);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
           // clock.Text = DateTime.Now.ToString();
        }

        private void add_btn_Click(object sender, EventArgs e)
        {
           // var frm_Add = new Add();
          //  frm_Add.ShowDialog();
          //  try
         //   {
         //       db.Add(new SE() { No = frm_Add._id, Name = frm_Add._name });
          //      dgv2.DataSource = new BindingList<SE>(db);
         //   }
         //   catch (Exception)
          //  {
          //      MessageBox.Show("不能为空！", "error");
           // }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void door_btn_Click_1(object sender, EventArgs e)
        {
            record.Add(new R() { Name = "旺财", Re = DateTime.Now.ToString() });

            dgv1.DataSource = new BindingList<R>(record);
        }

       

      

        private void button2_Click(object sender, EventArgs e)
        {
       //     videoSource.Stop();
      //      videoSourcePlayer1.Stop();
    //        btn1.Enabled = true;
    //        button2.Enabled = false;
    //        comboBox4.Enabled = true;
        }

       

    }
}
