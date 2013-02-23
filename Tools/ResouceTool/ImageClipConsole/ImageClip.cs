using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
namespace ImageClipConsole
{
	class ImageClip
	{
		public static void Clip(IList<TextureInfo> texInfoList, string fileName, string outputDir)
		{
			// 			try
			// 			{
			// 				int count = 10;// myarray.Count;//动态数据，保存所有图片的Top和Left，以及最大点的坐标
			// 
			// 				//int width = (((int)myarray[count - 2]) / 256 + 1) * 256;//使动态生成的图片长和宽式256的整数倍
			// 				//int height = (((int)myarray[count - 1]) / 256 + 1) * 256;
			// 				Bitmap newBitmap = new Bitmap(width, height);
			// 				Color pixel;
			// 				int width1 = 0, height1 = 0;
			// 				for (int j = 0; j < (count - 2) / 2; j++)
			// 				{
			// 					Bitmap oldBitmap = new System.Drawing.Bitmap("Images\\MainFrame.png");
			// 					//(Bitmap)((PictureBox)this.Controls.Find("newpicturebox"+j, true)[0]).Image;
			// 					// width1 = ((PictureBox)this.Controls.Find("newpicturebox"+j, true)[0]).Image.Width;
			// 					// height1 = ((PictureBox)this.Controls.Find("newpicturebox"+j, true)[0]).Image.Height;
			// 					int px = Convert.ToInt16(myarray[j * 2]);// ((PictureBox)this.Controls.Find("newpicturebox" + j, true)[0]).Location.X;
			// 					int py = Convert.ToInt16(myarray[j * 2 + 1]);//((PictureBox)this.Controls.Find("newpicturebox"+j, true)[0]).Location.Y;
			// 					for (int p = 0; p < width1; p++)
			// 						for (int q = 0; q < height1; q++)
			// 						{
			// 							pixel = oldBitmap.GetPixel(p, q);
			// 							newBitmap.SetPixel(px + p, py + q, pixel);
			// 						}
			// 				}
			// 				Clear();
			// 				this.pictureBox1.Size = new Size(width, height);
			// 				this.pictureBox1.Image = newBitmap;
			// 				newBitmap.Save(DirectoryInfoPath + "00.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
			// 			}
			// 			catch (Exception ex)
			// 			{
			// 				MessageBox.Show(ex.Message, "信息提示");
			// 			}

			//Image clip:

			//int width2 = this.pictureBox1.Width;
			//int height2 = this.pictureBox1.Height;
			Bitmap oldBitmap = new System.Drawing.Bitmap(fileName);
			foreach (TextureInfo texInfo in texInfoList)
			{
				Bitmap newBitmap = new System.Drawing.Bitmap(texInfo.sourceSize.Width, texInfo.sourceSize.Height);
				Color pixel;
				for (int i = 0; i < texInfo.texRect.Width; i++)
				{
					for (int j = 0; j < texInfo.texRect.Height; j++)
					{
						pixel = oldBitmap.GetPixel(texInfo.texRect.X + i, texInfo.texRect.Y + j);
						newBitmap.SetPixel(i + texInfo.offset.X, j + texInfo.offset.Y, pixel);

					}
				}
				newBitmap.Save(string.Format(@"{0}\{1}", outputDir, texInfo.fileName), System.Drawing.Imaging.ImageFormat.Png);
				newBitmap.Dispose();
			}

		}
	}
}
