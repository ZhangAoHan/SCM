namespace test
{
    partial class Add
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.name_t = new System.Windows.Forms.TextBox();
            this.id_t = new System.Windows.Forms.TextBox();
            this.cancel_btn = new System.Windows.Forms.Button();
            this.yes_btn = new System.Windows.Forms.Button();
            this.Name_l = new System.Windows.Forms.Label();
            this.No_l = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // name_t
            // 
            this.name_t.Location = new System.Drawing.Point(120, 118);
            this.name_t.Name = "name_t";
            this.name_t.Size = new System.Drawing.Size(111, 21);
            this.name_t.TabIndex = 13;
            // 
            // id_t
            // 
            this.id_t.Location = new System.Drawing.Point(120, 57);
            this.id_t.Name = "id_t";
            this.id_t.Size = new System.Drawing.Size(111, 21);
            this.id_t.TabIndex = 12;
            // 
            // cancel_btn
            // 
            this.cancel_btn.Location = new System.Drawing.Point(161, 183);
            this.cancel_btn.Name = "cancel_btn";
            this.cancel_btn.Size = new System.Drawing.Size(72, 23);
            this.cancel_btn.TabIndex = 11;
            this.cancel_btn.Text = "取消";
            this.cancel_btn.UseVisualStyleBackColor = true;
            this.cancel_btn.Click += new System.EventHandler(this.cancel_btn_Click);
            // 
            // yes_btn
            // 
            this.yes_btn.Location = new System.Drawing.Point(52, 183);
            this.yes_btn.Name = "yes_btn";
            this.yes_btn.Size = new System.Drawing.Size(73, 23);
            this.yes_btn.TabIndex = 10;
            this.yes_btn.Text = "确认";
            this.yes_btn.UseVisualStyleBackColor = true;
            this.yes_btn.Click += new System.EventHandler(this.yes_btn_Click);
            // 
            // Name_l
            // 
            this.Name_l.AutoSize = true;
            this.Name_l.Location = new System.Drawing.Point(61, 118);
            this.Name_l.Name = "Name_l";
            this.Name_l.Size = new System.Drawing.Size(29, 12);
            this.Name_l.TabIndex = 9;
            this.Name_l.Text = "姓名";
            // 
            // No_l
            // 
            this.No_l.AutoSize = true;
            this.No_l.Location = new System.Drawing.Point(61, 60);
            this.No_l.Name = "No_l";
            this.No_l.Size = new System.Drawing.Size(29, 12);
            this.No_l.TabIndex = 8;
            this.No_l.Text = "卡号";
            // 
            // Add
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.name_t);
            this.Controls.Add(this.id_t);
            this.Controls.Add(this.cancel_btn);
            this.Controls.Add(this.yes_btn);
            this.Controls.Add(this.Name_l);
            this.Controls.Add(this.No_l);
            this.Name = "Add";
            this.Text = "Add";
            this.Load += new System.EventHandler(this.Add_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox name_t;
        private System.Windows.Forms.TextBox id_t;
        private System.Windows.Forms.Button cancel_btn;
        private System.Windows.Forms.Button yes_btn;
        private System.Windows.Forms.Label Name_l;
        private System.Windows.Forms.Label No_l;
    }
}