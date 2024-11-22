/*
 * MIDDLE_FLexCAN.h
 *
 *  Created on: Nov 4, 2024
 *      Author: adm
 */

#ifndef INCLUDE_MIDDLE_FLEXCAN_H_
#define INCLUDE_MIDDLE_FLEXCAN_H_

#include "FlexCAN.h"

typedef enum
{
	/* Defines for MBx callback */
	MIDDLE_HANDLER_MB_0_TYPE		= 0U,
	MIDDLE_HANDLER_MB_1_TYPE,
	MIDDLE_HANDLER_MB_2_TYPE,
	MIDDLE_HANDLER_MB_3_TYPE,
	MIDDLE_HANDLER_MB_4_TYPE,
	MIDDLE_HANDLER_MB_5_TYPE,
	MIDDLE_HANDLER_MB_6_TYPE,
	MIDDLE_HANDLER_MB_7_TYPE,
	MIDDLE_HANDLER_MB_8_TYPE,
	MIDDLE_HANDLER_MB_9_TYPE,
	MIDDLE_HANDLER_MB_10_TYPE,
	MIDDLE_HANDLER_MB_11_TYPE,
	MIDDLE_HANDLER_MB_12_TYPE,
	MIDDLE_HANDLER_MB_13_TYPE,
	MIDDLE_HANDLER_MB_14_TYPE,
	MIDDLE_HANDLER_MB_15_TYPE,
	MIDDLE_HANDLER_MB_16_TYPE,
	MIDDLE_HANDLER_MB_17_TYPE,
	MIDDLE_HANDLER_MB_18_TYPE,
	MIDDLE_HANDLER_MB_19_TYPE,
	MIDDLE_HANDLER_MB_20_TYPE,
	MIDDLE_HANDLER_MB_21_TYPE,
	MIDDLE_HANDLER_MB_22_TYPE,
	MIDDLE_HANDLER_MB_23_TYPE,
	MIDDLE_HANDLER_MB_24_TYPE,
	MIDDLE_HANDLER_MB_25_TYPE,
	MIDDLE_HANDLER_MB_26_TYPE,
	MIDDLE_HANDLER_MB_27_TYPE,
	MIDDLE_HANDLER_MB_28_TYPE,
	MIDDLE_HANDLER_MB_29_TYPE,
	MIDDLE_HANDLER_MB_30_TYPE,
	MIDDLE_HANDLER_MB_31_TYPE,

	/* Defines for ERROR and ORED callback*/
	MIDDLE_HANDLER_ERROR_TYPE,
	MIDDLE_HANDLER_ORED_TYPE
}Middle_FlexCAN_Handler_e;

typedef enum
{
	MODULE_0_INS	= FlexCAN0_INS,
	MODULE_1_INS	= FlexCAN1_INS,
	MODULE_2_INS	= FlexCAN2_INS
}Middle_CAN_ModuleIns_e;

typedef struct
{
	FlexCAN_MbIndex_e 			MbIndex;
	uint32_t 					MbID;
	bool						MbInt;
	FlexCAN_CallbackType 		HandlerFunc;
	Middle_FlexCAN_Handler_e 	HandlerType;
}Middle_CAN_UserConfigType;

void Middle_FlexCAN_Init(Middle_CAN_ModuleIns_e Ins);
void Middle_FlexCAN_DeInit(Middle_CAN_ModuleIns_e Ins);
void Middle_FlexCAN_SetCallback(Middle_CAN_ModuleIns_e Ins, Middle_CAN_UserConfigType *UserConfig);
void Middle_FlexCAN_StandardTransmitMbInit(Middle_CAN_ModuleIns_e Ins, Middle_CAN_UserConfigType *UserConfig);
void Middle_FlexCAN_StandardReceiveMbInit(Middle_CAN_ModuleIns_e Ins, Middle_CAN_UserConfigType *UserConfig);
void Middle_CAN_Transmit(Middle_CAN_ModuleIns_e Ins, FlexCAN_MbIndex_e MbIndex, uint8_t *TxBuffer);
void Middle_CAN_Receive(Middle_CAN_ModuleIns_e Ins, FlexCAN_MbIndex_e MbIndex, uint8_t *RxBuffer);
uint8_t Middle_FlexCAN_GetAckStatus(Middle_CAN_ModuleIns_e Ins);

#endif /* INCLUDE_MIDDLE_FLEXCAN_H_ */
