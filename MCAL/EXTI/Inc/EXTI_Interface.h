#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


/*i.e LINE0 includes (PA0,PB0,PC0 ....)  -we decide the Port using SYSCFG */
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
} EXTI_Line_t;


typedef enum
{
    EXTI_DISABLE = 0,
    EXTI_ENABLE
} EXTI_State_t;


typedef enum
{
    EXTI_TRIGGER_RISING = 0,
    EXTI_TRIGGER_FALLING,
    EXTI_TRIGGER_BOTH
} EXTI_Trigger_t;

/* ============================================================
 *  Configuration structure for EXTI lines
 * ============================================================ */
typedef struct
{
    uint8_t Line;               /* EXTI line number (0..22 on STM32F446) */
    uint8_t Trigger;            /* Trigger selection: Rising, Falling, Both */
    uint8_t State;
    void (*Callback)(void);     /* User callback function for the interrupt */
} EXTI_Config_t;



/**
 * @brief  Initializes an EXTI line with the given configuration.
 * @param  Config: Pointer to a structure that holds the configuration settings
 *         for the EXTI line (trigger edge, mode, etc.).
 * @retval Status code (OK or ERROR).
 */
uint8_t EXTI_Init(const EXTI_Config_t* Config);


/**
 * @brief  Enables a specific EXTI line.
 * @param  Line: EXTI line to enable (e.g., EXTI0, EXTI1, ...).
 * @retval Status code (OK or ERROR).
 */
uint8_t EXTI_EnableLine(EXTI_Line_t Line);

/**
 * @brief  Disables a specific EXTI line.
 * @param  Line: EXTI line to disable.
 * @retval Status code (OK or ERROR).
 */
uint8_t EXTI_DisableLine(EXTI_Line_t Line);



/**
 * @brief  set trigger for  an EXTI line.
 * @param  Line: EXTI line number
 * @param  Trigger: EXTI trigger type
 * @retval Error state (OK or EXTI_WRONG_OPTION)
 */
uint8_t EXTI_SetTrgSource(EXTI_Line_t Line , EXTI_Trigger_t Trigger);


/**
 * @brief  Reads the pending interrupt flag for a specific EXTI line.
 * @param  Line: EXTI line to check.
 * @param  PendingState: Pointer to a variable where the pending state
 *         will be stored (1 = pending, 0 = not pending).
 * @retval Status code (OK or ERROR).
 */
uint8_t EXTI_ReadPendingFlag(EXTI_Line_t Line,uint8_t* PendingState);

/**
 * @brief  Clears the pending interrupt flag for a specific EXTI line.
 * @param  Line: EXTI line whose pending flag will be cleared.
 * @retval Status code (OK or ERROR).
 */
uint8_t EXTI_ClearPendingFlag(EXTI_Line_t Line);








#endif /* EXTI_INTERFACE_H_ */
