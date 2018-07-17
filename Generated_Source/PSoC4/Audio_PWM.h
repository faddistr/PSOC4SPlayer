/*******************************************************************************
* File Name: audio__PWM.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the audio__PWM
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_audio__PWM_H)
#define CY_TCPWM_audio__PWM_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} audio__PWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  audio__PWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define audio__PWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define audio__PWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define audio__PWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define audio__PWM_QUAD_ENCODING_MODES            (0lu)
#define audio__PWM_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define audio__PWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define audio__PWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define audio__PWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define audio__PWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define audio__PWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define audio__PWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define audio__PWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define audio__PWM_TC_RUN_MODE                    (0lu)
#define audio__PWM_TC_COUNTER_MODE                (0lu)
#define audio__PWM_TC_COMP_CAP_MODE               (2lu)
#define audio__PWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define audio__PWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define audio__PWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define audio__PWM_TC_START_SIGNAL_MODE           (0lu)
#define audio__PWM_TC_STOP_SIGNAL_MODE            (0lu)
#define audio__PWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define audio__PWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define audio__PWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define audio__PWM_TC_START_SIGNAL_PRESENT        (0lu)
#define audio__PWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define audio__PWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define audio__PWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define audio__PWM_PWM_KILL_EVENT                 (0lu)
#define audio__PWM_PWM_STOP_EVENT                 (0lu)
#define audio__PWM_PWM_MODE                       (4lu)
#define audio__PWM_PWM_OUT_N_INVERT               (0lu)
#define audio__PWM_PWM_OUT_INVERT                 (0lu)
#define audio__PWM_PWM_ALIGN                      (0lu)
#define audio__PWM_PWM_RUN_MODE                   (0lu)
#define audio__PWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define audio__PWM_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define audio__PWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define audio__PWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define audio__PWM_PWM_START_SIGNAL_MODE          (0lu)
#define audio__PWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define audio__PWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define audio__PWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define audio__PWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define audio__PWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define audio__PWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define audio__PWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define audio__PWM_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define audio__PWM_TC_PERIOD_VALUE                (65535lu)
#define audio__PWM_TC_COMPARE_VALUE               (65535lu)
#define audio__PWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define audio__PWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define audio__PWM_PWM_PERIOD_VALUE               (256lu)
#define audio__PWM_PWM_PERIOD_BUF_VALUE           (256lu)
#define audio__PWM_PWM_PERIOD_SWAP                (1lu)
#define audio__PWM_PWM_COMPARE_VALUE              (64lu)
#define audio__PWM_PWM_COMPARE_BUF_VALUE          (32lu)
#define audio__PWM_PWM_COMPARE_SWAP               (1lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define audio__PWM__LEFT 0
#define audio__PWM__RIGHT 1
#define audio__PWM__CENTER 2
#define audio__PWM__ASYMMETRIC 3

#define audio__PWM__X1 0
#define audio__PWM__X2 1
#define audio__PWM__X4 2

#define audio__PWM__PWM 4
#define audio__PWM__PWM_DT 5
#define audio__PWM__PWM_PR 6

#define audio__PWM__INVERSE 1
#define audio__PWM__DIRECT 0

#define audio__PWM__CAPTURE 2
#define audio__PWM__COMPARE 0

#define audio__PWM__TRIG_LEVEL 3
#define audio__PWM__TRIG_RISING 0
#define audio__PWM__TRIG_FALLING 1
#define audio__PWM__TRIG_BOTH 2

#define audio__PWM__INTR_MASK_TC 1
#define audio__PWM__INTR_MASK_CC_MATCH 2
#define audio__PWM__INTR_MASK_NONE 0
#define audio__PWM__INTR_MASK_TC_CC 3

#define audio__PWM__UNCONFIG 8
#define audio__PWM__TIMER 1
#define audio__PWM__QUAD 3
#define audio__PWM__PWM_SEL 7

#define audio__PWM__COUNT_UP 0
#define audio__PWM__COUNT_DOWN 1
#define audio__PWM__COUNT_UPDOWN0 2
#define audio__PWM__COUNT_UPDOWN1 3


/* Prescaler */
#define audio__PWM_PRESCALE_DIVBY1                ((uint32)(0u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY2                ((uint32)(1u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY4                ((uint32)(2u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY8                ((uint32)(3u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY16               ((uint32)(4u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY32               ((uint32)(5u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY64               ((uint32)(6u << audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_PRESCALE_DIVBY128              ((uint32)(7u << audio__PWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define audio__PWM_MODE_TIMER_COMPARE             ((uint32)(audio__PWM__COMPARE         <<  \
                                                                  audio__PWM_MODE_SHIFT))
#define audio__PWM_MODE_TIMER_CAPTURE             ((uint32)(audio__PWM__CAPTURE         <<  \
                                                                  audio__PWM_MODE_SHIFT))
#define audio__PWM_MODE_QUAD                      ((uint32)(audio__PWM__QUAD            <<  \
                                                                  audio__PWM_MODE_SHIFT))
#define audio__PWM_MODE_PWM                       ((uint32)(audio__PWM__PWM             <<  \
                                                                  audio__PWM_MODE_SHIFT))
#define audio__PWM_MODE_PWM_DT                    ((uint32)(audio__PWM__PWM_DT          <<  \
                                                                  audio__PWM_MODE_SHIFT))
#define audio__PWM_MODE_PWM_PR                    ((uint32)(audio__PWM__PWM_PR          <<  \
                                                                  audio__PWM_MODE_SHIFT))

/* Quad Modes */
#define audio__PWM_MODE_X1                        ((uint32)(audio__PWM__X1              <<  \
                                                                  audio__PWM_QUAD_MODE_SHIFT))
#define audio__PWM_MODE_X2                        ((uint32)(audio__PWM__X2              <<  \
                                                                  audio__PWM_QUAD_MODE_SHIFT))
#define audio__PWM_MODE_X4                        ((uint32)(audio__PWM__X4              <<  \
                                                                  audio__PWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define audio__PWM_COUNT_UP                       ((uint32)(audio__PWM__COUNT_UP        <<  \
                                                                  audio__PWM_UPDOWN_SHIFT))
#define audio__PWM_COUNT_DOWN                     ((uint32)(audio__PWM__COUNT_DOWN      <<  \
                                                                  audio__PWM_UPDOWN_SHIFT))
#define audio__PWM_COUNT_UPDOWN0                  ((uint32)(audio__PWM__COUNT_UPDOWN0   <<  \
                                                                  audio__PWM_UPDOWN_SHIFT))
#define audio__PWM_COUNT_UPDOWN1                  ((uint32)(audio__PWM__COUNT_UPDOWN1   <<  \
                                                                  audio__PWM_UPDOWN_SHIFT))

/* PWM output invert */
#define audio__PWM_INVERT_LINE                    ((uint32)(audio__PWM__INVERSE         <<  \
                                                                  audio__PWM_INV_OUT_SHIFT))
#define audio__PWM_INVERT_LINE_N                  ((uint32)(audio__PWM__INVERSE         <<  \
                                                                  audio__PWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define audio__PWM_TRIG_RISING                    ((uint32)audio__PWM__TRIG_RISING)
#define audio__PWM_TRIG_FALLING                   ((uint32)audio__PWM__TRIG_FALLING)
#define audio__PWM_TRIG_BOTH                      ((uint32)audio__PWM__TRIG_BOTH)
#define audio__PWM_TRIG_LEVEL                     ((uint32)audio__PWM__TRIG_LEVEL)

/* Interrupt mask */
#define audio__PWM_INTR_MASK_TC                   ((uint32)audio__PWM__INTR_MASK_TC)
#define audio__PWM_INTR_MASK_CC_MATCH             ((uint32)audio__PWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define audio__PWM_CC_MATCH_SET                   (0x00u)
#define audio__PWM_CC_MATCH_CLEAR                 (0x01u)
#define audio__PWM_CC_MATCH_INVERT                (0x02u)
#define audio__PWM_CC_MATCH_NO_CHANGE             (0x03u)
#define audio__PWM_OVERLOW_SET                    (0x00u)
#define audio__PWM_OVERLOW_CLEAR                  (0x04u)
#define audio__PWM_OVERLOW_INVERT                 (0x08u)
#define audio__PWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define audio__PWM_UNDERFLOW_SET                  (0x00u)
#define audio__PWM_UNDERFLOW_CLEAR                (0x10u)
#define audio__PWM_UNDERFLOW_INVERT               (0x20u)
#define audio__PWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define audio__PWM_PWM_MODE_LEFT                  (audio__PWM_CC_MATCH_CLEAR        |   \
                                                         audio__PWM_OVERLOW_SET           |   \
                                                         audio__PWM_UNDERFLOW_NO_CHANGE)
#define audio__PWM_PWM_MODE_RIGHT                 (audio__PWM_CC_MATCH_SET          |   \
                                                         audio__PWM_OVERLOW_NO_CHANGE     |   \
                                                         audio__PWM_UNDERFLOW_CLEAR)
#define audio__PWM_PWM_MODE_ASYM                  (audio__PWM_CC_MATCH_INVERT       |   \
                                                         audio__PWM_OVERLOW_SET           |   \
                                                         audio__PWM_UNDERFLOW_CLEAR)

#if (audio__PWM_CY_TCPWM_V2)
    #if(audio__PWM_CY_TCPWM_4000)
        #define audio__PWM_PWM_MODE_CENTER                (audio__PWM_CC_MATCH_INVERT       |   \
                                                                 audio__PWM_OVERLOW_NO_CHANGE     |   \
                                                                 audio__PWM_UNDERFLOW_CLEAR)
    #else
        #define audio__PWM_PWM_MODE_CENTER                (audio__PWM_CC_MATCH_INVERT       |   \
                                                                 audio__PWM_OVERLOW_SET           |   \
                                                                 audio__PWM_UNDERFLOW_CLEAR)
    #endif /* (audio__PWM_CY_TCPWM_4000) */
#else
    #define audio__PWM_PWM_MODE_CENTER                (audio__PWM_CC_MATCH_INVERT       |   \
                                                             audio__PWM_OVERLOW_NO_CHANGE     |   \
                                                             audio__PWM_UNDERFLOW_CLEAR)
#endif /* (audio__PWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define audio__PWM_CMD_CAPTURE                    (0u)
#define audio__PWM_CMD_RELOAD                     (8u)
#define audio__PWM_CMD_STOP                       (16u)
#define audio__PWM_CMD_START                      (24u)

/* Status */
#define audio__PWM_STATUS_DOWN                    (1u)
#define audio__PWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   audio__PWM_Init(void);
void   audio__PWM_Enable(void);
void   audio__PWM_Start(void);
void   audio__PWM_Stop(void);

void   audio__PWM_SetMode(uint32 mode);
void   audio__PWM_SetCounterMode(uint32 counterMode);
void   audio__PWM_SetPWMMode(uint32 modeMask);
void   audio__PWM_SetQDMode(uint32 qdMode);

void   audio__PWM_SetPrescaler(uint32 prescaler);
void   audio__PWM_TriggerCommand(uint32 mask, uint32 command);
void   audio__PWM_SetOneShot(uint32 oneShotEnable);
uint32 audio__PWM_ReadStatus(void);

void   audio__PWM_SetPWMSyncKill(uint32 syncKillEnable);
void   audio__PWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   audio__PWM_SetPWMDeadTime(uint32 deadTime);
void   audio__PWM_SetPWMInvert(uint32 mask);

void   audio__PWM_SetInterruptMode(uint32 interruptMask);
uint32 audio__PWM_GetInterruptSourceMasked(void);
uint32 audio__PWM_GetInterruptSource(void);
void   audio__PWM_ClearInterrupt(uint32 interruptMask);
void   audio__PWM_SetInterrupt(uint32 interruptMask);

void   audio__PWM_WriteCounter(uint32 count);
uint32 audio__PWM_ReadCounter(void);

uint32 audio__PWM_ReadCapture(void);
uint32 audio__PWM_ReadCaptureBuf(void);

void   audio__PWM_WritePeriod(uint32 period);
uint32 audio__PWM_ReadPeriod(void);
void   audio__PWM_WritePeriodBuf(uint32 periodBuf);
uint32 audio__PWM_ReadPeriodBuf(void);

void   audio__PWM_WriteCompare(uint32 compare);
uint32 audio__PWM_ReadCompare(void);
void   audio__PWM_WriteCompareBuf(uint32 compareBuf);
uint32 audio__PWM_ReadCompareBuf(void);

void   audio__PWM_SetPeriodSwap(uint32 swapEnable);
void   audio__PWM_SetCompareSwap(uint32 swapEnable);

void   audio__PWM_SetCaptureMode(uint32 triggerMode);
void   audio__PWM_SetReloadMode(uint32 triggerMode);
void   audio__PWM_SetStartMode(uint32 triggerMode);
void   audio__PWM_SetStopMode(uint32 triggerMode);
void   audio__PWM_SetCountMode(uint32 triggerMode);

void   audio__PWM_SaveConfig(void);
void   audio__PWM_RestoreConfig(void);
void   audio__PWM_Sleep(void);
void   audio__PWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define audio__PWM_BLOCK_CONTROL_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define audio__PWM_BLOCK_CONTROL_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define audio__PWM_COMMAND_REG                    (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define audio__PWM_COMMAND_PTR                    ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define audio__PWM_INTRRUPT_CAUSE_REG             (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define audio__PWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define audio__PWM_CONTROL_REG                    (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CTRL )
#define audio__PWM_CONTROL_PTR                    ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CTRL )
#define audio__PWM_STATUS_REG                     (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__STATUS )
#define audio__PWM_STATUS_PTR                     ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__STATUS )
#define audio__PWM_COUNTER_REG                    (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__COUNTER )
#define audio__PWM_COUNTER_PTR                    ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__COUNTER )
#define audio__PWM_COMP_CAP_REG                   (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CC )
#define audio__PWM_COMP_CAP_PTR                   ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CC )
#define audio__PWM_COMP_CAP_BUF_REG               (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define audio__PWM_COMP_CAP_BUF_PTR               ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define audio__PWM_PERIOD_REG                     (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__PERIOD )
#define audio__PWM_PERIOD_PTR                     ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__PERIOD )
#define audio__PWM_PERIOD_BUF_REG                 (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define audio__PWM_PERIOD_BUF_PTR                 ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define audio__PWM_TRIG_CONTROL0_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define audio__PWM_TRIG_CONTROL0_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define audio__PWM_TRIG_CONTROL1_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define audio__PWM_TRIG_CONTROL1_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define audio__PWM_TRIG_CONTROL2_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define audio__PWM_TRIG_CONTROL2_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define audio__PWM_INTERRUPT_REQ_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR )
#define audio__PWM_INTERRUPT_REQ_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR )
#define audio__PWM_INTERRUPT_SET_REG              (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_SET )
#define audio__PWM_INTERRUPT_SET_PTR              ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_SET )
#define audio__PWM_INTERRUPT_MASK_REG             (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define audio__PWM_INTERRUPT_MASK_PTR             ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define audio__PWM_INTERRUPT_MASKED_REG           (*(reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define audio__PWM_INTERRUPT_MASKED_PTR           ( (reg32 *) audio__PWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define audio__PWM_MASK                           ((uint32)audio__PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define audio__PWM_RELOAD_CC_SHIFT                (0u)
#define audio__PWM_RELOAD_PERIOD_SHIFT            (1u)
#define audio__PWM_PWM_SYNC_KILL_SHIFT            (2u)
#define audio__PWM_PWM_STOP_KILL_SHIFT            (3u)
#define audio__PWM_PRESCALER_SHIFT                (8u)
#define audio__PWM_UPDOWN_SHIFT                   (16u)
#define audio__PWM_ONESHOT_SHIFT                  (18u)
#define audio__PWM_QUAD_MODE_SHIFT                (20u)
#define audio__PWM_INV_OUT_SHIFT                  (20u)
#define audio__PWM_INV_COMPL_OUT_SHIFT            (21u)
#define audio__PWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define audio__PWM_RELOAD_CC_MASK                 ((uint32)(audio__PWM_1BIT_MASK        <<  \
                                                                            audio__PWM_RELOAD_CC_SHIFT))
#define audio__PWM_RELOAD_PERIOD_MASK             ((uint32)(audio__PWM_1BIT_MASK        <<  \
                                                                            audio__PWM_RELOAD_PERIOD_SHIFT))
#define audio__PWM_PWM_SYNC_KILL_MASK             ((uint32)(audio__PWM_1BIT_MASK        <<  \
                                                                            audio__PWM_PWM_SYNC_KILL_SHIFT))
#define audio__PWM_PWM_STOP_KILL_MASK             ((uint32)(audio__PWM_1BIT_MASK        <<  \
                                                                            audio__PWM_PWM_STOP_KILL_SHIFT))
#define audio__PWM_PRESCALER_MASK                 ((uint32)(audio__PWM_8BIT_MASK        <<  \
                                                                            audio__PWM_PRESCALER_SHIFT))
#define audio__PWM_UPDOWN_MASK                    ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                            audio__PWM_UPDOWN_SHIFT))
#define audio__PWM_ONESHOT_MASK                   ((uint32)(audio__PWM_1BIT_MASK        <<  \
                                                                            audio__PWM_ONESHOT_SHIFT))
#define audio__PWM_QUAD_MODE_MASK                 ((uint32)(audio__PWM_3BIT_MASK        <<  \
                                                                            audio__PWM_QUAD_MODE_SHIFT))
#define audio__PWM_INV_OUT_MASK                   ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                            audio__PWM_INV_OUT_SHIFT))
#define audio__PWM_MODE_MASK                      ((uint32)(audio__PWM_3BIT_MASK        <<  \
                                                                            audio__PWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define audio__PWM_CAPTURE_SHIFT                  (0u)
#define audio__PWM_COUNT_SHIFT                    (2u)
#define audio__PWM_RELOAD_SHIFT                   (4u)
#define audio__PWM_STOP_SHIFT                     (6u)
#define audio__PWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define audio__PWM_CAPTURE_MASK                   ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                  audio__PWM_CAPTURE_SHIFT))
#define audio__PWM_COUNT_MASK                     ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                  audio__PWM_COUNT_SHIFT))
#define audio__PWM_RELOAD_MASK                    ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                  audio__PWM_RELOAD_SHIFT))
#define audio__PWM_STOP_MASK                      ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                  audio__PWM_STOP_SHIFT))
#define audio__PWM_START_MASK                     ((uint32)(audio__PWM_2BIT_MASK        <<  \
                                                                  audio__PWM_START_SHIFT))

/* MASK */
#define audio__PWM_1BIT_MASK                      ((uint32)0x01u)
#define audio__PWM_2BIT_MASK                      ((uint32)0x03u)
#define audio__PWM_3BIT_MASK                      ((uint32)0x07u)
#define audio__PWM_6BIT_MASK                      ((uint32)0x3Fu)
#define audio__PWM_8BIT_MASK                      ((uint32)0xFFu)
#define audio__PWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define audio__PWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define audio__PWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(audio__PWM_QUAD_ENCODING_MODES     << audio__PWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(audio__PWM_CONFIG                  << audio__PWM_MODE_SHIFT)))

#define audio__PWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(audio__PWM_PWM_STOP_EVENT          << audio__PWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(audio__PWM_PWM_OUT_INVERT          << audio__PWM_INV_OUT_SHIFT))         |\
         ((uint32)(audio__PWM_PWM_OUT_N_INVERT        << audio__PWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(audio__PWM_PWM_MODE                << audio__PWM_MODE_SHIFT)))

#define audio__PWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(audio__PWM_PWM_RUN_MODE         << audio__PWM_ONESHOT_SHIFT))
            
#define audio__PWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(audio__PWM_PWM_ALIGN            << audio__PWM_UPDOWN_SHIFT))

#define audio__PWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(audio__PWM_PWM_KILL_EVENT      << audio__PWM_PWM_SYNC_KILL_SHIFT))

#define audio__PWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(audio__PWM_PWM_DEAD_TIME_CYCLE  << audio__PWM_PRESCALER_SHIFT))

#define audio__PWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(audio__PWM_PWM_PRESCALER        << audio__PWM_PRESCALER_SHIFT))

#define audio__PWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(audio__PWM_TC_PRESCALER            << audio__PWM_PRESCALER_SHIFT))       |\
         ((uint32)(audio__PWM_TC_COUNTER_MODE         << audio__PWM_UPDOWN_SHIFT))          |\
         ((uint32)(audio__PWM_TC_RUN_MODE             << audio__PWM_ONESHOT_SHIFT))         |\
         ((uint32)(audio__PWM_TC_COMP_CAP_MODE        << audio__PWM_MODE_SHIFT)))
        
#define audio__PWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(audio__PWM_QUAD_PHIA_SIGNAL_MODE   << audio__PWM_COUNT_SHIFT))           |\
         ((uint32)(audio__PWM_QUAD_INDEX_SIGNAL_MODE  << audio__PWM_RELOAD_SHIFT))          |\
         ((uint32)(audio__PWM_QUAD_STOP_SIGNAL_MODE   << audio__PWM_STOP_SHIFT))            |\
         ((uint32)(audio__PWM_QUAD_PHIB_SIGNAL_MODE   << audio__PWM_START_SHIFT)))

#define audio__PWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(audio__PWM_PWM_SWITCH_SIGNAL_MODE  << audio__PWM_CAPTURE_SHIFT))         |\
         ((uint32)(audio__PWM_PWM_COUNT_SIGNAL_MODE   << audio__PWM_COUNT_SHIFT))           |\
         ((uint32)(audio__PWM_PWM_RELOAD_SIGNAL_MODE  << audio__PWM_RELOAD_SHIFT))          |\
         ((uint32)(audio__PWM_PWM_STOP_SIGNAL_MODE    << audio__PWM_STOP_SHIFT))            |\
         ((uint32)(audio__PWM_PWM_START_SIGNAL_MODE   << audio__PWM_START_SHIFT)))

#define audio__PWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(audio__PWM_TC_CAPTURE_SIGNAL_MODE  << audio__PWM_CAPTURE_SHIFT))         |\
         ((uint32)(audio__PWM_TC_COUNT_SIGNAL_MODE    << audio__PWM_COUNT_SHIFT))           |\
         ((uint32)(audio__PWM_TC_RELOAD_SIGNAL_MODE   << audio__PWM_RELOAD_SHIFT))          |\
         ((uint32)(audio__PWM_TC_STOP_SIGNAL_MODE     << audio__PWM_STOP_SHIFT))            |\
         ((uint32)(audio__PWM_TC_START_SIGNAL_MODE    << audio__PWM_START_SHIFT)))
        
#define audio__PWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((audio__PWM__COUNT_UPDOWN0 == audio__PWM_TC_COUNTER_MODE)                  ||\
                 (audio__PWM__COUNT_UPDOWN1 == audio__PWM_TC_COUNTER_MODE))

#define audio__PWM_PWM_UPDOWN_CNT_USED                                                            \
                ((audio__PWM__CENTER == audio__PWM_PWM_ALIGN)                               ||\
                 (audio__PWM__ASYMMETRIC == audio__PWM_PWM_ALIGN))               
        
#define audio__PWM_PWM_PR_INIT_VALUE              (1u)
#define audio__PWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_audio__PWM_H */

/* [] END OF FILE */
