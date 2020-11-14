#include "stm32f10x.h"
#include "stm32f103c8_timer_driver.h"

/***********************~ Helper functions - hardware specific ~**************/


static inline void tim_setCountUp(timer_t *timer){

	timer->CR1 &= ~(0x3u << 6);
	timer->CR1 &= ~(0x1u << 4);

}


static inline void tim_setCountDown(timer_t *timer){

    timer->CR1 &= ~(0x3u << 6);
    timer->CR1 |= (0x1u << 4);

}


static inline void tim_setCountUpDown(timer_t *timer){

    timer->CR1 |= (0x3u << 6);
    timer->CR1 &= ~(0x1u << 4);

}



/***********************~ API functions - hardware agnostic ~*****************/


void timerInit (timerHandle_t *timer_h){

	switch (timer_h->config.direction){

	case CountUp:
	    tim_setCountUp(timer_h->pTIMx);
	    break;
	case CountDown:
	    tim_setCountDown(timer_h->pTIMx);
	    break;
	case CountUpDown:
	    tim_setCountDown(timer_h->pTIMx);
	    break;
	default :
	    break;
	}

	switch (timer_h->config.mode){

	case periodic:

	    break;
	case oneShot:

	    break;
	default:
	    break;
	}
    

}


void timerSetPeriod (timerHandle_t *timer){

}
