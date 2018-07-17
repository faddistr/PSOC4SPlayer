/*******************************************************************************
* File Name: PWM_TC.h
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
#if !defined(CY_ISR_PWM_TC_H)
#define CY_ISR_PWM_TC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PWM_TC_Start(void);
void PWM_TC_StartEx(cyisraddress address);
void PWM_TC_Stop(void);

CY_ISR_PROTO(PWM_TC_Interrupt);

void PWM_TC_SetVector(cyisraddress address);
cyisraddress PWM_TC_GetVector(void);

void PWM_TC_SetPriority(uint8 priority);
uint8 PWM_TC_GetPriority(void);

void PWM_TC_Enable(void);
uint8 PWM_TC_GetState(void);
void PWM_TC_Disable(void);

void PWM_TC_SetPending(void);
void PWM_TC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PWM_TC ISR. */
#define PWM_TC_INTC_VECTOR            ((reg32 *) PWM_TC__INTC_VECT)

/* Address of the PWM_TC ISR priority. */
#define PWM_TC_INTC_PRIOR             ((reg32 *) PWM_TC__INTC_PRIOR_REG)

/* Priority of the PWM_TC interrupt. */
#define PWM_TC_INTC_PRIOR_NUMBER      PWM_TC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PWM_TC interrupt. */
#define PWM_TC_INTC_SET_EN            ((reg32 *) PWM_TC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PWM_TC interrupt. */
#define PWM_TC_INTC_CLR_EN            ((reg32 *) PWM_TC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PWM_TC interrupt state to pending. */
#define PWM_TC_INTC_SET_PD            ((reg32 *) PWM_TC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PWM_TC interrupt. */
#define PWM_TC_INTC_CLR_PD            ((reg32 *) PWM_TC__INTC_CLR_PD_REG)



#endif /* CY_ISR_PWM_TC_H */


/* [] END OF FILE */
