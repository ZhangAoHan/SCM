using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace test
{
    public partial class Add : Form
    {
        public Add()
        {
            InitializeComponent();
        }

        private void Add_Load(object sender, EventArgs e)
        {

        }
        public string _id, _name;
        private void yes_btn_Click(object sender, EventArgs e)
        {
            _id = id_t.Text;
            _name = name_t.Text;
            this.Close();

        }

        private void cancel_btn_Click(object sender, EventArgs e)
        {

        }

        private void No_t_TextChanged(object sender, EventArgs e)
        {
            this.Close();
        }


    }
}
