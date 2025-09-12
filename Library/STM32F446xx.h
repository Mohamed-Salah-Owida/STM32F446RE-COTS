#ifndef STM32F446XX_H
#define STM32F446XX_H


/************************************** Various  memories base addresses *************************/

#define FLASH_BASE_ADDRESS		0x08000000U
#define SRAM_BASE_ADDRESS		0x20000000U
#define ROM_BASE_ADDRESS		0x1FFF0000U


/**************************************core peripheral base addresses *************************/

#define SYSTIC_BASE_ADDRESS     0xE000E010U




/******************* AHB1 Peripheral Base Addresses *******************/
#define GPIOA_BASE_ADDRESS		0x40020000U			
#define GPIOB_BASE_ADDRESS      0x40020400U 
#define GPIOC_BASE_ADDRESS      0x40020800U
#define GPIOD_BASE_ADDRESS      0x40020C00U           
#define GPIOE_BASE_ADDRESS      0x40021000U           
#define GPIOF_BASE_ADDRESS      0x40021400U           
#define GPIOG_BASE_ADDRESS      0x40021800U           
#define GPIOH_BASE_ADDRESS      0x40021C00U   
        
#define RCC_BASE_ADDRESS		0x40023800U

/******************* AHB2 Peripheral Base Addresses *******************/

/******************* AHB3 Peripheral Base Addresses *******************/

/******************* APB1 Peripheral Base Addresses *******************/

/******************* APB2 Peripheral Base Addresses *******************/




/*******************SYSTIC Registers Definition Structures *******************/

typedef struct
{
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;

}Systic_regdef_t;


/******************* RCC Registers Definition Structures *******************/
typedef struct
{
	volatile uint32_t CR;						/*RCC Clk Control Register*/
	volatile uint32_t PLLCFGR;					/*RCC PLL Configuration Register*/
	volatile uint32_t CFGR;						/*RCC Clk Interrupt Register*/
	volatile uint32_t CIR;						/*RCC AHB1 Peripheral Reset Register*/
	volatile uint32_t AHB1RSTR;					/*RCC AHB1 Peripheral Reset Register*/
	volatile uint32_t AHB2RSTR;					/*RCC AHB1 Peripheral Reset Register*/
	volatile uint32_t AHB3RSTR;					/*RCC AHB1 Peripheral Reset Register*/
	uint32_t RESERVED0;                         /*Reserved, 0x1C*/
	volatile uint32_t APB1RSTR;                 /*RCC APB1 perihpheral Reset Register*/
	volatile uint32_t APB2RSTR;                 /*RCC APB2 perihpheral Reset Register*/
	uint32_t RESERVED1[2];                      /*Reserved, 0x28 ~ 0x2C*/
	volatile uint32_t AHB1ENR;                  /*RCC AHB1 Peripheral Clk enable Register*/
	volatile uint32_t AHB2ENR;                  /*RCC AHB2 Peripheral Clk enable Register*/
	volatile uint32_t AHB3ENR;                  /*RCC AHB3 Peripheral Clk enable Register*/
	uint32_t RESERVED2;                         /*Reserved, 0x3C*/
	volatile uint32_t APB1ENR;                  /*RCC APB1 peripheral clk enable Register*/
	volatile uint32_t APB2ENR;                  /*RCC APB1 peripheral clk enable Register*/
	uint32_t RESERVED3[2];                      /*Reserved, 0x48 ~ 0x4C*/
	volatile uint32_t AHB1LPENR;                /*RCC AHB1 Peripherial clk enable in low power mode Register*/
	volatile uint32_t AHB2LPENR;                /*RCC AHB2 Peripherial clk enable in low power mode Register*/
	volatile uint32_t AHB3LPENR;                /*RCC AHB3 Peripherial clk enable in low power mode Register*/
	uint32_t RESERVED4;                         /*Reserved, 0x5C*/
	volatile uint32_t APB1LPENR;                /*RCC APB1 Peripheral clk enable in low power mode Register*/
	volatile uint32_t APB2LPENR;                /*RCC APB2 Peripheral clk enable in low power mode Register*/
	uint32_t RESERVED5[2];                      /*Reserved, 0x68 ~ 0x6C*/
	volatile uint32_t BDCR;                     /*RCC Back Domain Control Register*/
	volatile uint32_t CSR;                      /*RCC Clk Control & Status Register*/
	uint32_t RESERVED6[2];                      /*Reserve, 0x78~0x7C*/
	volatile uint32_t SSCGR;                    /*RCC Spread Spectrum clk generation Register*/
	volatile uint32_t PLLI2SCFGR;               /*RCC PLLI2S configuration Register*/
	volatile uint32_t PLLSAICFGR;               /*RCC PLLSAI configuration Register*/
	volatile uint32_t DCKCFGR;                  /*RCC Dedicated Clock configuration Register*/
	volatile uint32_t CKGATENR;                 /*RCC Clocks Gated Enable Register*/
	volatile uint32_t DCKCFGR2;                 /*RCC Dedicated Clocks Configuration register 2*/
	
	
}RCC_RegDef_t;

/******************* GPIO Registers Definition Structures *******************/
typedef struct
{
	volatile uint32_t MODER;				/*GPIO PORT Mode Register*/
	volatile uint32_t OTYPER;				/*GPIO PORT Output Type Register*/
	volatile uint32_t OSPEEDR;				/*GPIO PORT Output speed Register*/
	volatile uint32_t PUPDR;				/*GPIO PORT Pull-Up/Pull-Down Register*/
	volatile uint32_t IDR;					/*GPIO PORT Input Data Register*/
	volatile uint32_t ODR;					/*GPIO PORT Output Data Register*/
	volatile uint32_t BSRR;					/*GPIO PORT Bit Set/Reset Register*/
	volatile uint32_t LCKR;					/*GPIO PORT Lock Register*/
	volatile uint32_t AFR[2];				/*GPIO PORT Alternate Function High & Low Registers*/

}GPIO_RegDef_t;


/******************* RCC Peripheral Definition *******************/
#define RCC		((RCC_RegDef_t *) RCC_BASE_ADDRESS)


/******************* GPIO Peripheral Definitions *******************/
#define GPIOA		((GPIO_RegDef_t *) GPIOA_BASE_ADDRESS)
#define GPIOB		((GPIO_RegDef_t *) GPIOB_BASE_ADDRESS)
#define GPIOC		((GPIO_RegDef_t *) GPIOC_BASE_ADDRESS)
#define GPIOD		((GPIO_RegDef_t *) GPIOD_BASE_ADDRESS)
#define GPIOE		((GPIO_RegDef_t *) GPIOE_BASE_ADDRESS)
#define GPIOF		((GPIO_RegDef_t *) GPIOF_BASE_ADDRESS)
#define GPIOG		((GPIO_RegDef_t *) GPIOG_BASE_ADDRESS)
#define GPIOH		((GPIO_RegDef_t *) GPIOH_BASE_ADDRESS)



/******************* SYSTIC Peripheral Definition *******************/

#define Systic     ((Systic_regdef_t *) SYSTIC_BASE_ADDRESS )







#endif
