#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_



/******************* Masks *******************/
#define GPIO_1BIT_MASK  0b1
#define GPIO_2BIT_MASK  0b11
#define GPIO_4BIT_MASK	0b1111

#define GPIO_PERIPHERAL_NUM      8u

/******************* registers access bits(HM bits/Pin) *******************/
#define MODE_REG_PIN_ACCESS      2u
#define PUPD_REG_PIN_ACCESS      2u
#define OSPEEDR_REG_PIN_ACCESS   2u
#define AFR_REG_PIN_ACCESS       4u

/*used to calculate the AFR (low,high) and bit position */
#define PINS_PER_AFR_REG         8u






#endif /* GPIO_PRV_H_ */
