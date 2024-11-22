/*
 * node_speed.c
 *
 *  Created on: Nov 18, 2024
 *      Author: Manh
 */

/******************************************************************************/
/* Includes */
/******************************************************************************/

#include "node_speed.h"

/******************************************************************************/
/* Variables */
/******************************************************************************/

uint8_t MsgDataSpeed[2] = "OK";
uint8_t value = 0;
Speed_Ping_State_t Speed_Ping_State = SPEED_PING_NOT_READY;
Speed_Connect_State_t Speed_Connect_State = SPEED_OK;
/******************************************************************************/
/* Static APIs */
/******************************************************************************/

static void App_Read_Send_Speed_Data(void)
{
	value = MID_ADC_ReadData();
	Middle_CAN_Transmit(FlexCAN0_INS, MB0, &value);
}

static void App_ProcessSpeedPing(Speed_Ping_State_t* State)
{
	if(*State == SPEED_PING_READY)
	{
		Middle_CAN_Transmit(FlexCAN0_INS, MB1, MsgDataSpeed);
		*State = SPEED_PING_NOT_READY;
	}
}

static void App_CheckSpeedConnect()
{
	uint8_t ACK_State = 0;
	ACK_State = Middle_FlexCAN_GetAckStatus(MODULE_0_INS);
	if(ACK_State == 1)
	{
		Speed_Connect_State = SPEED_NOT_OK;
	}
}

static void App_SpeedReconnect(void)
{
	uint8_t ACK_State = 0;
	ACK_State = Middle_FlexCAN_GetAckStatus(MODULE_0_INS);
	if(Speed_Connect_State == SPEED_NOT_OK  && ACK_State == 0)
	{
		App_Read_Send_Speed_Data();
		Speed_Connect_State = SPEED_OK;
	}
}

/******************************************************************************/
/* CallBack APIs */
/******************************************************************************/

void App_Speed_ADC_Notification(uint16_t x)
{
	Middle_CAN_Transmit(FlexCAN0_INS, MB0, (uint8_t *)&x);
}

Node_Config_Data_Struct_type Node_Speed_Cfg =
	{
		.nodeType = NODE_TYPE_SPEEED,
		.threshold = 1};

MID_ADC_ConfigStruct_type ADC_Cfg_Speed =
	{
		.adcHwUnitId = IP_ADC0,
		.channel = ADC_CHANNEL_12,
		.nodeConfigPtr = &Node_Speed_Cfg,
		.callback = App_Speed_ADC_Notification};

void LPIT_Callback_Speed(uint8_t channel)
{
	switch (channel)
	{
	case 0:
		Speed_Ping_State = SPEED_PING_READY;
		break;
	default:
		break;
	}
}

void App_Speed_RcvRequest(void)
{
	App_Read_Send_Speed_Data();
}

/******************************************************************************/
/* Public APIs */
/******************************************************************************/

void App_NodeSpeed_Run()
{
	MID_ADC_Init(&ADC_Cfg_Speed);
	MID_LPIT_Init(LPIT_INS_0, LPIT_Callback_Speed);
	Middle_FlexCAN_Init(FlexCAN0_INS);
	Middle_CAN_UserConfigType UserCfgMBSendData = {
			.HandlerFunc = NULL,
			.MbID = 0x22,
			.MbIndex = MB0,
			.MbInt = true
	};

	Middle_CAN_UserConfigType UserCfgMBSendPing = {
			.HandlerFunc = NULL,
			.MbID = 0x44,
			.MbIndex = MB1,
			.MbInt = true
	};

	Middle_FlexCAN_StandardTransmitMbInit(FlexCAN0_INS, &UserCfgMBSendData);
	Middle_FlexCAN_StandardTransmitMbInit(FlexCAN0_INS, &UserCfgMBSendPing);

	Middle_CAN_UserConfigType UserCfgMBRequest = {
			.HandlerFunc = App_Speed_RcvRequest,
			.HandlerType = MIDDLE_HANDLER_MB_2_TYPE,
			.MbID = 0x55,
			.MbIndex = MB2,
			.MbInt = true
	};
	Middle_FlexCAN_StandardReceiveMbInit(FlexCAN0_INS, &UserCfgMBRequest);
	Middle_FlexCAN_SetCallback(FlexCAN0_INS, &UserCfgMBRequest);

	MID_LPIT_StartTimer(LPIT_INS_0, 0, 6000000);

	App_Read_Send_Speed_Data();
	while (1)
	{
		App_ProcessSpeedPing(&Speed_Ping_State);
		App_CheckSpeedConnect();
		App_SpeedReconnect();
	}
}
