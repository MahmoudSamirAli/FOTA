#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

#define NOK  0 
#define OK  1 
#define MODE_STATION   '1'
#define ESP_MODE   MODE_STATION
#define ESP_MODE_RESPONSE   6   //\r\nOK\r\n
#define ESP_WIFI_RESPONSE   35   //WIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n
#define ESP_SERVER1_RESPONSE   15   //\r\nCONNECT\r\n\r\nOK\r\n
#define ESP_SERVER2_RESPONSE   6   //\r\nOK\r\n
#define ESP_CHECK_RESPONSE  40     // RECV 40 BYTES\r\n\r\nSEND OK\r\n\r\n+IPD,1:(1)CLOSED
#define ESP_FILE_RESPONSE  100     // RECV 49 BYTES\r\n\r\nSEND OK\r\n\r\n+IPD,1425::(File Content)CLOSED
#define MODE_OK             1
#define NETWORK_OK          2
#define SERVER_IP_OK        3
#define MESSAGELENGTH_OK    4

/* Notes : 
            1- in main initialize RCC for UART & GPIO 
            2- UART BaudRate = 115200, configure oversampling and bus clock(uart bus -> apb2) to get it 115200
            3- Every Argument Must Be Passed In ASCII FORM 
            4- the return from ESP (Recieved by uart) is in ASCII : for func ESP_ReadFromServer
*/
void ESP_Init (void);
u8 ESP_SetMode (u8 Mode); //Must Be in ASCII 
u8 ESP_NetworkConnection (u8 * WIFI_Name , u8 * WIFI_Password );
u8 ESP_ServerConnection_1 (u8 * ServerIP );
u8 ESP_ServerConnection_2 (u8 * Length );
//"GET http://se7en.freevar.com/check.txt\r\n"
u8 ESP_CheckFilesExistence ( u8 * CheckCommand ); // Return Either '1' (if it's in the file) or 'L' (if there is nothing in the file)
// "GET http://se7en.freevar.com/files/FOTA_APP.hex\r\n"
void ESP_ReadFileFromServer ( u8 * ReadCommand , u8 * RecordBuffer );

#endif
