/*
 * MIDDLE_FlexCAN.c
 *
 *  Created on: Nov 4, 2024
 *      Author: adm
 */

#include "MIDDLE_FLexCAN.h"
#include "CLOCK.h"
#include "PORT.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */
/**
 * Array of PORT for instances FLEXCAN modules. Indexed by FLEXCAN instance number.
 */
#define FLEXCAN_PORT_INSTANCE { PORTE_Instance, PORTC_Instance, PORTB_Instance }

/**
 * PCC (Peripheral Clock Controller) indices for each FLEXCAN instance.
 */
#define PCC_FLEXCAN_Index { PCC_FlexCAN0_INDEX, PCC_FlexCAN1_INDEX, PCC_FlexCAN2_INDEX }

/**
 * PCC (Peripheral Clock Controller) indices for each FLEXCAN instance.
 */
#define FLEXCAN_MUX_Index { ALT5, ALT3, ALT4 }

#define FLEXCAN_MB_BASE_PTR { MB_FLEXCAN_0, MB_FLEXCAN_1, MB_FLEXCAN_2 }

/**
 * NVIC (Nested Vector Interrupt Controller) indices for LPUART receive and transmit interrupts.
 * Each entry corresponds to an LPUART instance's Rx/Tx interrupt number.
 */
#define NVIC_FLEXCAN_Index { CAN0_ORed_IRQn, CAN0_Error_IRQn, CAN1_ORed_IRQn, CAN1_Error_IRQn, CAN2_ORed_IRQn, CAN2_Error_IRQn }

#define NVIC_FLEXCAN_COUNT	6U

#define FLEXCAN_GET_FREQ(ClkSrc) \
		((ClkSrc == FlexCAN_CLKSRC_SYS) ? SCG_GetSysFreq() :\
		 (ClkSrc == FlexCAN_CLKSRC_OSC) ? 40000000U 	   : 0)

/* ----------------------------------------------------------------------------
   -- Variables
   ---------------------------------------------------------------------------- */
/**
 * PCC (Peripheral Clock Controller) indices for FLEXCAN instances.
 * @note This array is indexed by LPUART instance numbers.
 */
static uint8_t PCC_FlexCAN[FLEXCAN_INSTANCE_COUNT] = PCC_FLEXCAN_Index;

static uint8_t FlexCAN_PORT[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_PORT_INSTANCE;

static uint8_t FlexCAN_MUX[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_MUX_Index;

static FlexCAN_MbType *FlexCAN_MB[FLEXCAN_INSTANCE_COUNT]  = FLEXCAN_MB_BASE_PTR;

/**
 * Array to map FLEXCAN instances to their corresponding NVIC IRQ numbers.
 *
 * This array holds the NVIC IRQ numbers corresponding to each FLEXCAN instance.
 * @note This array is indexed by FLEXCAN instance numbers.
 */
static IRQn_Type NVIC_FLEXCAN[NVIC_FLEXCAN_COUNT]	= NVIC_FLEXCAN_Index;

/* ----------------------------------------------------------------------------
   -- Private functions
   ---------------------------------------------------------------------------- */

static void FlexCAN_PORT_Init(FlexCAN_Instance_e Ins, FlexCAN_PinType PortPin);
static void FlexCAN_NVIC_Control(FlexCAN_Instance_e Ins, FlexCAN_InterruptType IntControl);

/* ----------------------------------------------------------------------------
   -- Global functions
   ---------------------------------------------------------------------------- */
void Middle_FlexCAN_Init(FlexCAN_Instance_e Ins)
{
	FlexCAN_ConfigType FlexCANConfig;

	/* Configuration elements for FlexCAN module */
	FlexCANConfig.BitRate = 500000;
	FlexCANConfig.CLkSrc = FlexCAN_CLKSRC_SYS;
	FlexCANConfig.IntControl.IntError = FlexCAN_INT_ERROR_ENABLE;
	FlexCANConfig.PortPin.TxPin = FlexCAN0_Tx;
	FlexCANConfig.PortPin.RxPin = FlexCAN0_Rx;
	FlexCANConfig.RunMode = FlexCAN_MODE_LOOPBACK;
	FlexCANConfig.ClkFreq = FLEXCAN_GET_FREQ(FlexCANConfig.CLkSrc);

	/* PORT initialization */
	FlexCAN_PORT_Init(Ins, FlexCANConfig.PortPin);

	/* Enable clock for FlexCANx */
	PCC_PeriClockControl(PCC_FlexCAN[Ins], ENABLE);

	/* NVIC IRQ line configuration for FlexCAN interrupts */
	FlexCAN_NVIC_Control(Ins, FlexCANConfig.IntControl);

	/* Initializes FlexCAN driver */
	FlexCAN_Init(Ins, &FlexCANConfig);
}

void Middle_FlexCAN_DeInit(FlexCAN_Instance_e Ins)
{

	/* Deinit FlexCAN Driver */
	FlexCAN_DeInit(Ins);

	/* Disable FlexCAN clock */
	PCC_PeriClockControl(PCC_FlexCAN[Ins], DISABLE);

	/* Disable FlexCAN PORT clock */
	PCC_PeriClockControl(FlexCAN_PORT[Ins], DISABLE);
}

void Middle_FlexCAN_SetCallback(FlexCAN_Instance_e Ins, Middle_FlexCAN_Handler_e HandlerType, FlexCAN_CallbackType HandlerFunc)
{
	uint8_t CallbackID = 0U;

	CallbackID = HandlerType;

	FlexCAN_CallbackRegister(Ins, HandlerFunc, CallbackID);
}

/* ----------------------------------------------------------------------------
   -- Private functions
   ---------------------------------------------------------------------------- */

static void FlexCAN_PORT_Init(FlexCAN_Instance_e Ins, FlexCAN_PinType PortPin)
{
	PORT_Config_t	   PORTConfig;

	/* PORT Initialization for FlexCANx */
	PORTConfig.MUX = FlexCAN_MUX[Ins];
	PORT_Init(FlexCAN_PORT[Ins], PortPin.TxPin, &PORTConfig);
	PORT_Init(FlexCAN_PORT[Ins], PortPin.RxPin, &PORTConfig);
}

static void FlexCAN_NVIC_Control(FlexCAN_Instance_e Ins, FlexCAN_InterruptType IntControl)
{
	/* Error Interrupt NVIC configuration */
	if(IntControl.IntError == FlexCAN_INT_ERROR_ENABLE)
	{
	   /* Enable corresponding NVIC IRQ line */
	   NVIC_EnableIRQn(NVIC_FLEXCAN[(Ins*2U) + 1U]);
	}
	else
	{
	   /* Disable corresponding NVIC IRQ line */
	   NVIC_DisableIRQn(NVIC_FLEXCAN[(Ins*2U) + 1U]);
	}

	/* ORed Interrupt NVIC configuration */
	if((IntControl.IntBusOff | IntControl.IntRxWarning | IntControl.IntTxWarning) == ENABLE)
	{
	   /* Enable corresponding NVIC IRQ line */
	   NVIC_EnableIRQn(NVIC_FLEXCAN[Ins*2U]);
	}
	else
	{
	   /* Enable corresponding NVIC IRQ line */
	   NVIC_DisableIRQn(NVIC_FLEXCAN[Ins*2U]);
	}
}


