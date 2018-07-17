/** @file
 *  @brief Source file for timers utility
 */
#include "sysTickTimer.h"
#include "project.h"
#include "assert.h"

#define SYSTICK_CB_NUM 4

static volatile uint32_t counter = 0;
static bool isInit = false;

static void sysTickTimer_Handler(void);

void sysTickTimer_Init(void)
{
    counter = 0;
    CySysTickInit();
    CySysTickEnable();
    CySysTickSetCallback(SYSTICK_CB_NUM, sysTickTimer_Handler);
    isInit = true;
}

uint32_t sysTickTimer_GetTimeMs(void)
{
    ASSERT(isInit);
    return counter;
}

static void sysTickTimer_Handler(void)
{
      counter++;
}