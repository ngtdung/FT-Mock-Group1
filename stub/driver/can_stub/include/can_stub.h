#ifndef _IO
#ifndef CAN_STUB_H
#define CAN_STUB_H

#define     __I
#define     __O
#define     __IO
#endif
/* ----------------------------------------------------------------------------
   -- CAN Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 * @{
 */


/** CAN - Size of Registers Arrays */
#define CAN_RAMn_COUNT                           128u
#define CAN_RXIMR_COUNT                          32u
#define CAN_WMB_COUNT                            4u

/** CAN - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration Register, offset: 0x0 */
  __IO uint32_t CTRL1;                             /**< Control 1 register, offset: 0x4 */
  __IO uint32_t TIMER;                             /**< Free Running Timer, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t RXMGMASK;                          /**< Rx Mailboxes Global Mask Register, offset: 0x10 */
  __IO uint32_t RX14MASK;                          /**< Rx 14 Mask register, offset: 0x14 */
  __IO uint32_t RX15MASK;                          /**< Rx 15 Mask register, offset: 0x18 */
  __IO uint32_t ECR;                               /**< Error Counter, offset: 0x1C */
  __IO uint32_t ESR1;                              /**< Error and Status 1 register, offset: 0x20 */
       uint8_t RESERVED_1[4];
  __IO uint32_t IMASK1;                            /**< Interrupt Masks 1 register, offset: 0x28 */
       uint8_t RESERVED_2[4];
  __IO uint32_t IFLAG1;                            /**< Interrupt Flags 1 register, offset: 0x30 */
  __IO uint32_t CTRL2;                             /**< Control 2 register, offset: 0x34 */
  __I  uint32_t ESR2;                              /**< Error and Status 2 register, offset: 0x38 */
       uint8_t RESERVED_3[8];
  __I  uint32_t CRCR;                              /**< CRC Register, offset: 0x44 */
  __IO uint32_t RXFGMASK;                          /**< Rx FIFO Global Mask register, offset: 0x48 */
  __I  uint32_t RXFIR;                             /**< Rx FIFO Information Register, offset: 0x4C */
  __IO uint32_t CBT;                               /**< CAN Bit Timing Register, offset: 0x50 */
       uint8_t RESERVED_4[44];
  __IO uint32_t RAMn[CAN_RAMn_COUNT];              /**< Embedded RAM, array offset: 0x80, array step: 0x4 */
       uint8_t RESERVED_5[1536];
  __IO uint32_t RXIMR[CAN_RXIMR_COUNT];            /**< Rx Individual Mask Registers, array offset: 0x880, array step: 0x4 */
       uint8_t RESERVED_6[512];
  __IO uint32_t CTRL1_PN;                          /**< Pretended Networking Control 1 Register, offset: 0xB00 */
  __IO uint32_t CTRL2_PN;                          /**< Pretended Networking Control 2 Register, offset: 0xB04 */
  __IO uint32_t WU_MTC;                            /**< Pretended Networking Wake Up Match Register, offset: 0xB08 */
  __IO uint32_t FLT_ID1;                           /**< Pretended Networking ID Filter 1 Register, offset: 0xB0C */
  __IO uint32_t FLT_DLC;                           /**< Pretended Networking DLC Filter Register, offset: 0xB10 */
  __IO uint32_t PL1_LO;                            /**< Pretended Networking Payload Low Filter 1 Register, offset: 0xB14 */
  __IO uint32_t PL1_HI;                            /**< Pretended Networking Payload High Filter 1 Register, offset: 0xB18 */
  __IO uint32_t FLT_ID2_IDMASK;                    /**< Pretended Networking ID Filter 2 Register / ID Mask Register, offset: 0xB1C */
  __IO uint32_t PL2_PLMASK_LO;                     /**< Pretended Networking Payload Low Filter 2 Register / Payload Low Mask Register, offset: 0xB20 */
  __IO uint32_t PL2_PLMASK_HI;                     /**< Pretended Networking Payload High Filter 2 low order bits / Payload High Mask Register, offset: 0xB24 */
       uint8_t RESERVED_7[24];
  struct {                                         /* offset: 0xB40, array step: 0x10 */
    __I  uint32_t WMBn_CS;                           /**< Wake Up Message Buffer Register for C/S, array offset: 0xB40, array step: 0x10 */
    __I  uint32_t WMBn_ID;                           /**< Wake Up Message Buffer Register for ID, array offset: 0xB44, array step: 0x10 */
    __I  uint32_t WMBn_D03;                          /**< Wake Up Message Buffer Register for Data 0-3, array offset: 0xB48, array step: 0x10 */
    __I  uint32_t WMBn_D47;                          /**< Wake Up Message Buffer Register Data 4-7, array offset: 0xB4C, array step: 0x10 */
  } WMB[CAN_WMB_COUNT];
       uint8_t RESERVED_8[128];
  __IO uint32_t FDCTRL;                            /**< CAN FD Control Register, offset: 0xC00 */
  __IO uint32_t FDCBT;                             /**< CAN FD Bit Timing Register, offset: 0xC04 */
  __I  uint32_t FDCRC;                             /**< CAN FD CRC Register, offset: 0xC08 */
} CAN_Type, *CAN_MemMapPtr;

 /** Number of instances of the CAN module. */
#define CAN_INSTANCE_COUNT                       (3u)


/* CAN - Peripheral instance base addresses */
/** Peripheral CAN0 base pointer */
extern CAN_Type *CAN0;
/** Peripheral CAN1 base pointer */
extern CAN_Type *CAN1;
/** Peripheral CAN2 base pointer */
extern CAN_Type *CAN2;
/** Array initializer of CAN peripheral base pointers */
#define CAN_BASE_PTRS                            { CAN0, CAN1, CAN2 }
 /** Number of interrupt vector arrays for the CAN module. */
#define CAN_IRQS_ARR_COUNT                       (7u)
 /** Number of interrupt channels for the Rx_Warning type of CAN module. */
#define CAN_Rx_Warning_IRQS_CH_COUNT             (1u)
 /** Number of interrupt channels for the Tx_Warning type of CAN module. */
#define CAN_Tx_Warning_IRQS_CH_COUNT             (1u)
 /** Number of interrupt channels for the Wake_Up type of CAN module. */
#define CAN_Wake_Up_IRQS_CH_COUNT                (1u)
 /** Number of interrupt channels for the Error type of CAN module. */
#define CAN_Error_IRQS_CH_COUNT                  (1u)
 /** Number of interrupt channels for the Bus_Off type of CAN module. */
#define CAN_Bus_Off_IRQS_CH_COUNT                (1u)
 /** Number of interrupt channels for the ORed_0_15_MB type of CAN module. */
#define CAN_ORed_0_15_MB_IRQS_CH_COUNT           (1u)
 /** Number of interrupt channels for the ORed_16_31_MB type of CAN module. */
#define CAN_ORed_16_31_MB_IRQS_CH_COUNT          (1u)
/** Interrupt vectors for the CAN peripheral type */
#define CAN_Rx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_Tx_Warning_IRQS                      { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_Wake_Up_IRQS                         { CAN0_Wake_Up_IRQn, NotAvail_IRQn, NotAvail_IRQn }
#define CAN_Error_IRQS                           { CAN0_Error_IRQn, CAN1_Error_IRQn, CAN2_Error_IRQn }
#define CAN_Bus_Off_IRQS                         { CAN0_ORed_IRQn, CAN1_ORed_IRQn, CAN2_ORed_IRQn }
#define CAN_ORed_0_15_MB_IRQS                    { CAN0_ORed_0_15_MB_IRQn, CAN1_ORed_0_15_MB_IRQn, CAN2_ORed_0_15_MB_IRQn }
#define CAN_ORed_16_31_MB_IRQS                   { CAN0_ORed_16_31_MB_IRQn, NotAvail_IRQn, NotAvail_IRQn }

/* ----------------------------------------------------------------------------
   -- CAN Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAN_Register_Masks CAN Register Masks
 * @{
 */

/* MCR Bit Fields */
#define CAN_MCR_MAXMB_MASK                       0x7Fu
#define CAN_MCR_MAXMB_SHIFT                      0u
#define CAN_MCR_MAXMB_WIDTH                      7u
#define CAN_MCR_MAXMB(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_MCR_MAXMB_SHIFT))&CAN_MCR_MAXMB_MASK)
#define CAN_MCR_IDAM_MASK                        0x300u
#define CAN_MCR_IDAM_SHIFT                       8u
#define CAN_MCR_IDAM_WIDTH                       2u
#define CAN_MCR_IDAM(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_IDAM_SHIFT))&CAN_MCR_IDAM_MASK)
#define CAN_MCR_FDEN_MASK                        0x800u
#define CAN_MCR_FDEN_SHIFT                       11u
#define CAN_MCR_FDEN_WIDTH                       1u
#define CAN_MCR_FDEN(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_FDEN_SHIFT))&CAN_MCR_FDEN_MASK)
#define CAN_MCR_AEN_MASK                         0x1000u
#define CAN_MCR_AEN_SHIFT                        12u
#define CAN_MCR_AEN_WIDTH                        1u
#define CAN_MCR_AEN(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_MCR_AEN_SHIFT))&CAN_MCR_AEN_MASK)
#define CAN_MCR_LPRIOEN_MASK                     0x2000u
#define CAN_MCR_LPRIOEN_SHIFT                    13u
#define CAN_MCR_LPRIOEN_WIDTH                    1u
#define CAN_MCR_LPRIOEN(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_MCR_LPRIOEN_SHIFT))&CAN_MCR_LPRIOEN_MASK)
#define CAN_MCR_PNET_EN_MASK                     0x4000u
#define CAN_MCR_PNET_EN_SHIFT                    14u
#define CAN_MCR_PNET_EN_WIDTH                    1u
#define CAN_MCR_PNET_EN(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_MCR_PNET_EN_SHIFT))&CAN_MCR_PNET_EN_MASK)
#define CAN_MCR_DMA_MASK                         0x8000u
#define CAN_MCR_DMA_SHIFT                        15u
#define CAN_MCR_DMA_WIDTH                        1u
#define CAN_MCR_DMA(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_MCR_DMA_SHIFT))&CAN_MCR_DMA_MASK)
#define CAN_MCR_IRMQ_MASK                        0x10000u
#define CAN_MCR_IRMQ_SHIFT                       16u
#define CAN_MCR_IRMQ_WIDTH                       1u
#define CAN_MCR_IRMQ(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_IRMQ_SHIFT))&CAN_MCR_IRMQ_MASK)
#define CAN_MCR_SRXDIS_MASK                      0x20000u
#define CAN_MCR_SRXDIS_SHIFT                     17u
#define CAN_MCR_SRXDIS_WIDTH                     1u
#define CAN_MCR_SRXDIS(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_MCR_SRXDIS_SHIFT))&CAN_MCR_SRXDIS_MASK)
#define CAN_MCR_LPMACK_MASK                      0x100000u
#define CAN_MCR_LPMACK_SHIFT                     20u
#define CAN_MCR_LPMACK_WIDTH                     1u
#define CAN_MCR_LPMACK(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_MCR_LPMACK_SHIFT))&CAN_MCR_LPMACK_MASK)
#define CAN_MCR_WRNEN_MASK                       0x200000u
#define CAN_MCR_WRNEN_SHIFT                      21u
#define CAN_MCR_WRNEN_WIDTH                      1u
#define CAN_MCR_WRNEN(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_MCR_WRNEN_SHIFT))&CAN_MCR_WRNEN_MASK)
#define CAN_MCR_SUPV_MASK                        0x800000u
#define CAN_MCR_SUPV_SHIFT                       23u
#define CAN_MCR_SUPV_WIDTH                       1u
#define CAN_MCR_SUPV(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_SUPV_SHIFT))&CAN_MCR_SUPV_MASK)
#define CAN_MCR_FRZACK_MASK                      0x1000000u
#define CAN_MCR_FRZACK_SHIFT                     24u
#define CAN_MCR_FRZACK_WIDTH                     1u
#define CAN_MCR_FRZACK(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_MCR_FRZACK_SHIFT))&CAN_MCR_FRZACK_MASK)
#define CAN_MCR_SOFTRST_MASK                     0x2000000u
#define CAN_MCR_SOFTRST_SHIFT                    25u
#define CAN_MCR_SOFTRST_WIDTH                    1u
#define CAN_MCR_SOFTRST(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_MCR_SOFTRST_SHIFT))&CAN_MCR_SOFTRST_MASK)
#define CAN_MCR_NOTRDY_MASK                      0x8000000u
#define CAN_MCR_NOTRDY_SHIFT                     27u
#define CAN_MCR_NOTRDY_WIDTH                     1u
#define CAN_MCR_NOTRDY(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_MCR_NOTRDY_SHIFT))&CAN_MCR_NOTRDY_MASK)
#define CAN_MCR_HALT_MASK                        0x10000000u
#define CAN_MCR_HALT_SHIFT                       28u
#define CAN_MCR_HALT_WIDTH                       1u
#define CAN_MCR_HALT(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_HALT_SHIFT))&CAN_MCR_HALT_MASK)
#define CAN_MCR_RFEN_MASK                        0x20000000u
#define CAN_MCR_RFEN_SHIFT                       29u
#define CAN_MCR_RFEN_WIDTH                       1u
#define CAN_MCR_RFEN(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_RFEN_SHIFT))&CAN_MCR_RFEN_MASK)
#define CAN_MCR_FRZ_MASK                         0x40000000u
#define CAN_MCR_FRZ_SHIFT                        30u
#define CAN_MCR_FRZ_WIDTH                        1u
#define CAN_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_MCR_FRZ_SHIFT))&CAN_MCR_FRZ_MASK)
#define CAN_MCR_MDIS_MASK                        0x80000000u
#define CAN_MCR_MDIS_SHIFT                       31u
#define CAN_MCR_MDIS_WIDTH                       1u
#define CAN_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_MCR_MDIS_SHIFT))&CAN_MCR_MDIS_MASK)
/* CTRL1 Bit Fields */
#define CAN_CTRL1_PROPSEG_MASK                   0x7u
#define CAN_CTRL1_PROPSEG_SHIFT                  0u
#define CAN_CTRL1_PROPSEG_WIDTH                  3u
#define CAN_CTRL1_PROPSEG(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PROPSEG_SHIFT))&CAN_CTRL1_PROPSEG_MASK)
#define CAN_CTRL1_LOM_MASK                       0x8u
#define CAN_CTRL1_LOM_SHIFT                      3u
#define CAN_CTRL1_LOM_WIDTH                      1u
#define CAN_CTRL1_LOM(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_LOM_SHIFT))&CAN_CTRL1_LOM_MASK)
#define CAN_CTRL1_LBUF_MASK                      0x10u
#define CAN_CTRL1_LBUF_SHIFT                     4u
#define CAN_CTRL1_LBUF_WIDTH                     1u
#define CAN_CTRL1_LBUF(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_LBUF_SHIFT))&CAN_CTRL1_LBUF_MASK)
#define CAN_CTRL1_TSYN_MASK                      0x20u
#define CAN_CTRL1_TSYN_SHIFT                     5u
#define CAN_CTRL1_TSYN_WIDTH                     1u
#define CAN_CTRL1_TSYN(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_TSYN_SHIFT))&CAN_CTRL1_TSYN_MASK)
#define CAN_CTRL1_BOFFREC_MASK                   0x40u
#define CAN_CTRL1_BOFFREC_SHIFT                  6u
#define CAN_CTRL1_BOFFREC_WIDTH                  1u
#define CAN_CTRL1_BOFFREC(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_BOFFREC_SHIFT))&CAN_CTRL1_BOFFREC_MASK)
#define CAN_CTRL1_SMP_MASK                       0x80u
#define CAN_CTRL1_SMP_SHIFT                      7u
#define CAN_CTRL1_SMP_WIDTH                      1u
#define CAN_CTRL1_SMP(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_SMP_SHIFT))&CAN_CTRL1_SMP_MASK)
#define CAN_CTRL1_RWRNMSK_MASK                   0x400u
#define CAN_CTRL1_RWRNMSK_SHIFT                  10u
#define CAN_CTRL1_RWRNMSK_WIDTH                  1u
#define CAN_CTRL1_RWRNMSK(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_RWRNMSK_SHIFT))&CAN_CTRL1_RWRNMSK_MASK)
#define CAN_CTRL1_TWRNMSK_MASK                   0x800u
#define CAN_CTRL1_TWRNMSK_SHIFT                  11u
#define CAN_CTRL1_TWRNMSK_WIDTH                  1u
#define CAN_CTRL1_TWRNMSK(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_TWRNMSK_SHIFT))&CAN_CTRL1_TWRNMSK_MASK)
#define CAN_CTRL1_LPB_MASK                       0x1000u
#define CAN_CTRL1_LPB_SHIFT                      12u
#define CAN_CTRL1_LPB_WIDTH                      1u
#define CAN_CTRL1_LPB(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_LPB_SHIFT))&CAN_CTRL1_LPB_MASK)
#define CAN_CTRL1_CLKSRC_MASK                    0x2000u
#define CAN_CTRL1_CLKSRC_SHIFT                   13u
#define CAN_CTRL1_CLKSRC_WIDTH                   1u
#define CAN_CTRL1_CLKSRC(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_CLKSRC_SHIFT))&CAN_CTRL1_CLKSRC_MASK)
#define CAN_CTRL1_ERRMSK_MASK                    0x4000u
#define CAN_CTRL1_ERRMSK_SHIFT                   14u
#define CAN_CTRL1_ERRMSK_WIDTH                   1u
#define CAN_CTRL1_ERRMSK(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_ERRMSK_SHIFT))&CAN_CTRL1_ERRMSK_MASK)
#define CAN_CTRL1_BOFFMSK_MASK                   0x8000u
#define CAN_CTRL1_BOFFMSK_SHIFT                  15u
#define CAN_CTRL1_BOFFMSK_WIDTH                  1u
#define CAN_CTRL1_BOFFMSK(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_BOFFMSK_SHIFT))&CAN_CTRL1_BOFFMSK_MASK)
#define CAN_CTRL1_PSEG2_MASK                     0x70000u
#define CAN_CTRL1_PSEG2_SHIFT                    16u
#define CAN_CTRL1_PSEG2_WIDTH                    3u
#define CAN_CTRL1_PSEG2(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PSEG2_SHIFT))&CAN_CTRL1_PSEG2_MASK)
#define CAN_CTRL1_PSEG1_MASK                     0x380000u
#define CAN_CTRL1_PSEG1_SHIFT                    19u
#define CAN_CTRL1_PSEG1_WIDTH                    3u
#define CAN_CTRL1_PSEG1(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PSEG1_SHIFT))&CAN_CTRL1_PSEG1_MASK)
#define CAN_CTRL1_RJW_MASK                       0xC00000u
#define CAN_CTRL1_RJW_SHIFT                      22u
#define CAN_CTRL1_RJW_WIDTH                      2u
#define CAN_CTRL1_RJW(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_RJW_SHIFT))&CAN_CTRL1_RJW_MASK)
#define CAN_CTRL1_PRESDIV_MASK                   0xFF000000u
#define CAN_CTRL1_PRESDIV_SHIFT                  24u
#define CAN_CTRL1_PRESDIV_WIDTH                  8u
#define CAN_CTRL1_PRESDIV(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PRESDIV_SHIFT))&CAN_CTRL1_PRESDIV_MASK)
/* TIMER Bit Fields */
#define CAN_TIMER_TIMER_MASK                     0xFFFFu
#define CAN_TIMER_TIMER_SHIFT                    0u
#define CAN_TIMER_TIMER_WIDTH                    16u
#define CAN_TIMER_TIMER(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_TIMER_TIMER_SHIFT))&CAN_TIMER_TIMER_MASK)
/* RXMGMASK Bit Fields */
#define CAN_RXMGMASK_MG_MASK                     0xFFFFFFFFu
#define CAN_RXMGMASK_MG_SHIFT                    0u
#define CAN_RXMGMASK_MG_WIDTH                    32u
#define CAN_RXMGMASK_MG(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_RXMGMASK_MG_SHIFT))&CAN_RXMGMASK_MG_MASK)
/* RX14MASK Bit Fields */
#define CAN_RX14MASK_RX14M_MASK                  0xFFFFFFFFu
#define CAN_RX14MASK_RX14M_SHIFT                 0u
#define CAN_RX14MASK_RX14M_WIDTH                 32u
#define CAN_RX14MASK_RX14M(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_RX14MASK_RX14M_SHIFT))&CAN_RX14MASK_RX14M_MASK)
/* RX15MASK Bit Fields */
#define CAN_RX15MASK_RX15M_MASK                  0xFFFFFFFFu
#define CAN_RX15MASK_RX15M_SHIFT                 0u
#define CAN_RX15MASK_RX15M_WIDTH                 32u
#define CAN_RX15MASK_RX15M(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_RX15MASK_RX15M_SHIFT))&CAN_RX15MASK_RX15M_MASK)
/* ECR Bit Fields */
#define CAN_ECR_TXERRCNT_MASK                    0xFFu
#define CAN_ECR_TXERRCNT_SHIFT                   0u
#define CAN_ECR_TXERRCNT_WIDTH                   8u
#define CAN_ECR_TXERRCNT(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ECR_TXERRCNT_SHIFT))&CAN_ECR_TXERRCNT_MASK)
#define CAN_ECR_RXERRCNT_MASK                    0xFF00u
#define CAN_ECR_RXERRCNT_SHIFT                   8u
#define CAN_ECR_RXERRCNT_WIDTH                   8u
#define CAN_ECR_RXERRCNT(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ECR_RXERRCNT_SHIFT))&CAN_ECR_RXERRCNT_MASK)
#define CAN_ECR_TXERRCNT_FAST_MASK               0xFF0000u
#define CAN_ECR_TXERRCNT_FAST_SHIFT              16u
#define CAN_ECR_TXERRCNT_FAST_WIDTH              8u
#define CAN_ECR_TXERRCNT_FAST(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_ECR_TXERRCNT_FAST_SHIFT))&CAN_ECR_TXERRCNT_FAST_MASK)
#define CAN_ECR_RXERRCNT_FAST_MASK               0xFF000000u
#define CAN_ECR_RXERRCNT_FAST_SHIFT              24u
#define CAN_ECR_RXERRCNT_FAST_WIDTH              8u
#define CAN_ECR_RXERRCNT_FAST(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_ECR_RXERRCNT_FAST_SHIFT))&CAN_ECR_RXERRCNT_FAST_MASK)
/* ESR1 Bit Fields */
#define CAN_ESR1_ERRINT_MASK                     0x2u
#define CAN_ESR1_ERRINT_SHIFT                    1u
#define CAN_ESR1_ERRINT_WIDTH                    1u
#define CAN_ESR1_ERRINT(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_ERRINT_SHIFT))&CAN_ESR1_ERRINT_MASK)
#define CAN_ESR1_BOFFINT_MASK                    0x4u
#define CAN_ESR1_BOFFINT_SHIFT                   2u
#define CAN_ESR1_BOFFINT_WIDTH                   1u
#define CAN_ESR1_BOFFINT(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BOFFINT_SHIFT))&CAN_ESR1_BOFFINT_MASK)
#define CAN_ESR1_RX_MASK                         0x8u
#define CAN_ESR1_RX_SHIFT                        3u
#define CAN_ESR1_RX_WIDTH                        1u
#define CAN_ESR1_RX(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_RX_SHIFT))&CAN_ESR1_RX_MASK)
#define CAN_ESR1_FLTCONF_MASK                    0x30u
#define CAN_ESR1_FLTCONF_SHIFT                   4u
#define CAN_ESR1_FLTCONF_WIDTH                   2u
#define CAN_ESR1_FLTCONF(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_FLTCONF_SHIFT))&CAN_ESR1_FLTCONF_MASK)
#define CAN_ESR1_TX_MASK                         0x40u
#define CAN_ESR1_TX_SHIFT                        6u
#define CAN_ESR1_TX_WIDTH                        1u
#define CAN_ESR1_TX(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_TX_SHIFT))&CAN_ESR1_TX_MASK)
#define CAN_ESR1_IDLE_MASK                       0x80u
#define CAN_ESR1_IDLE_SHIFT                      7u
#define CAN_ESR1_IDLE_WIDTH                      1u
#define CAN_ESR1_IDLE(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_IDLE_SHIFT))&CAN_ESR1_IDLE_MASK)
#define CAN_ESR1_RXWRN_MASK                      0x100u
#define CAN_ESR1_RXWRN_SHIFT                     8u
#define CAN_ESR1_RXWRN_WIDTH                     1u
#define CAN_ESR1_RXWRN(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_RXWRN_SHIFT))&CAN_ESR1_RXWRN_MASK)
#define CAN_ESR1_TXWRN_MASK                      0x200u
#define CAN_ESR1_TXWRN_SHIFT                     9u
#define CAN_ESR1_TXWRN_WIDTH                     1u
#define CAN_ESR1_TXWRN(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_TXWRN_SHIFT))&CAN_ESR1_TXWRN_MASK)
#define CAN_ESR1_STFERR_MASK                     0x400u
#define CAN_ESR1_STFERR_SHIFT                    10u
#define CAN_ESR1_STFERR_WIDTH                    1u
#define CAN_ESR1_STFERR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_STFERR_SHIFT))&CAN_ESR1_STFERR_MASK)
#define CAN_ESR1_FRMERR_MASK                     0x800u
#define CAN_ESR1_FRMERR_SHIFT                    11u
#define CAN_ESR1_FRMERR_WIDTH                    1u
#define CAN_ESR1_FRMERR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_FRMERR_SHIFT))&CAN_ESR1_FRMERR_MASK)
#define CAN_ESR1_CRCERR_MASK                     0x1000u
#define CAN_ESR1_CRCERR_SHIFT                    12u
#define CAN_ESR1_CRCERR_WIDTH                    1u
#define CAN_ESR1_CRCERR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_CRCERR_SHIFT))&CAN_ESR1_CRCERR_MASK)
#define CAN_ESR1_ACKERR_MASK                     0x2000u
#define CAN_ESR1_ACKERR_SHIFT                    13u
#define CAN_ESR1_ACKERR_WIDTH                    1u
#define CAN_ESR1_ACKERR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_ACKERR_SHIFT))&CAN_ESR1_ACKERR_MASK)
#define CAN_ESR1_BIT0ERR_MASK                    0x4000u
#define CAN_ESR1_BIT0ERR_SHIFT                   14u
#define CAN_ESR1_BIT0ERR_WIDTH                   1u
#define CAN_ESR1_BIT0ERR(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BIT0ERR_SHIFT))&CAN_ESR1_BIT0ERR_MASK)
#define CAN_ESR1_BIT1ERR_MASK                    0x8000u
#define CAN_ESR1_BIT1ERR_SHIFT                   15u
#define CAN_ESR1_BIT1ERR_WIDTH                   1u
#define CAN_ESR1_BIT1ERR(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BIT1ERR_SHIFT))&CAN_ESR1_BIT1ERR_MASK)
#define CAN_ESR1_RWRNINT_MASK                    0x10000u
#define CAN_ESR1_RWRNINT_SHIFT                   16u
#define CAN_ESR1_RWRNINT_WIDTH                   1u
#define CAN_ESR1_RWRNINT(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_RWRNINT_SHIFT))&CAN_ESR1_RWRNINT_MASK)
#define CAN_ESR1_TWRNINT_MASK                    0x20000u
#define CAN_ESR1_TWRNINT_SHIFT                   17u
#define CAN_ESR1_TWRNINT_WIDTH                   1u
#define CAN_ESR1_TWRNINT(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_TWRNINT_SHIFT))&CAN_ESR1_TWRNINT_MASK)
#define CAN_ESR1_SYNCH_MASK                      0x40000u
#define CAN_ESR1_SYNCH_SHIFT                     18u
#define CAN_ESR1_SYNCH_WIDTH                     1u
#define CAN_ESR1_SYNCH(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_SYNCH_SHIFT))&CAN_ESR1_SYNCH_MASK)
#define CAN_ESR1_BOFFDONEINT_MASK                0x80000u
#define CAN_ESR1_BOFFDONEINT_SHIFT               19u
#define CAN_ESR1_BOFFDONEINT_WIDTH               1u
#define CAN_ESR1_BOFFDONEINT(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BOFFDONEINT_SHIFT))&CAN_ESR1_BOFFDONEINT_MASK)
#define CAN_ESR1_ERRINT_FAST_MASK                0x100000u
#define CAN_ESR1_ERRINT_FAST_SHIFT               20u
#define CAN_ESR1_ERRINT_FAST_WIDTH               1u
#define CAN_ESR1_ERRINT_FAST(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_ERRINT_FAST_SHIFT))&CAN_ESR1_ERRINT_FAST_MASK)
#define CAN_ESR1_ERROVR_MASK                     0x200000u
#define CAN_ESR1_ERROVR_SHIFT                    21u
#define CAN_ESR1_ERROVR_WIDTH                    1u
#define CAN_ESR1_ERROVR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_ERROVR_SHIFT))&CAN_ESR1_ERROVR_MASK)
#define CAN_ESR1_STFERR_FAST_MASK                0x4000000u
#define CAN_ESR1_STFERR_FAST_SHIFT               26u
#define CAN_ESR1_STFERR_FAST_WIDTH               1u
#define CAN_ESR1_STFERR_FAST(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_STFERR_FAST_SHIFT))&CAN_ESR1_STFERR_FAST_MASK)
#define CAN_ESR1_FRMERR_FAST_MASK                0x8000000u
#define CAN_ESR1_FRMERR_FAST_SHIFT               27u
#define CAN_ESR1_FRMERR_FAST_WIDTH               1u
#define CAN_ESR1_FRMERR_FAST(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_FRMERR_FAST_SHIFT))&CAN_ESR1_FRMERR_FAST_MASK)
#define CAN_ESR1_CRCERR_FAST_MASK                0x10000000u
#define CAN_ESR1_CRCERR_FAST_SHIFT               28u
#define CAN_ESR1_CRCERR_FAST_WIDTH               1u
#define CAN_ESR1_CRCERR_FAST(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_CRCERR_FAST_SHIFT))&CAN_ESR1_CRCERR_FAST_MASK)
#define CAN_ESR1_BIT0ERR_FAST_MASK               0x40000000u
#define CAN_ESR1_BIT0ERR_FAST_SHIFT              30u
#define CAN_ESR1_BIT0ERR_FAST_WIDTH              1u
#define CAN_ESR1_BIT0ERR_FAST(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BIT0ERR_FAST_SHIFT))&CAN_ESR1_BIT0ERR_FAST_MASK)
#define CAN_ESR1_BIT1ERR_FAST_MASK               0x80000000u
#define CAN_ESR1_BIT1ERR_FAST_SHIFT              31u
#define CAN_ESR1_BIT1ERR_FAST_WIDTH              1u
#define CAN_ESR1_BIT1ERR_FAST(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_ESR1_BIT1ERR_FAST_SHIFT))&CAN_ESR1_BIT1ERR_FAST_MASK)
/* IMASK1 Bit Fields */
#define CAN_IMASK1_BUF31TO0M_MASK                0xFFFFFFFFu
#define CAN_IMASK1_BUF31TO0M_SHIFT               0u
#define CAN_IMASK1_BUF31TO0M_WIDTH               32u
#define CAN_IMASK1_BUF31TO0M(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_IMASK1_BUF31TO0M_SHIFT))&CAN_IMASK1_BUF31TO0M_MASK)
/* IFLAG1 Bit Fields */
#define CAN_IFLAG1_BUF0I_MASK                    0x1u
#define CAN_IFLAG1_BUF0I_SHIFT                   0u
#define CAN_IFLAG1_BUF0I_WIDTH                   1u
#define CAN_IFLAG1_BUF0I(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF0I_SHIFT))&CAN_IFLAG1_BUF0I_MASK)
#define CAN_IFLAG1_BUF4TO1I_MASK                 0x1Eu
#define CAN_IFLAG1_BUF4TO1I_SHIFT                1u
#define CAN_IFLAG1_BUF4TO1I_WIDTH                4u
#define CAN_IFLAG1_BUF4TO1I(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF4TO1I_SHIFT))&CAN_IFLAG1_BUF4TO1I_MASK)
#define CAN_IFLAG1_BUF5I_MASK                    0x20u
#define CAN_IFLAG1_BUF5I_SHIFT                   5u
#define CAN_IFLAG1_BUF5I_WIDTH                   1u
#define CAN_IFLAG1_BUF5I(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF5I_SHIFT))&CAN_IFLAG1_BUF5I_MASK)
#define CAN_IFLAG1_BUF6I_MASK                    0x40u
#define CAN_IFLAG1_BUF6I_SHIFT                   6u
#define CAN_IFLAG1_BUF6I_WIDTH                   1u
#define CAN_IFLAG1_BUF6I(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF6I_SHIFT))&CAN_IFLAG1_BUF6I_MASK)
#define CAN_IFLAG1_BUF7I_MASK                    0x80u
#define CAN_IFLAG1_BUF7I_SHIFT                   7u
#define CAN_IFLAG1_BUF7I_WIDTH                   1u
#define CAN_IFLAG1_BUF7I(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF7I_SHIFT))&CAN_IFLAG1_BUF7I_MASK)
#define CAN_IFLAG1_BUF31TO8I_MASK                0xFFFFFF00u
#define CAN_IFLAG1_BUF31TO8I_SHIFT               8u
#define CAN_IFLAG1_BUF31TO8I_WIDTH               24u
#define CAN_IFLAG1_BUF31TO8I(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_IFLAG1_BUF31TO8I_SHIFT))&CAN_IFLAG1_BUF31TO8I_MASK)
/* CTRL2 Bit Fields */
#define CAN_CTRL2_EDFLTDIS_MASK                  0x800u
#define CAN_CTRL2_EDFLTDIS_SHIFT                 11u
#define CAN_CTRL2_EDFLTDIS_WIDTH                 1u
#define CAN_CTRL2_EDFLTDIS(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_EDFLTDIS_SHIFT))&CAN_CTRL2_EDFLTDIS_MASK)
#define CAN_CTRL2_ISOCANFDEN_MASK                0x1000u
#define CAN_CTRL2_ISOCANFDEN_SHIFT               12u
#define CAN_CTRL2_ISOCANFDEN_WIDTH               1u
#define CAN_CTRL2_ISOCANFDEN(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_ISOCANFDEN_SHIFT))&CAN_CTRL2_ISOCANFDEN_MASK)
#define CAN_CTRL2_PREXCEN_MASK                   0x4000u
#define CAN_CTRL2_PREXCEN_SHIFT                  14u
#define CAN_CTRL2_PREXCEN_WIDTH                  1u
#define CAN_CTRL2_PREXCEN(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_PREXCEN_SHIFT))&CAN_CTRL2_PREXCEN_MASK)
#define CAN_CTRL2_TIMER_SRC_MASK                 0x8000u
#define CAN_CTRL2_TIMER_SRC_SHIFT                15u
#define CAN_CTRL2_TIMER_SRC_WIDTH                1u
#define CAN_CTRL2_TIMER_SRC(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_TIMER_SRC_SHIFT))&CAN_CTRL2_TIMER_SRC_MASK)
#define CAN_CTRL2_EACEN_MASK                     0x10000u
#define CAN_CTRL2_EACEN_SHIFT                    16u
#define CAN_CTRL2_EACEN_WIDTH                    1u
#define CAN_CTRL2_EACEN(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_EACEN_SHIFT))&CAN_CTRL2_EACEN_MASK)
#define CAN_CTRL2_RRS_MASK                       0x20000u
#define CAN_CTRL2_RRS_SHIFT                      17u
#define CAN_CTRL2_RRS_WIDTH                      1u
#define CAN_CTRL2_RRS(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_RRS_SHIFT))&CAN_CTRL2_RRS_MASK)
#define CAN_CTRL2_MRP_MASK                       0x40000u
#define CAN_CTRL2_MRP_SHIFT                      18u
#define CAN_CTRL2_MRP_WIDTH                      1u
#define CAN_CTRL2_MRP(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_MRP_SHIFT))&CAN_CTRL2_MRP_MASK)
#define CAN_CTRL2_TASD_MASK                      0xF80000u
#define CAN_CTRL2_TASD_SHIFT                     19u
#define CAN_CTRL2_TASD_WIDTH                     5u
#define CAN_CTRL2_TASD(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_TASD_SHIFT))&CAN_CTRL2_TASD_MASK)
#define CAN_CTRL2_RFFN_MASK                      0xF000000u
#define CAN_CTRL2_RFFN_SHIFT                     24u
#define CAN_CTRL2_RFFN_WIDTH                     4u
#define CAN_CTRL2_RFFN(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_RFFN_SHIFT))&CAN_CTRL2_RFFN_MASK)
#define CAN_CTRL2_BOFFDONEMSK_MASK               0x40000000u
#define CAN_CTRL2_BOFFDONEMSK_SHIFT              30u
#define CAN_CTRL2_BOFFDONEMSK_WIDTH              1u
#define CAN_CTRL2_BOFFDONEMSK(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_BOFFDONEMSK_SHIFT))&CAN_CTRL2_BOFFDONEMSK_MASK)
#define CAN_CTRL2_ERRMSK_FAST_MASK               0x80000000u
#define CAN_CTRL2_ERRMSK_FAST_SHIFT              31u
#define CAN_CTRL2_ERRMSK_FAST_WIDTH              1u
#define CAN_CTRL2_ERRMSK_FAST(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_ERRMSK_FAST_SHIFT))&CAN_CTRL2_ERRMSK_FAST_MASK)
/* ESR2 Bit Fields */
#define CAN_ESR2_IMB_MASK                        0x2000u
#define CAN_ESR2_IMB_SHIFT                       13u
#define CAN_ESR2_IMB_WIDTH                       1u
#define CAN_ESR2_IMB(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_ESR2_IMB_SHIFT))&CAN_ESR2_IMB_MASK)
#define CAN_ESR2_VPS_MASK                        0x4000u
#define CAN_ESR2_VPS_SHIFT                       14u
#define CAN_ESR2_VPS_WIDTH                       1u
#define CAN_ESR2_VPS(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_ESR2_VPS_SHIFT))&CAN_ESR2_VPS_MASK)
#define CAN_ESR2_LPTM_MASK                       0x7F0000u
#define CAN_ESR2_LPTM_SHIFT                      16u
#define CAN_ESR2_LPTM_WIDTH                      7u
#define CAN_ESR2_LPTM(x)                         (((uint32_t)(((uint32_t)(x))<<CAN_ESR2_LPTM_SHIFT))&CAN_ESR2_LPTM_MASK)
/* CRCR Bit Fields */
#define CAN_CRCR_TXCRC_MASK                      0x7FFFu
#define CAN_CRCR_TXCRC_SHIFT                     0u
#define CAN_CRCR_TXCRC_WIDTH                     15u
#define CAN_CRCR_TXCRC(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CRCR_TXCRC_SHIFT))&CAN_CRCR_TXCRC_MASK)
#define CAN_CRCR_MBCRC_MASK                      0x7F0000u
#define CAN_CRCR_MBCRC_SHIFT                     16u
#define CAN_CRCR_MBCRC_WIDTH                     7u
#define CAN_CRCR_MBCRC(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CRCR_MBCRC_SHIFT))&CAN_CRCR_MBCRC_MASK)
/* RXFGMASK Bit Fields */
#define CAN_RXFGMASK_FGM_MASK                    0xFFFFFFFFu
#define CAN_RXFGMASK_FGM_SHIFT                   0u
#define CAN_RXFGMASK_FGM_WIDTH                   32u
#define CAN_RXFGMASK_FGM(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_RXFGMASK_FGM_SHIFT))&CAN_RXFGMASK_FGM_MASK)
/* RXFIR Bit Fields */
#define CAN_RXFIR_IDHIT_MASK                     0x1FFu
#define CAN_RXFIR_IDHIT_SHIFT                    0u
#define CAN_RXFIR_IDHIT_WIDTH                    9u
#define CAN_RXFIR_IDHIT(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_RXFIR_IDHIT_SHIFT))&CAN_RXFIR_IDHIT_MASK)
/* CBT Bit Fields */
#define CAN_CBT_EPSEG2_MASK                      0x1Fu
#define CAN_CBT_EPSEG2_SHIFT                     0u
#define CAN_CBT_EPSEG2_WIDTH                     5u
#define CAN_CBT_EPSEG2(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CBT_EPSEG2_SHIFT))&CAN_CBT_EPSEG2_MASK)
#define CAN_CBT_EPSEG1_MASK                      0x3E0u
#define CAN_CBT_EPSEG1_SHIFT                     5u
#define CAN_CBT_EPSEG1_WIDTH                     5u
#define CAN_CBT_EPSEG1(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_CBT_EPSEG1_SHIFT))&CAN_CBT_EPSEG1_MASK)
#define CAN_CBT_EPROPSEG_MASK                    0xFC00u
#define CAN_CBT_EPROPSEG_SHIFT                   10u
#define CAN_CBT_EPROPSEG_WIDTH                   6u
#define CAN_CBT_EPROPSEG(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_CBT_EPROPSEG_SHIFT))&CAN_CBT_EPROPSEG_MASK)
#define CAN_CBT_ERJW_MASK                        0x1F0000u
#define CAN_CBT_ERJW_SHIFT                       16u
#define CAN_CBT_ERJW_WIDTH                       5u
#define CAN_CBT_ERJW(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_CBT_ERJW_SHIFT))&CAN_CBT_ERJW_MASK)
#define CAN_CBT_EPRESDIV_MASK                    0x7FE00000u
#define CAN_CBT_EPRESDIV_SHIFT                   21u
#define CAN_CBT_EPRESDIV_WIDTH                   10u
#define CAN_CBT_EPRESDIV(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_CBT_EPRESDIV_SHIFT))&CAN_CBT_EPRESDIV_MASK)
#define CAN_CBT_BTF_MASK                         0x80000000u
#define CAN_CBT_BTF_SHIFT                        31u
#define CAN_CBT_BTF_WIDTH                        1u
#define CAN_CBT_BTF(x)                           (((uint32_t)(((uint32_t)(x))<<CAN_CBT_BTF_SHIFT))&CAN_CBT_BTF_MASK)
/* RAMn Bit Fields */
#define CAN_RAMn_DATA_BYTE_3_MASK                0xFFu
#define CAN_RAMn_DATA_BYTE_3_SHIFT               0u
#define CAN_RAMn_DATA_BYTE_3_WIDTH               8u
#define CAN_RAMn_DATA_BYTE_3(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_RAMn_DATA_BYTE_3_SHIFT))&CAN_RAMn_DATA_BYTE_3_MASK)
#define CAN_RAMn_DATA_BYTE_2_MASK                0xFF00u
#define CAN_RAMn_DATA_BYTE_2_SHIFT               8u
#define CAN_RAMn_DATA_BYTE_2_WIDTH               8u
#define CAN_RAMn_DATA_BYTE_2(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_RAMn_DATA_BYTE_2_SHIFT))&CAN_RAMn_DATA_BYTE_2_MASK)
#define CAN_RAMn_DATA_BYTE_1_MASK                0xFF0000u
#define CAN_RAMn_DATA_BYTE_1_SHIFT               16u
#define CAN_RAMn_DATA_BYTE_1_WIDTH               8u
#define CAN_RAMn_DATA_BYTE_1(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_RAMn_DATA_BYTE_1_SHIFT))&CAN_RAMn_DATA_BYTE_1_MASK)
#define CAN_RAMn_DATA_BYTE_0_MASK                0xFF000000u
#define CAN_RAMn_DATA_BYTE_0_SHIFT               24u
#define CAN_RAMn_DATA_BYTE_0_WIDTH               8u
#define CAN_RAMn_DATA_BYTE_0(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_RAMn_DATA_BYTE_0_SHIFT))&CAN_RAMn_DATA_BYTE_0_MASK)
/* RXIMR Bit Fields */
#define CAN_RXIMR_MI_MASK                        0xFFFFFFFFu
#define CAN_RXIMR_MI_SHIFT                       0u
#define CAN_RXIMR_MI_WIDTH                       32u
#define CAN_RXIMR_MI(x)                          (((uint32_t)(((uint32_t)(x))<<CAN_RXIMR_MI_SHIFT))&CAN_RXIMR_MI_MASK)
/* CTRL1_PN Bit Fields */
#define CAN_CTRL1_PN_FCS_MASK                    0x3u
#define CAN_CTRL1_PN_FCS_SHIFT                   0u
#define CAN_CTRL1_PN_FCS_WIDTH                   2u
#define CAN_CTRL1_PN_FCS(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_FCS_SHIFT))&CAN_CTRL1_PN_FCS_MASK)
#define CAN_CTRL1_PN_IDFS_MASK                   0xCu
#define CAN_CTRL1_PN_IDFS_SHIFT                  2u
#define CAN_CTRL1_PN_IDFS_WIDTH                  2u
#define CAN_CTRL1_PN_IDFS(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_IDFS_SHIFT))&CAN_CTRL1_PN_IDFS_MASK)
#define CAN_CTRL1_PN_PLFS_MASK                   0x30u
#define CAN_CTRL1_PN_PLFS_SHIFT                  4u
#define CAN_CTRL1_PN_PLFS_WIDTH                  2u
#define CAN_CTRL1_PN_PLFS(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_PLFS_SHIFT))&CAN_CTRL1_PN_PLFS_MASK)
#define CAN_CTRL1_PN_NMATCH_MASK                 0xFF00u
#define CAN_CTRL1_PN_NMATCH_SHIFT                8u
#define CAN_CTRL1_PN_NMATCH_WIDTH                8u
#define CAN_CTRL1_PN_NMATCH(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_NMATCH_SHIFT))&CAN_CTRL1_PN_NMATCH_MASK)
#define CAN_CTRL1_PN_WUMF_MSK_MASK               0x10000u
#define CAN_CTRL1_PN_WUMF_MSK_SHIFT              16u
#define CAN_CTRL1_PN_WUMF_MSK_WIDTH              1u
#define CAN_CTRL1_PN_WUMF_MSK(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_WUMF_MSK_SHIFT))&CAN_CTRL1_PN_WUMF_MSK_MASK)
#define CAN_CTRL1_PN_WTOF_MSK_MASK               0x20000u
#define CAN_CTRL1_PN_WTOF_MSK_SHIFT              17u
#define CAN_CTRL1_PN_WTOF_MSK_WIDTH              1u
#define CAN_CTRL1_PN_WTOF_MSK(x)                 (((uint32_t)(((uint32_t)(x))<<CAN_CTRL1_PN_WTOF_MSK_SHIFT))&CAN_CTRL1_PN_WTOF_MSK_MASK)
/* CTRL2_PN Bit Fields */
#define CAN_CTRL2_PN_MATCHTO_MASK                0xFFFFu
#define CAN_CTRL2_PN_MATCHTO_SHIFT               0u
#define CAN_CTRL2_PN_MATCHTO_WIDTH               16u
#define CAN_CTRL2_PN_MATCHTO(x)                  (((uint32_t)(((uint32_t)(x))<<CAN_CTRL2_PN_MATCHTO_SHIFT))&CAN_CTRL2_PN_MATCHTO_MASK)
/* WU_MTC Bit Fields */
#define CAN_WU_MTC_MCOUNTER_MASK                 0xFF00u
#define CAN_WU_MTC_MCOUNTER_SHIFT                8u
#define CAN_WU_MTC_MCOUNTER_WIDTH                8u
#define CAN_WU_MTC_MCOUNTER(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_WU_MTC_MCOUNTER_SHIFT))&CAN_WU_MTC_MCOUNTER_MASK)
#define CAN_WU_MTC_WUMF_MASK                     0x10000u
#define CAN_WU_MTC_WUMF_SHIFT                    16u
#define CAN_WU_MTC_WUMF_WIDTH                    1u
#define CAN_WU_MTC_WUMF(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WU_MTC_WUMF_SHIFT))&CAN_WU_MTC_WUMF_MASK)
#define CAN_WU_MTC_WTOF_MASK                     0x20000u
#define CAN_WU_MTC_WTOF_SHIFT                    17u
#define CAN_WU_MTC_WTOF_WIDTH                    1u
#define CAN_WU_MTC_WTOF(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WU_MTC_WTOF_SHIFT))&CAN_WU_MTC_WTOF_MASK)
/* FLT_ID1 Bit Fields */
#define CAN_FLT_ID1_FLT_ID1_MASK                 0x1FFFFFFFu
#define CAN_FLT_ID1_FLT_ID1_SHIFT                0u
#define CAN_FLT_ID1_FLT_ID1_WIDTH                29u
#define CAN_FLT_ID1_FLT_ID1(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID1_FLT_ID1_SHIFT))&CAN_FLT_ID1_FLT_ID1_MASK)
#define CAN_FLT_ID1_FLT_RTR_MASK                 0x20000000u
#define CAN_FLT_ID1_FLT_RTR_SHIFT                29u
#define CAN_FLT_ID1_FLT_RTR_WIDTH                1u
#define CAN_FLT_ID1_FLT_RTR(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID1_FLT_RTR_SHIFT))&CAN_FLT_ID1_FLT_RTR_MASK)
#define CAN_FLT_ID1_FLT_IDE_MASK                 0x40000000u
#define CAN_FLT_ID1_FLT_IDE_SHIFT                30u
#define CAN_FLT_ID1_FLT_IDE_WIDTH                1u
#define CAN_FLT_ID1_FLT_IDE(x)                   (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID1_FLT_IDE_SHIFT))&CAN_FLT_ID1_FLT_IDE_MASK)
/* FLT_DLC Bit Fields */
#define CAN_FLT_DLC_FLT_DLC_HI_MASK              0xFu
#define CAN_FLT_DLC_FLT_DLC_HI_SHIFT             0u
#define CAN_FLT_DLC_FLT_DLC_HI_WIDTH             4u
#define CAN_FLT_DLC_FLT_DLC_HI(x)                (((uint32_t)(((uint32_t)(x))<<CAN_FLT_DLC_FLT_DLC_HI_SHIFT))&CAN_FLT_DLC_FLT_DLC_HI_MASK)
#define CAN_FLT_DLC_FLT_DLC_LO_MASK              0xF0000u
#define CAN_FLT_DLC_FLT_DLC_LO_SHIFT             16u
#define CAN_FLT_DLC_FLT_DLC_LO_WIDTH             4u
#define CAN_FLT_DLC_FLT_DLC_LO(x)                (((uint32_t)(((uint32_t)(x))<<CAN_FLT_DLC_FLT_DLC_LO_SHIFT))&CAN_FLT_DLC_FLT_DLC_LO_MASK)
/* PL1_LO Bit Fields */
#define CAN_PL1_LO_Data_byte_3_MASK              0xFFu
#define CAN_PL1_LO_Data_byte_3_SHIFT             0u
#define CAN_PL1_LO_Data_byte_3_WIDTH             8u
#define CAN_PL1_LO_Data_byte_3(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_LO_Data_byte_3_SHIFT))&CAN_PL1_LO_Data_byte_3_MASK)
#define CAN_PL1_LO_Data_byte_2_MASK              0xFF00u
#define CAN_PL1_LO_Data_byte_2_SHIFT             8u
#define CAN_PL1_LO_Data_byte_2_WIDTH             8u
#define CAN_PL1_LO_Data_byte_2(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_LO_Data_byte_2_SHIFT))&CAN_PL1_LO_Data_byte_2_MASK)
#define CAN_PL1_LO_Data_byte_1_MASK              0xFF0000u
#define CAN_PL1_LO_Data_byte_1_SHIFT             16u
#define CAN_PL1_LO_Data_byte_1_WIDTH             8u
#define CAN_PL1_LO_Data_byte_1(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_LO_Data_byte_1_SHIFT))&CAN_PL1_LO_Data_byte_1_MASK)
#define CAN_PL1_LO_Data_byte_0_MASK              0xFF000000u
#define CAN_PL1_LO_Data_byte_0_SHIFT             24u
#define CAN_PL1_LO_Data_byte_0_WIDTH             8u
#define CAN_PL1_LO_Data_byte_0(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_LO_Data_byte_0_SHIFT))&CAN_PL1_LO_Data_byte_0_MASK)
/* PL1_HI Bit Fields */
#define CAN_PL1_HI_Data_byte_7_MASK              0xFFu
#define CAN_PL1_HI_Data_byte_7_SHIFT             0u
#define CAN_PL1_HI_Data_byte_7_WIDTH             8u
#define CAN_PL1_HI_Data_byte_7(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_HI_Data_byte_7_SHIFT))&CAN_PL1_HI_Data_byte_7_MASK)
#define CAN_PL1_HI_Data_byte_6_MASK              0xFF00u
#define CAN_PL1_HI_Data_byte_6_SHIFT             8u
#define CAN_PL1_HI_Data_byte_6_WIDTH             8u
#define CAN_PL1_HI_Data_byte_6(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_HI_Data_byte_6_SHIFT))&CAN_PL1_HI_Data_byte_6_MASK)
#define CAN_PL1_HI_Data_byte_5_MASK              0xFF0000u
#define CAN_PL1_HI_Data_byte_5_SHIFT             16u
#define CAN_PL1_HI_Data_byte_5_WIDTH             8u
#define CAN_PL1_HI_Data_byte_5(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_HI_Data_byte_5_SHIFT))&CAN_PL1_HI_Data_byte_5_MASK)
#define CAN_PL1_HI_Data_byte_4_MASK              0xFF000000u
#define CAN_PL1_HI_Data_byte_4_SHIFT             24u
#define CAN_PL1_HI_Data_byte_4_WIDTH             8u
#define CAN_PL1_HI_Data_byte_4(x)                (((uint32_t)(((uint32_t)(x))<<CAN_PL1_HI_Data_byte_4_SHIFT))&CAN_PL1_HI_Data_byte_4_MASK)
/* FLT_ID2_IDMASK Bit Fields */
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK   0x1FFFFFFFu
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT  0u
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_WIDTH  29u
#define CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK(x)     (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT))&CAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK)
#define CAN_FLT_ID2_IDMASK_RTR_MSK_MASK          0x20000000u
#define CAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT         29u
#define CAN_FLT_ID2_IDMASK_RTR_MSK_WIDTH         1u
#define CAN_FLT_ID2_IDMASK_RTR_MSK(x)            (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT))&CAN_FLT_ID2_IDMASK_RTR_MSK_MASK)
#define CAN_FLT_ID2_IDMASK_IDE_MSK_MASK          0x40000000u
#define CAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT         30u
#define CAN_FLT_ID2_IDMASK_IDE_MSK_WIDTH         1u
#define CAN_FLT_ID2_IDMASK_IDE_MSK(x)            (((uint32_t)(((uint32_t)(x))<<CAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT))&CAN_FLT_ID2_IDMASK_IDE_MSK_MASK)
/* PL2_PLMASK_LO Bit Fields */
#define CAN_PL2_PLMASK_LO_Data_byte_3_MASK       0xFFu
#define CAN_PL2_PLMASK_LO_Data_byte_3_SHIFT      0u
#define CAN_PL2_PLMASK_LO_Data_byte_3_WIDTH      8u
#define CAN_PL2_PLMASK_LO_Data_byte_3(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_LO_Data_byte_3_SHIFT))&CAN_PL2_PLMASK_LO_Data_byte_3_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_2_MASK       0xFF00u
#define CAN_PL2_PLMASK_LO_Data_byte_2_SHIFT      8u
#define CAN_PL2_PLMASK_LO_Data_byte_2_WIDTH      8u
#define CAN_PL2_PLMASK_LO_Data_byte_2(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_LO_Data_byte_2_SHIFT))&CAN_PL2_PLMASK_LO_Data_byte_2_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_1_MASK       0xFF0000u
#define CAN_PL2_PLMASK_LO_Data_byte_1_SHIFT      16u
#define CAN_PL2_PLMASK_LO_Data_byte_1_WIDTH      8u
#define CAN_PL2_PLMASK_LO_Data_byte_1(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_LO_Data_byte_1_SHIFT))&CAN_PL2_PLMASK_LO_Data_byte_1_MASK)
#define CAN_PL2_PLMASK_LO_Data_byte_0_MASK       0xFF000000u
#define CAN_PL2_PLMASK_LO_Data_byte_0_SHIFT      24u
#define CAN_PL2_PLMASK_LO_Data_byte_0_WIDTH      8u
#define CAN_PL2_PLMASK_LO_Data_byte_0(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_LO_Data_byte_0_SHIFT))&CAN_PL2_PLMASK_LO_Data_byte_0_MASK)
/* PL2_PLMASK_HI Bit Fields */
#define CAN_PL2_PLMASK_HI_Data_byte_7_MASK       0xFFu
#define CAN_PL2_PLMASK_HI_Data_byte_7_SHIFT      0u
#define CAN_PL2_PLMASK_HI_Data_byte_7_WIDTH      8u
#define CAN_PL2_PLMASK_HI_Data_byte_7(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_HI_Data_byte_7_SHIFT))&CAN_PL2_PLMASK_HI_Data_byte_7_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_6_MASK       0xFF00u
#define CAN_PL2_PLMASK_HI_Data_byte_6_SHIFT      8u
#define CAN_PL2_PLMASK_HI_Data_byte_6_WIDTH      8u
#define CAN_PL2_PLMASK_HI_Data_byte_6(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_HI_Data_byte_6_SHIFT))&CAN_PL2_PLMASK_HI_Data_byte_6_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_5_MASK       0xFF0000u
#define CAN_PL2_PLMASK_HI_Data_byte_5_SHIFT      16u
#define CAN_PL2_PLMASK_HI_Data_byte_5_WIDTH      8u
#define CAN_PL2_PLMASK_HI_Data_byte_5(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_HI_Data_byte_5_SHIFT))&CAN_PL2_PLMASK_HI_Data_byte_5_MASK)
#define CAN_PL2_PLMASK_HI_Data_byte_4_MASK       0xFF000000u
#define CAN_PL2_PLMASK_HI_Data_byte_4_SHIFT      24u
#define CAN_PL2_PLMASK_HI_Data_byte_4_WIDTH      8u
#define CAN_PL2_PLMASK_HI_Data_byte_4(x)         (((uint32_t)(((uint32_t)(x))<<CAN_PL2_PLMASK_HI_Data_byte_4_SHIFT))&CAN_PL2_PLMASK_HI_Data_byte_4_MASK)
/* WMBn_CS Bit Fields */
#define CAN_WMBn_CS_DLC_MASK                     0xF0000u
#define CAN_WMBn_CS_DLC_SHIFT                    16u
#define CAN_WMBn_CS_DLC_WIDTH                    4u
#define CAN_WMBn_CS_DLC(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_CS_DLC_SHIFT))&CAN_WMBn_CS_DLC_MASK)
#define CAN_WMBn_CS_RTR_MASK                     0x100000u
#define CAN_WMBn_CS_RTR_SHIFT                    20u
#define CAN_WMBn_CS_RTR_WIDTH                    1u
#define CAN_WMBn_CS_RTR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_CS_RTR_SHIFT))&CAN_WMBn_CS_RTR_MASK)
#define CAN_WMBn_CS_IDE_MASK                     0x200000u
#define CAN_WMBn_CS_IDE_SHIFT                    21u
#define CAN_WMBn_CS_IDE_WIDTH                    1u
#define CAN_WMBn_CS_IDE(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_CS_IDE_SHIFT))&CAN_WMBn_CS_IDE_MASK)
#define CAN_WMBn_CS_SRR_MASK                     0x400000u
#define CAN_WMBn_CS_SRR_SHIFT                    22u
#define CAN_WMBn_CS_SRR_WIDTH                    1u
#define CAN_WMBn_CS_SRR(x)                       (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_CS_SRR_SHIFT))&CAN_WMBn_CS_SRR_MASK)
/* WMBn_ID Bit Fields */
#define CAN_WMBn_ID_ID_MASK                      0x1FFFFFFFu
#define CAN_WMBn_ID_ID_SHIFT                     0u
#define CAN_WMBn_ID_ID_WIDTH                     29u
#define CAN_WMBn_ID_ID(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_ID_ID_SHIFT))&CAN_WMBn_ID_ID_MASK)
/* WMBn_D03 Bit Fields */
#define CAN_WMBn_D03_Data_byte_3_MASK            0xFFu
#define CAN_WMBn_D03_Data_byte_3_SHIFT           0u
#define CAN_WMBn_D03_Data_byte_3_WIDTH           8u
#define CAN_WMBn_D03_Data_byte_3(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D03_Data_byte_3_SHIFT))&CAN_WMBn_D03_Data_byte_3_MASK)
#define CAN_WMBn_D03_Data_byte_2_MASK            0xFF00u
#define CAN_WMBn_D03_Data_byte_2_SHIFT           8u
#define CAN_WMBn_D03_Data_byte_2_WIDTH           8u
#define CAN_WMBn_D03_Data_byte_2(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D03_Data_byte_2_SHIFT))&CAN_WMBn_D03_Data_byte_2_MASK)
#define CAN_WMBn_D03_Data_byte_1_MASK            0xFF0000u
#define CAN_WMBn_D03_Data_byte_1_SHIFT           16u
#define CAN_WMBn_D03_Data_byte_1_WIDTH           8u
#define CAN_WMBn_D03_Data_byte_1(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D03_Data_byte_1_SHIFT))&CAN_WMBn_D03_Data_byte_1_MASK)
#define CAN_WMBn_D03_Data_byte_0_MASK            0xFF000000u
#define CAN_WMBn_D03_Data_byte_0_SHIFT           24u
#define CAN_WMBn_D03_Data_byte_0_WIDTH           8u
#define CAN_WMBn_D03_Data_byte_0(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D03_Data_byte_0_SHIFT))&CAN_WMBn_D03_Data_byte_0_MASK)
/* WMBn_D47 Bit Fields */
#define CAN_WMBn_D47_Data_byte_7_MASK            0xFFu
#define CAN_WMBn_D47_Data_byte_7_SHIFT           0u
#define CAN_WMBn_D47_Data_byte_7_WIDTH           8u
#define CAN_WMBn_D47_Data_byte_7(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D47_Data_byte_7_SHIFT))&CAN_WMBn_D47_Data_byte_7_MASK)
#define CAN_WMBn_D47_Data_byte_6_MASK            0xFF00u
#define CAN_WMBn_D47_Data_byte_6_SHIFT           8u
#define CAN_WMBn_D47_Data_byte_6_WIDTH           8u
#define CAN_WMBn_D47_Data_byte_6(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D47_Data_byte_6_SHIFT))&CAN_WMBn_D47_Data_byte_6_MASK)
#define CAN_WMBn_D47_Data_byte_5_MASK            0xFF0000u
#define CAN_WMBn_D47_Data_byte_5_SHIFT           16u
#define CAN_WMBn_D47_Data_byte_5_WIDTH           8u
#define CAN_WMBn_D47_Data_byte_5(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D47_Data_byte_5_SHIFT))&CAN_WMBn_D47_Data_byte_5_MASK)
#define CAN_WMBn_D47_Data_byte_4_MASK            0xFF000000u
#define CAN_WMBn_D47_Data_byte_4_SHIFT           24u
#define CAN_WMBn_D47_Data_byte_4_WIDTH           8u
#define CAN_WMBn_D47_Data_byte_4(x)              (((uint32_t)(((uint32_t)(x))<<CAN_WMBn_D47_Data_byte_4_SHIFT))&CAN_WMBn_D47_Data_byte_4_MASK)
/* FDCTRL Bit Fields */
#define CAN_FDCTRL_TDCVAL_MASK                   0x3Fu
#define CAN_FDCTRL_TDCVAL_SHIFT                  0u
#define CAN_FDCTRL_TDCVAL_WIDTH                  6u
#define CAN_FDCTRL_TDCVAL(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_TDCVAL_SHIFT))&CAN_FDCTRL_TDCVAL_MASK)
#define CAN_FDCTRL_TDCOFF_MASK                   0x1F00u
#define CAN_FDCTRL_TDCOFF_SHIFT                  8u
#define CAN_FDCTRL_TDCOFF_WIDTH                  5u
#define CAN_FDCTRL_TDCOFF(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_TDCOFF_SHIFT))&CAN_FDCTRL_TDCOFF_MASK)
#define CAN_FDCTRL_TDCFAIL_MASK                  0x4000u
#define CAN_FDCTRL_TDCFAIL_SHIFT                 14u
#define CAN_FDCTRL_TDCFAIL_WIDTH                 1u
#define CAN_FDCTRL_TDCFAIL(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_TDCFAIL_SHIFT))&CAN_FDCTRL_TDCFAIL_MASK)
#define CAN_FDCTRL_TDCEN_MASK                    0x8000u
#define CAN_FDCTRL_TDCEN_SHIFT                   15u
#define CAN_FDCTRL_TDCEN_WIDTH                   1u
#define CAN_FDCTRL_TDCEN(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_TDCEN_SHIFT))&CAN_FDCTRL_TDCEN_MASK)
#define CAN_FDCTRL_MBDSR0_MASK                   0x30000u
#define CAN_FDCTRL_MBDSR0_SHIFT                  16u
#define CAN_FDCTRL_MBDSR0_WIDTH                  2u
#define CAN_FDCTRL_MBDSR0(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_MBDSR0_SHIFT))&CAN_FDCTRL_MBDSR0_MASK)
#define CAN_FDCTRL_FDRATE_MASK                   0x80000000u
#define CAN_FDCTRL_FDRATE_SHIFT                  31u
#define CAN_FDCTRL_FDRATE_WIDTH                  1u
#define CAN_FDCTRL_FDRATE(x)                     (((uint32_t)(((uint32_t)(x))<<CAN_FDCTRL_FDRATE_SHIFT))&CAN_FDCTRL_FDRATE_MASK)
/* FDCBT Bit Fields */
#define CAN_FDCBT_FPSEG2_MASK                    0x7u
#define CAN_FDCBT_FPSEG2_SHIFT                   0u
#define CAN_FDCBT_FPSEG2_WIDTH                   3u
#define CAN_FDCBT_FPSEG2(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_FDCBT_FPSEG2_SHIFT))&CAN_FDCBT_FPSEG2_MASK)
#define CAN_FDCBT_FPSEG1_MASK                    0xE0u
#define CAN_FDCBT_FPSEG1_SHIFT                   5u
#define CAN_FDCBT_FPSEG1_WIDTH                   3u
#define CAN_FDCBT_FPSEG1(x)                      (((uint32_t)(((uint32_t)(x))<<CAN_FDCBT_FPSEG1_SHIFT))&CAN_FDCBT_FPSEG1_MASK)
#define CAN_FDCBT_FPROPSEG_MASK                  0x7C00u
#define CAN_FDCBT_FPROPSEG_SHIFT                 10u
#define CAN_FDCBT_FPROPSEG_WIDTH                 5u
#define CAN_FDCBT_FPROPSEG(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_FDCBT_FPROPSEG_SHIFT))&CAN_FDCBT_FPROPSEG_MASK)
#define CAN_FDCBT_FRJW_MASK                      0x70000u
#define CAN_FDCBT_FRJW_SHIFT                     16u
#define CAN_FDCBT_FRJW_WIDTH                     3u
#define CAN_FDCBT_FRJW(x)                        (((uint32_t)(((uint32_t)(x))<<CAN_FDCBT_FRJW_SHIFT))&CAN_FDCBT_FRJW_MASK)
#define CAN_FDCBT_FPRESDIV_MASK                  0x3FF00000u
#define CAN_FDCBT_FPRESDIV_SHIFT                 20u
#define CAN_FDCBT_FPRESDIV_WIDTH                 10u
#define CAN_FDCBT_FPRESDIV(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_FDCBT_FPRESDIV_SHIFT))&CAN_FDCBT_FPRESDIV_MASK)
/* FDCRC Bit Fields */
#define CAN_FDCRC_FD_TXCRC_MASK                  0x1FFFFFu
#define CAN_FDCRC_FD_TXCRC_SHIFT                 0u
#define CAN_FDCRC_FD_TXCRC_WIDTH                 21u
#define CAN_FDCRC_FD_TXCRC(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_FDCRC_FD_TXCRC_SHIFT))&CAN_FDCRC_FD_TXCRC_MASK)
#define CAN_FDCRC_FD_MBCRC_MASK                  0x7F000000u
#define CAN_FDCRC_FD_MBCRC_SHIFT                 24u
#define CAN_FDCRC_FD_MBCRC_WIDTH                 7u
#define CAN_FDCRC_FD_MBCRC(x)                    (((uint32_t)(((uint32_t)(x))<<CAN_FDCRC_FD_MBCRC_SHIFT))&CAN_FDCRC_FD_MBCRC_MASK)

/*!
 * @}
 */ /* end of group CAN_Register_Masks */


/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */

#endif /* CAN_STUB_H */