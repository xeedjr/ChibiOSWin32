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

/**
 * @file    TIMv1/hal_st_lld.h
 * @brief   SIMUL/MEGA ST subsystem low level driver header.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup SIMUL
 * @{
 */

#ifndef HAL_ST_LLD_H
#define HAL_ST_LLD_H

/*==========================================================================*/
/* Driver constants.                                                        */
/*==========================================================================*/

/*==========================================================================*/
/* Driver pre-compile time settings.                                        */
/*==========================================================================*/

/* TODO: for models that have many timers, could add SIMUL_ST_USE_TIMER.      */

/*==========================================================================*/
/* Derived constants and error checks.                                      */
/*==========================================================================*/

/* TODO: error checks for valid timer selected.                             */

/*==========================================================================*/
/* Driver data structures and types.                                        */
/*==========================================================================*/

/*==========================================================================*/
/* Driver macros.                                                           */
/*==========================================================================*/

/*==========================================================================*/
/* External declarations.                                                   */
/*==========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
	systime_t st_lld_get_counter(void);
	void st_lld_start_alarm(systime_t time);
	void st_lld_stop_alarm(void);
	void st_lld_set_alarm(systime_t time);
	systime_t st_lld_get_alarm(void);
	bool st_lld_is_alarm_active(void);
  void st_lld_init(void);
#ifdef __cplusplus
}
#endif

/*==========================================================================*/
/* Driver inline functions.                                                 */
/*==========================================================================*/

#endif /* HAL_ST_LLD_H */

/** @} */
