/**
*   @file    PORT_Driver.h
*
*   @version 1.0.0
*
*   @addtogroup PORT
*   @{
*/

#ifndef __PORT_H__
#define __PORT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "S32K144.h"
#include "stdbool.h"
#include "assert.h"

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#define PORT_MAX_INSTANCE       5
#define PORTA_INSTANCE          0
#define PORTB_INSTANCE          1
#define PORTC_INSTANCE          2
#define PORTD_INSTANCE          3
#define PORTE_INSTANCE          4


/*==================================================================================================
*                                TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/**
 * @brief Enum type for PORT functions return type
 */
typedef enum DRV_PORT_ReturnCode_t
{
    DRV_PORT_RETURN_CODE_ERROR     = 0u,
    DRV_PORT_RETURN_CODE_SUCCESSED = 1u
} DRV_PORT_ReturnCode_type;

/**
 * @brief Internal pullup/pulldown of each GPIO input pin 
 */
typedef enum PORT_PullSelect_t
{
    PORT_INTERNAL_PULL_DOWN    = 0U,         /* Internal pull-down resistor is enabled */
    PORT_INTERNAL_PULL_UP      = 1U          /* Internal pull-up resistrr is enabled */
} PORT_PullSelect_type;

/** 
 * @brief Driver Strength mode of each GPIO output pin 
 */
typedef enum PORT_DriveStrengthMode_t
{
    PORT_DRIVER_STRENGTH_LOW   = 0U,    /* Low driver strength is configured on the corresponding pin */
    PORT_DRIVER_STRENGTH_HIGH  = 1U     /* High driver strength is configured on the corresponding pin */
} PORT_DriveStrengthMode_type;

/** @brief Pin Mux mode of each GPIO pin */
typedef enum PORT_PinMuxSelect_t
{
    PORT_MUX_ANALOG = 0U,           /* Corresponding pin is disabled, used as an analog pin */
    PORT_MUX_GPIO   = 1U,           /* Corresponding pin is configured GPIO */
    PORT_MUX_ALT2   = 2U,           /* Chip specific */
    PORT_MUX_ALT3   = 3U,           /* Chip specific */
    PORT_MUX_ALT4   = 4U,           /* Chip specific */
    PORT_MUX_ALT5   = 5U,           /* Chip specific */
    PORT_MUX_ALT6   = 6U,           /* Chip specific */
    PORT_MUX_ALT7   = 7U            /* Chip specific */
} PORT_PinMuxSelect_type;

/** @brief Interrupt mode of each GPIO input pin */
typedef enum PORT_InterruptConfig_t
{
    PORT_INT_DISABLE      = 0x0U,     /* Interrupt DMA request is disabled */
    PORT_DMA_RISING_EDGE  = 0x1U,     /* DMA request on rising edge */
    PORT_DMA_FALLING_EDGE = 0x2U,     /* DMA request on falling edge */
    PORT_DMA_EITHER_EDGE  = 0x3U,     /* DMA request on either edge */
    PORT_INT_LOGIC_ZERO   = 0x8U,     /* Interrupt when logic zero */
    PORT_INT_RISING_EDGE  = 0x9U,     /* Interrupt on Rising Edge */
    PORT_INT_FALLING_EDGE = 0xAU,     /* Interrupt on Falling Edge */
    PORT_INT_EITHER_EDGE  = 0xBU,     /* Interrupt on Either Edge */
    PORT_INT_LOGIC_ONE    = 0xCU      /* Interrupt when logic one */
} PORT_InterruptConfig_type;

typedef enum PORT_PullEnable_t
{
    PORT_PULL_DISABLE = 0u,         /* Port pull disable */
    PORT_PULL_ENABLE  = 1u          /* Port pull enable  */
} PORT_PullEnable_type;

typedef enum PORT_PaFilterEnable_t
{
    PORT_PASSIVE_FILTER_DISABLE = 0u,
    PORT_PASSIVE_FILTER_ENABLE  = 1u
} PORT_PaFilterEnable_type;

typedef uint8_t PORT_LockRegEnable_type;

/** @brief struct information need to config for a pin */
typedef struct PORT_Config_t
{
    PORT_PullEnable_type isPullEnable;                    /* Enable pullup/pulldown */
    PORT_PullSelect_type pullSelect;                      /* Select pullup/pulldown */
    PORT_PaFilterEnable_type isPassiveFilterEnable;       /* Enable passive filter */
    PORT_DriveStrengthMode_type driverStrengthMode;       /* Select driver strength mode */
    PORT_PinMuxSelect_type muxMode;                       /* Select pin mux mode */
    PORT_LockRegEnable_type isLockRegisterEnable;         /* Enable lock register */
    PORT_InterruptConfig_type interruptMode;              /* Select interrupt mode */
} PORT_Config_type;

/** @brief struct information need to config for a specific GPIO input pin
*/
typedef struct PORT_PinConfig_t
{
    uint8_t pinCode;                    /* pinCode represent both PORT name and pin number */
    PORT_Config_type userConfig;        /* struct input configure */
} PORT_PinConfig_type;



/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


DRV_PORT_ReturnCode_type DRV_PORT_InitPin(PORT_PinConfig_type *pinConfig);

DRV_PORT_ReturnCode_type DRV_PORT_InitMultiplePin(PORT_PinConfig_type *arrayPinsConfig[], int8_t numberPins);

/** @brief This function use to read ISF interrupt flag for individual pin
 * @param base Base address of individual PORT module
 * @param pin Pin want to configure
 * @return: 0 if ISF flag is not set, 1: if ISF flag is set
 */
uint8_t DRV_PORT_ReadInterruptFlagPin(uint8_t pinCode);

/** @brief This function use to clear ISF interrupt flag for individual pin
 * @param base Base address of individual PORT module
 * @param pin Pin want to configure
 */
void DRV_PORT_ClearInterruptFlagPin(uint8_t pinCode);

DRV_PORT_ReturnCode_type DRV_PORT_DeinitPin(uint8_t pinCode);

void DRV_PORT_DeinitMultiplePin(uint8_t *arrayPinCode, uint8_t numberPins);


#ifdef __cplusplus
}
#endif

#endif /* __PORT_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
