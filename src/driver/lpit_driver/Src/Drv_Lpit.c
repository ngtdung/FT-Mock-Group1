/*******************************************************************************
* Include
*******************************************************************************/
#include "Drv_Lpit.h"
#include "Lpit_hw_access.h"

/*******************************************************************************
* Variables
*******************************************************************************/

/* Declare array stores addresses of LPIT peripheral instances */
static LPIT_Type * LPIT_Base_Addr[LPIT_INSTANCE_COUNT] = IP_LPIT_BASE_PTRS;
/* Function pointer store address callback function */
static Lpit0_Callback_t s_callback;

/*******************************************************************************
* Code
*******************************************************************************/

LpitStatusType Drv_Lpit_Init(LpitInsType Lpit_ins, const LpitConfigType * UserConfig)
{
	LpitStatusType statusFunc = SUCCESS;

	if ((UserConfig != NULL) && (Lpit_ins == LPIT_INS_0))
	{
		LPIT_Type * lpitBase = LPIT_Base_Addr[Lpit_ins];

		/* Reset the timer channels and registers */
		Lpit_ResetTimer(lpitBase);

		/* Setup timer operation in debug and doze modes and enable clock for module */
		Lpit_SetupTimer(lpitBase, UserConfig->debug_en, UserConfig->doze_en);

		/* Setup the channel counters operation mode to "32-bit Periodic Counter"
		 * and keep default values for the trigger source */
		Lpit_SetTimerOperationMode(lpitBase, UserConfig->channel, UserConfig->timer_mode);

		/* Timer stop on timeout */
		Lpit_SetTimerStopOnInterrupt(lpitBase, UserConfig->channel, UserConfig->timer_stop_on_interrup);

		/* Enable channel interrupt */
		if ( LPIT_IRQ_DISABLE != UserConfig->interrupt)
		{
			Lpit_EnableChannelInterrupt(lpitBase, UserConfig->interrupt);

			/* Enable interrupt on NVIC for LPIT channel */
			switch (UserConfig->channel)
			{
				case LPIT_CHANNEL_0:
					Hal_Driver_NVIC_SetEnableIRQ(LPIT0_Ch0_IRQn);
					break;
				case LPIT_CHANNEL_1:
					Hal_Driver_NVIC_SetEnableIRQ(LPIT0_Ch1_IRQn);
					break;
				case LPIT_CHANNEL_2:
					Hal_Driver_NVIC_SetEnableIRQ(LPIT0_Ch2_IRQn);
					break;
				case LPIT_CHANNEL_3:
					Hal_Driver_NVIC_SetEnableIRQ(LPIT0_Ch3_IRQn);
					break;
				default:
					break;
			}

			/* Set call back function when interrupt occur */
			s_callback = UserConfig->callback;
		}
	}
	else
	{
		statusFunc = FAIL;
	}

	return statusFunc;
}

LpitStatusType Drv_Lpit_StartTimer(LpitInsType Lpit_ins, LpitChannelType channel, int64_t timer_value)
{
	LpitStatusType statusFunc = SUCCESS;

	if ((timer_value < 0) || ((uint64_t)timer_value > UINT32_MAX) || (Lpit_ins != LPIT_INS_0) ||
		(channel < LPIT_CHANNEL_0) || (channel > LPIT_CHANNEL_3))
	{
		statusFunc = FAIL;
	}
	else
	{
		LPIT_Type * lpitBase = LPIT_Base_Addr[Lpit_ins];
		/* Set timer value for channel */
		Lpit_SetTimerValue(lpitBase, channel, timer_value);

		/* Starts the timer counting afer all configuration */
		Lpit_EnableTimer(lpitBase, channel);
	}

    return statusFunc;
}

LpitStatusType Drv_Lpit_StopTimer(LpitInsType Lpit_ins, LpitChannelType channel)
{
	LpitStatusType statusFunc = SUCCESS;

	if ((Lpit_ins != LPIT_INS_0) || (channel < LPIT_CHANNEL_0) || (channel > LPIT_CHANNEL_3))
	{
		statusFunc = FAIL;
	}
	else
	{
		LPIT_Type * lpitBase = LPIT_Base_Addr[Lpit_ins];

		Lpit_DisableTimer(lpitBase, channel);
	}

    return statusFunc;
}

/* Interrupt service function for LPIT0 - channle 0 */
void LPIT0_Ch0_IRQHandler(void)
{
    uint8_t channel = 0;
    // for check flag channel
    for (channel = 0; channel <= LPIT_MAX_CHANNEL; channel ++)
    {
        if (Lpit_CheckInterruptFlagChannel(channel) == TRUE)
        {
            /* Clear Interrupt Flag */
            Lpit_ClearInterruptFlagChannel(channel);
            /* Call App_Lpit_Callback */
            (*s_callback)(channel);
        }
    }
}

LpitStatusType Drv_Lpit_Deinit(LpitInsType Lpit_ins, LpitChannelType channel)
{
	LpitStatusType statusFunc = SUCCESS;

	if ((Lpit_ins != LPIT_INS_0) || (channel < LPIT_CHANNEL_0) || (channel > LPIT_CHANNEL_3))
	{
		statusFunc = FAIL;
	}
	else
	{
		LPIT_Type * lpitBase = LPIT_Base_Addr[Lpit_ins];
		/* Reset the timer channels and registers */
		Lpit_ResetTimer(lpitBase);

		/* Setup timer operation in debug and doze modes and enable clock for module */
		Lpit_SetupTimer(lpitBase, LPIT_DEBUG_MODE_DISABLE, LPIT_DOZE_MODE_DISABLE);

		/* Timer stop on timeout */
		Lpit_SetTimerStopOnInterrupt(lpitBase, channel, LPIT_TSOI_DISABLE);

		/* Disable channel interrupt */
		Lpit_EnableChannelInterrupt(lpitBase, LPIT_IRQ_DISABLE);

		/* Disable interrupt on NVIC for LPIT channel */
		switch (channel)
		{
			case LPIT_CHANNEL_0:
				Hal_Driver_NVIC_ClearEnableIRQ(LPIT0_Ch0_IRQn);
				break;
			case LPIT_CHANNEL_1:
				Hal_Driver_NVIC_ClearEnableIRQ(LPIT0_Ch1_IRQn);
				break;
    		case LPIT_CHANNEL_2:
				Hal_Driver_NVIC_ClearEnableIRQ(LPIT0_Ch2_IRQn);
				break;
			case LPIT_CHANNEL_3:
				Hal_Driver_NVIC_ClearEnableIRQ(LPIT0_Ch3_IRQn);
				break;
			default:
				break;
		}

		/* Set call back function when interrupt occur */
		s_callback = NULL;
	}

    return statusFunc;
}

/*******************************************************************************
* end of file
*******************************************************************************/

