/*
 * NVIC.c
 *
 *  Created on: Apr 24, 2024
 *      Author: Le Hung
 */

#include "NVIC.h"

/**
 * @brief Enables a specific interrupt in the Nested Vectored Interrupt Controller (NVIC).
 */
void NVIC_EnableIRQn(IRQn_Type IRQn)
{
	uint8_t  n = 0; /* ISER[n] */
	uint8_t bitPos = 0; /* Bit position of the IRQnumber in the corresponding ISER[n]*/

	/* Find the corresponding Register of IRQnumber*/
	n = IRQn / 32;

	/* Find the bit position*/
	bitPos = IRQn % 32;

	/* Enable IRQ Line*/
	NVIC->ISER[n] |= (1 << bitPos);
}

/**
 * @brief Disables a specific interrupt in the Nested Vectored Interrupt Controller (NVIC).
 */
void NVIC_DisableIRQn(IRQn_Type IRQn)
{
	uint8_t n = 0; 		/* ISER[n] */
	uint8_t bitPos = 0; /* Bit position of the IRQnumber in the corresponding ISER[n]*/

	/* Find the corresponding Register of IRQnumber*/
	n = IRQn / 32;

	/* Find the bit position*/
	bitPos = IRQn % 32;

	/* Disable IRQ Line*/
	NVIC->ICER[n] |= (1 << bitPos);
}

/* ----------------------------------------------------------------------------
   -- End of File
   ---------------------------------------------------------------------------- */
