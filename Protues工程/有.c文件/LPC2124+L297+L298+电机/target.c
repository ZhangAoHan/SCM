/**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: target.c
**��        ��: lpc210x�������ֵ�ARM��Ŀ�������Ĵ��룬�����쳣��������Ŀ����ʼ������
**              ÿ������Ӧ����������ļ��Ŀ������û����ݳ������Ҫ�޸ı��ļ���
**ע        �⣺���ļ�������ARM��32λ���룩��ʽ���룬���򣬱������init.s��vector.s�ļ�
**              ���C���벻��ʹ��ARM��32λ���룩��ʽ����
********************************************************************************************************/

#define IN_TARGET
#include "config.h"

/*********************************************************************************************************
** ��������: IRQ_Exception
** ��������: �ж��쳣��������û�������Ҫ�Լ��ı����
**
********************************************************************************************************/
void __irq IRQ_Exception(void)
	{
    while(1);                   // ��һ���滻Ϊ�Լ��Ĵ���
	}

/*********************************************************************************************************
** ��������: FIQ_Exception
** ��������: �����ж��쳣��������û�������Ҫ�Լ��ı����
**           
********************************************************************************************************/
        void FIQ_Exception(void)
{
    while(1);                   // ��һ���滻Ϊ�Լ��Ĵ���
}

/*********************************************************************************************************
** ��������: TargetInit
** ��������: Ŀ����ʼ�����룬����Ҫ�ĵط����ã�������Ҫ�ı�

********************************************************************************************************/
        void TargetInit(void)
{
   
  PWMPR=0x00;                      //����Ƶ,����Ƶ��ΪFpclk
  PWMMCR=0x02;                     //����PWMMR0ƥ��ʱ��λPWMTC
  PWMMR0=Fpclk/2;                     //����PWM����
  PWMMR6=Fpclk/2/2;                     //����PWMռ�ձ�
  PWMLER=0x41;                     //PWMMR0,PWMMR6����
  PWMPCR=0x4000;                   //����PWM6���,����PWM
  PWMTCR=0x09;                     //������ʱ��,PWMʹ�� 
    /* ����Լ��Ĵ��� */
}

/*********************************************************************************************************
** ��������: TargetResetInit
** ��������: ����main����ǰĿ����ʼ�����룬������Ҫ�ı䣬����ɾ��

********************************************************************************************************/
        void TargetResetInit(void)
{

    /* ����ϵͳ������ʱ�� */
/*    PLLCON = 1;
#if ((Fcclk / 4) / Fpclk) == 1
    VPBDIV = 0;
#endif

#if ((Fcclk / 4) / Fpclk) == 2
    VPBDIV = 2;
#endif

#if ((Fcclk / 4) / Fpclk) == 4
    VPBDIV = 1;
#endif

#if (Fcco / Fcclk) == 2
    PLLCFG = ((Fcclk / Fosc) - 1) | (0 << 5);
#endif
#if (Fcco / Fcclk) == 4
    PLLCFG = ((Fcclk / Fosc) - 1) | (1 << 5);
#endif
#if (Fcco / Fcclk) == 8
    PLLCFG = ((Fcclk / Fosc) - 1) | (2 << 5);
#endif
#if (Fcco / Fcclk) == 16
    PLLCFG = ((Fcclk / Fosc) - 1) | (3 << 5);
#endif
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    while((PLLSTAT & (1 << 10)) == 0);
    PLLCON = 3;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
*/  
    
    /* ���ô洢������ģ�� */
    MAMCR = 2;		//MAMCR 8u2 00��MAM ���ܱ���ֹ��01��MAM���ܲ���ʹ�ܡ�10��MAM������ȫʹ��
    /* MAMTIM 8u3
    000��0������
    001��1��һ��ʱ����ֻ�� 1 ��������ʱ�ӣ�cclk������ MAM ȡָ��
    010��2��һ��ʱ����ֻ��2��������ʱ�ӣ�cclk������MAMȡָ��
    011��3��һ��ʱ����ֻ�� 3 ��������ʱ�ӣ�cclk������ MAM ȡָ��
    100��4��һ��ʱ����ֻ��4��������ʱ�ӣ�cclk������ MAM ȡָ��
    101��5��һ��ʱ����ֻ��5 ��������ʱ�ӣ�cclk������ MAM ȡָ��
    110��6��һ��ʱ����ֻ�� 6 ��������ʱ�ӣ�cclk������ MAM ȡָ��
    111��7��һ��ʱ����ֻ��7��������ʱ�ӣ�cclk������ MAM ȡָ��
     */
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
       
    /* ��ʼ��VIC */
    VICIntEnClr = 0xffffffff;//�������ж�ʹ�ܣ������ж�
    VICVectAddr = 0;//Ĭ��������ַ�Ĵ���
    VICIntSelect = 0;//1����Ӧ���ж��������ΪFIQ��0����Ӧ���ж��������ΪIRQ��

    /* ����Լ��Ĵ��� */

}

#include "rt_sys.h"
#include "stdio.h"

#pragma import(__use_no_semihosting_swi)
#pragma import(__use_two_region_memory)

        int __rt_div0(int a)
{
    a = a;
    return 0;
}

        int fputc(int ch,FILE *f)
{
    ch = ch;
    f = f;
    return 0;
}

    int fgetc(FILE *f)
{
    f = f;
    return 0;
}


        int _sys_close(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        int _sys_write(FILEHANDLE fh, const unsigned char * buf,
                      unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    return 0;
}
        int _sys_read(FILEHANDLE fh, unsigned char * buf,
                     unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    
    return 0;
}

       void _ttywrch(int ch)
{
    ch = ch;
}

        int _sys_istty(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
        int _sys_seek(FILEHANDLE fh, long pos)
{
    fh = fh;
    return 0;
}
        int _sys_ensure(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        long _sys_flen(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
       int _sys_tmpnam(char * name, int sig, unsigned maxlen)
{
    name = name;
    sig = sig;
    maxlen = maxlen;
    return 0;
}

        void _sys_exit(int returncode)
{
    returncode = returncode;
}

        char *_sys_command_string(char * cmd, int len)
{
    cmd = cmd;
    len = len;
    return 0;
}
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
