#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "RCC_interface.h"
#include "RCC_private.h"
 

void RCC_InitSysClk ( u8 SYS_CLK )
{
	switch (SYS_CLK )
	{
		case HSE_CLK :
			/* enable hse */
			SET_BIT ( RCC->CR , HSEON ) ;
			/* wait until the HSE br ready */
			while ( ! GET_BIT( RCC->CR , HSERDY ) ) ;
			/* select HSE as sys clk */
			RCC->CFGR &= SYS_CLK_MASK ;
			RCC->CFGR |= HSE_CLK ;
			/* Enable Clock security system */
			SET_BIT( RCC->CR , CSSON ) ;
			break ;
		case HSI_CLK :
			/* enable HSI */
			SET_BIT ( RCC->CR , HSION ) ;
			/* wait until the HSE br ready */
			while ( ! GET_BIT( RCC->CR , HSIRDY ) ) ;
			/* select HSI as sys clk */
			RCC->CFGR &= SYS_CLK_MASK ;
			RCC->CFGR |= HSI_CLK ;
			break ;
		default :
			break ;
}

}

u8 RCC_CheckSysClk ( void )
{
	return ( ( RCC->CFGR >> SWS_START_BIT ) & SWS_CHECK ) ;
}

void RCC_BusPrescaler (u8 A_Bus , u8 A_DivisionFactor )
{
	switch ( A_Bus )
	{
		case AHB_BUS :
			RCC->CFGR &= HPRE_MASK ;
			RCC->CFGR |= ( A_DivisionFactor << HPRE_START_BIT )  ; break ;
		case APB1_BUS : 			
			RCC->CFGR &= PPRE1_MASK ;
			RCC->CFGR |= ( A_DivisionFactor << PPRE1_START_BIT )  ; break ;
		case APB2_BUS : 
			RCC->CFGR &= PPRE2_MASK ;
			RCC->CFGR |= ( A_DivisionFactor << PPRE2_START_BIT )  ; break ;
		default   : /* WRONG BUS : DO NOTHING */			  break ; 
	}

}

void RCC_EnablePeripheralClock ( u8 A_Bus , u8 A_Preipheral )
{
	switch(A_Bus) 
	{
		case AHB_BUS : SET_BIT(RCC->AHB1ENR,A_Preipheral ) ; break;
		case APB1_BUS : SET_BIT(RCC->APB1ENR,A_Preipheral ) ; break;
		case APB2_BUS : SET_BIT(RCC->APB2ENR,A_Preipheral ) ; break;
		case AHB_BUS_LP : SET_BIT(RCC->AHB1LPENR,A_Preipheral ) ; break;
		default:    /* WRONG BUS : DO NOTHING */          break;
	}
}

void RCC_DisablePeripheralClock ( u8 A_Bus , u8 A_Preipheral )
{
	switch(A_Bus) 
	{
		case AHB_BUS  : CLR_BIT(RCC->AHB1ENR,A_Preipheral ) ; break;
		case APB1_BUS : CLR_BIT(RCC->APB1ENR,A_Preipheral ) ; break;
		case APB2_BUS : CLR_BIT(RCC->APB2ENR,A_Preipheral ) ; break;
		default:    /* WRONG BUS : DO NOTHING */          break;
	}
}


u8 _delay_ms ( u32 A_MilliSecond )
{
	A_MilliSecond *= 2000 ;
	while (A_MilliSecond)
	{
		asm("NOP") ;
		A_MilliSecond-- ;
	}
	return 1 ;
}
