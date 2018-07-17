/*******************************************************************************
* File Name: audio__NOUT.h  
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

#if !defined(CY_PINS_audio__NOUT_ALIASES_H) /* Pins audio__NOUT_ALIASES_H */
#define CY_PINS_audio__NOUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define audio__NOUT_0			(audio__NOUT__0__PC)
#define audio__NOUT_0_PS		(audio__NOUT__0__PS)
#define audio__NOUT_0_PC		(audio__NOUT__0__PC)
#define audio__NOUT_0_DR		(audio__NOUT__0__DR)
#define audio__NOUT_0_SHIFT	(audio__NOUT__0__SHIFT)
#define audio__NOUT_0_INTR	((uint16)((uint16)0x0003u << (audio__NOUT__0__SHIFT*2u)))

#define audio__NOUT_INTR_ALL	 ((uint16)(audio__NOUT_0_INTR))


#endif /* End Pins audio__NOUT_ALIASES_H */


/* [] END OF FILE */
