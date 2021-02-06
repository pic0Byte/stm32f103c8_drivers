/* stm32f103c8_timer_driver.h
 *
 *
 *
 */


/*  @ToDo
 *
 *  API documentation
 *
 *
 *
 */

#ifndef INC_STM32F103C8_TIMER_DRIVER_H
#define INC_STM32F103C8_TIMER_DRIVER_H


#include "stm32f103c8_bsp.h"


typedef TIM_TypeDef timer_t;

/*****************************************************************************/


typedef enum {TIM_DIR_countUp, TIM_DIR_countDown, TIM_DIR_countUpDown} __attribute__((packed, aligned(1))) timerDirection_t;


typedef enum {TIM_MOD_periodic, TIM_MOD_oneShot} __attribute__((packed, aligned(1))) timerMode_t;


typedef enum {TIM_CHDIR_output, TIM_CHDIR_input, TIM_CHDIR_inputAlt, TIM_CHDIR_intTrigger} timerChannelDir_t;


typedef enum {TIM_COM_frozen, TIM_COM_setToActive, TIM_COM_setToInactive, TIM_COM_toggle, TIM_COM_forceActive,
    TIM_COM_forceInactive, TIM_COM_pwmNonInverted, TIM_COM_pwmInverted} timerCompareOutMode_t;


typedef enum {TIM_PREL_preloadDi, TIM_PREL_preloadEn} timerRegisterPreload_t;


/*****************************************************************************/


typedef struct {

    uint16_t capCompValue;
    timerChannelDir_t channelDir;
    timerCompareOutMode_t outputMode;
    timerRegisterPreload_t capCompPreload;


} timerChannelConfig_t;


typedef struct {

   timerDirection_t direction;
   timerMode_t mode;
   uint16_t preScaler;
   uint16_t reloadValue;



} timerConfig_t;


typedef struct {

   timer_t *pTIMx;
   timerConfig_t config;
   timerChannelConfig_t channel1;
   timerChannelConfig_t channel2;
   timerChannelConfig_t channel3;
   timerChannelConfig_t channel4;

} timerHandle_t;




/*****************************************************************************/
/*                                 API                                       */

void timerInit (timerHandle_t *timer);

void timerChannelInit (timerHandle_t *handle, uint8_t channel);

void timerSetPeriod (timerHandle_t *handle, uint32_t uSeconds);

void timerSetPreScaler (timerHandle_t *handle, uint16_t value);

void timerSetCaptureCompare1Value (timerHandle_t *handle, uint16_t val);
void timerSetCaptureCompare2Value (timerHandle_t *handle, uint16_t val);
void timerSetCaptureCompare3Value (timerHandle_t *handle, uint16_t val);
void timerSetCaptureCompare4Value (timerHandle_t *handle, uint16_t val);

void timerIRQInit (timerHandle_t *handle);

//void timerSetIRQFunction (void (*funcP)());

void timer2InterruptCallback();


/*****************************************************************************/


#endif /* INC_STM32F103C8_TIMER_DRIVER_H */
