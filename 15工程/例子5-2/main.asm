mybits SEGMENT BIT                
           RSEG    mybits
FLAG:       DBIT    1              
P11         DATA    90H           
GREEN_LED  BIT     P1.2         
	     
myprog SEGMENT CODE               
           RSEG    myprog
		   LJMP    main
		   ORG     100H
main:      SETB    GREEN_LED       
           JB      FLAG, is_on      
           SETB    FLAG
           CLR     ACC.5          
is_on:     CLR     FLAG
           CLR     GREEN_LED      
END


