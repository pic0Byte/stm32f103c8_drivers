#include "stm32f103c8_timer_driver.h"



/**************************>  Timer related macros  <*************************/






/*****************>  Helper functions - hardware specific  <******************/

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


static inline void enableCounter (timer_t *timer) {

    timer->CR1 |= (1u << 0);

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

	case CountUp:
	    setCountUp(handle->pTIMx);
	    break;
	case CountDown:
	    setCountDown(handle->pTIMx);
	    break;
	case CountUpDown:
	    setCountUpDown(handle->pTIMx);
	    break;
	default :
	    break;
	}


	switch (handle->config.mode){

	case periodic:
	    setModePeriodic(handle->pTIMx);
	    break;
	case oneShot:
	    setModeOneShot(handle->pTIMx);
	    break;
	default:
	    break;
	}


	setPrescaler(handle->pTIMx, handle->config.preScaler);

	setReloadRegister(handle->pTIMx, handle->config.reloadValue);

	enableCounter (handle->pTIMx);
    

}


void timerSetPeriod (timerHandle_t *handle, uint32_t uSeconds){
    uint32_t ticks = (CLOCK_TICKS_PER_USEC * uSeconds);

    if (ticks <= 65535) {
        setReloadRegister (handle->pTIMx, ticks);
    }
}


void timerIRQInit (timerHandle_t *handle) {

    if (handle->pTIMx == TIM2) NVIC_EnableIRQ (TIM2_IRQn);
    else if (handle->pTIMx == TIM3) NVIC_EnableIRQ (TIM3_IRQn);
    else if (handle->pTIMx == TIM4) NVIC_EnableIRQ (TIM4_IRQn);

    handle->pTIMx->DIER |= (1u << 0);

}


__attribute__((weak)) void timer2InterruptCallback () {

}


/**************************>  Interrupt handlers  <***************************/


void TIM2_IRQHandler () {

    TIM2->SR &= ~(1u << 0);
    timer2InterruptCallback ();

}


void TIM3_IRQHandler () {

    TIM3->SR &= ~(1u << 0);
    //timer3InterruptCallback ();

}








