/** @file
 *  @brief Source file with main function
 */

/**
 * @mainpage
 *
 * ### INTRODUCTION
 *
 * This is simple realisation of the music player for Cypress PSOC4S MCU
 * It contains also very simple and primitive MIDI sequencer. 
 * Files is played from SD card, maybe BLE support will be added in the future.
 * (Too many projects with BLE, sorry)
 * For audio generation PWM with 8-bit resolution is using.
 * For SD card Fatfs library was ported from other Cypress MCU with some little enhancments to get maximum speed.
 * Since there is only 32K memory available, CapSense was not used.
 * UART is uses for debuging messages output.
 * Supported formats: <BR>
 * PCM/WAV 8-bit, Mono, sample rate: 4K, 8K, 16K, 32K, 64K without compression and without tags,
 * which is enought to here voice and other sounds for most people<BR>
 * MIDI type 0 (one MTrk record), better conver MIDI to WAV <BR>
 *
 * ### Architecture and code style
 * Due to limit resources of the MCU it was decided not to use any RTOS. 
 * Therefore 1-thread superloop architecture with async callse was used.
 * Code style was decided to use closed to MISRA-2012 standard
 *
 * ### Layers of the arcitecture
 * 
 * The lowest layer of sound generation is located in audio.c module.
 * 2 timers were used: 1 in PWM mode to generate required voltage level according to provided 
 * and 1 in compare mode which is dynamically reconfigured according to required sample rate. 
 * High levels modules just add their callbacks and uses audio_Play function for playing sepparated 8-bit samples.
 * Audio.c module provides also pseudo logarithmic attenuation volume adjustment of the input samples.
 *
 * testPlayer.c and player.c modules uses audio module directly.
 * testPlayer is generator of various debug sounds, which were used for hardware debugging.
 * player.c is controller of the music play. It also manages 1K cicle buffer, 
 * which is fullfiled by callbacks from other addon-players. Buffer is located in module buffer.c
 * Other modules just expand functionality of this module.
 *
 * Addon players are pcmPlayer(PCM and WAV) and midiPlayer(MIDI sequencer).
 * This two modules expand player.c
 *
 * High level module filePlayer.c searches for music files in root directory of the
 * SD card and selects required addon-player according to extension of the file. (wrapper for sd card in card.c)
 * When previous was ended filePlayer searches for next one.
 *
 * userControls.c module handles various events from button (only SW2 is available on CY8CKIT).
 * It determins duration of the button press. And provides event information to bussiness logic in main.c
 * Functions to measure time intervals are located in sysTickTimer (standart ARM`s SysTick is used).
 *
 * Bussiness logic and debug console handling is located in main.c
 *
 */
#include <project.h>
#include <stdbool.h>
#include <stdlib.h>
#include "uartPrint.h"
#include "card.h"
#include "pcmPlayer.h"
#include "midiPlayer.h"
#include "player.h"
#include "filePlayer.h"
#include "userControls.h"
#include "sysTickTimer.h"
#include "audio.h"
#include "testPlayer.h"
#include "buffer.h"

#define VOLUME_SET_MODE_TIMEOUT_MS 8000U
#define VOLUME_DEFAULT_PERC        100U

#define LED_ON						(0u)
#define LED_OFF						(1u)
#define LED_VOLUME_STEP             (20u)

typedef struct
{
    bool       enable;
    uint32_t   lastTimeStamp;
} volumeSetMode_t;

static volumeSetMode_t volumeSetMode = {.enable = false,};
static bool prevStatePlay = false;
static bool curStatePlay = false;

static void updateStatusLed(void);
static void increaseVolume(void);
static void displayVolume(uint8_t volume);
static void debugConsole_Run(void);
static void onBtnChange(userControlBtnState_t btnState);

/**
 * @brief Main function
 *
 */
int main()
{   
    CyGlobalIntEnable;
    
    UART_Start();
    uartPrintf("*******Audio_ player**********\r\n");
    
    sysTickTimer_Init();
    audio_Init();
    audio_SetVolume(VOLUME_DEFAULT_PERC);
    
    cardInit();
    cardMount();
    userControl_Init(onBtnChange);
    for(;;)
    {
        updateStatusLed();
        filePlayer_Run();
        userControl_Run();
        debugConsole_Run();
            
        if (volumeSetMode.enable && (sysTickTimer_IsTimePassedMs(volumeSetMode.lastTimeStamp, VOLUME_SET_MODE_TIMEOUT_MS)))
        {
            volumeSetMode.enable = false;
            displayVolume(0);
            uartPrintf("MAIN: Set volume mode Off\r\n");
        }  
    }
}

static void updateStatusLed(void)
{
    prevStatePlay = curStatePlay;
    curStatePlay = filePlayer_isPlay();
    
    if (prevStatePlay != curStatePlay)
    {
        LED9_Write(curStatePlay? LED_ON : LED_OFF);
    }
}

static void onBtnChange(userControlBtnState_t btnState)
{
    uartPrintf("MAIN: Btn state %d\r\n", btnState);
    switch(btnState)
    {
        case BTN_LONG_PRESS:
            volumeSetMode.enable = true;
            volumeSetMode.lastTimeStamp = sysTickTimer_GetTimeMs();
            displayVolume(audio_GetVolume());
            uartPrintf("MAIN: Set volume mode On\r\n");
            increaseVolume();
            break;
            
        case BTN_MIDDLE_PRESS:
            if (curStatePlay)
            {
                filePlayer_Pause();
            } else
            {
                filePlayer_Play();
            }
            break;
            
        case BTN_SHORT_PRESS:
            filePlayer_Next();
            break;
        
        default:
            break;
    }
}

static void increaseVolume(void)
{
    uint8_t volume = audio_GetVolume();
    
    volume += LED_VOLUME_STEP;
    if (volume > 100)
    {
        volume = 0;
    }
    
    audio_SetVolume(volume);           
    displayVolume(audio_GetVolume());
    volumeSetMode.lastTimeStamp = sysTickTimer_GetTimeMs();
}

static void displayVolume(uint8_t volume)
{
    LED4_Write( ( volume > ( 0 * LED_VOLUME_STEP ) ) ? LED_ON : LED_OFF );
    LED5_Write( ( volume > ( 1 * LED_VOLUME_STEP ) ) ? LED_ON : LED_OFF);
    LED6_Write( ( volume > ( 2 * LED_VOLUME_STEP ) ) ? LED_ON : LED_OFF);
    LED7_Write( ( volume > ( 3 * LED_VOLUME_STEP ) ) ? LED_ON : LED_OFF);
    LED8_Write( ( volume > ( 4 * LED_VOLUME_STEP ) ) ? LED_ON : LED_OFF);
}

static void debugConsole_Run(void) // for debug purposes
{
    static bool sine = false;
    static uint8_t note = 0;
    char uartchar;
    uint8_t volume;
    audio_SampleRate_t sampleRate;
    
    uartchar = UART_UartGetChar(); 
    if (uartchar != 0)
    {
        UART_UartPutString(">\r\n");
        switch (uartchar)
        {
            case 'b':
                player_Stop();
                break;
            
            case 'v':
                audio_SetSampleRate(AUDIO_SAMPLE_RATE_16K);
                pcmPlayerPlay("/v.pcm");
                break;
                
            case 't':
                audio_SetSampleRate(AUDIO_SAMPLE_RATE_32K);
                pcmPlayerPlay("/file2.pcm");
                break;
                
            case 'z':
                midiPlayer_Play("/test.mid");
                break;
            
            case 'l':
                filePlayer_Next();
                break;
                
            case 'u':
                cardUmount();
                break;
                
            case 'm':
                cardMount();
                break;
                
            case 'c':
                player_Play();
                break;
                
            case 'd':
                player_Pause();
                break;
                
            case 'w':
                pcmPlayerPlayWav("/f88.wav");
                break;
                
            case 'p':
                sine = !sine;
                if (sine)
                {
                    testPlayerPlay(TEST_PLAY_SINE, 0);
                } else
                {
                    testPlayerStop();
                }
                uartPrintf("Sine generation! status: %s\r\n", sine?"on":"off");
                break;
                
            case '-':
                sampleRate = audio_GetSampleRate();
                sampleRate++;
                if (AUDIO_SAMPLE_RATE_COUNT == sampleRate)
                {
                    sampleRate = AUDIO_SAMPLE_RATE_START;
                }
                audio_SetSampleRate(sampleRate);
                uartPrintf("Period: %d\r\n", sampleRate);
                break;
                
            case 'x':
                uartPrintf("SYSTICK: %d\r\n", sysTickTimer_GetTimeMs());
                break;
                
            case '=':
            case '+':
                sampleRate = audio_GetSampleRate();
                if (sampleRate > AUDIO_SAMPLE_RATE_START)
                {
                    sampleRate--;
                
                    if (AUDIO_SAMPLE_RATE_COUNT == AUDIO_SAMPLE_RATE_START)
                    {
                        sampleRate = (AUDIO_SAMPLE_RATE_COUNT - 1);
                    }
                    audio_SetSampleRate(sampleRate);
                    uartPrintf("Period: %d\r\n", sampleRate);
                }
                break;
                
            case 'y':
                note++;
                if (note == 12)
                {
                    note = 0;
                }
                testPlayerPlay(TEST_PLAY_NOTE, note);
                uartPrintf("Note: %d\r\n", note);
                break;

            case 'n':
                testPlayerPlay(TEST_PLAY_NOTE, note);
                uartPrintf("Note: %d\r\n", note);
                break;
                
            case ',':
                volume = audio_GetVolume();
                if (volume != 0)
                {
                    volume--;
                    audio_SetVolume(volume);
                }
                break;
            
            case '.':
                volume = audio_GetVolume();
                if (volume < 100)
                {
                    volume++;
                    audio_SetVolume(volume);
                }
                break;

            default:
                break;
        }    
    }
}
