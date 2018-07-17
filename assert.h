/** @file
 *  @brief Header file with assert definition
 */  
#ifndef ASSERT_H
#define ASSERT_H
#include "uartPrint.h"
/**
 * @defgroup Common
 *
 * @{
 */
#define ASSERT(b) \
        if(!(b)) \
        { \
            uartPrintf("RuntimeError: Assert in file: %s line: %d\r\n", __FILE__, __LINE__); \
            while(1) {} \
        }
/** @} */
#endif /* ASSERT_H */