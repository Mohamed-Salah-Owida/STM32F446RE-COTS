#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/* ================================================================
 * NVIC_INTERFACE_H_
 * Public interface for the Nested Vectored Interrupt Controller (NVIC)
 * ================================================================
 *
 * This file defines:
 *   1. NVIC_IRQ_t: Enumeration of all available external interrupt numbers
 *      for the STM32 device (matches vector table indices).
 *   2. Function prototypes to control NVIC interrupt enable/disable
 *      and pending flags.
 */


typedef enum
{
	IRQ0_WWDG,
	IRQ1_PVD,
	IRQ2_TAMP_STAMP,
	IRQ3_RTC_WKUP,
	IRQ4_FLASH,
	IRQ5_RCC,
	IRQ6_EXTI0,
	IRQ7_EXTI1,
	IRQ8_EXTI2,
	IRQ9_EXTI3,
	IRQ10_EXTI4,
	IRQ11_DMA1_Stream0,
	IRQ12_DMA1_Stream1,
	IRQ13_DMA1_Stream2,
	IRQ14_DMA1_Stream3,
	IRQ15_DMA1_Stream4,
	IRQ16_DMA1_Stream5,
	IRQ17_DMA1_Stream6,
	IRQ18_ADC,
	IRQ19_CAN1_TX,
	IRQ20_CAN1_RX0,
	IRQ21_CAN1_RX1,
	IRQ22_CAN1_SCE,
	IRQ23_EXTI9_5,
	IRQ24_TIM1_BRK_TIM9,
	IRQ25_TIM1_UP_TIM10,
	IRQ26_TIM1_TRG_COM_TIM11,
	IRQ27_TIM1_CC,
	IRQ28_TIM2,
	IRQ29_TIM3,
	IRQ30_TIM4,
	IRQ31_I2C1_EV,
	IRQ32_I2C1_ER,
	IRQ33_I2C2_EV,
	IRQ34_I2C2_ER,
	IRQ35_SPI1,
	IRQ36_SPI2,
	IRQ37_USART1,
	IRQ38_USART2,
	IRQ39_USART3,
	IRQ40_EXTI15_10,
	IRQ41_RTC_Alarm,
	IRQ42_OTG_FS_WKUP,
	IRQ43_TIM8_BRK_TIM12,
	IRQ44_TIM8_UP_TIM13,
	IRQ45_TIM8_TRG_COM_TIM14,
	IRQ46_TIM8_CC,
	IRQ47_DMA1_Stream7,
	IRQ48_FMC,
	IRQ49_SDIO,
	IRQ50_TIM5,
	IRQ51_SPI3,
	IRQ52_UART4,
	IRQ53_UART5,
	IRQ54_TIM6_DAC,
	IRQ55_TIM7,
	IRQ56_DMA2_Stream0,
	IRQ57_DMA2_Stream1,
	IRQ58_DMA2_Stream2,
	IRQ59_DMA2_Stream3,
	IRQ60_DMA2_Stream4,
	IRQ61_Reserved,
	IRQ62_Reserved,
	IRQ63_CAN2_TX,
	IRQ64_CAN2_RX0,
	IRQ65_CAN2_RX1,
	IRQ66_CAN2_SCE,
	IRQ67_OTG_FS,
	IRQ68_DMA2_Stream5,
	IRQ69_DMA2_Stream6,
	IRQ70_DMA2_Stream7,
	IRQ71_USART6,
	IRQ72_I2C3_EV,
	IRQ73_I2C3_ER,
	IRQ74_OTG_HS_EP1_OUT,
	IRQ75_OTG_HS_EP1_IN,
	IRQ76_OTG_HS_WKUP,
	IRQ77_OTG_HS,
	IRQ78_DCMI,
	IRQ81_FPU = 81,
	IRQ84_SPI4 = 84,
	IRQ87_SAI1 = 87,
	IRQ91_SAI2 = 91,
	IRQ92_QuadSPI,
	IRQ93_HDMI_CEC,
	IRQ94_SPDIF_RX,
	IRQ95_FMPI2C1_Event,
	IRQ96_FMPI2C1_Error

}NVIC_IRQ_t;




/**
 * @brief  Enable the selected interrupt line in the NVIC.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_EnableIRQ(NVIC_IRQ_t  Copy_u8IRQ );

/**
 * @brief  Disable the selected interrupt line in the NVIC.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_DisnableIRQ(NVIC_IRQ_t Copy_u8IRQ);

/**
 * @brief  Set (pend) the interrupt flag for software triggering.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_SetPendingFlag(NVIC_IRQ_t Copy_u8IRQ);

/**
 * @brief  Clear the pending interrupt flag.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_ClearPendingFlag(NVIC_IRQ_t Copy_u8IRQ);

/**
 * @brief  Set  the priority for the IRQs.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @return  Copy_u8ActvFlgStat  the state of the IRQ Active flag
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_GetActiveFlag(NVIC_IRQ_t Copy_u8IRQ, uint8_t* Copy_u8ActvFlgStat);

/**
 * @brief  Set  the priority for the IRQs.
 * @param  Copy_u8IRQ  IRQ number from NVIC_IRQ_t.
 * @param  Copy_u8Priority   the IRQ priority
 * @return 0 on success, non-zero on invalid input.
 */
uint8_t NVIC_SetPriority(NVIC_IRQ_t Copy_u8IRQ, uint8_t Copy_u8Priority);


#endif /* NVIC_INTERFACE_H_ */
