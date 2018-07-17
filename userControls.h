/** @file
 *  @brief Header file for button handlers
 */
#ifndef USER_CONTROLS_H
#define USER_CONTROLS_H
#include <stdint.h>
#include <stdbool.h>
    
 /**
 * @defgroup UserControls
 *
 * Button handling.
 * Module uses IRQ
 * 
 * @{
 */ 
/** Button events */
typedef enum
{
    BTN_LONG_PRESS,   /** User pressed button long */
    BTN_SHORT_PRESS,  /** User pressed button short */
    BTN_MIDDLE_PRESS, /** User pressed button middle */
} userControlBtnState_t;

/** Button change callback event, will be called inside Run function */
typedef void(*onBtnChange_t)(userControlBtnState_t btnStat);

/**
 * @brief Init function
 * Should be called before any actions with module
 *
 * @param[in] btn_cb button press callback
 *
 * @return none
 */
void userControl_Init(onBtnChange_t btn_cb);

/**
 * @brief Run functions
 * All processing of the events goes here
 *
 * @param none
 *
 * @return none
 */
void userControl_Run(void);
/** @} */
#endif /* USER_CONTROLS_H */