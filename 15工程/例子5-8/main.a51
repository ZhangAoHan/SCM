;*************	����˵��	**************

;����ʹ��P4.7 P4.6 ����ʾ0~3�ļ���ֵ

;******************************************
;******************************************
;����P4�˿ڵĵ�ַ
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
;// ����: count
;// ����: �жϷ����ӳ���
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


