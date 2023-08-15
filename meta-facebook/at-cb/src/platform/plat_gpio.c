/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include <logging/log.h>
#include "libutil.h"
#include "cmsis_os.h"
#include "hal_gpio.h"
#include "plat_gpio.h"
#include "plat_isr.h"
#include "plat_class.h"

LOG_MODULE_REGISTER(plat_gpio);

#define gpio_name_to_num(x) #x,
char *gpio_name[] = {
	name_gpioA name_gpioB name_gpioC name_gpioD name_gpioE name_gpioF name_gpioG name_gpioH
		name_gpioI name_gpioJ name_gpioK name_gpioL name_gpioM name_gpioN name_gpioO
			name_gpioP name_gpioQ name_gpioR name_gpioS name_gpioT name_gpioU
};

char *update_gpio_name[] = {
	update_name_gpioA update_name_gpioB update_name_gpioC update_name_gpioD name_gpioE
		name_gpioF name_gpioG name_gpioH name_gpioI name_gpioJ name_gpioK update_name_gpioL
			update_name_gpioM name_gpioN name_gpioO update_name_gpioP update_name_gpioQ
				name_gpioR update_name_gpioS name_gpioT name_gpioU
};
#undef gpio_name_to_num

// clang-format off

/* chip,
 * number,
 * is_init,is_latch,
 * direction,
 * status,
 * property,
 * int_type,
 * int_cb,
*/

GPIO_CFG plat_gpio_cfg[] = {
	/** Group A: 00-07 **/
	{ CHIP_GPIO, 0, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 1, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 2, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 3, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P1V25_ALERT },
	{ CHIP_GPIO, 4, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 5, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL2_ALERT },
	{ CHIP_GPIO, 6, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL3_ALERT },
	{ CHIP_GPIO, 7, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_FALLING, ISR_FIO_BUTTON },

	/** Group B: 08-15 **/
	{ CHIP_GPIO, 8, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 9, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 10, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 11, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 12, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 13, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 14, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 15, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group C: 16-23 **/
	{ CHIP_GPIO, 16, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 17, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 18, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 19, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 20, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 21, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 22, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 23, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group D: 24-31 **/
	{ CHIP_GPIO, 24, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 25, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 26, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 27, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 28, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 29, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 30, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 31, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group E: 32-29 **/
	{ CHIP_GPIO, 32, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 33, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 34, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 35, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 36, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 37, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 38, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 39, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group F: 40-47 **/
	{ CHIP_GPIO, 40, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_VR_ALERT },
	{ CHIP_GPIO, 41, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 42, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 43, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 44, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 45, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 46, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 47, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group G: 48-55 **/
	{ CHIP_GPIO, 48, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 49, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 50, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 51, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 52, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 53, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 54, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_FALLING, ISR_POWER_STATUS_CHANGE },
	{ CHIP_GPIO, 55, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group H: 56-63 **/
	{ CHIP_GPIO, 56, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 57, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 58, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 59, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 60, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 61, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 62, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 63, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group I: 64-71 **/
	{ CHIP_GPIO, 64, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 65, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 66, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 67, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 68, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 69, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 70, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 71, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group J: 72-79 **/
	{ CHIP_GPIO, 72, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 73, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 74, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 75, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 76, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 77, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 78, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 79, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group K: 80-87 **/
	{ CHIP_GPIO, 80, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 81, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 82, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 83, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 84, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 85, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 86, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 87, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group L: 88-95 **/
	{ CHIP_GPIO, 88, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 89, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 90, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 91, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 92, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 93, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 94, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 95, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group M: 96-103 **/
	{ CHIP_GPIO, 96, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 97, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 98, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 99, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 100, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 101, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 102, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 103, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group N: 104-111 **/
	{ CHIP_GPIO, 104, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 105, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 106, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 107, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 108, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 109, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 110, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 111, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group O: 112-119 **/
	{ CHIP_GPIO, 112, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 113, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 114, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 115, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 116, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 117, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 118, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 119, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group P: 120-127 **/
	{ CHIP_GPIO, 120, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 121, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 122, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 123, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 124, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 125, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 126, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 127, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group Q: 128-135 **/
	{ CHIP_GPIO, 128, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 129, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 130, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 131, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 132, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 133, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 134, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 135, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group R: 136-143 **/
	{ CHIP_GPIO, 136, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 137, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 138, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 139, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 140, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 141, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 142, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 143, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group S: 144-151 **/
	{ CHIP_GPIO, 144, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 145, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 146, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 147, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 148, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 149, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 150, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 151, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group T: 152-159 **/
	{ CHIP_GPIO, 152, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 153, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 154, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 155, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 156, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 157, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 158, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 159, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },

	/** Group U: 160-167 **/
	{ CHIP_GPIO, 160, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 161, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 162, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 163, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 164, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 165, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 166, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
	{ CHIP_GPIO, 167, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
};

GPIO_CFG update_gpio_cfg[] = {
  { CHIP_GPIO, 4, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL1_ALERT },
  { CHIP_GPIO, 10, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL4_ALERT },
  { CHIP_GPIO, 11, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL5_ALERT },
  { CHIP_GPIO, 12, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL6_ALERT },
  { CHIP_GPIO, 19, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL7_ALERT },
  { CHIP_GPIO, 30, DISABLE, DISABLE, GPIO_INPUT, GPIO_LOW, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 44, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 45, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 46, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_LOW, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 47, ENABLE, DISABLE, GPIO_OUTPUT, GPIO_HIGH, OPEN_DRAIN, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 88, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 89, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 90, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 91, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 92, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 93, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 94, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 95, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 97, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 99, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 100, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 101, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_DISABLE, NULL },
  { CHIP_GPIO, 127, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL10_ALERT },
  { CHIP_GPIO, 131, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL11_ALERT },
  { CHIP_GPIO, 132, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL12_ALERT },
  { CHIP_GPIO, 145, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL8_ALERT },
  { CHIP_GPIO, 146, ENABLE, DISABLE, GPIO_INPUT, GPIO_HIGH, PUSH_PULL, GPIO_INT_EDGE_BOTH, ISR_P12V_ACCL9_ALERT },
};
// clang-format on

void init_board_rev_gpio()
{
	// Need to init two GPIO before check expansion card position
	// Due to we doesn't intial GPIO table, using aspeed GPIO API to init GPIO
	const struct device *gpio_dev;
	gpio_dev = device_get_binding("GPIO0_M_P");

	gpio_pin_configure(gpio_dev, (REV_ID0 % GPIO_GROUP_SIZE), GPIO_INPUT);
	gpio_pin_configure(gpio_dev, (REV_ID1 % GPIO_GROUP_SIZE), GPIO_INPUT);
	gpio_pin_configure(gpio_dev, (REV_ID2 % GPIO_GROUP_SIZE), GPIO_INPUT);
	gpio_pin_configure(gpio_dev, (HSC_MODULE_PIN_NUM % GPIO_GROUP_SIZE), GPIO_INPUT);
	gpio_pin_configure(gpio_dev, (POWER_BRICK_MODULE_PIN_NUM % GPIO_GROUP_SIZE), GPIO_INPUT);
}

void update_gpio_cfg_name()
{
	uint8_t table_index = 0;
	uint8_t update_index = 0;
	uint8_t board_rev = get_board_revision();

	switch (board_rev) {
	case POC_STAGE:
	case EVT1_STAGE:
	case EVT2_STAGE:
		break;
	case DVT_STAGE:
	case PVT_STAGE:
	case MP_STAGE:
		for (update_index = 0; update_index < ARRAY_SIZE(update_gpio_cfg); ++update_index) {
			for (table_index = 0; table_index < ARRAY_SIZE(plat_gpio_cfg);
			     ++table_index) {
				if (update_gpio_cfg[update_index].number ==
				    plat_gpio_cfg[table_index].number) {
					memcpy(&plat_gpio_cfg[table_index],
					       &update_gpio_cfg[update_index], sizeof(GPIO_CFG));
					break;
				}

				if (table_index >= ARRAY_SIZE(plat_gpio_cfg)) {
					LOG_ERR("Update GPIO cfg fail, gpio number: 0x%x",
						update_gpio_cfg[update_index].number);
				}
			}
		}

		memcpy(&gpio_name, &update_gpio_name, sizeof(update_gpio_name));
		break;
	default:
		LOG_ERR("Update GPIO cfg fail, board revision: 0x%x", board_rev);
	}
}

bool pal_load_gpio_config(void)
{
	update_gpio_cfg_name();
	memcpy(&gpio_cfg[0], &plat_gpio_cfg[0], sizeof(plat_gpio_cfg));
	return 1;
};
