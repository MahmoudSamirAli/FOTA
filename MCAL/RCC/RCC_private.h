#ifndef     RCC_PRIVATE_H
#define     RCC_PRIVATE_H
 
#define     RCC_BASE_ADD    0x40023800 
typedef struct 
{
    u32 CR ;
    u32 PLLCFGR ;
    u32 CFGR ;
    u32 CIR ;
    u32 AHB1RSTR ;
    u32 AHB2RSTR ;
    u32 RESERVED1 ;
    u32 RESERVED2 ;
    u32 APB1RSTR ;
    u32 APB2RSTR ;
    u32 RESERVED3 ;
    u32 RESERVED4 ;
    u32 AHB1ENR ;
    u32 AHB2ENR ;
    u32 RESERVED5 ;
    u32 RESERVED6 ;
    u32 APB1ENR ;
    u32 APB2ENR ;
    u32 RESERVED7 ;
    u32 RESERVED8 ;
    u32 AHB1LPENR ;
    u32 AHB2LPENR ;
    u32 RESERVED9 ;
    u32 RESERVED10 ;
    u32 APB1LPENR ;
    u32 APB2LPENR ;
    u32 RESERVED11 ;
    u32 RESERVED12 ;
    u32 BDCR ;
    u32 CSR ; 
    u32 RESERVED13 ;
    u32 RESERVED14 ;
    u32 SSCGR ;
    u32 PLLI2SCFGR ;
    u32 RESERVED15 ;
}RCC_REG;
#define RCC     ( ( volatile RCC_REG * ) (RCC_BASE_ADD) )

 
/* Sys Clk MASK */
#define     SYS_CLK_MASK        0xFFFFFFF0
#define     SWS_START_BIT       2
#define     SWS_CHECK           3
/* For Bus Prescaler */
#define HPRE_START_BIT     4
#define PPRE1_START_BIT    10
#define PPRE2_START_BIT    13
#define     HPRE_MASK   0xFFFFFF0F
#define     PPRE1_MASK  0xFFFFE3FF
#define     PPRE2_MASK  0xFFFF1FFF
/* CR MACROS */
#define HSION   0
#define HSIRDY  1
#define HSEON   16
#define HSERDY  17
#define HSEPY   18
#define CSSON   19
#define PLLON   24
#define PLLRDY  25


#endif