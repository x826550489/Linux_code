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

/* \trace SPEC-1570 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_30_MCAN_INTERNAL /* compatibility */
#define CAN_30_MCAN_SOURCE     /* testability */
#define __CAN_SRC__       /* compatibility RTM not aware of multi driver instance */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#if !defined(__CAN_30_MCAN_SRC__) /* driver use ORGANI without infix */ /* COV_CAN_INTERNAL */
# define __CAN_30_MCAN_SRC__      /* for all MSR module (used by RTM) */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#endif

/* \trace SPEC-1408, SPEC-1590, SPEC-1588 */
/* PRQA S 0777 EOF */ /* MD_Can_0777_LL */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0841 EOF */ /* MD_Can_0841    */
/* PRQA S 0303 EOF */ /* MD_Can_HwAccess */
/* \trace SPEC-1392 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* \trace SPEC-1707 */
#include "CanIf.h"       /* for version check */
#include "Can_30_Mcan_Local.h"    /* have to be last include due to channel define will lead to problems */


#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
/* \trace SPEC-1596 */
# include "Det.h"
#endif

#if !defined(CAN_30_MCAN_AMD_RUNTIME_MEASUREMENT) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_30_MCAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_AMD_RUNTIME_MEASUREMENT */
# include "AmdRtm.h"
#endif

#if !defined(CAN_30_MCAN_RUNTIME_MEASUREMENT_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_30_MCAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# define C_30_MCAN_ENABLE_RUNTIME_MEASUREMENT_SUPPORT
# include "Rtm.h"
#endif

#include "vstdlib.h"

/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_30_MCAN_COREVERSION           != 0x1000u) /* \trace SPEC-1699 */
# error "Source and Header file are inconsistent!"
#endif
#if (CAN_30_MCAN_RELEASE_COREVERSION   != 0x03u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_30_MCAN_GEN_BASE_CFG5_VERSION) /* COV_CAN_COMPATIBILITY */
# if (CAN_30_MCAN_GEN_BASE_CFG5_VERSION         != 0x0103u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_30_MCAN_GEN_BASE_CFG5_VERSION is defined"
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

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(CAN_USE_NO_VECTOR_IF) /* for testability */
#else
# if defined(CANIF_VENDOR_ID) /* COV_CAN_COMPATIBILITY */
#  if (CANIF_VENDOR_ID == 0x001E) /* COV_CAN_COMPATIBILITY */
#   define CAN_USE_VECTOR_IF
#  endif
# endif
#endif
/* Compatibility to CBD */
/* instead of direct canCanInterruptCounter[] use Can_30_Mcan_GetCanInterruptCounter(Index) abstraction for ComStackLib */

#if (CAN_30_MCAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanHookBegin_Can_30_Mcan_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_30_Mcan_Init)
# define CanHookEnd_Can_30_Mcan_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_30_Mcan_Init)
# define CanHookBegin_Can_30_Mcan_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_30_Mcan_SetControllerMode)
# define CanHookEnd_Can_30_Mcan_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_30_Mcan_SetControllerMode)
# define CanHookBegin_Can_30_Mcan_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_30_Mcan_Write)
# define CanHookEnd_Can_30_Mcan_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_30_Mcan_Write)

#else /* BRS runtime measurement */
# define CanHookBegin_Can_30_Mcan_Init()
# define CanHookEnd_Can_30_Mcan_Init()
# define CanHookBegin_Can_30_Mcan_SetControllerMode() \

# define CanHookEnd_Can_30_Mcan_SetControllerMode() \

# define CanHookBegin_Can_30_Mcan_Write() \

# define CanHookEnd_Can_30_Mcan_Write() \

#endif

# define CanHookBegin_CanHL_30_Mcan_ReInit() \

# define CanHookEnd_CanHL_30_Mcan_ReInit() \

#define CanHookBegin_CanHL_30_Mcan_TxConfirmation() \

#define CanHookEnd_CanHL_30_Mcan_TxConfirmation() \

#define CanHookBegin_CanHL_30_Mcan_BasicCanMsgReceived() \

#define CanHookEnd_CanHL_30_Mcan_BasicCanMsgReceived() \

#define CanHookBegin_CanHL_30_Mcan_FullCanMsgReceived() \

#define CanHookEnd_CanHL_30_Mcan_FullCanMsgReceived() \

#define CanHookBegin_Can_30_Mcan_MainFunction_Write() \

#define CanHookEnd_Can_30_Mcan_MainFunction_Write() \

#define CanHookBegin_Can_30_Mcan_MainFunction_Read() \

#define CanHookEnd_Can_30_Mcan_MainFunction_Read() \


/*!
 *  Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
*/



/* Start value of the Message RAM Watchdog Counter. 
   With the reset value of '0' the counter is disabled. */
#define kCan_RWD                        0x00000000UL

/* Bitmasks of MCAN CCCR */
#define kCanCCCR_INIT                   0x00000001UL /*! '1'= Initialization is started */
#define kCanCCCR_CCE                    0x00000002UL /*! Configuration Change Enable: '1'= CPU has write access to the protected configuration registers (while CCCR.INIT = '1') */
#define kCanCCCR_ASM                    0x00000004UL /*! Restricted Operation Mode: '1'= Restricted Operation Mode active */
#define kCanCCCR_CSA                    0x00000008UL /*! Clock Stop Acknowledge: '1'= M_CAN may be set in power down by stopping host and core clock */
#define kCanCCCR_CSR                    0x00000010UL /*! Clock Stop Request:     '1'= Clock stop requested (after all pending transfers are completed and CAN reached Bus_Idle 
                                                                                    first INIT and then CSA will be set */
#define kCanCCCR_MON                    0x00000020UL /*! Bus Monitoring Mode:    '1'= Bus Monitoring Mode enabled */
#define kCanCCCR_DAR                    0x00000040UL /*! Disable Automatic Retransmission: '1'= Automatic retransmission disabled */
#define kCanCCCR_TEST                   0x00000080UL /*! Test Enable Mode:       '1'= Test Mode (write access to register TEST enabled) */

#define kCanFBTP_TDC_Disable            0x00000000UL          /*! Transceiver Delay Compensation disabled  */
#define kCanTDCR_TDC_Disable            kCanFBTP_TDC_Disable /*! TDCO moved to new register TDCR (since Rev. 3.1.0) */
#define kCanTDCR_FBTP_TDCO_300          0x1F000000UL /*! Transceiver Delay Compensation Offset from FBTP (Rev. 3.0) */
#define kCanTDCR_FBTP_TDCO_Mask_310     0x00FFFFFFUL  /*! Transceiver Delay Compensation Offset Mask (since Rev. 3.0) */
#define kCanFBTP_to_TDCR_bit_offset_r   16UL         /*! Transceiver Delay Compensation Offset bit offset from register FBTP to TDCR (Rev. 3.0 to Rev. 3.1.0) */

#if !defined(kCanGFC_ANFS) /* COV_CAN_HW_SPECIFIC */
/* Non-matching Frames Standard */
# define kCanGFC_ANFS                   0x00000030UL  /*! 0x00000000UL Accept in Rx FIFO 0
                                                        0x00000010UL Accept in Rx FIFO 1
                                                        0x00000030UL Reject */
#endif

#if !defined(kCanGFC_ANFE) /* COV_CAN_HW_SPECIFIC */
/* Non-matching Frames Extended */
# define kCanGFC_ANFE                   0x0000000CUL  /*! 0x00000000UL Accept in Rx FIFO 0
                                                        0x00000004UL Accept in Rx FIFO 1
                                                        0x0000000CUL Reject */
#endif

#if !defined(kCanGFC_RRFS) /* COV_CAN_HW_SPECIFIC */
/* Remote Frames Standard */
# define kCanGFC_RRFS                   0x00000002UL  /*! 0x00000000 Filter Remote Frames Standard       
                                                        0x00000002 Reject Remote Frames Standard */
#endif

#if !defined(kCanGFC_RRFE) /* COV_CAN_HW_SPECIFIC */
/* Remote Frames Extended */
# define kCanGFC_RRFE                   0x00000001UL  /*! 0x00000000 Filter Remote Frames Extended
                                                          0x00000001 Reject Remote Frames Extended */
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS )  /* COV_CAN_HW_SPECIFIC */

# define kCanMcanSSRegICS_EXT_TS_CNTR_OVFL    0x00000001UL      /*! External Timestamp Counter Overflow Interrupt status bit, write 1 to clear, RW1TC */
# define kCanMcanSSRegIECS_EXT_TS_CNTR_OVFL   0x00000001UL      /*! External Timestamp Counter Overflow Interrupt clear enable bit, write 1 to clear, RW1TC */
# define kCanMcanSSRegEOI_EOI                 0x000000FFUL      /*! End Of Interrupt bits, bits 0:7, RW */
# define kCanMcanSSRegEOI_EXT                 0x00000000UL      /*! End Of Interrupt for external timestamp interrupt */

# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_AGGR)  /* COV_CAN_HW_SPECIFIC */
#  define kCanMcanSSRegEccAggrEnableClear     0x00000003UL      /*! Aggregator Interrupt Enable Clear Register */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_AGGR */

# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_EOI)  /* COV_CAN_HW_SPECIFIC */
#  define kCanMcanSSRegEE_ECC_EOI             0x00000100UL      /*! End Of Interrupt for ECC interrupt bit, W */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_EOI */

# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_VBUSS)/* COV_CAN_HW_SPECIFIC */
#  define kCanMcanSSRegEccSecMsgVbussPending  0x00000003UL                       /*! Interrupt Pending for MSGMEM_PEND */
#  define kCanMcanSSRegEccSecEnableClr        kCanMcanSSRegEccSecMsgVbussPending  /*! Interrupt Enable Clear for CTRL_EDC_VBUSS_PEND and MSGMEM_PEND, write 1 to clear, RW1TC */
#  define kCanMcanSSRegEccDedEnableClr        kCanMcanSSRegEccSecMsgVbussPending  /*! Interrupt Enable Clear for CTRL_EDC_VBUSS_PEND and MSGMEM_PEND, write 1 to clear, RW1TC */
# else
#  define kCanMcanSSRegEccSecMsgMemPending    0x00000001UL                         /*! Interrupt Pending for CTRL_EDC_VBUSS_PEND */
#  define kCanMcanSSRegEccSecEnableClr        kCanMcanSSRegEccSecMsgMemPending      /*! Interrupt Enable Clear for MSGMEM_PEND, write 1 to clear, RW1TC */
#  define kCanMcanSSRegEccDedEnableClr        kCanMcanSSRegEccSecMsgMemPending      /*! Interrupt Enable Clear for MSGMEM_PEND, write 1 to clear, RW1TC */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_VBUSS */
#endif /* C_30_MCAN_ENABLE_REGEXT_MCANSS */

#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD )  /* COV_CAN_HW_SPECIFIC */

# define SICANFD_FS_ECC_ADDR_OFFSET      0x00000230UL      /*! Offset from Base Address of the MCAN registers in the SICANFD module to the Functional Safety registers */

# define kCanSICanFd_DCLS_FI_ERROR       0x00000007UL       /*! Causes a DCLS error, FL_DCLS = 0b111 */
# define kCanSICanFd_DCLS_FI_INEFFECTIVE 0x00000000UL       /*! DCLS Fault Injection is ineffective, FL_DCLS != 0b111 */
# define kCanSICanFd_ECC_INVERSION       0x00000007UL       /*! ECC - Inversion processing is applied to the written data or ECC code to Mesage RAM, FL_ECC = 0b111  */
# define kCanSICanFd_ECC_FI_INEFFECTIVE  0x00000000UL       /*! ECC Fault Injection Is Ineffective, FL_ECC != 0b111*/
# define kCanSICanFd_CLR_SEC             0x01000000UL       /*! Single Bit Error Detection Flag Clearance*/
# define kCanSICanFd_CLR_DED             0x00010000UL       /*! Double Bit Error Detection Flag Clearance*/
# define kCanSICanFd_CLR_DCLS            0x00000001UL       /*! DCLS comparison Error Detection Flag Clearance*/
# define kCanSICanFd_AL_KEYCODE          0xC3EDC6FEUL       /*! Key Code To Add Write Permissions to AL_SET_DCLS and AL_SET_ECC */
# define kCanSICanFd_AL_KEYSTATUS        0x00000001UL       /*! Key Status To Indicate If Key Code Is Set Correctly*/
# define kCanSICanFd_FI_DATA_D_NO_INV    0x00000000UL       /*! Fault Injection Bit Position for Data Written to Message RAM, No Bit Inversion */
# define kCanSICanFd_FI_DATA_E_NO_INV    0x00000000UL       /*! Fault Injection Bit Position for An ECC Code Written to Message RAM, No Bit Inversion */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
#define MCANAS1_FS_ECC_ADDR_OFFSET       0x00000830u             /*! Offset from Base Address of the MCAN module in the AS1 Can module to the Functional Safety registers */
#define MCANAS1_G24IRCLR_ADDR            0xF00003E0u             /*! Group 24 Interrupt Cause Clear Register */
#define MCANAS1_G24IRQCLR_BITNO0                  0u             /*! Group 24 IRQ Interrupt cause clear bit. Mcan Line 0 */

#define kCanMcanAs1_PROTECT_KEY_RELEASE  0xE3B7D8C5u             /*! Write control key for releasing function safety register*/
#define kCanMcanAs1_PROTECT_KEY_LOCK     0x00000000u             /*! Write control key for locking function safety register*/
#define kCanMcanAs1_ECCCTRL_DISABLE      0x00000001u             /*! ECC do not clear flags, disable interrupts, turn OFF the ECC function */
#define kCanMcanAs1_ECCRAM_DBGSEL        0x00000000u             /*! Set the access surface to the ECC part of the message RAM */
#define kCanMcanAs1_ECCRAM_DBG           0x00000000u             /*! Set the access route to the ECC part of message RAM to the ECC generation unit */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD )  /* COV_CAN_HW_SPECIFIC */        /* TTCanFD */
/* Global Register Masks */
# define TTCANFD_RXFTOP_CTL_ADDR_OFFSET          0x00000180UL   /*! Offset from Base Address of the MCAN registers in the TTCANFD module to the Receive FIFO Top control register */

# define kCanTTCanFD_CAN_CLEAR                    0x00000000UL    /*! Clear Register*/
# define kCanTTCanFD_CAN_CTL_MRAM_OFF             0x80000000UL    /*! MRAM off*/
# define kCanTTCanFD_CAN_CTL_STOP_REQ             0x000000FFUL    /*! Clock Stop Request for each TTCAN IP*/

# define kCanTTCanFD_CAN_STATUS_STOP_ACK          0x000000FFUL    /*! Clock Stop Acknowledge for each TTCAN IP*/

# define kCanTTCanFD_CAN_DESIGN_CFG_TS_PRESENT    0x00002000UL    /*! Design time time configured Time Stamp present*/
# define kCanTTCanFD_CAN_DESIGN_CFG_ECC_PRESENT   0x00001000UL    /*! Design time time configured ECC present*/
# define kCanTTCanFD_CAN_DESIGN_CFG_CAN_NR        0x00000700UL    /*! Design time time configured Number of CAN channels - 1*/
# define kCanTTCanFD_CAN_DESIGN_CFG_MRAM_SIZE     0x0000003FUL    /*! Design time time configured Message RAM size - 1 in KB*/

# define kCanTTCanFD_CAN_INTR0_CAUSE_INT0         0x000000FFUL    /*! Show pending m_ttcan_int0 of each channel*/
# define kCanTTCanFD_CAN_INTR0_CAUSE_INT0_0       0x00000001UL    /*! pending in channel 0 in subsystem*/
# define kCanTTCanFD_CAN_INTR0_CAUSE_INT0_1       0x00000002UL    /*! pending in channel 1 in subsystem*/
# define kCanTTCanFD_CAN_INTR0_CAUSE_INT0_2       0x00000004UL    /*! pending in channel 2 in subsystem*/

# define kCanTTCanFD_CAN_INTR1_CAUSE_INT1         0x000000FFUL    /*! Show pending m_ttcan_int1 of each channel*/
# define kCanTTCanFD_CAN_INTR1_CAUSE_INT1_0       0x00000001UL    /*! pending in channel 0 in subsystem*/
# define kCanTTCanFD_CAN_INTR1_CAUSE_INT1_1       0x00000002UL    /*! pending in channel 1 in subsystem*/
# define kCanTTCanFD_CAN_INTR1_CAUSE_INT1_2       0x00000004UL    /*! pending in channel 2 in subsystem*/

# define kCanTTCanFD_CAN_TS_CTL_ENABLED           0x80000000UL    /*! Counter enable bit*/
# define kCanTTCanFD_CAN_TS_CTL_PRESCALE          0x0000FFFFUL    /*! Time Stamp counter prescale value*/

# define kCanTTCanFD_CAN_TS_CNT_VALUE             0x0000FFFFUL    /*! The counter value of the Time Stamp Counter*/

# define kCanTTCanFD_CAN_ECC_CTL_ECC_EN           0x00010000UL    /*! Enable ECC for CANFD SRAM*/

# define kCanTTCanFD_CAN_ECC_ERR_INJ_ERR_PAR      0x7F000000UL    /*! ECC Parity bits to use for ECC error injection at address ERR_ADDR*/
# define kCanTTCanFD_CAN_ECC_ERR_INJ_ERR_EN       0x00100000UL    /*! Enable error injection*/
# define kCanTTCanFD_CAN_ECC_ERR_INJ_ERR_ADDR     0x0000FFFCUL    /*! Specifies the address of the word where an error will be injected on write or an non-correctable error will be suppressed*/

/* Channel Register Masks */
# define kCanTTCanFD_CAN_CH_RXFTOP_CTL_F1TPE      0x00000002UL    /*! FIFO 1 Top Pointer Enable*/
# define kCanTTCanFD_CAN_CH_RXFTOP_CTL_F0TPE      0x00000001UL    /*! FIFO 0 Top Pointer Enable*/

# define kCanTTCanFD_CAN_CH_RXFTOP0_STAT_F0TA     0x0000FFFFUL    /*! Current FIFO 0 Top Address*/

# define kCanTTCanFD_CAN_CH_RXFTOP0_DATA_F0TD     0xFFFFFFFFUL    /*! When enabled (F0TPE=1) read data from MRAM at location F0TA*/

# define kCanTTCanFD_CAN_CH_RXFTOP1_STAT_F1TA     0x0000FFFFUL    /*! Current FIFO 1 Top Address*/

# define kCanTTCanFD_CAN_CH_RXFTOP1_DATA_F1TD     0xFFFFFFFFUL    /*! When enabled (F1TPE=1) read data from MRAM at location F1TA*/
#endif

# if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */ /* STM32 FDCAN */
#  define kCanStmCanFD_CAN_CCU_CCFG_CLEAR       0x00000444UL    /*! Reset value for Calibration configuration register*/
#  define kCanStmCanFD_CAN_CCU_CWD_CLEAR        0x0000u        /*! Reset value for Calibration watchdog register */
#  define kCanStmCanFD_CAN_CCU_IR_CLEAR         0x00000000UL    /*! Reset value for Clock calibration unit interrupt register */
#  define kCanStmCanFD_CAN_CCU_IE_CLEAR         0x00000000UL    /*! Reset value for Clock calibration unit interrupt enable register  */
# endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TCC_PWD ) /* COV_CAN_HW_SPECIFIC */
# define kCanTCC_PWD_KEYCODE                    0x8030ACE5UL    /*! Key code to cdd write permissions to MRAM base address */
#endif

/*  High Priority Message Status Register (HPMS):
Bits 16     FLST Filter List
Indicates the filter list of the matching filter element.
0 Standard Filter List
1 Extended Filter List

Bits 17:23  FIDX Filter Index
Index of matching filter element. Range is 0 to SIDFC[LSS] - 1 resp. XIDFC[LSE] - 1.

Bits 24:25  MSI Message Storage Indicator
00 No FIFO selected
01 FIFO overrun
10 Message stored in FIFO 0
11 Message stored in FIFO 1

Bits 26:31  BIDX Buffer Index
Index of Rx FIFO element to which the message was stored. Only valid when MSI[1] = '1'.
*/
#define kCanHPMS_FLST_STD               0x00000000UL
#define kCanHPMS_FLST_EXT               0x00008000UL
#define kCanHPMS_FIDX                   0x00007F00UL
#define kCanHPMS_MSI_NOFIFO             0x00000000UL
#define kCanHPMS_MSI_FIFO_OWFL          0x00000040UL
#define kCanHPMS_MSI_FIFO_0             0x00000080UL
#define kCanHPMS_MSI_FIFO_1             0x000000C0UL
#define kCanHPMS_BIDX                   0x0000003FUL

/* Standard Message ID Filter element:
  Bits 31:30 SFT[1:0] Standard Filter Type
  00 Range filter from SF1ID to SF2ID (with SF2ID >= SF1ID)
  01 Dual ID filter for SF1ID or SF2ID
  10 Classic filter: SF1ID = filter, SF2ID = mask
  11 Reserved

  Bit 29:27 SFEC[2:0] Standard Filter Element Configuration
  000 Disable filter element
  001 Store in Rx FIFO 0 if filter matches
  010 Store in Rx FIFO 1 if filter matches
  011 Reject ID if filter matches
  100 Set priority if filter matches
  101 Set priority and store in FIFO 0 if filter matches
  110 Set priority and store in FIFO 1 if filter matches
  111 Store into Rx Buffer or as debug message, configuration of SFT[1:0] ignored
  All enabled filter elements are used for acceptance filtering of standard frames. 
  Acceptance filtering stops at the first matching enabled filter element or when the end 
  of the filter list is reached. 
  If SFEC = '100', '101', or '110' a match generates an interrupt (if enabled).
  In this case register HPMS is updated with the status of the priority match.

  Bits 26:16 SFID1[10:0] Standard Filter ID 1
  First ID of standard ID filter element.
  When filtering for debug messages this field defines the ID of a standard debug
  message to be stored to the re-assigned Rx FIFO 1 element 61...63. 
  The received identifiers must match exactly, no masking mechanism is used.

  Bits 10:0 SFID2[10:0] Standard Filter ID 2
  Second ID of standard ID filter element.
  When filtering for debug messages SFID2[5:0] defines the Rx FIFO 1 element number 
  for storage of a matching debug message.
  SFID2[10:9] decides whether the received message is treated as message A, B, or C of 
  the debug message sequence:
  00= Reserved
  01= Message A
  10= Message B
  11= Message C  */
#define kCanSFE_SFTRange               0x00000000UL
#define kCanSFE_SFTDualId              0x40000000UL
#define kCanSFE_SFTClassic             0x80000000UL
#define kCanSFE_SFTRes                 0xC0000000UL

#define kCanSFE_SFEC_Disable           0x00000000UL
#define kCanSFE_SFEC_F0                0x08000000UL
#define kCanSFE_SFEC_F1                0x10000000UL
#define kCanSFE_SFEC_Reject            0x18000000UL
#define kCanSFE_SFEC_SetPrio           0x20000000UL
#define kCanSFE_SFEC_SetPrioStoreF0    0x28000000UL
#define kCanSFE_SFEC_SetPrioStoreF1    0x30000000UL
#define kCanSFE_SFEC                   0x38000000UL

#define kCanSFE_SFID1                  0x07FF0000UL  /*! bits 16:26 */
#define kCanSFE_Res                    0x0000F800UL  /*! bits 11:15 */
#define kCanSFE_SFID2                  0x000007FFUL  /*! bits  0:10 */
#define kCanSFE_SFID2_RBSA             0x0000003FUL  /*! bits  0:5 */

/* Extended message ID filter element:
  F0 Bits 31:29 EFEC[2:0] Extended Filter Element Configuration 
  000 Disable filter element
  001 Store in Rx FIFO 0 if filter matches
  010 Store in Rx FIFO 1 if filter matches
  011 Reject ID if filter matches
  100 Set priority if filter matches
  101 Set priority and store in FIFO 0 if filter matches
  110 Set priority and store in FIFO 1 if filter matches
  111 Store as debug message, configuration of EFT[1:0] ignored

  F0 Bits 28:0 EFID1[28:0] Extended Filter ID 1
  When filtering for debug messages this field defines the ID of a extended debug 
  message to be stored to the re-assigned Rx FIFO 1 element 61...63. The received 
  identifiers must match exactly, no masking mechanism is used.

  F0 Bits 28:0  EFID1[28:0]

  F1 Bits 31:30 EFT[1:0] Extended Filter Type
  00 Range filter from EF1ID to EF2ID (EF2ID >= EF1ID)
  01 Dual ID filter for EF1ID or EF2ID
  10 Classic filter: EF1ID = filter, EF2ID = mask
  11 Range filter from EF1ID to EF2ID (EF2ID >= EF1ID), XIDAM mask not applied

  F1 Bits 28:0 EFID2[28:0]
  Extended Filter ID 2
  Second ID of extended ID filter element.
  When filtering for debug messages EFID2[5:0] defines the Rx FIFO 1 element number 
  for storage of a matching debug message.
  EFID2[10:9] decides whether the received message is treated as message A, B, or C of 
  the debug message sequence.
  00= Reserved
  01= Message A
  10= Message B
  11= Message C */
#define kCanEFE_EFTRangewMask          kCanSFE_SFTRange
#define kCanEFE_EFTDualId              kCanSFE_SFTDualId
#define kCanEFE_EFTClassic             kCanSFE_SFTClassic
#define kCanEFE_EFTRangewoMask         0xC0000000UL

#define kCanEFE_EFEC_Disable           0x00000000UL
#define kCanEFE_EFEC_F0                0x20000000UL
#define kCanEFE_EFEC_F1                0x40000000UL
#define kCanEFE_EFEC_Reject            0x60000000UL
#define kCanEFE_EFEC_SetPrio           0x80000000UL
#define kCanEFE_EFEC_SetPrioStoreF0    0xA0000000UL
#define kCanEFE_EFEC_SetPrioStoreF1    0xC0000000UL
#define kCanEFE_EFEC                   0xE0000000UL

#define kCanEFE_EFID1                  0x1FFFFFFFUL  /*! bits  0:28 */
#define kCanEFE_Res                    0x02000000UL  /*! bits    29 */
#define kCanEFE_EFID2                  0x1FFFFFFFUL  /*! bits  0:28 */
#define kCanEFE_EFID2_RBSA             0x0000003FUL  /*! bits  0:5 */

#define kCanSIDFCMax                   128  /* max number of std filters per channel */
#define kCanXIDFCMax                    64  /* max number of ext filters per channel */


/* Rx FIFO 0/1 Configuration (RXFnC):
Bits 0          Blocking or overwrite mode 
Bits 1:7        F0WM Rx FIFO 0 Watermark
                0     Watermark interrupt disabled
                1-64  Level for Rx FIFO 0 watermark interrupt (IR[RF0W])
                >64   Watermark interrupt disabled
Bits 8:9        Reserved
Bits 10:15      F0S Rx FIFO 0 Size
                0 No Rx FIFO 0
                1-64 Number of Rx FIFO 0 elements
                >64 Values greater than 64 are interpreted as 64
                The Rx FIFO 0 elements are indexed from 0 to F0S-1
Bits 16:29      FOSA Rx FIFO 0 Start Address
                Start address of Rx FIFO 0 in Message RAM (32-bit word address, Figure 547).
Bits 30:31      Reserved */
#define kCanRXF0C_F0WM         0x7F000000UL
#define kCanRXF0C_F0S          0x007F0000UL
#define kCanRXF1C_F0WM         kCanRXF0C_F0WM
#define kCanRXF1C_F0S          0x007F0000UL
#define kCanRXFnOM_BLOCK       0x00000000UL        /*! Blocking Mode  */
#define kCanRXFnOM_OVERWRITE   0x80000000UL        /*! Overwrite Mode */

/* Tx Buffer Configuration Register (TXBC):
Bit 1       TFQM Tx FIFO/Queue Mode
            0 Tx FIFO operation
            1 Tx Queue operation
Bits 2:7    TFQS Tx FIFO/Queue Size
            0   No Tx FIFO/Queue
            1-32 Number of Tx Buffers used for Tx FIFO/Queue
            >32 Values greater than 32 are interpreted as 32
Bits 10:15  NDTB Number of Dedicated Transmit Buffers
            0   No Dedicated Tx Buffers
            1-32 Number of Dedicated Tx Buffers
            >32 Values greater than 32 are interpreted as 32
Bits 16:29  TBSA Tx Buffers Start Address in Message RAM */
#define kCanTXBC_TFQM_MODE            0x40000000UL /*! 0=FIFO/1=QUEUE Mode */
#define kCanTXBC_TFQS                 0x3F000000UL /*! (1..32) FIFO/QUEUE size */
#define kCanTXBC_NDTB                 0x20u        /*! see CanTXBC: (1..32) Number of dedicated Tx buffers */
#define kCanTXBC_TBSA                 0x0000FFFCUL /*! Tx Buffer Start Address */

#define kCanTXBE_EFC                  0x00800000UL /*! Tx Buffer Event Fifo Control */

/* Tx Buffer Request Pending Register (TXBRP) */
#define kCanTXBRP_RP                  0x00000001UL   /* Tx request pending */
/* Tx Buffer confirmation and cancellation interrupts */
#define kCanTXBTIE_ENABLE_ALL         0xFFFFFFFFUL
#define kCanTXBCIE_ENABLE_ALL         0xFFFFFFFFUL
/* Frame detection */
#define kCanFrm_XTD                   0x40000000UL
#define kCanFrm_RTR                   0x20000000UL

/* Tx Event FIFO Configuration (TXEFC):
Bits [0:1]      Reserved.
Bits [2:7]      EFWM Event FIFO Watermark.
                0 Watermark interrupt disabled
                1..32 Level for Tx Event FIFO watermark interrupt (IR[TEFW])
                >32 Watermark interrupt disabled
Bits [8:9]      Reserved.
Bits [10:15]    EFS Event FIFO Size.
                0 Tx Event FIFO disabled
                1..32 Number of Tx Event FIFO elements
                >32 Values greater than 32 are interpreted as 32
                The Tx Event FIFO elements are indexed from 0 to EFS - 1
Bits [16:29]    EFSA Event FIFO Start Address.
                Start address of Tx Event FIFO in Message RAM (32-bit word address,Figure 547.
Bits [30:31]    Reserved. */
#define kCanTXEFC_EFWM        0x3F000000UL  /*! '0' or '>32' means INT disabled */
#define kCanTXEFC_EFS         0x003F0000UL  /*! '0' or '>32' means Event Fifo disabled */
#define kCanTXEFC_EFSA        0x0000FFFCUL  /*! Event Fifo Start Address */

/* Bitmasks of MCAN ECR */
#define kCanECR_CEL                     0x00FF0000UL  /*! CAN error logging     */
#define kCanECR_RP                      0x00008000UL  /*! receive error passive */
#define kCanECR_REC                     0x00007F00UL  /*! Rx error counter      */
#define kCanECR_TEC                     0x000000FFUL  /*! Tx error counter      */
/* Protocol Status Register (PSR): */
#define kCanPSR_REDL                    0x00002000UL /*! Received CAN FD Message with EDL flag */
#define kCanPSR_RBRS                    0x00001000UL /*! BRS flag of last received CAN FD Message */
#define kCanPSR_RBSI                    0x00000800UL /*! ESI CAN FD Message with ESI flag */
#define kCanPSR_FLEC                    0x00000700UL /*! Fast Last Error Code */
#define kCanPSR_PXE                     0x00004000UL /*! Protocol Exception Event */
#define kCanPSR_BO                      0x00000080UL /*! Bus_Off status */
#define kCanPSR_EW                      0x00000040UL /*! Warning status */
#define kCanPSR_EP                      0x00000020UL /*! Error Passive  */
#define kCanPSR_ACT                     0x00000018UL /*! Activity */
#define kCanPSR_ACT_SYNC                0x00000000UL /*! Activity: synchronizing */
#define kCanPSR_ACT_IDLE                0x00000008UL /*! Activity: idle          */
#define kCanPSR_ACT_RX                  0x00000010UL /*! Activity: reception     */
#define kCanPSR_ACT_TX                  0x00000018UL /*! Activity: transmission  */
#define kCanPSR_LEC                     0x00000007UL /*! last error code */

/* Protocol Status Register (PSR):
Bit 24      BO  Bus_Off Status
            1  The M_CAN is in Bus_Off state
Bit 25      EW  Warning Status
            0  Both error counters are below the Error_Warning limit of 96
            1  At least one of error counter has reached the Error_Warning limit of 96
Bit 26      EP  Error Passive
            0  Error_Active state (takes part in bus communication and sends an active error flag when an error has been detected)
            1  M_CAN is in the Error_Passive state
Bit 27:28   ACT Activity - Monitors the module's CAN communication state.
            00  Synchronizing - node is synchronizing on CAN communication
            01  Idle - node is neither receiver nor transmitter
            10  Receiver - node is operating as receiver
            11  Transmitter - node is operating as transmitter 
Bits 29:31  LEC Last Error Code (will be cleared to '0' when a message has been transferred (Rx or Tx) without error) */

#define kCanPSR_LEC_NO_ERROR           0x00u /*! No Error: No error occurred since LEC has been reset by successful reception or transmission */
#define kCanPSR_LEC_Stuff_ERROR        0x01u /*! Stuff Error: More than 5 equal bits in a sequence have occurred in a part of a received message where this is not allowed */
#define kCanPSR_LEC_FORM_ERROR         0x02u /*! Form Error: A fixed format part of a received frame has the wrong format */
#define kCanPSR_LEC_ACK_ERROR          0x03u /*! AckError: The message transmitted by the M_CAN was not acknowledged by another node */
#define kCanPSR_LEC_BIT1_ERROR         0x04u /*! Bit1Error: During transmission (except of the arbitration field): device wants to send a recessive level but the monitored bus value was dominant */
#define kCanPSR_LEC_BIT0_ERROR         0x05u /*! During transmission (message, ACK bit, active error flag, overload flag) device wants to send a dominant level but the monitored bus value was recessive.
During Bus_Off recovery this status is set each time a sequence of 11 recessive bits is monitored (monitor proceeding of Bus_Off recovery sequence) */
#define kCanPSR_LEC_CRC_ERROR          0x06u /*! CRCError: CRC of incoming message != CRC calculated from received data */
#define kCanPSR_LEC_NO_UPDATE          0x07u /*! NoChange: no CAN bus event was detected since the last read access (any read access to the PSR re-initializes the LEC to '7') */
 
#define kCanBusoff                    0x01u /*! CAN driver is in recovery phase after bus off */
#define kCanBusoffInit                0x02u /*! Driver finished recovery and needs to be initialized */
#define kCanNormal                    0x03u /*! Driver completed recovery and is in normal mode */

#define kCan_TSCC_TCP               0x00000000UL /*! Timestamp Counter Prescaler (hardware uses one more than the value programmed here) */
#define kCan_TSCC_TSS               0x00000000UL /*! 00 Timestamp counter value always zero */

#define kCan_TOCC_TOP               0x000000C8UL /*! Start value of the Timeout Counter (down-counter, in multiples of CAN bit times) */
#define kCan_TOCC_TOS               0x00000000UL /*! Timeout Select (00=Continuous operation, 01/10/11=controlled by Tx Event FIFO/by Rx FIFO 0/by Rx FIFO 1 */
#define kCan_TOCC_ETOC              0x00000001UL /*! 0=Timeout Counter disabled, 1=Timeout Counter enabled */

/* (IR)  The flags are set when one of the listed conditions is detected (edge-sensitive).
        The flags remain set until the Host clears them.
        A flag is cleared by writing a '1' to the corresponding bit position. Writing a '0' has no effect.
        A hard reset will clear the register.
  (IE)  The settings determine which status changes in the IR will be signalled on an interrupt line.
  (ILE) Each of the two interrupt lines to the CPU can be enabled/disabled separately by programming bits EINT0/EINT1. */
#if !defined(kCanIR_CLEAR_ALL)          /* COV_CAN_HW_SPECIFIC */
# if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
#  define kCanIR_CLEAR_ALL              0x3FFFFFFFUL  /*! clear all pending INT flags */
# else
#  define kCanIR_CLEAR_ALL              0xFFFFFFFFUL  /*! clear all pending INT flags */
# endif
#endif

#if !defined(kCanIE_DISABLE_ALL)        /* COV_CAN_HW_SPECIFIC */
# define kCanIE_DISABLE_ALL             0x00000000UL
#endif
#define kCan_ALL_ONE                    0xFFFFFFFFUL
#define kCanIE_ENABLE_ALL               kCan_ALL_ONE /* enable all INTs */
#define kCanILS_ALL_ZERO                0x00000000UL
#define kCanILE_EINT0                   0x00000001UL  /*! Enable  IL 0   */
#define kCanILE_DISABLE                 0x00000000UL  /*! Disable IL 0,1 */

/* Interrupts (IR):
Bit 0   STE   Stuff Error
Bit 1   FOE   Format Error
Bit 2   ACKE  Acknowledge Error
Bit 3   BE    Bit Error
Bit 4   CRCE  CRC Error
Bit 5   WDI   Message RAM Watchdog Interrupt 
Bit 6   BO    Bus_Off Status
Bit 7   EW    Warning Status 
Bit 8   EP    Error Passive Status
Bit 9   ELO   Error Logging Overflow
Bit 10  BEU   Message RAM Bit Error Uncorrected
Bit 11  BEC   Bit Error Corrected
Bit 12        MPC5746M = Reserved, MPC5777M = DRX (Message stored to Dedicated Rx Buffer)
Bit 13  TOO   Timeout Occurred
Bit 14  UMD   Unprocessed Message Discarded
              When a new message is received while the acceptance filtering process for the previously received message has not yet completed, this message is discarded.
Bit 15  TSW   Timestamp Wraparound
Bit 16  TEFL  Tx Event FIFO Event Lost
Bit 17  TEFF  Tx Event FIFO Full
Bit 18  TEFW  Tx Event FIFO Watermark Reached
Bit 19  TEFN  Tx Event FIFO New Entry
Bit 20  TFE   Tx FIFO Empty
Bit 21  TCF   Transmission Cancellation Finished
Bit 22  TC    Transmission Completed
Bit 23  HPM   High Priority Message
Bit 24  RF1L  Rx FIFO 1 Message Lost
Bit 25  RF1F  Rx FIFO 1 full
Bit 26  RF1W  Rx FIFO 1 Watermark Reached
Bit 27  RF1N  Rx FIFO 1 New Message
Bit 28  RF0L  Rx FIFO 0 Message Lost
Bit 29  RF0F  Rx FIFO 0 Full
Bit 30  RF0W  Rx FIFO 0 Watermark Reached
Bit 31  RF0N  Rx FIFO 0 New Message  */

#if( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
#define kCanIR_ARA                      0x20000000UL  /*!  Access to Reserved Address */
#define kCanIR_PED                      0x10000000UL  /*!  Protocol Error in Data Phase (Data Bit Time is used) */
#define kCanIR_PEA                      0x08000000UL  /*!  Protocol Error in Arbitration Phase (Nominal Bit Time is used) */
#else
#define kCanIR_STE                      0x80000000UL  /*! Stuff Error */
#define kCanIR_FOE                      0x40000000UL  /*! Format Error */
#define kCanIR_ACKE                     0x20000000UL /*! A transmitted message was not acknowledged by another node */
#define kCanIR_CRCE                     0x08000000UL /*! Received CRC did not match the calculated CRC */
#endif
#define kCanIR_WDI                      0x04000000UL /*! Watchdog Interrupt */
#define kCanIR_BO                       0x02000000UL /*! Bus_Off status changed */
#define kCanIR_EW                       0x01000000UL /*! Error_Warning status changed */
#define kCanIR_EP                       0x00800000UL /*! Error_Passive status changed */
#define kCanIR_BEU                      0x00200000UL /*! Bit Error Uncorrected */
#define kCanIR_BEC                      0x00100000UL /*! Bit Error Corrected */
#define kCanIR_DRX                      0x00080000UL /*! Message stored to Dedicated Rx Buffer (check NDAT1/2) */
#define kCanIR_MRAF                     0x00020000UL /*! Message RAM Access Failure */
#define kCanIR_TOO                      0x00040000UL /*! Timeout Occurred */
#define kCanIR_TCF                      0x00000400UL /*! Transmission cancellation finished */
#define kCanIR_TC                       0x00000200UL /*! Transmission completed */
#define kCanIR_HPM                      0x00000100UL /*! High Priority Message */
#define kCanIR_RF1L                     0x00000080UL /*! Rx FIFO 1 message lost (also set after write attempt to Rx FIFO 1 of size zero) */
#define kCanIR_RF1F                     0x00000040UL /*! Rx FIFO 1 full */
#define kCanIR_RF1W                     0x00000020UL /*! Rx FIFO 1 fill level reached watermark */
#define kCanIR_RF1N                     0x00000010UL /*! New message written to Rx FIFO 1 */
#define kCanIR_RF1X                     0x000000F0UL /*! Any Rx FIFO 1 */
#define kCanIR_RF0L                     0x00000008UL /*! Rx FIFO 0 message lost (also set after write attempt to Rx FIFO 0 of size zero) */
#define kCanIR_RF0F                     0x00000004UL /*! Rx FIFO 0 full */
#define kCanIR_RF0W                     0x00000002UL /*! Rx FIFO 0 fill level reached watermark */
#define kCanIR_RF0N                     0x00000001UL /*! New message written to Rx FIFO 0 */
#define kCanIR_RF0X                     0x0000000FUL /*! Any Rx FIFO 0 */
#define kCanIR_TFE                      0x00000800UL /*! Tx FIFO Empty */
#define kCanIR_TEFN                     0x00001000UL /*! Tx Event FIFO New Entry */
#define kCanIR_TEFW                     0x00002000UL /*! Tx Event FIFO Watermark Reached */
#define kCanIR_TEFF                     0x00004000UL /*! Tx Event FIFO Full */
#define kCanIR_TEFL                     0x00008000UL /*! Tx Event FIFO Event Lost */
#define kCanIR_TEF_EVTYPE_TX            0x00400000UL /*! Tx Event FIFO Event Type = Tx Event */
#define kCanIR_TEF_EVTYPE_TXCANCEL      0x00800000UL /*! Tx Event FIFO Event Type = Transmission in spite of cancellation */
#define kCanIR_TSW                      0x00010000UL /*! Timestamp Wrap-around */
#define kCanIR_ELO                      0x00400000UL /*! Error Logging Overflow */

/* Fifo (RXFn): */
#define kCanRXFnS_FnGI                  0x00003F00UL  /*! Fifo Get Index */
#define kCanRXFnS_FnFL                  0x0000007FUL  /*! Fifo Fill Level */

/*** A change of the CAN operation mode is requested by writing to this bit field. 
After change to the requested operation mode the bit field is reset to '00' and the status flags FACT and LACT are set accordingly. 
In case the requested CAN operation mode is not enabled, the value written to CMR is retained until it is overwritten by the next mode change request. 
Default is normal CAN operation 
CAN Mode Request
  00 unchanged
  01 Long Frame Mode request
  10 Long + Fast Frame Mode request
  11 Normal CAN operation request
CAN Mode Enable
  00 Normal CAN operation according to ISO11898-1
  01 Long        Frame Mode enabled: transmission of long, reception of long and fast CAN FD frames is enabled
  10 Long + Fast Frame Mode enabled: transmission and reception of long and fast CAN FD frames is enabled
  11 Long + Fast Frame Mode enabled: transmission and reception of long and fast CAN FD frames is enabled ***/
#if ( CAN_MCAN_REVISION >= 0x0310UL )    /* COV_CAN_HW_SPECIFIC */
/***  - CMR removed, transmit format configured in Tx Buffer element
      - CME replaced by FDOE and BRSE ***/
# define kCanCCCR_BRSE                  0x00000200UL /*! Bit Rate Switch enable */
# define kCanCCCR_FDOE                  0x00000100UL /*! FD operation enable */
# if ( CAN_MCAN_REVISION >= 0x0315UL )    /* COV_CAN_HW_SPECIFIC */
/***  NISO added since Rev. 3.1.5 ***/
#  define kCanCCCR_NISO                 0x00008000UL /*! Non ISO Operation 
                                                       0= CAN FD frame format according to ISO11898-1
                                                       1= CAN FD frame format according to Bosch CAN FD Spec. V1.0 */
# endif
#else
# define kCanCCCR_CME_CAN20             0x00000300UL /*! NORMAL CAN */
# define kCanCCCR_CME_LONG              0x00000100UL /*! LONG */
# define kCanCCCR_CME_LONG_FAST         0x00000200UL /*! LONG & FAST */
# define kCanCCCR_CMR_CAN20             0x00000C00UL /*! NORMAL CAN */
# define kCanCCCR_CMR_LONG              0x00000400UL /*! LONG */
# define kCanCCCR_CMR_LONG_FAST         0x00000800UL /*! LONG & FAST */
#endif

#define kCanCCCR_TXP                  0x00004000UL /*! Transmit Pause */
#if ( CAN_MCAN_REVISION >= 0x0310UL )   /* COV_CAN_HW_SPECIFIC */
# define kCanCCCR_EFBI                 0x00002000UL /*! new control bit PXHD (Protocol Exception Handling Disable) replaces status flag FDO */
# define kCanCCCR_PXHD                 0x00001000UL /*! new control bit EFBI (Edge Filtering during Bus Integration) replaces status flag FDBS */
#else
# define kCanCCCR_FDO                  0x00001000UL /*! CAN FD Operation */
# define kCanCCCR_FDBS                 0x00002000UL /*! CAN FD Bit Rate Switching */
#endif


#if !defined( CAN_30_MCAN_SET_BR_ID ) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_SET_BR_ID  0x0F
#endif

#if !defined(CAN_30_MCAN_NONE) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_NONE        0u
#endif
#if !defined(CAN_30_MCAN_BRS) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_BRS         1u
#endif
#if !defined(CAN_30_MCAN_FULL) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_FULL        2u
#endif
#if !defined(CAN_30_MCAN_FD_RXONLY) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_FD_RXONLY   2u
#endif
#if !defined(CAN_30_MCAN_FD_RXTX) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_FD_RXTX     1u
#endif

#if !defined(STD_ON) /* COV_CAN_COMPATIBILITY */
# define STD_ON          1u
#endif
#if !defined(STD_OFF) /* COV_CAN_COMPATIBILITY */
# define STD_OFF         0u
#endif

#if !defined (CAN_30_MCAN_FD_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_FD_SUPPORT CAN_30_MCAN_NONE
#endif

#if !defined (CAN_30_MCAN_TXP_SUPPORT) /* COV_CAN_HW_SPECIFIC */
# define CAN_30_MCAN_TXP_SUPPORT  STD_OFF
# define C_30_MCAN_DISABLE_CAN_TXP_SUPPORT
#else
# if (CAN_30_MCAN_TXP_SUPPORT == STD_ON)
#  define C_30_MCAN_ENABLE_CAN_TXP_SUPPORT
# else
#  define C_30_MCAN_DISABLE_CAN_TXP_SUPPORT
# endif
#endif

#if !defined( kCanNumberOfRxObjects )  /* COV_CAN_COMPATIBILITY */
# define kCanNumberOfRxObjects 0
#endif

/* Compatibility define */

/* PRQA S 3614 QAC_Can_3614 */ /* MD_Can_3614_LL */
/* PRQA  L:QAC_Can_3614 */

#define kCanZero                     0u


#define kCanRegCheckMaskCCCR_RP        0x00000003UL /*! CCE, INIT */
#define kCanRegCheckMaskCCCR_CCE       0xFFFFFFFDUL

#if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskFBTP    0x009F1FFFUL /*! TDC, DBRP, DTSEG1, DTSEG2, DSJW */
#else
# define kCanRegCheckMaskFBTP    0x1F9F0F73UL /*! TDCO, TDC, FBRP, FTSEG1, FTSEG2, FSJW */
#endif  /* MCAN Core Release < 0x0310UL */

#define kCanRegCheckMaskRWD    0x000000FFUL /*! WDC */

# if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
#  if ( CAN_MCAN_REVISION >= 0x0315UL ) /* COV_CAN_HW_SPECIFIC */
#   define kCanRegCheckMaskCCCR 0x0000F3F7UL /*! NISO, TXP, EFBI, PXHD, BRSE, FDOE, TEST, DAR, MON, CSR, CSA, ASM, CCE, INIT */
#  else
#   define kCanRegCheckMaskCCCR 0x000073F7UL /*! TXP, EFBI, PXHD, BRSE, FDOE, TEST, DAR, MON, CSR, CSA, ASM, CCE, INIT */
#  endif/* MCAN Core Release < 0x0315UL */
# else  
#  define kCanRegCheckMaskCCCR 0x00004FF7UL /*! TXP, CMR, CME, TEST, DAR, MON, CSR, CSA, ASM, CCE, INIT */
# endif/* MCAN Core Release < 0x0310UL */

#if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskBTP   0xFFFFFF7FUL /*! NSJW, NBRP, NTSEG1, NTSEG2 */
#else
# define kCanRegCheckMaskBTP   0x03FF3FFFUL /*! BRP, TSEG, TSEG2, SJW */
#endif /* MCAN Core Release < 0x0310UL */

#define kCanRegCheckMaskTSCC   0x000F0003UL /*! TCP, TSS */
#define kCanRegCheckMaskTOCC   0xFFFF0007UL /*! TOP, TOS, ETOC */

#if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskTDCR   0x00007F7FUL /*! TDCO, TDCF */
#endif /* MCAN Core Release < 0x0310UL */

#if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
#  if defined (C_30_MCAN_ENABLE_PARITY_INTERRUPT) /* COV_CAN_HW_SPECIFIC */
#   define kCanRegCheckMaskIE    0x3FFFFFFFUL /*! ARAE, PEDE, PEAE, WDIE, BOE, EWE, EPE, ELOE, BEUE, BECE, DRXE, TOOE, MRAFE, TSWE, TEFLE, TEFFE, TEFWE, TEFNE, TFEE, TCFE, TCE, HPME, RF1LE, RF1FE, RF1WE, RF1NE, RF0LE, RF0FE, RF0WE, RF0NE */
#   define kCanRegCheckMaskILS   0x3FFFFFFFUL /*! ARAL, PEDL, PEAL, WDIL, BOL, EWL, EPL, ELOL, BEUL, BECL, DRXL, TOOL, MRAFL, TSWL, TEFLL, TEFFL, TEFWL, TEFNL, TFEL, TCFL, TCL, HPML, RF1LL, RF1FL, RF1WL, RF1NL, RF0LL, RF0FL, RF0WL, RF0NL */
#  else
#   define kCanRegCheckMaskIE    0x3FCFFFFFUL /*! ARAE, PEDE, PEAE, WDIE, BOE, EWE, EPE, ELOE, DRXE, TOOE, MRAFE, TSWE, TEFLE, TEFFE, TEFWE, TEFNE, TFEE, TCFE, TCE, HPME, RF1LE, RF1FE, RF1WE, RF1NE, RF0LE, RF0FE, RF0WE, RF0NE */
#   define kCanRegCheckMaskILS   0x3FCFFFFFUL /*! ARAL, PEDL, PEAL, WDIL, BOL, EWL, EPL, ELOL, DRXL, TOOL, MRAFL, TSWL, TEFLL, TEFFL, TEFWL, TEFNL, TFEL, TCFL, TCL, HPML, RF1LL, RF1FL, RF1WL, RF1NL, RF0LL, RF0FL, RF0WL, RF0NL */
#  endif
#else
# define kCanRegCheckMaskIE    0xFFFFFFFFUL /*! STEE, FOEE, ACKEE, BEE, CRCEE, WDIE, BOE, EWE, EPE, ELOE, BEUE, BECE, DRXE, TOOE, MRAFE, TSWE, TEFLE, TEFFE, TEFWE, TEFNE, TFEE, TCFE, TCE, HPME, RF1LE, RF1FE, RF1WE, RF1NE, RF0LE, RF0FE, RF0WE, RF0NE */
# define kCanRegCheckMaskILS   0xFFFFFFFFUL /*! STEL, FOEL, ACKEL, BEL, CRCEL, WDIL, BOL, EWL, EPL, ELOL, BEUL, BECL, DRXL, TOOL, MRAFL, TSWL, TEFLL, TEFFL, TEFWL, TEFNL, TFEL, TCFL, TCL, HPML, RF1LL, RF1FL, RF1WL, RF1NL, RF0LL, RF0FL, RF0WL, RF0NL */
#endif /* MCAN Core Release < 0x0310UL */

# define kCanRegCheckMaskILE    0x00000003UL /*! EINT1, EINT0 */
#define kCanRegCheckMaskGFC    0x0000003FUL /*! ANFS, ANFE, RRFS, RRFE */
#define kCanRegCheckMaskSIDFC  0x00FFFFFCUL /*! LSS,FLSSA */
#define kCanRegCheckMaskXIDFC  0x007FFFFCUL /*! LSE, FLESA */
#define kCanRegCheckMaskXIDAM  0x1FFFFFFFUL /*! EIDM */
#define kCanRegCheckMaskRXF0C  0xFF7FFFFCUL /*! F0OM,F0WM, F0S, F0SA */
#define kCanRegCheckMaskRXF0A  0x0000003FUL /*! F0AI */
#define kCanRegCheckMaskRXBC   0x0000FFFCUL /*! RBSA */
#define kCanRegCheckMaskRXF1C  0xFF7FFFFCUL /*! F1OM, F1WM, F1S, F1SA */
#define kCanRegCheckMaskRXF1A  0x0000003FUL /*! F1AI */
#define kCanRegCheckMaskRXESC  0x00000777UL /*! RBDS, F1DS, F0DS */
#define kCanRegCheckMaskTXBC   0x7F3FFFFCUL /*! TFQM, TFQS, NDTB, TBSA */
#define kCanRegCheckMaskTXESC  0x00000007UL /*! TxBufferDataFieldSize */
#define kCanRegCheckMaskTXBTIE 0xFFFFFFFFUL /*! TIE31...TIE0 */
#define kCanRegCheckMaskTXEFC  0x3F3FFFFCUL /*! EFWM, EFS, EFSA */
#if defined ( C_30_MCAN_ENABLE_TTCAN_AVAILABLE ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskTTOCF  0x07FFFFFBUL /*! EVTP, ECC, EGTF, AWL, EECS, IRTO, LDSDL, TM GEN, OM */
#endif

#if defined( C_30_MCAN_ENABLE_STD_ID ) && (kCanNumberOfStandardFilter > 0)
# define kCanRegCheckMaskSMIDFE_S0   0xFFFF07FFUL /*! SFT, SFEC, SFID1, SFID2 */
#endif
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID) && (kCanNumberOfExtendedFilter > 0)
# define kCanRegCheckMaskEMIDFE_F0   0xFFFFFFFFUL /*! EFEC, EFID1 */
# define kCanRegCheckMaskEMIDFE_F1   0xDFFFFFFFUL /*! EFT, EFID2 */
#endif

#if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
# define kCanRegCheckMaskFBTP_DynMCan_300  0x1F9F0F73UL
# define kCanRegCheckMaskFBTP_DynMCan_310  0x009F1FFFUL
# define kCanRegCheckMaskCCCR_DynMCan_300  0x00004FF7UL
# define kCanRegCheckMaskCCCR_DynMCan_310  0x000073F7UL
# define kCanRegCheckMaskCCCR_DynMCan_315  0x0000F3F7UL
# define kCanRegCheckMaskBTP_DynMCan_300   0x03FF3FFFUL
# define kCanRegCheckMaskBTP_DynMCan_310   0xFFFFFF7FUL
# if ( CAN_MCAN_REVISION < 0x0310UL ) /* if this is not defined before due to MCan_rev<=300 */ /* COV_CAN_HW_SPECIFIC */
#  define kCanRegCheckMaskTDCR             0x00007F7FUL 
# endif 
# define kCanRegCheckMaskIE_DynMCan_300    0xFFFFFFFFUL 
# define kCanRegCheckMaskIE_DynMCan_310    0x3FFFFFFFUL
# define kCanRegCheckMaskILS_DynMCan_300   0xFFFFFFFFUL 
# define kCanRegCheckMaskILS_DynMCan_310   0x3FFFFFFFUL
# define kCanRegCheckMaskIR_DynMCan_300    0xFFFFFFFFUL
# define kCanRegCheckMaskIR_DynMCan_310    0x3FFFFFFFUL
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
# if defined (C_30_MCAN_ENABLE_MCANSS_CTRL_0) /* COV_CAN_HW_SPECIFIC */
#  define kCanRegCheckMaskMCANSS_CTRL                0x00000078UL /*! EXT_TS_CNTR_EN, AUTOWAKEUP, WAKEUPREQEN, DEBUG */
# else
#  define kCanRegCheckMaskMCANSS_CTRL                0x0000007EUL /*! EXT_TS_CNTR_EN, AUTOWAKEUP, WAKEUPREQEN, FREE, SOFT, CLKFACK */
# endif /* C_30_MCAN_ENABLE_MCANSS_CTRL_0 */
# define kCanRegCheckMaskMCANSS_EXT_TS_PRESCALER     0x00FFFFFFUL /*! PRESCALER */
#endif/* C_30_MCAN_ENABLE_REGEXT_MCANSS */

#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskSICANFD_AL_SET_DCLS 0x00000007UL /*! FI_DCLS */
# define kCanRegCheckMaskSICANFD_AL_SET_ECC  0x00000007UL /*! FI_ECC */
# define kCanRegCheckMaskSICANFD_FI_DATA_D   0xFFFFFFFFUL /*! FI_DATA_D */
# define kCanRegCheckMaskSICANFD_FI_DATA_E   0x0000007FUL /*! FI_DATA_E */
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskTTCANFD_RXFTOP_CTL  (kCanTTCanFD_CAN_CH_RXFTOP_CTL_F1TPE | kCanTTCanFD_CAN_CH_RXFTOP_CTL_F0TPE) /*! F0TPE, F1TPE */
#endif

#if defined(C_30_MCAN_ENABLE_SHM_DATAQOS) /* COV_CAN_HW_SPECIFIC */
# define kCanRegCheckMaskMRCFG_DATAQOS       0x00000003UL /*! Data Quality of Service */
#endif

/* *********************************************************************** */
/* SafeBSW check (LL)                                                      */
/* *********************************************************************** */
#if !defined(CAN_30_MCAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_SAFE_BSW    STD_OFF
#endif

#if (CAN_30_MCAN_SAFE_BSW == STD_ON)
# if ( CAN_MCAN_REVISION < 0x0315u )
#  error "Unsupported MCAN Revision version for SafeBSW !"
# endif
#endif


#if defined ( CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING )
# if ( CAN_MCAN_REVISION < 0x0310UL )
#  error "Unsupported MCAN Revision version for Security Event Reporting !"
# endif
#endif

/* *********************************************************************** */
/* Functional checks (LL)                                                  */
/* *********************************************************************** */
#if defined(C_30_MCAN_ENABLE_REGEXT_MCANAS1) && defined( C_30_MCAN_ENABLE_ISR_MANDATORY ) /* COV_CAN_HW_SPECIFIC_FUNCTIONALITY */
# if (CAN_30_MCAN_INTLOCK != CAN_30_MCAN_APPL) && !defined(C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  error "An unsupported feature is active!"
# endif
#endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */

/* for LL compatibility */
/* hw handles */
#define CAN_30_MCAN_HL_HW_TX_NORMAL_INDEX(hwch)     (Can_30_Mcan_GetTxBasicHwStart(hwch)) 
#if defined(CAN_30_MCAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_30_MCAN_HL_HW_TX_STARTINDEX(hwch)      (Can_30_Mcan_GetTxBasicHwStart(hwch))
#else
# define CAN_30_MCAN_HL_HW_TX_STARTINDEX(hwch)      (Can_30_Mcan_GetTxFullHwStart(hwch))
#endif
#define CAN_30_MCAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (Can_30_Mcan_GetTxFullHwStart(hwch))
#define CAN_30_MCAN_HL_HW_UNUSED_STARTINDEX(hwch)   (Can_30_Mcan_GetUnusedHwStart(hwch))
#define CAN_30_MCAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (Can_30_Mcan_GetRxFullHwStart(hwch))
#define CAN_30_MCAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (Can_30_Mcan_GetRxBasicHwStart(hwch))
#if defined(CAN_30_MCAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_30_MCAN_HL_HW_TX_STOPINDEX(hwch)       (Can_30_Mcan_GetTxFullHwStop(hwch))
#else
# define CAN_30_MCAN_HL_HW_TX_STOPINDEX(hwch)       (Can_30_Mcan_GetTxBasicHwStop(hwch))
#endif
#define CAN_30_MCAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (Can_30_Mcan_GetTxFullHwStop(hwch))
#define CAN_30_MCAN_HL_HW_UNUSED_STOPINDEX(hwch)    (Can_30_Mcan_GetUnusedHwStop(hwch))
#define CAN_30_MCAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (Can_30_Mcan_GetRxFullHwStop(hwch))
#define CAN_30_MCAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (Can_30_Mcan_GetRxBasicHwStop(hwch))
/* mailbox handles */
#define CAN_30_MCAN_HL_MB_RX_FULL_STARTINDEX(hwch)  (Can_30_Mcan_GetRxFullHandleStart(hwch))
#define CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(hwch) (Can_30_Mcan_GetRxBasicHandleStart(hwch))
#define CAN_30_MCAN_HL_MB_TX_FULL_STARTINDEX(hwch)  (Can_30_Mcan_GetTxFullHandleStart(hwch))
#define CAN_30_MCAN_HL_MB_TX_BASIC_STARTINDEX(hwch) (Can_30_Mcan_GetTxBasicHandleStart(hwch))
#define CAN_30_MCAN_HL_MB_RX_FULL_STOPINDEX(hwch)   (Can_30_Mcan_GetRxFullHandleStop(hwch))
#define CAN_30_MCAN_HL_MB_RX_BASIC_STOPINDEX(hwch)  (Can_30_Mcan_GetRxBasicHandleStop(hwch))
#define CAN_30_MCAN_HL_MB_TX_FULL_STOPINDEX(hwch)   (Can_30_Mcan_GetTxFullHandleStop(hwch))
#define CAN_30_MCAN_HL_MB_TX_BASIC_STOPINDEX(hwch)  (Can_30_Mcan_GetTxBasicHandleStop(hwch))

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
# if !defined(CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT) /* May be defined by test suite to stimulate RAM_CHECK failure */
#  if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#   define CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitIsMailboxCorrupt((initParaPtr))
#  else
#   define CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitIsMailboxCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_30_MCAN_RAM_CHECK_FINISHED_CTP) /* May be defined by test suite to check RAM_CHECK finished / executed */
#  define CAN_30_MCAN_RAM_CHECK_FINISHED_CTP(ch)
# endif
#endif
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
# if !defined(CAN_30_MCAN_RAM_CHECK_BEGIN_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#   define CAN_30_MCAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitBeginIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_30_MCAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitBeginIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_30_MCAN_RAM_CHECK_END_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#   define CAN_30_MCAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitEndIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_30_MCAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_30_Mcan_InitEndIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_30_MCAN_RAM_CHECK_READ_BACK_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  define CAN_30_MCAN_RAM_CHECK_READ_BACK_RESULT(ch)
# endif
#endif

#define CanHL_30_Mcan_IsStart(ch) ((Can_30_Mcan_GetLogStatus(ch) & CAN_30_MCAN_STATUS_START) == CAN_30_MCAN_STATUS_START)
#define CanHL_30_Mcan_IsSleep(ch) ((Can_30_Mcan_GetLogStatus(ch) & CAN_30_MCAN_STATUS_SLEEP) == CAN_30_MCAN_STATUS_SLEEP)
#define CanHL_30_Mcan_IsStop(ch) ((Can_30_Mcan_GetLogStatus(ch) & CAN_30_MCAN_STATUS_STOP) == CAN_30_MCAN_STATUS_STOP)
#define CanHL_30_Mcan_IsBusOff(ch) (Can_30_Mcan_IsIsBusOff(ch))
#define CanHL_30_Mcan_IsControllerInit(ch) ((Can_30_Mcan_GetLogStatus(ch) & CAN_30_MCAN_STATUS_INIT) == CAN_30_MCAN_STATUS_INIT)

#if defined(C_30_MCAN_ENABLE_CAN_FD_USED) /* also for BRS because DLC may be bigger than 8 and will be checked by CanIf */
# define CAN_30_MCAN_DLC2LEN(dlc) (Can_30_Mcan_DlcToFrameLenght[((uint8)(dlc)) & ((uint8)0xFu)])
# define CAN_30_MCAN_LEN2DLC(length) ((uint8)Can_30_Mcan_MessageLengthToDlc[(length)])
#else
# define CAN_30_MCAN_DLC2LEN(dlc) (dlc)
# define CAN_30_MCAN_LEN2DLC(length) (length)
#endif
#if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
# define CAN_30_MCAN_MAX_DATALEN_OBJ(Index) Can_30_Mcan_GetMailboxDataLen(Index)
#else
# define CAN_30_MCAN_MAX_DATALEN_OBJ(Index) 8u
#endif
#define CanHL_30_Mcan_IsFdMessage(id) (((id) & (Can_IdType)CAN_30_MCAN_ID_FD_MASK) == (Can_IdType)CAN_30_MCAN_ID_FD_MASK) /* \trace SPEC-60432, SPEC-50586 */
#define CanHL_30_Mcan_IsFdTxBrs(ch)   (Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(ch)) == CAN_30_MCAN_FD_RXTX) /* \trace SPEC-60432, SPEC-50586 */

/* PRQA L:FctLikeMacroLabel */

/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */
/* 
  parameter for Appl_30_McanCanTimerStart(),-End(), -Loop()
  index has to start with 0, continuous numbers have to be used. Gaps are not allowed! 
*/

# define kCan_30_McanACTIVE           0x00000001UL /* '1'= used to search or set the active connection  */ 
# define CanLL_30_Mcan_HwDlcMask      0x000F0000UL /* MCAN register layout */



/*
|<DataModelStart>| CanLL_30_Mcan_TxIsObjFree
Relation_Context:
# from CanTransmit, CanMsgTransmit, CanCopyDataAndStartTransmission() #
Relation:
ChannelAmount, TxBasicAmount
ChannelAmount, TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_30_Mcan_TxIsObjFree( hwCh, txObjHandle ) ( ((Cn->TXBC & kCanTXBC_TFQS) > 0UL) ? /* check Fifo/Queue size */ \
            (kCan_30_McanFalse!=kCan_30_McanFalse) :  /* N/A: Fifo/Queue exists with size != zero */ \
            ( ((Cn->TXBRP & ((vuint32)(kCanTXBRP_RP << (txObjHandle)))) == 0u) ) )   /* all buffers are dedicated buffers, return true if pending bit is not set */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
/* Each Tx Buffer has its own pending bit. 
   The bits are set via TXBAR. 
   The bits are reset after transmission has completed or has been cancelled (via TXBCR).

   A cancellation request resets the corresponding transmission request pending bit of register TXBRP. 
   The corresponding TXBCF bit is set for all unsuccessful transmissions.
   In DAR mode all transmissions are automatically cancelled if they are not successful. */



/* Power down mode
   Controlled by input signal clock stop request or via CCCR[CSR]. 
   As long as the clock stop request signal is active, bit CCCR[CSR] is read as one. 

   a) all pending transmission requests are completed
   b) Bus_Idle is awaited
   c) CCCR[INIT] is set to '1' (prevent any further CAN transfers)
   d) Clock stop acknowledge output signal =1, CCCR[CSA] =1 (M_CAN acknowledges that it is ready for power down)
   In this state, before the clocks are switched off, further register accesses can be made (write access to CCCR[INIT] has no effect)
   e) Module clock inputs (CAN and Host clock) may be switched off now */
/*
|<DataModelStart>| CanLL_30_Mcan_HwIsStop
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_30_Mcan_HwIsStop( hwCh )   ((Cn->CCCR & kCanCCCR_INIT) != 0UL)

/*
|<DataModelStart>| CanLL_30_Mcan_HwIsBusOff
Relation_Context:
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/

#define CanLL_30_Mcan_HwIsBusOff( hwCh ) ((Cn->PSR & kCanPSR_BO) != 0UL)

#if defined( C_30_MCAN_ENABLE_EXTENDED_STATUS )||defined(CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
/*
|<DataModelStart>| CanLL_30_Mcan_HwIsPassive
Relation_Context:
Relation:
CanGetStatus, OneChOpt, ChannelAmount, CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/


# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#  define CanLL_30_Mcan_HwIsPassive( hwCh ) ((Can_30_McanRxActualErrorCounter() >= 128u) || (Can_30_McanTxActualErrorCounter() >= 128u))
# else
#  define CanLL_30_Mcan_HwIsPassive( hwCh ) ((Can_30_McanRxActualErrorCounter(hwCh) >= 128u) || (Can_30_McanTxActualErrorCounter(hwCh) >= 128u))
# endif

#endif

#if defined( C_30_MCAN_ENABLE_EXTENDED_STATUS )
/*
|<DataModelStart>| CanLL_30_Mcan_HwIsWarning
Relation_Context:
Relation:
CanGetStatus, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/


# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#  define CanLL_30_Mcan_HwIsWarning( hwCh ) ((Can_30_McanRxActualErrorCounter() >= 96u) || (Can_30_McanTxActualErrorCounter() >= 96u))
# else
#  define CanLL_30_Mcan_HwIsWarning( hwCh ) ((Can_30_McanRxActualErrorCounter(hwCh) >= 96u) || (Can_30_McanTxActualErrorCounter(hwCh) >= 96u))
# endif
#endif /* C_30_MCAN_ENABLE_EXTENDED_STATUS */


#if defined( C_30_MCAN_ENABLE_HW_LOOP_TIMER )
# if defined(C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL)
#  define CanLL_30_Mcan_ApplCanTimerStart(loop)  Appl_30_McanCanTimerStart(channel, loop)
#  define CanLL_30_Mcan_ApplCanTimerEnd(loop)    Appl_30_McanCanTimerEnd(channel, loop)
#  define CanLL_30_Mcan_ApplCanTimerLoop(loop)   Appl_30_McanCanTimerLoop(channel, loop)
# else
#  define CanLL_30_Mcan_ApplCanTimerStart(loop)  Appl_30_McanCanTimerStart(loop)
#  define CanLL_30_Mcan_ApplCanTimerEnd(loop)    Appl_30_McanCanTimerEnd(loop)
#  define CanLL_30_Mcan_ApplCanTimerLoop(loop)   Appl_30_McanCanTimerLoop(loop)
# endif
#else
# define CanLL_30_Mcan_ApplCanTimerStart(loop)
# define CanLL_30_Mcan_ApplCanTimerEnd(loop)
# define CanLL_30_Mcan_ApplCanTimerLoop(loop)    (vuint8)(1u)
#endif

#if defined(CAN_30_MCAN_C_ENABLE_ARM_CORTEX_M) /* COV_CAN_HW_SPECIFIC */
# if defined ( V_COMP_KEIL ) || \
     defined ( V_COMP_GHS )  || \
     defined ( V_COMP_ARM )  
#  define V_ASM   __asm               /* PRQA S 3431 */ /* MD_Can_3431_LL */
# else
#  define V_ASM   asm                 /* PRQA S 3431 */ /* MD_Can_3431_LL */
# endif
# define CAN_MSG_RAM_SYNC()   V_ASM(" DMB") /* Data Memory Barrier (DMB) */
/* Ensures that all explicit data memory transfers before the DMB are completed 
   before any subsequent data memory transfers after the DMB starts.
 */
#else
# define CAN_MSG_RAM_SYNC()   
#endif


#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
# if !defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )
#  error "C_30_MCAN_ENABLE_CAN_RAM_CHECK has to be defined if C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED is set."
# endif
#endif


 

 
#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
#  if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#    define CAN_30_MCAN_RAM_CHECK_BEGIN_REG_REGEXT_RESULT(ch) CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT()
#  else
#    define CAN_30_MCAN_RAM_CHECK_BEGIN_REG_REGEXT_RESULT(ch) CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT((ch))
#  endif
# endif
#endif

/* PRQA L:FctLikeMacroLabel */

/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* BR:012 */
V_DEF_30_MCAN_CONST(V_NONE, uint8, CONST) Can_30_Mcan_MainVersion         = (uint8)CAN_30_MCAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_30_MCAN_CONST(V_NONE, uint8, CONST) Can_30_Mcan_SubVersion          = (uint8)CAN_30_MCAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_30_MCAN_CONST(V_NONE, uint8, CONST) Can_30_Mcan_ReleaseVersion      = (uint8)CAN_30_MCAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */


#if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
V_DEF_30_MCAN_CONST(CAN_STATIC, uint8, CONST) Can_30_Mcan_DlcToFrameLenght[16] = /* PRQA S 3218,3408 */ /* MD_Can_GlobalScope */
{
  0u,  1u,  2u,  3u,
  4u,  5u,  6u,  7u,
  8u, 12u, 16u, 20u,
 24u, 32u, 48u, 64u
};
V_DEF_30_MCAN_CONST(CAN_STATIC, uint8, CONST) Can_30_Mcan_MessageLengthToDlc[65] = /* PRQA S 3218,3408 */ /* MD_Can_GlobalScope */
{
/* 00..07 */  0u,  1u,  2u,  3u,  4u,  5u,  6u,  7u,
/* 08..15 */  8u,  9u,  9u,  9u,  9u, 10u, 10u, 10u,
/* 16..23 */ 10u, 11u, 11u, 11u, 11u, 12u, 12u, 12u,
/* 24..31 */ 12u, 13u, 13u, 13u, 13u, 13u, 13u, 13u,
/* 32..39 */ 13u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 40..47 */ 14u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 48..55 */ 14u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 56..63 */ 15u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 64     */ 15u
};
#endif

/* Global constants with CAN driver main and subversion */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )
/* ROM CATEGORY 4 START */
V_DEF_30_MCAN_CONST(CAN_STATIC, vuint32, CONST) Can_30_McanMemCheckValues32bit[3] =  /* PRQA S 3218 */ /* MD_Can_GlobalScope */
{
  0xAAAAAAAAUL, 0x55555555UL, 0x00000000UL
};
/* ROM CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
/* ROM CATEGORY 4 START */
V_DEF_30_MCAN_CONST(CAN_STATIC, vuint32, CONST) Can_30_McanRegCheckValues32bit[4] =  /* PRQA S 3218 */ /* MD_Can_GlobalScope */
{
  0xAAAAAAAAUL, 0x55555555UL, 0xAAAAAAAAUL, 0x00000000UL
};
/* ROM CATEGORY 4 END */
#endif

#if defined(C_30_MCAN_ENABLE_CAN_FD_FULL) 
V_DEF_30_MCAN_CONST(CAN_STATIC, vuint8, CONST) CanLL_30_Mcan_xES2Bytes[8] =
{
  8, 12, 16, 20,
 24, 32, 48, 64
};
#endif


#define CAN_30_MCAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined (C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION)
# if defined( C_30_MCAN_ENABLE_INIT_POST_PROCESS )
V_DEF_30_MCAN_VAR(V_NONE, vuint16, VAR_NOINIT) Can_McanRevision[kCan_30_McanNumberOfChannels];
# endif
#endif

/***************************************************************************************/
/* local data definitions   (need also INFIX because STATIC may be defined to nothing) */
/***************************************************************************************/
/* \trace SPEC-1585 */
/*! Semaphore to block reentrancy for Can_30_Mcan_MainFunction_Read() */
V_DEF_30_MCAN_VAR(CAN_STATIC, uint8, VAR_NOINIT) can_30_McanIsRxTaskLocked; /* PRQA S 3408 */ /* MD_Can_GlobalScope */


#if defined (C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION)
# if !defined( C_30_MCAN_ENABLE_INIT_POST_PROCESS )
V_DEF_30_MCAN_VAR(CAN_STATIC, vuint16, VAR_NOINIT) Can_McanRevision[kCan_30_McanNumberOfChannels];
# endif
#endif

#define CAN_30_MCAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define CAN_30_MCAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ! Mark module to be initialized (used to check double/none initialization) */
V_DEF_30_MCAN_VAR(CAN_STATIC, uint8, VAR_INIT) can_30_McanConfigInitFlag = CAN_30_MCAN_STATUS_UNINIT; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
# define CAN_30_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* not static because of debug/test usage */
#if defined(CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_30_MCAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_30_MCAN_P2CONST (V_NONE, Can_30_Mcan_ConfigType, VAR_INIT, CONST_PBCFG) Can_30_Mcan_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */ /* PRQA S 3408 */ /* MD_Can_ExternalScope */
# define CAN_30_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#else
# define CAN_30_MCAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_30_MCAN_CONSTP2CONST(V_NONE, Can_30_Mcan_ConfigType, CONST, CONST_PBCFG) Can_30_Mcan_ConfigDataPtr = NULL_PTR; /* PRQA S 3408,1514 */ /* MD_Can_ExternalScope */
# define CAN_30_MCAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/***************************************************************************/
/*  Safe Check                                                             */
/***************************************************************************/
#if !defined(CAN_30_MCAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_SAFE_BSW   STD_OFF
#else
# if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
#  if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_OFF) || (CAN_30_MCAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW_EXCLUSION */
#   error "Unsupported Feature activated for SafeBSW"
#  endif
# endif
#endif

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
# if (CAN_30_MCAN_SLEEP_SUPPORT == STD_ON) && (CAN_30_MCAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_30_MCAN_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#if (CAN_30_MCAN_WAKEUP_SUPPORT == STD_ON) && (CAN_30_MCAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_30_MCAN_WAKEUP_SUPPORT need activated CAN_30_MCAN_SLEEP_SUPPORT"
#endif
#if defined(C_30_MCAN_ENABLE_HW_LOOP_TIMER)
# if (CAN_30_MCAN_LOOP_MAX == 0)
#  error "CAN_30_MCAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_30_MCAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_30_MCAN_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
# if (CAN_30_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_30_MCAN_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#if (CAN_30_MCAN_MIRROR_MODE == STD_ON) && (!defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2) || (CAN_30_MCAN_GENERIC_PRECOPY == STD_OFF))
# error "CAN_30_MCAN_MIRROR_MODE need CAN_30_MCAN_GENERIC_CONFIRMATION with CAN_30_MCAN_API2 and CAN_30_MCAN_GENERIC_PRECOPY as STD_ON"
#endif
#if (CAN_30_MCAN_MULTIPLE_BASICCAN_TX == STD_ON)
# if (CAN_30_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* cancellation does not work in CanHL_30_Mcan_WritePrepareCancelTx for multiple BasicCAN messages, and is not useful for FIFO queue in CanIf (normally combined with multiple BCAN)*/
# error "CAN_30_MCAN_MULTIPLE_BASICCAN_TX and CAN_30_MCAN_HW_TRANSMIT_CANCELLATION are STD_ON but this combination is not supported"
# endif
#endif


/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#  define CanHL_30_Mcan_ApplCanTimerStart( timerIdx )  Appl_30_McanCanTimerStart( timerIdx );
#  define CanHL_30_Mcan_ApplCanTimerEnd( timerIdx )    Appl_30_McanCanTimerEnd( timerIdx );
# else
#  define CanHL_30_Mcan_ApplCanTimerStart( timerIdx )  Appl_30_McanCanTimerStart( channel, (timerIdx) );
#  define CanHL_30_Mcan_ApplCanTimerEnd( timerIdx )    Appl_30_McanCanTimerEnd( channel, (timerIdx) );
# endif
# define CanHL_30_Mcan_ApplCanTimerLoop( timerIdx )   if (Appl_30_McanCanTimerLoop(CAN_30_MCAN_CHANNEL_CANPARA_FIRST (timerIdx)) != CAN_OK) \
                                              { \
                                                break; \
                                              }

# if (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_OFF)
/* Internal handling of HW loops (like AutoSar) - otherwise ApplCanTimer... is defined an implemented by Application */
/****************************************************************************
| NAME:             Appl_30_McanCanTimerStart
****************************************************************************/
/* Used as macro to save runtime and code */
#  if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
/* \trace SPEC-1640 */
#    define Appl_30_McanCanTimerStart(source)     ((void)GetCounterValue( CAN_30_MCAN_OS_COUNTER_ID, &Can_30_Mcan_GetCanLoopTimeout(0, (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#    define Appl_30_McanCanTimerStart(ch, source) ((void)GetCounterValue( CAN_30_MCAN_OS_COUNTER_ID, &Can_30_Mcan_GetCanLoopTimeout((ch), (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
/****************************************************************************
| NAME:             Appl_30_McanCanTimerLoop
****************************************************************************/
/*
|<DataModelStart>| ApplCanTimerLoop
Relation_Context:
# from mode transition + any LL #
HardwareLoopCheck, HardwareCancelByAppl
Relation:
DevErrorDetect, OneChOpt
HardwareLoopCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) Appl_30_McanCanTimerLoop( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 source )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  uint8 errorId;
  uint8 apiId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  apiId = CAN_30_MCAN_HW_ACCESS_ID;
  retval = CAN_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and source is valid (no INIT check because may be used inside power on INIT) */
  if (source > CAN_30_MCAN_LOOP_MAX) /* CM_CAN_HL22 */
  {
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
#   if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TickType elapsedTime;
    TickType startTime;
    /* #110 Calculate the elapsed since time the start of this hardware loop (identified by parameter source). */
    /* Get start time (set by ApplCanTimerStart - temporary variable because GetElapsedValue modify original data */
    startTime = Can_30_Mcan_GetCanLoopTimeout(channel, source);
    /* Get elapsed time - from start time to now */
    /* #120 Throw DET error when GetElapsedValue() failed */
    if ( GetElapsedValue( CAN_30_MCAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != (StatusType)E_OK ) /* SBSW_CAN_HL37 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_30_MCAN_E_TIMEOUT_DET;
    }
    else
    {
      /* #130 Check if time out occurs for HW loop checks (none mode transition) \trace SPEC-1594 */
      if ( (TickType)CAN_30_MCAN_OS_TICK2MS( elapsedTime ) < (TickType)CAN_30_MCAN_TIMEOUT_DURATION ) /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 1840, 2985 */ /* MD_Can_IntegerCast, MD_Can_ConstValue */
      { /* no time out occur return OK */
        retval = CAN_OK;
      }
      else /* only used in case C_30_MCAN_ENABLE_HW_LOOP_TIMER but removed because of coverage TX for some organiy cases */
      { /* Mode Change synchronous & HW loop check */
        /* #140 Throw DET error and set hardware cancellation flag */
        if (source < CAN_30_MCAN_LOOP_MAX) /* COV_CAN_HARDWARE_FAILURE */
        { 
          errorId = CAN_30_MCAN_E_TIMEOUT_DET;
        }
      }
    }
    CAN_30_MCAN_DUMMY_STATEMENT(startTime); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)  
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(apiId, errorId);
  }
#  else
  CAN_30_MCAN_DUMMY_STATEMENT(apiId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/****************************************************************************
| NAME:             Appl_30_McanCanTimerEnd
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define Appl_30_McanCanTimerEnd Appl_30_McanCanTimerStart
# endif /* (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_OFF) */


/****************************************************************************
| NAME:             CanHL_30_Mcan_CleanUpSendState
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_CleanUpSendState
Relation_Context:
# from CanLL_30_Mcan_ModeTransition() #
Relation:
OneChOpt, ChannelAmount
MultiplexedTx
TxFullCANSupport
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_CleanUpSendState( CAN_30_MCAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_30_McanObjectHandle activeSendObject;
  Can_30_McanObjectHandle mailboxHandle;
  Can_HwHandleType mailboxElement;
  /* ----- Implementation ----------------------------------------------- */
  /* parameter channel is already checked by caller */
  /* #10 set all BasicCAN TX Objects to state FREE to allow a new transmission */
  mailboxHandle = Can_30_Mcan_GetTxBasicHandleStart(canHwChannel);
# if defined(C_30_MCAN_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; mailboxHandle < Can_30_Mcan_GetTxBasicHandleStop(canHwChannel); mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
# endif
  {
# if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    for (mailboxElement = 0u; mailboxElement < Can_30_Mcan_GetMailboxSize(mailboxHandle); mailboxElement++) /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
# else
    mailboxElement = 0u; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
# endif
    {
      activeSendObject = CanHL_30_Mcan_GetActiveSendObject(mailboxHandle, mailboxElement);
      Can_30_Mcan_SetActiveSendState(activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
    }
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if (Can_30_Mcan_GetMailboxType(mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #20 initialize TxHwFifo index and fill state */
      uint16 txHwFifo;
      txHwFifo = Can_30_Mcan_GetMailboxTxHwFifo(mailboxHandle);
#  if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
      if (txHwFifo >= (uint16)Can_30_Mcan_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
      {
        txHwFifo = 0u;
      }
#  endif
      Can_30_Mcan_SetTxHwFifoWriteIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_30_Mcan_SetTxHwFifoReadIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_30_Mcan_SetTxHwFifoFillCount(txHwFifo, 0u); /* SBSW_CAN_HL50 */
    }
# endif
  }
# if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
  /* #30 set all FullCAN TX Objects to state FREE to allow a new transmission */
  for (mailboxHandle = Can_30_Mcan_GetTxFullHandleStart(canHwChannel); mailboxHandle < Can_30_Mcan_GetTxFullHandleStop(canHwChannel); mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
  {
    activeSendObject = CanHL_30_Mcan_GetActiveSendObject(mailboxHandle, 0u); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    Can_30_Mcan_SetActiveSendState(activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */ 
  }
# endif
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/****************************************************************************
| NAME:             CanHL_30_Mcan_ReInit
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_ReInit
Relation_Context:
# from CanHL_30_Mcan_ModeTransition() #
Wakeup, OneChOpt, ChannelAmount
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
RamCheck
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Wakeup, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_30_Mcan_ReInit( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck )
{ /* \trace SPEC-1719, SPEC-1589, SPEC-1346, SPEC-1565 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCan_30_McanInitParaStruct initPara;
  CanHookBegin_CanHL_30_Mcan_ReInit();
  errorId = CAN_30_MCAN_E_NO_ERROR;
  initPara.isInitOk = kCan_30_McanFailed; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Config pointer is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* \trace SPEC-1718 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1713 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* \trace SPEC-1713 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 initialization controller states and initialization objects --- */
    initPara.initObject = Can_30_Mcan_GetLastInitObject(channel);
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    initPara.doRamCheck = doRamCheck;
#endif
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
    initPara.isChRamCheckFail = kCan_30_McanFalse;
#endif
    /* #110 clean up status (do not activate communication and let SLEEP and initialization to detect ram-check request) */
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK) && !defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
    if (doRamCheck == kCan_30_McanExecuteRamCheck)
    { /* #112 standard RAM check will be performed so delete old status CAN_DEACTIVATE_CONTROLLER but leave CAN_STATUS_INIT (info about PowerOn) */
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) & (uint8)CAN_30_MCAN_STATUS_INIT);  /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #114 extended RAM check may be performed so delete old status except CAN_DEACTIVATE_CONTROLLER and CAN_STATUS_INIT */
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) & ((uint8)(CAN_30_MCAN_DEACTIVATE_CONTROLLER) | (uint8)((uint8)CAN_30_MCAN_STATUS_INIT)));  /* SBSW_CAN_HL02 */
    }
    /* #125 begin initialization CanHL_30_Mcan_InitBegin() */
    initPara.isInitOk = CanHL_30_Mcan_InitBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
    /* #130 block invalid hardware access (silent check) */
    if (initPara.isInitOk == kCan_30_McanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    {
#if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
      /* #140 do TX FullCAN initialization CanHL_30_Mcan_InitTxFullCAN()*/
      initPara.isInitOk &= CanHL_30_Mcan_InitTxFullCAN(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#endif
      /* #150 do TX BasicCAN initialization CanHL_30_Mcan_InitTxBasicCAN() */
      initPara.isInitOk &= CanHL_30_Mcan_InitTxBasicCAN(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
      /* #170 do RX FullCAN initialization CanHL_30_Mcan_InitRxFullCAN() */
      initPara.isInitOk &= CanHL_30_Mcan_InitRxFullCAN(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#endif
#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
      /* #180 do RX BasicCAN initialization CanHL_30_Mcan_InitRxBasicCAN() */
      initPara.isInitOk &= CanHL_30_Mcan_InitRxBasicCAN(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#endif
      /* #190 end initialization CanHL_30_Mcan_InitEnd_InitMode() */
      initPara.isInitOk &= CanHL_30_Mcan_InitEnd_InitMode(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
      if (doRamCheck == kCan_30_McanExecuteRamCheck)
      { 
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
        /* #200 extended RamChecks new issue occur - notify corrupt register / deactivate controller */
        if (initPara.isChRamCheckFail == kCan_30_McanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          CanIf_30_Mcan_RamCheckCorruptController((uint8)Can_30_Mcan_GetCanToCanIfChannelMapping(channel));
          Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
        }
# else
        if( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) == CAN_30_MCAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        { /* #210 standard RAM check issue occur - call Appl_CanRamCheckFailed() (any mailbox fail) */
          if (Appl_30_Mcan_CanRamCheckFailed((uint8)channel) != CAN_30_MCAN_DEACTIVATE_CONTROLLER)
          { /* #220 let the application decide if communication stay disabled as set by RAM check or not */
            Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) & (uint8)(~(CAN_30_MCAN_DEACTIVATE_CONTROLLER))); /* Application decide to activate communication in case RAM_CHECK failed */  /* SBSW_CAN_HL02 */
          }
        }
# endif
        CAN_30_MCAN_RAM_CHECK_FINISHED_CTP(channel)
      }
#endif
    }
    if (initPara.isInitOk == kCan_30_McanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    { /* #280 set controller init flag when no issue occure before */
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | (CAN_30_MCAN_STATUS_INIT)); /* SBSW_CAN_HL02 */
    }
    else
    { /* #275 set error when issue occure before */
      Can_30_Mcan_SetLogStatus(channel, /* CAN_30_MCAN_STATUS_UNINIT | */ (Can_30_Mcan_GetLogStatus(channel) & (uint8)(CAN_30_MCAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      errorId = CAN_30_MCAN_E_UNINIT;
    }
  } /* controller active in multiple ECU configuration */

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INITCTR_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if !defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  CAN_30_MCAN_DUMMY_STATEMENT(doRamCheck); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_CanHL_30_Mcan_ReInit();
  return initPara.isInitOk;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             CanHL_30_Mcan_ModeTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_ModeTransition
Relation_Context:
# from Can_30_Mcan_Init #
ChannelAmount
# from Can_30_Mcan_MainFunction_BusOff, CanHL_30_Mcan_ErrorHandling #
StatusPolling, ChannelAmount
# from Can_30_Mcan_ChangeBaudrate #
ChannelAmount
# from Can_30_Mcan_SetBaudrate #
ChannelAmount
# from Can_30_Mcan_SetControllerMode #
Wakeup
RamCheck
# from Can_30_Mcan_RamCheckExecute #
RamCheck
# from Can_30_Mcan_RamCheckEnableController #
RamCheck
Relation:
OneChOpt, HardwareLoopCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_ModeTransition( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 transitionState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition in LL */
  transitionState = CanLL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
  if(transitionState != kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */
  { /* #20 first request fail so start Loop that wait short time for transition \trace SPEC-1642, SPEC-1635, SPEC-1630 */
    CanHL_30_Mcan_ApplCanTimerStart((uint8)CAN_30_MCAN_LOOP_MAX); /* SBSW_CAN_HL38 */
    do
    { /* #30 HW check mode reached (LL) */
      transitionState = CanLL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
      CanHL_30_Mcan_ApplCanTimerLoop((uint8)CAN_30_MCAN_LOOP_MAX); /* COV_CAN_TRANSITION_REQUEST */
    } while ( transitionState != kCan_30_McanOk ); /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 2990,2995 */ /* MD_Can_ConstValue */
    CanHL_30_Mcan_ApplCanTimerEnd ((uint8)CAN_30_MCAN_LOOP_MAX); /* SBSW_CAN_HL38 */ /* PRQA S 2843 */ /* MD_Can_HL_DereferencePointerValue */
  }
  if ( transitionState == kCan_30_McanRequested ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #50 transition requested so remember request to repeat it asynchronous */
    Can_30_Mcan_SetModeTransitionRequest(channel, transitionRequest); /* SBSW_CAN_HL01 */
    Can_30_Mcan_SetBusOffTransitionRequest(channel, busOffRecovery); /* SBSW_CAN_HL01 */
    Can_30_Mcan_SetRamCheckTransitionRequest(channel, doRamCheck); /* SBSW_CAN_HL01 */
  }
  return transitionState;
}

/****************************************************************************
| NAME:             CanHL_30_Mcan_NotifyTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_NotifyTransition
Relation_Context:
# from Can_30_Mcan_SetControllerMode() #
Wakeup
RamCheck
Relation:
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_NotifyTransition( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState )
{
  /* #10 if mode changed successful */
  if ( transitionState == kCan_30_McanOk ) /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #20 transition finished change internal state */
    Can_30_Mcan_SetLogStatus(channel, (uint8)((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_MASK_NOMODE) | canState)); /* SBSW_CAN_HL02 */
    /* #30 remove transition request */
    Can_30_Mcan_SetModeTransitionRequest(channel, kCan_30_McanModeNone); /* SBSW_CAN_HL01 */
    /* #40 call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_30_Mcan_ControllerModeIndication( (uint8)Can_30_Mcan_GetCanToCanIfChannelMapping(channel), canIfState );
  }
  CAN_30_MCAN_DUMMY_STATEMENT(transitionState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}


/****************************************************************************
| NAME:             CanHL_30_Mcan_WritePrepare
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_WritePrepare
Relation_Context:
# from Can_30_Mcan_Write() #
Relation:
TxFullCANSupport
MultiplexedTx, TxHwFifo
MultiplexedTx, HwCancelTx, IdenticalIdCancel
ChannelAmount
OneChOpt
TxBasicAmount
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_WritePrepare( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 calculate logical TX mailbox handle for FullCAN or for BasicCAN (Multiplexed TX) as start value */
  txPara->mailboxElement = 0u; /* PRQA S 2982 */ /* MD_MSR_RetVal */ /* SBSW_CAN_HL42 */
  txPara->activeSendObject = CanHL_30_Mcan_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
#if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
  if ( Can_30_Mcan_GetMailboxType(txPara->mailboxHandle) != CAN_30_MCAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  { /* #20 BasicCAN preparation - search for hardware and logical transmit handle and do cancellation */
#if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO) 
    Can_30_McanObjectHandle mailboxElement_max;
    mailboxElement_max = Can_30_Mcan_GetMailboxSize(txPara->mailboxHandle); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    /* \trace SPEC-1677, SPEC-1672, SPEC-1679, SPEC-1673, SPEC-1671 */
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if (Can_30_Mcan_GetMailboxType(txPara->mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #25 in case of FIFO object set logical TX mailbox handle to write index + element start  */
       txPara->mailboxElement = (Can_30_McanObjectHandle)Can_30_Mcan_GetTxHwFifoWriteIndex(Can_30_Mcan_GetMailboxTxHwFifo(txPara->mailboxHandle)); /* SBSW_CAN_HL42 */
       txPara->activeSendObject += txPara->mailboxElement; /* SBSW_CAN_HL42 */
    }
    else
# endif
    { /* #27 if normal or Mux Tx search from first to last element 0..1 or 0..3 for free object or one to be cancelled */
      Can_30_McanObjectHandle mailboxElementFound;
      Can_30_McanObjectHandle activeSendObjectFound;
      mailboxElementFound = mailboxElement_max; /* PRQA S 2982 */ /* MD_MSR_RetVal */
      activeSendObjectFound = mailboxElement_max; /* PRQA S 2982 */ /* MD_MSR_RetVal */
      for (txPara->mailboxElement = 0u; txPara->mailboxElement < mailboxElement_max; txPara->mailboxElement++) /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
      { /* #30 over all multiplexed TX objects: find free mailbox or mailbox with identical ID */
        if (Can_30_Mcan_GetActiveSendState(txPara->activeSendObject) == kCan_30_McanBufferFree)
        { /* #60 None Identical ID: else priority 1 - find free mailbox (no cancellation) */
          mailboxElementFound = txPara->mailboxElement;
          activeSendObjectFound = txPara->activeSendObject;
          break;
        }
        txPara->activeSendObject++; /* SBSW_CAN_HL42 */
      }
      if (mailboxElementFound == mailboxElement_max)
      { /* #90 no free or cancel mailbox found: return values set to valid element or to found element and cancel */
        txPara->mailboxElement = 0u; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = CanHL_30_Mcan_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
      }
      else
      {
        txPara->mailboxElement = mailboxElementFound; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = activeSendObjectFound; /* SBSW_CAN_HL42 */
      }
    } /* normal or mux tx */
#endif
  } /* end BasicCAN handling */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #200 no special FullCAN handling needed */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( defined(C_30_MCAN_ENABLE_TX_HW_FIFO) && defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/****************************************************************************
| NAME:             CanHL_30_Mcan_WriteSavePduInfo
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_WriteSavePduInfo
Relation_Context:
# from CanHL_30_Mcan_WritePrepareCancelTx #
HwCancelTx
# from CanHL_30_Mcan_WriteStart #
TxHwFifo, GenericConfirmation
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_WriteSavePduInfo( CanTxTransmissionParaStructPtr txPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
    /* #10 Get buffer to store data */
    uint16 activeSendData;
    activeSendData = CanHL_30_Mcan_GetActiveSendData(txPara->mailboxHandle, txPara->mailboxElement);
    /* #20 SDU pointer may be a null pointer in case the DLC is 0 - so do not copy data in this case */
    if(txPara->pdu.sdu != NULL_PTR)
    {
# if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
      if(Can_30_Mcan_GetSizeOfActiveSendData() >= (activeSendData + txPara->pdu.length)) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
# endif
      {
        /* #25 copy data with VStdLib optimized copy routine */
        VStdMemCpy((void*)&Can_30_Mcan_GetActiveSendData(activeSendData), (void*)txPara->pdu.sdu, txPara->pdu.length); /* SBSW_CAN_HL22 */ /* PRQA S 0314,0316 */ /* MD_Can_PointerVoidCast */
      }
    }
    /* #30 copy ID, DLC and pointer to data (also pdu as part of PduInfo struct) */
    Can_30_Mcan_SetActiveSendId(txPara->activeSendObject, txPara->pdu.id); /* SBSW_CAN_HL23 */
    Can_30_Mcan_SetActiveSendLength(txPara->activeSendObject, txPara->pdu.length); /* SBSW_CAN_HL23 */
    Can_30_Mcan_SetActiveSendSdu(txPara->activeSendObject, &Can_30_Mcan_GetActiveSendData(activeSendData)); /* SBSW_CAN_HL23 */
    Can_30_Mcan_SetActiveSendSwPduHandle(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL23 */
}
#endif


/****************************************************************************
| NAME:             CanHL_30_Mcan_WriteStart
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_WriteStart
Relation_Context:
# from Can_30_Mcan_Write #
Relation:
GenericPreTransmit
TxHwFifo, GenericConfirmation
IDType
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_30_Mcan_WriteStart( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 free TX mailbox found so start transmission \trace SPEC-1744 */
  if (Can_30_Mcan_GetActiveSendState(txPara->activeSendObject) == kCan_30_McanBufferFree)
  {
    uint8 llretval;
    /* #20 remember PDU and send state to use it in Confirmation function \trace SPEC-1675 */
    Can_30_Mcan_SetActiveSendPdu(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL05 */
    Can_30_Mcan_SetActiveSendState(txPara->activeSendObject, kCan_30_McanBufferSend); /* SBSW_CAN_HL04 */
#if defined(C_30_MCAN_ENABLE_PRETRANSMIT_FCT)
    /* call pretransmit function ----------------------------------------------- */
    Appl_30_Mcan_GenericPreTransmit( (uint8)channel, &(txPara->pdu) );  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL24 */
#endif
#if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if (Can_30_Mcan_GetMailboxType(txPara->mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #30 in case of FIFO and GenericConfirmation API2 remember also data for confirmation function */
# if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
      CanHL_30_Mcan_WriteSavePduInfo(txPara); /* SBSW_CAN_HL49 */
# endif
      /* #40 set Fifo to next element (writing) */
      CanHL_30_Mcan_SetNextTxHwFifoWriteIndex(txPara); /* SBSW_CAN_HL49 */
    }
#endif
    /* #50 HW prepare transmission */
    CanLL_30_Mcan_TxBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    /* #60 Set ID, ID type and DLC in HW register depend on ID type */
    txPara->dlcRaw = MK_TX_DLC(CAN_30_MCAN_LEN2DLC(txPara->pdu.length)); /* SBSW_CAN_HL42 */
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
# if defined(C_30_MCAN_ENABLE_MIXED_ID)
    if ( ((txPara->pdu.id) & CAN_30_MCAN_ID_IDE_MASK) != CAN_30_MCAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
    }
    else
# endif
    {
      SET_PARASTRUCT_IDRAW_TX_EXT(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
    }
#else
    {
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
#endif
    /* set id, dlc in hardware */
    CanLL_30_Mcan_TxSetMailbox(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    if(txPara->pdu.sdu != NULL_PTR)
    { /* #70 Set CAN data in HW register (LL) - only when data pointer is not null \trace SPEC-1680, SPEC-1572, SPEC-1678, SPEC-60421 */
      txPara->CanMemCopySrcPtr = txPara->pdu.sdu; /* SBSW_CAN_HL42 */
      CanLL_30_Mcan_TxCopyToCan(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    }
    /* #80 HW start transmission (LL) */
    llretval = CanLL_30_Mcan_TxStart(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    if (llretval == kCan_30_McanFailed) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
    { /* #90 transmit request wasn't successful in LL part - free mailbox */
      retval = CAN_NOT_OK; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
      Can_30_Mcan_SetActiveSendState(txPara->activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
    }
    /* HW finish transmission (LL) */
    CanLL_30_Mcan_TxEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    CAN_30_MCAN_DUMMY_STATEMENT(llretval); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  else
  { /* #200 no free TX mailbox found so return busy - also in case cancellation (BasicCAN) was possible \trace SPEC-1754, SPEC-1764, SPEC-1747 */
    retval = CAN_BUSY;
  }
  return retval;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_30_Mcan_GetActiveSendObject
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_GetActiveSendObject
Relation_Context:
# from CanHL_30_Mcan_InitXXX() #
Wakeup, OneChOpt, ChannelAmount
# from CanHL_30_Mcan_WritePrepare #
# from CanHL_30_Mcan_TxTaskCancelationHandling #
HwCancelTx
# from CanHL_30_Mcan_CleanUpSendState #
# from Can_30_Mcan_CancelTx #
TransmitCancellationAPI
# from CanHL_30_Mcan_TxConfirmation #
Relation:
DevErrorDetect
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_30_McanObjectHandle, STATIC_CODE) CanHL_30_Mcan_GetActiveSendObject( Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_30_McanObjectHandle activeSendObject;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendObject = (Can_30_McanObjectHandle) Can_30_Mcan_GetMailboxActiveSendObject(mailboxHandle) + mailboxElement;
#if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
  if (activeSendObject >= (Can_HwHandleType)Can_30_Mcan_GetSizeOfActiveSendObject()) /* CM_CAN_HL03 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendObject = ((Can_HwHandleType)Can_30_Mcan_GetSizeOfActiveSendObject() - (Can_HwHandleType)1u);
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)  
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_WRITE_ID, CAN_30_MCAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendObject;
}

#if ( defined(C_30_MCAN_ENABLE_TX_HW_FIFO) && defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/****************************************************************************
| NAME:             CanHL_30_Mcan_GetActiveSendData
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_GetActiveSendData
Relation_Context:
HwCancelTx, TxHwFifo
# from CanHL_30_Mcan_WritePrepare #
# from CanHL_30_Mcan_TxTaskCancelationHandling #
HwCancelTx
# from Can_30_Mcan_CancelTx #
TransmitCancellationAPI
# from CanHL_30_Mcan_TxConfirmation #
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_30_Mcan_GetActiveSendData( Can_HwHandleType mailboxHandle, uint8 mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 activeSendData;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendData = (uint16) (Can_30_Mcan_GetMailboxActiveSendData(mailboxHandle) + ((uint16)mailboxElement * (uint16)Can_30_Mcan_GetMailboxDataLen(mailboxHandle)));
#if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
  if ((activeSendData + Can_30_Mcan_GetMailboxDataLen(mailboxHandle)) > Can_30_Mcan_GetSizeOfActiveSendData()) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendData = 0u;
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)  
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_WRITE_ID, CAN_30_MCAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendData;
}
#endif

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_30_Mcan_RamCheckMailboxNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_RamCheckMailboxNotification
Relation_Context:
# CanHL_30_Mcan_InitXXX() #
Wakeup, OneChOpt, ChannelAmount, RamCheck
Relation:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RamCheckMailboxNotification( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 deactivate mailbox */
  Can_30_Mcan_SetMailboxState(initPara->mailboxHandle, kCan_30_McanFailed); /* SBSW_CAN_HL34 */
  /* #20 deactivate controller */
  Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
  /* #30 notify application about corrupt mailbox */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
  CanIf_30_Mcan_RamCheckCorruptMailbox((uint8)Can_30_Mcan_GetCanToCanIfChannelMapping(channel), initPara->mailboxHandle);
# else
#  if defined(C_30_MCAN_ENABLE_NOTIFY_CORRUPT_MAILBOX) /* with Mailbox Notification */
  Appl_30_Mcan_CanCorruptMailbox((uint8)channel, (initPara->hwObjHandle));
#  endif
# endif
}
#endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_InitBegin
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitBegin
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitBegin( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanFailed; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  if (CanLL_30_Mcan_InitBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara) == kCan_30_McanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL31 */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #20 Execute pattern RamCheck */
    if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
    {
      initPara->isChRamCheckFail |= CAN_30_MCAN_RAM_CHECK_BEGIN_REG_RESULT(channel, initPara); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
    } 
#endif
    /* #30 Initialize controller registers (Begin section) */
    initOk = CanLL_30_Mcan_InitBeginSetRegisters(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
  }
  return initOk;
}

#if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_30_Mcan_InitTxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitTxFullCAN
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount, TxFullCANSupport
Relation:
RamCheck
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitTxFullCAN( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  Can_30_McanObjectHandle activeSendObject;
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanOk;
  /* #10 iterate over all FullCAN TX */
  for (initPara->mailboxHandle = Can_30_Mcan_GetTxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_30_Mcan_GetTxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #20 initialize FullCAN TX mailboxes */
    initPara->hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_30_Mcan_GetActiveSendObject(initPara->mailboxHandle, 0u);
    Can_30_Mcan_SetActiveSendState(activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for FullCAN TX mailboxes */
    isMbRamCheckFail = kCan_30_McanFalse;
    if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* TX initialization */
    mailboxState = CanLL_30_Mcan_InitMailboxTx(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCan_30_McanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCan_30_McanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_INIT) != CAN_30_MCAN_STATUS_INIT )
    { /* PowerOn */
      Can_30_Mcan_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCan_30_McanTrue) || (Can_30_Mcan_GetMailboxState(initPara->mailboxHandle) == kCan_30_McanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_30_Mcan_InitMailboxTxDeactivate(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCan_30_McanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_30_Mcan_RamCheckMailboxNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_InitTxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitTxBasicCAN
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
MultiplexedTx, TxHwFifo
TxHwFifo, GenericConfirmation, IfTxBuffer
TxBasicAmount
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitTxBasicCAN( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  Can_30_McanObjectHandle activeSendObject;
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
#endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanOk;
  initPara->mailboxHandle = Can_30_Mcan_GetTxBasicHandleStart(canHwChannel); /* SBSW_CAN_HL36 */
#if defined(C_30_MCAN_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; initPara->mailboxHandle < Can_30_Mcan_GetTxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */
#endif
  { /* #10 iterate over all logical BasicCAN TX */
#if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO) 
    Can_30_McanObjectHandle activeSendObjectStop;
#endif
    initPara->hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_30_Mcan_GetActiveSendObject(initPara->mailboxHandle, 0u);
#if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO) 
    activeSendObjectStop = activeSendObject + Can_30_Mcan_GetMailboxSize(initPara->mailboxHandle);
    for (; activeSendObject < activeSendObjectStop; activeSendObject++)
#endif
    { /* #20 initialize BasicCAN TX mailboxes */
      Can_30_Mcan_SetActiveSendState(activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
    }
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if (Can_30_Mcan_GetMailboxType(initPara->mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #25 initialize TxHwFifo index and fill state */
      uint16 txHwFifo;
      txHwFifo = Can_30_Mcan_GetMailboxTxHwFifo(initPara->mailboxHandle);
#  if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
      if (txHwFifo >= (uint16)Can_30_Mcan_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
      {
        txHwFifo = 0u;
        initOk = kCan_30_McanFailed;
      }
#  endif
      Can_30_Mcan_SetTxHwFifoWriteIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_30_Mcan_SetTxHwFifoReadIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_30_Mcan_SetTxHwFifoFillCount(txHwFifo, 0u); /* SBSW_CAN_HL50 */
    }
# endif
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for BasicCAN TX mailboxes */
    isMbRamCheckFail = kCan_30_McanFalse;
    if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
#endif
    /* TX initialization */
    mailboxState = CanLL_30_Mcan_InitMailboxTx(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985,2986 */ /* MD_Can_ConstValue */
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCan_30_McanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCan_30_McanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_INIT) != CAN_30_MCAN_STATUS_INIT )
    { /* PowerOn */
      Can_30_Mcan_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCan_30_McanTrue) || (Can_30_Mcan_GetMailboxState(initPara->mailboxHandle) == kCan_30_McanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_30_Mcan_InitMailboxTxDeactivate(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCan_30_McanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_30_Mcan_RamCheckMailboxNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
#endif
  }
  return initOk;
} /* PRQA S 6010 */ /* MD_MSR_STPTH */


#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_30_Mcan_InitRxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitRxFullCAN
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
RamCheck
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitRxFullCAN( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanOk;
  for (initPara->mailboxHandle = Can_30_Mcan_GetRxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_30_Mcan_GetRxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all FullCAN RX mailboxes */
    initPara->hwObjHandle=Can_30_Mcan_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for FullCAN RX mailboxes */
    isMbRamCheckFail = kCan_30_McanFalse;
    if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
# endif
    /* #30 set ID for FullCAN RX mailboxes (LL) */
# if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
#  if defined(C_30_MCAN_ENABLE_MIXED_ID)
    if ( ((Can_IdType)Can_30_Mcan_GetMailboxIDValue(initPara->mailboxHandle) & CAN_30_MCAN_ID_IDE_MASK) != CAN_30_MCAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
    {
      initPara->idType = kCan_30_McanIdTypeStd; /* SBSW_CAN_HL36 */
      SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_30_Mcan_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
    else
#  endif
    {
      initPara->idType = kCan_30_McanIdTypeExt; /* SBSW_CAN_HL36 */ /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      SET_PARASTRUCT_IDRAW_RX_EXT(initPara, Can_30_Mcan_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
    }
# else
    initPara->idType = kCan_30_McanIdTypeStd; /* SBSW_CAN_HL36 */
    SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_30_Mcan_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */ /* PRQA S 4491,2985 */ /* MD_Can_IntegerCast */
# endif
    /* #40 initialize FullCAN RX mailboxes */
    mailboxState = CanLL_30_Mcan_InitMailboxRxFullCan(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCan_30_McanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCan_30_McanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_INIT) != CAN_30_MCAN_STATUS_INIT )
    { /* PowerOn */
      Can_30_Mcan_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCan_30_McanTrue) || (Can_30_Mcan_GetMailboxState(initPara->mailboxHandle) == kCan_30_McanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_30_Mcan_InitMailboxRxFullCanDeactivate(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCan_30_McanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_30_Mcan_RamCheckMailboxNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_30_Mcan_InitRxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitRxBasicCAN
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitRxBasicCAN( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanOk;
  for (initPara->mailboxHandle = Can_30_Mcan_GetRxBasicHandleStart(canHwChannel); initPara->mailboxHandle < Can_30_Mcan_GetRxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all BasicCAN RX mailboxes */
    initPara->hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #20 RAM check for BasicCAN RX mailboxes */
    isMbRamCheckFail = kCan_30_McanFalse;
    if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_30_MCAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
# endif
    /* #30 initialize BasicCAN RX mailboxes */
    mailboxState = CanLL_30_Mcan_InitMailboxRxBasicCan(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    if(mailboxState == kCan_30_McanFailed) { /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
      isMbRamCheckFail = kCan_30_McanTrue; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    if( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_INIT) != CAN_30_MCAN_STATUS_INIT )
    { /* PowerOn */
      Can_30_Mcan_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCan_30_McanTrue) || (Can_30_Mcan_GetMailboxState(initPara->mailboxHandle) == kCan_30_McanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCan_30_McanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_30_Mcan_RamCheckMailboxNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_InitEnd_InitMode
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitEnd_InitMode
Relation_Context:
# CanHL_30_Mcan_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitEnd_InitMode( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCan_30_McanOk;
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* #10 Execute pattern RamCheck */
  if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
  {
    initPara->isChRamCheckFail |= CAN_30_MCAN_RAM_CHECK_END_REG_RESULT(channel, initPara); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  } 
#endif

  /* #20 HW specific initialization end */
  initOk &= CanLL_30_Mcan_InitEndSetRegisters(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  initOk &= CanLL_30_Mcan_InitEnd( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara ); /* SBSW_CAN_HL31 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  return initOk;
}

#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_30_Mcan_RxBasicCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_RxBasicCanPolling
Relation_Context:
# from Can_30_Mcan_MainFunction_Read #
RxBasicCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxBasicCanPolling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCan_30_McanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_30_Mcan_RxBasicIsGlobalIndPending(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all BasicCAN mailboxes */
    for (taskPara.mailboxHandle = Can_30_Mcan_GetRxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_30_Mcan_GetRxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    { /* loop over all BasicCAN mailboxes with gap */
      taskPara.hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_30_Mcan_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_30_Mcan_RxBasicProcessPendings(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_30_MCAN_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_30_Mcan_RxFullCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_RxFullCanPolling
Relation_Context:
# from Can_30_Mcan_MainFunction_Read #
RxFullCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxFullCanPolling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCan_30_McanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_30_Mcan_RxFullIsGlobalIndPending(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all FullCAN mailboxes */
    for (taskPara.mailboxHandle = Can_30_Mcan_GetRxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_30_Mcan_GetRxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    {
      taskPara.hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_30_Mcan_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_30_Mcan_RxFullProcessPendings(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_30_MCAN_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_30_Mcan_RxMsgReceivedNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_RxMsgReceivedNotification
Relation_Context:
# from CanHL_30_Mcan_FullCanMsgReceived #
RxFullCANSupport
# from CanHL_30_Mcan_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
RxQueue, GenericPreCopy, MirrorMode
RxQueue, DevErrorDetect
RxQueue, CanFdSupport
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_RxMsgReceivedNotification( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined(C_30_MCAN_ENABLE_RX_QUEUE) && (CAN_30_MCAN_GENERIC_PRECOPY == STD_ON)
  Can_ReturnType generic_retval;
# endif
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 RX queue */
# if defined(C_30_MCAN_ENABLE_RX_QUEUE)
  /**************************** RxQueue handling **********************************/
    /* #20 EXCLUSIVE_AREA_4 secure RxQueue data handling */
  SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_4();
  if (Can_30_Mcan_GetRxQueueInfo().Count < Can_30_Mcan_GetSizeOfRxQueueBuffer()) /* COV_CAN_GENDATA_FAILURE */
  { /* #30 Queue not full: */
    /* #45 copy HRH, ID, DLC and data to RX queue */
    Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().WriteIndex).Hrh = rxStructPtr->localMailboxHandle; /* SBSW_CAN_HL18 */
    Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().WriteIndex).id  = rxStructPtr->localId; /* SBSW_CAN_HL18 */
    Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().WriteIndex).dlc = rxStructPtr->localDlc; /* SBSW_CAN_HL18 */

#  if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
    if (((uint8) (sizeof(Can_30_Mcan_GetRxQueueBuffer(0).data) / sizeof(Can_30_Mcan_GetRxQueueBuffer(0).data[0]))) < rxStructPtr->localDlc) /* CM_CAN_HL17 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_30_MCAN_E_PARAM_DLC;
    }
    else
#  endif
    {
      /* #46 copy data with VStdLib optimized copy routine */
      VStdMemCpy((void*)Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().WriteIndex).data, (void*)rxStructPtr->pChipData, rxStructPtr->localDlc); /* SBSW_CAN_HL19 */ /* PRQA S 0312,0314,0316 */ /* MD_Can_NoneVolatilePointerCast,MD_Can_PointerVoidCast,MD_Can_PointerVoidCast */
    }
      /* #47 increase pointer to next queue element */ 
    Can_30_Mcan_GetRxQueueInfo().Count++; /* SBSW_CAN_HL55 */ /* PRQA S 3387 */ /* MD_Can_HL_UsingIncOrDec */
    if (Can_30_Mcan_GetRxQueueInfo().WriteIndex < ((uint16)Can_30_Mcan_GetSizeOfRxQueueBuffer() - (uint16)1u) )
    {
      Can_30_Mcan_GetRxQueueInfo().WriteIndex++; /* SBSW_CAN_HL55 */ /* PRQA S 3387 */ /* MD_Can_HL_UsingIncOrDec */
    }
    else
    {
      Can_30_Mcan_GetRxQueueInfo().WriteIndex = 0u; /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
    }
  }
#  if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  else 
  { /* #50 Queue full: last message will be lost -> overrun in queue do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
    errorId = CAN_30_MCAN_E_RXQUEUE;
  }
#  endif
  SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_4();
# else /* C_30_MCAN_ENABLE_RX_QUEUE */
  /* #100 no RX queue */
  /* -------------------------- Interface + APPL Notifications --- */
    /* #110 call Appl_GenericPrecopy() depend on configuration and if mirror mode is active */
#  if (CAN_30_MCAN_GENERIC_PRECOPY == STD_ON)
#   if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
  if (Can_30_Mcan_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
  { /* do not call Appl_GenericPrecopy() in case mirror mode was disabled */
    generic_retval = CAN_OK;
  }
  else
#   endif
  {
    generic_retval = Appl_30_Mcan_GenericPrecopy((uint8)channel, (rxStructPtr->localId & CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT), rxStructPtr->localDlc, (Can_30_Mcan_DataPtrType)rxStructPtr->pChipData);  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
  if (generic_retval == CAN_OK) /* \trace SPEC-15119 */
#  endif
  { /* #120 call CanIf_RxIndication() if mirror mode is no active or Appl_GenericPrecopy() return OK \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
    CanIf_30_Mcan_RxIndication(rxStructPtr->localMailboxHandle, rxStructPtr->localId, rxStructPtr->localDlc, (Can_30_Mcan_DataPtrType)rxStructPtr->pChipData); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
# endif
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return errorId;
}
#endif

#if defined(C_30_MCAN_ENABLE_RX_QUEUE)
/****************************************************************************
| NAME:             CanHL_30_Mcan_RxQueueExecution
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/*
|<DataModelStart>| CanHL_30_Mcan_RxQueueExecution
Relation_Context:
# from Can_30_Mcan_MainFunction_Read #
RxQueue
Relation:
GenericPreCopy, OneChOpt, DevErrorDetect
GenericPreCopy, MirrorMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxQueueExecution( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute RxQueue (over all channels) */
  while ( Can_30_Mcan_GetRxQueueInfo().Count != (uint16)0 )
  { /* #20 over all filled RxQueue elements */
# if (CAN_30_MCAN_GENERIC_PRECOPY == STD_ON)
    Can_ReturnType generic_retval;
    CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
    generic_retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_30_Mcan_GetMailboxController(Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).Hrh);
#   if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
    if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #30 Check controller is valid */
      errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
    }
    else
#   endif
#  endif
#  if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
    if (Can_30_Mcan_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
    { /* #40 MirrorMode: only when mirror is activated for this controller */
      generic_retval = CAN_OK;
    }
    else
#  endif
    { /* #50 call Appl_GenericPrecopy() */
      generic_retval = Appl_30_Mcan_GenericPrecopy( (uint8)channel,
                (Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).id & CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT),
                Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).dlc,
                (Can_30_Mcan_DataPtrType)Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL06 */
    }
    if (generic_retval == CAN_OK)
# endif
    { /* #60 call CanIf_RxIndication() if Appl_GenericPrecopy() return OK or no generic precopy is used \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
      CanIf_30_Mcan_RxIndication( Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).Hrh, /* SBSW_CAN_HL06 */
              Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).id,
              Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).dlc,
              (Can_30_Mcan_DataPtrType)Can_30_Mcan_GetRxQueueBuffer(Can_30_Mcan_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */
    }
    /* #70 EXCLUSIVE_AREA_4 secure RxQueue handling */
    SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_4();
    /* #80 get next RxQueue element pointer */
    if (Can_30_Mcan_GetRxQueueInfo().ReadIndex >= ((uint16)Can_30_Mcan_GetSizeOfRxQueueBuffer() - (uint16)1u) ) /* CM_CAN_HL25 */
    {
      Can_30_Mcan_GetRxQueueInfo().ReadIndex = 0u; /* CM_CAN_HL25 */ /* SBSW_CAN_HL55 */
    }
    else
    {
      Can_30_Mcan_GetRxQueueInfo().ReadIndex++; /* SBSW_CAN_HL55 */ /* PRQA S 3387 */ /* MD_Can_HL_UsingIncOrDec */
    }
    Can_30_Mcan_GetRxQueueInfo().Count--; /* SBSW_CAN_HL55 */ /* PRQA S 3387 */ /* MD_Can_HL_UsingIncOrDec */
    SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_4();
  }
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
#endif


#if defined ( C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS )
# if defined (C_30_MCAN_ENABLE_CANSUBSYSTEMBASEADR) /* COV_CAN_HW_SPECIFIC */
/****************************************************************************
| NAME:             CanLL_30_Mcan_InitSubSystemVirtualAddr
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitSubSystemVirtualAddr
Relation_Context:
# CanLL_30_Mcan_InitSubSystemVirtualAddr() #
Relation:
OneChOpt
ChannelAmount
VirtualAddressing
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitSubSystemVirtualAddr(void)
{
  vuint8 subSystemIndex;
  /* #10 SafeBSW check for the amount of subsystems */
#  if( CAN_30_MCAN_SAFE_BSW == STD_ON )
  if(Can_30_Mcan_GetSizeOfCanSubSystemBaseAdr() != Can_30_Mcan_GetSizeOfCanVirtualSubSystemBaseAdr()) /* CM_CAN_LL_115 */ /* PRQA S 3325,2992,2742 */ /* MD_Can_3325_LL,MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
  else
#  endif
  {
    /* #20 Get virtual base address of subsystems */
    for (subSystemIndex = 0u; subSystemIndex<Can_30_Mcan_GetSizeOfCanSubSystemBaseAdr(); subSystemIndex++)
    {
      Can_30_Mcan_SetCanVirtualSubSystemBaseAdr(subSystemIndex, (vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)(Can_30_Mcan_GetCanSubSystemBaseAdr(subSystemIndex)), sizeof(vuint32)))); /* SBSW_CAN_LL_127 */
    }
  }
}
# endif
# if defined (C_30_MCAN_ENABLE_CANGLOBALBASEADR) /* COV_CAN_HW_SPECIFIC */
/****************************************************************************
| NAME:             CanLL_30_Mcan_InitGlobalVirtualAddr
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitGlobalVirtualAddr
Relation_Context:
# CanLL_30_Mcan_InitGlobalVirtualAddr() #
Relation:
OneChOpt
ChannelAmount
VirtualAddressing
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitGlobalVirtualAddr(void)
{
  /* #10 Get Virtual global address */
  Can_30_Mcan_SetCanVirtualGlobalBaseAdr((vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)(Can_30_Mcan_GetCanGlobalBaseAdr()), sizeof(vuint32))));
}
# endif
/****************************************************************************
| NAME:             CanLL_30_Mcan_InitVirtualAddr
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitVirtualAddr
Relation_Context:
# CanLL_30_Mcan_InitVirtualAddr() #
Relation:
OneChOpt
ChannelAmount
VirtualAddressing
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitVirtualAddr(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY)
{
  /* #10 Get virtual base address of Mcan controller */
  Can_30_Mcan_SetVirtualBasisAdrOfControllerData(canHwChannel, (vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)(Can_30_Mcan_GetBasisAdrOfControllerConfig(canHwChannel)), sizeof(vuint32)))) ; /* SBSW_CAN_LL_112 */
  
  /* #20 Get virtual base address of shared message RAM */
  Can_30_Mcan_SetStartAdrOfVirtualShmAdr(canHwChannel, (vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)), sizeof(vuint32)))) ;    /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetSIDFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetSIDFAOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetSIDFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetSIDFAOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetXIDFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetXIDFAOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetXIDFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetXIDFAOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXF0AOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXF0AOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXF0AOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXF0AOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXF1AOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXF1AOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXF1AOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXF1AOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXBAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXBAOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetRXBAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetRXBAOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;    /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetTXBAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetTXBAOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                  /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetTXBAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetTXBAOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;    /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetTXEFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetTXEFAOfShmAdr(canHwChannel)) - (vuint32)(Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)))  ;                /* SBSW_CAN_LL_103 */
  Can_30_Mcan_SetTXEFAOfVirtualShmAdr(canHwChannel, (vuint32)(Can_30_Mcan_GetTXEFAOfVirtualShmAdr(canHwChannel)) + (vuint32)(Can_30_Mcan_GetStartAdrOfVirtualShmAdr(canHwChannel)))  ;  /* SBSW_CAN_LL_103 */

# if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS )  /* COV_CAN_HW_SPECIFIC */
  /* #30 Get virtual McanSs base address */
  Can_30_Mcan_SetCanVirtualMcanSsBaseAddr(canHwChannel, (vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)((Can_30_Mcan_GetCanMcanSsBaseAddr(canHwChannel))), sizeof(vuint32)))); /* MCANSS Control extra registers pointer layout */ /* SBSW_CAN_LL_125 */
  /* #40 Get virtual McanECC base address */
  Can_30_Mcan_SetCanVirtualMcanEccBaseAddr(canHwChannel, ((vuint32)(Appl_30_McanCanPowerOnGetBaseAddress((vuint32)((Can_30_Mcan_GetCanEccAggrBaseAddr(canHwChannel))), sizeof(vuint32))); /* MCANSS ECC extra registers pointer layout */ /* SBSW_CAN_LL_126 */
# endif
 }
#endif
/****************************************************************************
| NAME:             CanLL_30_Mcan_WriteReg32
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_WriteReg32
Relation_Context:
# CanLL_InitBeginSetRegisters() #
RamCheck
Relation:
OneChOpt, RamCheck
ChannelAmount, RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_WriteReg32( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST Can_30_McanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8 result = kCan_30_McanFalse;
  /* #10 write register value */
  *regPtr = value; /* SBSW_CAN_HL35 */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED) 
  if (initPara->doRamCheck == kCan_30_McanExecuteRamCheck)
  {
    /* #20 read back value for RamCheck */
    volatile vuint32 readBack;
    readBack = *regPtr;
    if ((readBack & readMask) != (value & readMask)) /* COV_CAN_HARDWARE_FAILURE */
    {
      /* #30 return issue when read back value differs */
      result = kCan_30_McanTrue;  /* PRQA S 2982 */ /* MD_Can_2982_LL */
    }
    CAN_30_MCAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_HL36 */
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(readMask);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return result;
}


/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitBegin
Relation_Context:
# CanHL_30_Mcan_InitBegin() #
OneChOpt, ChannelAmount
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBegin( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* #10 Store current Mcan interrupt state (IE) */
  initPara->canInterruptOldStatus = (vuint32)(Cn->IE); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_109 */
#if defined (C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION)
/* Read actual CREL */
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  Can_McanRevision[0]                 = (vuint16)((Cn->CREL & 0xFFF00000UL) >> 20); /* SBSW_CAN_LL_106 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# else
  Can_McanRevision[channel] = (vuint16)((Cn->CREL & 0xFFF00000UL) >> 20); /* SBSW_CAN_LL_112 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif
# else
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* DYNAMIC_MCAN_REVISION */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBeginIsRegisterCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitBeginIsRegisterCorrupt
Relation_Context:
# CanHL_30_Mcan_InitBegin() #
OneChOpt, ChannelAmount, RamCheck
Relation:
OneChOpt, RamCheck,
ChannelAmount, HardwareLoopCheck, RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
/* PRQA S 0303 QAC_Can_0303_IsRegCorrupt */ /* MD_Can_HwAccess */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginIsRegisterCorrupt( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{ 
  vuint8 indx;
  vuint8 ret_val;
  
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  vuint32 var_kCanRegCheckMaskCCCR;
  vuint32 var_kCanRegCheckMaskFBTP;
  vuint32 var_kCanRegCheckMaskBTP;
  vuint32 var_kCanRegCheckMaskIE;
  vuint32 var_kCanRegCheckMaskILS;
  vuint32 var_kCanRegCheckMaskIR;
  
  if(CanGetMcanRevision(channel) < 0x310UL) /* For McanRevision 300 */ /* COV_CAN_HW_SPECIFIC */ /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
  {
    var_kCanRegCheckMaskCCCR =  kCanRegCheckMaskCCCR_DynMCan_300;
    var_kCanRegCheckMaskFBTP =  kCanRegCheckMaskFBTP_DynMCan_300;
    var_kCanRegCheckMaskBTP  =  kCanRegCheckMaskBTP_DynMCan_300;
    var_kCanRegCheckMaskIE   =  kCanRegCheckMaskIE_DynMCan_300;
    var_kCanRegCheckMaskILS  =  kCanRegCheckMaskILS_DynMCan_300;
    var_kCanRegCheckMaskIR   =  kCanRegCheckMaskIR_DynMCan_300;
  }
  else if (CanGetMcanRevision(channel) < 0x315UL) /* For McanRevision 310 */ /* COV_CAN_HW_SPECIFIC */ /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
  {
    var_kCanRegCheckMaskCCCR =  kCanRegCheckMaskCCCR_DynMCan_310;
    var_kCanRegCheckMaskFBTP =  kCanRegCheckMaskFBTP_DynMCan_310;
    var_kCanRegCheckMaskBTP  =  kCanRegCheckMaskBTP_DynMCan_310;
    var_kCanRegCheckMaskIE   =  kCanRegCheckMaskIE_DynMCan_310;
    var_kCanRegCheckMaskILS  =  kCanRegCheckMaskILS_DynMCan_310;
    var_kCanRegCheckMaskIR   =  kCanRegCheckMaskIR_DynMCan_310;

  }
  else /* For McanRevision 315 */ /* COV_CAN_HW_SPECIFIC */
  {
    var_kCanRegCheckMaskCCCR =  kCanRegCheckMaskCCCR_DynMCan_315;
    var_kCanRegCheckMaskFBTP =  kCanRegCheckMaskFBTP_DynMCan_310;
    var_kCanRegCheckMaskBTP  =  kCanRegCheckMaskBTP_DynMCan_310;
    var_kCanRegCheckMaskIE   =  kCanRegCheckMaskIE_DynMCan_310;
    var_kCanRegCheckMaskILS  =  kCanRegCheckMaskILS_DynMCan_310;
    var_kCanRegCheckMaskIR   =  kCanRegCheckMaskIR_DynMCan_310;
  }
# endif

# if defined ( C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCan_30_McanNumberOfChannels, kCanAllChannels, kCanErrorChannelHdlTooLarge); /* COV_CAN_GENDATA_FAILURE */
# endif

  /* ----- Implementation ----------------------------------------------- */

  /* assume the registers are not corrupt */
  ret_val = kCan_30_McanFalse;

  /* Initialization */
  if ((Cn->CCCR & kCanCCCR_INIT) != kCanCCCR_INIT ) /* If Init-Bit is not set */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
  {
    Cn->CCCR  = kCanCCCR_INIT; /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* PRQA S 2842 */ /* MD_Can_Assertion */ /* SBSW_CAN_LL_101 */
    while( ((Cn->CCCR & kCanCCCR_INIT) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303,2842,2843 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess,MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */ /* COV_CAN_HW_SPECIFIC */
    {/* Assure that INIT has been accepted. */}
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */ /* PRQA S 2842 */ /* MD_Can_Assertion */
  }

  /* Configuration Change Enable */
  Cn->CCCR |= kCanCCCR_CCE; /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
  CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* PRQA S 2842 */ /* MD_Can_Assertion */ /* SBSW_CAN_LL_101 */
  while( ((Cn->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303,2842,2843 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess,MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */ /* COV_CAN_HW_SPECIFIC */
  {/* Assure that CCE has been accepted. */}
  CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */ /* PRQA S 2842 */ /* MD_Can_Assertion */
  
  Cn->ILE = kCanILE_DISABLE; /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */ /* SBSW_CAN_LL_100 */ /* Ensure that the interrupt lines are disabled */
  
  /* #10 Iterate test patterns */
  for(indx = 0x00u; indx < 4u; indx++)
    { 
      /* #20 Write pattern to controller register */
      
      /* CC Control Register (CCCR) */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      Cn->CCCR = (((var_kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP) & Can_30_McanRegCheckValues32bit[indx])|kCanRegCheckMaskCCCR_RP); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# else
      Cn->CCCR = (((kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP) & Can_30_McanRegCheckValues32bit[indx])|kCanRegCheckMaskCCCR_RP); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# endif
       
      /* Data Bit Timing & Prescaler Register (FBTP),RP */ 
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      Cn->FBTP = (var_kCanRegCheckMaskFBTP & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  else
      Cn->FBTP = (kCanRegCheckMaskFBTP & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  endif

      /* RAM Watchdog (RWD), RP */
      Cn->RWD  = (kCanRegCheckMaskRWD  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Bit Timing and Prescaler Register (BTP/NBTP), RP */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      Cn->BTP = (var_kCanRegCheckMaskBTP  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  else
      Cn->BTP = (kCanRegCheckMaskBTP  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  endif
      
      /* Timestamp Counter Configuration (TSCC), RP */
      Cn->TSCC = (kCanRegCheckMaskTSCC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */  /*! Not supported but initialized */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Timeout Counter Configuration (TOCC), RP */
      Cn->TOCC = (kCanRegCheckMaskTOCC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */  /*! Not supported but initialized */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Timeout Counter Value (TOCV), RC */ 
      
      /* Transmitter Delay Compensation Register (TDCR), RP */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      if(CanGetMcanRevision(channel) < 0x310UL) /* For McanRevision 300 */ /* COV_CAN_HW_SPECIFIC */ /* PRQA S 2842,2843 */ /* MD_Can_2842_DynamicRevision_LL,MD_Can_HL_DereferencePointerValue */
# endif
      {
#  if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */ 
        Cn->TDCR = (kCanRegCheckMaskTDCR  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  endif /* MCAN Core Release < 0x0310UL */
      }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      else /* For McanRevision >300 */ /* COV_CAN_HW_SPECIFIC */
      {
#  if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */ 
        Cn->TDCR = (kCanRegCheckMaskTDCR  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#else
        Cn->res2[0] = (kCanRegCheckMaskTDCR  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */  /* TDCR not available when configured for rev 3.0 */
#  endif /* MCAN Core Release < 0x0310UL */
      }
# endif
      /* Interrupt Line Select (ILS), RW */
#  if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      Cn->IE = (var_kCanRegCheckMaskIE  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      Cn->ILS = (var_kCanRegCheckMaskILS  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  else
      Cn->IE = (kCanRegCheckMaskIE  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      Cn->ILS = (kCanRegCheckMaskILS  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
#  endif
    
      /* Global Filter Configuration (GFC),RP */
      Cn->GFC = (kCanRegCheckMaskGFC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Standard ID Filter Configuration (SIDFC), RP */
      Cn->SIDFC = (kCanRegCheckMaskSIDFC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Extended ID Filter Configuration (XIDFC), RP */
      Cn->XIDFC = (kCanRegCheckMaskXIDFC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Extended ID AND Mask (XIDAM), RP */
      Cn->XIDAM = (kCanRegCheckMaskXIDAM  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx FIFO 0 Configuration (RXF0C), RP */
      Cn->RXF0C.R = (kCanRegCheckMaskRXF0C  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx FIFO 0 Acknowledge (RXF0A), RW */
      Cn->RXF0A = (kCanRegCheckMaskRXF0A  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx Buffer Configuration (RXBC), RP */ 
      Cn->RXBC = (kCanRegCheckMaskRXBC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx FIFO 1 Configuration (RXF1C), RP */
      Cn->RXF1C.R = (kCanRegCheckMaskRXF1C  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx FIFO 1 Acknowledge (RXF1A), RW */
      Cn->RXF1A = (kCanRegCheckMaskRXF1A  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Rx Buffer / FIFO Element Size Configuration (RXESC), RP */ 
      Cn->RXESC.R = (kCanRegCheckMaskRXESC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Tx Buffer Configuration (TXBC) */
      Cn->TXBC = (kCanRegCheckMaskTXBC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Tx Buffer Element Size Configuration (TXESC) */ 
      Cn->TXESC = (kCanRegCheckMaskTXESC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Tx Buffer Transmission Interrupt Enable (TXBTIE), RW */
      Cn->TXBTIE = (kCanRegCheckMaskTXBTIE  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */  /* PRQA S 2986,4558,2842,2843 */ /* MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      /* Tx Event FIFO Configuration (TXEFC) */
      Cn->TXEFC = (kCanRegCheckMaskTXEFC  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */  /* Not supported but initialized */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
    
      /* #30 Check if register values are valid  */ 
      if(
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
          ( (Cn->FBTP    & var_kCanRegCheckMaskFBTP)  != (var_kCanRegCheckMaskFBTP  & Can_30_McanRegCheckValues32bit[indx])) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->CCCR & (var_kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP))!= ((var_kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP) & Can_30_McanRegCheckValues32bit[indx]) ) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->IE      & var_kCanRegCheckMaskIE)    != (var_kCanRegCheckMaskIE    & Can_30_McanRegCheckValues32bit[indx])) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->ILS     & var_kCanRegCheckMaskILS)   != (var_kCanRegCheckMaskILS   & Can_30_McanRegCheckValues32bit[indx])) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->BTP     & var_kCanRegCheckMaskBTP)   != (var_kCanRegCheckMaskBTP   & Can_30_McanRegCheckValues32bit[indx])) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# else
          ( (Cn->FBTP    & kCanRegCheckMaskFBTP)  != (kCanRegCheckMaskFBTP  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->CCCR & (kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP))!= ((kCanRegCheckMaskCCCR ^ kCanRegCheckMaskCCCR_RP) & Can_30_McanRegCheckValues32bit[indx]) ) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->IE      & kCanRegCheckMaskIE)    != (kCanRegCheckMaskIE    & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->ILS     & kCanRegCheckMaskILS)   != (kCanRegCheckMaskILS   & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->BTP     & kCanRegCheckMaskBTP)   != (kCanRegCheckMaskBTP   & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# endif
          ( (Cn->CCCR & (kCanCCCR_CCE | kCanCCCR_INIT))                     != (kCanCCCR_CCE | kCanCCCR_INIT)) || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RWD     & kCanRegCheckMaskRWD)   != (kCanRegCheckMaskRWD   & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TSCC    & kCanRegCheckMaskTSCC)  != (kCanRegCheckMaskTSCC  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TOCC    & kCanRegCheckMaskTOCC)  != (kCanRegCheckMaskTOCC  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
          ( (Cn->TDCR    & kCanRegCheckMaskTDCR)  != (kCanRegCheckMaskTDCR  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# endif /* MCAN Core Release < 0x0310UL */ 
          ( (Cn->GFC     & kCanRegCheckMaskGFC)   != (kCanRegCheckMaskGFC   & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->SIDFC   & kCanRegCheckMaskSIDFC) != (kCanRegCheckMaskSIDFC & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->XIDFC   & kCanRegCheckMaskXIDFC) != (kCanRegCheckMaskXIDFC & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->XIDAM   & kCanRegCheckMaskXIDAM) != (kCanRegCheckMaskXIDAM & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXF0C.R & kCanRegCheckMaskRXF0C) != (kCanRegCheckMaskRXF0C & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXF0A   & kCanRegCheckMaskRXF0A) != (kCanRegCheckMaskRXF0A & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXBC    & kCanRegCheckMaskRXBC)  != (kCanRegCheckMaskRXBC  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXF1C.R & kCanRegCheckMaskRXF1C) != (kCanRegCheckMaskRXF1C & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXF1A   & kCanRegCheckMaskRXF1A) != (kCanRegCheckMaskRXF1A & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->RXESC.R & kCanRegCheckMaskRXESC) != (kCanRegCheckMaskRXESC & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TXBC    & kCanRegCheckMaskTXBC)  != (kCanRegCheckMaskTXBC  & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TXESC   & kCanRegCheckMaskTXESC) != (kCanRegCheckMaskTXESC & Can_30_McanRegCheckValues32bit[indx]))   || /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TXBTIE  & kCanRegCheckMaskTXBTIE)!= (kCanRegCheckMaskTXBTIE& Can_30_McanRegCheckValues32bit[indx]))   ||  /* PRQA S 2986,4558,2842,2843 */ /* MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          ( (Cn->TXEFC   & kCanRegCheckMaskTXEFC) != (kCanRegCheckMaskTXEFC & Can_30_McanRegCheckValues32bit[indx]))    ) /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
          {
            ret_val = kCan_30_McanTrue; 
          }
    
      /* We need this extra case in order to check TDCR if Dynamic MCAN rev is configured for configuration with MCAN rev 3.0 but run on a > 3.0 target */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
#  if ( CAN_MCAN_REVISION < 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
      if(CanGetMcanRevision(channel) >= 0x310UL) /* TDCR is only available in rev >= 3.1, If configured for this rev, then the register is checked in above */ /* COV_CAN_HW_SPECIFIC */ /* PRQA S 2842,2843  */ /* MD_Can_2842_DynamicRevision_LL,MD_Can_HL_DereferencePointerValue */
      {
        if ((Cn->res2[0]  & kCanRegCheckMaskTDCR)  != (kCanRegCheckMaskTDCR  & Can_30_McanRegCheckValues32bit[indx])) /* COV_CAN_HARDWARE_FAILURE */
        {
          ret_val = kCan_30_McanTrue; 
        }
      }
#  endif
# endif
    }
    /* Ensure that the interrupts are disabled at this point. Otherwise, the CPU will get notified if there is an interrupt */
    Cn->IE  = 0x00000000UL; /* SBSW_CAN_LL_100 */ /* Disable MCAN Interrupts */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
    Cn->ILS = kCanILS_ALL_ZERO; /* SBSW_CAN_LL_100 */ /* Disable interrupt Line select */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */

# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
    Cn->IR  = var_kCanRegCheckMaskIR; /* SBSW_CAN_LL_100 */ /* Clear interrupt flags */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# else
    Cn->IR  = kCanIR_CLEAR_ALL; /* SBSW_CAN_LL_100 */ /* Clear interrupt flags */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
# endif

    for(indx = 0x00u; indx < 4u; indx++){
    /* Interrupt Line Enable (ILE), RW */
      Cn->ILE = (kCanRegCheckMaskILE  & Can_30_McanRegCheckValues32bit[indx]); /* SBSW_CAN_LL_100 */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
      if ( (Cn->ILE     & kCanRegCheckMaskILE)   != (kCanRegCheckMaskILE   & Can_30_McanRegCheckValues32bit[indx])) /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 2842,2843 */ /* MD_Can_Assertion,MD_Can_HL_DereferencePointerValue */
        {
          ret_val = kCan_30_McanTrue; 
        }
    }
# if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
    ret_val |= CAN_30_MCAN_RAM_CHECK_BEGIN_REG_REGEXT_RESULT(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
# endif

  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return(ret_val); 
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* PRQA  L:QAC_Can_0303_IsRegCorrupt */
/* CODE CATEGORY 4 END */

# if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 indx;
  vuint8 retval;

  /* assume the registers are not corrupt */
  retval = kCan_30_McanFalse;
  
   /* #10 Iterate test patterns */
  for(indx = 0u; indx < 4u; indx++)
  {
    /* #20 Write pattern to controller register */
    /* MCANSS general control register */
    McanExtraGlobalReg(channel)->MCANSS_CTRL = (kCanRegCheckMaskMCANSS_CTRL & Can_30_McanRegCheckValues32bit[indx]); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_125 */ 

    /* #30 Check if register values are valid */
    if( (McanExtraGlobalReg(channel)->MCANSS_CTRL & kCanRegCheckMaskMCANSS_CTRL) != (kCanRegCheckMaskMCANSS_CTRL & Can_30_McanRegCheckValues32bit[indx])) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_HARDWARE_FAILURE */
    {
      retval = kCan_30_McanTrue;
    }
  } 

  return retval;
}
/* CODE CATEGORY 4 END */
# endif /* COV_CAN_HW_SPECIFIC */

#endif /* C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBeginSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitBeginSetRegisters
Relation_Context:
# CanHL_30_Mcan_InitBegin() #
OneChOpt, ChannelAmount
Relation:
OneChOpt
ChannelAmount, StatusPolling
ChannelAmount, TxPolling
ChannelAmount, IndividualPolling
RxFullCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginSetRegisters( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  vuint8 result;
  /* #10 set MCAN configuration registers */
  result = CanLL_30_Mcan_SetAllRegister(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */ /* fill in all CAN registers */

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
  CanLL_30_Mcan_SetRegisterMcanSS(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */
#endif
#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
  CanLL_30_Mcan_SetRegisterSICanFD(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */
#endif
#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
  CanLL_30_Mcan_SetRegisterTTCanFD(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */
#endif
#if defined( C_30_MCAN_ENABLE_SHM_DATAQOS ) /* COV_CAN_HW_SPECIFIC */
  CanLL_30_Mcan_SetRegisterDataQoS(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */
#endif
  /* #20 set MCAN filter tables */
  result &= CanLL_30_Mcan_SetAllFilter(CAN_30_MCAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_LL_110 */ /* fill in CAN Message RAM */


  return(result);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxTx
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitMailboxTx
Relation_Context:
# CanHL_30_Mcan_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_30_Mcan_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
OneChOpt
ChannelAmount, TxPolling, IndividualPolling
TxHwFifo, MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxTx( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  Can_30_McanObjectHandle mailboxElement = 0; /* PRQA S 2981 */ /* MD_Can_RedundantInit */
#if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
  for(; mailboxElement < Can_30_Mcan_GetMailboxSize(initPara->mailboxHandle); mailboxElement++)
#endif
  {
    /* #10 get the Message RAM location */
    initPara->pTXB =  (Can_30_McanElmType*) &ShmTXB(initPara->hwObjHandle + mailboxElement); /* PRQA S 0303,0310,312,1891,4391,2985 */ /* MD_Can_HwAccess,MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast,MD_Can_1891_LL,MD_Can_IntegerCast,MD_Can_ConstValue */ /* SBSW_CAN_LL_109 */
#if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
    if( ((vuint32)initPara->pTXB < (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || ((vuint32)&ShmTXB(initPara->hwObjHandle + mailboxElement +1u) >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) ) /* PRQA S 0303,4391,2985 */ /* MD_Can_HwAccess,MD_Can_IntegerCast,MD_Can_ConstValue */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
    { /* SilentBSW check */
      initPara->pTXB = &ShmTXB(0u); /* PRQA S 0303,4391,2985 */ /* MD_Can_HwAccess,MD_Can_IntegerCast,MD_Can_ConstValue */ /* SBSW_CAN_LL_109 */ 
      Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
    }
#endif
    /* #20 reset FD flags and Dlc */
    initPara->pTXB->E1 = 0x00000000UL; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
#if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
    if(Can_30_Mcan_IsMailboxIndivPolling(initPara->mailboxHandle))   /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* poll this object */
    }
    else
#endif
    {
#if !defined( C_30_MCAN_ENABLE_TX_POLLING ) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
      /* #30 enable mailbox Tx interrupt if not in polling mode */
      initPara->txbtie |= (vuint32)(kCan_30_McanACTIVE << (initPara->hwObjHandle + mailboxElement)); /* PRQA S 2985 */ /* MD_Can_ConstValue */ /* allow CAN Tx Buffer confirmation and cancelation INTs */ /* SBSW_CAN_LL_109 */ 
#endif
    }
  } /* end for loop */
  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

#if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxTxDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_InitMailboxTxDeactivate
Relation_Context:
# CanHL_30_Mcan_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_30_Mcan_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxTxDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* #10 no actions necessary */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 4 END */
#endif



#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxFullCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitMailboxRxFullCan
Relation_Context:
# CanHL_30_Mcan_InitRxFullCAN() #
OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxFullCan( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{


  CAN_30_MCAN_DUMMY_STATEMENT(initPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

# if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxFullCanDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitMailboxRxFullCanDeactivate
Relation_Context:
# CanHL_30_Mcan_InitRxFullCAN() #
OneChOpt, ChannelAmount, RxFullCANSupport, RamCheck
Relation:
OneChOpt
ChannelAmount, IDType
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxFullCanDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  Can_30_McanObjectHandle index;
  /* #10 Deactive Standard ID Filter */
#  if defined( C_30_MCAN_ENABLE_STD_ID ) && (kCanNumberOfStandardFilter > 0)  
  for(index = 0u; index < Can_30_Mcan_GetCanSIDFC_LSSOfCanSIDFC(canHwChannel); index++)  /* SBSW_CAN_LL_109 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    /* If the Filter Is Configured to the RxBuffer, And if the SFID2 defined offset to the Rx Buffer Start Adress matches the hwObjHandle */
    if ( (((vuint32) (ShmSIDF(index)).S0 & kCanSFE_SFEC) == kCanSFE_SFEC ) && /* PRQA S 0303 */ /* MD_Can_HwAccess */
         (((vuint32) (ShmSIDF(index)).S0 & kCanSFE_SFID2_RBSA) == (vuint32)initPara->hwObjHandle) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_DISABLE_RX_MAILBOX */
    { /* Disable the filter element */
#   if( CAN_30_MCAN_SAFE_BSW == STD_ON )
      if( ((vuint32)&ShmSIDF(index).S0 <  (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
          ((vuint32)&ShmSIDF(index).S0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) )  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
      { /* SilentBSW check */
        Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      }
      else
#   endif
      {
        ShmSIDF(index).S0 |= kCanSFE_SFTRes; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
      }
    }
  }
#  endif  /* STD_FILTER */

  /* #20 Deactive Extended ID Filter */
#  if defined(C_30_MCAN_ENABLE_EXTENDED_ID) && (kCanNumberOfExtendedFilter > 0)
  for(index = 0u; index < Can_30_Mcan_GetCanXIDFC_LSEOfCanXIDFC(canHwChannel); index++)  /* SBSW_CAN_LL_109 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    if ( (((vuint32) (ShmXIDF(index)).F0 & kCanEFE_EFEC)       == kCanEFE_EFEC ) && /* PRQA S 0303 */ /* MD_Can_HwAccess */
         (((vuint32) (ShmXIDF(index)).F1 & kCanEFE_EFID2_RBSA) == (vuint32)initPara->hwObjHandle) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_DISABLE_RX_MAILBOX */
    {/* Disable the Filter element */
#   if( CAN_30_MCAN_SAFE_BSW == STD_ON )
      if( ((vuint32)&ShmXIDF(index).F0 <  (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
          ((vuint32)&ShmXIDF(index).F0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) )  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
      { /* SilentBSW check */
        Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      }
      else
#   endif
      {
        ShmXIDF(index).F0 &= ~kCanEFE_EFEC; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
      }
    }
  }
#  endif /* EXT_FILTER */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* avoid qac-9.3.1-3673 "parameter could be const" */
}
/* CODE CATEGORY 4 END */
# endif
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxBasicCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitMailboxRxBasicCan
Relation_Context:
# CanHL_30_Mcan_InitRxBasicCAN() #
OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxBasicCan( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* using CanLL_WriteReg32(&initPara) just to satisfy test is intentionally omitted */
  /* #10 no actions necessary */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

# if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate
Relation_Context:
# CanHL_30_Mcan_InitRxBasicCAN() #
OneChOpt, ChannelAmount, RxBasicCANSupport, RamCheck
Relation:
OneChOpt
ChannelAmount, DevErrorDetect, IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )  /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  Can_30_McanObjectHandle index;

#  if defined( C_30_MCAN_ENABLE_STD_ID ) && (kCanNumberOfStandardFilter > 0)  /* at least one std filter is available */
  /* #10 disable STD filters */
  for(index = 0u; index < Can_30_Mcan_GetCanSIDFC_LSSOfCanSIDFC(canHwChannel); index++) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    /* If Filter is configured to ( RXFIFO0 OR RXFIFO1) AND The filter offset matches the HwObjHandle */
    if ( ( (((vuint32) (ShmSIDF(index)).S0 & kCanSFE_SFEC_F0) == kCanSFE_SFEC_F0 ) && ( initPara->hwObjHandle == 0u)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */
         ( (((vuint32) (ShmSIDF(index)).S0 & kCanSFE_SFEC_F1) == kCanSFE_SFEC_F1 ) && ( initPara->hwObjHandle == 1u))   /* PRQA S 0303 */ /* MD_Can_HwAccess */
       ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_DISABLE_RX_MAILBOX */
    { /* Disable the filter element */
#    if( CAN_30_MCAN_SAFE_BSW == STD_ON )
      if( ((vuint32)&ShmSIDF(index).S0 <  (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
          ((vuint32)&ShmSIDF(index).S0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) )  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
      { /* SilentBSW check */
        Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      }
      else
#    endif
      {
        ShmSIDF(index).S0 |= kCanSFE_SFTRes; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
      }
    }
  }
#  endif

#  if defined(C_30_MCAN_ENABLE_EXTENDED_ID) && (kCanNumberOfExtendedFilter > 0)
  /* #20 disable EXT filters */
  for(index = 0u; index < Can_30_Mcan_GetCanXIDFC_LSEOfCanXIDFC(canHwChannel); index++) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    /* If Filter is configured to ( RXFIFO0 OR RXFIFO1) AND The filter offset matches the HwObjHandle */
    if ( ( (((vuint32) (ShmXIDF(index)).F0 & kCanEFE_EFEC_F0) == kCanEFE_EFEC_F0 ) && ( initPara->hwObjHandle == 0u)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */
         ( (((vuint32) (ShmXIDF(index)).F0 & kCanEFE_EFEC_F1) == kCanEFE_EFEC_F1 ) && ( initPara->hwObjHandle == 1u))  /* PRQA S 0303 */ /* MD_Can_HwAccess */
       ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_DISABLE_RX_MAILBOX */
    { /* Disable the filter element */
#    if( CAN_30_MCAN_SAFE_BSW == STD_ON )
      if( ((vuint32)&ShmXIDF(index).F0 <  (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
          ((vuint32)&ShmXIDF(index).F0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) )  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
      { /* SilentBSW check */
        Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      }
      else
#    endif
      {
        ShmXIDF(index).F0 &= ~kCanEFE_EFEC; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
      }
    }
  }
#  endif
}
/* CODE CATEGORY 4 END */
# endif
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEndIsRegisterCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitEndIsRegisterCorrupt
Relation_Context:
# CanHL_30_Mcan_InitEnd_InitMode() #
OneChOpt, ChannelAmount, RamCheck
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEndIsRegisterCorrupt( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions necessary */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return(kCan_30_McanFalse); /* Channel is not corrupt */
}
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEndSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitEndSetRegisters
Relation_Context:
# CanHL_30_Mcan_InitEnd_InitMode() #
OneChOpt, ChannelAmount
Relation:
ChannelAmount, GlobalInitPostProcess
ChannelAmount, IDType
RxBasicCANSupport
RxFullCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEndSetRegisters( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{


  /* #10 set STD filter configuration */
#if defined( C_30_MCAN_ENABLE_STD_ID )
  /*  11-bit standard Message ID filtering */
# if( kCanNumberOfStandardFilter > 0 ) 
  /* BasicCAN filter available */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->SIDFC), (vuint32)( ((vuint32)(initPara->stdFeCount) << 16) | ((vuint32)Can_30_Mcan_GetCanSIDFC_FLSSAOfCanSIDFC(canHwChannel)) ), kCanRegCheckMaskSIDFC, initPara);     /* SBSW_CAN_LL_100 */     /* PRQA S 0303 */ /* MD_Can_HwAccess */
# else
  /* No BasicCAN filter available */
#  if( kCanNumberOfRxObjects > 0 ) /* COV_CAN_COMPATIBILITY */
  /* FullCAN filter available */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->SIDFC), (vuint32)( ((vuint32)(initPara->stdFeCount) << 16) | (((vuint32)(Can_30_Mcan_GetCanShmAdr_SIDFAOfCanShmAdr(canHwChannel)) & 0x0000FFFFUL)) ), kCanRegCheckMaskSIDFC, initPara);     /* SBSW_CAN_LL_100 */     /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->SIDFC), (vuint32)(0x00000000UL), kCanRegCheckMaskSIDFC, initPara);    /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */  /* LSS zero means no standard filters at all available */
#  endif
# endif
#endif

  /* #20 set EXT filter configuration */
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID) 
  /*  29-bit extended Message ID filtering */
# if (kCanNumberOfExtendedFilter > 0) /* COV_CAN_COMPATIBILITY */
  /* BasicCAN filter available */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->XIDFC), (vuint32)( ((vuint32)(initPara->extFeCount) << 16) | ((vuint32)(Can_30_Mcan_GetCanXIDFC_FLESAOfCanXIDFC(canHwChannel))) ), kCanRegCheckMaskXIDFC, initPara);     /* SBSW_CAN_LL_100 */     /* PRQA S 0303 */ /* MD_Can_HwAccess */
# else
  /* No BasicCAN filter available */
#  if( kCanNumberOfRxObjects > 0 ) /* COV_CAN_COMPATIBILITY */
  /* FullCAN filter available */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->XIDFC), (vuint32)( ((vuint32)(initPara->extFeCount) << 16) | ((vuint32)((Can_30_Mcan_GetCanShmAdr_XIDFAOfCanShmAdr(canHwChannel)) & 0x0000FFFFUL)) ), kCanRegCheckMaskXIDFC, initPara);  /* PRQA S 0303 */ /* MD_Can_HwAccess */
  
#  else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->XIDFC), (vuint32)(0x00000000UL), kCanRegCheckMaskXIDFC, initPara);   /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* LSE zero means no extended filters at all available */
#  endif
# endif
#endif
   
  /* #30 set Interrupt configuration */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXBTIE), (vuint32)(initPara->txbtie), kCanRegCheckMaskTXBTIE, initPara); /* allow CAN Tx Buffer confirmation INTs */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXBCIE), (vuint32)(initPara->txbtie), kCan_ALL_ONE, initPara); /* allow CAN Tx Buffer cancellation INTs */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 

  Can_30_Mcan_GetCanIntEnable(channel) = initPara->ie;  /* SBSW_CAN_LL_112 */  /* keep for usage within ISR and SetControllerMode */

  /* Enable and Select Interrupt Lines */
  if(initPara->ie > 0UL)   /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->ILS), (vuint32)kCanILS_ALL_ZERO, kCanRegCheckMaskILS, initPara); /* All INTs assigned to INT line '0' */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->ILE), (vuint32)kCanILE_EINT0, kCanRegCheckMaskILE, initPara); /* Enable INT line '0' */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
  }
  else
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->ILE), (vuint32)kCanILE_DISABLE, kCanRegCheckMaskILE, initPara); /* Disable INT lines */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
  }
  /* If not PowerOn Init */
  if ( (Can_30_Mcan_GetLogStatus(canHwChannel) & kCan_30_McanHwIsInit) == kCan_30_McanHwIsInit ){
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->IE), (vuint32)(initPara->canInterruptOldStatus), kCanRegCheckMaskIE, initPara); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
  }
  else
  {
    /* Power On */
    if(initPara->ie > 0UL)   /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->IE), (vuint32)(initPara->ie), kCanRegCheckMaskIE, initPara); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
    }
    else
    {
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->IE), (vuint32)kCanIE_DISABLE_ALL, kCanRegCheckMaskIE, initPara); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
    }
#if ( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
  /* The Protocol Exception Event is signalled via PSR.ACT (and PSR.PXE if MCAN Rev. >=3.1.0 ).
     Thus the status has to be monitored */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
    if(CanGetMcanRevision(channel) <= 0x310UL) /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
    {
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->IE), (vuint32)(Cn->IE | (kCanIR_TOO)), kCanRegCheckMaskIE, initPara); /* Enable timeout interrupt */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 
    }
#endif
  }

  /* #40 handle application callback */
#if defined( C_30_MCAN_ENABLE_INIT_POST_PROCESS )
  /* The post processing function is called within the initialization mode of the CAN controller.
     The application can directly overwrite existing configuration in the CAN controller.
     Example: overwriting the baudrate settings with dynamic values, necessary macros are provided in the LL part */
  Appl_30_McanCanInitPostProcessing(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
#endif
  CAN_MSG_RAM_SYNC(); /* PRQA S 1006 */ /* MD_Can_1006_inlineASM */
  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitEnd
Relation_Context:
# CanHL_30_Mcan_InitEnd_InitMode() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEnd( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* After resetting CCCR[INIT] the Bit Stream Processor (BSP) synchronizes itself to the data transfer 
     on the CAN bus by waiting for Bus_Idle (sequence of 11 consecutive recessive bits) .
     CCCR[CCE] is automatically reset when CCCR[INIT] is reset. */
  /* CCCR_: INIT, CCE, ASM, CSR, MON, DAR, TEST disabled (automated retransmission is enabled) */
 vuint8 return_value;  
  
  /* #10 return initialization status */
  /* try to avoid "3673  QAC9-CORE: hardware specific (param could be const)" */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return_value = initPara->isInitOk;

  return (return_value);
}
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitIsMailboxCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitIsMailboxCorrupt
Relation_Context:
# CanHL_30_Mcan_InitXXX() #
OneChOpt, ChannelAmount
Relation:
RamCheck
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport, MultipleBasicCanObjects
MultiplexedTx, TxHwFifo, RxBasicCANSupport
DevErrorDetect
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_30_Mcan_InitIsMailboxCorrupt( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )  /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8   ret_val;
  Can_30_McanObjectHandle mailboxElement = 0;
  volatile vuint32* p2Shm = V_NULL; /* PRQA S 2981 */ /* MD_Can_RedundantInit */

  ret_val = kCan_30_McanFalse; /* Assume That The Mailbox is not corrupt */

# if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
  for (;(( mailboxElement < Can_30_Mcan_GetMailboxSize(initPara->mailboxHandle) ) && (ret_val == kCan_30_McanFalse)); mailboxElement++) /* COV_CAN_HARDWARE_FAILURE */
# endif
  {

    /* If TX Buffer */
    if((initPara->mailboxHandle) < CAN_30_MCAN_HL_MB_TX_BASIC_STOPINDEX(canHwChannel)) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */
    {
      p2Shm = (vuint32*) (pShmTXB(initPara->hwObjHandle + mailboxElement)); /* PRQA S 0303,0310,312,1891,4391,2985,2880 */ /* MD_Can_HwAccess,MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast,MD_Can_1891_LL,MD_Can_IntegerCast,MD_Can_ConstValue,MD_MSR_Unreachable */
    }
# if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
    else if ((initPara->mailboxHandle) < CAN_30_MCAN_HL_MB_RX_FULL_STOPINDEX(canHwChannel))
    {
      p2Shm = (vuint32*) (ShmRXB(initPara->hwObjHandle)); /* PRQA S 0303,0310,312,1891,4391 */ /* MD_Can_HwAccess,MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast,MD_Can_1891_LL,MD_Can_IntegerCast */
    }
# endif
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS)
    else
    {
      /* Rx FIFO 0 */
      if(initPara->mailboxHandle == CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        p2Shm = (vuint32*) (ShmRXF0(mailboxElement));   /* PRQA S 0303,0310,312,2985,4391,1891 */ /* MD_Can_HwAccess,MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast,MD_Can_ConstValue,MD_Can_IntegerCast,MD_Can_1891_LL */
      }
#  if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
      else if(initPara->mailboxHandle == (CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u) ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        p2Shm = (vuint32*) (ShmRXF1(mailboxElement));  /* PRQA S 0303,0310,312,2985,4391,1891 */ /* MD_Can_HwAccess,MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast,MD_Can_ConstValue,MD_Can_IntegerCast,MD_Can_1891_LL */
      }
#  endif
      else
      {
        /* Handle not found, RAM check will return True */
      }
    }
# endif
    if(p2Shm != V_NULL)  /* COV_CAN_GENDATA_FAILURE */
    { /* found valid handle */
      if( ((vuint32)p2Shm < (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || ((vuint32)p2Shm >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) ) /* PRQA S 0306,0303 */ /* MD_Can_0306_HWaccess_LL,MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
      { 
        ret_val = kCan_30_McanTrue; /* address out of range assuming mailbox is corrupt */
      }
      else
      {
        vuint8 i;
        /* at this point the mailbox is not initialized therefore the contents are not saved! */
        /* #20 Iterate test patterns (check ID, Flags Dlc, Data) */
        for(i = 0u; (i < 3u) && (ret_val == kCan_30_McanFalse); i++) /* COV_CAN_HARDWARE_FAILURE */
        { /* PRQA S 0303 QAC_Can_0303 */ /* MD_Can_HwAccess */
          vuint8 j;
# if defined (C_30_MCAN_ENABLE_CAN_FD_FULL)
          for(j=0u ; (j < ((Can_30_Mcan_GetMaxDataLenOfMailbox(initPara->mailboxHandle)/4u) + (8u/4u))) && (ret_val == kCan_30_McanFalse);j++) /* Maximum mailbox size pluss 8 byte header */ /* COV_CAN_HARDWARE_FAILURE */
# else
          for(j=0u; (j <  4u) && (ret_val == kCan_30_McanFalse);j++)  /* 16 byte per mbox */ /* COV_CAN_HARDWARE_FAILURE */
# endif
          {
            p2Shm[j] = Can_30_McanMemCheckValues32bit[i];  /* SBSW_CAN_LL_103 */ /* T0/R0 */
            if(p2Shm[j] != Can_30_McanMemCheckValues32bit[i]) /* COV_CAN_HARDWARE_FAILURE */
            {
              ret_val = kCan_30_McanTrue; /* Mailbox is corrupt */
              /* no break allowed by QAC */
            } 
          }
          /* no break allowed by QAC */
        } 
        /* PRQA  L:QAC_Can_0303 */
      }
    }
    else
    { /* handle not found */
      ret_val = kCan_30_McanTrue;
    }
  }
  return(ret_val);
}  /* PRQA S 6010, 6030, 6080 */  /* MD_MSR_STPTH,MD_MSR_STCYC, MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_CAN_RAM_CHECK */


/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitPowerOn
Relation_Context:
# from Can_Init #
Relation:
OneChOpt
ChannelAmount, Variant
EccConfiguration
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitPowerOn(void)
{
  vuint8 ret;
#if ( CAN_30_MCAN_SAFE_BSW == STD_ON )
  if (CanLL_30_Mcan_CheckGeneratedData() == kCan_30_McanFailed) /* CM_CAN_LL_112 */ /* PRQA S 2992,2996,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
    ret = kCan_30_McanFailed; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
  else
#endif
  {
#if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
# if defined (C_30_MCAN_ENABLE_CANSUBSYSTEMBASEADR) /* COV_CAN_HW_SPECIFIC */
  CanLL_30_Mcan_InitSubSystemVirtualAddr();
#endif
# if defined (C_30_MCAN_ENABLE_CANGLOBALBASEADR) /* COV_CAN_HW_SPECIFIC */
 CanLL_30_Mcan_InitGlobalVirtualAddr();
# endif
#endif
#if defined( C_30_MCAN_ENABLE_REGEXT_TCC ) /* COV_CAN_HW_SPECIFIC */
    CanLL_30_Mcan_SetGlobalRegisterTCC();
#endif
    /* #10 initialize the configured Message RAM area */
    ret = Can_EccInit();
#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
    CanLL_30_Mcan_SetGlobalRegisterTTCanFD();
#endif
#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
    CanLL_30_Mcan_SetGlobalRegisterMcanAS1();
#endif
#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
    CanLL_30_Mcan_SetGlobalRegisterStmFdCan();
#endif
  }
  return(ret);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitPowerOnChannelSpecific
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitPowerOnChannelSpecific
Relation_Context:
# from Can_Init #
Relation:
OneChOpt
ChannelAmount
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitPowerOnChannelSpecific(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY)
{
  /* #10 initialize local variables used for BusOff, Transmit, Interrupt handling and Security event reporting */
#if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
  CanLL_30_Mcan_InitVirtualAddr(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
#endif
  Can_30_Mcan_GetCanBusOffNotification(canHwChannel) = 0; /* SBSW_CAN_LL_112 */ 
#if defined ( CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING )
  Can_30_Mcan_GetPSRValue(canHwChannel) = 0;              /* SBSW_CAN_LL_112 */
#endif
  Can_30_Mcan_GetCanTXBRP(canHwChannel) = 0;              /* SBSW_CAN_LL_112 */ 
  Can_30_Mcan_GetCanIntEnable(canHwChannel) = 0;          /* SBSW_CAN_LL_112 */ 
#if defined (C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION)  
  Can_McanRevision[canHwChannel] = 0;             /* SBSW_CAN_LL_112 */ 
#endif
  Can_30_Mcan_GetCanPrevMode(canHwChannel)  = 0xFF;       /* SBSW_CAN_LL_112 */ 
  Can_30_Mcan_GetCanLastState(canHwChannel) = 0xFF;       /* SBSW_CAN_LL_112 */ 
  return(kCan_30_McanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMemoryPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_InitMemoryPowerOn
Relation_Context:
# from Can_InitMemory #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMemoryPowerOn(void)
{
  /* #10 no actions necessary */
}
/* CODE CATEGORY 4 END */




/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxBegin
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
ChannelAmount, DevErrorDetect
MultiplexedTx
TxHwFifo
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* #10 initialize the pointer to the mailbox */
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if(Can_30_Mcan_GetMailboxType(txPara->mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      txPara->lpTXB = &ShmTXB(Can_30_McanGetTxHwFifoPutIndex(canHwChannel)); /* PRQA S 0303,4391 */ /* MD_Can_HwAccess,MD_Can_IntegerCast */ /* SBSW_CAN_LL_113 */
    }
    else
# endif
    {
      txPara->lpTXB = &ShmTXB((vuint32)txPara->hwObjHandle + (vuint32)(txPara->mailboxElement)); /* PRQA S 0303,1891,4391 */ /* MD_Can_HwAccess,MD_Can_1891_LL,MD_Can_IntegerCast */ /* SBSW_CAN_LL_113 */
    }

  /* #20 check boundaries */
# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if( ((vuint32)txPara->lpTXB < (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || ((vuint32)&ShmTXB(txPara->hwObjHandle +1u) >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) ) /* PRQA S 0303,4391 */ /* MD_Can_HwAccess,MD_Can_IntegerCast */ /* CM_CAN_LL_103 */  /* COV_CAN_GENDATA_FAILURE */
  { /* SilentBSW check */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_WRITE_ID, CAN_30_MCAN_E_PARAM_HANDLE);
    txPara->lpTXB = (Can_30_McanElmType*)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel); /* assure no out of bounds access */ /* PRQA S 0303 */ /* MD_Can_HwAccess */  /* SBSW_CAN_LL_113 */
  }
# endif
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxSetMailbox
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxSetMailbox
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
ChannelAmount, IDType
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxSetMailbox(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 set the mailbox control registers */
  txPara->lpTXB->E0 = txPara->idRaw0;                       /* SBSW_CAN_LL_103 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
# if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
  txPara->lpTXB->E1 =  ( ((vuint32) (((vuint32)txPara->dlcRaw) << 16)) | 
                         ((vuint32) (((vuint32)txPara->fdType) << 16)) | 
                         ((vuint32) (((vuint32)txPara->fdBrsType) << 16)) ); /* set DLC/FDF/BRS */  /* SBSW_CAN_LL_103 */  /* PRQA S 0303 */  /* MD_Can_HwAccess */
# else
  txPara->lpTXB->E1 = (vuint32) (((vuint32)txPara->dlcRaw) << 16);           /* set DLC/FDF/BRS */  /* SBSW_CAN_LL_103 */  /* PRQA S 0303 */  /* MD_Can_HwAccess */
# endif  /* C_30_MCAN_ENABLE_CAN_FD_USED */
#else
  txPara->lpTXB->E1 = (vuint32) (((vuint32)txPara->dlcRaw) << 16);           /* set DLC */          /* SBSW_CAN_LL_103 */  /* PRQA S 0303 */  /* MD_Can_HwAccess */
#endif  /* CAN_MCAN_REVISION */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxCopyToCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxCopyToCan
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
ChannelAmount, CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxCopyToCan(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
#  if defined( C_CPUTYPE_BITORDER_LSB2MSB ) /* COV_CAN_CPUTYPE */
#  else
  vuint8 offset;
#  endif
  vuint8 curWord, curByte;
  tAlignCopyElem copyElem;  /* PRQA S 0759 */ /* MD_Can_Union */

  /* #10 copy the transmit data to a temporary buffer and set the mailbox data registers */
  curByte = 0u;
#  if defined (C_30_MCAN_ENABLE_CAN_FD_FULL)
  for (curWord = 0u; (curWord << 2u) < txPara->frameLen; curWord++) /* CM_CAN_LL_105 */ 
#  else
  for (curWord = 0u; (curWord) < 2u; curWord++) /* CM_CAN_LL_105 */ 
#  endif
  {
#  if defined( C_CPUTYPE_BITORDER_LSB2MSB ) /* COV_CAN_CPUTYPE */
    do
    { /* for each 32 bit word */
#   if defined (C_30_MCAN_ENABLE_CAN_FD_FULL)
      if(curByte < txPara->messageLen)  /* CM_CAN_LL_105 */ 
#   endif
      { /* either copy data */
        copyElem.b[curByte & 0x03u] = txPara->CanMemCopySrcPtr[curByte]; /* SBSW_CAN_LL_104 */ /* CM_CAN_LL_104 */
      }
#   if defined (C_30_MCAN_ENABLE_CAN_FD_FULL) 
      else
      { /* or fill up with padding pattern */
        copyElem.b[curByte & 0x03u] = txPara->paddingVal;              /* SBSW_CAN_LL_104 */ /* CM_CAN_LL_104 */
      }
#   endif
      curByte++;
    } while((curByte & 0x03u) != 0u);                             /* CM_CAN_LL_104 */
#  else /* LSB2MSB */
    offset = 3u;
    do
    { /* for each 32 bit word */
#   if defined (C_30_MCAN_ENABLE_CAN_FD_FULL)
      if(curByte < txPara->messageLen) 
#   endif
      { /* either copy data */
        copyElem.b[offset] = txPara->CanMemCopySrcPtr[curByte]; /* SBSW_CAN_LL_104 */  
      }
#   if defined (C_30_MCAN_ENABLE_CAN_FD_FULL)
      else
      { /* or fill up with padding pattern */
        copyElem.b[offset] = txPara->paddingVal;              /* SBSW_CAN_LL_104 */
      }
#   endif
      curByte++;
      offset--;
    } while((curByte & 0x03u) != 0u);                     /* CM_CAN_LL_104 */  
#  endif /* LSB2MSB */
    /* move to Message RAM */
    txPara->lpTXB->data[curWord] = copyElem.dw; /* SBSW_CAN_LL_103 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  } /* end for loop */

  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

} /* CanLL_30_Mcan_TxCopyToCan */
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxStart
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxStart
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
ChannelAmount, CanFdSupport, IDType
MultiplexedTx
TxHwFifo
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_TxStart(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8  retvalue = kCan_30_McanOk;
  vuint32 txBRP;

  /* #10 get the corresponding Tx Buffer */
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
  if(Can_30_Mcan_GetMailboxType(txPara->mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
  {
    txBRP = (vuint32)(kCan_30_McanACTIVE << Can_30_McanGetTxHwFifoPutIndex(canHwChannel)); /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
  else
# endif
  {
    txBRP = (vuint32)(kCan_30_McanACTIVE << ((txPara->hwObjHandle) + (txPara->mailboxElement)));
  }
  /* Each Tx Buffer has its own Add Request bit. 
     Writing a '1' will set the corresponding Add Request bit (writing a '0' has no impact). 
     This enables the Host to set transmission requests for multiple Tx Buffers with one write to TXBAR. 
     TXBAR bits are set only for those Tx Buffers configured via TXBC. 
     When no Tx scan is running, the bits are reset immediately, else the bits remain set until the Tx scan process has completed. */
  {
    /* #20 set transmission request */
    CAN_MSG_RAM_SYNC(); /* PRQA S 1006 */ /* MD_Can_1006_inlineASM */
    Cn->TXBAR = txBRP;   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */ 
    /* Each Tx Buffer has its own Transmission Request Pending bit. 
     The bits are set via register TXBAR. The bits are reset after a requested transmission has completed or has been cancelled via register TXBCR.
     TXBRP bits are set only for those Tx Buffers configured via TXBC. 
     After a TXBRP bit has been set, a Tx scan is started to check for the pending Tx request with the highest priority (lowest ID).
     A cancellation request resets the corresponding transmission request pending bit of register TXBRP. 
     In case a transmission has already been started when a cancellation is requested, this is done at the end of the transmission, 
     regardless whether the transmission was successful or not. The cancellation request bits are reset directly after the corresponding TXBRP bit has been reset. */
     /* #30 store the Tx Buffer number for confirmation handling */
     Can_30_Mcan_GetCanTXBRP(canHwChannel) |= txBRP;   /* SBSW_CAN_LL_112 */ 
  }
  return(retvalue);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxEnd
Relation_Context:
# from Can_Write #
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions necessary */
  CAN_30_MCAN_DUMMY_STATEMENT(txPara);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

#if defined( C_30_MCAN_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxIsGlobalConfPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxIsGlobalConfPending
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
OneChOpt, ChannelAmount
MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_TxIsGlobalConfPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCan_30_McanFalse;
  /* #10 check for pending transmit requests */
  if(Can_30_Mcan_GetCanTXBRP(canHwChannel) != 0u)
  { /* Tx request is pending (do not check the HW Flags because reset is done only within next transmit request) */
    retVal = kCan_30_McanTrue;
  }
  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxProcessPendings
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
OneChOpt
ChannelAmount, MultiplexedTx
ChannelAmount, TxHwFifo
TxHwFifo, MultiplexedTx
ChannelAmount, TxBasicAmount, TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  Can_30_McanDeclareGlobalInterruptOldStatus
  vuint32 txBRP;
  Can_30_McanObjectHandle mailboxElement = 0;

  Can_30_McanNestedGlobalInterruptDisable();

# if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    for (;mailboxElement < Can_30_Mcan_GetMailboxSize(taskPara->mailboxHandle); mailboxElement++)
# endif
    {
      /* #10 get the corresponding Tx Buffer number to be confirmed */
      txBRP = CanLL_30_Mcan_if_TxIsObjConfPending(CAN_30_MCAN_CHANNEL_CANPARA_FIRST ((vuint32)(kCan_30_McanACTIVE << (taskPara->hwObjHandle + mailboxElement))) ); /* PRQA S 2985 */ /* MD_Can_ConstValue */
      /* #20 confirmation handling for a specific Tx Buffer */
      if(txBRP == kCan_30_McanOk) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* at least one Tx buffer is pending */
        CanHL_30_Mcan_TxConfirmationPolling(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, mailboxElement, taskPara->hwObjHandle + mailboxElement); /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
    }
  Can_30_McanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 2 END */
#endif /* C_30_MCAN_ENABLE_TX_POLLING */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxConfBegin
Relation_Context:
# from CanHL_30_Mcan_TxConfirmation #
Relation:
OneChOpt
ChannelAmount, TxBasicAmount, TxFullAmount
MultiplexedTx
IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)  /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint32 txBRP = (vuint32)(kCan_30_McanACTIVE << (txConfPara->hwObjHandle));
  
  Can_30_McanDeclareGlobalInterruptOldStatus
 
  /* #10 check for unexpected confirmation */
  assertHardware( ((Can_30_Mcan_GetCanTXBRP(canHwChannel) & txBRP) != 0UL), canHwChannel, kCanErrorUnexpectedConfirmation); /* COV_CAN_GENDATA_FAILURE */

  Can_30_McanNestedGlobalInterruptDisable();
  /* #20 clear pending flag for a specific Tx Buffer */  
  Can_30_Mcan_GetCanTXBRP(canHwChannel)     &= ((vuint32)~txBRP);  /* SBSW_CAN_LL_112 */  
  Can_30_McanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 1 END */


#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfSetTxConfStruct
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxConfSetTxConfStruct
Relation_Context:
# from CanHL_30_Mcan_TxConfirmation #
GenericConfirmation
Relation:
OneChOpt
ChannelAmount, MultiplexedTx, CanFdSupport, TxBasicAmount, TxFullCANSupport, TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfSetTxConfStruct(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
{
#if defined( C_30_MCAN_ENABLE_CAN_FD_FULL )
  {
    vuint8 i;
    for(i=0u ; i< (Can_30_Mcan_GetMaxDataLenOfMailbox(txConfPara->mailboxHandle)/4u) ; i++)
    {
      *(vuint32*)&txConfPara->tmpTXB.data[i] = ShmTXB(txConfPara->hwObjHandle).data[i];                  /* PRQA S 0303,0312,4391 */      /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast,MD_Can_IntegerCast */                /* first transfer the 32 bit aligned Message RAM to a byte array */ /* SBSW_CAN_LL_109 */ 
      *(vuint32*)&txConfPara->tmpTXB.data[i] = CanBswap32(*(vuint32*)&txConfPara->tmpTXB.data[i]);     /* PRQA S 0303,0312,0404 */ /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast,MD_Can_0404_LL */ /* then sort bytes depending on endianess */ /* SBSW_CAN_LL_109 */ 
    }
  }
#else
  *(vuint32*)&txConfPara->tmpTXB.data[0] = ShmTXB(txConfPara->hwObjHandle).data[0];                  /* PRQA S 0303,0312 */ /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast */                     /* first transfer the 32 bit aligned Message RAM to a byte array */ /* SBSW_CAN_LL_109 */ 
  *(vuint32*)&txConfPara->tmpTXB.data[1] = ShmTXB(txConfPara->hwObjHandle).data[1];                  /* PRQA S 0303,0312 */ /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_LL_109 */ 
  *(vuint32*)&txConfPara->tmpTXB.data[0] = CanBswap32(*(vuint32*)&txConfPara->tmpTXB.data[0]);     /* PRQA S 0303,0312,0404 */ /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast,MD_Can_0404_LL */ /* then sort bytes depending on endianess */ /* SBSW_CAN_LL_109 */ 
  *(vuint32*)&txConfPara->tmpTXB.data[1] = CanBswap32(*(vuint32*)&txConfPara->tmpTXB.data[1]);     /* PRQA S 0303,0312,0404 */ /* MD_Can_HwAccess,MD_Can_NoneVolatilePointerCast,MD_Can_0404_LL */  /* SBSW_CAN_LL_109 */ 
#endif

  /* #10 set pointers in the transmit structure */
  txConfPara->txStructConf->pChipData   = (Can_30_McanChipDataPtr)&txConfPara->tmpTXB.data[0]; /* finally hand the byte pointer to the application */ /* SBSW_CAN_LL_109 */ 
  txConfPara->txStructConf->pChipMsgObj = (Can_30_McanChipMsgPtr) &ShmTXB(txConfPara->hwObjHandle).E0;  /* PRQA S 0310,0303,4391 */ /* MD_Can_PointerCast, MD_Can_HwAccess, MD_Can_IntegerCast */  /* SBSW_CAN_LL_109 */ 
}
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_TxConfEnd
Relation_Context:
# from CanHL_30_Mcan_TxConfirmation #
Relation:
OneChOpt,
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions necessary */
  CAN_30_MCAN_DUMMY_STATEMENT(txConfPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */



#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicMsgReceivedBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicMsgReceivedBegin
Relation_Context:
# from CanHL_30_Mcan_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
OneChOpt
ChannelAmount
HardwareLoopCheck
CanFdSupport
MultipleBasicCanObjects
Overrun
RxFullAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicMsgReceivedBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  vuint8  indexL;
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
  vuint8  fElmSize;
# endif

  /* #10 get the FIFO buffer */
# if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if(rxBasicPara->mailboxHandle == (CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u) )  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* point to Fifo-1 */
    rxBasicPara->pFifoAck    = &(Cn->RXF1A); /* SBSW_CAN_LL_109 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */
    rxBasicPara->pFifoStatus = &(Cn->RXF1S); /* SBSW_CAN_LL_109 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */
    rxBasicPara->fGetIndex   = (vuint8)(rxBasicPara->pFifoStatus->B.FnGI); /* SBSW_CAN_LL_109 */ 
    rxBasicPara->pShm        = ShmRXF1(rxBasicPara->fGetIndex);            /* PRQA S 0303,1891,4391 */ /* MD_Can_HwAccess,MD_Can_1891_LL,MD_Can_IntegerCast */ /* SBSW_CAN_LL_109 */ 
  }
  else
# endif
  { /* point to Fifo-0 */
    rxBasicPara->pFifoAck    = &(Cn->RXF0A); /* SBSW_CAN_LL_109 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */
    rxBasicPara->pFifoStatus = &(Cn->RXF0S); /* SBSW_CAN_LL_109 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */
    rxBasicPara->fGetIndex   = (vuint8)(rxBasicPara->pFifoStatus->B.FnGI); /* SBSW_CAN_LL_109 */ 
    rxBasicPara->pShm        = ShmRXF0(rxBasicPara->fGetIndex);            /* PRQA S 0303,1891,4391 */ /* MD_Can_HwAccess,MD_Can_1891_LL,MD_Can_IntegerCast */ /* SBSW_CAN_LL_109 */
  }

  /* #20 copy mailbox contents to temporary buffer */
  rxBasicPara->fElm.E0      = rxBasicPara->pShm->E0; /* SBSW_CAN_LL_109 */ 
  rxBasicPara->fElm.E1      = rxBasicPara->pShm->E1; /* SBSW_CAN_LL_109 */ 
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
  fElmSize = CAN_30_MCAN_DLC2LEN(((rxBasicPara->fElm.E1) & 0x000F0000UL) >> 16u); /* SBSW_CAN_LL_109 */
  for(indexL = 0u; (indexL << 2u) < fElmSize; indexL++)
#else
  for(indexL = 0u; indexL < 2u; indexL++)
#endif
  {
    rxBasicPara->fElm.data[indexL] = CanBswap32(rxBasicPara->pShm->data[indexL]);    /* PRQA S 0404 */  /* MD_Can_0404_LL */ /* SBSW_CAN_LL_109 */ 
  }

  /* #30 set pointers to the received message */
  rxBasicPara->rxStruct.pChipMsgObj = (Can_30_McanChipMsgPtr)  &rxBasicPara->fElm.E0;      /* SBSW_CAN_LL_109 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */
  rxBasicPara->rxStruct.pChipData   = (Can_30_McanChipDataPtr) &rxBasicPara->fElm.data[0]; /* SBSW_CAN_LL_109 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */

  return(kCan_30_McanOk);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicReleaseObj
Relation_Context:
# from CanHL_30_Mcan_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
OneChOpt
ChannelAmount, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicReleaseObj(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  if( (((vuint32)*(vuint32*) rxBasicPara->pFifoStatus) & kCanRXFnS_FnFL) > 0UL)  /* PRQA S 0310,0312 */ /* MD_Can_PointerCast,MD_Can_NoneVolatilePointerCast */ /* COV_CAN_MCAN_SAFETY_CHECK */
  { /* Attention: ACK with Fill Level '0' will result in a endless read loop !!! */
    /* ACK: After the Host has read a message or a sequence of messages it has to write the buffer index of the last element read to FnAI. 
            This will set the Get Index RXFnS[FnGI] to FnAI+1 and update the FIFO Fill Level RXF0S[FnFL]. */
    /* #10 acknowledge the received messsage and go to the next one, if available */
    *rxBasicPara->pFifoAck    = (rxBasicPara->fGetIndex & 0x0000003FUL); /* SBSW_CAN_LL_109 */  
  }
  else
  {
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, CAN_30_MCAN_E_PARAM_CONTROLLER);   /* COV_CAN_HARDWARE_FAILURE */
  }
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicMsgReceivedEnd
Relation_Context:
# from CanHL_30_Mcan_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicMsgReceivedEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions required */
  CAN_30_MCAN_DUMMY_STATEMENT(rxBasicPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

# if defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicIsGlobalIndPending
Relation_Context:
# from CanHL_30_Mcan_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount, MultipleBasicCanObjects, RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
# CAN_BOSCH_ERRATUM_012 #
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicIsGlobalIndPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8  retvalue = kCan_30_McanFalse;
# if ( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
#  if !defined( C_30_MCAN_ENABLE_ISR_MANDATORY )  /* ISR not available, pure polling configuration */
  {/* check periodically for erratum12 */
    if( (Cn->IR  & kCanIR_TOO) != 0u)
    { /* timeout arrived */
      CanInterruptTimeoutCounter(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
    }
  }
#  endif
# endif

  /* #10 check the FIFO fill level for reception events */
#if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if( ((Cn->RXF0S.R & kCanRXFnS_FnFL) > 0u) || ((Cn->RXF1S.R & kCanRXFnS_FnFL) > 0u) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
  if( ((Cn->RXF0S.R & kCanRXFnS_FnFL) > 0u) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
  {
    retvalue = kCan_30_McanTrue;
  }
  return retvalue;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicProcessPendings
Relation_Context:
# from CanHL_30_Mcan_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount, MultipleBasicCanObjects, RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint8 fillLevel;

  /* #10 get the corresponding FIFO buffer */
#if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if(taskPara->mailboxHandle == (CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* point to Fifo-1 */
    fillLevel = Cn->RXF1S.B.FnFL;  /* PRQA S 1843,4558,0303 */ /* MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
  }
  else
#endif
  { /* point to Fifo-0 */
    fillLevel = Cn->RXF0S.B.FnFL;  /* PRQA S 1843,4558,0303 */ /* MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
  }
  
  /* #20 call the reception handling for each message until the FIFO buffer is empty */
  while( ((fillLevel) > 0u) ) 
  {
    fillLevel--;
    CanHL_30_Mcan_BasicCanMsgReceivedPolling(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, taskPara->hwObjHandle);
  }

}
/* CODE CATEGORY 2 END */
# endif /* C_30_MCAN_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullMsgReceivedBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxFullMsgReceivedBegin
Relation_Context:
# from CanHL_30_Mcan_FullCanMsgReceived #
RxFullCANSupport
Relation:
OneChOpt, ChannelAmount, HardwareLoopCheck
CanFdSupport
Overrun
RxFullCANSupport, RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxFullMsgReceivedBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
  vuint8 rElmSize, indexL;
# endif
# if defined (C_CPUTYPE_BITORDER_MSB2LSB) /* COV_CAN_CPUTYPE */
  vuint32 fElmTmp;
#endif

  rxFullPara->rxStruct.pChipMsgObj = (Can_30_McanChipMsgPtr)  &rxFullPara->bfElm;         /* SBSW_CAN_LL_109 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */
  rxFullPara->rxStruct.pChipData   = (Can_30_McanChipDataPtr) &rxFullPara->bfElm.data[0]; /* SBSW_CAN_LL_109 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */ 

  /* #10 get the pointer to the message object */
  rxFullPara->pShm = ShmRXB(rxFullPara->hwObjHandle); /* PRQA S 0303,1891,4391 */ /* MD_Can_HwAccess,MD_Can_1891_LL,MD_Can_IntegerCast */ /* SBSW_CAN_LL_109 */
  rxFullPara->bfElm.E0 = rxFullPara->pShm->E0; /* SBSW_CAN_LL_109 */ 
  rxFullPara->bfElm.E1 = rxFullPara->pShm->E1; /* SBSW_CAN_LL_109 */ 

# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
  rElmSize = CAN_30_MCAN_DLC2LEN((vuint32)((rxFullPara->bfElm.E1) & 0x000F0000UL) >> 16u); /* SBSW_CAN_LL_109 */

  /* #20 copy the data */
  for(indexL = 0u; (indexL << 2u) < rElmSize; indexL++) /* SBSW_CAN_LL_109 */ /* SBSW_CAN_LL_109 */ 
  {
# if defined (C_CPUTYPE_BITORDER_MSB2LSB) /* COV_CAN_CPUTYPE */
    fElmTmp            = rxFullPara->pShm->data[indexL];  /* SBSW_CAN_LL_109 */ 
    rxFullPara->bfElm.data[indexL] = CanBswap32(fElmTmp); /* SBSW_CAN_LL_109 */ 
# else
    rxFullPara->bfElm.data[indexL] = rxFullPara->pShm->data[indexL];  /* SBSW_CAN_LL_109 */ 
# endif
  }
#else /* C_30_MCAN_ENABLE_CAN_FD_FULL */
# if defined (C_CPUTYPE_BITORDER_MSB2LSB) /* COV_CAN_CPUTYPE */
  fElmTmp = rxFullPara->pShm->data[0]; /* SBSW_CAN_LL_109 */ 
  rxFullPara->bfElm.data[0] = CanBswap32(fElmTmp); /* SBSW_CAN_LL_109 */ 
  fElmTmp = rxFullPara->pShm->data[1]; /* SBSW_CAN_LL_109 */ 
  rxFullPara->bfElm.data[1] = CanBswap32(fElmTmp); /* SBSW_CAN_LL_109 */ 
# else
  rxFullPara->bfElm.data[0] = rxFullPara->pShm->data[0]; /* SBSW_CAN_LL_109 */ 
  rxFullPara->bfElm.data[1] = rxFullPara->pShm->data[1]; /* SBSW_CAN_LL_109 */ 
# endif
#endif /* C_30_MCAN_ENABLE_CAN_FD_FULL */

  /* #30 clear the New Data Flag  */
  Cn->NDATA[(rxFullPara->hwObjHandle>>0x05UL)] = (0x00000001UL << (rxFullPara->hwObjHandle & 0x1FUL)); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */
  
  /* While an Rx Buffer's New Data flag is set, a Message ID Filter Element referencing this specific Rx Buffer will not match, causing the acceptance filtering to continue. 
   Following Message ID Filter Elements may cause the received message to be stored 
   - into another Rx Buffer or
   - into an Rx FIFO or
   - the message may be rejected,
   depending on filter configuration. */
  return(kCan_30_McanOk);
}
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxFullReleaseObj
Relation_Context:
# from CanHL_30_Mcan_FullCanMsgReceived #
RxFullCANSupport
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
 V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullReleaseObj(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions required */
  CAN_30_MCAN_DUMMY_STATEMENT(rxFullPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxFullMsgReceivedEnd
Relation_Context:
# from CanHL_30_Mcan_FullCanMsgReceived #
RxFullCANSupport
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullMsgReceivedEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 no actions required */
  CAN_30_MCAN_DUMMY_STATEMENT(rxFullPara);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


# if defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxFullIsGlobalIndPending
Relation_Context:
# from CanHL_30_Mcan_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
# CAN_BOSCH_ERRATUM_012 #
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxFullIsGlobalIndPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCan_30_McanFalse;
# if ( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
#  if !defined( C_30_MCAN_ENABLE_ISR_MANDATORY )  /* ISR not available, pure polling configuration */
  {/* check periodically for erratum12 */
    if( (Cn->IR  & kCanIR_TOO) != 0u) /* PRQA S 0303 */ /* MD_Can_HwAccess */
    { /* timeout arrived */
      CanInterruptTimeoutCounter(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
    }
  }
#  endif
# endif

  /* #10 check the receive buffer new data registers for reception events */
  if( (Cn->NDATA[0] != 0u) || (Cn->NDATA[1] != 0u) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    retVal = kCan_30_McanTrue;
  }
  return retVal;
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxFullProcessPendings
Relation_Context:
# from CanHL_30_Mcan_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  vuint32 ndfPos, shiftVal, ndata;

  /* #10 calculate the corresponding Tx Buffer */
  ndfPos = (vuint32)taskPara->hwObjHandle; 
  if(ndfPos >= 32u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    ndata = Cn->NDATA[1]; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_106 */
    ndfPos -= 32u;
  }
  else
  {
    ndata = Cn->NDATA[0]; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_106 */
  }

  shiftVal = (vuint32)(0x00000001UL << ndfPos);

  /* #20 call the reception handling for the mailbox which received a new message */
  if( (ndata & shiftVal) != 0u)
  {
    /* While an Rx Buffers NDF is set the belonging ID Filter will not match, causing the acceptance filtering to continue. 
       Following ID Filters may cause the received message to be stored into another Rx Buffer or into an Rx FIFO or the message may be rejected. */
    CanHL_30_Mcan_FullCanMsgReceivedPolling(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST (taskPara->mailboxHandle), (taskPara->hwObjHandle));
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_30_MCAN_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */



#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING) 

/****************************************************************************
| NAME:             CanLL_30_Mcan_GetLastErrorCode
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_GetLastErrorCode
Relation_Context:
StatusPolling
# from CanLL_30_Mcan_ErrorNotificationHandling #
Relation:
OneChOpt, ChannelAmount
CanSecurityEventReporting, CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
*/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_GetLastErrorCode(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 ErrorValue = kCanPSR_LEC_NO_ERROR; /* PRQA S 2981 */ /* MD_Can_RedundantInit */

# if defined ( C_30_MCAN_ENABLE_CAN_FD_FULL ) || defined ( C_30_MCAN_ENABLE_CAN_FD_USED )
  /* #10 check the type of the last frame: FD frame or not */
  if ((Can_30_Mcan_GetPSRValue(canHwChannel) & kCanPSR_RBRS) == kCanPSR_RBRS)
  {
   ErrorValue = (vuint8)((Can_30_Mcan_GetPSRValue(canHwChannel) & kCanPSR_FLEC) >> 8);
  }
  else
  {
    ErrorValue = (vuint8)(Can_30_Mcan_GetPSRValue(canHwChannel) & kCanPSR_LEC);
  }
# else
  ErrorValue = (vuint8)(Can_30_Mcan_GetPSRValue(canHwChannel) & kCanPSR_LEC);
# endif

  /* #20 return the error value */
  return ErrorValue;
}

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorStatePassiveTransitionOccurred
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_ErrorStatePassiveTransitionOccurred
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling
Relation:
OneChOpt, ChannelAmount
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_ErrorStatePassiveTransitionOccured( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCan_30_McanFalse;

  /* #10 Check if a transistion to error state passive has occurred */
  if ((Cn->IR & kCanIR_EP) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */
  {
    if (CanLL_30_Mcan_HwIsPassive( canHwChannel )) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    {
      retVal = kCan_30_McanTrue;
    }

   /* #15 Clear the error state passive flag */
   Cn->IR = (vuint32)(kCanIR_EP); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */
  }

  return(retVal);
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorNotificationHandling
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_ErrorNotificationHandling
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling
Relation:
OneChOpt, ChannelAmount
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorNotificationHandling( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
 
 /* #10 check the error code and call the error notification */
switch (CanLL_30_Mcan_GetLastErrorCode(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY))
 {
  case kCanPSR_LEC_Stuff_ERROR:
  /* Stuffing bits not as expected */
  CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_CHECK_STUFFING_FAILED);
  break;

  case kCanPSR_LEC_FORM_ERROR:
  /* Violations of the fixed frame format */
  CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_CHECK_FORM_FAILED);
  break;

  case kCanPSR_LEC_ACK_ERROR:
    /* Acknowledgement check failed */
    CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_CHECK_ACK_FAILED);
  break;

  case kCanPSR_LEC_BIT1_ERROR:
   /* A 0 was transmitted and a 1 was read back */
   CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_BIT_MONITORING0);
  break;

  case kCanPSR_LEC_BIT0_ERROR:
    /* A 1 was transmitted and a 0 was read back */
    CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_BIT_MONITORING1);
  break;

  case kCanPSR_LEC_CRC_ERROR:
  /* CRC failed */
  CanHL_30_Mcan_ErrorNotification(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST CAN_ERROR_CHECK_CRC_FAILED);
  break;

  default:
  /*! No error detected - value 0 or 7 of LEC or FLEC means that no error detected */
  break;
 }
}
/* CODE CATEGORY 2 END */
#endif /* CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorHandlingBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_ErrorHandlingBegin
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling
Relation:
OneChOpt, ChannelAmount
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
# CAN_MCAN_REVISION #
# CAN_BOSCH_ERRATUM_011 #
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorHandlingBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ***
  If the CAN protocol controller has detected an error condition (e.g. CRC error), the message is 
  discarded with the following impact on the affected Rx Buffer or Rx FIFO:
  Rx Buffer: NDF of matching Rx Buffer is NOT set, but Rx Buffer (partly) overwritten with received data. 
  Rx FIFO:   Put index of FIFO is NOT updated,  but FIFO element (partly) overwritten with received data. 

  If the matching Rx FIFO is operated in overwrite mode, the boundary conditions have to be considered
  It might happen that a received message is written to the Message RAM (put index) while the CPU is 
  reading from the Message RAM (get index). 
  In this case inconsistent data may be read from the FIFO element.
  For error type see PSR.LEC respectively PSR.FLEC.
  *** */
#if ( CAN_BOSCH_ERRATUM_011 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
  if((Cn->IR & kCanIR_MRAF) != 0)        /* COV_CAN_MCAN_NOT_SUPPORTED */
  {  /* IR.MRAF is erroneously set during frame reception while the M_CAN is in Error Passive state and 
        the Receive Error Counter has the value ECR.REC = 127.
        Workaround:
        The Message RAM Access Failure routine needs to check whether ECR.RP = '1' 
        (REC has reached the error passive level of 128) and ECR.REC = 127. 
        In this case reset IR.MRAF, no further action required. */
    /* #10 clear erroneous interrupt flag (see MCAN Erratum #11) */
    if( ((Cn->ECR & kCanECR_RP) != 0) && (((Cn->ECR & kCanECR_REC) >> 8) == 127) ) /* COV_CAN_HW_SPECIFIC */
    {
      Cn->IR = kCanIR_MRAF;   /* SBSW_CAN_LL_100 */    /* reset and forget */
    }
  }
#endif
#if ( CAN_BOSCH_ERRATUM_011 == STD_OFF )  /* COV_CAN_HW_SPECIFIC_FUNCTIONALITY */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if defined( CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING )
  Can_30_Mcan_GetPSRValue(canHwChannel) = Cn->PSR; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_112 */
#endif
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_BusOffOccured
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_BusOffOccured
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_BusOffOccured(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal = kCan_30_McanFalse;
  /* #10 check if a busoff occurred */
  if(CanErrorHandlingBusOff(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanOk) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    retVal = kCan_30_McanTrue;
  }
  return(retVal);
}
/* CODE CATEGORY 2 END */

#if defined( C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS )    /* COV_CAN_OVERRUN_IN_STATUS */
# if defined( C_30_MCAN_ENABLE_OVERRUN ) && defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS)
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicCanOverrun
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_RxBasicCanOverrun
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling, Overrun, RxBasicCANSupport
Relation:
OneChOpt
MultipleBasicCanObjects, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicCanOverrun(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 ret_val = kCan_30_McanFalse;

  /* #10 check if a receive FIFO buffer overrun occurred */
#  if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if( ((Cn->IR) & ((vuint32)(kCanIR_RF0L | kCanIR_RF1L)) ) != 0UL) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  else
  if( ((Cn->IR) & (kCanIR_RF0L) ) != 0UL)               /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  endif
  {
    /* #20 clear the overrun (and full) flag */
    Cn->IR = (vuint32)(kCanIR_RF0L | kCanIR_RF0F | kCanIR_RF1L | kCanIR_RF1F);   /* SBSW_CAN_LL_100 */  /* PRQA S 0303 */ /* MD_Can_HwAccess */
    ret_val = kCan_30_McanTrue;
  }
  return(ret_val);
}
/* CODE CATEGORY 2 END */
# endif

#endif /* C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorHandlingEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_ErrorHandlingEnd
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
StatusPolling
Relation:
OneChOpt
MultipleBasicCanObjects, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorHandlingEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if( ((Cn->IR) & (kCanIR_RF0L | kCanIR_RF1L) ) != 0UL) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
  if( ((Cn->IR) & (kCanIR_RF0L) ) != 0UL)               /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
  {
    /* #10 clear overrun (and full) flag */
    Cn->IR = (vuint32)(kCanIR_RF0L | kCanIR_RF0F | kCanIR_RF1L | kCanIR_RF1F);   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
}
/* CODE CATEGORY 2 END */

#if defined( C_30_MCAN_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_GetStatusBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_GetStatusBegin
Relation_Context:
# from Can_30_Mcan_GetStatus
CanGetStatus
Relation:
OneChOpt,
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 3 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_GetStatusBegin(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY)
{
  /* #10 no actions required */
  CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 3 END */
#endif



/**********************************************************************************************************************
 *  CanLL_30_Mcan_ModeTransition
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_ModeTransition
Relation_Context:
# from CanHL_30_Mcan_ModeTransition() #
Wakeup, OneChOpt, HardwareLoopCheck, ChannelAmount
RamCheck, OneChOpt, HardwareLoopCheck, ChannelAmount
# from Can_Mainfunction_Mode() #
ChannelAmount
Relation:
OneChOpt
SilentMode, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck)
{
  vuint8 ret = kCan_30_McanFailed;

  switch(mode)
  {
    case kCan_30_McanModeStartReinit:      /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    case kCan_30_McanModeResetBusOffEnd:   /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      /* #10 START (reinit BusOffEnd) request  */
      /* perform BusOffEnd handling (delete pending BusOff), goto START  */
      /* #20 START (reinit) request */
      /* Reinit means that a call of CanHL_30_Mcan_ReInit() should be included (after set to init mode) before the transition to final target mode */
      if( (Can_30_Mcan_GetCanPrevMode(canHwChannel) == mode) && (Can_30_Mcan_GetCanLastState(canHwChannel) == kCan_30_McanRequested) ) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
      { /* repeat requested mode change without repeating reinit */
        ret = CanLL_30_Mcan_StartRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
      }
      else
      {
        ret = CanHL_30_Mcan_ReInit(CAN_30_MCAN_CHANNEL_CANPARA_FIRST ramCheck);
        if(ret == kCan_30_McanOk) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
        {
          ret = CanLL_30_Mcan_StartRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
        }
      }
      break;

    case kCan_30_McanModeStart:   /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      /* #30 START request */
      /* if in stop mode, otherwise first go to stop mode */
      ret = CanLL_30_Mcan_StartRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
      break;

#if defined(C_30_MCAN_ENABLE_SILENT_MODE) 
    case kCan_30_McanModeSilent:
      /* #40 START SILENT request */
      /* if in stop mode, otherwise first go to stop mode */
      if( (Can_30_Mcan_GetCanPrevMode(canHwChannel) == mode) && (Can_30_Mcan_GetCanLastState(canHwChannel) == kCan_30_McanRequested) ) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
      { /* repeat requested mode change without repeating reinit */
        ret = CanLL_30_Mcan_StartSilentRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
      }
      else
      {
        ret = CanHL_30_Mcan_ReInit(CAN_30_MCAN_CHANNEL_CANPARA_FIRST ramCheck);
        if(ret == kCan_30_McanOk) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
        {
          ret = CanLL_30_Mcan_StartSilentRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
        }
      }
      break;
#endif

    case kCan_30_McanModeResetBusOffStart:   /* ASR: kCan_30_McanModeResetBusOffEnd or kCan_30_McanModeResetBusOffStart should do a Reinit (short is ok, ASR: with CanHL_30_Mcan_CleanUpSendState()) */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    case kCan_30_McanModeStopReinit:
        /* #50 STOP (reinit BusOffStart) request */
        if( (Can_30_Mcan_GetCanPrevMode(canHwChannel) == mode) && (Can_30_Mcan_GetCanLastState(canHwChannel) == kCan_30_McanRequested) ) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
        { /* repeat requested mode change without repeating reinit */
          ret = CanLL_30_Mcan_StopRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
        }
        else
        {
          ret = CanHL_30_Mcan_ReInit(CAN_30_MCAN_CHANNEL_CANPARA_FIRST ramCheck);
          if(ret == kCan_30_McanOk) /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          {
            ret = CanLL_30_Mcan_StopRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
          }
        }
        if(ret == kCan_30_McanOk) { /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          ApplCan_30_McanClockStop(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* offer the application to turn off the clocks (CAN, Host) */
        }
        CanHL_30_Mcan_CleanUpSendState(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
      break;

    case kCan_30_McanModeStopReinitFast:     /* distinguish for fast if applicable */
        /* #60 STOP FAST request */
        ret = CanLL_30_Mcan_StopRequest(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
        if(ret == kCan_30_McanOk) { /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          CanLL_30_Mcan_StopReinit(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
          ApplCan_30_McanClockStop(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* offer the application to turn off the clocks (CAN, Host) */
          CanHL_30_Mcan_CleanUpSendState(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
        }
      break;

    default:
      /* ret is kCan_30_McanFailed */
      break;
  }
  
  Can_30_Mcan_GetCanPrevMode(canHwChannel) = mode; /* SBSW_CAN_LL_112 */ 
  Can_30_Mcan_GetCanLastState(canHwChannel) = ret; /* SBSW_CAN_LL_112 */

  CAN_30_MCAN_DUMMY_STATEMENT(busOffRecovery);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return ret;
}  /* PRQA S 6030 */  /* MD_MSR_STCYC */
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_StopReinit
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_StopReinit
Relation_Context:
# from CanLL_ModeTransition() #
OneChOpt, HardwareLoopCheck, ChannelAmount
Relation:
OneChOpt
ChannelAmount, RamCheck
RxFullCANSupport, RxBasicCANSupport, MultipleBasicCanObjects, CanFdSupport
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
/* PRQA S 0303 QAC_Can_0303_StopReinit */ /* MD_Can_HwAccess */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_StopReinit(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 tmpECR; /* PRQA S 3203 */ /* MD_Can_3203_LL */

  /* #10 reset FullCAN flags */
#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS ) 
  Cn->NDATA[0] = kCan_ALL_ONE;   /* SBSW_CAN_LL_100 */   
  Cn->NDATA[1] = kCan_ALL_ONE;   /* SBSW_CAN_LL_100 */   
#endif

  /* CAN error logging is reset by read access to ECR[CEL] */
  /* #20 reset error counter */
  tmpECR = Cn->ECR; /* CAN error logging is reset by read access to ECR[CEL] */  /* PRQA S 3198,3199 */ /* MD_MSR_14.2 */
  CAN_30_MCAN_DUMMY_STATEMENT(tmpECR);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* CCCR[CCE] is automatically reset when CCCR[INIT] is reset */
  Cn->CCCR |= kCanCCCR_CCE;             /* SBSW_CAN_LL_100 */   

  /* #30 reset transmit requests */
  Can_30_Mcan_GetCanTXBRP(canHwChannel)   = 0;  /* SBSW_CAN_LL_112 */ 
  
  /* If there are any pending Tx requests. */
  if ((Cn->TXBRP)!=0UL) /* COV_CAN_PENDING_TX_REQUEST */
  {
    Cn->TXBCR = (vuint32)(Cn->TXBRP); /* SBSW_CAN_LL_100 */ /* Cancel pending tx requests */
  }

  /* #40 reset global PSR value */
#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
  Can_30_Mcan_GetPSRValue(canHwChannel) = 0; /* SBSW_CAN_LL_112 */
#endif
  
  /* #50 reset CAN FD bits */
#if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
  if(Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(channel)) != CAN_30_MCAN_NONE)
  {
    if(Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(channel)) == CAN_30_MCAN_FD_RXTX)
    { /* CAN_30_MCAN_FD_RXTX */
# if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
      Cn->CCCR |= (vuint32)(kCanCCCR_FDOE | kCanCCCR_BRSE);   /* SBSW_CAN_LL_100 */   /* FD operation, BRS enabled */
# else
      Cn->CCCR &= (vuint32)(~(kCanCCCR_CME_CAN20));           /* SBSW_CAN_LL_100 */   /* reset CME bits */
      Cn->CCCR |= kCanCCCR_CME_LONG_FAST;                     /* SBSW_CAN_LL_100 */   /* enable LONG and FAST */
# endif
    }
    else
    { /* CAN_FD_RXONLY */
# if ( CAN_MCAN_REVISION >= 0x0310UL ) /* COV_CAN_HW_SPECIFIC */
      Cn->CCCR &= (vuint32)(~(kCanCCCR_FDOE | kCanCCCR_BRSE)); /* SBSW_CAN_LL_100 */  /* reset FD bits */
      Cn->CCCR |= (vuint32)(kCanCCCR_FDOE);                    /* SBSW_CAN_LL_100 */  /* FD operation, BRS disabled */
# else
      Cn->CCCR &= (vuint32)(~(kCanCCCR_CME_CAN20));   /* SBSW_CAN_LL_100 */  /* reset CME bits */
      Cn->CCCR |= kCanCCCR_CME_LONG;                  /* SBSW_CAN_LL_100 */  /* enable LONG  */
# endif
    }
  }
  else
  { /* CAN_30_MCAN_NONE */
# if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
    Cn->CCCR &= (vuint32)(~(kCanCCCR_FDOE | kCanCCCR_BRSE));   /* SBSW_CAN_LL_100 */    /* No FD operation, BRS disabled */
# else
    Cn->CCCR &= (vuint32)(~(kCanCCCR_CME_CAN20));              /* SBSW_CAN_LL_100 */    /* enable NORMAL CAN */
# endif
  }
#else
# if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
    /* FD operation disabled */
    Cn->CCCR &= (vuint32)(~(kCanCCCR_FDOE | kCanCCCR_BRSE));   /* SBSW_CAN_LL_100 */    /* No FD operation, BRS disabled */
# else
    Cn->CCCR &= (vuint32)(~(kCanCCCR_CME_CAN20));              /* SBSW_CAN_LL_100 */    /* enable NORMAL CAN */
# endif
#endif

  /* #60 clear pending FIFO messages */
  CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
  while( (((Cn->RXF0S).B.FnFL) > 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopRxFifo) != CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    Cn->RXF0A = Cn->RXF0S.B.FnGI;   /* SBSW_CAN_LL_100 */   
  }
  CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
#if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
  while( (((Cn->RXF1S).B.FnFL) > 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopRxFifo) != CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    Cn->RXF1A = Cn->RXF1S.B.FnGI;   /* SBSW_CAN_LL_100 */   
  }
  CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
#endif

  /* #70 delete all pending interrupt requests */
  Cn->IR = kCanIR_CLEAR_ALL;   /* SBSW_CAN_LL_100 */   
}
/* PRQA  L:QAC_Can_0303_StopReinit */
/* CODE CATEGORY 4 END */



#if defined( C_30_MCAN_ENABLE_CAN_CAN_INTERRUPT_CONTROL )   /* COV_CAN_LOCK_ISR_BY_APPL */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_CanInterruptDisable
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_CanInterruptDisable
Relation_Context:
# from Can_DisableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
Relation:
IntLock
OneChOpt 
ChannelAmount, CanInterruptControl, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_CanInterruptDisable(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST tCan_30_McanLLCanIntOldPtr localInterruptOldFlagPtr)
{
  /* #10 Save old state and disable MCAN interrupts */
#  if defined(C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL)  /* COV_CAN_HW_SPECIFIC */
#   if defined(C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN)         /* COV_CAN_HW_SPECIFIC */
#    error "OS interrupt control is not supported with CAN_ISR_ALL_CHAN" 
#   endif  
  boolean  retval;
  (void)osIsInterruptSourceEnabled(Can_30_Mcan_GetIsrOsId(canHwChannel), &retval); /* SBSW_CAN_LL_121 */
  (void)osDisableInterruptSource(Can_30_Mcan_GetIsrOsId(canHwChannel));
  *(localInterruptOldFlagPtr) = (vuint32) retval; /* SBSW_CAN_LL_122 */
#  else
  *(localInterruptOldFlagPtr) = Cn->IE;   /* SBSW_CAN_HL16 */      /* PRQA S 0303 */ /* MD_Can_HwAccess */
  Cn->IE = 0;                             /* SBSW_CAN_LL_100 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  endif /* C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL */
} /* CanLL_30_Mcan_CanInterruptDisable */
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_CanInterruptRestore
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_CanInterruptRestore
Relation_Context:
# from Can_EnableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
Relation:
OneChOpt
ChannelAmount, CanInterruptControl, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling
IntLock
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_CanInterruptRestore(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST tCan_30_McanLLCanIntOld localInterruptOldFlag)
{
#  if defined(C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL)    /* COV_CAN_HW_SPECIFIC */
#   if defined(C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN)           /* COV_CAN_HW_SPECIFIC */
#    error "OS interrupt control is not supported with CAN_ISR_ALL_CHAN" 
#   endif 
  if( (vuint32)localInterruptOldFlag == TRUE ) /* COV_CAN_OS_INT_SOURCE */
  {
    (void)osEnableInterruptSource(Can_30_Mcan_GetIsrOsId(canHwChannel), kCan_30_McanFalse);
  }
#  else
  /* #10 restore previous state (before disabling interrupts) */
  Cn->IE = (localInterruptOldFlag);   /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  endif /* C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL */
} /* CanLL_30_Mcan_CanInterruptRestore */
/* CODE CATEGORY 1 END */
#endif /*  C_30_MCAN_ENABLE_CAN_CAN_INTERRUPT_CONTROL */






#if defined( C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM ) /* COV_CAN_HW_SPECIFIC */
/* **************************************************************************
| NAME:             Can_EccInit
| CALLED BY:        Can_Init()
| PRECONDITIONS:    MCAN clock must be available, Interrupts must be disabled
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      The internal SRAM features Error Correcting Code (ECC). 
|                   Because these ECC bits can contain random data after the device is turned on, 
|                   all SRAM locations must be initialized before being read by application code. 
|                   Initialization is done by executing 64-bit writes to the entire SRAM block. 
|                   (The value written does not matter at this point.)
************************************************************************** */
/*************************************************************************
 *  Can_EccInit
 *********************************************************************** */
/*
|<DataModelStart>| Can_EccInit
Relation_Context:
# from Can_Init #
Relation:
OneChOpt
ChannelAmount
RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
* Internal comment removed.
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) Can_EccInit(void)
{
  /*Local Variables*/
  vuint8 ret = kCan_30_McanOk;
  vuint16  ch, idx;
  vuint32  length;
  vuint32* dst;

  /* #120 initialize CAN Message RAM area for each channel */
  for(ch = 0; ch < kCan_30_McanNumberOfChannels; ch++)
  {
    dst = (vuint32*) Can_30_Mcan_GetStartAdrOfShmAdr(ch);   /* PRQA S 0306 */ /* MD_Can_0306_HWaccess_LL */
    length = (Can_30_Mcan_GetStopAdrOfShmAdr(ch) - Can_30_Mcan_GetStartAdrOfShmAdr(ch)) >> 2;  /* SMI-64561 */ 
    for(idx = 0; idx < length; idx++)
    {
      dst[idx] = 0x00000000UL; /* SBSW_CAN_LL_108 */ 
    }
  }
  return (ret);
}
/* CODE CATEGORY 1 END */
#endif /* C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM */

#if defined( C_30_MCAN_ENABLE_TX_POLLING )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_if_TxIsObjConfPending
****************************************************************************/
/*
|<DataModelStart>| CanLL_if_TxIsObjConfPending
Relation_Context:
# from CanLL_TxProcessPendings #
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint32, STATIC_CODE) CanLL_30_Mcan_if_TxIsObjConfPending( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST vuint32 txBuffer ) 
{
  vuint32 ret;

  ret = kCan_30_McanOk; /* assume at least one Tx object confirmation is pending */

  /* #10 check for pending tx requests */
  if( ((Can_30_Mcan_GetCanTXBRP(canHwChannel) & txBuffer) != 0u) && ((Cn->TXBTO & txBuffer) != 0u) ) /* PRQA S 3673,0303 */ /* MD_Can_NoneConstParameterPointer,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
  { /* #20 confirmation shows up */
  }
  else
  { /* #30 no request pending or outstanding confirmation */
    ret = kCan_30_McanFailed;
  }
  return(ret);
}/* CanLL_30_Mcan_if_TxIsObjConfPending */
/* CODE CATEGORY 4 END */
#endif


#if ( CAN_BOSCH_ERRATUM_010 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanBoschErratum_010
****************************************************************************/
/*
|<DataModelStart>| CanBoschErratum_010
Relation_Context:
# from CanLL_30_Mcan_SetAllRegister #
Relation:
OneChOpt
ChannelAmount, HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanBoschErratum_010( CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY )  /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* When CCCR.CCE is set while a Tx scan is in progress, the Tx Handler FSM stops. 
     After CCCR.INIT and CCCR.CCE are reset, the Tx Handler FSM does not execute transmission requests.
     Workaround:
     1) Cancel all pending transmission requests by writing 0hFFFF FFFF to register TXBCR
     2) Issue a clock stop request by setting bit CCCR.CSR
     3) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
     4) First reset CCCR.CSR
     5) Then reset CCCR.INIT
     6) Wait until CCCR.INIT is read as zero
     7) Issue a second clock stop request by setting bit CCCR.CSR
     8) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
     9) Set CCCR.CCE and reset CCCR.CSR */

  if((Cn->PSR & kCanPSR_ACT_TX) == kCanPSR_ACT_TX) /* #10 check operation */
  { /* operating as transmitter */
    Cn->TXBCR = kCan_ALL_ONE;   /* SBSW_CAN_LL_100 */    /* #20 cancel pending tx requests */
    Cn->CCCR |= kCanCCCR_CSR;   /* SBSW_CAN_LL_100 */    /* #30 issue clock stop request   */

    /* #40 await clock stop acknowledge */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_CSA) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopClockStop) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
    { /* Assure that the previous value has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */

    /* #50 return to normal mode */
    Cn->CCCR &= (vuint32)~(kCanCCCR_CSR);   /* SBSW_CAN_LL_100 */
    Cn->CCCR &= (vuint32)~(kCanCCCR_INIT);   /* SBSW_CAN_LL_100 */

    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */
    while( ((Cn->CCCR & kCanCCCR_INIT) != 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
    { /* Assure that the previous value written to INIT has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  

    /* #60 issue 2'nd clock stop request */
    Cn->CCCR |= kCanCCCR_CSR;   /* SBSW_CAN_LL_100 */   
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_CSA) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopClockStop) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
    { /* Assure that the previous value written to CSR has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */  

    /* #70 now CCE can be set */
    Cn->CCCR |= kCanCCCR_CCE;   /* SBSW_CAN_LL_100 */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
    { /* Assure that the previous value written to CCE has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  

    /* #80 reset clock stop request */
    Cn->CCCR &= (vuint32)(~kCanCCCR_CSR);   /* SBSW_CAN_LL_100 */   
  }
  else
  { /* #90 CCE can be set immediately */
    Cn->CCCR |= kCanCCCR_CCE;   /* SBSW_CAN_LL_100 */   
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
    { /* Assure that the previous value has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
  }
} /* CanBoschErratum_010 */
/* CODE CATEGORY 4 END */ 
#endif
  





/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanErrorHandlingBusOff
****************************************************************************/
/*
|<DataModelStart>| CanErrorHandlingBusOff
Relation_Context:
# from CanLL_BusOffOccured #
Relation:
OneChOpt
ChannelAmount, DynamicMcanRevision
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
# CAN_BOSCH_ERRATUM_007 #
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanErrorHandlingBusOff(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 ret;

  /* The Bus_Off recovery sequence cannot be shortened by setting or resetting CCCR[INIT.] 
     If the device goes Bus_Off, it will set CCCR[INIT] of its own accord, stopping all bus activities. 
     Once CCCR[INIT] has been cleared by the CPU, the device will then wait for 129 occurrences of Bus Idle 
     (129 x 11 consecutive recessive bits) before resuming normal operation. 
     At the end of the Bus_Off recovery sequence, the Error Management Counters will be reset. 
     During the waiting time after the resetting of CCCR[INIT], each time a sequence of 11 recessive bits has been monitored, 
     a Bit 0 Error code is written to PSR[LEC], enabling the CPU to readily check up whether the CAN bus is stuck at dominant or continuously disturbed 
     and to monitor the Bus_Off recovery sequence. ECR[REC] is used to count these sequences. */
  /* Uncorrected Message RAM bit error detected: BEU sets CCCR[INIT] to '1' to avoid transmission of corrupted data.
     Controlled by Message RAM bit error input signal generated by an optional external ECC logic attached to the Message RAM. */
  /* #10 check error status */
#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
  /* Avoid read access to PSR register when security event reporting is enabled */
  if( (((Cn->IR & kCanIR_BO)  != 0UL) && ((Can_30_Mcan_GetPSRValue(canHwChannel) & kCanPSR_BO) != 0UL)) /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
  if( (((Cn->IR & kCanIR_BO)  != 0UL) && ((Cn->PSR & kCanPSR_BO) != 0UL)) /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
#if defined(C_30_MCAN_ENABLE_PARITY_INTERRUPT) /* COV_CAN_HW_SPECIFIC */
    || ((Cn->IR & kCanIR_BEU) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
    ) /* COV_CAN_HW_SPECIFIC */
  { 
    /* #20 check for BusOff (BusOff state, Bit Error Uncorrected or Message RAM failure detected) */
    { /* BusOff status changed to BusOff OR Bit Error Uncorrected appeared */
      if(Can_30_Mcan_GetCanBusOffNotification(canHwChannel) == kCanBusoff) /* COV_CAN_BUSOFFNOTIFICATION */
      { /* already detected */
      }
      else
      { 
        Can_30_Mcan_GetCanBusOffNotification(canHwChannel) = kCanBusoff;  /* SBSW_CAN_LL_112 */ 
      }
    }
    /* #40 reset flags */
#if defined(C_30_MCAN_ENABLE_PARITY_INTERRUPT) /* COV_CAN_HW_SPECIFIC */
    Cn->IR = (vuint32)(kCanIR_BO | kCanIR_BEU);   /* SBSW_CAN_LL_100 */    /* reset flags */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
    Cn->IR = (vuint32)(kCanIR_BO);                /* SBSW_CAN_LL_100 */    /* reset flags */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
    ret = kCan_30_McanOk;
  }
  else
  {
    ret = kCan_30_McanFailed;
  }

  if(((Cn->IR & kCanIR_MRAF) != 0UL)) /* COV_CAN_MCAN_NOT_SUPPORTED */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  { /* Message RAM annoyance */
    /* #30 check for Restricted Mode, if so try to get back to normal mode */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON) 
        Can_30_Mcan_CallDetReportError(CAN_30_MCAN_CTRBUSOFF_ID, CAN_30_MCAN_E_MRAF); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#endif
    if((Cn->CCCR & kCanCCCR_ASM) != 0UL)  /* COV_CAN_MCAN_NOT_SUPPORTED */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    { /* Regained in Restricted Mode, Tx Handler read problem assumed.
       In Restricted Operation Mode the node is able to receive data and remote frames and to give
       acknowledge to valid frames, but it does not send any frames (data, remote, active error or overload). 
       In case of an error or overload condition, it does not send dominant bits but waits for bus idle to resynchronize itself. */
#if ( CAN_BOSCH_ERRATUM_007 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
       /* Effects:
           With the next transmission after leaving Restricted Operation Mode (reset CCCR.ASM), a frame with an 
           unexpected identifier and control field is transmitted which accidentally might be accepted by another receiver.
           Workaround:
           To recover from Restricted Operation Mode proceed as follows:
           1) Cancel all pending transmission requests by writing 0hFFFF FFFF to register TXBCR
           2) Issue a clock stop request by setting bit CCCR.CSR
           3) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
           4) First reset CCCR.CSR
           5) Then reset CCCR.INIT
           6) Wait until CCCR.INIT is read as zero
           7) Issue a second clock stop request by setting bit CCCR.CSR
           8) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
           9) Set CCCR.CCE, reset CCCR.CSR, and reset CCCR.ASM
           10) Restart M_CAN by writing CCCR.INIT = '0'
           11) Configure the CAN operation mode by writing to CCCR.CMR
           12) Request the transmissions cancelled by step one */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      if(CanGetMcanRevision(channel) < 0x310UL) /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
      {
        Cn->TXBCR = kCan_ALL_ONE;          /* SBSW_CAN_LL_100 */  /* cancel all */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        Cn->CCCR |= (vuint32)kCanCCCR_CSR; /* SBSW_CAN_LL_100 */  /* clock stop request */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        /*  After CSR first INIT and then CSA will be set after all pending transfer requests have been completed and the CAN bus reached idle. */
        CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */ 
        while( ((Cn->CCCR & kCanCCCR_CSA) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopClockStop) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
        { /* Assure that CSA and thus also INIT has been accepted */ }
        CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopClockStop);    /* SBSW_CAN_LL_101 */

        Cn->CCCR &= (vuint32)~(kCanCCCR_CSR);  /* SBSW_CAN_LL_100 */  /* PRQA S 0303 */ /* MD_Can_HwAccess */
        Cn->CCCR &= (vuint32)~(kCanCCCR_INIT); /* SBSW_CAN_LL_100 */  /* PRQA S 0303 */ /* MD_Can_HwAccess */

        CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit);  /* SBSW_CAN_LL_101 */  
        while( ((Cn->CCCR & kCanCCCR_INIT) != 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
        { /* Assure that INIT has been accepted */ }
        CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit);    /* SBSW_CAN_LL_101 */  
        Cn->CCCR |= (vuint32)kCanCCCR_CSR;      /* SBSW_CAN_LL_100 */       /* 2'nd clock stop request */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */  
        while( ((Cn->CCCR & kCanCCCR_CSA) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopClockStop) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */
        { /* Assure that CSA and thus also INIT has been accepted */ }
        CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopClockStop);   /* SBSW_CAN_LL_101 */  
        Cn->CCCR |= (vuint32)kCanCCCR_CCE;      /* SBSW_CAN_LL_100 */   /* configuration change enabled */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        Cn->CCCR &= (vuint32)(~kCanCCCR_CSR);   /* SBSW_CAN_LL_100 */   /* reset CSR  */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        Cn->CCCR &= (vuint32)(~kCanCCCR_ASM);   /* SBSW_CAN_LL_100 */   /* now leave restricted mode  */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
        /* Step 10) and 11) is accomplished during start transition, 
           Step 12) has to be done by the application! */
      }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
      else
      {
        Cn->CCCR &= ( (~kCanCCCR_ASM) );   /* SBSW_CAN_LL_100 */    /* leave Restricted Mode */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      }
# endif
#else /* CAN_BOSCH_ERRATUM_007 */ 
      Cn->CCCR &= ( (~kCanCCCR_ASM) );     /* SBSW_CAN_LL_100 */    /* leave Restricted Mode */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
      ret = kCan_30_McanOk;
      }
    else
    { /* Rx Handler filtering or access to Message RAM access problem assumed */
      /* At least one message was discarded (kCanIR_UMD for MCAN < 3.0.0) */
      /* Do not return a positive busoff notification for only MRAF RX Issue */
    }
    Cn->IR = (vuint32)(kCanIR_MRAF); /* SBSW_CAN_LL_100 */    /* reset flags */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
  return(ret);
} /* CanErrorHandlingBusOff */
/* CODE CATEGORY 4 END */


/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetAllFilter
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_SetAllFilter
Relation_Context:
# from CanLL_InitBeginSetRegisters #
Relation:
OneChOpt
ChannelAmount, HardwareLoopCheck, IDType, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_SetAllFilter(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
#if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  vuint8 result = kCan_30_McanOk;
#endif
  /* 10 set std id filter */
#if defined( C_30_MCAN_ENABLE_STD_ID ) && (kCanNumberOfStandardFilter > 0)  /* at least one std filter is available */
  initPara->pFS = &Can_30_Mcan_GetCanSIDFE(Can_30_Mcan_GetCanSIDFEStartIndex(canHwChannel));  /* SBSW_CAN_LL_109 */ 
  for(initPara->tmpVal = 0; initPara->tmpVal < (Can_30_Mcan_GetCanSIDFC_LSSOfCanSIDFC(canHwChannel)); (initPara->tmpVal)++) /* SBSW_CAN_LL_109 */  /* SBSW_CAN_LL_109 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* copy std filter elements to SHM */
# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
    if( ((vuint32)&ShmSIDF(initPara->stdFeCount).S0 < (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || ((vuint32)&ShmSIDF(initPara->stdFeCount).S0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */  /* COV_CAN_GENDATA_FAILURE */
    { /* SilentBSW check */
      Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      result = kCan_30_McanFailed;
    }
    else
# endif
    {
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(ShmSIDF(initPara->stdFeCount).S0), (vuint32)(initPara->pFS[initPara->tmpVal]), kCanRegCheckMaskSMIDFE_S0, initPara);   /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_103 */
      (initPara->stdFeCount)++;  /* SBSW_CAN_LL_109 */ 
    }
  }
#endif  /* STD_FILTER */

  /* 20 set ext id filter */
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID) && (kCanNumberOfExtendedFilter > 0)
  for(initPara->tmpVal = 0; initPara->tmpVal < (Can_30_Mcan_GetCanXIDFC_LSEOfCanXIDFC(canHwChannel)); (initPara->tmpVal)++) /* SBSW_CAN_LL_109 */  /* SBSW_CAN_LL_109 */ 
  { /* copy ext filter elements to SHM */
# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
    if( ((vuint32)&ShmXIDF(initPara->extFeCount).F0 < (vuint32)Can_30_Mcan_GetStartAdrOfShmAdr(canHwChannel)) || ((vuint32)&ShmXIDF(initPara->extFeCount).F0 >= (vuint32)Can_30_Mcan_GetStopAdrOfShmAdr(canHwChannel) ) ) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* CM_CAN_LL_103 */ /* COV_CAN_GENDATA_FAILURE */
    { /* SilentBSW check */
      Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);
      result = kCan_30_McanFailed;
    }
    else
# endif
    {
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(ShmXIDF(initPara->extFeCount).F0), (vuint32)(Can_30_Mcan_GetCanXIDFEEIDFE_0OfCanXIDFE(Can_30_Mcan_GetCanXIDFEStartIndex(canHwChannel) + initPara->tmpVal)), kCanRegCheckMaskEMIDFE_F0, initPara);  /* SBSW_CAN_LL_103 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(ShmXIDF(initPara->extFeCount).F1), (vuint32)(Can_30_Mcan_GetCanXIDFEEIDFE_1OfCanXIDFE(Can_30_Mcan_GetCanXIDFEStartIndex(canHwChannel) + initPara->tmpVal)), kCanRegCheckMaskEMIDFE_F1, initPara);  /* SBSW_CAN_LL_103 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      (initPara->extFeCount)++; /* SBSW_CAN_LL_109 */ 
    }
  }
#endif /* EXT_FILTER */


#if (!defined( C_30_MCAN_ENABLE_STD_ID ) || (kCanNumberOfStandardFilter <= 0u) ) && (!defined(C_30_MCAN_ENABLE_EXTENDED_ID) || (kCanNumberOfExtendedFilter <= 0u))
  CAN_30_MCAN_DUMMY_STATEMENT(initPara);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT;  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  return(result);
#else
  return(kCan_30_McanOk);
#endif
} /* CanLL_30_Mcan_SetAllFilter */
/* CODE CATEGORY 4 END */
 

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetAllRegister
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_SetAllRegister
Relation_Context:
# from CanLL_InitBeginSetRegisters #
Relation:
OneChOpt
ChannelAmount, IDType, CanFdSupport, RxFullCANSupport, RxBasicCANSupport, MultipleBasicCanObjects
ChannelAmount, HardwareLoopCheck, RxPolling, TxPolling, IndividualPolling, StatusPolling
CanSecurityEventReporting
Parameter_PreCompile:
Parameter_Data:
Constrain:
# CAN_BOSCH_ERRATUM_008 #
# CAN_BOSCH_ERRATUM_010 #
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_SetAllRegister(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara)
{
  vuint32 LocalRegValue;
  initPara->tmpVal = 0;     /* SBSW_CAN_LL_109 */    /* PRQA S 2982 */ /* MD_Can_2982_LL */ 
#if defined( C_30_MCAN_ENABLE_STD_ID )
  initPara->stdFeCount = 0; /* SBSW_CAN_LL_109 */    /* PRQA S 2982 */ /* MD_Can_2982_LL */
#endif
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
  initPara->extFeCount = 0; /* SBSW_CAN_LL_109 */    /* PRQA S 2982 */ /* MD_Can_2982_LL */
#endif
  
#if defined(C_30_MCAN_ENABLE_STD_ID) 
  CAN_30_MCAN_DUMMY_STATEMENT(initPara->stdFeCount);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* SBSW_CAN_LL_109 */ 
#endif
#if defined(C_30_MCAN_ENABLE_EXTENDED_ID) 
  CAN_30_MCAN_DUMMY_STATEMENT(initPara->extFeCount);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* SBSW_CAN_LL_109 */ 
#endif

  /* #10 assure configuration enable mode */
  /* Initialization is started by setting CCCR[INIT]. This does not change any configuration register.
     M_CAN configuration register access is only enabled when CCCR[INIT] and CCCR[CCE] are set (protected write).
     While CCCR[INIT]==1: 
     - message transfer on CAN bus is stopped, 
     - CAN bus Tx output is recessive. */
  
#if ( CAN_BOSCH_ERRATUM_008 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
  /* When CCCR.INIT is set while the M_CAN is receiving a frame, the next received frame         
     after resetting CCCR.INIT will cause IR.MRAF to be set.
     Effects:
     IR.MRAF is set when the first frame after resetting CCCR.INIT is received although that
     frame is received correctly.
     Workaround:
     1) Issue a clock stop request by setting bit CCCR.CSR
        When clock stop is requested, first CCCR.INIT and then CCCR.CSA will be set 
        after all pending transfer requests have been completed and the CAN bus reached idle.
     2) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
     3) Before resetting CCCR.INIT first reset CCCR.CSR. */
  /*  When CSR is requested, first INIT and then CSA will be set after all pending transfer 
      requests have been completed and the CAN bus reached idle. */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  if(CanGetMcanRevision(channel) < 0x310UL) /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
  {
    Cn->TXBCR = kCan_ALL_ONE;    /* SBSW_CAN_LL_100 */    /* cancel pending tx requests */
     /* Clear Previous CCCR configuration except INIT and CSR bits */
    Cn->CCCR &= (kCanCCCR_CSR | kCanCCCR_INIT);  /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */

    Cn->CCCR |= kCanCCCR_CSR;   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */
    while( ((Cn->CCCR & kCanCCCR_CSA) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopClockStop) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
    { /* Assure that CSA/INIT has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopClockStop); /* SBSW_CAN_LL_101 */  
  }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  else
  {
    Cn->CCCR  |= kCanCCCR_INIT;  /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_INIT) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
    { /* Assure that INIT has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
  }
# endif
#else
  Cn->CCCR = kCanCCCR_INIT;               /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
  while( ((Cn->CCCR & kCanCCCR_INIT) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
  { /* Assure that INIT has been accepted. */ }
  CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit);  /* SBSW_CAN_LL_101 */  
#endif      
  
#if ( CAN_BOSCH_ERRATUM_010 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  if(CanGetMcanRevision(channel) < 0x310UL) /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
  {
    CanBoschErratum_010(CAN_30_MCAN_CHANNEL_CANPARA_ONLY);
  }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  else
  {
    Cn->CCCR = (vuint32)(kCanCCCR_INIT | kCanCCCR_CCE);   /* set all zero */  /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */
    while( ((Cn->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
    { /* Assure that the previous value has been accepted. */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
  }
# endif
#else
  Cn->CCCR = (vuint32)(kCanCCCR_INIT | kCanCCCR_CCE);   /* set all zero */  /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
  while( ((Cn->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
  { /* Assure that the previous value has been accepted. */ }
  CanLL_30_Mcan_ApplCanTimerEnd( kCan_30_McanLoopInit ); /* SBSW_CAN_LL_101 */  
#endif
  
  /* #20 support additional features via user config file */
  LocalRegValue = Cn->CCCR; /* PRQA S 0303 */ /* MD_Can_HwAccess */
  

  /* #30 support CAN-FD */
#if ( CAN_MCAN_REVISION >= 0x0315UL ) /* COV_CAN_HW_SPECIFIC */
# if ( Can_30_Mcan_GetCAN_FD_NISO() == STD_ON)    /* COV_CAN_HW_SPECIFIC */
    LocalRegValue |= (vuint32) kCanCCCR_NISO;
# else
    LocalRegValue &= (vuint32)~kCanCCCR_NISO;
# endif
#endif
  
#if defined( C_30_MCAN_ENABLE_CAN_FD_USED )
  if (Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(channel)) != CAN_30_MCAN_NONE)
  {
# if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
      LocalRegValue |= (vuint32)(  kCanCCCR_FDOE | kCanCCCR_BRSE);    /* FD operation, BRS enabled */
# else
      LocalRegValue |= kCanCCCR_CME_LONG_FAST;                       /* enable LONG and FAST */
# endif
  }
  else
  { 
# if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
    /* FD operation disabled */
    LocalRegValue &= (vuint32)(~(kCanCCCR_FDOE | kCanCCCR_BRSE));  /* reset FD bits */
# else
    LocalRegValue &= (vuint32)(~(kCanCCCR_CME_CAN20));            /* enable NORMAL CAN */
# endif
  }
#else
# if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
  /* FD operation disabled */
  LocalRegValue &= (vuint32)(~(kCanCCCR_FDOE | kCanCCCR_BRSE));    /* reset FD bits */
# else
  LocalRegValue &= (vuint32)(~(kCanCCCR_CME_CAN20));               /* enable NORMAL CAN */
# endif
#endif
  /* Write the accumulated CCCR Value to the CCCR Register*/
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->CCCR), (vuint32)LocalRegValue, kCan_ALL_ONE, initPara);  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ 

  /* #40 support Rx FullCAN */
  /* Delete all pending interrupt requests */
  Cn->IR       = kCanIR_CLEAR_ALL; /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS ) 
  Cn->NDATA[0] = kCan_ALL_ONE;     /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  Cn->NDATA[1] = kCan_ALL_ONE;     /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
  
  /* Start value of the Message RAM Watchdog Counter. 
     The RAM Watchdog Counter is clocked by the Host clock. 
     With the reset value of '0' the counter is disabled. */
  /* Only with ( CAN_BOSCH_ERRATUM_013 == STD_ON )
     This Errata is not considered by the CAN driver (see "Note" below).
     When the M_CAN wants to store a received frame and the Message RAM does not respond in time, 
     this message cannot be stored completely and is discarded. Interrupt flag IR.MRAF is set. 
     It may happen that the next received message is stored incomplete, then the respective 
     Rx Buffer holds inconsistent data.
     Workaround:
     Configure the RAM Watchdog to the maximum expected Message RAM access delay. 
     In case the Watchdog Interrupt IR.WDI is set discard the frame received after IR.MRAF has been activated.
     Note:
     When the M_CAN has been integrated correctly, this can only occur in case of a Message RAM/Arbiter problem.
     if(IR.MRAF .AND. IR.WDI) then just Acknowledge and proceed for further messages. */
  /* Start value of the Message RAM Watchdog Counter. With the reset value of '0' the counter is disabled. 
     A Message RAM access via the M_CAN's Master Interface starts the Watchdog Counter with RWD.WDC. 
     The counter is reloaded with RWD.WDC when the Message RAM signals successful completion. 
     In case there is no response from the Message RAM until the counter has counted down to zero, 
     the counter stops and IR.WDI is set. 
     The RAM Watchdog Counter is clocked by the Host clock. */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RWD), (vuint32)kCan_RWD, kCanRegCheckMaskRWD, initPara);  /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  
#if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
# if defined( C_30_MCAN_ENABLE_CAN_FD_USED )
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->FBTP, Can_30_Mcan_GetCanFBTP(initPara->initObject), kCan_ALL_ONE, initPara );  /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */   /* SBSW_CAN_HL36 */ /* Fast Bit Timing and Prescaler Register (FBTP) */ 
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->TDCR, Can_30_Mcan_GetCanTDCR(initPara->initObject), kCan_ALL_ONE, initPara );  /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */   /* SBSW_CAN_HL36 */ /* Transmitter Delay Compensation Register (TDCR.[TDCO|TDCF]) */
# else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->FBTP, kCanFBTP_TDC_Disable, kCan_ALL_ONE, initPara );                         /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */   /* SBSW_CAN_HL36 */ /* Transceiver Delay Compensation disabled */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->TDCR, kCanTDCR_TDC_Disable, kCan_ALL_ONE, initPara );                         /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */   /* SBSW_CAN_HL36 */ /* Transceiver Delay Compensation disabled */
# endif
#else  /* MCAN Core Release < 0x310UL */
   
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  if(CanGetMcanRevision(channel) < 0x310UL) /* For McanRevision 300 */ /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
  {
# if defined( C_30_MCAN_ENABLE_CAN_FD_USED )
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->FBTP, Can_30_Mcan_GetCanFBTP(initPara->initObject),kCan_ALL_ONE, initPara );  /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_HL36 */ /* Fast Bit Timing and Prescaler Register (FBTP) */
# else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->FBTP, kCanFBTP_TDC_Disable, kCan_ALL_ONE, initPara );                        /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_HL36 */ /* Transceiver Delay Compensation disabled */
#  endif 
  }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  else /* For McanRevision >300 */
  {
#  if defined( C_30_MCAN_ENABLE_CAN_FD_USED )
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Cn->FBTP,(kCanTDCR_FBTP_TDCO_Mask_310 & Can_30_Mcan_GetCanFBTP(initPara->initObject)),kCan_ALL_ONE, initPara );                                 /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_LL_100 */ /* SBSW_CAN_HL36 */ /* Fast Bit Timing and Prescaler Register (FBTP) */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Cn->res2[0],((kCanTDCR_FBTP_TDCO_300 & Can_30_Mcan_GetCanFBTP(initPara->initObject))>>kCanFBTP_to_TDCR_bit_offset_r),kCan_ALL_ONE, initPara );  /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_LL_100 */ /* SBSW_CAN_HL36 */ /* Transceiver Delay Compensation disabled, TDCR Register, Bugfix, TDCF not awailabe when configured for rev 3.0 */
#  else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Cn->res2[0],kCanTDCR_TDC_Disable,kCan_ALL_ONE, initPara );                                                                                     /* PRQA S 0303, 2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_LL_100 */ /* SBSW_CAN_HL36 */ /* Transceiver Delay Compensation disabled, TDCR Register, Bugfix */  
#  endif 
  }
# endif 
#endif  /* CAN_MCAN_REVISION >= 0x310UL */
  
  /* Bit Timing and Prescaler Register (BTP) */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &Cn->BTP,Can_30_Mcan_GetCanBTP(initPara->initObject),kCan_ALL_ONE, initPara ); /* PRQA S 0303,2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_HL36 */

  /* TSCC-Timestamp Counter Configuration Register */
#if defined ( C_30_MCAN_ENABLE_CAN_FD_USED ) && (kCan_TSCC_TSS > 0)
#  error ">>> Note: With CAN FD an external counter is required for timestamp generation (TSCC.TSS = "10") <<<"
#endif
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TSCC), (vuint32)(kCan_TSCC_TCP|kCan_TSCC_TSS), kCanRegCheckMaskTSCC, initPara); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ /* '0' = keep the counter quiet - otherwise use (kCan_TSCC_TCP|kCan_TSCC_TSS) */
  /* TSCV-Timestamp Counter Value Register 
     With TSCC[TSS] = '01' the Counter is incremented. The counter value is captured on start of frame (both Rx and Tx).
     A wrap around sets interrupt flag IR[TSW].
     Write access resets the counter to zero. */
  Cn->TSCV = 0x00000000UL;   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  
  /* TOCC-Timeout Counter Configuration Register */
  /* Note: If CAN FD BRS feature is used then the timeout counter is clocked differently in arbitration and data field. */
#if ( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  if(CanGetMcanRevision(channel) <= 0x310UL) /* PRQA S 2842  */ /* MD_Can_2842_DynamicRevision_LL */
# endif
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TOCC), (vuint32)( (vuint32)(kCan_TOCC_TOP<<16) | kCan_TOCC_TOS | kCan_TOCC_ETOC ), kCanRegCheckMaskTOCC, initPara); /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
# if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
  else
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TOCC), (vuint32)(0UL), kCanRegCheckMaskTOCC, initPara); /* '0' = keep the counter quiet */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
# endif
#else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TOCC), (vuint32)(0UL), kCanRegCheckMaskTOCC, initPara);  /* SBSW_CAN_LL_100 */     /* '0' = keep the counter quiet */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
  /* TOP[15:0]  Timeout Period - Start value of the Timeout Counter (down-counter).
     TOS[29:30] Timeout Select - When operating in Continuous mode, a write to TOCV presets the counter to TOCC[TOP] and continues down-counting. 
                                 00=Continuous operation, 01/10/11=controlled by Tx Event FIFO/by Rx FIFO 0/by Rx FIFO 1
     ETOC[31]   '1' = Enable Timeout Counter */
  /* TOCV-Timeout Counter Value Register
     The Timeout Counter is decremented in multiples of CAN bit times depending on the configuration of TSCC.TCP. 
     When decremented to zero, interrupt flag IR.TOO is set and the Timeout Counter is stopped. 
     Start and reset/restart conditions are configured via TOCC.TOS. */
  Cn->TOCV = 0x00000000UL;   /* SBSW_CAN_LL_100 */   /* PRQA S 0303 */ /* MD_Can_HwAccess */ 
  
  /* The counters of the Error Management Logic EML are unchanged. */
  initPara->tmpVal = Cn->ECR; /* CAN error logging is reset by read access to ECR[CEL] */  /* PRQA S 3198,3199,0303 */ /* MD_MSR_14.2,MD_MSR_14.2,MD_Can_HwAccess */ /* SBSW_CAN_LL_109 */ 
  CAN_30_MCAN_DUMMY_STATEMENT(initPara->tmpVal);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */  /* SBSW_CAN_LL_109 */ 
  /* Global settings for Message ID filtering. 
     The GFC controls the filter path for standard and extended messages */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Cn->GFC,Can_30_Mcan_GetCanGFC(canHwChannel), kCan_ALL_ONE, initPara );   /* PRQA S 0303,2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_HL36 */ /* accept/reject non matching and remote (Std/Ext) frames */

  /* Acceptance filtering of ext. frames the "Ext-ID AND Mask (XIDAM)" is ANDed with the received Message ID */
  /* There are two possibilities when range filtering is used together with extended frames:
     EFT = '00': The ID of received frames is ANDed with XIDAM before the range filter is applied
     EFT = '11': XIDAM is not used for range filtering.
     Intended for masking of 29-bit IDs in SAE J1939. With the reset value of all bits set to one the mask is not active. */

  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Cn->XIDAM,(Can_30_Mcan_GetCanXIDAM(canHwChannel)), kCan_ALL_ONE, initPara );  /* PRQA S 0303,2986 */ /* MD_Can_HwAccess,MD_Can_ConstValue */  /* SBSW_CAN_HL36 */

  /* Rx Buffer Start Address (RBSA) configures the start address of the Rx Buffers section in the Message RAM */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXBC), (vuint32)Can_30_Mcan_GetCanRXBC(canHwChannel), kCanRegCheckMaskRXBC, initPara);   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */  /* Rx Buffer Start Address (RBSA) configures the start address of the Rx Buffers section in the Message RAM */
#if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
  /* Rx Buffer/FIFO Element Size Configuration (RXESC): number of data bytes for an Rx element, sizes >8 bytes are for CAN FD only.
     RBDS: Rx Buffer Data Field Size = 8,12,16,20,24,32,48,64 byte
     F1DS: Rx FIFO 1 Data Field Size = 8,12,16,20,24,32,48,64 byte
     F0DS: Rx FIFO 0 Data Field Size = 8,12,16,20,24,32,48,64 byte
     Note: In case the data field size of an accepted CAN frame exceeds the data field size configured for the matching Rx element, 
           only the number of bytes as configured by RXESC are stored. The rest of the frame data field is ignored. */
  LocalRegValue = (vuint32)( (((vuint32)Can_30_Mcan_GetRBDSOfShmElementSize(canHwChannel))<<8) | (((vuint32)Can_30_Mcan_GetF1DSOfShmElementSize(canHwChannel))<<4) | ((vuint32)Can_30_Mcan_GetF0DSOfShmElementSize(canHwChannel)) );
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXESC.R), (vuint32)LocalRegValue, kCanRegCheckMaskRXESC, initPara);    /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXESC.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXESC, initPara);    /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* Reset to default value */
#endif

  /* #60 support (Multiple) BasicCAN */
#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
  /* Rx FIFO 0 Configuration (RXF0C) */
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF0C.R), (vuint32)(Can_30_Mcan_GetCanRXF0C(canHwChannel)), kCanRegCheckMaskRXF0C, initPara);    /* SBSW_CAN_LL_100 */  /* PRQA S 0303 */ /* MD_Can_HwAccess */  /* Using default value kCanRXFnOM_BLOCK */
  }
  else
  { 
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF0C.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXF0C, initPara);   /* SBSW_CAN_LL_100 */   /* PRQA S 0303,2880 */ /* MD_Can_HwAccess,MD_Can_ConstValue */
  }
  /* RXF0S-Rx FIFO 0 Status Register (reset with CCCR.INIT) */
  /* RXF0A-Rx FIFO 0 Acknowledge Register (reset with CCCR.INIT)
     After reading a message (or a sequence of messages) the buffer index of the last element read has to be written to F0AI. 
     This sets the Get Index to F0AI + 1 and updates the Fill Level */
  
# if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  /* Rx FIFO 1 Configuration (RXF1C) */
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 1u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF1C.R), (vuint32)(Can_30_Mcan_GetCanRXF1C(canHwChannel)), kCanRegCheckMaskRXF1C, initPara); /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* Using default value kCanRXFnOM_BLOCK */
  }
  else
  { 
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF1C.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXF1C, initPara);   /* SBSW_CAN_LL_100 */ /* PRQA S 0303, 2880 */ /* MD_Can_HwAccess, MD_MSR_Unreachable */
  }
# else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF1C.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXF1C, initPara);    /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* Fifo 1 not supported */
# endif
  /* RXF1S-Rx FIFO 1 Status Register */
  /* RXF1A-Rx FIFO 1 Acknowledge Register 
     After reading a message (or a sequence of messages) the buffer index of the last element read has to be written to F0AI. 
     This sets the Get Index to F0AI + 1 and updates the Fill Level */
#else /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF0C.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXF0C, initPara);    /* SBSW_CAN_LL_100 */   /* Fifo 0 not supported */  /* PRQA S 0303 */ /* MD_Can_HwAccess */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->RXF1C.R), (vuint32)(0x00000000UL), kCanRegCheckMaskRXF1C, initPara);    /* SBSW_CAN_LL_100 */   /* Fifo 1 not supported */  /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */
  
  /* Tx Buffer Configuration (TXBC): */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXBC), (vuint32)(Can_30_Mcan_GetCanTXBC(canHwChannel)), kCanRegCheckMaskTXBC, initPara);   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  /* #70 support Tx side */

#if defined( C_30_MCAN_ENABLE_CAN_FD_FULL )
  /* Tx Buffer Element Size Configuration (TXESC): number of data bytes for a Tx Buffer element, sizes >8 bytes are for CAN FD only. */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXESC), (vuint32)(Can_30_Mcan_GetTBDSOfShmElementSize(canHwChannel)), kCanRegCheckMaskTXESC, initPara);   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  /*  Tx Buffer Data Field Size = 8,12,16,20,24,32,48,64 byte
      Note: In case the data length code DLC of a Tx Buffer element is configured to a value higher than the Tx Buffer data field size, 
      the bytes not defined by the Tx Buffer are transmitted as '0xCC' (padding bytes). */
#else
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXESC), (vuint32)(0x00000000UL), kCanRegCheckMaskTXESC, initPara);   /* SBSW_CAN_LL_100 */    /* 8 data bytes */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif

  /* Tx Event FIFO Configuration (TXEFC) */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TXEFC), (vuint32)(0x00000000UL), kCanRegCheckMaskTXEFC, initPara);   /* SBSW_CAN_LL_100 */    /* No Tx Event Fifo supported */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

  /* #80 interrupt control */
  /* Interrupt registers */
  initPara->ie     = kCanIE_DISABLE_ALL; /* SBSW_CAN_LL_109 */ 
  initPara->txbtie = kCanIE_DISABLE_ALL; /* SBSW_CAN_LL_109 */ 

#if( (!defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING )) || (defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )) )    /* COV_CAN_CBD_COMPATIBILITY */
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
# if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
    if(Can_30_Mcan_IsMailboxIndivPolling(CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)) == kCan_30_McanFalse) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif /* C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */
    {
      initPara->ie |= kCanIR_RF0N; /* SBSW_CAN_LL_109 */ /* use new msg */
    }
  }
# if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 1u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
#  if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
    if(Can_30_Mcan_IsMailboxIndivPolling(CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u) == kCan_30_McanFalse) /* PRQA S 1881 */ /* MD_MSR_AutosarBoolean */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#  endif /* C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */
    {
      initPara->ie |= kCanIR_RF1N; /* SBSW_CAN_LL_109 */   /* use new msg */
    }
  }
# endif /* C_30_MCAN_ENABLE_MULTIPLE_BASICCAN */
#endif  /* C_30_MCAN_ENABLE_RX_BASICCAN_POLLING || C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */

#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
#  if( (!defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )) || (defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )) )
  initPara->ie |= (kCanIR_DRX); /* SBSW_CAN_LL_109 */   /*    Bit 12 DRX     Message stored to Dedicated Rx Buffer */
  /* After the last word of a matching Rx message has been written to the Message RAM the NDF within NDAT1,2 is set. 
     As long as the NDF is set, the respective Rx Buffer is locked. The NDF has to be reset by the Host.
     While a specific NDF is set the refering Filter Element will not match, causing the acceptance filtering to continue. 
     Subsequent Filter Elements may cause the received message to be stored into 
     - another Rx Buffer, or 
     - an Rx FIFO, or
     - the message may be rejected. */
# endif /* C_30_MCAN_ENABLE_RX_FULLCAN_POLLING || C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if !defined(C_30_MCAN_ENABLE_TX_POLLING) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
  /* Bit 19 TEFNE   Tx Event FIFO New Entry Interrupt Enable
     Bit 21 TCFE    Transmission Cancellation Finished Interrupt Enable
     Bit 22 TCE     Transmission Completed Interrupt Enable */
  initPara->ie |= (kCanIR_TC); /* SBSW_CAN_LL_109 */
#endif
#if !defined(C_30_MCAN_ENABLE_ERROR_POLLING)
# if defined(C_30_MCAN_ENABLE_PARITY_INTERRUPT) /* COV_CAN_HW_SPECIFIC */
  initPara->ie |= (kCanIR_BEU); /* SBSW_CAN_LL_109 */   /* Bit Error Uncorrected */
# endif
  initPara->ie |= (kCanIR_BO); /* SBSW_CAN_LL_109 */   /* BusOff */

# if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
  /* Interrupt configuration for security feature */
  initPara->ie |= (kCanIR_EP); /* SBSW_CAN_LL_109 */ /* Passive error enable interrupt */
  initPara->ie |= (kCanIR_PEA); /* SBSW_CAN_LL_109 */ /* Protocol Error in Arbitration Phase enable interrupt */
#  if defined ( C_30_MCAN_ENABLE_CAN_FD_FULL ) || defined ( C_30_MCAN_ENABLE_CAN_FD_USED )
  initPara->ie |= (kCanIR_PED); /* SBSW_CAN_LL_109 */ /* Protocol Error in Data Phase enable interrupt */
#  endif
# endif
  initPara->ie |= (kCanIR_MRAF); /* SBSW_CAN_LL_109 */
  /* Bit 0  STEE    Stuff Error Interrupt Enable
     Bit 1  FOEE    Format Error Interrupt Enable
     Bit 2  ACKEE   Acknowledge Error Interrupt Enable
     Bit 3  BEE     Bit Error Interrupt Disable
     Bit 4  CRCEE   CRC Error Interrupt Enable
     Bit 5  WDIE    Watchdog Interrupt Enable
     Bit 6  BOE     Bus_Off Status Interrupt Enable
     Bit 7  EWE     Warning Status Interrupt Enable
     Bit 8  EPE     Error Passive Interrupt Enable
     Bit 9  ELO     Error Logging Overflow Enable
     Bit10  BEU     Bit Error Uncorrected Enable
     Bit11  BEC     Bit Error Corrected Enable
     Bit17  MRAF    Message RAM Access Failure (since MCAN 3.0.0)
     Bit27  PEA     Protocol Error in Arbitration Phase (since MCAN 3.1.0) */
# if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
    initPara->ie |= kCanIR_RF0L;  /* use overrun */ /* SBSW_CAN_LL_109 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  }
#  if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if(Can_30_Mcan_GetRxBasicHandleMax(canHwChannel) > 1u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2741 */ /* MD_Can_ConstValue */
  {
    initPara->ie |= kCanIR_RF1L;  /* use overrun */ /* SBSW_CAN_LL_109 */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  }
#  endif
# endif
#endif

  /* #90 if available keep TTCAN quiet */
#if defined ( C_30_MCAN_ENABLE_TTCAN_AVAILABLE ) /* COV_CAN_HW_SPECIFIC */
  if(Can_30_Mcan_IsIsTTCan(canHwChannel)) /* TTCAN */ /* COV_CAN_HW_SPECIFIC */
  {
    /* TT Operation Configuration Register:  Event-driven CAN communication, Application Watchdog disabled  */
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->TTOCF), (vuint32)(0x00000000UL), kCanRegCheckMaskTTOCF, initPara);   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
#endif

  return(kCan_30_McanOk); /* independent of RAM Check failure(s) returned within para struct */
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */ 
/* CanLL_30_Mcan_SetAllRegister */
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetRegisterMcanSS
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetRegisterMcanSS(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo)
{
  /* Initialize channel specific registers for MCANSS */

  /* MCANSS general control register */
  /* #10 Disregard debug suspend, external timestamp counter and automatic wakeup */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(McanExtraGlobalReg(channel)->MCANSS_CTRL), 0u, kCanRegCheckMaskMCANSS_CTRL, localInfo ); /* SBSW_CAN_LL_125 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */                                              

  /* #20 Disable External Timestamp Counter functionality */
  /* Interrupt status clear shadow register */
  McanExtraGlobalReg(channel)->MCANSS_ICS  |= kCanMcanSSRegICS_EXT_TS_CNTR_OVFL;                  /* clear external timestamp counter overflow interrupt status */           /* SBSW_CAN_LL_125 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

  /* Interrupt enable clear shadow register */
  McanExtraGlobalReg(channel)->MCANSS_IECS |= kCanMcanSSRegIECS_EXT_TS_CNTR_OVFL;                 /* clear external timestamp counter overflow interrupt enable*/            /* SBSW_CAN_LL_125 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

  /* End of interrupt register */
# if defined (C_30_MCAN_ENABLE_MCANSS_EOI) /* COV_CAN_HW_SPECIFIC */
  McanExtraGlobalReg(channel)->MCANSS_EOI  = (vuint32)(kCanMcanSSRegEOI_EXT);                     /* Clear External Timestamp Interrupt level */                             /* SBSW_CAN_LL_125 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# else
  McanExtraGlobalReg(channel)->MCANSS_EOI  &= (vuint32)(~kCanMcanSSRegEOI_EOI);                   /* set MCANSS_EOI EOI bits to 0 */                                         /* SBSW_CAN_LL_125 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif /* C_30_MCAN_ENABLE_MCANSS_EOI */

  /* External timestamp prescaler register */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(McanExtraGlobalReg(channel)->MCANSS_EXT_TS_PRESCALER), 0u, kCanRegCheckMaskMCANSS_EXT_TS_PRESCALER, localInfo); /* Clear prescaler */ /* SBSW_CAN_LL_125 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

  /* #30 Disable ECC functionality */
# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_AGGR)/* COV_CAN_HW_SPECIFIC */
  McanEccReg(channel)->MCANSS_ECC_AGGR_ENABLE_CLR = kCanMcanSSRegEccAggrEnableClear;              /* SBSW_CAN_LL_126 */ /* Disable ECC Aggregator for Timeout and parity */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif /* C_30_MCAN_ENABLE_MCANSS_ECC_AGGR */
  /* End of interrupt for ECC interrupt register */
#if defined (C_30_MCAN_ENABLE_MCANSS_ECC_EOI) /* COV_CAN_HW_SPECIFIC */
  McanExtraGlobalReg(channel)->MCANSS_ECC_EOI &= (vuint32)(~kCanMcanSSRegEE_ECC_EOI);             /* set MCANSS_ECC_EOI ECC_EOI to 0 */                                     /* SBSW_CAN_LL_125 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_EOI */
/* Clear Interrupt Enable for MSGMEM_PEND */
  McanEccReg(channel)->MCANSS_ECC_SEC_ENABLE_CLR_REG0 = (vuint32)(kCanMcanSSRegEccSecEnableClr);  /* SBSW_CAN_LL_126 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

/* Clear Interrupt Enable for MSGMEM_PEND */
  McanEccReg(channel)->MCANSS_ECC_DED_ENABLE_CLR_REG0 = (vuint32)(kCanMcanSSRegEccDedEnableClr);  /* SBSW_CAN_LL_126 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
}
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_REGEXT_MCANSS */


#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetRegisterSICanFD
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetRegisterSICanFD(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo)
{
  /* Set Key Code for write to AL_SET_* register*/
  SICANFD(channel)->SICANFD_AL_KEYCD = (vuint32)(kCanSICanFd_AL_KEYCODE);                    /* Enable Write to SET registers with Key Code */ /* SBSW_CAN_LL_115 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  /* #10 Initialise DCLS Fault Injection Configuration Register */
  if ( ((SICANFD(channel)->SICANFD_AL_KEYST) & (vuint32)(kCanSICanFd_AL_KEYSTATUS)) == (vuint32)(kCanSICanFd_AL_KEYSTATUS) ) /* Key Code Setting Is Done */  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_SICANFD_KEY_FAILURE */
  {
    /* DCLS Fault Injection Configuration Register*/
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(SICANFD(channel)->SICANFD_AL_SET_DCLS),(vuint32)(kCanSICanFd_DCLS_FI_INEFFECTIVE),kCanRegCheckMaskSICANFD_AL_SET_DCLS, localInfo); /* Set DCLS Fault Injection to Ineffective*/ /* SBSW_CAN_LL_115 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
  else
  {
    assertHardware(0, canHwChannel, kCanErrorSICANFDKeyRejected);
  }
  /* Set Key Code for write to AL_SET_* register*/
  SICANFD(channel)->SICANFD_AL_KEYCD = (vuint32)(kCanSICanFd_AL_KEYCODE);                    /* Enable Write to SET registers with Key Code */ /* SBSW_CAN_LL_115 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  /* #20 Initialise ECC Fault Injection Setting Register */
  if ( ((SICANFD(channel)->SICANFD_AL_KEYST) & (vuint32)(kCanSICanFd_AL_KEYSTATUS)) == (vuint32)(kCanSICanFd_AL_KEYSTATUS) ) /* Key Code Setting Is Done */  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_SICANFD_KEY_FAILURE */
  {
    /* ECC Fault Injection Setting Register*/
    (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(SICANFD(channel)->SICANFD_AL_SET_ECC),(vuint32)(kCanSICanFd_ECC_FI_INEFFECTIVE),kCanRegCheckMaskSICANFD_AL_SET_ECC, localInfo); /* Set ECC Fault Injection to Ineffective*/ /* SBSW_CAN_LL_115 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  }
  else
  {
    assertHardware(0, canHwChannel, kCanErrorSICANFDKeyRejected);
  }
  /* #30 Clear SEC, DEC and DCLS Flags */
  SICANFD(channel)->SICANFD_AL_CLR = ((vuint32)(kCanSICanFd_CLR_SEC)  |                      /* Clear SEC Flag*/ /* SBSW_CAN_LL_115 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
                                      (vuint32)(kCanSICanFd_CLR_DED)  |                      /* Clear DEC Flag*/
                                      (vuint32)(kCanSICanFd_CLR_DCLS));                      /* Clear DCLS Flag*/

  /* #40 Initialize ECC Fault Injection Position register for data and ECC */
  /*ECC Fault Injection Posistion Setting Register(data)*/
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(SICANFD(channel)->SICANFD_FI_DATA_D),(vuint32)(kCanSICanFd_FI_DATA_D_NO_INV),kCanRegCheckMaskSICANFD_FI_DATA_D, localInfo); /* Fault Injection Bit Position for Data Written to Message RAM, No Bit Inversion */ /* SBSW_CAN_LL_115 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  /*ECC Fault Injection Position Setting Register (ECC)*/
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(SICANFD(channel)->SICANFD_FI_DATA_E),(vuint32)(kCanSICanFd_FI_DATA_E_NO_INV),kCanRegCheckMaskSICANFD_FI_DATA_E, localInfo); /* Fault Injection Bit Position for An ECC Code Written to Message RAM, No Bit Inversion */ /* SBSW_CAN_LL_115 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

}
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_REGEXT_SICANFD */

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetRegisterTTCanFD
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetRegisterTTCanFD(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo)
{
  /* #10 Initialize Receive FIFO Top control register */
  (void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(TTCANFD(channel)->TTCANFD_CAN_CH_RXFTOP_CTL),(vuint32)(kCanTTCanFD_CAN_CLEAR),kCanRegCheckMaskTTCANFD_RXFTOP_CTL, localInfo); /* Disable FIFO 0 and 1 Top Pointer */ /* SBSW_CAN_LL_116 */ /* SBSW_CAN_HL36 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
}
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_REGEXT_TTCANFD */

#if defined( C_30_MCAN_ENABLE_SHM_DATAQOS ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetRegisterDataQoS
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetRegisterDataQoS(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo)
{
  /* #10 Set Shared Message RAM Data Quality of Service */
(void)CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(Cn->MRCFG), (vuint32)(Can_30_Mcan_GetCAN_DataQoS()), kCanRegCheckMaskMRCFG_DATAQOS, localInfo); /* SBSW_CAN_LL_100 */
}
/* CODE CATEGORY 4 END */
#endif /* C_30_MCAN_ENABLE_SHM_DATAQOS */

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetGlobalRegisterTTCanFD
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterTTCanFD(void)
{
  /*Local Variables*/
  vuint8 indx;

#  if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if((Can_30_Mcan_GetSizeOfCanSubSystemBaseAdr() != 2u) && (Can_30_Mcan_GetSizeOfCanSubSystemBaseAdr() != 1u) ) /* PRQA S 3325,2992,2742 */ /* MD_Can_3325_LL,MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { 
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
#  endif
  {
    /* #10 Get Number of Active Subsystems */
    for (indx=0;indx<Can_30_Mcan_GetSizeOfCanSubSystemBaseAdr(); indx++)
    {
      /*#20 Initialize Global registers for the active subsystem */
      TTCANFD_SUB(indx)->TTCANFD_CAN_CTL = kCanTTCanFD_CAN_CLEAR;         /* Clear MRAM Off */ /* SBSW_CAN_LL_117 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ 
                                                                          /* Clear Stop Request for each TTCAN IP */
      TTCANFD_SUB(indx)->TTCANFD_CAN_TS_CTL = kCanTTCanFD_CAN_CLEAR;      /* Disable Counter */ /* SBSW_CAN_LL_117 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
                                                                          /* Initialize Time Stamp counter prescale value to 0 */
      TTCANFD_SUB(indx)->TTCANFD_CAN_TS_CNT = kCanTTCanFD_CAN_CLEAR;      /* Clear Time Stamp Counter value to 0*/ /* SBSW_CAN_LL_117 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */ 
      TTCANFD_SUB(indx)->TTCANFD_CAN_ECC_CTL = kCanTTCanFD_CAN_CLEAR;     /* Disable ECC for CANFD SRAM*/ /* SBSW_CAN_LL_117 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      TTCANFD_SUB(indx)->TTCANFD_CAN_ECC_ERR_INJ = (kCanTTCanFD_CAN_CLEAR | kCanTTCanFD_CAN_ECC_ERR_INJ_ERR_ADDR); /* Initialize ECC Parity bits used to ECC error injection to 0 */ /* SBSW_CAN_LL_117 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
                                                                                                                   /* Disable error injection */
                                                                                                                   /* Initialize the address of the word where an error will be injected to 0 */
    }
  }
} /* CanLL_30_Mcan_SetGlobalRegisterTTCanFD */
/* CODE CATEGORY 4 END */
#endif /*End C_30_MCAN_ENABLE_REGEXT_TTCANFD*/

#if ( CAN_30_MCAN_SAFE_BSW == STD_ON )
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_CheckGeneratedData
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_CheckGeneratedData(void)
{
  /* Local Variables */
  vuint8 ret = kCan_30_McanOk;
  /* #10 Check size of ShmAdr table */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
  if ((Can_30_Mcan_GetSizeOfShmAdr() != kCan_30_McanNumberOfChannels) || (Can_30_Mcan_GetSizeOfVirtualShmAdr() != kCan_30_McanNumberOfChannels)) /* CM_CAN_LL_112 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
# else
  if (Can_30_Mcan_GetSizeOfShmAdr() != kCan_30_McanNumberOfChannels) /* CM_CAN_LL_112 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
# endif
    {
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    ret = kCan_30_McanFailed;
  }
# if defined ( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
  /* #20 Check size of McanSsBaseAddr table */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
  if ((Can_30_Mcan_GetSizeOfCanMcanSsBaseAddr() != kCan_30_McanNumberOfChannels) || (Can_30_Mcan_GetSizeOfVirtualCanMcanSsBaseAddr() != kCan_30_McanNumberOfChannels))/* CM_CAN_LL_113 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
# else
  if (Can_30_Mcan_GetSizeOfCanMcanSsBaseAddr() != kCan_30_McanNumberOfChannels) /* CM_CAN_LL_113 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
# endif
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    ret = kCan_30_McanFailed;
  }
  /* #30 Check size of EccAggrBaseAddr table */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
  if ((Can_30_Mcan_GetSizeOfCanEccAggrBaseAddr() != kCan_30_McanNumberOfChannels) || (Can_30_Mcan_GetSizeOfVirtualCanEccAggrBaseAddr() != kCan_30_McanNumberOfChannels))/* CM_CAN_LL_114 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
# else
  if (Can_30_Mcan_GetSizeOfCanEccAggrBaseAddr() != kCan_30_McanNumberOfChannels) /* CM_CAN_LL_114 */ /* PRQA S 2992,2742 */ /* MD_Can_ConstValue,MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
# endif
  {
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    ret = kCan_30_McanFailed;
  }
# endif
  return (ret);
} /* CanLL_30_Mcan_CheckGeneratedData */
/* CODE CATEGORY 4 END */
#endif /* End C_30_MCAN_ENABLE_REGEXT_MCANSS */

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetGlobalRegisterMcanAS1
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterMcanAS1(void)
{

# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if(!Can_30_Mcan_HasCanGlobalBaseAdr()) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 3325 */ /* MD_Can_3325_LL */
  { 
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); 
  }
  else
# endif
  {
    /* #10 Release the functional safety registers */
    MCANAS1_FSECC->MCANAS1_PROTECT_KEY = kCanMcanAs1_PROTECT_KEY_RELEASE; /* SBSW_CAN_LL_124 */
    /* #20 Disable ECC interrupts */
    MCANAS1_FSECC->MCANAS1_ECCCTRL = kCanMcanAs1_ECCCTRL_DISABLE;         /* SBSW_CAN_LL_124 */
    /* #30 Set surface access to ECC */
    MCANAS1_FSECC->MCANAS1_ECCRAM_DBGSEL = kCanMcanAs1_ECCRAM_DBGSEL;     /* SBSW_CAN_LL_124 */
    /* #40 Set route access to ECC generation unit */
    MCANAS1_FSECC->MCANAS1_ECCRAM_DBG = kCanMcanAs1_ECCRAM_DBG;           /* SBSW_CAN_LL_124 */
    /* #50 Lock the functional safety registers */
    MCANAS1_FSECC->MCANAS1_PROTECT_KEY = kCanMcanAs1_PROTECT_KEY_LOCK;    /* SBSW_CAN_LL_124 */
  }
} /* CanLL_30_Mcan_SetGlobalRegisterMcanAS1 */
/* CODE CATEGORY 4 END */
#endif /*End C_30_MCAN_ENABLE_REGEXT_MCANAS1*/


#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetGlobalRegisterStmFdCan
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterStmFdCan(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
#if defined(C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL) && defined( C_30_MCAN_ENABLE_HW_LOOP_TIMER )
  channel = 0;
#endif

# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if(!Can_30_Mcan_HasCanGlobalBaseAdr()) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 3325 */ /* MD_Can_3325_LL */
  { 
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA); 
  }
  else
# endif
  { /* #10 Set and verify CAN1 to be in init and CCE */
    if ((STMFDCAN_MCAN0->CCCR & kCanCCCR_INIT) != kCanCCCR_INIT ) /* If Init-Bit is not set */ /* PRQA S 2842 */ /* MD_Can_Assertion */
    {
      STMFDCAN_MCAN0->CCCR  |= kCanCCCR_INIT; /* SBSW_CAN_LL_100 */ /* PRQA S 2842 */ /* MD_Can_Assertion */
      CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanStmFdLoopInit); /* PRQA S 2842 */ /* MD_Can_Assertion */ /* SBSW_CAN_LL_101 */
      while( ((STMFDCAN_MCAN0->CCCR & kCanCCCR_INIT) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanStmFdLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303,2842 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess,MD_Can_Assertion */ /* COV_CAN_HW_SPECIFIC */
      {/* Assure that INIT has been accepted. */}
      CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanStmFdLoopInit); /* SBSW_CAN_LL_101 */
    }  
    if ((STMFDCAN_MCAN0->CCCR & kCanCCCR_CCE) != kCanCCCR_CCE ) /* If CCE-Bit is not set */ /* PRQA S 2842 */ /* MD_Can_Assertion */
    {
      STMFDCAN_MCAN0->CCCR  |= kCanCCCR_CCE; /* SBSW_CAN_LL_100 */ /* PRQA S 2842 */ /* MD_Can_Assertion */
      CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanStmFdLoopInit); /* PRQA S 2842 */ /* MD_Can_Assertion */ /* SBSW_CAN_LL_101 */
      while( ((STMFDCAN_MCAN0->CCCR & kCanCCCR_CCE) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanStmFdLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303,2842 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess,MD_Can_Assertion */ /* COV_CAN_HW_SPECIFIC */
      {/* Assure that CCE has been accepted. */}
      CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanStmFdLoopInit); /* SBSW_CAN_LL_101 */
    }
    /* #20 Initialize Global Register for StmFdCan CCU(Clock Calibration Unit) */
    STMFDCAN_CCU->STMFDCAN_CCU_CCFG = kCanStmCanFD_CAN_CCU_CCFG_CLEAR;
    STMFDCAN_CCU->STMFDCAN_CCU_CWD = kCanStmCanFD_CAN_CCU_CWD_CLEAR;
    STMFDCAN_CCU->STMFDCAN_CCU_IR = kCanStmCanFD_CAN_CCU_IR_CLEAR;
    STMFDCAN_CCU->STMFDCAN_CCU_IE = kCanStmCanFD_CAN_CCU_IE_CLEAR;
  }
} /* CanLL_30_Mcan_SetGlobalRegisterStmFdCan */
/* CODE CATEGORY 4 END */
#endif /*End C_30_MCAN_ENABLE_REGEXT_STMFDCAN*/

#if defined( C_30_MCAN_ENABLE_REGEXT_TCC ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_SetGlobalRegisterTCC
****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterTCC(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Verify Global base address for TCC */
# if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if(!Can_30_Mcan_HasCanGlobalBaseAdr())                                          /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2742 */ /* MD_Can_ConstValue */
  { 
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, CAN_30_MCAN_E_GENDATA);                             /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
# endif
  { 
    /* #20 Unlock the password protection over the config registers */
# if defined( C_30_MCAN_ENABLE_REGEXT_TCC_PWD ) && !defined (CAN_30_MCAN_TCC_PWD_OFF)
    TCC_CFG->CAN_CFG_WR_PW = kCanTCC_PWD_KEYCODE;                                                             /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    assertHardware((TCC_CFG->CAN_CFG_WR_PW == 1u), 0u, kCanErrorPwdRejected);                                                       /* PRQA S 0303 */ /* MD_Can_HwAccess */
    TCC_CFG->CAN_CFG_WR_LOCK = 0u;                                                                            /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif

    /* #30 Initialize the config registers to hold the Message RAM addresses */
# if defined( kCan_30_McanPhysToLogChannelIndex_0 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    TCC_CFG->CFG1_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(Can_30_Mcan_GetPhysToLogChannel(0)) >> 16u;       /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  else
#   if defined( C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL)
    TCC_CFG->CFG1_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(kCan_30_McanPhysToLogChannelIndex_0) >> 16u;      /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   else 
    TCC_CFG->CFG1_MRAM_ADDR = (Can_30_Mcan_GetStartAdrOfShmAdr(0)) >> 16u;                                     /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   endif    
#  endif 
# endif

# if defined( kCan_30_McanPhysToLogChannelIndex_1 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    TCC_CFG->CFG2_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(Can_30_Mcan_GetPhysToLogChannel(1)) >> 16u;      /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  else
#   if defined( C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL)
    TCC_CFG->CFG2_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(kCan_30_McanPhysToLogChannelIndex_1) >> 16u;     /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   else 
    TCC_CFG->CFG2_MRAM_ADDR = (Can_30_Mcan_GetStartAdrOfShmAdr(0)) >> 16u;                                    /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   endif      
#  endif  
# endif

# if defined( kCan_30_McanPhysToLogChannelIndex_2 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
#  if defined( CAN_30_MCAN_USE_PHYSTOLOG_MAPPING )
    TCC_CFG->CFG3_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(Can_30_Mcan_GetPhysToLogChannel(2)) >> 16u;      /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  else
#   if defined( C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL)
    TCC_CFG->CFG3_MRAM_ADDR = Can_30_Mcan_GetStartAdrOfShmAdr(kCan_30_McanPhysToLogChannelIndex_2) >> 16u;     /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   else 
    TCC_CFG->CFG3_MRAM_ADDR = (Can_30_Mcan_GetStartAdrOfShmAdr(0)) >> 16u;                                    /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#   endif 
#  endif  
# endif
    /* #40 Secure the Config registers with password protection */
# if defined( C_30_MCAN_ENABLE_REGEXT_TCC_PWD ) && !defined (CAN_30_MCAN_TCC_PWD_OFF)
    TCC_CFG->CAN_CFG_WR_PW = kCanTCC_PWD_KEYCODE;                                                            /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    assertHardware((TCC_CFG->CAN_CFG_WR_PW == 1u), 0u, kCanErrorPwdRejected);                                                      /* PRQA S 0303 */ /* MD_Can_HwAccess */
    TCC_CFG->CAN_CFG_WR_LOCK = 1u;                                                                           /* SBSW_CAN_LL_128 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif
  }
} /* CanLL_30_Mcan_SetGlobalRegisterTCC */
/* CODE CATEGORY 4 END */
#endif /*End C_30_MCAN_ENABLE_REGEXT_TCC*/

#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
# if !defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING ) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )        /* ISR necessary; no pure polling configuration */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanBasicInterruptRx
****************************************************************************/
/*
|<DataModelStart>| CanBasicInterruptRx
Relation_Context:
# CanInterrupt() #
Relation:
OneChOpt
ChannelAmount
RxBasicCANSupport, MultipleBasicCanObjects, RxPolling, TxPolling, IndividualPolling, HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanBasicInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* #30 check Fifo - 0 (BasicCAN0) for new data */
  if( ((Cn->IR) & kCanIR_RF0N) != 0UL)  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  { /* rcvd new msg in FIFO 0 */
    Cn->IR = (kCanIR_RF0N);   /* SBSW_CAN_LL_100 */    /* clear */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
    if(Can_30_Mcan_IsMailboxIndivPolling(CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)))  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { 
      /* poll this object later on during the next read task cycle */ 
    }
    else
# endif
    {
      CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
      while( (((Cn->RXF0S).B.FnFL) > 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopRxFifo) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* hwObjHandle for RxFifo0 is 0 */
        CanHL_30_Mcan_BasicCanMsgReceived(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST (CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel)), 0u ); 
      }
      CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
    }
  }

# if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  /* #40 check Fifo - 1 (BasicCAN1) for new data */
  if( ((Cn->IR) & kCanIR_RF1N) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* Rcvd new msg in FIFO 1 */
    Cn->IR = (kCanIR_RF1N); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */ /* Clear */
#  if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
    if(Can_30_Mcan_IsMailboxIndivPolling(CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      /* poll this object later on during the next read task cycle */ 
    }
    else
#  endif
    {
      CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
      while( (((Cn->RXF1S).B.FnFL) > 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopRxFifo) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
      {
        /* Increment the MailboxHandle. There is an  additional mailbox object for FIFO-1. hwObjHandle for RxFifo-1 is 1 */
        CanHL_30_Mcan_BasicCanMsgReceived(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST (CAN_30_MCAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel) + 1u), 1u ); 
      }
      CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopRxFifo); /* SBSW_CAN_LL_102 */  
    }
  }
# endif /* C_30_MCAN_ENABLE_MULTIPLE_BASICCAN */
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */  
/* CanBasicInterruptRx */
/* CODE CATEGORY 4 END */
# endif /* _ENABLE_RX_BASICCAN_OBJECTS */
#endif /* _ENABLE_RX_BASICCAN_POLLING || _ENABLE_INDIVIDUAL_POLLING */

#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
# if (!defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING ) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING ))        /* ISR necessary; no pure polling configuration */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanFullInterruptRx
****************************************************************************/
/*
|<DataModelStart>| CanFullInterruptRx
Relation_Context:
# CanInterrupt() #
Relation:
OneChOpt
ChannelAmount
RxFullCANSupport, RxPolling, TxPolling, IndividualPolling, HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanFullInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint32 ndata[2], shiftVal;
  vuint8  ndf, idx;
  Can_30_McanObjectHandle hwObjHandle;

  /* #20 check RxBuffer (FullCAN) for new data */
  /* Rx Buffer Handling
    - Reset interrupt flag IR.DRX
    - Read New Data registers
    - Read messages from Message RAM
    - Reset New Data flags of processed messages */
  if( ((Cn->IR) & kCanIR_DRX ) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* rcvd FullCAN msg(s) */
    Cn->IR = (kCanIR_DRX); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */  /* Reset interrupt flag */
    ndata[0] = Cn->NDATA[0]; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_106 */  /* Read New Data registers */
    ndata[1] = Cn->NDATA[1]; /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_106 */
    /* After the last word of a matching received message has been written to the Message RAM, the respective New Data flag in register NDAT1,2 is set. 
       As long as the New Data flag is set, the respective Rx Buffer is locked against updates from received matching frames. */
    ndf = 0u;
    idx = 0u;
    hwObjHandle = 0u;
    while( ((ndata[0] | ndata[1]) > 0UL) && (idx < 2u) ) /* CM_CAN_LL_107 */  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* at least one buffer not read yet AND first sweep */
      shiftVal = (vuint32)(0x00000001UL << ndf);
      if((ndata[idx] & shiftVal) != 0UL)
      { /* detected NDF */
#  if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
        if(Can_30_Mcan_IsMailboxIndivPolling(CAN_30_MCAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel) + hwObjHandle))  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        { 
          /* poll this object later on during the next read task cycle */ 
        }
        else
#  endif
        { /* Attention:
             While an Rx Buffers NDF is set the belonging ID Filter will not match, causing the acceptance filtering to continue. 
             Following ID Filters may cause the received message to be stored into another Rx Buffer or into an Rx FIFO or the message may be rejected. */
          CanHL_30_Mcan_FullCanMsgReceived(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST ((CAN_30_MCAN_HL_MB_RX_FULL_STARTINDEX(canHwChannel)) + hwObjHandle), hwObjHandle);
        }
        ndata[idx] &= (vuint32) (~shiftVal); /* reset NDF */  /* SBSW_CAN_LL_107 */
      }
      hwObjHandle++;
      ndf++;
      if(ndf >= 32u)  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* next 32 FullCAN Buffers */
        ndf = 0u;
        idx += 1u;
      }
    } /* endwhile */
  } /* endif Rx FullCAN interrupt */
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */  
/* CanFullInterruptRx */
/* CODE CATEGORY 4 END */
# endif
#endif


/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanInterruptErrorHandling
****************************************************************************/
/*
|<DataModelStart>| CanInterruptErrorHandling
Relation_Context:
# CanInterrupt() #
Relation:
OneChOpt
ChannelAmount
StatusPolling, RxBasicCANSupport, MultipleBasicCanObjects
CanSecurityEventReporting, CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#if !defined(C_30_MCAN_ENABLE_ERROR_POLLING)
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanInterruptErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 ret;
  vuint32 CanLocal_IR;

  /* #10 check error status and call error handling */
  CanLocal_IR = Cn->IR; /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  /* #20 check for Message Lost */
# if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
  if(((CanLocal_IR & Cn->IE & kCanIR_RF0L) != 0UL) || ((CanLocal_IR & Cn->IE & kCanIR_RF1L) != 0UL)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# else
  if( (CanLocal_IR & Cn->IE & kCanIR_RF0L) != 0UL)                                            /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
# endif
  { /* msg lost due to either FIFO 0/1 full or with size zero */
    CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
    /* #30 clear overflow flags */
    Cn->IR = (vuint32)(kCanIR_RF0L | kCanIR_RF0F | kCanIR_RF1L | kCanIR_RF1F);   /* SBSW_CAN_LL_100 */   /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */ /* clear flag(s) */
  }

  ret = kCan_30_McanFailed; /* do not proceed with further IR Flags evaluation */
  /* #40 check for Message RAM failure */
# if defined(C_30_MCAN_ENABLE_PARITY_INTERRUPT) /* COV_CAN_HW_SPECIFIC */
  if( (CanLocal_IR & Cn->IE & kCanIR_BEU) != 0UL) /* COV_CAN_HW_SPECIFIC */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  { /* Bit Error Uncorrected */
    CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
    /* #50 clear Message RAM failure */
    Cn->IR = (kCanIR_BEU);   /* SBSW_CAN_LL_100 */    /* clear flag */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  }
  /* #60 check for busoff failure */
  else if( (CanLocal_IR & Cn->IE & kCanIR_BO) != 0UL) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
# else
  if( (CanLocal_IR & Cn->IE & kCanIR_BO) != 0u) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
# endif 
  { /* Bus_Off status changed */
    CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
    /*  In contrast to Bus_Off neither Warning-/Error- status nor ACK or CRC errors are considered (kCanIR_EW,kCanIR_EP,kCanIR_ACKE, kCanIR_CRCE,) */
    /* #70 clear busoff error flags */
    Cn->IR = (kCanIR_BO);   /* SBSW_CAN_LL_100 */    /* clear flag */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  }
  /* #80 check for access failure flags */
  else if( (CanLocal_IR & Cn->IE & kCanIR_MRAF) != 0UL) /* COV_CAN_MCAN_NOT_SUPPORTED */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  { /* Message RAM Access Failure
        The flag is set, when the Rx Handler
        - has not completed acceptance filtering or storage of an accepted message until the arbitration
        field of the following message has been received. In this case acceptance filtering or message
        storage is aborted and the Rx Handler starts processing of the following message.
        - was not able to write a message to the Message RAM. In this case message storage is aborted.
        In both cases the FIFO put index is not updated resp. the New Data flag for a dedicated Rx Buffer
        is not set, a partly stored message is overwritten when the next message is stored to this location.
        
        The flag is also set when the Tx Handler 
        - was not able to read a message from the Message RAM in time. 
        In this case message transmission is aborted. 
        In case of a Tx Handler access failure the M_CAN is switched into Restricted Operation Mode.  */
    CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
    /* #90 clear access failure flags */
    Cn->IR = (kCanIR_MRAF);   /* SBSW_CAN_LL_100 */    /* clear flag */ /* PRQA S 0303,2842 */ /* MD_Can_HwAccess,MD_Can_HL_DereferencePointerValue */
  }

# if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING) 
  /* #100 check for security events */
  else if(((CanLocal_IR & Cn->IE & kCanIR_EP) != 0UL) || ((CanLocal_IR & Cn->IE & kCanIR_PEA) != 0UL) /* PRQA S 0303, 0303 */ /* MD_Can_HwAccess */
#  if defined ( C_30_MCAN_ENABLE_CAN_FD_FULL ) || defined ( C_30_MCAN_ENABLE_CAN_FD_USED )
   || ((CanLocal_IR & Cn->IE & kCanIR_PED) != 0UL)  /* PRQA S 0303 */ /* MD_Can_HwAccess */
#  endif
  )
  { 

#  if defined ( C_30_MCAN_ENABLE_CAN_FD_FULL ) || defined ( C_30_MCAN_ENABLE_CAN_FD_USED )    
       /* Clear the PED flag */
    Cn->IR = (vuint32)(kCanIR_PED); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */
#  endif
      /* Clear the PEA flag */
   Cn->IR = (vuint32)(kCanIR_PEA); /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* SBSW_CAN_LL_100 */

    /* Security event detected */
   CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
   
   /* When security event is detected, Software should continue handling the Tx,Rx and other Interrupts (ESCAN00110641) */
   ret = kCan_30_McanOk;
  }
# endif
  else
  {
    ret = kCan_30_McanOk;
  }
  return(ret);
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* CanInterruptErrorHandling */
/* CODE CATEGORY 4 END */
#endif


/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanInterruptTx
****************************************************************************/
/*
|<DataModelStart>| CanInterruptTx
Relation_Context:
# CanInterrupt() #
Relation:
OneChOpt
ChannelAmount, TxPolling, IndividualPolling
ChannelAmount, TxHwFifo
TxHwFifo, MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
#if !defined(C_30_MCAN_ENABLE_TX_POLLING) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInterruptTx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8  hwObjHdl;
  Can_30_McanObjectHandle  mboxHdl;
  Can_30_McanObjectHandle  mailboxElement = kCanZero; /* PRQA S 2981 */  /* MD_Can_RedundantInit */
  vuint32 bPos;
  vuint32 CanLocal_IR;

  CanLocal_IR = Cn->IR; /* PRQA S 0303 */ /* MD_Can_HwAccess */

  /* #10 check transmit status */
  if( (CanLocal_IR & Cn->IE & kCanIR_TC) != 0UL) /* COV_CAN_TX_INTERRUPT */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  { /* Tx Confirmation */
    /* #20 clear flags */
    Cn->IR = (kCanIR_TC);   /* SBSW_CAN_LL_100 */    /* clear */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    /* Each Tx Buffer has its own Transmission Occurred bit. 
       The bits are set when the corresponding TXBRP bit is cleared after a successful transmission. 
       The bits are reset when a new transmission is requested by writing a '1' to the corresponding bit of register TXBAR. */
    bPos = kCan_30_McanACTIVE;
    hwObjHdl = 0;
    /* #30 check for Transmit Confirmation */
    while ( (hwObjHdl < kCanTXBC_NDTB) && (Can_30_Mcan_GetCanTXBRP(canHwChannel) > 0UL) )
    { /* at least one transmission is pending */
      mboxHdl = Can_30_Mcan_GetMailboxHandleOfMemorySectionObjects( Can_30_Mcan_GetMemorySectionStartOfMemorySectionInfo(canHwChannel) + hwObjHdl);
#  if defined( C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION ) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
      mailboxElement = Can_30_Mcan_GetMailboxElementOfMemorySectionObjects(Can_30_Mcan_GetMemorySectionStartOfMemorySectionInfo(canHwChannel) + hwObjHdl);
#  endif
      if( ((Can_30_Mcan_GetCanTXBRP(canHwChannel) & bPos) != 0UL) && ( ((Cn->TXBTO & bPos) != 0UL) ) ) /* COV_CAN_HW_SPECIFIC */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      { /* found requested confirmation */
# if defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
        if(Can_30_Mcan_IsMailboxIndivPolling(mboxHdl)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        { /* poll this object */
        }
        else
# endif
        {
          CanHL_30_Mcan_TxConfirmation(CAN_30_MCAN_CHANNEL_CANPARA_FIRST mboxHdl, mailboxElement, hwObjHdl);
        }
      }
      hwObjHdl++;
      bPos <<= 1;
    } /* end while */
  }  /* endif TC */

} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* CanInterruptTx */
/* CODE CATEGORY 4 END */
#endif

#if( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanInterruptTimeoutCounter
****************************************************************************/
/*
|<DataModelStart>| CanInterruptTimeoutCounter
Relation_Context:
# CanInterrupt() #
Relation:
OneChOpt
ChannelAmount
HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInterruptTimeoutCounter(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* timeout arrived */

  /* The erratum is limited to the case where a receiving M_CAN with PXHD enabled enters Bus Integration state 
     after detection of bits FDF and res both recessive.
     Effects:
     The receiver stops for an unpredictable amount of time.
     To leave Bus Integration state, at least one dominant bit has to be detected by a receiving
     M_CAN to start counting of 11 consecutive recessive bits.
     With Protocol Exception Handling enabled (CCCR.PXHD = '0'):
      - PSR.PXE (Protocol Exception Event) is signalled
      - Operation state changes from Receiver (PSR.ACT = '10') to Integrating (PSR.ACT = '00') at the next sample point.
      Workaround:
       R3.1.0: disable Protocol Exception Event Handling (CCCR.PXHD = '1')
       Other revisions: set and release INIT  */
  /* #10 check for protocol error */
#  if ( CAN_MCAN_REVISION >= 0x310UL ) /* COV_CAN_HW_SPECIFIC */
  if( ((Cn->CCCR & kCanCCCR_PXHD) == 0UL) && ((Cn->PSR & kCanPSR_PXE) != 0UL) && ((Cn->PSR & kCanPSR_ACT) == 0UL) ) /* COV_CAN_HW_SPECIFIC */
#  else
  if( ((Cn->PSR & kCanPSR_BO) == 0UL) && ((Cn->PSR & kCanPSR_ACT) == 0UL) )
#  endif /* CAN_MCAN_REVISION */
  { /* PXE and ACT is reset on read.
       Note: Disable Protocol Exception Handling 'CCCR.PXHD = 1' generates an error frame thus we prefer this workaround */
    /* #20 accomplish propagated workaround */
    Cn->CCCR |= kCanCCCR_INIT; /* SBSW_CAN_LL_100 */  /* Setting INIT means the MCAN node is detached from the CAN Bus, the Tx Pin becomes recessive '1'.
                                                           During INIT = '1' the MCAN is stopped, all other nodes are not disturbed.) */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_102 */  
    while( ((Cn->CCCR & kCanCCCR_INIT) == 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
    { /* Assure that INIT has been accepted */ }
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit);  /* SBSW_CAN_LL_102 */  
    Cn->CCCR &= (vuint32)(~kCanCCCR_INIT);  /* SBSW_CAN_LL_100 */   
  }

  /* #30 keep counter running for further supervision */
  /* further periodical interruption requested due to PSR monitoring */
  Cn->TOCV = 0; /* SBSW_CAN_LL_100 */ /* When the counter reaches zero IR.TOO is set. In Continuous Mode the counter is immediately restarted at TOCC.TOP.
                                           Thus reload counter once more NOW (before clearing the IR) with TOCC[TOP] and continue down counting */
  Cn->IR = kCanIR_TOO;   /* SBSW_CAN_LL_100 */    /* clear */
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* CanInterruptTimeoutCounter */
/* CODE CATEGORY 4 END */
#endif




/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_StartRequest
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_StartRequest
Relation_Context:
# from CanLL_ModeTransition #
Relation:
OneChOpt
ChannelAmount
HardwareLoopCheck
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StartRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 transitionRequest;
  transitionRequest = kCan_30_McanOk; /* PRQA S 2982 */ /* MD_Can_2982_LL */

  /* #10 requested mode already reached */
  if((Cn->CCCR & kCanCCCR_INIT) == 0UL)  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    transitionRequest = kCan_30_McanOk;
  }
  else
  {
    /* #20 request mode transition if not reached yet */
    /* request RUNNING mode finish Power Down:
       a) Reset CCCR[CSR] (before resetting the CSR bit the module clocks must have been turned on by the application)
       b) M_CAN will acknowledge the reset of the CSR bit by resetting CCCR[CSA]. 
       c) Now the application can reset CCCR[INIT] to restart the CAN communication */
    ApplCan_30_McanClockStart(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);        /* request the application to turn on the clocks (CAN, Host) */
    
    /* The CCCR[CSR] have been set during the handling of the Erratas */
    /* CCCR[CSR] have to be reset first */
    Cn->CCCR &= (vuint32)~(kCanCCCR_CSR); /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    Cn->CCCR &= (vuint32)~(kCanCCCR_INIT); /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    /* To leave power down mode, the application has to turn on the module clocks before resetting CCCR.CSR. 
       MCAN will acknowledge this by resetting CCCR.CSA. 
       Afterwards, the application can restart CAN communication by resetting bit CCCR.INIT. */
    /* After resetting CCCR[INIT] the Bit Stream Processor (BSP) synchronizes itself to the data transfer 
       on the CAN bus by waiting for Bus_Idle (sequence of 11 consecutive recessive bits) .
       CCCR[CCE] is automatically reset when CCCR[INIT] is reset. */
    /* CCCR_: INIT, CCE, ASM, CSR, MON, DAR, TEST disabled (automated retransmission is enabled) */

    /* #30 check current state: if already reached then avoid asynchronous all */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & kCanCCCR_INIT) != 0UL) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */
    {/* Assure that INIT has been accepted. */}
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    if ( (Cn->CCCR & kCanCCCR_INIT) != 0UL) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    {
      transitionRequest = kCan_30_McanRequested; /* assure start mode request */
    }
  }

  return(transitionRequest);
} /* CanLL_30_Mcan_StartRequest */
/* CODE CATEGORY 4 END */


#if defined(C_30_MCAN_ENABLE_SILENT_MODE) 
/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_StartSilentRequest
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_StartRequest
Relation_Context:
# from CanLL_ModeTransition #
Relation:
OneChOpt
ChannelAmount
SilentMode, HardwareLoopCheck
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StartSilentRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 transitionRequest;
  transitionRequest = kCan_30_McanOk; /* PRQA S 2982 */ /* MD_Can_2982_LL */

  /* #10 requested mode already reached */
  if( ((Cn->CCCR & (kCanCCCR_MON | kCanCCCR_ASM | kCanCCCR_INIT)) == (kCanCCCR_MON | kCanCCCR_ASM)) )   /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
  {
  }
  else
  {
    /* #20 request mode transition if not reached yet */
    /* request RUNNING mode finish Power Down:
       a) Reset CCCR[CSR] (before resetting the CSR bit the module clocks must have been turned on by the application)
       b) M_CAN will acknowledge the reset of the CSR bit by resetting CCCR[CSA]. 
       c) Now the application can reset CCCR[INIT] to restart the CAN communication */
    ApplCan_30_McanClockStart(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);        /* request the application to turn on the clocks (CAN, Host) */
    { /* start in silent mode */
      Cn->CCCR |= kCanCCCR_INIT;                /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      Cn->CCCR |= kCanCCCR_CCE;                 /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
      Cn->CCCR |= kCanCCCR_MON | kCanCCCR_ASM;  /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    }
    
    /* The CCCR[CSR] have been set during the handling of the Erratas */
    /* CCCR[CSR] have to be reset first */
    Cn->CCCR &= (vuint32)~(kCanCCCR_CSR); /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    Cn->CCCR &= (vuint32)~(kCanCCCR_INIT); /* SBSW_CAN_LL_100 */ /* PRQA S 0303 */ /* MD_Can_HwAccess */

    /* To leave power down mode, the application has to turn on the module clocks before resetting CCCR.CSR. 
       MCAN will acknowledge this by resetting CCCR.CSA. 
       Afterwards, the application can restart CAN communication by resetting bit CCCR.INIT. */
    /* After resetting CCCR[INIT] the Bit Stream Processor (BSP) synchronizes itself to the data transfer
       on the CAN bus by waiting for Bus_Idle (sequence of 11 consecutive recessive bits) .
       CCCR[CCE] is automatically reset when CCCR[INIT] is reset. */
    /* CCCR_: INIT, CCE, ASM, CSR, MON, DAR, TEST disabled (automated retransmission is enabled) */

    /* #30 check current state: if already reached then avoid asynchronous all */
    CanLL_30_Mcan_ApplCanTimerStart(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    while( ((Cn->CCCR & (vuint32)(kCanCCCR_MON | kCanCCCR_ASM | kCanCCCR_INIT)) != (kCanCCCR_MON | kCanCCCR_ASM)) && (CanLL_30_Mcan_ApplCanTimerLoop(kCan_30_McanLoopInit) !=  CAN_NOT_OK) ) /* PRQA S 1881,4558,3415,0303 */ /* MD_MSR_AutosarBoolean,MD_Can_4558_RHsideEffect,MD_Can_4558_RHsideEffect,MD_Can_HwAccess */ /* COV_CAN_HW_SPECIFIC */ 
    {/* Assure that INIT/SILENT has been accepted. */}
    CanLL_30_Mcan_ApplCanTimerEnd(kCan_30_McanLoopInit); /* SBSW_CAN_LL_101 */  
    if( ((Cn->CCCR & (kCanCCCR_MON | kCanCCCR_ASM | kCanCCCR_INIT)) != (kCanCCCR_MON | kCanCCCR_ASM)) )   /* COV_CAN_HARDWARE_FAILURE */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    {
      transitionRequest = kCan_30_McanRequested; /* assure silent mode request */
    }
  }

  return(transitionRequest);
} /* CanLL_30_Mcan_StartSilentRequest */
/* CODE CATEGORY 4 END */
#endif

/* CODE CATEGORY 4 START */
/****************************************************************************
| NAME:             CanLL_30_Mcan_StopRequest
****************************************************************************/
/*
|<DataModelStart>| CanLL_30_Mcan_StopRequest
Relation_Context:
# from CanLL_ModeTransition #
Relation:
OneChOpt
ChannelAmount
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StopRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 transitionRequest;
  transitionRequest = kCan_30_McanFailed; /* PRQA S 2982 */ /* MD_Can_2982_LL */

  /* #10 check current state */
  if( (Cn->CCCR & kCanCCCR_INIT) == 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */
  { /* in normal operating mode */
    Cn->TXBCR = kCan_ALL_ONE;   /* SBSW_CAN_LL_100 */ /* cancel any pending request */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
    /* While CCCR[INIT] is set, message transfer from and to the CAN bus is stopped, the status of the CAN bus transmit output is recessive (HIGH). 
       Setting CCCR[INIT] does not change any configuration register. 
       After resetting CCCR[INIT] the Bit Stream Processor (BSP) synchronizes itself to the data transfer on the CAN bus 
       by waiting for the occurrence of a sequence of 11 consecutive recessive bits (= Bus_Idle) before it can take part in bus activities and start the message transfer. */
#if ( CAN_BOSCH_ERRATUM_008 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
    /* When CCCR.INIT is set while the M_CAN is receiving a frame, the next received frame         
       after resetting CCCR.INIT will cause IR.MRAF to be set.
        Workaround:
        1) Issue a clock stop request by setting bit CCCR.CSR
        2) Wait until the M_CAN sets CCCR.INIT and CCCR.CSA to one
           Before resetting CCCR.INIT first reset CCCR.CSR. */
#endif
    /* #20 request mode transition if not reached yet */
    /* Put HW to halt mode, if it is not already there */
    /*  Power down:
        The M_CAN can be set into power down mode via CCCR[CSR]. 
        When clock stop is requested (CCCR[CSR]='1') first INIT and then CSA will be set after all pending transfer requests are completed and the CAN bus reached idle.
        1)  As long as the clock stop request signal is active, bit CCCR[CSR] is read as one. 
        1a) When all pending transmission requests have completed, 
        1b) then M_CAN waits until bus idle state is detected. 
        2)  The M_CAN sets CCCR[INIT] to one to prevent any further CAN transfers. 
        3)  Now M_CAN acknowledges that it is ready for power down by setting CCCR[CSA] to one. 
            In this state, before the clocks are switched off, further register accesses can be made. 
            A write access to CCCR[INIT] will have no effect. 
        4)  Now the module clock inputs (CAN clock and host clock) may be switched off. 
        5)  To leave power down mode, the application has to turn on the module clocks before resetting CCCR[CSR]. 
        5a) The M_CAN will acknowledge this by resetting CCCR[CSA]. 
        6)  Afterwards, the application can restart CAN communication by resetting bit CCCR[INIT]. */
#if ( CAN_BOSCH_ERRATUM_008 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
    Cn->CCCR |= kCanCCCR_CSR;   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
    /*  When clock stop is requested, first INIT then CSA will be set 
        after all pending transfer requests have been completed and the CAN bus reached idle. */
    if((Cn->CCCR & kCanCCCR_CSA) != kCanCCCR_CSA) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#else
    Cn->CCCR |= kCanCCCR_INIT;   /* SBSW_CAN_LL_100 */    /* PRQA S 0303 */ /* MD_Can_HwAccess */
    if((Cn->CCCR & kCanCCCR_INIT) != kCanCCCR_INIT) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 0303 */ /* MD_Can_HwAccess */
#endif
    { /* Set clock stop request, then wait for acknowledge (CSA) */
      transitionRequest = kCan_30_McanRequested;
    }
    else
    { /* Already in sleep mode. Nothing to be done */
      transitionRequest = kCan_30_McanOk;
    }
  }
  else
  { /* Already in stop mode */
    transitionRequest = kCan_30_McanOk;
  }
  return(transitionRequest);
} /* CanLL_30_Mcan_StopRequest */
/* CODE CATEGORY 4 END */

#if defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/****************************************************************************
| NAME:             CanHL_30_Mcan_TxConfirmationPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_TxConfirmationPolling
Relation_Context:
# from CanLL_30_Mcan_TxProcessPendings #
TxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_TxConfirmationPolling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle mailboxHandle, Can_30_McanObjectHandle mailboxElement, Can_30_McanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. (avoid nested call of confirmation (individual polling) and CancelTx interrupt confirmation out of Can interrupt like TP) */
  Can_30_Mcan_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_30_Mcan_TxConfirmation() for handling */
  CanHL_30_Mcan_TxConfirmation(CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, mailboxElement, hwObjHandle);
  Can_30_Mcan_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_TxConfirmation
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_TxConfirmation
Relation_Context:
# from CanHL_30_Mcan_TxConfirmationPolling #
# from Tx Interrupt #
TxPolling, IndividualPolling
Relation:
TxHwFifo, GenericConfirmation
DevErrorDetect, TxPolling, OneChOpt
TransmitCancellationAPI
GenericConfirmation, IfTxBuffer
HwCancelTx
GenericConfirmation, MirrorMode
HwCancelTx, TransmitCancellationAPI, GenericConfirmation
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_TxConfirmation( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle mailboxHandle, Can_30_McanObjectHandle mailboxElement, Can_30_McanObjectHandle hwObjHandle )
{
  /* \trace SPEC-1574 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCan_30_McanTxConfirmationParaStruct txConfPara;
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
  tCan_30_McanTxConfInfoStruct txConfInfoStruct = {0}; /* init see TAR-171 */
#endif
  CanHookBegin_CanHL_30_Mcan_TxConfirmation();
  errorId = CAN_30_MCAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  txConfPara.mailboxHandle = mailboxHandle;
  txConfPara.mailboxElement = mailboxElement; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
  txConfPara.hwObjHandle = hwObjHandle; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
  txConfPara.txStructConf = &txConfInfoStruct;
#endif
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  /* #10 Check if parameter controller and hwObjHandle is valid (only for Interrupt system, polling do this by caller) */
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( 
#  if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
       ((txConfPara.mailboxHandle < Can_30_Mcan_GetTxFullHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_30_Mcan_GetTxFullHandleStop(canHwChannel))) &&  /* PRQA S 2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
#  endif
       ((txConfPara.mailboxHandle < Can_30_Mcan_GetTxBasicHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_30_Mcan_GetTxBasicHandleStop(canHwChannel))) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduIdType tmp_pdu;
#if defined(C_30_MCAN_ENABLE_CANCEL_SUPPORT_API)
    uint8_least tmp_state;
#endif
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_ReturnType generic_retval;
#endif
#if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
    if (Can_30_Mcan_GetMailboxType(txConfPara.mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #110 in case of Fifo element get the read index */
      txConfPara.mailboxElement = CanHL_30_Mcan_GetNextTxHwFifoReadIndex(&txConfPara); /* SBSW_CAN_HL45 */
    }
#endif
    txConfPara.activeSendObject = CanHL_30_Mcan_GetActiveSendObject(txConfPara.mailboxHandle, txConfPara.mailboxElement); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    {
      /* #120 Pre Release HW transmit object (LL) */
      CanLL_30_Mcan_TxConfBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
      /* #130 Remember PDU for confirmation parameter */
      tmp_pdu   = Can_30_Mcan_GetActiveSendPdu(txConfPara.activeSendObject);
#if defined(C_30_MCAN_ENABLE_CANCEL_SUPPORT_API)
      /* #140 Remember SEND STATE which may be modified due to new transmit call in indication */
      tmp_state = (uint8_least)Can_30_Mcan_GetActiveSendState(txConfPara.activeSendObject);
#endif
      { /* #200 Set send state to free to allow next TX out of confirmation or direct (reload queue) */
        /* #210 Notify the application by call Appl_GenericConfirmation() and CanIf_TxConfirmation() */
        /*      - Appl_GenericConfirmation() if configured and mirror mode is active
                and afterwards depend of return value
                - CanIf_TxConfirmation() if generic confirmation return OK, or no generic is used, and TX is not cancelled */
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API1)
        Can_30_Mcan_SetActiveSendState(txConfPara.activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
        if (Appl_30_Mcan_GenericConfirmation( tmp_pdu ) == CAN_OK)
#elif defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
# if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
        if (Can_30_Mcan_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
        { /* MirrorMode is inactive so call the following CanIf_TxConfirmation() */
          Can_30_Mcan_SetActiveSendState(txConfPara.activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
          generic_retval = CAN_OK;
        }
        else
# endif
        { /* #230 For generic confirmation with API2 copy PDU data as parameter for Appl_GenericConfirmation() */
# if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
          if (Can_30_Mcan_GetMailboxType(txConfPara.mailboxHandle) == CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
          { /* #240 in case of FIFO get data out of Fifo storage */
            Can_PduType canPdu;
#  if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
            uint8 canData[64];
#  else
            uint8 canData[8];
#  endif
            canPdu.sdu = (Can_SduPtrType)canData;
            /* copy temporary to secure data because of incoming can_Write() after free buffer */
            canPdu.id = Can_30_Mcan_GetActiveSendId(txConfPara.activeSendObject); /* PRQA S 4391 */ /* MD_Can_IntegerCast */
            canPdu.length = Can_30_Mcan_GetActiveSendLength(txConfPara.activeSendObject);
#  if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
            canPdu.length = CAN_30_MCAN_HL_MIN((canPdu.length), (sizeof(canData)/sizeof(uint8))); /* CM_CAN_HL33 */ /* COV_CAN_TX_CONF_DATA_FAILURE */
#  endif
            VStdMemCpy((void*)canPdu.sdu, (void*)Can_30_Mcan_GetActiveSendSdu(txConfPara.activeSendObject), canPdu.length); /* SBSW_CAN_HL56 */ /* PRQA S 0314,0316 */ /* MD_Can_PointerVoidCast */
            canPdu.swPduHandle = Can_30_Mcan_GetActiveSendPdu(txConfPara.activeSendObject);
            Can_30_Mcan_SetActiveSendState(txConfPara.activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
            /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
            generic_retval = Appl_30_Mcan_GenericConfirmation( (uint8)channel, &canPdu ); /* SBSW_CAN_HL32 */
          }
          else
# endif
          { /* #250 in case of none FIFO get data out of CAN cell buffer (LL txStructConf) */
            Can_PduType canPdu;
            /* #260 get confirmation data out of hardware */
            CanLL_30_Mcan_TxConfSetTxConfStruct(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
            CanHL_30_Mcan_SetCanPduInfo(&canPdu, &txConfPara); /* SBSW_CAN_HL32 */ /* SBSW_CAN_HL45 */
            canPdu.swPduHandle = tmp_pdu;
            Can_30_Mcan_SetActiveSendState(txConfPara.activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
            /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
            generic_retval = Appl_30_Mcan_GenericConfirmation( (uint8)channel, &canPdu ); /* SBSW_CAN_HL32 */
          }
        }
        /* #300 Appl_GenericConfirmation() decide to call Indication */
        if (generic_retval == CAN_OK)
#else /* no generic confirmation */
        Can_30_Mcan_SetActiveSendState(txConfPara.activeSendObject, kCan_30_McanBufferFree); /* SBSW_CAN_HL04 */
#endif
        {
#if defined(C_30_MCAN_ENABLE_CANCEL_SUPPORT_API)
          /* #310 If TX is SW cancelled call CanIf_CancelTxNotification() */
          if (tmp_state == kCan_30_McanBufferCancelSw) /* COV_CAN_CANCEL_SW_STIMULATION */
          {
            CanIf_30_Mcan_CancelTxNotification(tmp_pdu, FALSE);
          }
          else
#endif  /* #320 otherwise call CanIf_TxConfirmation() */
          {
            CanIf_30_Mcan_TxConfirmation(tmp_pdu); /* \trace SPEC-1726, SPEC-1571 */
          }
        }
#if (defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API1) || defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)) && (CAN_30_MCAN_TRANSMIT_BUFFER == STD_ON)
        /* #350 otherwise no CanIf_TxConfirmation() will be called so call CanIf_CancelTxNotification() just to notify IF to restart sending out of Queue */
        else
        {
# if defined(C_30_MCAN_ENABLE_CANCEL_SUPPORT_API)
          CanIf_30_Mcan_CancelTxNotification( tmp_pdu, FALSE );
# else
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# endif
        }
#endif
      }
      /* #500 Post release HW transmit object (LL) */
      CanLL_30_Mcan_TxConfEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
# if !defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_TXCNF_ID, errorId);
  }
# endif
#endif
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CanHookEnd_CanHL_30_Mcan_TxConfirmation();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
/****************************************************************************
| NAME:             CanHL_30_Mcan_GetNextTxHwFifoReadIndex
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_GetNextTxHwFifoReadIndex
Relation_Context:
# from CanHL_30_Mcan_TxConfirmation #
TxHwFifo
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_STATIC, Can_30_McanObjectHandle, STATIC_CODE) CanHL_30_Mcan_GetNextTxHwFifoReadIndex(CanTxConfirmationParaStructPtr txConfPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  Can_30_McanObjectHandle mailboxElement;
  uint16 txHwFifo;
  /* #10 need to do the FIFO index access atomic - use EXCLUSIVE_AREA_7 */
  SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_7();
  txHwFifo = Can_30_Mcan_GetMailboxTxHwFifo(txConfPara->mailboxHandle);
# if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
  if (txHwFifo >= (uint16)Can_30_Mcan_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
  {
    txHwFifo = 0u;
  }
# endif
  /* #20 get Fifo element read index */
  mailboxElement = (Can_30_McanObjectHandle)Can_30_Mcan_GetTxHwFifoReadIndex(txHwFifo);
  /* #30 move to next Fifo element read index */
  if (Can_30_Mcan_GetTxHwFifoReadIndex(txHwFifo) < ((uint16)Can_30_Mcan_GetMailboxSize(txConfPara->mailboxHandle) - (uint16)1u) ) /* CM_CAN_HL25 */
  {
    Can_30_Mcan_IncTxHwFifoReadIndex(txHwFifo); /* SBSW_CAN_HL50 */
  }
  else
  {
    Can_30_Mcan_SetTxHwFifoReadIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
  }
  Can_30_Mcan_DecTxHwFifoFillCount(txHwFifo); /* SBSW_CAN_HL50 */
  SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_7();
  return mailboxElement;
}

/****************************************************************************
| NAME:             CanHL_30_Mcan_SetNextTxHwFifoWriteIndex
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_SetNextTxHwFifoWriteIndex
Relation_Context:
# from CanHL_30_Mcan_WriteStart #
TxHwFifo
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_SetNextTxHwFifoWriteIndex(CanTxTransmissionParaStructPtr txPara) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  uint16 txHwFifo;
  /* #10 need to do the FIFO index access atomic - use EXCLUSIVE_AREA_7 */
  SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_7();
  txHwFifo = Can_30_Mcan_GetMailboxTxHwFifo(txPara->mailboxHandle);
# if (CAN_30_MCAN_SAFE_BSW == STD_ON) /* COV_CAN_30_MCAN_SAFE_BSW */
  if (txHwFifo >= (uint16)Can_30_Mcan_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
  {
    txHwFifo = 0u;
  }
# endif
  /* #30 move to next Fifo element write index */
  Can_30_Mcan_IncTxHwFifoFillCount(txHwFifo); /* SBSW_CAN_HL50 */
  if (Can_30_Mcan_GetTxHwFifoWriteIndex(txHwFifo) < ((uint16)Can_30_Mcan_GetMailboxSize(txPara->mailboxHandle) - (uint16)1u) )
  {
    Can_30_Mcan_IncTxHwFifoWriteIndex(txHwFifo); /* SBSW_CAN_HL50 */
  }
  else
  {
    Can_30_Mcan_SetTxHwFifoWriteIndex(txHwFifo,0); /* SBSW_CAN_HL50 */
  }
  SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_7();
}
#endif

#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
/****************************************************************************
| NAME:             CanHL_30_Mcan_SetCanPduInfo
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_SetCanPduInfo
Relation_Context:
# from CanHL_30_Mcan_TxConfirmation #
GenericConfirmation
Relation:
IDType
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_SetCanPduInfo(Can_30_Mcan_PduInfoPtrType_var PduInfo, CanTxConfirmationParaStructPtr txConfPara) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */ /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* #10 set data pointer */
  PduInfo->sdu = (Can_SduPtrType) txConfPara->txStructConf->pChipData; /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL46 */
  /* #20 set data length */
  PduInfo->length = Can_30_McanTxActualDLC(txConfPara->txStructConf); /* SBSW_CAN_HL46 */
  /* #30 set ID */
# if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
#  if defined(C_30_MCAN_ENABLE_MIXED_ID)
  if ( Can_30_McanTxActualIdType(txConfPara->txStructConf) == kCan_30_McanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* Mixed ID */
    PduInfo->id = (Can_IdType)Can_30_McanTxActualStdId(txConfPara->txStructConf); /* PRQA S 4391 */ /* MD_Can_IntegerCast */ /* SBSW_CAN_HL46 */
  }
  else
#  endif  /* pure Extended ID */
  { /* Extended ID */
    PduInfo->id = (Can_IdType)(Can_30_McanTxActualExtId(txConfPara->txStructConf) | CAN_30_MCAN_ID_IDE_MASK); /* SBSW_CAN_HL46 */
  }
# else    /* Standard ID */
  PduInfo->id = Can_30_McanTxActualStdId(txConfPara->txStructConf); /* SBSW_CAN_HL46 */
# endif
# if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
  if ( Can_30_McanTxActualFdType(txConfPara->txStructConf) == kCan_30_McanFdTypeFd )
  {
    PduInfo->id |= (Can_IdType)CAN_30_MCAN_ID_FD_MASK; /* SBSW_CAN_HL46 */
  }
# endif
  PduInfo->id &= CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT; /* SBSW_CAN_HL46 */
}
#endif


#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_30_Mcan_BasicCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_BasicCanMsgReceivedPolling
Relation_Context:
# from CanLL_30_Mcan_RxBasicProcessPendings #
RxBasicCANSupport
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_BasicCanMsgReceivedPolling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_30_Mcan_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_30_Mcan_BasicCanMsgReceived() for handling */
  CanHL_30_Mcan_BasicCanMsgReceived( CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_30_Mcan_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_BasicCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_BasicCanMsgReceived
Relation_Context:
# from CanHL_30_Mcan_BasicCanMsgReceivedPolling #
RxBasicCANSupport
# from Rx Interrupt #
Relation:
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_BasicCanMsgReceived( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCan_30_McanRxBasicParaStruct rxBasicPara;
  CanHookBegin_CanHL_30_Mcan_BasicCanMsgReceived();
  errorId = CAN_30_MCAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  rxBasicPara.mailboxHandle = rxMailboxHandle;
  rxBasicPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON) && !defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING)
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif 
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanLL_30_Mcan_RxBasicMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_30_Mcan_RxBasicMsgReceivedBegin(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &rxBasicPara) == kCan_30_McanOk) /* SBSW_CAN_HL26 */ /* COV_CAN_RxBasicMsgReceivedBegin */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
    {
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
      /* -------------------------- RAM check failed --- */
      if ((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) != CAN_30_MCAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
# if defined(C_30_MCAN_ENABLE_OVERRUN)
#  if !defined(C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS) /* COV_CAN_OVERRUN_IN_STATUS */
#  endif
# endif
        /* \trace SPEC-1346 */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxBasicPara.rxStruct.localDlc = Can_30_McanRxActualDLC((&(rxBasicPara.rxStruct)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
#  if defined(C_30_MCAN_ENABLE_MIXED_ID)
          if ( Can_30_McanRxActualIdType((&(rxBasicPara.rxStruct))) == kCan_30_McanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)Can_30_McanRxActualStdId((&(rxBasicPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)(Can_30_McanRxActualExtId((&(rxBasicPara.rxStruct))) | CAN_30_MCAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxBasicPara.rxStruct.localId = Can_30_McanRxActualStdId((&(rxBasicPara.rxStruct)));
# endif
# if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
            if ( Can_30_McanRxActualFdType((&(rxBasicPara.rxStruct))) == kCan_30_McanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxBasicPara.rxStruct.localId |= (Can_IdType)CAN_30_MCAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((Can_30_McanRxActualFdType((&(rxBasicPara.rxStruct))) != kCan_30_McanFdTypeFd) && (rxBasicPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING) || defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING))
            /* #140 Check HRH is BasicCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxBasicPara.mailboxHandle < Can_30_Mcan_GetRxBasicHandleStart(canHwChannel)) ||
                 (rxBasicPara.mailboxHandle >= Can_30_Mcan_GetRxBasicHandleStop(canHwChannel)) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_HANDLE;
            } 
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox (MAX over all PDU for this mailbox) */
            if (rxBasicPara.rxStruct.localDlc > CAN_30_MCAN_MAX_DATALEN_OBJ(rxBasicPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_30_Mcan_RxMsgReceivedNotification() */
              rxBasicPara.rxStruct.localMailboxHandle = rxBasicPara.mailboxHandle;
              errorId = CanHL_30_Mcan_RxMsgReceivedNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(rxBasicPara.rxStruct)); /* SBSW_CAN_HL26 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_30_Mcan_RxBasicMsgReceivedEnd() */
    CanLL_30_Mcan_RxBasicReleaseObj(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
    CanLL_30_Mcan_RxBasicMsgReceivedEnd(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_30_Mcan_BasicCanMsgReceived();
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_30_Mcan_FullCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_FullCanMsgReceivedPolling
Relation_Context:
# from CanLL_30_Mcan_RxFullProcessPendings #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_FullCanMsgReceivedPolling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_30_Mcan_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_30_Mcan_FullCanMsgReceived() for handling */
  CanHL_30_Mcan_FullCanMsgReceived( CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_30_Mcan_EnableControllerInterrupts((uint8)channel);
}
# endif

/****************************************************************************
| NAME:             CanHL_30_Mcan_FullCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_FullCanMsgReceived
Relation_Context:
# from CanLL_30_Mcan_FullCanMsgReceivedPolling #
RxFullCANSupport
# from Rx Interrupt #
Relation:
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_FullCanMsgReceived( CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCan_30_McanRxFullParaStruct rxFullPara;
  CanHookBegin_CanHL_30_Mcan_FullCanMsgReceived();
  errorId = CAN_30_MCAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  rxFullPara.mailboxHandle = rxMailboxHandle;
  rxFullPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
#   if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanLL_30_Mcan_RxFullMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_30_Mcan_RxFullMsgReceivedBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara) == kCan_30_McanOk) /* SBSW_CAN_HL27 */ /* COV_CAN_RxFullMsgReceivedBegin */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
    {
  /* -------------------------- RAM check failed --- */
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
      if ((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) != CAN_30_MCAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
        /* -------------------------- Overrun --- */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxFullPara.rxStruct.localDlc = Can_30_McanRxActualDLC((&(rxFullPara.rxStruct)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_30_MCAN_ENABLE_EXTENDED_ID)
#  if defined(C_30_MCAN_ENABLE_MIXED_ID)
          if ( Can_30_McanRxActualIdType((&(rxFullPara.rxStruct))) == kCan_30_McanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxFullPara.rxStruct.localId = (Can_IdType)Can_30_McanRxActualStdId((&(rxFullPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxFullPara.rxStruct.localId = (Can_IdType)(Can_30_McanRxActualExtId((&(rxFullPara.rxStruct))) | CAN_30_MCAN_ID_IDE_MASK);
          }
# else 
          rxFullPara.rxStruct.localId = Can_30_McanRxActualStdId((&(rxFullPara.rxStruct)));
# endif
          { /* ID has valid IdType */
# if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
            if ( Can_30_McanRxActualFdType((&(rxFullPara.rxStruct))) == kCan_30_McanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxFullPara.rxStruct.localId |= (Can_IdType)CAN_30_MCAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((Can_30_McanRxActualFdType((&(rxFullPara.rxStruct))) != kCan_30_McanFdTypeFd) && (rxFullPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) || defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING)) /* COV_CAN_RX_FULLCAN_POLLING */
            /* #140 Check HRH is FullCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxFullPara.mailboxHandle < Can_30_Mcan_GetRxFullHandleStart(canHwChannel)) ||
                 (rxFullPara.mailboxHandle >= Can_30_Mcan_GetRxFullHandleStop(canHwChannel)) )  /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_HANDLE;
            }
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox */
            if (rxFullPara.rxStruct.localDlc > CAN_30_MCAN_MAX_DATALEN_OBJ(rxFullPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_30_MCAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_30_Mcan_RxMsgReceivedNotification() */
              rxFullPara.rxStruct.localMailboxHandle = rxFullPara.mailboxHandle;
              errorId = CanHL_30_Mcan_RxMsgReceivedNotification(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &(rxFullPara.rxStruct)); /* SBSW_CAN_HL27 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_30_Mcan_RxFullMsgReceivedEnd() */
    CanLL_30_Mcan_RxFullReleaseObj(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
    CanLL_30_Mcan_RxFullMsgReceivedEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_30_Mcan_FullCanMsgReceived();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_30_Mcan_ErrorHandling
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_ErrorHandling
Relation_Context:
# from Can_30_Mcan_MainFunction_BusOff() #
StatusPolling
# from BusOff Interrupt #
StatusPolling
Relation:
DevErrorDetect, StatusPolling, OneChOpt
Overrun
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_ErrorHandling( CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_30_MCAN_ENABLE_ERROR_POLLING) /* COV_CAN_ERROR_POLLING */
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit */
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Pre Error handling (LL) */
    CanLL_30_Mcan_ErrorHandlingBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
    /* #30 Check if Transition to error state passive occured (LL) */
    if (CanLL_30_Mcan_ErrorStatePassiveTransitionOccured(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue)
    {
      uint16 rxErrorCount; /* ESCAN00110429 */
      uint16 txErrorCount;
      /* #35 Report the Rx/Tx error counters */
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
      rxErrorCount = Can_30_McanRxActualErrorCounter();
      txErrorCount = Can_30_McanTxActualErrorCounter();
# else
      rxErrorCount = Can_30_McanRxActualErrorCounter(channel);
      txErrorCount = Can_30_McanTxActualErrorCounter(channel);
# endif
      CanHL_30_Mcan_ControllerErrorStatePassive(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST rxErrorCount, txErrorCount);
    }
    /* #40 Error Notification Handling (LL) */
    CanLL_30_Mcan_ErrorNotificationHandling(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
#endif
    if ( (CanLL_30_Mcan_BusOffOccured(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue) && (!Can_30_Mcan_IsIsBusOff(channel) /* avoid repeated call */)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      /* #90 EXCLUSIVE_AREA_6 secure mode changes */
      SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
      /* #100 BUSOFF occur -> ECU Manager restart Controller (no ResetBusOffStart/End needed) */
      Can_30_Mcan_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */
      /* #110 ResetBusOffStart need when BUSOFF handled by Application */
      (void)CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCan_30_McanModeResetBusOffStart, kCan_30_McanContinueBusOffRecovery, kCan_30_McanSuppressRamCheck);
      /* #115 Controller is in STOP mode after ResetBusOffStart \trace SPEC-1578, SPEC-1664, SPEC-1663 */
      /* #120 Status changed to STOP - no more call of STOP from CAN Interface */
      Can_30_Mcan_SetLogStatus(channel, (uint8)((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_MASK_NOMODE) | CAN_30_MCAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
      SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
      /* #130 notify higher layer by call CanIf_ControllerBusOff() \trace SPEC-1726, SPEC-1578 */
      CanIf_30_Mcan_ControllerBusOff((uint8)Can_30_Mcan_GetCanToCanIfChannelMapping(channel));
    }
#if defined(C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS) /* COV_CAN_OVERRUN_IN_STATUS */
    /* #135 check for status register (overrun occur) */
# if defined(C_30_MCAN_ENABLE_OVERRUN) && defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
    /* #140 notify BasicCAN overrun DET or Appl_CanOverrun() */
    if (CanLL_30_Mcan_RxBasicCanOverrun(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue)
    {
#  if (CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_DET)
      errorId = CAN_30_MCAN_E_DATALOST; /* \trace SPEC-1686 */
#  else /* CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_APPL */
      Appl_30_Mcan_CanOverrun( (uint8)channel );
#  endif
    }
# endif
#endif
    /* #200 Post Error handling (LL) */
    CanLL_30_Mcan_ErrorHandlingEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_CTRBUSOFF_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
/****************************************************************************
| NAME:             CanHL_30_Mcan_ControllerErrorStatePassive
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_ControllerErrorStatePassive
Relation_Context:
# from CanHL_30_Mcan_ErrorHandling() #
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_ControllerErrorStatePassive( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint16 RxErrorCounter, uint16 TxErrorCounter )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Notify passive state to the CanIf and pass on the error counters */
  CanIf_ControllerErrorStatePassive(channel, RxErrorCounter, TxErrorCounter);
}

/****************************************************************************
| NAME:             CanHL_30_Mcan_ErrorNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_30_Mcan_ErrorNotification
Relation_Context:
# from CanLL_30_Mcan_ErrorNotificationHandling() #
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_ErrorNotification( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST Can_ErrorType CanError ) /* PRQA S 3219 */ /* MD_Can_HL_UnusedFunction */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Notify the error to CanIf */
  CanIf_ErrorNotification(channel, CanError);
}
#endif /* CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING */


#define CAN_30_MCAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*-------------------------------------------------------------------------*/

#define CAN_30_MCAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (CAN_30_MCAN_VERSION_INFO_API == STD_ON) /* \trace SPEC-1716 */
/****************************************************************************
| NAME:             Can_30_Mcan_GetVersionInfo
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetVersionInfo
Relation_Context:
VersionInfoApi
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_GetVersionInfo( Can_30_Mcan_VersionInfoPtrType VersionInfo )
{ /* \trace SPEC-1723 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter versionInfo is an illegal null pointer \trace SPEC-1721 */
  if (VersionInfo == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
# endif
  { /* #100 copy version info to given pointer parameter \trace SPEC-1717 */
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID   = CAN_30_MCAN_VENDOR_ID; /* SBSW_CAN_HL10 */
    VersionInfo->moduleID   = CAN_30_MCAN_MODULE_ID; /* SBSW_CAN_HL10 */
    VersionInfo->sw_major_version = (uint8)CAN_30_MCAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_minor_version = (uint8)CAN_30_MCAN_SW_MINOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_patch_version = (uint8)CAN_30_MCAN_SW_PATCH_VERSION; /* SBSW_CAN_HL10 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_VERSION_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

/****************************************************************************
| NAME:             Can_30_Mcan_InitMemory
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_InitMemory
Relation_Context:
Relation:
Variant
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_InitMemory( void )
{ /* BR:011 */
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 mark driver as uninitialized \trace SPEC-1650 */
  can_30_McanConfigInitFlag = CAN_30_MCAN_STATUS_UNINIT;
#if defined(CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER)
  /* #20 reset global configuration pointer */
  Can_30_Mcan_ConfigDataPtr = NULL_PTR;
#endif /* otherwise constant pointer is used */
  /* #30 HW reset memory */
  CanLL_30_Mcan_InitMemoryPowerOn(); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
#if(CAN_30_MCAN_DEV_ERROR_DETECT == STD_OFF)
  CAN_30_MCAN_DUMMY_STATEMENT(can_30_McanConfigInitFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}


#if ((CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_30_MCAN_SET_BAUDRATE_API == STD_OFF))
/****************************************************************************
| NAME:             Can_30_Mcan_ChangeBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_ChangeBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_ChangeBaudrate( uint8 Controller, V_DEF_30_MCAN_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20314 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_30_MCAN_E_PARAM_BAUDRATE; /* explicit default as Issue - remove when baud rate fit */ /* \trace SPEC-20321 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-20338 */
  if ( can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT )
  {
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCan_30_McanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-20331 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_STOP) != CAN_30_MCAN_STATUS_STOP )
  { /* \trace SPEC-1655, SPEC-20312 */
    errorId = CAN_30_MCAN_E_TRANSITION;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_30_Mcan_GetInitObjectStartIndex(channel); baudrateIndex < Can_30_Mcan_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_30_Mcan_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 set baud rate and reinitialize controller to activate baud rate \trace SPEC-1669 */
        uint8 transitionState;
        Can_30_Mcan_SetLastInitObject(channel, (uint8)baudrateIndex); /* SBSW_CAN_HL11 */
        transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST kCan_30_McanModeStopReinit, kCan_30_McanFinishBusOffRecovery, kCan_30_McanSuppressRamCheck);
        if (transitionState == kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */
        { /* #50 check transition STOP (Reinit) is successful */
          Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
        }
        retval = E_OK;
        errorId = CAN_30_MCAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_CHANGE_BR_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_30_Mcan_CheckBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_CheckBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_CheckBaudrate( uint8 Controller, V_DEF_30_MCAN_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20311 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_30_MCAN_E_PARAM_BAUDRATE; /* \trace SPEC-20317 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT \trace SPEC-20328, SPEC-20318 */
  if ( can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT )
  {
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCan_30_McanNumberOfChannels )
  { /* \trace SPEC-20335 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_30_Mcan_GetInitObjectStartIndex(channel); baudrateIndex < Can_30_Mcan_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_30_Mcan_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 requested baud rate is set - return OK */
        retval = E_OK;
        errorId = CAN_30_MCAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_CHECK_BR_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif /* CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON */

#if (CAN_30_MCAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_30_Mcan_SetBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_SetBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{ /* \trace SPEC-50605 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  /* #5 return E_NOT_OK in case no fitting baudrate is found */
  retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-50595 */
  if ( can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT )
  {
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCan_30_McanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-50587 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_STATUS_STOP) != CAN_30_MCAN_STATUS_STOP )
  { /* \trace SPEC-50584 */
    errorId = CAN_30_MCAN_E_TRANSITION;
  }
  else
  if ( BaudRateConfigID >= (uint16)(Can_30_Mcan_GetInitObjectStartIndex(channel + 1u) - Can_30_Mcan_GetInitObjectStartIndex(channel)) ) /* PRQA S 4391 */ /* MD_Can_IntegerCast */
  { /* \trace SPEC-50625, SPEC-50563 */
    errorId = CAN_30_MCAN_E_PARAM_BAUDRATE;
  }
  else
# endif
  { /* #50 set baud rate and reinitialize controller to activate baud rate */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    Can_30_Mcan_SetLastInitObject(channel, (uint8)(Can_30_Mcan_GetInitObjectStartIndex(channel) + BaudRateConfigID)); /* SBSW_CAN_HL11 */
    transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST kCan_30_McanModeStopReinit, kCan_30_McanFinishBusOffRecovery, kCan_30_McanSuppressRamCheck);
    /* #60 check if hardware cancellation appear while mode change, so for the baud rate set is not successful \trace SPEC-60434 */
    if (transitionState == kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */
    {
      retval = E_OK;
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_SET_BR_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CAN_30_MCAN_SET_BAUDRATE_API == STD_ON */

/****************************************************************************
| NAME:             Can_30_Mcan_Init
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_Init
Relation_Context:
Relation:
Variant, DevErrorDetect
RxQueue
OneChOpt
Variant
Wakeup
MirrorMode
SilentMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_Init( Can_30_Mcan_ConfigPtrType ConfigPtr ) /* PRQA S 3206 */ /* MD_MSR_DummyStmt */
{ /* \trace SPEC-1587, SPEC-1708 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_30_Mcan_Init();
  errorId = CAN_30_MCAN_E_NO_ERROR;
#if defined(CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER) /* PostBuild (load+sel) */
  Can_30_Mcan_ConfigDataPtr = ConfigPtr; /* \trace SPEC-1394, SPEC-1575 */
# if defined(CAN_30_MCAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* PostBuildLoadable */
  if (ConfigPtr == NULL_PTR)
  { /* #10 EcuM null pointer configuration check and notification */
    EcuM_BswErrorHook((uint16) CAN_30_MCAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
  }
  else
#  if (CAN_30_MCAN_FINALMAGICNUMBER == STD_ON) /* COV_CAN_FINALMAGICNUMBER */
  if (Can_30_Mcan_GetFinalMagicNumber() != 20510u) /* COV_CAN_GENDATA_FAILURE */
  { /* #20 EcuM wrong magic number check and notification */
    EcuM_BswErrorHook((uint16) CAN_30_MCAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
#  endif
# else
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #30 Check if all parameters are valid \trace SPEC-1724 */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
#  endif
# endif
#else
  CAN_30_MCAN_DUMMY_STATEMENT(ConfigPtr);  /* PRQA S 1338, 2982, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
  ConfigPtr = Can_30_Mcan_ConfigDataPtr;  /* PRQA S 2983,1338 */ /* MD_MSR_DummyStmt */
# endif
#endif /* CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag != CAN_30_MCAN_STATUS_UNINIT)
  {
    /* #60 Check already initialized -> 2nd call is not allowed \trace SPEC-1712, SPEC-1722 */
    errorId = CAN_30_MCAN_E_TRANSITION;
  }
  else
#endif
  if (  ( Can_30_Mcan_GetBaseDll_GeneratorVersion()     != (uint16)CAN_30_MCAN_GEN_BASE_CFG5_VERSION ) ||  /* PRQA S 2742 */ /* MD_Can_ConstValue */
        ( Can_30_Mcan_GetPlatformDll_GeneratorVersion() != (uint16)CAN_30_MCAN_GEN_Mpc5700McanAsr_VERSION ) ) /* COV_CAN_GENDATA_FAILURE */
  {
    /* #70 EcuM generator and compatibility version check and notification */
#if defined(CAN_30_MCAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* not for PostBuildSelectable */
    EcuM_BswErrorHook((uint16) CAN_30_MCAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#else
    errorId = CAN_30_MCAN_E_UNINIT; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#endif
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    {
      can_30_McanIsRxTaskLocked = kCan_30_McanFalse;
#if defined(C_30_MCAN_ENABLE_RX_QUEUE)
      /* #110 delete RxQueue (all channels) */
      Can_30_Mcan_GetRxQueueInfo().WriteIndex = 0u;  /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
      Can_30_Mcan_GetRxQueueInfo().ReadIndex = 0u; /* SBSW_CAN_HL55 */
      Can_30_Mcan_GetRxQueueInfo().Count = 0u; /* SBSW_CAN_HL55 */
#endif
      /* #120 Set active Identity */
      /* #130 HW specific power on (LL) */
      if (CanLL_30_Mcan_InitPowerOn() == kCan_30_McanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
      {
        can_30_McanConfigInitFlag = CAN_30_MCAN_STATUS_INIT; /* \trace SPEC-1648 */ /* before Controller initialization begin */
#if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
        for (channel = 0u; channel < kCan_30_McanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#endif
        { /* #132 for each controller */
#if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
          if ( Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed ) /* COV_CAN_GENDATA_FAILURE */
          { /* #134 not for inactive controller */
            continue;
          }
#endif
          /* #140 initialize start up values for each controllers */
          Can_30_Mcan_SetLogStatus(channel, CAN_30_MCAN_STATUS_UNINIT); /* PowerOn mark */ /* SBSW_CAN_HL02 */
          Can_30_Mcan_SetModeTransitionRequest(channel, kCan_30_McanModeNone); /* SBSW_CAN_HL01 */
          Can_30_Mcan_SetBusOffTransitionRequest(channel, kCan_30_McanFinishBusOffRecovery); /* SBSW_CAN_HL01 */
          Can_30_Mcan_SetRamCheckTransitionRequest(channel, kCan_30_McanSuppressRamCheck); /* SBSW_CAN_HL01 */
          Can_30_Mcan_SetIsBusOff(channel, FALSE);  /* start up: no BUSOFF */ /* SBSW_CAN_HL08 */
          Can_30_Mcan_SetCanInterruptCounter(channel, 0u); /* SBSW_CAN_HL12 */
#if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
          Can_30_Mcan_SetMirrorModeState(channel, CDDMIRROR_INACTIVE); /* SBSW_CAN_HL20 */
#endif
#if defined(C_30_MCAN_ENABLE_SILENT_MODE)
          Can_30_Mcan_SetSilentModeState(channel, CAN_SILENT_INACTIVE); /* SBSW_CAN_HL20 */
#endif
          /* #155 HW channel specific power on */
          if (CanLL_30_Mcan_InitPowerOnChannelSpecific(CAN_30_MCAN_CHANNEL_CANPARA_ONLY) == kCan_30_McanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
          {
            uint8 transitionState;
            /* #160 set baud rate and initialize all CAN controllers \trace SPEC-1587, SPEC-1656 */
            Can_30_Mcan_SetLastInitObject(channel, (uint8)(Can_30_Mcan_GetInitObjectStartIndex(channel) + Can_30_Mcan_GetCanControllerDefaultBaudrateIdx(CAN_30_MCAN_HL_HW_CHANNEL_STARTINDEX(channel)))); /* SBSW_CAN_HL11 */
            transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST kCan_30_McanModeStopReinit, kCan_30_McanFinishBusOffRecovery, kCan_30_McanExecuteRamCheck);
            if (transitionState == kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */
            { /* #170 check transition STOP (Reinit) is successful */
              Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_STATUS_STOP); /* STOP mode reached or issue */ /* SBSW_CAN_HL02 */
            }
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
            else
            {              
              errorId = CAN_30_MCAN_E_TRANSITION;
            }
#endif
          }
        }
      } /* CanLL_30_Mcan_InitPowerOn */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_INIT_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_30_Mcan_Init();
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_SetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_SetControllerMode
Relation_Context:
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
DevErrorDetect, TransitionCheck
RamCheck, ChannelAmount
SilentMode, ChannelAmount
ReInitStart
Wakeup
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{ /* \trace SPEC-1715 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_ReturnType retval;
  uint8 transitionRequest;
  uint8 busOffRecovery;
  uint8 doRamCheck;
  uint8 transitionState;
  CanHookBegin_Can_30_Mcan_SetControllerMode();
  retval = CAN_NOT_OK;  /* \trace SPEC-1407 */ /* For successful transition it is set explicit to CAN_OK */
  transitionState = kCan_30_McanFailed;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Transition is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* \trace SPEC-1731 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1732 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER; /* \trace SPEC3874 */
  }
  else
# endif
#endif
  { /* #50 second level check (modes and transitions) only valid when controller is in active ECU and valid */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
    if (!CanHL_30_Mcan_IsControllerInit(channel))
    { /* #60 Check controller is initialized */
      errorId = CAN_30_MCAN_E_UNINIT;
    }
    else
    if ((!CanHL_30_Mcan_IsStop(channel)) && (Transition == CAN_T_START))
    { /* #70 Check No-STOP -> START-Req is invalid \trace SPEC-1637 */ /* ESCAN00073272 */
      errorId = CAN_30_MCAN_E_TRANSITION;
    }
    else
# if (CAN_30_MCAN_TRANSITION_CHECK == STD_ON)  /* SREQ00000291 */
    if ( ((!CanHL_30_Mcan_IsStop(channel)) && (!CanHL_30_Mcan_IsSleep(channel)) && ((Transition == CAN_T_WAKEUP) || (Transition == CAN_T_SLEEP))) ||
         ((CanHL_30_Mcan_IsSleep(channel)) && (Transition == CAN_T_STOP)) )
    { /* #80 Check  No STOP Nor SLEEP -> SLEEP-Req   or   No SLEEP Nor STOP --> WAKEUP-Req   is invalid \trace SPEC-1654, SPEC-1649 */
      /* #90 Check  No START Nor STOP -> STOP-Req is invalid \trace SPEC-1652 */
      errorId = CAN_30_MCAN_E_TRANSITION;
    }
    else
# endif
#endif
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #95 controller is active (no RAM check issue): */
    if ((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) != CAN_30_MCAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
      SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
      /* #125 HW begin mode transition */
      switch(Transition)
      {
      case CAN_T_START:
        /* #200 Handle --- START --- transition */
        if (Can_30_Mcan_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        { /* #210 BUSOFF occur so finish BUSOFF handling and do START transition inside */
          transitionRequest = kCan_30_McanModeResetBusOffEnd;
        } 
        else
        {
#if defined(C_30_MCAN_ENABLE_SILENT_MODE)
          if (Can_30_Mcan_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
          {
            transitionRequest = kCan_30_McanModeSilent;
          }
          else
#endif
          {
#if (CAN_30_MCAN_REINIT_START == STD_ON)
            transitionRequest = kCan_30_McanModeStartReinit;
#else
            transitionRequest = kCan_30_McanModeStart;
#endif
          }
        }
        busOffRecovery = kCan_30_McanContinueBusOffRecovery;
        doRamCheck = kCan_30_McanSuppressRamCheck;
        transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        if ( transitionState == kCan_30_McanOk ) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
        {
          Can_30_Mcan_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
        }
        CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_START, CANIF_CS_STARTED, transitionState);
        break;

      case CAN_T_STOP:
        /* #300 Handle --- STOP --- transition */
        transitionRequest = kCan_30_McanModeStopReinitFast;
        busOffRecovery = kCan_30_McanContinueBusOffRecovery;
        doRamCheck = kCan_30_McanSuppressRamCheck;
        transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_WAKEUP:
        /* #400 Handle --- WAKEUP --- transition */
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK) && !defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
        if (!CanHL_30_Mcan_IsStop(channel)) { /* do not call RAM_CHECK again in case CanIf call wakeup a second time (buswakeup + stop transition afterwards) */
          /* #415 do standard RAM check CanHL_30_Mcan_DoRamCheck() if controller is not in STOP mode */
          transitionRequest = kCan_30_McanModeStopReinit;
          doRamCheck = kCan_30_McanExecuteRamCheck;
        }
        else
#endif
        {
          transitionRequest = kCan_30_McanModeStopReinitFast;
          doRamCheck = kCan_30_McanSuppressRamCheck;
        }
        {
          busOffRecovery = kCan_30_McanFinishBusOffRecovery;
        }
        transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_SLEEP: /* \trace SPEC-1639 */
        /* #500 Handle --- SLEEP --- transition */
        { /* #520 no WAKEUP-source-ref: do emulated SLEEP mode \trace SPEC-1629, SPEC-1641, SPEC-1645 */
          transitionState = kCan_30_McanOk;
        }
        CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_SLEEP, CANIF_CS_SLEEP, transitionState);
        break;

      default:
        /* #600 check unknown transition, return NOT_OK \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_30_MCAN_E_TRANSITION; /* \trace SPEC-1733, SPEC-1407 */
        break;
      } /* switch */
      SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
    }
  }
  if ( transitionState != kCan_30_McanFailed ) /* COV_CAN_TRANSITION_REQUEST */ /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */
  {
    retval = CAN_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_SETCTR_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_30_Mcan_SetControllerMode();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_DisableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_DisableControllerInterrupts
Relation_Context:
# from Can_30_Mcan_MainFunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_30_Mcan_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_30_Mcan_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_DisableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1746 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* \trace SPEC-1750 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1742 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1750 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_1();
    if (Can_30_Mcan_GetCanInterruptCounter(channel) == 0u)
    { /* #110 Disable only when not disabled before (count nesting) \trace SPEC-1735, SPEC-1745 */
#if (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_DRIVER) || (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      { /* #120 Disable CAN interrupt for each HW channel */
        CanLL_30_Mcan_CanInterruptDisable(CAN_30_MCAN_CHANNEL_CANPARA_FIRST  &Can_30_Mcan_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_HL16 */
      }
#endif
#if (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_APPL) || (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      /* #130 Let application Disable CAN interrupt ApplCanInterruptDisable() */
      Appl_30_McanCanInterruptDisable((uint8)channel);
#endif
    }
    Can_30_Mcan_IncCanInterruptCounter(channel); /* \trace SPEC-1748 */ /* SBSW_CAN_HL12 */
    SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_DIINT_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_EnableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_EnableControllerInterrupts
Relation_Context:
# from Can_30_Mcan_MainFunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_30_Mcan_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_30_Mcan_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt 
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_EnableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1741 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* \trace SPEC-1739 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1752 */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1739 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_1();
    if (Can_30_Mcan_GetCanInterruptCounter(channel) != 0u)
    { /* #110 Enable only when disabled before (count nesting) \trace SPEC-1749, SPEC-1748 */
      Can_30_Mcan_DecCanInterruptCounter(channel); /* SBSW_CAN_HL12 */
      if (Can_30_Mcan_GetCanInterruptCounter(channel) == 0u) /* \trace SPEC-1736, SPEC-1756 */
      {
#if (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_DRIVER) || (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        { /* #120 Disable CAN interrupt for each HW channel */
          CanLL_30_Mcan_CanInterruptRestore(CAN_30_MCAN_CHANNEL_CANPARA_FIRST Can_30_Mcan_GetCanInterruptOldStatus(canHwChannel));
        }
#endif
#if (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_APPL) || (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        /* #130 Let application Enable CAN interrupt ApplCanInterruptRestore() */
        Appl_30_McanCanInterruptRestore((uint8)channel);
#endif
      }
    }
    SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_ENINT_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_Write
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_Write
Relation_Context:
Relation:
DevErrorDetect
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
DevErrorDetect, TxFullCANSupport
DevErrorDetect, CanFdSupport
DevErrorDetect, IDType
RamCheck
UseVectorCanIf
CanFdSupport
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_Write( Can_HwHandleType Hth, Can_30_Mcan_PduInfoPtrType PduInfo )
{ /* \trace SPEC-1751, SPEC-1760, SPEC-1406 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  CanHookBegin_Can_30_Mcan_Write();
  errorId = CAN_30_MCAN_E_NO_ERROR;
  retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* \trace SPEC-1759 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (Hth >= Can_30_Mcan_GetSizeOfMailbox()) {
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
#endif
  {
#if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_30_Mcan_GetMailboxController(Hth);
#endif
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_30_MCAN_E_PARAM_HANDLE;
    }
    else
# endif
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_30_MCAN_E_PARAM_HANDLE;
    }
    else
# endif
    if (!CanHL_30_Mcan_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1407 */
      errorId = CAN_30_MCAN_E_UNINIT;
    }
    else
# if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
    if ((Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_MUX_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
    if ((Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_MUX_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
    { /* \trace SPEC-1763 */
      errorId = CAN_30_MCAN_E_PARAM_HANDLE;
    }
    else
    if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) && (PduInfo->length != 0u)))
    { /* \trace SPEC-1761 */
      errorId = CAN_30_MCAN_E_PARAM_POINTER;
    }
    else
# if !defined(C_30_MCAN_ENABLE_CAN_FD_USED)
    if ( CanHL_30_Mcan_IsFdMessage(PduInfo->id) )
    { /* no CAN_FD: Check parameter PduInfo->id should not have FD bit in ID */
      errorId = CAN_30_MCAN_E_PARAM_POINTER;
    }
    else
# endif
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
    if ( ((PduInfo->length > 8u) && (Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(channel)) == CAN_30_MCAN_NONE)) ||
         (PduInfo->length > CAN_30_MCAN_MAX_DATALEN_OBJ(Hth)) ) /* COV_CAN_GENDATA_FAILURE */
         { /* \trace SPEC-1758 */
      /* \trace SPEC-60433 */ /* CAN_FD: Check parameter PduInfo->length is smaller than 9 for none FD configuration
         If development error detection for the CAN module is enabled and the CAN Controller is not in CAN FD mode (no CanControllerFdBaudrateConfig):
         The function Can_30_Mcan_Write shall raise the error CAN_E_PARAM_DLC and shall return CAN_NOT_OK if the length is more than 8 byte.() */
      /* CAN_FD: Check parameter PduInfo->length against PDU maximum size */
      errorId = CAN_30_MCAN_E_PARAM_DLC;
    }
    else
# else
    if ( PduInfo->length > CAN_30_MCAN_MAX_DATALEN_OBJ(Hth) ) /* CM_CAN_HL20 */
    { /* \trace SPEC-1758 */ /* Check parameter PduInfo->length against maximum buffer size */
      errorId = CAN_30_MCAN_E_PARAM_DLC;
    }
    else
# endif
# if defined(C_30_MCAN_ENABLE_MIXED_ID)
    if ( ((PduInfo->id & (Can_IdType)CAN_30_MCAN_ID_IDE_MASK) != (Can_IdType)CAN_30_MCAN_ID_IDE_MASK ) && ( (PduInfo->id & (Can_IdType)CAN_30_MCAN_ID_MASK) > (Can_IdType)CAN_30_MCAN_ID_MASK_STD ) ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* Check parameter PduInfo->id for STD ID is in STD range (EXT is always in range) */
      errorId = CAN_30_MCAN_E_PARAM_POINTER;
    }
    else
# endif
    if ( (PduInfo->id & (Can_IdType)CAN_30_MCAN_ID_UNUSED_MASK) != (Can_IdType)0UL )
    { /* Check parameter PduInfo->id contains illegal bits (e.g. bigger ID value than MAX for given type) */
      errorId = CAN_30_MCAN_E_PARAM_POINTER;
    }
    else
#endif
    /* ----- Implementation ----------------------------------------------- */
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #150 reject deactivated mailbox (by RamCheck) */
    if (Can_30_Mcan_GetMailboxState(Hth) == kCan_30_McanFailed) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      retval = CAN_NOT_OK;
    }
    else
#endif
    /* #180 check Hardware is in BUSOFF recovery state and is not able to handle a request: return BUSY \trace SPEC-1764 */
    if (Can_30_Mcan_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      retval = CAN_NOT_OK; /* ESCAN00096369 */
    }
    else
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
    /* #200 controller is active (no RAM check issue): */
    if ((Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) != CAN_30_MCAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_HARDWARE_FAILURE */
#endif
    {
      /* #205 temporary pdu buffer to avoid data modification on constant data (modification in generic pretransmit) */
      tCan_30_McanTxTransmissionParaStruct txPara;
      /* #210 EXCLUSIVE_AREA_2: Interrupts may not be locked and re-entrant call may occur. */
      /*                        Time in between ID search and lock of mailbox is critical 
                                (only when no Vector Interface used otherwise CanIf EXCLUSIVE_AREA is used instead) 
                                Can_30_Mcan_Write() could be called re-entrant, there for also for polling systems the interrupts have to be locked  
                                this is essential while check for mailbox is free (in between if (free) and set to not free) and save PDU handle */
#if !defined(CAN_USE_VECTOR_IF)
      SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_2();
#endif
      txPara.mailboxHandle = Hth;
      txPara.hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(Hth); 
      txPara.pdu.id = PduInfo->id;
      txPara.pdu.length = PduInfo->length;
      txPara.pdu.sdu = PduInfo->sdu;
      txPara.pdu.swPduHandle = PduInfo->swPduHandle;
#if defined(C_30_MCAN_ENABLE_CAN_FD_USED)
      if (txPara.pdu.length <= 8u) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if (Can_30_Mcan_GetInitObjectFdBrsConfig(Can_30_Mcan_GetLastInitObject(channel)) == CAN_30_MCAN_NONE)
        { /* #220 remove FD flag when no FD support is activated in this initialization structure and DLC not greater than 8 */
          /* CAN FD also support an extended payload which allows the transmission of up to 64 bytes.
          This feature also depends on the CAN FD configuration (see CanControllerFdBaudrateConfig).
          Therefore, if the CAN FD feature is enabled and the CAN FD flag is set in CanId passed to
           Can_30_Mcan_Write(), CanDrv supports the transmission of PDUs with a length up to 64 bytes.
          If there is a request to transmit a CAN FD frame without the CAN FD feature enabled the
          frame is sent as conventional CAN frame as long as the PDU length <= 8 bytes. */
          txPara.pdu.id = txPara.pdu.id & ((Can_IdType)(CAN_30_MCAN_ID_IDE_MASK | CAN_30_MCAN_ID_MASK)); /* CAN_FD_   mask out the FD bit */
        }
      }
      txPara.fdBrsType = kCan_30_McanFdBrsTypeFalse;
      if (CanHL_30_Mcan_IsFdMessage(txPara.pdu.id))
      {
        txPara.fdType = kCan_30_McanFdTypeFd;
        if (CanHL_30_Mcan_IsFdTxBrs(channel))
        {
          txPara.fdBrsType = kCan_30_McanFdBrsTypeTrue;
        }
      } else {
        txPara.fdType = kCan_30_McanFdTypeClassic;
      }
      txPara.messageLen = txPara.pdu.length;
      txPara.frameLen = CAN_30_MCAN_DLC2LEN(CAN_30_MCAN_LEN2DLC(txPara.messageLen));
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
      txPara.paddingVal = Can_30_Mcan_GetMailboxFdPadding(txPara.mailboxHandle);
# endif
#endif
      /* #230 search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary */
      CanHL_30_Mcan_WritePrepare(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */
      /* #240 start transmission for given handle (if free) and return state */
      retval = CanHL_30_Mcan_WriteStart(CAN_30_MCAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */

#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
      /* avoid change of PDU information due to TX interrupt while changing */
      SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_2();
#endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_WRITE_ID, errorId);
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_30_Mcan_Write();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             ASR4.x - Can_30_Mcan_CheckWakeup
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_CheckWakeup
Relation_Context:
Relation:
Wakeup, DevErrorDetect, OneChOpt
Wakeup, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
#if defined(C_30_MCAN_ENABLE_CHECK_WAKEUP_CAN_RET_TYPE) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_CHECKWAKEUP_RETTYPE Can_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     CAN_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK CAN_NOT_OK
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_CheckWakeup( uint8 Controller )
#else
# define CAN_30_MCAN_CHECKWAKEUP_RETTYPE Std_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     E_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK E_NOT_OK
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_CheckWakeup( uint8 Controller )
#endif
{ /* \trace SPEC-1740 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_30_MCAN_CHECKWAKEUP_RETTYPE retval;
  retval = CAN_CHECKWAKEUP_RETVAL_NOT_OK; /* \trace SPEC-1407 */
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_MainFunction_Write
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_MainFunction_Write
Relation_Context:
Relation:
TxPolling, HwCancelTx, DevErrorDetect
TxPolling, HwCancelTx, OneChOpt
TxPolling, HwCancelTx, Variant
TxPolling, HwCancelTx, Wakeup
TxPolling, IndividualPolling
TxPolling, TxFullCANSupport, IndividualPolling
TxFullCANSupport, HwCancelTx
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_MainFunction_Write( void )
{ /* \trace SPEC-1766 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_30_MCAN_ENABLE_TX_POLLING) 
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  CanHookBegin_Can_30_Mcan_MainFunction_Write();
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_30_Mcan_Write() */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1767 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCan_30_McanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON) /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
      if (!CanHL_30_Mcan_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_30_MCAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_30_Mcan_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          tCan_30_McanTaskParaStruct taskPara;
# if defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #100 do confirmation handling for pending mailboxes */
          if ( CanLL_30_Mcan_TxIsGlobalConfPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #110 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_30_Mcan_GetTxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_30_Mcan_GetTxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #120 iterate over all TxBasicCAN */
              taskPara.hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#  if defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_30_Mcan_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
              { /* #130 is mailbox handled by polling (individual) */
                /* #140 call LL confirmation handling */
                CanLL_30_Mcan_TxProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
# endif
# if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
#  if defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #200 do confirmation handling for pending mailboxes */
          if ( CanLL_30_Mcan_TxIsGlobalConfPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #210 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_30_Mcan_GetTxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_30_Mcan_GetTxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #220 iterate over all TxFullCAN */
              taskPara.hwObjHandle = Can_30_Mcan_GetMailboxHwHandle(taskPara.mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#   if defined(C_30_MCAN_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_30_Mcan_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#   endif
              { /* #230 is mailbox handled by polling (individual) */
                /* #240 call LL confirmation handling */
                CanLL_30_Mcan_TxProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
#  endif
# endif
        } /* !IsSleep */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_MAINFCT_WRITE_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

#else
  CanHookBegin_Can_30_Mcan_MainFunction_Write();
#endif /* C_30_MCAN_ENABLE_TX_POLLING */
  CanHookEnd_Can_30_Mcan_MainFunction_Write();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_MainFunction_Read
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_MainFunction_Read
Relation_Context:
Relation:
DevErrorDetect
RxPolling, OneChOpt
RxPolling, Variant
RxPolling, DevErrorDetect
RxPolling, Wakeup
RxPolling, RxFullCANSupport
RxPolling, RxBasicCANSupport
RxQueue
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_MainFunction_Read( void )
{ /* \trace SPEC-1776 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_30_Mcan_MainFunction_Read();
  errorId = CAN_30_MCAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check Driver is initialized \trace SPEC-1784 */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  {
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  /* #20 semaphore to secure parallel access to RX buffers interrupt or polling \trace SPEC-1569 */
  if ( can_30_McanIsRxTaskLocked == kCan_30_McanFalse )  /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */
  {
#if defined(C_30_MCAN_ENABLE_RX_POLLING) /* COV_CAN_RX_POLLING */
    CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
#endif
    can_30_McanIsRxTaskLocked = kCan_30_McanTrue; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#if defined(C_30_MCAN_ENABLE_RX_POLLING) /* \trace SPEC-1782 */ /* COV_CAN_RX_POLLING */
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCan_30_McanNumberOfChannels; channel++)
# endif
    { /* #30 iterate over all active controller */
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_30_Mcan_IsControllerInit(channel))
      { /* #60 Check controller is initialized */
        errorId = CAN_30_MCAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_30_Mcan_IsSleep(channel) )
        { /* #70 do not access CAN hardware in SLEEP */
          /* #80 over all HW channel \trace SPEC-1774 */
# if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
          /* #90 search for all pending FullCAN mailbox objects and call notification */
          CanHL_30_Mcan_RxFullCanPolling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
          /* #100 search for all pending BasicCAN mailbox objects and call notification */
          CanHL_30_Mcan_RxBasicCanPolling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
# endif
        }
      }
    }
#endif /* C_30_MCAN_ENABLE_RX_POLLING */
#if defined(C_30_MCAN_ENABLE_RX_QUEUE)
    /* #200 execute RxQueue CanHL_30_Mcan_RxQueueExecution() */
    CanHL_30_Mcan_RxQueueExecution(); 
#endif
    can_30_McanIsRxTaskLocked = kCan_30_McanFalse;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_30_Mcan_MainFunction_Read();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_MainFunction_BusOff
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_MainFunction_BusOff
Relation_Context:
Relation:
StatusPolling, DevErrorDetect, ChannelAmount
StatusPolling, OneChOpt
StatusPolling, Variant, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_MainFunction_BusOff( void )
{ /* \trace SPEC-1783 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_30_MCAN_ENABLE_ERROR_POLLING) /* \trace SPEC-1778 */ /* COV_CAN_ERROR_POLLING */
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1780 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCan_30_McanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_30_Mcan_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_30_MCAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_30_Mcan_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          /* #80 disable CAN interrupts */
          Can_30_Mcan_DisableControllerInterrupts((uint8)channel);
          /* #90 call CanHL_30_Mcan_ErrorHandling */
          CanHL_30_Mcan_ErrorHandling( CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY );
          Can_30_Mcan_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_MAINFCT_BO_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#endif /* C_30_MCAN_ENABLE_ERROR_POLLING */
}


/****************************************************************************
| NAME:             Can_30_Mcan_MainFunction_Wakeup
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_MainFunction_Wakeup
Relation_Context:
Relation:
WakeupPolling, Wakeup, DevErrorDetect
WakeupPolling, Wakeup, OneChOpt
WakeupPolling, Wakeup, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_MainFunction_Wakeup( void )
{ /* \trace SPEC-1770 */
  /* ----- Local Variables ---------------------------------------------- */
}

/****************************************************************************
| NAME:             Can_30_Mcan_MainFunction_Mode
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_MainFunction_Mode
Relation_Context:
Relation:
DevErrorDetect
OneChOpt, ChannelAmount
Variant, ChannelAmount
DevErrorDetect, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_MainFunction_Mode( void )
{ /* \trace SPEC-1775 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1779 */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# endif
  { /* #15 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCan_30_McanNumberOfChannels; channel++) /* CM_CAN_HL01 */
# endif
    { /* #20 over all active controller */
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_30_Mcan_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-1779 */
        errorId = CAN_30_MCAN_E_UNINIT;
      }
      else
# endif
      {
        uint8 transitionRequest;
        uint8 busOffRecovery;
        uint8 doRamCheck;
        uint8 transitionState;
        transitionRequest = Can_30_Mcan_GetModeTransitionRequest(channel);
        busOffRecovery = Can_30_Mcan_GetBusOffTransitionRequest(channel);
        doRamCheck = Can_30_Mcan_GetRamCheckTransitionRequest(channel);
        /* #55 only one transition request at one time is possible - execute it \trace SPEC-1771 */
        if(transitionRequest != kCan_30_McanModeNone)
        {
          transitionState = CanLL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
          switch(transitionRequest)
          {
            case kCan_30_McanModeStopReinitFast: /* COV_CAN_TRANSITION_REQUEST */
            case kCan_30_McanModeStopReinit: /* COV_CAN_TRANSITION_REQUEST */
              CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
              break;
# if (CAN_30_MCAN_REINIT_START == STD_ON)
            case kCan_30_McanModeStartReinit: /* COV_CAN_TRANSITION_REQUEST */
# else
            case kCan_30_McanModeStart: /* COV_CAN_TRANSITION_REQUEST */
# endif
            case kCan_30_McanModeResetBusOffEnd: /* COV_CAN_TRANSITION_REQUEST */
# if defined(C_30_MCAN_ENABLE_SILENT_MODE)
            case kCan_30_McanModeSilent: /* COV_CAN_TRANSITION_REQUEST */
# endif
              CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST CAN_30_MCAN_STATUS_START, CANIF_CS_STARTED, transitionState);
              if ( transitionState == kCan_30_McanOk ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_TRANSITION_REQUEST */
              {
                Can_30_Mcan_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
              }
              break;
            case kCan_30_McanModeResetBusOffStart: /* COV_CAN_TRANSITION_REQUEST */ /* not expected, no repetition request */
            default: /* COV_CAN_TRANSITION_REQUEST */
              break;
          }
        }
      }
    } /* over all channels */
    SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_6();
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_MAINFCT_MODE_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */


/****************************************************************************
| NAME:             Can_30_Mcan_CancelTx
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_CancelTx
Relation_Context:
TransmitCancellationAPI
Relation:
DevErrorDetect, TxFullCANSupport
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
TxFullCANSupport, HwCancelTx
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_30_MCAN_ENABLE_CANCEL_SUPPORT_API)
  CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
  tCan_30_McanTxCancellationParaStruct txCancellationPara;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (Hth >= Can_30_Mcan_GetSizeOfMailbox())
  { /* #20 Check Hth is in range */
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
#  if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
  if ((Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_MUX_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  else
  if ((Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_MUX_TYPE) && (Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  endif
  { /* #30 Check Hth is FullCAN or BasicCAN */
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
# if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_30_Mcan_GetMailboxController(Hth);
# endif
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #40 Check parameter controller is in range */
      errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    { /* #60 Check parameter controller is valid */
      errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_30_Mcan_IsControllerInit(channel))
    { /* #70 Check controller is initialized */
      errorId = CAN_30_MCAN_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
      txCancellationPara.mailboxHandle = Hth;
      txCancellationPara.mailboxElement = 0u;
      txCancellationPara.activeSendObject = CanHL_30_Mcan_GetActiveSendObject(txCancellationPara.mailboxHandle, txCancellationPara.mailboxElement);

# if defined (C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
      if ( Can_30_Mcan_GetMailboxType(Hth) != CAN_30_MCAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      { /* #100 is BasicCAN */
# if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO) /* \trace SPEC-1677 */
        for (; txCancellationPara.mailboxElement < Can_30_Mcan_GetMailboxSize(Hth); txCancellationPara.mailboxElement++, txCancellationPara.activeSendObject++) /* PRQA S 2463,3387,3418 */ /* MD_Can_HL_AdditionalExpressionInForLoop,MD_Can_HL_UsingIncOrDec,MD_Can_IncompleteForLoop */
# endif
        { /* #110 over all Multiplexed TX objects - search for handle */
          if (Can_30_Mcan_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
          {
            if ((Can_30_Mcan_GetActiveSendState(txCancellationPara.activeSendObject) == kCan_30_McanBufferSend)
                )  /* COV_CAN_CANCEL_SW_STIMULATION */
            { /* #120 PDU found in active send list - handle found */
              /* #130 CANCEL_IN_HW is active - just suppress TX confirmation */
              Can_30_Mcan_SetActiveSendState(txCancellationPara.activeSendObject, kCan_30_McanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
# if defined(C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
              break;
# endif
            }
          }
        }
      }
# if defined (C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
      else
      { /* #200 is FullCAN */
        if (Can_30_Mcan_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
        {
          if ((Can_30_Mcan_GetActiveSendState(txCancellationPara.activeSendObject) == kCan_30_McanBufferSend)
             )  /* COV_CAN_CANCEL_SW_STIMULATION */
          { /* #210 mailbox to cancel is valid (PDU, handle, send state OK) */
            /* #220 CANCEL_FULLCAN_IN_HW is active - just suppress TX confirmation */
            Can_30_Mcan_SetActiveSendState(txCancellationPara.activeSendObject, kCan_30_McanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
          }
        }
      }
# endif
    }
    CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_WRITE_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#else /* CAN_ENABLE_CANCEL_SUPPORT_API */
  CAN_30_MCAN_DUMMY_STATEMENT(Hth); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_30_MCAN_DUMMY_STATEMENT(PduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* CAN_ENABLE_CANCEL_SUPPORT_API */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#if (CAN_30_MCAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_30_Mcan_GetStatus
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetStatus
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, uint8, CODE) Can_30_Mcan_GetStatus( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 canReturnCode;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  canReturnCode = CAN_30_MCAN_STATUS_INCONSISTENT; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* #50 Check controller is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_30_Mcan_GetStatusBegin(CAN_30_MCAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    /* #100 set logical state as return value */
    canReturnCode = (uint8)Can_30_Mcan_GetLogStatus(channel);
    if ( CanLL_30_Mcan_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #150 set BUSOFF - BUSOFF can only happen on first HW channel (with TX objects) */
      canReturnCode |= CAN_30_MCAN_STATUS_BUSOFF;
    }
# if defined(C_30_MCAN_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    {    
      if ( CanLL_30_Mcan_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #160 set Error Passive */
        canReturnCode |= CAN_30_MCAN_STATUS_PASSIVE;
      }    
      if ( CanLL_30_Mcan_HwIsWarning(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #170 set Error Warning */
        canReturnCode |= CAN_30_MCAN_STATUS_WARNING;
      }
    }
# endif /* C_30_MCAN_ENABLE_EXTENDED_STATUS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return (uint8)canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_GetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetControllerMode
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerMode( uint8 Controller, Can_30_Mcan_ControllerStatePtrType ControllerModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameters are valid */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (ControllerModePtr == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 get logical controller mode from state machine variable */
    if (!CanHL_30_Mcan_IsControllerInit(channel))
    {
      *ControllerModePtr = CAN_CS_UNINIT; /* SBSW_CAN_HL51 */
    }
    else if (CanHL_30_Mcan_IsStart(channel))
    {
      *ControllerModePtr = CAN_CS_STARTED; /* SBSW_CAN_HL51 */
    } 
    else if (CanHL_30_Mcan_IsSleep(channel))
    {
      *ControllerModePtr = CAN_CS_SLEEP; /* SBSW_CAN_HL51 */
    }
    else /* default is:   if (CanHL_30_Mcan_IsStop(channel)) */
    {
      *ControllerModePtr = CAN_CS_STOPPED; /* SBSW_CAN_HL51 */
    }
    canReturnCode = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_GETCTR_MODE_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_GetControllerErrorState
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetControllerErrorState
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerErrorState( uint8 Controller, Can_30_Mcan_ErrorStatePtrType ErrorStatePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (ErrorStatePtr == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_30_Mcan_GetStatusBegin(CAN_30_MCAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    if ( CanLL_30_Mcan_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #40 set BUSOFF */
      *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF; /* SBSW_CAN_HL52 */
    } 
# if defined(C_30_MCAN_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    else if ( CanLL_30_Mcan_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #50 set Error Passive */
      *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE; /* SBSW_CAN_HL52 */
    }
# endif /* C_30_MCAN_ENABLE_EXTENDED_STATUS */
    else
    { /* #60 default return is ACTIVE */
      *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE; /* SBSW_CAN_HL52 */
    }
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_GETCTR_STATE_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_GetControllerTxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetControllerTxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerTxErrorCounter( uint8 Controller, Can_30_Mcan_ErrorCounterPtrType TxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (TxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    *TxErrorCounterPtr = Can_30_McanTxActualErrorCounter(); /* SBSW_CAN_HL53 */
# else
    *TxErrorCounterPtr = Can_30_McanTxActualErrorCounter(channel); /* SBSW_CAN_HL53 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_GETCTR_TXCNT_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_30_Mcan_GetControllerRxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_GetControllerRxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerRxErrorCounter( uint8 Controller, Can_30_Mcan_ErrorCounterPtrType RxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_30_Mcan_GetCanIfChannelId(channel) == kCan_30_McanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_30_Mcan_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (RxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_30_MCAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
    *RxErrorCounterPtr = Can_30_McanRxActualErrorCounter(); /* SBSW_CAN_HL54 */
# else
    *RxErrorCounterPtr = Can_30_McanRxActualErrorCounter(channel); /* SBSW_CAN_HL54 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_GETCTR_RXCNT_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif

#if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
/****************************************************************************
| NAME:             Can_30_Mcan_SetMirrorMode
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_SetMirrorMode
Relation_Context:
MirrorMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_SetMirrorMode( uint8 Controller, CddMirror_MirrorModeType mirrorMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_30_Mcan_SetMirrorModeState(channel, mirrorMode); /* SBSW_CAN_HL20 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if defined(C_30_MCAN_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             Can_30_Mcan_SetSilentMode
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_SetSilentMode
Relation_Context:
SilentMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_SetSilentMode( uint8 Controller, Can_30_Mcan_SilentModeType silentMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Std_ReturnType retval;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set silent mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_30_Mcan_SetSilentModeState(channel, silentMode); /* SBSW_CAN_HL20 */
    retval = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             Can_30_Mcan_RamCheckExecute
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_RamCheckExecute
Relation_Context:
Relation:
RamCheck, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckExecute( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 Do RamCheck by execute reinitialization with activated check */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST kCan_30_McanModeStopReinit, kCan_30_McanFinishBusOffRecovery, kCan_30_McanExecuteRamCheck);
    if (transitionState == kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */
    { /* #40 check transition STOP (Reinit) is successful */
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/****************************************************************************
| NAME:             Can_30_Mcan_RamCheckEnableMailbox
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_RamCheckEnableMailbox
Relation_Context:
Relation:
RamCheck, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckEnableMailbox( Can_HwHandleType htrh )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
  if (htrh >= Can_30_Mcan_GetSizeOfMailbox()) { /* CM_CAN_HL28 */
    errorId = CAN_30_MCAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #15 disable controller to force reinitialization afterwards in Can_30_Mcan_RamCheckEnableController() */
    Can_30_Mcan_SetLogStatus(Can_30_Mcan_GetMailboxController(htrh), CAN_30_MCAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL40 */
    /* #20 reactivate mailbox */
    Can_30_Mcan_SetMailboxState(htrh, kCan_30_McanOk); /* SBSW_CAN_HL34 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/****************************************************************************
| NAME:             Can_30_Mcan_RamCheckEnableController
****************************************************************************/
/*
|<DataModelStart>| Can_30_Mcan_RamCheckEnableController
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckEnableController( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_30_MCAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_DETECT == STD_ON)
  if (can_30_McanConfigInitFlag == CAN_30_MCAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_30_MCAN_E_UNINIT;
  }
  else
#  if !defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCan_30_McanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_30_MCAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 activate controller only when currently disabled */
    if ( (Can_30_Mcan_GetLogStatus(channel) & CAN_30_MCAN_DEACTIVATE_CONTROLLER) == CAN_30_MCAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      uint8 transitionState;
      /* #40 re-initialize to activate mailboxes and controller after RAM check issue */
      Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) & (uint8)(~(CAN_30_MCAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      transitionState = CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANPARA_FIRST kCan_30_McanModeStopReinit, kCan_30_McanFinishBusOffRecovery, kCan_30_McanSuppressRamCheck);
      if (transitionState == kCan_30_McanOk) /* COV_CAN_TRANSITION_REQUEST */
      { /* #40 check transition STOP (Reinit) is successful */
        Can_30_Mcan_SetLogStatus(channel, Can_30_Mcan_GetLogStatus(channel) | CAN_30_MCAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_30_MCAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_30_MCAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
  CAN_30_MCAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif



# if defined( C_30_MCAN_ENABLE_ISR_MANDATORY )  /* ISR necessary; no pure polling configuration */

/* **************************************************************************
| NAME:             CanInterrupt_30_Mcan
| CALLED BY:        CanIsr_<physicalChannelIndex>()
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt structure
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (BUSOFF, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an RX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   a wakeup has to be generated. 
|
|                   If an TX-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be adapted to 
|                   really used name of the interrupt functions.
|
* ************************************************************************* */
/*
|<DataModelStart>| CanInterrupt
Relation_Context:
Relation:
OneChOpt
ChannelAmount, RxBasicCANSupport, MultipleBasicCanObjects, RxFullCANSupport, RxPolling, TxPolling, StatusPolling, IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) CanInterrupt_30_Mcan(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY)
{

#  if( CAN_30_MCAN_SAFE_BSW == STD_ON ) 
  if (canHwChannel >= kCan_30_McanNumberOfChannels) /* PRQA S 2742 */ /* MD_Can_ConstValue */ /* CM_CAN_LL_100 */ /* COV_CAN_GENDATA_FAILURE */
  {
    Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, CAN_30_MCAN_E_GENDATA); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
  else
#  endif
  {
#  if !defined ( C_30_MCAN_SINGLE_RECEIVE_CHANNEL ) 
    CAN_30_MCAN_DUMMY_STATEMENT(canHwChannel);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif

    /* #10 check for interrupt sources */
#  if !defined(C_30_MCAN_ENABLE_ERROR_POLLING)
    /* #20 handle error interrupt */
    if(CanInterruptErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY) == kCan_30_McanOk) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#  endif
    {
#  if !defined(C_30_MCAN_ENABLE_TX_POLLING) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
      CanInterruptTx(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
#  endif

#  if( CAN_BOSCH_ERRATUM_012 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
      /* #30 handle timeout interrupt */
      if( (Cn->IR & kCanIR_TOO) != 0UL)
      { /* timeout arrived */
        CanInterruptTimeoutCounter(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);
      }
#  endif

#  if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
      /* #40 handle BasicCAN (FIFO) interrupt */
#   if( (!defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING )) || (defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )) ) /* ISR necessary; no pure polling configuration */
#    if defined( C_30_MCAN_ENABLE_MULTIPLE_BASICCAN )
      if( (Can_30_Mcan_GetCanIntEnable(canHwChannel) & (kCanIR_RF0N | kCanIR_RF1N)) != 0UL) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if( (Cn->IR & (kCanIR_RF0N | kCanIR_RF1N)) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#    else
      if( (Can_30_Mcan_GetCanIntEnable(canHwChannel) &  kCanIR_RF0N) != 0UL) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if( (Cn->IR &  kCanIR_RF0N) != 0UL)  /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#    endif
        { /* Rx FIFO(0,1) */
          CanBasicInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY); /* call Interrupt handling with logical channel */
        }
      }
#   endif
#  endif
#  if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
#   if ( (!defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )) || (defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )) )          /* ISR necessary; no pure polling configuration */
      /* Rx Buffer Handling
        - Reset interrupt flag IR.DRX
        - Read New Data registers
        - Read messages from Message RAM
        - Reset New Data flags of processed messages */
      /* #50 handle FullCAN interrupt */
      if( (Can_30_Mcan_GetCanIntEnable(canHwChannel) & kCanIR_DRX) != 0UL)  /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if( (Cn->IR & kCanIR_DRX) != 0UL) /* PRQA S 0303 */ /* MD_Can_HwAccess */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
        { /* rcvd FullCAN msg(s) */
          CanFullInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY);     /* call Interrupt handling with logical channel */
        }
      }
#   endif
#  endif
    }
  } /* end else DET check */
#  if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
#   if !((defined(C_30_MCAN_ENABLE_OSEK_OS) && defined(C_30_MCAN_ENABLE_OSEK_OS_INTCAT2)) || defined(C_30_MCAN_ENABLE_ISRVOID) )
  /* Clear interrupt cause in the external interrupt controller in case of interrupt category 1 */
      MCANAS1_CLRIRCAUSE(MCANAS1_G24IRQCLR_BITNO0);
#   endif
#  endif 

} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* CanInterrupt */
# endif /* End of ISR_MANDATORY */
/* CODE CATEGORY 1 END */

#define CAN_30_MCAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: SPEC-1597 */
/* Currently no use-case / not supported: SPEC-1601, SPEC-1592, SPEC-1582 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Goto:
PRQA message 2001
  Reason: 'goto' statements are used to reduce code complexity.
  Risk: Incorrect jump.
  Prevention: Code inspection and runtime tests.

MD_Can_MultipleReturn:
PRQA message 2889
  Reason: Multiple return paths are used to reduce code complexity.
  Risk: Return a function too soon.
  Prevention: Code inspection and runtime tests.

MD_Can_ParameterName:
PRQA message 0784, 0788
  Reason: A parameter that is also used as a macro name is accepted for compatibility reasons.
  Risk: The macro can change the declaration unintentionally and readability is reduced.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_ConstValue:
PRQA message 2741, 2742, 2880, 2985, 2986, 2990, 2991, 2992, 2993, 2994, 2995, 2996
  Reason: Value is constant depending on configuration aspects or platform specific implementation. This leads to constant control expressions, unreachable code or redundant operations.
  Risk: Wrong or missing functionality.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_EmptyFunction:
PRQA message 2987
  Reason: Function is empty depending on configuration aspects and platform specific implementation.
  Risk: Function implementation missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_NoneConstParameterPointer:
PRQA message 3673
  Reason: Non-const pointer parameter is required by the internal interface or compatibility reasons but depending on the configuration or specific platform implementation the target may not always be modified.
  Risk: Read only data could be modified without intention.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_ModuleDefine:
PRQA message 0602, 0603
  Reason: Usage of reserved identifiers with leading underscores is accepted for compatibility reasons.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_RedundantInit:
PRQA message 2981
  Reason: Reduce code complexity by using an explicit variable initializer that may be always modified before being used in some configurations.
  Risk: Unintended change of value.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_GlobalScope:
PRQA message 3218
  Reason: The usage of variables depends on configuration aspects and they may be used only once or defined globally to improve overview.
  Risk: None.
  Prevention: None.

MD_Can_ExternalScope:
PRQA message 1514, 3408, 3447, 3451, 3210
  Reason: The variable is used by other modules and can't be declared static.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_GenData:
PRQA message 1533, 3408
  Reason: These constants are defined in a generated file and cannot be moved to the static source file. Visibility might be reduced by stricter switches for the declaration (kept for compatibility reasons).
  Risk: Compile or link errors.
  Prevention: Code inspection and compile-link of the different variants in the component and integration test.

MD_Can_Union:
PRQA message 0750, 0759
  Reason: Using union type to handle different data accesses.
  Risk: Misinterpreted data.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_Assertion:
PRQA message 2842, 2897
  Reason: Assertion leads to apparent out of bounds indexing or casting an apparent negative value to an unsigned type.
  Risk: Undefined behaviour.
  Prevention: Code inspection. The assertion itself prevents the apparent anomaly.

MD_Can_PointerVoidCast:
PRQA message 0314, 0316
  Reason: API is defined with pointer to void parameter, so pointer has to be casted to or from void.
  Risk: Wrong data access or undefiend behavior for platforms where the byte alignment is not arbitrary.
  Prevention: Code inspection and test with the target compiler/platform in the component test.

MD_Can_PointerCast:
PRQA message 0310
  Reason: Different pointer type is used to access data.
  Risk: Wrong memory is accessed or alignment is incorrect.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_NoneVolatilePointerCast:
PRQA message 0312
  Reason: Cast to none volatile pointer.
  Risk: Incorrect multiple context access.
  Prevention: Code inspection checks that the value is not multiple accessed.

MD_Can_HwAccess:
PRQA message 0303
  Reason: Hardware access needs cast between a pointer to volatile object and an integral type.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_MixedSigns:
PRQA message 4393, 4394
  Reason: Casting from signed to unsigned types and vice versa is needed as different types are intentionally used.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IntegerCast:
PRQA message 4391, 4398, 4399, 4491
  Reason: Explicit cast to a different integer type.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_CompilerAbstraction:
PRQA message 0342
  Reason: Glue operator used for compiler abstraction.
  Risk: Only K&R compiler support glue operator.
  Prevention: Compile test show whether compiler accept glue operator.

MD_Can_NoElseAfterIf:
PRQA message 2004
  Reason: No default handling needed for if-else-if here.
  Risk: Missing default handling.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IncompleteForLoop:
PRQA message 3418
  Reason: Comma operator in for-loop header is used to get a compact code.
  Risk: Uninitialized variable.
  Prevention: Code inspection and test of different variants in the component test.


MD_Can_HL_UndefTypes:
ID 0841
  Reason: CBD types defined for CAN driver usage but should be not seen in other modules to avoid MSR-CBD mixture problems.
  Risk: None
  Prevention: None

MD_Can_HL_UnusedFunction:
ID 3219
  Reason: depend on platform implementation this function is never called.
  Risk: Function call missing.
  Prevention: Code inspection and component test.
  
MD_Can_HL_UsingIncOrDec:
ID 3387
  Reason: using increment (++) or decrement (--) operator on complex expression.
  Risk: Potential side effects other than that caused by the increment or decrement operator.
  Prevention: Code inspection.
  
MD_Can_HL_DereferencePointerValue:
ID 2843
  Reason: Suspicious: Dereference of an invalid pointer value.
  Risk: Potential dereference access to wrong data.
  Prevention: Code inspection.
  
MD_Can_HL_AdditionalExpressionInForLoop:
ID 2463
  Reason: The variable incremented in the third expression of this for statement is not the variable identified as the loop control variable.
  Risk: Potential side effects.
  Prevention: Code inspection.
  
MD_Can_HL_ExternalDeclaration:
PRQA message 3449, 3451
  Reason: The function or variable is declared as external, because the supporting module is not included or does not declare it depend on configuration aspects.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component test.

MD_Can_HL_MultipleTypeDeclaration:
PRQA message 1506, 1507, 1508
  Reason: Same Type defined multiple in order to support multiple use cases.
  Risk: Usage of wrong type.
  Prevention: Code inspection.
  

MD_Can_0404_LL:
Misra Rule 13.2
  Reason:  Byte swap macro used.
  Risk: None
  Prevention: Code inspection assuring that there is no other access to the data during several accesses than by the swap macro.

MD_Can_1891_LL:
Misra Rule 10.8
  Reason: Due to configuration specific types.
  Risk: None
  Prevention: Code inspection.

MD_Can_3305_LL:
Misra Rule 0.0
  Reason: Generic access macro for normal and extended CAN-IDs
  Risk: Memory access exception error.
  Prevention: Code inspection. Alignment is checked for each specific platform.

MD_Can_2842_DynamicRevision_LL:
PRQA message 2842
  Reason: get the value from extern variable defined in the generated data
  Risk: None
  Prevention: None

MD_Can_1006_inlineASM:
Misra Rule 1.1
  Reason: Improve performance by using (platform specific) inline assembler.
  Risk: None
  Prevention: None

MD_Can_0777_LL:
Misra Rule 5.1
  Reason: Identifiers rely on the significance of more than 31 characters.
  Risk: compile or linker error
  Prevention: None

MD_Can_0306_HWaccess_LL:
Misra Rule 11.3
  Reason: Hardware access need pointer to CAN Message RAM.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_4558_RHsideEffect:
Misra Rule 10.1
  Reason: Right hand side evaluation does not need to take place in the case where the left hand side evaluates to false.
  Risk: None
  Prevention: None

MD_Can_3325_LL:
Misra Rule 14.1
  Reason: Configuration or platform specific dependent constant control expression and thus unreachable code.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0635:
Misra Rule 6.4
  Reason: Using unsigned int as approved by MISRA
  Risk: None
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3431_LL:
Misra Rule 19.4
  Reason: This control statement definition is explicitly the intention here.
  Risk: None
  Prevention: None

MD_Can_3614_LL:
Preprocessor
  Reason: Defined within a block due to code repetition mechanism.
  Risk: None
  Prevention: Code inspection, compile tests and runtime tests.

MD_Can_3684:
Misra Rule 8.12
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2982_LL:
Major
  Reason: Preset with default value or read to reset the hardware.
  Risk:   None
  Prevention: None

MD_Can_3203_LL:
Redundancy
  Reason: Used for hardware access due to reset at read.
  Risk:   None
  Prevention: None

MD_Can_0488_LL:
Misra Rule 17.4
  Reason: performing pointer arithmetic
  Risk: Segmentation faults or storage violations
  Prevention: Code review and runtime tests
  
MD_Can_0841:
Misra Rule 19.6
  Reason: Rarely used and always for test purpose.
  Risk: None.
  Prevention: Code inspection and multiple configuration aspects used in component test.

*/

/****************************************************************************/
/*  Silent deviations                                                       */
/****************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CAN_HL01
 \DESCRIPTION Write access to Can_30_McanModeTransitionRequest with controller as index. Controller index is checked against sizeof Can_30_McanModeTransitionRequest in Can_30_Mcan_SetControllerMode(), Can_30_Mcan_RamCheckExecute(), Can_30_Mcan_MainFunction_Mode(), Can_30_Mcan_Init() and CanHL_30_Mcan_ReInit().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL02
 \DESCRIPTION Write access to Can_30_McanLogStatus with controller as index. Controller index is checked against sizeof CanLogStatus in Can_30_Mcan_SetControllerMode(), CanHL_30_Mcan_ErrorHandling(), Can_30_Mcan_RamCheckEnableController(), Can_30_Mcan_MainFunction_Mode(), Can_30_Mcan_Init() and CanHL_30_Mcan_ReInit().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL04
 \DESCRIPTION Write access to Can_30_McanActiveSendState with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject in Can_30_Mcan_CleanUpSendState(), CanHL_30_Mcan_WritePrepare(), CanHL_30_Mcan_InitTxFullCAN(), CanHL_30_Mcan_InitTxBasicCAN(), CanHL_30_Mcan_TxTaskCancelationHandling(), CanHL_30_Mcan_TxConfirmation() and Can_30_Mcan_CancelTx().
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL05
 \DESCRIPTION Write access to CanActiveSendPdu with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL06
 \DESCRIPTION Call Can_30_Mcan_GenericPrecopy() and CanIf_RxIndication() with parameter RX Queue data pointer. The data pointer is only used for read access and it is always a valid pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL07
 \DESCRIPTION Call Can_30_Mcan_GenericPrecopy() and CanIf_RxIndication() with parameter Rx Struct data pointer. The data pointer is only used for read access. Parameter is of type P2CONST in API.
 \COUNTERMEASURE \N [CM_CAN_HL31]

\ID SBSW_CAN_HL08
 \DESCRIPTION Write access to Can_30_McanIsBusOff with controller as index. Controller index is checked against sizeof CanIsBusOff in Can_30_Mcan_SetControllerMode(), CanHL_30_Mcan_ErrorHandling() and Can_30_Mcan_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL09
 \DESCRIPTION Write access to Can_30_McanIsWakeup with controller as index. Controller index is checked against sizeof CanIsWakeup in CanHL_30_Mcan_WakeUpHandling(), Can_30_Mcan_CheckWakeup(), reinitialization and Can_30_Mcan_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL10
 \DESCRIPTION Write access to VersionInfo pointer within function Can_30_Mcan_GetVersionInfo()
 \COUNTERMEASURE \N caller of Can_30_Mcan_GetVersionInfo() has to ensure that VersionInfo pointer is valid. (global description available)

\ID SBSW_CAN_HL11
 \DESCRIPTION Write access to Can_30_McanLastInitObject with controller as index. Controller index is checked against sizeof Can_30_McanLastInitObject in CanHL_30_Mcan_ReInit(), Can_30_Mcan_ChangeBaudrate(), Can_30_Mcan_SetBaudrate() and Can_30_Mcan_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL12
 \DESCRIPTION Write access to Can_30_McanInterruptCounter with controller as index. Controller index is checked against sizeof Can_30_McanInterruptCounter in Can_30_Mcan_Init(), Can_30_Mcan_EnableControllerInterrupts() and Can_30_Mcan_DisableControllerInterrupts()
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL16
 \DESCRIPTION Call CanLL_30_Mcan_CanInterruptDisable() with parameter Can_30_McanInterruptOldStatus as pointer (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL18
 \DESCRIPTION Write access to Can_30_McanRxQueueBuffer with queue write index. Write index is checked against size of CanRxQueueBuffer.
 \COUNTERMEASURE \R [CM_CAN_HL24]

\ID SBSW_CAN_HL19
 \DESCRIPTION Write access to Can_30_McanRxQueueBuffer.data with queue write index and data index. Write index is checked against size of Can_30_McanRxQueueBuffer. (see also generator CM_CAN_HL04 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_HL24]
                 \R [CM_CAN_HL17]

\ID SBSW_CAN_HL20
 \DESCRIPTION Write access to CanMirrorModeState with controller as index. Controller is checked against size of CanMirrorModeState.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL22
 \DESCRIPTION Write access to ActiveSendData with activeSendData + length as index. Index is checked against size of table.
 \COUNTERMEASURE \R [CM_CAN_HL20]

\ID SBSW_CAN_HL23
 \DESCRIPTION Write access to ActiveSendObject stuct with activeSendObject as index. activeSendObject is checked against size of Can_30_McanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL24
 \DESCRIPTION Call Appl_30_Mcan_GenericPreTransmit() with parameter PduInfoPtr_var pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL25
 \DESCRIPTION Call CanIf_CancelTxConfirmation() with parameter Can_30_McanActiveSendObject.PduInfo[activeSendObject] as pointer with activeSendObject as index. activeSendObject is checked against size of Can_30_McanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL26
 \DESCRIPTION Call CanHL_30_Mcan_RxBasicMsgReceivedBegin(), CanHL_30_Mcan_RxMsgReceivedNotification() and CanHL_30_Mcan_RxBasicMsgReceivedEnd() with parameter rxBasicPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL27
 \DESCRIPTION Call CanHL_30_Mcan_RxFullMsgReceivedBegin(), CanHL_30_Mcan_RxFullReceivedNotification() and CanHL_30_Mcan_RxFullMsgReceivedEnd() with parameter rxFullPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL29
 \DESCRIPTION Write access to rxBasicPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL30
 \DESCRIPTION Write access to rxFullPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL31
 \DESCRIPTION Call Initialization subroutines with initPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL32
 \DESCRIPTION Call Appl_30_Mcan_GenericConfirmation and CanHL_30_Mcan_SetCanPduInfo with canPdu pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL33
 \DESCRIPTION Write access to Can_30_McanBusOffCounter with controller as index. Controller index is checked against sizeof CanBusOffCounter in Can_30_Mcan_SetControllerMode(), CanHL_30_Mcan_ErrorHandling() and Can_30_Mcan_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL34
 \DESCRIPTION Write access to Can_30_McanMailboxState with mailbox handle as index. Index secured by ComStackLib [CM_CAN_HL29] and [CM_CAN_HL30] and checked against size of Can_30_McanMailboxState.
 \COUNTERMEASURE \R [CM_CAN_HL28]

\ID SBSW_CAN_HL35
 \DESCRIPTION Call with pointer to CAN cell register for write and read access.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL36
 \DESCRIPTION Write access to initPara structure as pointer (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL37
 \DESCRIPTION Call GetElapsedValue with timer value pointers as parameter (module local defined).
 \COUNTERMEASURE \N The timer values are static and always valid.

\ID SBSW_CAN_HL38
 \DESCRIPTION Call GetCounterValue with timer value (LoopTimeout) pointers as parameter. Controller index is checked against size of ControllerData, kCanLoopXXX as index in LoopTimeout table is always smaller than the dimension of the table given as static user type in ComStackLib and checked against this value.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL22]

\ID SBSW_CAN_HL39
 \DESCRIPTION Undefine preprocessor switch to stimulate user defined feature (only test purpose).
 \COUNTERMEASURE \N Redefinement activates a none documented feature.

\ID SBSW_CAN_HL40
 \DESCRIPTION Write access to Can_30_McanLogStatus with controller as index. Controller is secured by qualified use-case CSL03 of ComStackLib.
 \COUNTERMEASURE \N [CM_CAN_HL02]

\ID SBSW_CAN_HL41
 \DESCRIPTION Write access to Can_30_McanActiveSendState with activeSendObject as index. activeSendObject is temporary stored in a list of [1,3] elements where each element is initialized to a valid value and always written with size check before.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL42
 \DESCRIPTION Write access to txPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL43
 \DESCRIPTION Write access to taskPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL44
 \DESCRIPTION Call task subroutines with taskPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL45
 \DESCRIPTION Call confirmation subroutines with txConfPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL46
 \DESCRIPTION Write access to txConfPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL47
 \DESCRIPTION Call cancellation subroutines with txCancellationPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL48
 \DESCRIPTION Write access to txCancellationPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL49
 \DESCRIPTION Call transmit subroutines with txPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL50
 \DESCRIPTION Write access to TxHwFifo member FillCount, WriteIndex and ReadIndex with Mailbox member TxHwFifo as Index. Index is checked against size of TxHwFifo array.
 \COUNTERMEASURE \R [CM_CAN_HL32]

\ID SBSW_CAN_HL51
 \DESCRIPTION Write access to ControllerModePtr pointer within function Can_30_Mcan_GetControllerMode()
 \COUNTERMEASURE \N caller of Can_30_Mcan_GetControllerMode() has to ensure that ControllerModePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL52
 \DESCRIPTION Write access to ErrorStatePtr pointer within function Can_30_Mcan_GetControllerErrorState()
 \COUNTERMEASURE \N caller of Can_30_Mcan_GetControllerErrorState() has to ensure that ErrorStatePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL53
 \DESCRIPTION Write access to TxErrorCounterPtr pointer within function Can_30_Mcan_GetControllerTxErrorCounter()
 \COUNTERMEASURE \N caller of Can_30_Mcan_GetControllerTxErrorCounter() has to ensure that TxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL54
 \DESCRIPTION Write access to RxErrorCounterPtr pointer within function Can_30_Mcan_GetControllerRxErrorCounter()
 \COUNTERMEASURE \N caller of Can_30_Mcan_GetControllerRxErrorCounter() has to ensure that RxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL55
 \DESCRIPTION A ComStackLib generated variable is accessed.
 \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

\ID SBSW_CAN_HL56
 \DESCRIPTION Write access to local canPdu.sdu with canPdu.length as array size.
 \COUNTERMEASURE \R [CM_CAN_HL33]



\ID SBSW_CAN_LL_100
 \DESCRIPTION       Accessing the MCAN Registers via the channel specific Base Address and a valid static (typedef) offset which is valid.
 \COUNTERMEASURE \S The Base Address is assured via user review (see Safety Manual SMI-64562)
                 \R [CM_CAN_LL_100]
                 \R [CM_CAN_HL01]

\ID SBSW_CAN_LL_101
 \DESCRIPTION       The channel parameter and timer value is used as index for array access.
 \COUNTERMEASURE \R [CM_CAN_HL22]
                 \R [CM_CAN_HL01]

\ID SBSW_CAN_LL_102
 \DESCRIPTION       The channel parameter (assured via the caller software) and timer index (assured via error directive) used for array access.
 \COUNTERMEASURE \R [CM_CAN_LL_102]

\ID SBSW_CAN_LL_103
 \DESCRIPTION       Pointer access to the Message RAM (assured via a runtime check).
 \COUNTERMEASURE \R [CM_CAN_LL_103]
                 \R [CM_CAN_LL_112]

\ID SBSW_CAN_LL_104
 \DESCRIPTION       The dimension values used for the variable access are assured with the loop end condition and the modulo operation (bit operator ampersand).
 \COUNTERMEASURE \R [CM_CAN_LL_104]
                 \R [CM_CAN_LL_105]

\ID SBSW_CAN_LL_106
 \DESCRIPTION       The array access is assured using a constant index.
 \COUNTERMEASURE \N Constant index assures correct access.

\ID SBSW_CAN_LL_107
 \DESCRIPTION       The dimension values used for the variable access are assured with a limited index.
 \COUNTERMEASURE \R [CM_CAN_LL_107]

\ID SBSW_CAN_LL_108
 \DESCRIPTION       Initialization within the address range of the Message RAM (assured via  user review, see Safety Manual), the channel is assured via Core/ComStackLib.
 \COUNTERMEASURE \S Message RAM begin and end address must be verified by the user (see Safety Manual SMI-64561), the number of CAN channels must be verified together with the Base Address (see Safety Manual SMI-64562).

\ID SBSW_CAN_LL_109
 \DESCRIPTION       Pointer write access to a local variable coming from the caller function
 \COUNTERMEASURE \N The caller ensures that the pointer is valid and pointer's type matches the variable type.

 \ID SBSW_CAN_LL_110
 \DESCRIPTION       Call Initialization subroutines with initInfo pointer as parameter.
 \COUNTERMEASURE \S The structure is static and has to be assured with a review and thus it is always valid (pointer to a local stack variable even already assured by the caller).

\ID SBSW_CAN_LL_111
 \DESCRIPTION       The channel parameter is provided (assured via a runtime check).
 \COUNTERMEASURE \R [CM_CAN_LL_111]

\ID SBSW_CAN_LL_112
 \DESCRIPTION       The channel parameter is used as index for array access.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_LL_113
 \DESCRIPTION       Local variable assignment.
 \COUNTERMEASURE \N The local variable is always available.

\ID SBSW_CAN_LL_114
 \DESCRIPTION       Local array variable assignment.
 \COUNTERMEASURE \N The array index cannot become greater than 16 and 4*16 elements are always available with CAN_FD_FULL.

\ID SBSW_CAN_LL_115
 \DESCRIPTION       Accessing the SICANFD Functional Safety Registers via the channel specific Base Address and a static (defined) offset.
 \COUNTERMEASURE \S The Base Address and offset is assured via  user review (see Safety Manual SMI-153796), the channel is assured via Core/ComStackLib.

\ID SBSW_CAN_LL_116
 \DESCRIPTION       Accessing the Traveo2 (TTCANFD) Receive FIFO Top control register via the channel specific Base Address and a static (defined) offset.
 \COUNTERMEASURE \S The Base Address and offset is assured via  user review (see Safety Manual SMI-183990), the channel is assured via Core/ComStackLib.

\ID SBSW_CAN_LL_117
 \DESCRIPTION       Accessing the Global CAN registers via subsystem specific base address. The hardware structure is assured by review. The table access is executed using ComStackLib (Qualified use-case CSL01).
 \COUNTERMEASURE \S The Base Address is assured via user review (see Safety Manual SMI-183991).

\ID SBSW_CAN_LL_118
 \DESCRIPTION       Assembler instruction is inserted.
 \COUNTERMEASURE \N Always valid because there is no memory access.

\ID SBSW_CAN_LL_119
 \DESCRIPTION Write access via pointer to interrupt controller register.
 \COUNTERMEASURE \N In case of SafeBSW 'OS interrupt control' has to be enabled and this code is never active. This is ensured by a MSSV check and compiler error directive.


\ID SBSW_CAN_LL_121
 \DESCRIPTION Call a function with pointer to retVal.
 \COUNTERMEASURE \N The pointer has a static type and always references a local variable.
 
\ID SBSW_CAN_LL_122
 \DESCRIPTION Write access via pointer to CanInterruptOldStatus (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \N This local function is only called with valid pointers.

\ID SBSW_CAN_LL_123
 \DESCRIPTION Read access via pointer to interrupt controller register.
 \COUNTERMEASURE \N In case of SafeBSW 'OS interrupt control' has to be enabled and this code is never active. This is ensured by a MSSV check and compiler error directive.

\ID SBSW_CAN_LL_124
 \DESCRIPTION       Accessing the AS1 Can Module Functional Safety Registers via the global Base Address and a static (defined) offset.
 \COUNTERMEASURE \S The Base Address and offset is assured via user review (see Safety Manual SMI-278313).

\ID SBSW_CAN_LL_125
 \DESCRIPTION       Accessing the MCAN subsystem registers (MCANX_SS) either with a channel base address or with own subsystem base address. Both base addresses are retrieved from a table and the table access is executed using ComStackLib (Qualified use-case CSL01). The hardware structure including the static offset is assured by review.
 \COUNTERMEASURE \S The Base Address is assured via user review (see Safety Manual SMI-549173).
                 \S The Base Address is assured via user review (see Safety Manual SMI-64562).
                 \R [CM_CAN_LL_113]
                 \R [CM_CAN_HL01]

\ID SBSW_CAN_LL_126
 \DESCRIPTION       Accessing the MCAN ECC aggregator registers (MCANX_ECC_AGGR) either with a channel base address or with own subsystem base address. Both base addresses are retrieved from a table and the table access is executed using ComStackLib (Qualified use-case CSL01). The hardware structure including the static offset is assured by review.
 \COUNTERMEASURE \S The Base Address is assured via user review (see Safety Manual SMI-549174).
                 \S The Base Address is assured via user review (see Safety Manual SMI-64562).
                 \R [CM_CAN_LL_114]
                 \R [CM_CAN_HL01]
\ID SBSW_CAN_LL_127
 \DESCRIPTION       Accessing the Global CAN subsystem table via subsystem specific index. The table access is executed using ComStackLib (Qualified use-case CSL01).
 \COUNTERMEASURE \R [CM_CAN_LL_115]

\ID SBSW_CAN_LL_128
 \DESCRIPTION       Accessing the CAN Configuration registers via the global Base Address.
 \COUNTERMEASURE \S The CAN Configuration Base Address is assured via user review (see Safety Manual SMI-833100).
 

SBSW_JUSTIFICATION_END */

/* Counter measurement description

\CM CM_CAN_HL01 A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM CM_CAN_HL02 Qualified use-case CSL03 of ComStackLib (CanMailbox.ControllerConfigIdx is always in range of controller ControllerData)
\CM CM_CAN_HL03 A runtime check ensures activeSendObject index is in valid range for Can_ActiveSendObject table (Qualified use-case CSL01 of ComStackLib - Can_ActiveSendObject size is extended by CAN_MULTIPLEXED_TX_MAX within generator to allow an access to logObjHandle+CAN_MULTIPLEXED_TX_MAX).
\CM CM_CAN_HL17 A runtime check ensures DLC index is always smaller than the dimension of CanRxQueueBuffer.data.
\CM CM_CAN_HL18 A runtime check ensures HRH values is always in range of start stop index of the given mailbox type. (Qualified use-case CSL03 of ComStackLib - start-stop index fit to mailbox entrys)
\CM CM_CAN_HL20 A runtime check ensures size of ActiveSendData (dataByte). For CAN-FD it is checked against the size of the table. For none CAN-FD size is checked against 8 as defined.
\CM CM_CAN_HL22 A runtime check ensures source index for LoopTimeout array is always smaller than the dimension of LoopTimeout.
\CM CM_CAN_HL24 A runtime check ensures RxQueue write index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL25 A runtime check ensures RxQueue read index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL28 A runtime check ensures htrh index is always smaller than the dimension of CanMailboxState (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL29 Qualified use-case CSL02 of ComStackLib (size of CanMailboxState == size of CanMailbox) 
\CM CM_CAN_HL30 Qualified use-case CSL03 of ComStackLib (CanMailbox - CanController Start/Stop HtrhIndex).
\CM CM_CAN_HL31 valid mailbox data area is assigned to rxStruct.pChipData pointer (Has to be given by LL implementation part).
\CM CM_CAN_HL32 A runtime check ensures TxHwFifo index is always smaller than the dimension of TxHwFifo (Qualified use-case CSL01 of ComStackLib).
\CM CM_CAN_HL33 canPdu.length is limited to size of canPdu.sdu.


\CM CM_CAN_LL_100 A runtime check ensures that the controller index is always smaller than number of elements in base address array (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM CM_CAN_LL_102 A runtime check ensures controller index is always smaller than the number of elements in arrays using controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM CM_CAN_LL_103 A runtime check ensures pointer access is always in the correct memory area.
\CM CM_CAN_LL_104 Using the bit operator "&" assures the maximum length of the index to guarantee that the dimension is sufficient.
\CM CM_CAN_LL_105 The loop end condition guarantees that the dimension is sufficient.
\CM CM_CAN_LL_107 The limited index ('0' or '1') guarantees that the dimension is sufficient.
\CM CM_CAN_LL_109 The static structure(element) address is assured via a fix typedef and thus always valid.
\CM CM_CAN_LL_111 A runtime check ensures that the channel parameter is always in the correct range.
\CM CM_CAN_LL_112 A runtime check ensures that the generated table has the correct size (Qualified use-case CSL01 of ComStackLib size of Can_ShmAdr).
\CM CM_CAN_LL_113 A runtime check ensures that the generated table has the correct size (Qualified use-case CSL01 of ComStackLib size of CanMcanSsBaseAddr).
\CM CM_CAN_LL_114 A runtime check ensures that the generated table has the correct size (Qualified use-case CSL01 of ComStackLib size of CanEccAggrBaseAddr).
\CM CM_CAN_LL_115 A runtime check ensures that the generated table has the correct size (Qualified use-case CSL01 of ComStackLib size of CanVirtualSubSystemBaseAdr).

*/

/****************************************************************************/
/*  Coverage Justification                                                  */
/****************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CAN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xf
  \ACCEPT XF tf tf
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to older AUTOSAR/Component versions. 

\ID COV_CAN_INTERNAL
  \ACCEPT XF
  \ACCEPT TX
  \REASON This switch is always active within CAN driver context. Secure visibility of internal interface and cannot be stimulated to off while test. The code is verified by code inspection.

\ID COV_CAN_CANCEL_SW_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \ACCEPT TF tf xf
  \REASON It is not possible to stimulate a sw cancellation while the message is already start to send when hw cancellation is active. The code is verified by code inspection.

\ID COV_CAN_AMD_RUNTIME_MEASUREMENT
  \ACCEPT XF
  \REASON The feature AMD Runtime Measurement is not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_FINALMAGICNUMBER
  \ACCEPT TX
  \REASON Switch is always true is OK here no side effect will occur when switch is false verified by review.

\ID COV_CAN_30_MCAN_SAFE_BSW_EXCLUSION
  \ACCEPT XF xf xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \REASON BUSOFF not stimulated in each configruation. The behavior does not depend on each configuration variant but TCASE-274 takes long runtime and will not be executed for each configuration.   

\ID COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG
  \ACCEPT XF
  \ACCEPT TX
  \REASON Wakeup may be always activated or deactivated depend on configuration. Not all configurations contain activated or deactivated wakeup for at least one controller, but is sufficiantly tested in some configuations with both settings.

\ID COV_IMPLICITE_TXCANCEL
  \ACCEPT TX
  \REASON In some configurations there will be no recancellation but for this case there is no active code (empty else), so this is not really a test case.

\ID COV_CAN_TX_CONF_DATA_FAILURE
  \ACCEPT XF
  \REASON Hard to stimulate invalid active send data against configured object length. The code is verified by code inspection.

---------------- LL ------------------

\ID COV_CAN_MISRA
  \ACCEPT XF
  \ACCEPT TX
  \REASON only used for MISRA analysis not active in production code.

\ID COV_CAN_MICROSAR_VERSION
  \ACCEPT XF
  \ACCEPT TX
  \REASON The feature is supported different for MicroSar4 and MicroSar3.  The code is verified by code inspection.

\ID COV_CAN_MULTI_ECU_CONFIG
  \ACCEPT XF
  \REASON The feature is supported different for MicroSar4 and MicroSar3.  The code is verified by code inspection.

\ID COV_CAN_GEN_HW_START_STOP_IDX
  \ACCEPT TX
  \REASON The feature GEN_HW_START_STOP is always supported for SafeBSW but may be not used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_PARTIAL_NETWORK
  \ACCEPT XF
  \REASON The feature Partial Network is not supported for SafeBSW but be used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_MULTIPLE_BASICCAN_TX
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_SLEEP_SUPPORT
  \ACCEPT XF
  \REASON The feature is platform specific - always IN-active.

\ID COV_CAN_WAKEUP_SUPPORT
  \ACCEPT XF
  \REASON The feature is platform specific - always IN-active.

\ID COV_CAN_EMULATE_SLEEP
  \ACCEPT TX
  \ACCEPT TX tf tx
  \ACCEPT TX tx tx
  \ACCEPT TX xf tx
  \ACCEPT XF
  \REASON The feature Emulated Sleep is always supported for SafeBSW but used in MSR3. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_TX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_BASICCAN_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_POLLING
  \ACCEPT TF
  \REASON The feature configuration specific - fully supported.

\ID COV_CAN_ERROR_POLLING
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_WAKEUP_POLLING
  \ACCEPT XF
  \REASON The feature is platform specific - fully NOT supported.

\ID COV_CAN_INDIVIDUAL_POLLING
  \ACCEPT TF
  \REASON The feature is platform and Project specific.

\ID COV_CAN_TX_POLLING_OR_CANCEL_IN_HW_TASK
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tf xf
  \REASON The feature is platform specific - C_30_MCAN_HL_ENABLE_CANCEL_IN_HW_TASK is always true or false.

\ID COV_CAN_GENERIC_CONFIRMATION_API2
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_FD_SUPPORT
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_MULTIPLE_BASICCAN
  \ACCEPT TF
  \REASON The feature is platform and Project specific - fully supported.

\ID COV_CAN_TX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_FULLCAN_OBJECTS
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_HW_TRANSMIT_CANCELLATION
  \ACCEPT XF
  \REASON The feature is platform specific - fully NOT supported.

\ID COV_CAN_CANCEL_IN_HW
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF xf tf
  \ACCEPT XF xf tf
  \ACCEPT XF xf xf
  \ACCEPT TF tf xf
  \REASON The feature is platform specific - (temporarily) not supported.

\ID COV_CAN_HARDWARE_CANCELLATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_EXTENDED_ID
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MIXED_ID
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_OVERRUN_NOTIFICATION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_MULTIPLEXED_TRANSMISSION
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RX_QUEUE
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_TX_HW_FIFO
  \ACCEPT XF
  \REASON The feature is platform specific - fully NOT supported.

\ID COV_CAN_TXINDIRECTIONHWTOLOG
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_HW_LAYOUT_TXBASIC_FIRST
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_TX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_RX_FULLCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_BASICCAN_HWHANDLE_REVERSE
  \ACCEPT XF
  \REASON The feature is platform specific - always deactivated.

\ID COV_CAN_EXTENDED_STATUS
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_OVERRUN_IN_STATUS
  \ACCEPT TX
  \REASON The feature is platform specific - always activated.

\ID COV_CAN_RxBasicMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_RxFullMsgReceivedBegin
  \ACCEPT TX
  \REASON The feature is platform specific - always active.

\ID COV_CAN_HW_EXIT_TRANSMIT
  \ACCEPT TX
  \REASON The feature is platform specific - always active.


\ID COV_CAN_LL_HARDWARE_BEHAVIOUR
  \ACCEPT TX
  \ACCEPT XF xf xx
  \ACCEPT XX xx xx
  \ACCEPT XX xx xx xx
  \ACCEPT XF xf xx xx
  \ACCEPT XF tf xf xf
  \ACCEPT XF tf xf
  \ACCEPT TF xf tf
  \REASON The condition checks for hardware behaviour that cannot be stimulated. The code is verified by code inspection.


\ID COV_CAN_HARDWARE_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF tf xf
  \ACCEPT XF xf xf
  \ACCEPT XF tx xf
  \ACCEPT XF xf xx
  \ACCEPT XF xf xx xx
  \ACCEPT XF xf xf xf xf
  \ACCEPT XF tx tx tx tx
  \ACCEPT XF tf xf xf
  \ACCEPT XF xf xf xf  
  \ACCEPT TF tf xf
  \ACCEPT TF tf tx
  \ACCEPT TF xf tf
  \ACCEPT TF tf tx tx
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \ACCEPT XF xf xf
  \ACCEPT XF tx tx
  \ACCEPT XF tx xf
  \ACCEPT XF xf xx
  \ACCEPT XF tx tx tx tx 
  \ACCEPT TF tf xf
  \ACCEPT TF xf tf
  \ACCEPT TF xf tf xf tf
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT XF xf xx
  \ACCEPT TF tf tx
  \ACCEPT TF tf xf
  \ACCEPT TF tf tf xf xf
  \ACCEPT TF tf tf tf xf
  \ACCEPT TF tf xf xf tf
  \ACCEPT TF tf xf tf xf
  \ACCEPT TF xf tf xf xf
  \ACCEPT TF xf tf tf tf
  \ACCEPT TF xf tf tf xf
  \ACCEPT TF xf xf tf xf
  \ACCEPT TF xf xf xf tf
  \ACCEPT XF xf xx xf xf
  \ACCEPT XF xf xx xx xx
  \REASON Generated data does not contain all data sets but checked in code. Not encapsulated with preprocessor switch to simplify code.

\ID COV_CAN_OS_USAGE
  \ACCEPT TX
  \ACCEPT TX xf tx
  \ACCEPT TX tx xf
  \ACCEPT XF
  \ACCEPT XF xf tx
  \ACCEPT XF tx xf
  \ACCEPT XF tf tf
  \ACCEPT XF xf tf
  \ACCEPT TF tx tf
  \ACCEPT TF xf xf
  \REASON not all OS types used in component test. The code is verified by code inspection.

\ID COV_CAN_LOCK_ISR_BY_APPL
  \ACCEPT TX tf tf
  \ACCEPT TF xf tf 
  \REASON CAN interrupts never locked by application only within tests. It is not part of the component test to check application code. The code is verified by code inspection.

\ID COV_CAN_RAM_CHECK
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_RAM_CHECK_EXTENDED
  \ACCEPT XF
  \REASON The feature is platform specific - fully NOT supported.

\ID COV_CAN_TIMEOUT_DURATION
  \ACCEPT TF
  \REASON Hardware loop time out is platform specific never reached.

\ID COV_CAN_TRANSITION_REQUEST
  \ACCEPT TF
  \ACCEPT TF tf tf
  \ACCEPT X
  \ACCEPT XX
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX tx tx
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_TRANSITION_PROCESSED
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON StartProcessed are only called in the case where the asynchronous mode change did go to normal mode when requested. This is timing dependent and depends on the configured baud rate. The code is verified by code inspection. 

\ID COV_CAN_TRANSITION_REQUEST_WAKEUP
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_TRANSITION_REQUEST_SLEEP
  \ACCEPT TF
  \ACCEPT TF tf tf
  \REASON Mode transition is platform specific always true or false.

\ID COV_CAN_BASICCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received BasicCAN mailbox is always a valid object and found while search.

\ID COV_CAN_FULLCAN_SEARCH_LINEAR
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Received FullCAN mailbox is always a valid object and found while search.

\ID COV_CAN_RAM_CHECK_NO_STIMULATION
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \REASON some configurations do not stimulate RamCheck by test suite, to check the standard CAN driver behaviour.

\ID COV_CAN_HWOBJINDIVPOLLING
  \ACCEPT TF
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all configurations stimulate this (e.g. Individual polling is set but all objects are polled). 
 
\ID COV_CAN_30_MCAN_SAFE_BSW
  \ACCEPT TF
  \REASON The feature is platform specific - fully supported.

\ID COV_CAN_OSCAT_CONFIG_CHECK
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF tx xf
  \ACCEPT XF xf xf
  \REASON The 'osdISrCan_xx' define is only available in case OSEK OS is used. Only used to verify correct configuration and does not influence the runtime code.

\ID COV_CAN_MCAN_SAFETY_CHECK
  \ACCEPT TX
  \REASON The condition checks for unexpected behaviour that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_MCAN_NOT_SUPPORTED
  \ACCEPT XF tx xf xx
  \ACCEPT XF
  \REASON The condition checks for unexpected behaviour that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_VERSION_CHECK
  \ACCEPT TX
  \REASON Only allowed resp. requested for a specific MCAN Revision 
  
\ID COV_CAN_HW_SPECIFIC
  \ACCEPT XX
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF
  \ACCEPT XF xf xf xf xf
  \ACCEPT XF xf xx xf xf
  \ACCEPT TF tf tf xf xf
  \ACCEPT XF xf xf
  \ACCEPT XF xf xx
  \ACCEPT XF tx 
  \ACCEPT XF xf xx xf
  \ACCEPT TF xf tf
  \ACCEPT TF tx tf
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \ACCEPT TX tx xf
  \ACCEPT TX xf
  \ACCEPT TF tf tf xf
  \ACCEPT TF tx tf xf 
  \ACCEPT TX tx xf xf
  \ACCEPT TF tx tf xf xf
  \ACCEPT XF tx xf tx
  \ACCEPT XF tx xf
  \ACCEPT TX tx tx tx
  \REASON The condition checks for revision/hardware specific defines which do not change. The code is verified by code inspection.

\ID COV_CAN_HW_SPECIFIC_FUNCTIONALITY
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX xf xf tx
  \ACCEPT XF xf xf
  \ACCEPT XF xf tf
  \ACCEPT XF xf xf xf xf
  \ACCEPT TX xf tx
  \ACCEPT TX tx xf
  \ACCEPT TX tx xf xf
  \ACCEPT TX xf xf xf tx
  \ACCEPT TX xf xf tx xf
  \REASON The condition checks for hardware specific functionality which do not change. The code is verified by code inspection.
  
\ID COV_CAN_OS_INT_CONTROL
  \ACCEPT TF
  \ACCEPT XF
  \REASON The condition checks for hardware specific functionality which do not change. The code is verified by code inspection.

\ID COV_CAN_OS_INT_SOURCE
  \ACCEPT TX
  \ACCEPT XF
  \REASON The condition checks if the interrupts should be restored. This depends on if the configuration uses interrupts or not. The code is verified by code inspection.

\ID COV_CAN_NOT_IN_ALL_CFG_AND_HW_SPECIFIC
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT TX tx tx
  \ACCEPT XF xf xx
  \ACCEPT X
  \REASON The condition checks as well for timing as also for revision/hardware specific defines which do not change. The code is verified by code inspection.

\ID COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT TF tf tx tf
  \ACCEPT TF tx tf tf
  \ACCEPT TF tx tf tx
  \ACCEPT TF tx tx tf
  \ACCEPT TF tf tx
  \ACCEPT TF tx tf
  \ACCEPT TF tx tx tf tf
  \ACCEPT TF tf tf tx tf
  \ACCEPT TF tf tf tx tx tf
  \ACCEPT TF tx tf tx tf
  \ACCEPT TF tf tx tx
  \ACCEPT TF tf tx tx tf
  \ACCEPT TF tf tf tx
  \REASON No BasicCAN  The code is verified by code inspection.

\ID COV_CAN_DISABLE_RX_MAILBOX
  \ACCEPT TF tf xf tx
  \ACCEPT TF tf xf tf
  \ACCEPT TF tx xx tf
  \ACCEPT TF xf tf tx
  \ACCEPT TX tx xx tx
  \ACCEPT TF tx tf tf tx
  \ACCEPT TF tf tx tf tf
  \ACCEPT TF tf tx xf xx
  \ACCEPT TF xf xx tf tf
  \ACCEPT TX tx tx xx xx
  \ACCEPT TX tx xx
  \ACCEPT TF tf xf
  \ACCEPT TF xf tf
  \ACCEPT XF tf xf
  \ACCEPT XF xf xx
  \ACCEPT XX xx xx
  \REASON The condition checks whether the filter belongs to the corrupt mailbox. This depends on the mailbox configuration. The code is verified by code inspection.

\ID COV_CAN_INTERRUPT
  \ACCEPT TX
  \REASON The condition checks whether an interrupt has occurred AND that the interrupt is enabled in HW. The condition occurs in interrupt context. The code is verified by code inspection.

\ID COV_CAN_TX_INTERRUPT
  \ACCEPT TX
  \ACCEPT XF
  \REASON The condition checks whether an TX interrupt has occurred AND that the interrupt is enabled in HW. The condition occurs in  TX interrupt and should therefore not be false when tx interrupt is enabled. "XF" acceptance is due to "IndivPollALL" configurations, where interrupts are enabled but no TX interrupt is expected. The deviation is correct and is verified by code inspection.

\ID COV_CAN_ISR_PROTOTYPE
  \ACCEPT TX xf xf
  \REASON The condition checks whether the ISR prototype is disabled by user config and is used to reassure that the ISR prototype is enabled if not explicitly disabled. Deviations are correct and assured with code inspection.

\ID COV_CAN_BUSOFFNOTIFICATION
  \ACCEPT XF
\REASON The condition checks if a bus-off notification is already sent to the application. This is timing depended and related to unexpected behavior, therefore, it cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_CHANNEL_USED
  \ACCEPT TX
  \ACCEPT XF
  \REASON The test is executed with a defined channels. Due to variant handling, a channel can be defined, however, not used. The code is verified by code inspection.
  
\ID COV_CAN_CBD_COMPATIBILITY
  \ACCEPT TX tf tf
  \REASON The condition checks whether interrupt or polling handling is requested. This is used to ensure compatibility to CANbedded. 

\ID COV_CAN_ERRATUM_OFF
  \ACCEPT XX
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf xf
  \REASON Specific Errata only used for specific MCAN Revisions. If the Revision is not under test then the erratum is always inactive.

\ID COV_CAN_START_SEQ_ERRATAS
  \ACCEPT XF
  \ACCEPT TX
  \REASON Specific to MCAN revision and Erratas. The start sequence is different depending on the Erratas.

\ID COV_CAN_CPUTYPE
  \ACCEPT XF
  \ACCEPT TX
  \REASON Feature depends on the platform specific invariant endianness

\ID COV_CAN_EQUAL_CHANNEL_LAYOUT
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF tx tf xf xf xf xf 
  \ACCEPT TX tx xf xf xf
  \ACCEPT TF tf xf xf xf
  \ACCEPT XF xf xf xf xf
  \REASON The test is executed on defined channels. The channel layout is equal for each channel.

\ID COV_CAN_DEFINED_CHANNELS
  \ACCEPT XF tx tf xf xf xf xf 
  \REASON The tests are extecuted on specific channels and does not cover all available channels in the hardware. The code is verified by code inspection.

\ID COV_CAN_DERIVATIVE_SWITCH
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \REASON Only one derivative can be tested for one time. To check supported derivatives, please look for the "Equivalent Hardware Checklist"

\ID COV_CAN_COMPILER_SWITCH
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT TX tx xf
  \ACCEPT TX xf tx
  \REASON Only one compiler can be tested for one time.

\ID COV_CAN_GENTOOL_SPECIFIC
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XF xf xf
  \ACCEPT XF xf xx
  \ACCEPT TF xf tf
  \ACCEPT TX tx tx
  \ACCEPT  TX tx xf xf
  \REASON Feature is only relevant for a specific generation tool (e.g. GENy, CFG5, ...)

\ID COV_CAN_SICANFD_KEY_FAILURE
  \ACCEPT TX
  \REASON The condition checks if static key described in HW manual for SICANFD is accepted. Failure cannot be stimulated. The code is verified by code inspection.
  
\ID COV_CAN_PENDING_TX_REQUEST
  \ACCEPT XF
  \REASON The condition checks if there are any pending TX requests when Stop mode is called. Test of functionality is performed with debugger. The code is verified by code inspection.

\ID COV_CAN_SAFE_BSW_EXCLUSION_LL
  \ACCEPT XF xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_PROTECTED_WRITE_LL
  \ACCEPT XX
  \REASON The feature is platform specific. The code is verified by code inspection.

END_COVERAGE_JUSTIFICATION */ 


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

