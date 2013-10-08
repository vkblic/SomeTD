using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using IDS_Helper;
using System.IO;
namespace ImageClip
{
	public partial class Form1 : Form
	{
		string source_path_;
		string dest_path_;
		public Form1()
		{
			InitializeComponent();
			this.textBoxSrcPath.Text = @"d:\";
			this.textBoxOutput.Text = @"d:\atlase";
	
	
			//this.textBoxSrcPath.Text = @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\";
			//this.textBoxOutput.Text = @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\temp\towerHD\";
		}

		private void btnGenerate_Click(object sender, EventArgs e)
		{
			//var temp = PListReader.Read(this.textBoxSrcPath.Text + "\\" + this.textBoxFileName.Text + ".plist");
			//ImageClip.Clip(temp, this.textBoxSrcPath.Text + "\\" + this.textBoxFileName.Text + ".png", this.textBoxOutput.Text);
			//ImageClip.Clip(temp, @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\enemies_snow.png", @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\Temp\enemies_snow\");


			source_path_ = this.textBoxSrcPath.Text;
			dest_path_ = this.textBoxOutput.Text;
			this.Processor();
			MessageBox.Show( "Done！" );
		}
		class Atlase
		{
			public string png_path;
			public string plist_path;
			public Atlase( string png, string plist )
			{
				this.png_path = png;
				this.plist_path = plist;

			}
		}
		public void Processor()
		{
			// get all atlases in source path
			var atlases = new List<Atlase>();
			var files = FileHelper.GetAllFiles( source_path_, "*.png" );
			foreach ( FileInfo file in files )
			{
				string name = file.Name.Split( '.' )[0];
				string plist_name = string.Format( "{0}\\{1}.plist", file.Directory.FullName, name );
				if ( FileHelper.FileExist( plist_name ) )
				{
					string atlases_path = string.Format( "{0}\\{1}", dest_path_, name );
					string sprite_path = string.Format( "{0}\\sprites", atlases_path );
					FileHelper.CreateDirectory( sprite_path );
					FileHelper.CopyFile( plist_name, string.Format( "{0}\\{1}.plist", atlases_path, name ), true );
					FileHelper.CopyFile( file.FullName, string.Format( "{0}\\{1}.png", atlases_path, name ), true );

					var texture_list = PListReader.Read( plist_name );
					ImageClip.Clip( texture_list, file.FullName, sprite_path );
				}

			}
			
		}
	}
}
