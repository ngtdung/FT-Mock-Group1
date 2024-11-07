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
    uint32_t PRESCALER = 0;
    uint32_t PROP_SEG = 0;
    uint32_t P_SEG = 0;
    uint32_t ACTUAL_BAUD = 0;
    uint32_t BEST_PRESCALER = 0, BEST_PROP_SEG = 0, BEST_P_SEG = 0;
    uint32_t MIN_ERROR = UINT32_MAX;
	uint32_t ERROR = 0;
	uint32_t BITRATE_SET = 0;

    // Duyá»‡t qua cÃ¡c giÃ¡ trá»‹ há»£p lÃ½ cho PROP_SEG vÃ  TSEG
    for (PROP_SEG = 1; PROP_SEG <= 7; PROP_SEG++)
    {
        for (P_SEG = 2; P_SEG <= 8; P_SEG++)
        {
            // TÃ­nh toÃ¡n prescaler cho cÃ¡c giÃ¡ trá»‹ Ä‘ang xÃ©t
            PRESCALER = (Clocks / (BitRate * (1 + PROP_SEG + 2 * P_SEG))) - 1;

            // Kiá»ƒm tra prescaler trong giá»›i háº¡n
            if (PRESCALER > 255 && PRESCALER < 0)
                continue;
            if ((1 + PROP_SEG + 2 * P_SEG) > 11 && (1 + PROP_SEG + 2 * P_SEG) < 21)
                continue;
            if (((P_SEG * 100) / (1 + PROP_SEG + 2 * P_SEG) > 24) && ((P_SEG * 100) / (1 + PROP_SEG + 2 * P_SEG) < 20))

                // TÃ­nh toÃ¡n baud rate thá»±c táº¿
                ACTUAL_BAUD = Clocks / ((PRESCALER + 1) * (1 + PROP_SEG + 2 * P_SEG));

            // TÃ­nh sai sá»‘ giá»¯a baud rate mong muá»‘n vÃ  thá»±c táº¿
            ERROR = (ACTUAL_BAUD > BitRate) ? (ACTUAL_BAUD - BitRate) : (BitRate - ACTUAL_BAUD);

            // LÆ°u giÃ¡ trá»‹ tá»‘t nháº¥t khi sai sá»‘ nhá»� nháº¥t
            if (ERROR < MIN_ERROR)
            {
                MIN_ERROR = ERROR;
                BEST_PRESCALER = PRESCALER;
                BEST_PROP_SEG = PROP_SEG;
                BEST_P_SEG = P_SEG;
            }
            else
            {
            	/* Do nothing */
            }
        }
    }
	BITRATE_SET = (BEST_PRESCALER << FLEXCAN_CTRL1_PRESDIV_SHIFT) | (BEST_PROP_SEG << FLEXCAN_CTRL1_PROPSEG_SHIFT) | (BEST_P_SEG << FLEXCAN_CTRL1_PSEG1_SHIFT) | (BEST_P_SEG << FLEXCAN_CTRL1_PSEG2_SHIFT);
	/* Sets best parameters for FlexCAN module */
    FlexCANx->CTRL1 |= BITRATE_SET;
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
