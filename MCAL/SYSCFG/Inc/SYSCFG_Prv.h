#ifndef SYSCFG_PRV_H_
#define SYSCFG_PRV_H_





/* Maximum number of EXTI lines (0–15 = 16 lines total) */
#define MAX_LINE_NUM       15U

/* Maximum number of GPIO ports supported (A–F in STM32F4 series) */
#define MAX_PORT_NUM       6U


#define EXTI_LINES_PER_REG       4     /* Each EXTICR register handles 4 EXTI lines */
#define EXTI_BITS_PER_LINE       4     /* Each EXTI line is represented by 4 bits   */


/* Mask for 4-bit field in EXTICR registers
   Each EXTI line is configured using 4 bits */
#define EXTICR_4BITS_MASK  0xfU




#endif /* SYSCFG_PRV_H_ */
