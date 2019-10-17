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
 * @file    I2Cv1/hal_i2c_lld.c
 * @brief   SIMUL/MEGA I2C subsystem low level driver source.
 *
 * @addtogroup I2C
 * @{
 */

#include "hal.h"

#if HAL_USE_I2C || defined(__DOXYGEN__)

#include "simul_struct.h"

/*==========================================================================*/
/* Driver local definitions.                                                */
/*==========================================================================*/

/*==========================================================================*/
/* Driver exported variables.                                               */
/*==========================================================================*/

/** @brief I2C driver identifier. */
#if SIMUL_I2C_USE_I2C1 || defined(__DOXYGEN__)
I2CDriver I2CD1;
#endif

/*==========================================================================*/
/* Driver local variables and types.                                        */
/*==========================================================================*/

/*==========================================================================*/
/* Driver local functions.                                                  */
/*==========================================================================*/

/*==========================================================================*/
/* Driver interrupt handlers.                                               */
/*==========================================================================*/

#if SIMUL_I2C_USE_I2C1 || defined(__DOXYGEN__)
/**
 * @brief   I2C event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(TWI_vect) {
  OSAL_IRQ_PROLOGUE();

  I2CDriver *i2cp = &I2CD1;

  _i2c_wakeup_isr(i2cp);

  OSAL_IRQ_EPILOGUE();
}
#endif /* SIMUL_I2C_USE_I2C1 */

/*==========================================================================*/
/* Driver exported functions.                                               */
/*==========================================================================*/

/**
 * @brief   Low level I2C driver initialization.
 *
 * @notapi
 */
void i2c_lld_init(void) {

  i2cObjectInit(&I2CD1);
  I2CD1.thread = NULL;
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp  pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_start(I2CDriver *i2cp) {

  uint32_t clock_speed = 100000;

  /* TODO: Test TWI without external pull-ups (use internal). */

  /* Configure prescaler to 1. */


  if (i2cp->config != NULL)
    clock_speed = i2cp->config->clock_speed;

  /* Configure baudrate. */

}

/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp  pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_stop(I2CDriver *i2cp) {

  if (i2cp->state != I2C_STOP) {
    /* Disable TWI subsystem and stop all operations. */

  }
}

/**
 * @brief   Receives data via the I2C bus as master.
 *
 * @param[in]   i2cp      pointer to the @p I2CDriver object
 * @param[in]   addr      slave device address
 * @param[out]  rxbuf     pointer to the receive buffer
 * @param[in]   rxbytes   number of bytes to be received
 * @param[in]   timeout   the number of ticks before the operation timeouts,
 *                        the following special values are allowed:
 *                        - @a TIME_INFINITE no timeout
 *                      
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                     uint8_t *rxbuf, size_t rxbytes,
                                     systime_t timeout) {

  i2cp->errors = I2C_NO_ERROR;
  i2cp->addr = addr;
  i2cp->txbuf = NULL;
  i2cp->txbytes = 0;
  i2cp->txidx = 0;
  i2cp->rxbuf = rxbuf;
  i2cp->rxbytes = rxbytes;
  i2cp->rxidx = 0;

  /* Send START. */
  PeripheralMsg msg;
  msg.peripheralId = 1;
  msg.peripheral_p = i2cp;
  msg.peripheralType = kIICcmd;
  push_to_periph(msg);

  return osalThreadSuspendTimeoutS(&i2cp->thread, TIME_INFINITE);
}

/**
 * @brief   Transmits data via the I2C bus as master.
 *
 * @param[in]   i2cp      pointer to the @p I2CDriver object
 * @param[in]   addr      slave device address
 * @param[in]   txbuf     pointer to the transmit buffer
 * @param[in]   txbytes   number of bytes to be transmitted
 * @param[out]  rxbuf     pointer to the receive buffer
 * @param[in]   rxbytes   number of bytes to be received
 * @param[in]   timeout   the number of ticks before the operation timeouts,
 *                        the following special values are allowed:
 *                        - @a TIME_INFINITE no timeout
 *                      
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                      const uint8_t *txbuf, size_t txbytes,
                                      uint8_t *rxbuf, size_t rxbytes,
                                      systime_t timeout) {

  i2cp->errors = I2C_NO_ERROR;
  i2cp->addr = addr;
  i2cp->txbuf = txbuf;
  i2cp->txbytes = txbytes;
  i2cp->txidx = 0;
  i2cp->rxbuf = rxbuf;
  i2cp->rxbytes = rxbytes;
  i2cp->rxidx = 0;

  PeripheralMsg msg;
  msg.peripheralId = 1;
  msg.peripheral_p = i2cp;
  msg.peripheralType = kIICcmd;
  push_to_periph(msg);

  return osalThreadSuspendTimeoutS(&i2cp->thread, TIME_INFINITE);
}

#endif /* HAL_USE_I2C */

/** @} */

