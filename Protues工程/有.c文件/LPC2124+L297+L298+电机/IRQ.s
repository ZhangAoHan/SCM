
;********************************************************************************************************/


NoInt       EQU 0x80

USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

    CODE32
    PRESERVE8
    AREA    IRQ,CODE,READONLY

    MACRO
$IRQ_Label HANDLER $IRQ_Exception_Function

        EXPORT  $IRQ_Label                      ; The label for exports ����ı��
        IMPORT  $IRQ_Exception_Function         ; The imported labels ���õ��ⲿ���

$IRQ_Label
        SUB     LR, LR, #4                      ; Calculate the returning address ���㷵�ص�ַ
        STMFD   SP!, {R0-R3, R12, LR}           ; Protects the task environments �������񻷾�
        MRS     R3, SPSR                        ; Protects the status variable ����״̬
        STMFD   SP, {R3,LR}^                    ; Protects SPSR and SP in user status, Notice: DO NOT write back.����SPSR���û�״̬��SP,ע�ⲻ�ܻ�д
                                                ; If the SP is written back, it should be adjusted to its appropriate value later.�����д�����û���SP�����Ժ���Ҫ����SP
        NOP
        SUB     SP, SP, #4*2

        MSR     CPSR_c, #(NoInt | SYS32Mode)    ; Switch to the System Mode �л���ϵͳģʽ 
       
        BL      $IRQ_Exception_Function         ; call the C interrupt handler funtion ����c���Ե��жϴ������

        MSR     CPSR_c, #(NoInt | IRQ32Mode)    ; Switch bak to IRQ mode �л���irqģʽ
        LDMFD   SP, {R3,LR}^                    ; Recover SPSR and SP in user status, Notic: DO NOT write back. �ָ�SPSR���û�״̬��SP,ע�ⲻ�ܻ�д
                                                ; If the SP is written back, it should be adjusted to its appropriate value later.�����д�����û���SP�����Ժ���Ҫ����SP
        MSR     SPSR_cxsf, R3
        ADD     SP, SP, #4*2                    ; 

        LDMFD   SP!, {R0-R3, R12, PC}^          ;
    MEND

;/* ��������жϾ�����û�����ʵ������ı� */
;/* Add interrupt handler here��user could change it as needed */

;Timer0_Handler  HANDLER Timer0

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
