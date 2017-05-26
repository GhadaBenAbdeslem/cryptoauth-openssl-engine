/****************************************************************************
 * Copyright (C) 2017 Digi International Inc, All Rights Reserved.
 *
 * This software is provided as instructional material without charge
 * by Digi International for use by its employees and customers
 * subject to the following terms.
 *
 * PERMISSION
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software, to deal with it without restriction,
 * including without limitation the rights to use, copy,  modify, merge,
 * publish, distribute, sublicense, and/or sell copies of it, and to permit
 * persons to whom it is furnished to do so, provided the above copyright
 * notice and this permission notice are included in all derived works
 * and the use of this software is restricted to Digi products.
 *
 * WARRANTY
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.
 *
 * LIABILITY
 * IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES,
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE,
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE
 * OR OTHER DEALINGS WITH THE SOFTWARE.
 *
 ****************************************************************************/

#ifndef HAL_I2CDEV_LINUX_H_
#define HAL_I2CDEV_LINUX_H_

#define MAX_BUSES    1

ATCA_STATUS hal_i2c_discover_buses(int i2c_buses[], int max_buses);
ATCA_STATUS hal_i2c_discover_devices(int busNum, ATCAIfaceCfg cfg[],
				     int *found);
ATCA_STATUS hal_i2c_init(void *hal, ATCAIfaceCfg *cfg);
ATCA_STATUS hal_i2c_post_init(ATCAIface iface);
ATCA_STATUS hal_i2c_send(ATCAIface iface, uint8_t *txdata, int txlength);
ATCA_STATUS hal_i2c_receive(ATCAIface iface, uint8_t *rxdata,
			    uint16_t *rxlength);
ATCA_STATUS hal_i2c_wake(ATCAIface iface);
ATCA_STATUS hal_i2c_idle(ATCAIface iface);
ATCA_STATUS hal_i2c_sleep(ATCAIface iface);
ATCA_STATUS hal_i2c_release(void *hal_data);

#endif /* HAL_I2CDEV_LINUX_H_ */
