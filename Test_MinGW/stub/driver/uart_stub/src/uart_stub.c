#include "../include/uart_stub.h"

#include <stdint.h>

static LPUART_Type s_lpuartBase[LPUART_INSTANCE_COUNT];
//static S32_NVIC_Type s_NVICBase[S32_NVIC_INSTANCE_COUNT];

LPUART_Type *LPUART0 = &s_lpuartBase[0];
LPUART_Type *LPUART1 = &s_lpuartBase[1];
LPUART_Type *LPUART2 = &s_lpuartBase[2];

//S32_NVIC_Type *S32_NVIC = &s_NVICBase[0];



