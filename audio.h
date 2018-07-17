/** @file
 *  @brief Header file with low-level audio output functions
 */  
#ifndef AUDIO_H
#define AUDIO_H
/**
 * @defgroup Audio
 *
 * Low level functions for audio processing
 *
 * @{
*/
#include <stdint.h>
#include <stdbool.h>
    
#define AUDIO_SAMPLE_RATE_START AUDIO_SAMPLE_RATE_4K

/** Type of the callback which will be called in timer interrupt */
typedef void (*audio_SampleCb_t)(void);

/** Supported sample rates */
typedef enum
{
    AUDIO_SAMPLE_RATE_4K,
    AUDIO_SAMPLE_RATE_8K,
    AUDIO_SAMPLE_RATE_16K,
    AUDIO_SAMPLE_RATE_32K,
    AUDIO_SAMPLE_RATE_64K,
    AUDIO_SAMPLE_RATE_COUNT,
    AUDIO_SAMPLE_RATE_DEFAULT = AUDIO_SAMPLE_RATE_16K,
} audio_SampleRate_t;

/**
 * @brief Audio initialisation
 * Call to audio_Start is required before playing
 *
 * @param none
 * @return none
 */
void audio_Init(void);

/**
 * @brief Play simple audio sample
 *
 * @param none
 * @return none
 */
void audio_Play(uint8_t sample);

/**
 * @brief Stop sound output
 *
 * @param none
 * @return none
 */
void audio_Stop(void);

/**
 * @brief Start sound output
 *
 * @param none
 * @return none
 */
void audio_Start(void);

/**
 * @brief Set sample rate
 *
 * @param[in] rate Sample rate 
 * @return false if sample rate is not supported
 *
 * @see audio_SampleRate_t
 */
bool audio_SetSampleRate(audio_SampleRate_t rate);

/**
 * @brief Get sample rate
 *
 * @param none 
 * @return current sample rate
 *
 * @see audio_SampleRate_t
 */
audio_SampleRate_t audio_GetSampleRate(void);

/**
 * @brief Set callback for timer function
 *
 * @param[in] cb - callback
 *
 * @return false on error
 *
 * @see audio_SampleCb_t
 */
bool audio_SetCallback(audio_SampleCb_t cb);

/**
 * @brief Set volume
 *
 * @param[in] volPerc volume in percent 0 - 100
 *
 * @return false on error
 */
bool audio_SetVolume(uint8_t volPerc);

/**
 * @brief Get volume
 *
 * @param none
 *
 * @return current volume
 */
uint8_t audio_GetVolume(void);
/** @} */  
#endif /* AUDIO_H */