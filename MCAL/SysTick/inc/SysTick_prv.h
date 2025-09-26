#ifndef SYSTIC_PRV_H_
#define SYSTIC_PRV_H_


/*-------------------- System Configuration --------------------*/

// System clock frequency (Hz)
#define SYSTEM_FREQUANCY	16000000UL



#define MS_PER_SECOND    1000U     /* System clock frequency (Hz)*/

#define US_PER_SECOND    1000000U  /* Number of microseconds in one second*/

/* Value to reset the SysTick current value register*/
#define SYSTICK_CVR_RESET   0U

/* Value to reset the SysTick current value register   2^24 - 1 */
#define MAX_NO_TICKS    16777215UL


#define CSR_ENABLE_BIT_SHIFTING     0U
#define CSR_CLKSOURCE_BIT_SHIFTING   2u
#define CSR_COUNTFLAG_BIT_SHIFING   16U



#endif /* SYSTIC_PRV_H_ */
