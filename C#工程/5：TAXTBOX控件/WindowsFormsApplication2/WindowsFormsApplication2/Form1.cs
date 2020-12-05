using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void 蓝色_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionColor = Color.Blue;
        }

        private void 红色_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionColor = Color.Red;
        }

        private void 隶书18_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionFont = new Font("隶书",18);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionBullet = true;
        }

        private void 复原_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectionFont = new Font("宋体", 15);  //字体复原
            richTextBox1.SelectionBullet = false;    //项目符号复原
            richTextBox1.SelectionColor = Color.Black;    //颜色复原
        }
    }
}
