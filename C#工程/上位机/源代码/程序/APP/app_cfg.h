/*------------------------------------------------------------------------------------
        		   STM32 UCOS-II �����񹤳�ģ��(USART)
 ˵��: дAPP����app.c���,д��Ӳ����ص���������bsp.c��ɲ��Ҷ�����Ӧ��ͷ�ļ�,����д��
 	   includes.h��.��ģ�����Ѿ����UCOS-II��STM32�ϵ���ֲ,���Ը�����Ŀ�Ĳ�ͬ�ü��ں�
	   ��С�����,����os_cfg.h��ɲü�.�������Դ�3��LED��ʾ1�����ڷ��͵Ķ�����ִ��.
	   
	   ����һ������Ĳ���:								
	   *(1) ��app_cfg.h�����������ȼ���ջ��С,Ҳ���Ǻ궨�塣
	   *(2) ��main�ļ��ж�������ջ OS_STK task_led1_stk[TASK_LED1_STK_SIZE]��
	   *(3) ��app.c�ж�������ľ�������Ҫ��ʲô,Ҳ����дһ������ģ��,��ס��Ҫ��app.h����������.
	   *(4) ��main�����д������� OSTaskCreate(Task_LED1,(void *)0,&task_led1_stk[TASK_LED1_STK_SIZE-1], TASK_LED1_PRIO);
	   *(5) �������м������һ������Ĵ�����

 ʱ��: 2013��8��19��       BoX��д
-------------------------------------------------------------------------------------*/
#ifndef __APP_CFG_H
#define __APP_CFG_H

/*******************�����������ȼ�*******************/   
#define TASK_LED1_PRIO          4
#define TASK_LED2_PRIO          3
#define TASK_LED3_PRIO          2
#define TASK_USART_PRIO         1           
 
/************����ջ��С����λΪ OS_STK ��************/   
#define TASK_LED1_STK_SIZE      80 
#define TASK_LED2_STK_SIZE	    80
#define TASK_LED3_STK_SIZE	    80
#define TASK_USART_STK_SIZE     80

#endif
