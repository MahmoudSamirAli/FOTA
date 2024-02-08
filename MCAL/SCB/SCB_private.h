#ifndef SCB_PRIVATE_H
#define SCB_PRIVATE_H


typedef struct
{
    u32 CPUID;
    u32 ICSR;
    u32 VTOR;
    u32 AIRCR;
    u32 SCR;
    u32 CCR;
    u32 SHPR1;
    u32 SHPR2;
    u32 SHPR3;
    u32 SHCSR;
    u32 CFSR;
    u32 HFSR;
    u32 RESERVED;
    u32 MMFAR;
    u32 BFAR;
} SCB_t;

#define SCB_BASE_ADD   0xE000ED00
#define SCB     ( ( volatile SCB_t * ) (SCB_BASE_ADD) )


/* GROUPS AND SUB GROUPS NUMBERS */
#define GROUPS_16_SUB_NONE  0x05FA0300     
#define GROUPS_8_SUB_2      0x05FA0400     
#define GROUPS_4_SUB_4      0x05FA0500     
#define GROUPS_2_SUB_8      0x05FA0600     
#define GROUPS_NONE_SUB_16  0x05FA0700     


#endif