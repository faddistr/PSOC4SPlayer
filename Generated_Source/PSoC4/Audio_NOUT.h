/*******************************************************************************
* File Name: audio__NOUT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_audio__NOUT_H) /* Pins audio__NOUT_H */
#define CY_PINS_audio__NOUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "audio__NOUT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} audio__NOUT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   audio__NOUT_Read(void);
void    audio__NOUT_Write(uint8 value);
uint8   audio__NOUT_ReadDataReg(void);
#if defined(audio__NOUT__PC) || (CY_PSOC4_4200L) 
    void    audio__NOUT_SetDriveMode(uint8 mode);
#endif
void    audio__NOUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   audio__NOUT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void audio__NOUT_Sleep(void); 
void audio__NOUT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(audio__NOUT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define audio__NOUT_DRIVE_MODE_BITS        (3)
    #define audio__NOUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - audio__NOUT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the audio__NOUT_SetDriveMode() function.
         *  @{
         */
        #define audio__NOUT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define audio__NOUT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define audio__NOUT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define audio__NOUT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define audio__NOUT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define audio__NOUT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define audio__NOUT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define audio__NOUT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define audio__NOUT_MASK               audio__NOUT__MASK
#define audio__NOUT_SHIFT              audio__NOUT__SHIFT
#define audio__NOUT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in audio__NOUT_SetInterruptMode() function.
     *  @{
     */
        #define audio__NOUT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define audio__NOUT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define audio__NOUT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define audio__NOUT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(audio__NOUT__SIO)
    #define audio__NOUT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(audio__NOUT__PC) && (CY_PSOC4_4200L)
    #define audio__NOUT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define audio__NOUT_USBIO_DISABLE              ((uint32)(~audio__NOUT_USBIO_ENABLE))
    #define audio__NOUT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define audio__NOUT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define audio__NOUT_USBIO_ENTER_SLEEP          ((uint32)((1u << audio__NOUT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << audio__NOUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define audio__NOUT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << audio__NOUT_USBIO_SUSPEND_SHIFT)))
    #define audio__NOUT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << audio__NOUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define audio__NOUT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(audio__NOUT__PC)
    /* Port Configuration */
    #define audio__NOUT_PC                 (* (reg32 *) audio__NOUT__PC)
#endif
/* Pin State */
#define audio__NOUT_PS                     (* (reg32 *) audio__NOUT__PS)
/* Data Register */
#define audio__NOUT_DR                     (* (reg32 *) audio__NOUT__DR)
/* Input Buffer Disable Override */
#define audio__NOUT_INP_DIS                (* (reg32 *) audio__NOUT__PC2)

/* Interrupt configuration Registers */
#define audio__NOUT_INTCFG                 (* (reg32 *) audio__NOUT__INTCFG)
#define audio__NOUT_INTSTAT                (* (reg32 *) audio__NOUT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define audio__NOUT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(audio__NOUT__SIO)
    #define audio__NOUT_SIO_REG            (* (reg32 *) audio__NOUT__SIO)
#endif /* (audio__NOUT__SIO_CFG) */

/* USBIO registers */
#if !defined(audio__NOUT__PC) && (CY_PSOC4_4200L)
    #define audio__NOUT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define audio__NOUT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define audio__NOUT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define audio__NOUT_DRIVE_MODE_SHIFT       (0x00u)
#define audio__NOUT_DRIVE_MODE_MASK        (0x07u << audio__NOUT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins audio__NOUT_H */


/* [] END OF FILE */
