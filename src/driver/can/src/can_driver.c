#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Include
 ******************************************************************************/
#include "can_driver.h"
#include <stdio.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NUM_BYTES_EACH_WORD (4U)
#define MAX_NUMBER_OF_WORD (18U)

#define ONE_BYTE (8U)
#define THREE_BYTES (24U)
#define FLEXCAN_0_INDEX (0u)
#define FLEXCAN_1_INDEX (1u)
#define FLEXCAN_2_INDEX (2u)

#define FLEXCAN_INSTANCE_0 (0u)
#define FLEXCAN_INSTANCE_1 (1u)
#define FLEXCAN_INSTANCE_2 (2u)

#define CAN_INSTANCE_NUMBER (3U)

#define WORD_LENGTH (4u)
#define RANGE_OF_MB (uint8_t)(512 / (WORD_LENGTH * NUM_BYTES_EACH_WORD))

/*******************************************************************************
 * Variable Definiion
 ******************************************************************************/

// static uint8_t s_mbWordLength;
// static uint8_t RANGE_OF_MB;
static FlexCAN_CallbackIRQ s_callbackIrq_0;
static FlexCAN_CallbackIRQ s_callbackIrq_1;
static FlexCAN_CallbackIRQ s_callbackIrq_2;
// CAN_Type *const insCanBase[CAN_INSTANCE_NUMBER] = CAN_BASE_PTRS; /* (0x40024000u, 0x40025000u, 0x4002B000u } */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/**
 * @brief     Enter freeze mode
 *
 * @param[in] instance: Input instance
 *
 * @return    None
 */
static void FlexCAN_Enter_Freeze_Mode(uint32_t instance);
/**
 * @brief     Exit freeze mode
 *
 * @param[in] instance: Input instance
 *
 * @return    None
 */
static void FlexCAN_Exit_Freeze_Mode(uint32_t instance);
/**
 * @brief     Clear all message buffers
 *
 * @param[in] instance: Input instance
 *
 * @return    None
 */
static void FlexCAN_Clear_Message_Buffer(uint32_t instance);
/**
 * @brief     Set bit rate
 *
 * @param[in] instance: Input instance
 * @param[in] bit_timing: Input data to config bit rate
 *
 * @return    None
 */
static void FlexCAN_Set_Bit_Rate(uint32_t instance, FlexCAN_bit_timing_t *bit_timing);
/**
 * @brief     Get base address according to instance
 *
 * @param[in]  instance: Input instance
 * @param[out] bassAddress: Output CAN base address with respective instance
 *
 * @return    FLEXCAN_RETURN_CODE_SUCCESS    : Valid input instance
 *            FLEXCAN_RETURN_CODE_INVALID_INS: Invalid input instance
 */
static FlexCAN_ReturnCode_t FlexCAN_Get_Base_Address(uint32_t instance, CAN_Type **bassAddress);

/*******************************************************************************
 * Function
 ******************************************************************************/
static FlexCAN_ReturnCode_t FlexCAN_Get_Base_Address(uint32_t instance, CAN_Type **bassAddress)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_SUCCESS;

    if (instance == FLEXCAN_INSTANCE_0)
    {
        *bassAddress = CAN0;
    }
    else if (instance == FLEXCAN_INSTANCE_1)
    {
        *bassAddress = CAN1;
    }
    else if (instance == FLEXCAN_INSTANCE_2)
    {
        *bassAddress = CAN2;
    }
    else
    {
        retVal = FLEXCAN_RETURN_CODE_INVALID_INS;
    }

    return retVal;
}

static void FlexCAN_Enter_Freeze_Mode(uint32_t instance)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    /* Enable to enter FreezeMode */
    sp_base->MCR = (sp_base->MCR & ~CAN_MCR_FRZ_MASK) | CAN_MCR_FRZ(1U);
    /* Enter FreezeMode */
    sp_base->MCR = (sp_base->MCR & ~CAN_MCR_HALT_MASK) | CAN_MCR_HALT(1U);
    /* Check whether bit MDIS in CAN_MCR is set to 1. If it is, clear it to 0 */
    if (((sp_base->MCR & CAN_MCR_MDIS_MASK) >> CAN_MCR_MDIS_SHIFT) != 0U)
    {
        sp_base->MCR &= ~CAN_MCR_MDIS_MASK;
    }
    while ((sp_base->MCR & CAN_MCR_FRZACK_MASK) == 0U)
    {
        /* do nothing to wait enter freezeMode */
    }
}

static void FlexCAN_Exit_Freeze_Mode(uint32_t instance)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    /* No Freeze mode request */
    sp_base->MCR = (sp_base->MCR & ~CAN_MCR_HALT_MASK) | CAN_MCR_HALT(0U);
    /* Disable to enter FreezeMode */
    sp_base->MCR = (sp_base->MCR & ~CAN_MCR_FRZ_MASK) | CAN_MCR_FRZ(0U);

    while ((sp_base->MCR & CAN_MCR_FRZACK_MASK) != 0U)
    {
        /* do nothing to sure exit freezeMode */
    }
    /* Check FlexCAN module is either in Normal mode, Listen-Only mode, or Loop-Back mode */
    while ((sp_base->MCR & CAN_MCR_NOTRDY_MASK) != 0U)
    {
        /* do nothing */
    }
}

static void FlexCAN_Clear_Message_Buffer(uint32_t instance)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    uint8_t index = 0;

    /* CAN0: clear 32 message buffers x 4 words/msg buf = 128 words */
    for (index = 0; index < CAN_RAMn_COUNT; index++)
    {
        /* Clear msg buf word */
        sp_base->RAMn[index] = 0U;
    }
}

static void FlexCAN_Set_Bit_Rate(uint32_t instance, FlexCAN_bit_timing_t *bitTiming)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    sp_base->CTRL1 = CAN_CTRL1_PRESDIV(bitTiming->presdiv) |
                     CAN_CTRL1_RJW(bitTiming->rjw) |
                     CAN_CTRL1_PSEG1(bitTiming->pseg1) |
                     CAN_CTRL1_PSEG2(bitTiming->pseg2) |
                     CAN_CTRL1_SMP(bitTiming->smp) |
                     CAN_CTRL1_PROPSEG(bitTiming->propseg);
}

FlexCAN_ReturnCode_t FlexCAN_Config_Tx_MessageBuffer(uint32_t instance, uint8_t indexOfMB, FlexCAN_TX_MessageBuffer_t *DataOfMB)
{
    CAN_Type *sp_base;
    uint8_t dataLength = 0;
    uint8_t indexOfData = 0;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    uint8_t byteIndex = 0;
    uint8_t IndexOfRAM = 0;
    uint32_t *mbData;

    mbData = (uint32_t *)DataOfMB;
    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    /* DLC max value is 8  with CAN 2.0 standard frame */
    if (FLEXCAN_RETURN_CODE_SUCCESS == retVal)
    {
        if (indexOfMB <= RANGE_OF_MB)
        {
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    if (FLEXCAN_RETURN_CODE_SUCCESS == retVal)
    {
        dataLength = (uint8_t)(DataOfMB->cfControl.dlc);
        /* Write the payload date bytes */
        for (indexOfData = 0; indexOfData < dataLength; indexOfData++)
        {
            byteIndex = indexOfData / NUM_BYTES_EACH_WORD;
            IndexOfRAM = indexOfMB * WORD_LENGTH + OFFSET_START_OF_DATA_MB + byteIndex;
            /* write data for each byte of word by sequence */
            sp_base->RAMn[IndexOfRAM] = sp_base->RAMn[IndexOfRAM] << ONE_BYTE;
            sp_base->RAMn[IndexOfRAM] |= DataOfMB->dataByte[indexOfData];
        }
        /* Config the Control and Status word with desired configuration */
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_START_OF_MB] = 0U;
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_START_OF_MB] = *mbData;
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_ID_OF_MB] = 0U;
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_ID_OF_MB] = *(mbData + 1);
        /* Activate the message buffer to transmit the CAN frame */
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
        sp_base->RAMn[indexOfMB * WORD_LENGTH + OFFSET_START_OF_MB] |= (CODE_SEND << MB_CODE_SHIFT);
    }

    return retVal;
}

/* CAN FD disable, IRMQ disable */
/*
 * wordSize = 4: -> 8 bytes payload -> plus 2 word for configuration field
 * wordSize = 6: -> 16 bytes payload
 * wordSize = 10: -> 32 bytes payload
 * wordSize = 18: -> 64 bytes payload
 */
FlexCAN_ReturnCode_t FlexCAN_Init(uint32_t instance, uint8_t wordSize, FlexCAN_bit_timing_t *bitTiming)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if ((bitTiming != NULL) && (wordSize <= MAX_NUMBER_OF_WORD))
        {
            /* enable clock to CAN_Driver0 */
            // PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK;
            /* Disable module before selecting clock   */
            sp_base->MCR |= CAN_MCR_MDIS_MASK;
            /* CLKSRC=0 -> CAN engine clock source is the oscillator clock, the oscillator clock frequency must be lower than bus clock */
            sp_base->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;
            /* Enter freeze mode */
            FlexCAN_Enter_Freeze_Mode(instance);
            FlexCAN_Set_Bit_Rate(instance, bitTiming);
            FlexCAN_Clear_Message_Buffer(instance);
            /* Self-reception disabled -> module cannot receive frames which are transmitted by itself */
            sp_base->MCR = (sp_base->MCR & ~CAN_MCR_SRXDIS_MASK) | CAN_MCR_SRXDIS(1U);
            /* Exit freeze mode */
            FlexCAN_Exit_Freeze_Mode(instance);
            /* Check whether FlexCAN is synchronized to the CAN bus and able to join communication process */
            if ((sp_base->ESR1 >> CAN_ESR1_SYNCH_SHIFT) & CAN_ESR1_SYNCH_WIDTH)
            {
                retVal = FLEXCAN_RETURN_CODE_SUCCESS;
            }
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_Config_RX_MessageBuffer(uint32_t instance, uint8_t IndexOfMb, FlexCAN_RX_MessageBuffer_t *config)
{
    uint8_t index = 0;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if ((config->cfID.id <= MB_ID_MASK) && (IndexOfMb <= RANGE_OF_MB))
        {
            if ((((sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F) != CODE_INACTIVE_RX)
            {
                sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
                sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] |= (CODE_INACTIVE_RX << MB_CODE_SHIFT);
            }
            FlexCAN_Enter_Freeze_Mode(instance);
            /* Set Rx Global mask*/
            sp_base->RXMGMASK = 0;
            sp_base->RXMGMASK = config->RxIdMask;
            /* Set Rx Global mask */
            sp_base->RXIMR[IndexOfMb] = config->RxIdFilter;
            sp_base->RXIMR[IndexOfMb] = config->RxIdFilter;
            FlexCAN_Exit_Freeze_Mode(instance);
            /* Set config for MB, write 0b0100 to Control and Status word to activate MB */
            sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
            sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] = (CODE_RECEIVE_EMPTY << MB_CODE_SHIFT) | (config->cfControl.ide << MB_IDE_SHIFT);
            /* Write the ID word */
            sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_ID_OF_MB] = 0;
            sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_ID_OF_MB] = config->cfID.id;
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_ClearInterruptFlag(uint32_t instance, uint32_t flagIndex)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if (flagIndex <= RANGE_OF_MB)
        {
            sp_base->IFLAG1 |= (1 << flagIndex);
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_Send(uint32_t instance, uint8_t IndexOfMb, FlexCAN_TX_MessageBuffer_t *mbData)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if (mbData != NULL)
        {
            /* Clear interrupt flag */
            retVal = FlexCAN_ClearInterruptFlag(instance, IndexOfMb);
            /* Check whether MB is active */
            if (((((sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F) != CODE_INACTIVE_TX) &&
                ((((sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F) != CODE_ABORT_TRANSMISSION) &&
                ((((sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F) != CODE_INACTIVE_RX))
            {
                /* Write ABORT code to the CODE field */
                sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
                sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] |= (CODE_ABORT_TRANSMISSION << MB_CODE_SHIFT);
                /* Clear the corresponding IFLAG */
                retVal = FlexCAN_ClearInterruptFlag(instance, IndexOfMb);
            }
            /* Config TX message buffer to send */
            retVal = FlexCAN_Config_Tx_MessageBuffer(instance, IndexOfMb, mbData);
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_Receive(uint32_t instance, uint8_t IndexOfMb, FlexCAN_TX_MessageBuffer_t *mbData)
{
    uint8_t indexData = 0;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if (IndexOfMb <= RANGE_OF_MB)
        {
            /* Waiting CAN update mailbox data by move-in process, wait for busy bit be negated */
            while ((sp_base->RAMn[IndexOfMb * WORD_LENGTH] >> MB_CODE_SHIFT) & CODE_BUSY)
            {
                /* Do nothing */
            }
            /* Get data and configuration from MB */
            mbData->cfID.id = 0;
            mbData->cfID.id = (sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_ID_OF_MB] & MB_ID_MASK) >> MB_ID_SHIFT;
            mbData->cfControl.dlc = (sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_START_OF_MB] & MB_DLC_MASK) >> MB_DLC_SHIFT;
            for (indexData = 0U; indexData < (uint8_t)mbData->cfControl.dlc; indexData++)
            {
                mbData->dataByte[indexData] = (uint8_t)(sp_base->RAMn[IndexOfMb * WORD_LENGTH + OFFSET_DATA_START_OF_MB + (indexData / NUM_BYTES_EACH_WORD)] >> (THREE_BYTES - ONE_BYTE * (indexData % NUM_BYTES_EACH_WORD)));
            }
            mbData->cfID.prio = 0;
            /* Read free running timer to unlock mailbox */
            (void)sp_base->TIMER;
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_ConfigInterrupt(uint32_t instance, uint8_t IndexOfMb)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;

    retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        FlexCAN_Enter_Freeze_Mode(instance);
        /* Enable interrupt for both transmission and reception */
        sp_base->IMASK1 |= (1 << IndexOfMb);
        FlexCAN_Exit_Freeze_Mode(instance);
    }

    return retVal;
}

FlexCAN_ReturnCode_t FlexCAN_InitIRQ(uint32_t instance, IRQn_Type irqIndex, FlexCAN_CallbackIRQ CAN_MiddlewareCallback)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    CAN_Type *sp_base;
    if (NULL != CAN_MiddlewareCallback)
    {
        retVal = FlexCAN_Get_Base_Address(instance, &sp_base);
    }

    if (retVal == FLEXCAN_RETURN_CODE_SUCCESS)
    {
        if ((irqIndex >= CAN0_ORed_IRQn) && (irqIndex <= CAN2_ORed_0_15_MB_IRQn))
        {
            S32_NVIC->ISER[irqIndex / 32] |= (1 << (irqIndex % 32));
           switch (instance)
           {
            case FLEXCAN_INSTANCE_0:
                s_callbackIrq_0 = CAN_MiddlewareCallback;
                break;
            case FLEXCAN_INSTANCE_1:
                s_callbackIrq_1 = CAN_MiddlewareCallback;
                break;
            default: //FLEXCAN_INSTANCE_2
                s_callbackIrq_2 = CAN_MiddlewareCallback;
                break;
           }
            retVal = FLEXCAN_RETURN_CODE_SUCCESS;
        }
        else
        {
            retVal = FLEXCAN_RETURN_CODE_FAIL;
        }
    }

    return retVal;
}

void CAN0_ORed_0_15_MB_IRQHandler()
{
    uint8_t flagIndex = 0;
    CAN_Type *sp_base;
    uint8_t g_flagInterruptMB = 0;

    sp_base = CAN0;
    for (flagIndex = 0; flagIndex < RANGE_OF_MB; flagIndex++)
    {
        if (((sp_base->IFLAG1) >> flagIndex) & 1U)
        {
            g_flagInterruptMB = flagIndex;
            break;
        }
    }
    s_callbackIrq_0(g_flagInterruptMB);
}

void CAN1_ORed_0_15_MB_IRQHandler()
{
    uint8_t flagIndex = 0;
    CAN_Type *sp_base;
    uint8_t g_flagInterruptMB = 0;

    sp_base = CAN1;
    for (flagIndex = 0; flagIndex < RANGE_OF_MB; flagIndex++)
    {
        if (((sp_base->IFLAG1) >> flagIndex) & 1U)
        {
            g_flagInterruptMB = flagIndex;
            break;
        }
    }
    s_callbackIrq_1(g_flagInterruptMB);
}

void CAN2_ORed_0_15_MB_IRQHandler()
{
    uint8_t flagIndex = 0;
    CAN_Type *sp_base;
    uint8_t g_flagInterruptMB = 0;

    sp_base = CAN2;
    for (flagIndex = 0; flagIndex < RANGE_OF_MB; flagIndex++)
    {
        if (((sp_base->IFLAG1) >> flagIndex) & 1U)
        {
            g_flagInterruptMB = flagIndex;
            break;
        }
    }
    s_callbackIrq_2(g_flagInterruptMB);
}

#ifdef __cplusplus
}
#endif
/*******************************************************************************
 * End of file
 ******************************************************************************/
