/*  stm32f103c8_pwm_driver.h
 *
 *  By pic0byte 2021
 *
 *  Provides an interface for reading incremental rotary encoders
 *  using timers 1-4
 *
 *
 *  Usage:
 *
 *  Setup config struct.
 *  TIM1, TIM2, TIM3 & TIM4 are valid timers to use in timer handle,
 *
 *  call encoderInit
 *
 *
 *  read counter value using encoderGetCount function
 *
 */

#ifndef INC_STM32F103C8_ENCODER_DRIVER_H
#define INC_STM32F103C8_ENCODER_DRIVER_H


#include "stm32f103c8_bsp.h"
#include "stm32f103c8_timer_driver.h"
#include "stm32f103c8_gpio_driver.h"

/*****************************************************************************/


typedef enum {ENC_CT_disabled, ENC_CT_pin2Trigger, ENC_CT_pin1Trigger, ENC_CT_bothPinsTrigger} encoderCountTrigger_t;


/*****************************************************************************/


typedef struct {

    uint16_t maxCount;
    uint16_t startCount;
    encoderCountTrigger_t countTrigger;

} encoderConfig_t;


typedef struct {

    encoderConfig_t config;
    timerHandle_t timer;
    GPIOHandle_t pin1;
    GPIOHandle_t pin2;

} encoderHandle_t;


/*****************************************************************************/
/*                                 API                                       */


void encoderInit (encoderHandle_t *handle);

uint16_t encoderGetCount (encoderHandle_t *handle);


/*****************************************************************************/


#endif /* INC_STM32F103C8_ENCODER_DRIVER_H */
