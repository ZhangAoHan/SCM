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

        private void Form1_DoubleClick(object sender, EventArgs e)
        {
            MessageBox.Show("点击");
        }

        private void 新建ToolStripMenuItem_Click(object sender, EventArgs e)
        {
        
        }

      //  private void Form1_Load(object sender, EventArgs e)
     //   {
     //       MessageBox.Show("点击");
      //  }


    }
}
