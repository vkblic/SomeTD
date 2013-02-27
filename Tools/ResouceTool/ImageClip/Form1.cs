using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageClip
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			this.textBoxSrcPath.Text = @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\";
			this.textBoxOutput.Text = @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\temp\ingame_gui\";
		}

		private void btnGenerate_Click(object sender, EventArgs e)
		{
			var temp = PListReader.Read(this.textBoxSrcPath.Text + "\\" + this.textBoxFileName.Text + ".plist");
			ImageClip.Clip(temp, this.textBoxSrcPath.Text + "\\" + this.textBoxFileName.Text + ".png", this.textBoxOutput.Text);
			//ImageClip.Clip(temp, @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\enemies_snow.png", @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\Temp\enemies_snow\");
			MessageBox.Show("Done！");
			
		}
	}
}
