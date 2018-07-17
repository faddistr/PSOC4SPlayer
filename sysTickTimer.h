/** @file
 *  @brief Header file for timers utility
 */
#ifndef SYSTICKTIMER_H
#define SYSTICKTIMER_H
#include <stdint.h>
#include <stdbool.h>
 /**
 * @defgroup sysTickTimer
 *
 * The utility to measure time
 *
 * sysTickTimer component API
 * Used for time measurement
 * Period of the timer 1ms
 * @{
 */ 

/**
 * @brief Configures sysTick Timer
 * Should be called before any actions with module
 *
 * @return none
 */
void sysTickTimer_Init(void);

/**
 * @brief Reading of sysTick Timer counter
 * Miliseconds that are passed from moment of call of 
 * the init function
 *
 * @return actual sysTick Timer value
 */
uint32_t sysTickTimer_GetTimeMs(void);

/**
 * @brief Time period passing check
 *
 * @param[in]  savedTime the time when checking started
 * @param[in]  period  required period
 *
 * @return true if the period is passed, false - if it is not passed
 */
inline bool sysTickTimer_IsTimePassedMs(uint32_t savedTime, uint32_t period)
{
    return ((sysTickTimer_GetTimeMs() - savedTime) >= period);
}
/** @} */
#endif /* SYSTICKTIMER_H */