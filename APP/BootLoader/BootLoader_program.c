#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/SCB/SCB_interface.h"
#include "../../MCAL/FMI/FMI_interface.h"

#include "BootLoader_interface.h"


u32 APP_Address = 0x08004004 ;


void BL_AsciiToHex ( u8 RecordBuffer[] )
{
	u16 i = 0 ;
	while ( RecordBuffer[i] != 'L' )
	{
		if ( RecordBuffer[i] >= '0' && RecordBuffer[i] <= '9' )
		{
			RecordBuffer[i] -= '0' ;
		}
		else if ( RecordBuffer[i] >= 'A' && RecordBuffer[i] <= 'F' )
		{
			RecordBuffer[i] -= 'A' ;
			RecordBuffer[i] += 10 ;
		}
		else if ( RecordBuffer[i] >= 'a' && RecordBuffer[i] <= 'f' )
		{
			RecordBuffer[i] -= 'a' ;
			RecordBuffer[i] += 10 ;
		}
		else
		{
			/* Do Nothing */
		}
		i++ ;
	}
}


void BL_RecordParsingAndFlashing ( u32 AppBaseAddress , u8 RecordBuffer[]  )
{
	u32 Address = AppBaseAddress ;
	u8 CC = 0 ;
	u8 FirstCharInData = 9 ;
	u8 Data[20] = {0} ;
	u16 Counter = 0 ; // u16 due to 5000 element buffer
// L is specific for the ESP module which send "CLOSED" at the end of communication  L not C becouse C might be in hex file when L is not 
	while ( RecordBuffer[Counter] != 'L' ) 
	{
		if ( RecordBuffer[Counter] == ':' && RecordBuffer[Counter+1] != ':'  )
		{
			/* Pars CC */
			CC = ( (RecordBuffer[Counter+1]<<4) | RecordBuffer[Counter+2] ) ;
			/* Pars Data */
			if ( RecordBuffer[Counter+8] == 0 ) // Record Type => Data Record
			{
				for ( u8 i = 0 ; i < CC ; i++ )
				{
					/* pars the data */
					Data[i] = ( ( RecordBuffer[ Counter + FirstCharInData ] << 4 ) | ( RecordBuffer [ Counter + FirstCharInData + 1  ] ) ) ;
					FirstCharInData += 2 ;
				}
				FirstCharInData = 9 ;
				/* Pars Address */
				Address &= LOW_NIPPLE_MASK ; // clear low nipple
				Address |= (u32) ((((u32)RecordBuffer[Counter + 3]) << 12 ) |
							(((u32)RecordBuffer[Counter + 4]) << 8)  |
							(((u32)RecordBuffer[Counter + 5] )<< 4)  |
							(((u32)RecordBuffer[Counter + 6] )<< 0)  );
				/* Write Data */
				FMI_Write( Address , Data , CC ) ;

			}
			else if ( RecordBuffer[Counter+8] == 5 ) // end of hex file 
				break ;
		}
		Counter++ ;
	}
}


void BL_JumpToAnApp( u32 AppBaseAddress )
{
	P2F_t StartupcodeAddress ;
	SCB_ResetVectorTableAddress( AppBaseAddress) ;
	// startup code address (which is the address of rest handler) be in the vector table address + 4 (data sheet page 41 at the Reference Manuel )
	// Address must be casted to pointer to function due to the calling in the next step.
	StartupcodeAddress =  *( (P2F_t*) (AppBaseAddress + 0x4) ) ;
	StartupcodeAddress() ;
}



