/*******************************************************************************
* File Name: audio__NOUT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "audio__NOUT.h"

static audio__NOUT_BACKUP_STRUCT  audio__NOUT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: audio__NOUT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet audio__NOUT_SUT.c usage_audio__NOUT_Sleep_Wakeup
*******************************************************************************/
void audio__NOUT_Sleep(void)
{
    #if defined(audio__NOUT__PC)
        audio__NOUT_backup.pcState = audio__NOUT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            audio__NOUT_backup.usbState = audio__NOUT_CR1_REG;
            audio__NOUT_USB_POWER_REG |= audio__NOUT_USBIO_ENTER_SLEEP;
            audio__NOUT_CR1_REG &= audio__NOUT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(audio__NOUT__SIO)
        audio__NOUT_backup.sioState = audio__NOUT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        audio__NOUT_SIO_REG &= (uint32)(~audio__NOUT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: audio__NOUT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to audio__NOUT_Sleep() for an example usage.
*******************************************************************************/
void audio__NOUT_Wakeup(void)
{
    #if defined(audio__NOUT__PC)
        audio__NOUT_PC = audio__NOUT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            audio__NOUT_USB_POWER_REG &= audio__NOUT_USBIO_EXIT_SLEEP_PH1;
            audio__NOUT_CR1_REG = audio__NOUT_backup.usbState;
            audio__NOUT_USB_POWER_REG &= audio__NOUT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(audio__NOUT__SIO)
        audio__NOUT_SIO_REG = audio__NOUT_backup.sioState;
    #endif
}


/* [] END OF FILE */
