

#ifndef _DRV_LPUART_H_
#define _DRV_LPUART_H_
/*================================================================================================
===========================================TYPE DEFINITIONS=======================================
==================================================================================================*/

#include "Driver_Header.h"


typedef enum
{
    DRV_UART_dataBitCount_7  = 0xFFU,                       /*!< 7-bit data characters */
    DRV_UART_dataBitCount_8  = 0x00U,                       /*!< 8-bit data characters */
    DRV_UART_dataBitCount_9  = 0x01U,                       /*!< 9-bit data characters */
    DRV_UART_dataBitCount_10 = 0x02U                        /*!< 10-bit data characters */
} DRV_UART_DataBitCountType;

typedef enum
{
    DRV_UART_parityModeDisabled = 0x00U,                    /*!< parity disabled */
    DRV_UART_parityModeEven     = 0x02U,                    /*!< parity enabled, type even, bit setting: PE|PT = 10 */
    DRV_UART_parityModeOdd      = 0x03U                     /*!< parity enabled, type odd,  bit setting: PE|PT = 11 */
} DRV_UART_ParityModeType;

typedef enum
{
    DRV_UART_stopBitCountOne = 0x00U,                       /*!< one stop bit */
    DRV_UART_stopBitCountTwo = 0x01U                        /*!< two stop bits */
} DRV_UART_StopBitCountType;

typedef enum
{
    DRV_UART_notUsingInterrupts = 0x00U,                    /*!< Not use interrupt to perform UART transfer */
    DRV_UART_usingInterrupts    = 0x01U                     /*!< Using interrupts to perform UART transfer */
} DRV_UART_TransferType;

 typedef enum
 {
     DRV_UART_callBackError         = 0x0u,                  /* callback function to handle error*/
     DRV_UART_callBackTransmitter   = 0x1u,                  /* callback function to handle transmiting data */
     DRV_UART_callBackReceiver      = 0x2u,                  /* callback function to handle receiving data */
 }DRV_UART_CallBackFunctionType;


typedef enum
{
    DRV_UART_baudRateValue_600      = 600U,
    DRV_UART_baudRateValue_9600     = 9600U,
    DRV_UART_baudRateValue_12800    = 12800U,
    DRV_UART_baudRateValue_38400    = 38400U,
    DRV_UART_baudRateValue_128000   = 128000U,
    DRV_UART_baudRateValue_230400   = 230400U,
    DRV_UART_baudRateValue_256000   = 256000U,
    DRV_UART_baudRateValue_115200   = 115200U,
} DRV_UART_BaudrateValueType;

typedef enum
{
    DRV_UART_instance_0 = 0x00U,                            /*UART instance 0*/
    DRV_UART_instance_1 = 0x01U,                            /*UART instance 1*/
    DRV_UART_instance_2 = 0x02U,                            /*UART instance 2*/
    DRV_UART_instanceCount = 0x03U,                         /*UART instance count*/
}DRV_UART_InstanceType;

typedef enum
{
    DRV_UART_txBusy                     = 0xFFU,        /*!< Data Transmission process is ongoing> */
    DRV_UART_rxBusy                     = 0xFEU,        /*!< Data Reception process is ongoing> */
	DRV_UART_stateReady                 = 0x22U,		/*!< The UART module is free to use> */
	DRV_UART_stateDefault               = 0x55U,		/*!< The UART is in default state. Module is not initialized> */
	DRV_UART_stateInitialized           = 0xEEU,		/*!< The UART module is initialized> */
    DRV_UART_stateRxOverrunError        = 0x01U, 		/*!< Receiver encountered an overrun error> */
    DRV_UART_stateFramingError          = 0x02U,    	/*!< Receiver encountered a framing error> */
    DRV_UART_stateParityError           = 0x03U,     	/*!< Receiver encountered a parity error> */
    DRV_UART_stateNoiseError            = 0x04U,      	/*!< Receiver encountered a noise error> */
    DRV_UART_ok                         = 0x00U,		/*!< UART module operates OK> */
    DRV_UART_error                      = 0x05U,		/*!< UART module ERROR> */
    DRV_UART_busy                       = 0x06U,		/*!< UART busy> */
}DRV_UART_StatusType;

typedef enum
{
    DRV_UART_soscClkSouce               = 0x00U,        /*!< SOSCCLK source = 8000000U Hz>*/
    DRV_UART_fircClkSouce               = 0x01U,        /*!< FIRCCLK source = 48000000U Hz>*/
}DRV_UART_ClkSourceType;

/* UART configuration structure */
typedef struct
{
	DRV_UART_DataBitCountType bitCountPerChar;          /*Number of bits in a character*/
	DRV_UART_ParityModeType parityMode;                 /*Parity mode, disabled (default), even, odd*/
	DRV_UART_StopBitCountType stopBit;                  /*Number of stop bits, 1 stop bit (default) or 2 stop bits*/
	DRV_UART_BaudrateValueType baudRate;                /*UART module baudrate*/
    DRV_UART_TransferType transferType;                 /*UART module transfer type*/
    DRV_UART_ClkSourceType clockSource;                 /*UART module clock source*/
}DRV_UART_ConfigType;

/* UART receive buffer structure */
typedef struct
{
    uint8_t *prxBuff;       	                        /* pointer points to the receive buffer*/
    uint16_t rxBuffSize; 	                            /* size of the receive buffer*/
    uint16_t rxCount;                                   /* the receive buffer counter*/
    DRV_UART_StatusType rxStatus;                       /* the status of receiver*/
    bool isRxBusy;                                      /* Check the status of receiver*/

} DRV_UART_RxBuffType;

/* UART transmit buffer structure */
typedef struct
{
    uint8_t *ptxBuff;                                   /* pointer points to the transmit buffer*/
    uint16_t txBuffSize; 	                            /* size of the receive buffer*/
    uint16_t txCount;                                   /* the transmit buffer counter*/
    DRV_UART_StatusType txStatus;                       /* the status of transmitter*/
    bool isTxBusy;                                      /* Check the status of transmitter*/
} DRV_UART_TxBuffType;

/* Function pointer to register the function callback for dectecting errors */
typedef void (*DRV_CallBackErrorLPUART)(DRV_UART_StatusType error_type);
/* Function pointer to register the function callback */
typedef void (*DRV_CallBack_LPUART)(void);

/*================================================================================================
========================================FUNCTIONS PROTOTYPE=======================================
==================================================================================================*/

/**
 * @brief This function is responsible for initializing UART module
 *
 * @param uartConfig : UART configuration elements: data bits per char, parity mode, stop bit, baud rate, transfer type
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_Init(const DRV_UART_InstanceType instance, const DRV_UART_ConfigType *uartConfig);

/**
 * @brief This function is responsible for Deinitializing UART module
 *
 * @param instance : instance decides the LPUART base pointer
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_Deinit(const DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for setting  The UART's baud rate
 *
 * @param instance : instance decides the LPUART base pointer
 * @param baudRate : baud rate for UART module
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_SetBaudRate(const DRV_UART_InstanceType instance, const DRV_UART_BaudrateValueType baudRate);

/**
 * @brief This function is responsible for transmitting data via interrupt method
 *
 * @param instance : instance decides the LPUART base pointer
 * @param txBuffer : transmit buffer
 * @param length   : transmit buffer size
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_SendDataInterrupt(const DRV_UART_InstanceType instance, uint8_t *data, uint16_t length);


/**
 * @brief This function is responsible for receiving data via interrupt method
 *
 * @param instance : instance decides the LPUART base pointer
 * @param data     : receive buffer
 * @param length   : receive buffer size
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_ReceiveDataInterrupt(const DRV_UART_InstanceType instance, const uint8_t* data, uint16_t length);

/**
 * @brief This function is responsible for aborting the receiver
 *
 * @param instance : instance decides the LPUART base pointer
 */
DRV_UART_StatusType DRV_UART_AbortReceiving(const DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for aborting the transmitter
 *
 * @param instance : instance decides the LPUART base pointer
 * @return DRV_UART_StatusType
 */
DRV_UART_StatusType DRV_UART_AbortTransmitting(const DRV_UART_InstanceType instance);

/**
 * @brief : This function is responsible for registering function callback depending on the callback function type
 *
 * @param callBackType : Choose type of the callback function
 * @param cbFunction : The pointer points to a function that be called when an interrupt happens
 */
void DRV_UART_InstallCallBack(DRV_UART_CallBackFunctionType callBackType, DRV_CallBack_LPUART cbFunction);

/**
 * @brief This function is responsible for registering error detecting function
 *
 * @param cbFunctionE : The pointer points to a function that be called when an errors via UART interrupt happens
 */
void DRV_UART_InstallCallBackE(DRV_CallBackErrorLPUART cbFunctionE);

/**
 * @brief This function is responsible for disabling the Tx
 *
 * @param instance : instance decides the LPUART base pointer
 */
void DRV_UART_DisableTx(const DRV_UART_InstanceType instance);

/**
 * @brief This function is responsible for disabling the Rx
 *
 * @param instance : instance decides the LPUART base pointer
 */
void DRV_UART_DisableRx(const DRV_UART_InstanceType instance);

/**
 * @brief : This function is responsible for enabling the Tx
 *
 */
void DRV_UART_EnableTx(const DRV_UART_InstanceType instance);

/**
 * @brief : This function is responsible for enabling the Rx
 *
 */
void DRV_UART_EnableRx(const DRV_UART_InstanceType instance);

#endif /* _DRV_LPUART_H_ */
