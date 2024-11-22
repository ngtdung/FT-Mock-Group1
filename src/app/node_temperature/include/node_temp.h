/*
 * node_temp.h
 *
 *  Created on: Nov 18, 2024
 *      Author: Manh
 */

#ifndef APP_NODE_TEMPERATURE_INCLUDE_NODE_TEMP_H_
#define APP_NODE_TEMPERATURE_INCLUDE_NODE_TEMP_H_

#include "Middleware_Header.h"

typedef enum {
	TEMP_PING_READY,
	TEMP_PING_NOT_READY,
}Temp_Ping_State_t;


typedef enum {
	TEMP_OK = 0u,
	TEMP_NOT_OK = 1u,
}Temp_Connect_State_t;

void App_NodeTemp_Run();

#endif /* APP_NODE_TEMPERATURE_INCLUDE_NODE_TEMP_H_ */
