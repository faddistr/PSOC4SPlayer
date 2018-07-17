/** @file
 *  @brief Source file for player of sound files
 */  
#include <string.h>
#include "filePlayer.h"
#include "card.h"
#include "player.h"
#include "pcmPlayer.h"
#include "midiPlayer.h"
#include "assert.h"

/** Maximum size of the file extension */
#define MAX_EXT_SIZE 4U

const char rootDir[] ="/"; 

typedef enum
{
    FILE_NOT_SUPPORTED,
    FILE_PCM,
    FILE_MIDI,
    FILE_WAV,
    FILE_AMOUNT
} fileType_t;

typedef struct
{
    char        ext[MAX_EXT_SIZE + 1];
    fileType_t  type;
} fileExstRow_t;

typedef enum
{
    FILE_PLAYER_START,
    FILE_PLAYER_PLAY,
    FILE_PLAYER_PAUSE,
    FILE_PLAYER_STOP,
    FILE_PLAYER_NO_DIR,
} filePlayer_State_t;

typedef struct
{
    DIR                 dir;
    FILINFO             fno_temp;
    filePlayer_State_t  state;
} filePlayer_t;

static const fileExstRow_t extDB[] = 
{
    { .ext = ".WAV",  .type =  FILE_WAV, },
    { .ext = ".PCM",  .type =  FILE_PCM, },
    { .ext = ".MID",  .type =  FILE_MIDI,},
};

static const uint32_t extDB_size = sizeof(extDB) / sizeof(fileExstRow_t); /* Will be calculated at compile time */

static bool filePlayer_Init(void);
static bool filePlayer_GetNextFile(void);
static fileType_t filePlayer_GetFileType(void);

static filePlayer_t filePlayer = {.state = FILE_PLAYER_START,};

void filePlayer_Pause(void)
{
    if (FILE_PLAYER_PLAY == filePlayer.state)
    {
        player_Pause();
        filePlayer.state = FILE_PLAYER_PAUSE;
    }
}

void filePlayer_Stop(void)
{
    if (FILE_PLAYER_START != filePlayer.state)
    {
        filePlayer.state = FILE_PLAYER_STOP;
        player_Stop();
    }
}

void filePlayer_Play(void)
{
    if (FILE_PLAYER_PAUSE == filePlayer.state)
    {
        filePlayer.state = FILE_PLAYER_PLAY;
        player_Play();
    } else
    {
       filePlayer_Next();
    }
}

bool filePlayer_isPlay(void)
{
    return (filePlayer.state == FILE_PLAYER_PLAY);
}

void filePlayer_Next(void)
{
    fileType_t fileType;
    bool ret = false;
     
    if (FILE_PLAYER_START != filePlayer.state)
    {
        filePlayer_Stop();
        do
        {
            ret = filePlayer_GetNextFile();
            if (!ret)
            {
                uartPrintf("FPLAYER: No files, rewind to the begining\r\n");
                filePlayer.state = FILE_PLAYER_START;
                break;
            }
            
            fileType = filePlayer_GetFileType();
            uartPrintf("FPLAYER: %s Type: %d\r\n", filePlayer.fno_temp.fname, fileType);
            switch(fileType)
            {
                case FILE_WAV:
                    ret = pcmPlayerPlayWav(filePlayer.fno_temp.fname);
                    break;
                
                case FILE_PCM:
                    audio_SetSampleRate(AUDIO_SAMPLE_RATE_32K);
                    ret = pcmPlayerPlay(filePlayer.fno_temp.fname);
                    break;
                
                case FILE_MIDI:
                    ret = midiPlayer_Play(filePlayer.fno_temp.fname);
                    break;
                
                default:
                    ret = false;
                    break;
            } 
        } while(!ret);
        
        if (ret)
        {
           filePlayer.state = FILE_PLAYER_PLAY;
        }
    }
}

void filePlayer_Run(void)
{
    player_Run();
    switch (filePlayer.state)
    {
        case FILE_PLAYER_START:
            if (filePlayer_Init())
            {
                uartPrintf("FPLAYER: Started!\r\n");
                filePlayer.state = FILE_PLAYER_STOP;
            }
            break;
            
        case FILE_PLAYER_STOP:   
        case FILE_PLAYER_PAUSE:
            break;
            
        case FILE_PLAYER_PLAY:
            if (!player_IsPlaying())
            {
                filePlayer_Next();
            }
            break;
        
        default:
            uartPrintf("FPLAYER: Wrong state %d\r\n", filePlayer.state);
            ASSERT(false);
            break;
    }
 
}

static fileType_t filePlayer_GetFileType(void)
{
    uint32_t i;
    fileType_t ret = FILE_NOT_SUPPORTED;
    
    for (i = 0; i < extDB_size; i++)
    {
        if (NULL != strstr(filePlayer.fno_temp.fname, extDB[i].ext))
        {
            ret = extDB[i].type;
            break;
        }
    }
    
    return ret; 
}

static bool filePlayer_GetNextFile(void)
{
    FRESULT res;
    bool ret = false;
    
    do
    {
         res = f_readdir(&filePlayer.dir, &filePlayer.fno_temp);
         if (res != FR_OK)
         {
            uartPrintf("FPLAYER: Error readdir\r\n");
            break;
         }
            
         if (0 == filePlayer.fno_temp.fname[0])
         {
           uartPrintf("FPLAYER: Dir end, restart!\r\n");
           break;              
          } else
          {
            if (!(filePlayer.fno_temp.fattrib & AM_DIR))
            {
               ret = true;
               break;
             }
          }
    } while (true);
        
    if (FR_OK != res)
    {
       cardErrorPrint(res);
    }
        
    return ret;
}

static bool filePlayer_Init(void)
{
    bool res = false;

    FRESULT resF = f_opendir(&filePlayer.dir, rootDir);
    if (resF == FR_OK) {
        res = true;
    } else
    {
        uartPrintf("FPLAYER: Error openDir\r\n");
        cardErrorPrint(resF);
    }
    
    return res;
}

