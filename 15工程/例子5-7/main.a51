
;*************	功能说明	**************

;程序使用P4.7 P4.6 来显示0~3的计数值

;******************************************
;******************************************
;定义P4端口的地址
P4        DATA 0C0H
;******************************************
    CSEG AT  0x0000
	LJMP main
	my_prog  SEGMENT CODE
		     RSEG my_prog
             ORG 0x100		
Main:
	USING   0
Loop1:
	MOV     A,#0
Loop2:
	JB   ACC.0, SETP41
	SETB P4.7
	JMP  CON
SETP41:
	CLR  P4.7
CON:
	JB   ACC.1,SETP42
	SETB P4.6
	JMP  CON1
SETP42:
	CLR  P4.6
CON1:
    MOV  R0,#20
dly:
	ACALL   delay
	DEC R0
    CJNE    R0,#0,dly
    INC     A
    CJNE    A,#4,Loop2
    JMP    Loop1	
;********************************

;//==============================
;// 函数: delay
;// 描述: 延时子程序。
;//==============================
delay:
    MOV		R3, #0FFH
delay_1:	
   MOV		R4, #0FFH
	 
delay_2:
	DEC		R4				;
	CJNE	R4,#0,delay_2	;
	DEC		R3
	CJNE    R3,#0,delay_1	;
	RET
	
	END


