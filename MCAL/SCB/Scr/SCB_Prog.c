#include <stdint.h>

#include "STM32F446xx.h"
#include "ErrType.h"

#include "SCB_Interface.h"
#include "SCB_Prv.h"

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



void SCB_EnableFault(SCB_FaultType_t faultType)
{
	switch (faultType)
	{
	case SCB_FAULT_MEMMANAGE:
		SCB->SHCRS |= (1<< SCB_SHCSR_MEMFAULTENA_Pos);
		break;

	case SCB_FAULT_BUS:
		SCB->SHCRS |= (1 << SCB_SHCSR_BUSFAULTENA_Pos);
		break;

	case SCB_FAULT_USAGE:
		SCB->SHCRS |= (1 << SCB_SHCSR_USGFAULTENA_Pos);
		break;

	default:
		/* Invalid type – do nothing or handle error */
		break;
	}
}



void SCB_DisableFault(SCB_FaultType_t faultType)
{
	switch (faultType)
		{
		case SCB_FAULT_MEMMANAGE:
			SCB->SHCRS &= ~(1<< SCB_SHCSR_MEMFAULTENA_Pos);
			break;

		case SCB_FAULT_BUS:
			SCB->SHCRS &= ~(1 << SCB_SHCSR_BUSFAULTENA_Pos);
			break;

		case SCB_FAULT_USAGE:
			SCB->SHCRS &= ~(1 << SCB_SHCSR_USGFAULTENA_Pos);
			break;

		default:
			/* Invalid type – do nothing or handle error */
			break;
		}
}



void SCB_EnableDivByZeroTrap(void)
{
    /* Set DIV_0_TRP (bit 4) in CCR: */
    SCB->CCR |= (1<<SCB_CCR_DIV_0_TRP_Pos);

}
