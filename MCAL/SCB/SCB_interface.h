#ifndef SCB_INTERFACE_H
#define SCB_INTERFACE_H


/* NUMBER OF GROUPS */
#define G16_S0     16 // 16 Group Options and No Sub Groups ( IPR[N](bits 4:7)the all 4 bits Selct INT Group )
#define G8_S2      8  // / 16 Options for Group and 2 for Sub Groups  ( IPR[N](bits 4:7) bits 5:7 Selct INT Group and bit 4 Select Sub Group )
#define G4_S4      4
#define G2_S8      2
#define G1_S16     1 // System has one group, SW Priority determined according to sub group
void SCB_SetNumberOfGroups (u8 A_NumberOfGroups ) ;

/*Address Passed as value not as an address (data sheet requirments)
example need to reset the address to 0x8004000 
SCB_ResetVectorTableAddress(0x8004000) ; not SCB_ResetVectorTableAddress( (u32*) 0x8004000) ;
*/
void SCB_ResetVectorTableAddress( u32 NewAddress  ) ;


#endif