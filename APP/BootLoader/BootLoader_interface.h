#ifndef     BOOTLODER_H
#define     BOOTLODER_H


typedef void (*P2F_t) (void) ; // p2f data type 

void BL_AsciiToHex ( u8 RecordBuffer[] ) ;
// Depends on base address of flash memory in application linker script
void BL_RecordParsingAndFlashing ( u32 AppBaseAddress , u8 RecordBuffer[]  ) ;
#define LOW_NIPPLE_MASK    0xFFFF0000


void BL_JumpToAnApp( u32 AppBaseAddress ) ;


#endif
