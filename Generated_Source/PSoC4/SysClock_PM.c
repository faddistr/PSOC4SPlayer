/*******************************************************************************
* File Name: SysClock_PM.c
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

#include "SysClock.h"

static SysClock_BACKUP_STRUCT SysClock_backup;


/*******************************************************************************
* Function Name: SysClock_SaveConfig
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
void SysClock_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SysClock_Sleep
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
void SysClock_Sleep(void)
{
    if(0u != (SysClock_BLOCK_CONTROL_REG & SysClock_MASK))
    {
        SysClock_backup.enableState = 1u;
    }
    else
    {
        SysClock_backup.enableState = 0u;
    }

    SysClock_Stop();
    SysClock_SaveConfig();
}


/*******************************************************************************
* Function Name: SysClock_RestoreConfig
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
void SysClock_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SysClock_Wakeup
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
void SysClock_Wakeup(void)
{
    SysClock_RestoreConfig();

    if(0u != SysClock_backup.enableState)
    {
        SysClock_Enable();
    }
}


/* [] END OF FILE */
