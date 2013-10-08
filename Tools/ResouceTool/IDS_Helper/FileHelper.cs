using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.IO;
using System.Data;
using System.Diagnostics;
using System.Drawing;
namespace IDS_Helper
{
	/// <summary>
	/// 给定目录下给定类型的文件, 并按照文件名排序
	/// </summary>
	public static class FileHelper
	{
		public static List<FileInfo> GetAllFiles( string path, string filter, bool recursive = false )
		{
			if ( !Directory.Exists( path ) )
				return null;

			return FileHelper.GetAllFiles( new DirectoryInfo( path ), filter, recursive );
		}
		public static List<FileInfo> GetAllFiles( DirectoryInfo directory, string filter, bool recursive = false )
		{
			List<FileInfo> fileList = new List<FileInfo>();
			if ( recursive )
			{
				DirectoryInfo[] subDirectories = directory.GetDirectories();
				foreach ( DirectoryInfo subDirectory in subDirectories )
				{
					var subDirfiles = FileHelper.GetAllFiles( subDirectory, filter );
					if ( subDirfiles != null )
						fileList.AddRange( subDirfiles );
				}
			}
			FileInfo[] files = directory.GetFiles( filter );
			fileList.AddRange( files );

			if ( fileList.Count != 0 )
				return fileList;
			return null;
		}


		public static event UpdateUIState updateState;
		public delegate void UpdateUIState( string text, System.Drawing.Color color, int pos = 0 );
		/// <summary>
		/// 获取所有的SQl Scripts 文件目录
		/// </summary>
		/// <param name="filePath">根目录路径</param>
		/// <param name="files">结果集</param>
		/// <param name="searchPattern">类型参数如"*.txt"</param>
		/// <returns>是否成功获取</returns>
		public static bool getSqlFilesEx( string filePath, out List<FileInfo> files, string searchPattern )
		{
			// check null
			if ( !Directory.Exists( filePath ) )
			{
				files = null;
				return false;
			}
			try
			{
				files = getFilesEx( filePath, searchPattern );//new List<FileInfo>();
			}
			catch ( Exception e )
			{
				files = null;
				//System.Windows.Forms.MessageBox.Show(e.Message);
				Console.WriteLine( e.Message );
				Debug.WriteLine( e.Message );
				return false;
			}

			files.Sort( ( s1, s2 ) => { return string.Compare( s1.FullName, s2.FullName ); } );
			return true;

			//fileNames.AddRange()
			//files = new List<string>();
		}

		/// <summary>
		/// 获取给定目录下所有的制定类型文件
		/// </summary>
		/// <param name="dir"></param>
		private static List<FileInfo> getFilesEx( string strPath, string searchPattern )
		{
			DirectoryInfo dir = new DirectoryInfo( strPath );
			//fileNames = new List<string>();
			FileInfo[] fileArrs = dir.GetFiles( searchPattern );
			List<FileInfo> files = new List<FileInfo>();
			files.AddRange( fileArrs );

			DirectoryInfo[] subdir = dir.GetDirectories();
			for ( int i = 0; i < subdir.Length; i++ )
			{
				files.AddRange( getFilesEx( subdir[i].FullName, searchPattern ) );
			}
			return files;
		}
		/// <summary>
		/// 文件存在性检测
		/// </summary>
		/// <param name="fileNames">文件名集合</param>
		/// <returns></returns>
		public static bool FileExist( List<string> fileNames )
		{
			if ( fileNames == null )
				return false;

			foreach ( string fileName in fileNames )
			{
				if ( !File.Exists( fileName ) )
				{
					if ( updateState != null )
						updateState( fileName + " not exist!", System.Drawing.Color.Red );
					return false;
				}
			}

			return true;
		}

		/// <summary>
		/// 文件存在性检测
		/// </summary>
		/// <param name="fileName">文件名</param>
		/// <returns></returns>
		public static bool FileExist( string fileName )
		{
			if ( !File.Exists( fileName ) )
			{
				if ( updateState != null )
					updateState( fileName + " not exist!", System.Drawing.Color.Red );
				return false;
			}
			return true;
		}

		/// <summary>
		/// 删除文件
		/// </summary>
		/// <param name="fileNames">文件名集合</param>
		public static void DeleteFiles( List<string> fileNames )
		{
			foreach ( string fileName in fileNames )
			{
				if ( File.Exists( fileName ) )
				{
					try
					{
						File.Delete( fileName );
					}
					catch ( System.Exception ex )
					{
						if ( updateState != null )
							updateState( ex.Message, System.Drawing.Color.Red );
					}
				}
				else
				{
					if ( updateState != null )
						updateState( "Can't find" + fileName, System.Drawing.Color.Red );
				}
			}
		}

		/// <summary>
		/// 删除文件
		/// </summary>
		/// <param name="fileNames">文件名</param>
		public static void DeleteFile( string fileName )
		{
			if ( File.Exists( fileName ) )
			{
				try
				{
					File.Delete( fileName );
					//updateState("Delete: " + fileName, System.Drawing.Color.Green);
				}
				catch ( System.Exception ex )
				{
					if ( updateState != null )
						updateState( ex.Message, System.Drawing.Color.Red );
					Console.WriteLine( ex.Message );
				}
			}
			else
				if ( updateState != null )
					updateState( "Can't find" + fileName, System.Drawing.Color.Red );
		}

		public static bool DirectoryExsits( string _dir_path )
		{
			return Directory.Exists( _dir_path );
		}

		/// <summary>
		/// 删除文件夹
		/// </summary>
		/// <param name="directoryNames">文件夹名</param>
		/// <param name="recursive">是否删除子文件夹</param>
		public static void DeleteDirectory( string directoryNames, bool recursive )
		{
			if ( Directory.Exists( directoryNames ) )
			{
				try
				{
					Directory.Delete( directoryNames, recursive );
					//updateState("Delete: " + directoryNames, System.Drawing.Color.Green);
				}
				catch ( System.Exception ex )
				{
					if ( updateState != null )
						updateState( ex.Message, System.Drawing.Color.Red );
				}
			}
			else
			{
				if ( updateState != null )
					updateState( "Can't find" + directoryNames, System.Drawing.Color.Red );
			}

#if DEBUG
			Console.WriteLine( string.Format( "Delete {0} done!", directoryNames ) );
#endif
		}

		/// <summary>
		/// 删除文件夹
		/// </summary>
		/// <param name="directoryNames">文件夹集合</param>
		public static void DeleteDirectories( IList<string> directoryNames, bool recursive )
		{
			if ( directoryNames == null )
				return;
			foreach ( string dir in directoryNames )
			{
				if ( Directory.Exists( dir ) )
				{
					try
					{
						Directory.Delete( dir, recursive );
						Console.WriteLine( "Directory Delete Success: {0}", dir );
					}
					catch ( System.Exception ex )
					{
						Console.WriteLine( ex );
						if ( updateState != null )
							updateState( ex.Message, System.Drawing.Color.Red );
					}
				}
				else
				{
					Console.WriteLine( "Can't find" + dir );
					if ( updateState != null )
						updateState( "Can't find" + dir, System.Drawing.Color.Red );
				}
			}
		}

		/// <summary>
		/// 创建文件夹
		/// </summary>
		/// <param name="path"></param>
		public static void CreateDirectory( string path )
		{
			//StringBuilder stringBuilder = new StringBuilder(200);
			if ( Directory.Exists( path ) )
			{
#if DEBUG
				string msg = string.Format( "[Path {0}]: Already exist!", path );
				if ( updateState != null )
					updateState( msg, System.Drawing.Color.Red );
				Console.WriteLine( msg, path );
#endif

				return;
			}

			//创建所有父级文件夹
			List<string> parents = new List<string>( path.Split( new char[] { '\\' } ) );
			bool isremote = path[0] == '\\';
			StringBuilder stringBuider = new StringBuilder( 512 );
			// 远程目录没有完成, 在判断如\\192.168xxxxx\时Directory.Exists回出现问题, Directory.CreateDirectory报异常, 之后在处理
			if ( isremote )
			{
				//stringBuider.Append("\\\\");
				parents.RemoveRange( 0, 2 );
				parents[0] = "\\\\" + parents[0];
				//
			}
			try
			{
				foreach ( string parent in parents )
				{
					// 远程主机不去判断"\\192.168xxxxx\" 是否存在, Directory.Exists()对于"\\192.168xxxxx\" 会有问题
					stringBuider.AppendFormat( "{0}\\", parent );
					if ( parent == string.Empty || parent.Substring( 0, 2 ) == "\\\\" )
						continue;
					if ( !Directory.Exists( stringBuider.ToString() ) )
					{
						Directory.CreateDirectory( stringBuider.ToString() );
						//if (updateState != null)
						//	updateState("Create directory: " + stringBuider.ToString(), System.Drawing.Color.Green);
						//Console.WriteLine("CreateDirectory: " + stringBuider.ToString() );
					}
				}
#if DEBUG
				if ( updateState != null )
					updateState( "CreateDirectory: " + path + " succeed!", System.Drawing.Color.Green );
				Console.WriteLine( "CreateDirectory: " + path + " succeed!" );
#endif
			}
			catch ( System.Exception ex )
			{
				if ( updateState != null )
					updateState( "Create Directory" + path + "Fail!\n" + ex.Message, System.Drawing.Color.Red );
				Console.WriteLine( "Create Directory" + path + "Fail!\n" + ex.Message );
			}

		}

		/// <summary>
		/// 复制文件夹下所有文件到目标位置, 创建目标文件夹(如果需要)
		/// </summary>
		/// <param name="source"></param>
		/// <param name="dest"></param>
		/// <param name="overwrite"></param>
		public static void CopyDirectory( string source, string dest, bool overwrite )
		{
			CreateDirectory( dest );
			Console.WriteLine( "directory: " + dest );
			// 复制文件
			try
			{
				string[] fileNames = Directory.GetFiles( source, "*.*" );
				foreach ( string fileName in fileNames )
				{
					string[] name = fileName.Split( '\\' );
					string destf = string.Format( "{0}\\{1}", dest, name[name.Length - 1] );
					File.Copy( fileName, destf, overwrite );
					//updateState(destf, System.Drawing.Color.Green);
					Console.WriteLine( "file: " + name[name.Length - 1] );
				}
			}
			catch ( System.Exception ex )
			{
				Console.WriteLine( ex.Message );
				if ( updateState != null )
					updateState( ex.Message + "\n" + source, System.Drawing.Color.Red );
			}
			// 复制文件夹
			try
			{
				string[] dirNames = Directory.GetDirectories( source );
				foreach ( string dir in dirNames )
				{
					DirectoryInfo dirInfo = new DirectoryInfo( dir );
					string sorceDir = string.Format( "{0}\\{1}", source, dirInfo.Name );
					string destDir = string.Format( "{0}\\{1}", dest, dirInfo.Name );
					CopyDirectory( sorceDir, destDir, true );
				}
			}
			catch ( System.Exception ex )
			{
				Console.WriteLine( ex.Message );
				if ( updateState != null )
					updateState( ex.Message + "\n" + source, System.Drawing.Color.Red );
			}
		}

		/// <summary>
		/// 拷贝文件到目标位置
		/// </summary>
		/// <param name="source"></param>
		/// <param name="dest"></param>
		/// <param name="overWrite"></param>
		public static void CopyFile( string source, string dest, bool overWrite )
		{
			StringBuilder sb = new StringBuilder();
			if ( !File.Exists( source ) )
			{
				sb.AppendFormat( "File: {0} Not Exist!", source );
				if ( updateState != null )
					updateState( sb.ToString(), System.Drawing.Color.Red );
				Console.WriteLine( sb.ToString() );
				return;
			}
			FileInfo fi = new FileInfo( source );

			FileHelper.CreateDirectory( fi.DirectoryName );
			try
			{
				File.Copy( source, dest, overWrite );
				//updateState("copyFile Done\n" + source + "\n" + dest, System.Drawing.Color.Green);
			}
			catch ( Exception e )
			{
				if ( updateState != null )
					updateState( e.Message + "\n" + source + "\n" + dest, System.Drawing.Color.Red );
				Console.WriteLine( "FileHelper.CopyFile: error! {0}", e.Message );
			}

		}
		/// <summary>
		/// 复制一个类型的文件到目标文件夹
		/// </summary>
		/// <param name="srcPaht"></param>
		/// <param name="destPath"></param>
		/// <param name="type"></param>
		/*public static void CopyFileByType(string srcPath, string destPath, string type)
		{
			try
			{
				string[] files = Directory.GetFiles(srcPath, type);
				foreach (string file in files)
				{
					FileInfo fileInfo = new FileInfo(file);
					File.Copy(file, string.Format("{0}\\{1}", destPath, fileInfo.Name));
				}
			}
			catch (System.Exception e)
			{
				StringBuilder sb = new StringBuilder();
				sb.AppendFormat("CopyFileByType: {0}\n", e.Message);
				sb.AppendFormat("srcPath: {0}", srcPath);

				string errorMsg = string.Format("CopyFileByType: {0}")
				if (updateState != null)
					updateState(e.Message + "\n" + srcPath + "\n" + destPath, System.Drawing.Color.Red);
			}
		}*/

		/// <summary>
		/// 复制某类文件(循环参数)
		/// </summary>
		/// <param name="srcPath"></param>
		/// <param name="destPath"></param>
		/// <param name="type"></param>
		/// <param name="recursive"></param>
		public static void CopyFileByType( string srcPath, string destPath, string type, bool recursive, bool overwrite )
		{
			CreateDirectory( destPath );
			try
			{
				string[] files = Directory.GetFiles( srcPath, type );
				foreach ( string file in files )
				{
					FileInfo fileInfo = new FileInfo( file );
					string destFile = string.Format( "{0}\\{1}", destPath, fileInfo.Name );
					File.Copy( file, destFile, overwrite );
#if DEBUG
					Console.WriteLine( destFile + " done!" );
#endif
				}
			}
			catch ( System.Exception e )
			{
				StringBuilder sb = new StringBuilder();
				sb.AppendFormat( "CopyFileByType: {0}\n", e.Message );
				sb.AppendFormat( "srcPath: {0}\n", srcPath );
				sb.AppendFormat( "destPath: {0}\n", destPath );
				sb.AppendFormat( "type: {0}\n", type );
				if ( updateState != null )
					updateState( sb.ToString(), System.Drawing.Color.Red );
				Console.WriteLine( sb.ToString() );
			}
			if ( !recursive )
				return;
			string[] dirs = Directory.GetDirectories( srcPath );
			foreach ( string dir in dirs )
			{
				string[] subDirs = dir.Split( '\\' );
				string newDestPath = string.Format( "{0}\\{1}", destPath, subDirs[subDirs.Length - 1] );

				CopyFileByType( dir, newDestPath, type, recursive, true );
			}

		}

		/// <summary>
		/// 删除目标文件夹
		/// </summary>
		/// <param name="path"></param>
		/// <param name="recursive"></param>
		/*public static void DelDirectory(string path, bool recursive = false)
		{
			try
			{
				if (Directory.Exists(path))
					Directory.Delete(path, recursive);
			}
			catch (System.Exception ex)
			{
				//Console.WriteLine(ex.Message);
				if (updateState != null)
					updateState(string.Format("{0}\n{1}", path, ex.Message), System.Drawing.Color.Red);
			}
		}*/
	}

}
