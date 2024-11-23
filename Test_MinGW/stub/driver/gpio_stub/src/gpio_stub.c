#include <stdint.h>
#include "gpio_stub.h"

static GPIO_Type IP_GPIO_BASE[5];

GPIO_Type* IP_PTA = &IP_GPIO_BASE[0];
GPIO_Type* IP_PTB = &IP_GPIO_BASE[1];
GPIO_Type* IP_PTC = &IP_GPIO_BASE[2];
GPIO_Type* IP_PTD = &IP_GPIO_BASE[3];
GPIO_Type* IP_PTE = &IP_GPIO_BASE[4];

