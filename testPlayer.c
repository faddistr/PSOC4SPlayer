/** @file
 *  @brief Source file for test purpose player
 */
#include "testPlayer.h"
#include "audio.h"
#include "assert.h"

static bool    isPlay = false;
static uint8_t phase = 0;
static testPlayerMode_t curMode = TEST_PLAY_SINE;

static uint32_t curArg = 0;
static uint16_t s_noteFreqEx16k[ 12 ] = { 0xFCDF, 0xEEAE, 0xE147, 0xD4A3, 0xC8B4, 0xBD70, 0xB2CE, 0xA8C4, 0x9F4B, 0x965C, 0x8DEB, 0x85F3 };
static uint8_t  sine_ar[] = {0x88,0xd8,0xff,0xd9,0x80,0x27,0x01,0x28};
static uint16_t tempC = 0;

static void testplayer_audio_Cb(void)
{
    if (isPlay)
    {
        switch (curMode)
        {
            case TEST_PLAY_SINE:
                audio_Play(sine_ar[phase++]);
                if (phase == sizeof(sine_ar))
                {
                    phase = 0;
                }
                break;
            
            case TEST_PLAY_NOTE:
                tempC += s_noteFreqEx16k[curArg];
                audio_Play(((tempC >> 15) & 0x01));
                break;
        
            default:
                audio_Stop();
                break;
        }
    }
}

void testPlayerStop(void)
{
    isPlay = false;
    audio_Stop();
}

void testPlayerStart(void)
{
    isPlay = true;
    ASSERT(true == audio_SetCallback(testplayer_audio_Cb));
    audio_Start();
}

bool testPlayerPlay(testPlayerMode_t mode, uint8_t arg)
{
    bool result = false;
    
    if (mode < TEST_PLAY_MODE_COUNT)
    {
        curMode = mode;
        result = true;
        curArg = arg;   
        testPlayerStart();
    }
    
    return result;
}