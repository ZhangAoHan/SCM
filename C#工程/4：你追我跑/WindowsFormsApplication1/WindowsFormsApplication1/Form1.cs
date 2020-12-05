using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_MouseEnter(object sender, EventArgs e)
        {
            int x = this.ClientSize.Width - label1.Width;
            int y = this.ClientSize.Height - label1.Height;
            Random r = new Random(); //产生随机数
            //MessageBox.Show(r.Next(0,5).ToString());
            label1.Location = new Point(r.Next(0,x+1),r.Next(0,y+1));
        }

        private void label1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("你真厉害，追到了我");
        }
    }
}
