#include <stdint.h>
#include "adc_stub.h"

static ADC_Type IP_ADC_BASE[2];
static PCC_Type PCC_BASE;
static PDB_Type IP_PDB_BASE[2];

ADC_Type *IP_ADC0 = &IP_ADC_BASE[0];
ADC_Type *IP_ADC1 = &IP_ADC_BASE[1];

PCC_Type *PCC = &PCC_BASE;

PDB_Type *IP_PDB0 = &IP_PDB_BASE[0];
PDB_Type *IP_PDB1 = &IP_PDB_BASE[1];

