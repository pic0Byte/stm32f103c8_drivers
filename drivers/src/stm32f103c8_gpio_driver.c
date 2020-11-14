/*
 * stm32f103c8_gpio_driver.c
 *
 *  Created on: 14 Nov 2020
 *      Author: Mitch
 */

#include "stm32f103c8_gpio_driver.h"


/*****************>  Helper functions - hardware specific  <******************/


static inline void enableClock (GPIOHandle_t *handle) {
    if (handle->GPIOx == GPIOA) {
        RCC_PCLK_GPIOA_EN;

    } else if (handle->GPIOx == GPIOB) {
        RCC_PCLK_GPIOB_EN;

    } else if (handle->GPIOx == GPIOC) {
        RCC_PCLK_GPIOC_EN;

    } else if (handle->GPIOx == GPIOD) {
        RCC_PCLK_GPIOD_EN;

    }
}


static inline void setModeIF (GPIOHandle_t *handle) {

    uint8_t reg = (handle->config.pinNumber / 32);
    uint8_t position = ((handle->config.pinNumber * 4) % 32);

    if (reg == 1) {
        handle->GPIOx->CRH &= ~(3u << position);
        handle->GPIOx->CRH &= ~(3u << (position + 2));
        handle->GPIOx->CRH |= (1u << (position + 2));
    } else if (reg == 0) {
        handle->GPIOx->CRL &= ~(3u << position);
        handle->GPIOx->CRL &= ~(3u << (position + 2));
        handle->GPIOx->CRL |= (1u << (position + 2));
    }

}


static inline void setModeOPP (GPIOHandle_t *handle) {

    uint8_t position = ((handle->config.pinNumber * 4) % 32);

    if (handle->config.pinNumber > 7u) {
        handle->GPIOx->CRH &= ~(3u << position);
        handle->GPIOx->CRH &= ~(3u << (position + 2));
        handle->GPIOx->CRH |= (3u << position);
        //handle->GPIOx->CRH |= (2u << (position + 2));

    } else {
        handle->GPIOx->CRL &= ~(3u << position);
        handle->GPIOx->CRL &= ~(3u << (position + 2));
        handle->GPIOx->CRL |= (3u << position);
        //handle->GPIOx->CRL |= (2u << (position + 2));

    }

}


static inline void writePinHigh (GPIOHandle_t *handle) {
    handle->GPIOx->BSRR = (1u << handle->config.pinNumber);
}


static inline void writePinLow (GPIOHandle_t *handle) {
    handle->GPIOx->BRR = (1u << handle->config.pinNumber);
}


static inline uint32_t getPinState (GPIOHandle_t *handle) {
    uint32_t state = (handle->GPIOx->ODR & (1u << handle->config.pinNumber));
    return state;
}


/*******************>  API functions - hardware agnostic  <*******************/


void GPIO_init (GPIOHandle_t *handle) {

    enableClock(handle);

    if (handle->config.mode == inputFloating) {
        setModeIF(handle);

    } else if (handle->config.mode == inputPullUp) {
        //
    } else if (handle->config.mode == inputPullDown) {
        //
    } else if (handle->config.mode == analog) {
        //
    } else if (handle->config.mode == outputOD) {
        //
    } else if (handle->config.mode == outputPP) {
        setModeOPP(handle);

    } else if (handle->config.mode == altFunctionPP) {
        //
    } else if (handle->config.mode == altFunctionOD) {
        //
    }
}


void GPIO_writePin (GPIOHandle_t *handle, uint8_t state) {

    if (state == GPIO_HIGH) {
        writePinHigh(handle);
    } else if (state == GPIO_LOW) {
        writePinLow(handle);
    }

}


void GPIO_togglePin (GPIOHandle_t *handle) {

    if (getPinState(handle)) {
        writePinLow(handle);
    } else {
        writePinHigh(handle);
    }


}
