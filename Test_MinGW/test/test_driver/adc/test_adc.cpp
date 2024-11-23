/********************************************************************************
 * UNIT TEST FOR ADC
 *
 * @author : Group1 tester
 *
 *******************************************************************************/

#include <iostream>
#include "gtest/gtest.h"
#include "S32K144.h"
#include "ADC_driver.h"

using namespace std;

#define ADC_ED_PRICISION_CH_U8 (16U)
#define CURRENT_DATA_RESULT_REG (4U)

static uint16_t varCheck = 0U;
static uint16_t varCheckNULL = 0U;
static uint8_t Instance = 0U;
static uint8_t Instance1 = 1U;
static uint8_t Instance2 = 2U;
static ADC_Channel_type channel = ADC_CHANNEL_12;
static IRQCallBack ADC_CallBack = NULL;

static void ADCDriver_CallBack(uint16_t dataOrigin);
static void ADCDriver_CallBack(uint16_t dataOrigin)
{
	varCheck = 1U;
	varCheckNULL = dataOrigin;
}

class ADCDriver : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
		memset(IP_ADC0, 0, sizeof(ADC_Type));
		memset(IP_ADC1, 0, sizeof(ADC_Type));
	}
};

/*============================= TEST ADC INIT ================================= */

/********************************************************************************
 * Test case TC001-TC006
 * Link requirement : [SWS_ADC_001] [SWS_ADC_002] [SWS_ADC_003]
 * @details : Configuaration with request from user
 *
 *******************************************************************************/

/*==============================Config with ADC ==============================*/
/* Instance 0 */
TEST(ADCDriver, TC001)
{
	ADC_Driver_ReturnCode_t status0 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR: ADC Channel ";

	IP_ADC0->SC1[0] |= ADC_SC1_COCO_MASK;
	status0 = DRV_ADC_Init(Instance, channel, ADCDriver_CallBack);

	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status0) << "ERROR : IP_ADC0 Driver Status not Successed ";
	EXPECT_EQ(0x80, IP_ADC0->SC1[0]) << "ERROR : Config register SC1 ";
	EXPECT_EQ(0x00, (IP_ADC0->CFG1) & ADC_CFG1_ADIV_MASK) << "ERROR : Config register CFG1 - Conversion ";
	EXPECT_EQ(0x04, (IP_ADC0->CFG1) & (0x03 << ADC_CFG1_MODE_SHIFT)) << "ERROR : Config register CFG1 - Divide Ratio ";
	EXPECT_EQ(0x0C, IP_ADC0->CFG2) << "ERROR : Config register CFG2 ";
	EXPECT_EQ(0x40, (IP_ADC0->SC2) & ADC_SC2_ADTRG_MASK) << "ERROR : Config register SC2 - HW trigger ";
	EXPECT_EQ(0x00, IP_ADC0->SC3) << "ERROR : Config register SC3 ";
}

/* Instance 1 */
TEST(ADCDriver, TC002)
{
	ADC_Driver_ReturnCode_t status1 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR: ADC Channel ";

	IP_ADC1->SC1[0] |= ADC_SC1_COCO_MASK;
	status1 = DRV_ADC_Init(Instance1, channel, ADCDriver_CallBack);

	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status1) << "ERROR : IP_ADC1 Driver Status not Successed ";
	EXPECT_EQ(0x80, IP_ADC1->SC1[0]) << "ERROR : Config register SC1 ";
	EXPECT_EQ(0x00, (IP_ADC1->CFG1) & ADC_CFG1_ADIV_MASK) << "ERROR : Config register CFG1 - Conversion ";
	EXPECT_EQ(0x04, (IP_ADC1->CFG1) & (0x03 << ADC_CFG1_MODE_SHIFT)) << "ERROR : Config register CFG1 - Divide Ratio ";
	EXPECT_EQ(0x0C, IP_ADC1->CFG2) << "ERROR : Config register CFG2 ";
	EXPECT_EQ(0x40, (IP_ADC1->SC2) & ADC_SC2_ADTRG_MASK) << "ERROR : Config register SC2 - HW trigger ";
	EXPECT_EQ(0x00, IP_ADC1->SC3) << "ERROR : Config register SC3 ";
}

/* Instance 2 */
TEST(ADCDriver, TC003)
{
	ADC_Driver_ReturnCode_t status2 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR: ADC Channel ";

	status2 = DRV_ADC_Init(Instance2, channel, ADCDriver_CallBack);
	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_ERROR, status2) << "ERROR : ADC2 Driver Status not Successed ";
}

/* ===========================Config with PDB ===============================*/
/* Instance 0 */
TEST(ADCDriver, TC004)
{
	ADC_Driver_ReturnCode_t status0 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	IP_ADC0->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	status0 = DRV_ADC_Init(Instance, channel, ADCDriver_CallBack);

	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status0) << "ERROR : IP_ADC0 Driver Status not Successed ";
	EXPECT_EQ(0x40000000, PCC->PCCn[PCC_PDB0_INDEX]) << "ERROR : Enable Clock ";
	EXPECT_EQ(0x0000493E, IP_PDB0->MOD) << "ERROR : Config register MOD ";
	EXPECT_EQ(0x00001010, IP_PDB0->CH[0].C1) << "ERROR : Config register CH[0].C1 ";
	EXPECT_EQ(0x0000249F, IP_PDB0->CH[0].DLY[4]) << "ERROR : Config register CH[0].DLY[4] ";
	EXPECT_EQ(0x00006000, (IP_PDB0->SC) & (PDB_SC_PRESCALER_MASK)) << "ERROR : Config register SC bit Prescaler ";
	EXPECT_EQ(0x00000F00, (IP_PDB0->SC) & (PDB_SC_TRGSEL_MASK)) << "ERROR : Config register SC bit TRGSEL ";
	EXPECT_EQ(0x0000000C, (IP_PDB0->SC) & (PDB_SC_MULT_MASK)) << "ERROR : Config register SC MULT ";
	EXPECT_EQ(0x00000002, (IP_PDB0->SC) & (PDB_SC_CONT_MASK)) << "ERROR : Config register SC CONT ";
	EXPECT_EQ(0x00000080, (IP_PDB0->SC & (PDB_SC_PDBEN_MASK))) << "ERROR : Config register SC PDBEN ";
	EXPECT_EQ(0x00000001, (IP_PDB0->SC) & (PDB_SC_LDOK_MASK)) << "ERROR : Config register SC LDOK ";
	EXPECT_EQ(0x00010000, (IP_PDB0->SC) & (PDB_SC_SWTRIG_MASK)) << "ERROR : Config register SC SWTRIG ";
}

/* Instance 1 */
TEST(ADCDriver, TC005)
{
	ADC_Driver_ReturnCode_t status1 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	IP_ADC1->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	status1 = DRV_ADC_Init(Instance1, channel, ADCDriver_CallBack);

	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status1) << "ERROR : IP_ADC1 Driver Status not Successed ";
	EXPECT_EQ(0x40000000, PCC->PCCn[PCC_PDB1_INDEX]) << "ERROR : Enable Clock ";
	EXPECT_EQ(0x0000493E, IP_PDB1->MOD) << "ERROR : Config register MOD ";
	EXPECT_EQ(0x00001010, IP_PDB1->CH[0].C1) << "ERROR : Config register CH[0].C1 ";
	EXPECT_EQ(0x0000249F, IP_PDB1->CH[0].DLY[4]) << "ERROR : Config register CH[0].DLY[4] ";
	EXPECT_EQ(0x00006000, (IP_PDB1->SC) & (PDB_SC_PRESCALER_MASK)) << "ERROR : Config register SC bit Prescaler ";
	EXPECT_EQ(0x00000F00, (IP_PDB1->SC) & (PDB_SC_TRGSEL_MASK)) << "ERROR : Config register SC bit TRGSEL ";
	EXPECT_EQ(0x0000000C, (IP_PDB1->SC) & (PDB_SC_MULT_MASK)) << "ERROR : Config register SC MULT ";
	EXPECT_EQ(0x00000002, (IP_PDB1->SC) & (PDB_SC_CONT_MASK)) << "ERROR : Config register SC CONT ";
	EXPECT_EQ(0x00000080, (IP_PDB1->SC & (PDB_SC_PDBEN_MASK))) << "ERROR : Config register SC PDBEN ";
	EXPECT_EQ(0x00000001, (IP_PDB1->SC) & (PDB_SC_LDOK_MASK)) << "ERROR : Config register SC LDOK ";
	EXPECT_EQ(0x00010000, (IP_PDB1->SC) & (PDB_SC_SWTRIG_MASK)) << "ERROR : Config register SC SWTRIG ";
}

/* Instance 2 */
TEST(ADCDriver, TC006)
{
	ADC_Driver_ReturnCode_t status2 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	status2 = DRV_ADC_Init(Instance2, channel, ADCDriver_CallBack);
	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_ERROR, status2) << "ERROR : ADC2 Driver Status not Successed ";
}

/*=========================== TEST ENABLE INTERRUPT =========================== */
/********************************************************************************
 * Test case TC007-TC009
 * Link requirement : [SWS_ADC_004] [SWS_ADC_005]
 * @details : Enable Interrupt with request config from user
 *
 *******************************************************************************/

/* Instance 0 */
TEST(ADCDriver, TC007)
{
	ADC_Driver_ReturnCode_t status0 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	status0 = DRV_ADC_EnableIRQ(Instance, channel);
	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status0) << "ERROR: IP_ADC0 Enable Interrupt Status not Successed ";

	EXPECT_EQ(0x80, S32_NVIC->ISER[(uint32_t)(ADC0_IRQn) >> 5U]) << "ERROR : Interrupt set Enable Register ";
	EXPECT_EQ(ADC_SC1_ADCH(channel), (IP_ADC0->SC1[CURRENT_DATA_RESULT_REG]) & ADC_SC1_ADCH(channel)) << "ERROR : IP_ADC0 Input channel select - ADCH Channel ";
	EXPECT_EQ(ADC_SC1_AIEN_MASK, (IP_ADC0->SC1[CURRENT_DATA_RESULT_REG]) & (ADC_SC1_AIEN_MASK)) << "ERROR : IP_ADC0 Enable Interrupt ";
}

/* Instance 1 */
TEST(ADCDriver, TC008)
{
	ADC_Driver_ReturnCode_t status1 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	status1 = DRV_ADC_EnableIRQ(Instance1, channel);
	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_SUCCESSED, status1) << "ERROR: IP_ADC1 Enable Interrupt Status not Successed ";

	EXPECT_EQ(0x100, S32_NVIC->ISER[(uint32_t)(ADC1_IRQn) >> 5U]) << "ERROR : Interrupt set Enable Register ";
	EXPECT_EQ(ADC_SC1_ADCH(channel), (IP_ADC1->SC1[CURRENT_DATA_RESULT_REG]) & ADC_SC1_ADCH(channel)) << "ERROR : IP_ADC1 Input channel select - ADCH Channel ";
	EXPECT_EQ(ADC_SC1_AIEN_MASK, (IP_ADC1->SC1[CURRENT_DATA_RESULT_REG]) & (ADC_SC1_AIEN_MASK)) << "ERROR : IP_ADC1 Enable Interrupt ";
}

/* Instance 2 */
TEST(ADCDriver, TC009)
{
	ADC_Driver_ReturnCode_t status2 = ADC_DRIVER_RETURN_CODE_ERROR;
	EXPECT_TRUE(channel < ADC_ED_PRICISION_CH_U8) << "ERROR : ADC Channel ";

	status2 = DRV_ADC_EnableIRQ(Instance2, channel);
	EXPECT_EQ(ADC_DRIVER_RETURN_CODE_ERROR, status2) << "ERROR: ADC2 Enable Interrupt Status not Successed ";
}

/*=========================== TEST INTERRUPT IP_ADC0 ============================== */

/********************************************************************************
 * Test case TC010-TC011
 * Link requirement : [SWS_ADC_006] [SWS_ADC_007] [SWS_ADC_008]
 * @details : Read Data raw from sensor (ADC 0)
 *
 *******************************************************************************/

/* Verify with value of function call back ADC_CallBack = ADCDriver_CallBack */

TEST(ADCDriver, TC010)
{
	varCheckNULL = 0x00;
	varCheck = 0;
	IP_ADC0->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	DRV_ADC_Init(Instance, channel, ADCDriver_CallBack);
	IP_ADC0->R[CURRENT_DATA_RESULT_REG] = 0xFF;
	ADC0_IRQHandler();

	EXPECT_EQ(0xFF, varCheckNULL) << "ERROR : Check Data Interrupt with IP_ADC0 ";
	EXPECT_EQ(1U, varCheck) << "ERROR : CallBack Function ";
}

/* Verify with value of function call back ADC_CallBack = NULL */
TEST(ADCDriver, TC011)
{
	varCheckNULL = 0x00;
	varCheck = 0;
	IP_ADC0->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	DRV_ADC_Init(Instance, channel, ADC_CallBack);
	IP_ADC0->R[CURRENT_DATA_RESULT_REG] = 0xFF;
	ADC0_IRQHandler();

	EXPECT_EQ(0x00, varCheckNULL) << "ERROR : Check Data Interrupt with IP_ADC0 ";
	EXPECT_EQ(0U, varCheck) << "ERROR : CallBack Function (NULL) ";
}

/*=========================== TEST INTERRUPT IP_ADC1 ============================ */
/********************************************************************************
 * Test case TC012
 * Link requirement : [SWS_ADC_006] [SWS_ADC_007] [SWS_ADC_008]
 * @details : Read data raw from sensor (IP_ADC1)
 *
 *******************************************************************************/

/* Verify with value of function call back ADC_CallBack = ADCDriver_CallBack */
TEST(ADCDriver, TC012)
{
	varCheckNULL = 0x00;
	varCheck = 0;
	IP_ADC1->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	DRV_ADC_Init(Instance1, channel, ADCDriver_CallBack);
	IP_ADC1->R[CURRENT_DATA_RESULT_REG] = 0xFF;
	ADC1_IRQHandler();

	EXPECT_EQ(0xFF, varCheckNULL) << "ERROR : Check Data Interrupt with IP_ADC1 ";
	EXPECT_EQ(1U, varCheck) << "ERROR : CallBack Function ";
}

/* Verify with value of function call back ADC_CallBack = NULL */
TEST(ADCDriver, TC013)
{
	varCheckNULL = 0x00;
	varCheck = 0;
	IP_ADC1->SC1[0] |= ADC_SC1_COCO_MASK; /* Setup register status */
	DRV_ADC_Init(Instance1, channel, ADC_CallBack);
	IP_ADC1->R[CURRENT_DATA_RESULT_REG] = 0xFF;
	ADC1_IRQHandler();

	EXPECT_EQ(0x00, varCheckNULL) << "ERROR : Check Data Interrupt with IP_ADC1 ";
	EXPECT_EQ(0U, varCheck) << "ERROR : CallBack Function (NULL) ";
}
