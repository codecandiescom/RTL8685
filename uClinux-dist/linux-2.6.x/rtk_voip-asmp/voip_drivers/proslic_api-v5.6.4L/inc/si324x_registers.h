/*
** Copyright (c) 2007 by Silicon Laboratories
**
** $Id: si324x_registers.h,v 1.1 2012/08/21 09:43:53 krammer Exp $
**
** Si324x_Registers.h
**
** Author(s): 
** laj
**
** Distributed by: 
** Silicon Laboratories, Inc
**
** This file contains proprietary information.	 
** No dissemination allowed without prior written permission from
** Silicon Laboratories, Inc.
**
** File Description:
** This is the header file that contains
** register and RAM names definitions for 
** the Si324x ProSLIC.
**
** Dependancies:
** 
**
*/
#ifndef SI324XREGS_H
#define SI324XREGS_H

/*
** This defines the neumomics for the Si324x registers
*/
enum REGISTERS {
ID,
RESET,
MSTREN,
MSTRSTAT,
RAMSTAT,
RAM_ADDR_HI,
RAM_DATA_B0,
RAM_DATA_B1,
RAM_DATA_B2,
RAM_DATA_B3,
RAM_ADDR_LO,
PCMMODE,
PCMTXLO,
PCMTXHI,
PCMRXLO,
PCMRXHI,
IRQ,
IRQ0,
IRQ1,
IRQ2,
IRQ3,
IRQ4,
IRQEN1,
IRQEN2,
IRQEN3,
IRQEN4,
CALR0,
CALR1,
CALR2,
CALR3,
LINEFEED,
POLREV,
SPEEDUP_DIS,
SPEEDUP,
LCRRTP,
OFFLOAD,
BATSELMAP,
BATSEL,
RINGCON,
RINGTALO,
RINGTAHI,
RINGTILO,
RINGTIHI,
LOOPBACK,
DIGCON,
RA,
ZCAL_EN,
PMCON,
OMODE,
OCON,
O1TALO,
O1TAHI,
O1TILO,
O1TIHI,
O2TALO,
O2TAHI,
O2TILO,
O2TIHI,
FSKDAT,
FSKDEPTH,
TONDTMF,
TONDET,
TONEN,
GCI_CI,
GLOBSTAT1,
GLOBSTAT2,
USERSTAT,
GPIO,
GPIO_CFG1,
GPIO_CFG2,
GPIO_CFG3,
DIAG1,
DIAG2,
CM_CLAMP,
REG74,
REG75,
REG76,
REG77,
REG78,
REG79,
AUTO,
JMPEN,
JMP0LO,
JMP0HI,
JMP1LO,
JMP1HI,
JMP2LO,
JMP2HI,
JMP3LO,
JMP3HI,
JMP4LO,
JMP4HI,
JMP5LO,
JMP5HI,
JMP6LO,
JMP6HI,
JMP7LO,
JMP7HI,
PDN,
PDN_STAT
};


/*
** This defines the neumomics for the Si324x RAM locations (revB)
*/
enum SRAM {
IRNGNG_SENSE,
MADC_VTIPC,
MADC_VRINGC,
MADC_VBAT,
MADC_VLONG,
MADC_VBLKRNG,
MADC_IBLKRNG,
MADC_ILONG,
MADC_ITIP,
MADC_IRING,
MADC_ILOOP,
VDIFF_SENSE,
VTIP,
VRING,
P_Q1_D,
P_Q2_D,
P_Q3_D,
P_Q4_D,
P_Q5_D,
P_Q6_D,
P_Q1,
DIAG_EX1,
DIAG_EX2,
DIAG_LPF_MADC,
DIAG_DMM_I,
DIAG_DMM_V,
OSC1FREQ,
OSC1AMP,
OSC1PHAS,
OSC2FREQ,
OSC2AMP,
OSC2PHAS,
TESTB0_1,
TESTB1_1,
TESTB2_1,
TESTA1_1,
TESTA2_1,
TESTB0_2,
TESTB1_2,
TESTB2_2,
TESTA1_2,
TESTA2_2,
TESTB0_3,
TESTB1_3,
TESTB2_3,
TESTA1_3,
TESTA2_3,
TESTPKO,
TESTAVO,
TESTWLN,
TESTAVBW,
TESTPKFL,
TESTAVFL,
TESTPKTH,
TESTAVTH,
DAC_IN_SYNC1,
BYPASS_REG,
LCRMASK_CNT,
DAC_IN_SYNC,
TEMP,
TEMP_ISR,
P_Q2,
P_Q3,
P_Q4,
P_Q5,
P_Q6,
ILOOP_FILT,
ILONG_FILT,
VBAT_FILT,
VDIFF_FILT,
VCM_FILT,
VBAT_CNT,
V_VLIM_SCALED,
V_VLIM_TRACK,
V_VLIM_MODFEED,
DIAG_P_OUT,
DIAG_COUNT,
ROW0_MAG,
ROW1_MAG,
ROW2_MAG,
ROW3_MAG,
COL0_MAG,
COL1_MAG,
COL2_MAG,
COL3_MAG,
ROW0_2ND_Y1,
ROW1_2ND_Y1,
ROW2_2ND_Y1,
ROW3_2ND_Y1,
COL0_2ND_Y1,
COL1_2ND_Y1,
COL2_2ND_Y1,
COL3_2ND_Y1,
ROW0_2ND_Y2,
ROW1_2ND_Y2,
ROW2_2ND_Y2,
ROW3_2ND_Y2,
COL0_2ND_Y2,
COL1_2ND_Y2,
COL2_2ND_Y2,
COL3_2ND_Y2,
DTMF_IN,
DTMFDTF_D2_1,
DTMFDTF_D1_1,
DTMFDTF_OUT_1,
DTMFDTF_D2_2,
DTMFDTF_D1_2,
DTMFDTF_OUT_2,
DTMFDTF_D2_3,
DTMFDTF_D1_3,
DTMFDTF_OUT_3,
DTMFDTF_OUT,
DTMFLPF_D2_1,
DTMFLPF_D1_1,
DTMFLPF_OUT_1,
DTMFLPF_D2_2,
DTMFLPF_D1_2,
DTMFLPF_OUT_2,
DTMF_ROW,
DTMFHPF_D2_1,
DTMFHPF_D1_1,
DTMFHPF_OUT_1,
DTMFHPF_D2_2,
DTMFHPF_D1_2,
DTMFHPF_OUT_2,
DTMF_COL,
ROW_POWER,
COL_POWER,
GP_TIMER,
SPR_INTERP_DIF,
SPR_INTERP_DIF_OUT,
SPR_INTERP_INT,
SPR_CNT,
ROW0_Y1,
ROW0_Y2,
ROW1_Y1,
ROW1_Y2,
ROW2_Y1,
ROW2_Y2,
ROW3_Y1,
ROW3_Y2,
COL0_Y1,
COL0_Y2,
COL1_Y1,
COL1_Y2,
COL2_Y1,
COL2_Y2,
COL3_Y1,
COL3_Y2,
ROWMAX_MAG,
COLMAX_MAG,
ROW0_2ND_MAG,
COL0_2ND_MAG,
ROW_THR,
COL_THR,
OSC1_Y,
OSC2_Y,
OSC1_X,
OSC1_COEFF,
OSC2_X,
OSC2_COEFF,
RXACIIR_D2_1,
RXACIIR_OUT_1,
RXACIIR_D2_2,
RXACIIR_D1_2,
RXACIIR_OUT_2,
RXACIIR_D2_3,
RXACIIR_D1_3,
RXACIIR_OUT,
RXACIIR_OUT_3,
TXACCOMB_D1,
TXACCOMB_D2,
TXACCOMB_D3,
TXACSINC_OUT,
TXACHPF_D1_2,
TXACHPF_D2_1,
TXACHPF_D2_2,
TXACHPF_OUT,
TXACHPF_OUT_1,
TXACHPF_OUT_2,
TXACIIR_D2_1,
TXACIIR_OUT_1,
TXACIIR_D2_2,
TXACIIR_D1_2,
TXACIIR_OUT_2,
TXACIIR_D2_3,
TXACIIR_D1_3,
TXACIIR_OUT_3,
TXACIIR_OUT,
ECIIR_D1,
ECIIR_D2,
EC_DELAY1,
EC_DELAY2,
EC_DELAY3,
EC_DELAY4,
EC_DELAY5,
EC_DELAY6,
EC_DELAY7,
EC_DELAY8,
EC_DELAY9,
EC_DELAY10,
EC_DELAY11,
ECHO_EST,
EC_OUT,
TESTFILT_OUT_1,
TESTFILT_D1_1,
TESTFILT_D2_1,
TESTFILT_OUT_2,
TESTFILT_D1_2,
TESTFILT_D2_2,
TESTFILT_OUT_3,
TESTFILT_D1_3,
TESTFILT_D2_3,
TESTFILT_PEAK,
TESTFILT_ABS,
TESTFILT_MEANACC,
TESTFILT_COUNT,
TESTFILT_NO_OFFSET,
RING_X,
RING_Y,
RING_INT,
RING_Y_D1,
RING_DIFF,
RING_DELTA,
WTCHDOG_CNT,
RING_WAVE,
RRD2LINEFEED_CNT,
ONEKHZ_COUNT,
TX2100_Y1,
TX2100_Y2,
TX2100_MAG,
RX2100_Y1,
RX2100_Y2,
RX2100_MAG,
TX2100_POWER,
RX2100_POWER,
TX2100_IN,
RX2100_IN,
RINGTRIP_COUNT,
RINGTRIP_DC1,
RINGTRIP_DC2,
RINGTRIP_AC1,
RINGTRIP_AC2,
RINGTRIP_AC_COUNT,
RINGTRIP_DC_COUNT,
RINGTRIP_AC_RESULT,
RINGTRIP_DC_RESULT,
RINGTRIP_ABS,
TXACEQ_OUT,
LCR_DBI_CNT,
BAT_DBI_CNT,
LONG_DBI_CNT,
TXACEQ_DELAY3,
TXACEQ_DELAY2,
TXACEQ_DELAY1,
RXACEQ_DELAY3,
RXACEQ_DELAY2,
RXACEQ_DELAY1,
RXACEQ_IN,
TXDCCOMB_D1,
TXDCCOMB_D2,
TXDCSINC_OUT,
RXACDIFF_D1,
DC_NOTCH_1,
DC_NOTCH_2,
DC_NOTCH_OUT,
DC_NOTCH_SCALED,
V_FEED_IN,
I_TAR,
CONST_VLIM,
UNITY,
TXACNOTCH_1,
TXACNOTCH_2,
TXACNOTCH_OUT,
ZSYNTH_1,
ZSYNTH_2,
ZSYNTH_OUT_1,
TXACD2_1_0,
TXACD2_1_1,
TXACD2_1_2,
TXACD2_1_3,
TXACD2_1_4,
TXACD2_1_5,
TXACD2_1_OUT,
TXACD2_2_0,
TXACD2_2_1,
TXACD2_2_2,
TXACD2_2_3,
TXACD2_2_4,
TXACD2_2_5,
TXACD2_2_OUT,
TXACD2_3_0,
TXACD2_3_1,
TXACD2_3_2,
TXACD2_3_3,
TXACD2_3_4,
TXACD2_3_5,
TXACD2_3_OUT,
RXACI2_1_1,
RXACI2_1_2,
RXACI2_1_3,
RXACI2_1_4,
RXACI2_1_OUT,
RXACI2_2_1,
RXACI2_2_2,
RXACI2_2_3,
RXACI2_2_4,
RXACI2_2_OUT,
RXACI2_3_1,
RXACI2_3_2,
RXACI2_3_3,
RXACI2_3_4,
RXACI2_3_OUT,
TXACCOMP1,
TXACCOMP_OUT,
RXACCOMP1,
RXACCOMP_OUT,
RXACHPF_D1_2,
RXACHPF_D2_1,
RXACHPF_D2_2,
RXACHPF_OUT,
RXACHPF_OUT_1,
RXACHPF_OUT_2,
RXACEQ_OUT,
METER_I_1,
METER_I_OUT,
METER_LPF_1,
METER_LPF_2,
METER_LPF_OUT_1,
METER_BP_1,
METER_BP_2,
METER_BP_OUT,
METER_SRC_OUT,
PMDIFF_D1,
PMDIFF_D2,
RING_LPF_1,
RING_LPF_2,
RING_LPF_OUT,
RING_INTERP_DIFF,
RING_INTERP_DIFF_OUT,
RING_INTERP_INT,
RING_INTERP_INT_OUT,
V_ILIM_TRACK,
V_RFEED_TRACK,
LF_SPEEDUP_CNT,
DC_SPEEDUP_CNT,
AC_SPEEDUP_CNT,
LCR_SPEEDUP_CNT,
CM_SPEEDUP_CNT,
DC_SPEEDUP_MASK,
ZSYNTH_IN,
I_TAR_SAVE,
V_TR_MAX,
V_TR_MAX_TEMP,
COUNTER_VTR,
I_RING_AVG,
COUNTER_IRING,
COMP_RATIO,
MADC_VBAT_DIV2,
VDIFF_PK_T,
PEAK_CNT,
CM_DBI_CNT,
VCM_LAST,
VBATL_SENSE,
VBATH_SENSE,
VBATR_SENSE,
BAT_SETTLE_CNT,
VBAT_TGT,
VBAT_REQ,
VCM_HIRES,
VCM_LORES,
ILOOP1,
ILONG2,
ITIP1,
IRING1,
CAL_TEMP1,
CAL_TEMP2,
CAL_TEMP3,
CAL_TEMP4,
CAL_TEMP5,
CAL_TEMP6,
CAL_TEMP7,
CMRR_DIVISOR,
CMRR_REMAINDER,
CMRR_Q_PTR,
CAL_LKG_DWN_C0,
CAL_LKG_DWN_V0,
CAL_LKG_DWN_CN,
CAL_LKG_DWN_VN,
CAL_LKG_DWN_VLSB,
CAL_LKG_DWN_ILSB,
CAL_LKG_DWN_DACCODE,
CAL_LKG_DWN_ICALC,
CAL_ONHK_Z,
CAL_LB_SETTLE,
CAL_DECLPF_V0,
CAL_DECLPF_V1,
CAL_DECLPF_V2,
CAL_GOERTZEL_V0,
CAL_GOERTZEL_V1,
CAL_DECLPF_Y,
CAL_GOERTZEL_Y,
P_HVIC,
VBATL_MIRROR,
VBATH_MIRROR,
VBATR_MIRROR,
DIAG_EX1_OUT,
DIAG_EX2_OUT,
DIAG_DMM_V_OUT,
DIAG_DMM_I_OUT,
DIAG_P,
DIAG_LPF_V,
DIAG_LPF_I,
DIAG_TONE_FLAG,
ILOOP1_LAST,
RING_ENTRY_VOC,
MADC_VBAT_LAST,
DC_NOTCH_LAST,
EZSYNTH_1,
EZSYNTH_2,
ZSYNTH_OUT,
CMRR,
CAL_SUBSTATE,
CAL_STATE_DCDAC,
UNUSED424,
UNUSED425,
UNUSED426,
UNUSED427,
UNUSED428,
UNUSED429,
UNUSED430,
UNUSED431,
UNUSED432,
UNUSED433,
UNUSED434,
UNUSED435,
UNUSED436,
UNUSED437,
UNUSED438,
UNUSED439,
UNUSED440,
UNUSED441,
UNUSED442,
UNUSED443,
UNUSED444,
UNUSED445,
UNUSED446,
UNUSED447,
UNUSED448,
UNUSED449,
UNUSED450,
UNUSED451,
UNUSED452,
UNUSED453,
UNUSED454,
UNUSED455,
UNUSED456,
UNUSED457,
UNUSED458,
UNUSED459,
UNUSED460,
UNUSED461,
UNUSED462,
UNUSED463,
UNUSED464,
UNUSED465,
UNUSED466,
UNUSED467,
UNUSED468,
UNUSED469,
UNUSED470,
UNUSED471,
UNUSED472,
UNUSED473,
UNUSED474,
UNUSED475,
UNUSED476,
UNUSED477,
UNUSED478,
UNUSED479,
UNUSED480,
UNUSED481,
UNUSED482,
UNUSED483,
UNUSED484,
UNUSED485,
UNUSED486,
UNUSED487,
UNUSED488,
UNUSED489,
UNUSED490,
UNUSED491,
UNUSED492,
UNUSED493,
UNUSED494,
UNUSED495,
UNUSED496,
UNUSED497,
UNUSED498,
UNUSED499,
UNUSED500,
UNUSED501,
UNUSED502,
UNUSED503,
UNUSED504,
UNUSED505,
UNUSED506,
UNUSED507,
UNUSED508,
UNUSED509,
UNUSED510,
UNUSED511,
MINUS_ONE,
ILOOPLPF,
ILONGLPF,
BATLPF,
VDIFFLPF,
VCMLPF,
TXACIIR_B0_1,
TXACIIR_B1_1,
TXACIIR_A1_1,
TXACIIR_B0_2,
TXACIIR_B1_2,
TXACIIR_B2_2,
TXACIIR_A1_2,
TXACIIR_A2_2,
TXACIIR_B0_3,
TXACIIR_B1_3,
TXACIIR_B2_3,
TXACIIR_A1_3,
TXACIIR_A2_3,
TXACHPF_B0_1,
TXACHPF_B1_1,
TXACHPF_A1_1,
TXACHPF_B0_2,
TXACHPF_B1_2,
TXACHPF_B2_2,
TXACHPF_A1_2,
TXACHPF_A2_2,
TXACHPF_GAIN,
TXACEQ_C0,
TXACEQ_C1,
TXACEQ_C2,
TXACEQ_C3,
TXACGAIN,
RXACGAIN,
RXACEQ_C0,
RXACEQ_C1,
RXACEQ_C2,
RXACEQ_C3,
RXACIIR_B0_1,
RXACIIR_B1_1,
RXACIIR_A1_1,
RXACIIR_B0_2,
RXACIIR_B1_2,
RXACIIR_B2_2,
RXACIIR_A1_2,
RXACIIR_A2_2,
RXACIIR_B0_3,
RXACIIR_B1_3,
RXACIIR_B2_3,
RXACIIR_A1_3,
RXACIIR_A2_3,
ECFIR_C2,
ECFIR_C3,
ECFIR_C4,
ECFIR_C5,
ECFIR_C6,
ECFIR_C7,
ECFIR_C8,
ECFIR_C9,
ECIIR_B0,
ECIIR_B1,
ECIIR_A1,
ECIIR_A2,
DTMFDTF_B0_1,
DTMFDTF_B1_1,
DTMFDTF_B2_1,
DTMFDTF_A1_1,
DTMFDTF_A2_1,
DTMFDTF_B0_2,
DTMFDTF_B1_2,
DTMFDTF_B2_2,
DTMFDTF_A1_2,
DTMFDTF_A2_2,
DTMFDTF_B0_3,
DTMFDTF_B1_3,
DTMFDTF_B2_3,
DTMFDTF_A1_3,
DTMFDTF_A2_3,
DTMFDTF_GAIN,
DTMFLPF_B0_1,
DTMFLPF_B1_1,
DTMFLPF_B2_1,
DTMFLPF_A1_1,
DTMFLPF_A2_1,
DTMFLPF_B0_2,
DTMFLPF_B1_2,
DTMFLPF_B2_2,
DTMFLPF_A1_2,
DTMFLPF_A2_2,
DTMFLPF_GAIN,
DTMFHPF_B0_1,
DTMFHPF_B1_1,
DTMFHPF_B2_1,
DTMFHPF_A1_1,
DTMFHPF_A2_1,
DTMFHPF_B0_2,
DTMFHPF_B1_2,
DTMFHPF_B2_2,
DTMFHPF_A1_2,
DTMFHPF_A2_2,
DTMFHPF_GAIN,
POWER_GAIN,
GOERTZEL_GAIN,
MODEM_GAIN,
HOTBIT1,
HOTBIT0,
ROW0_C1,
ROW1_C1,
ROW2_C1,
ROW3_C1,
COL0_C1,
COL1_C1,
COL2_C1,
COL3_C1,
ROW0_C2,
ROW1_C2,
ROW2_C2,
ROW3_C2,
COL0_C2,
COL1_C2,
COL2_C2,
COL3_C2,
SLOPE_VLIM,
SLOPE_RFEED,
SLOPE_ILIM,
SLOPE_RING,
SLOPE_DELTA1,
SLOPE_DELTA2,
V_VLIM,
V_RFEED,
V_ILIM,
CONST_RFEED,
CONST_ILIM,
I_VLIM,
DC_DAC_GAIN,
VDIFF_TH,
NOTCH_B0,
NOTCH_B1,
NOTCH_B2,
NOTCH_A1,
NOTCH_A2,
ZSYNTH_B0,
ZSYNTH_B1,
ZSYNTH_B2,
ZSYNTH_A1,
ZSYNTH_A2,
RXACHPF_B0_1,
RXACHPF_B1_1,
RXACHPF_A1_1,
RXACHPF_B0_2,
RXACHPF_B1_2,
RXACHPF_B2_2,
RXACHPF_A1_2,
RXACHPF_A2_2,
RXACHPF_GAIN,
MASK7LSB,
METER_LPF_B0,
METER_LPF_B1,
METER_LPF_B2,
METER_LPF_A1,
METER_LPF_A2,
METER_SIG_0,
METER_SIG_1,
METER_SIG_2,
METER_SIG_3,
METER_SIG_4,
METER_SIG_5,
METER_SIG_6,
METER_SIG_7,
METER_SIG_8,
METER_SIG_9,
METER_SIG_10,
METER_SIG_11,
METER_SIG_12,
METER_SIG_13,
METER_SIG_14,
METER_SIG_15,
METER_BP_B0,
METER_BP_B1,
METER_BP_B2,
METER_BP_A1,
METER_BP_A2,
PM_AMP_THRESH,
PM_GAIN,
RING_LPF_B0,
RING_LPF_B1,
RING_LPF_B2,
RING_LPF_A1,
RING_LPF_A2,
LCRDBI,
LONGDBI,
VBAT_TIMER,
LF_SPEEDUP_TIMER,
DC_SPEEDUP_TIMER,
AC_SPEEDUP_TIMER,
LCR_SPEEDUP_TIMER,
CM_SPEEDUP_TIMER,
VCM_TH,
AC_SPEEDUP_TH,
SPR_SIG_0,
SPR_SIG_1,
SPR_SIG_2,
SPR_SIG_3,
SPR_SIG_4,
SPR_SIG_5,
SPR_SIG_6,
SPR_SIG_7,
SPR_SIG_8,
SPR_SIG_9,
SPR_SIG_10,
SPR_SIG_11,
SPR_SIG_12,
SPR_SIG_13,
SPR_SIG_14,
SPR_SIG_15,
SPR_SIG_16,
SPR_SIG_17,
SPR_SIG_18,
COUNTER_VTR_VAL,
CONST_028,
CONST_032,
CONST_038,
CONST_046,
COUNTER_IRING_VAL,
GAIN_RING,
RING_HYST,
COMP_Z,
CONST_115,
CONST_110,
CONST_105,
CONST_100,
CONST_095,
CONST_090,
CONST_085,
V_RASUM_IDEAL,
CONST_ONE,
VCM_OH,
VCM_RING,
VCM_HYST,
VOV_GND,
VOV_BAT,
VOV_RING_BAT,
CM_DBI,
RTPER,
P_TH_HVIC,
P_TH_Q1256,
P_TH_Q34,
COEF_P_HVIC,
COEF_P_OFFLD,
COEF_Q34,
R_OFFLOAD,
R_63,
BAT_HYST,
BAT_DBI,
VBATL_EXPECT,
VBATH_EXPECT,
VBATR_EXPECT,
BAT_SETTLE,
VBAT_IRQ_TH,
MADC_VTIPC_OS,
MADC_VRINGC_OS,
MADC_VBAT_OS,
MADC_VLONG_OS,
MADC_VBLKRNG_OS,
MADC_IBLKRNG_OS,
MADC_ILONG_OS,
MADC_ISNS_STDBY_OS,
MADC_ISNS_OS,
MADC_ILOOP_OS,
MADC_SCALE_ILOOP,
MADC_VBLKRNG_DC,
MADC_IBLKRNG_DC,
DC_ADC_OS,
CAL_UNITY,
CAL_CMRR_N,
CAL_CMRR_NINV,
ACADC_OFFSET,
ACDAC_OFFSET,
CAL_DCDAC_CODE,
CAL_DCDAC_15MA,
CAL_LKG_TSETTLE,
CAL_LKG_IREF100,
CAL_LKG_LIM100UA,
CAL_LKG_VREF25,
CAL_LKG_VLSB_0_INV,
CAL_LKG_RDCSNS_EFF,
CAL_LKG_RDCOFF_EFF,
CAL_LKG_CODE_OS,
CAL_LKG_VMAX_THR,
CAL_LB_TSQUELCH,
CAL_LB_TCHARGE,
CAL_LB_TSETTLE0,
CAL_GOERTZEL_DLY,
CAL_GOERTZEL_ALPHA,
CAL_DECLPF_K,
CAL_DECLPF_B1,
CAL_DECLPF_B2,
CAL_DECLPF_A1,
CAL_DECLPF_A2,
CAL_ACADC_THRL,
CAL_ACADC_THRH,
CAL_ACADC_TSETTLE,
DTROW0TH,
DTROW1TH,
DTROW2TH,
DTROW3TH,
DTCOL0TH,
DTCOL1TH,
DTCOL2TH,
DTCOL3TH,
DTFTWTH,
DTRTWTH,
DTROWRTH,
DTCOLRTH,
DTROW2HTH,
DTCOL2HTH,
DTMINPTH,
DTHOTTH,
RXPWR,
TXPWR,
RXMODPWR,
TXMODPWR,
FSKFREQ0,
FSKFREQ1,
FSKAMP0,
FSKAMP1,
FSK01,
FSK10,
VOCDELTA,
VOCLTH,
VOCHTH,
RINGOF,
RINGFR,
RINGAMP,
RINGPHAS,
RTDCTH,
RTACTH,
RTDCDB,
RTACDB,
RTCOUNT,
LCROFFHK,
LCRONHK,
LCRMASK,
LCRMASK_POLREV,
LCRMASK_STATE,
LCRMASK_LINECAP,
LONGHITH,
LONGLOTH,
IRING_LIM,
RRD_DELAY,
RRD_DELAY2,
DIAG_LPF_8K,
DIAG_LPF_128K,
DIAG_INV_N,
DIAG_GAIN,
DIAG_G_CAL,
DIAG_OS_CAL,
SPR_GAIN_TRIM,
MADC_VBAT_HYST,
AC_DAC_GAIN,
STDBY_THRLO,
STDBY_THRHI,
AC_DAC_GAIN0,
EZSYNTH_B0,
EZSYNTH_B1,
EZSYNTH_B2,
EZSYNTH_A1,
EZSYNTH_A2,
AC_ADC_GAIN,
UNUSED881,
UNUSED882,
UNUSED883,
UNUSED884,
UNUSED885,
UNUSED886,
UNUSED887,
UNUSED888,
UNUSED889,
UNUSED890,
UNUSED891,
UNUSED892,
UNUSED893,
UNUSED894,
UNUSED895,
VOV_RING_GND,
P_TH_OFFLD,
UNUSED898,
UNUSED899,
UNUSED900,
ADAP_RING_MIN_I,
UNUSED902,
UNUSED903,
UNUSED904,
UNUSED905,
RXACGAIN_SAVE,
UNUSED907,
UNUSED908,
UNUSED909,
UNUSED910,
UNUSED911,
UNUSED912,
UNUSED913,
UNUSED914,
UNUSED915,
UNUSED916,
UNUSED917,
UNUSED918,
UNUSED919,
UNUSED920,
UNUSED921,
UNUSED922,
UNUSED923,
UNUSED924,
UNUSED925,
UNUSED926,
UNUSED927,
UNUSED928,
UNUSED929,
UNUSED930,
UNUSED931,
UNUSED932,
UNUSED933,
UNUSED934,
UNUSED935,
UNUSED936,
UNUSED937,
UNUSED938,
UNUSED939,
UNUSED940,
UNUSED941,
UNUSED942,
UNUSED943,
UNUSED944,
UNUSED945,
UNUSED946,
UNUSED947,
UNUSED948,
UNUSED949,
UNUSED950,
UNUSED951,
UNUSED952,
UNUSED953,
UNUSED954,
UNUSED955,
UNUSED956,
UNUSED957,
UNUSED958,
UNUSED959,
UNUSED960,
UNUSED961,
UNUSED962,
UNUSED963,
UNUSED964,
UNUSED965,
UNUSED966,
UNUSED967,
UNUSED968,
UNUSED969,
UNUSED970,
UNUSED971,
UNUSED972,
UNUSED973,
UNUSED974,
UNUSED975,
UNUSED976,
UNUSED977,
UNUSED978,
UNUSED979,
UNUSED980,
UNUSED981,
UNUSED982,
UNUSED983,
UNUSED984,
UNUSED985,
UNUSED986,
UNUSED987,
UNUSED988,
UNUSED989,
UNUSED990,
UNUSED991,
UNUSED992,
UNUSED993,
UNUSED994,
UNUSED995,
UNUSED996,
UNUSED997,
UNUSED998,
UNUSED999,
UNUSED1000,
UNUSED1001,
UNUSED1002,
UNUSED1003,
UNUSED1004,
UNUSED1005,
UNUSED1006,
UNUSED1007,
UNUSED1008,
UNUSED1009,
UNUSED1010,
UNUSED1011,
UNUSED1012,
UNUSED1013,
UNUSED1014,
UNUSED1015,
UNUSED1016,
UNUSED1017,
UNUSED1018,
UNUSED1019,
UNUSED1020,
UNUSED1021,
UNUSED1022,
UNUSED1023
};

enum {
    PD_BIAS = 1413,
    PD_VBAT_SNS = 1418,
    MADC_LOOP_MAN = 1445,
    HVIC_CNTL_MAN = 1451,
    CAL_TRNRD_DACT = 1458,
    CAL_TRNRD_DACR,
    CMDAC_FWD = 1476,
    CMDAC_REV
};


#endif
