#include <stdint.h>
#include "STM32F446xx.h"
#include "ErrType.h"

#include "SYSCFG_Interface.h"
#include "SYSCFG_Prv.h"





/* ============================================================
 * @brief  Configure EXTI line to be connected to a specific GPIO port
 *
 * @param  Line : EXTI line number (0–15 for GPIO pins)
 * @param  Port : GPIO port to connect (SYSCFG_PORTA–SYSCFG_PORTG)
 *
 * @retval Error state:
 *         - OK if operation is successful
 *         - SYSCFG_WRONG_OPTION if line/port is invalid
 *==================================================================*/
uint8_t SYSCFG_SetEXTILine(SYSCFG_Line_t Line, SYSCFG_Port_t Port)
{
	uint8_t Local_u8ErrorState =OK ;

	if((Line < MAX_LINE_NUM) && (Port < MAX_PORT_NUM))
	{
		uint8_t RegNum = (Line  / EXTI_LINES_PER_REG);
		uint8_t BitNum = ((Line % EXTI_LINES_PER_REG) * EXTI_BITS_PER_LINE);

		SYSCFG -> EXTICR[RegNum] &= ~(EXTICR_4BITS_MASK << BitNum);
		SYSCFG -> EXTICR[RegNum] |=  (Port << BitNum);
	}
	else
	{
		Local_u8ErrorState = SYSCFG_WRONG_OPTION ;
	}

	return Local_u8ErrorState ;
}
