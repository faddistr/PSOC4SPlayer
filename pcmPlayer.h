/** @file
 *  @brief Header file for WAV/PCM player
 */ 
#ifndef PCM_PLAYER_H
#define PCM_PLAYER_H

#include <stdbool.h>
/**
 * @defgroup PcmWavPlayer
 * Only 8-bit unsigned samples are supported
 * No compression, no tags. One channel.
 * 32k, 16k, 8k, 4k sample rate
 *
 * @{
 */  
/**
 * @brief Play PCM file
 * Sample rate will not be setted
 * Samples will be treated as mono, 8-bit, unsigned (pcm_u8)
 *
 * @param[in] fname full path to file on SD card
 *
 * @return false failed to play
 */
bool pcmPlayerPlay(const char *fname);

/**
 * @brief Play WAV file
 *
 * @param[in] fname full path to file on SD card
 *
 * @return false failed to play
 */
bool pcmPlayerPlayWav(const char *fname);
/** @} */   
#endif /* PCM_PLAYER_H */