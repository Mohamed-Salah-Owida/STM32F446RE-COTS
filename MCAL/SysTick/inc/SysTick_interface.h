#ifndef SYSTIC_INTERFACE_H_   // Prevent multiple inclusions of this header file
#define SYSTIC_INTERFACE_H_

/**
 * @brief Delay execution for a specified number of milliseconds.
 *
 * This function uses the SysTick timer to generate a blocking delay.
 * @param copy_u32Ms  Number of milliseconds to delay.

 */
void SYSTICK_DelayMs(uint32_t copy_u32Ms);

/**
 * @brief Delay execution for a specified number of microseconds.
 *
 * This function uses the SysTick timer to generate a blocking delay.
 * @param copy_u32Us  Number of microseconds to delay.

 */
void SYSTICK_DelayUs(uint32_t copy_u32Us);

#endif /* SYSTIC_INTERFACE_H_ */  // End of include guard
