#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "FMI_private.h"
#include "FMI_interface.h"

void FMI_Write ( u32 A_StartingAddress , u8 * Data , u8 DataLength) 
{
    /* Check there is no current operation */
    while ( GET_BIT( FMI->SR , BSY_BIT) ) ; 

    /* Unlock Control Register */
    if ( GET_BIT( FMI->CR , LOCK_BIT ) )
    {
        FMI->KEYR = KEY1 ; 
        FMI->KEYR = KEY2 ; 
    }
    /* Set Parallelism */
    FMI->CR &=  ~(PSIZE_MASK<<8) ; 
    FMI->CR |=   0<<8 ; // Program in terms of 'Byte' 
    /* SET PG bit */
    SET_BIT ( FMI->CR , PG_BIT  ) ; 

    /* Send Data */
    for (u8 i = 0 ; i < DataLength ; i++ )
    {
        *( (u8*)A_StartingAddress ) = *(Data+i) ; 
        /* Wait Operation to be done */
        while ( GET_BIT( FMI->SR , BSY_BIT) ) ;
        /* Incrementing by 1 due to size of data is Byte */
        A_StartingAddress += 1 ;
    }


    /* Clear PG bit */
    CLR_BIT ( FMI->CR , PG_BIT  ) ; 

}


void FMI_SectorErase ( u8 A_SectorNumber )
{
    /* Check there is no current operation */
    while ( GET_BIT( FMI->SR , BSY_BIT) ) ; 
    /* Unlock Control Register */
    if ( GET_BIT( FMI->CR , LOCK_BIT ) )
    {
        FMI->KEYR = KEY1 ; 
        FMI->KEYR = KEY2 ; 
    }
    /* SET SER bit */
    SET_BIT ( FMI->CR , SER_BIT  ) ; 
    /* Selsect Sector */
    FMI->CR &=  ~(SNB_MASK<<3) ; 
    FMI->CR |=   A_SectorNumber<<3 ;
    /* Start  */
    SET_BIT ( FMI->CR , STRT_BIT  ) ; 
    /* Wait Operation to be done */
    while ( GET_BIT( FMI->SR , BSY_BIT) ) ; 
    /* Clear SER bit */
    CLR_BIT ( FMI->CR , SER_BIT  ) ; 
}

// void FMI_MassErase ( void )
// {
//     /* Check there is no current operation */
//     while ( GET_BIT( FMI->SR , BSY_BIT) ) ; 

//     /* Unlock Control Register */
//         if ( GET_BIT( FMI->CR , LOCK_BIT ) )
//     {
//         FMI->KEYR = KEY1 ; 
//         FMI->KEYR = KEY2 ; 
//     }
//     /* SET MER bit */
//     SET_BIT ( FMI->CR , MER_BIT  ) ; 

//     /* Start  */
//     SET_BIT ( FMI->CR , STRT_BIT  ) ; 

//     /* Wait Operation to be done */
//     while ( GET_BIT( FMI->SR , BSY_BIT) ) ; 

//     /* Clear MER bit */
//     CLR_BIT ( FMI->CR , MER_BIT  ) ; 

// }

