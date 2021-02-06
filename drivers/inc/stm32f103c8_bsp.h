/*
 * stm32f103c8_bsp.h
 *
 *  Created on: 14 Nov 2020
 *      Author: Mitch
 */

#ifndef INC_STM32F103C8_BSP_H
#define INC_STM32F103C8_BSP_H

#include "stm32f10x.h"


#define CLOCK_TICKS_PER_SEC         8000000u
#define CLOCK_TICKS_PER_USEC        (CLOCK_TICKS_PER_SEC / 1000000)


/*********************>  Clock enable / disable macros  <*********************/


/* AFIO */
#define RCC_PCLK_AFIO_EN                (RCC->APB2ENR |= (1u << 0))


/* GPIO */
#define RCC_PCLK_GPIOA_EN               (RCC->APB2ENR |= (1u << 2))
#define RCC_PCLK_GPIOB_EN               (RCC->APB2ENR |= (1u << 3))
#define RCC_PCLK_GPIOC_EN               (RCC->APB2ENR |= (1u << 4))
#define RCC_PCLK_GPIOD_EN               (RCC->APB2ENR |= (1u << 5))


#define RCC_PCLK_GPIOA_DI               (RCC->APB2ENR &= ~(1u << 2))
#define RCC_PCLK_GPIOB_DI               (RCC->APB2ENR &= ~(1u << 3))
#define RCC_PCLK_GPIOC_DI               (RCC->APB2ENR &= ~(1u << 4))
#define RCC_PCLK_GPIOD_DI               (RCC->APB2ENR &= ~(1u << 5))


/* Timers */
#define RCC_PCLK_TIM1_EN                (RCC->APB2ENR |= (1u << 11))
#define RCC_PCLK_TIM2_EN                (RCC->APB1ENR |= (1u << 0))
#define RCC_PCLK_TIM3_EN                (RCC->APB1ENR |= (1u << 1))
#define RCC_PCLK_TIM4_EN                (RCC->APB1ENR |= (1u << 2))
#define RCC_PCLK_TIM5_EN                (RCC->APB1ENR |= (1u << 3))
#define RCC_PCLK_TIM6_EN                (RCC->APB1ENR |= (1u << 4))
#define RCC_PCLK_TIM7_EN                (RCC->APB1ENR |= (1u << 5))
#define RCC_PCLK_TIM8_EN                (RCC->APB2ENR |= (1u << 13))
#define RCC_PCLK_TIM9_EN                (RCC->APB2ENR |= (1u << 19))
#define RCC_PCLK_TIM10_EN               (RCC->APB2ENR |= (1u << 20))
#define RCC_PCLK_TIM11_EN               (RCC->APB2ENR |= (1u << 21))
#define RCC_PCLK_TIM12_EN               (RCC->APB1ENR |= (1u << 6))
#define RCC_PCLK_TIM13_EN               (RCC->APB1ENR |= (1u << 7))
#define RCC_PCLK_TIM14_EN               (RCC->APB1ENR |= (1u << 8))


#define RCC_PCLK_TIM1_DI                (RCC->APB2ENR &= ~(1u << 11))
#define RCC_PCLK_TIM2_DI                (RCC->APB1ENR &= ~(1u << 0))
#define RCC_PCLK_TIM3_DI                (RCC->APB1ENR &= ~(1u << 1))
#define RCC_PCLK_TIM4_DI                (RCC->APB1ENR &= ~(1u << 2))
#define RCC_PCLK_TIM5_DI                (RCC->APB1ENR &= ~(1u << 3))
#define RCC_PCLK_TIM6_DI                (RCC->APB1ENR &= ~(1u << 4))
#define RCC_PCLK_TIM7_DI                (RCC->APB1ENR &= ~(1u << 5))
#define RCC_PCLK_TIM8_DI                (RCC->APB2ENR &= ~(1u << 13))
#define RCC_PCLK_TIM9_DI                (RCC->APB2ENR &= ~(1u << 19))
#define RCC_PCLK_TIM10_DI               (RCC->APB2ENR &= ~(1u << 20))
#define RCC_PCLK_TIM11_DI               (RCC->APB2ENR &= ~(1u << 21))
#define RCC_PCLK_TIM12_DI               (RCC->APB1ENR &= ~(1u << 6))
#define RCC_PCLK_TIM13_DI               (RCC->APB1ENR &= ~(1u << 7))
#define RCC_PCLK_TIM14_DI               (RCC->APB1ENR &= ~(1u << 8))


/* I2C */
#define RCC_PCLK_I2C1_EN                (RCC->APB1ENR |= (1u << 21))
#define RCC_PCLK_I2C2_EN                (RCC->APB1ENR |= (1u << 22))

#define RCC_PCLK_I2C1_DI                (RCC->APB1ENR &= ~(1u << 21))
#define RCC_PCLK_I2C2_DI                (RCC->APB1ENR &= ~(1u << 22))


/******************************************************************************/


#endif /* INC_STM32F103C8_BSP_H */
