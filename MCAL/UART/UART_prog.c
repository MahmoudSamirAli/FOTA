#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "UART_private.h"
#include "UART_interface.h"


void UART_Init ( UART_Config * Option )
{
	/* Over Sampling And Baud Rate */
	switch ( Option -> OverSampling )
	{
		case OverSampling_16 : CLR_BIT ( UART1 -> CR1 , OVER8 )  ;
//		    				   UART1 -> BRR = 0x341 ; // 9600
								UART1-> BRR = 0x45 ; // 115200
							   break ; 
		case OverSampling_8  : SET_BIT ( UART1 -> CR1 , OVER8 )  ; 
		    				   UART1 -> BRR = 0x681 ; // 9600
							    break ; 
		default : /* DO Nothing */ break ;
	}
    /* ENABLE RECIEVER & TRANSMITTER */
	switch ( Option -> Mode )
	{
		case Mode_Tranmitter_Only :         SET_BIT (UART1 -> CR1 , TE ) ; break ;
		case Mode_Reciever_Only   :         SET_BIT (UART1 -> CR1 , RE ) ; break ; 
		case Mode_Tranmitter_Reciever :     SET_BIT (UART1 -> CR1 , TE ) ;
    									    SET_BIT (UART1 -> CR1 , RE ) ;
											break ; 
		default : break ;
	}
	/* Data Width */
	switch ( Option -> DataWidth )
	{
		case DataWidth_8 : CLR_BIT ( UART1 -> CR1 , M ) ; break ;
		case DataWidth_9 : SET_BIT ( UART1 -> CR1 , M ) ; break ;
		default : /* Non Option */ break ;
	}
	/* Stop Bits */
	switch ( Option -> StopBits ) 
	{
		case StopBits_1   : UART1 -> CR2 |= ( 0 << STOP_BIT_0 ) ; break ;
		case StopBits_0_5 : UART1 -> CR2 |= ( 1 << STOP_BIT_0 ) ; break ;
		case StopBits_2   : UART1 -> CR2 |= ( 2 << STOP_BIT_0 ) ; break ;
		case StopBits_1_5 : UART1 -> CR2 |= ( 3 << STOP_BIT_0 ) ; break ;
		default : break ;
	}
    /* Enable UART */
    SET_BIT ( UART1 -> CR1 , UE ) ;
}


void UART_TransmitData( u8 A_Data )
{
    /* Chek Flag Empty */
    while ( GET_BIT (  UART1 -> SR  , TXE ) == 0 ) ;
    /* Write Data In Tranmition Buffer */
    UART1 -> DR = A_Data ;
}

void UART_Recieve (u8 * RecieveData )
{
	u32 TimeOut = 0 ;
    while ( ( GET_BIT (  UART1 -> SR  , RXNE ) == 0 ) )
    {
    	TimeOut++ ;
    	if ( TimeOut == 1000000 )
    		break;
    }
    *RecieveData = UART1->DR  ; 
}

 
void UART_TransmitString( u8 *String )
{
    while ( *String != '\0' )
    {
        UART_TransmitData ( *String ) ;
        String++ ;
    }
}

void UART_TransmitNumber ( u32 A_Number )
{
	u32 Power = 1 ;
	u32 CopyNumber = A_Number ;

	while ( CopyNumber != 0 )
	{
		CopyNumber /= 10 ;
		Power*= 10 ;
	}

	Power /= 10 ;

	while ( Power > 0 )
	{
		UART_TransmitData ( ( A_Number / Power ) + 48 ) ;
		A_Number %= Power ;
		Power /= 10 ;
	}
}

u16 UART_RecieveNumber (void)
{
	u8 Index = 0 ; 
	u8 Arr[10] = {0} ;
	u32 Power = 1 ; 
	u32 RecievedNumber = 0 ;
	while (1)
	{
		UART_Recieve ( &Arr[Index] ) ;
		if ( Arr[Index] == '\r' ) //( '\r' ) is the ( Enter ) of Putty Program 
		{
			break ;
		}
		else 
		{
			Index++ ;
		}
	}

	for ( u8 i = 0 ; i < Index ; i++ )
	{
		Power *= 10 ;
	}
	
	Power /= 10 ;
	
	for ( u8 i = 0 ; i <= Index ; i++ )
	{
		RecievedNumber += ( ( Arr[i] - 48 ) * Power ) ;
		Power /= 10 ;
	}

	return RecievedNumber ;
}



