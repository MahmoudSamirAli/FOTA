#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "MCAL/FMI/FMI_interface.h"

#include "HAL/ESP/ESP_interface.h"

#include "APP/BootLoader/BootLoader_interface.h"

#define CheckTillFilesExistence 4
#define CheckTillReadFile       6

void FOTA_Init (void)
{
	//SYS_CLOCK => 16 MHZ - UART Clock = 8 MHZ
	RCC_InitSysClk(HSI_CLK) ;
	RCC_BusPrescaler(AHB_BUS , SYS_CLK_DIVIDED_BY_2  ) ;
	RCC_BusPrescaler( APB2_BUS , AHB_DIVIDED_BY_1 ) ;
	//GPIO_RCC
	RCC_EnablePeripheralClock(AHB_BUS , RCC_GPIOA ) ;
	RCC_EnablePeripheralClock(AHB_BUS , RCC_GPIOB ) ;
	//FMI_RCC
	RCC_EnablePeripheralClock(AHB_BUS_LP , RCC_FMI ) ;
	// UART__RCC_GPIO
	RCC_EnablePeripheralClock( APB2_BUS , RCC_USART1  ) ;
	GPIO_SetPinMode(GPIO_PORTB , PIN6 , MODE_AF ) ;
	GPIO_SetPinAlternativeFunction(GPIO_PORTB , PIN6 , 7 ) ;
	GPIO_SetPinOConfig(GPIO_PORTB , PIN6 , OTYPE_PP , OSPEED_LOW ) ;
	GPIO_SetPinMode(GPIO_PORTB , PIN7 , MODE_AF ) ;
	GPIO_SetPinAlternativeFunction(GPIO_PORTB , PIN7 , 7 ) ;
	GPIO_SetPinState(GPIO_PORTB , PIN7 , STATE_NO_PULL ) ;
    /*  Erase Before Flashing : the sector that will be filled with the incoming app */
	FMI_SectorErase(1) ;
}

int main (void)
{
	/*
	 * @Reset check the server :
	 * 1- if there is a file uploaded to the server -> download,flash then start execute it.
	 * 2- if there is no files ,Jump to the default app.
	 */
	u8 L_CheckFilesExistence = 0 ;
	u8 RecordBuffer[5000] = {0} ; //Specific for my app.hex
	u8 L_Detector = 0 ;
	/* System Initialization */
	FOTA_Init() ;

	ESP_Init() ;
	L_Detector += ESP_SetMode(ESP_MODE) ; // Saturation Mode.
	L_Detector += ESP_NetworkConnection("Mahmoud Samir","MS_1234##") ; // Wifi Name and Password.
	L_Detector += ESP_ServerConnection_1("69.197.143.14") ; // Sever IP.
	L_Detector += ESP_ServerConnection_2("40") ;  // Message Length.
	if ( L_Detector == CheckTillFilesExistence )
	L_CheckFilesExistence = ESP_CheckFilesExistence("GET http://se7en.freevar.com/check.txt\r\n"); // Checking if a file is uploaded.
	if ( L_CheckFilesExistence == '1' ) // if CheckFilesExistence == 1 that means there is a file uploaded into the server
	{
		_delay_ms(500) ; // Just a breathtaking
		L_Detector += ESP_ServerConnection_1("69.197.143.14") ; // Reconnect to the server (this step is must,because the ESP Disconnect the server after every communication)
		L_Detector += ESP_ServerConnection_2("49") ;  // Message Length.
		if ( L_Detector == CheckTillReadFile )
		ESP_ReadFileFromServer("GET http://se7en.freevar.com/files/FOTA_APP.hex\r\n" , RecordBuffer) ;
		BL_AsciiToHex(RecordBuffer) ;
		BL_RecordParsingAndFlashing(0x8004000 , RecordBuffer ) ;
		BL_JumpToAnApp(0x8004000) ;
	}


	/**********************************************************************/
	/* You can add some code here to print the value of L_Detector        */
	/* to know if there is a problem with ESP where it is specifically    */
	/**********************************************************************/
	/* if there is a problem with the WIFI turn a led to notify the user */
	if (  L_Detector < CheckTillFilesExistence  )
	{
		GPIO_SetPinMode(GPIO_PORTA , PIN7 , MODE_OUTPUT  ) ;
		GPIO_SetPinOConfig( GPIO_PORTA , PIN7 , OTYPE_PP , OSPEED_LOW ) ;
		GPIO_SetPinState(GPIO_PORTA , PIN7 , STATE_HIGH ) ;
	}

	/* Default APP : Toggling Led (It might be any app) */
	GPIO_SetPinMode(GPIO_PORTA , PIN0 , MODE_OUTPUT  ) ;
	GPIO_SetPinOConfig( GPIO_PORTA , PIN0 , OTYPE_PP , OSPEED_LOW ) ;
	GPIO_SetPinState(GPIO_PORTA , PIN0 , STATE_HIGH ) ;
	while (1)
	{
		GPIO_TogglePinOutputState(GPIO_PORTA , PIN0) ;
		_delay_ms(1000) ;
	}
}
