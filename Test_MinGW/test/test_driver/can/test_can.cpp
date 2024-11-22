#include<gtest/gtest.h>
#include<iostream>
#include<pthread.h>
#include"can_stub.h"
#include"FlexCAN.h"

#define INVALID_INSTANCE (3U)
#define INVALID_MB 		(33U)
#define MCR_RESET_VALUE (0xD890000FU)

FLEXCAN_Type CAN0;
FLEXCAN_Type CAN1;
FLEXCAN_Type CAN2;

FLEXCAN_Type * FlexCANInstanceArr[FLEXCAN_INSTANCE_COUNT] = IP_FLEXCAN_BASE_PTRS;

pthread_t FreezeThreadID;
pthread_t SoftResetThreadID;
pthread_mutex_t Lock = PTHREAD_MUTEX_INITIALIZER;
uint8_t RequestFreezeThread = 0;
uint8_t RequestSoftResetThread = 0;
uint8_t Data[8] = {0xFF, 0xCA, 0x1, 0x23, 0x20, 0x8, 0x55, 0x0};

FlexCAN_InterruptType FlexCAN0IntControl = {
		FlexCAN_INT_BUSOFF_DISABLE,
		FlexCAN_INT_ERROR_ENABLE,
		FlexCAN_INT_TxWARNING_DISABLE,
		FlexCAN_INT_RxWARNING_DISABLE
};

FlexCAN_ConfigType DefaultFlexCANConfig = {
		/* Configuration elements for FlexCAN module */
			.MaxNoMB = 31,
			.BitRate = 500000,
			.ClkFreq = 48000000,
			.RunMode = FlexCAN_MODE_LOOPBACK,
			.CLkSrc = FlexCAN_CLKSRC_SYS
};

FlexCAN_ConfigType FlexCANConfig = DefaultFlexCANConfig;

FlexCAN_MbHeaderType TxMailboxConfig = {
			.EDL = 0,
			.BRS = 0,
			.ESI = 0,
			.MbType = FlexCAN_MB_TX,
			.IdType = FlexCAN_STANDARD,
			.IsRemote = false,
			.DataLen = 8,
			.MbID = 1,
			.IsEnableMbInt = false
};

FlexCAN_MbHeaderType RxMailboxConfig = {
			.EDL = 0,
			.BRS = 0,
			.ESI = 0,
			.MbType = FlexCAN_MB_RX,
			.IdType = FlexCAN_STANDARD,
			.IsRemote = false,
			.DataLen = 8,
			.MbID = 1,
			.IsEnableMbInt = true
};

static void * ExitFreeze(void * argv){
	if(RequestFreezeThread == 1){
		FLEXCAN_Type  * FlexCANx = (FLEXCAN_Type *) argv;
		/* Freeze mode is entered while FRZ = 1 and HALT = 1 */
		while((FlexCANx->MCR & FLEXCAN_MCR_MDIS_MASK) != 0);
		pthread_mutex_lock(&Lock);
		FlexCANx->MCR |= (1 << FLEXCAN_MCR_FRZ_SHIFT);
		FlexCANx->MCR |= (1 << FLEXCAN_MCR_HALT_SHIFT);
		FlexCANx->MCR |= (1 << FLEXCAN_MCR_NOTRDY_SHIFT);
		FlexCANx->MCR |= (1 << FLEXCAN_MCR_FRZACK_SHIFT);
		pthread_mutex_unlock(&Lock);
		/* When entering freeze mode, FRZACK = 1 */
		while((FlexCANx->MCR & FLEXCAN_MCR_FRZ_MASK) && (FlexCANx->MCR & FLEXCAN_MCR_HALT_MASK));
		pthread_mutex_lock(&Lock);
		FlexCANx->MCR &= ~(1 << FLEXCAN_MCR_FRZACK_SHIFT);
		FlexCANx->MCR &= ~(1 << FLEXCAN_MCR_NOTRDY_SHIFT);
		pthread_mutex_unlock(&Lock);
		pthread_exit(NULL);
		RequestFreezeThread = 0;
	}
	return NULL;
}

static void * ExitSoftReset(void * argv){
	if(RequestSoftResetThread == 1){
		FLEXCAN_Type  * FlexCANx = (FLEXCAN_Type *) argv;
		uint32_t Value = MCR_RESET_VALUE;

		while((FlexCANx->MCR & FLEXCAN_MCR_SOFTRST_MASK) == 0);
		pthread_mutex_lock(&Lock);
		FlexCANx->MCR &= ~FLEXCAN_MCR_SOFTRST_MASK;
		FlexCANx->CTRL1 = 0;
		/* All bits of MCR return to its reset state except for FRZACK and LPMACK */
		Value &= (FlexCANx->MCR | ~FLEXCAN_MCR_LPMACK_MASK);
		Value |= (FlexCANx->MCR & FLEXCAN_MCR_FRZACK_MASK);
		FlexCANx->MCR = Value;
		RequestSoftResetThread = 0;
		pthread_mutex_unlock(&Lock);
	}
	pthread_exit(NULL);
	return NULL;
}

class CAN_TEST : public ::testing::Test {
protected:
    // Called before every test
    void SetUp() override {
    	uint8_t Index = 0;

    	FlexCAN_SetModuleState(FlexCAN0_INS, FLEXCAN_STATE_UNINIT);
    	FlexCAN_SetModuleState(FlexCAN1_INS, FLEXCAN_STATE_UNINIT);
    	FlexCAN_SetModuleState(FlexCAN2_INS, FLEXCAN_STATE_UNINIT);

    	/* MCR reset value */
    	CAN0.MCR = MCR_RESET_VALUE;
    	CAN1.MCR = MCR_RESET_VALUE;
    	CAN2.MCR = MCR_RESET_VALUE;

    	CAN0.CTRL1 = 0;
		CAN1.CTRL1 = 0;
		CAN2.CTRL1 = 0;

    	CAN0.IFLAG1 = 0;
    	CAN1.IFLAG1 = 0;
    	CAN2.IFLAG1 = 0;

    	CAN0.IMASK1 = 0;
    	CAN1.IMASK1 = 0;
		CAN2.IMASK1 = 0;

    	pthread_mutex_init(&Lock, NULL);
    	RequestFreezeThread = 0;
    	RequestSoftResetThread = 0;

    	FlexCANConfig = DefaultFlexCANConfig;

    	/* Clear mailbox */
    	for(Index = 0; Index < 128; Index++){
    		CAN0.RAMn[Index] = 0;
    		CAN1.RAMn[Index] = 0;
    		CAN2.RAMn[Index] = 0;
    	}
    }
};

/**************************************************************************/
/* Test for function FlexCAN_Init() */
/**************************************************************************/
/**
 * @test_id
 * @brief 			Verify initialization when there has been no initialization before.
 * @pre 			N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Verify that the initial state of each FlexCAN module is FLEXCAN_STATE_UNINIT.
 * 					# VERIFICATION POINT: FLEXCAN_STATE_UNINIT for all instances.
 * 					Set the `RequestFreezeThread` flag to 1 and create a thread to handle freeze mode.
 * 					Call `FlexCAN_Init` with a valid instance index and a valid configuration pointer.
 * 					Wait for the freeze thread to exit using `pthread_join`.
 * 					Verify that the module state is set to FLEXCAN_STATE_READY.
 * 					# VERIFICATION POINT: FLEXCAN_STATE_READY after initialization.
 * 					Check that the `MCR_MDIS` bit is cleared (value = 0).
 * 					# VERIFICATION POINT: MCR_MDIS bit = 0.
 * 					Check that the `MCR_FRZACK` bit is cleared (value = 0).
 * 					# VERIFICATION POINT: MCR_FRZACK bit = 0.
 * 					Verify that no interrupt mask bits (`BOFFMSK`, `ERRMSK`, `TWRNMSK`, `RWRNMSK`) are set in the `CTRL1` register.
 * 					# VERIFICATION POINT: No interrupt mask bits in CTRL1 are set (BOFFMSK, ERRMSK, TWRNMSK, RWRNMSK).
 */
TEST_F(CAN_TEST,TC001){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		RequestFreezeThread = 1;
		pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)FlexCANInstanceArr[InstanceIndex]);
		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, &FlexCANConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		while(pthread_join(FreezeThreadID, NULL) != 0);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_READY);
		EXPECT_EQ(FlexCANInstanceArr[InstanceIndex]->MCR & FLEXCAN_MCR_MDIS_MASK, 0U);
		EXPECT_EQ((FlexCANInstanceArr[InstanceIndex]->MCR & FLEXCAN_MCR_FRZACK_MASK), 0U);
		/* No interrupt should be raised */
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_BOFFMSK_MASK);
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_ERRMSK_MASK);
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_TWRNMSK_MASK);
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_RWRNMSK_MASK);
	}

}

/**
 * @test_id
 * @brief			Verify FlexCAN initialization with interrupts enabled when there has been no prior initialization.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Call `FlexCAN_Init` with each valid instance index, a non-NULL configuration pointer, and all interrupts enabled (Bus Off, Error, Tx Warning, Rx Warning).
 * 					# VERIFICATION POINT: State = FLEXCAN_STATE_READY.
 * 					# VERIFICATION POINT: MCR_MDIS bit = 0.
 * 					# VERIFICATION POINT: MCR_FRZACK bit = 0.
 * 					# VERIFICATION POINT: ESR1_SYNCH bit = 1.
 * 					# VERIFICATION POINT: Interrupt mask bits in CTRL1 are set (BOFFMSK, ERRMSK, TWRNMSK, RWRNMSK).
 */
TEST_F(CAN_TEST,TC002){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	/* No interrupt should be raised */
	EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_BOFFMSK_MASK);
	EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_ERRMSK_MASK);
	EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_TWRNMSK_MASK);
	EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_RWRNMSK_MASK);

	FlexCANConfig.IntControl.IntBusOff = FlexCAN_INT_BUSOFF_ENABLE;
	FlexCANConfig.IntControl.IntError = FlexCAN_INT_ERROR_ENABLE;
	FlexCANConfig.IntControl.IntTxWarning = FlexCAN_INT_TxWARNING_ENABLE;
	FlexCANConfig.IntControl.IntRxWarning = FlexCAN_INT_RxWARNING_ENABLE;

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		RequestFreezeThread = 1;
		pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)FlexCANInstanceArr[InstanceIndex]);
		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, &FlexCANConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		while(pthread_join(FreezeThreadID, NULL) != 0);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_READY);
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->MCR & FLEXCAN_MCR_MDIS_MASK);
		EXPECT_FALSE(FlexCANInstanceArr[InstanceIndex]->MCR & FLEXCAN_MCR_FRZACK_MASK);
		/* No interrupt should be raised */
		EXPECT_TRUE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_BOFFMSK_MASK);
		EXPECT_TRUE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_ERRMSK_MASK);
		EXPECT_TRUE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_TWRNMSK_MASK);
		EXPECT_TRUE(FlexCANInstanceArr[InstanceIndex]->CTRL1 & FLEXCAN_CTRL1_RWRNMSK_MASK);
	}
}

/**
 * @test_id
 * @brief			Verify that FlexCAN initialization fails when an instance is already initialized and ensure the state remains unchanged.
 * @pre				All FlexCAN instances must be uninitialized before the test begins.
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Call `FlexCAN_Init` with each valid instance index, a non-NULL configuration pointer, and all interrupts enabled (Bus Off, Error, Tx Warning, Rx Warning).
 * 					# VERIFICATION POINT: State = FLEXCAN_STATE_READY after successful initialization.
 * 					# VERIFICATION POINT: Initialization fails with FLEXCAN_DRIVER_RETURN_CODE_ERROR when called on an already initialized instance.
 * 					# VERIFICATION POINT: Module state remains FLEXCAN_STATE_READY after a failed reinitialization attempt.
 */
TEST_F(CAN_TEST,TC003){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		RequestFreezeThread = 1;
		pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)FlexCANInstanceArr[InstanceIndex]);
		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, &FlexCANConfig),FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		while(pthread_join(FreezeThreadID, NULL) != 0);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_READY);

		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, &FlexCANConfig),FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_READY);
	}
}

/**
 * @test_id
 * @brief			Verify that FlexCAN initialization fails when provided with an invalid instance or a NULL configuration pointer, and ensure the state remains unchanged.
 * @pre				All FlexCAN instances must be uninitialized before the test begins.
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Call `FlexCAN_Init` with an invalid instance index and a valid configuration pointer.
 * 					# VERIFICATION POINT: Initialization fails with FLEXCAN_DRIVER_RETURN_CODE_ERROR.
 * 					# VERIFICATION POINT: Module state remains FLEXCAN_STATE_UNINIT after failed initialization.
 * 					For each valid instance index, call `FlexCAN_Init` with a NULL configuration pointer.
 * 					# VERIFICATION POINT: Initialization fails with FLEXCAN_DRIVER_RETURN_CODE_ERROR.
 * 					# VERIFICATION POINT: Module state remains FLEXCAN_STATE_UNINIT after failed initialization.
 */
TEST_F(CAN_TEST,TC004){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)INVALID_INSTANCE, &FlexCANConfig),FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_UNINIT);

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_UNINIT);


	}
}

/**
 * @test_id
 * @brief			Verify that FlexCAN deinitialization correctly resets the module state and configuration after successful initialization.
 * @pre				All FlexCAN instances must be uninitialized before the test begins.
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Call `FlexCAN_Init` with each valid instance index and a non-NULL configuration pointer.
 * 					# VERIFICATION POINT: Module state = FLEXCAN_STATE_READY after successful initialization.
 * 					Call `FlexCAN_DeInit` with each valid instance index.
 * 					# VERIFICATION POINT: Module state = FLEXCAN_STATE_UNINIT after successful deinitialization.
 * 					# VERIFICATION POINT: MCR register is reset to the default value (MCR_RESET_VALUE) after deinitialization.
 */

TEST_F(CAN_TEST,TC005){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		RequestFreezeThread = 1;
		pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)FlexCANInstanceArr[InstanceIndex]);
		EXPECT_EQ(FlexCAN_Init((FlexCAN_Instance_e)InstanceIndex, &FlexCANConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		while(pthread_join(FreezeThreadID, NULL) != 0);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_READY);

		RequestSoftResetThread = 1;
		pthread_create(&SoftResetThreadID, NULL, ExitSoftReset, (void*)FlexCANInstanceArr[InstanceIndex]);
		EXPECT_EQ(FlexCAN_DeInit((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		while(pthread_join(SoftResetThreadID, NULL) != 0);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_UNINIT);
		EXPECT_EQ(FlexCANInstanceArr[InstanceIndex]->MCR, MCR_RESET_VALUE) << InstanceIndex;
	}

}

/**
 * @test_id
 * @brief			Verify that FlexCAN deinitialization fails when the module is not initialized and ensures the state remains unchanged.
 * @pre				All FlexCAN instances must be uninitialized before the test begins.
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					For each valid instance index, call `FlexCAN_DeInit` without prior initialization.
 * 					# VERIFICATION POINT: `FlexCAN_DeInit` returns FLEXCAN_DRIVER_RETURN_CODE_ERROR.
 * 					# VERIFICATION POINT: Module state remains FLEXCAN_STATE_UNINIT after the failed deinitialization attempt.
 */
TEST_F(CAN_TEST,TC006){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		EXPECT_EQ(FlexCAN_DeInit((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_UNINIT);
	}

}

/**
 * @test_id
 * @brief			Verify that FlexCAN deinitialization fails when called with an invalid instance index and ensures the state remains unchanged.
 * @pre				All FlexCAN instances must be uninitialized before the test begins.
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					Call `FlexCAN_DeInit` with an invalid instance index.
 * 					# VERIFICATION POINT: `FlexCAN_DeInit` returns FLEXCAN_DRIVER_RETURN_CODE_ERROR.
 * 					# VERIFICATION POINT: Module state remains FLEXCAN_STATE_UNINIT for all valid instances.
 */
TEST_F(CAN_TEST,TC007){
	uint8_t InstanceIndex = 0;

	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN1_INS), FLEXCAN_STATE_UNINIT);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN2_INS), FLEXCAN_STATE_UNINIT);

	EXPECT_EQ(FlexCAN_DeInit((FlexCAN_Instance_e)INVALID_INSTANCE), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	EXPECT_EQ(FlexCAN_GetModuleState((FlexCAN_Instance_e)InstanceIndex), FLEXCAN_STATE_UNINIT);

}

/**
 * @test_id
 * @brief			Verify mailbox initialization and ensure the ID and code match the expected values.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Call `FlexCAN_MbInit` to initialize a mailbox with the given configuration.
 * 					# VERIFICATION POINT: Verify that the Mailbox ID matches the configured `MbID`.
 * 					# VERIFICATION POINT: Verify that the Mailbox code is set to `Rx_CODE_EMPTY`.
 */
TEST_F(CAN_TEST,TC008){
	uint16_t MailboxID = 0;
	uint8_t MailboxCode = 0;
	EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, MB0, &RxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	MailboxID = (CAN0.RAMn[1] & FLEXCAN_RAMn_DATA_WORD_1_ID_MASK) >> FLEXCAN_RAMn_DATA_WORD_1_ID_SHIFT;
	MailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >> FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;
	/* Verify mailbox's ID */
	EXPECT_EQ(MailboxID, RxMailboxConfig.MbID);
	/* Verify mailbox's code */
	EXPECT_EQ(MailboxCode, Rx_CODE_EMPTY);
}

/**
 * @test_id
 * @brief			Verify mailbox initialization and ensure the ID and code match the expected values for transmission.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Call `FlexCAN_MbInit` to initialize a mailbox for transmission with the given configuration.
 * 					# VERIFICATION POINT: Verify that the Mailbox ID matches the configured `MbID`.
 * 					# VERIFICATION POINT: Verify that the Mailbox code is set to `Tx_CODE_INACTIVE`.
 */
TEST_F(CAN_TEST,TC009){
	uint16_t MailboxID = 0;
	uint8_t MailboxCode = 0;
	EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, MB0, &TxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	MailboxID = (CAN0.RAMn[1] & FLEXCAN_RAMn_DATA_WORD_1_ID_MASK) >> FLEXCAN_RAMn_DATA_WORD_1_ID_SHIFT;
	MailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >> FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;
	/* Verify mailbox's ID */
	EXPECT_EQ(MailboxID, TxMailboxConfig.MbID);
	/* Verify mailbox's code */
	EXPECT_EQ(MailboxCode, Tx_CODE_INACTIVE);
}

/**
 * @test_id
 * @brief			Verify initialization of multiple mailboxes and check interrupt enablement for each.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Initialize each mailbox (0 to 31) for reception with the given configuration.
 * 					# VERIFICATION POINT: Check that the mailbox initialization returns success.
 * 					# VERIFICATION POINT: Verify that the corresponding interrupt for each mailbox is enabled in `IMASK1`.
 */
TEST_F(CAN_TEST,TC010){
	uint8_t MailboxIndex = 0;
	uint8_t NumberOfMailbox = 32;

	for(MailboxIndex = 0; MailboxIndex < NumberOfMailbox; MailboxIndex++){
		EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, (FlexCAN_MbIndex_e) MailboxIndex, &RxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
		EXPECT_TRUE(CAN0.IMASK1 << MailboxIndex);
	}

}

/**
 * @test_id
 * @brief			Verify error handling when invalid mailbox indices or NULL configurations are passed.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Try initializing a mailbox with an invalid mailbox index for each instance.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR`.
 * 					# Try initializing a mailbox with a valid index but NULL configuration for each instance.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR`.
 * 					# Try initializing mailboxes with invalid instance or invalid mailbox index.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR` for each invalid case.
 */

TEST_F(CAN_TEST,TC011){
	uint8_t MailboxIndex = 0;
	uint8_t NumberOfMailbox = 32;
	uint8_t InstanceIndex = 0;

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		EXPECT_EQ(FlexCAN_MbInit((FlexCAN_Instance_e)InstanceIndex, (FlexCAN_MbIndex_e)INVALID_MB, &RxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_MbInit((FlexCAN_Instance_e)InstanceIndex, MB0, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

	for(MailboxIndex = 0; InstanceIndex < NumberOfMailbox; InstanceIndex++){
		EXPECT_EQ(FlexCAN_MbInit((FlexCAN_Instance_e)INVALID_INSTANCE, (FlexCAN_MbIndex_e)MailboxIndex, &RxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, (FlexCAN_MbIndex_e)MailboxIndex, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

}

/**
 * @test_id
 * @brief			Verify error handling during transmission with invalid mailbox indices or NULL data.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Attempt to transmit data with an invalid mailbox index for each instance.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR`.
 * 					# Attempt to transmit data with a valid mailbox index but NULL data for each instance.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR`.
 * 					# Attempt to transmit data with an invalid instance or invalid mailbox index.
 * 					# VERIFICATION POINT: Ensure the return code is `FLEXCAN_DRIVER_RETURN_CODE_ERROR` for each invalid case.
 */
TEST_F(CAN_TEST,TC012){
	uint8_t MailboxIndex = 0;
	uint8_t NumberOfMailbox = 32;
	uint8_t InstanceIndex = 0;

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		EXPECT_EQ(FlexCAN_Transmit((FlexCAN_Instance_e)InstanceIndex, (FlexCAN_MbIndex_e)INVALID_MB, Data), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_Transmit((FlexCAN_Instance_e)InstanceIndex, MB0, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

	for(MailboxIndex = 0; InstanceIndex < NumberOfMailbox; InstanceIndex++){
		EXPECT_EQ(FlexCAN_Transmit((FlexCAN_Instance_e)INVALID_INSTANCE, (FlexCAN_MbIndex_e)MailboxIndex, Data), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_Transmit(FlexCAN0_INS, (FlexCAN_MbIndex_e)MailboxIndex, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

}

/**
 * @test_id
 * @brief			Verify data transmission and correct placement in the mailbox after transmission.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Initialize FlexCAN and the corresponding mailbox.
 * 					# VERIFICATION POINT: Ensure FlexCAN is in the `READY` state.
 * 					# Perform data transmission using FlexCAN.
 * 					# VERIFICATION POINT: Ensure that the mailbox code is `DATA` (indicating successful transmission).
 * 					# Verify that the data transmitted matches the expected data in the mailbox.
 * 					# VERIFICATION POINT: Ensure that the transmitted bytes match the data placed in the mailbox.
 */
TEST_F(CAN_TEST,TC013){
	uint8_t TxMailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >>
			FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;;
	uint32_t MailboxWord[2] = {0};
	uint8_t ByteIndex = 0;
	uint8_t MailboxByte0 = 0;
	uint8_t MailboxByte1 = 0;
	uint8_t MailboxByte2 = 0;
	uint8_t MailboxByte3 = 0;

	RequestFreezeThread = 1;
	pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)&CAN0);
	EXPECT_EQ(FlexCAN_Init(FlexCAN0_INS, &FlexCANConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_READY);

	EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, MB0, &TxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	EXPECT_EQ(FlexCAN_Transmit(FlexCAN0_INS, MB0, Data), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);

	MailboxWord[0] = CAN0.RAMn[2];
	MailboxWord[1] = CAN0.RAMn[3];
	TxMailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >>
			FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;

	EXPECT_EQ(TxMailboxCode, Tx_CODE_DATA);
	for(ByteIndex = 0; ByteIndex < 2; ByteIndex++){
		MailboxByte0 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_0_MASK) >> 24;
		MailboxByte1 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_1_MASK) >> 16;
		MailboxByte2 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_2_MASK) >> 8;
		MailboxByte3 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_3_MASK);

		EXPECT_EQ(MailboxByte0, Data[0 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte1, Data[1 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte2, Data[2 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte3, Data[3 + 4*ByteIndex]);
	}
}

/**
 * @test_id
 * @brief			Verify data transmission and correct data retrieval from the mailbox.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Initialize FlexCAN and the corresponding transmit mailbox.
 * 					# VERIFICATION POINT: Ensure FlexCAN is in the `READY` state.
 * 					# Perform data transmission using FlexCAN.
 * 					# VERIFICATION POINT: Ensure the mailbox code is `DATA` (indicating successful transmission).
 * 					# Verify that the transmitted data is correctly placed in the mailbox.
 * 					# Read the data from the mailbox and verify it matches the transmitted data.
 * 					# VERIFICATION POINT: Ensure that the data retrieved from the mailbox matches the transmitted data byte-by-byte.
 */
TEST_F(CAN_TEST,TC014){
	uint8_t Data[8] = {0xFF, 0xCA, 0x1, 0x23, 0x20, 0x8, 0x55, 0x0};
	uint8_t DataRead[8] = {0};
	uint8_t TxMailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >>
			FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;;
	uint32_t MailboxWord[2] = {0};
	uint8_t ByteIndex = 0;
	uint8_t MailboxByte0 = 0;
	uint8_t MailboxByte1 = 0;
	uint8_t MailboxByte2 = 0;
	uint8_t MailboxByte3 = 0;

	RequestFreezeThread = 1;
	pthread_create(&FreezeThreadID, NULL, ExitFreeze, (void *)&CAN0);
	EXPECT_EQ(FlexCAN_Init(FlexCAN0_INS, &FlexCANConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	EXPECT_EQ(FlexCAN_GetModuleState(FlexCAN0_INS), FLEXCAN_STATE_READY);

	EXPECT_EQ(FlexCAN_MbInit(FlexCAN0_INS, MB0, &TxMailboxConfig), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	EXPECT_EQ(FlexCAN_Transmit(FlexCAN0_INS, MB0, Data), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	EXPECT_EQ(FlexCAN_ReadMailboxData(FlexCAN0_INS, MB0, DataRead), FLEXCAN_DRIVER_RETURN_CODE_SUCCESSED);
	MailboxWord[0] = CAN0.RAMn[2];
	MailboxWord[1] = CAN0.RAMn[3];
	TxMailboxCode = (CAN0.RAMn[0] & FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK) >>
			FLEXCAN_RAMn_DATA_WORD_0_CODE_SHIFT;

	EXPECT_EQ(TxMailboxCode, Tx_CODE_DATA);
	for(ByteIndex = 0; ByteIndex < 2; ByteIndex++){
		MailboxByte0 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_0_MASK) >> 24;
		MailboxByte1 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_1_MASK) >> 16;
		MailboxByte2 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_2_MASK) >> 8;
		MailboxByte3 = (MailboxWord[ByteIndex] & FLEXCAN_RAMn_DATA_BYTE_3_MASK);

		EXPECT_EQ(MailboxByte0, Data[0 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte1, Data[1 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte2, Data[2 + 4*ByteIndex]);
		EXPECT_EQ(MailboxByte3, Data[3 + 4*ByteIndex]);
	}

	for(ByteIndex = 0; ByteIndex < 8; ByteIndex++){
		EXPECT_EQ(Data[ByteIndex], DataRead[ByteIndex]);
	}
}

/**
 * @test_id
 * @brief			Verify error handling when reading from an invalid or NULL mailbox.
 * @pre				N/A
 * @test_type		Functional
 * @test_procedure	Test procedure steps:
 * 					# Attempt to read data from an invalid mailbox (invalid mailbox index or NULL pointer).
 * 					# VERIFICATION POINT: Ensure the function returns an error (`FLEXCAN_DRIVER_RETURN_CODE_ERROR`).
 * 					# Repeat the test for all FlexCAN instances and mailboxes.
 * 					# Ensure that invalid mailbox reads (out of bounds or NULL) result in an error code.
 */

TEST_F(CAN_TEST,TC015){
	uint8_t MailboxIndex = 0;
	uint8_t NumberOfMailbox = 32;
	uint8_t InstanceIndex = 0;
	uint8_t DataRead[8] = {};

	for(InstanceIndex = 0; InstanceIndex < FLEXCAN_INSTANCE_COUNT; InstanceIndex++){
		EXPECT_EQ(FlexCAN_ReadMailboxData((FlexCAN_Instance_e)InstanceIndex, (FlexCAN_MbIndex_e)INVALID_MB, DataRead), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_ReadMailboxData((FlexCAN_Instance_e)InstanceIndex, MB0, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

	for(MailboxIndex = 0; InstanceIndex < NumberOfMailbox; InstanceIndex++){
		EXPECT_EQ(FlexCAN_ReadMailboxData((FlexCAN_Instance_e)INVALID_INSTANCE, (FlexCAN_MbIndex_e)MailboxIndex, DataRead), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
		EXPECT_EQ(FlexCAN_ReadMailboxData(FlexCAN0_INS, (FlexCAN_MbIndex_e)MailboxIndex, NULL), FLEXCAN_DRIVER_RETURN_CODE_ERROR);
	}

}
