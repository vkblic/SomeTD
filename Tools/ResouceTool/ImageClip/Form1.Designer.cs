namespace ImageClip
{
	partial class Form1
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
			this.textBoxSrcPath = new System.Windows.Forms.TextBox();
			this.textBoxOutput = new System.Windows.Forms.TextBox();
			this.btnGenerate = new System.Windows.Forms.Button();
			this.textBoxFileName = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// textBoxSrcPath
			// 
			this.textBoxSrcPath.Location = new System.Drawing.Point(12, 31);
			this.textBoxSrcPath.Name = "textBoxSrcPath";
			this.textBoxSrcPath.Size = new System.Drawing.Size(466, 20);
			this.textBoxSrcPath.TabIndex = 0;
			this.textBoxSrcPath.Text = "SourcePath";
			// 
			// textBoxOutput
			// 
			this.textBoxOutput.Location = new System.Drawing.Point(12, 73);
			this.textBoxOutput.Name = "textBoxOutput";
			this.textBoxOutput.Size = new System.Drawing.Size(466, 20);
			this.textBoxOutput.TabIndex = 1;
			this.textBoxOutput.Text = "Output";
			// 
			// btnGenerate
			// 
			this.btnGenerate.Location = new System.Drawing.Point(368, 208);
			this.btnGenerate.Name = "btnGenerate";
			this.btnGenerate.Size = new System.Drawing.Size(75, 23);
			this.btnGenerate.TabIndex = 2;
			this.btnGenerate.Text = "Generate";
			this.btnGenerate.UseVisualStyleBackColor = true;
			this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
			// 
			// textBoxFileName
			// 
			this.textBoxFileName.Location = new System.Drawing.Point(12, 110);
			this.textBoxFileName.Name = "textBoxFileName";
			this.textBoxFileName.Size = new System.Drawing.Size(100, 20);
			this.textBoxFileName.TabIndex = 3;
			this.textBoxFileName.Text = "FileName";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(490, 278);
			this.Controls.Add(this.textBoxFileName);
			this.Controls.Add(this.btnGenerate);
			this.Controls.Add(this.textBoxOutput);
			this.Controls.Add(this.textBoxSrcPath);
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox textBoxSrcPath;
		private System.Windows.Forms.TextBox textBoxOutput;
		private System.Windows.Forms.Button btnGenerate;
		private System.Windows.Forms.TextBox textBoxFileName;
	}
}

