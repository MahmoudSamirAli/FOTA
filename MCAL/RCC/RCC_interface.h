#ifndef     RCC_INTERFACE_H
#define     RCC_INTERFACE_H
 
/************* RCC PERIPHERAL CLOCK CONTROL ************/
// AHB1
typedef enum 
{
    RCC_GPIOA ,
    RCC_GPIOB ,
    RCC_DMA1 = 21 ,
    RCC_DMA2 
}AHB_Peripherals;
// AHB1 LOW POWER
typedef enum 
{
    RCC_FMI = 15 ,
}AHB_LP_Peripherals;
//APB1
typedef enum 
{
    RCC_TIM2 ,
    RCC_TIM3 ,
    RCC_TIM4 ,
    RCC_TIM5 ,
    RCC_WWDG = 11 ,
    RCC_SPI2 = 14 ,
    RCC_SPI3 ,
    RCC_USART2 = 17 ,
    RCC_I2C1 = 21 ,
    RCC_I2C2 ,
    RCC_I2C3 
}APB1_Peripherals;
//APB2
typedef enum 
{
    RCC_TIM1 , 
    RCC_USART1 = 4 , 
    RCC_USART6 , 
    RCC_ADC1 = 8 ,
    RCC_SDIO = 11 ,
    RCC_SPI1 ,
    RCC_SPI4 ,
    RCC_SYSCF ,     // EXTI
    RCC_TIM9 = 16 , 
    RCC_TIM10 ,
    RCC_TIM11
}APB2_Peripherals ;
/**********  PRESCALER  ***********/
// CONFIGURE AHB CLOCK VALUE
typedef enum 
{
    SYS_CLK_DIVIDED_BY_1 = 7 , 
    SYS_CLK_DIVIDED_BY_2 ,
    SYS_CLK_DIVIDED_BY_4 , 
    SYS_CLK_DIVIDED_BY_8 , 
    SYS_CLK_DIVIDED_BY_16 ,
    SYS_CLK_DIVIDED_BY_64 ,
    SYS_CLK_DIVIDED_BY_128 ,
    SYS_CLK_DIVIDED_BY_256 ,
    SYS_CLK_DIVIDED_BY_512
}AHB_PRESCALER_OPTIONS ;
// CONFIGURE APB1,2 CLOCK VALUES
typedef enum 
{
    AHB_DIVIDED_BY_1 = 3 ,
    AHB_DIVIDED_BY_2 ,
    AHB_DIVIDED_BY_4 ,
    AHB_DIVIDED_BY_8 ,
    AHB_DIVIDED_BY_16
}APBx_PRESCALER_OPTIONS ;
/********** BUSES ***********/
typedef enum  
{
    AHB_BUS ,
    APB1_BUS ,
    APB2_BUS ,
    AHB_BUS_LP
}BUSES ;
/********** SYSTEM CLOCK OPTIONS ********/
typedef enum 
{
    HSI_CLK , 
    HSE_CLK , 
    PLL_CLK  
}SYS_CLOCK ;

/********* FUNCTIONS *******/
void RCC_InitSysClk ( u8 SYS_CLK );
void RCC_BusPrescaler (u8 A_Bus , u8 A_DivisionFactor );
void RCC_EnablePeripheralClock ( u8 A_Bus , u8 A_Preipheral );
void RCC_DisablePeripheralClock ( u8 A_Bus , u8 A_Preipheral );
u8 _delay_ms ( u32 A_MilliSecond );




#endif
