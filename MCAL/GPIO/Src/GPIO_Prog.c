#include <stdint.h>
#include <stddef.h>
#include "STM32F446xx.h"
#include "GPIO_Interface.h"
#include "GPIO_Prv.h"



/**
 * @brief  Initialize a GPIO pin with the given configuration
 * @param[in]  PinConfig: Pointer to pin configuration structure (Mode, Speed, Pull, etc.)
 * @retval GPIOErrorStates_t (error code: OK, NullPtr, InvalidPortName)
 *
 * This function configures:
 *  - Pin mode (Input, Output, Alternate Function, Analog)
 *  - Output type (Push-pull, Open-drain)
 *  - Output speed (Low, Medium, Fast, High)
 *  - Pull-up / Pull-down resistors
 *  - Alternate function (if mode = ALT_FUNC)
 */
uint8_t GPIO_u8PinInit(const PinConfig_t * PinConfig)  //const ptr to follow least privilege rule   so the function cann't change in the struct
{
	GPIOErrorStates_t ErrorState = GPIO_OK;

	if (PinConfig != NULL) // Check if pointer is valid
	{

		switch(PinConfig ->Port)  // Select GPIO port
		{
		/************************************  PORTA *********************************/
		case PORTA:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOA -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOA -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOA -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOA -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOA -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOA -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOA -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOA -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7) // AFR[0] for pins 0-7
				{
					GPIOA -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOA -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8) // AFR[1] for pins 8-15
				{
					GPIOA -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOA -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTB*********************************/
		case PORTB:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOB -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOB -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOB -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOB -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOB -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOB -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOB -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOB -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)// AFR[0] for pins 0-7
				{
					GPIOB -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOB -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)// AFR[1] for pins 8-15
				{
					GPIOB -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOB -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTC *********************************/
		case PORTC:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOC -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOC -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOC -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOC -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOC -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOC -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOC -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOC -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOC -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOC -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOC -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOC -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTD *********************************/
		case PORTD:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOD -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOD -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOD -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOD -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOD -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOD -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOD -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOD -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOD -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOD -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOD -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOD -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTE *********************************/
		case PORTE:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOE -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOE -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOE -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOE -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOE -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOE -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOE -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOE -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOE -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOE -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOE -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOE -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTF *********************************/
		case PORTF:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOF -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOF -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOF -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOF -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOF -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOF -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOF -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOF -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOF -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOF -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOF -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOF -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

			/************************************  PORTG *********************************/
		case PORTG:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOG -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOG -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOG -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOG -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOG -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOG -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOG -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOG -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOG -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOG -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOG -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOG -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;

		case PORTH:
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			GPIOH -> MODER &= ~(GPIO_2BIT_MASK  << (2*(PinConfig->Pin)));
			GPIOH -> MODER |= ((PinConfig -> Mode ) << (2*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				GPIOH -> OTYPER &= ~( GPIO_1BIT_MASK << (PinConfig -> Pin));
				GPIOH -> OTYPER |= ((PinConfig -> OutputType ) << (PinConfig -> Pin));


				// Output speed: Low / Medium / Fast / High
				GPIOH -> OSPEEDR &= ~( GPIO_2BIT_MASK << (2*(PinConfig->Pin)));
				GPIOH -> OSPEEDR |= ((PinConfig -> Speed ) << (2*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			GPIOH -> PUPDR &= ~( GPIO_2BIT_MASK << (2*PinConfig -> Pin));
			GPIOH -> PUPDR |= ((PinConfig -> PullType ) << (2*(PinConfig->Pin)));

			if(PinConfig -> Mode   == ALT_FUNC)
			{
				/* 4- If Alternate Function mode → set AF register */
				if(PinConfig -> Pin <= 7)
				{
					GPIOH -> AFR[0] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin)));
					GPIOH -> AFR[0] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin)));

				}
				else if(PinConfig -> Pin >= 8)
				{
					GPIOH -> AFR[1] &= ~( GPIO_4BIT_MASK << (4*(PinConfig->Pin - 8 )));
					GPIOH -> AFR[1] |= ((PinConfig -> AltFunc ) << (4*(PinConfig->Pin -8)));
				}

			}
			break;
		default : ErrorState = GPIO_InvalidPortName ;break ;
		}


	}
	else
	{
		ErrorState = GPIO_NullPtr ;
	}

	return ErrorState ;
}



/**
 * @brief  Set pin output value (HIGH or LOW)
 * @param  Port: GPIO port
 * @param  Pin: Pin number (0-15)
 * @param  PinVal: LOW (0) or HIGH (1)
 * @retval GPIOErrorStates_t
 *
 * Uses BSRR register:
 *   - Writing to bits 0–15 → sets pin to 1 (HIGH)
 *   - Writing to bits 16–31 → resets pin to 0 (LOW)
 */
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t Pin, PinVal_t PinVal)
{
	GPIOErrorStates_t ErrorState = GPIO_OK;
	switch (Port)
	{
	case PORTA :
		if(PinVal == HIGH )
		{ GPIOA -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOA -> BSRR = (1 << (Pin+16)); }break ;
	case PORTB :
		if(PinVal == HIGH )
		{ GPIOB -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOB -> BSRR = (1 << (Pin+16)); } break ;
	case PORTC :
		if(PinVal == HIGH )
		{ GPIOC -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOC -> BSRR = (1 << (Pin+16)); } break ;
	case PORTD :
		if(PinVal == HIGH )
		{ GPIOD -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOD-> BSRR = (1 << (Pin+16)); } break ;
	case PORTE :
		if(PinVal == HIGH )
		{ GPIOE -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOE -> BSRR = (1 << (Pin+16)); } break ;
	case PORTF :
		if(PinVal == HIGH )
		{ GPIOF -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOF -> BSRR = (1 << (Pin+16)); } break ;
	case PORTG :
		if(PinVal == HIGH )
		{ GPIOG -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOG -> BSRR = (1 << (Pin+16)); } break ;
	case PORTH :
		if(PinVal == HIGH )
		{ GPIOH -> BSRR = (1 << Pin); }
		else if (PinVal == LOW )
		{ GPIOH -> BSRR = (1 << (Pin+16)); }break;
	default : ErrorState = GPIO_InvalidPortName;break;

	}

	return ErrorState ;

}



/**
 * @brief  Toggle output pin value
 * @param  Port: GPIO port
 * @param  Pin: Pin number
 * @retval GPIOErrorStates_t
 *
 * Uses ODR (Output Data Register) with XOR to flip bit.
 */
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t Pin)
{
	GPIOErrorStates_t ErrorState = GPIO_OK;
	switch(Port)
	{
	case PORTA: GPIOA->ODR ^= (1 << Pin); break;
	case PORTB: GPIOB->ODR ^= (1 << Pin); break;
	case PORTC: GPIOC->ODR ^= (1 << Pin); break;
	case PORTD: GPIOD->ODR ^= (1 << Pin); break;
	case PORTE: GPIOE->ODR ^= (1 << Pin); break;
	case PORTF: GPIOF->ODR ^= (1 << Pin); break;
	case PORTG: GPIOG->ODR ^= (1 << Pin); break;
	case PORTH: GPIOH->ODR ^= (1 << Pin); break;
	default: ErrorState = GPIO_InvalidPortName; break;
	}

	return ErrorState ;
}




/**
 * @brief  Read input pin value
 * @param  Port: GPIO port
 * @param  Pin: Pin number
 * @param  PinVal: Pointer to store pin state (0 or 1)
 * @retval GPIOErrorStates_t
 *
 * Reads IDR (Input Data Register).
 */
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t Pin, PinVal_t* PinVal)
{
	GPIOErrorStates_t ErrorState = GPIO_OK;

	if(PinVal != NULL) // Check pointer validity
	{
		switch(Port)
		{
		case PORTA: *PinVal = (GPIOA->IDR >> Pin) & 1; break;
		case PORTB: *PinVal = (GPIOB->IDR >> Pin) & 1; break;
		case PORTC: *PinVal = (GPIOC->IDR >> Pin) & 1; break;
		case PORTD: *PinVal = (GPIOD->IDR >> Pin) & 1; break;
		case PORTE: *PinVal = (GPIOE->IDR >> Pin) & 1; break;
		case PORTF: *PinVal = (GPIOF->IDR >> Pin) & 1; break;
		case PORTG: *PinVal = (GPIOG->IDR >> Pin) & 1; break;
		case PORTH: *PinVal = (GPIOH->IDR >> Pin) & 1; break;
		default: ErrorState = GPIO_InvalidPortName; break;
		}
	}
	else
	{
		ErrorState =GPIO_InvalidPortName;
	}

	return ErrorState ;
}





