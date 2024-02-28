/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*  \file     Can_30_Mcan.c / Can_30_Mcan_Irq.c
 *  \brief    Implementation of the CAN driver
 *  \details  see functional description below
 *
 *********************************************************************************************************************/
/* ***************************************************************************
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Version Author Description
| ---------  ------- ------ --------------------------------------------------
| 2012-04-13 1.00.00  Her - Initial revision (alpha version)
| 2012-08-28 1.00.01  Her - Initial revision (beta version )
| 2013-02-01 1.01.00  Her - ESCAN00065098: Initial release version
| 2013-03-18 1.02.00  Her - ESCAN00065594: Additional (High End) features
| 2013-06-03 1.03.00  Her - ESCAN00068062: Rx Dedicated Buffers support
|                     Her - ESCAN00068305: Reduce RAM resource consumption by tailoring the configuration
|                     Her - ESCAN00068956: CAN messages to be transmitted are missing
| 2013-07-26 1.03.80  Her - ESCAN00069335: CAN-FD Bitrate Switching Prototype
| 2013-08-08 1.04.00  Her - ESCAN00069461: Further transmissions are not accepted but a memory violation is reported
|                     Her - ESCAN00069673: Conditional ECC initialization of the embedded CAN Message RAM
|                     Her - ESCAN00069937: GHS support
| 2013-09-27 1.05.00  Her - ESCAN00070770: Use Overrun in Status
|                     Her - ESCAN00070771: Compiler error: "finishRxFullCan" undefined
| 2013-10-17 1.06.00  Her - ESCAN00070952: Support customer specific post initialization
|                     Her - ESCAN00071166: AR4-328: Predefined Runtime Measurement Points
|                     Her - ESCAN00071326: Delayed overrun notification
|                     Her - ESCAN00071493: Message processed in wrong (interrupt or task ) context 
| 2013-11-20 1.07.00  Her - ESCAN00073084: Improvements on derivative handling
| 2014-02-12 1.08.00  Her - ESCAN00073939: Enhanced CAN-FD (Full) support
| 2014-03-17 1.09.00  Her - ESCAN00074327: Support embedded assembler for DiabData
| 2014-06-13 1.10.00  Her - ESCAN00076201: Support MPC5777C derivative
| 2014-10-30 2.00.00  Her - ESCAN00079193: AR4-R11 Update using ComStackLib
| 2015-01-30 2.01.00  Her - ESCAN00079800: Added CBD support (for Traveo derivative)
| 2015-02-20 2.02.00  Her - ESCAN00081372: AR4-R11 Update using ComStackLib (support Spc58xx)
| 2015-03-18 2.02.01  Her - ESCAN00081884: compile error
| 2015-04-02 2.02.02  Her - ESCAN00082190: Power Down (sleep mode) correction
|                     Her - ESCAN00082291: Memory access misalignment exception
| 2015-04-16 2.02.03  Her - ESCAN00082521: Extended Id Type not correct detected
|                     Her - ESCAN00082722: CANbedded only: Memory access misalignment exception
|                     Her - ESCAN00082724: Speed up TxCopyToCan
| 2015-07-06 2.02.04  Her - ESCAN00083815: Tx Confirmation gets lost
|                     Her - ESCAN00088481: Compiler error occurs
| 2015-07-30 2.03.00  Her - ESCAN00084313: Support MCAN Core release 3.1.0 ff.
|                     Her - ESCAN00084515: Use generated FullCAN masks
|                     Her - ESCAN00084650: Support ARM Cortex-Mx Data Memory Barrier
|                     Her - ESCAN00084814: Compiler error due to nested macro construction
| 2015-10-09 2.03.01  Her - ESCAN00085813: Endless loop during reception of messages
| 2015-11-11 2.04.00  Her - ESCAN00086128: Dynamic Rx FullCAN Message filtering failure
|                     Her - ESCAN00086359: Bosch Errata - support of workaround
| 2015-12-02 2.04.01  Her - ESCAN00086934: Support Keil compiler
|                     Her - ESCAN00087003: Missing pre-processor constants
|                     Her - ESCAN00087005: Re-Initialization fails
|                     Her - ESCAN00087056: Erroneous cancel notification
| 2015-12-03 2.05.00  Her - ESCAN00087255: Restructured due to AR4/R14
|                     Her - ESCAN00087256: Compile warning (erratum_013)
| 2016-01-21 2.05.01  Her - ESCAN00087586: Memory overwrite during RAM check
|                     Her - ESCAN00087612: Wrong mailbox checked
| 2016-02-19 2.06.00  Her - ESCAN00088392: Support 8 CAN channels (only Organi affected)
|                     Her - ESCAN00088519: Support more than 255 Dynamic Rx Objects
|                     Her - ESCAN00088756: Reserved bits may only be written with "0"
|                     Her - ESCAN00088813: Incorrect switching between Normal CAN and CAN-FD
|                     Her - ESCAN00089048: Support Mirror Mode (CBD)
|                     Her - ESCAN00089049: Assertion causes compile error
|                     Her - ESCAN00089131: Dynamic Rx objects compile error
| 2016-04-12 2.06.01  Her - ESCAN00089406: AR4/R14 adaptations to AR3
| 2016-04-22 2.06.02  Her - ESCAN00089587: Memory overwrite during RAM check
|                     Her - ESCAN00089610: CAN-ID Rx access macros
| 2016-04-28 2.07.00  Her - ESCAN00089867: MISRA improvements
|            2.08.xx  Her - ESCAN00092200: Will be used for Silent branch
| 2016-06-22 2.09.00  Her - ESCAN00090584: Function call with missing parameter
|                     Her - ESCAN00090761: Generated filter for dynamic Rx objects must be disabled by default
|                     Her - ESCAN00090825: Omit obsolete cancellation delay 
|                     Her - ESCAN00091096: Support AR4/R16
|                     Her - ESCAN00091328: Support Mirror Mode (ASR)
|                     Her - ESCAN00091329: CAN-FD Bit Rate Switch always active
| 2016-08-24 2.10.00  Her - ESCAN00091681: Support dynamic MCAN Revision adaptation
|                     Her - ESCAN00092569: Compiler error: identifier "pduInfo_var_id" is undefined
|                     Her - ESCAN00092315: Compiler warning: function "CanLL_30_Mcan_WakeUpHandling" was declared but never referenced
|                     Her - ESCAN00092713: Preprocessor parse error
| 2016-10-28 2.11.00  Pl  - ESCAN00092591: Support Aurix Plus with AR4/R16
| 2016-11-24 2.12.00  Her - ESCAN00092995: CAN-FD message without BRS will not be received
|                     Her - ESCAN00093167: Compiler error "maybe misaligned memory access"
|                     Pl  - ESCAN00093244: CAN Interrupt lock work not correct (Aurix Plus only)
| 2017-01-25 2.13.00  Pl  - ESCAN00093483: CAN communication only possible with channels CAN0, CAN4, CAN8 (Aurix Plus only)
|                     Pl  - ESCAN00093726: Support C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL (Aurix Plus only)
| 2017-02-02 2.13.01  Her - ESCAN00093849: CAN data bytes containing wrong content 
|                     Her - ESCAN00093852: Support Extended ID Masking
| 2017-03-09 2.14.00  Rse - ESCAN00094323: Support TeleChips Tcc802x derivatives for CANbedded
| 2017-04-19 2.14.01  Pl  - ESCAN00094085: Implementation of workaround for MCMCAN_TC.003_EPN Corruption of transmitted CAN Frame
| 2017-05-10 2.15.00  Her - ESCAN00094883: Improper workaround for MCAN Erratum #10 
| 2017-05-11 2.16.00  Her - ESCAN00094518: MCAN SafeBSW Support
| 2017-08-10 2.16.01  Her - STORYC-2289  : FEAT-2738 (silent mode), FEAT-2888 (selective multiplexedTx)
| 2017-08-25 2.17.00  Pl  - STORYC-2250  : M-CAN: Support new platform Telemaco3P with ARM DS5 compiler with CFG5
|                     Her - STORYC-2289  : Support derivatives TCC8021, SAMCA1E for CANbedded
| 2017-09-12 2.20.00  Her - STORYC-2729  : Support derivatives SPC5777M with AR4/R19, MCAN SafeBSW Support
|                     Her - STORYC-2780  : Stop Mode transition behaviour improved
|                     Her - ESCAN00097246: Pending Tx requests block transition to stop mode
|                     Her - ESCAN00097151: Incomplete Mirror Data
| 2017-10-27 2.21.00  Her - STORYC-2729  : MCAN SafeBSW Support (continued and ExtRamCheck Beta)
| 2017-12-01 3.00.00  Pl  - STORYC-3153  : Add infixing to support multiple driver instanced
|                     Her - STORYC-3325  : AR3/GENy adaptation
|                     Huo - ESCAN00098069: Add external PIA
| 2018-01-25 3.01.00  Hum - STORYC-4102  : Support Extended Ram Check
|                     Her - ESCAN00097602: OS assertion "CAN interrupt lost"
|                     Hum - ESCAN00098469: TCF Init enabled regardless of CANCEL_IN_HW
|                     Hum - ESCAN00098470: TDCR write not performed correctly in correspondance with dynamic MCAN revision. CAN_BOSCH_ERRATUM_012
|                     Hum - ESCAN00098467: Missing ampersand in RAM check resulting in a DET error.
| 2018-03-07 3.02.00  Pl  - STORYC-4771  : Support TC38X for Tricore
|                     Her - ESCAN00098887: static variable "mirrorData" linker section issue, 
|                     Her - ESCAN00098890: use kCan_30_McanLoopStop instead of kCan_30_McanLoopSleep (AR3 issue)
| 2018-09-17 4.00.00  Her - STORYC-6298  : MCAN RI 2.0 adaptation
|                     Hum - STORYC-6490  : Support for Traveo2
| 2018-10-26 4.00.01  Yoe - ESCAN00101172: Compiler error: wrong number of arguments in call to CanReInit
| 2019-03-14 5.00.00  Her - STORYC-7220  : from CBD/RI2.0 to AR/R21,R22 adaptation
|                     Hum - STORYC-8107  : Adapations for TriCore R22
|                     Hum - STORYC-7923  : Merge version 3-03-00 - 3-09-01:
|                                          - STORYC-4711  : Support TDA3x additional registers
|                                          - STORYC-4584  : Infixing improvements
|                                          - STORYC-5038  : Support GNU Compiler for TC38X
|                                          - ESCAN00099574: Adaptation LL for CANBEDDED
|                                          - STORYC-5679  : Support for Visconti5
|                                          - STORYC-5763  : Support extended ram check for TDA3x
|                                          - STORYC-6686  : Support for Traveo2
|                                          - STORYC-6964  : Support SafeBSW for RH850
|                                          - STORYC-7393  : Support SafeBsw for Tricore TC3xx
|                                          - STORYC-7392  : Support Extended RAM check for Tricore TC3xx
|                                          - ESCAN00101336: Rx BasicCan not deactivated when hwMailbox is corrupted
|                                          - ESCAN00101842: Extended Ram Check does not validate all configured registers
|                                          - STORYC-7578  : Support for ATSAME51/54 derivatives (STORYC-7633 for CANBEDDED)
|                                          - ESCAN00102628: Can controller does not leave NISO mode
| 2019-04-12 5.01.00  Hum - ESCAN00102829: Can driver causes hardware exception
|                     Hum - ESCAN00102850: Hardware issue "MCMCAN_AI.H001_EPN"
|                     Hum - STORYC-8181  : Support Traveo2 HighEnd
| 2019-04-29 5.02.00  Hum - STORYC-8270  : Support Panasonic AS1
|                     Yoe - STORYC-8139  : Support ARM6 Compiler for STA1385
|                     Yoe - STORYC-8386  : Support MCAN revision 3.0.x and Infixing
|                     Yoe - STORYC-8385  : Support SafeBsw MSR4 R22 ARM32
|                     Yoe - ESCAN00103110: RAM check not executed in the MCAN  message RAM area
|                     Yoe - ESCAN00103135: Remove  support of STA1385_cut1
|                     Hum - ESCAN00103996: Compile error "CAN_E_GENDATA not defined"
| 2019-05-29 5.02.01  Hum - STORYC-8555  : Improve additional functionality handling in Jacinto6, Traveo2 and Visconti5
| 2019-06-17 5.02.02  Hum - ESCAN00103387: Transmit Confirmation function called for wrong mailbox
| 2019-08-21 5.03.00  Pl  - STORYC-8854  : Support for AWR1 RI 2.0 core 3.03.00
|                     Her - ESCAN00103377: Same peripheral region configuration for "CAN_PROTECTED_AREA_CHANNEL" and "CAN_PROTECTED_AREA_GLOBAL"
|                     Hum - ESCAN00104123: CAN driver sends incorrect receive BasicCan handle to CanIf
| 2019-11-10 5.04.00  Hum - CAN-605      : Driver Improvements
|                     Hum - CAN-606      : Message RAM Optimization
|                     Hum - CAN-601      : Support Tx Hw Fifo
|                     Hum - ESCAN00104276: Compile error when using "CanBtpReg()" with Init Post Processing
|                     Hum - ESCAN00104735: Interrupts are unconditionally re-enabled after Can_DisableControllerInterrupts()
|                     Naj - CAN-760      : MISRA Improvements
|                     Red - CAN-784      : Support STM32H742 for R23
| 2020-02-11 5.05.00  Hum - CAN-936      : Support for TriCore in CANbedded
| 2020-04-14 5.06.00  Hum - CAN-865      : TriCore 2G Hardware Message RAM Initialization Support
|                     Naj - CAN-1171     : Support TCC80XX
|                     Pl  - CAN-1279     : MISRA improvements
| 2020-06-03 5.07.00  Hum - CAN-1396     : Support for TDA4 (Jacinto7)
| 2020-09-15 5.08.00  Pl  - ESCAN00106662: Channel Independent TTCAN for CBD
|                     Pl  - CAN-1296     : TraveoII CBD Subsystem Table
|                     Hum - CAN-1678     : Support for TriCore TC3E7 with Diab Compiler
|                     Naj - CAN-1179     : Hardware Object Layout change
|                     Naj - ESCAN00106609: TCC803x CAN Configuration Write Protection
|                     Naj - ESCAN00107330: Verify channel parameter in Interrupt handling
|                     Naj - ESCAN00107331: Support for Tx Delayed FullCAN for Multichannel
|                     Naj - ESCAN00107332: Undesirable Basic CAN deactivation during RAM check
|                     Hum - ESCAN00107394: Wrong base addresses accessed for TDA3x
|                     Hum - ESCAN00107466: Size of generated message RAM table not checked during runtime
| 2020-10-14 5.08.01  Naj - CAN-1514     : Support TDA4 for CANbedded
| 2021-01-11 5.08.02  Meid- CAN-2154     : Reworks for TI platforms
|                     Naj - ESCAN00107521: Hw Loops used in wrong context
|                     Naj - ESCAN00108028: Unexpected CAN interrupt
|                     Hum - CAN-2320     : Remove call to TriCore Safety Endinit registers during initialization
| 2021-05-26 5.09.00  Red - CAN-1251     : Support Virtual Addressing
|                     Pl  - CAN-2442     : Canbedded Dynamic Rx Object RI 2.0
| 2021-06-07 5.09.01  Pl  - ESCAN00109428: Compiler error: kCanIdTypeExt is not a member of initPara
| 2021-06-14 5.09.02  Meid- CANHAL-43    : Improve Switches for CAN Interrupt handling
| 2021-09-01 5.10.00  Hnj - CANHAL-177   : R26 Support of Security Event Reporting
|                     Hnj - CANHAL-456   : Remove r-m-w when writing to TXBAR
| 2021-11-01 5.10.01  Hnj - ESCAN00110335: Virtual addressing not activated when enabled in the generator
|                     Hnj - CANHAL-719   : Added MISRA justification
|                     Hnj - ESCAN00110641: Unhandled interrupt request when a security event is detected
| 2021-11-17 5.10.02  Ped - ESCAN00110742: Error state passive not reported for receive errors
| 2021-12-10 5.10.03  Ped - CANHAL-205   : Support of Security Event Reporting Tricore
| 2022-01-17 5.10.04  Hnj - CANHAL-186   : Add SBWS justification with reference to SMI-833100
|************************************************************************** */

/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_30_MCAN_INTERNAL
#define CAN_30_MCAN_IRQ_SOURCE     /* testability */

#include "Can_30_Mcan.h"
#if defined(V_OSTYPE_OSEK) /* COV_CAN_OS_USAGE */
# include "osek.h"
#endif
/* \trace SPEC-1408 */
#if defined(V_OSTYPE_AUTOSAR) /* COV_CAN_OS_USAGE */
# include "Os.h"
#endif


/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_30_MCAN_COREVERSION           != 0x1000u) /* \trace SPEC-1699, SPEC-3837 */
# error "Header file are inconsistent!"
#endif
#if (CAN_30_MCAN_RELEASE_COREVERSION   != 0x03u)
# error "Header file are inconsistent!"
#endif
#if( DRVCAN_MPC5700MCANASR_VERSION != 0x0510)
# error "Source and Header file are inconsistent!"
#endif

#if( DRVCAN_MPC5700MCANASR_RELEASE_VERSION != 0x04)
# error "Source and Header file are inconsistent!"
#endif

#if defined(CAN_30_MCAN_GEN_Mpc5700McanAsr_VERSION )  /* COV_CAN_VERSION_CHECK */
# if(CAN_30_MCAN_GEN_Mpc5700McanAsr_VERSION != 0x0504)     /* CFG5 */
#  error "Generated Data are inconsistent!"
# endif
#else
# define CAN_30_MCAN_GEN_Mpc5700McanAsr_VERSION         CAN_30_MCAN_GEN_MPC5700MCANASR_VERSION
# if(CAN_30_MCAN_GEN_MPC5700MCANASR_VERSION != 0x0100)
#  error "Generated Data are inconsistent!"
# endif
#endif

#if defined(CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_30_MCAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
V_DEF_30_MCAN_P2CONST (extern, Can_30_Mcan_ConfigType, VAR_INIT, CONST_PBCFG) Can_30_Mcan_ConfigDataPtr; /* PRQA S 3447,3449,3451,3210 */ /* MD_Can_ExternalScope */
# define CAN_30_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/***************************************************************************/
/* Interrupt Service Routine                                               */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_CODE  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* \trace SPEC-1579, SPEC-1395, SPEC-1567 */
/* PRQA S 3614 QAC_Can_3614 */ /* MD_Can_3614_LL */
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
# define CanPhysToLogChannel_0
# define CanPhysToLogChannelIndex_0
# define CanPhysToLogChannel_1
# define CanPhysToLogChannelIndex_1
# define CanPhysToLogChannel_2
# define CanPhysToLogChannelIndex_2
# define CanPhysToLogChannel_3
# define CanPhysToLogChannelIndex_3
# define CanPhysToLogChannel_4
# define CanPhysToLogChannelIndex_4
# define CanPhysToLogChannel_5
# define CanPhysToLogChannelIndex_5
# define CanPhysToLogChannel_6
# define CanPhysToLogChannelIndex_6
# define CanPhysToLogChannel_7
# define CanPhysToLogChannelIndex_7
# define CanPhysToLogChannel_8
# define CanPhysToLogChannelIndex_8
# define CanPhysToLogChannel_9
# define CanPhysToLogChannelIndex_9
# define CanPhysToLogChannel_10
# define CanPhysToLogChannelIndex_10
# define CanPhysToLogChannel_11
# define CanPhysToLogChannelIndex_11
# define CanPhysToLogChannel_12
# define CanPhysToLogChannelIndex_12
# define CanPhysToLogChannel_13
# define CanPhysToLogChannelIndex_13
# define CanPhysToLogChannel_14
# define CanPhysToLogChannelIndex_14
# define CanPhysToLogChannel_15
# define CanPhysToLogChannelIndex_15
# define CanPhysToLogChannel_16
# define CanPhysToLogChannelIndex_16
# define CanPhysToLogChannel_17
# define CanPhysToLogChannelIndex_17
# define CanPhysToLogChannel_18
# define CanPhysToLogChannelIndex_18
# define CanPhysToLogChannel_19
# define CanPhysToLogChannelIndex_19
#else
# define CanPhysToLogChannel_0       kCan_30_McanPhysToLogChannelIndex_0
# define CanPhysToLogChannelIndex_0  kCan_30_McanPhysToLogChannelIndex_0,
# define CanPhysToLogChannel_1       kCan_30_McanPhysToLogChannelIndex_1
# define CanPhysToLogChannelIndex_1  kCan_30_McanPhysToLogChannelIndex_1,
# define CanPhysToLogChannel_2       kCan_30_McanPhysToLogChannelIndex_2
# define CanPhysToLogChannelIndex_2  kCan_30_McanPhysToLogChannelIndex_2,
# define CanPhysToLogChannel_3       kCan_30_McanPhysToLogChannelIndex_3
# define CanPhysToLogChannelIndex_3  kCan_30_McanPhysToLogChannelIndex_3,
# define CanPhysToLogChannel_4       kCan_30_McanPhysToLogChannelIndex_4
# define CanPhysToLogChannelIndex_4  kCan_30_McanPhysToLogChannelIndex_4,
# define CanPhysToLogChannel_5       kCan_30_McanPhysToLogChannelIndex_5
# define CanPhysToLogChannelIndex_5  kCan_30_McanPhysToLogChannelIndex_5,
# define CanPhysToLogChannel_6       kCan_30_McanPhysToLogChannelIndex_6
# define CanPhysToLogChannelIndex_6  kCan_30_McanPhysToLogChannelIndex_6,
# define CanPhysToLogChannel_7       kCan_30_McanPhysToLogChannelIndex_7
# define CanPhysToLogChannelIndex_7  kCan_30_McanPhysToLogChannelIndex_7,
# define CanPhysToLogChannel_8       kCan_30_McanPhysToLogChannelIndex_8
# define CanPhysToLogChannelIndex_8  kCan_30_McanPhysToLogChannelIndex_8,
# define CanPhysToLogChannel_9       kCan_30_McanPhysToLogChannelIndex_9
# define CanPhysToLogChannelIndex_9  kCan_30_McanPhysToLogChannelIndex_9,
# define CanPhysToLogChannel_10       kCan_30_McanPhysToLogChannelIndex_10
# define CanPhysToLogChannelIndex_10  kCan_30_McanPhysToLogChannelIndex_10,
# define CanPhysToLogChannel_11       kCan_30_McanPhysToLogChannelIndex_11
# define CanPhysToLogChannelIndex_11  kCan_30_McanPhysToLogChannelIndex_11,
# define CanPhysToLogChannel_12       kCan_30_McanPhysToLogChannelIndex_12
# define CanPhysToLogChannelIndex_12  kCan_30_McanPhysToLogChannelIndex_12,
# define CanPhysToLogChannel_13       kCan_30_McanPhysToLogChannelIndex_13
# define CanPhysToLogChannelIndex_13  kCan_30_McanPhysToLogChannelIndex_13,
# define CanPhysToLogChannel_14       kCan_30_McanPhysToLogChannelIndex_14
# define CanPhysToLogChannelIndex_14  kCan_30_McanPhysToLogChannelIndex_14,
# define CanPhysToLogChannel_15       kCan_30_McanPhysToLogChannelIndex_15
# define CanPhysToLogChannelIndex_15  kCan_30_McanPhysToLogChannelIndex_15,
# define CanPhysToLogChannel_16       kCan_30_McanPhysToLogChannelIndex_16
# define CanPhysToLogChannelIndex_16  kCan_30_McanPhysToLogChannelIndex_16,
# define CanPhysToLogChannel_17       kCan_30_McanPhysToLogChannelIndex_17
# define CanPhysToLogChannelIndex_17  kCan_30_McanPhysToLogChannelIndex_17,
# define CanPhysToLogChannel_18       kCan_30_McanPhysToLogChannelIndex_18
# define CanPhysToLogChannelIndex_18  kCan_30_McanPhysToLogChannelIndex_18,
# define CanPhysToLogChannel_19       kCan_30_McanPhysToLogChannelIndex_19
# define CanPhysToLogChannelIndex_19  kCan_30_McanPhysToLogChannelIndex_19,
#endif
/* PRQA  L:QAC_Can_3614 */



#if defined( C_30_MCAN_ENABLE_ISR_MANDATORY )  /* ISR necessary; no pure polling configuration */

# if defined( C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN ) /* COV_CAN_HW_SPECIFIC */
/* **************************************************************************
| NAME:             Can_30_McanIsr_MCAN
| CALLED BY:        HLL, ASR: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|
|  Attention:  has to be replaced with the name of the ISR. 
|              Naming conventions: with Name = "", "Rx", "Tx", "RxTx", "Wakeup", "Status" 
|  The name of the ISR will always have a channel index at the end. Even in single channel
|  systems.
************************************************************************** */
/* CODE CATEGORY 1 START */
/*!
 * Internal comment removed.
 *
 *
 */
#  if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#   if defined (osdIsrCanIsrCat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#    if (osdIsrCanIsrCat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( Can_30_McanIsr_MCAN ) /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#  else
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#    if (osdIsrCanIsrCat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if defined ( C_30_MCAN_ENABLE_ISRVOID )
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_MCAN( void )
#   else
#    if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#     pragma ghs interrupt
#    endif
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_MCAN( void )
#   endif
#  endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#  if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#  endif

/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_0 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(0) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(0))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(0))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_0)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_0)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(0));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_0);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_1 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(1) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(1))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(1))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_1)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_1)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(1));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_1);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_2 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(2) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(2))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(2))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_2)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_2)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(2));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_2);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_3 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(3) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(3))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(3))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_3)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_3)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(3));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_3);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_4 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(4) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(4))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(4))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_4)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_4)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(4));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_4);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_5 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(5) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(5))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(5))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_5)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_5)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(5));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_5);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_6 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(6) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(6))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(6))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_6)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_6)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(6));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_6);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_7 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(7) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(7))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(7))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_7)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_7)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(7));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_7);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_8 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(8) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(8))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(8))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_8)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_8)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(8));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_8);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_9 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(9) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(9))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(9))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_9)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_9)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(9));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_9);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_10 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(10) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(10))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(10))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_10)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_10)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(10));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_10);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_11 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(11) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(11))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(11))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_11)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_11)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(11));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_11);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_12 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(12) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(12))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(12))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_12)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_12)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(12));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_12);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_13 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(13) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(13))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(13))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_13)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_13)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(13));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_13);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_14 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(14) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(14))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(14))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_14)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_14)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(14));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_14);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_15 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(15) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(15))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(15))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_15)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_15)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(15));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_15);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_16 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(16) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(16))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(16))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_16)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_16)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(16));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_16);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_17 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(17) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(17))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(17))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_17)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_17)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(17));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_17);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_18 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(18) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(18))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(18))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_18)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_18)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(18));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_18);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_19 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    if(Can_30_Mcan_GetPhysToLogChannel(19) != kCan_30_McanChannelNotUsed) /* COV_CAN_CHANNEL_USED */
    {
      if((CnX(Can_30_Mcan_GetPhysToLogChannel(19))->IR & CnX(Can_30_Mcan_GetPhysToLogChannel(19))->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   else
      if((CnX(kCan_30_McanPhysToLogChannelIndex_19)->IR & CnX(kCan_30_McanPhysToLogChannelIndex_19)->IE) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_INTERRUPT */
#   endif
      {
        /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
        CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(19));    /* call Interrupthandling with identity dependend logical channel */
#   else
        CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_19);                      /* call Interrupthandling with logical channel */
#   endif
      }
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    }
#   endif
#  endif
/* CODE CATEGORY 1 END */

#  if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#  endif
} /* END OF CanISR */

# else /* C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN */

/****************************************************************************
| NAME:             Can_30_McanIsr_0
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_0 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_0Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_0Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_0 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_0Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_0( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_0( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(0));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_0);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_1
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_1 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_1Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_1Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_1 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_1Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_1( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_1( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(1));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_1);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_2
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_2 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_2Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_2Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_2 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_2Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_2( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_2( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(2));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_2);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_3
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_3 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_3Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_3Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_3 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_3Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_3( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_3( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(3));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_3);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_4
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_4 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_4Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_4Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_4 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_4Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_4( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_4( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(4));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_4);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_5
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_5 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_5Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_5Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_5 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_5Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_5( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_5( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(5));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_5);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_6
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_6 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_6Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_6Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_6 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_6Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_6( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_6( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(6));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_6);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_7
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_7 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_7Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_7Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_7 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_7Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_7( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_7( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(7));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_7);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_8
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_8 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_8Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_8Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_8 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_8Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_8Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_8( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_8( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(8));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_8);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_8) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_9
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_9 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_9Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_9Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_9 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_9Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_9Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_9( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_9( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(9));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_9);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_9) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_10
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_10 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_10Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_10Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_10 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_10Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_10Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_10( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_10( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(10));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_10);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_10) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_11
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_11 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_11Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_11Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_11 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_11Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_11Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_11( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_11( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(11));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_11);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_11) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_12
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_12 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_12Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_12Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_12 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_12Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_12Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_12( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_12( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(12));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_12);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_12) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_13
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_13 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_13Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_13Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_13 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_13Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_13Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_13( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_13( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(13));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_13);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_13) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_14
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_14 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_14Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_14Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_14 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_14Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_14Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_14( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_14( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(14));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_14);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_14) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_15
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_15 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_15Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_15Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_15 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_15Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_15Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_15( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_15( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(15));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_15);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_15) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_16
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_16 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_16Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_16Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_16 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_16Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_16Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_16( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_16( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(16));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_16);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_16) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_17
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_17 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_17Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_17Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_17 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_17Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_17Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_17( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_17( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(17));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_17);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_17) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_18
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_18 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_18Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_18Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_18 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_18Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_18Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_18( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_18( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(18));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_18);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_18) */
/* CODE CATEGORY 1 END */
/****************************************************************************
| NAME:             Can_30_McanIsr_19
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( kCan_30_McanPhysToLogChannelIndex_19 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
/* CODE CATEGORY 1 START */
#   if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined( C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 ) /* COV_CAN_OS_USAGE */
#    if defined (osdIsrCanIsr_19Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_19Cat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
/*!
 * Internal comment removed.
 *
 *
 */
ISR( Can_30_McanIsr_19 )    /* PRQA S 3408 */ /* ISR prototypes must be provided by OSEK header file */
#   else
#    if defined( C_30_MCAN_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_19Cat) /* COV_CAN_OSCAT_CONFIG_CHECK */
#     if (osdIsrCanIsr_19Cat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if defined ( C_30_MCAN_ENABLE_ISRVOID )
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_19( void )
#    else
#      if defined(V_COMP_GHS) && !defined(MISRA_CHECK) /* COV_CAN_COMPILER_SWITCH */
#       pragma ghs interrupt
#      endif
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_19( void )
#    endif
#   endif /* C_30_MCAN_ENABLE_OSEK_OS */
{
#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
    /* #10 call interrupt handler */
#   if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    CanInterrupt_30_Mcan(Can_30_Mcan_GetPhysToLogChannel(19));    /* call Interrupthandling with identity dependend logical channel */
#   else
    CanInterrupt_30_Mcan(kCan_30_McanPhysToLogChannelIndex_19);                      /* call Interrupthandling with logical channel */
#   endif

#   if !defined(MISRA_CHECK)  /* COV_CAN_MISRA */
#   endif
} /* END OF CanISR */
#  endif /* (kCan_30_McanPhysToLogChannelIndex_19) */
/* CODE CATEGORY 1 END */

# endif /* C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN */
#endif  /* Not a pure polling configuration */


#define CAN_30_MCAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

