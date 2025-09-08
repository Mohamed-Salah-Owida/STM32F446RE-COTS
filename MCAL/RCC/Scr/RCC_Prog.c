#include <stdint.h>

#include "STM32F446xx.h"
#include "ErrType.h"

#include "RCC_Interface.h"
#include "RCC_Prv.h"


/**
 * @brief Enable or disable a clock source (HSI, HSE, PLL, PLLI2S, PLLSAI)
 *
 * This function controls the ON/OFF state of the different system clock sources.
 * It also waits until the "Ready" flag is set, ensuring the oscillator is stable.
 *
 * @param CLKType   : The clock type (HSI, HSE, PLLP, PLLI2S, PLLSAI, etc.)
 * @param CLKStatus : Desired status (ON / OFF)
 *
 * @return uint8_t  : Error state (OK, TIMEOUT, INVALID_INPUT, WRONG_CLK_SRC_INPUT, etc.)
 */
uint8_t RCC_SetClkStatus(RCC_CLKTypes_t CLKType, RCC_CLKStatus_t CLKStatus)
{
    uint8_t Local_u8ErrorState = OK;
    uint32_t TimeOutCounter = 0;

    switch(CLKType)
    {
    case HSI:   // High-Speed Internal oscillator
        if (CLKStatus == ON) {
            RCC->CR |= (1 << HSI_ON); // Enable HSI
            // Wait until HSI Ready flag is set or timeout occurs
            while ((TimeOutCounter < TIME_OUT) && !(RCC->CR & (1 << HSI_RDY))) {
                TimeOutCounter++;
            }
        }
        else if (CLKStatus == OFF) {
            // Cannot turn off if HSI is the system clock
            if ((RCC->CFGR & CFGR_SW_BITS_MASK) == HSI || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == HSI) {
                Local_u8ErrorState = SWITCHING_OFF_SELECTED_CLK;
            }
            else {
                RCC->CR &= ~(1 << HSI_ON);
            }
        }
        else {
            Local_u8ErrorState = INVALID_INPUT;
        }
        break;

    case HSE:   // High-Speed External oscillator
        if (CLKStatus == ON) {
            RCC->CR |= (1 << HSE_ON); // Enable HSE
            while ((TimeOutCounter < TIME_OUT) && !(RCC->CR & (1 << HSE_RDY))) {
                TimeOutCounter++;
            }
        }
        else if (CLKStatus == OFF) {
            if ((RCC->CFGR & CFGR_SW_BITS_MASK) == HSE || ((RCC->CFGR >> 2) & CFGR_SW_BITS_MASK) == HSE) {
                Local_u8ErrorState = SWITCHING_OFF_SELECTED_CLK;
            }
            else {
                RCC->CR &= ~(1 << HSE_ON);
            }
        }
        else {
            Local_u8ErrorState = INVALID_INPUT;
        }
        break;

    case PLLP:  // Main PLL
        if (CLKStatus == ON) {
            RCC->CR |= (1 << PLL_ON); // Enable PLL
            while ((TimeOutCounter < TIME_OUT) && !(RCC->CR & (1 << PLL_RDY))) {
                TimeOutCounter++;
            }
        }
        else if (CLKStatus == OFF) {
            // Cannot disable PLL if it is used as SYSCLK (via PLLP or PLLR)
            if ((RCC->CFGR & CFGR_SW_BITS_MASK) == PLLP ||
                ((RCC->CFGR & CFGR_SWS_BITS_MASK) >> TWO_BITS_SHIFTING_MASK) == PLLP ||
                (RCC->CFGR & CFGR_SW_BITS_MASK) == PLLR ||
                ((RCC->CFGR & CFGR_SWS_BITS_MASK) >> TWO_BITS_SHIFTING_MASK) == PLLR)
            {
                Local_u8ErrorState = SWITCHING_OFF_SELECTED_CLK;
            }
            else {
                RCC->CR &= ~(1 << PLL_ON); // Disable PLL
            }
        }
        else {
            Local_u8ErrorState = INVALID_INPUT;
        }
        break;

    case PLLI2S:    // PLL for audio (I2S, SAI, SPDIFRX)
        if (CLKStatus == ON) {
            RCC->CR |= (1 << PLLI2S_ON);
            while ((TimeOutCounter < TIME_OUT) && !(RCC->CR & (1 << PLLI2S_RDY))) {
                TimeOutCounter++;
            }
        }
        else if (CLKStatus == OFF) {
            RCC->CR &= ~(1 << PLLI2S_ON);
        }
        else {
            Local_u8ErrorState = INVALID_INPUT;
        }
        break;

    case PLLSAI:    // PLL for SAI, LTDC
        if (CLKStatus == ON) {
            RCC->CR |= (1 << PLLSAI_ON);
            while ((TimeOutCounter < TIME_OUT) && !(RCC->CR & (1 << PLLSAI_RDY))) {
                TimeOutCounter++;
            }
        }
        else if (CLKStatus == OFF) {
            RCC->CR &= ~(1 << PLLSAI_ON);
        }
        else {
            Local_u8ErrorState = INVALID_INPUT;
        }
        break;

    default:
        Local_u8ErrorState = WRONG_CLK_SRC_INPUT;
    }

    // Timeout error handling
    if (TimeOutCounter == TIME_OUT) {
        Local_u8ErrorState = TIMEOUT;
    }

    return Local_u8ErrorState;
}


/**
 * @brief Select system clock source
 *
 * @param CLKType : HSI, HSE, PLLP, or PLLR
 * @return uint8_t : Error state
 */
uint8_t RCC_SetSysClk(RCC_CLKTypes_t CLKType)
{
    uint8_t Local_u8ErrorState = OK;

    if (CLKType != HSI && CLKType != HSE && CLKType != PLLP && CLKType != PLLR) {
        Local_u8ErrorState = WRONG_CLK_SRC_INPUT;
    }
    else {
        RCC->CFGR &= ~(CFGR_SW_BITS_MASK); // Clear system clock bits
        RCC->CFGR |= CLKType;              // Set new system clock
    }

    return Local_u8ErrorState;
}


/**
 * @brief Configure HSE (crystal or bypass)
 */
uint8_t RCC_HSEConfig(HSE_Mode_t HSEMode)
{
    uint8_t Local_u8ErrorState = OK;

    if (HSEMode == HSE_CRYSTAL) {
        RCC->CR &= ~(1U << HSE_BYP); // Normal crystal oscillator
    }
    else if (HSEMode == HSE_BYPASS) {
        RCC->CR |= (1U << HSE_BYP); // External clock bypass
    }
    else {
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}


/**
 * @brief Configure PLL (PLLM, PLLN, PLLP, PLLQ, PLLR)
 *
 * Calculates frequencies, checks constraints, then writes to PLLCFGR.
 */
uint8_t RCC_ConfigPLL(RCC_PLLConfig_t *PLLConfig)
{
    // Compute intermediate frequencies
    uint32_t f_in     = (PLLConfig->PLLSource == 0) ? 16 : PLLConfig->HSE_Value; // MHz
    uint32_t VCO_in   = f_in / PLLConfig->PLLM;
    uint32_t VCO_out  = VCO_in * PLLConfig->PLLN;
    uint32_t PLL_Out  = VCO_out / PLLConfig->PLLP;
    uint32_t PLL_QOut = VCO_out / PLLConfig->PLLQ;

    uint8_t Local_u8ErrorState = OK;

    if (!(RCC->CR & (1 << PLL_ON))) // Configure only if PLL is OFF
    {
        // Set PLL source (HSI or HSE)
        RCC->PLLCFGR &= ~(1 << PLLSRC);
        RCC->PLLCFGR |= (PLLConfig->PLLSource << PLLSRC);

        // Configure PLLM
        if (PLLConfig->PLLM >= 2 && PLLConfig->PLLM <= 63 && VCO_in >= 1 && VCO_in <= 2) {
            RCC->PLLCFGR &= ~(CFGR_PLL_M_BITS_MASK << PLLM0);
            RCC->PLLCFGR |= (PLLConfig->PLLM << PLLM0);
        }
        else {
            Local_u8ErrorState = RCC_ERROR_PLLM;
        }

        // Configure PLLN
        if (PLLConfig->PLLN >= 50 && PLLConfig->PLLN <= 432 && VCO_out >= 100 && VCO_out <= 432) {
            RCC->PLLCFGR &= ~(CFGR_PLL_N_BITS_MASK << PLLN0);
            RCC->PLLCFGR |= (PLLConfig->PLLN << PLLN0);
        }
        else {
            Local_u8ErrorState = RCC_ERROR_PLLN;
        }

        // Configure PLLP
        if (PLLConfig->PLLP >= 2 && PLLConfig->PLLP <= 8 && PLL_Out <= 180) {
            RCC->PLLCFGR &= ~(CFGR_PLL_P_BITS_MASK << PLLP0);
            RCC->PLLCFGR |= (PLLConfig->PLLP << PLLP0);
        }
        else {
            Local_u8ErrorState = RCC_ERROR_PLLP;
        }

        // Configure PLLQ
        if (PLLConfig->PLLQ >= 2 && PLLConfig->PLLQ <= 15 && PLL_QOut <= 48) {
            RCC->PLLCFGR &= ~(CFGR_PLL_Q_BITS_MASK << PLLQ0);
            RCC->PLLCFGR |= (PLLConfig->PLLQ << PLLQ0);
        }
        else {
            Local_u8ErrorState = RCC_ERROR_PLLQ;
        }

        // Configure PLLR
        if (PLLConfig->PLLR >= 2 && PLLConfig->PLLR <= 7) {
            RCC->PLLCFGR &= ~(CFGR_PLL_R_BITS_MASK << PLLR0);
            RCC->PLLCFGR |= (PLLConfig->PLLR << PLLR0);
        }
    }
    else {
        Local_u8ErrorState = CONFIGING_PLL_WHILE_ON;
    }

    return Local_u8ErrorState;
}


/* -------------------- Peripheral Clock Enable/Disable -------------------- */

/**
 * @brief Enable AHB1 peripheral clock
 */
void RCC_AHB1EnableClk(AHB1_Peripheral_t Peripheral)
{
    RCC->AHB1ENR |= (1 << Peripheral);
}

/**
 * @brief Disable AHB1 peripheral clock
 */
void RCC_AHB1DisableClk(AHB1_Peripheral_t Peripheral)
{
    RCC->AHB1ENR &= ~(1 << Peripheral);
}

/**
 * @brief Enable AHB2 peripheral clock
 */
void RCC_AHB2EnableClk(AHB2_Peripheral_t Peripheral)
{
    RCC->AHB2ENR |= (1 << Peripheral);
}

/**
 * @brief Disable AHB2 peripheral clock
 */
void RCC_AHB2DisableClk(AHB2_Peripheral_t Peripheral)
{
    RCC->AHB2ENR &= ~(1 << Peripheral);
}

/**
 * @brief Enable AHB3 peripheral clock
 */
void RCC_AHB3EnableClk(AHB3_Peripheral_t Peripheral)
{
    RCC->AHB3ENR |= (1 << Peripheral);
}

/**
 * @brief Disable AHB3 peripheral clock
 */
void RCC_AHB3DisableClk(AHB3_Peripheral_t Peripheral)
{
    RCC->AHB3ENR &= ~(1 << Peripheral);
}

/**
 * @brief Enable APB1 peripheral clock
 */
void RCC_APB1EnableCLK(APB1_Peripheral_t Peripheral)
{
    RCC->APB1ENR |= (1 << Peripheral);
}

/**
 * @brief Disable APB1 peripheral clock
 */
void RCC_APB1DisableCLK(APB1_Peripheral_t Peripheral)
{
    RCC->APB1ENR &= ~(1 << Peripheral);
}

/**
 * @brief Enable APB2 peripheral clock
 */
void RCC_APB2EnableCLK(APB2_Peripheral_t Peripheral)
{
    RCC->APB2ENR |= (1 << Peripheral);
}

/**
 * @brief Disable APB2 peripheral clock
 */
void RCC_APB2DisableCLK(APB2_Peripheral_t Peripheral)
{
    RCC->APB2ENR &= ~(1 << Peripheral);
}
