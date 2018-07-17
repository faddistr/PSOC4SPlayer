/** @file
 *  @brief Source file for master player
 */ 
#include <stdint.h>
#include <stdlib.h>
#include "player.h"
#include "uartPrint.h"
#include "assert.h"
#include "audio.h"

typedef struct
{
    bool               isPlay;
    bool               isInit;
    bool               needStop;
    playerCbs_t        cbs;
} player_t;

static void player_audio_Cb(void);

static player_t player = {.isInit = false,};

void player_Init(playerCbs_t *cbs)
{
    ASSERT(NULL != cbs);
    ASSERT(NULL != cbs->onDataRead);
    ASSERT(NULL != cbs->onStop);
    
    if (player.isInit)
    {
        player_Stop();
    }
    
    player.cbs    = *cbs;
    player.isInit = true;
    buffer_Init(player.cbs.onDataRead);
    uartPrintf("Player: Init\r\n");
}

void player_Play(void)
{
    if (player.isInit)
    {
        player.isPlay = true;
        player.needStop = false;
        ASSERT(audio_SetCallback(player_audio_Cb));
        audio_Start();
        uartPrintf("Player: Play\r\n");
    } else
    {
        uartPrintf("Player: No open files\r\n");
    }
}

void player_Pause(void)
{
    if (player.isPlay)
    {
        player.isPlay = false;
        audio_Stop();
        uartPrintf("Player: Stop playing\r\n");
    }
}

void player_Stop(void)
{
    if (player.isInit)
    {
        player.needStop = false;
        player_Pause();
        buffer_Stop();
        player.isInit = false;
        uartPrintf("Player: Stopped\r\n");
        player.cbs.onStop();      
    }
}

void player_Run(void)
{
    if (player.isPlay)
    {
        buffer_Run();
        if (player.needStop)
        {
            player_Stop();
        }
    }
}

bool player_IsPlaying(void)
{
    return player.isPlay;
}

static void player_audio_Cb(void)
{
    uint8_t sample;
    
    if ((player.isPlay) && (!player.needStop))
    {
        if (buffer_GetNext(&sample))
        {
            audio_Play(sample);
        } else
        {
            player.needStop = true;
        }
    }
}
