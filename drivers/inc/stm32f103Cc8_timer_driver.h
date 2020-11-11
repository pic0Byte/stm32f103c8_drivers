/* stm32f103c8_timer_driver.h
 *
 *
 *
 */

#include "stm32f10x.h"


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

   timer_t *pTIMx;
   timerConfig_t config;

} timerHandle_t;


typedef struct {
   timerDirection_t direction;
   timerMode_t mode;
} timerConfig_t;

/******************************************************************************/
/*                                 API                                        */

void timerInit (timerHandle_t *timer);
void timerSetPeriod (timerHandle_t *timer);

voide timerSetIRQFunction (void (*funcP)());



/******************************************************************************/
