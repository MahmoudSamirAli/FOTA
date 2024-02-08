#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

typedef struct 
{
    u32 SR ;
    u32 DR ;
    u32 BRR ;
    u32 CR1 ;
    u32 CR2 ;
    u32 CR3 ;
    u32 GTPR ;
}UART_R ;

#define UART_1_BASE_ADDRESS   0x40011000
#define UART_2_BASE_ADDRESS   0x40014400
#define UART_6_BASE_ADDRESS   0x40011400

#define UART1  ( (volatile UART_R * ) (UART_1_BASE_ADDRESS) )
#define UART2  ( (volatile UART_R * ) (UART_2_BASE_ADDRESS) )
#define UART6  ( (volatile UART_R * ) (UART_6_BASE_ADDRESS) )


/* Two Different Design Methods */
/********************************
1 - Using #defines ====> Consume No Memory
// STATUS REGISTER
#define TXE   7
#define TC   6
#define RXNE   5 
*********************************/
/* 2 - Using enum ====> Consume Memory = sizeof(enum) Mostly == 4 Bytes */
typedef enum 
{
    RXNE = 5 ,
    TXE  = 7  
}SR_Bits ;

/*
// CR 1 
#define UE       13
#define WORD_LENGTH   12
#define TXEIE   7
#define TCIE   6
#define RXNEIE   5
#define TE   3
#define RE   2
*/
typedef enum 
{
    RE = 2 ,
    TE , 
    M  = 12 ,
    UE , // : USART enable
    OVER8 = 15 
}CR1_Bits ;
/*
//CR2
#define STOP_BIT_0  12
#define STOP_BIT_1  13
*/
typedef enum 
{
    STOP_BIT_0 = 12 , 
    STOP_BIT_1
}CR2_Bits ;
#endif