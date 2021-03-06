/*  stm32f103c8_timer_driver.c
 *
 *  By pic0Byte 2021
 *
 *
 *
 */


/*  @ToDo
 *
 *  Helpers:
 *  ---enableChannelOutput--- done!
 *  ---setChannelDir--- done!
 *  ---setCapCompOutMode--- done!
 *
 *  combine setmode & setcountup/down/updown?
 *
 *  API:
 *  timerChannelInit input setup (output is done - convert from if() to switch())
 *  finish interrupt handlers
 *
 *  move setCaptureCompare functions into hardware specific API section???
 *
 */



#include "stm32f103c8_timer_driver.h"



/**************************>  Timer related macros  <*************************/






/*****************>  Helper functions - hardware specific  <******************/
/*  @Helpers                                                                 */


static inline void disableClock (_timer_t *timer) {

    if (timer == TIM1) RCC_PCLK_TIM1_DI;
    if (timer == TIM2) RCC_PCLK_TIM2_DI;
    if (timer == TIM3) RCC_PCLK_TIM3_DI;
    if (timer == TIM4) RCC_PCLK_TIM4_DI;
    if (timer == TIM5) RCC_PCLK_TIM5_DI;
    if (timer == TIM6) RCC_PCLK_TIM6_DI;
    if (timer == TIM7) RCC_PCLK_TIM7_DI;
    if (timer == TIM8) RCC_PCLK_TIM8_DI;
    if (timer == TIM9) RCC_PCLK_TIM9_DI;
    if (timer == TIM10) RCC_PCLK_TIM10_DI;
    if (timer == TIM11) RCC_PCLK_TIM11_DI;
    if (timer == TIM12) RCC_PCLK_TIM12_DI;
    if (timer == TIM13) RCC_PCLK_TIM13_DI;
    if (timer == TIM14) RCC_PCLK_TIM14_DI;


}


static inline void disableCounter (_timer_t *timer) {

    timer->CR1 &= ~(1u << 0);

}


static inline void enableClock (_timer_t *timer) {

    if (timer == TIM1) RCC_PCLK_TIM1_EN;
    if (timer == TIM2) RCC_PCLK_TIM2_EN;
    if (timer == TIM3) RCC_PCLK_TIM3_EN;
    if (timer == TIM4) RCC_PCLK_TIM4_EN;
    if (timer == TIM5) RCC_PCLK_TIM5_EN;
    if (timer == TIM6) RCC_PCLK_TIM6_EN;
    if (timer == TIM7) RCC_PCLK_TIM7_EN;
    if (timer == TIM8) RCC_PCLK_TIM8_EN;
    if (timer == TIM9) RCC_PCLK_TIM9_EN;
    if (timer == TIM10) RCC_PCLK_TIM10_EN;
    if (timer == TIM11) RCC_PCLK_TIM11_EN;
    if (timer == TIM12) RCC_PCLK_TIM12_EN;
    if (timer == TIM13) RCC_PCLK_TIM13_EN;
    if (timer == TIM14) RCC_PCLK_TIM14_EN;

}


static inline void enableCapCompOut (timerHandle_t *handle, uint8_t channel) {


    switch (channel) {

    case 1:
        handle->pTIMx->CCER |= (1u << 0);
        break;

    case 2:
        handle->pTIMx->CCER |= (1u << 4);
        break;

    case 3:
        handle->pTIMx->CCER |= (1u << 8);
        break;

    case 4:
        handle->pTIMx->CCER |= (1u << 12);
        break;

    default:
        break;
    }


}


static inline void enableCounter (_timer_t *timer) {

    timer->CR1 |= (1u << 0);

}


static inline uint16_t getCaptureCompare1Value (_timer_t *timer) {
    return timer->CCR1;
}


static inline uint16_t getCaptureCompare2Value (_timer_t *timer) {
    return timer->CCR2;
}


static inline uint16_t getCaptureCompare3Value (_timer_t *timer) {
    return timer->CCR3;
}


static inline uint16_t getCaptureCompare4Value (_timer_t *timer) {
    return timer->CCR4;
}


static inline void setCapCompOutMode (timerHandle_t *handle, uint8_t channel) {

    switch (channel) {

    case 1:
        handle->pTIMx->CCMR1 &= ~(3u << 4);
        handle->pTIMx->CCMR1 |= ((handle->channel1.outputCompareMode) << 4);
        break;

    case 2:
        handle->pTIMx->CCMR1 &= ~(3u << 12);
        handle->pTIMx->CCMR1 |= ((handle->channel2.outputCompareMode) << 12);
        break;

    case 3:
        handle->pTIMx->CCMR2 &= ~(3u << 4);
        handle->pTIMx->CCMR2 |= ((handle->channel3.outputCompareMode) << 4);
        break;

    case 4:
        handle->pTIMx->CCMR2 &= ~(3u << 12);
        handle->pTIMx->CCMR2 |= ((handle->channel4.outputCompareMode) << 12);
        break;

    default:
        break;

    }

}


static inline void setCaptureCompare1Value (_timer_t *timer, uint16_t val) {
    timer->CCR1 = val;
}


static inline void setCaptureCompare2Value (_timer_t *timer, uint16_t val) {
    timer->CCR2 = val;
}


static inline void setCaptureCompare3Value (_timer_t *timer, uint16_t val) {
    timer->CCR3 = val;
}


static inline void setCaptureCompare4Value (_timer_t *timer, uint16_t val) {
    timer->CCR4 = val;
}


static inline void setChannelDir (timerHandle_t *handle, uint8_t channel) {

        switch (channel) {

        case 1:
            handle->pTIMx->CCMR1 &= ~(3u << 0);
            handle->pTIMx->CCMR1 |= ((handle->channel1.channelDir) << 0);
            break;

        case 2:
            handle->pTIMx->CCMR1 &= ~(3u << 8);
            handle->pTIMx->CCMR1 |= ((handle->channel2.channelDir) << 8);
            break;

        case 3:
            handle->pTIMx->CCMR2 &= ~(3u << 0);
            handle->pTIMx->CCMR2 |= ((handle->channel3.channelDir) << 0);
            break;

        case 4:
            handle->pTIMx->CCMR2 &= ~(3u << 8);
            handle->pTIMx->CCMR2 |= ((handle->channel4.channelDir) << 8);
            break;

        default:
            break;
        }

}


static inline void setChannelInputFilter(timerHandle_t *handle, uint8_t channel, timerChannelConfig_t *config) {

    uint8_t position = ((((channel - 1) * 8) + 4) % 16);
    if (channel <= 2) {
        handle->pTIMx->CCMR1 |= (config->inputFilter << position);
    } else if (channel <= 4) {
        handle->pTIMx->CCMR2 |= (config->inputFilter << position);
    }
}


static inline void setChannelInputPrescaler (timerHandle_t *handle, uint8_t channel, timerChannelConfig_t *config) {

    uint8_t position = ((((channel - 1) * 8) + 2) % 16);
    if (channel <= 2) {
        handle->pTIMx->CCMR1 |= (config->channelInputPrescaler << position);
    } else if (channel <= 4) {
        handle->pTIMx->CCMR2 |= (config->channelInputPrescaler << position);
    }
}


static inline void setCountUp (_timer_t *timer) {

	timer->CR1 &= ~(0x3u << 5);
	timer->CR1 &= ~(0x1u << 4);

}


static inline void setCountDown (_timer_t *timer) {

    timer->CR1 &= ~(0x3u << 5);
    timer->CR1 |= (0x1u << 4);

}


static inline void setCountUpDown (_timer_t *timer) {

    timer->CR1 |= (0x3u << 6);
    timer->CR1 &= ~(0x1u << 4);

}


static inline void setExtTriggerPrescaler (timerHandle_t *handle) {

    if (handle->slaveConfig.exTriggerPrescaler <= TIM_EXTPR_divBy8) {

        handle->pTIMx->SMCR &= ~(3u << 12);
        handle->pTIMx->SMCR |= (handle->slaveConfig.exTriggerPrescaler << 12);
    }



}


static inline void setInputEdgeTrigger(timerHandle_t *handle, uint8_t channel, timerChannelConfig_t *config) {
    uint8_t position = (((channel - 1) * 4) + 1);
    handle->pTIMx->CCER |= (config->inputEdgeTrigger << position);
}



static inline void setModePeriodic (_timer_t *timer) {

    timer->CR1 &= ~(1u << 3);

}


static inline void setModeOneShot (_timer_t *timer) {

    timer->CR1 |= (1u << 3);

}


static inline void setPrescaler (_timer_t *timer, uint16_t value) {

    timer->PSC = value;

}


static inline void setReloadRegister (_timer_t *timer, uint16_t ticks) {

    timer->ARR = ticks;

}


static inline void setSlaveMode (_timer_t *timer, timerSlaveMode_t slaveMode) {

    timer->SMCR |= (slaveMode << 0);

}


/*******************>  API functions - hardware agnostic  <*******************/



void timerInit (timerHandle_t *handle){


    if (handle) {

        enableClock (handle->pTIMx);


        switch (handle->config.direction){

        case TIM_DIR_countUp:
            setCountUp(handle->pTIMx);
            break;
        case TIM_DIR_countDown:
            setCountDown(handle->pTIMx);
            break;
        case TIM_DIR_countUpDown:
            setCountUpDown(handle->pTIMx);
            break;
        default :
            break;
        }


        switch (handle->config.mode){

        case TIM_MOD_periodic:
            setModePeriodic(handle->pTIMx);
            break;
        case TIM_MOD_oneShot:
            setModeOneShot(handle->pTIMx);
            break;
        default:
            break;
        }



        setPrescaler(handle->pTIMx, handle->config.preScaler);

        setReloadRegister(handle->pTIMx, handle->config.reloadValue);


        enableCounter (handle->pTIMx);
    }
    

}


void timerChannelInit (timerHandle_t *handle, uint8_t channel) {

    if (handle) {

        switch (channel) {

        case 1:
            setChannelDir (handle, 1);

            switch (handle->channel1.channelDir) {

            case TIM_CHDIR_output:
                setCapCompOutMode (handle, 1);
                enableCapCompOut(handle, 1);
                break;

            case TIM_CHDIR_input:
                setInputEdgeTrigger(handle, 1, &(handle->channel1));
                setChannelInputPrescaler (handle, 1, &(handle->channel1));
                setChannelInputFilter(handle, 1, &(handle->channel1));
                enableCapCompOut(handle, 1);
                break;

            case TIM_CHDIR_inputAlt:
                break;

            case TIM_CHDIR_intTrigger:
                break;

            default:
                break;

            }

            break;

            case 2:
                setChannelDir (handle, 2);

                switch (handle->channel2.channelDir) {

                case TIM_CHDIR_output:
                    setCapCompOutMode (handle, 2);
                    enableCapCompOut(handle, 2);
                    break;

                case TIM_CHDIR_input:
                    setInputEdgeTrigger(handle, 2, &(handle->channel2));
                    setChannelInputFilter(handle, 2, &(handle->channel2));
                    enableCapCompOut(handle, 2);
                    break;

                case TIM_CHDIR_inputAlt:
                    break;

                case TIM_CHDIR_intTrigger:
                    break;

                default:
                    break;

                }

                case 3:
                    setChannelDir (handle, 3);

                    switch (handle->channel3.channelDir) {

                    case TIM_CHDIR_output:
                        setCapCompOutMode (handle, 3);
                        enableCapCompOut(handle, 3);
                        break;

                    case TIM_CHDIR_input:
                        setInputEdgeTrigger(handle, 3, &(handle->channel3));
                        enableCapCompOut(handle, 3);
                        break;

                    case TIM_CHDIR_inputAlt:
                        break;

                    case TIM_CHDIR_intTrigger:
                        break;

                    default:
                        break;

                    }

                    case 4:
                        setChannelDir (handle, 4);

                        switch (handle->channel4.channelDir) {

                        case TIM_CHDIR_output:
                            setCapCompOutMode (handle, 4);
                            enableCapCompOut(handle, 4);
                            break;

                        case TIM_CHDIR_input:
                            setInputEdgeTrigger(handle, 4, &(handle->channel4));
                            enableCapCompOut(handle, 4);
                            break;

                        case TIM_CHDIR_inputAlt:
                            break;

                        case TIM_CHDIR_intTrigger:
                            break;

                        default:
                            break;

                        }

                        default:
                            break;

        }
    }

}


uint16_t timerGetCaptureCompare1Value (timerHandle_t *handle) {
    return getCaptureCompare1Value(handle->pTIMx);
}


uint16_t timerGetCaptureCompare2Value (timerHandle_t *handle) {
    return getCaptureCompare2Value(handle->pTIMx);
}


uint16_t timerGetCaptureCompare3Value (timerHandle_t *handle) {
    return getCaptureCompare3Value(handle->pTIMx);
}


uint16_t timerGetCaptureCompare4Value (timerHandle_t *handle) {
    return getCaptureCompare4Value(handle->pTIMx);
}


void timerSlaveInit (timerHandle_t *handle) {


    if (handle) {

        setSlaveMode (handle->pTIMx, handle->slaveConfig.slaveMode);
        setExtTriggerPrescaler (handle);

    }

}


void timerSetPeriod (timerHandle_t *handle, uint32_t uSeconds) {
    uint32_t ticks = (CLOCK_TICKS_PER_USEC * uSeconds);

    if (ticks <= 65535) {
        setReloadRegister (handle->pTIMx, ticks);
    }
}


void timerSetCaptureCompare1Value (timerHandle_t *handle, uint16_t val) {

    setCaptureCompare1Value(handle->pTIMx, val);

}


void timerSetCaptureCompare2Value (timerHandle_t *handle, uint16_t val) {

    setCaptureCompare2Value(handle->pTIMx, val);

}


void timerSetCaptureCompare3Value (timerHandle_t *handle, uint16_t val) {

    setCaptureCompare3Value(handle->pTIMx, val);

}


void timerSetCaptureCompare4Value (timerHandle_t *handle, uint16_t val) {

    setCaptureCompare4Value(handle->pTIMx, val);

}


uint16_t timerGetCountVal (timerHandle_t *handle){
    return handle->pTIMx->CNT;
}


void timerSetCounterVal (timerHandle_t *handle, uint16_t value) {

    handle->pTIMx->CNT = value;
}


void timerIRQInit (timerHandle_t *handle) {

    if (handle->pTIMx == TIM2) NVIC_EnableIRQ (TIM2_IRQn);
    else if (handle->pTIMx == TIM3) NVIC_EnableIRQ (TIM3_IRQn);
    else if (handle->pTIMx == TIM4) NVIC_EnableIRQ (TIM4_IRQn);

    handle->pTIMx->DIER |= (1u << 0);

}


__attribute__((weak)) void timer2InterruptCallback () {}
__attribute__((weak)) void timer3InterruptCallback () {}
__attribute__((weak)) void timer4InterruptCallback () {}


/**************************>  Interrupt handlers  <***************************/



void TIM2_IRQHandler () {

    TIM2->SR &= ~(1u << 0);
    timer2InterruptCallback ();

}


void TIM3_IRQHandler () {

    TIM3->SR &= ~(1u << 0);
    timer3InterruptCallback ();

}


void TIM4_IRQHandler () {

    TIM4->SR &= ~(1u << 0);
    timer4InterruptCallback ();

}


/*****************************************************************************/






