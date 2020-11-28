#include "nes_mapper.h"

#define Map4_Chr_Swap()    ( MAPx->regs[ 0 ] & 0x80 )
#define Map4_Prg_Swap()    ( MAPx->regs[ 0 ] & 0x40 )

void Map4_Set_CPU_Banks(void);
void Map4_Set_PPU_Banks(void);

//*******************************************************************
void MAP4_Reset()
{
	int nPage;
	
	//if(RomHeader->crc32==0xB85AEA68)RomHeader->NES_model=1; //»ê¶·ÂÞ2ÎÞµÐ°æ

	/* Initialize State Registers */
	for ( nPage = 0; nPage < 8; nPage++ )
	{
		MAPx->regs[ nPage ] = 0x00;
	}
	/* Set ROM Banks */
	MAPx->prg0 = 0;
	MAPx->prg1 = 1;
	//	SetBank_CPU();

	/* Set PPU Banks */
	//  if ( Neshd->byVRomSize > 0 )
	if( VROM_1K_SIZE )
	{
		MAPx->chr01 = 0;
		MAPx->chr23 = 2;
		MAPx->chr4  = 4;
		MAPx->chr5  = 5;
		MAPx->chr6  = 6;
		MAPx->chr7  = 7;
		Map4_Set_PPU_Banks();
	}else 
	{
		MAPx->chr01 = MAPx->chr23 = 0;
		MAPx->chr4 = MAPx->chr5 = MAPx->chr6 = MAPx->chr7 = 0;
	}
	/* Initialize IRQ Registers */
	MAPx->irq_enabled = 0;
	MAPx->irq_counter = 0;
	MAPx->irq_counter = 0;
	MAPx->irq_request = 0;
	MAPx->irq_present = 0;
	MAPx->irq_present_vbl = 0;

}
extern int NES_scanline;		//nesÉ¨ÃèÏß
/*-------------------------------------------------------------------*/
/*  Mapper 4 Write Function                                          */
/*-------------------------------------------------------------------*/
void MAP4_Write(uint16 wAddr,uint8 byData  )
{
	uint16 dwBankNum; 
	switch ( wAddr & 0xe001 )
	{
		case 0x8000:
			MAPx->regs[ 0 ] = byData;
			Map4_Set_PPU_Banks();
			Map4_Set_CPU_Banks();//******************************************************
			break;

		case 0x8001:
			MAPx->regs[ 1 ] = byData;
			dwBankNum = MAPx->regs[ 1 ];

			switch ( MAPx->regs[ 0 ] & 0x07 )
			{
				/* Set PPU Banks */
				case 0x00:
					//if ( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						dwBankNum &= 0xfe;
						MAPx->chr01 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break;
				case 0x01:
					//if( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						dwBankNum &= 0xfe;
						MAPx->chr23 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break;

				case 0x02:
					//if( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						MAPx->chr4 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break; 
				case 0x03:
					//if( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						MAPx->chr5 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break;

				case 0x04:
					//if( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						MAPx->chr6 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break;

				case 0x05:
					//if( Neshd->byVRomSize > 0 )
					if( VROM_1K_SIZE )
					{
						MAPx->chr7 = dwBankNum;
						Map4_Set_PPU_Banks();
					}
					break; 
				/* Set ROM Banks */
				case 0x06:
					MAPx->prg0 = dwBankNum;
					Map4_Set_CPU_Banks();//*****************************************************
					break; 
				case 0x07:
					MAPx->prg1 = dwBankNum;
					Map4_Set_CPU_Banks();//*****************************************************
					break;
			}
			break; 
		case 0xa000:
			MAPx->regs[ 2 ] = byData; 
			if ( !(RomHeader->flags_1&0x8) )//ÆÁÄ»VRAM²¼¾Ö 
			{
				if ( byData & 0x01 )
				{
					set_mirroring(0,0,1,1);//Ë®Æ½¾µÏñ
				} else {
					set_mirroring(0,1,0,1);//´¹Ö±¾µÏñ
				}	  
			}
			break; 
		case 0xa001:
			MAPx->regs[ 3 ] = byData;
			break;

		case 0xc000:
			MAPx->regs[ 4 ] = byData;
			MAPx->irq_counter = byData;
			break;

		case 0xc001:
			MAPx->regs[ 5 ] = byData;
			if ( NES_scanline < 240 )
			{
				MAPx->irq_counter |= 0x80;
				MAPx->irq_present = 0xff;
			} else {
				MAPx->irq_counter |= 0x80;
				MAPx->irq_present_vbl = 0xff;
				MAPx->irq_present = 0;
			}
			break;

		case 0xe000:
			MAPx->regs[ 6 ] = byData;
			MAPx->irq_enabled = 0;
			MAPx->irq_request = 0;
			break;

		case 0xe001:
			MAPx->regs[ 7 ] = byData;
			MAPx->irq_enabled = 1;
			MAPx->irq_request = 0;
			break;
	}
}
//***********************************************************************************
void MAP4_HSync( int scanline )
{                                           //  ( PPU.m_REG[1] & 0x08 || PPU.m_REG[1] & 0x10))	                        			
	if( (scanline >= 0 && scanline <= 239) &&( spr_enabled() || bg_enabled()))
	{
		if( MAPx->irq_present_vbl ) {
			MAPx->irq_counter = MAPx->irq_counter;
			MAPx->irq_present_vbl = 0;
		}
		if( MAPx->irq_present ) {
			MAPx->irq_counter = MAPx->irq_counter;
			MAPx->irq_present = 0;
		} else if( MAPx->irq_counter > 0 ) {
			MAPx->irq_counter--;
		}

		if( MAPx->irq_counter == 0 ) {
			if( MAPx->irq_enabled ) {
				MAPx->irq_request = 0xFF;
			}
			MAPx->irq_present = 0xFF;
		}
	}
	if( MAPx->irq_request  ) {
		CPU_IRQ;//		IRQ_REQ;
	}
}			
/*-------------------------------------------------------------------*/
/*  Mapper 4 Set CPU Banks Function                                  */
/*-------------------------------------------------------------------*/
void Map4_Set_CPU_Banks(void)
{
  if ( Map4_Prg_Swap() )//tst r1,#0x40;****************************************
  {                                      //#define ROMLASTPAGE(a) &ROM[ Neshd->byRomSize * 0x4000 - ( (a) + 1 ) * 0x2000 ]
//    ROMBANK0 = ROMLASTPAGE( 1 );       //#define ROMPAGE(a)     &ROM[ (a) * 0x2000 ]
//    ROMBANK1 = ROMPAGE( MAPx->prg1 % ( Neshd->byRomSize << 1 ) );
//    ROMBANK2 = ROMPAGE( MAPx->prg0 % ( Neshd->byRomSize << 1 ) );
//    ROMBANK3 = ROMLASTPAGE( 0 );
//	  set_CPU_banks(num_8k_ROM_banks-2,prg1,prg0,num_8k_ROM_banks-1);
//******************************************************************************	  
	  map89_(-2);  //6502.s
      mapAB_(MAPx->prg1);
      mapCD_(MAPx->prg0);
      mapEF_(-1);//RomHeader->vrom_8k-1
//************************************************************************************
  } else {
//    ROMBANK0 = ROMPAGE( MAPx->prg0 % ( Neshd->byRomSize << 1 ) );
//    ROMBANK1 = ROMPAGE( MAPx->prg1 % ( Neshd->byRomSize << 1 ) );
//    ROMBANK2 = ROMLASTPAGE( 1 );
//    ROMBANK3 = ROMLASTPAGE( 0 );
//	  set_CPU_banks(prg0,prg1,num_8k_ROM_banks-2,num_8k_ROM_banks-1);
//**********************************************************************************	  
      map89_(MAPx->prg0);  //6502.s
      mapAB_(MAPx->prg1);
      mapCD_(-2);
      mapEF_(-1);//RomHeader->vrom_8k-1
//**************************************************************************
  }
}

void Map4_Set_PPU_Banks(void)
{
	if( VROM_1K_SIZE ) {
		if( MAPx->regs[0] & 0x80 ) {
			
			set_PPU_banks(MAPx->chr4, MAPx->chr5, MAPx->chr6, MAPx->chr7,
			              MAPx->chr01,MAPx->chr01+1,MAPx->chr23,MAPx->chr23+1);
//			SetVROM_1K_Bank(0,MAPx->chr4);
//			SetVROM_1K_Bank(1,MAPx->chr5);
//			SetVROM_1K_Bank(2,MAPx->chr6);
//			SetVROM_1K_Bank(3,MAPx->chr7);
//			SetVROM_1K_Bank(4,MAPx->chr01);
//			SetVROM_1K_Bank(5,MAPx->chr01+1);
//			SetVROM_1K_Bank(6,MAPx->chr23);
//			SetVROM_1K_Bank(7,MAPx->chr23+1);			
			
		} else {

			set_PPU_banks(MAPx->chr01,MAPx->chr01+1,MAPx->chr23,MAPx->chr23+1,
			              MAPx->chr4,MAPx->chr5,MAPx->chr6,MAPx->chr7);
//			SetVROM_1K_Bank(4,MAPx->chr4);
//			SetVROM_1K_Bank(5,MAPx->chr5);
//			SetVROM_1K_Bank(6,MAPx->chr6);
//			SetVROM_1K_Bank(7,MAPx->chr7);
//			SetVROM_1K_Bank(0,MAPx->chr01);
//			SetVROM_1K_Bank(1,MAPx->chr01+1);
//			SetVROM_1K_Bank(2,MAPx->chr23);
//			SetVROM_1K_Bank(3,MAPx->chr23+1);						
		}
	} else {
		if( MAPx->regs[0] & 0x80 ) {
		
			  set_VRAM_bank(0, MAPx->chr4);
			  set_VRAM_bank(1, MAPx->chr5);
			  set_VRAM_bank(2, MAPx->chr6);
			  set_VRAM_bank(3, MAPx->chr7);
			  set_VRAM_bank(4, MAPx->chr01+0);
			  set_VRAM_bank(5, MAPx->chr01+1);
			  set_VRAM_bank(6, MAPx->chr23+0);
			  set_VRAM_bank(7, MAPx->chr23+1);		
//********************************************************************************				
//			SetCRAM_1K_Bank( 4, MAPx->chr01+0);
//			SetCRAM_1K_Bank( 5, MAPx->chr01+1);
//			SetCRAM_1K_Bank( 6, MAPx->chr23+0);
//			SetCRAM_1K_Bank( 7, MAPx->chr23+1);
//			SetCRAM_1K_Bank( 0, MAPx->chr4 );
//			SetCRAM_1K_Bank( 1, MAPx->chr5 );
//			SetCRAM_1K_Bank( 2, MAPx->chr6 );
//			SetCRAM_1K_Bank( 3, MAPx->chr7 );
			
		} else {

			  set_VRAM_bank(0, MAPx->chr01+0);
			  set_VRAM_bank(1, MAPx->chr01+1);
			  set_VRAM_bank(2, MAPx->chr23+0);
			  set_VRAM_bank(3, MAPx->chr23+1);
			  set_VRAM_bank(4, MAPx->chr4);
			  set_VRAM_bank(5, MAPx->chr5);
			  set_VRAM_bank(6, MAPx->chr6);
			  set_VRAM_bank(7, MAPx->chr7);
//******************************************************************************
//			SetCRAM_1K_Bank( 0, MAPx->chr01+0);
//			SetCRAM_1K_Bank( 1, MAPx->chr01+1);
//			SetCRAM_1K_Bank( 2, MAPx->chr23+0);
//			SetCRAM_1K_Bank( 3, MAPx->chr23+1);
//			SetCRAM_1K_Bank( 4, MAPx->chr4);
//			SetCRAM_1K_Bank( 5, MAPx->chr5);
//			SetCRAM_1K_Bank( 6, MAPx->chr6);
//			SetCRAM_1K_Bank( 7, MAPx->chr7);
			
		}
	}
} 
//*****************************************************************
void MAP4_Init()
{
	NES_Mapper->Reset = MAP4_Reset;;
	NES_Mapper->Write = MAP4_Write; ; 
	NES_Mapper->HSync = MAP4_HSync;;
}
 


