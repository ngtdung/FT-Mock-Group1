#include <iostream>
#include <gtest/gtest.h>
#include <pthread.h>
#include <cstring>
#include "S32K144.h"
#include "can_driver.h"

using namespace std;

#define CAN_0 (0U)
#define CAN_1 (1U)
#define CAN_2 (2U)
#define INVALID_CAN_INSTANCE (3U)

#define INV_IRQ_1 (77U)
#define INV_IRQ_2 (96U)

#define MB_TRANSMIT_INDEX (0U)
#define MB_RECEIVE_INDEX (1U)
#define MB_BROADCAST_INDEX (2U)
#define MB_INVALID_INDEX (33U)

#define WORD_SIZE (4u)
#define WORD_LENGTH (4U)
#define WORD_SIZE_INV (19U)

#define MB_MAX_DLC (8u)

#define MB_CODE_SHIFT (24U)

#define MB_STANDARD_ID_MASK ((uint32_t)(0x1FFC0000U))
#define MB_ID_FILTER ((uint32_t)(0x02U))

#define CONVERT_DATA_MESSAGE_BUFER(DATA) ((((DATA) & (0xFF << 24u)) >> 24u) | \
                                          (((DATA) & (0xFF << 16u)) >> 8u) |  \
                                          (((DATA) & (0xFF << 8u)) << 8u) |   \
                                          (((DATA) & (0xFF)) << 24u))

static FlexCAN_ID_config_MB_t s_ID_config = {
    .id = 2u,
    .prio = 3u};

static FlexCAN_control_MB_t s_controlMB = {
    .timeStamp = 0,
    .dlc = MB_MAX_DLC,
    .rtr = 0,
    .ide = 1,
    .srr = 1,
    .reserve1 = 0,
    .code = 0,
    .reserve2 = 0,
    .esi = 0,
    .brs = 0,
    .edl = 0};

static FlexCAN_TX_MessageBuffer_t s_TX_MB = {
    .cfControl = s_controlMB,
    .cfID = s_ID_config,
    .dataByte = {0xAB, 0xCD, 0xEF, 0x01, 0x02}
};

static FlexCAN_RX_MessageBuffer_t s_RX_MB = {
    .cfControl = s_controlMB,
    .cfID = s_ID_config,
    .RxIdMask = MB_STANDARD_ID_MASK,
    .RxIdFilter = MB_ID_FILTER,
};

static void *break_exit_freeze(void *argv)
{
    CAN_Type *sp_base = (CAN_Type *)argv;

    while ((sp_base->MCR & CAN_MCR_HALT_MASK) == 0)
    {
        /* Do nothing */
    }

    EXPECT_EQ(CAN_MCR_FRZ(1U), sp_base->MCR & CAN_MCR_FRZ_MASK)
        << "ERROR: CAN_MCR_FRZ is not set";

    EXPECT_EQ(CAN_MCR_HALT(1U), sp_base->MCR & CAN_MCR_HALT_MASK)
        << "ERROR: CAN_MCR_HALT is not set";

    sp_base->MCR |= (1u << CAN_MCR_FRZACK_SHIFT);

    while ((sp_base->MCR & CAN_MCR_HALT_MASK) != 0)
    {
        /* Do nothing */
    }

    EXPECT_EQ(CAN_MCR_MDIS(0U), sp_base->MCR & CAN_MCR_MDIS_MASK)
        << "ERROR: CAN_MCR_MDIS is not clear";

    EXPECT_EQ(CAN_MCR_HALT(0U), sp_base->MCR & CAN_MCR_HALT_MASK)
        << "ERROR: CAN_MCR_HALT is not clear";

    EXPECT_EQ(CAN_MCR_FRZ(0U), (sp_base->MCR & CAN_MCR_FRZ_MASK))
        << "ERROR: CAN_MCR_FRZ is not clear";

    sp_base->MCR &= ~(1u << CAN_MCR_FRZACK_SHIFT);

    for (int32_t index = 0; index < 10000; index++)
    {
        /* Do nothing */
    }

    sp_base->MCR &= ~(1u << CAN_MCR_NOTRDY_SHIFT);
    pthread_exit(NULL);
}

class CANDriver : public ::testing::Test
{
protected:
    void SetUp() override
    {
        /* Do nothing */
    }

    void TearDown() override
    {
        memset(CAN0, 0, sizeof(CAN_Type));
        memset(CAN1, 0, sizeof(CAN_Type));
        memset(CAN2, 0, sizeof(CAN_Type));
    }

    pthread_t threadID;

    static void CAN_CallbackHandler(uint8_t flagInterruptMB)
    {
        (void)flagInterruptMB;
    }

    FlexCAN_bit_timing_t s_bitTiming =
        {
            .presdiv = 0u,
            .rjw = 3u,
            .pseg1 = 3u,
            .pseg2 = 3u,
            .smp = 1u,
            .propseg = 6u};
};

/**************************************************************************/
/* Test for function FlexCAN_Init() */
/**************************************************************************/

/* Test return success and test bit timing config */
TEST_F(CANDriver, TC001)
{
    CAN0->MCR = CAN0->MCR & (~CAN_MCR_FRZACK_MASK);
    /* Check FlexCAN module is either in Normal mode, Listen-Only mode, or Loop-Back mode */
    CAN0->MCR = CAN0->MCR & (~CAN_MCR_NOTRDY_MASK);

    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;

    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    retVal = FlexCAN_Init(CAN_0, WORD_SIZE, &s_bitTiming);

    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";

    EXPECT_EQ(0x20000, CAN0->MCR) << "ERROR MCR REGISTER"; // check MCR init value

    EXPECT_EQ(0xDB0086, CAN0->CTRL1) << "ERROR CTRL1 REGISTER";
}

/* Test CAN ESR1_SYNCH to return success */
TEST_F(CANDriver, TC002)
{
    CAN0->MCR = CAN0->MCR & (~CAN_MCR_FRZACK_MASK);
    /* Check FlexCAN module is either in Normal mode, Listen-Only mode, or Loop-Back mode */
    CAN0->MCR = CAN0->MCR & (~CAN_MCR_NOTRDY_MASK);
    CAN0->ESR1 |= (CAN_ESR1_SYNCH_WIDTH << CAN_ESR1_SYNCH_SHIFT);

    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    retVal = FlexCAN_Init(CAN_0, WORD_SIZE, &s_bitTiming);

    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
}

/* FlexCAN_Init: Invalid input param */
TEST_F(CANDriver, TC003)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_Init(INVALID_CAN_INSTANCE, WORD_SIZE, &s_bitTiming))
        << "ERROR: Can not detect the invalid instance";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_Init(CAN_0, WORD_SIZE, NULL))
        << "ERROR: Can not detect the NULL input";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_Init(CAN_0, WORD_SIZE_INV, &s_bitTiming))
        << "ERROR: Can not detect the invalid word size";
}

/**************************************************************************/
/* Test for function FlexCAN_Config_Tx_MessageBuffer() */
/**************************************************************************/

/* Pass the valid CAN instance */
TEST_F(CANDriver, TC004)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure CAN 0";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_1, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure CAN 1";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_2, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure CAN 2";
}

/* Pass the valid mailbox index */
TEST_F(CANDriver, TC005)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure the transmit mailbox";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_0, MB_RECEIVE_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure the receive mailbox";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_Tx_MessageBuffer(CAN_0, MB_BROADCAST_INDEX, &s_TX_MB))
        << "ERROR: Failed to configure the broadcast mailbox";
}

/* Pass the invalid CAN instance */
TEST_F(CANDriver, TC006)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_Config_Tx_MessageBuffer(INVALID_CAN_INSTANCE, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to check the invalid arguments";
}

/* Pass the invalid mailbox index */
TEST_F(CANDriver, TC007)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_Config_Tx_MessageBuffer(CAN_0, MB_INVALID_INDEX, &s_TX_MB))
        << "ERROR: Failed to check the invalid arguments";
}

/* Test for data CAN_RAMn */
TEST_F(CANDriver, TC008)
{
    uint32_t g_flagIndex = 1;
    FlexCAN_TX_MessageBuffer_t msgBuffer;
    msgBuffer.cfControl.srr = 1U;
    msgBuffer.cfControl.ide = 1U;
    msgBuffer.cfControl.edl = 0U;
    msgBuffer.cfControl.brs = 0U;
    msgBuffer.cfControl.esi = 0U;
    msgBuffer.cfControl.rtr = 0U;
    msgBuffer.cfControl.dlc = MB_MAX_DLC;
    msgBuffer.cfID.id = 2U;
    msgBuffer.cfID.prio = 0U;
    msgBuffer.dataByte[0] = 0XAB;
    msgBuffer.dataByte[1] = 0XCD;
    msgBuffer.dataByte[2] = 0XEF;

    uint32_t *DataOfMB = (uint32_t *)&msgBuffer;
    *DataOfMB |= (CODE_SEND << MB_CODE_SHIFT);

    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Init(CAN_0, WORD_SIZE, &s_bitTiming);
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    retVal = FlexCAN_Config_Tx_MessageBuffer(CAN_0, g_flagIndex, &msgBuffer);

    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ(CAN0->RAMn[g_flagIndex * 4 + 0], *DataOfMB);
    EXPECT_EQ(CAN0->RAMn[g_flagIndex * 4 + 1], *(DataOfMB + 1));
}

/* Test for data CAN_RAMn */
TEST_F(CANDriver, TC009)
{
    uint32_t g_flagIndex = 1;

    uint32_t *DataOfMB = (uint32_t *)&s_TX_MB;
    *DataOfMB |= (CODE_SEND << MB_CODE_SHIFT);

    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Init(CAN_0, WORD_SIZE, &s_bitTiming);
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    retVal = FlexCAN_Config_Tx_MessageBuffer(CAN_0, g_flagIndex, &s_TX_MB);

    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ(CAN0->RAMn[g_flagIndex * 4 + 0], *DataOfMB);
    EXPECT_EQ(CAN0->RAMn[g_flagIndex * 4 + 1], *(DataOfMB + 1));
}

/**************************************************************************/
/* Test for function FlexCAN_Config_RX_MessageBuffer() */
/**************************************************************************/

/* Test return*/
TEST_F(CANDriver, TC010)
{
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Config_RX_MessageBuffer(CAN_0, MB_RECEIVE_INDEX, &s_RX_MB))
        << "ERROR: Failed to return for function FlexCAN_Config_RX_MessageBuffer";
}

/* Test data register */
TEST_F(CANDriver, TC011)
{

    EXPECT_EQ((((CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F),
              CODE_INACTIVE_RX)
        << "ERROR: Failed not EQ CODE inactive";

    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] |= (0x0F << MB_CODE_SHIFT);
    FlexCAN_Config_RX_MessageBuffer(CAN_0, MB_RECEIVE_INDEX, &s_RX_MB);

    EXPECT_NE((((CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F),
              CODE_INACTIVE_RX)
        << "ERROR: Failed to return for function FlexCAN_Config_RX_MessageBuffer";

    EXPECT_EQ(CAN0->RXMGMASK, s_RX_MB.RxIdMask)
        << "ERROR: Failed ID MASK in function FlexCAN_Config_RX_MessageBuffer";

    EXPECT_EQ(CAN0->RXIMR[MB_RECEIVE_INDEX], s_RX_MB.RxIdFilter)
        << "ERROR: Failed ID Filter in function FlexCAN_Config_RX_MessageBuffer";

    EXPECT_EQ(CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_ID_OF_MB], s_RX_MB.cfID.id)
        << "ERROR: Failed ID in function FlexCAN_Config_RX_MessageBuffer";
}

/* Test check invalid instance */
TEST_F(CANDriver, TC012)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_Config_RX_MessageBuffer(INVALID_CAN_INSTANCE, MB_RECEIVE_INDEX, &s_RX_MB))
        << "ERROR: Failed to return for function FlexCAN_Config_RX_MessageBuffer";
}

/* Test check return code fail */
TEST_F(CANDriver, TC013)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;

    retVal = FlexCAN_Config_RX_MessageBuffer(CAN_0, MB_INVALID_INDEX, &s_RX_MB);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL, retVal) << "ERROR: Failed to return for function FlexCAN_Config_RX_MessageBuffer";
}
/**************************************************************************/

/**************************************************************************/
/* Test for function FlexCAN_Send() */
/**************************************************************************/
/* Test return */
TEST_F(CANDriver, TC014)
{

    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to return the send mailbox";
}

/* Test whether MB is active */
TEST_F(CANDriver, TC015)
{
    uint8_t g_CodeMB;
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB);
    g_CodeMB = ((CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB]) >> MB_CODE_SHIFT) & 0x0F;
    EXPECT_NE(g_CodeMB, CODE_INACTIVE_TX) << "ERROR: code inactive TX";
    EXPECT_NE(g_CodeMB, CODE_ABORT_TRANSMISSION) << "ERROR: code abort transmission";
    EXPECT_NE(g_CodeMB, CODE_INACTIVE_RX) << "ERROR: code inactive RX";
}

/* Test the corresponding IFLAG bit to be asserted */
TEST_F(CANDriver, TC016)
{
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB);
    EXPECT_NE((CAN0->IFLAG1) & (0x1 << MB_TRANSMIT_INDEX), 0) << "ERROR: IFLAG bit not set";
}

/* Test check invalid instance */
TEST_F(CANDriver, TC017)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
                FlexCAN_Send(INVALID_CAN_INSTANCE, MB_TRANSMIT_INDEX, &s_TX_MB))
        << "ERROR: Failed to return for function FlexCAN_Send";
}

/* Test inactive for function FlexCAN_Send() */
TEST_F(CANDriver, TC018)
{
    /* Cover tacken  */
    CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] |= (0x0F << MB_CODE_SHIFT);
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB);

    CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
    CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] |= (CODE_INACTIVE_TX << MB_CODE_SHIFT);
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB);

    CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] &= ~(MB_CODE_MASK);
    CAN0->RAMn[MB_TRANSMIT_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] |= (CODE_ABORT_TRANSMISSION << MB_CODE_SHIFT);
    pthread_create(&threadID, NULL, break_exit_freeze, (void *)CAN0);
    FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, &s_TX_MB);

    /* Check return code fail */
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_Send(CAN_0, MB_TRANSMIT_INDEX, NULL))
        << "ERROR: Failed to return for function FlexCAN_Send";
}
/**************************************************************************/

/**************************************************************************/
/* Test for function FlexCAN_Receive() */
/**************************************************************************/
/* Test return */
TEST_F(CANDriver, TC019)
{
    FlexCAN_TX_MessageBuffer_t g_Data;
    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] |= (MB_MAX_DLC << MB_DLC_SHIFT);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_Receive(CAN_0, MB_RECEIVE_INDEX, &g_Data))
        << "ERROR: Failed to return for function FlexCAN_Receive";
}

TEST_F(CANDriver, TC020)
{
    FlexCAN_TX_MessageBuffer_t g_Data;
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_Receive(INVALID_CAN_INSTANCE, MB_RECEIVE_INDEX, &g_Data))
        << "ERROR: Failed to return for function FlexCAN_Receive";
}

TEST_F(CANDriver, TC021)
{
    FlexCAN_TX_MessageBuffer_t g_Data;

    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_Receive(CAN_0, MB_INVALID_INDEX, &g_Data))
        << "ERROR: Failed to return for function FlexCAN_Receive";
}

/* Test data receive */
TEST_F(CANDriver, TC022)
{
    FlexCAN_TX_MessageBuffer_t g_DataReceive;
    /* Imitate message bufer */
    uint32_t *DataOfMB = (uint32_t *)&s_TX_MB;
    *DataOfMB |= (CODE_SEND << MB_CODE_SHIFT);

    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] = *DataOfMB;
    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_ID_OF_MB] = *(DataOfMB + 1);
    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_DATA_START_OF_MB] = CONVERT_DATA_MESSAGE_BUFER(*(DataOfMB + 2));
    CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_DATA_START_OF_MB + 1] = CONVERT_DATA_MESSAGE_BUFER(*(DataOfMB + 3));

    /* Call FlexCAN_Receive and receive data */
    FlexCAN_Receive(CAN_0, MB_RECEIVE_INDEX, &g_DataReceive);
    uint32_t *Data = (uint32_t *)&g_DataReceive;

    /* Test */
    EXPECT_EQ(g_DataReceive.cfID.id, (CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_ID_OF_MB] & MB_ID_MASK) >> MB_ID_SHIFT)
        << "ERROR: Failed data id receive";
    EXPECT_EQ(g_DataReceive.cfID.prio, 0)
        << "ERROR: Failed data prio receive";
    EXPECT_EQ(g_DataReceive.cfControl.dlc, (CAN0->RAMn[MB_RECEIVE_INDEX * WORD_LENGTH + OFFSET_START_OF_MB] & MB_DLC_MASK) >> MB_DLC_SHIFT)
        << "ERROR: Failed data dlc receive";
    EXPECT_EQ(*(Data + 2), *(DataOfMB + 2))
        << "ERROR: Failed data receive";
    EXPECT_EQ(*(Data + 3), *(DataOfMB + 3))
        << "ERROR: Failed data receive";
}
/**************************************************************************/

/**************************************************************************/
/* Test for function FlexCAN_ConfigInterrupt() */
/**************************************************************************/
/* Test register data */
TEST_F(CANDriver, TC023)
{
    uint32_t g_flagIndex = 1;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;

    /* INSTANCE 1 */
    pthread_create(&threadID, NULL, break_exit_freeze, (void*)CAN1);
    retVal = FlexCAN_ConfigInterrupt(CAN_1, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal)
    << "ERROR SUCCESS";
    EXPECT_EQ((CAN1->IMASK1) & (1 << g_flagIndex), (1 << g_flagIndex))
    << "ERROR: enable interrupt";

}

/* Test register data */
TEST_F(CANDriver, TC024)
{
    uint32_t g_flagIndex = 1;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;

    /* INSTANCE 2 */
    pthread_create(&threadID, NULL, break_exit_freeze, (void*)CAN2);
    retVal = FlexCAN_ConfigInterrupt(CAN_2, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ((CAN2->IMASK1) & (1 << g_flagIndex), (1 << g_flagIndex))
    << "ERROR: enable interrupt";

}

/* FlexCAN_ConfigInterrupt: Pass the invalid param */
TEST_F(CANDriver, TC0025)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_ConfigInterrupt(INVALID_CAN_INSTANCE, MB_RECEIVE_INDEX))
        << "ERROR: Can not check the wrong instance";
}

/**************************************************************************/
/* Test for function FlexCAN_ClearInterruptFlag() */
/**************************************************************************/
/* Test Can instance */
TEST_F(CANDriver, TC026)
{
    uint32_t g_flagIndex = 1;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    /* INSTANCE 0 */
    retVal = FlexCAN_ClearInterruptFlag(CAN_0, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ((CAN0->IFLAG1) & (1 << g_flagIndex), (1 << g_flagIndex)) << "ERROR: Clear interrupt flag";

    /* INSTANCE 1 */
    retVal = FlexCAN_ClearInterruptFlag(CAN_1, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ((CAN1->IFLAG1) & (1 << g_flagIndex), (1 << g_flagIndex)) << "ERROR: Clear interrupt flag";

    /* INSTANCE 2 */
    retVal = FlexCAN_ClearInterruptFlag(CAN_2, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS, retVal) << "ERROR SUCCESS";
    EXPECT_EQ((CAN2->IFLAG1) & (1 << g_flagIndex), (1 << g_flagIndex)) << "ERROR: Clear interrupt flag";
}

/* Test invalid can instance */
TEST_F(CANDriver, TC027)
{
    uint32_t g_flagIndex = 1;
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    /* INSTANCE 0 */
    retVal = FlexCAN_ClearInterruptFlag(INVALID_CAN_INSTANCE, g_flagIndex);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS, retVal) << "ERROR SUCCESS";
}

/* Test invalid index */
TEST_F(CANDriver, TC028)
{
    FlexCAN_ReturnCode_t retVal = FLEXCAN_RETURN_CODE_FAIL;
    /* INSTANCE 0 */
    retVal = FlexCAN_ClearInterruptFlag(CAN_0, MB_INVALID_INDEX);
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL, retVal) << "ERROR SUCCESS";
}
/**************************************************************************/

/**************************************************************************/
/* FlexCAN_InitIRQ(): pass the valid param */
/**************************************************************************/
TEST_F(CANDriver, TC029)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_InitIRQ(CAN_0, CAN0_ORed_0_15_MB_IRQn, CAN_CallbackHandler))
        << "ERROR: Init IRQ failed";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_InitIRQ(CAN_1, CAN1_ORed_0_15_MB_IRQn, CAN_CallbackHandler))
        << "ERROR: Init IRQ failed";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_SUCCESS,
              FlexCAN_InitIRQ(CAN_2, CAN2_ORed_0_15_MB_IRQn, CAN_CallbackHandler))
        << "ERROR: Init IRQ failed";
}

/**************************************************************************/
/* FlexCAN_InitIRQ(): pass the invalid param */
/**************************************************************************/
TEST_F(CANDriver, TC030)
{
    EXPECT_EQ(FLEXCAN_RETURN_CODE_INVALID_INS,
              FlexCAN_InitIRQ(INVALID_CAN_INSTANCE, CAN0_ORed_0_15_MB_IRQn, CAN_CallbackHandler))
        << "ERROR: Can not check the wrong instance";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_InitIRQ(CAN_0, (IRQn_Type)INV_IRQ_1, CAN_CallbackHandler))
        << "ERROR: Can not check the wrong IRQ type";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_InitIRQ(CAN_0, (IRQn_Type)INV_IRQ_2, CAN_CallbackHandler))
        << "ERROR: Can not check the wrong IRQ type";
    EXPECT_EQ(FLEXCAN_RETURN_CODE_FAIL,
              FlexCAN_InitIRQ(CAN_0, CAN0_ORed_0_15_MB_IRQn, NULL))
        << "ERROR: Can not check NULL function";
}

/**************************************************************************/
/* Test CAN0_ORed_0_15_MB_IRQHandler */
/**************************************************************************/
TEST_F(CANDriver, TC031)
{
    uint8_t flagIndex = 3u;

    CAN0->IFLAG1 |= (1 << flagIndex);
    FlexCAN_InitIRQ(CAN_0, CAN0_ORed_0_15_MB_IRQn, CAN_CallbackHandler);
    CAN0_ORed_0_15_MB_IRQHandler();
}

/**************************************************************************/
/* Test CAN1_ORed_0_15_MB_IRQHandler */
/**************************************************************************/
TEST_F(CANDriver, TC032)
{
    uint8_t flagIndex = 3u;

    CAN1->IFLAG1 |= (1 << flagIndex);
    FlexCAN_InitIRQ(CAN_1, CAN1_ORed_0_15_MB_IRQn, CAN_CallbackHandler);
    CAN1_ORed_0_15_MB_IRQHandler();
}

/**************************************************************************/
/* Test CAN2_ORed_0_15_MB_IRQHandler */
/**************************************************************************/
TEST_F(CANDriver, TC033)
{
    uint8_t flagIndex = 3u;

    CAN2->IFLAG1 |= (1 << flagIndex);
    FlexCAN_InitIRQ(CAN_2, CAN2_ORed_0_15_MB_IRQn, CAN_CallbackHandler);
    CAN2_ORed_0_15_MB_IRQHandler();
}

/**************************************************************************/
/* CAN0_ORed_0_15_MB_IRQHandler: cover injection branch */
/**************************************************************************/
TEST_F(CANDriver, TC034)
{
    CAN0->IFLAG1 = 0u;
    CAN0_ORed_0_15_MB_IRQHandler();
}

/**************************************************************************/
/* CAN1_ORed_0_15_MB_IRQHandler: cover injection branch */
/**************************************************************************/
TEST_F(CANDriver, TC035)
{
    CAN0->IFLAG1 = 0u;
    CAN1_ORed_0_15_MB_IRQHandler();
}

/**************************************************************************/
/* CAN2_ORed_0_15_MB_IRQHandler: cover injection branch */
/**************************************************************************/
TEST_F(CANDriver, TC036)
{
    CAN0->IFLAG1 = 0u;
    CAN2_ORed_0_15_MB_IRQHandler();
}


