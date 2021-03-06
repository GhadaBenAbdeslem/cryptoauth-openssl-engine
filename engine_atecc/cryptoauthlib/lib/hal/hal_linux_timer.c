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
#include "atca_hal.h"
#include <unistd.h>

/**
 * brief HAL function for us delay.
 *
 * @param delay Delay time in microseconds.
 */
void atca_delay_us(uint32_t delay)
{
	usleep(delay);
}

/**
 * @brief Delays for a number of tens of microseconds.
 *
 * @param delay Delay time in tens of microseconds.
 */
void atca_delay_10us(uint32_t delay)
{
	usleep(delay * 10);
}

/**
 * @brief HAL function for ms delay.
 *
 * @param delay Delay time in milliseconds.
 */
void atca_delay_ms(uint32_t delay)
{
	/* We have no native ms-sleep call in Linux */
	usleep(delay * 1000);
}
