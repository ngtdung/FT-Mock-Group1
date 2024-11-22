#ifndef NODE_SPEED_H_
#define NODE_SPEED_H_

#include "Middleware_Header.h"
#include "Driver_Header.h"

typedef enum {
	SPEED_PING_READY,
	SPEED_PING_NOT_READY,
}Speed_Ping_State_t;


typedef enum {
	SPEED_OK = 0u,
	SPEED_NOT_OK = 1u,
}Speed_Connect_State_t;

void App_NodeSpeed_Run();
#endif
