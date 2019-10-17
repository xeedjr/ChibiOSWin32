/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
   This driver is based on the work done by Matteo Serva available at
   http://github.com/matteoserva/ChibiOS-SIMUL
*/

/**
 * @file    TIMv1/hal_gpt_lld.c
 * @brief   SIMUL/MEGA GPT subsystem low level driver source.
 *
 * @addtogroup GPT
 * @{
 */

#include "hal.h"
#include "Rest.h"

#if HAL_USE_GPT || defined(__DOXYGEN__)

/*==========================================================================*/
/* Driver local definitions.                                                */
/*==========================================================================*/



/*==========================================================================*/
/* Driver exported variables.                                               */
/*==========================================================================*/

#if SIMUL_GPT_USE_TIM1 || defined(__DOXYGEN__)
GPTDriver GPTD1;
#endif
#if SIMUL_GPT_USE_TIM2 || defined(__DOXYGEN__)
GPTDriver GPTD2;
#endif
#if SIMUL_GPT_USE_TIM3 || defined(__DOXYGEN__)
GPTDriver GPTD3;
#endif
#if SIMUL_GPT_USE_TIM4 || defined(__DOXYGEN__)
GPTDriver GPTD4;
#endif
#if SIMUL_GPT_USE_TIM5 || defined(__DOXYGEN__)
GPTDriver GPTD5;
#endif

/*==========================================================================*/
/* Driver local variables.                                                  */
/*==========================================================================*/



/*==========================================================================*/
/* Driver local functions.                                                  */
/*==========================================================================*/

/**
 * @brief   TODO: Comment this function.
 *
 * @param[in] freq
 * @param[in] ratio   pointer to the ratio used to calculate the prescaler
 * @param[in] n       ....
 * @return            ....
 */


/**
 * @brief   TODO: Comment this function.
 *
 * @param[in] gptp  pointer to the General Purpose Timer driver.
 */
static void gpt_lld_serve_interrupt(GPTDriver *gptp) {

  gptp->counter++;
  if (gptp->counter == gptp->period) {
    gptp->counter = 0;
    if (gptp->state == GPT_ONESHOT) {
      gptp->state = GPT_READY;             /* Back in GPT_READY state.     */
      gpt_lld_stop_timer(gptp);            /* Timer automatically stopped. */
    }
    gptp->callback(gptp);
  }
}

/**
 * @brief   GPT low level driver dummy callback.
 *
 * @param[in] gptp  pointer to the General Purpose Timer driver.
 */
static void gpt_lld_dummy_callback(GPTDriver *gptp) {
}

/**
 * @brief   Get the timer index.
 *
 * @param[in] gptp  pointer to the General Purpose Timer driver.
 */
static uint8_t getTimerIndex(GPTDriver *gptp) {

  uint8_t index = 0;

#if SIMUL_GPT_USE_TIM1 || defined(__DOXYGEN__)
  if (gptp == &GPTD1) return index;
  else index++;
#endif
#if SIMUL_GPT_USE_TIM2 || defined(__DOXYGEN__)
  if (gptp == &GPTD2) return index;
  else index++;
#endif
#if SIMUL_GPT_USE_TIM3 || defined(__DOXYGEN__)
  if (gptp == &GPTD3) return index;
  else index++;
#endif
#if SIMUL_GPT_USE_TIM4 || defined(__DOXYGEN__)
  if (gptp == &GPTD4) return index;
  else index++;
#endif
#if SIMUL_GPT_USE_TIM5 || defined(__DOXYGEN__)
  if (gptp == &GPTD5) return index;
  else index++;
#endif
  return -1;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if SIMUL_GPT_USE_TIM1 || defined(__DOXYGEN__)
/**
 * @brief   TIM1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(TIMER1_COMPA_vect) {

  OSAL_IRQ_PROLOGUE();
  gpt_lld_serve_interrupt(&GPTD1);
  OSAL_IRQ_EPILOGUE();
}
#endif

#if SIMUL_GPT_USE_TIM2 || defined(__DOXYGEN__)
/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(TIMER2_COMPA_vect) {

  OSAL_IRQ_PROLOGUE();
  gpt_lld_serve_interrupt(&GPTD2);
  OSAL_IRQ_EPILOGUE();
}
#endif

#if SIMUL_GPT_USE_TIM3 || defined(__DOXYGEN__)
/**
 * @brief   TIM3 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(TIMER3_COMPA_vect) {

  OSAL_IRQ_PROLOGUE();
  gpt_lld_serve_interrupt(&GPTD3);
  OSAL_IRQ_EPILOGUE();
}
#endif

#if SIMUL_GPT_USE_TIM4 || defined(__DOXYGEN__)
/**
 * @brief   TIM4 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(TIMER4_COMPA_vect) {

  OSAL_IRQ_PROLOGUE();
  gpt_lld_serve_interrupt(&GPTD4);
  OSAL_IRQ_EPILOGUE();
}
#endif

#if SIMUL_GPT_USE_TIM5 || defined(__DOXYGEN__)
/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(TIMER5_COMPA_vect) {

  OSAL_IRQ_PROLOGUE();
  gpt_lld_serve_interrupt(&GPTD5);
  OSAL_IRQ_EPILOGUE();
}
#endif

/*==========================================================================*/
/* Driver exported functions.                                               */
/*==========================================================================*/

/**
 * @brief   Low level GPT driver initialization.
 *
 * @notapi
 */
void gpt_lld_init(void) {

#if SIMUL_GPT_USE_TIM1 || defined(__DOXYGEN__)
  gptObjectInit(&GPTD1);
#endif
#if SIMUL_GPT_USE_TIM2 || defined(__DOXYGEN__)
  gptObjectInit(&GPTD2);
#endif
#if SIMUL_GPT_USE_TIM3 || defined(__DOXYGEN__)
  gptObjectInit(&GPTD3);
#endif
#if SIMUL_GPT_USE_TIM4 || defined(__DOXYGEN__)
  gptObjectInit(&GPTD4);
#endif
#if SIMUL_GPT_USE_TIM5 || defined(__DOXYGEN__)
  gptObjectInit(&GPTD5);
#endif
}

/**
 * @brief   Configures and activates the GPT peripheral.
 *
 * @param[in] gptp    pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_start(GPTDriver *gptp) {

  //uint8_t psc;

  if (gptp->state == GPT_STOP) {
    /* Clock activation.*/
  }

  startObjectModule((void*)gptp, "gpt");
  /* Configuration.*/


}

/**
 * @brief   Deactivates the GPT peripheral.
 *
 * @param[in] gptp    pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_stop(GPTDriver *gptp) {

  /* nothing to be done */
  if (gptp->state == GPT_READY) {
    /* Clock de-activation.*/
  }
  gpt_lld_stop_timer(gptp);
}

/**
 * @brief   Starts the timer in continuous mode.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 * @param[in] period    period in ticks
 *
 * @notapi
 */
void gpt_lld_start_timer(GPTDriver *gptp, gptcnt_t period) {

  gptp->callback = gptp->config->callback;
  gptp->period = period;
  gptp->counter = 0;

  uint8_t i = getTimerIndex(gptp);

}

/**
 * @brief   Stops the timer.
 *
 * @param[in] gptp    pointer to the @p GPTDriver object
 *
 * @notapi
 */
void gpt_lld_stop_timer(GPTDriver *gptp) {

  uint8_t i = getTimerIndex(gptp);


}

/**
 * @brief   Starts the timer in one shot mode and waits for completion.
 * @details This function specifically polls the timer waiting for completion
 *          in order to not have extra delays caused by interrupt servicing,
 *          this function is only recommended for short delays.
 *
 * @param[in] gptp      pointer to the @p GPTDriver object
 * @param[in] interval  time interval in ticks
 *
 * @notapi
 */
void gpt_lld_polled_delay(GPTDriver *gptp, gptcnt_t interval) {

  gptp->callback = gpt_lld_dummy_callback;
  gpt_lld_start_timer(gptp, interval);
  //FIX
  while (gptp->state != GPT_READY) {}
}

#endif /* HAL_USE_GPT */

/** @} */
