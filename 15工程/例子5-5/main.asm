my_seg SEGMENT XDATA                        ; ����XDATA��
           RSEG    my_seg
XBUFFER:   DS      2                        ; ���������ֽڵĴ洢�ռ�
   CSEG AT 0
 
myprog SEGMENT CODE                         ;  ����CODE��
           RSEG    myprog
		   LJMP    main
		   ORG     100H
main:      MOV     DPTR,#XBUFFER     ;  XBUFFER�ĵ�ַ�͸�DPTR�Ĵ���
           CLR      A                ;  �ۼ�������
           MOVX    @DPTR,A           ;  ���ۼ���A�������͸�DPTRָ���XBUFFER����
           INC      DPTR             ;  �Ĵ���DPTR�����ݼ�1
           CLR      A                ;  �ۼ���A����
           MOVX    @DPTR,A           ;  �ۼ���A�������͸�DPTRָ���XBUFFER����
END


