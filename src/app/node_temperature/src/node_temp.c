/*
 * node_temp.c
 *
 *  Created on: Nov 18, 2024
 *      Author: Manh
 */

/******************************************************************************/
/* Includes */
/******************************************************************************/

#include "node_temp.h"

/******************************************************************************/
/* Variables */
/******************************************************************************/

uint8_t MsgDataTemp[2] = "OK";
Temp_Ping_State_t Temp_Ping_State = TEMP_PING_NOT_READY;
Temp_Connect_State_t Temp_Connect_State = TEMP_OK;
uint8_t Temp_value = 0;

/******************************************************************************/
/* Local APIs */
/******************************************************************************/

static void App_Read_Send_Temp_Data(void)
{
	Temp_value = MID_ADC_ReadData();
	Middle_CAN_Transmit(FlexCAN0_INS, MB0, &Temp_value);
}


static void App_ProcessTempPing(Temp_Ping_State_t* State)
{
	if(*State == TEMP_PING_READY)
	{
		FlexCAN_Transmit(FlexCAN0_INS, MB1, MsgDataTemp);
		*State = TEMP_PING_NOT_READY;
	}
}

static void App_CheckTempConnect(void)
{
	uint8_t ACK_State = 0;
	ACK_State = Middle_FlexCAN_GetAckStatus(MODULE_0_INS);
	if(ACK_State == 1)
	{
		Temp_Connect_State = TEMP_NOT_OK;
	}
}

static void App_TempReconnect(void)
{
	uint8_t ACK_State = 0;
	ACK_State = Middle_FlexCAN_GetAckStatus(MODULE_0_INS);
	if(Temp_Connect_State == TEMP_NOT_OK  && ACK_State == 0)
	{
		App_Read_Send_Temp_Data();
		Temp_Connect_State = TEMP_OK;
	}
}

/******************************************************************************/
/* CallBack APIs */
/******************************************************************************/

void App_Temp_ADC_Notification(uint16_t x)
{
	FlexCAN_Transmit(FlexCAN0_INS, MB0, (uint8_t *)&x);
}

Node_Config_Data_Struct_type Node_Temp_Cfg =
	{
		.nodeType = NODE_TYPE_TEMPERATURE,
		.threshold = 1};

MID_ADC_ConfigStruct_type ADC_Cfg_Temp =
	{
		.adcHwUnitId = IP_ADC0,
		.channel = ADC_CHANNEL_12,
		.nodeConfigPtr = &Node_Temp_Cfg,
		.callback = App_Temp_ADC_Notification};

void LPIT_Callback_Temp(uint8_t channel)
{
	switch (channel)
	{
	case 0:
		Temp_Ping_State = TEMP_PING_READY;
		break;
	default:
		break;
	}
}

void App_Temp_RcvRequest(void)
{
	App_Read_Send_Temp_Data();
}

/******************************************************************************/
/* Public APIs */
/******************************************************************************/

void App_NodeTemp_Run()
{
	MID_ADC_Init(&ADC_Cfg_Temp);
	MID_LPIT_Init(LPIT_INS_0, LPIT_Callback_Temp);
	Middle_FlexCAN_Init(FlexCAN0_INS);
	Middle_CAN_UserConfigType UserCfgMBSendData = {
			.HandlerFunc = NULL,
			.MbID = 0x11,
			.MbIndex = MB0,
			.MbInt = true
	};

	Middle_CAN_UserConfigType UserCfgMBSendPing = {
			.HandlerFunc = NULL,
			.MbID = 0x33,
			.MbIndex = MB1,
			.MbInt = true
	};

	Middle_FlexCAN_StandardTransmitMbInit(FlexCAN0_INS, &UserCfgMBSendData);
	Middle_FlexCAN_StandardTransmitMbInit(FlexCAN0_INS, &UserCfgMBSendPing);

	Middle_CAN_UserConfigType UserCfgMBRequest = {
			.HandlerFunc = App_Temp_RcvRequest,
			.HandlerType = MIDDLE_HANDLER_MB_2_TYPE,
			.MbID = 0x55,
			.MbIndex = MB2,
			.MbInt = true
	};
	Middle_FlexCAN_StandardReceiveMbInit(FlexCAN0_INS, &UserCfgMBRequest);
	Middle_FlexCAN_SetCallback(FlexCAN0_INS, &UserCfgMBRequest);

	MID_LPIT_StartTimer(LPIT_INS_0, 0, 6000000);

	App_Read_Send_Temp_Data();
	while (1)
	{
		App_ProcessTempPing(&Temp_Ping_State);
		App_CheckTempConnect();
		App_TempReconnect();
	}
}
