#ifndef   FMI_PRIVATE_H
#define   FMI_PRIVATE_H


typedef struct 
{
    volatile u32 ACR ; 
    volatile u32 KEYR ; 
    volatile u32 OPTKEYR ; 
    volatile u32 SR ; 
    volatile u32 CR ; 
    volatile u32 OPTCR ; 
}FMI_REG ; 

#define FMI_BASE_ADD   0x40023C00
#define FMI    (  (volatile FMI_REG *)  ( FMI_BASE_ADD ) )



#define LOCK_BIT   31 
#define BSY_BIT    16
#define STRT_BIT   16
#define MER_BIT    2
#define SER_BIT    1
#define PG_BIT     0


#define SNB_MASK   0b1111
#define PSIZE_MASK   0b11

#define KEY1	0x45670123
#define KEY2    0xCDEF89AB

#endif