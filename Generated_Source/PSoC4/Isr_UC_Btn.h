/*******************************************************************************
* File Name: Isr_UC_Btn.h
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
#if !defined(CY_ISR_Isr_UC_Btn_H)
#define CY_ISR_Isr_UC_Btn_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Isr_UC_Btn_Start(void);
void Isr_UC_Btn_StartEx(cyisraddress address);
void Isr_UC_Btn_Stop(void);

CY_ISR_PROTO(Isr_UC_Btn_Interrupt);

void Isr_UC_Btn_SetVector(cyisraddress address);
cyisraddress Isr_UC_Btn_GetVector(void);

void Isr_UC_Btn_SetPriority(uint8 priority);
uint8 Isr_UC_Btn_GetPriority(void);

void Isr_UC_Btn_Enable(void);
uint8 Isr_UC_Btn_GetState(void);
void Isr_UC_Btn_Disable(void);

void Isr_UC_Btn_SetPending(void);
void Isr_UC_Btn_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Isr_UC_Btn ISR. */
#define Isr_UC_Btn_INTC_VECTOR            ((reg32 *) Isr_UC_Btn__INTC_VECT)

/* Address of the Isr_UC_Btn ISR priority. */
#define Isr_UC_Btn_INTC_PRIOR             ((reg32 *) Isr_UC_Btn__INTC_PRIOR_REG)

/* Priority of the Isr_UC_Btn interrupt. */
#define Isr_UC_Btn_INTC_PRIOR_NUMBER      Isr_UC_Btn__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Isr_UC_Btn interrupt. */
#define Isr_UC_Btn_INTC_SET_EN            ((reg32 *) Isr_UC_Btn__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Isr_UC_Btn interrupt. */
#define Isr_UC_Btn_INTC_CLR_EN            ((reg32 *) Isr_UC_Btn__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Isr_UC_Btn interrupt state to pending. */
#define Isr_UC_Btn_INTC_SET_PD            ((reg32 *) Isr_UC_Btn__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Isr_UC_Btn interrupt. */
#define Isr_UC_Btn_INTC_CLR_PD            ((reg32 *) Isr_UC_Btn__INTC_CLR_PD_REG)



#endif /* CY_ISR_Isr_UC_Btn_H */


/* [] END OF FILE */
