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

/***** #include-s *****/
#include "atca_command.h"
#include "atca_hal.h"
#include "atca_iface.h"
#include "atca_status.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/types.h>

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

/***** #define-s *****/
#define FD_CLOSED_FILE     -1
#define LEN_FILENAME       11

/*
 * Word Address Values (see 6.2.1)
 */
#define WORD_ADDRESS_RESET     0x00
#define WORD_ADDRESS_SLEEP     0x01
#define WORD_ADDRESS_IDLE      0x02
#define WORD_ADDRESS_COMMAND   0x03

#define I2C_DEBUG 0

#define debug_cond(cond, fmt, args...)                  \
        do {                                            \
                if (cond)                               \
                        printf(fmt, ##args);            \
        } while (0)

#define debug(fmt, args...)                     \
        debug_cond(I2C_DEBUG, fmt, ##args)

/***** Global variables *****/
static int i2c_bus_ref_ct = 0;   /*!< Total in-use count across buses. */

/*!
 * @brief File descriptor for the I2C bus (/dev/i2c-X).
 */
static int fd_i2c;

/***** Functions *****/

/*!
 * @brief Closes the open I2C device node.
 */
static int i2c_close(void)
{
	int ret;

	ret = close(fd_i2c);
	fd_i2c = FD_CLOSED_FILE;

	return ret;
}

/*!
 * @brief Opens the I2C device node.
 *
 * @param i2c_bus Number of bus to which the slave is attached (/dev/i2c-X).
 * @param slave_addr Address of the I2C slave.
 *
 * @return Error code (0 in case of success).
 */
static ATCA_STATUS i2c_open(ATCAIfaceCfg *cfg)
{
	const uint8_t i2c_bus = cfg->atcai2c.bus;
	const uint8_t slave_addr = cfg->atcai2c.slave_address >> 1;
	char filename[LEN_FILENAME];
	int ret = ATCA_SUCCESS;

	sprintf(filename, "/dev/i2c-%d", i2c_bus);
	fd_i2c = open(filename, O_RDWR);
	if (fd_i2c < 0) {
		ret = ATCA_NO_DEVICES;
		goto out;
	}

	/* Config I2C address */
	if (ioctl(fd_i2c, I2C_SLAVE_FORCE, slave_addr) < 0) {
		i2c_close();
		ret = ATCA_NO_DEVICES;
		goto out;
	}

out:
	return ret;
}

/**
 * @brief Wrapper to send short commands to the CryptoAuth chip over i2c.
 *
 * @param iface Interface of the CryptoAuth chip.
 * @param command Code of the command to be sent.
 *
 * @return Completion status.
 */
ATCA_STATUS i2c_send_command(ATCAIface iface, uint8_t command)
{
	ATCAIfaceCfg *cfg = atgetifacecfg(iface);
	ATCA_STATUS ret = ATCA_SUCCESS;
	struct i2c_msg msg = {
                .addr  = cfg->atcai2c.slave_address >> 1,
                .flags = 0,
                .len   = 1,
                .buf   = &command
        };
        struct i2c_rdwr_ioctl_data msg_ctrl = {
                .msgs  = &msg,
                .nmsgs = 1
        };

	if (ioctl(fd_i2c, I2C_RDWR, &msg_ctrl) < 0) {
		debug("Error writing to I2C -- %s (%d)\n", strerror(errno),
		       errno);
		ret = ATCA_COMM_FAIL;
	}

	return ret;
}



/**
 * @brief Discover i2c buses available for this hardware.
 *
 * @param i2c_buses An array of logical bus numbers.
 * @param max_buses Maximum number of buses the app attempts to discover.
 */
ATCA_STATUS hal_i2c_discover_buses(int i2c_buses[], int max_buses)
{
	return ATCA_UNIMPLEMENTED;
}

/**
 * @brief Discover any CryptoAuth devices on a given logical bus number.
 * @param[in] busNum Logical bus number on which to look for CryptoAuth devices.
 * @param[out] cfg[] Array of interface configs to be filled in this function.
 * @param[out] *found Number of devices found on this bus.
 */
ATCA_STATUS hal_i2c_discover_devices(int busNum, ATCAIfaceCfg cfg[], int *found)
{
	/* This could be done by accessing the sysfs */
	return ATCA_UNIMPLEMENTED;
}

/**
 * @brief hal_i2c_init manages requests to initialize a physical interface.
 * It manages use counts so when an interface has released the physical layer,
 * it will disable the interface for some other use.
 * You can have multiple ATCAIFace instances using the same bus, and you can
 * have multiple ATCAIFace instances on multiple i2c buses, so hal_i2c_init
 * manages these things and ATCAIFace is abstracted from the physical details.
 * This function initializes an I2C interface using given configuration.
 * @param[in] hal - opaque ptr to HAL data
 * @param[in] cfg - interface configuration
 */
ATCA_STATUS hal_i2c_init(void *hal, ATCAIfaceCfg *cfg)
{
	int ret = ATCA_SUCCESS;

	i2c_bus_ref_ct++;

	if (i2c_open(cfg)) {
		debug("Error opening i2c\n");
		ret = ATCA_COMM_FAIL;
	}
}

/**
 * @brief HAL implementation of I2C post init
 * @param[in] iface  instance
 * @return ATCA_STATUS
 */
ATCA_STATUS hal_i2c_post_init(ATCAIface iface)
{
	return ATCA_SUCCESS; /* nothing to do */
}

/**
 * @brief HAL implementation of I2C send.
 *
 * @param[in] iface Instance of the interface.
 * @param[in] txdata Buffer with the bytes to send.
 * @param[in] txlength Number of bytes to send.
 *
 * @return ATCA_STATUS
 *
 * @note The upper layers already implement retry mechanisms.
 */
ATCA_STATUS hal_i2c_send(ATCAIface iface, uint8_t *txdata, int txlength)
{
	ATCA_STATUS ret = ATCA_SUCCESS;
	ATCAIfaceCfg *cfg = atgetifacecfg(iface);
	struct i2c_msg msg = {
                .addr  =  cfg->atcai2c.slave_address >> 1,
                .flags = 0,
                .buf   = txdata
        };
        struct i2c_rdwr_ioctl_data msg_ctrl = {
                .msgs  = &msg,
                .nmsgs = 1
        };

	/*
	 * Write the Word Address explicitly.
	 * The buffer received from upper layers of the library already has a
	 * placeholder for it in the first position, but this byte must be
	 * added in the HAL, and the byte count incremented.
	 */
	txdata[0] = WORD_ADDRESS_COMMAND;
	msg.len = txlength + 1;

	if (ioctl(fd_i2c, I2C_RDWR, &msg_ctrl) < 0) {
                debug("CryptoAuth write error - %s (%d)\n", strerror(errno),
		       errno);
                ret = ATCA_COMM_FAIL;
	}

        return ret;
}

/**
 * @brief HAL implementation of I2C receive function for ASF I2C
 *
 * @param[in] iface Instance of the CryptoAuth chip.
 * @param[in] rxdata Pointer to a buffer for received data.
 * @param[in] rxlength Pointer to expected number of receive bytes.
 *
 * @return ATCA_STATUS
 */
ATCA_STATUS hal_i2c_receive(ATCAIface iface, uint8_t *rxdata,
			    uint16_t *rxlength)
{
	ATCA_STATUS ret = ATCA_COMM_FAIL;
	ATCAIfaceCfg *cfg = atgetifacecfg(iface);
	int retries = cfg->rx_retries;
	struct i2c_msg msg = {
		.addr  = cfg->atcai2c.slave_address >> 1,
		.flags = I2C_M_RD,
		.len   = *rxlength,
		.buf   = rxdata
	};
	struct i2c_rdwr_ioctl_data msg_ctrl = {
		.msgs  = &msg,
		.nmsgs = 1
	};

	do {
		if (ioctl(fd_i2c, I2C_RDWR, &msg_ctrl) < 0) {
			debug("hal_i2c_receive ioctl failed: %s \n", 
				strerror(errno));
			usleep(1);
		} else {
			ret = ATCA_SUCCESS;
			break;
		}
	} while (--retries > 0);

	return ret;
}

/**
 * @brief Send wakeup pulse in case the CryptoAuth chip is asleep.
 *
 * @param cfg Configuration of the CryptoAuth chip interface.
 *
 * @return Result of the operation (0 = success, other value = error).
 */
static ATCA_STATUS send_wakeup_pulse(ATCAIfaceCfg *cfg)
{
	/*
	 * From 6.1.1 "I/O Conditions. Device is Asleep":
	 *
	 * "The Wake condition requires that either the system processor
	 * manually drives the SDA pin low for t_WLO, or a data byte of
	 * 0x00 be transmitted at a clock rate sufficiently slow so that
	 * SDA is low for a minimum period of t_WLO."
	 *
	 * (t_WLO = 60 microseconds)
	 */
	unsigned char buffer = 0x00;

	write(fd_i2c, &buffer, 1);

	return ATCA_SUCCESS;
}

/**
 * @brief Wake up CryptoAuth device using I2C bus.
 *
 * @param[in] iface Interface to logical device to wakeup.
 */
ATCA_STATUS hal_i2c_wake(ATCAIface iface)
{
	ATCA_STATUS ret = ATCA_SUCCESS;
	ATCAIfaceCfg *cfg = atgetifacecfg(iface);
	int retries = cfg->rx_retries;
	uint16_t length = 4;
	uint8_t data[4];
	uint8_t expected[4] = {0x04, 0x11, 0x33, 0x43};

	if (send_wakeup_pulse(cfg) != ATCA_SUCCESS) {
		debug("Could not send wakeup command\n");
		ret = ATCA_COMM_FAIL;
		goto out;
	}

	atca_delay_us(cfg->wake_delay);

	/* Now try to read the wakeup response from the chip */
	do {
		ret = hal_i2c_receive(iface, data, &length);
		retries--;
	} while (retries && ret != ATCA_SUCCESS);

	if (ret != ATCA_SUCCESS || memcmp(data, expected, 4)) {
		ret = ATCA_COMM_FAIL;
		goto out;
	}

out:
	return ret;
}

/**
 * @brief Idle CryptoAuth device using I2C bus.
 * @param[in] iface Interface to logical device to idle.
 */
ATCA_STATUS hal_i2c_idle(ATCAIface iface)
{
	return i2c_send_command(iface, WORD_ADDRESS_IDLE);
}

/**
 * @brief Sleep CryptoAuth device using I2C bus.
 *
 * @param[in] iface Interface to logical device to sleep.
 */
ATCA_STATUS hal_i2c_sleep(ATCAIface iface)
{
	return i2c_send_command(iface, WORD_ADDRESS_SLEEP);
}

/**
 * @brief Manage reference count and release resource if no more refences exist.
 * @param[in] hal_data HAL data structure, known only to the HAL implementation.
 */
ATCA_STATUS hal_i2c_release(void *hal_data)
{
	i2c_bus_ref_ct--;

	if (i2c_bus_ref_ct <= 0)
		i2c_close();

	return ATCA_SUCCESS;
}
