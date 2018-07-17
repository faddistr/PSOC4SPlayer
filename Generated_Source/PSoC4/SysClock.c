/*******************************************************************************
* File Name: SysClock.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SysClock
*  component
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

#include "SysClock.h"

uint8 SysClock_initVar = 0u;


/*******************************************************************************
* Function Name: SysClock_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SysClock configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SysClock__QUAD == SysClock_CONFIG)
        SysClock_CONTROL_REG = SysClock_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SysClock_TRIG_CONTROL1_REG  = SysClock_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SysClock_SetInterruptMode(SysClock_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SysClock_SetCounterMode(SysClock_COUNT_DOWN);
        SysClock_WritePeriod(SysClock_QUAD_PERIOD_INIT_VALUE);
        SysClock_WriteCounter(SysClock_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SysClock__QUAD == SysClock_CONFIG) */

    #if (SysClock__TIMER == SysClock_CONFIG)
        SysClock_CONTROL_REG = SysClock_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SysClock_TRIG_CONTROL1_REG  = SysClock_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SysClock_SetInterruptMode(SysClock_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SysClock_WritePeriod(SysClock_TC_PERIOD_VALUE );

        #if (SysClock__COMPARE == SysClock_TC_COMP_CAP_MODE)
            SysClock_WriteCompare(SysClock_TC_COMPARE_VALUE);

            #if (1u == SysClock_TC_COMPARE_SWAP)
                SysClock_SetCompareSwap(1u);
                SysClock_WriteCompareBuf(SysClock_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SysClock_TC_COMPARE_SWAP) */
        #endif  /* (SysClock__COMPARE == SysClock_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SysClock_CY_TCPWM_V2 && SysClock_TIMER_UPDOWN_CNT_USED && !SysClock_CY_TCPWM_4000)
            SysClock_WriteCounter(1u);
        #elif(SysClock__COUNT_DOWN == SysClock_TC_COUNTER_MODE)
            SysClock_WriteCounter(SysClock_TC_PERIOD_VALUE);
        #else
            SysClock_WriteCounter(0u);
        #endif /* (SysClock_CY_TCPWM_V2 && SysClock_TIMER_UPDOWN_CNT_USED && !SysClock_CY_TCPWM_4000) */
    #endif  /* (SysClock__TIMER == SysClock_CONFIG) */

    #if (SysClock__PWM_SEL == SysClock_CONFIG)
        SysClock_CONTROL_REG = SysClock_CTRL_PWM_BASE_CONFIG;

        #if (SysClock__PWM_PR == SysClock_PWM_MODE)
            SysClock_CONTROL_REG |= SysClock_CTRL_PWM_RUN_MODE;
            SysClock_WriteCounter(SysClock_PWM_PR_INIT_VALUE);
        #else
            SysClock_CONTROL_REG |= SysClock_CTRL_PWM_ALIGN | SysClock_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SysClock_CY_TCPWM_V2 && SysClock_PWM_UPDOWN_CNT_USED && !SysClock_CY_TCPWM_4000)
                SysClock_WriteCounter(1u);
            #elif (SysClock__RIGHT == SysClock_PWM_ALIGN)
                SysClock_WriteCounter(SysClock_PWM_PERIOD_VALUE);
            #else 
                SysClock_WriteCounter(0u);
            #endif  /* (SysClock_CY_TCPWM_V2 && SysClock_PWM_UPDOWN_CNT_USED && !SysClock_CY_TCPWM_4000) */
        #endif  /* (SysClock__PWM_PR == SysClock_PWM_MODE) */

        #if (SysClock__PWM_DT == SysClock_PWM_MODE)
            SysClock_CONTROL_REG |= SysClock_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SysClock__PWM_DT == SysClock_PWM_MODE) */

        #if (SysClock__PWM == SysClock_PWM_MODE)
            SysClock_CONTROL_REG |= SysClock_CTRL_PWM_PRESCALER;
        #endif  /* (SysClock__PWM == SysClock_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SysClock_TRIG_CONTROL1_REG  = SysClock_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SysClock_SetInterruptMode(SysClock_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SysClock__PWM_PR == SysClock_PWM_MODE)
            SysClock_TRIG_CONTROL2_REG =
                    (SysClock_CC_MATCH_NO_CHANGE    |
                    SysClock_OVERLOW_NO_CHANGE      |
                    SysClock_UNDERFLOW_NO_CHANGE);
        #else
            #if (SysClock__LEFT == SysClock_PWM_ALIGN)
                SysClock_TRIG_CONTROL2_REG = SysClock_PWM_MODE_LEFT;
            #endif  /* ( SysClock_PWM_LEFT == SysClock_PWM_ALIGN) */

            #if (SysClock__RIGHT == SysClock_PWM_ALIGN)
                SysClock_TRIG_CONTROL2_REG = SysClock_PWM_MODE_RIGHT;
            #endif  /* ( SysClock_PWM_RIGHT == SysClock_PWM_ALIGN) */

            #if (SysClock__CENTER == SysClock_PWM_ALIGN)
                SysClock_TRIG_CONTROL2_REG = SysClock_PWM_MODE_CENTER;
            #endif  /* ( SysClock_PWM_CENTER == SysClock_PWM_ALIGN) */

            #if (SysClock__ASYMMETRIC == SysClock_PWM_ALIGN)
                SysClock_TRIG_CONTROL2_REG = SysClock_PWM_MODE_ASYM;
            #endif  /* (SysClock__ASYMMETRIC == SysClock_PWM_ALIGN) */
        #endif  /* (SysClock__PWM_PR == SysClock_PWM_MODE) */

        /* Set other values from customizer */
        SysClock_WritePeriod(SysClock_PWM_PERIOD_VALUE );
        SysClock_WriteCompare(SysClock_PWM_COMPARE_VALUE);

        #if (1u == SysClock_PWM_COMPARE_SWAP)
            SysClock_SetCompareSwap(1u);
            SysClock_WriteCompareBuf(SysClock_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SysClock_PWM_COMPARE_SWAP) */

        #if (1u == SysClock_PWM_PERIOD_SWAP)
            SysClock_SetPeriodSwap(1u);
            SysClock_WritePeriodBuf(SysClock_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SysClock_PWM_PERIOD_SWAP) */
    #endif  /* (SysClock__PWM_SEL == SysClock_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SysClock_Enable
********************************************************************************
*
* Summary:
*  Enables the SysClock.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SysClock_BLOCK_CONTROL_REG |= SysClock_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SysClock__PWM_SEL == SysClock_CONFIG)
        #if (0u == SysClock_PWM_START_SIGNAL_PRESENT)
            SysClock_TriggerCommand(SysClock_MASK, SysClock_CMD_START);
        #endif /* (0u == SysClock_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SysClock__PWM_SEL == SysClock_CONFIG) */

    #if (SysClock__TIMER == SysClock_CONFIG)
        #if (0u == SysClock_TC_START_SIGNAL_PRESENT)
            SysClock_TriggerCommand(SysClock_MASK, SysClock_CMD_START);
        #endif /* (0u == SysClock_TC_START_SIGNAL_PRESENT) */
    #endif /* (SysClock__TIMER == SysClock_CONFIG) */
    
    #if (SysClock__QUAD == SysClock_CONFIG)
        #if (0u != SysClock_QUAD_AUTO_START)
            SysClock_TriggerCommand(SysClock_MASK, SysClock_CMD_RELOAD);
        #endif /* (0u != SysClock_QUAD_AUTO_START) */
    #endif  /* (SysClock__QUAD == SysClock_CONFIG) */
}


/*******************************************************************************
* Function Name: SysClock_Start
********************************************************************************
*
* Summary:
*  Initializes the SysClock with default customizer
*  values when called the first time and enables the SysClock.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SysClock_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SysClock_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SysClock_Start() routine.
*
*******************************************************************************/
void SysClock_Start(void)
{
    if (0u == SysClock_initVar)
    {
        SysClock_Init();
        SysClock_initVar = 1u;
    }

    SysClock_Enable();
}


/*******************************************************************************
* Function Name: SysClock_Stop
********************************************************************************
*
* Summary:
*  Disables the SysClock.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_BLOCK_CONTROL_REG &= (uint32)~SysClock_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SysClock. This function is used when
*  configured as a generic SysClock and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SysClock to operate in
*   Values:
*   - SysClock_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SysClock_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SysClock_MODE_QUAD - Quadrature decoder
*         - SysClock_MODE_PWM - PWM
*         - SysClock_MODE_PWM_DT - PWM with dead time
*         - SysClock_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_MODE_MASK;
    SysClock_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SysClock_MODE_X1 - Counts on phi 1 rising
*         - SysClock_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SysClock_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_QUAD_MODE_MASK;
    SysClock_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SysClock_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SysClock_PRESCALE_DIVBY2    - Divide by 2
*         - SysClock_PRESCALE_DIVBY4    - Divide by 4
*         - SysClock_PRESCALE_DIVBY8    - Divide by 8
*         - SysClock_PRESCALE_DIVBY16   - Divide by 16
*         - SysClock_PRESCALE_DIVBY32   - Divide by 32
*         - SysClock_PRESCALE_DIVBY64   - Divide by 64
*         - SysClock_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_PRESCALER_MASK;
    SysClock_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SysClock runs
*  continuously or stops when terminal count is reached.  By default the
*  SysClock operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_ONESHOT_MASK;
    SysClock_CONTROL_REG |= ((uint32)((oneShotEnable & SysClock_1BIT_MASK) <<
                                                               SysClock_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPWMMode(uint32 modeMask)
{
    SysClock_TRIG_CONTROL2_REG = (modeMask & SysClock_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SysClock_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_PWM_SYNC_KILL_MASK;
    SysClock_CONTROL_REG |= ((uint32)((syncKillEnable & SysClock_1BIT_MASK)  <<
                                               SysClock_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_PWM_STOP_KILL_MASK;
    SysClock_CONTROL_REG |= ((uint32)((stopOnKillEnable & SysClock_1BIT_MASK)  <<
                                                         SysClock_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_PRESCALER_MASK;
    SysClock_CONTROL_REG |= ((uint32)((deadTime & SysClock_8BIT_MASK) <<
                                                          SysClock_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - SysClock_INVERT_LINE   - Inverts the line output
*         - SysClock_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_INV_OUT_MASK;
    SysClock_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SysClock_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_WriteCounter(uint32 count)
{
    SysClock_COUNTER_REG = (count & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 SysClock_ReadCounter(void)
{
    return (SysClock_COUNTER_REG & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SysClock_COUNT_UP       - Counts up
*     - SysClock_COUNT_DOWN     - Counts down
*     - SysClock_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SysClock_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_UPDOWN_MASK;
    SysClock_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_WritePeriod(uint32 period)
{
    SysClock_PERIOD_REG = (period & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SysClock_ReadPeriod(void)
{
    return (SysClock_PERIOD_REG & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_RELOAD_CC_MASK;
    SysClock_CONTROL_REG |= (swapEnable & SysClock_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_WritePeriodBuf(uint32 periodBuf)
{
    SysClock_PERIOD_BUF_REG = (periodBuf & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SysClock_ReadPeriodBuf(void)
{
    return (SysClock_PERIOD_BUF_REG & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_CONTROL_REG &= (uint32)~SysClock_RELOAD_PERIOD_MASK;
    SysClock_CONTROL_REG |= ((uint32)((swapEnable & SysClock_1BIT_MASK) <<
                                                            SysClock_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SysClock_WriteCompare(uint32 compare)
{
    #if (SysClock_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SysClock_CY_TCPWM_4000) */

    #if (SysClock_CY_TCPWM_4000)
        currentMode = ((SysClock_CONTROL_REG & SysClock_UPDOWN_MASK) >> SysClock_UPDOWN_SHIFT);

        if (((uint32)SysClock__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SysClock__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SysClock_CY_TCPWM_4000) */
    
    SysClock_COMP_CAP_REG = (compare & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SysClock_ReadCompare(void)
{
    #if (SysClock_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SysClock_CY_TCPWM_4000) */

    #if (SysClock_CY_TCPWM_4000)
        currentMode = ((SysClock_CONTROL_REG & SysClock_UPDOWN_MASK) >> SysClock_UPDOWN_SHIFT);
        
        regVal = SysClock_COMP_CAP_REG;
        
        if (((uint32)SysClock__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SysClock__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SysClock_16BIT_MASK);
    #else
        return (SysClock_COMP_CAP_REG & SysClock_16BIT_MASK);
    #endif /* (SysClock_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SysClock_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SysClock_WriteCompareBuf(uint32 compareBuf)
{
    #if (SysClock_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SysClock_CY_TCPWM_4000) */

    #if (SysClock_CY_TCPWM_4000)
        currentMode = ((SysClock_CONTROL_REG & SysClock_UPDOWN_MASK) >> SysClock_UPDOWN_SHIFT);

        if (((uint32)SysClock__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SysClock__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SysClock_CY_TCPWM_4000) */
    
    SysClock_COMP_CAP_BUF_REG = (compareBuf & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SysClock_ReadCompareBuf(void)
{
    #if (SysClock_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SysClock_CY_TCPWM_4000) */

    #if (SysClock_CY_TCPWM_4000)
        currentMode = ((SysClock_CONTROL_REG & SysClock_UPDOWN_MASK) >> SysClock_UPDOWN_SHIFT);

        regVal = SysClock_COMP_CAP_BUF_REG;
        
        if (((uint32)SysClock__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SysClock__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SysClock_16BIT_MASK);
    #else
        return (SysClock_COMP_CAP_BUF_REG & SysClock_16BIT_MASK);
    #endif /* (SysClock_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SysClock_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 SysClock_ReadCapture(void)
{
    return (SysClock_COMP_CAP_REG & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 SysClock_ReadCaptureBuf(void)
{
    return (SysClock_COMP_CAP_BUF_REG & SysClock_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SysClock_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SysClock_TRIG_LEVEL     - Level
*     - SysClock_TRIG_RISING    - Rising edge
*     - SysClock_TRIG_FALLING   - Falling edge
*     - SysClock_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_TRIG_CONTROL1_REG &= (uint32)~SysClock_CAPTURE_MASK;
    SysClock_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SysClock_TRIG_LEVEL     - Level
*     - SysClock_TRIG_RISING    - Rising edge
*     - SysClock_TRIG_FALLING   - Falling edge
*     - SysClock_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_TRIG_CONTROL1_REG &= (uint32)~SysClock_RELOAD_MASK;
    SysClock_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SysClock_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SysClock_TRIG_LEVEL     - Level
*     - SysClock_TRIG_RISING    - Rising edge
*     - SysClock_TRIG_FALLING   - Falling edge
*     - SysClock_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_TRIG_CONTROL1_REG &= (uint32)~SysClock_START_MASK;
    SysClock_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SysClock_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SysClock_TRIG_LEVEL     - Level
*     - SysClock_TRIG_RISING    - Rising edge
*     - SysClock_TRIG_FALLING   - Falling edge
*     - SysClock_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_TRIG_CONTROL1_REG &= (uint32)~SysClock_STOP_MASK;
    SysClock_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SysClock_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SysClock_TRIG_LEVEL     - Level
*     - SysClock_TRIG_RISING    - Rising edge
*     - SysClock_TRIG_FALLING   - Falling edge
*     - SysClock_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_TRIG_CONTROL1_REG &= (uint32)~SysClock_COUNT_MASK;
    SysClock_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SysClock_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - SysClock_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SysClock_CMD_RELOAD     - Trigger Reload/Index command
*     - SysClock_CMD_STOP       - Trigger Stop/Kill command
*     - SysClock_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SysClock_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SysClock_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SysClock.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SysClock_STATUS_DOWN    - Set if counting down
*     - SysClock_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SysClock_ReadStatus(void)
{
    return ((SysClock_STATUS_REG >> SysClock_RUNNING_STATUS_SHIFT) |
            (SysClock_STATUS_REG & SysClock_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SysClock_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SysClock_INTR_MASK_TC       - Terminal count mask
*     - SysClock_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetInterruptMode(uint32 interruptMask)
{
    SysClock_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SysClock_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - SysClock_INTR_MASK_TC       - Terminal count mask
*     - SysClock_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SysClock_GetInterruptSourceMasked(void)
{
    return (SysClock_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SysClock_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - SysClock_INTR_MASK_TC       - Terminal count mask
*     - SysClock_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SysClock_GetInterruptSource(void)
{
    return (SysClock_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SysClock_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SysClock_INTR_MASK_TC       - Terminal count mask
*     - SysClock_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_ClearInterrupt(uint32 interruptMask)
{
    SysClock_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SysClock_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SysClock_INTR_MASK_TC       - Terminal count mask
*     - SysClock_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SysClock_SetInterrupt(uint32 interruptMask)
{
    SysClock_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
