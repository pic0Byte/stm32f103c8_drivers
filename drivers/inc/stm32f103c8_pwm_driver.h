/*  stm32f103c8_pwm_driver.h
 *
 *  By pic0byte 2021
 *
 *  Controls up to 4 PWM modules using timer 1 - 4
 *  each module has 4 channels, with independently settable duty cycle
 *  (each module has 1 common frequency)
 *
 *  Usage:
 *
 *  Setup config struct.
 *  TIM1, TIM2, TIM3 & TIM4 are valid timers to use in timer handle,
 *
 *  call pwmInit, then call channelInit for each channel you
 *  want to use.
 *
 *  Set duty for each channel using API setDuty function
 *
 */




/*  @ToDo
 *
 *
 *
 */



#ifndef INC_STM32F103C8_PWM_DRIVER_H
#define INC_STM32F103C8_PWM_DRIVER_H


#include "stm32f103c8_bsp.h"
#include "stm32f103c8_timer_driver.h"
#include "stm32f103c8_gpio_driver.h"


/*****************************************************************************/


typedef enum {PWM_CHP_inverted, PWM_CHP_nonInverted} pwmChannelPolarity_t;


/*****************************************************************************/


typedef struct {

    uint32_t freq;
    pwmChannelPolarity_t ch1Polarity;
    pwmChannelPolarity_t ch2Polarity;
    pwmChannelPolarity_t ch3Polarity;
    pwmChannelPolarity_t ch4Polarity;


} pwmConfig_t;


typedef struct{

    pwmConfig_t config;
    timerHandle_t timer;

    GPIOHandle_t outputPin1;
    GPIOHandle_t outputPin2;
    GPIOHandle_t outputPin3;
    GPIOHandle_t outputPin4;

} pwmHandle_t;


/*****************************************************************************/
/*                                 API                                       */


/*  pwmInit
 *
 *  Arguments: pointer to pwm handle
 *
 *  Notes: requires freq member to be set before calling function
 *
 *
 *
 */
void pwmInit (pwmHandle_t *handle);


/*  pwmChannelInit
 *
 *  Arguments: pointer to pwm handle, channel number
 *
 *  Notes: requires channelPolarity member to be set before calling function
 *
 *
 *
 */
void pwmChannelInit (pwmHandle_t *handle, uint8_t channel);


/*  pwmSetDuty
 *
 * Arguments: pouinter to pwm handle, number between 0 & 100
 *
 *
 */
void pwmSetDuty (pwmHandle_t *handle, uint8_t channel, uint8_t val);


/*****************************************************************************/



#endif /* INC_STM32F103C8_PWM_DRIVER_H */
