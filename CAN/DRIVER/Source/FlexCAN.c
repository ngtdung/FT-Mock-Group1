/*
 * FlexCAN.c
 *
 *  Created on: Oct 23, 2024
 *      Author: adm
 */

#include "FlexCAN.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------
   -- Variables
   ---------------------------------------------------------------------------- */

FlexCAN_CallbackType DRV_FlexCAN_Callback[FLEXCAN_INSTANCE_COUNT*NUMBER_OF_HANDLER_TYPE];
FlexCAN_CallbackType DRV_FlexCAN_MbCallback[32U];

/**
 * Base addresses for FLEXCAN modules.
 * @note This array is indexed by LPUART instance numbers.
 */
static FLEXCAN_Type *FlexCAN_Base_Addr[FLEXCAN_INSTANCE_COUNT] = IP_FLEXCAN_BASE_PTRS;

FlexCAN_MbType * FlexCAN_MB[FLEXCAN_INSTANCE_COUNT] = {MB_FLEXCAN_0, MB_FLEXCAN_1, MB_FLEXCAN_2};

/* ----------------------------------------------------------------------------
   -- Private functions
   ---------------------------------------------------------------------------- */
static void FlexCAN_ModuleControl(FLEXCAN_Type *FlexCANx, uint8_t EnOrDis);
static void FlexCAN_ClkSrcSelect(FLEXCAN_Type *FlexCANx, FlexCAN_ClkSrc_e CLkSrc);
static void FlexCAN_ClearMB(FLEXCAN_Type *FlexCANx);
static void FlexCAN_RunModeSelect(FLEXCAN_Type *FlexCANx, FlexCAN_Mode_e Mode);
static void FlexCAN_IntControl(FLEXCAN_Type *FlexCANx, FlexCAN_InterruptType IntType);
static void FlexCAN_SetBitRate(FLEXCAN_Type *FlexCANx, uint32_t Clocks, uint32_t BitRate);
static void FLexCAN_FreezeModeControl(FLEXCAN_Type *FlexCANx, uint8_t EnOrDis);
static void FlexCAN_SoftReset(FLEXCAN_Type *FlexCANx);
static void FlexCAN_MBSetEDL(FlexCAN_MbStructureType * Mbx, uint8_t EDLValue);
static void FlexCAN_MBSetBRS(FlexCAN_MbStructureType * Mbx, uint8_t BRSValue);
static void FlexCAN_MBSetESI(FlexCAN_MbStructureType * Mbx, uint8_t ESIValue);
static void FlexCAN_MBSetIDType(FlexCAN_MbStructureType * Mbx, FlexCAN_MsgIDType_e IDType);
static void FlexCAN_MBSetRTR(FlexCAN_MbStructureType * Mbx, bool IsRemote);
static void FlexCAN_MBSetDataLength(FlexCAN_MbStructureType * Mbx, uint16_t Datalen);
static void FlexCAN_MBSetID(FlexCAN_MbStructureType * Mbx, uint16_t ID);
static void FlexCAN_MbSetType(FlexCAN_MbStructureType * Mbx, FlexCAN_MbType_e MbType);
static void FlexCAN_MbSetInterrupt(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex, bool IsEnableMbInt);

/* ----------------------------------------------------------------------------
   -- Global functions
   ---------------------------------------------------------------------------- */
void FlexCAN_Init(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_ConfigType *FlexCAN_Config)
{
	FLEXCAN_Type *FlexCANx = FlexCAN_Base_Addr[FlexCAN_Ins];

	/* Disable the FlexCAN module */
	FlexCAN_ModuleControl(FlexCANx, DISABLE);

   /* Selects clock source for CAN module */
	FlexCAN_ClkSrcSelect(FlexCANx, FlexCAN_Config->CLkSrc);

   /* Enable FlexCAN module -> FlexCAN automatically enters Freeze Mode */
	FlexCAN_ModuleControl(FlexCANx, ENABLE);

   /* Sets desired bit rate for FlexCAN module */
   FlexCAN_SetBitRate(FlexCANx, FlexCAN_Config->ClkFreq, FlexCAN_Config->BitRate);

   /* Clear MSG Buffers */
   FlexCAN_ClearMB(FlexCANx);

   /* Select mode for FlexCAN module */
   FlexCAN_RunModeSelect(FlexCANx, FlexCAN_Config->RunMode);

   /* Interrupts controlling for FLexCAN module */
   FlexCAN_IntControl(FlexCANx, FlexCAN_Config->IntControl);

   /* Sets desired bit rate for FLexCAN module */
   FlexCAN_SetBitRate(FlexCANx, FlexCAN_Config->ClkFreq, FlexCAN_Config->BitRate);

   /* Exit Freeze mode */
   FLexCAN_FreezeModeControl(FlexCANx, DISABLE);
}

void FlexCAN_DeInit(FlexCAN_Instance_e FlexCAN_Ins)
{
	FLEXCAN_Type *FlexCANx = FlexCAN_Base_Addr[FlexCAN_Ins];

	/* Reset memory-mapped registers */
	FlexCAN_SoftReset(FlexCANx);

	/* Disable the FlexCAN module */
	FlexCAN_ModuleControl(FlexCANx, DISABLE);
}

void Driver_FlexCAN_CallbackRegister(FlexCAN_CallbackType CallbackFunc, uint8_t CallbackID)
{
	/* Saving handler function to the corresponding callback pointer */
	DRV_FlexCAN_Callback[CallbackID] = CallbackFunc;
}

void FlexCAN_MbInit(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex,
					FlexCAN_MbHeaderType * FLexCAN_MbConfig){
	FlexCAN_MbStructureType * Mbx = &((FlexCAN_MB[FlexCAN_Ins])->MB[MbIndex]);

	FlexCAN_MBSetEDL(Mbx, FLexCAN_MbConfig->EDL);

	FlexCAN_MBSetBRS(Mbx, FLexCAN_MbConfig->BRS);

	FlexCAN_MBSetESI(Mbx, FLexCAN_MbConfig->ESI);

	/* SRR must always be 1 */
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_SRR_MASK;

	FlexCAN_MBSetIDType(Mbx, FLexCAN_MbConfig->IdType);

	FlexCAN_MBSetRTR(Mbx, FLexCAN_MbConfig->IsRemote);

	FlexCAN_MBSetDataLength(Mbx, FLexCAN_MbConfig->DataLen);

	FlexCAN_MBSetID(Mbx, FLexCAN_MbConfig->MbID);

	FlexCAN_MbSetType(Mbx, FLexCAN_MbConfig->MbType);

	FlexCAN_MbSetInterrupt(FlexCAN_Ins, MbIndex, FLexCAN_MbConfig->IsEnableMbInt);

}

void FlexCAN_Transmit(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex,
		              uint8_t * MsgData){
	FLEXCAN_Type * FlexCANx = FlexCAN_Base_Addr[FlexCAN_Ins];
	FlexCAN_MbStructureType * Mbx = &((FlexCAN_MB[FlexCAN_Ins])->MB[MbIndex]);
	uint8_t DataLen = (((Mbx->Header[0]) & FLEXCAN_RAMn_DATA_WORD_0_DLC_MASK)
						>> FLEXCAN_RAMn_DATA_WORD_0_DLC_SHIFT);
	uint8_t Index = 0;
	uint8_t WordIndex = 0;
	uint8_t WordSize = 4;
	uint8_t ByteOffset = 0;

	/* Clear Int Flag */
	FlexCANx->IFLAG1 &= ~(1 << MbIndex);

	/* Clear data */
	Mbx->Payload[0] = 0;
	Mbx->Payload[1] = 0;

	/* Message data to RAM */
	for(Index = 0; Index < DataLen; Index++){
		WordIndex = Index / WordSize;
		ByteOffset = 3 - (Index % WordSize);
		Mbx->Payload[WordIndex] |= MsgData[Index] << (8 * ByteOffset);
	}

	/* Start transmitting */
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_CODE(Tx_CODE_DATA);
}

void FlexCAN_ReadMailboxData(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex,
		                     uint8_t * MsgData){

	FlexCAN_MbStructureType * Mbx = &((FlexCAN_MB[FlexCAN_Ins])->MB[MbIndex]);
	uint8_t DataLen = (((Mbx->Header[0]) & FLEXCAN_RAMn_DATA_WORD_0_DLC_MASK)
							>> FLEXCAN_RAMn_DATA_WORD_0_DLC_SHIFT);
	uint8_t Index = 0;
	uint8_t WordIndex = 0;
	uint8_t WordSize = 4;
	uint8_t ByteOffset = 0;

	for(Index = 0; Index < DataLen; Index++){
		WordIndex = (Index / WordSize);
		ByteOffset = 3 - (Index % WordSize);
		MsgData[Index] = ((Mbx->Payload[WordIndex]) >> (8 * ByteOffset));
	}
	/* Unlock the Mailbox */
	(void)((Mbx->Header[0]) & FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_MASK
			>> FLEXCAN_RAMn_DATA_WORD_0_TIME_STAMP_SHIFT);
}

/* ----------------------------------------------------------------------------
   -- Private functions
   ---------------------------------------------------------------------------- */
static void FlexCAN_ModuleControl(FLEXCAN_Type *FlexCANx, uint8_t EnOrDis)
{
	if(EnOrDis == ENABLE)
	{
		/* Enable the FlexCAN module */
	   FlexCANx->MCR &= ~FLEXCAN_MCR_MDIS_MASK;

	   /* Wait for FRZACK */
	   while(((FlexCANx->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT) != SET);
	}
	else
	{
		/* Disable the FlexCAN module */
	   FlexCANx->MCR |= FLEXCAN_MCR_MDIS_MASK;
	}
}

static void FlexCAN_ClkSrcSelect(FLEXCAN_Type *FlexCANx, FlexCAN_ClkSrc_e CLkSrc)
{
	/* Selects clock source for FlexCAN module*/
   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_CLKSRC_MASK;
   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_CLKSRC(CLkSrc);
}

static void FlexCAN_ClearMB(FLEXCAN_Type *FlexCANx)
{
	uint8_t i = 0;

	/* Clears all MBs of FlexCAN module */
   for(i = 0U; i < 128U ;i++)
   {
	   FlexCANx->RAMn[i] = 0x0;
   }
}

static void FlexCAN_RunModeSelect(FLEXCAN_Type *FlexCANx, FlexCAN_Mode_e RunMode)
{
   if(RunMode == FlexCAN_MODE_LOOPBACK)
   {
	   /* Enables loop back mode */
	   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_LPB_MASK;
   }
   else
   {
	   /* Enables normal mode */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_LPB_MASK;
   }
}

static void FlexCAN_IntControl(FLEXCAN_Type *FlexCANx, FlexCAN_InterruptType IntType)
{
   /* Error interrupt configuration */
   if(IntType.IntError == FlexCAN_INT_ERROR_ENABLE)
   {
	   /* Enable error interrupt */
	   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_ERRMSK_MASK;
   }
   else
   {
	   /* Disable error interrupt */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_ERRMSK_MASK;
   }

   /* ORed interrupt configuration */
   if((IntType.IntBusOff | IntType.IntTxWarning | IntType.IntRxWarning) == SET)
   {
	   /* Bus Off Interrupt configuration */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_BOFFMSK_MASK;
	   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_BOFFMSK(IntType.IntBusOff);

	   /* Tx warning Interrupt configuration */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_TWRNMSK_MASK;
	   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_TWRNMSK(IntType.IntTxWarning);

	   /* Rx warning Interrupt configuration */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_RWRNMSK_MASK;
	   FlexCANx->CTRL1 |= FLEXCAN_CTRL1_RWRNMSK(IntType.IntRxWarning);
   }
   else
   {
	   /* Interrupts disabled */
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_BOFFMSK_MASK;
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_BOFFMSK_MASK;
	   FlexCANx->CTRL1 &= ~FLEXCAN_CTRL1_BOFFMSK_MASK;
   }
}

static void FlexCAN_SetBitRate(FLEXCAN_Type *FlexCANx, uint32_t Clocks, uint32_t BitRate)
{
	uint32_t prescaler = 0;
    uint32_t prop_seg = 0;
    uint32_t tseg = 0;
    uint32_t actual_baud = 0;
    uint32_t best_prescaler = 0, best_prop_seg = 0, best_tseg = 0;
    uint32_t min_error = UINT32_MAX;

    for (prop_seg = 1; prop_seg <= 7; prop_seg++)
    {
        for (tseg = 2; tseg <= 8; tseg++)
        {
            prescaler = (Clocks / (BitRate * (1 + prop_seg + 2 * tseg))) - 1;

            if (prescaler > 255 || prescaler < 0)
                continue;
            if ((1 + prop_seg + 2 * tseg) < 11 || (1 + prop_seg + 2 * tseg) > 21)
                continue;
            if (((tseg * 100) / (1 + prop_seg + 2 * tseg) > 25) || ((tseg * 100) / (1 + prop_seg + 2 * tseg) < 20))

                actual_baud = Clocks / ((prescaler + 1) * (1 + prop_seg + 2 * tseg));

            uint32_t error = (actual_baud > BitRate) ? (actual_baud - BitRate) : (BitRate - actual_baud);

            if (error < min_error)
            {
                min_error = error;
                best_prescaler = prescaler;
                best_prop_seg = prop_seg - 1;
                best_tseg = tseg - 1;
            }
        }
    }
    FlexCANx->CTRL1 |= (best_prescaler << FLEXCAN_CTRL1_PRESDIV_SHIFT) | (best_prop_seg << FLEXCAN_CTRL1_PROPSEG_SHIFT) | (best_tseg << FLEXCAN_CTRL1_PSEG1_SHIFT) | (best_tseg << FLEXCAN_CTRL1_PSEG2_SHIFT);
}

static void FLexCAN_FreezeModeControl(FLEXCAN_Type *FlexCANx, uint8_t EnOrDis)
{
	if(EnOrDis == ENABLE)
	{
		/* Enters freeze mode */
		FlexCANx->MCR |= FLEXCAN_MCR_FRZ_MASK;

	   /* Wait for FRZACK */
	   while(((FlexCANx->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT) != SET);
	}
	else
	{
		/* Exits freeze mode */
		FlexCANx->MCR &= ~FLEXCAN_MCR_FRZ_MASK;

	   /* Wait for FRZACK to clear (not in freeze mode) */
	   while ((FlexCANx->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT);

	   /* Wait for NOTRDY to clear (module ready) */
	   while ((FlexCANx->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT);
	}
}

static void FlexCAN_SoftReset(FLEXCAN_Type *FlexCANx)
{
	/* Reset memory-mapped registers */
	FlexCANx->MCR |= FLEXCAN_MCR_SOFTRST_MASK;

	/* Wait for the reset procedure completed */
	while(((FlexCANx->MCR & FLEXCAN_MCR_SOFTRST_MASK) >> FLEXCAN_MCR_SOFTRST_SHIFT) == SET);
}

static void FlexCAN_MBSetEDL(FlexCAN_MbStructureType * Mbx, uint8_t EDLValue){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_EDL_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_EDL(EDLValue);
}

static void FlexCAN_MBSetBRS(FlexCAN_MbStructureType * Mbx, uint8_t BRSValue){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_BRS_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_BRS(BRSValue);
}

static void FlexCAN_MBSetESI(FlexCAN_MbStructureType * Mbx, uint8_t ESIValue){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_ESI_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_ESI(ESIValue);
}

static void FlexCAN_MBSetIDType(FlexCAN_MbStructureType * Mbx, FlexCAN_MsgIDType_e IDType){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_IDE_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_IDE(IDType);
}

static void FlexCAN_MBSetRTR(FlexCAN_MbStructureType * Mbx, bool IsRemote){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_RTR_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_RTR(IsRemote);
}

static void FlexCAN_MBSetDataLength(FlexCAN_MbStructureType * Mbx, uint16_t Datalen){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_DLC_MASK;
	Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_DLC(Datalen);
}

static void FlexCAN_MBSetID(FlexCAN_MbStructureType * Mbx, uint16_t ID){
	Mbx->Header[1] &= ~FLEXCAN_RAMn_DATA_WORD_1_ID_MASK;
	Mbx->Header[1] |= FLEXCAN_RAMn_DATA_WORD_1_ID(ID);
}

static void FlexCAN_MbSetType(FlexCAN_MbStructureType * Mbx, FlexCAN_MbType_e MbType){
	Mbx->Header[0] &= ~FLEXCAN_RAMn_DATA_WORD_0_CODE_MASK;
	if(MbType == FlexCAN_MB_TX){
		/* Set code to INACTIVE status */
		Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_CODE(Tx_CODE_INACTIVE);
	}else{
		Mbx->Header[0] |= FLEXCAN_RAMn_DATA_WORD_0_CODE(Rx_CODE_EMPTY);
	}
}

static void FlexCAN_MbSetInterrupt(FlexCAN_Instance_e FlexCAN_Ins, FlexCAN_MbIndex_e MbIndex, bool IsEnableMbInt){
	FLEXCAN_Type * FlexCANx = FlexCAN_Base_Addr[FlexCAN_Ins];
	IRQn_Type IntIndex = DMA0_IRQn;

	if(FlexCAN_Ins == 0){
		if(MbIndex <= 15){
			IntIndex = CAN0_ORed_0_15_MB_IRQn;
		}else{
			IntIndex = CAN0_ORed_16_31_MB_IRQn;
		}
	}else if(FlexCAN_Ins == 1){
		IntIndex = CAN1_ORed_0_15_MB_IRQn;
	}else{
		IntIndex = CAN2_ORed_0_15_MB_IRQn;
	}

	if(IsEnableMbInt){
		FlexCANx->IMASK1 |= (1 << MbIndex);
		NVIC_EnableIRQn(IntIndex);
	}else{
		FlexCANx->IMASK1 &= ~(1 << MbIndex);
		NVIC_DisableIRQn(IntIndex);
	}
}

/* Handlers for FlexCAN interrupts */
void CAN0_ORed_IRQHandler()
{
	/* CAN0 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
	DRV_FlexCAN_Callback[0]();
}
void CAN0_Error_IRQHandler()
{
	/* CAN0 Interrupt indicating that errors were detected on the CAN bus */
	DRV_FlexCAN_Callback[1]();
}

void CAN0_ORed_0_15_MB_IRQHandler()
{
	/* CAN0 OR'ed Message buffer (0-15)*/
	DRV_FlexCAN_Callback[2]();
}

void CAN0_ORed_16_31_MB_IRQHandler()
{
	/* CAN0 OR'ed Message buffer (16-31)*/
	DRV_FlexCAN_Callback[3]();
}

void CAN1_Red_IRQHandler()
{
	/* CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
	DRV_FlexCAN_Callback[4]();
}
void CAN1_Error_IRQHandler()
{
	/* CAN1 Interrupt indicating that errors were detected on the CAN bus */
	DRV_FlexCAN_Callback[5]();
}

void CAN1_ORed_0_15_MB_IRQHandler()
{
	/* CAN1 OR'ed Message buffer (0-15)*/
	DRV_FlexCAN_Callback[6]();
}

void CAN1_ORed_16_31_MB_IRQHandler()
{
	/* CAN1 OR'ed Message buffer (16-31)*/
	DRV_FlexCAN_Callback[7]();
}

void CAN2_ORed_IRQHandler()
{
	/* CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
	DRV_FlexCAN_Callback[8]();
}
void CAN2_Error_IRQHandler()
{
	/* CAN2 Interrupt indicating that errors were detected on the CAN bus */
	DRV_FlexCAN_Callback[9]();
}

void CAN2_ORed_0_15_MB_IRQHandler()
{
	/* CAN2 OR'ed Message buffer (0-15)*/
	DRV_FlexCAN_Callback[10]();
}

void CAN2_ORed_16_31_MB_IRQHandler()
{
	/* CAN2 OR'ed Message buffer (16-31)*/
	DRV_FlexCAN_Callback[11]();
}
