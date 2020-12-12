myvars SEGMENT IDATA            ;定义IDATA段
           RSEG    myvars
BUFFER:    DS      100          ; 保留100个字节
 CSEG AT 0                      ; 定位到程序存储器0x0000的位置。
	 
myprog SEGMENT CODE             ; 定义代码段
           RSEG     myprog
		   LJMP     main        ; 无条件跳转到main
		   ORG      100H        ; 定位到100H的位置
main:      MOV     R0,#BUFFER   ; 将BUFFER的地址给R0
           MOV     A,@R0        ; 将R0指向的内部RAM的内容给累加器A
           INC      R0          ; 将R0寄存器的内容递增1
           MOV     @R0,A        ; 将累加器A的内容给了R0寄存器所指向的存储器地址
END

