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
	MIDDLE_HANDLER_ERROR_TYPE		= 0U,
	MIDDLE_HANDLER_ORED_TYPE		= 1U,
	MIDDLE_HANDLER_0_15_MB_TYPE		= 2U,
	MDDILE_HANDLER_16_31_MB_TYPE	= 3U
}Middle_FlexCAN_Handler_e;

void Middle_FlexCAN_Init(FlexCAN_Instance_e Ins);
void Middle_FlexCAN_DeInit(FlexCAN_Instance_e Ins);
void Middle_FlexCAN_SetCallback(FlexCAN_Instance_e Ins, Middle_FlexCAN_Handler_e HandlerType, FlexCAN_CallbackType HandlerFunc);


#endif /* INCLUDE_MIDDLE_FLEXCAN_H_ */
