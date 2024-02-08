#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GPIO_private.h"
#include "GPIO_interface.h"



void GPIO_SetPinMode ( u8 A_Port , u8 A_Pin , u8 A_Mode )
{
    switch ( A_Port )
    {
        case GPIO_PORTA : 
        if ( A_Pin != PIN13 && A_Pin != PIN14 && A_Pin != PIN15 ) // J_Tag PINS
        {
            GPIOA->MODER &= ~( MODE_MASK << ( A_Pin*2 ) )  ;
            GPIOA->MODER |= ( A_Mode << ( A_Pin*2 ) )  ;
        }
        break;
        case GPIO_PORTB : 
        if ( A_Pin != PIN2 && A_Pin != PIN4 && A_Pin != PIN3 ) // J_Tag PINS
        {
            GPIOB->MODER &= ~( MODE_MASK << ( A_Pin*2 ) )  ;
            GPIOB->MODER |= ( A_Mode << ( A_Pin*2 ) )  ;
        }
        break;
    }        
}

void GPIO_SetPinOConfig ( u8 A_Port , u8 A_Pin , u8 A_OType , u8 A_OSpeed)
{
    switch ( A_Port )
    {
        case GPIO_PORTA : 
        if ( A_Pin != PIN13 && A_Pin != PIN14 && A_Pin != PIN15 ) // J_Tag PINS
        {
            GPIOA->OTYPER &= ~(OTYPE_MASK<<A_Pin) ;
            GPIOA->OTYPER |= ( A_OType<<A_Pin)  ;
            GPIOA->OSPEEDR &= ~( SPEED_MASK  << ( A_Pin*2 ) );
            GPIOA->OSPEEDR |= ( A_OSpeed << ( A_Pin*2 ) );
        }
        break;
        case GPIO_PORTB : 
        if ( A_Pin != PIN2 && A_Pin != PIN4 && A_Pin != PIN3 ) // J_Tag PINS
        {
            GPIOB->OTYPER &= ~(OTYPE_MASK<<A_Pin) ;
            GPIOB->OTYPER |= ( A_OType<<A_Pin)  ;
            GPIOB->OSPEEDR &= ~( SPEED_MASK  << ( A_Pin*2 ) );
            GPIOB->OSPEEDR |= ( A_OSpeed << ( A_Pin*2 ) );
        }
        break;
    }        
}

void GPIO_SetPinState ( u8 A_Port , u8 A_Pin , u8 A_State )
{
    switch ( A_Port )
    {
        case GPIO_PORTA : 
        if ( A_Pin != PIN13 && A_Pin != PIN14 && A_Pin != PIN15 ) // J_Tag PINS
        {
            switch ( A_State )
            {
                case STATE_HIGH  : 
                case STATE_FLOAT : 
                    GPIOA->BSRR |= ( 1 << A_Pin ) ; break ; 
                case STATE_LOW : 
                    GPIOA->BSRR |= ( 1 << (A_Pin+16) ) ; break ;
                case STATE_NO_PULL : 
                    GPIOA->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ; break ;
                case STATE_PULL_UP : 
                    GPIOA->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ;
                    GPIOA->PUPDR |=  ( 1 << (A_Pin * 2) ) ; break ;
                case STATE_PULL_DOWN : 
                    GPIOA->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ;
                    GPIOA->PUPDR |=  ( 2 << (A_Pin * 2) ) ; break ;
            }
        }
        break;
        case GPIO_PORTB : 
        if ( A_Pin != PIN2 && A_Pin != PIN4 && A_Pin != PIN3 ) // J_Tag PINS
        {
            switch ( A_State )
            {
                case STATE_HIGH  : 
                case STATE_FLOAT : 
                    GPIOB->BSRR |= ( 1 << A_Pin ) ; break ; 
                case STATE_LOW : 
                    GPIOB->BSRR |= ( 1 << (A_Pin+16) ) ; break ;
                case STATE_NO_PULL : 
                    GPIOB->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ; break ;
                case STATE_PULL_UP : 
                    GPIOB->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ;
                    GPIOB->PUPDR |=  ( 1 << (A_Pin * 2) ) ; break ;
                case STATE_PULL_DOWN : 
                    GPIOB->PUPDR &= ~( PUPD_MASK << (A_Pin * 2) ) ;
                    GPIOB->PUPDR |=  ( 2 << (A_Pin * 2) ) ; break ;
            }
        }
        break;
    }        
}

void GPIO_TogglePinOutputState (u8 A_Port , u8 A_Pin )
{
    u8 L_Check ;
    switch (A_Port)
    {
        case GPIO_PORTA :
        L_Check = GET_BIT( GPIOA->ODR , A_Pin ) ;
        if      (L_Check == 1 ) { SET_BIT ( GPIOA->BSRR , (A_Pin + RESET_SHIFT ) ); } 
        else if (L_Check == 0 ) { SET_BIT ( GPIOA->BSRR , A_Pin ) ;    }
        else {} 
        break; 
        case GPIO_PORTB :
        L_Check = GET_BIT( GPIOB->ODR , A_Pin ) ;
        if      (L_Check == 1 ) { SET_BIT ( GPIOB->BSRR , (A_Pin + RESET_SHIFT ) ); } 
        else if (L_Check == 0 ) { SET_BIT ( GPIOB->BSRR , A_Pin ) ;    }
        else {} 
        break;                      
        default : /* */ break ;
    }
}

u8 GPIO_GetPinInputValue ( u8 A_Port , u8 A_PinNumber )
{
	u8 L_PinValue = 30 ; // random value 
    switch ( A_Port )
    {
        case GPIO_PORTA : L_PinValue = GET_BIT( GPIOA->IDR , A_PinNumber )  ; break ;
        case GPIO_PORTB : L_PinValue = GET_BIT( GPIOB->IDR , A_PinNumber )  ; break ;
        default : break ; 
    }
    return L_PinValue ;
}

void GPIO_SetPinAlternativeFunction ( u8 A_Port , u8 A_Pin , u8 A_AF )
{
    switch ( A_Port )
    {
        case GPIO_PORTA : 
        if ( A_Pin != PIN13 && A_Pin != PIN14 && A_Pin != PIN15 ) // J_Tag PINS
        {
            if ( A_Pin < 8 )
            {
                GPIOA->AFRL &= ~(AF_Mask << A_Pin*4 )   ;
                GPIOA->AFRL |= (A_AF << A_Pin*4 )      ;
            }
            else if ( A_Pin >= 8 )
            {
                GPIOA->AFRH &= ~(AF_Mask << (A_Pin-8)*4 )   ;
                GPIOA->AFRH |= (A_AF << (A_Pin-AF_8)*4 )      ;
            }
            else { }
        }
        break;
        case GPIO_PORTB : 
        if ( A_Pin != PIN2 && A_Pin != PIN4 && A_Pin != PIN3 ) // J_Tag PINS
        {
            if ( A_Pin < 8 )
            {
                GPIOB->AFRL &= ~(AF_Mask << A_Pin*4 )   ;
                GPIOB->AFRL |= (A_AF << A_Pin*4 )      ;
            }
            else if ( A_Pin >= 8 )
            {
                GPIOB->AFRH &= ~(AF_Mask <<(A_Pin-8)*4 )   ;
                GPIOB->AFRH |= (A_AF << (A_Pin-8)*4 )      ;
            }
            else { }
        }
        break;
    }           
}

void GPIO_OutValOnPortALowNipple ( u8 A_Value )
{
    GPIOA->MODER &= 0xFFFF0000 ; // Clear Mode of First 8 Pins
    GPIOA->MODER |= 0x5555 ; // Set Low Nipple Output
    GPIOA->OTYPER = 0 ; // Output PP
    GPIOA->ODR = A_Value ; 
}
