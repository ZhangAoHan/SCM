//引用命名空间
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;







//命名空间或项目名称
namespace cshangp程序结构
{
    //Program类
    class Program
    {
        int A = 0;   //实例方法
        static int B=0;  //静态方法

        static void Main(string[] args)   //static 静态   main主函数   程序的启动
        {
            class1 c1 = new class1();    //将class1实例化
            c1.sla();   //调用class1类中的函数
            c1.vir();
           // const double pi = 3.1415926;  //定义常量
            ly(8);   //静态方法可以直接调用静态方法
            //Program.ly(8);   //与上面效果一样
            ly(7);
            ly(6);
            Console.ReadKey();
            B=1;  //静态方法只能调用静态变量
            
        }


        //方法体(不是静态就是实例)  静态方法体
         static void ly(int num)
        {
            int a = 1;
            for (int i = num; i > 0; i--) a *= i;
            Console.WriteLine("{0}的阶乘是：{1}",num,a);
        }
         void LY()   //实例方法
         {
             A = 0;
             B = 1;//实例方法可以调用静态变量和实例变量
             ly(5);   //实例方法可以调用静态函数    但静态方法1不能调用实例函数
         }
    }
    class class1   //新建一个类
    {
        public virtual void vir()   //虚方法
        {
            Console.WriteLine("虚方法");
        }
        public void sla()    //非虚方法
        {
            Console.WriteLine("非虚方法");
        }
    }
  //  class class2 : class1   //class2继承class1
  //  {
   //     public new void non()
   //     {
    //        class1 c1 = new class1();
    //        c1.vir();
     //       c1.sla();
      //  }
  //  }
}
