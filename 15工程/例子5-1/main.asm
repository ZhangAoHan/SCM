NAME main
my_seg SEGMENT CODE                  ; 声明代码段my_seg
           RSEG    my_seg            ; 切换到代码段my_seg
TABLE:     DB      3,2,5,0xFF        ; 声明四个常数
	
myprog SEGMENT CODE                  ; 声明代码段myprog
           RSEG    myprog            ; 切换到代码段myprog
		   LJMP main                 ; 在程序存储器0x0000的位置有一条跳转指令
		   USING 0                   ; 使用第一组寄存器
		   ORG 100H                  ; 定位到代码段100H的位置
 main:     MOV     DPTR, #TABLE      ; 将TABLE表的地址送给DPTR
           MOV     A,#3              ; 将常数送给累加器A 
           MOVC    A,@A+DPTR         ; 将DPTR+3所指向的程序Flash的内容送到累加器A
		   MOV     P1,0              ; 将P1端口置0x0000
		   MOV     P1,A              ; 将P1端口置累加器A的内容
END
