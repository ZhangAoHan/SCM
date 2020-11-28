#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "delay.h"	 	
#include "vs10xx.h"		
#include "dm9000.h"		
#include "w25qxx.h"	 	
#include "fattester.h"	 

//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)DM9000_WriteReg,"void DM9000_WriteReg(u16 reg,u16 data)", 
	(void*)DM9000_ReadReg,"u16 DM9000_ReadReg(u16 reg)", 
	(void*)W25QXX_Erase_Chip,"void W25QXX_Erase_Chip(void)", 
	(void*)VS_RD_Reg,"u16 VS_RD_Reg(u8 address)", 
		
	(void*)VS_WRAM_Write,"void VS_WRAM_Write(u16 addr,u16 val)", 
	(void*)VS_WRAM_Read,"u16 VS_WRAM_Read(u16 addr)", 
	(void*)VS_SPK_Set,"void VS_SPK_Set(u8 sw)", 
  	(void*)gui_show_ptstr,"void gui_show_ptstr(u16 x,u16 y,u16 xend,u16 yend,u16 offset,u16 color,u8 size,u8 *str,u8 mode)", 
 	(void*)W25QXX_Erase_Chip,"void W25QXX_Erase_Chip(void)", 
 	(void*)gui_color_chg,"u16 gui_color_chg(u32 rgb)", 
 	(void*)bmp_encode,"u8 bmp_encode(u8 *filename,u16 x,u16 y,u16 width,u16 height,u8 mode)", 
 
	(void*)mf_mount,"u8 mf_mount(u8* path,u8 mt)",

	(void*)mf_open,"u8 mf_open(u8*path,u8 mode)",
	(void*)mf_close,"u8 mf_close(void)",
	(void*)mf_read,"u8 mf_read(u16 len)",
	(void*)mf_write,"u8 mf_write(u8*dat,u16 len)",
 	(void*)mf_opendir,"u8 mf_opendir(u8* path)",
	(void*)mf_readdir,"u8 mf_readdir(void)",

 	(void*)mf_scan_files,"u32 mf_scan_files(u8 * path)",
 	(void*)mf_showfree,"u32 mf_showfree(u8 *drv)",
	(void*)mf_lseek,"u8 mf_lseek(u32 offset)",
	(void*)mf_tell,"u8 mf_tell(void)",
 	(void*)mf_size,"u32 mf_size(void)",


	(void*)mf_fmkfs,"u8 mf_fmkfs(u8 drv,u8 mode,u16 au)",
	(void*)mf_mkdir,"u8 mf_mkdir(u8*name)",
	(void*)mf_unlink,"u8 mf_unlink(u8 *name)",
 	(void*)mf_rename,"u8 mf_rename(u8 *oldname,u8* newname)",
  	(void*)SCCB_WR_Reg,"u8 SCCB_WR_Reg(u8 reg,u8 data)",
  	(void*)SCCB_RD_Reg,"u8 SCCB_RD_Reg(u8 reg)",
	(void*)mf_scan_files,"u8 mf_scan_files(u8 * path)", 	 
	(void*)ai_load_picfile,"u8 ai_load_picfile(const u8 *filename,u16 x,u16 y,u16 width,u16 height,u8 fast)", 	 
		
};		
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















