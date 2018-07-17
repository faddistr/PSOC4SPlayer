/** @file
 *  @brief Source file for low level audio functions
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"
#include "audio.h"
#include "assert.h"

#define MAX_VOL_VALUE  100U
#define MAX_FACTOR     14U

static bool play   = true;
static bool isInit = false;
static uint32_t volume = 0;
static uint8_t volumePerc = 0;
static audio_SampleRate_t sampleRate = AUDIO_SAMPLE_RATE_COUNT;
static uint32_t audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_COUNT];
static audio_SampleCb_t audio_OnTimerCb = NULL;

static void audio_PrintSampleRate(audio_SampleRate_t rate);

CY_ISR(Isr_TC_Handler)
{   
    Timer_audio_ClearInterrupt(Timer_audio_INTR_MASK_TC);
    if ((NULL != audio_OnTimerCb) && (play))
    {
        audio_OnTimerCb();
    }
}

void audio_Play(uint8_t sample)
{
    uint32_t volumeChange = volume>>1;
    uint32_t tmp = 0;
     
    ASSERT(isInit);
    //attenuation volume adjusment of the input samples.
    //idea from https://www.microchip.com/forums/m932509.aspx
    if (volume&0x01)
    {
        volumeChange++;
        tmp = sample >> volumeChange;
        tmp = tmp + (tmp >> 1);
    } else
    {
        tmp = sample >> volumeChange;
    }

    PWM_WriteCompare(tmp & 0xff); 
}

void audio_Start(void)
{
    ASSERT(isInit);
    
    play = true;
    uartPrintf("Audio: Started\r\n");
}

void audio_Stop(void)
{
    ASSERT(isInit);
    
    play = false;
    audio_Play(0);
    uartPrintf("Audio: Stopped\r\n");
}

bool audio_SetSampleRate(audio_SampleRate_t rate)
{
    bool result = false;
    
    ASSERT(isInit);
    if (AUDIO_SAMPLE_RATE_COUNT > rate)
    {
        result = true;
        sampleRate = rate;
        Timer_audio_Stop();
        Timer_audio_WritePeriod(audio_SampleRateTPeriods[sampleRate]);
        Timer_audio_Start();
        PWM_WriteCompare(0);
        uartPrintf("Audio: Timer rate %d\r\n", audio_SampleRateTPeriods[sampleRate]);
        audio_PrintSampleRate(sampleRate);
    }
    
    return result;
}

audio_SampleRate_t audio_GetSampleRate(void)
{
    ASSERT(isInit);
    return sampleRate;
}

bool audio_SetCallback(audio_SampleCb_t cb)
{
    ASSERT(isInit);
    bool result = false;
    
    if (cb != NULL)
    {
        result = true;
        audio_OnTimerCb = cb;
        uartPrintf("Audio: Callback set.\r\n");
    }

    return result;
}

void audio_Init(void)
{
    /* To avoid update and position bugs */
    audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_4K]  = 256;
    audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_8K]  = 128;
    audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_16K] = 64;
    audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_32K] = 32;
    audio_SampleRateTPeriods[AUDIO_SAMPLE_RATE_64K] = 16;
    
    isInit = true;

    Isr_TC_StartEx(Isr_TC_Handler);
    PWM_Start();
    
    ASSERT(true == audio_SetSampleRate(AUDIO_SAMPLE_RATE_DEFAULT));
    Timer_audio_Start();
    uartPrintf("Audio: Inited.\r\n");
    audio_SetVolume(50);
}

bool audio_SetVolume(uint8_t perc)
{
    bool result = false;
    ASSERT(isInit);
    
    if (MAX_VOL_VALUE >= perc)
    {
        result = true;
        volumePerc = perc;
        volume = MAX_FACTOR - (perc * MAX_FACTOR ) / 100; 
        uartPrintf("Audio: Set volume %d %d.\r\n", perc, volume);
    }
      
    return result;
}

uint8_t audio_GetVolume(void)
{
    uint8_t retval = volumePerc;
    
    ASSERT(isInit);
    
    return retval;
}

static void audio_PrintSampleRate(audio_SampleRate_t rate)
{
    switch (rate)
    {
        case AUDIO_SAMPLE_RATE_4K:
            uartPrintf("Audio: Rate 4K\r\n");
            break;
        
        case AUDIO_SAMPLE_RATE_8K:
            uartPrintf("Audio: Rate 8K\r\n");
            break;
        
        case AUDIO_SAMPLE_RATE_16K:
            uartPrintf("Audio: Rate 16K\r\n");
            break;
        
        case AUDIO_SAMPLE_RATE_32K:
            uartPrintf("Audio: Rate 32K\r\n");
            break;
        
        case AUDIO_SAMPLE_RATE_64K:
            uartPrintf("Audio: Rate 64K\r\n");
            break;
    
        default:
            uartPrintf("Audio: Unknown rate %d\r\n", rate);
            break;
    }
}