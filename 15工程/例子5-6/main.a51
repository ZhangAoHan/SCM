NAME main
idata_seg  SEGMENT CODE 
	          RSEG idata_seg
    i:  DW     1234 
	j:	DW     6789 
xdata_seg  SEGMENT XDATA
              RSEG xdata_seg
    k:    DS  2

              CSEG  AT 0x0000
	          LJMP  main
              ORG   0x0100 
				  
 main:        MOV     DPTR,#i             
			  MOV     A,#1
			  MOVC    A,@A+DPTR             
			  MOV     R0,A
              MOV     DPTR,#j
			  MOV     A,#1
			  MOVC    A,@A+DPTR
              ADD     A,R0
			  MOV     DPTR,#k
			  INC     DPTR
			  MOVX    @DPTR,A
			  MOV     DPTR,#i             
			  MOV     A,#0
			  MOVC    A,@A+DPTR             
			  MOV     R0,A
              MOV     DPTR,#j
			  MOV     A,#0
			  MOVC    A,@A+DPTR
              ADDC    A,R0                 
			  MOV     DPTR,#K
			  MOVX    @DPTR,A
END