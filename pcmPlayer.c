/** @file
 *  @brief Source file for WAV/PCM player
 */ 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "pcmPlayer.h"
#include "card.h"
#include "uartPrint.h"
#include "assert.h"

#define AUDIO_FORMAT_PCM 1U

/** Canonical WAV header */
typedef struct
{
    uint8_t   chunkId[4];
    uint32_t  chunkSize;
    uint8_t   format[4];
    uint8_t   subchunk1Id[4];
    uint32_t  subchunk1Size;
    uint16_t  audioFormat;
    uint16_t  channels;
    uint32_t  sampleRate;
    uint32_t  byteRate;
    uint16_t  blockAlign;
    uint16_t  bitsPerSample;
    uint8_t   subchunk2Id[4];
    uint32_t  subchunk2Size;
} __attribute__ ((packed))  pcmPlayer_WAVHdr_t;

const char riffStr[] = "RIFF";
const char waveStr[] = "WAVE";
const char fmtStr[]  = "fmt "; 
const char dataStr[] = "data";

static bool pcmPlayerPlayInt(const char *fname, bool isWav);
static void pcmPlayerLoadNextCb(uint8_t *buffer, uint32_t maxSize, uint32_t *obtainedSize);
static void pcmPlayerOnEnd(void);
static bool pcmPlayerCheckHeader(void);
static bool pcmPlayerCheckSampleRate(pcmPlayer_WAVHdr_t *hdr);
static bool pcmPlayerSetSampleRate(uint32_t sampleRate);
static void pcmPlayerContinue(void);

static FIL fp;
static bool isOpen = false;
static bool needStop = false;
static bool fileWav = false;
static uint32_t sampleRate = 0;

static playerCbs_t playerCb = {.onDataRead = pcmPlayerLoadNextCb, .onStop = pcmPlayerOnEnd};

bool pcmPlayerPlayWav(const char *fname)
{    
    return pcmPlayerPlayInt(fname, true);
}

bool pcmPlayerPlay(const char *fname)
{
    return pcmPlayerPlayInt(fname, false);
}

static void pcmPlayerContinue(void)
{
    uartPrintf("PCM: Play\\Continue\r\n");
    if (isOpen)
    {
        player_Play();
    } else
    {
        uartPrintf("PCM: Continue - not open\r\n");
    }
}

static bool pcmPlayerSetSampleRate(uint32_t sampleRate)
{
    bool res = false;
    
    switch (sampleRate)
    {
        case 4000:
            res = audio_SetSampleRate(AUDIO_SAMPLE_RATE_4K);
            break;
            
        case 8000:
            res = audio_SetSampleRate(AUDIO_SAMPLE_RATE_8K);
            break;
            
        case 16000:
            res = audio_SetSampleRate(AUDIO_SAMPLE_RATE_16K);
            break;
            
        case 32000:
            res = audio_SetSampleRate(AUDIO_SAMPLE_RATE_32K);
            break;
            
        case 64000:
            res = audio_SetSampleRate(AUDIO_SAMPLE_RATE_64K);
            break;
    
        default:
            break;
    }
    
    return res;
}

static bool pcmPlayerCheckSampleRate(pcmPlayer_WAVHdr_t *hdr)
{
    bool res = false;
    
    switch (hdr->sampleRate)
    {
        case 4000:
        case 8000:
        case 16000:
        case 32000:
        case 64000:
            res = true;
            break;
    
        default:
            break;
    }
    
    return res;
}

static bool pcmPlayerCheckHeader(void)
{
    pcmPlayer_WAVHdr_t header;
    UINT    read;
    uint8_t resultF = RES_OK;
    bool    ret = false; 
    
    do
    {
        resultF = f_read(&fp, &header, sizeof(pcmPlayer_WAVHdr_t), &read);
        if (RES_OK != resultF)
        {
            uartPrintf("PCM: Failed to read WAV header %d\r\n", resultF);
            break;
        }
        
        if (sizeof(pcmPlayer_WAVHdr_t) != read)
        {
            uartPrintf("PCM: Failed to read WAV header - incorrect length\r\n");
            break;
        }
        
        if (0 != memcmp(header.chunkId, riffStr, sizeof(header.chunkId)))
        {
            uartPrintf("PCM: Failed to read WAV header - wrong chunk id\r\n");
            break;
        }
        
        if (0 != memcmp(header.format, waveStr, sizeof(header.format)))
        {
            uartPrintf("PCM: Failed to read WAV header - wrong format id\r\n");
            break;
        }
        
        if (0 != memcmp(header.subchunk1Id, fmtStr, sizeof(header.subchunk1Id)))
        {
            uartPrintf("PCM: Failed to read WAV header - wrong subchunk1 id\r\n");
            break;
        }
        
        if (0 != memcmp(header.subchunk2Id, dataStr, sizeof(header.subchunk2Id)))
        {
            uartPrintf("PCM: Failed to read WAV header - wrong subchunk2 id\r\n");
            break;
        }
        
        if (AUDIO_FORMAT_PCM != header.audioFormat)
        {
            uartPrintf("PCM: Only uncompress pcm supported. Sorry\r\n");
            break;
        }
        
        if (!pcmPlayerCheckSampleRate(&header))
        {
            uartPrintf("PCM: Sample rate not supported\r\n");
            break;
        }
        
        if (1 < header.channels)
        {
            uartPrintf("PCM: Only 1 channel supported\r\n");
            break;
        }
        
        if (8 != header.bitsPerSample)
        {
            uartPrintf("PCM: Only 8 bit supported\r\n");
            break;
        }

        sampleRate = header.sampleRate;
        ret = true;
    } while(false);
    
    if (RES_OK != resultF)
    {
        cardErrorPrint(resultF);
    }
    
    
    return ret;
}

static bool pcmPlayerPlayInt(const char *fname, bool isWav)
{
    uint8_t resultF = RES_OK;
    bool result = false;
    
    uartPrintf("PCM: Play %s\r\n", fname);
    if (isOpen)
    {
        player_Stop();
    }
    fileWav = false;
    
    do
    {
        resultF = f_open(&fp, fname, FA_READ);
        if (RES_OK != resultF)
        {
            uartPrintf("PCM: Failed at open %d\r\n", resultF);
            break;
        }
        
        if (isWav)
        {
            if (!pcmPlayerCheckHeader())
            {
                break;
            }
            
            if (!pcmPlayerSetSampleRate(sampleRate))
            {
               break;
            }
            
            fileWav = true;
        }
     
        result = true;
        isOpen = true;
        player_Init(&playerCb);      
        pcmPlayerContinue();
    } while (false);
    
    if (RES_OK != resultF)
    {
        cardErrorPrint(resultF);
    }
    
    return result;
}

static void pcmPlayerOnEnd(void)
{
    uint8_t resultF;
    
    uartPrintf("PCM: End\r\n");
    uartPrintf("PCM: Stop and close the file\r\n");
    needStop = false;
    if (isOpen)
    {
        isOpen = false;
        resultF = f_close(&fp);
        if (RES_OK != resultF)
        {
            cardErrorPrint(resultF);
        }
    }
}

static void pcmPlayerLoadNextCb(uint8_t *buffer, uint32_t maxSize, uint32_t *obtainedSize)
{
    uint8_t resultF;
    
    ASSERT(isOpen);
    if (!needStop)
    {
        resultF = f_read(&fp, buffer, maxSize, (UINT *)obtainedSize);
        if (RES_OK != resultF)
        {
            uartPrintf("PCM: f_read failed\r\n");
            cardErrorPrint(resultF);
            *obtainedSize = 0;
        }
        
        if (0 == *obtainedSize)
        {
            needStop = true;
            player_Stop();
        }
    }
}