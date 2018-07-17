/** @file
 *  @brief Source file for button handlers
 */
#include <stdbool.h>
#include "project.h"
#include "assert.h"
#include "userControls.h"
#include "sysTickTimer.h"

#define BUTTON_PRESS   0
#define BUTTON_RELEASE 1U

#define BUTTON_LONG_PRESS_MS        3000U 
#define BUTTON_MIDDLE_PRESS_MS      1000U 


typedef struct
{
    bool                isInit;
    bool                isIRQ;
    bool                longPressSend;
    uint32_t            timeStampPrev;
    uint32_t            timeStampCur;
    uint8_t             curState;
    uint8_t             prevState;
    onBtnChange_t       onBtnChangeCb;
} userControl_t;

static userControl_t userControl = {.isInit = false};

CY_ISR(Isr_UC_Btn_Handler)
{
    Button_ClearInterrupt();
    
    userControl.isIRQ = true;
    Isr_UC_Btn_ClearPending();
}

void userControl_Init(onBtnChange_t btn_cb)
{
    ASSERT(NULL != btn_cb);

    userControl.isInit = true;
    userControl.onBtnChangeCb = btn_cb;
    userControl.isIRQ = false;
    userControl.prevState = BUTTON_RELEASE;
    userControl.curState  = BUTTON_RELEASE;
    userControl.timeStampPrev = 0;
    Isr_UC_Btn_StartEx(Isr_UC_Btn_Handler);
}

void userControl_Run(void)
{
   ASSERT(userControl.isInit);

   /* No bounce problem observed, skip debouncing for now. */
   if (userControl.isIRQ)
   {
        userControl.isIRQ = false;
        
        userControl.timeStampPrev = userControl.timeStampCur;
        userControl.prevState = userControl.curState;
    
        userControl.curState = Button_Read();
        userControl.timeStampCur = sysTickTimer_GetTimeMs();
        
        if ((userControl.prevState != userControl.curState) && (userControl.prevState == BUTTON_PRESS))
        {
            do
            {
                if (sysTickTimer_IsTimePassedMs(userControl.timeStampPrev, BUTTON_LONG_PRESS_MS))
                {
                    userControl.onBtnChangeCb(BTN_LONG_PRESS);
                    break;
                }
                
                if (sysTickTimer_IsTimePassedMs(userControl.timeStampPrev, BUTTON_MIDDLE_PRESS_MS))
                {
                    userControl.onBtnChangeCb(BTN_MIDDLE_PRESS);
                    break;
                }

               userControl.onBtnChangeCb(BTN_SHORT_PRESS);
            } while(false);
        }
    }
}