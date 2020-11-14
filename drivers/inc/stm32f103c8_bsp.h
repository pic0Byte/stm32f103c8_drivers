/*
 * stm32f103c8_bsp.h
 *
 *  Created on: 14 Nov 2020
 *      Author: Mitch
 */

#ifndef INC_STM32F103C8_BSP_H_
#define INC_STM32F103C8_BSP_H_

#include "stm32f10x.h"


/*********************>  Clock enable / disable macros  <*********************/


#define RCC_PCLK_GPIOA_EN            RCC->APB2ENR |= (1u << 2)
#define RCC_PCLK_GPIOB_EN            RCC->APB2ENR |= (1u << 3)
#define RCC_PCLK_GPIOC_EN            RCC->APB2ENR |= (1u << 4)
#define RCC_PCLK_GPIOD_EN            RCC->APB2ENR |= (1u << 5)


#define RCC_PCLK_GPIOA_DI            RCC->APB2ENR &= ~(1u << 2)
#define RCC_PCLK_GPIOB_DI            RCC->APB2ENR &= ~(1u << 3)
#define RCC_PCLK_GPIOC_DI            RCC->APB2ENR &= ~(1u << 4)
#define RCC_PCLK_GPIOD_DI            RCC->APB2ENR &= ~(1u << 5)


#endif /* INC_STM32F103C8_BSP_H_ */
