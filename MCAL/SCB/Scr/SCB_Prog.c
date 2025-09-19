#include <stdint.h>

#include "STM32F446xx.h"
#include "ErrType.h"

#include "SCB_Interface.h"





/**
 * @brief  Sets the priority grouping for the NVIC by writing to SCB->AIRCR.
 *
 * @param  PriorityGroup: Use one of the macros SCB_PRI_GROUP_3..SCB_PRI_GROUP_7.
 *                        These include the required write key (0x05FA).
 *
 * @retval uint8_t:
 *         - OK                       : If PriorityGroup value is valid.
 *         - SCB_WRONG_PRI_GROUP_OPTION: If the value is outside the allowed range.
 */

uint8_t SCB_SetPriorityGroup(uint32_t PriorityGroup)
{
	uint8_t Local_u8ErrorState = OK;

	if(PriorityGroup >= SCB_PRI_GROUP_3 && PriorityGroup <= SCB_PRI_GROUP_7 )
	{
		 /* Write the priority group value directly to the AIRCR register*/
		SCB -> AIRCR = PriorityGroup ;
	}
	else
	{
		Local_u8ErrorState = SCB_WRONG_PRI_GROUP_OPTION ;
	}

	return Local_u8ErrorState;
}
