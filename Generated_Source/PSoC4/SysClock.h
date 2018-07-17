/*******************************************************************************
* File Name: SysClock.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SysClock
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

#if !defined(CY_TCPWM_SysClock_H)
#define CY_TCPWM_SysClock_H


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
} SysClock_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SysClock_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SysClock_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SysClock_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SysClock_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SysClock_QUAD_ENCODING_MODES            (0lu)
#define SysClock_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SysClock_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SysClock_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SysClock_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SysClock_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SysClock_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SysClock_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SysClock_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SysClock_TC_RUN_MODE                    (0lu)
#define SysClock_TC_COUNTER_MODE                (0lu)
#define SysClock_TC_COMP_CAP_MODE               (0lu)
#define SysClock_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SysClock_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SysClock_TC_COUNT_SIGNAL_MODE           (3lu)
#define SysClock_TC_START_SIGNAL_MODE           (0lu)
#define SysClock_TC_STOP_SIGNAL_MODE            (0lu)
#define SysClock_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SysClock_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SysClock_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SysClock_TC_START_SIGNAL_PRESENT        (0lu)
#define SysClock_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SysClock_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SysClock_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SysClock_PWM_KILL_EVENT                 (0lu)
#define SysClock_PWM_STOP_EVENT                 (0lu)
#define SysClock_PWM_MODE                       (4lu)
#define SysClock_PWM_OUT_N_INVERT               (0lu)
#define SysClock_PWM_OUT_INVERT                 (0lu)
#define SysClock_PWM_ALIGN                      (0lu)
#define SysClock_PWM_RUN_MODE                   (0lu)
#define SysClock_PWM_DEAD_TIME_CYCLE            (0lu)
#define SysClock_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SysClock_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SysClock_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SysClock_PWM_START_SIGNAL_MODE          (0lu)
#define SysClock_PWM_STOP_SIGNAL_MODE           (0lu)
#define SysClock_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SysClock_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SysClock_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SysClock_PWM_START_SIGNAL_PRESENT       (0lu)
#define SysClock_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SysClock_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SysClock_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SysClock_TC_PERIOD_VALUE                (1000lu)
#define SysClock_TC_COMPARE_VALUE               (1000lu)
#define SysClock_TC_COMPARE_BUF_VALUE           (65535lu)
#define SysClock_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SysClock_PWM_PERIOD_VALUE               (65535lu)
#define SysClock_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SysClock_PWM_PERIOD_SWAP                (0lu)
#define SysClock_PWM_COMPARE_VALUE              (65535lu)
#define SysClock_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SysClock_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SysClock__LEFT 0
#define SysClock__RIGHT 1
#define SysClock__CENTER 2
#define SysClock__ASYMMETRIC 3

#define SysClock__X1 0
#define SysClock__X2 1
#define SysClock__X4 2

#define SysClock__PWM 4
#define SysClock__PWM_DT 5
#define SysClock__PWM_PR 6

#define SysClock__INVERSE 1
#define SysClock__DIRECT 0

#define SysClock__CAPTURE 2
#define SysClock__COMPARE 0

#define SysClock__TRIG_LEVEL 3
#define SysClock__TRIG_RISING 0
#define SysClock__TRIG_FALLING 1
#define SysClock__TRIG_BOTH 2

#define SysClock__INTR_MASK_TC 1
#define SysClock__INTR_MASK_CC_MATCH 2
#define SysClock__INTR_MASK_NONE 0
#define SysClock__INTR_MASK_TC_CC 3

#define SysClock__UNCONFIG 8
#define SysClock__TIMER 1
#define SysClock__QUAD 3
#define SysClock__PWM_SEL 7

#define SysClock__COUNT_UP 0
#define SysClock__COUNT_DOWN 1
#define SysClock__COUNT_UPDOWN0 2
#define SysClock__COUNT_UPDOWN1 3


/* Prescaler */
#define SysClock_PRESCALE_DIVBY1                ((uint32)(0u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY2                ((uint32)(1u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY4                ((uint32)(2u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY8                ((uint32)(3u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY16               ((uint32)(4u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY32               ((uint32)(5u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY64               ((uint32)(6u << SysClock_PRESCALER_SHIFT))
#define SysClock_PRESCALE_DIVBY128              ((uint32)(7u << SysClock_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SysClock_MODE_TIMER_COMPARE             ((uint32)(SysClock__COMPARE         <<  \
                                                                  SysClock_MODE_SHIFT))
#define SysClock_MODE_TIMER_CAPTURE             ((uint32)(SysClock__CAPTURE         <<  \
                                                                  SysClock_MODE_SHIFT))
#define SysClock_MODE_QUAD                      ((uint32)(SysClock__QUAD            <<  \
                                                                  SysClock_MODE_SHIFT))
#define SysClock_MODE_PWM                       ((uint32)(SysClock__PWM             <<  \
                                                                  SysClock_MODE_SHIFT))
#define SysClock_MODE_PWM_DT                    ((uint32)(SysClock__PWM_DT          <<  \
                                                                  SysClock_MODE_SHIFT))
#define SysClock_MODE_PWM_PR                    ((uint32)(SysClock__PWM_PR          <<  \
                                                                  SysClock_MODE_SHIFT))

/* Quad Modes */
#define SysClock_MODE_X1                        ((uint32)(SysClock__X1              <<  \
                                                                  SysClock_QUAD_MODE_SHIFT))
#define SysClock_MODE_X2                        ((uint32)(SysClock__X2              <<  \
                                                                  SysClock_QUAD_MODE_SHIFT))
#define SysClock_MODE_X4                        ((uint32)(SysClock__X4              <<  \
                                                                  SysClock_QUAD_MODE_SHIFT))

/* Counter modes */
#define SysClock_COUNT_UP                       ((uint32)(SysClock__COUNT_UP        <<  \
                                                                  SysClock_UPDOWN_SHIFT))
#define SysClock_COUNT_DOWN                     ((uint32)(SysClock__COUNT_DOWN      <<  \
                                                                  SysClock_UPDOWN_SHIFT))
#define SysClock_COUNT_UPDOWN0                  ((uint32)(SysClock__COUNT_UPDOWN0   <<  \
                                                                  SysClock_UPDOWN_SHIFT))
#define SysClock_COUNT_UPDOWN1                  ((uint32)(SysClock__COUNT_UPDOWN1   <<  \
                                                                  SysClock_UPDOWN_SHIFT))

/* PWM output invert */
#define SysClock_INVERT_LINE                    ((uint32)(SysClock__INVERSE         <<  \
                                                                  SysClock_INV_OUT_SHIFT))
#define SysClock_INVERT_LINE_N                  ((uint32)(SysClock__INVERSE         <<  \
                                                                  SysClock_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SysClock_TRIG_RISING                    ((uint32)SysClock__TRIG_RISING)
#define SysClock_TRIG_FALLING                   ((uint32)SysClock__TRIG_FALLING)
#define SysClock_TRIG_BOTH                      ((uint32)SysClock__TRIG_BOTH)
#define SysClock_TRIG_LEVEL                     ((uint32)SysClock__TRIG_LEVEL)

/* Interrupt mask */
#define SysClock_INTR_MASK_TC                   ((uint32)SysClock__INTR_MASK_TC)
#define SysClock_INTR_MASK_CC_MATCH             ((uint32)SysClock__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SysClock_CC_MATCH_SET                   (0x00u)
#define SysClock_CC_MATCH_CLEAR                 (0x01u)
#define SysClock_CC_MATCH_INVERT                (0x02u)
#define SysClock_CC_MATCH_NO_CHANGE             (0x03u)
#define SysClock_OVERLOW_SET                    (0x00u)
#define SysClock_OVERLOW_CLEAR                  (0x04u)
#define SysClock_OVERLOW_INVERT                 (0x08u)
#define SysClock_OVERLOW_NO_CHANGE              (0x0Cu)
#define SysClock_UNDERFLOW_SET                  (0x00u)
#define SysClock_UNDERFLOW_CLEAR                (0x10u)
#define SysClock_UNDERFLOW_INVERT               (0x20u)
#define SysClock_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SysClock_PWM_MODE_LEFT                  (SysClock_CC_MATCH_CLEAR        |   \
                                                         SysClock_OVERLOW_SET           |   \
                                                         SysClock_UNDERFLOW_NO_CHANGE)
#define SysClock_PWM_MODE_RIGHT                 (SysClock_CC_MATCH_SET          |   \
                                                         SysClock_OVERLOW_NO_CHANGE     |   \
                                                         SysClock_UNDERFLOW_CLEAR)
#define SysClock_PWM_MODE_ASYM                  (SysClock_CC_MATCH_INVERT       |   \
                                                         SysClock_OVERLOW_SET           |   \
                                                         SysClock_UNDERFLOW_CLEAR)

#if (SysClock_CY_TCPWM_V2)
    #if(SysClock_CY_TCPWM_4000)
        #define SysClock_PWM_MODE_CENTER                (SysClock_CC_MATCH_INVERT       |   \
                                                                 SysClock_OVERLOW_NO_CHANGE     |   \
                                                                 SysClock_UNDERFLOW_CLEAR)
    #else
        #define SysClock_PWM_MODE_CENTER                (SysClock_CC_MATCH_INVERT       |   \
                                                                 SysClock_OVERLOW_SET           |   \
                                                                 SysClock_UNDERFLOW_CLEAR)
    #endif /* (SysClock_CY_TCPWM_4000) */
#else
    #define SysClock_PWM_MODE_CENTER                (SysClock_CC_MATCH_INVERT       |   \
                                                             SysClock_OVERLOW_NO_CHANGE     |   \
                                                             SysClock_UNDERFLOW_CLEAR)
#endif /* (SysClock_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SysClock_CMD_CAPTURE                    (0u)
#define SysClock_CMD_RELOAD                     (8u)
#define SysClock_CMD_STOP                       (16u)
#define SysClock_CMD_START                      (24u)

/* Status */
#define SysClock_STATUS_DOWN                    (1u)
#define SysClock_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SysClock_Init(void);
void   SysClock_Enable(void);
void   SysClock_Start(void);
void   SysClock_Stop(void);

void   SysClock_SetMode(uint32 mode);
void   SysClock_SetCounterMode(uint32 counterMode);
void   SysClock_SetPWMMode(uint32 modeMask);
void   SysClock_SetQDMode(uint32 qdMode);

void   SysClock_SetPrescaler(uint32 prescaler);
void   SysClock_TriggerCommand(uint32 mask, uint32 command);
void   SysClock_SetOneShot(uint32 oneShotEnable);
uint32 SysClock_ReadStatus(void);

void   SysClock_SetPWMSyncKill(uint32 syncKillEnable);
void   SysClock_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SysClock_SetPWMDeadTime(uint32 deadTime);
void   SysClock_SetPWMInvert(uint32 mask);

void   SysClock_SetInterruptMode(uint32 interruptMask);
uint32 SysClock_GetInterruptSourceMasked(void);
uint32 SysClock_GetInterruptSource(void);
void   SysClock_ClearInterrupt(uint32 interruptMask);
void   SysClock_SetInterrupt(uint32 interruptMask);

void   SysClock_WriteCounter(uint32 count);
uint32 SysClock_ReadCounter(void);

uint32 SysClock_ReadCapture(void);
uint32 SysClock_ReadCaptureBuf(void);

void   SysClock_WritePeriod(uint32 period);
uint32 SysClock_ReadPeriod(void);
void   SysClock_WritePeriodBuf(uint32 periodBuf);
uint32 SysClock_ReadPeriodBuf(void);

void   SysClock_WriteCompare(uint32 compare);
uint32 SysClock_ReadCompare(void);
void   SysClock_WriteCompareBuf(uint32 compareBuf);
uint32 SysClock_ReadCompareBuf(void);

void   SysClock_SetPeriodSwap(uint32 swapEnable);
void   SysClock_SetCompareSwap(uint32 swapEnable);

void   SysClock_SetCaptureMode(uint32 triggerMode);
void   SysClock_SetReloadMode(uint32 triggerMode);
void   SysClock_SetStartMode(uint32 triggerMode);
void   SysClock_SetStopMode(uint32 triggerMode);
void   SysClock_SetCountMode(uint32 triggerMode);

void   SysClock_SaveConfig(void);
void   SysClock_RestoreConfig(void);
void   SysClock_Sleep(void);
void   SysClock_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SysClock_BLOCK_CONTROL_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SysClock_BLOCK_CONTROL_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SysClock_COMMAND_REG                    (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SysClock_COMMAND_PTR                    ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SysClock_INTRRUPT_CAUSE_REG             (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SysClock_INTRRUPT_CAUSE_PTR             ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SysClock_CONTROL_REG                    (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__CTRL )
#define SysClock_CONTROL_PTR                    ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__CTRL )
#define SysClock_STATUS_REG                     (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__STATUS )
#define SysClock_STATUS_PTR                     ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__STATUS )
#define SysClock_COUNTER_REG                    (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__COUNTER )
#define SysClock_COUNTER_PTR                    ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__COUNTER )
#define SysClock_COMP_CAP_REG                   (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__CC )
#define SysClock_COMP_CAP_PTR                   ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__CC )
#define SysClock_COMP_CAP_BUF_REG               (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__CC_BUFF )
#define SysClock_COMP_CAP_BUF_PTR               ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__CC_BUFF )
#define SysClock_PERIOD_REG                     (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__PERIOD )
#define SysClock_PERIOD_PTR                     ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__PERIOD )
#define SysClock_PERIOD_BUF_REG                 (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SysClock_PERIOD_BUF_PTR                 ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SysClock_TRIG_CONTROL0_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SysClock_TRIG_CONTROL0_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SysClock_TRIG_CONTROL1_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SysClock_TRIG_CONTROL1_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SysClock_TRIG_CONTROL2_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SysClock_TRIG_CONTROL2_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SysClock_INTERRUPT_REQ_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR )
#define SysClock_INTERRUPT_REQ_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR )
#define SysClock_INTERRUPT_SET_REG              (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_SET )
#define SysClock_INTERRUPT_SET_PTR              ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_SET )
#define SysClock_INTERRUPT_MASK_REG             (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_MASK )
#define SysClock_INTERRUPT_MASK_PTR             ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_MASK )
#define SysClock_INTERRUPT_MASKED_REG           (*(reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SysClock_INTERRUPT_MASKED_PTR           ( (reg32 *) SysClock_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SysClock_MASK                           ((uint32)SysClock_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SysClock_RELOAD_CC_SHIFT                (0u)
#define SysClock_RELOAD_PERIOD_SHIFT            (1u)
#define SysClock_PWM_SYNC_KILL_SHIFT            (2u)
#define SysClock_PWM_STOP_KILL_SHIFT            (3u)
#define SysClock_PRESCALER_SHIFT                (8u)
#define SysClock_UPDOWN_SHIFT                   (16u)
#define SysClock_ONESHOT_SHIFT                  (18u)
#define SysClock_QUAD_MODE_SHIFT                (20u)
#define SysClock_INV_OUT_SHIFT                  (20u)
#define SysClock_INV_COMPL_OUT_SHIFT            (21u)
#define SysClock_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SysClock_RELOAD_CC_MASK                 ((uint32)(SysClock_1BIT_MASK        <<  \
                                                                            SysClock_RELOAD_CC_SHIFT))
#define SysClock_RELOAD_PERIOD_MASK             ((uint32)(SysClock_1BIT_MASK        <<  \
                                                                            SysClock_RELOAD_PERIOD_SHIFT))
#define SysClock_PWM_SYNC_KILL_MASK             ((uint32)(SysClock_1BIT_MASK        <<  \
                                                                            SysClock_PWM_SYNC_KILL_SHIFT))
#define SysClock_PWM_STOP_KILL_MASK             ((uint32)(SysClock_1BIT_MASK        <<  \
                                                                            SysClock_PWM_STOP_KILL_SHIFT))
#define SysClock_PRESCALER_MASK                 ((uint32)(SysClock_8BIT_MASK        <<  \
                                                                            SysClock_PRESCALER_SHIFT))
#define SysClock_UPDOWN_MASK                    ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                            SysClock_UPDOWN_SHIFT))
#define SysClock_ONESHOT_MASK                   ((uint32)(SysClock_1BIT_MASK        <<  \
                                                                            SysClock_ONESHOT_SHIFT))
#define SysClock_QUAD_MODE_MASK                 ((uint32)(SysClock_3BIT_MASK        <<  \
                                                                            SysClock_QUAD_MODE_SHIFT))
#define SysClock_INV_OUT_MASK                   ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                            SysClock_INV_OUT_SHIFT))
#define SysClock_MODE_MASK                      ((uint32)(SysClock_3BIT_MASK        <<  \
                                                                            SysClock_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SysClock_CAPTURE_SHIFT                  (0u)
#define SysClock_COUNT_SHIFT                    (2u)
#define SysClock_RELOAD_SHIFT                   (4u)
#define SysClock_STOP_SHIFT                     (6u)
#define SysClock_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SysClock_CAPTURE_MASK                   ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                  SysClock_CAPTURE_SHIFT))
#define SysClock_COUNT_MASK                     ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                  SysClock_COUNT_SHIFT))
#define SysClock_RELOAD_MASK                    ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                  SysClock_RELOAD_SHIFT))
#define SysClock_STOP_MASK                      ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                  SysClock_STOP_SHIFT))
#define SysClock_START_MASK                     ((uint32)(SysClock_2BIT_MASK        <<  \
                                                                  SysClock_START_SHIFT))

/* MASK */
#define SysClock_1BIT_MASK                      ((uint32)0x01u)
#define SysClock_2BIT_MASK                      ((uint32)0x03u)
#define SysClock_3BIT_MASK                      ((uint32)0x07u)
#define SysClock_6BIT_MASK                      ((uint32)0x3Fu)
#define SysClock_8BIT_MASK                      ((uint32)0xFFu)
#define SysClock_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SysClock_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SysClock_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SysClock_QUAD_ENCODING_MODES     << SysClock_QUAD_MODE_SHIFT))       |\
         ((uint32)(SysClock_CONFIG                  << SysClock_MODE_SHIFT)))

#define SysClock_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SysClock_PWM_STOP_EVENT          << SysClock_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SysClock_PWM_OUT_INVERT          << SysClock_INV_OUT_SHIFT))         |\
         ((uint32)(SysClock_PWM_OUT_N_INVERT        << SysClock_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SysClock_PWM_MODE                << SysClock_MODE_SHIFT)))

#define SysClock_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SysClock_PWM_RUN_MODE         << SysClock_ONESHOT_SHIFT))
            
#define SysClock_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SysClock_PWM_ALIGN            << SysClock_UPDOWN_SHIFT))

#define SysClock_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SysClock_PWM_KILL_EVENT      << SysClock_PWM_SYNC_KILL_SHIFT))

#define SysClock_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SysClock_PWM_DEAD_TIME_CYCLE  << SysClock_PRESCALER_SHIFT))

#define SysClock_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SysClock_PWM_PRESCALER        << SysClock_PRESCALER_SHIFT))

#define SysClock_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SysClock_TC_PRESCALER            << SysClock_PRESCALER_SHIFT))       |\
         ((uint32)(SysClock_TC_COUNTER_MODE         << SysClock_UPDOWN_SHIFT))          |\
         ((uint32)(SysClock_TC_RUN_MODE             << SysClock_ONESHOT_SHIFT))         |\
         ((uint32)(SysClock_TC_COMP_CAP_MODE        << SysClock_MODE_SHIFT)))
        
#define SysClock_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SysClock_QUAD_PHIA_SIGNAL_MODE   << SysClock_COUNT_SHIFT))           |\
         ((uint32)(SysClock_QUAD_INDEX_SIGNAL_MODE  << SysClock_RELOAD_SHIFT))          |\
         ((uint32)(SysClock_QUAD_STOP_SIGNAL_MODE   << SysClock_STOP_SHIFT))            |\
         ((uint32)(SysClock_QUAD_PHIB_SIGNAL_MODE   << SysClock_START_SHIFT)))

#define SysClock_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SysClock_PWM_SWITCH_SIGNAL_MODE  << SysClock_CAPTURE_SHIFT))         |\
         ((uint32)(SysClock_PWM_COUNT_SIGNAL_MODE   << SysClock_COUNT_SHIFT))           |\
         ((uint32)(SysClock_PWM_RELOAD_SIGNAL_MODE  << SysClock_RELOAD_SHIFT))          |\
         ((uint32)(SysClock_PWM_STOP_SIGNAL_MODE    << SysClock_STOP_SHIFT))            |\
         ((uint32)(SysClock_PWM_START_SIGNAL_MODE   << SysClock_START_SHIFT)))

#define SysClock_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SysClock_TC_CAPTURE_SIGNAL_MODE  << SysClock_CAPTURE_SHIFT))         |\
         ((uint32)(SysClock_TC_COUNT_SIGNAL_MODE    << SysClock_COUNT_SHIFT))           |\
         ((uint32)(SysClock_TC_RELOAD_SIGNAL_MODE   << SysClock_RELOAD_SHIFT))          |\
         ((uint32)(SysClock_TC_STOP_SIGNAL_MODE     << SysClock_STOP_SHIFT))            |\
         ((uint32)(SysClock_TC_START_SIGNAL_MODE    << SysClock_START_SHIFT)))
        
#define SysClock_TIMER_UPDOWN_CNT_USED                                                          \
                ((SysClock__COUNT_UPDOWN0 == SysClock_TC_COUNTER_MODE)                  ||\
                 (SysClock__COUNT_UPDOWN1 == SysClock_TC_COUNTER_MODE))

#define SysClock_PWM_UPDOWN_CNT_USED                                                            \
                ((SysClock__CENTER == SysClock_PWM_ALIGN)                               ||\
                 (SysClock__ASYMMETRIC == SysClock_PWM_ALIGN))               
        
#define SysClock_PWM_PR_INIT_VALUE              (1u)
#define SysClock_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SysClock_H */

/* [] END OF FILE */
