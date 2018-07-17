/** @file
 *  @brief Header file for master player
 */ 
#ifndef PLAYER_H
#define PLAYER_H
    
#include "buffer.h"
#include "audio.h"
/**
 * @defgroup PlayerInterface
 *
 * @{
 */  
    
/** On stop callback type description */
typedef void(*playerCb_t)(void);

/** Callback structure for various player events */
typedef struct
{
    buffer_OnNeedDataCb onDataRead; /** Buffer should be populated with data */
    playerCb_t          onStop;     /** Player stopped */
} playerCbs_t;

/**
 * @brief Init functions for player
 * This function should be called before any actions with player
 * player_Stop will be called if needed
 *
 * @param[in] cbs structure with event callbacks
 *
 * @return none
 *
 * @see playerCbs_t
 * @see player_Stop
 */
void player_Init(playerCbs_t *cbs);

/**
 * @brief Start play
 *
 * @param none
 *
 * @return none
 */
void player_Play(void);

/**
 * @brief Pause music
 *
 * @param none
 *
 * @return none
 */
void player_Pause(void);

/**
 * @brief Stop player and set to uninit state
 * Will be called inside init function if required
 *
 * @param none
 *
 * @return none
 */
void player_Stop(void);

/**
 * @brief Run managment function for player
 *
 * @param none
 *
 * @return none
 */
void player_Run(void);

/**
 * @brief Get state of the player
 *
 * @param none
 *
 * @return true sound output is in progress
 */
bool player_IsPlaying(void);
/** @} */   
#endif /* PLAYER_H */