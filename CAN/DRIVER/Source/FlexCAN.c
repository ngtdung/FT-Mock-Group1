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

FlexCAN_CallbackType DRV_FlexCAN_Callback[FLEXCAN_INSTANCE_COUNT*2U];

/**
 * Base addresses for FLEXCAN modules.
 * @note This array is indexed by LPUART instance numbers.
 */
static FLEXCAN_Type *FlexCAN_Base_Addr[FLEXCAN_INSTANCE_COUNT] = IP_FLEXCAN_BASE_PTRS;

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

    // Duyá»‡t qua cÃ¡c giÃ¡ trá»‹ há»£p lÃ½ cho PROP_SEG vÃ  TSEG
    for (prop_seg = 1; prop_seg <= 7; prop_seg++)
    {
        for (tseg = 2; tseg <= 8; tseg++)
        {
            // TÃ­nh toÃ¡n prescaler cho cÃ¡c giÃ¡ trá»‹ Ä‘ang xÃ©t
            prescaler = (Clocks / (BitRate * (1 + prop_seg + 2 * tseg))) - 1;

            // Kiá»ƒm tra prescaler trong giá»›i háº¡n
            if (prescaler > 255 && prescaler < 0)
                continue;
            if ((1 + prop_seg + 2 * tseg) > 11 && (1 + prop_seg + 2 * tseg) < 21)
                continue;
            if (((tseg * 100) / (1 + prop_seg + 2 * tseg) > 24) && ((tseg * 100) / (1 + prop_seg + 2 * tseg) < 20))

                // TÃ­nh toÃ¡n baud rate thá»±c táº¿
                actual_baud = Clocks / ((prescaler + 1) * (1 + prop_seg + 2 * tseg));

            // TÃ­nh sai sá»‘ giá»¯a baud rate mong muá»‘n vÃ  thá»±c táº¿
            uint32_t error = (actual_baud > BitRate) ? (actual_baud - BitRate) : (BitRate - actual_baud);

            // LÆ°u giÃ¡ trá»‹ tá»‘t nháº¥t khi sai sá»‘ nhá»� nháº¥t
            if (error < min_error)
            {
                min_error = error;
                best_prescaler = prescaler;
                best_prop_seg = prop_seg;
                best_tseg = tseg;
            }
            else
            {
            	/* Do nothing */
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

void CAN1_Red_IRQHandler()
{
	/* CAN1 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
	DRV_FlexCAN_Callback[2]();
}
void CAN1_Error_IRQHandler()
{
	/* CAN1 Interrupt indicating that errors were detected on the CAN bus */
	DRV_FlexCAN_Callback[3]();
}

void CAN2_ORed_IRQHandler()
{
	/* CAN2 OR'ed [Bus Off OR Transmit Warning OR Receive Warning] */
	DRV_FlexCAN_Callback[4]();
}
void CAN2_Error_IRQHandler()
{
	/* CAN2 Interrupt indicating that errors were detected on the CAN bus */
	DRV_FlexCAN_Callback[5]();
}
