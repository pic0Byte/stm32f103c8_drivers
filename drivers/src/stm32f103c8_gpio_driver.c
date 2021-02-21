/*
 * stm32f103c8_gpio_driver.c
 *
 *  Created on: 14 Nov 2020
 *      Author: pic0byte
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


static inline void enableInterrupt (GPIOHandle_t *handle) {

    if (handle->config.pinNumber <= 15) {

        RCC_PCLK_AFIO_EN;

        uint8_t port;
        uint8_t position = ((handle->config.pinNumber * 4) % 16);

        if (handle->GPIOx == GPIOA) {
            port = 0;
        } else if (handle->GPIOx == GPIOB) {
            port = 1;
        } else if (handle->GPIOx == GPIOC) {
            port = 2;
        }


        EXTI->RTSR |= (handle->config.risingEdgeInterruptEnable << handle->config.pinNumber);
        EXTI->FTSR |= (handle->config.fallingEdgeInterruptEnable << handle->config.pinNumber);
        EXTI->IMR |= (1u << handle->config.pinNumber);

        switch (handle->config.pinNumber) {

        case 0:
            AFIO->EXTICR[0] &= ~(15u << position);
            AFIO->EXTICR[0] |= port << position;
            NVIC_EnableIRQ(EXTI0_IRQn);
            break;
        case 1:
            AFIO->EXTICR[0] &= ~(15u << position);
            AFIO->EXTICR[0] |= port << position;
            NVIC_EnableIRQ(EXTI1_IRQn);
            break;
        case 2:
            AFIO->EXTICR[0] &= ~(15u << position);
            AFIO->EXTICR[0] |= port << position;
            NVIC_EnableIRQ(EXTI2_IRQn);
            break;
        case 3:
            AFIO->EXTICR[0] &= ~(15u << position);
            AFIO->EXTICR[0] |= port << position;
            NVIC_EnableIRQ(EXTI3_IRQn);
            break;
        case 4:
            AFIO->EXTICR[1] &= ~(15u << position);
            AFIO->EXTICR[1] |= port << position;
            NVIC_EnableIRQ(EXTI4_IRQn);
            break;
        case 5:
            AFIO->EXTICR[1] &= ~(15u << position);
            AFIO->EXTICR[1] |= port << position;
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 6:
            AFIO->EXTICR[1] &= ~(15u << position);
            AFIO->EXTICR[1] |= port << position;
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 7:
            AFIO->EXTICR[1] &= ~(15u << position);
            AFIO->EXTICR[1] |= port << position;
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 8:
            AFIO->EXTICR[2] &= ~(15u << position);
            AFIO->EXTICR[2] |= port << position;
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 9:
            AFIO->EXTICR[2] &= ~(15u << position);
            AFIO->EXTICR[2] |= port << position;
            NVIC_EnableIRQ(EXTI9_5_IRQn);
            break;
        case 10:
            AFIO->EXTICR[2] &= ~(15u << position);
            AFIO->EXTICR[2] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        case 11:
            AFIO->EXTICR[2] &= ~(15u << position);
            AFIO->EXTICR[2] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        case 12:
            AFIO->EXTICR[3] &= ~(15u << position);
            AFIO->EXTICR[3] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        case 13:
            AFIO->EXTICR[3] &= ~(15u << position);
            AFIO->EXTICR[3] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        case 14:
            AFIO->EXTICR[3] &= ~(15u << position);
            AFIO->EXTICR[3] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        case 15:
            AFIO->EXTICR[3] &= ~(15u << position);
            AFIO->EXTICR[3] |= port << position;
            NVIC_EnableIRQ(EXTI15_10_IRQn);
            break;
        default:
            break;
        }
    }

}


static inline gpioState_t readPin(GPIOHandle_t *handle) {

    return ((handle->GPIOx->IDR & (1u << handle->config.pinNumber)) >> handle->config.pinNumber);

}


static inline void setModeInput (GPIOHandle_t *handle) {

    if (handle->config.inputMode <= GPIO_IMOD_puPd) {

        uint8_t reg = ((handle->config.pinNumber * 4) / 32);
        uint8_t position = ((handle->config.pinNumber * 4) % 32);

        if (reg == 1) {
            handle->GPIOx->CRH &= ~(3u << position);
            handle->GPIOx->CRH |= (handle->config.direction << position);
            handle->GPIOx->CRH &= ~(3u << (position + 2));
            handle->GPIOx->CRH |= (handle->config.inputMode << (position + 2));
        } else if (reg == 0) {
            handle->GPIOx->CRL &= ~(3u << position);
            handle->GPIOx->CRL |= (handle->config.direction << position);
            handle->GPIOx->CRL &= ~(3u << (position + 2));
            handle->GPIOx->CRL |= ((handle->config.inputMode) << (position + 2));
        }

        if (handle->config.inputMode == GPIO_IMOD_puPd) {
            handle->GPIOx->ODR |= (handle->config.pullUpDown << handle->config.pinNumber);
        }
    }
}


static inline void setModeOutput(GPIOHandle_t *handle) {

    if (handle->config.outputMode <= GPIO_OMOD_altFunOpenDrain) {

        uint8_t reg = ((handle->config.pinNumber * 4) / 32);
        uint8_t position = ((handle->config.pinNumber * 4) % 32);

        if (reg == 1) {
            handle->GPIOx->CRH &= ~(3u << position);
            handle->GPIOx->CRH |= (handle->config.direction << position);
            handle->GPIOx->CRH &= ~(3u << (position + 2));
            handle->GPIOx->CRH |= (handle->config.outputMode << (position + 2));
        } else if (reg == 0) {
            handle->GPIOx->CRL &= ~(3u << position);
            handle->GPIOx->CRL |= (handle->config.direction << position);
            handle->GPIOx->CRL &= ~(3u << (position + 2));
            handle->GPIOx->CRL |= ((handle->config.outputMode) << (position + 2));
        }
    }

}


static inline void writePinHigh (GPIOHandle_t *handle) {
    handle->GPIOx->BSRR = (1u << handle->config.pinNumber);
}


static inline void writePinLow (GPIOHandle_t *handle) {
    handle->GPIOx->BRR = (1u << handle->config.pinNumber);
}


static inline uint32_t getPinState (GPIOHandle_t *handle) {
    return (handle->GPIOx->ODR & (1u << handle->config.pinNumber));
}


/*******************>  API functions - hardware agnostic  <*******************/


void GPIOinit (GPIOHandle_t *handle) {

    if (handle) {

        enableClock(handle);

        if (handle->config.direction == GPIO_DIR_input) {
            setModeInput(handle);
        } else if (handle->config.direction <= GPIO_DIR_output50Mhz) {
            setModeOutput(handle);
        }

    }

}


gpioState_t GPIOReadPin (GPIOHandle_t *handle) {

    return readPin(handle);

}


void GPIO_writePin (GPIOHandle_t *handle, uint8_t state) {

    if (state == GPIO_ST_high) {
        writePinHigh(handle);
    } else if (state == GPIO_ST_low) {
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


void gpioEnableInterrupt (GPIOHandle_t *handle) {

    enableInterrupt (handle);

}


__attribute__((weak)) void exti0InterruptCallback () {}
__attribute__((weak)) void exti1InterruptCallback () {}
__attribute__((weak)) void exti2InterruptCallback () {}
__attribute__((weak)) void exti3InterruptCallback () {}
__attribute__((weak)) void exti4InterruptCallback () {}
__attribute__((weak)) void exti5InterruptCallback () {}
__attribute__((weak)) void exti6InterruptCallback () {}
__attribute__((weak)) void exti7InterruptCallback () {}
__attribute__((weak)) void exti8InterruptCallback () {}
__attribute__((weak)) void exti9InterruptCallback () {}
__attribute__((weak)) void exti10InterruptCallback () {}
__attribute__((weak)) void exti11InterruptCallback () {}
__attribute__((weak)) void exti12InterruptCallback () {}
__attribute__((weak)) void exti13InterruptCallback () {}
__attribute__((weak)) void exti14InterruptCallback () {}
__attribute__((weak)) void exti15InterruptCallback () {}

/**************************>  Interrupt handlers  <***************************/


void EXTI0_IRQHandler() {

    EXTI->PR = (1u << 0);
    exti0InterruptCallback();

}


void EXTI1_IRQHandler() {

    EXTI->PR = (1u << 1);
    exti1InterruptCallback();

}


void EXTI2_IRQHandler() {

    EXTI->PR = (1u << 2);
    exti2InterruptCallback();

}


void EXTI3_IRQHandler() {

    EXTI->PR = (1u << 3);
    exti3InterruptCallback();

}


void EXTI4_IRQHandler() {

    EXTI->PR = (1u << 4);
    exti4InterruptCallback();

}


void EXTI9_5_IRQHandler() {

    if (EXTI->PR & (1u << 5)) {
        EXTI->PR = (1u << 5);
        exti5InterruptCallback();
    }

    if (EXTI->PR & (1u << 6)) {
        EXTI->PR = (1u << 6);
        exti6InterruptCallback();
    }

    if (EXTI->PR & (1u << 7)) {
        EXTI->PR = (1u << 7);
        exti7InterruptCallback();
    }

    if (EXTI->PR & (1u << 8)) {
        EXTI->PR = (1u << 8);
        exti8InterruptCallback();
    }

    if (EXTI->PR & (1u << 9)) {
        EXTI->PR = (1u << 9);
        exti6InterruptCallback();
    }

}


void EXTI15_10_IRQHandler() {

    if (EXTI->PR & (1u << 10)) {
        EXTI->PR = (1u << 10);
        exti10InterruptCallback();
    }

    if (EXTI->PR & (1u << 11)) {
        EXTI->PR = (1u << 11);
        exti11InterruptCallback();
    }

    if (EXTI->PR & (1u << 12)) {
        EXTI->PR = (1u << 12);
        exti12InterruptCallback();
    }

    if (EXTI->PR & (1u << 13)) {
        EXTI->PR = (1u << 13);
        exti13InterruptCallback();
    }

    if (EXTI->PR & (1u << 14)) {
        EXTI->PR = (1u << 14);
        exti14InterruptCallback();

    if (EXTI->PR & (1u << 15)) {
        EXTI->PR = (1u << 15);
        exti15InterruptCallback();
    }
    }

}


