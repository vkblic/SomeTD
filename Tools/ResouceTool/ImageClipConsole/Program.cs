using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImageClipConsole
{
	class Program
	{
		static void Main(string[] args)
		{
			PListReader reader = new PListReader();

			//var temp = reader.Read(@"F:\Kindom rush\enemies_snow.plist");
			//ImageClip.Clip(temp, @"F:\Kindom rush\enemies_snow.png", @"F:\Kindom rush\Temp\enemies_snow\");

			var temp = reader.Read(@"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\enemies_snow.plist");
			ImageClip.Clip(temp, @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\enemies_snow.png", @"E:\Developer\[GameProgramming]\[SomeTD]\Resouce\Kingdom Rush.app\Temp\enemies_snow\");
		}
	}
}
