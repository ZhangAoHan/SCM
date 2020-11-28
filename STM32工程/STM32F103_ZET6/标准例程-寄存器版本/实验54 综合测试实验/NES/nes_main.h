#ifndef __NES_MAIN_H
#define __NES_MAIN_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//��������ֲ������ye781205��NESģ��������
//ALIENTEK STM32������
//NES������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/1
//�汾��V1.0  			  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#define NES_SKIP_FRAME 	2		//����ģ������֡��,Ĭ����2֡
 
 
#define INLINE 	static inline
#define int8 	char
#define int16 	short
#define int32 	int
#define uint8 	unsigned char
#define uint16 	unsigned short
#define uint32 	unsigned int
#define boolean uint8 



//nes��Ϣͷ�ṹ��
typedef struct
{
	unsigned char id[3]; // 'NES'
	unsigned char ctrl_z; // control-z
	unsigned char num_16k_rom_banks;
	unsigned char num_8k_vrom_banks;
	unsigned char flags_1;
	unsigned char flags_2;
	unsigned char reserved[8];
}NES_header;   
 
extern int MapperNo;			//map���
extern int NES_scanline;		//ɨ����
extern NES_header *RomHeader;	//rom�ļ�ͷ 
extern int VROM_1K_SIZE;
extern int VROM_8K_SIZE; 
extern u8 cpunmi;  				//cpu�жϱ�־  �� 6502.s����
extern u8 cpuirq;			
extern u8 PADdata;   			//�ֱ�1��ֵ 
extern u8 PADdata1;   			//�ֱ�1��ֵ 
extern u8 lianan_biao;			//������־ 
#define  CPU_NMI  cpunmi=1;
#define  CPU_IRQ  cpuirq=1;
#define  NES_RAM_SPEED	0 	 	//1:�ڴ�ռ��С  0:�ٶȿ�


void cpu6502_init(void);		//�� cart.s
void run6502(u32); 		   		//�� 6502.s 
u8 nes_load_rom(void);
void nes_sram_free(void);
u8 nes_sram_malloc(u32 romsize);
u8 nes_load(u8* pname);
void nes_set_window(void);
void nes_get_gamepadval(void);
void nes_emulate_frame(void);
void debug_6502(u16 reg0,u8 reg1);

void nes_i2s_dma_tx_callback(void);
int nes_sound_open(int samples_per_sync,int sample_rate);
void nes_sound_close(void);
void nes_apu_fill_buffer(int samples,u8* wavebuf); 

extern u32 get_crc32(u8* buf, u32 len);
#endif







