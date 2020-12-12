myvar  SEGMENT DATA           ; 定义数据段
           RSEG    myvar
VALUE:     DS      1          ; 在DATA空间保存一个字节 

IO_PORT2   DATA    0A0H        ; 特殊功能寄存器
VALUE2     DATA    20H         ; 存储器的绝对地址
     
myprog SEGMENT CODE            ; 定义CODE段
           RSEG    myprog
		   LJMP    main
		   ORG     100H
main:      MOV     A,IO_PORT2   ; 直接访问DATA
           ADD     A,VALUE
           MOV     VALUE2,A
           MOV     R1,#VALUE    ; 加载VALUE的值R1
           ADD     A,@R1        ; 间接访问VALUE
END


