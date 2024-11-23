/**
*   @file    GPIO_Driver.c
*
*   @version 1.0.0
*
*   @addtogroup GPIO
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "GPIO_Driver.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define PORT_EXTRACT_INSTANCE(value)    (uint8_t)(((value) & 0xE0) >> 5)
#define PORT_EXTRACT_PIN(value)         (uint8_t)((value) & 0x1F)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

GPIO_Type *g_gpioPortBase[PORT_MAX_INSTANCE];

void InitGpioPortBase()
{
    g_gpioPortBase[0] = IP_PTA;
    g_gpioPortBase[1] = IP_PTB;
    g_gpioPortBase[2] = IP_PTC;
    g_gpioPortBase[3] = IP_PTD;
    g_gpioPortBase[4] = IP_PTE;
}

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                      GLOBAL FUNCTIONS
==================================================================================================*/

DRV_GPIO_ReturnCode_type DRV_GPIO_PinModeConfig(const GPIO_PinConfig_type *pinConfig)
{
    InitGpioPortBase();
    DRV_GPIO_ReturnCode_type retVal = DRV_GPIO_RETURN_CODE_ERROR;
    uint8_t pin = PORT_EXTRACT_PIN(pinConfig->pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinConfig->pinCode);
    GPIO_Type *base = g_gpioPortBase[port_instance];

   if((port_instance < PORT_MAX_INSTANCE) && ((void *)0 != pinConfig))
   {
       retVal = DRV_GPIO_RETURN_CODE_SUCCESSED;
   }

   if(DRV_GPIO_RETURN_CODE_SUCCESSED == retVal)
   {
       if (GPIO_PIN_MODE_OUTPUT == pinConfig->pinMode)
       {
           base->PDDR |= (1UL << pin);
           base->PDOR |= (1UL << pin);
       }
       else if (GPIO_PIN_MODE_INPUT == pinConfig->pinMode)
       {
           base->PDDR &= ~(1UL << pin);
       }
   }

   return retVal;
}

void DRV_GPIO_SetOutput(uint8_t pinCode)
{
    InitGpioPortBase();
    uint8_t pin = PORT_EXTRACT_PIN(pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
    GPIO_Type *base = g_gpioPortBase[port_instance];

    base->PSOR |= (1UL << pin);
}

void DRV_GPIO_ClearOutput(uint8_t pinCode)
{
    InitGpioPortBase();
    uint8_t pin = PORT_EXTRACT_PIN(pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
    GPIO_Type *base = g_gpioPortBase[port_instance];

    /* PCOR - Port Clear Output Register */
    /* Write 1 to this field, bit in PDOR is cleared to logic 0 */
    base->PCOR |= (1UL << pin);
}

void DRV_GPIO_ToggleOutput(uint8_t pinCode)
{
   uint8_t pin = PORT_EXTRACT_PIN(pinCode);
   uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
   GPIO_Type *base = g_gpioPortBase[port_instance];

   /* PTOR - Port Toggle Output Register */
   /* Write 1 to this field to set inverse existing logic state */
   base->PTOR |= (1UL << pin);
}

GPIO_Level_type DRV_GPIO_ReadPin(uint8_t pinCode)
{
   GPIO_Level_type readValue;     /*< read input pin value >*/
   uint8_t pin = PORT_EXTRACT_PIN(pinCode);
   uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
   GPIO_Type *base = g_gpioPortBase[port_instance];

   /* check PDIR field */
   /* Port Data Input register */
   /* This register captures the logic levels driven into input pin */
   if (((base->PDIR >> pin) & 0x01) == GPIO_PIN_LEVEL_HIGH)
   {
       readValue = GPIO_PIN_LEVEL_HIGH;
   }
   else
   {
       readValue = GPIO_PIN_LEVEL_LOW;
   }

   return readValue;
}

void DRV_GPIO_WritePin(uint8_t pinCode, const GPIO_Level_type level)
{
   uint8_t pin = PORT_EXTRACT_PIN(pinCode);
   uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
   GPIO_Type *base = g_gpioPortBase[port_instance];

   /* Port Data Output register */
   /* This register configures the logic levels driven on output pin.*/
   if (level == GPIO_PIN_LEVEL_LOW)
   {
       base->PDOR &= ~(1UL << pin);
   }
   else
   {
       base->PDOR |= (1UL << pin);
   }
}

#ifdef __cplusplus
}
#endif
