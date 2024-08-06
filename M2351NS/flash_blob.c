/**
 * @file    flash_blob.c
 * @brief   Flash algorithm for the M2351_NS
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

#include "..\flash_blob.h"


extern uint32_t FlashAlgoHeader;
extern uint32_t FlashAlgoBase;
extern uint32_t FlashAlgoLimit;

static const sector_info_t sectors_info[] = {
    {0x00000000, 0x00000800},
 };

static const program_target_t flash = {
    0x30008021, // Init
    0x30008045, // UnInit
    0x30008059, // EraseChip
    0x3000805D, // EraseSector
    0x30008085, // ProgramPage

    // breakpoint = RAM start + 1
    // RSB : base address is address of Execution Region PrgData in map file
    //       to access global/static data
    // RSP : Initial stack pointer
    {
        0x30008001, // breakpoint instruction address
        0x30008000 + 0x20 + 0xD0,   // static base register value (image start + header + static base offset)
        0x30009000  // initial stack pointer
    },

    0x3000A000, // program_buffer, any valid RAM location with +512 bytes of headroom
    0x30008000, // algo_start, start of RAM
    //sizeof(output_flash_prog_blob), // algo_size, size of array above
    (0xD0 + 0x20),
    //output_flash_prog_blob,  // image, flash algo instruction array
    (const uint32_t *)&FlashAlgoHeader,
    2048        // ram_to_flash_bytes_to_be_written
};
