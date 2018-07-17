/** @file
 *  @brief Header file for debug prints
 */
#ifndef UART_PRINT_H
#define UART_PRINT_H
 /**
 * @defgroup DebugPrintf
 *
 * @{
 */     
/** Maximum size of buffer */
#define MAX_PRINT_BUFF_SIZE 100U
    
/**
 * @brief UART printf function
 * Print buffer is limited to MAX_PRINT_BUFF_SIZE  
 *
 * @param[in]  sFormat format of printed message
 * @param[in]  ... optional arguments
 *
 * @return none
 * @see MAX_PRINT_BUFF_SIZE
 */
void uartPrintf(const char * sFormat, ...);
/** @} */
#endif /* UART_PRINT_H */
