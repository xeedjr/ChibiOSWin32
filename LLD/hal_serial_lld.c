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
 * @file    USARTv1/hal_serial_lld.c
 * @brief   SIMUL/MEGA SERIAL subsystem low level driver code.
 *
 * @addtogroup SERIAL
 * @{
 */

#include "hal.h"

#if HAL_USE_SERIAL || defined(__DOXYGEN__)

/*==========================================================================*/
/* Driver exported variables.                                               */
/*==========================================================================*/

/**
 * @brief   USART0 serial driver identifier.
 * @note    The name does not follow the convention used in the other ports
 *          (COMn) because a name conflict with the SIMUL headers.
 */
#if SIMUL_SERIAL_USE_USART0 || defined(__DOXYGEN__)
SerialDriver SD1;


#endif /* SIMUL_SERIAL_USE_USART0 */

/**
 * @brief   USART1 serial driver identifier.
 * @note    The name does not follow the convention used in the other ports
 *          (COMn) because a name conflict with the SIMUL headers.
 */
#if SIMUL_SERIAL_USE_USART1 || defined(__DOXYGEN__)
SerialDriver SD2;


#endif /* SIMUL_SERIAL_USE_USART1 */

/*==========================================================================*/
/* Driver local variables and types.                                        */
/*==========================================================================*/

/**
 * @brief   Driver default configuration.
 */
static const SerialConfig default_config = {
  UBRR2x_F(SERIAL_DEFAULT_BITRATE),
  USART_CHAR_SIZE_8
};

/*==========================================================================*/
/* Driver local functions.                                                  */
/*==========================================================================*/

static void set_error(uint8_t sra, SerialDriver *sdp) {
  eventflags_t sts = 0;
  uint8_t dor = 0;
  uint8_t upe = 0;
  uint8_t fe = 0;

#if SIMUL_SERIAL_USE_USART0
  if (&SD1 == sdp) {

  }
#endif

#if SIMUL_SERIAL_USE_USART1
  if (&SD2 == sdp) {

  }
#endif

  if (sra & dor)
    sts |= SD_OVERRUN_ERROR;
  if (sra & upe)
    sts |= SD_PARITY_ERROR;
  if (sra & fe)
    sts |= SD_FRAMING_ERROR;
  osalSysLockFromISR();
  chnAddFlagsI(sdp, sts);
  osalSysUnlockFromISR();
}

#if SIMUL_SERIAL_USE_USART0 || defined(__DOXYGEN__)
static void notify1(io_queue_t *qp) {

  (void)qp;

}

/**
 * @brief   USART0 initialization.
 *
 * @param[in] config    the architecture-dependent serial driver configuration
 */
static void usart0_init(const SerialConfig *config) {


}

/**
 * @brief   USART0 de-initialization.
 */
static void usart0_deinit(void) {


}
#endif

#if SIMUL_SERIAL_USE_USART1 || defined(__DOXYGEN__)
static void notify2(io_queue_t *qp) {

  (void)qp;

}

/**
 * @brief   USART1 initialization.
 *
 * @param[in] config    the architecture-dependent serial driver configuration
 */
static void usart1_init(const SerialConfig *config) {

}

/**
 * @brief   USART1 de-initialization.
 */
static void usart1_deinit(void) {

}
#endif

/*==========================================================================*/
/* Driver interrupt handlers.                                               */
/*==========================================================================*/

#if SIMUL_SERIAL_USE_USART0 || defined(__DOXYGEN__)
/**
 * @brief   USART0 RX interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SIMUL_SD1_RX_VECT) {
  uint8_t sra;

  OSAL_IRQ_PROLOGUE();

  // TODO
  //sra = UCSR0A;
  //if (sra & ((1 << DOR0) | (1 << UPE0) | (1 << FE0)))
  //  set_error(sra, &SD1);
  osalSysLockFromISR();
  //sdIncomingDataI(&SD1, UDR0);
  osalSysUnlockFromISR();

  OSAL_IRQ_EPILOGUE();
}

/**
 * @brief   USART0 TX interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SIMUL_SD1_TX_VECT) {
  msg_t b;

  OSAL_IRQ_PROLOGUE();

  osalSysLockFromISR();
  b = sdRequestDataI(&SD1);
  osalSysUnlockFromISR();
//  if (b < MSG_OK)
//    UCSR0B &= ~(1 << UDRIE0);
//  else
//    UDR0 = b;

  OSAL_IRQ_EPILOGUE();
}
#endif /* SIMUL_SERIAL_USE_USART0 */

#if SIMUL_SERIAL_USE_USART1 || defined(__DOXYGEN__)
/**
 * @brief   USART1 RX interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SIMUL_SD2_RX_VECT) {
  uint8_t sra;

  OSAL_IRQ_PROLOGUE();

  sra = UCSR1A;
  if (sra & ((1 << DOR1) | (1 << UPE1) | (1 << FE1)))
    set_error(sra, &SD2);
  osalSysLockFromISR();
  sdIncomingDataI(&SD2, UDR1);
  osalSysUnlockFromISR();

  OSAL_IRQ_EPILOGUE();
}

/**
 * @brief   USART1 TX interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SIMUL_SD2_TX_VECT) {
  msg_t b;

  OSAL_IRQ_PROLOGUE();

  osalSysLockFromISR();
  b = sdRequestDataI(&SD2);
  osalSysUnlockFromISR();
  if (b < MSG_OK)
    UCSR1B &= ~(1 << UDRIE1);
  else
    UDR1 = b;

  OSAL_IRQ_EPILOGUE();
}
#endif /* SIMUL_SERIAL_USE_USART1 */

/*==========================================================================*/
/* Driver exported functions.                                               */
/*==========================================================================*/

/**
 * @brief   Low level serial driver initialization.
 *
 * @notapi
 */
void sd_lld_init(void) {

#if SIMUL_SERIAL_USE_USART0
  sdObjectInit(&SD1, NULL, notify1);
#endif
#if SIMUL_SERIAL_USE_USART1
  sdObjectInit(&SD2, NULL, notify2);
#endif
}

/**
 * @brief   Low level serial driver configuration and (re)start.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] config    the architecture-dependent serial driver configuration.
 *                      If this parameter is set to @p NULL then a default
 *                      configuration is used.
 *
 * @notapi
 */
void sd_lld_start(SerialDriver *sdp, const SerialConfig *config) {

  if (config == NULL)
    config = &default_config;

#if SIMUL_SERIAL_USE_USART0
  if (&SD1 == sdp) {
    usart0_init(config);
    return;
  }
#endif
#if SIMUL_SERIAL_USE_USART1
  if (&SD2 == sdp) {
    usart1_init(config);
    return;
  }
#endif
}

/**
 * @brief   Low level serial driver stop.
 * @details De-initializes the USART, stops the associated clock, resets the
 *          interrupt vector.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 *
 * @notapi
 */
void sd_lld_stop(SerialDriver *sdp) {

#if SIMUL_SERIAL_USE_USART0
  if (&SD1 == sdp)
    usart0_deinit();
#endif
#if SIMUL_SERIAL_USE_USART1
  if (&SD2 == sdp)
    usart1_deinit();
#endif
}

#endif /* HAL_USE_SERIAL */

/** @} */
