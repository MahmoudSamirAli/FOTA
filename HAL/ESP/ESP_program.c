#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"


#include "../../MCAL/RCC/RCC_interface.h" // for _delay_ms() ; 
#include "../../MCAL/UART/UART_interface.h"


#include "ESP_interface.h"

/* Notes : 
            1- in main initialize RCC for UART & GPIO 
            2- UART BaudRate = 115200, configure oversampling and bus clock(uart bus -> apb2) to get it 115200
            3- Every Argument Must Be Passed In ASCII FORM 
*/

u8 G_HandShake = 0 ;

void ESP_Init (void)
{
	/* 1- Init the UART : With Transmite only mode to avoid filling the Reciever Register from Echo */
	UART_Config Init = { .OverSampling = OverSampling_16 , .DataWidth = DataWidth_8 , .StopBits = 1 , .Mode = Mode_Tranmitter_Only } ;
	UART_Init( &Init ) ;
	/* 2- Send Dummy AT commands to avoid baud rate corruption */
	UART_TransmitString("AT\r\n") ;
	_delay_ms(1000);
	UART_TransmitString("AT\r\n") ;
	_delay_ms(1000);
	/* 3- Cancel Echo */
	UART_TransmitString("ATE0\r\n") ;
	/* 4- Configure the UART mode to recieve transmit to listen to the response of ESP */
	Init.Mode = Mode_Tranmitter_Reciever  ;
	UART_Init( &Init ) ;
}

u8 ESP_SetMode (u8 Mode)
{
	u8 BreakLoop = 0 ;
	u8 Recieve = 0 ; u8 Recieve_Copy = 0 ;
	u8 L_Return = NOK ; 
	for ( u8 I = 0 ; I < 3 ; I++ )
	{
		UART_TransmitString("AT+CWMODE=");
		UART_TransmitData(Mode);
		UART_TransmitString("\r\n") ;
		for ( u8 i = 0 ; i < ESP_MODE_RESPONSE ; i++ )
		{
			UART_Recieve( &Recieve ) ;
			if ( Recieve_Copy == 'O' && Recieve == 'K' )
			{
				G_HandShake = MODE_OK ;
				BreakLoop = 1 ;
				L_Return = OK ;
				break ;
			}
			else
			{
				Recieve_Copy = Recieve ;
			}
		}
		if ( BreakLoop == 1 )
		{
			break ; 
		}
		_delay_ms(1000);
	}
	return L_Return ;
}


u8 ESP_NetworkConnection (u8 * WIFI_Name , u8 * WIFI_Password )
{
	u8 BreakLoop = 0 ;
	u8 Recieve = 0 ; u8 Recieve_Copy = 0 ;
	u8 L_Return = NOK ; 

	/* Clearing The Receiver Buffer From Last Command */
	/*************************/
	UART_Recieve( &Recieve ) ;
	/*************************/
	if ( G_HandShake == MODE_OK )
	{
		for ( u8 I = 0 ; I < 3 ; I++ )
		{
			UART_TransmitString("AT+CWJAP_CUR=\"");
			UART_TransmitString(WIFI_Name);
			UART_TransmitString("\",\"");
			UART_TransmitString(WIFI_Password);
			UART_TransmitString("\"\r\n") ;
			for ( u8 i = 0 ; i < ESP_WIFI_RESPONSE ; i++ )
			{
				UART_Recieve( &Recieve ) ;
				if ( Recieve_Copy == 'I' && Recieve == 'P' ) // WIFI GOt IP
				{
					G_HandShake = NETWORK_OK ;
					BreakLoop = 1 ;
					L_Return = OK ; 
					break ;
				}
				else
				{
					Recieve_Copy = Recieve ;
				}
			}
			if ( BreakLoop == 1 )
			{
				break ; 
			}
			_delay_ms(1000);
		}	
	}
	return L_Return ; 
}

u8 ESP_ServerConnection_1 (u8 * ServerIP )
{
	u8 BreakLoop = 0 ;
	u8 Recieve = 0 ; u8 Recieve_Copy = 0 ;
	u8 L_Return = NOK ;
	/* Clearing The Receiver Buffer From Last Command */
	/*************************/
	UART_Recieve( &Recieve ) ;
	/*************************/
	if ( G_HandShake == NETWORK_OK || G_HandShake == MESSAGELENGTH_OK ) // MESSAGELENGTH_OK => Due To Read File , we won't reconnect to the network we reconnect only the server
	{
		for ( u8 I = 0 ; I < 3 ; I++ )
		{
			UART_TransmitString("AT+CIPSTART=\"TCP\",\"");
			UART_TransmitString(ServerIP);
			UART_TransmitString("\",80\r\n");
			for ( u8 i = 0 ; i < ESP_SERVER1_RESPONSE ; i++ )
			{
				UART_Recieve( &Recieve ) ;
				if ( Recieve_Copy == 'O' && Recieve == 'K' )
				{
					G_HandShake = SERVER_IP_OK ;
					BreakLoop = 1 ;
					L_Return = OK ;
					break ;
				}
				else
				{
					Recieve_Copy = Recieve ;
				}
			}
			if ( BreakLoop == 1 )
			{
				break ; 
			}
			_delay_ms(1000);
		}
	}
	return L_Return ;
}

u8 ESP_ServerConnection_2 (u8 * Length )
{
	u8 BreakLoop = 0 ;
	u8 Recieve = 0 ; u8 Recieve_Copy = 0 ;
	u8 L_Return = NOK ; 
	/* Clearing The Receiver Buffer From Last Command */
	/*************************/
	UART_Recieve( &Recieve ) ;
	/*************************/
	if ( G_HandShake == SERVER_IP_OK )
	{
		for ( u8 I = 0 ; I < 3 ; I++ )
		{
			UART_TransmitString("AT+CIPSEND=");
			UART_TransmitString(Length);
			UART_TransmitString("\r\n") ;
			for ( u8 i = 0 ; i < ESP_SERVER2_RESPONSE ; i++ )
			{
				UART_Recieve( &Recieve ) ;
				if ( Recieve_Copy == 'O' && Recieve == 'K' )
				{
					G_HandShake = MESSAGELENGTH_OK ;
					BreakLoop = 1 ;
					L_Return = OK ;
					break ;
				}
				else
				{
					Recieve_Copy = Recieve ;
				}
			}
			if ( BreakLoop == 1 )
			{
				break ; 
			}
			_delay_ms(1000);
		}
	}
	return L_Return ;
}
//"GET http://se7en.freevar.com/check.txt\r\n"
u8 ESP_CheckFilesExistence ( u8 * CheckCommand )
{
	u8 BreakLoop = 0 ; 
	u8 Recieve = 0 ; 
	
	/* Clearing The Receiver Buffer From Last Command */
	/*************************/
	UART_Recieve( &Recieve ) ;
	/*************************/
	if ( G_HandShake == MESSAGELENGTH_OK )
	{
		for ( u8 I = 0 ; I < 3 ; I++ )
		{
			UART_TransmitString(CheckCommand) ;
			for ( u8 i = 0 ; i < ESP_CHECK_RESPONSE ; i++ )
			{
				UART_Recieve( &Recieve ) ;
				if ( Recieve == '1' || Recieve == 'L' )
				{
					BreakLoop = 1 ;
					break ;
				}
			}
			if ( BreakLoop == 1 )
			{
				break ; 
			}
			else 
			{
				_delay_ms(1000) ;
				ESP_ServerConnection_1("69.197.143.14") ; 
				ESP_ServerConnection_2("40") ; 
			}
		}
	} 

	return Recieve ; 
}

// "GET http://se7en.freevar.com/files/FOTA_APP.hex\r\n"
void ESP_ReadFileFromServer ( u8 * ReadCommand , u8 * RecordBuffer )
{

	u8 Recieve = 0 ; u8 Recieve_Copy = 0 ;
	u8 * RecordBufferBaseAdd = RecordBuffer ; 
	u8 BreakLoop = 0 ;
	/* Clearing The Receiver Buffer From Last Command */
	/*************************/
	UART_Recieve( &Recieve ) ;
	/*************************/
	if ( G_HandShake == MESSAGELENGTH_OK )
	{
		for ( u8 I = 0 ; I < 3 ; I++ )
		{
			UART_TransmitString(ReadCommand) ;
			for ( u8 i = 0 ; i < ESP_FILE_RESPONSE ; i++ )
			{
				UART_Recieve( &Recieve ) ;
				if ( Recieve_Copy == ':' && Recieve == ':' )
				{
					do
					{
						RecordBuffer++ ;
						UART_Recieve(RecordBuffer) ;
					}while ( *(RecordBuffer) != 'L' ) ; // C -> CLOSED (ESP)
					*RecordBufferBaseAdd = Recieve ;
					BreakLoop = 1 ;
					break ;
				}
				else
				{
					Recieve_Copy = Recieve ;
				}
			}
			if ( BreakLoop == 1 )
			{
				break ; 
			}
			else 
			{
				_delay_ms(1000) ;
				ESP_ServerConnection_1("69.197.143.14") ; 
				ESP_ServerConnection_2("49") ; 
			}
		}
	}

}
