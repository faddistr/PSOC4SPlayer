/** @file
 *  @brief Source file for MIDI sequencer
 */ 
#include <string.h>
#include "midiPlayer.h"
#include "player.h"
#include "uartPrint.h"
#include "card.h"
#include "assert.h"

/** Square wave or sine wave, square wave sounds better */
#define SQUARE_WAVE      1
/* 32 000 per second */
#define SAMPLES_PER_MS   32U
#define DEFAULT_TEMPO_MS 500U
#define CHANNELS_MAX     16U


#define EVENT_NOTE_OFF           0x80U
#define EVENT_NOTE_ON            0x90U
#define EVENT_NOTE_AFTERTOUCH    0xA0U
#define EVENT_CONTROLLER         0xB0U
#define EVENT_PROGRAM_CHANGE     0xC0U
#define EVENT_CHANNEL_AFTERTOUCH 0xD0U
#define EVENT_PITCH_BEND         0xE0U
#define EVENT_META               0xFFU

#define EVENT_META_SET_TEMPO 0x51U
#define EVENT_META_TIME_SEQ  0x58U
#define EVENT_META_EOF       0x2FU

#define HTOS(x) ((x)>>8) | ((x)<<8)
#define HTOL(x) (((x)>>24)&0xff) | \
                (((x)<<8)&0xff0000) |\
                (((x)>>8)&0xff00) |\
                (((x)<<24)&0xff000000)

typedef struct {
    uint8_t   type[4];
    uint32_t  size;
} __attribute__ ((packed)) midiPlayer_ChunkHeader_t;

typedef struct {
    uint16_t                 format;
    uint16_t                 tracks;
    uint16_t                 division;   
} __attribute__ ((packed)) midiPlayer_MTHD_t;

typedef struct {
    midiPlayer_ChunkHeader_t chunkHeader;
    midiPlayer_MTHD_t        data;
} __attribute__ ((packed)) midiPlayer_FileHeader_t;

typedef struct {
   uint16_t  cnt;
   uint16_t  cntadd;
} midiPlayer_chanState_t;

typedef struct
{
    uint8_t   channel;
    uint32_t  wait;
    uint16_t  sample;
} midiPlayer_event_t;

typedef struct
{
    uint8_t     m_nze;
    uint8_t     m_t1;
    uint8_t     m_t2;
    uint8_t     m_t3;  
} midiPlayer_wngState_t;

typedef struct
{
   midiPlayer_FileHeader_t   fileHeader;
   midiPlayer_ChunkHeader_t  trackHeader;
   uint32_t                  tempo;
   uint32_t                  samplePerQuarter;
   midiPlayer_chanState_t    chanState[CHANNELS_MAX];
   midiPlayer_event_t        nextEvent;
   bool                      isError;
   bool                      isEnd;
   bool                      isOpen;
   uint8_t                   maxChan;
   FIL                       fp;
   midiPlayer_wngState_t     wng;
} midiPlayer_t;

static bool midiPlayer_Init(void);
static void midiPlayer_LoadNextCb(uint8_t *buffer, uint32_t maxSize, uint32_t *obtainedSize);
static bool midiPlayer_ReadVariableLength(uint32_t *dst);
static bool midiPlayer_ReadChunkHeader(midiPlayer_ChunkHeader_t *dst);
static bool midiPlayer_ReadByte(uint8_t *byte);
static bool midiPlayer_ReadEvent(uint8_t *id, uint32_t *delta_time);
static bool midiPlayer_ParseEventMeta(void);
static bool midiPlayer_SkipEvent(uint32_t params);
static void midiPlayer_ProcessEvents(void);
static void midiPlayer_ParseEvent(uint8_t id, uint32_t delta_time);
static uint32_t midiPlayer_ConvSamplesCnt(uint32_t src);
static uint32_t midiPlayer_GetCalcVal(void);
static uint8_t midiPlayer_GetSample(void);
static uint16_t midiPlayer_ConvNoteSample(uint8_t noteIdx);
static void midiPlayer_SetChanState(uint8_t chanIdx, uint16_t sample);
static void midiPlayer_OnEndCb(void);
static void midiPlayer_Close(void);
static uint8_t midiPlayer_GetWhiteNoise(void);

static const char mthdStr [] = "MThd"; 
static const char mtrkStr [] = "MTrk"; 
static const uint16_t s_noteFreqEx32k[ 12 ] = { 0x7E6F, 0x7757, 0x70A3, 0x6A51, 0x645A, 0x5EB8, 0x5967, 0x5462, 0x4FA5, 0x4B2E, 0x46F5, 0x42F9 };

#if !SQUARE_WAVE
static const int8_t s_sineTable[ 64 ] = { 
    0x00, 0x03, 0x06, 0x09, 0x0C, 0x0F, 0x11, 0x14, 0x16, 0x18, 0x1A, 0x1B, 0x1D, 0x1E, 0x1E, 0x1F, 
    0x1F, 0x1F, 0x1E, 0x1E, 0x1D, 0x1B, 0x1A, 0x18, 0x16, 0x14, 0x11, 0x0F, 0x0C, 0x09, 0x06, 0x03, 
    0x00, 0xFC, 0xF9, 0xF6, 0xF3, 0xF0, 0xEE, 0xEB, 0xE9, 0xE7, 0xE5, 0xE4, 0xE2, 0xE1, 0xE1, 0xE0, 
    0xE0, 0xE0, 0xE1, 0xE1, 0xE2, 0xE4, 0xE5, 0xE7, 0xE9, 0xEB, 0xEE, 0xF0, 0xF3, 0xF6, 0xF9, 0xFC };
#endif

static playerCbs_t playerCb = {.onDataRead = midiPlayer_LoadNextCb, .onStop = midiPlayer_OnEndCb};
static midiPlayer_t midiPlayer = {.isOpen = false,};

bool midiPlayer_Play(const char *fname)
{
    uint8_t resultF = RES_OK;
    bool    result = false;
    
    uartPrintf("MIDI: Play %s\r\n", fname);
    if (midiPlayer.isOpen)
    {
        player_Stop();
    }
   
    resultF = f_open(&midiPlayer.fp, fname, FA_READ);
    if (RES_OK != resultF)
    {
        uartPrintf("MIDI: Failed at open %d\r\n", resultF);
        cardErrorPrint(resultF);
    } else
    {
        result = midiPlayer_Init();         
    }    
    
    if (result)
    {
       player_Play();
    }

    return result;
}


static bool midiPlayer_Init(void)
{
    char    type[5] = {0};
    UINT    len = 0;
    uint8_t resultF = RES_OK;
    bool res = false;
    
    do
    {
        resultF = f_read(&midiPlayer.fp, &midiPlayer.fileHeader, sizeof(midiPlayer_FileHeader_t), &len);
        if (RES_OK != resultF)
        {
            uartPrintf("MIDI: Failed at reading header\r\n", resultF);
            break;
        }
        
        memcpy(type, midiPlayer.fileHeader.chunkHeader.type, sizeof(midiPlayer.fileHeader.chunkHeader.type));
        midiPlayer.fileHeader.chunkHeader.size = HTOL(midiPlayer.fileHeader.chunkHeader.size);
        uartPrintf("MIDI: 0 chunk type %s\r\n", type);
        uartPrintf("MIDI: 0 chunk size %d\r\n", midiPlayer.fileHeader.chunkHeader.size);
        if (memcmp(mthdStr, type, sizeof(midiPlayer.fileHeader.chunkHeader.type)))
        {
            uartPrintf("MIDI: Wrong chunk type\r\n");
            break;
        }
        
        if (6 != midiPlayer.fileHeader.chunkHeader.size)
        {
            uartPrintf("MIDI: Size of 0-chunk should be 6 according to standard\r\n");
            break;
        }
        
        midiPlayer.fileHeader.data.format   = HTOS(midiPlayer.fileHeader.data.format);
        midiPlayer.fileHeader.data.tracks   = HTOS(midiPlayer.fileHeader.data.tracks);
        midiPlayer.fileHeader.data.division = HTOS(midiPlayer.fileHeader.data.division);
        
        uartPrintf("MIDI: Format: %d\r\n", midiPlayer.fileHeader.data.format);
        uartPrintf("MIDI: Tracks: %d\r\n", midiPlayer.fileHeader.data.tracks);
        uartPrintf("MIDI: Division: %d\r\n", midiPlayer.fileHeader.data.division);
        if (0 != midiPlayer.fileHeader.data.format)
        {
            uartPrintf("MIDI: Only format 0 currently supported. Sorry\r\n");
            break;
        }
        
        if (midiPlayer.fileHeader.data.division & 0x8000)
        {
            uartPrintf("MIDI: Time format: number of delta-time units per SMTPE frame. Not supported. Sorry\r\n");
            break;
        } else
        {
            uartPrintf("MIDI: Time format: number of delta-time units in each a quarter-note\r\n");
        }

        
        if (!midiPlayer_ReadChunkHeader(&midiPlayer.trackHeader))
        {
            break;
        }

        res = true;
        
        midiPlayer.isOpen  = true;
        midiPlayer.isEnd   = false;
        midiPlayer.isError = false;
        midiPlayer.nextEvent.wait    = 0;
        midiPlayer.maxChan = 0;
        memset(midiPlayer.chanState, 0x00, sizeof(midiPlayer.chanState));
        midiPlayer.tempo   =  DEFAULT_TEMPO_MS;
        midiPlayer.samplePerQuarter = midiPlayer_GetCalcVal();
        audio_SetSampleRate(AUDIO_SAMPLE_RATE_32K);
        player_Init(&playerCb);  
        
    } while (false);
    
    if (RES_OK != resultF)
    {
        cardErrorPrint(resultF); 
    }
    
    if (!res)
    {
        midiPlayer_Close();
    }
 
    return res;
}

static uint32_t midiPlayer_GetCalcVal(void)
{
    uint32_t tmp = ((midiPlayer.tempo * SAMPLES_PER_MS) / midiPlayer.fileHeader.data.division);

    uartPrintf("MIDI: Samples per quarter %d\r\n", tmp);
    return tmp;
}

static bool midiPlayer_ReadChunkHeader(midiPlayer_ChunkHeader_t *dst)
{

    UINT len = 0;
    bool res = false;
    uint8_t resultF = f_read(&midiPlayer.fp, dst, sizeof(midiPlayer_ChunkHeader_t), &len);
    
    do
    {
        if (RES_OK != resultF)
        {
            uartPrintf("MIDI: Failed at reading track header %d\r\n", resultF);
            cardErrorPrint(resultF);
            break;
        }
        
        if (sizeof(midiPlayer_ChunkHeader_t) != len)
        {
            uartPrintf("MIDI: Failed at reading track header(length) L: %d\r\n", len);
            break;
        }
        
        if (0 != memcmp(dst->type, mtrkStr, 4))
        {
            uartPrintf("MIDI: Failed at checking tracker header type (not MTrk)\r\n");
            break;
        }
        
        dst->size = HTOL(dst->size);
        uartPrintf("MIDI: Track size: %d\r\n", dst->size);   
        res = true;
    } while(false);
    
    return res;
}

static bool midiPlayer_ReadByte(uint8_t *byte)
{
    UINT len = 0;
    bool ret = false;
    uint8_t resultF = f_read(&midiPlayer.fp, byte, 1, &len);
    
    do
    {
        if (RES_OK != resultF)
        {
            uartPrintf("MIDI: Failed at reading file %d\r\n", resultF);
            cardErrorPrint(resultF);
            break;
        }
        
        if (1 != len)
        {
            uartPrintf("MIDI: Failed at reading file(length) %d\r\n", len);
            break;
        }
        
        ret = true;
    } while (false);
    
    return ret;
}

static bool midiPlayer_ReadVariableLength(uint32_t *dst)
{
    bool ret = false;
    uint32_t v = 0;
    uint8_t c;
   
    if (midiPlayer_ReadByte(&c))
    {
        v = c & 0x7F;
        while( c & 0x80 )
        {
            if (!midiPlayer_ReadByte(&c))
            {
                break;
            }
            v = ( v << 7 ) | ( c & 0x7F );
        }
        
        ret = true;
        *dst = v;
    }

  return ret;
}

static uint32_t midiPlayer_ConvSamplesCnt(uint32_t src)
{
    return (midiPlayer.samplePerQuarter * src);
}

static uint8_t midiPlayer_GetWhiteNoise(void)
{
    uint8_t b;
    uint8_t b1;

    midiPlayer.wng.m_t1 = midiPlayer.wng.m_nze;
    midiPlayer.wng.m_t1 &= 66;

    if ( ( midiPlayer.wng.m_t1 != 0 )  && ( midiPlayer.wng.m_t1 < 66 ) )
    {
        b = 1;
    }
    else
    {
        b = 0;
    }

    b1 = midiPlayer.wng.m_t2 >> 7;
    midiPlayer.wng.m_t2 <<= 1;
    midiPlayer.wng.m_t2 |= b;
    b = midiPlayer.wng.m_t3 >> 7;
    midiPlayer.wng.m_t3 <<= 1;
    midiPlayer.wng.m_t3 |= b1;
    midiPlayer.wng.m_nze <<= 1;
    midiPlayer.wng.m_nze |= b;

    return midiPlayer.wng.m_nze;
}         

static bool midiPlayer_ParseEventMeta(void)
{
    uint32_t i;
    uint8_t id;
    uint32_t length;
    uint8_t tmp[3];
    bool isOk = true;
    bool res = midiPlayer_ReadByte(&id);
    
    do
    {
        if (!res)
        {
            break;
        }
        
        res = midiPlayer_ReadVariableLength(&length);
        if (!res)
        {
            break;
        }
        
        
        switch(id)
        {
            case EVENT_META_SET_TEMPO:
                for (i = 0; i < 3; i++)
                {
                    if (!midiPlayer_ReadByte(&tmp[i]))
                    {
                        isOk = false;
                        break;
                    }
                }
                    
                if (isOk)
                {
                    midiPlayer.tempo = tmp[0] * 65536 + tmp[1] * 256 + tmp[2];
                    midiPlayer.tempo = midiPlayer.tempo / 1000;
                    uartPrintf("MIDI: Set tempo: %d\r\n", midiPlayer.tempo);
                    midiPlayer.samplePerQuarter = midiPlayer_GetCalcVal();
                    res = true;
                }
                break;
                
            case EVENT_META_EOF:
                uartPrintf("MIDI: End of track\r\n");
                midiPlayer.isEnd = true;
                res = true;
                break;
            
            default:
                uartPrintf("MIDI: Unknown midi meta event %X\r\n", id);
                res = midiPlayer_SkipEvent(length);
                break;
        }
       
    } while (false);
    
    return res;
}

static bool midiPlayer_SkipEvent(uint32_t params)
{
    uint32_t i;
    uint8_t tmp;
    bool ret = true; 
    
    for (i = 0; i < params; i++)
    {
        if (!midiPlayer_ReadByte(&tmp))
        {
            ret = false;
            break;
        }
    }
    
    return ret;
}

static uint16_t midiPlayer_ConvNoteSample(uint8_t noteIdx)
{
    uint8_t noteIdxAr;
    uint8_t noteDiv;
    uint16_t ret;
    // Main idea from http://www.deep-shadows.com/hax/wordpress/?page_id=1111
    noteIdx = noteIdx & 0x7F;
    if (noteIdx <= 1)
    {
        ret = noteIdx;
    } else
    {
        noteIdxAr = 132 - 1 - noteIdx;
        noteDiv   = noteIdxAr / 12; //how many octaves down
        noteIdxAr = noteIdxAr % 12; //Index in array
        ret = s_noteFreqEx32k[noteIdxAr] >> noteDiv;
    }

    return ret;
}

static void midiPlayer_ParseEvent(uint8_t id, uint32_t delta_time)
{   
    if (EVENT_META == id)
    {
        midiPlayer.isError = !midiPlayer_ParseEventMeta();
    } else
    {
        uint8_t noteIdx;
        uint8_t commad;
        uint8_t chanIdx;
        
        commad  = id & 0xF0;
        chanIdx = id & 0x0F; 
        
        if (chanIdx > midiPlayer.maxChan)
        {
            midiPlayer.maxChan = chanIdx;
        }
        switch (commad)
        {
            case EVENT_NOTE_AFTERTOUCH:
                uartPrintf("MIDI: Aftertouch event %X\r\n", id);
                midiPlayer.isError = !midiPlayer_SkipEvent(2);
                break;
            
            case EVENT_CONTROLLER:
                uartPrintf("MIDI: Controller event %X\r\n", id);
                midiPlayer.isError = !midiPlayer_SkipEvent(2);
                break;
            
            case EVENT_PROGRAM_CHANGE:
                uartPrintf("MIDI: Program change event %X\r\n", id);
                midiPlayer.isError = !midiPlayer_SkipEvent(1);
                break;
                
            case EVENT_CHANNEL_AFTERTOUCH:
                uartPrintf("MIDI: Channel aftertouch event %X\r\n", id);
                midiPlayer.isError = !midiPlayer_SkipEvent(1);
                break;
                
            case EVENT_PITCH_BEND:
                midiPlayer.isError = !midiPlayer_SkipEvent(2);
                break;
                
            case EVENT_NOTE_ON:
                midiPlayer.nextEvent.wait = midiPlayer_ConvSamplesCnt(delta_time);
                midiPlayer.isError = !midiPlayer_ReadByte(&noteIdx); 
                if (midiPlayer.isError)
                {
                    break;
                }
                midiPlayer.nextEvent.channel = chanIdx;
                midiPlayer.nextEvent.sample = midiPlayer_ConvNoteSample(noteIdx);
                if (0 == midiPlayer.nextEvent.wait)
                {
                      midiPlayer_SetChanState(midiPlayer.nextEvent.channel, midiPlayer.nextEvent.sample);
                }
                midiPlayer.isError = !midiPlayer_SkipEvent(1); /* Skip velocity */
                break;
                
            case EVENT_NOTE_OFF:
                midiPlayer.nextEvent.wait = midiPlayer_ConvSamplesCnt(delta_time);
                midiPlayer.nextEvent.sample = 0; 
                midiPlayer.nextEvent.channel = chanIdx;
                if (0 == midiPlayer.nextEvent.wait)
                {
                      midiPlayer_SetChanState(midiPlayer.nextEvent.channel, midiPlayer.nextEvent.sample);
                }
                midiPlayer.isError = !midiPlayer_SkipEvent(2); /* Skip velocity and note index */
                break;
        
            default:
                uartPrintf("MIDI: Unknown event %X\r\n", id);
                midiPlayer.isError = true;
                break;   
        }
    }
}

static bool midiPlayer_ReadEvent(uint8_t *id, uint32_t *delta_time)
{
    bool  ret = false;

    do
    {
        if (!midiPlayer_ReadVariableLength(delta_time))
        {
            uartPrintf("MIDI: Failed to obtain delta time\r\n");
            break;
        }
        
        if (!midiPlayer_ReadByte(id))
        {
            uartPrintf("MIDI: Failed to obtain event id\r\n");
            break;
        }
        
        ret = true;
    } while(false);
        
    return ret;
}

static void midiPlayer_SetChanState(uint8_t chanIdx, uint16_t sample)
{
    midiPlayer.chanState[chanIdx].cnt = 0;
    midiPlayer.chanState[chanIdx].cntadd = sample * 2;
}

static void midiPlayer_ProcessEvents(void)
{
    uint8_t  eventId;
    uint32_t delta_time;
    
    midiPlayer_SetChanState(midiPlayer.nextEvent.channel, midiPlayer.nextEvent.sample);
    do
    {
        midiPlayer_ReadEvent(&eventId, &delta_time);
        midiPlayer_ParseEvent(eventId, delta_time);
        
        if (midiPlayer.isEnd)
        {
            break;
        }
        
        if (midiPlayer.isError)
        {
            break;
        }       
    } while (0 == midiPlayer.nextEvent.wait);
}

static uint8_t midiPlayer_GetSample(void)
{
    #if SQUARE_WAVE
    uint8_t sample = 0;
    #else
    uint8_t sample = 0x80;
    #endif
    uint32_t i;
    
    for (i = 0; i < (midiPlayer.maxChan + 1); i++)
    {
        if (1 == midiPlayer.chanState[i].cntadd)
        {
            #if SQUARE_WAVE
            sample += (midiPlayer_GetWhiteNoise() & 0x01);
            #else
            if ( ( midiPlayer_GetWhiteNoise() & 1 ) != 0 )
            {     
                sample += 127 / (midiPlayer.maxChan + 1) / 4;
            }       
            #endif
        } else
        {    
            midiPlayer.chanState[i].cnt += midiPlayer.chanState[i].cntadd;
            #if SQUARE_WAVE
            sample += ((midiPlayer.chanState[i].cnt >> 15) & 0x01);
            #else
            sample += s_sineTable[ ( midiPlayer.chanState[i].cnt >> (15 - 5 ) ) & 63 ];  
            #endif
        }
    }

    return sample;
}

static void midiPlayer_LoadNextCb(uint8_t *buffer, uint32_t maxSize, uint32_t *obtainedSize)
{
    uint32_t i;
    
    if (!midiPlayer.isEnd)
    {
        for (i = 0; i < maxSize; i++)
        {
            if (0 == midiPlayer.nextEvent.wait)
            {
                midiPlayer_ProcessEvents();

                if ((midiPlayer.isError) || (midiPlayer.isEnd))
                {
                    uartPrintf("MIDI: Error or stop\r\n");
                    break;
                }
            } else
            {
                midiPlayer.nextEvent.wait--;
            }
            
            buffer[i] = midiPlayer_GetSample();
        }
        
        *obtainedSize = i;
       
        if (midiPlayer.isError)
        {
            uartPrintf("MIDI: Error\r\n");
            player_Stop();
        }
    }
}

static void midiPlayer_Close(void)
{
    if (midiPlayer.isOpen)
    {
        uartPrintf("MIDI: Closing file\r\n");
        midiPlayer.isOpen = false;
        ASSERT((FRESULT)RES_OK == f_close(&midiPlayer.fp));
    }
}

static void midiPlayer_OnEndCb(void)
{
    uartPrintf("MIDI: On end\r\n");
    midiPlayer_Close();
}