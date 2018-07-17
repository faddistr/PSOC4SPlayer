/** @file
 *  @brief Header file with cicle buffer functions
 */  
#ifndef BUFFER_H
#define BUFFER_H
#include <stdint.h>
#include <stdbool.h>
/**
 * @defgroup CicleBuffer
 *
 * Cicle buffer
 * Callback will automaticaly called for each half of buffer, 
 * when pointer will be out of this half
 *
 * @{
 */
/** Maximum size of the buffer, should be power of 2 */
#define BUFFER_SIZE 512U
    
/** Callback when data is required ptr - start pointer, max_size - maximum size, size - actual size */ 
typedef void(*buffer_OnNeedDataCb)(uint8_t *ptr, uint32_t max_size, uint32_t *size);

/**
 * @brief Init function of the buffer
 *
 * It is required to call this function before any actions with buffer
 *
 * @param[in] needDataCb pointer on callback which will be called 
 * inside Run functions when data is required
 *
 * @return none
 * @see buffer_OnNeedDataCb
 */
void buffer_Init(buffer_OnNeedDataCb needDataCb);

/**
 * @brief Get next element from buffer
 *
 * @param[out] next pointer to store next element
 *
 * @return false - no more data available
 */
bool buffer_GetNext(uint8_t *next);

/**
 * @brief Run managment function for buffer
 *
 * @return none
 */
void buffer_Run(void);

/**
 * @brief Stop buffer
 * will be automaticaly called in Init if required
 *
 * @return none
 */
void buffer_Stop(void);

/** @} */
#endif /* BUFFER_H */