#ifndef NODE_FORWARDER_H_
#define NODE_FORWARDER_H_

#include "Middleware_Header.h"
#include "Driver_Header.h"

typedef enum{
	CAN_SPEED_READY = 0u,
	CAN_SPEED_NOT_READY,
	CAN_TEMP_READY,
	CAN_TEMP_NOT_READY,
}CAN_State_t;

typedef enum{
	TEMP_ERROR = 0u,
	TEMP_NOT_ERROR = 1u,
	TEMP_STILL_ERROR,
}TEMP_ERROR_State_t;

typedef enum{
	SPEED_ERROR = 0u,
	SPEED_NOT_ERROR = 1u,
	SPEED_STILL_ERROR
}SPEED_ERROR_State_t;

typedef enum {
	FWD_OK = 0u,
	FWD_NOT_OK = 1u,
}FWD_Connect_State_t;

typedef struct{
	uint8_t NODE_Speed_Data;
	uint8_t NODE_Temp_Data;
}Data_t;

void App_Forwarder_Run(void);

#endif
