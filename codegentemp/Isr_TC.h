/*******************************************************************************
* File Name: Isr_TC.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Isr_TC_H)
#define CY_ISR_Isr_TC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Isr_TC_Start(void);
void Isr_TC_StartEx(cyisraddress address);
void Isr_TC_Stop(void);

CY_ISR_PROTO(Isr_TC_Interrupt);

void Isr_TC_SetVector(cyisraddress address);
cyisraddress Isr_TC_GetVector(void);

void Isr_TC_SetPriority(uint8 priority);
uint8 Isr_TC_GetPriority(void);

void Isr_TC_Enable(void);
uint8 Isr_TC_GetState(void);
void Isr_TC_Disable(void);

void Isr_TC_SetPending(void);
void Isr_TC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Isr_TC ISR. */
#define Isr_TC_INTC_VECTOR            ((reg32 *) Isr_TC__INTC_VECT)

/* Address of the Isr_TC ISR priority. */
#define Isr_TC_INTC_PRIOR             ((reg32 *) Isr_TC__INTC_PRIOR_REG)

/* Priority of the Isr_TC interrupt. */
#define Isr_TC_INTC_PRIOR_NUMBER      Isr_TC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Isr_TC interrupt. */
#define Isr_TC_INTC_SET_EN            ((reg32 *) Isr_TC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Isr_TC interrupt. */
#define Isr_TC_INTC_CLR_EN            ((reg32 *) Isr_TC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Isr_TC interrupt state to pending. */
#define Isr_TC_INTC_SET_PD            ((reg32 *) Isr_TC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Isr_TC interrupt. */
#define Isr_TC_INTC_CLR_PD            ((reg32 *) Isr_TC__INTC_CLR_PD_REG)



#endif /* CY_ISR_Isr_TC_H */


/* [] END OF FILE */
