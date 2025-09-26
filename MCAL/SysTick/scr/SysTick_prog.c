#include <stdint.h>
#include "STM32F446xx.h"

#include "Systic_interface.h"
#include  "Systic_prv.h"




/**
 * @brief   Creates a delay in milliseconds using the SysTick timer.
 * @param   copy_u32Ms  Desired delay in milliseconds.
 */
void SYSTICK_DelayMs(uint32_t copy_u32Ms)
{
	/* Calculate ticks per millisecond based on system frequency*/
	uint32_t Local_u32Tick_per_ms = (SYSTEM_FREQUANCY / MS_PER_SECOND);
	/* Total number of ticks required for the delay*/
	uint32_t Local_u32Total_ticks = copy_u32Ms * Local_u32Tick_per_ms;
	uint32_t Local_u32Reload_value = 0;


	/* Select AHB as the clock source for SysTick */
	Systic -> CSR |= (1 << CSR_CLKSOURCE_BIT_SHIFTING);

	/* Loop until all ticks are consumed*/
	while(Local_u32Total_ticks > 0 )
	{
		/*Choose the reload value: either all remaining ticks or the maximum supported*/
		if(Local_u32Total_ticks  <= MAX_NO_TICKS)
		{
			Local_u32Reload_value = Local_u32Total_ticks ;
		}
		else

		{
			Local_u32Reload_value = MAX_NO_TICKS ;
		}

		/* Load the reload register (minus 1, as SysTick counts from this value to zero)*/
		Systic-> RVR = Local_u32Reload_value - 1;


		/* Clear the current value register to reset the counter*/
		Systic-> CVR = SYSTICK_CVR_RESET;

		/* Enable the SysTick timer*/
		Systic-> CSR |= (1 << CSR_ENABLE_BIT_SHIFTING);


		/* Wait until the COUNTFLAG is set (timer has reached zero)*/
		while (!((Systic-> CSR >> CSR_COUNTFLAG_BIT_SHIFING) & 1))
		{
			/* Do nothing */
		}

		/* Disable the SysTick timer*/
		Systic-> CSR &= ~(1 << CSR_ENABLE_BIT_SHIFTING);

		/*Subtract the elapsed ticks from the total*/
		Local_u32Total_ticks -= Local_u32Reload_value ;
	}
}


/**
 * @brief   Creates a delay in microseconds using the SysTick timer.
 * @param   copy_u32Us  Desired delay in microseconds.
 */
void SYSTICK_DelayUs(uint32_t copy_u32Us)
{
	/* Calculate ticks per microsecond based on system frequency*/
	uint32_t Local_u32Tick_per_Us = (SYSTEM_FREQUANCY / US_PER_SECOND);

	/*Total number of ticks required for the delay*/
	uint32_t Local_u32Total_ticks = copy_u32Us * Local_u32Tick_per_Us;
	uint32_t Local_u32Reload_value = 0;



	 /* Select AHB as the clock source for SysTick */
	Systic -> CSR |= (1 << CSR_CLKSOURCE_BIT_SHIFTING);

	 /* Loop until all ticks are consumed*/
	while(Local_u32Total_ticks > 0 )
	{
		 /* Choose the reload value: either all remaining ticks or the maximum supported*/
		if(Local_u32Total_ticks  <= MAX_NO_TICKS)
		{
			Local_u32Reload_value = Local_u32Total_ticks ;
		}
		else

		{
			Local_u32Reload_value = MAX_NO_TICKS ;
		}

        /* Load the reload register (minus 1, as SysTick counts from this value to zero)*/
		Systic-> RVR = Local_u32Reload_value - 1;

        /* Clear the current value register to reset the counter*/
		Systic-> CVR = SYSTICK_CVR_RESET;

        /* Enable the SysTick timer*/
		Systic-> CSR |= (1 << CSR_ENABLE_BIT_SHIFTING);

		 /* Wait until the COUNTFLAG is set (timer has reached zero)*/
		while (!((Systic-> CSR >> CSR_COUNTFLAG_BIT_SHIFING) & 1))
		{
			/* Do nothing */
		}

		 /* Disable the SysTick timer*/
		Systic-> CSR &= ~(1 << CSR_ENABLE_BIT_SHIFTING);

		 /* Subtract the elapsed ticks from the total*/
		Local_u32Total_ticks -= Local_u32Reload_value ;
	}
}





