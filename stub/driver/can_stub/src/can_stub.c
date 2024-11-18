#include <stdint.h>
#include "can_stub.h"

static CAN_Type s_can[CAN_INSTANCE_COUNT];
CAN_Type *CAN0 = &s_can[0];
CAN_Type *CAN1 = &s_can[1];
CAN_Type *CAN2 = &s_can[2];