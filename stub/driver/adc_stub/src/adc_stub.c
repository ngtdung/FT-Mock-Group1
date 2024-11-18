#include <stdint.h>
#include "adc_stub.h"

static ADC_Type ADC_BASE[2];
static PCC_Type PCC_BASE;
static PDB_Type PDB_BASE[2];

ADC_Type *ADC0 = &ADC_BASE[0];
ADC_Type *ADC1 = &ADC_BASE[1];

PCC_Type *PCC = &PCC_BASE;

PDB_Type *PDB0 = &PDB_BASE[0];
PDB_Type *PDB1 = &PDB_BASE[1];

