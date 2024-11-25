/*
 * test_lpit_driver.cpp
 *
 *  Created on: Nov 21, 2024
 *      Author: HI
 */
/*******************************************************************************
* Include
*******************************************************************************/
#include <iostream>
#include <stdbool.h>
#include "gtest/gtest.h"
#include <pthread.h>
#include <cstring>
#include "S32K144.h"
#include "Drv_Lpit.h"
using namespace std;

/*******************************************************************************
* Definitions
*******************************************************************************/
/* Define an invalid LPIT channel for boundary testing */
#define LPIT_CHANNEL_INVALID     4U

/*******************************************************************************
* Api
*******************************************************************************/
/* Callback function prototype for LPIT interrupt handling */
static void LPIT_Driver_CallBack(uint8_t channel);

/*******************************************************************************
* Variables
*******************************************************************************/

/* Flags to verify callback function execution for each channel */
static uint8_t testCallback_channel0 = false;
static uint8_t testCallback_channel1 = false;
static uint8_t testCallback_channel2 = false;
static uint8_t testCallback_channel3 = false;

/* Configuration structure for LPIT initialization */
LpitConfigType LPIT_Config = {
        .debug_en       = LPIT_DEBUG_MODE_ENABLE, /* Enable debug mode */
        .doze_en        = LPIT_DOZE_MODE_ENABLE, /* Enable doze mode */
        .timer_mode     = LPIT_PERIODIC_CNT, /* Set periodic timer mode */
        .callback       = LPIT_Driver_CallBack /* Set callback function */
};

/*******************************************************************************
* Code
*******************************************************************************/

/* Test class for LPIT driver */
class LPITDriver : public ::testing::Test
{
protected:
    /* Setup function executed before each test case */
    void SetUp() override
    {
    }

    /* Teardown function executed after each test case */
    void TearDown() override
    {
        /* Clear the LPIT registers for testing */
        memset(IP_LPIT0, 0, sizeof(LPIT_Type));
    }
};

/* Callback function to handle LPIT interrupts */
void LPIT_Driver_CallBack(uint8_t channel)
{
    switch (channel)
    {
        case 0: /* Handle callback for channel 0 */
        {
            testCallback_channel0 = true;
            break;
        }

        case 1: /* Handle callback for channel 1 */
        {
            testCallback_channel1 = true;
            break;
        }

        case 2: /* Handle callback for channel 2 */
        {
            testCallback_channel2 = true;
            break;
        }

        case 3: /* Handle callback for channel 3 */
        {
            testCallback_channel3 = true;
            break;
        }

        default: /* Default case for invalid channels */
            break;
    }
}

/* Test Case 001: Verify LPIT initialization for a single channel */
TEST(LPITDriver, TC001)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */
    uint8_t idx = 0;

    /* Array to store LPIT channel configuration */
    LpitChannelType LPIT_Channel_Config[] = {LPIT_CHANNEL_0};

    /* Array to store LPIT interrupt configuration */
    LpitInterruptType LPIT_IntChannel[] = {LPIT_IRQ_CHANNEL_0};

    /* Configure channels */
    LPIT_Config.channel        = LPIT_Channel_Config;
    /* Number of channels */
    LPIT_Config.num_of_channel = (sizeof(LPIT_Channel_Config) / sizeof(LPIT_Channel_Config[0]));

    /* Configure interrupts */
    LPIT_Config.interrupt      = LPIT_IntChannel;
    /* Number of interrupts */
    LPIT_Config.num_of_interrupt = (sizeof(LPIT_IntChannel) / sizeof(LPIT_IntChannel[0]));

    /* Call LPIT initialization function */
    statusFunc = DRV_LPIT_Init(LPIT_INS_0, &LPIT_Config);

    /* Validate successful initialization */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 Driver Status not Successed ";
    EXPECT_EQ(0x0DU, IP_LPIT0->MCR) << "ERROR : Config module control register ";
    EXPECT_EQ(0x01U, IP_LPIT0->MIER) << "ERROR : Config Module Interrupt Enable Register ";

    /* Validate configuration for each channel */
    for (idx = 0; idx < LPIT_Config.num_of_channel; idx ++)
    {
        EXPECT_TRUE(LPIT_Config.channel[idx] < LPIT_CHANNEL_INVALID) << "ERROR: LPIT Channel ";
        EXPECT_EQ(0x00U, (IP_LPIT0->TMR[LPIT_Config.channel[idx]].TCTRL)) << "ERROR : Config Time control for Channel ";
    }
}

/* Test Case 002: Verify LPIT initialization for two channels */
TEST(LPITDriver, TC002)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */
    uint8_t idx = 0;

    /* Array to store LPIT channel configuration */
    LpitChannelType LPIT_Channel_Config[] = {LPIT_CHANNEL_0, LPIT_CHANNEL_1};

    /* Array to store LPIT interrupt configuration */
    LpitInterruptType LPIT_IntChannel[] = {LPIT_IRQ_CHANNEL_0, LPIT_IRQ_CHANNEL_1};

    /* Configure channels */
    LPIT_Config.channel        = LPIT_Channel_Config;
    /* Number of channels */
    LPIT_Config.num_of_channel = (sizeof(LPIT_Channel_Config) / sizeof(LPIT_Channel_Config[0]));

    /* Configure interrupts */
    LPIT_Config.interrupt      = LPIT_IntChannel;
    /* Number of interrupts */
    LPIT_Config.num_of_interrupt = (sizeof(LPIT_IntChannel) / sizeof(LPIT_IntChannel[0]));

    /* Call LPIT initialization function */
    statusFunc = DRV_LPIT_Init(LPIT_INS_0, &LPIT_Config);

    /* Validate successful initialization */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 Driver Status not Successed ";
    EXPECT_EQ(0x0DU, IP_LPIT0->MCR) << "ERROR : Config module control register ";
    EXPECT_EQ(0x03U, IP_LPIT0->MIER) << "ERROR : Config Module Interrupt Enable Register ";

    /* Validate configuration for each channel */
    for (idx = 0; idx < LPIT_Config.num_of_channel; idx ++)
    {
        EXPECT_TRUE(LPIT_Config.channel[idx] < LPIT_CHANNEL_INVALID) << "ERROR: LPIT Channel ";
        EXPECT_EQ(0x00U, (IP_LPIT0->TMR[LPIT_Config.channel[idx]].TCTRL)) << "ERROR : Config Time control for Channel ";
    }
}

/* Test Case 002: Verify LPIT initialization for three channels */
TEST(LPITDriver, TC003)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */
    uint8_t idx = 0;

    /* Array to store LPIT channel configuration */
    LpitChannelType LPIT_Channel_Config[] = {LPIT_CHANNEL_0, LPIT_CHANNEL_1, LPIT_CHANNEL_2};

    /* Array to store LPIT interrupt configuration */
    LpitInterruptType LPIT_IntChannel[] = {LPIT_IRQ_CHANNEL_0, LPIT_IRQ_CHANNEL_1, LPIT_IRQ_CHANNEL_2};

    /* Configure channels */
    LPIT_Config.channel        = LPIT_Channel_Config;
    /* Number of channels */
    LPIT_Config.num_of_channel = (sizeof(LPIT_Channel_Config) / sizeof(LPIT_Channel_Config[0]));

    /* Configure interrupts */
    LPIT_Config.interrupt      = LPIT_IntChannel;
    /* Number of interrupts */
    LPIT_Config.num_of_interrupt = (sizeof(LPIT_IntChannel) / sizeof(LPIT_IntChannel[0]));

    /* Call LPIT initialization function */
    statusFunc = DRV_LPIT_Init(LPIT_INS_0, &LPIT_Config);

    /* Validate successful initialization */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 Driver Status not Successed ";
    EXPECT_EQ(0x0DU, IP_LPIT0->MCR) << "ERROR : Config module control register ";
    EXPECT_EQ(0x07U, IP_LPIT0->MIER) << "ERROR : Config Module Interrupt Enable Register ";

    /* Validate configuration for each channel */
    for (idx = 0; idx < LPIT_Config.num_of_channel; idx ++)
    {
        EXPECT_TRUE(LPIT_Config.channel[idx] < LPIT_CHANNEL_INVALID) << "ERROR: LPIT Channel ";
        EXPECT_EQ(0x00U, (IP_LPIT0->TMR[LPIT_Config.channel[idx]].TCTRL)) << "ERROR : Config Time control for Channel ";
    }
}

/* Test Case 002: Verify LPIT initialization for four channels */
TEST(LPITDriver, TC004)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */
    uint8_t idx = 0;

    /* Array to store LPIT channel configuration */
    LpitChannelType LPIT_Channel_Config[] = {LPIT_CHANNEL_0, LPIT_CHANNEL_1, LPIT_CHANNEL_2, LPIT_CHANNEL_3};

    /* Array to store LPIT interrupt configuration */
    LpitInterruptType LPIT_IntChannel[] = {LPIT_IRQ_CHANNEL_0, LPIT_IRQ_CHANNEL_1, LPIT_IRQ_CHANNEL_2, LPIT_IRQ_CHANNEL_3};

    /* Configure channels */
    LPIT_Config.channel        = LPIT_Channel_Config;
    /* Number of channels */
    LPIT_Config.num_of_channel = (sizeof(LPIT_Channel_Config) / sizeof(LPIT_Channel_Config[0]));

    /* Configure interrupts */
    LPIT_Config.interrupt      = LPIT_IntChannel;
    /* Number of interrupts */
    LPIT_Config.num_of_interrupt = (sizeof(LPIT_IntChannel) / sizeof(LPIT_IntChannel[0]));

    /* Call LPIT initialization function */
    statusFunc = DRV_LPIT_Init(LPIT_INS_0, &LPIT_Config);

    /* Validate successful initialization */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 Driver Status not Successed ";
    EXPECT_EQ(0x0DU, IP_LPIT0->MCR) << "ERROR : Config module control register ";
    EXPECT_EQ(0x0FU, IP_LPIT0->MIER) << "ERROR : Config Module Interrupt Enable Register ";

    /* Validate configuration for each channel */
    for (idx = 0; idx < LPIT_Config.num_of_channel; idx ++)
    {
        EXPECT_TRUE(LPIT_Config.channel[idx] < LPIT_CHANNEL_INVALID) << "ERROR: LPIT Channel ";
        EXPECT_EQ(0x00U, (IP_LPIT0->TMR[LPIT_Config.channel[idx]].TCTRL)) << "ERROR : Config Time control for Channel ";
    }
}

/* Test Case 003: Verify starting the timer for channel 0 */
TEST(LPITDriver, TC005)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */

    /* Start the timer for channel 0 */
    statusFunc = DRV_LPIT_StartTimer(LPIT_INS_0, LPIT_CHANNEL_0, 0x10000U);

    /* Validate successful timer start */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 channel 0 startup failed ";
    EXPECT_EQ((0x10000U - 1U), (IP_LPIT0->TMR[LPIT_CHANNEL_0].TVAL)) << "ERROR : Set timer value ";
    EXPECT_EQ(0x01U, (IP_LPIT0->TMR[LPIT_CHANNEL_0].TCTRL)) << "ERROR : Enable timer channel 0 ";
}

/* Test Case 004: Verify stopping the timer for channel 0 */
TEST(LPITDriver, TC006)
{
    LpitStatusType statusFunc = LPIT_STT_FAIL; /* Initialize status */

    /* Stop the timer for channel 0 */
    statusFunc = DRV_LPIT_StopTimer(LPIT_INS_0, LPIT_CHANNEL_0);

    /* Validate successful timer stop */
    EXPECT_EQ(LPIT_STT_SUCCESS, statusFunc) << "ERROR : LPIT0 channel 0 stop failed ";
    EXPECT_EQ(0x00U, (IP_LPIT0->TMR[LPIT_CHANNEL_0].TCTRL)) << "ERROR : Disable timer channel 0 ";
}

/* Test Case 005: Verify callback execution for channel 0 */
TEST(LPITDriver, TC007)
{
    IP_LPIT0->MSR |= (1U << LPIT_CHANNEL_0); /* Simulate interrupt for channel 0 */
    LPIT0_Ch0_IRQHandler(); /* Call interrupt handler */

    /* Validate callback function execution */
    EXPECT_EQ(true, testCallback_channel0) << "ERROR : LPIT0 channel 0 callback function ";
}

/* Test Case 006: Verify callback execution for channel 1 */
TEST(LPITDriver, TC008)
{
    IP_LPIT0->MSR |= (1U << LPIT_CHANNEL_1); /* Simulate interrupt for channel 1 */
    LPIT0_Ch1_IRQHandler(); /* Call interrupt handler */

    /* Validate callback function execution */
    EXPECT_EQ(true, testCallback_channel1) << "ERROR : LPIT0 channel 1 callback function ";
}

/* Test Case 006: Verify callback execution for channel 2 */
TEST(LPITDriver, TC009)
{
    IP_LPIT0->MSR |= (1U << LPIT_CHANNEL_2); /* Simulate interrupt for channel 2 */
    LPIT0_Ch2_IRQHandler(); /* Call interrupt handler */

    /* Validate callback function execution */
    EXPECT_EQ(true, testCallback_channel2) << "ERROR : LPIT0 channel 2 callback function ";
}

/* Test Case 006: Verify callback execution for channel 3 */
TEST(LPITDriver, TC010)
{
    IP_LPIT0->MSR |= (1U << LPIT_CHANNEL_3); /* Simulate interrupt for channel 3 */
    LPIT0_Ch3_IRQHandler(); /* Call interrupt handler */

    /* Validate callback function execution */
    EXPECT_EQ(true, testCallback_channel3) << "ERROR : LPIT0 channel 3 callback function ";
}

/*******************************************************************************
* end of file
*******************************************************************************/
