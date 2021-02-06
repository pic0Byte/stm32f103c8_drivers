/*
 * stm32f103c8_gpio_driver.h
 *
 *  Created on: 14 Nov 2020
 *      Author: Mitch
 */

#ifndef INC_STM32F103C8_GPIO_DRIVER_H_
#define INC_STM32F103C8_GPIO_DRIVER_H_


#include "stm32f103c8_bsp.h"


/*************************>  Configuration enum's  <**************************/

typedef enum {inputFloating, inputPullUp, inputPullDown, analog, outputOD, outputPP, altFunctionPP, altFunctionOD} GPIO_mode;


typedef enum {disabled, risingEdge, fallingEdge, risingFallingEdge} GPIO_interruptType;


/*************************>  Structure typedef's  <***************************/


typedef GPIO_TypeDef GPIO_t;


typedef struct {

    GPIO_mode mode;
    uint8_t pinNumber;
    GPIO_interruptType interruptType;

} GPIOConfig_t;


typedef struct {

    GPIO_t *GPIOx;
    GPIOConfig_t config;

} GPIOHandle_t;


/***********************>  API function prototypes  <*************************/

void GPIO_init(GPIOHandle_t *handle);

void GPIO_writePin(GPIOHandle_t *handle, uint8_t state);
void GPIO_togglePin(GPIOHandle_t *handle);

/*****************************>  GPIO macros  <*******************************/

#define GPIO_LOW                0x0u
#define GPIO_HIGH               0x1u

#endif /* INC_STM32F103C8_GPIO_DRIVER_H_ */
