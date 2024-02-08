#ifndef   FMI_INTERFACE_H
#define   FMI_INTERFACE_H


#define PSIZE_BYTE   0
#define PSIZE_HWORD   1
#define PSIZE_WORD   2
#define PSIZE_DWORD   3

void FMI_MassErase ( void ) ; 
void FMI_SectorErase ( u8 A_SectorNumber ) ; 
void FMI_Write ( u32 A_StartingAddress , u8 * Data , u8 DataLength)  ;




#endif
