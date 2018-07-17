/** @file
 *  @brief Header file for fatfs managment functions
 */  
#ifndef CARD_H
#define CARD_H
/**
 * @defgroup SDCard
 *
 * @{
 */
#include <stdbool.h>
#include "fatfs\diskio.h"
#include "fatfs\ff.h"
    
/**
 * @brief Init function for SD card
 * Init SPI. Set initial values for internal variables.
 * Should be called before any actions with SD card
 *
 * @param none
 *
 * @return none
 */
void cardInit(void);

/**
 * @brief Mount function for SD card
 * Mount SD card
 *
 * @param none
 *
 * @return false - error, true - card mounted
 */  
bool cardMount(void);

/**
 * @brief Umount function for SD card
 *
 * @param none
 *
 * @return none
 */  
void cardUmount(void);

/**
 * @brief Print fatfs error
 *
 * @param[in] result fatfs result for print
 *
 * @return none
 */  
void cardErrorPrint(FRESULT result);
/** @} */  
#endif /* CARD_H */