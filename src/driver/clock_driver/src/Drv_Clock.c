/*******************************************************************************
* Include
*******************************************************************************/
#include "Drv_Clock.h"

/*******************************************************************************
* Code
*******************************************************************************/
void DRV_CLOCK_Enable(uint8_t Periperal)
{
    IP_PCC ->PCCn[Periperal] |= PCC_PCCn_CGC(1);
}

void DRV_CLOCK_ConfigBusClock(const SystemClockConfigType * UserConfig)
{
    IP_SCG->RCCR &= ~ SCG_RCCR_DIVCORE_MASK;
    IP_SCG->RCCR |= SCG_RCCR_DIVCORE(UserConfig -> divcore);
}

void DRV_CLOCK_ConfigAsynClock(uint8_t Periperal, const AsynClockConfigType * UserConfig)
{
    /* Init Clock - Async Clock */

    /* Disable bus clock for module */
    IP_PCC->PCCn[Periperal] &= ~PCC_PCCn_CGC_MASK;

    switch (UserConfig->clockSource)
    {
        case PCS_SOSCDIV2_CLK:
        {
            /* Disable SOSC before config SOCSDIV */
            IP_SCG->SOSCCSR &= ~SCG_SOSCCSR_SOSCEN_MASK;
            IP_SCG->SOSCDIV |= SCG_SOSCDIV_SOSCDIV2(UserConfig->clockDIV2);
            /* Enable SOSC */
            IP_SCG->SOSCCSR |= SCG_SOSCCSR_SOSCEN(1U);
            break;
        }

        case PCS_SIRCDIV2_CLK:
        {
            /* Disable Slow IRC before config SIRCDIV */
            IP_SCG->SIRCCSR &= ~SCG_SIRCCSR_SIRCEN_MASK;
            IP_SCG->SIRCDIV |= SCG_SIRCDIV_SIRCDIV2(UserConfig->clockDIV2);
            /* Enable Slow IRC */
            IP_SCG->SIRCCSR |= SCG_SIRCCSR_SIRCEN(1U);
            break;
        }

        case PCS_FIRCDIV2_CLK:
        {
            /* Disable Fast IRC before config FIRCDIV */
            IP_SCG->FIRCCSR &= ~SCG_FIRCCSR_FIRCEN_MASK;
            IP_SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(UserConfig->clockDIV2);
            /* Enable Fast IRC */
            IP_SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN(1U);
            break;
        }

        case PCS_SPLLDIV2_CLK:
        {
            /* Disable SPLL before config SPLLDIV */
            IP_SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK;
            IP_SCG->SPLLDIV |= SCG_SPLLDIV_SPLLDIV2(UserConfig->clockDIV2);
            /* Enable SPLL */
            IP_SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN(1U);
            break;
        }

        default:
        {
            break;
        }
    }

    /* Select clock source for function peripheral */
    IP_PCC->PCCn[Periperal] |= PCC_PCCn_PCS(UserConfig->clockSource);
    /* Enabble Bus Clock */
    IP_PCC->PCCn[Periperal] |= PCC_PCCn_CGC(1U);
}

void DRV_CLOCK_Disable(uint8_t Periperal)
{
    IP_PCC ->PCCn[Periperal] &= ~PCC_PCCn_CGC_MASK;
}

/*******************************************************************************
* end of file
*******************************************************************************/
