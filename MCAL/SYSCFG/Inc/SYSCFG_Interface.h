#ifndef SYSCFG_INTERFACE_H_
#define SYSCFG_INTERFACE_H_


typedef enum
{
    SYSCFG_PORTA = 0,
    SYSCFG_PORTB,
    SYSCFG_PORTC,
    SYSCFG_PORTD,
    SYSCFG_PORTE,
    SYSCFG_PORTF,
    SYSCFG_PORTG,
} SYSCFG_Port_t;


typedef enum
{
    EXTI_LINE0 = 0,
    EXTI_LINE1,
    EXTI_LINE2,
    EXTI_LINE3,
    EXTI_LINE4,
    EXTI_LINE5,
    EXTI_LINE6,
    EXTI_LINE7,
    EXTI_LINE8,
    EXTI_LINE9,
    EXTI_LINE10,
    EXTI_LINE11,
    EXTI_LINE12,
    EXTI_LINE13,
    EXTI_LINE14,
    EXTI_LINE15,
    /* Add (e.g., EXTI16 = PVD, EXTI21 = RTC, etc.) */
} SYSCFG_Line_t;





/* ============================================================
 * @brief Map an EXTI line to a given port
 * @param line: EXTI line (0–15 for GPIO pins)
 * @param port: Port to be connected (A–G)
 * @return Error state (OK or error code)
 * ============================================================ */
uint8_t SYSCFG_SetEXTILine(SYSCFG_Line_t line, SYSCFG_Port_t port);


#endif /* SYSCFG_INTERFACE_H_ */
