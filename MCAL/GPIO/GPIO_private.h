#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


typedef struct 
{
    u32  MODER ;
    u32  OTYPER ;
    u32  OSPEEDR ;
    u32  PUPDR ;
    u32  IDR ;
    u32  ODR ;
    u32  BSRR ;
    u32  LCKR ;
    u32  AFRL ;
    u32  AFRH ;
}GPIO_t;

 
// #define GPIO_REGS   10
// #define MODER    0
// #define OTYPER   1
// #define OSPEEDR  2
// #define PUPDR    3
// #define IDR      4
// #define ODR      5
// #define BSRR     6
// #define LCKR     7
// #define AFRL     8
// #define AFRH     9

// typedef struct
// {
//     u32 GPIO[GPIO_REGS] ;
// }GPIO_t;
// Accessing : 
//              GPIOA -> GPIO[MODER] = Value ; ....

#define GPIOA_BASE_ADD   0x40020000
#define GPIOA   ( (volatile GPIO_t * ) (GPIOA_BASE_ADD) )


#define GPIOB_BASE_ADD   0x40020400
#define GPIOB   ( (volatile GPIO_t * ) (GPIOB_BASE_ADD) )


#define GPIOC_BASE_ADD   0x40020800
#define GPIOC   ( (volatile GPIO_t * ) (GPIOB_BASE_ADD) )

#define OTYPE_MASK   0b1 
#define ODR_MASK   0b1 
#define SPEED_MASK   0b11
#define MODE_MASK    0b11
#define PUPD_MASK    0b11
#define AF_Mask      0b1111
#define NIPPLE_MASK 0xFFFF
#define RESET_SHIFT  16

/* MODE OPTIONS */
#define INPUT_MODE   0
#define OUTPUT_MODE  1
#define AF_MODE      2
#define ANALOG_MODE  3

#endif