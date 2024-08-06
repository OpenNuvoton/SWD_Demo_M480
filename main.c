/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    M480 Series SWD & Flash Programming Sample Code
 *
 * @copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
 #include <stdio.h>
#include "NuMicro.h"

#include "error.h"
#include "swd_host.h"
#include "target_config.h"

#define PLL_CLOCK       192000000


extern error_t target_flash_init(void);
extern error_t target_flash_uninit(void);
extern error_t target_flash_program_page(uint32_t addr, const uint8_t *buf, uint32_t size);
extern error_t target_flash_erase_sector(uint32_t addr);
extern error_t target_flash_erase_chip(void);

extern uint32_t UserImageBase;
extern uint32_t UserImageLimit;


void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    uint32_t u32PID;
    uint32_t u32Addr;
    uint32_t u32ImageSize;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %dHz\n", SystemCoreClock);

    printf("+-------------------------------------------------+\n");
    printf("|    SWD & Flash Programming Sample Code          |\n");
    printf("+-------------------------------------------------+\n\n");
    printf("  >> Use PA.10 as SWD_CLK Pin and PA.9 as SWD IO Pin (IO_Config.h) << \n");
    printf("     Press any key to start...\n\n");
    getchar();

#ifndef __TARGET_M2351_NS__
    if (!target_set_state(RESET_PROGRAM))
    {
        return 0;
    }

    if (!swd_read_memory(0x40000000, (uint8_t *)&u32PID, 4))
    {
        return 0;
    }

    printf(" The Target PID is 0x%X\n", u32PID);
#endif

    printf(" Start Programming Image (LoadImage.s).\n");

    if (target_flash_init() != ERROR_SUCCESS)
    {
        return 0;
    }

    for (u32Addr = target_device.flash_start; u32Addr < target_device.flash_end; u32Addr += target_device.sector_size)
    {
        if (target_flash_erase_sector(u32Addr) != ERROR_SUCCESS)
        {
            return 0;
        }
    }

    printf(" Erase Done.\n");

    u32ImageSize = (uint32_t)&UserImageLimit - (uint32_t)&UserImageBase;

    if (target_flash_program_page(target_device.flash_start, (const uint8_t *)&UserImageBase, u32ImageSize) != ERROR_SUCCESS)
    {
        return 0;
    }

    printf(" Program Done.\n");

    if (target_flash_uninit() != ERROR_SUCCESS)
    {
        return 0;
    }

    while(1);
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
