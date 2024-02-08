#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SCB_interface.h"
#include "SCB_private.h"
 
/* Number of GROUPS and SUB_GROUPS are depending on each other */
void SCB_SetNumberOfGroups (u8 A_NumberOfGroups )
{ 
    switch (A_NumberOfGroups)
    {
        case G16_S0 : SCB->AIRCR = GROUPS_16_SUB_NONE ; break;
        case G8_S2  : SCB->AIRCR = GROUPS_8_SUB_2  ;    break;
        case G4_S4  : SCB->AIRCR = GROUPS_4_SUB_4 ;     break;
        case G2_S8  : SCB->AIRCR = GROUPS_2_SUB_8 ;     break;
        case G1_S16 : SCB->AIRCR = GROUPS_NONE_SUB_16 ; break;
        default: /* Wrong Input : Do Nothing */ break;
    }
}

void SCB_ResetVectorTableAddress( u32 NewAddress  )
{
//    NewAddress &= 0xFFFFFFE0 ; // Clear first 9 bits as data sheet requirments
    SCB->VTOR = NewAddress ;
}
