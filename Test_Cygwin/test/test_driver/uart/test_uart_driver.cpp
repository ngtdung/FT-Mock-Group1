/********************************************************************************
 * UNIT TEST FOR UART
 *
 * @author : HoangTM17@fpt.com
 *
 *******************************************************************************/
#include <iostream>
#include "gtest/gtest.h"
#include "S32K144.h"

#include "../../../driver/uart/include/uart_driver.h"

#define DRV_UART_CTRL_ERROR_REC_INTERRUPT_MASK 0xF000000u
#define DRV_UART_STAT_ERROR_REC_FLAG_MASK 0xF0000u
#define MAX_BAUDRATE_ERROR_PERCENT 2U
#define MAX_PARITY_COUNT_TYPE 3U
#define MAX_STOP_BIT_COUNT 2U
#define NO_USE_PARITY 0U
uint8_t TransmitCount = 0;
uint8_t ReceiveCount = 0;
uint8_t ErrorCount = 0;
LPUART_Type *s_lpuartBase[LPUART_INSTANCE_COUNT] = LPUART_BASE_PTRS;

static DRV_UART_ConfigType s_uartConfig = {
    .bitCountPerChar = DRV_UART_dataBitCount_7,
    .parityMode = DRV_UART_parityModeDisabled,
    .stopBit = DRV_UART_stopBitCountOne,
    .baudRate = DRV_UART_baudRateValue_115200,
    .transferType = DRV_UART_notUsingInterrupts,
    .clockSource = DRV_UART_fircClkSouce,
};
/* define callback fucntion */
static void ErrorCallback(void)
{
    ErrorCount++;
}
static void ErrorCallbackE(DRV_UART_StatusType error_type)
{
    ErrorCount++;
}
static void ReceiveCallback(void)
{
    ReceiveCount++;
}
static void TransmitCallBack(void)
{
    TransmitCount++;
}
/**
 * @brief This function is responsible for checking the baud rate UART acceptance range
 *
 * @param instance
 * @param BaudrateDesired
 * @param BaudrateErrorPercent
 * @return true
 * @return false
 */
bool IsCorrectBaudRateFunc(DRV_UART_BaudrateValueType BaudrateDesired, uint8_t BaudrateErrorPercent)
{
    uint8_t osr = 0;
    uint16_t sbr = 0;
    uint32_t baudRateTest = 0;
    uint32_t baudRateMax = 0;
    uint32_t baudRateMin = 0;
    uint32_t UART_SourceCLK = 48000000U;
    uint8_t ret_val = 0x01U;
    osr = (s_lpuartBase[1U]->BAUD & LPUART_BAUD_OSR_MASK) >> LPUART_BAUD_OSR_SHIFT;
    sbr = s_lpuartBase[1U]->BAUD & LPUART_BAUD_SBR_MASK;
    baudRateMin = BaudrateDesired - BaudrateDesired * BaudrateErrorPercent / 100;
    baudRateMax = BaudrateDesired + BaudrateDesired * BaudrateErrorPercent / 100;
    baudRateTest = static_cast<uint32_t>(UART_SourceCLK) / (sbr * (osr + 1U));
    if (baudRateTest < baudRateMax && baudRateTest > baudRateMin)
    {
        ret_val = true;
    }
    return ret_val;
}
/**
 * @test_id          UART_TC_01
 * @brief            Test case is responsible for checking invalid parameter of UART init function
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# configuring with all instance
 *                       -# KEY VERIFICATION_POINT check return status of UART init must be DRV_UART_error if a parameter is out of range
 *                       -# UART DeInit
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_01)
{
    DRV_UART_ConfigType *p_uart = NULL;
    DRV_UART_StatusType ret_val;
    /*@step configuring invalid instance*/
    ret_val = DRV_UART_Init(static_cast<DRV_UART_InstanceType>(5), &s_uartConfig);
    /*@step VERIFICATION_POINT check return status of UART init must be DRV_UART_error if a parameter is out of range*/
    EXPECT_EQ(ret_val, DRV_UART_error);
    /*@step UART DeInit*/
    DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(5));
    ret_val = DRV_UART_Init(static_cast<DRV_UART_InstanceType>(1), p_uart);
    /*@step KEY VERIFICATION_POINT check return status of UART init must be DRV_UART_error if a parameter is out of range*/
    EXPECT_EQ(ret_val, DRV_UART_error);
    /*@step UART DeInit*/
    DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(5));
}
/**
 * @test_id          UART_TC_02
 * @brief            Test case is to check UART Init function when setting parity type
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop for checking all parity type
 *                       -# Get parity_enable bit from register
 *                       -# KEY VERIFICATION_POINT: check parity type must be equal to expected parity type if config use parity
 *                       -# KEY VERIFICATION_POINT check parity type must be NO_USE_PARITY if didn't config to use parity
 *                       -# UART DeInit
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_02)
{
    uint8_t instance = 0;
    uint8_t ParityEnableBit = 0;

    /*@step loop for checking parity mode for EVEN mode*/
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        s_uartConfig.parityMode = DRV_UART_parityModeEven;
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step Get parity_enable bit from register */
        ParityEnableBit = (s_lpuartBase[instance]->CTRL & LPUART_CTRL_PE_MASK) >> LPUART_CTRL_PE_SHIFT;
        /*@step KEY VERIFICATION_POINT check parity type must be use parity mode EVEN if config to use parity */
        EXPECT_EQ(ParityEnableBit, 0x01U);
        EXPECT_EQ((s_lpuartBase[instance]->CTRL & LPUART_CTRL_PT_MASK) >> LPUART_CTRL_PT_SHIFT, 0x00U);
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
    }
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step Get parity_enable bit from register */
        ParityEnableBit = (s_lpuartBase[instance]->CTRL & LPUART_CTRL_PE_MASK) >> LPUART_CTRL_PE_SHIFT;
        /*@step KEY VERIFICATION_POINT check parity type must be NO_USE_PARITY didn't config to use parity */
        EXPECT_EQ(ParityEnableBit, 0x00U);
        EXPECT_EQ((s_lpuartBase[instance]->CTRL & LPUART_CTRL_PT_MASK) >> LPUART_CTRL_PT_SHIFT, 0x00U);
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
    }
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        s_uartConfig.parityMode = DRV_UART_parityModeOdd;
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step Get parity_enable bit from register */
        ParityEnableBit = (s_lpuartBase[instance]->CTRL & LPUART_CTRL_PE_MASK) >> LPUART_CTRL_PE_SHIFT;
        /*@step KEY VERIFICATION_POINT check parity type must be use parity mode EVEN if config to use parity */
        EXPECT_EQ(ParityEnableBit, 0x01U);
        EXPECT_EQ((s_lpuartBase[instance]->CTRL & LPUART_CTRL_PT_MASK) >> LPUART_CTRL_PT_SHIFT, 0x01U);
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
    }
}

/**
 * @test_id          UART_TC_03
 * @brief            Test case is to check UART Init function when configuring bit count per char
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop for setting instance
 *                       -# UART Init
 *                       -# Configure parity type: Not using parity.
 *                       -# Check all bit count per char
 *                       -# KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config does not use parity.
 *                       -# Create loop for configuring parity types odd and even.
 *                       -# Check all bit count per char
 *                       -# KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config use parity
 *                       -# UART DeInit
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_03)
{
    uint8_t instance;
    uint8_t ParityTypeIndex;
    DRV_UART_ParityModeType ParityType[3] = {DRV_UART_parityModeDisabled, DRV_UART_parityModeEven,
                                             DRV_UART_parityModeOdd};

    /*@step Create loop for setting instance*/
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        /*@step Configure parity type: Not using parity.*/
        s_uartConfig.parityMode = static_cast<DRV_UART_ParityModeType>(DRV_UART_parityModeDisabled);
        /*@step Configure number of data bit for config uart variable */
        s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_7);
        /*@step UART Init*/
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config does not use parity */
        EXPECT_EQ(0x01U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M7_MASK) >> LPUART_CTRL_M7_SHIFT);
        /*@step UART Deinit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

        /*@step Configure number of data bit for config uart variable */
        s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_8);
        /*@step UART Init*/
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config does not use parity */
        EXPECT_EQ(0x00U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M_MASK) >> LPUART_CTRL_M_SHIFT);
        /*@step UART Deinit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

        /*@step Configure number of data bit for config uart variable */
        s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_9);
        /*@step UART Init*/
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config does not use parity */
        EXPECT_EQ(0x01U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M_MASK) >> LPUART_CTRL_M_SHIFT);
        /*@step UART Deinit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

        /*@step Configure number of data bit for config uart variable */
        s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_10);
        /*@step UART Init*/
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config does not use parity */
        EXPECT_EQ(0x01U, (s_lpuartBase[instance]->BAUD & LPUART_BAUD_M10_MASK) >> LPUART_BAUD_M10_SHIFT);
        /*@step UART Deinit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

        /*@step Create loop for configuring parity types odd and even*/
        for (ParityTypeIndex = 1; ParityTypeIndex < 3; ParityTypeIndex++)
        {
            s_uartConfig.parityMode = static_cast<DRV_UART_ParityModeType>(ParityType[ParityTypeIndex]);
            /*@step Configure number of data bit for config uart variable */
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_7);
            /*@step UART Init*/
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
            /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config use parity*/
            EXPECT_EQ(0x00U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M7_MASK) >> LPUART_CTRL_M7_SHIFT);
            EXPECT_EQ(0x00U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M_MASK) >> LPUART_CTRL_M_SHIFT);
            /*@step UART Deinit*/
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

            /*@step Configure number of data bit for config uart variable */
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_8);
            /*@step UART Init*/
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
            /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config use parity*/
            EXPECT_EQ(0x01U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M_MASK) >> LPUART_CTRL_M_SHIFT);
            /*@step UART Deinit*/
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

            /*@step Configure number of data bit for config uart variable */
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_9);
            /*@step UART Init*/
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
            /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config use parity*/
            EXPECT_EQ(0x00U, (s_lpuartBase[instance]->CTRL & LPUART_CTRL_M_MASK) >> LPUART_CTRL_M_SHIFT);
            EXPECT_EQ(0x01U, (s_lpuartBase[instance]->BAUD & LPUART_BAUD_M10_MASK) >> LPUART_BAUD_M10_SHIFT);
            /*@step UART Deinit*/
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));

            /*@step Configure number of data bit for config uart variable */
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(DRV_UART_dataBitCount_10);
            /*@step UART Init*/
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
            /*@step KEY VERIFICATION_POINT: check bit count per char must be equal to expected parity type if config use parity*/
            EXPECT_EQ(0x00U, (s_lpuartBase[instance]->BAUD & LPUART_BAUD_M10_MASK) >> LPUART_BAUD_M10_SHIFT);
            /*@step UART Deinit*/
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
        }
    }
}
/**
 * @test_id          UART_TC_04
 * @brief            Test case to check receive polling process
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop to check all instance of LPUART
 *                       -# Configure number of data bit for config uart variable
 *                       -# Initialize for a instance of uart
 *                       -# Create receive flag for simulation
 *                       -# VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be DRV_UART_error
 *                       -# Receive buffer with valid buffer and length want to receive
 *                       -# KEY VERIFICATION_POINT: Check if receive process is completed
 *                       -# Receive polling with wrong number of data bits
 *                       -# VERIFICATION_POINT: Check return status when calling receive polling function with invalid number of data bit
 *                       -# De-Init for an instance of LPUART
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_04)
{
    uint8_t Buffer[4] = {'a', 'b', 'c', 'd'};
    DRV_UART_StatusType state_of_uart;
    uint8_t LpuartIndex;
    uint8_t NumDataBitTypeIndex;
    uint8_t FalseNumDataBit = 15;
    DRV_UART_DataBitCountType NumDataBit[4] = {DRV_UART_dataBitCount_7, DRV_UART_dataBitCount_8,
                                               DRV_UART_dataBitCount_9, DRV_UART_dataBitCount_10};

    /*@step Create loop to check all instance of LPUART */
    for (LpuartIndex = 0; LpuartIndex < LPUART_INSTANCE_COUNT; LpuartIndex++)
    {
        /* Configure instance of uart */
        for (NumDataBitTypeIndex = 0; NumDataBitTypeIndex < 4; NumDataBitTypeIndex++)
        {
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(NumDataBit[NumDataBitTypeIndex]);
            /*@step Initialize for a instance of uart */
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

            /*@step Create receive flag for simulation */
            s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_RDRF_MASK;

            /*@step VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be UART_ERROR */
            state_of_uart = DRV_UART_ReceiveDataPolling(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 0U);
            EXPECT_EQ(state_of_uart, DRV_UART_error);
            state_of_uart = DRV_UART_ReceiveDataPolling(static_cast<DRV_UART_InstanceType>(LpuartIndex), NULL, 4U);
            EXPECT_EQ(state_of_uart, DRV_UART_error);

            /*@step Receive buffer with valid buffer and length want to receive */
            state_of_uart = DRV_UART_ReceiveDataPolling(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 4U);
            /*@step VERIFICATION_POINT: Check if receive process is completed */
            EXPECT_EQ(state_of_uart, DRV_UART_stateReady);

            /*@step De-Init for a instance of LPUART */
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
        }

        /*@step Receive polling with wrong number of data bits*/
        s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(FalseNumDataBit);
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

        /*@step Create receive flag for simulation */
        s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_RDRF_MASK;

        /*@step Check return status when calling receive polling function */
        state_of_uart = DRV_UART_ReceiveDataPolling(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 4U);
        EXPECT_EQ(state_of_uart, DRV_UART_stateReady);
    }
}
/**
 * @test_id          UART_TC_05
 * @brief            Test case to check receive interrupt process
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop to check all instance of LPUART
 *                       -# Configure number of data bit for config uart variable
 *                       -# Initialize for a instance of uart
 *                       -# Simulate receive flag
 *                       -# Set callback function for receive and error handle process
 *                       -# VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be DRV_UART_error
 *                       -# Set up Count variable that call by callback function to check after uart process
 *                       -# Receive buffer with valid buffer and length
 *                       -# VERIFICATION_POINT: Check if receive process is completed
 *                       -# Handle process, wait for uart receive all buffer
 *                       -# KEY VERIFICATION_POINT: After handle receive process completed, only receive interrupt process has taken place
 *                       -# De-Init for a instance of LPUART
 *                       -# If uart state is not ready, status must be DRV_UART_rxBusy
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_05)
{
    uint8_t Buffer[4] = {'a', 'b', 'c', 'd'};
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    DRV_UART_StatusType state_of_uart;
    uint8_t LpuartIndex;
    uint8_t NumDataBitTypeIndex;
    DRV_UART_DataBitCountType NumDataBit[4] = {DRV_UART_dataBitCount_7, DRV_UART_dataBitCount_8,
                                               DRV_UART_dataBitCount_9, DRV_UART_dataBitCount_10};

    /*@step Create loop to check all instance of LPUART */
    for (LpuartIndex = 0; LpuartIndex < LPUART_INSTANCE_COUNT; LpuartIndex++)
    {
        /* Configure instance of uart */
        for (NumDataBitTypeIndex = 0; NumDataBitTypeIndex < 4; NumDataBitTypeIndex++)
        {
            /*@step Configure number of data bit for config uart variable */
            s_uartConfig.bitCountPerChar = static_cast<DRV_UART_DataBitCountType>(NumDataBit[NumDataBitTypeIndex]);

            /*@step Initialize for a instance of uart */
            DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

            /*@step Create receive flag for simulation */
            s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_RDRF_MASK;

            /*@step Set callback function for receive and error handle process */
            DRV_UART_InstallCallBack(DRV_UART_callBackReceiver, ReceiveCallback);
            DRV_UART_InstallCallBack(DRV_UART_callBackError, ErrorCallback);

            /*@step VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be UART_ERROR */
            state_of_uart = DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 0U);
            EXPECT_EQ(state_of_uart, DRV_UART_error);
            state_of_uart = DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), NULL, 4U);
            EXPECT_EQ(state_of_uart, DRV_UART_error);

            /*@step Set up Count variable that call by callback function to check after uart process */
            TransmitCount = 0;
            ReceiveCount = 0;
            ErrorCount = 0;

            /*@step Receive buffer with valid buffer and lenght want to receive */
            state_of_uart = DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 4U);

            /*@step VERIFICATION_POINT: Check if receive process is completed */
            EXPECT_EQ(state_of_uart, DRV_UART_rxBusy);

            /*@step Handle process, wait for UART to receive all buffer */
            for (int i = 0; i < 8; i++)
            {
                if (0U == LpuartIndex)
                {
                    LPUART0_RxTx_IRQHandler();
                }
                else if (1U == LpuartIndex)
                {
                    LPUART1_RxTx_IRQHandler();
                }
                else
                {
                    LPUART2_RxTx_IRQHandler();
                }
            }

            /*@step KEY VERIFICATION_POINT: After handling receive process has completed, only receive interrupt process has taken place */
            EXPECT_EQ(TransmitCount, 0U);
            EXPECT_EQ(ReceiveCount, 1U);
            EXPECT_EQ(ErrorCount, 0U);

            /*@step De-Init for a instance of LPUART */
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));

            /*@step If uart state is not ready, status must be UART_BUSY */
            state_of_uart = DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 4U);
            EXPECT_EQ(state_of_uart, DRV_UART_rxBusy);

            /*@step De-Init for a instance of LPUART */
            DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
        }
    }
}
/**
 * @test_id          UART_TC_06
 * @brief            Test case is to check UART Init function when configuring stop bit
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop for checking UART instances
 *                       -# Configure stop bit for UART module
 *                       -# KEY VERIFICATION_POINT: check stop bit must be equal to expected stop bit
 *                       -# UART DeInit
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_06)
{
    uint8_t instance = 0x00U;
    uint8_t reg = 0;
    /*@step Create loop for setting instance*/
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        /*@step Configure stop bit for UART module*/
        s_uartConfig.stopBit = DRV_UART_stopBitCountTwo;
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check stop bit must be equal to expected stop bit*/
        reg = (s_lpuartBase[instance]->BAUD & LPUART_BAUD_SBNS_MASK) >> LPUART_BAUD_SBNS_SHIFT;
        EXPECT_EQ(reg, 0x01u);
        /*@step UART DeInit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
    }
    for (instance = 0; instance < LPUART_INSTANCE_COUNT; instance++)
    {
        /*@step Configure stop bit for UART module*/
        s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(instance), &s_uartConfig);
        /*@step KEY VERIFICATION_POINT: check stop bit must be equal to expected stop bit*/
        reg = (s_lpuartBase[instance]->BAUD & LPUART_BAUD_SBNS_MASK) >> LPUART_BAUD_SBNS_SHIFT;
        EXPECT_EQ(reg, 0x00u);
        /*@step UART DeInit*/
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(instance));
    }
}
/**
 * @test_id          UART_TC_07
 * @brief            Test case is check UART Deinit function
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Config for initialized UART instance
 *                       -# Initialize for a instance of uart
 *                       -# Deinit uart
 *                       -# KEY VERIFICATION_POINT: Check condition after De-Init
 *                       -# Deinit uart with invalid instance
 *                       -# KEY VERIFICATION_POINT: Check condition after De-Init
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_07)
{
    uint32_t CheckControlRegister = 0;
    uint8_t LpuartIndex = 0;
    DRV_UART_StatusType CheckStatusUart;

    /*@step Config for initialize uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
    s_uartConfig.baudRate = DRV_UART_baudRateValue_115200;
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    s_uartConfig.clockSource = DRV_UART_fircClkSouce;

    /*@step Initialize for a instance of uart */
    DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

    /*@step Deinit uart */
    CheckStatusUart = DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
    CheckControlRegister = s_lpuartBase[0u]->CTRL;

    /*@step KEY VERIFICATION_POINT: Check condition after De-Init */
    EXPECT_EQ(DRV_UART_ok, CheckStatusUart);
    EXPECT_EQ(0x00000000U, CheckControlRegister);

    /*@step Deinit uart with invalid instance */
    CheckStatusUart = DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(3U));

    /*@step KEY VERIFICATION_POINT: Check condition after De-Init */
    EXPECT_EQ(DRV_UART_error, CheckStatusUart);
}
/**
 * @test_id          UART_TC_08
 * @brief            Test case is check UART abort receving function
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Config for initialize uart
 *                       -# Create loop to check all instance of LPUART
 *                       -# Initialize for an instance of UART
 *                       -# Enable receive interrupt
 *                       -# Abort receive for an instance of UART
 *                       -# KEY VERIFICATION_POINT: Check receiver flags after calling abort function
 *                       -# VERIFICATION_POINT: Check return status after calling abort receive function
 *                       -# Deinit for an instance of UART
 *
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_08)
{
    uint8_t Buffer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint8_t LpuartIndex;
    uint32_t RIE_Check;
    uint32_t RE_Check;

    DRV_UART_StatusType CheckStatusUart;
    /*@step Config for initialize uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
    s_uartConfig.baudRate = DRV_UART_baudRateValue_115200;
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    s_uartConfig.clockSource = DRV_UART_fircClkSouce;

    /*@step Create loop to check all instance of LPUART */
    for (LpuartIndex = 0; LpuartIndex < LPUART_INSTANCE_COUNT; LpuartIndex++)
    {
        /*@step Initialize for an instance of uart */
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

        /* Enable receive interrupt */
        DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 8U);

        /* Abort receive for an instance of UART */
        CheckStatusUart = DRV_UART_AbortReceiving(static_cast<DRV_UART_InstanceType>(LpuartIndex));

        /* KEY VERIFICATION_POINT: Check receiver flags after calling abort function */
        RIE_Check = s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_RIE_MASK;
        RE_Check = s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_RE_MASK;
        EXPECT_EQ(RIE_Check, 0U);
        EXPECT_EQ(RE_Check, 0U);

        /* VERIFICATION_POINT: Check return status after calling abort receive function */
        EXPECT_EQ(CheckStatusUart, DRV_UART_stateReady);

        /* Deinit for an instance of UART */
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
    }
}
/**
 * @test_id          UART_TC_09
 * @brief            Test case is check UART abort transmitting function
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Config for initialize uart
 *                       -# Create loop to check all instance of LPUART
 *                       -# Initialize for an instance of UART
 *                       -# Enable transmit interrupt
 *                       -# Abort transmitting for an instance of UART
 *                       -# KEY VERIFICATION_POINT: Check transmitter flags after calling abort function
 *                       -# VERIFICATION_POINT: Check return status after calling abort transmitting function
 *                       -# Deinit for an instance of UART
 *
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_09)
{
    uint8_t Buffer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint8_t LpuartIndex;
    uint32_t TIE_Check;
    uint32_t TE_Check;

    DRV_UART_StatusType CheckStatusUart;
    /*@step Config for initialize uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
    s_uartConfig.baudRate = DRV_UART_baudRateValue_115200;
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    s_uartConfig.clockSource = DRV_UART_fircClkSouce;

    /*@step Create loop to check all instance of LPUART */
    for (LpuartIndex = 0; LpuartIndex < LPUART_INSTANCE_COUNT; LpuartIndex++)
    {
        /*@step Initialize for an instance of uart */
        DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

        /* Enable receive interrupt */
        DRV_UART_SendDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 8U);

        /* Abort receive for an instance of UART */
        CheckStatusUart = DRV_UART_AbortTransmitting(static_cast<DRV_UART_InstanceType>(LpuartIndex));

        /* KEY VERIFICATION_POINT: Check receiver flags after calling abort function */
        TIE_Check = s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_TIE_MASK;
        TE_Check = s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_TE_MASK;
        EXPECT_EQ(TIE_Check, 0U);
        EXPECT_EQ(TE_Check, 0U);

        /* VERIFICATION_POINT: Check return status after calling abort receive function */
        EXPECT_EQ(CheckStatusUart, DRV_UART_stateReady);

        /* Deinit for an instance of UART */
        DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
    }
}
/**
 * @test_id          UART_TC_10
 * @brief            Test case is check UART install callbacks
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Config for initialize uart
 *                       -# Set callback function for receive and error handle process
 *                       -# Initialize for an instance of uart
 *                       -# Create receive flag for simulation
 *                       -# Receive interrupt for an instance of UART
 *                       -# Handle process, wait for UART to receive all buffer
 *                       -# KEY VERIFICATION_POINT: After handling receive process has completed, only receive interrupt process has taken place
 *                       -# Create transmit flag for simulation, clear receive flag
 *                       -# Transmit interrupt for an instance of UART
 *                       -# Handle process, wait for UART to send all buffer
 *                       -# KEY VERIFICATION_POINT: After handling receive process has completed, only transmit interrupt process has taken place
 *                       -# Create receiver overrun flag for simulation
 *                       -# Simulate UART transmit/receive interrupt event
 *                       -# Create noise flag for simulation
 *                       -# Simulate UART transmit/receive interrupt event
 *                       -# Create framing error flag for simulation
 *                       -# Simulate UART transmit/receive interrupt event
 *                       -# Create parity error flag for simulation
 *                       -# Simulate UART transmit/receive interrupt event
 *                       -# KEY VERIFICATION_POINT: After handling error process has completed, error callback function is called for each UART error
 *                       -# Deinit UART
 * @pass_criteria    Verification Points are successful.
 */
TEST(UART_TS_01, UART_TC_10)
{
    uint8_t Buffer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint8_t LpuartIndex = 0;
    TransmitCount = 0;
    ReceiveCount = 0;
    ErrorCount = 0;

    /*@step Config for initialize uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
    s_uartConfig.baudRate = DRV_UART_baudRateValue_115200;
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    s_uartConfig.clockSource = DRV_UART_fircClkSouce;

    /*@step Set callback function for receive and error handle process */
    DRV_UART_InstallCallBack(DRV_UART_callBackTransmitter, TransmitCallBack);
    DRV_UART_InstallCallBack(DRV_UART_callBackReceiver, ReceiveCallback);
    DRV_UART_InstallCallBack(DRV_UART_callBackError, ErrorCallback);
    DRV_UART_InstallCallBackE(ErrorCallbackE);

    /*@step Initialize for an instance of uart */
    DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

    /*@step Create receive flag for simulation */
    s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_RDRF_MASK;

    /* Receive interrupt for an instance of UART */
    DRV_UART_ReceiveDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 8U);

    /*@step Handle process, wait for UART to receive all buffer */
    for (int i = 0; i < 8; i++)
    {
        LPUART0_RxTx_IRQHandler();
    }

    /*@step VERIFICATION_POINT: After handling receive process has completed, only receive interrupt process has taken place */
    EXPECT_EQ(TransmitCount, 0U);
    EXPECT_EQ(ReceiveCount, 1U);
    EXPECT_EQ(ErrorCount, 0U);

    TransmitCount = 0;
    ReceiveCount = 0;
    ErrorCount = 0;

    /*@step Create transmit flag for simulation, clear receive flag */
    s_lpuartBase[LpuartIndex]->STAT &= ~LPUART_STAT_RDRF_MASK;
    s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_TDRE_MASK;

    /* Transmit interrupt for an instance of UART */
    DRV_UART_SendDataInterrupt(static_cast<DRV_UART_InstanceType>(LpuartIndex), Buffer, 8U);

    /*@step Handle process, wait for UART to send all buffer */
    for (int i = 0; i < 8; i++)
    {
        LPUART0_RxTx_IRQHandler();
    }

    /*@step VERIFICATION_POINT: After handling receive process has completed, only transmit interrupt process has taken place */
    EXPECT_EQ(TransmitCount, 1U);
    EXPECT_EQ(ReceiveCount, 0U);
    EXPECT_EQ(ErrorCount, 0U);

    TransmitCount = 0;
    ReceiveCount = 0;
    ErrorCount = 0;
    s_lpuartBase[LpuartIndex]->CTRL |= DRV_UART_CTRL_ERROR_REC_INTERRUPT_MASK;
    s_lpuartBase[LpuartIndex]->STAT &= ~LPUART_STAT_TDRE_MASK;

    /*@step Create default situation for simulation */
    s_lpuartBase[LpuartIndex]->STAT |= LPUART_STAT_PF_MASK;

    /*@step Simulate UART transmit/receive interrupt event */
    LPUART0_RxTx_IRQHandler();
    /*@step Create receiver overrun flag for simulation */
    s_lpuartBase[LpuartIndex]->STAT = LPUART_STAT_OR_MASK;

    /*@step Simulate UART transmit/receive interrupt event */
    LPUART0_RxTx_IRQHandler();

    /*@step Create noise flag for simulation */
    s_lpuartBase[LpuartIndex]->STAT = LPUART_STAT_NF_MASK;
    /*@step Simulate UART transmit/receive interrupt event */
    LPUART0_RxTx_IRQHandler();

    /*@step Create framing error flag for simulation */
    s_lpuartBase[LpuartIndex]->STAT = LPUART_STAT_FE_MASK;

    /*@step Simulate UART transmit/receive interrupt event */
    LPUART0_RxTx_IRQHandler();

    /*@step Create parity error flag for simulation */
    s_lpuartBase[LpuartIndex]->STAT = LPUART_STAT_PF_MASK;

    /*@step Simulate UART transmit/receive interrupt event */
    LPUART0_RxTx_IRQHandler();

    /*@step VERIFICATION_POINT: After handling error process has completed, error callback function is called for each UART error */
    EXPECT_EQ(TransmitCount, 0U);
    EXPECT_EQ(ReceiveCount, 0U);
    EXPECT_EQ(ErrorCount, 5U);

    /*@step Deinit UART */
    DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
}
/**
 * @test_id          UART_TC_11
 * @brief            Test case to check transmit interrupt and uart shall provide function to handle transmit interrupt process
 * whether is it working properly?
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_procedure   Steps:
 *                       -# Create loop to check all instances of LPUART
 *                       -# Create loop to check all Number of data types
 *                       -# Configure number of data bit for config uart variable
 *                       -# Initialize for a instance of uart
 *                       -# Create transmit flag because using simulation gg test
 *                       -# Set callback function for transmit and error handle process
 *                       -# VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be DRV_UART_error
 *                       -# Set up Count variable that call by callback function to check after uart process
 *                       -# Transmit buffer with valid buffer and lenght want to transmit
 *                       -# Handle process, wait for uart transmit all buffer
 *                       -# VERIFICATION_POINT: Check if transmit process is completed
 *                       -# KEY VERIFICATION_POINT: After handle transmit process completed, only transmit interrupt process has taken place
 *                       -# De-Init for a instance of LPUART
 *                       -# if uart state is not ready, transmit status must be DRV_UART_txBusy
 * @pass_criteria    Verification Points are successful.
 * @requirements
 * @traceability
 */
TEST(UART_TS_01, UART_TC_11)
{
    uint8_t buffer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    DRV_UART_StatusType status;
    DRV_UART_InstanceType instance[3] = {DRV_UART_instance_0, DRV_UART_instance_1, DRV_UART_instance_2};
    uint8_t uartIndex;
    uint8_t NumDataBitTypeIndex;
    DRV_UART_DataBitCountType NumDataBit[4] = {DRV_UART_dataBitCount_7, DRV_UART_dataBitCount_8,
                                               DRV_UART_dataBitCount_9, DRV_UART_dataBitCount_10};

    s_uartConfig.transferType = DRV_UART_usingInterrupts;

    /*@step Create loop to check all instance of LPUART */
    for (uartIndex = 0; uartIndex < LPUART_INSTANCE_COUNT; uartIndex++)
    {
        /*@step Create loop to check all Number of data types */
        for (NumDataBitTypeIndex = 0; NumDataBitTypeIndex < 4; NumDataBitTypeIndex++)
        {
            s_uartConfig.bitCountPerChar = NumDataBit[NumDataBitTypeIndex];

            /*@step Initialize for a instance of uart */
            DRV_UART_Init(instance[uartIndex], &s_uartConfig);

            /*@step Create transmit flag because using simulation gg test */
            s_lpuartBase[uartIndex]->STAT |= LPUART_STAT_TDRE_MASK;
            s_lpuartBase[uartIndex]->STAT |= LPUART_STAT_TC_MASK;

            /*@step Set callback function for transmit and error handle process */
            DRV_UART_InstallCallBack(DRV_UART_callBackError, ErrorCallback);
            DRV_UART_InstallCallBack(DRV_UART_callBackTransmitter, TransmitCallBack);

            /*@step Check if Buffer is Null or length is 0, status must be error */
            status = DRV_UART_SendDataInterrupt(instance[uartIndex], buffer, 0U);
            EXPECT_EQ(status, DRV_UART_error);
            status = DRV_UART_SendDataInterrupt(instance[uartIndex], NULL, 8U);
            EXPECT_EQ(status, DRV_UART_error);

            /*@step Set up Count variable that call by callback function to check after uart process */
            TransmitCount = 0;
            ReceiveCount = 0;
            ErrorCount = 0;

            /*@step Transmit buffer with valid buffer and length want to transmit */
            status = DRV_UART_SendDataInterrupt(instance[uartIndex], buffer, 8U);

            /*@step Handle process, wait for uart transmit all buffer */
            for (int i = 0; i < 8; i++)
            {
                if (0U == uartIndex)
                {
                    LPUART0_RxTx_IRQHandler();
                }
                else if (1U == uartIndex)
                {
                    LPUART1_RxTx_IRQHandler();
                }
                else
                {
                    LPUART2_RxTx_IRQHandler();
                }
            }
            /*@step VERIFICATION_POINT: Check if transmit process is completed */
            EXPECT_EQ(status, DRV_UART_txBusy);

            /*@step KEY VERIFICATION_POINT: After handle transmit process completed, only transmit interrupt process has taken place */
            EXPECT_EQ(TransmitCount, 1U);
            EXPECT_EQ(ReceiveCount, 0U);
            EXPECT_EQ(ErrorCount, 0U);

            /*@step De-Init for a instance of LPUART */
            DRV_UART_Deinit(instance[uartIndex]);

            /*@step if uart state is not ready, transmit status must be DRV_UART_txBusy */
            status = DRV_UART_SendDataInterrupt(instance[uartIndex], buffer, 8U);
            EXPECT_EQ(status, DRV_UART_txBusy);
        }
    }
}
/**
 * @test_id          UART_TC_12
 * @brief            Test case to check transmit polling
 * whether is it working properly?
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_type
 * @test_technique
 * @test_procedure   Steps:
 *                       -# Create loop to check all instance of LPUART
 *                       -# Create loop to check all Number of data types
 *                       -# Configure number of data bit for config uart variable
 *                       -# Initialize for a instance of uart
 *                       -# Create transmit flag because using simulation gg test
 *                       -# Set callback function for transmit and error handle process
 *                       -# VERIFICATION_POINT: Check if Buffer is Null or length is 0, status must be DRV_UART_error
 *                       -# Set up Count variable that call by callback function to check after uart process
 *                       -# Transmit buffer with valid buffer and lenght want to transmit
 *                       -# VERIFICATION_POINT: Check if transmit process is completed
 * @pass_criteria    Verification Points are successful.
 * @requirements
 * @traceability
 */
TEST(UART_TS_01, UART_TC_12)
{
    uint8_t buffer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    DRV_UART_StatusType status;
    DRV_UART_InstanceType instance[3] = {DRV_UART_instance_0, DRV_UART_instance_1, DRV_UART_instance_2};
    uint8_t uartIndex;
    uint8_t NumDataBitTypeIndex;
    DRV_UART_DataBitCountType NumDataBit[5] = {DRV_UART_dataBitCount_7, DRV_UART_dataBitCount_8,
                                               DRV_UART_dataBitCount_9, DRV_UART_dataBitCount_10, static_cast<DRV_UART_DataBitCountType>(0x68)};

    s_uartConfig.transferType = DRV_UART_notUsingInterrupts;

    /*@step Create loop to check all instance of LPUART */
    for (uartIndex = 0; uartIndex < LPUART_INSTANCE_COUNT; uartIndex++)
    {
        /*@step Create loop to check all Number of data types */
        for (NumDataBitTypeIndex = 0; NumDataBitTypeIndex < 5; NumDataBitTypeIndex++)
        {
            s_uartConfig.bitCountPerChar = NumDataBit[NumDataBitTypeIndex];

            /*@step Initialize for a instance of uart */
            DRV_UART_Init(instance[uartIndex], &s_uartConfig);

            /*@step Create transmit flag because using simulation gg test */
            s_lpuartBase[uartIndex]->STAT |= LPUART_STAT_TDRE_MASK;
            s_lpuartBase[uartIndex]->STAT |= LPUART_STAT_TC_MASK;

            /*@step Check if Buffer is Null or length is 0, status must be DRV_UART_error */
            status = DRV_UART_SendDataPolling(instance[uartIndex], buffer, 0U);
            EXPECT_EQ(status, DRV_UART_error);

            status = DRV_UART_SendDataPolling(instance[uartIndex], NULL, 8U);
            EXPECT_EQ(status, DRV_UART_error);

            /*@step Transmit buffer with valid buffer and length want to transmit */
            status = DRV_UART_SendDataPolling(instance[uartIndex], buffer, 8U);

            /*@step VERIFICATION_POINT: Check if transmit process is completed */
            EXPECT_EQ(status, DRV_UART_stateReady);
        }
    }
}
/**
 * @test_id          UART_TC_13
 * @brief            Test case is check enable and disable transmitter/receiver
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_type
 * @test_technique
 * @test_procedure   Steps:
 *                       -# Config for initialize uart
 *                       -# Initialize for an instance of uart
 *                       -# Enable UART transmitter
 *                       -# KEY VERIFICATION_POINT: Check TE bit in CTRL register
 *                       -# Disable UART transmitter
 *                       -# KEY VERIFICATION_POINT: Check TE bit in CTRL register
 *                       -# Enable UART receiver
 *                       -# KEY VERIFICATION_POINT: Check RE bit in CTRL register
 *                       -# Disable UART receiver
 *                       -# KEY VERIFICATION_POINT: Check RE bit in CTRL register
 *                       -# Deinit UART
 * @pass_criteria    Verification Points are successful.
 * @requirements
 * @traceability
 */
TEST(UART_TS_01, UART_TC_13)
{
    uint8_t LpuartIndex = 0;
    uint8_t TE_Check = 0;
    uint8_t RE_Check = 0;

    /*@step Config for initialize uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;
    s_uartConfig.baudRate = DRV_UART_baudRateValue_115200;
    s_uartConfig.transferType = DRV_UART_usingInterrupts;
    s_uartConfig.clockSource = DRV_UART_fircClkSouce;

    /*@step Initialize for an instance of uart */
    DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

    /*@step Enable UART transmitter */
    DRV_UART_EnableTx(static_cast<DRV_UART_InstanceType>(LpuartIndex));

    /*@step KEY VERIFICATION_POINT: Check TE bit in CTRL register */
    TE_Check = (s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_TE_MASK) >> LPUART_CTRL_TE_SHIFT;
    EXPECT_EQ(TE_Check, 1);

    /*@step Disable UART transmitter */
    DRV_UART_DisableTx(static_cast<DRV_UART_InstanceType>(LpuartIndex));

    /*@step KEY VERIFICATION_POINT: Check TE bit in CTRL register */
    TE_Check = (s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_TE_MASK) >> LPUART_CTRL_TE_SHIFT;
    EXPECT_EQ(TE_Check, 0);

    /*@step Enable UART receiver */
    DRV_UART_EnableRx(static_cast<DRV_UART_InstanceType>(LpuartIndex));

    /*@step KEY VERIFICATION_POINT: Check RE bit in CTRL register */
    RE_Check = (s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_RE_MASK) >> LPUART_CTRL_RE_SHIFT;
    EXPECT_EQ(RE_Check, 1);

    /*@step Disable UART receiver */
    DRV_UART_DisableRx(static_cast<DRV_UART_InstanceType>(LpuartIndex));

    /*@step KEY VERIFICATION_POINT: Check RE bit in CTRL register */
    RE_Check = (s_lpuartBase[LpuartIndex]->CTRL & LPUART_CTRL_RE_MASK) >> LPUART_CTRL_RE_SHIFT;
    EXPECT_EQ(RE_Check, 0);

    /*@step Deinit UART */
    DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
}
/**
 * @test_id          UART_TC_14
 * @brief            test case is created to check DRV_UART_Init function with configuring baudrate
 * @details
 * @pre              N/A
 * @post             N/A
 * @test_level       Automation Testing
 * @test_type
 * @test_technique
 * @test_procedure   Steps:
 *                       -# Configure for initalized UART.
 *                       -# Create loop to configure all UART instances.
 *                       -# Create loop to configure all baud rates.
 *                       -# Create loop to configure all clock sources.
 *                       -# Initialize UART.
 *                       -# KEY VERIFICATION_POINT: Check set Baudrate is correct.
 * @pass_criteria    Verification Points are successful.
 * @requirements
 * @traceability
 */

TEST(UART_TS_01, UART_TC_14)
{
    uint8_t LpuartIndex;
    bool IsCorrectBaudRate = false;
    uint8_t baudrate_check_index;
    uint8_t clk_src_index;

    /*@step Config for initialized uart */
    s_uartConfig.bitCountPerChar = DRV_UART_dataBitCount_8;
    s_uartConfig.parityMode = DRV_UART_parityModeDisabled;
    s_uartConfig.stopBit = DRV_UART_stopBitCountOne;

    DRV_UART_BaudrateValueType baudRateRange[3] = {DRV_UART_baudRateValue_9600,
                                                   DRV_UART_baudRateValue_12800, DRV_UART_baudRateValue_115200};

    DRV_UART_ClkSourceType clkSrc[2] = {DRV_UART_soscClkSouce, DRV_UART_fircClkSouce};

    /*@step Create loop to configure all UART instances*/
    for (LpuartIndex = 0; LpuartIndex < LPUART_INSTANCE_COUNT; LpuartIndex++)
    {
        /*@step Create loop to configure all baud rates*/
        for (baudrate_check_index = 0; baudrate_check_index < 3; baudrate_check_index++)
        {
            /*@step Create loop to configure all clock sources*/
            for (clk_src_index = 0; clk_src_index < 2; clk_src_index++)
            {
                s_uartConfig.baudRate = static_cast<DRV_UART_BaudrateValueType>(baudRateRange[baudrate_check_index]);
                s_uartConfig.clockSource = static_cast<DRV_UART_ClkSourceType>(clkSrc[clk_src_index]);

                /*@step initialize for a instance of uart */
                DRV_UART_Init(static_cast<DRV_UART_InstanceType>(LpuartIndex), &s_uartConfig);

                /*@step KEY VERIFICATION_POINT: Check set Baudrate is correct*/
                IsCorrectBaudRate = IsCorrectBaudRateFunc(s_uartConfig.baudRate, MAX_BAUDRATE_ERROR_PERCENT);
                EXPECT_EQ(IsCorrectBaudRate, true);

                /* Deinit uart */
                DRV_UART_Deinit(static_cast<DRV_UART_InstanceType>(LpuartIndex));
            }
        }
    }
}
