/*
 * MIDDLE_FLexCAN.h
 *
 *  Created on: Nov 4, 2024
 *      Author: adm
 */

#ifndef INCLUDE_MIDDLE_FLEXCAN_H_
#define INCLUDE_MIDDLE_FLEXCAN_H_

#include "FlexCAN.h"

void MIDDLE_FlexCAN_Init(FlexCAN_Instance_e Ins);
void MIDDLE_FlexCAN_DeInit(FlexCAN_Instance_e Ins);
void MIDDLE_FlexCAN_SetCallback(FlexCAN_Instance_e Ins);

#endif /* INCLUDE_MIDDLE_FLEXCAN_H_ */
