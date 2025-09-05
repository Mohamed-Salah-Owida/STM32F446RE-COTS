#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/**
 * @file GPIO_Interface.h
 * @author Mohamed Salah Owida
 * @brief Public interface for GPIO driver (STM32F446xx)
 *
 * This file contains type definitions, enums, structures,
 * and function prototypes for GPIO configuration and control.
 */



/*=============================
    Port Definitions
 ==============================*/
/**
 * @enum Port_t
 * @brief Available GPIO ports on STM32F446xx
 */
typedef enum
{
	PORTA = 0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
}Port_t;

/*=============================
    Pin Definitions
 ==============================*/
/**
 * @enum Pin_t
 * @brief Pin numbers (0–15) for each port
 */
typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}Pin_t;

/*=============================
    Pin Mode Definitions
 ==============================*/
/**
 * @enum Mode_t
 * @brief Pin operating modes
 */
typedef enum
{
	INPUT = 0,
	OUTPUT,
	ALT_FUNC,
	ANALOG
}Mode_t;

/*=============================
    Output Speed Definitions
 ==============================*/
/**
 * @enum OutputSpeed_t
 * @brief Output driver speed
 */
typedef enum
{
	LOW_SPEED = 0,
	MEDIUM_SPEED,
	FAST_SPEED,
	HIGH_SPEED
}OutputSpeed_t;

/*=============================
    Output Type Definitions
 ==============================*/
/**
 * @enum OutputType_t
 * @brief Output driver type
 */
typedef enum
{
	PUSH_PULL = 0,
	OPEN_DRAIN
}OutputType_t;

/*=============================
    Alternate Function Definitions
 ==============================*/
/**
 * @enum AltFunc_t
 * @brief Alternate function numbers (AF0–AF15)
 *
 * Each AF maps a pin to a peripheral (USART, SPI, I2C, etc.)
 */
typedef enum
{
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AltFunc_t;

/*=============================
    Pull-Up / Pull-Down Definitions
 ==============================*/
/**
 * @enum PullType_t
 * @brief Internal resistor configuration
 */
typedef enum
{
	NO_PULL = 0,
	PULL_UP,
	PULL_DOWN
}PullType_t;

/*=============================
    Pin Value Definitions
 ==============================*/
/**
 * @enum PinVal_t
 * @brief Logical output/input values for pins
 */
typedef enum
{
	LOW = 0,
	HIGH
}PinVal_t;

/*=============================
    Pin Configuration Structure
 ==============================*/
/**
 * @struct PinConfig_t
 * @brief Configuration structure for GPIO pin initialization
 */
typedef struct
{
	Port_t Port;             /*  GPIO port (A–H) */
	Pin_t Pin;               /*  Pin number (0–15) */
	Mode_t Mode;             /*  Pin mode (Input, Output, AF, Analog) */
	OutputType_t OutputType; /*  Output type (Push-pull / Open-drain) */
	OutputSpeed_t Speed;     /*  Output speed */
	PullType_t PullType;     /*  Pull-up / Pull-down */
	AltFunc_t AltFunc;       /*  Alternate function number */
}PinConfig_t;

/*=============================
    Function Prototypes
 ==============================*/

/**
 * @brief Initialize a GPIO pin
 * @param PinConfig Pointer to configuration structure
 * @retval GPIOErrorStates_t
 */
uint8_t GPIO_u8PinInit(const PinConfig_t * PinConfig);

/**
 * @brief Set output pin value
 * @param Port  name (A–H)
 * @param Pin Pin number (0–15)
 * @param PinVal Value (LOW or HIGH)
 * @retval GPIOErrorStates_t
 */
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t Pin, PinVal_t PinVal);

/**
 * @brief Toggle output pin value
 * @param Port  name (A–H)
 * @param PinNum Pin number (0–15)
 * @retval GPIOErrorStates_t
 */
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum);

/**
 * @brief Read input pin value
 * @param Port  name (A–H)
 * @param PinNum Pin number (0–15)
 * @param PinVal Pointer to store read value
 * @retval GPIOErrorStates_t
 */
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t* PinVal);

#endif /* GPIO_INTERFACE_H_ */
