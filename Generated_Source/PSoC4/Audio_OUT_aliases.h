/*******************************************************************************
* File Name: Audio_OUT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Audio_OUT_ALIASES_H) /* Pins Audio_OUT_ALIASES_H */
#define CY_PINS_Audio_OUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Audio_OUT_0			(Audio_OUT__0__PC)
#define Audio_OUT_0_PS		(Audio_OUT__0__PS)
#define Audio_OUT_0_PC		(Audio_OUT__0__PC)
#define Audio_OUT_0_DR		(Audio_OUT__0__DR)
#define Audio_OUT_0_SHIFT	(Audio_OUT__0__SHIFT)
#define Audio_OUT_0_INTR	((uint16)((uint16)0x0003u << (Audio_OUT__0__SHIFT*2u)))

#define Audio_OUT_INTR_ALL	 ((uint16)(Audio_OUT_0_INTR))


#endif /* End Pins Audio_OUT_ALIASES_H */


/* [] END OF FILE */
