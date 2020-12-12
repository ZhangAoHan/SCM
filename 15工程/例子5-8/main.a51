;*************	功能说明	**************

;程序使用P4.7 P4.6 来显示0~3的计数值

;******************************************
;******************************************
;定义P4端口的地址
P4        DATA 0C0H
;******************************************
	
	my_prog  SEGMENT CODE
		     RSEG my_prog
		     LJMP main
			 ORG 0x0003
			 LJMP count
             ORG 0x100		
Main:
	    USING   0
        MOV SP, #40H
	    SETB IT0
	    SETB EX0
	    SETB EA
		MOV  A,#0
loop:   ljmp loop
;********************************

;//==============================
;// 函数: count
;// 描述: 中断服务子程序
;//==============================
count:  
        PUSH DPH
	    PUSH 02H
    	JB   ACC.0, SETP41
	    SETB P4.7
	    JMP  CON
SETP41: CLR  P4.7
CON:    JB   ACC.1,SETP42
	    SETB P4.6
	    JMP  CON1
SETP42: CLR  P4.6
CON1:	INC  A
	    POP  DPH
		POP  02H
	    RETI
END


