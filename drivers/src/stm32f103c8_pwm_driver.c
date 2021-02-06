#include "stm32f103c8_pwm_driver.h"


/*****************>  Helper functions - hardware specific  <******************/


static inline void setChannelPins (pwmHandle_t *handle) {


    if (handle->timer.pTIMx == TIM1) {

        handle->outputPin1.GPIOx = GPIOA;
        handle->outputPin1.config.pinNumber = 8;
        handle->outputPin2.GPIOx = GPIOA;
        handle->outputPin2.config.pinNumber = 9;
        handle->outputPin3.GPIOx = GPIOA;
        handle->outputPin3.config.pinNumber = 10;
        handle->outputPin4.GPIOx = GPIOA;
        handle->outputPin4.config.pinNumber = 11;

    } else if (handle->timer.pTIMx == TIM2) {

        handle->outputPin1.GPIOx = GPIOA;
        handle->outputPin1.config.pinNumber = 0;
        handle->outputPin2.GPIOx = GPIOA;
        handle->outputPin2.config.pinNumber = 1;
        handle->outputPin3.GPIOx = GPIOA;
        handle->outputPin3.config.pinNumber = 2;
        handle->outputPin4.GPIOx = GPIOA;
        handle->outputPin4.config.pinNumber = 3;

    } else if (handle->timer.pTIMx == TIM3) {

        handle->outputPin1.GPIOx = GPIOA;
        handle->outputPin1.config.pinNumber = 6;
        handle->outputPin2.GPIOx = GPIOA;
        handle->outputPin2.config.pinNumber = 7;
        handle->outputPin3.GPIOx = GPIOB;
        handle->outputPin3.config.pinNumber = 0;
        handle->outputPin4.GPIOx = GPIOB;
        handle->outputPin4.config.pinNumber = 1;

    } else if (handle->timer.pTIMx == TIM4) {

        handle->outputPin1.GPIOx = GPIOB;
        handle->outputPin1.config.pinNumber = 6;
        handle->outputPin2.GPIOx = GPIOB;
        handle->outputPin2.config.pinNumber = 7;
        handle->outputPin3.GPIOx = GPIOB;
        handle->outputPin3.config.pinNumber = 8;
        handle->outputPin4.GPIOx = GPIOB;
        handle->outputPin4.config.pinNumber = 9;

    }

}


static inline void setFrequency (pwmHandle_t *handle) {

    double reload = (((1 / (double)handle->config.freq) / (1 / (double)CLOCK_TICKS_PER_SEC)) / 2);

    handle->timer.pTIMx->ARR = (uint16_t)reload;
    handle->timer.pTIMx->PSC = 0;

}


static inline uint16_t getARR (timerHandle_t *handle) {
    return handle->pTIMx->ARR;
}

/*******************>  API functions - hardware agnostic  <*******************/


void pwmInit (pwmHandle_t *handle) {


    setChannelPins(handle);

    handle->timer.config.direction = TIM_DIR_countUpDown;
    handle->timer.config.mode = TIM_MOD_periodic;

    timerInit(&(handle->timer));
    setFrequency(handle);



}


void pwmChannelInit (pwmHandle_t *handle, uint8_t channel) {


    switch (channel) {

    case 1:

        handle->outputPin1.config.mode = altFunctionPP;

        if (handle->config.ch1Polarity == PWM_CHP_inverted) {

            handle->timer.channel1.outputMode = TIM_COM_pwmInverted;

        } else {

            handle->timer.channel1.outputMode = TIM_COM_pwmNonInverted;

        }

        handle->timer.channel1.capCompPreload = TIM_PREL_preloadEn;

        GPIO_init(&(handle->outputPin1));
        timerChannelInit(&(handle->timer), 1);
        break;

    case 2:

        handle->outputPin2.config.mode = altFunctionPP;

        if (handle->config.ch2Polarity == PWM_CHP_inverted) {

            handle->timer.channel2.outputMode = TIM_COM_pwmInverted;

        } else {

            handle->timer.channel2.outputMode = TIM_COM_pwmNonInverted;

        }

        handle->timer.channel2.capCompPreload = TIM_PREL_preloadEn;

        GPIO_init(&(handle->outputPin2));
        timerChannelInit(&(handle->timer), 2);
        break;

    case 3:

        handle->outputPin3.config.mode = altFunctionPP;

        if (handle->config.ch3Polarity == PWM_CHP_inverted) {

            handle->timer.channel3.outputMode = TIM_COM_pwmInverted;

        } else {

            handle->timer.channel3.outputMode = TIM_COM_pwmNonInverted;

        }

        handle->timer.channel3.capCompPreload = TIM_PREL_preloadEn;

        GPIO_init(&(handle->outputPin3));
        timerChannelInit(&(handle->timer), 3);
        break;

    case 4:

        handle->outputPin4.config.mode = altFunctionPP;

        if (handle->config.ch4Polarity == PWM_CHP_inverted) {

            handle->timer.channel4.outputMode = TIM_COM_pwmInverted;

        } else {

            handle->timer.channel4.outputMode = TIM_COM_pwmNonInverted;

        }

        handle->timer.channel4.capCompPreload = TIM_PREL_preloadEn;

        GPIO_init(&(handle->outputPin4));
        timerChannelInit(&(handle->timer), 4);
        break;

    default:
        break;
    }







}


void pwmSetDuty (pwmHandle_t *handle, uint8_t channel, uint8_t val) {

    if (val > 100) {
        val = 100;
    }

    double div = ((double)val / 100);
    double capComp = ((double)(getARR(&(handle->timer))) * div);

    switch (channel) {
    case 1:
        timerSetCaptureCompare1Value((&(handle->timer)), (uint16_t)capComp);
        break;

    case 2:
        timerSetCaptureCompare2Value((&(handle->timer)), (uint16_t)capComp);
        break;

    case 3:
        timerSetCaptureCompare3Value((&(handle->timer)), (uint16_t)capComp);
        break;

    case 4:
        timerSetCaptureCompare4Value((&(handle->timer)), (uint16_t)capComp);
        break;

    default:
        break;

    }



}


/**************************>  Interrupt handlers  <***************************/






