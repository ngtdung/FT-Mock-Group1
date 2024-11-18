#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "S32K144.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define CODE_SEND (0xC)                /* 1100 */
#define CODE_RECEIVE_EMPTY (0x4U)      /* 0100 */
#define CODE_ABORT_TRANSMISSION (0x9U) /* 1001 */
#define CODE_INACTIVE_RX (0x0U)           /* 0000 */
#define CODE_INACTIVE_TX (0x8U)           /* 1000 */
#define CODE_BUSY (0x1u)

#define OFFSET_START_OF_DATA_MB (2U)

#define MB_CODE_SHIFT (24U)
#define MB_IDE_SHIFT (21U)
#define MB_EDL_SHIFT (31U)
#define MB_BRS_SHIFT (30U)
#define MB_ESI_SHIFT (29U)
#define MB_SRR_SHIFT (22U)
#define MB_RTR_SHIFT (20U)
#define MB_DLC_SHIFT (16U)
#define MB_ID_SHIFT (0U)

#define MB_ID_MASK (0x1FFFFFFFU)
#define MB_DLC_MASK (0x000F0000U)
#define MB_CODE_MASK (0x0F000000U)

#define OFFSET_START_OF_MB (0u)
#define OFFSET_ID_OF_MB (1U)
#define OFFSET_DATA_START_OF_MB (2U)

/*******************************************************************************
 * Datatype Definiton
 ******************************************************************************/
typedef enum
{
    FLEXCAN_RETURN_CODE_SUCCESS = 0U,
    FLEXCAN_RETURN_CODE_FAIL,
    FLEXCAN_RETURN_CODE_INVALID_INS
} FlexCAN_ReturnCode_t;

typedef struct
{
    uint32_t timeStamp : 16;
    uint32_t dlc       : 4;
    uint32_t rtr       : 1;
    uint32_t ide       : 1;
    uint32_t srr       : 1;
    uint32_t reserve1  : 1;
    uint32_t code      : 4;
    uint32_t reserve2  : 1;
    uint32_t esi       : 1;
    uint32_t brs       : 1;
    uint32_t edl       : 1;
} FlexCAN_control_MB_t;

typedef struct
{
    uint32_t id   : 29;
    uint32_t prio : 3;
} FlexCAN_ID_config_MB_t;

typedef struct
{
    FlexCAN_control_MB_t cfControl;
    FlexCAN_ID_config_MB_t cfID;
    uint32_t RxIdMask;
    uint32_t RxIdFilter;
} FlexCAN_RX_MessageBuffer_t;

typedef struct
{
    FlexCAN_control_MB_t cfControl;
    FlexCAN_ID_config_MB_t cfID;
    uint8_t dataByte[64];
} FlexCAN_TX_MessageBuffer_t;

typedef struct
{
    uint8_t presdiv;
    uint8_t rjw;
    uint8_t pseg1;
    uint8_t pseg2;
    uint8_t smp;
    uint8_t propseg;
} FlexCAN_bit_timing_t;

typedef void (*FlexCAN_CallbackIRQ)(uint8_t);
/*******************************************************************************
 * APIs
 ******************************************************************************/
/**
 * @brief     CAN initialization
 *
 * @param[in] instance: Input instance
 * @param[in] wordSize: Input word size per message buffer
 * @param[in] bitTiming: Input data to config bit rate
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS    : Initialize successful
 *            FLEXCAN_RETURN_CODE_FAIL       : Invalid input word size or bit timing
 *            FLEXCAN_RETURN_CODE_INVALID_INS: Invalid input instance
 */
FlexCAN_ReturnCode_t FlexCAN_Init(uint32_t instance, uint8_t wordSize, FlexCAN_bit_timing_t *bitTiming);
/**
 * @brief     Config transmit message buffer
 *
 * @param[in] instance: Input instance
 * @param[in] indexOfMB: Input index of message buffer
 * @param[in] DataOfMB: Input data to config message buffer
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Config successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Config unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_Config_Tx_MessageBuffer(uint32_t instance, uint8_t indexOfMB, FlexCAN_TX_MessageBuffer_t *DataOfMB);
/**
 * @brief     Config receive message buffer
 *
 * @param[in] instance: Input instance
 * @param[in] IndexOfMb: Input index of message buffer
 * @param[in] config: Input data to config message buffer
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Config successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Config unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_Config_RX_MessageBuffer(uint32_t instance, uint8_t IndexOfMb, FlexCAN_RX_MessageBuffer_t *config);
/**
 * @brief     Send data to CAN BUS
 *
 * @param[in] instance: Input instance
 * @param[in] IndexOfMb: Input index of message buffer
 * @param[in] mbData: Input data to config message buffer
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Send successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Send unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_Send(uint32_t instance, uint8_t IndexOfMb, FlexCAN_TX_MessageBuffer_t *mbData);
/**
 * @brief     Receive data from CAN BUS
 *
 * @param[in] instance: Input instance
 * @param[in] IndexOfMb: Input index of message buffer
 * @param[out] mbData:   Output buffer to store received data
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Receive successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Receive unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_Receive(uint32_t instance, uint8_t IndexOfMb, FlexCAN_TX_MessageBuffer_t *mbData);
/**
 * @brief     Enable interrupt for message buffer
 *
 * @param[in] instance: Input instance
 * @param[in] instance: Input index of message buffer will be enabled interrupt
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Config successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Config unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_ConfigInterrupt(uint32_t instance, uint8_t IndexOfMb);
/**
 * @brief     Initialize interrupt
 *
 * @param[in] instance: Input instance
 * @param[in] irqIndex: Input index of interrupt handler
 * @param[in] CAN_MiddlewareCallback: Input address of callback function
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Initialize successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Initialize unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_InitIRQ(uint32_t instance, IRQn_Type irqIndex, FlexCAN_CallbackIRQ CAN_MiddlewareCallback);
/**
 * @brief     Clear interrupt flag
 *
 * @param[in] instance: Input instance
 * @param[in] flagIndex: Input index of interrupt flag to clear
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS: Clear successful
 *            FLEXCAN_RETURN_CODE_FAIL   : Clear unsuccessful
 */
FlexCAN_ReturnCode_t FlexCAN_ClearInterruptFlag(uint32_t instance, uint32_t flagIndex);

#endif /* __CAN_H__ */

#ifdef __cplusplus
}
#endif

/*******************************************************************************
 * End of file
 ******************************************************************************/
