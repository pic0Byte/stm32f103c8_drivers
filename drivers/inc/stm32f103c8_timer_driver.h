/* stm32f103c8_timer_driver.h
 *
 *
 *
 */


#include "stm32f103c8_bsp.h"


typedef TIM_TypeDef timer_t;

/******************************************************************************/


typedef enum{

   CountUp,
   CountDown,
   CountUpDown

} timerDirection_t;


typedef enum{

   periodic,
   oneShot

} timerMode_t;

/******************************************************************************/

typedef struct {
   timerDirection_t direction;
   timerMode_t mode;
   uint16_t preScaler;
   uint16_t reloadValue;
} timerConfig_t;


typedef struct {

   timer_t *pTIMx;
   timerConfig_t config;

} timerHandle_t;




/******************************************************************************/
/*                                 API                                        */

void timerInit (timerHandle_t *timer);
void timerSetPeriod (timerHandle_t *handle, uint32_t uSeconds);
void timeerSetPreScaler (timerHandle_t *handle, uint16_t value);

//void timerSetIRQFunction (void (*funcP)());

void timerIRQInit (timerHandle_t *handle);

void timer2InterruptCallback();


/******************************************************************************/
