/*
 * node_forwarder.c
 *
 *  Created on: Nov 18, 2024
 *      Author: Manh
 */

/******************************************************************************/
/* Includes */
/******************************************************************************/
#include "node_forwarder.h"
#include <stdio.h>

/******************************************************************************/
/* Definations */
/******************************************************************************/

#define RX_MB_COUNT 4
#define DEFAULT_UART_MSG 0
#define STD_UART_MSG 125
#define ERROR_VALUE 250
#define DLC_UART_MSG 1
#define THRESHOLD_SPEED 120
#define THRESHOLD_TEMP_HIGH 37
#define THRESHOLD_TEMP_LOW 15

/******************************************************************************/
/* Variables */
/******************************************************************************/

CAN_State_t g_CAN_TEMP_State = CAN_TEMP_NOT_READY;
CAN_State_t g_CAN_SPEED_State = CAN_SPEED_NOT_READY;

TEMP_ERROR_State_t Temp_Error_State = TEMP_ERROR;
SPEED_ERROR_State_t Speed_Error_State = SPEED_ERROR;

Data_t g_Data = {
	.NODE_Speed_Data = 0,
	.NODE_Temp_Data = 0
};
uint8_t g_Msg = 0;
uint8_t UART_Respone_Msg[12] = {0};
uint8_t Request_CAN = 0x07;

FWD_Connect_State_t FWD_Connect_State = FWD_NOT_OK;

void App_NewTempValue_Notification(void);
void App_NewTempPing_Notification(void);
void App_NewSpeedValue_Notification(void);
void App_NewSpeedPing_Notification(void);



void (*CallBack_arr[RX_MB_COUNT])(void) = {App_NewTempValue_Notification, App_NewSpeedValue_Notification, App_NewTempPing_Notification, App_NewSpeedPing_Notification};
Middle_FlexCAN_Handler_e Handler_Type_arr[RX_MB_COUNT] = {MIDDLE_HANDLER_MB_0_TYPE, MIDDLE_HANDLER_MB_1_TYPE, MIDDLE_HANDLER_MB_6_TYPE, MIDDLE_HANDLER_MB_7_TYPE};
FlexCAN_MbIndex_e ReceiveMB[RX_MB_COUNT] = {MB0, MB1, MB6, MB7};
uint32_t ReceiveMB_Adr[RX_MB_COUNT] = {0x11, 0x22, 0x33, 0x44};

/******************************************************************************/
/* Local APIs */
/******************************************************************************/

static void createString(const Data_t* data, uint8_t* output, size_t outputSize) {
	uint8_t dataTemp = data->NODE_Temp_Data;
	uint8_t dataSpeed = data->NODE_Speed_Data;
    if (data != NULL && output != NULL) {
    	snprintf((char*)output, outputSize, "49%02x%02x%02x53\n", dataTemp, dataSpeed, (uint8_t)(dataTemp+dataSpeed));
    }
}



static void App_Process_UART_Request(uint8_t* Rcv_Msg)
{
	if(*Rcv_Msg  == STD_UART_MSG){
		createString(&g_Data, UART_Respone_Msg, sizeof(UART_Respone_Msg));
		DRV_UART_SendDataInterrupt(DRV_UART_instance_1,
						(uint8_t*)UART_Respone_Msg, sizeof(UART_Respone_Msg));
		*Rcv_Msg = DEFAULT_UART_MSG;
	}
}

static void App_Process_CAN_NewValue(CAN_State_t *state)
{
	if(*state == CAN_SPEED_READY){
		FlexCAN_ReadMailboxData(FlexCAN0_INS, MB1, &(g_Data.NODE_Speed_Data));
		*state = CAN_SPEED_NOT_READY;
	}else if(*state == CAN_TEMP_READY){
		FlexCAN_ReadMailboxData(FlexCAN0_INS, MB0, &(g_Data.NODE_Temp_Data));
		*state = CAN_TEMP_NOT_READY;
	}
}

static void App_Process_LEDWarning(void)
{
	if (g_Data.NODE_Temp_Data > THRESHOLD_TEMP_HIGH && g_Data.NODE_Temp_Data != ERROR_VALUE)
	{
		MID_GPIO_LEDOn(RED);
		MID_GPIO_LEDOff(BLUE);
	}
	else if (g_Data.NODE_Temp_Data < THRESHOLD_TEMP_LOW)
	{
		MID_GPIO_LEDOn(BLUE);
		MID_GPIO_LEDOff(RED);
	}
	else
	{
		MID_GPIO_LEDOff(RED);
		MID_GPIO_LEDOff(BLUE);
	}
	if (g_Data.NODE_Speed_Data > THRESHOLD_SPEED && g_Data.NODE_Speed_Data != ERROR_VALUE)
	{
		MID_GPIO_LEDOn(GREEN);
	}
	else
	{
		MID_GPIO_LEDOff(GREEN);
	}
}


/******************************************************************************/
/* CallBack APIs */
/******************************************************************************/

void App_CheckPing_Notification(uint8_t channel)
{
	if(Speed_Error_State == SPEED_NOT_ERROR){
		Speed_Error_State = SPEED_ERROR;
	}else if(Speed_Error_State == SPEED_ERROR){
		Speed_Error_State = SPEED_STILL_ERROR;
		g_Data.NODE_Speed_Data = ERROR_VALUE;
	}else{

	}

	if(Temp_Error_State == TEMP_NOT_ERROR){
		Temp_Error_State = TEMP_ERROR;
	}else if(Temp_Error_State == TEMP_ERROR){
		Temp_Error_State = TEMP_STILL_ERROR;
		g_Data.NODE_Temp_Data = ERROR_VALUE;
	}
}


void App_NewTempValue_Notification(void)
{
	g_CAN_TEMP_State = CAN_TEMP_READY;
}

void App_NewTempPing_Notification(void)
{
	if(Temp_Error_State == TEMP_STILL_ERROR){
		Middle_CAN_Transmit(FlexCAN0_INS, MB5, &Request_CAN);
	}
	Temp_Error_State = TEMP_NOT_ERROR;
}

void App_NewSpeedValue_Notification(void)
{
	g_CAN_SPEED_State = CAN_SPEED_READY;
}

void App_NewSpeedPing_Notification(void)
{
	if(Speed_Error_State == SPEED_STILL_ERROR){
		Middle_CAN_Transmit(FlexCAN0_INS, MB5, &Request_CAN);
	}
	Speed_Error_State = SPEED_NOT_ERROR;
}

void App_Check_Request_UART(void)
{
	MID_UART_ReceiveDataInterrupt(DRV_UART_instance_1, &g_Msg, DLC_UART_MSG);
}

/******************************************************************************/
/* Public APIs */
/******************************************************************************/

void App_Forwarder_Run(void)
{

		/*GPIO Init*/

		MID_GPIO_Init();
		MID_GPIO_LEDOff(BLUE);
		MID_GPIO_LEDOff(GREEN);
		MID_GPIO_LEDOff(RED);

		/*CAN Init*/

	    Middle_FlexCAN_Init(FlexCAN0_INS);
	    for(uint8_t MB_Index = 0; MB_Index < RX_MB_COUNT; MB_Index++){
			Middle_CAN_UserConfigType UserCfgMB = {
					.HandlerFunc = CallBack_arr[MB_Index] ,
					.HandlerType = Handler_Type_arr[MB_Index],
					.MbID = ReceiveMB_Adr[MB_Index],
					.MbIndex = ReceiveMB[MB_Index],
					.MbInt = true
			};
	    	Middle_FlexCAN_StandardReceiveMbInit(FlexCAN0_INS, &UserCfgMB);
			Middle_FlexCAN_SetCallback(FlexCAN0_INS, &UserCfgMB);
	    }

		Middle_CAN_UserConfigType InitialMB = {
				.HandlerFunc = NULL,
				.MbID = 0x55,
				.MbIndex = MB5,
				.MbInt = true
		};
		Middle_FlexCAN_StandardTransmitMbInit(FlexCAN0_INS, &InitialMB);

	    /*LPIT Init*/

		MID_LPIT_Init(LPIT_INS_0, App_CheckPing_Notification);
	    MID_LPIT_StartTimer(LPIT_INS_0, LPIT_CHANNEL_0, 12000000);

	    /*UART Init*/

		MID_UART_Init();
		MID_UART_InstallCallBack(DRV_UART_callBackReceiver, App_Check_Request_UART);
		MID_UART_ReceiveDataInterrupt(DRV_UART_instance_1, &g_Msg, DLC_UART_MSG);

		/*CAN Send Request when Starting*/

		Middle_CAN_Transmit(FlexCAN0_INS, MB5, &Request_CAN);
    while(1){
    	App_Process_CAN_NewValue(&g_CAN_TEMP_State);
    	App_Process_CAN_NewValue(&g_CAN_SPEED_State);
    	App_Process_UART_Request(&g_Msg);
    	App_Process_LEDWarning();
    };
}
