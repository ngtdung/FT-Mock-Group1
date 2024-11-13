/*
 * FlexCAN.h
 *
 *  Created on: Oct 23, 2024
 *      Author: adm
 */

#ifndef FLEXCAN_H_
#define FLEXCAN_H_

#include "Driver_Header.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */
#define NUMBER_OF_HANDLER_TYPE		4U

#define FLEXCAN_RAMn_DATA_WORD_0_EDL_MASK			(0x80000000U)
#define FLEXCAN_RAMn_DATA_WORD_0_EDL_SHIFT			(31U)
#define FLEXCAN_RAMn_DATA_WORD_0_EDL(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_EDL_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_EDL_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_BRS_MASK			(0x40000000U)
#define FLEXCAN_RAMn_DATA_WORD_0_BRS_SHIFT			(30U)
#define FLEXCAN_RAMn_DATA_WORD_0_BRS(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_BRS_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_BRS_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_ESI_MASK			(0x20000000U)
#define FLEXCAN_RAMn_DATA_WORD_0_ESI_SHIFT			(29U)
#define FLEXCAN_RAMn_DATA_WORD_0_ESI(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_ESI_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_ESI_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK			(0xF000000U)
#define FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT			(24U)
#define FLEXCAN_RAMn_DATA_WORD_0_CODE(x)    		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_SRR_MASK   		(0x400000U)
#define FLEXCAN_RAMn_DATA_WORD_0_SRR_SHIFT  		(22U)
#define FLEXCAN_RAMn_DATA_WORD_0_SRR(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_SRR_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_SRR_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_IDE_MASK   		(0x200000U)
#define FLEXCAN_RAMn_DATA_WORD_0_IDE_SHIFT  		(21U)
#define FLEXCAN_RAMn_DATA_WORD_0_IDE(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_IDE_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_IDE_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_RTR_MASK   		(0x100000U)
#define FLEXCAN_RAMn_DATA_WORD_0_RTR_SHIFT  		(20U)
#define FLEXCAN_RAMn_DATA_WORD_0_RTR(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_RTR_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_RTR_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_DLC_MASK   		(0xF0000U)
#define FLEXCAN_RAMn_DATA_WORD_0_DLC_SHIFT  		(16U)
#define FLEXCAN_RAMn_DATA_WORD_0_DLC(x)     		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_DLC_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_DLC_MASK)

#define FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_MASK   	(0x7FFFU)
#define FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_SHIFT  	(0U)
#define FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP(x)     	(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_MASK)

#define FLEXCAN_RAMn_DATA_WORD_1_ID_MASK    		(0x1FFC0000U)
#define FLEXCAN_RAMn_DATA_WORD_1_ID_SHIFT   		(18U)
#define FLEXCAN_RAMn_DATA_WORD_1_ID(x)      		(((uint32_t)(((uint32_t)(x)) << FLEXCAN_RAMn_DATA_WORD_1_ID_SHIFT)) & FLEXCAN_RAMn_DATA_WORD_1_ID_MASK)

typedef void (*FlexCAN_CallbackType)(void);

/* Structures and enums for CAN configuration */
typedef enum
{
    FlexCAN0_Ins = 0U,
    FlexCAN1_Ins = 1U,
    FlexCAN2_Ins = 2U,
}FlexCAN_Instance_e;

typedef enum
{
	FlexCAN0_Tx	= 5U,
	FlexCAN1_Tx	= 7U,
	FlexCAN2_Tx	= 13U
}FlexCAN_TxPin_e;

typedef enum
{
	FlexCAN0_Rx	= 4U,
	FlexCAN1_Rx	= 6U,
	FlexCAN2_Rx	= 12U
}FlexCAN_RxPin_e;

typedef enum
{
	FlexCAN_MODE_NORMAL 	= 0U,
	FlexCAN_MODE_LOOPBACK	= 1U
}FlexCAN_Mode_e;

typedef enum
{
	FlexCAN_CLKSRC_SYS		= 1U,
	FlexCAN_CLKSRC_OSC		= 0U
}FlexCAN_ClkSrc_e;

typedef enum
{
	FlexCAN_MB_TX	= 0U,
	FlexCAN_MB_RX	= 1U
}FlexCAN_MbType_e;

typedef enum
{
	FlexCAN_INT_BUSOFF_DISABLE  = 0U,
	FlexCAN_INT_BUSOFF_ENABLE	= 1U
}FlexCAN_IntBusOff_e;

typedef enum
{
	FlexCAN_INT_ERROR_DISABLE  	= 0U,
	FlexCAN_INT_ERROR_ENABLE	= 1U
}FlexCAN_IntError_e;

typedef enum
{
	FlexCAN_INT_TxWARNING_DISABLE  	= 0U,
	FlexCAN_INT_TxWARNING_ENABLE	= 1U
}FlexCAN_IntTxWarning_e;

typedef enum
{
	FlexCAN_INT_RxWARNING_DISABLE  	= 0U,
	FlexCAN_INT_RxWARNING_ENABLE	= 1U
}FlexCAN_IntRxWarning_e;

typedef struct
{
	FlexCAN_IntBusOff_e		IntBusOff;
	FlexCAN_IntError_e		IntError;
	FlexCAN_IntTxWarning_e	IntTxWarning;
	FlexCAN_IntRxWarning_e	IntRxWarning;
}FlexCAN_InterruptType;

typedef enum
{
	Rx_CODE_INACTIVE		= 0U,
	Rx_CODE_EMPTY			= 4U,
	Rx_CODE_FULL			= 2U,
	Rx_CODE_OVERRUN			= 6U,
	Rx_CODE_RANSWER			= 10U,
	Rx_CODE_BUSY			= 1U
}FlexCAN_RxCODE_e;

typedef enum
{
	Tx_CODE_INACTIVE		= 8U,
	Tx_CODE_ABORT			= 9U,
	Tx_CODE_DATA			= 12U,
	Tx_CODE_REMOTE			= 12U,
	Tx_CODE_TANSWER			= 14U,
}FlexCAN_TxCODE_e;

typedef enum
{
    MB0 = 0U,
    MB1,
    MB2,
    MB3,
    MB4,
    MB5,
    MB6,
    MB7,
    MB8,
    MB9,
    MB10,
    MB11,
    MB12,
    MB13,
    MB14,
    MB15,
    MB16,
    MB17,
    MB18,
    MB19,
    MB20,
    MB21,
    MB22,
    MB23,
    MB24,
    MB25,
    MB26,
    MB27,
    MB28,
    MB29,
    MB30,
    MB31
} FlexCAN_MbIndex_e;

typedef enum
{
	FLEXCAN_STATE_UNINIT		= 0U,
	FLEXCAN_STATE_READY		= 1U,
	FLEXCAN_STATE_STARTED		= 2U
} FlexCAN_State_e;

typedef struct
{
	FlexCAN_TxPin_e			TxPin;
	FlexCAN_RxPin_e			RxPin;
}FlexCAN_PinType;


typedef struct
{
	uint32_t 				BitRate;
	uint32_t 				ClkFreq;
	FlexCAN_Mode_e			RunMode;
	FlexCAN_ClkSrc_e		CLkSrc;
	FlexCAN_PinType			PortPin;
	FlexCAN_InterruptType	IntControl;
}FlexCAN_ConfigType;

typedef enum{
	FlexCAN_STANDARD = 0U,
	FlexCAN_EXT = 1U
}FlexCAN_MsgIDType_e;

typedef struct
{
	uint8_t 			EDL;
	uint8_t 			BRS;
	uint8_t 			ESI;
	FlexCAN_MbType_e	MbType;
	FlexCAN_MsgIDType_e IdType;
	bool				IsRemote;
	uint8_t				DataLen;
	uint16_t 			MbID;
	bool				IsEnableMbInt;
}FlexCAN_MbHeaderType;

typedef struct
{
	uint32_t 			Header[2];
	uint32_t 			Payload[2];
}FlexCAN_MbStructureType;

typedef struct
{
	FlexCAN_MbStructureType	MB[32];
}FlexCAN_MbType;

#define	MB_FLEXCAN_0	((FlexCAN_MbType*)0x40024080U)
#define MB_FLEXCAN_1	((FlexCAN_MbType*)0x40025080U)
#define MB_FLEXCAN_2	((FlexCAN_MbType*)0x4002B080U)

void FlexCAN_MbInit(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex, FlexCAN_MbHeaderType *FLexCAN_MbConfig);
void FlexCAN_Init(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_ConfigType *FlexCAN_Config);
void FlexCAN_DeInit(FlexCAN_Instance_e FlexCAN_Ins);
void FlexCAN_Transmit(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex, uint8_t * MsgData);
void FlexCAN_ReadMailboxData(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex, uint8_t * MsgData);
void FlexCAN_CallbackRegister(FlexCAN_Instance_e Ins, FlexCAN_CallbackType CallbackFunc, uint8_t CallbackID);
FlexCAN_State_e FlexCAN_GetModuleState(FlexCAN_Instance_e Ins);

#endif /* FLEXCAN_H_ */
