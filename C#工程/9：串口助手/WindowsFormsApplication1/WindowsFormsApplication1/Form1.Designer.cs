namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.time = new System.Windows.Forms.Label();
            this.xttime = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.dkck = new System.Windows.Forms.Button();
            this.tzwh = new System.Windows.Forms.ComboBox();
            this.btlh = new System.Windows.Forms.ComboBox();
            this.ckh = new System.Windows.Forms.ComboBox();
            this.sjwh = new System.Windows.Forms.ComboBox();
            this.xywh = new System.Windows.Forms.ComboBox();
            this.ck = new System.Windows.Forms.Label();
            this.xyw = new System.Windows.Forms.Label();
            this.sj = new System.Windows.Forms.Label();
            this.tzw = new System.Windows.Forms.Label();
            this.btl = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button3 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.xttime.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // time
            // 
            this.time.AutoSize = true;
            this.time.Location = new System.Drawing.Point(23, 27);
            this.time.Name = "time";
            this.time.Size = new System.Drawing.Size(11, 12);
            this.time.TabIndex = 0;
            this.time.Text = "l";
            // 
            // xttime
            // 
            this.xttime.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.xttime.Controls.Add(this.time);
            this.xttime.Location = new System.Drawing.Point(739, 378);
            this.xttime.Name = "xttime";
            this.xttime.Size = new System.Drawing.Size(113, 48);
            this.xttime.TabIndex = 1;
            this.xttime.TabStop = false;
            this.xttime.Text = "系统时间";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Yellow;
            this.groupBox1.Controls.Add(this.dkck);
            this.groupBox1.Controls.Add(this.tzwh);
            this.groupBox1.Controls.Add(this.btlh);
            this.groupBox1.Controls.Add(this.ckh);
            this.groupBox1.Controls.Add(this.sjwh);
            this.groupBox1.Controls.Add(this.xywh);
            this.groupBox1.Controls.Add(this.ck);
            this.groupBox1.Controls.Add(this.xyw);
            this.groupBox1.Controls.Add(this.sj);
            this.groupBox1.Controls.Add(this.tzw);
            this.groupBox1.Controls.Add(this.btl);
            this.groupBox1.Location = new System.Drawing.Point(2, 137);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(279, 289);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口配置";
            // 
            // dkck
            // 
            this.dkck.Location = new System.Drawing.Point(136, 227);
            this.dkck.Name = "dkck";
            this.dkck.Size = new System.Drawing.Size(107, 53);
            this.dkck.TabIndex = 13;
            this.dkck.Text = "打开串口";
            this.dkck.UseVisualStyleBackColor = true;
            this.dkck.Click += new System.EventHandler(this.dkck_Click);
            // 
            // tzwh
            // 
            this.tzwh.FormattingEnabled = true;
            this.tzwh.Items.AddRange(new object[] {
            "1",
            "2",
            "3"});
            this.tzwh.Location = new System.Drawing.Point(122, 154);
            this.tzwh.Name = "tzwh";
            this.tzwh.Size = new System.Drawing.Size(121, 20);
            this.tzwh.TabIndex = 12;
            this.tzwh.Text = "1";
            // 
            // btlh
            // 
            this.btlh.FormattingEnabled = true;
            this.btlh.Items.AddRange(new object[] {
            "4800",
            "9600",
            "115200"});
            this.btlh.Location = new System.Drawing.Point(122, 114);
            this.btlh.Name = "btlh";
            this.btlh.Size = new System.Drawing.Size(121, 20);
            this.btlh.TabIndex = 11;
            this.btlh.Text = "9600";
            // 
            // ckh
            // 
            this.ckh.FormattingEnabled = true;
            this.ckh.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10",
            "COM21"});
            this.ckh.Location = new System.Drawing.Point(122, 34);
            this.ckh.Name = "ckh";
            this.ckh.Size = new System.Drawing.Size(121, 20);
            this.ckh.TabIndex = 10;
            this.ckh.Text = "COM9";
            // 
            // sjwh
            // 
            this.sjwh.FormattingEnabled = true;
            this.sjwh.Items.AddRange(new object[] {
            "8"});
            this.sjwh.Location = new System.Drawing.Point(122, 74);
            this.sjwh.Name = "sjwh";
            this.sjwh.Size = new System.Drawing.Size(121, 20);
            this.sjwh.TabIndex = 9;
            this.sjwh.Text = "8";
            // 
            // xywh
            // 
            this.xywh.FormattingEnabled = true;
            this.xywh.Items.AddRange(new object[] {
            "None"});
            this.xywh.Location = new System.Drawing.Point(122, 194);
            this.xywh.Name = "xywh";
            this.xywh.Size = new System.Drawing.Size(121, 20);
            this.xywh.TabIndex = 8;
            this.xywh.Text = "None";
            // 
            // ck
            // 
            this.ck.AutoSize = true;
            this.ck.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ck.Location = new System.Drawing.Point(22, 33);
            this.ck.Name = "ck";
            this.ck.Size = new System.Drawing.Size(76, 16);
            this.ck.TabIndex = 3;
            this.ck.Text = "串口号：";
            // 
            // xyw
            // 
            this.xyw.AutoSize = true;
            this.xyw.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.xyw.Location = new System.Drawing.Point(22, 201);
            this.xyw.Name = "xyw";
            this.xyw.Size = new System.Drawing.Size(68, 16);
            this.xyw.TabIndex = 7;
            this.xyw.Text = "校验位:";
            // 
            // sj
            // 
            this.sj.AutoSize = true;
            this.sj.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.sj.Location = new System.Drawing.Point(22, 75);
            this.sj.Name = "sj";
            this.sj.Size = new System.Drawing.Size(68, 16);
            this.sj.TabIndex = 4;
            this.sj.Text = "数据位:";
            // 
            // tzw
            // 
            this.tzw.AutoSize = true;
            this.tzw.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tzw.Location = new System.Drawing.Point(22, 159);
            this.tzw.Name = "tzw";
            this.tzw.Size = new System.Drawing.Size(68, 16);
            this.tzw.TabIndex = 6;
            this.tzw.Text = "停止位:";
            // 
            // btl
            // 
            this.btl.AutoSize = true;
            this.btl.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btl.Location = new System.Drawing.Point(22, 117);
            this.btl.Name = "btl";
            this.btl.Size = new System.Drawing.Size(68, 16);
            this.btl.TabIndex = 5;
            this.btl.Text = "波特率:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("叶根友毛笔行书2.0版", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.ForeColor = System.Drawing.Color.CornflowerBlue;
            this.label6.Location = new System.Drawing.Point(16, 55);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(93, 18);
            this.label6.TabIndex = 8;
            this.label6.Text = "发送的数据:";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Aqua;
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.textBox1);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Location = new System.Drawing.Point(410, 1);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(442, 129);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "发送数据区";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("叶根友毛笔行书2.0版", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(6, 105);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 18);
            this.label1.TabIndex = 12;
            this.label1.Text = "发送";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(128, 11);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(303, 112);
            this.textBox1.TabIndex = 10;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(410, 159);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 43);
            this.button1.TabIndex = 10;
            this.button1.Text = "开灯";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(589, 159);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 43);
            this.button2.TabIndex = 11;
            this.button2.Text = "关灯";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(6, 20);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(381, 185);
            this.textBox2.TabIndex = 13;
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Yellow;
            this.groupBox3.Controls.Add(this.textBox2);
            this.groupBox3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox3.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.groupBox3.Location = new System.Drawing.Point(306, 212);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(393, 214);
            this.groupBox3.TabIndex = 14;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "收到的数据";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(739, 232);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 48);
            this.button3.TabIndex = 14;
            this.button3.Text = "开始接收";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(136, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 15;
            this.label2.Text = "0";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(17, 40);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 34);
            this.button4.TabIndex = 16;
            this.button4.Text = "button4";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(176, 60);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(15, 23);
            this.label4.TabIndex = 18;
            this.label4.Text = "0";
            // 
            // label5
            // 
            this.label5.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(155, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(15, 23);
            this.label5.TabIndex = 19;
            this.label5.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(853, 426);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.xttime);
            this.Name = "Form1";
            this.Text = "上位机控制LED灯量灭";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.xttime.ResumeLayout(false);
            this.xttime.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label time;
        private System.Windows.Forms.GroupBox xttime;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button dkck;
        private System.Windows.Forms.ComboBox tzwh;
        private System.Windows.Forms.ComboBox btlh;
        private System.Windows.Forms.ComboBox ckh;
        private System.Windows.Forms.ComboBox sjwh;
        private System.Windows.Forms.ComboBox xywh;
        private System.Windows.Forms.Label ck;
        private System.Windows.Forms.Label xyw;
        private System.Windows.Forms.Label sj;
        private System.Windows.Forms.Label tzw;
        private System.Windows.Forms.Label btl;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}

