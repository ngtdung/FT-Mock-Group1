#ifndef INC_MIDD_UART_H_
#define INC_MIDD_UART_H_

#include "Driver_Header.h"
/* Function prototype */
void MID_UART_Init(void);
void MIDD_AppRun(void);
void MID_UART_InstallCallBack(DRV_UART_CallBackFunctionType callBackType, DRV_CallBack_LPUART cbFunction);
DRV_UART_StatusType MID_UART_ReceiveDataInterrupt(const DRV_UART_InstanceType instance, const uint8_t *rxBuff, const uint16_t rxSize);

#endif /* INC_MIDD_UART_H_ */
