#include "Driver_Header.h"

typedef enum
{
    GREEN = 112U,
    RED = 111U,
    BLUE = 96U,
}LED_Color_t;

void MID_GPIO_Init(void);
void MID_GPIO_LEDInit(LED_Color_t Color);
void MID_GPIO_LEDOn(LED_Color_t Color);
void MID_GPIO_LEDOff(LED_Color_t Color);
