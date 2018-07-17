/** @file
 *  @brief Source file for fatfs managment functions
 */  
#include "project.h"
#include "card.h"
#include "assert.h"

#define SD_CARD_DISABLE 1U
#define SD_CARD_ENABLE  0U

const unsigned long rtcYear = 2018;
const unsigned long rtcMonth = 10;
const unsigned long rtcDay = 16;
const unsigned long rtcHour = 10;
const unsigned long rtcMinutes = 32;
const unsigned long rtcSeconds = 0;
FATFS fatFs;
static bool isInit = false;
static bool isMounted = false;

bool cardMount(void)
{
    char label[128] = {0};
    DWORD freeclusters;
    DWORD freesectors;
    DWORD totalsectors;
    
    FATFS *fatFsPtr;
    uint8 resultF;
    bool result = false;
    
    ASSERT(isInit);
    
    if (isMounted)
    {
        uartPrintf("SD: Already mounted!\r\n");
        result = true;
    } else
    {
        do {
            resultF = f_mount(&fatFs, "", 1);
            if (RES_OK != resultF)
            {
                uartPrintf("SD: f_mount failed %d\r\n", resultF);
                break;
            }
       
            resultF = f_getlabel("", label, 0);
            if (RES_OK != resultF)
            {
                uartPrintf("SD: f_getlabel failed %d\r\n", resultF);
                break;
            }
            
           resultF = f_getfree("", &freeclusters, &fatFsPtr);
           if (RES_OK != resultF)
           {
               uartPrintf("SD: f_getfree failed %d\r\n", resultF);
               break;
           }
          
           totalsectors = (fatFsPtr->n_fatent - 2) * fatFsPtr->csize;
           freesectors = freeclusters * fatFsPtr->csize;  
           result = true;
           isMounted = true;
        } while (false); 
        
        if (result)
        {
            uartPrintf("SD: Mounted!\r\n");
            uartPrintf("SD: Label: %s\r\n", label);
            uartPrintf("SD: Free clusters: %d\r\n", freeclusters);
            uartPrintf("SD: Total sectors: %d\r\n", totalsectors);
            uartPrintf("SD: Free sectors: %d\r\n", freesectors);
        }
    }
    
    if (!result)
    {
        cardErrorPrint(resultF);
    } 
    
    return result;
}

void cardUmount(void)
{
    uint8 resultF;
    
    ASSERT(isInit);

    if (isMounted)
    {
        resultF = f_mount(NULL, "", 1);
        if (RES_OK != resultF)
        {
            cardErrorPrint(resultF);
        }
        
        uartPrintf("SD: Unmounted!\r\n");
        isMounted = false;   
    } else
    {
        uartPrintf("SD: Unmount - not mounted!\r\n");
    }
}

void cardInit(void)
{
    isInit = true;
    
    SPI_Start();
    SPI_ss0_m_Write(SD_CARD_DISABLE);
    uartPrintf("SD: Inited\r\n");
}

void cardErrorPrint(FRESULT result)
{
    switch (result)
    {
        case FR_DISK_ERR:
            uartPrintf("SD: error: (FR_DISK_ERR) low level error.\r\n");
            break;
            
        case FR_INT_ERR:
            uartPrintf("SD: error: (FR_INT_ERR)\r\n");
            break; 
            
        case FR_NOT_READY:
            uartPrintf("SD: error: (FR_NOT_READY) card not ready.\r\n");
            break;
            
        case FR_NO_FILE:
            uartPrintf("SD: error: (FR_NO_FILE) invalid file.\r\n");
            break;
            
        case FR_NO_PATH:
            uartPrintf("SD: error: (FR_NO_PATH) invalid path.\r\n");
            break;
            
        case FR_INVALID_NAME:
            uartPrintf("SD: error: (FR_INVALID_NAME) invalid name.\r\n");
            break;
            
        case FR_DENIED:
            uartPrintf("SD: error: (FR_DENIED) operation denied.\r\n");
            break;
            
        case FR_EXIST:
            uartPrintf("SD: error: (FR_EXIST) it exists yet...\r\n");
            break;
            
        case FR_INVALID_OBJECT:
            uartPrintf("SD: error: (FR_INVALID_OBJECT)\r\n");
            break;
            
        case FR_WRITE_PROTECTED:
            uartPrintf("SD: error: (FR_WRITE_PROTECTED)\r\n");
            break;
            
        case FR_INVALID_DRIVE:
            uartPrintf("SD: error: (FR_INVALID_DRIVE)\r\n");
            break;
            
        case FR_NOT_ENABLED:
            uartPrintf("SD: error: (FR_NOT_ENABLED) card unmounted.\r\n");
            break;
            
        case FR_NO_FILESYSTEM:
            uartPrintf("SD: error: (FR_NO_FILESYSTEM) no valid FAT volume.\r\n");
            break;  
            
        case FR_MKFS_ABORTED:
            uartPrintf("SD: error: (FR_MKFS_ABORTED)\r\n");
            break;
            
        case FR_TIMEOUT:
            uartPrintf("SD: error: (FR_TIMEOUT)\r\n");
            break;
            
        case FR_LOCKED:
            uartPrintf("SD: error: (FR_LOCKED)\r\n");
            break;
            
        case FR_NOT_ENOUGH_CORE:
            uartPrintf("SD: error: (FR_NOT_ENOUGH_CORE)\r\n");
            break;     
            
        case FR_TOO_MANY_OPEN_FILES:
            uartPrintf("SD: error: (FR_TOO_MANY_OPEN_FILES)\r\n");
            break;
            
        case FR_INVALID_PARAMETER:
            uartPrintf("SD: error: (FR_INVALID_PARAMETER)\r\n"); 
            break; 
            
        default: 
            break;
    }
}

DWORD get_fattime()
{
	return (((DWORD)rtcYear - 1980) << 25) | ((DWORD)rtcMonth << 21) | ((DWORD)rtcDay << 16)| (WORD)(rtcHour << 11)| 
            (WORD)(rtcMinutes << 5)	| (WORD)(rtcSeconds >> 1);;
}