/** @file
 *  @brief Source file for debug prints
 */
#include <project.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "uartPrint.h"

static char buff[MAX_PRINT_BUFF_SIZE];

void uartPrintf(const char * sFormat, ...)
{
    va_list ParamList;

	va_start(ParamList, sFormat);
    vsnprintf(buff, sizeof(buff), sFormat, ParamList);
	va_end(ParamList);
    UART_UartPutString(buff);
}
