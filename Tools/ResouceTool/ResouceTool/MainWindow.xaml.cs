using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
//using System.Drawing.Drawing2D;
//using System.Drawing;

namespace ResouceTool
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		int maxMarginLeft = 0;
		int maxMarginTop = 0;
		int minMarginLeft = 0;
		int minMarginTop = 0;
		int gridWidth = 768;
		int gridHeight = 384;
		public MainWindow()
		{
			
			InitializeComponent();
			//Image myImage3 = new Image();

			//读取源文件
			System.Drawing.Bitmap bitmap = new System.Drawing.Bitmap("Images\\MainFrame.png");

			int width = bitmap.Width;
			int height = bitmap.Height;
			this.image1.Height = height;
			this.image1.Width = width;

			//计算margin范围
			if (width < gridWidth)
			{
				maxMarginLeft = gridWidth - width;
			}
			else if (width > gridWidth)
			{
				minMarginLeft = gridWidth - width;
			}

			if (height < gridHeight)
			{
				maxMarginTop = gridHeight - height;
			}
			else if (height > gridHeight)
			{
				minMarginTop = gridHeight - height;
			}

			MessageBox.Show("beforeMs");
			// 存入内存
			MemoryStream ms = new MemoryStream();
			bitmap.Save(ms, System.Drawing.Imaging.ImageFormat.Png);

			MessageBox.Show("afterMS");

			//建立BitmapImage, 使用该图片流
			ms.Position = 0;
			BitmapImage testRect = new BitmapImage();
			testRect.BeginInit();
			//Do not create a memory store. All requests for the image are filled directly by the image file.
			testRect.CacheOption = System.Windows.Media.Imaging.BitmapCacheOption.None;
			testRect.UriSource = null;
			testRect.StreamSource = ms;
			//testRect.SourceRect = new System.Windows.Int32Rect(11, 123, 460, 52);
			testRect.EndInit();

			MessageBox.Show("afterBitMap");

			this.image1.Source = testRect;
			//System.Drawing.Image i = System.Drawing.Image.FromStream(ms);

			//ImageSource is = new ImageSource

			//this.image1.Source = i;

			//myImage3.Stretch = Stretch.Fill;
			//myImage3.Source = bi3;

		}
		//System.Windows.Thickness thickness = new System.Windows.Thickness();
		Point lastPoint = new Point();
		private void image1_MouseMove(object sender, MouseEventArgs e)
		{
			Point p = e.GetPosition(this);
			textBlock1.Text = string.Format("{0},{1}", p.X, p.Y);

			Point curPoint = e.GetPosition(this);
			if (e.LeftButton == MouseButtonState.Pressed)
			{
				System.Windows.Thickness margin = this.image1.Margin;
				margin.Left += curPoint.X - lastPoint.X;
				margin.Top += curPoint.Y - lastPoint.Y;
				if (margin.Left > maxMarginLeft)
					margin.Left = maxMarginLeft;
				else if (margin.Left < minMarginLeft)
					margin.Left = minMarginLeft;

				if (margin.Top > maxMarginTop)
					margin.Top = maxMarginTop;
				else if (margin.Top < minMarginTop)
					margin.Top = minMarginTop;
				this.image1.Margin = margin;
			}
			e.Handled = true;
			lastPoint.X = curPoint.X;
			lastPoint.Y = curPoint.Y;
		}

		private void image1_MouseEnter(object sender, MouseEventArgs e)
		{
			//Point p = e.GetPosition(this);
			//textBlock1.Text = string.Format("{0},{1}", p.X, p.Y);
			e.Handled = true;
		}

		private void MouseMoveHandler(object sender, MouseEventArgs e)
		{
			// Get the x and y coordinates of the mouse pointer.
			System.Windows.Point position = e.GetPosition(this);
			double pX = position.X;
			double pY = position.Y;

			// Sets the Height/Width of the circle to the mouse coordinates.
			//ellipse.Width = pX;
			//ellipse.Height = pY;
		}

		private void Button_Click(object sender, RoutedEventArgs e)
		{
			//Image myImage = new Image();
			BitmapImage bi = new BitmapImage();

			// Begin initialization.
			bi.BeginInit();

			// Set properties.
			/*bi.CacheOption = BitmapCacheOption.OnDemand;
			bi.CreateOptions = BitmapCreateOptions.DelayCreation;
			bi.DecodePixelHeight = 125;
			bi.DecodePixelWidth = 125;
			bi.Rotation = Rotation.Rotate90;
			MessageBox.Show(bi.IsDownloading.ToString());*/
			bi.UriSource = new Uri("\\res\\MainFrame.png", UriKind.Relative);

			// End initialization.
			bi.EndInit();
			MemoryStream ms = new MemoryStream();
			//bi.StreamSource.CopyTo(ms);
			//bi.
			//bi.
			//string a = string.Format("DecodePixelHeight: {0}\nDecodePixelWidth: {1}\nHeight: {2}\nWidth: {3} ");//
			//myImage.Source = bi;
			//myImage.Stretch = Stretch.None;
			//myImage.Margin = new Thickness(5);
		}

		private void image1_MouseLeave_1(object sender, MouseEventArgs e)
		{

		}

		private void image1_MouseLeftButtonDown_1(object sender, MouseButtonEventArgs e)
		{
			Point curPoint = e.GetPosition(this);
			lastPoint.X = curPoint.X;
			lastPoint.Y = curPoint.Y;
			image1.Cursor = Cursors.Hand;
		}

		private void image1_PreviewMouseLeftButtonUp_1(object sender, MouseButtonEventArgs e)
		{
			image1.Cursor = Cursors.Arrow;
		}


	}
}
