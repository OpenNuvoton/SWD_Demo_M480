/**
 * @file    IO_Config.h
 * @brief   
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __IO_CONFIG_H__
#define __IO_CONFIG_H__

#include "NuMicro.h"


// Debug Port I/O Pins

// SWCLK Pin
#define PIN_SWCLK_PORT          PA
#define PIN_SWCLK_GPIO          PA10
#define PIN_SWCLK_BIT           10

// SWDIO Out Pin
#define PIN_SWDIO_PORT          PA
#define PIN_SWDIO_GPIO          PA9
#define PIN_SWDIO_BIT           9

// nRESET Pin
#define PIN_nRESET_PORT         PA
#define PIN_nRESET_GPIO         PA11
#define PIN_nRESET_BIT          11

#endif
