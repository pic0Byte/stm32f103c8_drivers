/*
 * stm32f103c8_gpio_driver.h
 *
 *  Created on: 14 Nov 2020
 *      Author: pic0byte
 */

#ifndef INC_STM32F103C8_GPIO_DRIVER_H_
#define INC_STM32F103C8_GPIO_DRIVER_H_


#include "stm32f103c8_bsp.h"


/*************************>  Configuration enum's  <**************************/


typedef enum {GPIO_ST_low, GPIO_ST_high} gpioState_t;


typedef enum {GPIO_DIR_input, GPIO_DIR_output10Mhz, GPIO_DIR_output2Mhz, GPIO_DIR_output50Mhz} gpioDir_t;


typedef enum {GPIO_IMOD_analog, GPIO_IMOD_floating, GPIO_IMOD_puPd} gpioInputMode_t;


typedef enum {GPIO_OMOD_outPushPull, GPIO_OMOD_outOpenDrain, GPIO_OMOD_altFunPushPull, GPIO_OMOD_altFunOpenDrain} gpioOutputMode_t;


typedef enum {GPIO_PUPD_pullDown, GPIO_PUPD_pullUp} gpioPullUpDown_t;


typedef enum {GPIO_EEN_edgeDisabled, GPIO_EEN_edgeEnabled} gpioEdgeEnable_t;


/*************************>  Structure typedef's  <***************************/


typedef GPIO_TypeDef GPIO_t;


typedef struct {

    gpioDir_t direction;
    gpioInputMode_t inputMode;
    gpioPullUpDown_t pullUpDown;
    gpioOutputMode_t outputMode;
    uint8_t pinNumber;
    gpioEdgeEnable_t risingEdgeInterruptEnable;
    gpioEdgeEnable_t fallingEdgeInterruptEnable;

} GPIOConfig_t;


typedef struct {

    GPIO_t *GPIOx;
    GPIOConfig_t config;

} GPIOHandle_t;


/***********************>  API function prototypes  <*************************/

void GPIOinit(GPIOHandle_t *handle);


gpioState_t GPIOReadPin (GPIOHandle_t *handle);
void GPIO_writePin(GPIOHandle_t *handle, uint8_t state);
void GPIO_togglePin(GPIOHandle_t *handle);


void gpioEnableInterrupt (GPIOHandle_t *handle);

void exti0InterruptCallback ();
void exti1InterruptCallback ();
void exti2InterruptCallback ();
void exti3InterruptCallback ();
void exti4InterruptCallback ();
void exti5InterruptCallback ();
void exti6InterruptCallback ();
void exti7InterruptCallback ();
void exti8InterruptCallback ();
void exti9InterruptCallback ();
void exti10InterruptCallback ();
void exti11InterruptCallback ();
void exti12InterruptCallback ();
void exti13InterruptCallback ();
void exti14InterruptCallback ();
void exti15InterruptCallback ();


/*****************************************************************************/





#endif /* INC_STM32F103C8_GPIO_DRIVER_H_ */
