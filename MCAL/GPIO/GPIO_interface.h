#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
/* PORTS OPTIONS */
/**
#define PORTA   0
#define PORTB   1*/
 
typedef enum 
{
    GPIO_PORTA ,
    GPIO_PORTB
}A_PORT ;
/* MODES */
#define MODE_INPUT      0
#define MODE_OUTPUT     1
#define MODE_AF         2
#define MODE_ANALOG     3
/* OUTPUT CONFIGRATIONS */
/* OUTPUT TYPES */
#define OTYPE_PP 0
#define OTYPE_OD 1
/*SPEED POTIONS*/
#define OSPEED_LOW           0  // 8 MHZ
#define OSPEED_MEDIUM        1  // 50 MHZ
#define OSPEED_HIGH          2  // 80 MHZ
#define OSPEED_VERY_HIGH     3  // 150 MHZ
/* PIN STATE */
#define STATE_HIGH        0
#define STATE_FLOAT       1
#define STATE_LOW         2
#define STATE_NO_PULL     3
#define STATE_PULL_UP     4
#define STATE_PULL_DOWN   5
/* PINS OPTIONS */
#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7 
#define PIN8  8
#define PIN9  9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
/* AF Options */
#define AF_0  0 // MCO_1 -  JTMS_ SWDIO -  JTCK_ SWCLK - JTDI - JTDO- SWO -JTDO- SWO
#define AF_1  1
#define AF_2  2
#define AF_3  3
#define AF_4  4
#define AF_5  5
#define AF_6  6
#define AF_7  7 
#define AF_8  8
#define AF_9  9
#define AF_10 10
#define AF_11 11
#define AF_12 12
#define AF_13 13
#define AF_14 14
#define AF_15 15



/* Modes : INPUT - OUTPUT - AF - ANALOG */
void GPIO_SetPinMode ( u8 A_Port , u8 A_Pin , u8 A_Mode ) ;
/* OCNFIG : A_OType  : OTYPE_PP - OTYPE_OD 
            A_OSpeed : LOW_SPEED - MEDIUM_SPEED - HIGH_SPEED - VERY_HIGH_SPEED */
void GPIO_SetPinOConfig ( u8 A_Port , u8 A_Pin , u8 A_OType , u8 A_OSpeed) ;
/* STATES : AS OUTPUT => HIGH - FLOAT - LOW -  
          : AS INPUT => NO_PULL - PULL_UP - PULL_DOWN  */
void GPIO_SetPinState ( u8 A_Port , u8 A_Pin , u8 A_State ) ;

void GPIO_TogglePinOutputState (u8 A_Port , u8 A_Pin );

u8 GPIO_GetPinInputValue ( u8 A_Port , u8 A_PinNumber ) ;
/* A_AF : AF_x  x = 0:15 */
void GPIO_SetPinAlternativeFunction ( u8 A_Port , u8 A_Pin , u8 A_AF );
/* THE LOW NIPPLE SET AS OUTPUT INSIDE THIS FUNC */
void GPIO_OutValOnPortALowNipple ( u8 A_Value );



#endif
