/** @file
 *  @brief Header file for player of sound files
 */  
#ifndef FILE_PLAYER_H
#define FILE_PLAYER_H
/**
 * @defgroup FilePlayer
 * 
 * Searches for all music files in root dir and 
 * playing of them. File player will be stopped and reseted when there will be 
 * no files for playing in root dir.  
 * Will automaticaly select "codec"
 *
 * @{
 */  
#include <stdbool.h>
    
/**
 * @brief Run managment function for player
 * Processing of the internal state machine
 *
 * @param none
 *
 * @return none
 */
void filePlayer_Run(void);

/**
 * @brief Pause play
 *
 * @param none
 *
 * @return none
 */
void filePlayer_Pause(void);

/**
 * @brief Resume or start play
 *
 * @param none
 *
 * @return none
 */
void filePlayer_Play(void);

/**
 * @brief Stop player
 *
 * @param none
 *
 * @return none
 */
void filePlayer_Stop(void);

/**
 * @brief Play next song
 *
 * @param none
 *
 * @return none
 */
void filePlayer_Next(void);

/**
 * @brief Get state of player
 *
 * @param none
 *
 * @return true player is playing something
 */
bool filePlayer_isPlay(void);
/** @} */
#endif /* FILE_PLAYER_H */
