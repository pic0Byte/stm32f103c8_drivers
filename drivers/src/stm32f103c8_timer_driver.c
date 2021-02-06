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


static inline void disableClock (timer_t *timer) {

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


static inline void disableCounter (timer_t *timer) {

    timer->CR1 &= ~(1u << 0);

}


static inline void enableClock (timer_t *timer) {

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


static inline void enableChannelOutput (timerHandle_t *handle, uint8_t channel) {


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


static inline void enableCounter (timer_t *timer) {

    timer->CR1 |= (1u << 0);

}


static inline void setCapCompOutMode (timerHandle_t *handle, uint8_t channel) {

    switch (channel) {

    case 1:
        handle->pTIMx->CCMR1 &= ~(3u << 4);
        handle->pTIMx->CCMR1 |= ((handle->channel1.outputMode) << 4);
        break;

    case 2:
        handle->pTIMx->CCMR1 &= ~(3u << 12);
        handle->pTIMx->CCMR1 |= ((handle->channel2.outputMode) << 12);
        break;

    case 3:
        handle->pTIMx->CCMR2 &= ~(3u << 4);
        handle->pTIMx->CCMR2 |= ((handle->channel3.outputMode) << 4);
        break;

    case 4:
        handle->pTIMx->CCMR2 &= ~(3u << 12);
        handle->pTIMx->CCMR2 |= ((handle->channel4.outputMode) << 12);
        break;

    default:
        break;

    }

}


static inline void setCaptureCompare1Value (timer_t *timer, uint16_t val) {
    timer->CCR1 = val;
}


static inline void setCaptureCompare2Value (timer_t *timer, uint16_t val) {
    timer->CCR2 = val;
}


static inline void setCaptureCompare3Value (timer_t *timer, uint16_t val) {
    timer->CCR3 = val;
}


static inline void setCaptureCompare4Value (timer_t *timer, uint16_t val) {
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


static inline void setCountUp (timer_t *timer) {

	timer->CR1 &= ~(0x3u << 5);
	timer->CR1 &= ~(0x1u << 4);

}


static inline void setCountDown (timer_t *timer) {

    timer->CR1 &= ~(0x3u << 5);
    timer->CR1 |= (0x1u << 4);

}


static inline void setCountUpDown (timer_t *timer) {

    timer->CR1 |= (0x3u << 6);
    timer->CR1 &= ~(0x1u << 4);

}


static inline void setModePeriodic (timer_t *timer) {

    timer->CR1 &= ~(1u << 3);

}


static inline void setModeOneShot (timer_t *timer) {

    timer->CR1 |= (1u << 3);

}


static inline void setPrescaler (timer_t *timer, uint16_t value) {

    timer->PSC = value;

}


static inline void setReloadRegister (timer_t *timer, uint16_t ticks) {

    timer->ARR = ticks;

}



/*******************>  API functions - hardware agnostic  <*******************/



void timerInit (timerHandle_t *handle){


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


void timerChannelInit (timerHandle_t *handle, uint8_t channel) {

    switch (channel) {

    case 1:
        setChannelDir (handle, 1);

        switch (handle->channel1.channelDir) {

        case TIM_CHDIR_output:
            setCapCompOutMode (handle, 1);
            enableChannelOutput(handle, 1);
            break;

        case TIM_CHDIR_input:
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
            enableChannelOutput(handle, 2);
            break;

        case TIM_CHDIR_input:
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
            enableChannelOutput(handle, 3);
            break;

        case TIM_CHDIR_input:
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
            enableChannelOutput(handle, 4);
            break;

        case TIM_CHDIR_input:
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


void timerIRQInit (timerHandle_t *handle) {

    if (handle->pTIMx == TIM2) NVIC_EnableIRQ (TIM2_IRQn);
    else if (handle->pTIMx == TIM3) NVIC_EnableIRQ (TIM3_IRQn);
    else if (handle->pTIMx == TIM4) NVIC_EnableIRQ (TIM4_IRQn);

    handle->pTIMx->DIER |= (1u << 0);

}


__attribute__((weak)) void timer2InterruptCallback () {

}


__attribute__((weak)) void timer3InterruptCallback () {

}



/**************************>  Interrupt handlers  <***************************/



void TIM2_IRQHandler () {

    TIM2->SR &= ~(1u << 0);
    timer2InterruptCallback ();

}


void TIM3_IRQHandler () {

    TIM3->SR &= ~(1u << 0);
    timer3InterruptCallback ();

}


/*****************************************************************************/






