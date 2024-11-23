/********************************************************************************
 * UNIT TEST FOR GPIO
 *
 * @author : Group1 tester
 *
 *******************************************************************************/

#include <iostream>
#include "gtest/gtest.h"
#include "S32K144.h"
#include "GPIO_Driver.h"

using namespace std;



class GPIODriver : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
		memset(IP_PTA, 0, sizeof(GPIO_Type));
		memset(IP_PTB, 0, sizeof(GPIO_Type));
        memset(IP_PTC, 0, sizeof(GPIO_Type));
        memset(IP_PTD, 0, sizeof(GPIO_Type));
        memset(IP_PTE, 0, sizeof(GPIO_Type));
	}
};

/*============================= TEST GPIO INIT ================================= */

/********************************************************************************
 * Test case TC001-TC005
 * @details : Configuaration with request from user
 *
 *******************************************************************************/

/*============================== Config with GPIO ==============================*/

/* PORT A */
TEST(GPIODriver, TC001)
{
    GPIO_PinConfig_type pConfig =
    {
        .pinCode = 0x0A,
        .pinMode = GPIO_PIN_MODE_OUTPUT
    };

    DRV_GPIO_ReturnCode_type status0 = DRV_GPIO_PinModeConfig(&pConfig);

    EXPECT_EQ(DRV_GPIO_RETURN_CODE_SUCCESSED, status0) << "ERROR: Init Driver Status not Successed";

    EXPECT_TRUE(IP_PTA->PDDR & GPIO_PDDR_PDD_MASK) << "ERROR: Pin output not set";
}

/* PORT B */
TEST(GPIODriver, TC002)
{
    GPIO_PinConfig_type pConfig =
    {
        .pinCode = 0x2A,
        .pinMode = GPIO_PIN_MODE_OUTPUT
    };

    DRV_GPIO_ReturnCode_type status0 = DRV_GPIO_PinModeConfig(&pConfig);

    EXPECT_EQ(DRV_GPIO_RETURN_CODE_SUCCESSED, status0) << "ERROR: Init Driver Status not Successed";

    EXPECT_TRUE(IP_PTB->PDDR & GPIO_PDDR_PDD_MASK) << "ERROR: Pin output not set";
}

/* PORT C */
TEST(GPIODriver, TC003)
{
    GPIO_PinConfig_type pConfig =
    {
        .pinCode = 0x4A,
        .pinMode = GPIO_PIN_MODE_OUTPUT
    };

    DRV_GPIO_ReturnCode_type status0 = DRV_GPIO_PinModeConfig(&pConfig);

    EXPECT_EQ(DRV_GPIO_RETURN_CODE_SUCCESSED, status0) << "ERROR: Init Driver Status not Successed";

    EXPECT_TRUE(IP_PTC->PDDR & GPIO_PDDR_PDD_MASK) << "ERROR: Pin output not set";
}

/* PORT D */
TEST(GPIODriver, TC004)
{
    GPIO_PinConfig_type pConfig =
    {
        .pinCode = 0x6A,
        .pinMode = GPIO_PIN_MODE_OUTPUT
    };

    DRV_GPIO_ReturnCode_type status0 = DRV_GPIO_PinModeConfig(&pConfig);

    EXPECT_EQ(DRV_GPIO_RETURN_CODE_SUCCESSED, status0) << "ERROR: Init Driver Status not Successed";

    EXPECT_TRUE(IP_PTD->PDDR & GPIO_PDDR_PDD_MASK) << "ERROR: Pin output not set";
}


/* PORT E */
TEST(GPIODriver, TC005)
{
    GPIO_PinConfig_type pConfig =
    {
        .pinCode = 0x8A,
        .pinMode = GPIO_PIN_MODE_OUTPUT
    };

    DRV_GPIO_ReturnCode_type status0 = DRV_GPIO_PinModeConfig(&pConfig);

    EXPECT_EQ(DRV_GPIO_RETURN_CODE_SUCCESSED, status0) << "ERROR: Init Driver Status not Successed";

    EXPECT_TRUE(IP_PTE->PDDR & GPIO_PDDR_PDD_MASK) << "ERROR: Pin output mode not set";
}

/*=========================== TEST GPIO SET OUTPUT ============================ */

/********************************************************************************
 * Test case TC006-TC010
 * @details : Configuaration with request from user
 *
 *******************************************************************************/

TEST(GPIODriver, TC006)
{
    uint8_t pinCode = 0x0A;

    DRV_GPIO_SetOutput(pinCode);

    EXPECT_TRUE(IP_PTA->PSOR & GPIO_PSOR_PTSO_MASK) << "ERROR: Pin output not set";
}

TEST(GPIODriver, TC007)
{
    uint8_t pinCode = 0x2A;

    DRV_GPIO_SetOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PSOR & GPIO_PSOR_PTSO_MASK) << "ERROR: Pin output not set";
}

TEST(GPIODriver, TC008)
{
    uint8_t pinCode = 0x4A;

    DRV_GPIO_SetOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PSOR & GPIO_PSOR_PTSO_MASK) << "ERROR: Pin output not set";
}

TEST(GPIODriver, TC009)
{
    uint8_t pinCode = 0x6A;

    DRV_GPIO_SetOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PSOR & GPIO_PSOR_PTSO_MASK) << "ERROR: Pin output not set";
}

TEST(GPIODriver, TC010)
{
    uint8_t pinCode = 0x8A;

    DRV_GPIO_SetOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PSOR & GPIO_PSOR_PTSO_MASK) << "ERROR: Pin output not set";
}

/*=========================== TEST GPIO CLEAR OUTPUT ============================ */

/********************************************************************************
 * Test case TC011-TC015
 * @details : Clear output of specific port pin
 *
 *******************************************************************************/

TEST(GPIODriver, TC011)
{
    uint8_t pinCode = 0x0A;

    DRV_GPIO_ClearOutput(pinCode);

    EXPECT_TRUE(IP_PTA->PCOR & GPIO_PCOR_PTCO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC012)
{
    uint8_t pinCode = 0x2A;

    DRV_GPIO_ClearOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PCOR & GPIO_PCOR_PTCO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC013)
{
    uint8_t pinCode = 0x4A;

    DRV_GPIO_ClearOutput(pinCode);

    EXPECT_TRUE(IP_PTC->PCOR & GPIO_PCOR_PTCO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC014)
{
    uint8_t pinCode = 0x6A;

    DRV_GPIO_ClearOutput(pinCode);

    EXPECT_TRUE(IP_PTD->PCOR & GPIO_PCOR_PTCO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC015)
{
    uint8_t pinCode = 0x8A;

    DRV_GPIO_ClearOutput(pinCode);

    EXPECT_TRUE(IP_PTE->PCOR & GPIO_PCOR_PTCO_MASK) << "ERROR: Pin output not clear";
}


/*=========================== TEST GPIO TOGGLE OUTPUT ============================ */

/********************************************************************************
 * Test case TC016-TC020
 * @details : Toggle output of specific port pin
 *
 *******************************************************************************/

TEST(GPIODriver, TC016)
{
    uint8_t pinCode = 0x0A;

    DRV_GPIO_ToggleOutput(pinCode);

    EXPECT_TRUE(IP_PTA->PTOR & GPIO_PTOR_PTTO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC017)
{
    uint8_t pinCode = 0x2A;

    DRV_GPIO_ToggleOutput(pinCode);

    EXPECT_TRUE(IP_PTB->PTOR & GPIO_PTOR_PTTO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC018)
{
    uint8_t pinCode = 0x4A;

    DRV_GPIO_ToggleOutput(pinCode);

    EXPECT_TRUE(IP_PTC->PTOR & GPIO_PTOR_PTTO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC019)
{
    uint8_t pinCode = 0x6A;

    DRV_GPIO_ToggleOutput(pinCode);

    EXPECT_TRUE(IP_PTD->PTOR & GPIO_PTOR_PTTO_MASK) << "ERROR: Pin output not clear";
}

TEST(GPIODriver, TC020)
{
    uint8_t pinCode = 0x8A;

    DRV_GPIO_ToggleOutput(pinCode);

    EXPECT_TRUE(IP_PTE->PTOR & GPIO_PTOR_PTTO_MASK) << "ERROR: Pin output not clear";
}

