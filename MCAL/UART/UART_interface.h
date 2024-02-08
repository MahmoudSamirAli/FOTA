#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/* Options Tow Differnt Methods *
1 - 
// #define OverSampling_16   0
// #define OverSampling_8    1
// #define DataWidth_8       0
// #define DataWidth_16       1
*/
/* 2 - */
typedef enum 
{
    OverSampling_16 ,
    OverSampling_8 ,
    DataWidth_8 ,
    DataWidth_9 ,
    StopBits_0_5 ,
    StopBits_1 ,
    StopBits_1_5 ,
    StopBits_2 ,
    Mode_Tranmitter_Only ,
    Mode_Reciever_Only ,
    Mode_Tranmitter_Reciever 
}UART_Config_Options ;


/* Struct used inside main function to configure the used UART */
typedef struct 
{
    u8 OverSampling ; // OPTIONS : 16 - 8 

    u8 DataWidth ;   // OPTIONS : 8 - 9 bits

    u8 StopBits  ;  // OPTIONS : 0.5 - 1 - 1.5 - 2  Stop bits

    u8 Mode ;       // OPTIONS : Tranmitter_Only - Reciever_Only - Mode_Tranmitter_Reciever

    u32 BaudRate ;   // OPTIONS : Mostly 9600 

}UART_Config ;



void UART_Init ( UART_Config * Option ) ;
void UART_TransmitData( u8 A_Data ) ;
void UART_Recieve (u8 * RecieveData ) ;
void UART_TransmitString( u8 *String ) ;



#endif