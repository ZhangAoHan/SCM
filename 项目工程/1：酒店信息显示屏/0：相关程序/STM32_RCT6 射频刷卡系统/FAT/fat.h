#ifndef __FAT_H__
#define __FAT_H__		    	 
#include <stm32f10x.h>   
//#include <stm32f10x_map.h>
//#include <stm32f10x_nvic.h> 

#include "mmc_sd.h"	
//#include "untogb.h"    
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//FAT 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/5/13 
//版本：V2.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V2.0修改说明  20111025
//1,在网友"螃蟹爱虫"的帮助下,解决了一个重大的bug,现在多数不能支持的卡,都可以支持了.
//其实是FAT_Init函数的初始化部分有错误.现已修正.    
//////////////////////////////////////////////////////////////////////////////////


//重定义区
typedef char  CHAR;
typedef short SHORT;
typedef long  LONG;			   
typedef unsigned long   DWORD;
typedef int             BOOL;
typedef u8              BYTE;
typedef unsigned short  WORD;
  
#define FALSE 0
#define TRUE  1 
					   																    
#define MSDOSFSROOT     0               // cluster 0 means the root dir
#define CLUST_FREE      0               // cluster 0 also means a free cluster
#define MSDOSFSFREE     CLUST_FREE
#define CLUST_FIRST     2             	// first legal cluster number
#define CLUST_RSRVD     0xfff6      	// reserved cluster range
#define CLUST_BAD       0xfff7     		// a cluster with a defect
#define CLUST_EOFS      0xfff8     		// start of eof cluster range
#define CLUST_EOFE      0xffff      	// end of eof cluster range

//dir_clust:当前目录簇号
//FileInfo: 文件指针
//type:     要浏览的文件类型
//返回值:   当前文件索引
//文件夹中 ".":代表当前目录,"..":代表上一级目录
//文件目录项的文件属性位
#define	AM_RDO	0x01	//只读文件
#define	AM_HID	0x02	//隐藏文件
#define	AM_SYS	0x04	//系统文件
#define	AM_VOL	0x08	//卷标
#define AM_LFN	0x0F	//长文件名字段
#define AM_DIR	0x10	//文件夹
#define AM_ARC	0x20	//归档文件
 
//文件信息结构体
#define T_MP1  1<<0
#define T_MP2  1<<1
#define T_MP3  1<<2
#define T_MP4  1<<3
#define T_M4A  1<<4
#define T_3GP  1<<5
#define T_3G2  1<<6
#define T_OGG  1<<7
#define T_ACC  1<<8
#define T_WMA  1<<9
#define T_WAV  1<<10
#define T_MID  1<<11	
#define T_FLAC 1<<12

#define T_LRC  1<<13
#define T_TXT  1<<14
#define T_C    1<<15
#define T_H    1<<16
						 
#define T_FILE 1<<17
#define T_FON  1<<18
#define T_SYS  1<<19

#define T_BMP  1<<20
#define T_JPG  1<<21
#define T_JPEG 1<<22
						 
#define MAX_LONG_NAME_SIZE 80	/* 26*n+2   n=3 */	
//文件信息结构体
//包括文件名,文件类型,文件属性,起始簇和偏移量
typedef struct  
{
	BYTE F_ShortName[8];//保存八个字节的短文件名
	BYTE F_Name[MAX_LONG_NAME_SIZE];
	unsigned long F_StartCluster;			//< file starting cluster for last file accessed
	unsigned long F_Size;					//< file size for last file accessed
	u8  F_Attr;				            	//< file attr for last file accessed
	u32	F_Type;
	//unsigned short CreateTime;			//< file creation time for last file accessed
	//unsigned short CreateDate;			//< file creation date for last file accessed
	unsigned long F_CurClust;				//当前簇号
	unsigned int  F_Offset;				    //在簇号里面的扇区偏移
}FileInfoStruct;

//使用packed 以字节分配.避免数据对齐的问题
//硬盘分区表,每个分区占用16个字节,64个字节支持最大4个分区
//在SD卡上一般使用的是一个,也就是第一个分区.
typedef __packed struct  // length 16 bytes
{			
	BYTE	prIsActive;	    //0x80 表明该分区是否是活动分区
	BYTE	prStartHead;	//开始磁头
	WORD	prStartCylSect;	//开始扇区(低6位)和开始柱面(高10位)
	BYTE	prPartType;		//系统ID
	BYTE	prEndHead;		//结束磁头
	WORD	prEndCylSect;	//结束扇区和结束柱面
	DWORD	prStartLBA;		//相对扇区数,也就是从这里到逻辑扇区0的偏移(以扇区为单位)
	DWORD	prSize;			//总扇区数
}partrecord;  
//磁盘引导区 MBR扇区     
typedef __packed struct 
{
	BYTE	psPartCode[512-64-2];		//MBR引导程序代码存放区
	BYTE	psPart[64];					//硬盘分区表 64个字节
	BYTE	psBootSectSig0;				//2个字节的有效结束标志
	BYTE	psBootSectSig1;
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
}partsector;
//扩展分区
typedef __packed struct  
{
	BYTE	exDriveNumber;     // drive number (0x80)//0x00 for floopy disk 0x80 for hard disk
	BYTE	exReserved1;	   // reserved should always set 0
	BYTE	exBootSignature;   // ext. boot signature (0x29)
#define EXBOOTSIG       0x29
	BYTE	exVolumeID[4];	   // volume ID number
	BYTE	exVolumeLabel[11]; // volume label "NO NAME"
	BYTE	exFileSysType[8];  // fs type (FAT12 or FAT)
}extboot;
//FAT16 DBR区,操作系统引导记录区
typedef __packed struct 
{
	BYTE	bsJump[3];					// jump inst E9xxxx or EBxx90
	BYTE	bsOemName[8];				// OEM name and version
	BYTE	bsBPB[25];					// BIOS parameter block
	BYTE	bsExt[26];					// Bootsector Extension
	BYTE	bsBootCode[448];			// pad so structure is 512b
	BYTE	bsBootSectSig0;				// boot sector signature byte 0x55 
	BYTE	bsBootSectSig1;				// boot sector signature byte 0xAA
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
}bootsector50;

//FAT 16 BPB
typedef __packed struct
{
        WORD	bpbBytesPerSec; // bytes per sector				//512 1024 2048 or 4096
        BYTE	bpbSecPerClust; // sectors per cluster			// power of 2
        WORD	bpbResSectors;  // number of reserved sectors	//1 is recommend
        BYTE	bpbFATs;        // number of FATs				// 2 is recommend
        WORD	bpbRootDirEnts; // number of root directory entries
        WORD	bpbSectors;     // total number of sectors
        BYTE	bpbMedia;       // media descriptor				//0xf8 match the fat[0]
        WORD	bpbFATsecs;     // number of sectors per FAT
        WORD	bpbSecPerTrack; // sectors per track
        WORD	bpbHeads;       // number of heads
        DWORD	bpbHiddenSecs;  // # of hidden sectors
        DWORD	bpbHugeSectors; // # of sectors if bpbSectors == 0
}bpb50;

//FAT32 DBR区,操作系统引导记录区
typedef __packed struct 
{
	BYTE	bsJump[3];					// jump inst E9xxxx or EBxx90
	BYTE	bsOemName[8];				// OEM name and version
	BYTE	bsBPB[53];					// BIOS parameter block
	BYTE	bsExt[26];					// Bootsector Extension
	BYTE	bsBootCode[418];			// pad so structure is 512b
	BYTE	bsBootSectSig2;				// boot sector signature byte 0x00 
	BYTE	bsBootSectSig3;				// boot sector signature byte 0x00
	BYTE	bsBootSectSig0;				// boot sector signature byte 0x55 
	BYTE	bsBootSectSig1;				// boot sector signature byte 0xAA
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
#define BOOTSIG2        0x00
#define BOOTSIG3        0x00
}bootsector710;

//FAT 32 BPB
typedef __packed struct 
{
		WORD	bpbBytesPerSec;	// bytes per sector
		BYTE	bpbSecPerClust;	// sectors per cluster
		WORD	bpbResSectors;	// number of reserved sectors
		BYTE	bpbFATs;		// number of FATs
		WORD	bpbRootDirEnts;	// number of root directory entries
		WORD	bpbSectors;		// total number of sectors
		BYTE	bpbMedia;		// media descriptor
		WORD	bpbFATsecs;		// number of sectors per FAT
		WORD	bpbSecPerTrack;	// sectors per track
		WORD	bpbHeads;		// number of heads
		DWORD	bpbHiddenSecs;	// # of hidden sectors
// 3.3 compat ends here
		DWORD	bpbHugeSectors;	// # of sectors if bpbSectors == 0
// 5.0 compat ends here
		DWORD     bpbBigFATsecs;// like bpbFATsecs for FAT32
		WORD      bpbExtFlags;	// extended flags:
#define FATNUM    0xf			// mask for numbering active FAT
#define FATMIRROR 0x80			// FAT is mirrored (like it always was)
		WORD      bpbFSVers;	// filesystem version
#define FSVERS    0				// currently only 0 is understood
		DWORD     bpbRootClust;	// start cluster for root directory
		WORD      bpbFSInfo;	// filesystem info structure sector
		WORD      bpbBackup;	// backup boot sector
		// There is a 12 byte filler here, but we ignore it
}bpb710;	  

// 文件结构体
typedef __packed struct
{
		BYTE		deName[8];      	// filename, blank filled
#define SLOT_EMPTY      0x00            // slot has never been used
#define SLOT_E5         0x05            // the real value is 0xE5
#define SLOT_DELETED    0xE5            // file in this slot deleted
#define SLOT_DIR		0x2E			// a directorymmm
		BYTE		deExtension[3]; 	// extension, blank filled
		BYTE		deAttributes;   	// file attributes
#define ATTR_NORMAL     0x00            // 普通文件
#define ATTR_READONLY   0x01            // 只读文件
#define ATTR_HIDDEN     0x02            // 隐藏文件
#define ATTR_SYSTEM     0x04            // 系统文件
#define ATTR_VOLUME     0x08            // 卷标
#define ATTR_LONG_FILENAME	0x0F		// 长文件名标志			    
#define ATTR_DIRECTORY  0x10            // 文件夹文件
#define ATTR_ARCHIVE    0x20            // 新的或者归档文件
		BYTE        deLowerCase;    	// NT VFAT lower case flags  (set to zero)
#define LCASE_BASE      0x08            // filename base in lower case
#define LCASE_EXT       0x10            // filename extension in lower case
		BYTE        deCHundredth;   	// hundredth of seconds in CTime
		BYTE        deCTime[2];     	// create time
		BYTE        deCDate[2];     	// create date
		BYTE        deADate[2];     	// access date
		WORD        deHighClust; 		// high bytes of cluster number
		BYTE        deMTime[2];     	// last update time
		BYTE        deMDate[2];     	// last update date
		WORD        deStartCluster; 	// starting cluster of file
		DWORD       deFileSize;  		// size of file in bytes
}direntry;

// number of directory entries in one sector
#define DIRENTRIES_PER_SECTOR	0x10	//when the bpbBytesPerSec=512 

// Structure of a Win95 long name directory entry
typedef __packed struct 
{
		BYTE			weCnt;			// 
#define WIN_LAST        0x40
#define WIN_CNT         0x3f
		BYTE		wePart1[10];
		BYTE		weAttributes;
#define ATTR_WIN95      0x0f
		BYTE		weReserved1;
		BYTE		weChksum;
		BYTE		wePart2[12];
		WORD       	weReserved2;
		BYTE		wePart3[4];
}winentry;

//tinyFAT表结构
//利用FAT表的一致性,一般后一个簇比前一个簇只是大一.
//将FAT表压缩成小的tinyFAT表	  
typedef __packed struct 
{
	#define Fat_Table_Size 10        //tinyFAT表大小
	#define Fat_Head_Size  10		 //tinyFAT表头大小
	u8  Fat_Head_Pos;                //tinyFAT表的上一个表头位置
	u32 Fat_Base_Head[Fat_Head_Size];//tinyFAT表的 表头数组
	u32 Fat_Base_Tab[Fat_Table_Size];//文件的tinyFAT基址表
	u16 Fat_Base_Len[Fat_Table_Size];//基址偏移量
	u8  Fat_Over;                    //文件的tinyFAT表是否全部读出标记位   
}FAT_TABLE;	 

#define WIN_ENTRY_CHARS	13      // Number of chars per winentry

// Maximum filename length in Win95
// Note: Must be < sizeof(dirent.d_name)
#define WIN_MAXLEN      255

// This is the format of the contents of the deTime field in the direntry
// structure.
// We don't use bitfields because we don't know how compilers for
// arbitrary machines will lay them out.
#define DT_2SECONDS_MASK        0x1F    // seconds divided by 2
#define DT_2SECONDS_SHIFT       0
#define DT_MINUTES_MASK         0x7E0   // minutes
#define DT_MINUTES_SHIFT        5
#define DT_HOURS_MASK           0xF800  // hours
#define DT_HOURS_SHIFT          11

// This is the format of the contents of the deDate field in the direntry
// structure.
#define DD_DAY_MASK				0x1F	// day of month
#define DD_DAY_SHIFT			0
#define DD_MONTH_MASK			0x1E0	// month
#define DD_MONTH_SHIFT			5
#define DD_YEAR_MASK			0xFE00	// year - 1980
#define DD_YEAR_SHIFT			9

//外部函数可能用到的数据
extern BYTE FAT32_Enable;	 //FAT32文件系统标志
extern DWORD FirstDirClust;  //根目录簇号
extern DWORD Cur_Dir_Cluster;//当前目录簇号
extern DWORD Fat_Dir_Cluster;//父目录簇号 在FAT文件夹里面CopyDirentruyItem函数中修改!
extern WORD SectorsPerClust;
extern WORD BytesPerSector;
extern FileInfoStruct F_Info[3];
extern u8 fat_buffer[512];//FAT文件系统操作缓冲区				   
//FAT原有的函数	    
unsigned char FAT_Init(void);//初始化												  
unsigned long FAT_NextCluster(unsigned long cluster);//查找下一簇号	
u32 fatClustToSect(u32 cluster);//将簇号转换为扇区号
u8 Get_File_Info(u32 dir_clust,FileInfoStruct *FileInfo,u32 type,u16 *count);//查找文件
void F_Open(FileInfoStruct *FileInfo);//打开文件
unsigned char F_Read(FileInfoStruct *FileInfo,u8 *buf);//读文件，size=0代表整个文件	 
unsigned long FAT_OpenDir(BYTE * dir);//打开目录
FileInfoStruct F_Search(u32 cluster,unsigned char *Name,u32 type);//查找指定名字的文件

u32 FatTab_Next_Cluster(unsigned long cluster);
u32 FatTab_Prev_Cluster(unsigned long cluster);
void Copy_Fat_Table(unsigned long cluster);	  
#endif
















