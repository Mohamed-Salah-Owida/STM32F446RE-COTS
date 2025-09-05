#include <stdint.h>
#include <stddef.h>
#include "STM32F446xx.h"
#include "GPIO_Interface.h"
#include "GPIO_Prv.h"
#include "ErrType.h"




// static following least privilege rules
static GPIO_RegDef_t* GPIO_PORT[GPIO_PERIPHERAL_NUM] ={GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH };


/**
 * @brief  Initialize a GPIO pin with the given configuration
 * @param[in]  PinConfig: Pointer to pin configuration structure (Mode, Speed, Pull, etc.)
 * @retval Error_State (error code: OK, NullPtr, InvalidPortName)
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
	uint8_t ErrorState = OK;

	if (PinConfig != NULL) // Check if pointer is valid
	{
		if((PinConfig->Port <= PORTH) && (PinConfig->Pin <= PIN15))
		{
			/* 1- Configure pin mode (00: Input, 01: Output, 10: Alt func, 11: Analog) */
			(GPIO_PORT[PinConfig->Port] -> MODER) &= ~(( GPIO_2BIT_MASK ) << (MODE_REG_PIN_ACCESS*(PinConfig->Pin)));
			(GPIO_PORT[PinConfig->Port] -> MODER) |=  ((PinConfig->Mode ) << (MODE_REG_PIN_ACCESS*(PinConfig->Pin)));

			/* 2- If Output or Alternate Function → configure Type & Speed */
			if(PinConfig -> Mode == OUTPUT    || PinConfig -> Mode == ALT_FUNC )
			{
				// Output type: Push-pull / Open-drain
				(GPIO_PORT[PinConfig->Port] -> OTYPER) &= ~( GPIO_1BIT_MASK << (PinConfig->Pin));
				(GPIO_PORT[PinConfig->Port] -> OTYPER) |= ((PinConfig->OutputType ) << (PinConfig->Pin));


				// Output speed: Low / Medium / Fast / High
				(GPIO_PORT[PinConfig->Port] -> OSPEEDR) &= ~(( GPIO_2BIT_MASK )<< (OSPEEDR_REG_PIN_ACCESS*(PinConfig->Pin)));
				(GPIO_PORT[PinConfig->Port] -> OSPEEDR) |=  ((PinConfig->Speed)<< (OSPEEDR_REG_PIN_ACCESS*(PinConfig->Pin)));
			}

			/* 3- Configure Pull-up / Pull-down (00: None, 01: PU, 10: PD) */
			(GPIO_PORT[PinConfig->Port] -> PUPDR) &= ~(( GPIO_2BIT_MASK ) << (PUPD_REG_PIN_ACCESS*(PinConfig->Pin)));
			(GPIO_PORT[PinConfig->Port] -> PUPDR) |=  ((PinConfig->PullType) << (PUPD_REG_PIN_ACCESS*(PinConfig->Pin)));

			/* 4- If Alternate Function mode → set AF register */
			if(PinConfig -> Mode   == ALT_FUNC)
			{
				uint8_t Local_u8RegNum =(PinConfig->Pin)/PINS_PER_AFR_REG;
				uint8_t Local_u8PinNum =(PinConfig->Pin) %PINS_PER_AFR_REG;
				(GPIO_PORT[PinConfig->Port] -> AFR[Local_u8RegNum]) &= ~( GPIO_4BIT_MASK<< (AFR_REG_PIN_ACCESS*(Local_u8PinNum)));
				(GPIO_PORT[PinConfig->Port] -> AFR[Local_u8RegNum]) |=((PinConfig -> AltFunc ) << (AFR_REG_PIN_ACCESS*(Local_u8PinNum)));
			}
		}

		else
		{
			ErrorState = INVALID_PORT_NUM ;
		}
	}
	else
	{
		ErrorState = NULL_PTR ;
	}
	return ErrorState ;
}



/**
 * @brief  Set pin output value (HIGH or LOW)
 * @param  Port: GPIO port
 * @param  Pin: Pin number (0-15)
 * @param  PinVal: LOW (0) or HIGH (1)
 * @retval Error_State
 *
 * Uses BSRR register:
 *   - Writing to bits 0–15 → sets pin to 1 (HIGH)
 *   - Writing to bits 16–31 → resets pin to 0 (LOW)
 */
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t Pin, PinVal_t PinVal)
{
	uint8_t ErrorState = OK;

	if((Port <= PORTH) && (Pin <= PIN15))
	{

		if(PinVal == HIGH )
		{
			(GPIO_PORT[Port])->BSRR = (1 << Pin);
		}
		else if(PinVal == LOW )
		{
			(GPIO_PORT[Port])->BSRR = (1 << (Pin+16));
		}
		else
		{
			ErrorState = NOK ;
		}
	}
	else
	{
		ErrorState = INVALID_PORT_NUM ;
	}

	return ErrorState ;

}



/**
 * @brief  Toggle output pin value
 * @param  Port: GPIO port
 * @param  Pin: Pin number
 * @retval Error_State
 *
 * Uses ODR (Output Data Register) with XOR to flip bit.
 */
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t Pin)
{
	uint8_t ErrorState = OK;

	if((Port <= PORTH) && (Pin <= PIN15))
	{

		(GPIO_PORT[Port])->ODR ^= (1 << Pin);

	}
	else
	{
		ErrorState = INVALID_PORT_NUM ;
	}

	return ErrorState ;
}




/**
 * @brief  Read input pin value
 * @param  Port: GPIO port
 * @param  Pin: Pin number
 * @param  PinVal: Pointer to store pin state (0 or 1)
 * @retval Error_State
 *
 * Reads IDR (Input Data Register).
 */
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t Pin, PinVal_t* PinVal)
{
	uint8_t ErrorState = OK;



	if(PinVal != NULL) // Check pointer validity
	{
		if((Port <= PORTH) && (Pin <= PIN15))
		{

			*PinVal = ((GPIO_PORT[Port])->IDR >> Pin) & 1;

		}
		else
		{
			ErrorState = INVALID_PORT_NUM ;
		}
	}
	else
	{
		ErrorState =INVALID_PORT_NUM;
	}

	return ErrorState ;
}





