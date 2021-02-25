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


typedef enum {TIM_ICF_noFilter, TIM_ICF_noDiv2samples, TIM_ICF_noDiv4samples, TIM_ICF_noDiv8samples, TIM_ICF_div2_6samples, TIM_ICF_div2_8samples,
    TIM_ICF_div4_6samples, TIM_ICF_div4_8samples, TIM_ICF_div8_6samples, TIM_ICF_div8_8samples, TIM_ICF_div16_5samples, TIM_ICF_div16_6samples,
    TIM_ICF_div16_8samples, TIM_ICF_div32_5samples, TIM_ICF_div32_6samples, TIM_ICF_div32_8samples} timerChannelInputCapFilter_t;


typedef enum {TIM_IETR_risingEdge, TIM_IETR_fsllingEdge} timerChannelInputEdgeTrigger_t;


typedef enum {TIM_COM_frozen, TIM_COM_setToActive, TIM_COM_setToInactive, TIM_COM_toggle, TIM_COM_forceActive,
    TIM_COM_forceInactive, TIM_COM_pwmNonInverted, TIM_COM_pwmInverted} timerChannelOutputCompareMode_t;


typedef enum {TIM_EXTPR_prescalerDisabled, TIM_EXTPR_divBy2, TIM_EXTPR_divBy4, TIM_EXTPR_divBy8} timerExTrigPrescaler_t;


typedef enum {TIM_PREL_preloadDi, TIM_PREL_preloadEn} timerRegisterPreload_t;


typedef enum {TIM_SLM_disabled, TIM_SLM_encoderT2, TIM_SLM_encoderT1, TIM_SLM_encoderTBoth, TIM_SLM_resetMode,
    TIM_SLM_gatedMode, TIM_SLM_triggerMode, TIM_SLM_externalMode} timerSlaveMode_t;








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
    timerChannelOutputCompareMode_t outputCompareMode;
    timerRegisterPreload_t capCompPreload;
    timerChannelInputEdgeTrigger_t inputEdgeTrigger;
    timerExTrigPrescaler_t channelInputPrescaler;
    timerChannelInputCapFilter_t inputFilter;


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

uint16_t timerGetCaptureCompare1Value (timerHandle_t *handle);

uint16_t timerGetCaptureCompare2Value (timerHandle_t *handle);

uint16_t timerGetCaptureCompare3Value (timerHandle_t *handle);

uint16_t timerGetCaptureCompare4Value (timerHandle_t *handle);

void timerSlaveInit (timerHandle_t *handle);

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
