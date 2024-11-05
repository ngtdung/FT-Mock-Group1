/*
 * HAL_PORT.h
 *
 *  Created on: Apr 24, 2024
 *      Author: adm
 */

#ifndef INC_HAL_PORT_H_
#define INC_HAL_PORT_H_

#include "S32K144.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */
/**
 * @brief Array of PCC indices for PORT instances.
 *
 * This macro defines an array containing the PCC indices corresponding to PORT instances.
 * Each element corresponds to a specific PORT instance identified by an index.
 */
#define PCC_PORT_Index { PCC_PORTA_INDEX, PCC_PORTB_INDEX, PCC_PORTC_INDEX, PCC_PORTD_INDEX, PCC_PORTE_INDEX }

/**
 * @brief Array of NVIC IRQ numbers for PORT instances.
 *
 * This macro defines an array containing the NVIC IRQ numbers corresponding to PORT instances.
 * Each element corresponds to a specific PORT instance identified by an index.
 */
#define NVIC_PORT_IRQ { PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn, PORTE_IRQn }

/**
 * @brief Enumeration for configuring pull-up/pull-down control of a GPIO port.
 */
typedef enum
{
    PULLDOWN = 0U,  /**< Configure the port with pull-down control */
    PULLUP   = 1U,  /**< Configure the port with pull-up control */
	NOPULL 	 = 2U
} PORT_PUPDControl_e;
/*! @} */

/**
 * @brief Multiplexing function options for GPIO ports.
 */
typedef enum
{
    DISABLED = 0U,  /**< Port disabled */
    GPIO     = 1U,  /**< Use GPIO function */
    ALT2     = 2U,  /**< Alternative function 2 */
    ALT3     = 3U,  /**< Alternative function 3 */
    ALT4     = 4U,  /**< Alternative function 4 */
    ALT5     = 5U,  /**< Alternative function 5 */
    ALT6     = 6U,  /**< Alternative function 6 */
    ALT7     = 7U   /**< Alternative function 7 */
} PORT_MUX_e;
/*! @} */

/**
 * @brief Enumeration for configuring interrupt triggers on a GPIO port.
 */
typedef enum
{
    IntDisable   = 0U,   /**< Disable interrupts on the port */
    LogicLow     = 8U,   /**< Interrupt on logic low level */
    RisingEdge   = 9U,   /**< Interrupt on rising edge */
    FallingEdge  = 10U,  /**< Interrupt on falling edge */
    EitherEdge   = 11U,  /**< Interrupt on either edge (rising or falling) */
    LogicHigh    = 12U   /**< Interrupt on logic high level */
} PORT_InterruptConfig_e;
/*! @} */

/**
 * @brief Enumeration of GPIO port instances.
 */
typedef enum
{
    PORTA_Instance = 0U,  /**< GPIO Port A instance */
    PORTB_Instance = 1U,  /**< GPIO Port B instance */
    PORTC_Instance = 2U,  /**< GPIO Port C instance */
    PORTD_Instance = 3U,  /**< GPIO Port D instance */
    PORTE_Instance = 4U   /**< GPIO Port E instance */
} PORT_Instance_e;
/*! @} */

/**
 * @brief Enumeration of PCC (Peripheral Clock Control) instances for GPIO ports.
 */
typedef enum
{
    PCC_PORTA_Instance = 0U,  /**< PCC instance for GPIO Port A */
    PCC_PORTB_Instance = 1U,  /**< PCC instance for GPIO Port B */
    PCC_PORTC_Instance = 2U,  /**< PCC instance for GPIO Port C */
    PCC_PORTD_Instance = 3U,  /**< PCC instance for GPIO Port D */
    PCC_PORTE_Instance = 4U   /**< PCC instance for GPIO Port E */
} PCC_PORT_Instance_e;
/*! @} */

/**
 * @brief Enumeration of GPIO pin numbers.
 *
 * This enumeration represents individual GPIO pin numbers from 0 to 31.
 */
typedef enum
{
    Pin0  = 0U,   /**< GPIO pin number 0 */
    Pin1  = 1U,   /**< GPIO pin number 1 */
    Pin2  = 2U,   /**< GPIO pin number 2 */
    Pin3  = 3U,   /**< GPIO pin number 3 */
    Pin4  = 4U,   /**< GPIO pin number 4 */
    Pin5  = 5U,   /**< GPIO pin number 5 */
    Pin6  = 6U,   /**< GPIO pin number 6 */
    Pin7  = 7U,   /**< GPIO pin number 7 */
    Pin8  = 8U,   /**< GPIO pin number 8 */
    Pin9  = 9U,   /**< GPIO pin number 9 */
    Pin10 = 10U,  /**< GPIO pin number 10 */
    Pin11 = 11U,  /**< GPIO pin number 11 */
    Pin12 = 12U,  /**< GPIO pin number 12 */
    Pin13 = 13U,  /**< GPIO pin number 13 */
    Pin14 = 14U,  /**< GPIO pin number 14 */
    Pin15 = 15U,  /**< GPIO pin number 15 */
    Pin16 = 16U,  /**< GPIO pin number 16 */
    Pin17 = 17U,  /**< GPIO pin number 17 */
    Pin18 = 18U,  /**< GPIO pin number 18 */
    Pin19 = 19U,  /**< GPIO pin number 19 */
    Pin20 = 20U,  /**< GPIO pin number 20 */
    Pin21 = 21U,  /**< GPIO pin number 21 */
    Pin22 = 22U,  /**< GPIO pin number 22 */
    Pin23 = 23U,  /**< GPIO pin number 23 */
    Pin24 = 24U,  /**< GPIO pin number 24 */
    Pin25 = 25U,  /**< GPIO pin number 25 */
    Pin26 = 26U,  /**< GPIO pin number 26 */
    Pin27 = 27U,  /**< GPIO pin number 27 */
    Pin28 = 28U,  /**< GPIO pin number 28 */
    Pin29 = 29U,  /**< GPIO pin number 29 */
    Pin30 = 30U,  /**< GPIO pin number 30 */
    Pin31 = 31U   /**< GPIO pin number 31 */
} GPIO_PinNumber_e;

/**
 * @brief Configuration structure for a GPIO port.
 */
typedef struct
{
    PORT_PUPDControl_e PUPDControl;              /**< Pull-up/pull-down control configuration */
    PORT_MUX_e MUX;                         	/**< Multiplexing configuration */
    PORT_InterruptConfig_e InterruptConfig; 	/**< Interrupt configuration */
} PORT_Config_t;
/*! @} */

/* ----------------------------------------------------------------------------
   -- API
   ---------------------------------------------------------------------------- */

/**
 * @brief Initializes a GPIO port pin with the specified configuration.
 *
 * This function configures a specific GPIO pin on a port with the provided configuration settings.
 *
 * @param PORT_Instance The GPIO port instance
 * @param pinNumber The pin number within the GPIO port
 * @param PORTConfig Pointer to a PORT_Config_t structure containing the desired configuration settings.
 */
void PORT_Init(PORT_Instance_e PORT_Instance, GPIO_PinNumber_e pinNumber, const PORT_Config_t *PORTConfig);
void PORT_DeInit(PORT_Instance_e PORT_Instance);

#endif /* INC_HAL_PORT_H_ */
