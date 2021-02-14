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

typedef enum {GPIO_MOD_inputFloating, GPIO_MOD_inputPullUp, GPIO_MOD_inputPullDown, GPIO_MOD_analog, GPIO_MOD_outputOD, GPIO_MOD_outputPP,
    GPIO_MOD_altFunctionPP, GPIO_MOD_altFunctionOD} GPIO_mode;


typedef enum {GPIO_INT_disabled, GPIO_INT_risingEdge, GPIO_INT_fallingEdge, GPIO_INT_risingFallingEdge} GPIO_interruptType;


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

void GPIOinit(GPIOHandle_t *handle);

void GPIO_writePin(GPIOHandle_t *handle, uint8_t state);
void GPIO_togglePin(GPIOHandle_t *handle);

/*****************************>  GPIO macros  <*******************************/

#define GPIO_LOW                0x0u
#define GPIO_HIGH               0x1u

#endif /* INC_STM32F103C8_GPIO_DRIVER_H_ */
