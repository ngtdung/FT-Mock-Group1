/*================================================================================================
============================================INCLUDE FILES=========================================
==================================================================================================*/
#include "DRV_LPUART.h"

/*================================================================================================
============================================MACROS DEFINE=========================================
==================================================================================================*/
/**
 * @brief This macro defines bit fields that will be set in CTRL register
 *
 */
#define DRV_UART_CTRL_ERROR_REC_INTERRUPT_MASK 0xF000000u

/**
 * @brief This macro defines bit fields that will be set in STAT register
 *
 */
#define DRV_UART_STAT_ERROR_REC_FLAG_MASK 0xF0000u


/*================================================================================================
=========================================GLOBAL VARIABLES=========================================
==================================================================================================*/
/**
 * @brief This static global array is a const array of uart module base address equivalent with instances
 *
 */
static LPUART_Type *const s_lpuartBase[LPUART_INSTANCE_COUNT] = IP_LPUART_BASE_PTRS;

/**
 * @brief This static global array is a const array of uart interrupt handler function equivalent with instances
 *
 */
static IRQn_Type s_lpuartRxTxIrqId[LPUART_INSTANCE_COUNT] = {LPUART0_RxTx_IRQn, LPUART1_RxTx_IRQn, LPUART2_RxTx_IRQn};


/**
 * @brief This static global receive buffer is used for handle interrupt receive function
 *
 */
static DRV_UART_RxBuffType s_UARTrxBufferstr[LPUART_INSTANCE_COUNT];

/**
 * @brief This static global transmit buffer is used for handle interrupt transmit function
 *
 */
static DRV_UART_TxBuffType s_UARTtxBufferstr[LPUART_INSTANCE_COUNT];

/**
 * @brief Function pointer for registering callback function for detecting errors
 *
 */
static DRV_CallBackErrorLPUART s_UARTx_ErrorCallBack = NULL;


/**
 * @brief Global pointer function array for a specific callback function interrupt UART
 *
 */

static DRV_CallBack_LPUART s_UARTfunctionPointer[3] = {NULL, NULL, NULL};

/**
 * @brief This static global array for configuring UART module
 *
 */
static DRV_UART_ConfigType s_UARTconfig[LPUART_INSTANCE_COUNT];

/**
 * @brief This static global is for choosing clock source
 *
 */
static uint32_t s_UARTclkSource[LPUART_INSTANCE_COUNT];

/*================================================================================================
========================================FUNCTIONS PROTOTYPE=======================================
==================================================================================================*/

/**
 * @brief This function is responsible fo configuring bits per character for the UART module
 *
 * @param instance : instance decides the LPUART base pointer
 * @param bitCountPerChar : Number of bits per char (8, 9, or 10, depending on the LPUART instance)
 * @param parityMode : Specifies whether parity bit is enabled for the parity mode
 * @return DRV_UART_StatusType
 */
static DRV_UART_StatusType DRV_UART_SetBitCountPerChar(const DRV_UART_InstanceType instance, const DRV_UART_DataBitCountType bitCountPerChar, const DRV_UART_ParityModeType parityMode);

/**
 * @brief This function is responsible for configuring the parity mode for the UART module
 *
 * @param instance : instance decides the LPUART base pointer
 * @param parityMode : Specifies whether parity bit is enabled for the parity mode
 * @return DRV_UART_StatusType
 */
static DRV_UART_StatusType DRV_UART_SetParityMode(const DRV_UART_InstanceType instance, const DRV_UART_ParityModeType parityMode);

/**
 * @brief This function is responsible for configuring stop bit for the UART module
 *
 * @param instance : instance decides the LPUART base pointer
 * @param stopBitCount :Number of stop bits depend on DRV_UART_StopBitCountType enum
 * @return DRV_UART_StatusType
 */
static DRV_UART_StatusType DRV_UART_SetStopBit(const DRV_UART_InstanceType instance, const uint8_t stopBitCount);

/**
 * @brief This function is responsible for handling receive data via interrupt
 *
 * @param instance : instance decides the LPUART base pointer
 */
static void DRV_UART_HanldeInterruptRx(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for handling transmit data via interrupt
 *
 * @param instance : instance decides the LPUART base pointer
 */
static void DRV_UART_HanldeInterruptTx(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for handling error via interrupt
 *
 * @param instance : instance decides the LPUART base pointer
 */
static void DRV_UART_HanldeInterruptError(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for checking the interrupt flag of revceiver
 *
 * @param instance : instance decides the LPUART base pointer
 * @return true : receive data buffer is full
 * @return false : receive data buffer is empty
 */
static bool DRV_UART_CheckIFReceiver(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for checking the interrupt errors
 *
 * @param instance : instance decides the LPUART base pointer
 * @return true : The UART module encountered errors
 * @return false : The UART module has no errors
 */
static bool DRV_UART_CheckIFError(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for checking the interrupt flag of transmitter
 *
 * @param instance : instance decides the LPUART base pointer
 * @return true : transmit data buffer is empty
 * @return false : transmit data buffer is full
 */
static bool DRV_UART_CheckIFTransmitter(DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for handling interrupt request.
 * This function decides to execute type of the interrupt function
 *
 * @param instance : instance decides the LPUART base pointer
 */
static void DRV_UART_HanldeInterrupt(DRV_UART_InstanceType instance);

/*================================================================================================
======================================FUNCTIONS DEFNITION=========================================
==================================================================================================*/

/**
 * @brief : This function is responsible fo configuring bits per character for the UART module
 *
 */
static DRV_UART_StatusType DRV_UART_SetBitCountPerChar(const DRV_UART_InstanceType instance, const DRV_UART_DataBitCountType bitCountPerChar, const DRV_UART_ParityModeType parityMode)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_DataBitCountType temp_count = (uint32_t)bitCountPerChar;

	/* if parity is enabled, count increment 1 */
	if ((bool)parityMode)
	{
		temp_count += 1U;
	}

	/* If the desired bit count is 10-bits, set M10 bit of BAUD register */
	if (temp_count == DRV_UART_dataBitCount_10)
	{
		/*Enable 10-bit characters length*/
		base->BAUD = ((base->BAUD & ~LPUART_BAUD_M10_MASK) | (uint32_t)1 << LPUART_BAUD_M10_SHIFT);
	}
	if (temp_count != DRV_UART_dataBitCount_10)
	{
		base->BAUD &= ~(uint32_t)1 << LPUART_BAUD_M10_SHIFT;
		base->CTRL &= ~(uint32_t)1 << LPUART_CTRL_M_SHIFT;
		base->CTRL &= ~(uint32_t)1 << LPUART_CTRL_M7_SHIFT;
		if (temp_count == DRV_UART_dataBitCount_8)
		{
			base->CTRL &= ~(uint32_t)1 << LPUART_CTRL_M_SHIFT;
		}
		if (temp_count == DRV_UART_dataBitCount_9)
		{
			base->CTRL |= (uint32_t)1 << LPUART_CTRL_M_SHIFT;
		}
		if (temp_count == DRV_UART_dataBitCount_7)
		{
			base->CTRL |= (uint32_t)1 << LPUART_CTRL_M7_SHIFT;
		}
	}
	return DRV_UART_ok;
}

/**
 * @brief This function is responsible for configuring the parity mode for the UART module
 *
 */
static DRV_UART_StatusType DRV_UART_SetParityMode(const DRV_UART_InstanceType instance, const DRV_UART_ParityModeType parityMode)
{
	LPUART_Type *base = s_lpuartBase[instance];
	/* Enable parity mode PE */
	base->CTRL = (base->CTRL & ~LPUART_CTRL_PE_MASK) | (((uint32_t)parityMode >> 0x01U) << LPUART_CTRL_PE_SHIFT);
	/* Select parity mode PT */
    base->CTRL = (base->CTRL & ~LPUART_CTRL_PT_MASK) | (((uint32_t)parityMode & 0x01U) << LPUART_CTRL_PT_SHIFT);
	return DRV_UART_ok;
}

/**
 * @brief This function is responsible for configuring stop bit for the UART module
 *
 */

static DRV_UART_StatusType DRV_UART_SetStopBit(const DRV_UART_InstanceType instance, const uint8_t stopBitCount)
{
	LPUART_Type *base = s_lpuartBase[instance];
	base->BAUD = (base->BAUD & ~(uint32_t)1 << LPUART_BAUD_SBNS_SHIFT) | ((uint32_t)stopBitCount << LPUART_BAUD_SBNS_SHIFT); // Reset and set SBNS bit
	return DRV_UART_ok;
}


/**
 * @brief This function is responsible for setting  The UART's baud rate
 *
 */
DRV_UART_StatusType DRV_UART_SetBaudRate(const DRV_UART_InstanceType instance, const DRV_UART_BaudrateValueType baudRate)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_StatusType ret_val = DRV_UART_ok;
	uint32_t UART_SourceCLK = s_UARTclkSource[instance];
	uint8_t osr_compare = 4;  /* osr 1st value = 4 */
	uint16_t sbr_compare = 0; /* sbr 1st value with osr = 4 */
	uint16_t sbr_cmploop = 0; /* Using for loop */
	uint32_t baud_cal = 0;	  /* baudrate 1st value with osr = 4 */
	uint32_t baud_diff = 0;	  /* Using for loop */
	uint32_t baud_loop = 0;	  /* Using for loop */
	uint32_t diff_loop = 0;	  /* Using for loop */
	sbr_compare = (uint16_t)(UART_SourceCLK / (baudRate * (uint32_t)osr_compare));
	baud_cal = (uint32_t)(UART_SourceCLK / ((uint32_t)sbr_compare * osr_compare));

	if (baud_cal > baudRate)
	{
		baud_diff = baud_cal - baudRate;
	}
	else
	{
		baud_diff = baudRate - baud_cal;
	}
	for (uint32_t i = 5; i < 33; i++)
	{
		sbr_cmploop = (uint16_t)(UART_SourceCLK / (baudRate * (uint32_t)i));
		baud_loop = (uint32_t)(UART_SourceCLK / ((uint32_t)sbr_cmploop * i));
		if (baud_loop > baudRate)
		{
			diff_loop = baud_loop - baudRate;
		}
		else
		{
			diff_loop = baudRate - baud_loop;
		}
		if (diff_loop < baud_diff)
		{
			osr_compare = i;
			sbr_compare = sbr_cmploop;
			baud_diff = diff_loop;
		}
	}

	/* if OSR is between 4x and 7x oversampling, turn on BOTHEDGE */
	if (osr_compare < 8)
	{
		/* set bit BOTHEDGE pos 17 */
		base->BAUD = ((base->BAUD & ~(uint32_t)1 << 17) | (uint32_t)1 << 17);
	}

	/*If instance == DRV_UART_instance_1, always assign to osr_compare = 16*/
	if(instance == DRV_UART_instance_1) {
		osr_compare = 16;
		sbr_compare = UART_SourceCLK / (baudRate * osr_compare);
	}
	osr_compare -= 1U;
	/*program the OSR value (bit value is one less than actual value)*/
	base->BAUD = ((base->BAUD & ~(uint32_t)0x1F << 24) | (uint32_t)osr_compare << 24); /* set osr_cmp pos 24, mask = 1F LPUART_BAUD_OSR_MASK*/

	/*write the SBR value to the BAUD registers*/
	base->BAUD = ((base->BAUD & ~(uint32_t)0x1FFF << 0) | (uint32_t)sbr_compare << 0); /* set sbr_compare pos 0, mask = 1FFF LPUART_BAUD_SBR_MASK*/
	return ret_val;
}

/**
 * @brief : This function is responsible for initializing UART module
 *
 */
DRV_UART_StatusType DRV_UART_Init(const DRV_UART_InstanceType instance, const DRV_UART_ConfigType *uartConfig)
{
	DRV_UART_StatusType ret_val = DRV_UART_stateReady;
	if(uartConfig->clockSource == DRV_UART_fircClkSouce)
	{
		s_UARTclkSource[instance] = 48000000U;
	}
	else if(uartConfig->clockSource == DRV_UART_soscClkSouce)
	{
		s_UARTclkSource[instance] = 8000000U;
	}
	LPUART_Type *base = s_lpuartBase[instance];
	/* Check condition */
	if (instance < DRV_UART_instanceCount && uartConfig != NULL)
	{
		/* Set the default oversampling ratio (16) and baud-rate divider (4)*/
		base->BAUD = 0x0F000004;

		/* Clear the error/interrupt flags*/
		base->STAT = 0xC01FC000;

		/* Reset all features/interrupts by default*/
		base->CTRL = 0x00000000;

		/* reset match address */
		base->MATCH = 0x00000000;

		/*Set bit count for LPUART*/
		DRV_UART_SetBitCountPerChar(instance, uartConfig->bitCountPerChar, (bool)uartConfig->parityMode);

		/*Set parity mode for LPUART*/
		DRV_UART_SetParityMode(instance, uartConfig->parityMode);

		/*Set stop bit number*/
		DRV_UART_SetStopBit(instance, uartConfig->stopBit);

		/*Set baudrate*/
		DRV_UART_SetBaudRate(instance, uartConfig->baudRate);

		/*Enable interrupt for given LPUART*/
		if (DRV_UART_usingInterrupts == uartConfig->transferType)
		{
			NVIC->ISER[s_lpuartRxTxIrqId[instance] / 32] = 1 << (s_lpuartRxTxIrqId[instance] % 32);
		}
		s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateReady;
		s_UARTtxBufferstr[instance].isTxBusy = false;
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateReady;
		s_UARTrxBufferstr[instance].isRxBusy = false;
	}
	else
	{
		return ret_val = DRV_UART_error;
	}
	return ret_val;
}

/**
 * @brief : This function is responsible for enabling the Tx
 *
 */
void DRV_UART_EnableTx(const DRV_UART_InstanceType instance)
{
	s_lpuartBase[instance]->CTRL = ((s_lpuartBase[instance]->CTRL & ~LPUART_CTRL_TE_MASK) | (uint32_t)1 << LPUART_CTRL_TE_SHIFT);
}

/**
 * @brief : This function is responsible for disabling the Tx
 *
 */
void DRV_UART_DisableTx(const DRV_UART_InstanceType instance)
{
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_TE_MASK;
}

/**
 * @brief : This function is responsible for enabling the Rx
 *
 */
void DRV_UART_EnableRx(const DRV_UART_InstanceType instance)
{
	s_lpuartBase[instance]->CTRL = ((s_lpuartBase[instance]->CTRL & ~LPUART_CTRL_RE_MASK) | (uint32_t)1 << LPUART_CTRL_RE_SHIFT);
}

/**
 * @brief : This function is responsible for disabling the Rx
 *
 */
void DRV_UART_DisableRx(const DRV_UART_InstanceType instance)
{
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_RE_MASK;
}


/**
 * @brief : This function is responsible for transmitting data via interrupt method
 *
 */
DRV_UART_StatusType DRV_UART_SendDataPolling(const DRV_UART_InstanceType instance, const uint8_t *txBuff, uint16_t txSize)
{
	LPUART_Type *base = s_lpuartBase[instance];
	uint8_t tempData1, tempData2;
	DRV_UART_StatusType ret_val = DRV_UART_stateReady;
	if (instance < LPUART_INSTANCE_COUNT && txBuff != NULL && txSize > 0U)
	{
		if(!(s_UARTtxBufferstr[instance].isTxBusy))
		{
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_txBusy;
			s_UARTtxBufferstr[instance].isTxBusy = true;
			/* Enable the LPUART transmitter */
			base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | (1UL << LPUART_CTRL_TE_SHIFT);
			/* Wait for the register write operation to complete */
			while ((base->CTRL & LPUART_CTRL_TE_MASK) != LPUART_CTRL_TE_MASK)
			{
			}
			while (txSize > 0U)
			{
				while (!((bool)(base->STAT & LPUART_STAT_TDRE_MASK) != 0))
				{
				}
				switch (s_UARTconfig[instance].bitCountPerChar)
				{
				case DRV_UART_dataBitCount_7:
					base->DATA = *txBuff & (uint8_t)0x7F;
					while ((s_lpuartBase[instance]->STAT & LPUART_STAT_TC_MASK) == 0)
					{
					}
					++txBuff;
					txSize--;
					break;
				case DRV_UART_dataBitCount_8:
					base->DATA = *txBuff & (uint8_t)0xFF;
					while ((s_lpuartBase[instance]->STAT & LPUART_STAT_TC_MASK) == 0)
					{
					}
					++txBuff;
					--txSize;
					break;
				case DRV_UART_dataBitCount_9:
					tempData1 = *txBuff;
					tempData2 = *(txBuff+1);
					base->DATA = ((tempData2 << 8) | tempData1) & (uint16_t)0x01FF;
					while ((base->STAT & LPUART_STAT_TC_MASK) == 0)
					{
					}
					++txBuff;
					++txBuff;
					txSize -= 2U;
					break;
				case DRV_UART_dataBitCount_10:
					tempData1 = *txBuff;
					tempData2 = *(txBuff+1);
					base->DATA = ((tempData2 << 8) | tempData1) & (uint16_t)0x03FF;
					while ((base->STAT & LPUART_STAT_TC_MASK) == 0)
					{
					}
					++txBuff;
					++txBuff;
					txSize -= 2U;
					break;
				default:
					break;
				}
			}
			/* Disable the LPUART transmitter */
			base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | (0UL << LPUART_CTRL_TE_SHIFT);
			/* Wait for the register write operation to complete */
			while ((base->CTRL & LPUART_CTRL_TE_MASK) == LPUART_CTRL_TE_MASK)
			{
			}
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateReady;
			s_UARTtxBufferstr[instance].isTxBusy = false;
		}
		else
		{
			ret_val = DRV_UART_txBusy;
		}
	}
	else
	{
		ret_val = DRV_UART_error;
	}
	return ret_val;
}

/**
 * @brief : This function is responsible for transmitting data via interrupt method
 *
 */
DRV_UART_StatusType DRV_UART_SendDataInterrupt(const DRV_UART_InstanceType instance, uint8_t *data, uint16_t length)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_StatusType ret_val = DRV_UART_txBusy;

	if (!(s_UARTtxBufferstr[instance].isTxBusy))
	{
		if ((data != NULL) && (length > 0U) && (instance < LPUART_INSTANCE_COUNT))
		{
			s_UARTtxBufferstr[instance].ptxBuff = data;
			s_UARTtxBufferstr[instance].txBuffSize = length;
			s_UARTtxBufferstr[instance].txCount = 0;
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_txBusy;
			s_UARTtxBufferstr[instance].isTxBusy = true;
			/* Enable the LPUART transmitter */
			base->CTRL = (base->CTRL & ~LPUART_CTRL_TE_MASK) | (1UL << LPUART_CTRL_TE_SHIFT);
			/* Wait for the register write operation to complete */
			while ((base->CTRL & LPUART_CTRL_TE_MASK) != LPUART_CTRL_TE_MASK)
			{
			}
			/* enable interrupt Tx*/
			base->CTRL |= LPUART_CTRL_TIE_MASK;
		}
		else
		{
			ret_val = DRV_UART_error;
		}
	}
	else
	{
		ret_val = DRV_UART_txBusy;
	}
	return ret_val;
}

/**
 * @brief : This function is responsible for receiving data via polling method
 *
 */
DRV_UART_StatusType DRV_UART_ReceiveDataPolling(const DRV_UART_InstanceType instance, uint8_t *rxBuff, uint16_t rxSize)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_StatusType ret_val = DRV_UART_stateReady;
	uint16_t data = 0;
	if (!(s_UARTrxBufferstr[instance].isRxBusy))
	{
		/* Check valid parameters*/
		if (instance < LPUART_INSTANCE_COUNT && rxBuff != NULL && rxSize > 0)
		{
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_txBusy;
			s_UARTtxBufferstr[instance].isTxBusy = true;
			/*Enable Receiver*/
			base->CTRL = (base->CTRL & ~LPUART_CTRL_RE_MASK) | (1UL << LPUART_CTRL_RE_SHIFT);
			while ((base->CTRL & LPUART_CTRL_RE_MASK) != LPUART_CTRL_RE_MASK)
			{
			}

			while (rxSize > 0u)
			{
				while ((base->STAT & LPUART_STAT_RDRF_MASK) == 0)
				{
				}
				data = (uint16_t)base->DATA;
				switch (s_UARTconfig[instance].bitCountPerChar)
				{
				case DRV_UART_dataBitCount_7:
					*rxBuff = data & (uint8_t)0x7F;
					++rxBuff;
					--rxSize;
					break;
				case DRV_UART_dataBitCount_8:
					*rxBuff = data & (uint8_t)0xFF;
					++rxBuff;
					--rxSize;
					break;
				case DRV_UART_dataBitCount_9:
					*rxBuff = data & (uint8_t)0xFF;
					*(rxBuff+1) = (data >> 8) & (uint8_t)0x01;
					++rxBuff;
					++rxBuff;
					rxSize -= 2U;
					break;
				case DRV_UART_dataBitCount_10:
					*rxBuff = data & (uint8_t)0xFF;
					*(rxBuff+1) = (data >> 8) & (uint8_t)0x03;
					++rxBuff;
					++rxBuff;
					rxSize -= 2U;
					break;
				default:
					break;
				}
			}
			/*Disable Receiver*/
			base->CTRL &= ~LPUART_CTRL_RE_MASK;
			while ((base->CTRL & LPUART_CTRL_RE_MASK) == LPUART_CTRL_RE_MASK)
			{
			}
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateReady;
			s_UARTtxBufferstr[instance].isTxBusy = false;
		}
		else
		{
			ret_val = DRV_UART_error;
		}
	}
	else
	{
		ret_val = DRV_UART_txBusy;
	}
	return ret_val;
}

/**
 * @brief This function is responsible for aborting the receiver
 *
 */
DRV_UART_StatusType DRV_UART_AbortReceiving(const DRV_UART_InstanceType instance)
{
	/*reset rx buffer*/
	s_UARTrxBufferstr[instance].prxBuff = NULL;
	s_UARTrxBufferstr[instance].rxBuffSize = 0;
	s_UARTrxBufferstr[instance].rxCount = 0;
	s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateReady;
	s_UARTrxBufferstr[instance].isRxBusy = false;
	/*Disable reciever*/
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_RIE_MASK;
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_RE_MASK;
	return DRV_UART_stateReady;
}

/**
 * @brief This function is responsible for aborting the transmitter
 *
 */
DRV_UART_StatusType DRV_UART_AbortTransmitting(const DRV_UART_InstanceType instance)
{
	/*reset rx buffer*/
	s_UARTtxBufferstr[instance].ptxBuff = NULL;
	s_UARTtxBufferstr[instance].txBuffSize = 0;
	s_UARTtxBufferstr[instance].txCount = 0;
	s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateReady;
	s_UARTtxBufferstr[instance].isTxBusy = false;
	/*Disable reciever*/
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_TIE_MASK;
	s_lpuartBase[instance]->CTRL &= ~LPUART_CTRL_TE_MASK;
	return DRV_UART_stateReady;
}


/**
 * @brief : This function is responsible for receiving data via interrupt method
 *
 */
DRV_UART_StatusType DRV_UART_ReceiveDataInterrupt(const DRV_UART_InstanceType instance, const uint8_t *rxBuff, const uint16_t rxSize)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_StatusType ret_val = DRV_UART_rxBusy;

	if (!(s_UARTrxBufferstr[instance].isRxBusy))
	{
		if ((rxBuff != NULL) && (rxSize != 0U))
		{
			s_UARTrxBufferstr[instance].prxBuff = (uint8_t *)rxBuff;
			s_UARTrxBufferstr[instance].rxBuffSize = rxSize;
			s_UARTrxBufferstr[instance].rxCount = 0;
			s_UARTrxBufferstr[instance].rxStatus = DRV_UART_rxBusy;
			s_UARTrxBufferstr[instance].isRxBusy = true;
			/*Disable errors status*/
			base->STAT |= DRV_UART_STAT_ERROR_REC_FLAG_MASK;
			/*Enable receiver*/
			base->CTRL = (base->CTRL & ~LPUART_CTRL_RE_MASK) | (1UL << LPUART_CTRL_RE_SHIFT);
			while ((base->CTRL & LPUART_CTRL_RE_MASK) != LPUART_CTRL_RE_MASK){};
			/* enable interrupt errors detect*/
			base->CTRL |= DRV_UART_CTRL_ERROR_REC_INTERRUPT_MASK;
			/* enable interrupt rx*/
			base->CTRL |= LPUART_CTRL_RIE_MASK;
		}
		else
		{
			ret_val = DRV_UART_error;
		}
	}
	else
	{
		ret_val = DRV_UART_rxBusy;
	}

	return ret_val;
}

void LPUART0_RxTx_IRQHandler()
{
	DRV_UART_HanldeInterrupt(DRV_UART_instance_0);
}

void LPUART1_RxTx_IRQHandler()
{
	DRV_UART_HanldeInterrupt(DRV_UART_instance_1);
}

void LPUART2_RxTx_IRQHandler()
{
	DRV_UART_HanldeInterrupt(DRV_UART_instance_2);
}

/**
 * @brief : This function is responsible for registering function callback depending on the callback function type
 *
 */
void DRV_UART_InstallCallBack(DRV_UART_CallBackFunctionType callBackType, DRV_CallBack_LPUART cbFunction)
{
	if(callBackType == DRV_UART_callBackError)
	{
		s_UARTfunctionPointer[DRV_UART_callBackError] = cbFunction;
	}
	if(callBackType == DRV_UART_callBackTransmitter)
	{
		s_UARTfunctionPointer[DRV_UART_callBackTransmitter] = cbFunction;
	}
	if(callBackType == DRV_UART_callBackReceiver)
	{
		s_UARTfunctionPointer[DRV_UART_callBackReceiver] = cbFunction;
	}
}

/**
 * @brief : This function is responsible for disabling the Tx and Rx
 *
 */
void DRV_UART_InstallCallBackE(DRV_CallBackErrorLPUART cbFunctionE)
{
	s_UARTx_ErrorCallBack = cbFunctionE;
}

/**
 * @brief This function is responsible for checking the interrupt flag of revceiver
 *
 */
static bool DRV_UART_CheckIFReceiver(DRV_UART_InstanceType instance)
{
	bool retval = false;

	if ((s_lpuartBase[instance]->STAT & LPUART_STAT_RDRF_MASK) != 0)
	{
		retval = true;
	}

	return retval;
}


/**
 * @brief : This function is responsible for checking the interrupt flag of transmitter
 *
 */
static bool DRV_UART_CheckIFTransmitter(DRV_UART_InstanceType instance)
{
	bool retval = false;

	if ((s_lpuartBase[instance]->STAT & LPUART_STAT_TDRE_MASK) != 0)
	{
		retval = true;
	}

	return retval;
}

/**
 * @brief : This function is responsible for checking the interrupt flag of error
 *
 */
static bool DRV_UART_CheckIFError(DRV_UART_InstanceType instance)
{
	bool retval = false;

	if ((s_lpuartBase[instance]->STAT & DRV_UART_STAT_ERROR_REC_FLAG_MASK) != 0)
	{
		retval = true;
	}

	return retval;
}

/**
 * @brief : This function is responsible for handling interrupt request.
 * This function decides to execute type of the interrupt function
 *
 */
static void DRV_UART_HanldeInterrupt(DRV_UART_InstanceType instance)
{
	if (DRV_UART_CheckIFReceiver(instance))
	{
		DRV_UART_HanldeInterruptRx(instance);
	}
	else if (DRV_UART_CheckIFTransmitter(instance))
	{
		DRV_UART_HanldeInterruptTx(instance);
	}
	else if (DRV_UART_CheckIFError(instance))
	{
		DRV_UART_HanldeInterruptError(instance);
	}
}

/**
 * @brief : This function is responsible for handling receive data via interrupt
 *
 */
static void DRV_UART_HanldeInterruptRx(DRV_UART_InstanceType instance)
{
	LPUART_Type *base = s_lpuartBase[instance];
	uint16_t data;
	data = (uint16_t)base->DATA;
	if (s_UARTrxBufferstr[instance].isRxBusy)
	{
		switch (s_UARTconfig[instance].bitCountPerChar)
		{
		case DRV_UART_dataBitCount_7:
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount] = data & (uint8_t)0x7F;
			s_UARTrxBufferstr[instance].rxCount++;
			break;
		case DRV_UART_dataBitCount_8:
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount] = data & (uint8_t)0xFF;
			s_UARTrxBufferstr[instance].rxCount++;
			break;
		case DRV_UART_dataBitCount_9:
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount] = data & (uint8_t)0xFF;
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount + 1] = (data >> 8) & (uint8_t)0x01;
			s_UARTrxBufferstr[instance].rxCount += 2;
			break;
		case DRV_UART_dataBitCount_10:
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount] = data & (uint8_t)0xFF;
			s_UARTrxBufferstr[instance].prxBuff[s_UARTrxBufferstr[instance].rxCount + 1] = (data >> 8) & (uint8_t)0x03;
			s_UARTrxBufferstr[instance].rxCount += 2;
			break;
		default:
			break;
		}
		/*Check the remaining data. if no data remains, disable the receiver*/
		if (s_UARTrxBufferstr[instance].rxCount == s_UARTrxBufferstr[instance].rxBuffSize)
		{

			/* disable interrupt rx*/
			base->CTRL &= ~LPUART_CTRL_RIE_MASK; /*interrupt recieve*/
			base->CTRL &= ~LPUART_CTRL_RE_MASK;
			s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateReady;
			s_UARTrxBufferstr[instance].isRxBusy = false;
			if (s_UARTfunctionPointer[DRV_UART_callBackReceiver])
			{
				s_UARTfunctionPointer[DRV_UART_callBackReceiver]();
			}
		}
	}
}

/**
 * @brief : This function is responsible for handling transmit data via interrupt
 *
 */
static void DRV_UART_HanldeInterruptTx(DRV_UART_InstanceType instance)
{
	LPUART_Type *base = s_lpuartBase[instance];
	uint8_t tempData1, tempData2;
	if (s_UARTtxBufferstr[instance].isTxBusy)
	{
		switch (s_UARTconfig[instance].bitCountPerChar)
		{
		case DRV_UART_dataBitCount_7:
			base->DATA = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount] & (uint8_t)0x7F;

			s_UARTtxBufferstr[instance].txCount++;
			break;
		case DRV_UART_dataBitCount_8:
			base->DATA = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount] & (uint8_t)0xFF;

			s_UARTtxBufferstr[instance].txCount++;
			break;
		case DRV_UART_dataBitCount_9:
			tempData1 = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount];
			tempData2 = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount + 1];
			base->DATA = ((tempData2 << 8) | tempData1) & (uint16_t)0x01FF;

			s_UARTtxBufferstr[instance].txCount += 2;
			break;
		case DRV_UART_dataBitCount_10:
			tempData1 = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount];
			tempData2 = s_UARTtxBufferstr[instance].ptxBuff[s_UARTtxBufferstr[instance].txCount + 1];
			base->DATA = ((tempData2 << 8) | tempData1) & (uint16_t)0x03FF;

			s_UARTtxBufferstr[instance].txCount += 2;
			break;
		default:
			break;
		}
		if (s_UARTtxBufferstr[instance].txCount == s_UARTtxBufferstr[instance].txBuffSize)
		{

			/*Disable interrupt transmit and transmitter*/
			base->CTRL &= ~LPUART_CTRL_TIE_MASK;
			base->CTRL &= ~LPUART_CTRL_TE_MASK;
			if (s_UARTfunctionPointer[DRV_UART_callBackTransmitter])
			{
				s_UARTfunctionPointer[DRV_UART_callBackTransmitter]();
			}
			s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateReady;
			s_UARTtxBufferstr[instance].isTxBusy = false;
		}
	}
}

/**
 * @brief This function is responsible for handling error via interrupt
 *
 */
static void DRV_UART_HanldeInterruptError(DRV_UART_InstanceType instance)
{
	LPUART_Type *base = s_lpuartBase[instance];
	uint32_t temp;
	temp = base->STAT & DRV_UART_STAT_ERROR_REC_FLAG_MASK;
	switch (temp)
	{
	case LPUART_STAT_OR_MASK:
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateRxOverrunError;
		break;
	case LPUART_STAT_NF_MASK:
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateNoiseError;
		break;
	case LPUART_STAT_FE_MASK:
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateFramingError;
		break;
	case LPUART_STAT_PF_MASK:
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateParityError;
		break;
	default:
		break;
	}
	/*Clear errors status*/
	base->STAT |= DRV_UART_STAT_ERROR_REC_FLAG_MASK;
	/*Disable errors detecting*/
	base->CTRL &= ~DRV_UART_CTRL_ERROR_REC_INTERRUPT_MASK;
	/* disable interrupt rx*/
	base->CTRL &= ~LPUART_CTRL_RIE_MASK;
	if (s_UARTfunctionPointer[DRV_UART_callBackError])
	{
		s_UARTx_ErrorCallBack(s_UARTrxBufferstr[instance].rxStatus);
	}
}


/**
 * @brief : This function is responsible for Deinitializing UART module
 *
 */
DRV_UART_StatusType DRV_UART_Deinit(const DRV_UART_InstanceType instance)
{
	LPUART_Type *base = s_lpuartBase[instance];
	DRV_UART_StatusType ret_val = DRV_UART_ok;
	if (instance < LPUART_INSTANCE_COUNT)
	{
		/* Clear the error and interrupt flags */
		base->STAT = 0xC01FC000U;
		/* Reset all features and interrupts detecting by default */
		base->CTRL = 0x00000000;
		/* Reset match addresses */
		base->MATCH = 0x00000000;
		/* Clear BAUD register */
		base->BAUD = 0x0F000004;
		/* Set function pointer points to NULL for each type of the interrupt */
		s_UARTfunctionPointer[DRV_UART_callBackError] = NULL;
		s_UARTfunctionPointer[DRV_UART_callBackReceiver] = NULL;
		s_UARTfunctionPointer[DRV_UART_callBackTransmitter] = NULL;

		/* Assign Default state for LPUART module */
		s_UARTtxBufferstr[instance].txStatus = DRV_UART_stateDefault;
		s_UARTtxBufferstr[instance].isTxBusy = false;
		s_UARTrxBufferstr[instance].rxStatus = DRV_UART_stateDefault;
		s_UARTrxBufferstr[instance].isRxBusy = false;
		/* Disable NVIC module*/
		NVIC->ICER[s_lpuartRxTxIrqId[instance] / 32] = 1 << (s_lpuartRxTxIrqId[instance] % 32);
		/* Disable transmitter and receiver */
		base->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
		while (((base->CTRL & LPUART_CTRL_RE_MASK) >> LPUART_CTRL_RE_SHIFT != 0) && ((base->CTRL & LPUART_CTRL_TE_MASK) >> LPUART_CTRL_TE_SHIFT != 0));
	}
	else
	{
		ret_val = DRV_UART_error;
	}
	return ret_val;
}
