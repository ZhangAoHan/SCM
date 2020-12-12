$NOMOD51

$INCLUDE (reg51.inc)
	
NAME CONTROL_GPIO
P4        DATA 0C0H                
segcode segment code
	public CONTROL_GPIO
	rseg segcode
CONTROL_GPIO:
        MOV  A,#0                
Loop2:  JB   ACC.0, SETP41          
	    SETB P4.6                   
	    JMP  CON                  
SETP41: CLR  P4.6                   
CON:    JB   ACC.1,SETP42          
	    SETB P4.7                    
	    JMP  CON1                
SETP42: CLR  P4.7    
CON1:   JB   ACC.2, SETP43          
	    SETB P1.6                   
	    JMP  CON2                  
SETP43: CLR  P1.6                   
CON2:   JB   ACC.3,SETP44          
	    SETB P1.7                    
	    JMP  CON3                
SETP44: CLR  P1.7    
CON3:   INC  A
        JMP  Loop2
		RET

END 
		