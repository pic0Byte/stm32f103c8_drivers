/* stm32f103c8_timer_driver.h
 *
 *
 *
 */


/*  @ToDo
 *
 *  Slave mode config & init
 *
 *  input capcomp implementation
 *
 *  API documentation
 *
 *
 *
 */

#ifndef INC_STM32F103C8_TIMER_DRIVER_H
#define INC_STM32F103C8_TIMER_DRIVER_H


#include "stm32f103c8_bsp.h"


typedef TIM_TypeDef _timer_t;

/*****************************************************************************/


typedef enum {TIM_DIR_countUp, TIM_DIR_countDown, TIM_DIR_countUpDown} __attribute__((packed, aligned(1))) timerDirection_t;


typedef enum {TIM_MOD_periodic, TIM_MOD_oneShot} __attribute__((packed, aligned(1))) timerMode_t;


typedef enum {TIM_CHDIR_output, TIM_CHDIR_input, TIM_CHDIR_inputAlt, TIM_CHDIR_intTrigger} timerChannelDir_t;


typedef enum {TIM_EXTPR_prescalerDisabled, TIM_EXTPR_divBy2, TIM_EXTPR_divBy4, TIM_EXTPR_divBy8} timerExTrigPrescaler_t;


typedef enum {TIM_COM_frozen, TIM_COM_setToActive, TIM_COM_setToInactive, TIM_COM_toggle, TIM_COM_forceActive,
    TIM_COM_forceInactive, TIM_COM_pwmNonInverted, TIM_COM_pwmInverted} timerOutputCompareMode_t;


typedef enum {TIM_PREL_preloadDi, TIM_PREL_preloadEn} timerRegisterPreload_t;


typedef enum {TIM_SLM_disabled, TIM_SLM_encoderT2, TIM_SLM_encoderT1, TIM_SLM_encoderTBoth, TIM_SLM_resetMode,
    TIM_SLM_gatedMode, TIM_SLM_triggerMode, TIM_SLM_externalMode} timerSlaveMode_t;


//typedef enum {TIM_IM_encoder, TIM_IM_encoder2} timerInputCompareMode_t;





/*****************************************************************************/


typedef struct {

   timerDirection_t direction;
   timerMode_t mode;
   uint16_t preScaler;
   uint16_t reloadValue;





} timerConfig_t;


typedef struct {

    uint16_t capCompValue;
    timerChannelDir_t channelDir;
    timerOutputCompareMode_t outputCompareMode;
    timerRegisterPreload_t capCompPreload;

    //timerInputCompareMode_t inputCompareMode;
    uint8_t channelInputPrescaler;


} timerChannelConfig_t;



typedef struct {

    timerSlaveMode_t slaveMode;
    timerExTrigPrescaler_t exTriggerPrescaler;

} TimerSlaveConfig_t;


typedef struct {

   _timer_t *pTIMx;
   timerConfig_t config;
   timerChannelConfig_t channel1;
   timerChannelConfig_t channel2;
   timerChannelConfig_t channel3;
   timerChannelConfig_t channel4;
   TimerSlaveConfig_t slaveConfig;

} timerHandle_t;




/*****************************************************************************/
/*                                 API                                       */

void timerInit (timerHandle_t *handle);

void timerChannelInit (timerHandle_t *handle, uint8_t channel);

void timerSlaveInit (timerHandle_t *handle);



//void timerSetPeriod (timerHandle_t *handle, uint32_t uSeconds);


void timerSetCounterVal (timerHandle_t *handle, uint16_t value);

uint16_t timerGetCountVal (timerHandle_t *handle);

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
