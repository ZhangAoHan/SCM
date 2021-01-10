using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;  //右键  解析
using System.Text;
//调用System.Runtime.InteropServices;的函数
namespace 外部方法
{
    
    class Program
    {
        [DllImport("User32.dll")]
        public static extern int MessageBox(int h,string m,string c,int type);
        static int Main(string[] args)
        {
            Console.Write("请您输入姓名");
            string name = Console.ReadLine();
            return MessageBox(0,"您好："+name+"\n\n"+"欢迎来到","欢迎提升",0);
        }
    }
}
