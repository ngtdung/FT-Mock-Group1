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

LpitStatusType DRV_LPIT_Init(LpitInsType Lpit_ins, const LpitConfigType * UserConfig)
{
    LpitStatusType statusFunc = SUCCESS;
    uint8_t idx = 0;

    if ((UserConfig != DRV_LPIT_NULL_PTR) && (Lpit_ins == LPIT_INS_0))
    {
        LPIT_Type * lpitBase = LPIT_Base_Addr[Lpit_ins];

        /* Reset the timer channels and registers */
        Lpit_ResetTimer(lpitBase);

        /* Setup timer operation in debug and doze modes and enable clock for module */
        Lpit_SetupTimer(lpitBase, UserConfig->debug_en, UserConfig->doze_en);

        /************************/
        for (idx = 0; idx <= UserConfig->num_of_channel; idx++)
        {
            /* Setup the channel counters operation mode to "32-bit Periodic Counter"
             * and keep default values for the trigger source */
            Lpit_SetTimerOperationMode(lpitBase, (UserConfig->channel)[idx], UserConfig->timer_mode);

            /* Timer stop on timeout */
            Lpit_SetTimerStopOnInterrupt(lpitBase, (UserConfig->channel)[idx], UserConfig->timer_stop_on_interrup);
        }

        /* Enable channel interrupt */
        if (UserConfig->num_of_interrupt != 0U)
        {
            for (idx = 0; idx <= UserConfig->num_of_interrupt; idx++)
            {
                Lpit_EnableChannelInterrupt(lpitBase, (UserConfig->interrupt)[idx]);

                /* Enable interrupt on NVIC for LPIT channel */
                switch ((UserConfig->interrupt)[idx])
                {
                    case LPIT_IRQ_CHANNEL_0:
                        NVIC_EnableIRQn(LPIT0_Ch0_IRQn);
                        break;
                    case LPIT_IRQ_CHANNEL_1:
                        NVIC_EnableIRQn(LPIT0_Ch1_IRQn);
                        break;
                    case LPIT_IRQ_CHANNEL_2:
                        NVIC_EnableIRQn(LPIT0_Ch2_IRQn);
                        break;
                    case LPIT_IRQ_CHANNEL_3:
                        NVIC_EnableIRQn(LPIT0_Ch3_IRQn);
                        break;
                    default:
                        break;
                }
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

LpitStatusType DRV_LPIT_StartTimer(LpitInsType Lpit_ins, LpitChannelType channel, int64_t timer_value)
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

LpitStatusType DRV_LPIT_StopTimer(LpitInsType Lpit_ins, LpitChannelType channel)
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
    if (Lpit_CheckInterruptFlagChannel(LPIT_CHANNEL_0))
    {
        /* Clear Interrupt Flag */
        Lpit_ClearInterruptFlagChannel(LPIT_CHANNEL_0);
        /* Call App_Lpit_Callback */
        (*s_callback)(LPIT_CHANNEL_0);
    }
}

void LPIT0_Ch1_IRQHandler(void)
{
    if (Lpit_CheckInterruptFlagChannel(LPIT_CHANNEL_1))
    {
        /* Clear Interrupt Flag */
        Lpit_ClearInterruptFlagChannel(LPIT_CHANNEL_1);
        /* Call App_Lpit_Callback */
        (*s_callback)(LPIT_CHANNEL_1);
    }
    else {}
}

void LPIT0_Ch2_IRQHandler(void)
{
    if (Lpit_CheckInterruptFlagChannel(LPIT_CHANNEL_2))
    {
        /* Clear Interrupt Flag */
        Lpit_ClearInterruptFlagChannel(LPIT_CHANNEL_2);
        /* Call App_Lpit_Callback */
        (*s_callback)(LPIT_CHANNEL_2);
    }
    else {}
}

void LPIT0_Ch3_IRQHandler(void)
{
    if (Lpit_CheckInterruptFlagChannel(LPIT_CHANNEL_3))
    {
        /* Clear Interrupt Flag */
        Lpit_ClearInterruptFlagChannel(LPIT_CHANNEL_3);
        /* Call App_Lpit_Callback */
        (*s_callback)(LPIT_CHANNEL_3);
    }
    else {}
}

LpitStatusType DRV_LPIT_Deinit(LpitInsType Lpit_ins, LpitChannelType channel)
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
                NVIC_DisableIRQn(LPIT0_Ch0_IRQn);
                break;
            case LPIT_CHANNEL_1:
                NVIC_DisableIRQn(LPIT0_Ch1_IRQn);
                break;
            case LPIT_CHANNEL_2:
                NVIC_DisableIRQn(LPIT0_Ch2_IRQn);
                break;
            case LPIT_CHANNEL_3:
                NVIC_DisableIRQn(LPIT0_Ch3_IRQn);
                break;
            default:
                break;
        }

        /* Set call back function when interrupt occur */
        s_callback = DRV_LPIT_NULL_PTR;
    }

    return statusFunc;
}

/*******************************************************************************
* end of file
*******************************************************************************/
