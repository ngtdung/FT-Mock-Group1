#include "MIDD_UART.h"

/************************* Macro *********************************/
#define UART_TX_PIN 71U
#define UART_RX_PIN 70U

/*********************** Static function prototypes ****************/
static void MIDD_uartInit(void);
static void MIDD_clockInit(void);

/*********************** Configuration Variables *******************/
DRV_UART_ConfigType UserConfig = {
  .baudRate = DRV_UART_baudRateValue_115200,
  .bitCountPerChar = DRV_UART_dataBitCount_8,
  .clockSource = DRV_UART_fircClkSouce,
  .parityMode = DRV_UART_parityModeDisabled,
  .stopBit = DRV_UART_stopBitCountOne,
  .transferType = DRV_UART_usingInterrupts
};

PORT_Config_type PORTConfig = {
  .muxMode = portMuxAlt2,
};

/*************************** Functions *****************************/

static void MIDD_clockInit(void) {
    // Enable clock for PORTC using the desired clock source and divider settings
    PCC_PeriClockControl(PCC_PORTC_INDEX, CLOCK_SIRCDIV2_CLK, CLOCK_DIV_1, ENABLE);

    // Enable clock for LPUART1 with appropriate source and divider settings
    PCC_PeriClockControl(PCC_LPUART1_INDEX, CLOCK_FIRCDIV2_CLK, CLOCK_DIV_1, ENABLE);

    // Disable clock for LPUART1 if not needed temporarily
   // PCC_PeriClockControl(PCC_LPUART1_INDEX, CLOCK_FIRCDIV2_CLK, CLOCK_DIV_1, DISABLE);

    // Set FIRCDIV2 divider value directly (if this setting is part of the specific clock configuration)
    //IP_SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1);

    // Configure the LPUART1 peripheral clock source to FIRC (3u represents FIRC as the source)
  //  PCC_PeriClockControl(PCC_LPUART1_INDEX, CLOCK_FIRCDIV2_CLK, CLOCK_DIV_1, ENABLE);
}


static void MIDD_uartInit(void) {
  /* Initialize Tx and Rx pin configurations */

  PORT_PinConfig_type s_txPinCf = {
    .pinCode = UART_TX_PIN,
    .userConfig = PORTConfig
  };

  PORT_PinConfig_type s_rxPinCf = {
    .pinCode = UART_RX_PIN,
    .userConfig = PORTConfig
  };

  /* Initialize Tx and Rx pins */
  PORT_Driver_InitPin(&s_txPinCf);
  PORT_Driver_InitPin(&s_rxPinCf);

  /* Initialize UART with the specified configuration */
  DRV_UART_Init(DRV_UART_instance_1, &UserConfig);
  NVIC_EnableIRQn(LPUART1_RxTx_IRQn);

  // Optional: Install callback if needed
  // DRV_UART_InstallCallBack(DRV_UART_callBackReceiver, MIDD_checkRequest);
}

void MIDD_AppRun(void) {
  const char *message = "Send Data Polling\n";
  DRV_UART_SendDataPolling(DRV_UART_instance_1, (const uint8_t *)message, strlen(message));
}

void MIDD_Init(void) {
  /* Initialize clock and UART */
  MIDD_clockInit();
  MIDD_uartInit();
}
