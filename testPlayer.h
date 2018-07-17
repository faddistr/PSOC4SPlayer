/** @file
 *  @brief Header file for test purpose player
 */
#ifndef TESTPLAYER_H
#define TESTPLAYER_H
#include <stdbool.h>
#include <stdint.h>
 /**
 * @defgroup TestPlayer
 *
 * Various test signal generation functions
 * This module is not controlled through player.c module
 * @{
 */ 
    
/** Various modes of player */
typedef enum
{
    TEST_PLAY_SINE, /** Play sine, 1KHz for 16K sample rate */
    TEST_PLAY_NOTE, /** Play note for 16K sample rate */
    TEST_PLAY_MODE_COUNT,
} testPlayerMode_t;

/**
 * @brief Play test signal
 *
 * @param[in]  mode mode of the player
 * @param[in]  arg additional argument if required (note)
 *
 * @return false in case of error
 */
bool testPlayerPlay(testPlayerMode_t mode, uint8_t arg);

/**
 * @brief Stop(pause) test signal generation
 *
 * @param none
 *
 * @return none
 */
void testPlayerStop(void);

/**
 * @brief Resume test signal generation
 *
 * @param none
 *
 * @return none
 */
void testPlayerStart(void);
/** @} */
#endif /* TESTPLAYER_H */