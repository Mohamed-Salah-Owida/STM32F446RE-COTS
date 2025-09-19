/**
 ******************************************************************************
 * @file    SCB_Interface.h
 * @brief   System Control Block (SCB) Priority Grouping Interface.
 *          This file defines macros, enums, and function prototypes for
 *          configuring interrupt priority grouping on ARM Cortex-M processors.
 *
 *          Priority grouping splits the available priority bits between
 *          "group priority" (preemption) and "subpriority" (tie-breaking).
 *          These settings directly affect how the Nested Vectored Interrupt
 *          Controller (NVIC) handles interrupt arbitration.
 *
 * @note    The 0x05FAxxxx values are written to the SCB->AIRCR register to
 *          select priority grouping (see ARM Cortex-M Architecture Reference).
 ******************************************************************************
 */

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_




/* ----------------------------- PRIORITY GROUP MACROS ----------------------
 * Each macro corresponds to a PRIGROUP configuration written to SCB->AIRCR.
 * Format: 0x05FA0X00 (where X = 3..7).
 *
 * Group priority = preemption level.
 * Subpriority    = priority within the same group level.
 */
#define SCB_PRI_GROUP_3     (0x05FA0300)        /*group priority 4, subpriority 0*/
#define SCB_PRI_GROUP_4     (0x05FA0400)        /*group priority 3, subpriority 1*/
#define SCB_PRI_GROUP_5     (0x05FA0500)        /*group priority 2, subpriority 2*/
#define SCB_PRI_GROUP_6     (0x05FA0600)        /*group priority 1, subpriority 3*/
#define SCB_PRI_GROUP_7     (0x05FA0700)        /*group priority 0, subpriority 4*/



/* ----------------------------- ENUMS FOR GROUP 3 --------------------------
 * Priority options for PRIGROUP = 3 (4 group bits, 0 subpriority bits).
 * Only group levels matter; no subpriorities exist.
 */
typedef enum
{
    G0, G1, G2, G3, G4, G5, G6, G7,
    G8, G9, G10, G11, G12, G13, G14, G15
} PriGroup3_Options_t;

/* ----------------------------- ENUMS FOR GROUP 4 --------------------------
 * PRIGROUP = 4 (3 group bits, 1 subpriority bit).
 * 8 groups × 2 subpriorities = 16 options.
 */
typedef enum
{
    G0_S0, G0_S1,
    G1_S0, G1_S1,
    G2_S0, G2_S1,
    G3_S0, G3_S1,
    G4_S0, G4_S1,
    G5_S0, G5_S1,
    G6_S0, G6_S1,
    G7_S0, G7_S1
} PriGroup4_Options_t;

/* ----------------------------- ENUMS FOR GROUP 5 --------------------------
 * PRIGROUP = 5 (2 group bits, 2 subpriority bits).
 * 4 groups × 4 subpriorities = 16 options.
 */
typedef enum
{
    G0_S0, G0_S1, G0_S2, G0_S3,
    G1_S0, G1_S1, G1_S2, G1_S3,
    G2_S0, G2_S1, G2_S2, G2_S3,
    G3_S0, G3_S1, G3_S2, G3_S3
} PriGroup5_Options_t;

/* ----------------------------- ENUMS FOR GROUP 6 --------------------------
 * PRIGROUP = 6 (1 group bit, 3 subpriority bits).
 * 2 groups × 8 subpriorities = 16 options.
 */
typedef enum
{
    G0_S0, G0_S1, G0_S2, G0_S3, G0_S4, G0_S5, G0_S6, G0_S7,
    G1_S0, G1_S1, G1_S2, G1_S3, G1_S4, G1_S5, G1_S6, G1_S7
} PriGroup6_Options_t;


/* ----------------------------- ENUMS FOR GROUP 7 --------------------------
 * PRIGROUP = 7 (0 group bits, 4 subpriority bits).
 * Only subpriorities matter; all belong to a single group.
 */
typedef enum
{
    S0, S1, S2, S3, S4, S5, S6, S7,
    S8, S9, S10, S11, S12, S13, S14, S15
}PriGroup7_Options_t;





/**
 * @brief  Set the priority grouping for NVIC interrupts.
 * @param  PriorityGroup: Use one of the SCB_PRI_GROUP_X macros.
 * @retval uint8_t: Returns 0 (OK) on success or an error code.
 */
uint8_t SCB_SetPriorityGroup(uint32_t PriorityGroup);



#endif /* SCB_INTERFACE_H_ */
