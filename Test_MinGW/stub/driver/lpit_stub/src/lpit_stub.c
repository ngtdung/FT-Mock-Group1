#include <stdint.h>
#include "lpit_stub.h"

static LPIT_Type s_lpit[LPIT_INSTANCE_COUNT];
LPIT_Type * IP_LPIT0 = &s_lpit[0];
