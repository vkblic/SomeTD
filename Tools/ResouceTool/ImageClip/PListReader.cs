using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HtmlAgilityPack;
namespace ImageClip
{

	public class plistKeyInfo
	{
		public static string ColorRect = "spriteColorRect";
		public static string Offset = "spriteOffset";
		public static string SpriteSize = "spriteSize";
		public static string SourceSize = "spriteSourceSize";
		public static string FrameRect = "textureRect";
		public static string Rotated = "textureRotated";
	}

	public class rect
	{
		public rect( int x, int y, int width, int height )
		{
			this.X = x;
			this.Y = y;
			this.Width = width;
			this.Height = height;
		}
		public int X { get; set; }
		public int Y { get; set; }
		public int Width { get; set; }
		public int Height { get; set; }
	}
	public class size
	{
		public size( int width, int height )
		{

			this.Width = width;
			this.Height = height;
		}
		public int Width { get; set; }
		public int Height { get; set; }

	}
	public class point
	{
		public point( int x, int y )
		{

			this.x = x;
			this.y = y;
		}
		public int x;
		public int y;
	}
	public class TextureInfo
	{
		public string fileName;
		public rect texRect;
		public size sourceSize;
		public point offset;
		public rect innerRect;
		public bool isRotated;

	}
	public class PListReader
	{
		public static List<TextureInfo> Read( string fileName )
		{

			HtmlAgilityPack.HtmlDocument htmlDoc = new HtmlAgilityPack.HtmlDocument();
			htmlDoc.DetectEncodingAndLoad( fileName, true );
			//htmlDoc.
			HtmlNode Plist = htmlDoc.DocumentNode.Element( "plist" );
			HtmlNodeCollection dicNodes = Plist.ChildNodes["dict"].ChildNodes[3].ChildNodes;


			int count = dicNodes.Count / 2;
			int i = 0;

			var texInfoes = new List<TextureInfo>();

			string key = null;
			//var value = null;
			var dic = new Dictionary<string, Dictionary<string, string>>();
			foreach ( HtmlNode node in dicNodes )
			{
				if ( node.Name[0] == '#' )
					continue;

				if ( node.Name[0] == 'k' )
				{
					key = node.InnerHtml;
				}
				else
				{
					var value = new Dictionary<string, string>();
					string subKey = null;
					string subValue = null;
					foreach ( HtmlNode infoNode in node.ChildNodes )
					{
						if ( infoNode.Name[0] == '#' )
							continue;

						if ( infoNode.Name[0] == 'k' )
						{
							subKey = infoNode.InnerHtml;
						}
						else
						{
							if ( infoNode.InnerHtml == string.Empty )
								subValue = infoNode.Name;
							else
								subValue = infoNode.InnerHtml;
							//subValue = infoNode.InnerHtml == string.Empty ? infoNode.Name : infoNode.InnerHtml;

							value.Add( subKey, subValue );
							subKey = null;
							subValue = null;
						}
					}
					dic.Add( key, value );
					key = null;
					value = null;
				}

			}

			foreach ( string item in dic.Keys )
			{
				TextureInfo texInfo = new TextureInfo();

				texInfo.fileName = item;

				var value = dic[item];


				//获取FrameRect
				texInfo.texRect = GetFrameRect( value[plistKeyInfo.FrameRect] );


				//计算并存储offsetRect
				texInfo.offset = new point( 0, 0 );
				GetTowNumber( value[plistKeyInfo.Offset], out texInfo.offset.x, out texInfo.offset.y );


				//获取SourceSize
				int width;
				int height;
				GetTowNumber( value[plistKeyInfo.SourceSize], out width, out height );

				texInfo.sourceSize = new size( width, height );
				// 				Console.WriteLine("{0}: {1}, {2} ; {3}, {4}",
				// 					tempinfo.fileName,
				// 					tempinfo.texRect.X, tempinfo.texRect.Y,
				// 					tempinfo.texRect.Width, tempinfo.texRect.Height
				// 					);

				// 是否旋转
				texInfo.isRotated = value[plistKeyInfo.Rotated] == "true" ? true : false;

				//计算实际的innerRect的值
				texInfo.innerRect = new rect( 0, 0, 0, 0 );
				if ( texInfo.isRotated )
				{
					texInfo.innerRect.Width = texInfo.texRect.Height;
					texInfo.innerRect.Height = texInfo.texRect.Width;
				}
				else
				{
					texInfo.innerRect.Width = texInfo.texRect.Width;
					texInfo.innerRect.Height = texInfo.texRect.Height;
				}
				texInfo.innerRect.X = ( texInfo.sourceSize.Width - texInfo.innerRect.Width ) / 2 + texInfo.offset.x;
				texInfo.innerRect.Y = ( texInfo.sourceSize.Height - texInfo.innerRect.Height ) / 2 - texInfo.offset.y;



				texInfoes.Add( texInfo );
			}



			return texInfoes;
		}

		/// <summary>
		/// 获取图片颜色最小区域数据在整合纹理中的rect
		/// </summary>
		/// <param name="rectInfo"></param>
		public static rect GetFrameRect( string rectInfo )
		{

			//<string>{{36, 88}, {34, 30}}</string>
			var temp = new List<int>(); //临时存储坐标点
			int tempNum = -1; //临时变量
			for ( int j = 0; j < rectInfo.Length; j++ )
			{
				if ( rectInfo[j] == '}' || rectInfo[j] == '{'
					|| rectInfo[j] == ' ' || rectInfo[j] == ',' )
				{
					if ( tempNum != -1 )
					{
						temp.Add( tempNum );
						tempNum = -1;
					}
					continue;
				}
				if ( tempNum == -1 )
					tempNum = 0;
				tempNum *= 10;
				tempNum += ( (int)rectInfo[j] - 48 );

			}

			return new rect( temp[0], temp[1], temp[2], temp[3] );
		}




		/// <summary>
		/// 计算偏移rect
		/// </summary>
		/// <param name="rectInfo"></param>
		/// <returns></returns>
		public static rect GetOffsetRect( string offset, string colorRect )
		{
			//这里先把

			int offsetX;
			int offsetY;
			GetTowNumber( offset, out offsetX, out offsetY );
			var tempNums = new List<int>(); //临时存储坐标点
			int tempNum = -1; //临时变量

			tempNums.Clear();
			tempNum = -1;
			//<string>{{36, 88}, {34, 30}}</string>
			for ( int j = 0; j < colorRect.Length; j++ )
			{
				if ( colorRect[j] == '}' || colorRect[j] == '{'
					|| colorRect[j] == ' ' || colorRect[j] == ',' )
				{
					if ( tempNum != -1 )
					{
						tempNums.Add( tempNum );
						tempNum = -1;
					}
					continue;
				}
				if ( tempNum == -1 )
					tempNum = 0;
				tempNum *= 10;
				tempNum += ( (int)colorRect[j] - 48 );

			}

			return new rect( tempNums[0] - offsetX, tempNums[1] + offsetY, tempNums[2], tempNums[3] );
		}

		/// <summary>
		/// 获取{x, y}中的x, y
		/// </summary>
		/// <param name="offset"></param>
		/// <param name="X"></param>
		/// <param name="Y"></param>
		public static void GetTowNumber( string offset, out int X, out int Y )
		{
			var tempNums = new List<int>(); //临时存储坐标点
			int tempNum = -1; //临时变量
			bool isOffsetNegative = false;
			//<key>spriteOffset</key>
			//<string>{3, -2}</string>
			for ( int i = 0; i < offset.Length; i++ )
			{
				if ( offset[i] == '}' || offset[i] == '{'
					|| offset[i] == ' ' || offset[i] == ',' )
				{
					if ( tempNum != -1 )
					{
						if ( isOffsetNegative )
						{
							tempNum *= -1;
							isOffsetNegative = false;
						}

						tempNums.Add( tempNum );
						tempNum = -1;
					}
					continue;
				}
				if ( tempNum == -1 )
				{
					tempNum = 0;
					if ( offset[i] == '-' )
					{
						isOffsetNegative = true;
						continue;
					}
				}
				tempNum *= 10;
				tempNum += ( (int)offset[i] - 48 );
			}

			X = tempNums[0];
			Y = tempNums[1];
		}
	}
}
