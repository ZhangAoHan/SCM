
;********************************************************************************************************/

;define the stack size
;定义堆栈的大小
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         0
IRQ_STACK_LEGTH         EQU         256
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

NoInt       EQU 0x80

USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

    IMPORT __use_no_semihosting_swi

;The imported labels
;引入的外部标号在这声明
    IMPORT  FIQ_Exception                   ;Fast interrupt exceptions handler 快速中断异常处理程序
    IMPORT  __main                          ;The entry point to the main function C语言主程序入口 
    IMPORT  TargetResetInit                 ;initialize the target board 目标板基本初始化

;The emported labels
;给外部使用的标号在这声明
    EXPORT  bottom_of_heap
    EXPORT  StackUsr
    
    EXPORT  Reset
    EXPORT __user_initial_stackheap

    CODE32
    PRESERVE8
    AREA    vectors,CODE,READONLY
        ENTRY

;interrupt vectors
;中断向量表
Reset
        LDR     PC, ResetAddr
        LDR     PC, UndefinedAddr
        LDR     PC, SWI_Addr
        LDR     PC, PrefetchAddr
        LDR     PC, DataAbortAddr
        DCD     0xb9205f80
        LDR     PC, [PC, #-0xff0]
        LDR     PC, FIQ_Addr

ResetAddr           DCD     ResetInit
UndefinedAddr       DCD     Undefined
SWI_Addr            DCD     SoftwareInterrupt
PrefetchAddr        DCD     PrefetchAbort
DataAbortAddr       DCD     DataAbort
Nouse               DCD     0
IRQ_Addr            DCD     0
FIQ_Addr            DCD     FIQ_Handler


;未定义指令
Undefined
        B       Undefined

;软中断
SoftwareInterrupt			
        B       SoftwareInterrupt	

;取指令中止
PrefetchAbort
        B       PrefetchAbort

;取数据中止
DataAbort
        B       DataAbort

;快速中断
FIQ_Handler
        STMFD   SP!, {R0-R3,R12,LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3,R12,LR}
        SUBS    PC,  LR,  #4
        

;********************************************************************************************************/
InitStack    
        MOV     R0, LR
;Build the SVC stack
;设置管理模式堆栈
        MSR     CPSR_c, #0xd3		
        LDR     SP, StackSvc	
;Build the IRQ stack	
;设置中断模式堆栈
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;Build the FIQ stack
;设置快速中断模式堆栈
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;Build the DATAABORT stack
;设置中止模式堆栈
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;Build the UDF stack
;设置未定义模式堆栈
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;Build the SYS stack
;设置系统模式堆栈
        MSR     CPSR_c, #0x5f
        LDR     SP, =StackUsr

        MOV     PC, R0


;********************************************************************************************************/
ResetInit
        
        BL      InitStack               ;初始化堆栈 Initialize the stack
        BL      TargetResetInit         ;目标板基本初始化 Initialize the target board
                                        ;跳转到c语言入口 Jump to the entry point of C program
        B       __main

;********************************************************************************************************/
__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
;    LDR   r1,=StackUsr
    MOV   pc,lr


StackSvc           DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)* 4
StackIrq           DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)* 4
StackFiq           DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)* 4
StackAbt           DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)* 4
StackUnd           DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)* 4


    
;/* 分配堆栈空间 */
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;Stack spaces for Administration Mode 管理模式堆栈空间
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;Stack spaces for Interrupt ReQuest Mode 中断模式堆栈空间
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;Stack spaces for Fast Interrupt reQuest Mode 快速中断模式堆栈空间
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;Stack spaces for Suspend Mode 中止义模式堆栈空间
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;Stack spaces for Undefined Mode 未定义模式堆栈


        AREA    Heap, DATA, NOINIT
bottom_of_heap    SPACE   1

        AREA    Stacks, DATA, NOINIT
StackUsr

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
