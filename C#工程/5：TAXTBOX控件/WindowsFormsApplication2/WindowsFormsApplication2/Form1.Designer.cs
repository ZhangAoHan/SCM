namespace WindowsFormsApplication2
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
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.蓝色 = new System.Windows.Forms.Button();
            this.红色 = new System.Windows.Forms.Button();
            this.隶书18 = new System.Windows.Forms.Button();
            this.复原 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(0, 24);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(183, 239);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "操作时请先选用文本";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(206, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "操作区";
            // 
            // 蓝色
            // 
            this.蓝色.Location = new System.Drawing.Point(189, 24);
            this.蓝色.Name = "蓝色";
            this.蓝色.Size = new System.Drawing.Size(75, 23);
            this.蓝色.TabIndex = 3;
            this.蓝色.Text = "蓝色";
            this.蓝色.UseVisualStyleBackColor = true;
            this.蓝色.Click += new System.EventHandler(this.蓝色_Click);
            // 
            // 红色
            // 
            this.红色.Location = new System.Drawing.Point(189, 77);
            this.红色.Name = "红色";
            this.红色.Size = new System.Drawing.Size(75, 23);
            this.红色.TabIndex = 4;
            this.红色.Text = "红色";
            this.红色.UseVisualStyleBackColor = true;
            this.红色.Click += new System.EventHandler(this.红色_Click);
            // 
            // 隶书18
            // 
            this.隶书18.Location = new System.Drawing.Point(189, 130);
            this.隶书18.Name = "隶书18";
            this.隶书18.Size = new System.Drawing.Size(75, 23);
            this.隶书18.TabIndex = 5;
            this.隶书18.Text = "隶书18";
            this.隶书18.UseVisualStyleBackColor = true;
            this.隶书18.Click += new System.EventHandler(this.隶书18_Click);
            // 
            // 复原
            // 
            this.复原.Location = new System.Drawing.Point(189, 236);
            this.复原.Name = "复原";
            this.复原.Size = new System.Drawing.Size(75, 23);
            this.复原.TabIndex = 6;
            this.复原.Text = "复原";
            this.复原.UseVisualStyleBackColor = true;
            this.复原.Click += new System.EventHandler(this.复原_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(189, 183);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "项目符号";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.复原);
            this.Controls.Add(this.隶书18);
            this.Controls.Add(this.红色);
            this.Controls.Add(this.蓝色);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.richTextBox1);
            this.Name = "Form1";
            this.Text = "张奥涵";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button 蓝色;
        private System.Windows.Forms.Button 红色;
        private System.Windows.Forms.Button 隶书18;
        private System.Windows.Forms.Button 复原;
        private System.Windows.Forms.Button button1;
    }
}

