NAME main
my_seg SEGMENT CODE                  ; ���������my_seg
           RSEG    my_seg            ; �л��������my_seg
TABLE:     DB      3,2,5,0xFF        ; �����ĸ�����
	
myprog SEGMENT CODE                  ; ���������myprog
           RSEG    myprog            ; �л��������myprog
		   LJMP main                 ; �ڳ���洢��0x0000��λ����һ����תָ��
		   USING 0                   ; ʹ�õ�һ��Ĵ���
		   ORG 100H                  ; ��λ�������100H��λ��
 main:     MOV     DPTR, #TABLE      ; ��TABLE��ĵ�ַ�͸�DPTR
           MOV     A,#3              ; �������͸��ۼ���A 
           MOVC    A,@A+DPTR         ; ��DPTR+3��ָ��ĳ���Flash�������͵��ۼ���A
		   MOV     P1,0              ; ��P1�˿���0x0000
		   MOV     P1,A              ; ��P1�˿����ۼ���A������
END
