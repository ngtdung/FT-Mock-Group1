#include <stdint.h>
#include "irq_stub.h"

static S32_NVIC_Type s_S32_NVIC;
S32_NVIC_Type *S32_NVIC = &s_S32_NVIC;