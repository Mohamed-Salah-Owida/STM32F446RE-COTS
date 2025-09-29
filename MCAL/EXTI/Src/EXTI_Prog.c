#include <stdint.h>
#include "STM32F446xx.h"
#include "ErrType.h"

#include "EXTI_Interface.h"
#include "EXTI_Prv.h"



/*
 * Array of callback function pointers for each EXTI line.
 * Each index corresponds to an EXTI line number.
 * When an interrupt occurs on that line, the stored callback is executed.
 */
void (*EXTI_CallBackArray[MAX_LINE_NUM + 1])(void) = {NULL};


/**
 * @brief  Initialize an EXTI line with the given configuration.
 * @param  Config: Pointer to EXTI_Config_t containing:
 *                 - Line number
 *                 - State (enable/disable)
 *                 - Trigger type (rising/falling/both)
 *                 - Callback function pointer
 * @retval Error state (OK, NULL_PTR, or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_Init(const EXTI_Config_t *Config)
{
	uint8_t Local_u8ErrorState = OK;

	if (Config != NULL)
	{
		if (Config->Line <= MAX_LINE_NUM)
		{
			/* 1 - Configure interrupt line state */
			if (Config->State == EXTI_ENABLE)
			{
				EXTI->IMR |= (1 << Config->Line);
			}

			else if (Config->State == EXTI_DISABLE)
			{
				EXTI->IMR &= ~(1 << Config->Line);
			}

			else
			{
				Local_u8ErrorState = EXTI_WRONG_OPTION;
			}


			/* 2 - Configure trigger selection */
			EXTI->RTSR &= ~(1 << Config->Line);  // clear first
			EXTI->FTSR &= ~(1 << Config->Line);

			switch (Config->Trigger)
			{
			case EXTI_TRIGGER_RISING:
				EXTI->RTSR |= (1 << Config->Line);
				break;
			case EXTI_TRIGGER_FALLING:
				EXTI->FTSR |= (1 << Config->Line);
				break;
			case EXTI_TRIGGER_BOTH:
				EXTI->RTSR |= (1 << Config->Line);
				EXTI->FTSR |= (1 << Config->Line);
				break;
			default:
				Local_u8ErrorState = EXTI_WRONG_OPTION;
			}

			/* 3 - Store the callback function */
			if (Config->Callback != NULL)
			{
				EXTI_CallBackArray[Config->Line] = Config-> Callback;
			}
		}
		else
		{
			Local_u8ErrorState = EXTI_WRONG_OPTION;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}







/**
 * @brief  Enable an EXTI line.
 * @param  Line: EXTI line number
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_EnableLine(EXTI_Line_t Line)
{
	uint8_t Local_u8ErrorState =OK ;

	if (Line <= MAX_LINE_NUM)
	{
		EXTI->IMR |= (1 << Line);
	}
	else
	{
		Local_u8ErrorState = EXTI_WRONG_OPTION;
	}

	return Local_u8ErrorState;
}


/**
 * @brief  Disable an EXTI line.
 * @param  Line: EXTI line number
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_DisableLine(EXTI_Line_t Line)
{
	uint8_t Local_u8ErrorState =OK ;

	if (Line <= MAX_LINE_NUM)
	{
		EXTI->IMR &= ~(1 << Line);
	}
	else
	{
		Local_u8ErrorState = EXTI_WRONG_OPTION;
	}

	return Local_u8ErrorState;
}


/**
 * @brief  set trigger for  an EXTI line.
 * @param  Line: EXTI line number
 * @param  Trigger: EXTI trigger type
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_SetTrgSource(EXTI_Line_t Line , EXTI_Trigger_t Trigger)
{
	uint8_t Local_u8ErrorState =OK ;


	/* 2 - Configure trigger selection */
	EXTI->RTSR &= ~(1 << Line);  // clear first
	EXTI->FTSR &= ~(1 << Line);

	switch (Trigger)
	{
	case EXTI_TRIGGER_RISING:
		EXTI->RTSR |= (1 << Line);
		break;
	case EXTI_TRIGGER_FALLING:
		EXTI->FTSR |= (1 << Line);
		break;
	case EXTI_TRIGGER_BOTH:
		EXTI->RTSR |= (1 <<Line);
		EXTI->FTSR |= (1 <<Line);
		break;
	default:
		Local_u8ErrorState = EXTI_WRONG_OPTION;
	}

	return Local_u8ErrorState;
}




/**
 * @brief  Read the pending flag for a given EXTI line.
 * @param  Line: EXTI line number
 * @param  PendingState: Pointer where result will be stored (1 = pending, 0 = not pending)
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */

uint8_t EXTI_ReadPendingFlag(EXTI_Line_t Line,uint8_t* PendingState)
{
	uint8_t Local_u8ErrorState =OK ;

	if(PendingState != NULL)
	{
		if (Line <= MAX_LINE_NUM)
		{
			*PendingState = ( ((EXTI->PR) >> Line) & 1 );
		}
		else
		{
			Local_u8ErrorState = EXTI_WRONG_OPTION;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;

}


/**
 * @brief  Clear the pending flag for a given EXTI line.
 * @param  Line: EXTI line number
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_ClearPendingFlag(EXTI_Line_t Line)
{
	uint8_t Local_u8ErrorState =OK ;

	if (Line <= MAX_LINE_NUM)
	{
		/* Writing 1 clears the pending bit */
		EXTI->PR = (1 << Line);
	}
	else
	{
		Local_u8ErrorState = EXTI_WRONG_OPTION;
	}

	return Local_u8ErrorState;

}

/* ======================= Interrupt Handlers ======================= */


/**
 * @brief  Handle EXTI line 0 interrupt
 */
void EXTI0_IRQHandler(void)
{
	if (EXTI_CallBackArray[0] != NULL)
	{
		EXTI_ClearPendingFlag(0);
		EXTI_CallBackArray[0]();  /*Call user function*/
	}
}



/**
 * @brief  Handle EXTI line 1 interrupt
 */
void EXTI1_IRQHandler (void)
{
	if (EXTI_CallBackArray[1] != NULL)
	{
		EXTI_ClearPendingFlag(1);
		EXTI_CallBackArray[1]();
	}
}
/**
 * @brief  Handle EXTI line 2 interrupt
 */
void EXTI2_IRQHandler (void)
{
	if (EXTI_CallBackArray[2] != NULL)
	{
		EXTI_ClearPendingFlag(2);
		EXTI_CallBackArray[2]();
	}
}


/**
 * @brief  Handle EXTI line 3 interrupt
 */
void EXTI3_IRQHandler (void)
{
	if (EXTI_CallBackArray[3] != NULL)
	{
		EXTI_ClearPendingFlag(3);
		EXTI_CallBackArray[3]();
	}
}

/**
 * @brief  Handle EXTI line 4 interrupt
 */
void EXTI4_IRQHandler (void)
{
	if (EXTI_CallBackArray[4] != NULL)
	{
		EXTI_ClearPendingFlag(4);
		EXTI_CallBackArray[4]();
	}
}



/**
 * @brief  Handle EXTI lines 5 to 9 interrupts (shared vector).
 *         Checks which line caused the interrupt, clears its flag,
 *         and calls the corresponding callback.
 */
void EXTI9_5_IRQHandler(void)
{
	uint8_t Local_u8PendingFlagState ;
	uint8_t Local_u8Iterator ;

	for(Local_u8Iterator = 5 ; Local_u8Iterator <=9 ; Local_u8Iterator++)
	{
		EXTI_ReadPendingFlag(Local_u8Iterator,&Local_u8PendingFlagState);

		if(Local_u8PendingFlagState == 1)
		{
			if (EXTI_CallBackArray[Local_u8Iterator] != NULL)
			{
				EXTI_ClearPendingFlag(Local_u8Iterator);
				EXTI_CallBackArray[Local_u8Iterator]();

			}
		}
	}

}


/**
 * @brief  Handle EXTI lines 10 to 15 interrupts (shared vector).
 */
void EXTI15_10_IRQHandler(void)
{
	uint8_t Local_u8PendingFlagState ;
	uint8_t Local_u8Iterator ;

	for(Local_u8Iterator = 10 ; Local_u8Iterator <=15 ; Local_u8Iterator++)
	{
		EXTI_ReadPendingFlag(Local_u8Iterator,&Local_u8PendingFlagState);
		if(Local_u8PendingFlagState == 1)
		{
			if (EXTI_CallBackArray[Local_u8Iterator] != NULL)
			{
				EXTI_ClearPendingFlag(Local_u8Iterator);
				EXTI_CallBackArray[Local_u8Iterator]();

			}
		}
	}

}
