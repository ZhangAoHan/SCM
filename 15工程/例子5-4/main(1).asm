myvar  SEGMENT DATA           ; �������ݶ�
           RSEG    myvar
VALUE:     DS      1          ; ��DATA�ռ䱣��һ���ֽ� 

IO_PORT2   DATA    0A0H        ; ���⹦�ܼĴ���
VALUE2     DATA    20H         ; �洢���ľ��Ե�ַ
     
myprog SEGMENT CODE            ; ����CODE��
           RSEG    myprog
		   LJMP    main
		   ORG     100H
main:      MOV     A,IO_PORT2   ; ֱ�ӷ���DATA
           ADD     A,VALUE
           MOV     VALUE2,A
           MOV     R1,#VALUE    ; ����VALUE��ֵR1
           ADD     A,@R1        ; ��ӷ���VALUE
END


