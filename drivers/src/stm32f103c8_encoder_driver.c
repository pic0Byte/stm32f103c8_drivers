


#include "stm32f103c8_encoder_driver.h"



/*****************>  Helper functions - hardware specific  <******************/


static inline void setChannelPins (encoderHandle_t *handle) {


    if (handle->timer.pTIMx == TIM1) {

        handle->pin1.GPIOx = GPIOA;
        handle->pin1.config.pinNumber = 8;
        handle->pin2.GPIOx = GPIOA;
        handle->pin2.config.pinNumber = 9;


    } else if (handle->timer.pTIMx == TIM2) {

        handle->pin1.GPIOx = GPIOA;
        handle->pin1.config.pinNumber = 0;
        handle->pin2.GPIOx = GPIOA;
        handle->pin2.config.pinNumber = 1;


    } else if (handle->timer.pTIMx == TIM3) {

        handle->pin1.GPIOx = GPIOA;
        handle->pin1.config.pinNumber = 6;
        handle->pin2.GPIOx = GPIOA;
        handle->pin2.config.pinNumber = 7;


    } else if (handle->timer.pTIMx == TIM4) {

        handle->pin1.GPIOx = GPIOB;
        handle->pin1.config.pinNumber = 6;
        handle->pin2.GPIOx = GPIOB;
        handle->pin2.config.pinNumber = 7;


    }

}


/*******************>  API functions - hardware agnostic  <*******************/


void encoderInit (encoderHandle_t *handle) {

    handle->timer.config.direction = TIM_DIR_countUp;
    handle->timer.config.mode = TIM_MOD_periodic;
    handle->timer.config.reloadValue = handle->config.maxCount;
    timerInit(&(handle->timer));


    handle->timer.channel1.channelDir = TIM_CHDIR_input;
    handle->timer.channel2.channelDir = TIM_CHDIR_input;
    timerChannelInit(&(handle->timer), 1);
    timerChannelInit(&(handle->timer), 2);

    if (handle->config.countTrigger <= ENC_CT_bothPinsTrigger) {
        handle->timer.slaveConfig.slaveMode = handle->config.countTrigger;
    }
    timerSlaveInit(&(handle->timer));

    setChannelPins(handle);
    handle->pin1.config.inputMode = GPIO_IMOD_puPd;
    handle->pin1.config.pullUpDown = GPIO_PUPD_pullUp;
    handle->pin2.config.inputMode = GPIO_IMOD_puPd;
    handle->pin2.config.pullUpDown = GPIO_PUPD_pullUp;
    GPIOinit(&(handle->pin1));
    GPIOinit(&(handle->pin2));

    timerSetCounterVal(&(handle->timer), handle->config.startCount);

}


uint16_t encoderGetCount (encoderHandle_t *handle) {

    return timerGetCountVal(&(handle->timer));

}


