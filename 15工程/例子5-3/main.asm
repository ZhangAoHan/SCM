myvars SEGMENT IDATA            ;����IDATA��
           RSEG    myvars
BUFFER:    DS      100          ; ����100���ֽ�
 CSEG AT 0                      ; ��λ������洢��0x0000��λ�á�
	 
myprog SEGMENT CODE             ; ��������
           RSEG     myprog
		   LJMP     main        ; ��������ת��main
		   ORG      100H        ; ��λ��100H��λ��
main:      MOV     R0,#BUFFER   ; ��BUFFER�ĵ�ַ��R0
           MOV     A,@R0        ; ��R0ָ����ڲ�RAM�����ݸ��ۼ���A
           INC      R0          ; ��R0�Ĵ��������ݵ���1
           MOV     @R0,A        ; ���ۼ���A�����ݸ���R0�Ĵ�����ָ��Ĵ洢����ַ
END

