/********************************************************************************
 * UNIT TEST FOR PORT
 *
 * @author : Group1 tester
 *
 *******************************************************************************/

#include <iostream>
#include "gtest/gtest.h"
#include "S32K144.h"
#include "PORT_Driver.h"
#include<pthread.h>

using namespace std;

pthread_t ThreadID;

void * ClearISF(void * argv){
	PORT_Type* Port = (PORT_Type *)argv;
	uint8_t PCRIndex = 0;

	for(PCRIndex = 0; PCRIndex < 32; PCRIndex++){
		if((Port->PCR[PCRIndex] & PORT_PCR_ISF_MASK) != 0){
			Port->PCR[PCRIndex] &= ~(PORT_PCR_ISF_MASK);
		}
	}
	pthread_exit(NULL);
	return NULL;
}

class PORTDriver : public ::testing::Test
{
protected:
	void SetUp() override
	{
		memset(IP_PORTA, 0, sizeof(PORT_Type));
		memset(IP_PORTB, 0, sizeof(PORT_Type));
		memset(IP_PORTC, 0, sizeof(PORT_Type));
		memset(IP_PORTD, 0, sizeof(PORT_Type));
		memset(IP_PORTE, 0, sizeof(PORT_Type));
	}

	void TearDown() override
	{

	}
};

/*============================= TEST PORT INIT ================================= */

/********************************************************************************
 * Test case TC001-TC005
 * @details : Configuaration with request from user
 *
 *******************************************************************************/

/*==============================Config with PORT ==============================*/

/* Port A */
TEST_F(PORTDriver, TC001)
{
    PORT_PinConfig_type pinConfig = {
        .pinCode = 0x0A,  // PORTA pin 10 (0x0A: PORTA = 0x00, Pin 10 = 0x0A)
        .userConfig = {
            .isPullEnable = PORT_PULL_ENABLE,
            .pullSelect = PORT_INTERNAL_PULL_UP,
            .isPassiveFilterEnable = PORT_PASSIVE_FILTER_DISABLE,
            .driverStrengthMode = PORT_DRIVER_STRENGTH_HIGH,
            .muxMode = PORT_MUX_GPIO,
            .interruptMode = PORT_INT_DISABLE
        }
    };

    IP_PORTA->PCR[10] = 0;

    DRV_PORT_ReturnCode_type status = DRV_PORT_InitPin(&pinConfig);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: InitPin did not return success";

    EXPECT_NE(IP_PORTA->PCR[10] & PORT_PCR_PE_MASK, 0U) << "ERROR: Pull-up/down not enabled";
    EXPECT_NE(IP_PORTA->PCR[10] & PORT_PCR_PS_MASK, 0U) << "ERROR: Pull-up not selected";

    EXPECT_NE(IP_PORTA->PCR[10] & PORT_PCR_DSE_MASK, 0U) << "ERROR: High driver strength not set";

    EXPECT_EQ(PORT_MUX_GPIO << PORT_PCR_MUX_SHIFT, IP_PORTA->PCR[10] & PORT_PCR_MUX_MASK) << "ERROR: MUX mode not set";

    EXPECT_EQ(IP_PORTA->PCR[10] & PORT_PCR_LK_MASK, 0U) << "ERROR: Lock register incorrectly enabled";

    EXPECT_EQ(0, IP_PORTA->PCR[10] & PORT_PCR_IRQC_MASK) << "ERROR: Interrupt mode not disabled";
}

/* Port B */
TEST_F(PORTDriver, TC002)
{
    PORT_PinConfig_type pinConfig = {
        .pinCode = 0x2A,  // PORTB pin 10 (0x0A: PORTB = 0x01, Pin 10 = 0x0A)
        .userConfig = {
            .isPullEnable = PORT_PULL_ENABLE,
            .pullSelect = PORT_INTERNAL_PULL_UP,
            .isPassiveFilterEnable = PORT_PASSIVE_FILTER_DISABLE,
            .driverStrengthMode = PORT_DRIVER_STRENGTH_HIGH,
            .muxMode = PORT_MUX_GPIO,
            .interruptMode = PORT_INT_DISABLE
        }
    };

    IP_PORTB->PCR[10] = 0;

    DRV_PORT_ReturnCode_type status = DRV_PORT_InitPin(&pinConfig);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: InitPin did not return success";

    EXPECT_TRUE(IP_PORTB->PCR[10] & PORT_PCR_PE_MASK) << "ERROR: Pull-up/down not enabled";
    EXPECT_TRUE(IP_PORTB->PCR[10] & PORT_PCR_PS_MASK) << "ERROR: Pull-up not selected";

    EXPECT_TRUE(IP_PORTB->PCR[10] & PORT_PCR_DSE_MASK) << "ERROR: High driver strength not set";

    EXPECT_EQ(PORT_MUX_GPIO << PORT_PCR_MUX_SHIFT, IP_PORTB->PCR[10] & PORT_PCR_MUX_MASK) << "ERROR: MUX mode not set";

    EXPECT_FALSE(IP_PORTB->PCR[10] & PORT_PCR_LK_MASK) << "ERROR: Lock register incorrectly enabled";

    EXPECT_EQ(0, IP_PORTB->PCR[10] & PORT_PCR_IRQC_MASK) << "ERROR: Interrupt mode not disabled";
}

/* Port C */
TEST_F(PORTDriver, TC003)
{
    PORT_PinConfig_type pinConfig = {
        .pinCode = 0x4A,  // PORTC pin 10 (0x0A: PORTC = 0x02, Pin 10 = 0x0A)
        .userConfig = {
            .isPullEnable = PORT_PULL_ENABLE,
            .pullSelect = PORT_INTERNAL_PULL_UP,
            .isPassiveFilterEnable = PORT_PASSIVE_FILTER_DISABLE,
            .driverStrengthMode = PORT_DRIVER_STRENGTH_HIGH,
            .muxMode = PORT_MUX_GPIO,
            .interruptMode = PORT_INT_DISABLE
        }
    };

    IP_PORTC->PCR[10] = 0;

    DRV_PORT_ReturnCode_type status = DRV_PORT_InitPin(&pinConfig);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: InitPin did not return success";

    EXPECT_TRUE(IP_PORTC->PCR[10] & PORT_PCR_PE_MASK) << "ERROR: Pull-up/down not enabled";
    EXPECT_TRUE(IP_PORTC->PCR[10] & PORT_PCR_PS_MASK) << "ERROR: Pull-up not selected";

    EXPECT_TRUE(IP_PORTC->PCR[10] & PORT_PCR_DSE_MASK) << "ERROR: High driver strength not set";

    EXPECT_EQ(PORT_MUX_GPIO << PORT_PCR_MUX_SHIFT, IP_PORTC->PCR[10] & PORT_PCR_MUX_MASK) << "ERROR: MUX mode not set";

    EXPECT_FALSE(IP_PORTC->PCR[10] & PORT_PCR_LK_MASK) << "ERROR: Lock register incorrectly enabled";

    EXPECT_EQ(0, IP_PORTC->PCR[10] & PORT_PCR_IRQC_MASK) << "ERROR: Interrupt mode not disabled";
}

/* Port D */
TEST_F(PORTDriver, TC004)
{
    PORT_PinConfig_type pinConfig = {
        .pinCode = 0x6A,  // PORTD pin 10 (0x0A: PORTD = 0x03, Pin 10 = 0x0A)
        .userConfig = {
            .isPullEnable = PORT_PULL_ENABLE,
            .pullSelect = PORT_INTERNAL_PULL_UP,
            .isPassiveFilterEnable = PORT_PASSIVE_FILTER_DISABLE,
            .driverStrengthMode = PORT_DRIVER_STRENGTH_HIGH,
            .muxMode = PORT_MUX_GPIO,
            .interruptMode = PORT_INT_DISABLE
        }
    };

    IP_PORTD->PCR[10] = 0;

    DRV_PORT_ReturnCode_type status = DRV_PORT_InitPin(&pinConfig);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: InitPin did not return success";

    EXPECT_TRUE(IP_PORTD->PCR[10] & PORT_PCR_PE_MASK) << "ERROR: Pull-up/down not enabled";
    EXPECT_TRUE(IP_PORTD->PCR[10] & PORT_PCR_PS_MASK) << "ERROR: Pull-up not selected";

    EXPECT_TRUE(IP_PORTD->PCR[10] & PORT_PCR_DSE_MASK) << "ERROR: High driver strength not set";

    EXPECT_EQ(PORT_MUX_GPIO << PORT_PCR_MUX_SHIFT, IP_PORTD->PCR[10] & PORT_PCR_MUX_MASK) << "ERROR: MUX mode not set";

    EXPECT_FALSE(IP_PORTD->PCR[10] & PORT_PCR_LK_MASK) << "ERROR: Lock register incorrectly enabled";

    EXPECT_EQ(0, IP_PORTD->PCR[10] & PORT_PCR_IRQC_MASK) << "ERROR: Interrupt mode not disabled";
}

/* Port E */
TEST_F(PORTDriver, TC005)
{
    PORT_PinConfig_type pinConfig = {
        .pinCode = 0x8A,  // PORTE pin 10 (0x0A: PORTE = 0x04, Pin 10 = 0x0A)
        .userConfig = {
            .isPullEnable = PORT_PULL_ENABLE,
            .pullSelect = PORT_INTERNAL_PULL_UP,
            .isPassiveFilterEnable = PORT_PASSIVE_FILTER_DISABLE,
            .driverStrengthMode = PORT_DRIVER_STRENGTH_HIGH,
            .muxMode = PORT_MUX_GPIO,
            .interruptMode = PORT_INT_DISABLE
        }
    };

    IP_PORTE->PCR[10] = 0;

    DRV_PORT_ReturnCode_type status = DRV_PORT_InitPin(&pinConfig);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: InitPin did not return success";

    EXPECT_TRUE(IP_PORTE->PCR[10] & PORT_PCR_PE_MASK) << "ERROR: Pull-up/down not enabled";
    EXPECT_TRUE(IP_PORTE->PCR[10] & PORT_PCR_PS_MASK) << "ERROR: Pull-up not selected";

    EXPECT_TRUE(IP_PORTE->PCR[10] & PORT_PCR_DSE_MASK) << "ERROR: High driver strength not set";

    EXPECT_EQ(PORT_MUX_GPIO << PORT_PCR_MUX_SHIFT, IP_PORTE->PCR[10] & PORT_PCR_MUX_MASK) << "ERROR: MUX mode not set";

    EXPECT_FALSE(IP_PORTE->PCR[10] & PORT_PCR_LK_MASK) << "ERROR: Lock register incorrectly enabled";

    EXPECT_EQ(0, IP_PORTE->PCR[10] & PORT_PCR_IRQC_MASK) << "ERROR: Interrupt mode not disabled";
}

/*=========================== TEST PORT DE-INIT ================================ */

/********************************************************************************
 * Test case TC006-TC0010
 * @details : Configuaration with request from user
 *
 *******************************************************************************/

/* Port A */
TEST_F(PORTDriver, TC006)
{
    DRV_PORT_ReturnCode_type status = DRV_PORT_DeinitPin(0x0A);

    pthread_create(&ThreadID, NULL, ClearISF, (void*)IP_PORTA);
    pthread_join(ThreadID, NULL);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: De-InitPin did not return success";

    EXPECT_EQ(0, IP_PORTA->PCR[10]) << "ERROR: De-InitPin not success";
}

/* Port B */
TEST_F(PORTDriver, TC007)
{
    DRV_PORT_ReturnCode_type status = DRV_PORT_DeinitPin(0x2A);

    pthread_create(&ThreadID, NULL, ClearISF, (void*)IP_PORTB);
    pthread_join(ThreadID, NULL);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: De-InitPin did not return success";

    EXPECT_EQ(0, IP_PORTB->PCR[10]) << "ERROR: De-InitPin not success";
}

/* Port C */
TEST_F(PORTDriver, TC008)
{
    DRV_PORT_ReturnCode_type status = DRV_PORT_DeinitPin(0x4A);

    pthread_create(&ThreadID, NULL, ClearISF, (void*)IP_PORTC);
    pthread_join(ThreadID, NULL);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: De-InitPin did not return success";

    EXPECT_EQ(0, IP_PORTC->PCR[10]) << "ERROR: De-InitPin not success";
}

/* Port D */
TEST_F(PORTDriver, TC009)
{
    DRV_PORT_ReturnCode_type status = DRV_PORT_DeinitPin(0x6A);

    pthread_create(&ThreadID, NULL, ClearISF, (void*)IP_PORTD);
    pthread_join(ThreadID, NULL);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: De-InitPin did not return success";

    EXPECT_EQ(0, IP_PORTD->PCR[10]) << "ERROR: De-InitPin not success";
}

/* Port E */
TEST_F(PORTDriver, TC0010)
{
    DRV_PORT_ReturnCode_type status = DRV_PORT_DeinitPin(0x8A);
    pthread_create(&ThreadID, NULL, ClearISF, (void*)IP_PORTE);
    pthread_join(ThreadID, NULL);

    EXPECT_EQ(DRV_PORT_RETURN_CODE_SUCCESSED, status) << "ERROR: De-InitPin did not return success";

    EXPECT_EQ(0, IP_PORTE->PCR[10]) << "ERROR: De-InitPin not success";
}



