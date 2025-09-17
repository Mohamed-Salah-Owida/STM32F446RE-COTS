#ifndef NVIC_PRV_H_
#define NVIC_PRV_H_

/* ================================================================
 * NVIC_PRV_H_
 * Private definitions for Nested Vectored Interrupt Controller (NVIC)
 * ================================================================
 */


/* NVIC registers (ISER, ICER, etc.) are grouped in 32-bit blocks*/
#define  NVIC_REG_SIZE                32U

/* Range of supported external interrupt numbers for this MCU*/
#define  INTERRUPTS_START             0U
#define  INTERRUPTS_END               96U

/* Valid priority levels for this device*/
#define MIN_PRIORITY_NUM              0U
#define MAX_PRIORITY_NUM              15U

/* In the NVIC Interrupt Priority Registers (IPR), only the upper 4 bits*/
#define IPR_PRIORITY_FIELD_SHIFTING   4U















#endif /* NVIC_PRV_H_ */
