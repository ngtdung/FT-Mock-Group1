/*
 * HAL_PORT.c
 *
 *  Created on: Apr 24, 2024
 *      Author: adm
 */

#include "PORT.h"

/* ----------------------------------------------------------------------------
   -- Variables
   ---------------------------------------------------------------------------- */
/**
 * @brief Array of base addresses for GPIO port instances.
 *
 * This array holds the base addresses of GPIO port instances indexed by their enum values.
 * The array is initialized with the predefined base addresses of each GPIO port instance.
 */
static PORT_Type *PORT_Base_Addr[PORT_INSTANCE_COUNT] = IP_PORT_BASE_PTRS;

/**
 * @brief Array of PCC (Peripheral Clock Control) indices for GPIO port instances.
 *
 * This array holds the PCC indices corresponding to GPIO port instances indexed by their enum values.
 * The array is initialized with the predefined PCC indices for each GPIO port instance.
 */
static uint8_t PCC_PORT[PORT_INSTANCE_COUNT] = PCC_PORT_Index;

/**
 * @brief Array of NVIC interrupt numbers for PORT instances.
 *
 * This array holds the NVIC interrupt numbers corresponding to PORT instances.
 * Each element corresponds to a specific PORT instance identified by an index.
 * The array is used to configure NVIC interrupts for PORTs.
 */
static uint8_t NVIC_PORT[PORT_INSTANCE_COUNT] = NVIC_PORT_IRQ;

/* ----------------------------------------------------------------------------
   -- Code
   ---------------------------------------------------------------------------- */
/**
 * @brief Initializes a GPIO port pin with the specified configuration.
 */
void PORT_Init(PORT_Instance_e PORT_Instance, GPIO_PinNumber_e pinNumber, const PORT_Config_t *PORTConfig)
{
	PORT_Type *PORTx = PORT_Base_Addr[PORT_Instance];
	uint8_t PCCPORTindex = PCC_PORT[PORT_Instance];

	/* Enable PORT Clock */
	IP_PCC->PCCn[PCCPORTindex] |= PCC_PCCn_CGC(1);

	/* Modify MUX Field */
	PORTx->PCR[pinNumber] &= ~PORT_PCR_MUX_MASK;
	PORTx->PCR[pinNumber] |= PORT_PCR_MUX(PORTConfig->MUX);

	/* Pull configuration*/
	if(PORTConfig->PUPDControl == NOPULL)
	{
		/* Disable Pull*/
		PORTx->PCR[pinNumber] &= ~PORT_PCR_PE_MASK;
	}
	else
	{
		/* Enable Pull-up or Pull-down*/
		PORTx->PCR[pinNumber] |= PORT_PCR_PE(1);
		PORTx->PCR[pinNumber] &= ~PORT_PCR_PS_MASK;
		PORTx->PCR[pinNumber] |= PORT_PCR_PS(PORTConfig->PUPDControl);
	}

	/* Interrupt configuration */
	PORTx->PCR[pinNumber] &= ~PORT_PCR_IRQC_MASK;
	PORTx->PCR[pinNumber] |= PORT_PCR_IRQC(PORTConfig->InterruptConfig);

	if(PORTConfig->InterruptConfig > IntDisable)
	{
		NVIC_EnableIRQn(NVIC_PORT[PORT_Instance]);
	}
	else
	{
		NVIC_DisableIRQn(NVIC_PORT[PORT_Instance]);
	}
}

void PORT_DeInit(PORT_Instance_e PORT_Instance)
{
	/* Disable PORT Clock */
	IP_PCC->PCCn[PCC_PORT[PORT_Instance]] &= ~PCC_PCCn_CGC(0x1);
}

/* ----------------------------------------------------------------------------
   -- End of File
   ---------------------------------------------------------------------------- */
