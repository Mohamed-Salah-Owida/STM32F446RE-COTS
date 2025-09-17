#include <stdint.h>
#include "STM32F446xx.h"
#include "ErrType.h"

#include "NVIC_Interface.h"
#include "NVIC_Prv.h"

/*============================================================================
 * Enable an interrupt in NVIC
 * Arguments:
 *   Copy_u8IRQ – IRQ number from NVIC_IRQ_t enum
 * Returns:
 *   OK or NVIC_WRONG_IRQ_OPTION if IRQ number is invalid
 *===========================================================================*/
uint8_t NVIC_EnableIRQ(NVIC_IRQ_t  Copy_u8IRQ )
{
	uint8_t Local_u8ErrorState =OK ;

	if((Copy_u8IRQ >= INTERRUPTS_START)  && (Copy_u8IRQ <= INTERRUPTS_END) )
	{
        /* Determine which ISER register and bit correspond to this IRQ*/
		uint8_t Local_u8RegNum = (Copy_u8IRQ / NVIC_REG_SIZE);
		uint8_t Local_u8BitNum = (Copy_u8IRQ % NVIC_REG_SIZE);

        /* Write 1 to ISER bit to enable interrupt*/
		NVIC -> ISER[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION   ;
	}

	return Local_u8ErrorState ;
}


/*============================================================================
 * Disable an interrupt in NVIC
 *===========================================================================*/
uint8_t NVIC_DisnableIRQ(NVIC_IRQ_t Copy_u8IRQ)
{
	uint8_t Local_u8ErrorState =OK ;

	if((Copy_u8IRQ >= INTERRUPTS_START)  && (Copy_u8IRQ <= INTERRUPTS_END) )
	{
		uint8_t Local_u8RegNum = (Copy_u8IRQ / NVIC_REG_SIZE);
		uint8_t Local_u8BitNum = (Copy_u8IRQ % NVIC_REG_SIZE);

        /*Write 1 to ICER bit to disable interrupt*/
		NVIC -> ICER[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION   ;
	}

	return Local_u8ErrorState ;
}

/*============================================================================
 * Set pending flag for an interrupt (software-triggered interrupt)
 *===========================================================================*/
uint8_t NVIC_SetPendingFlag(NVIC_IRQ_t Copy_u8IRQ)
{
	uint8_t Local_u8ErrorState =OK ;

	if((Copy_u8IRQ >= INTERRUPTS_START)  && (Copy_u8IRQ <= INTERRUPTS_END) )
	{
		uint8_t Local_u8RegNum = (Copy_u8IRQ / NVIC_REG_SIZE);
		uint8_t Local_u8BitNum = (Copy_u8IRQ % NVIC_REG_SIZE);
		NVIC -> ISPR[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION   ;
	}

	return Local_u8ErrorState ;
}


/*============================================================================
 * Clear pending flag for an interrupt
 *===========================================================================*/
uint8_t NVIC_ClearPendingFlag(NVIC_IRQ_t Copy_u8IRQ)
{
	uint8_t Local_u8ErrorState =OK ;

	if((Copy_u8IRQ >= INTERRUPTS_START)  && (Copy_u8IRQ <= INTERRUPTS_END) )
	{
		uint8_t Local_u8RegNum = (Copy_u8IRQ / NVIC_REG_SIZE);
		uint8_t Local_u8BitNum = (Copy_u8IRQ % NVIC_REG_SIZE);
		NVIC -> ICPR[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION   ;
	}

	return Local_u8ErrorState ;
}


/*============================================================================
 * Get active flag status for an interrupt
 *===========================================================================*/
uint8_t NVIC_GetActiveFlag(NVIC_IRQ_t Copy_u8IRQ, uint8_t* Copy_u8ActvFlgStat)
{

	uint8_t Local_u8ErrorState = OK;


	if((Copy_u8IRQ >= INTERRUPTS_START) && (Copy_u8IRQ <= INTERRUPTS_END))
	{
		uint8_t Local_u8RegNum = (Copy_u8IRQ / NVIC_REG_SIZE);
		uint8_t Local_u8BitNum = (Copy_u8IRQ % NVIC_REG_SIZE);

		*Copy_u8ActvFlgStat = (1 & ((NVIC -> IABR[Local_u8RegNum]) >> Local_u8BitNum));

	}

	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION  ;
	}


	return Local_u8ErrorState;
}



/*============================================================================
 * Set interrupt priority
 *   - Priority values are shifted into the high bits (<< 4) because
 *     STM32F4 uses only upper bits of each 8-bit priority field.
 *===========================================================================*/
uint8_t NVIC_SetPriority(NVIC_IRQ_t Copy_u8IRQ, uint8_t Copy_u8Priority)
{

	uint8_t Local_u8ErrorState = OK;

	if((Copy_u8IRQ >= INTERRUPTS_START) && (Copy_u8IRQ <= INTERRUPTS_END))
	{

		if((Copy_u8Priority >= MIN_PRIORITY_NUM) && (Copy_u8Priority <= MAX_PRIORITY_NUM))
		{
			(NVIC -> IPR[Copy_u8IRQ]) = Copy_u8Priority << IPR_PRIORITY_FIELD_SHIFTING;
		}

		else
		{
			Local_u8ErrorState = NVIC_Invalid_Priority;
		}

	}
	else
	{
		Local_u8ErrorState = NVIC_WRONG_IRQ_OPTION  ;
	}

	return Local_u8ErrorState;
}
