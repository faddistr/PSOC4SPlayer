/** @file
 *  @brief Source file with cicle buffer functions
 */  
#include <stdlib.h>
#include "buffer.h"
#include "assert.h"

#define BUFFER_MIDDLE  (BUFFER_SIZE>>1)

typedef struct
{
    uint8_t              data[BUFFER_SIZE];
    uint32_t             lastIdx;
    uint32_t             curIdx;
    bool                 firstHalf;
    buffer_OnNeedDataCb  needDataCb;
    bool                 isInit;
    bool                 isRun;
} buffer_t;

static buffer_t buffer = {.isInit = false, .isRun = false,};

void buffer_Init(buffer_OnNeedDataCb needDataCb)
{
    buffer_Stop();
    ASSERT(NULL != needDataCb);
    
    buffer.needDataCb = needDataCb;
    buffer.isInit     = true; 
    
    buffer.needDataCb(buffer.data, sizeof(buffer.data), &buffer.lastIdx);
    if (0 != buffer.lastIdx)
    {
        buffer.isRun = true;
    }
}

bool buffer_GetNext(uint8_t *next)
{   
    ASSERT(true == buffer.isInit);
    if (buffer.isRun)
    {
        if ((sizeof(buffer.data) != buffer.lastIdx) && (buffer.curIdx == buffer.lastIdx))
        {
            buffer.isRun = false;
        } else
        {           
            if (sizeof(buffer.data) == buffer.curIdx)
            {
                buffer.curIdx = 0;
            }
        }
        *next = buffer.data[buffer.curIdx++]; 
    }
    
    return buffer.isRun;
}

void buffer_Run(void)
{
    if (buffer.isInit && buffer.isRun)
    {
        uint32_t dataReaded = BUFFER_MIDDLE; 
        if (buffer.firstHalf)
        {
            if (buffer.curIdx >= BUFFER_MIDDLE) /* pointer is outside first half */
            {
                buffer.needDataCb(&buffer.data[0], BUFFER_MIDDLE, &dataReaded);  /* populate it */
                buffer.firstHalf = !buffer.firstHalf;
                if (BUFFER_MIDDLE != dataReaded)
                {
                    buffer.lastIdx = dataReaded;
                }
            }
        } else
        {
            if (buffer.curIdx < BUFFER_MIDDLE) /* pointer is outside second half */
            {
                buffer.needDataCb(&buffer.data[BUFFER_MIDDLE], BUFFER_MIDDLE, &dataReaded);  /* populate it */
                buffer.firstHalf = !buffer.firstHalf;
                if (BUFFER_MIDDLE != dataReaded)
                {
                    buffer.lastIdx = dataReaded;
                }
            }
        } 
    }
}

void buffer_Stop(void)
{
    buffer.lastIdx    = sizeof(buffer.data);
    buffer.curIdx     = 0;
    buffer.firstHalf  = true;
    buffer.needDataCb = NULL;
    buffer.isRun      = false;
    buffer.isInit     = true;
}

