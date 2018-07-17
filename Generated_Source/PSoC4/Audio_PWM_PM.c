/*******************************************************************************
* File Name: audio__PWM_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "audio__PWM.h"

static audio__PWM_BACKUP_STRUCT audio__PWM_backup;


/*******************************************************************************
* Function Name: audio__PWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio__PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: audio__PWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio__PWM_Sleep(void)
{
    if(0u != (audio__PWM_BLOCK_CONTROL_REG & audio__PWM_MASK))
    {
        audio__PWM_backup.enableState = 1u;
    }
    else
    {
        audio__PWM_backup.enableState = 0u;
    }

    audio__PWM_Stop();
    audio__PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: audio__PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio__PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: audio__PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void audio__PWM_Wakeup(void)
{
    audio__PWM_RestoreConfig();

    if(0u != audio__PWM_backup.enableState)
    {
        audio__PWM_Enable();
    }
}


/* [] END OF FILE */
