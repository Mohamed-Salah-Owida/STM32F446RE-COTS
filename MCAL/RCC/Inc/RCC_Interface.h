#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/*===========================================
 *   RCC DRIVER - INTERFACE HEADER FILE
 *   For STM32F446RE
 *===========================================*/


/*-------------------------------------------
 * Available clock source types
 *-------------------------------------------*/
typedef enum
{
	HSI,      // High Speed Internal oscillator (16 MHz)
	HSE,      // High Speed External oscillator (crystal or bypass)
	PLLP,     // Main PLL (P output -> system clock)
	PLLR,     // Main PLL (R output -> SAI/I2S clocks)
	PLLI2S,   // PLL dedicated for audio (I2S/SAI)
	PLLSAI    // PLL dedicated for SAI
}RCC_CLKTypes_t;


/*-------------------------------------------
 * HSE (High Speed External) clock modes
 *-------------------------------------------*/
typedef enum {
	HSE_CRYSTAL = 0,   // Use crystal oscillator on HSE pin
	HSE_BYPASS         // Use external clock signal on HSE pin (bypass mode)
} HSE_Mode_t;


/*-------------------------------------------
 * Clock status (enable or disable)
 * Used for turning ON/OFF HSI, HSE, PLL...
 *-------------------------------------------*/
typedef enum {
	ON,
	OFF
}RCC_CLKStatus_t;


/*-------------------------------------------
 * AHB1 peripherals (RCC_AHB1ENR register)
 * Each enum value corresponds to a bit position
 *-------------------------------------------*/
typedef enum
{
	AHB1_GPIOA,
	AHB1_GPIOB,
	AHB1_GPIOC,
	AHB1_GPIOD,
	AHB1_GPIOE,
	AHB1_GPIOF,
	AHB1_GPIOG,
	AHB1_GPIOH,
	AHB1_CRC = 12,
	AHB1_BKP_SRAM = 18,
	AHB1_DMA1 = 21,
	AHB1_DMA2,
	AHB1_OTGHS = 29,
	AHB1_OTGHS_ULPI
}AHB1_Peripheral_t;


/*-------------------------------------------
 * AHB2 peripherals (RCC_AHB2ENR register)
 *-------------------------------------------*/
typedef enum
{
	AHB2_DCMI = 0,
	AHB2_OTGFS = 7
}AHB2_Peripheral_t;


/*-------------------------------------------
 * AHB3 peripherals (RCC_AHB3ENR register)
 *-------------------------------------------*/
typedef enum
{
	AHB3_FMC = 0,
	AHB3_QSPI
}AHB3_Peripheral_t;


/*-------------------------------------------
 * APB1 peripherals (RCC_APB1ENR register)
 *-------------------------------------------*/
typedef enum
{
	APB1_TIM2,
	APB1_TIM3,
	APB1_TIM4,
	APB1_TIM5,
	APB1_TIM6,
	APB1_TIM7,
	APB1_TIM12,
	APB1_TIM13,
	APB1_TIM14,
	APB1_WWDG = 11,
	APB1_SPI2 = 14,
	APB1_SPI3,
	APB1_SPDIFRX,
	APB1_USART2,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_I2C3,
	APB1_FMPI2C1,
	APB1_CAN1,
	APB1_CAN2,
	APB1_CEC,
	APB1_PWR,
	APB1_DAC
}APB1_Peripheral_t;


/*-------------------------------------------
 * APB2 peripherals (RCC_APB2ENR register)
 *-------------------------------------------*/
typedef enum
{
	APB2_TIM1,
	APB2_TIM8,
	APB2_USART1 = 4,
	APB2_USART6,
	APB2_ADC1 = 8,
	APB2_ADC2,
	APB2_ADC3,
	APB2_SDIO,
	APB2_SPI1,
	APB2_SPI4,
	APB2_SYSCFG,
	APB2_TIM9 = 16,
	APB2_TIM10,
	APB2_TIM11,
	APB2_SAI1 = 22,
	APB2_SAI2
}APB2_Peripheral_t;


/*-------------------------------------------
 * PLL configuration structure
 * Fields must satisfy datasheet ranges:
 * - PLLM: input divider (2..63)
 * - PLLN: multiplier (50..432)
 * - PLLP: system clock divider (2,4,6,8)
 * - PLLQ: USB/SDIO/RNG divider (2..15)
 * - PLLR: SAI/I2S divider (2..7)
 * - PLLSource: 0=HSI, 1=HSE
 * - HSE_Value: HSE frequency in MHz
 *-------------------------------------------*/
typedef struct {
    uint8_t  PLLM;
    uint16_t PLLN;
    uint8_t  PLLP;
    uint8_t  PLLQ;
    uint8_t  PLLR;
    uint8_t  PLLSource;
    uint32_t HSE_Value;
} RCC_PLLConfig_t;


/*===========================================
 * Function Prototypes
 *===========================================*/

/* Enable/disable a specific clock source (HSI, HSE, PLL...) */
uint8_t RCC_SetClkStatus(RCC_CLKTypes_t CLKType, RCC_CLKStatus_t CLKStatus);

/* Select the system clock source (HSI, HSE, or PLLP) */
uint8_t RCC_SetSysClk(RCC_CLKTypes_t CLKType);

/* Configure HSE mode (crystal or bypass) */
uint8_t RCC_HSEConfig(HSE_Mode_t HSEMode);

/* Configure main PLL factors (PLLM, PLLN, PLLP, PLLQ, PLLR) */
uint8_t RCC_ConfigPLL(RCC_PLLConfig_t *PLLConfig);

/* Enable/disable peripherals on AHB1 bus */
void RCC_AHB1EnableClk(AHB1_Peripheral_t Peripheral);
void RCC_AHB1DisableClk(AHB1_Peripheral_t Peripheral);

/* Enable/disable peripherals on AHB2 bus */
void RCC_AHB2EnableClk(AHB2_Peripheral_t Peripheral);
void RCC_AHB2DisableClk(AHB2_Peripheral_t Peripheral);

/* Enable/disable peripherals on AHB3 bus */
void RCC_AHB3EnableClk(AHB3_Peripheral_t Peripheral);
void RCC_AHB3DisableClk(AHB3_Peripheral_t Peripheral);

/* Enable/disable peripherals on APB1 bus */
void RCC_APB1EnableCLK(APB1_Peripheral_t Peripheral);
void RCC_APB1DisableCLK(APB1_Peripheral_t Peripheral);

/* Enable/disable peripherals on APB2 bus */
void RCC_APB2EnableCLK(APB2_Peripheral_t Peripheral);
void RCC_APB2DisableCLK(APB2_Peripheral_t Peripheral);

#endif /* RCC_INTERFACE_H_ */
