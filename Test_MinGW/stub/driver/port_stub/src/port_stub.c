#include <stdint.h>
#include "port_stub.h"

static PORT_Type IP_PORT_BASE[5];

PORT_Type* IP_PORTA = &IP_PORT_BASE[0];
PORT_Type* IP_PORTB = &IP_PORT_BASE[1];
PORT_Type* IP_PORTC = &IP_PORT_BASE[2];
PORT_Type* IP_PORTD = &IP_PORT_BASE[3];
PORT_Type* IP_PORTE = &IP_PORT_BASE[4];

