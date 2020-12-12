my_seg SEGMENT XDATA                        ; 定义XDATA段
           RSEG    my_seg
XBUFFER:   DS      2                        ; 保留两个字节的存储空间
   CSEG AT 0
 
myprog SEGMENT CODE                         ;  定义CODE段
           RSEG    myprog
		   LJMP    main
		   ORG     100H
main:      MOV     DPTR,#XBUFFER     ;  XBUFFER的地址送给DPTR寄存器
           CLR      A                ;  累加器清零
           MOVX    @DPTR,A           ;  将累加器A的内容送给DPTR指向的XBUFFER区域
           INC      DPTR             ;  寄存器DPTR的内容加1
           CLR      A                ;  累加器A清零
           MOVX    @DPTR,A           ;  累加器A的内容送给DPTR指向的XBUFFER区域
END


