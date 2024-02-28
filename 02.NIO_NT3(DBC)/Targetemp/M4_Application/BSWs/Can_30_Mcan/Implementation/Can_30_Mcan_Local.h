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

#if !defined(CAN_30_MCAN_LOCAL_H)
#define  CAN_30_MCAN_LOCAL_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
/* \trace SPEC-1583 */
#include "SchM_Can_30_Mcan.h"
#include "Can_30_Mcan.h"         /* include also all needed types */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_30_MCAN_COREVERSION           != 0x1000u) /* \trace SPEC-1699 */
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

/* PRQA S 3453 EOF */ /* MD_MSR_FctLikeMacro */

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#if defined(C_30_MCAN_ENABLE_MIXED_ID) || defined(C_30_MCAN_ENABLE_EXTENDED_ID)
# define CAN_30_MCAN_ID_IDE_MASK            0x80000000UL
# define CAN_30_MCAN_ID_FD_MASK             0x40000000UL /* \trace SPEC-50553 */
# define CAN_30_MCAN_ID_MASK                0x1FFFFFFFUL
# define CAN_30_MCAN_ID_MASK_STD            0x000007FFUL
# define CAN_30_MCAN_ID_UNUSED_MASK         0x20000000UL
#else
# define CAN_30_MCAN_ID_IDE_MASK            0x0000U
# define CAN_30_MCAN_ID_FD_MASK             0x4000U /* \trace SPEC-50553 */
# define CAN_30_MCAN_ID_MASK                0x07FFU
# define CAN_30_MCAN_ID_MASK_STD            0x07FFU
# define CAN_30_MCAN_ID_UNUSED_MASK         0x3800U
#endif
#define kCan_30_McanAllChannels  ((Can_30_McanChannelHandle)0xFFU)

#if !defined(C_DRV_30_MCAN_INTERNAL) /* COV_CAN_INTERNAL */
# error "Can_30_Mcan_Local.h should only be included by Can.c"
#endif
/* real amount of controllers in this system (LT and PB) */
#define kCan_30_McanNumberOfChannels  Can_30_Mcan_GetControllerMax()
/* if kCan_30_McanNumberOfChannels used to declare a table/dimension this table has to be generated to be also Link-Time-capable */
/*  -> see ESCAN00028069 controller-amount has to be Link-Time-capable */
/* real amount of controllers in this system (LT and PB) */
#define kCan_30_McanNumberOfHwChannels  kCan_30_McanNumberOfChannels

#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((Can_30_McanChannelHandle)0)
# define canHwChannel                           ((Can_30_McanChannelHandle)0)
# define CAN_30_MCAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((Can_30_McanChannelHandle)0)
# define CAN_30_MCAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((Can_30_McanChannelHandle)0)
#else
# define channel                                Controller
# define canHwChannel                           Controller
# define CAN_30_MCAN_HL_HW_CHANNEL_STARTINDEX(ch)       (ch)
# define CAN_30_MCAN_HL_HW_CHANNEL_STOPINDEX(ch)        (ch)
#endif
#if !defined(CAN_30_MCAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_TRANSITION_CHECK STD_ON /* default may be deactivated by user configuration */
#endif
#if !defined(CAN_30_MCAN_REINIT_START) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_REINIT_START STD_OFF
#endif

#if !defined(CAN_30_MCAN_OS_TICK2MS) /* COV_CAN_COMPATIBILITY */
# error "CAN_30_MCAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
#endif
#if !defined(CAN_30_MCAN_OS_COUNTER_ID) /* COV_CAN_COMPATIBILITY */
# error "CAN_30_MCAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
#endif

#if !defined(CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT (CAN_30_MCAN_ID_IDE_MASK | CAN_30_MCAN_ID_FD_MASK | CAN_30_MCAN_ID_MASK)
/* May be changed to mask out FD-bit: (CAN_30_MCAN_ID_IDE_MASK | CAN_30_MCAN_ID_MASK) */
#endif

/* MCAN Version */

#if !defined ( CAN_30_MCAN_C_ENABLE_MPC5700_MCAN_MAJOR_CREL )     /* MCAN Core Release */
# error "Derivative not defined."
#endif
#if !defined ( C_30_MCAN_ENABLE_MPC5700_MCAN_CREL_STEP )          /* COV_CAN_HW_SPECIFIC */
# define C_30_MCAN_ENABLE_MPC5700_MCAN_CREL_STEP       0u         /* Step of MCAN Core Release */
#endif
#if !defined ( C_30_MCAN_ENABLE_MPC5700_MCAN_CREL_SSTEP )         /* COV_CAN_HW_SPECIFIC */
# define C_30_MCAN_ENABLE_MPC5700_MCAN_CREL_SSTEP      0u         /* Sub-Step of MCAN Core Release */
#endif
#if ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() > 3u )    /* COV_CAN_HW_SPECIFIC */
# error "MCAN Revision is not supported yet."
#endif

#if defined(CAN_MCAN_REVISION) /* COV_CAN_INTERNAL */
#else
# if(   ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ) && ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()  >= 2u ) && ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_SSTEP() >= 1u ))   /* COV_CAN_HW_SPECIFIC */
#  define CAN_MCAN_REVISION  0x0321u
# elif( ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ) &&  ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()  >= 2u ))  /* COV_CAN_HW_SPECIFIC */
#  define CAN_MCAN_REVISION  0x0320u
# elif( ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ) &&  ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()  >= 1u ) && ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_SSTEP() >= 5u ))  /* COV_CAN_HW_SPECIFIC */
#  define CAN_MCAN_REVISION  0x0315u
# elif( ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ) &&  ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()  >= 1u ))  /* COV_CAN_HW_SPECIFIC */
#  define CAN_MCAN_REVISION  0x0310u
# elif( ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ))    /* COV_CAN_HW_SPECIFIC */
#  define CAN_MCAN_REVISION  0x0300u
# elif(   Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() == 2u )     /* COV_CAN_HW_SPECIFIC */
#  error "This MCAN Revision is no longer supported."
# elif(   Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() == 1u )     /* COV_CAN_HW_SPECIFIC */
#  error "This MCAN Revision is no longer supported."
# else
#  error "Unknown MCAN Revision detected."
# endif
#endif /* CAN_MCAN_REVISION */


/* MCAN Errata */
/* Erratum #16:  "Configuration of NBTP.NTSEG2 = '0' not allowed." 
                  Relevant for MCAN Rel. 3.1.0, 3.2.0, 3.2.1    */
# if ( CAN_MCAN_REVISION >= 0x0315UL)  /* COV_CAN_HW_SPECIFIC */
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_006 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_006       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_007 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_007       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_008 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_008       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_010 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_010       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1, 3.1.0 */ 
# if !defined CAN_BOSCH_ERRATUM_011 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_011       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.6, 3.0.0, 3.0.1, 3.1.0 */
# if !defined CAN_BOSCH_ERRATUM_012 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_012       STD_OFF
# endif

#elif ( CAN_MCAN_REVISION >= 0x0310UL)  /* COV_CAN_HW_SPECIFIC */
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_006 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_006       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_007 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_007       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_008 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_008       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_010 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_010       STD_OFF
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1, 3.1.0 */ 
# if !defined CAN_BOSCH_ERRATUM_011 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_011       STD_ON
# endif
/* Relevant for MCAN Rel. 2.9.6, 3.0.0, 3.0.1, 3.1.0 */
# if !defined CAN_BOSCH_ERRATUM_012 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_012       STD_ON
# endif

#else
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_006 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_006       STD_ON
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_007 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_007       STD_ON
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_008 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_008       STD_ON
# endif
/* Relevant for MCAN Rel. 2.9.5, 2.9.6, 3.0.0, 3.0.1 */
# if !defined CAN_BOSCH_ERRATUM_010 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_010       STD_ON
# endif

# if !defined CAN_BOSCH_ERRATUM_011
#  define CAN_BOSCH_ERRATUM_011      STD_ON
# endif

# if !defined CAN_BOSCH_ERRATUM_012 /* COV_CAN_ERRATUM_OFF */
#  define CAN_BOSCH_ERRATUM_012       STD_OFF /* PXHD exists since 3.1.0 */
# endif
#endif


#if( (!defined(C_30_MCAN_ENABLE_EXTENDED_ID)) || (defined(C_30_MCAN_ENABLE_MIXED_ID)) )
# define C_30_MCAN_ENABLE_STD_ID
#endif

#if( (defined( C_30_MCAN_ENABLE_GENERATE_FULLCAN_MASK ))  || (defined( C_30_MCAN_DISABLE_GENERATE_FULLCAN_MASK )) || (defined( CAN_C_30_MCAN_ENABLE_GENERATE_FULLCAN_MASK )) ) /* COV_CAN_GENTOOL_SPECIFIC */
# define C_30_MCAN_ENABLE_FULLCAN_FILTER_GENERATION
#else
# error "Inconsistent Generation Tool. Please update GENy DLL Hw_Mpc5700McanCpuCan to version 1.09.00 or later."
#endif

#if !defined (kCanNumberOfStandardFilter) /* COV_CAN_COMPATIBILITY */
# if defined( CAN_30_MCAN_SIDFEUSEDOFSIDFC )      /* COV_CAN_COMPATIBILITY */
#  if( CAN_30_MCAN_SIDFEUSEDOFSIDFC == STD_ON )
#   define kCanNumberOfStandardFilter  1
#  else
#   define kCanNumberOfStandardFilter  0
#  endif
# else
#  define kCanNumberOfStandardFilter  1  /* GENy */
# endif
#endif

#if !defined (kCanNumberOfExtendedFilter) /* COV_CAN_COMPATIBILITY */
# if defined( CAN_30_MCAN_XIDFEUSEDOFXIDFC )      /* COV_CAN_COMPATIBILITY */
#  if( CAN_30_MCAN_XIDFEUSEDOFXIDFC == STD_ON )
#   define kCanNumberOfExtendedFilter  1
#  else
#   define kCanNumberOfExtendedFilter  0
#  endif
# else
#  define kCanNumberOfExtendedFilter  1   /* GENy */
# endif
#endif


/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable Can_ActiveSendState */
#define kCan_30_McanBufferFree              (uint8)0xFF     /* mark objects as free */
#define kCan_30_McanBufferCancel            (uint8)0xFE     /* mark object as currently cancelling */
#define kCan_30_McanBufferCancelSw          (uint8)0xFD
#define kCan_30_McanBufferSend              (uint8)0x01     /* occupied send object */

/* HL return values */
#define kCan_30_McanFailed                  (uint8)0x00     /* similar to CAN_NOT_OK but value may differ --> converted in HL (LL only use kCan...) */
#define kCan_30_McanOk                      (uint8)0x01     /* similar to CAN_OK */
#define kCan_30_McanRequested               (uint8)0x03

#define kCan_30_McanFalse                   kCan_30_McanFailed
#define kCan_30_McanTrue                    kCan_30_McanOk

#define Can_30_Mcan_GetControllerMax()                        Can_30_Mcan_GetSizeOfControllerData()
#define Can_30_Mcan_GetCanToCanIfChannelMapping(Index)        Can_30_Mcan_GetCanIfChannelId((Index))

/* ControllerConfig */
#define Can_30_Mcan_GetCanControllerDefaultBaudrate(logCh)    Can_30_Mcan_GetCanControllerDefaultBaudrateOfControllerConfig(logCh)
#define Can_30_Mcan_GetCanControllerDefaultBaudrateIdx(logCh) Can_30_Mcan_GetCanControllerDefaultBaudrateIdxOfControllerConfig(logCh)
#if !defined(Can_30_Mcan_GetMailboxRxBasicLengthOfControllerConfig) /* If no Object is available ComStackLib do not generate start-stop index */
# define Can_30_Mcan_GetMailboxRxBasicLengthOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxRxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxRxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_30_Mcan_GetRxBasicHandleMax(logCh)                Can_30_Mcan_GetMailboxRxBasicLengthOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxBasicHandleStart(logCh)              (Can_HwHandleType)Can_30_Mcan_GetMailboxRxBasicStartIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxBasicHandleStop(logCh)               (Can_HwHandleType)Can_30_Mcan_GetMailboxRxBasicEndIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxBasicHwStart(logCh)                  Can_30_Mcan_GetRxBasicHwStartOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxBasicHwStop(logCh)                   Can_30_Mcan_GetRxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_30_Mcan_GetMailboxRxFullLengthOfControllerConfig)
# define Can_30_Mcan_GetMailboxRxFullLengthOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxRxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxRxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_30_Mcan_GetRxFullHandleMax(logCh)                 Can_30_Mcan_GetMailboxRxFullLengthOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxFullHandleStart(logCh)               (Can_HwHandleType)Can_30_Mcan_GetMailboxRxFullStartIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxFullHandleStop(logCh)                (Can_HwHandleType)Can_30_Mcan_GetMailboxRxFullEndIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxFullHwStart(logCh)                   Can_30_Mcan_GetRxFullHwStartOfControllerConfig(logCh)
#define Can_30_Mcan_GetRxFullHwStop(logCh)                    Can_30_Mcan_GetRxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_30_Mcan_GetMailboxTxBasicLengthOfControllerConfig) /* COV_CAN_GENDATA_FAILURE */
# define Can_30_Mcan_GetMailboxTxBasicLengthOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxTxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxTxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_30_Mcan_GetTxBasicHandleMax(logCh)                Can_30_Mcan_GetMailboxTxBasicLengthOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxBasicHandleStart(logCh)              (Can_HwHandleType)Can_30_Mcan_GetMailboxTxBasicStartIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxBasicHandleStop(logCh)               (Can_HwHandleType)Can_30_Mcan_GetMailboxTxBasicEndIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxBasicHwStart(logCh)                  Can_30_Mcan_GetTxBasicHwStartOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxBasicHwStop(logCh)                   Can_30_Mcan_GetTxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_30_Mcan_GetMailboxTxFullLengthOfControllerConfig)
# define Can_30_Mcan_GetMailboxTxFullLengthOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxTxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxTxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_30_Mcan_GetTxFullHandleMax(logCh)                 Can_30_Mcan_GetMailboxTxFullLengthOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxFullHandleStart(logCh)               (Can_HwHandleType)Can_30_Mcan_GetMailboxTxFullStartIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxFullHandleStop(logCh)                (Can_HwHandleType)Can_30_Mcan_GetMailboxTxFullEndIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxFullHwStart(logCh)                   Can_30_Mcan_GetTxFullHwStartOfControllerConfig(logCh)
#define Can_30_Mcan_GetTxFullHwStop(logCh)                    Can_30_Mcan_GetTxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_30_Mcan_GetMailboxUnusedLengthOfControllerConfig)  /* COV_CAN_GENDATA_FAILURE */
# define Can_30_Mcan_GetMailboxUnusedLengthOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxUnusedStartIdxOfControllerConfig(logCh) 0u
# define Can_30_Mcan_GetMailboxUnusedEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_30_Mcan_GetUnusedHandleMax(logCh)                 Can_30_Mcan_GetMailboxUnusedLengthOfControllerConfig(logCh)
#define Can_30_Mcan_GetUnusedHandleStart(logCh)               (Can_HwHandleType)Can_30_Mcan_GetMailboxUnusedStartIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetUnusedHandleStop(logCh)                (Can_HwHandleType)Can_30_Mcan_GetMailboxUnusedEndIdxOfControllerConfig(logCh)
#define Can_30_Mcan_GetUnusedHwStart(logCh)                   Can_30_Mcan_GetUnusedHwStartOfControllerConfig(logCh)
#define Can_30_Mcan_GetUnusedHwStop(logCh)                    Can_30_Mcan_GetUnusedHwStopOfControllerConfig(logCh)

/* Mailbox */
/* GetMailboxSize: logical size of mailbox - use LL specific generated data to get hardware object size if needed */
#define Can_30_Mcan_GetMailboxSize(htrh)                      Can_30_Mcan_GetMailboxSizeOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxHwHandle(htrh)                  Can_30_Mcan_GetHwHandleOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxIDValue(htrh)                   Can_30_Mcan_GetIDValueOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxType(htrh)                      Can_30_Mcan_GetMailboxTypeOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxDataLen(htrh)                   Can_30_Mcan_GetMaxDataLenOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxFdPadding(htrh)                 Can_30_Mcan_GetFdPaddingOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxController(htrh)                (Can_30_McanChannelHandle)Can_30_Mcan_GetControllerConfigIdxOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxActiveSendObject(htrh)          Can_30_Mcan_GetActiveSendObjectOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxActiveSendData(htrh)            Can_30_Mcan_GetActiveSendDataOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxMemSecObjIndex(htrh)            Can_30_Mcan_GetMemorySectionsIndexOfMailbox(htrh)
#define Can_30_Mcan_IsMailboxIndivPolling(htrh)               Can_30_Mcan_IsIsIndivPollingOfMailbox(htrh)
#define Can_30_Mcan_GetMailboxTxHwFifo(htrh)                  Can_30_Mcan_GetTxHwFifoOfMailbox(htrh)

/* MemorySectionInfo */
#define Can_30_Mcan_GetMemSecAddress(memSec)                  Can_30_Mcan_GetMemoryStartAddressOfMemorySectionInfo(memSec)
#define Can_30_Mcan_GetMemSecStartIndex(memSec)               Can_30_Mcan_GetMemorySectionStartOfMemorySectionInfo(memSec)

/* MemorySectionObjects */
#define Can_30_Mcan_GetMemSecObjHwHandle(memSecObj)           Can_30_Mcan_GetHwHandleOfMemorySectionObjects(memSecObj)
#define Can_30_Mcan_GetMemSecObjMailboxElement(memSecObj)     Can_30_Mcan_GetMailboxElementOfMemorySectionObjects(memSecObj)
#define Can_30_Mcan_GetMemSecObjMailboxHandle(memSecObj)      Can_30_Mcan_GetMailboxHandleOfMemorySectionObjects(memSecObj)
#define Can_30_Mcan_IsMemSecObjIndivPolling(memSecObj)        Can_30_Mcan_IsIsIndivPollingOfMemorySectionObjects(memSecObj)

/* VAR */
#define Can_30_Mcan_GetLastInitObject(Index)                   Can_30_Mcan_GetLastInitObjectOfControllerData(Index)
#define Can_30_Mcan_SetLastInitObject(Index, Value)            Can_30_Mcan_SetLastInitObjectOfControllerData(Index, Value)
#define Can_30_Mcan_GetCanInterruptOldStatus(Index)            Can_30_Mcan_GetCanInterruptOldStatusOfControllerData(Index)
#define Can_30_Mcan_SetCanInterruptOldStatus(Index, Value)     Can_30_Mcan_SetCanInterruptOldStatusOfControllerData(Index, Value)
#define Can_30_Mcan_GetCanInterruptCounter(Index)              Can_30_Mcan_GetCanInterruptCounterOfControllerData(Index)
#define Can_30_Mcan_SetCanInterruptCounter(Index, Value)       Can_30_Mcan_SetCanInterruptCounterOfControllerData(Index, Value)
#define Can_30_Mcan_IncCanInterruptCounter(Index)              Can_30_Mcan_IncCanInterruptCounterOfControllerData(Index)
#define Can_30_Mcan_DecCanInterruptCounter(Index)              Can_30_Mcan_DecCanInterruptCounterOfControllerData(Index)
#define Can_30_Mcan_IsIsWakeup(Index)                          Can_30_Mcan_IsIsWakeupOfControllerData(Index)
#define Can_30_Mcan_SetIsWakeup(Index, Value)                  Can_30_Mcan_SetIsWakeupOfControllerData(Index, Value)
#define Can_30_Mcan_IsIsBusOff(Index)                          Can_30_Mcan_IsIsBusOffOfControllerData(Index)
#define Can_30_Mcan_SetIsBusOff(Index, Value)                  Can_30_Mcan_SetIsBusOffOfControllerData(Index, Value)
#define Can_30_Mcan_GetModeTransitionRequest(Index)            Can_30_Mcan_GetModeTransitionRequestOfControllerData(Index)
#define Can_30_Mcan_SetModeTransitionRequest(Index, Value)     Can_30_Mcan_SetModeTransitionRequestOfControllerData(Index, Value)
#define Can_30_Mcan_GetBusOffTransitionRequest(Index)          Can_30_Mcan_GetBusOffTransitionRequestOfControllerData(Index)
#define Can_30_Mcan_SetBusOffTransitionRequest(Index, Value)   Can_30_Mcan_SetBusOffTransitionRequestOfControllerData(Index, Value)
#define Can_30_Mcan_GetRamCheckTransitionRequest(Index)        Can_30_Mcan_GetRamCheckTransitionRequestOfControllerData(Index)
#define Can_30_Mcan_SetRamCheckTransitionRequest(Index, Value) Can_30_Mcan_SetRamCheckTransitionRequestOfControllerData(Index, Value)
/* controller states */
#define Can_30_Mcan_GetLogStatus(Index)                        Can_30_Mcan_GetLogStatusOfControllerData(Index)
#define Can_30_Mcan_SetLogStatus(Index, Value)                 Can_30_Mcan_SetLogStatusOfControllerData(Index, Value)
#define Can_30_Mcan_GetCanLoopTimeout(ch, Index)               (Can_30_Mcan_GetLoopTimeoutOfControllerData(ch))[(Index)]
#define Can_30_Mcan_GetMirrorModeState(Index)                  Can_30_Mcan_GetMirrorModeStateOfControllerData(Index)
#define Can_30_Mcan_SetMirrorModeState(Index, Value)           Can_30_Mcan_SetMirrorModeStateOfControllerData(Index, Value)
#define Can_30_Mcan_GetSilentModeState(Index)                  Can_30_Mcan_GetSilentModeStateOfControllerData(Index)
#define Can_30_Mcan_SetSilentModeState(Index, Value)           Can_30_Mcan_SetSilentModeStateOfControllerData(Index, Value)
/* ActiveSend */
#define Can_30_Mcan_GetActiveSendPdu(Index)                    Can_30_Mcan_GetPduOfActiveSendObject(Index)
#define Can_30_Mcan_SetActiveSendPdu(Index, Value)             Can_30_Mcan_SetPduOfActiveSendObject(Index, Value)
#define Can_30_Mcan_GetActiveSendState(Index)                  Can_30_Mcan_GetStateOfActiveSendObject(Index)
#define Can_30_Mcan_SetActiveSendState(Index, Value)           Can_30_Mcan_SetStateOfActiveSendObject(Index, Value)
#define Can_30_Mcan_GetActiveSendPduInfo(Index)                Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)
#define Can_30_Mcan_GetActiveSendId(Index)                     (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).id
#define Can_30_Mcan_SetActiveSendId(Index, Value)              (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).id = (Value)
#define Can_30_Mcan_GetActiveSendLength(Index)                 (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).length
#define Can_30_Mcan_SetActiveSendLength(Index, Value)          (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).length = (Value)
#define Can_30_Mcan_GetActiveSendSdu(Index)                    (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).sdu
#define Can_30_Mcan_SetActiveSendSdu(Index, Value)             (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).sdu = (Value)
#define Can_30_Mcan_GetActiveSendSwPduHandle(Index)            (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).swPduHandle
#define Can_30_Mcan_SetActiveSendSwPduHandle(Index, Value)     (Can_30_Mcan_GetPduInfoOfActiveSendObject(Index)).swPduHandle = (Value)
/* Use already ComStackLib name #define Can_30_Mcan_GetActiveSendData(Index)                   Can_30_Mcan_GetActiveSendData(Index) */
/* TxHwFifo */
#define Can_30_Mcan_GetTxHwFifoWriteIndex(fifo)                Can_30_Mcan_GetWriteIndexOfTxHwFifo(fifo)
#define Can_30_Mcan_SetTxHwFifoWriteIndex(fifo, Value)         Can_30_Mcan_SetWriteIndexOfTxHwFifo(fifo, Value)
#define Can_30_Mcan_IncTxHwFifoWriteIndex(fifo)                Can_30_Mcan_IncWriteIndexOfTxHwFifo(fifo)
#define Can_30_Mcan_GetTxHwFifoReadIndex(fifo)                 Can_30_Mcan_GetReadIndexOfTxHwFifo(fifo)
#define Can_30_Mcan_SetTxHwFifoReadIndex(fifo, Value)          Can_30_Mcan_SetReadIndexOfTxHwFifo(fifo, Value)
#define Can_30_Mcan_IncTxHwFifoReadIndex(fifo)                 Can_30_Mcan_IncReadIndexOfTxHwFifo(fifo)
#define Can_30_Mcan_GetTxHwFifoFillCount(fifo)                 Can_30_Mcan_GetFillCountOfTxHwFifo(fifo)
#define Can_30_Mcan_SetTxHwFifoFillCount(fifo, Value)          Can_30_Mcan_SetFillCountOfTxHwFifo(fifo, Value)
#define Can_30_Mcan_IncTxHwFifoFillCount(fifo)                 Can_30_Mcan_IncFillCountOfTxHwFifo(fifo)
#define Can_30_Mcan_DecTxHwFifoFillCount(fifo)                 Can_30_Mcan_DecFillCountOfTxHwFifo(fifo)

#if defined( CAN_30_MCAN_GEN_COM_STACK_LIB )  /* COV_CAN_COMPATIBILITY */
# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
#  define GET_TXRXBB_OFFSET(num, dli) (vuint32)((num) * (8u + CanLL_30_Mcan_xES2Bytes[dli]))
#  define GET_N_BYTES_FROM_ES(elementSize) (CanLL_30_Mcan_xES2Bytes[(elementSize)&0x7u])
#  define GET_RX0F_OFFSET(num) (GET_TXRXBB_OFFSET((num), Can_30_Mcan_GetF0DSOfShmElementSize(canHwChannel)))
#  define GET_RX1F_OFFSET(num) (GET_TXRXBB_OFFSET((num), Can_30_Mcan_GetF1DSOfShmElementSize(canHwChannel)))
#  define GET_RXB_OFFSET(num)  (GET_TXRXBB_OFFSET((num), Can_30_Mcan_GetRBDSOfShmElementSize(canHwChannel)))
#  define GET_TXB_OFFSET(num)  (GET_TXRXBB_OFFSET((num), Can_30_Mcan_GetTBDSOfShmElementSize(canHwChannel)))
# else
#  define GET_RX0F_OFFSET(num) ((vuint32)(num)<<4u)
#  define GET_RX1F_OFFSET(num) ((vuint32)(num)<<4u)
#  define GET_RXB_OFFSET(num)  ((vuint32)(num)<<4u)
#  define GET_TXB_OFFSET(num)  ((vuint32)(num)<<4u)
# endif
#if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
# define ShmSIDF(num)      (*((t_30_McanSIFEType*) (Can_30_Mcan_GetSIDFAOfVirtualShmAdr(canHwChannel) + GET_SIDF_OFFSET(num))))
# define ShmXIDF(num)      (*((t_30_McanXIFEType*) (Can_30_Mcan_GetXIDFAOfVirtualShmAdr(canHwChannel) + GET_XIDF_OFFSET(num))))
# define ShmRXF0(num)      (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXF0AOfVirtualShmAdr(canHwChannel) + GET_RX0F_OFFSET(num)) )
# define ShmRXF1(num)      (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXF1AOfVirtualShmAdr(canHwChannel) + GET_RX1F_OFFSET(num)) )
# define ShmRXB(num)       (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXBAOfShmAdr(canHwChannel)  + GET_RXB_OFFSET (num)) )
# define ShmTXEF(num)      (*((tTxEventFifoElmType*)(Can_30_Mcan_GetTXEFAOfVirtualShmAdr(canHwChannel) + GET_TXEF_OFFSET(num))))
# define ShmTXB(num)       (*((Can_30_McanElmType*) (Can_30_Mcan_GetTXBAOfVirtualShmAdr(canHwChannel)  + GET_TXB_OFFSET (num))))
# define pShmTXB(num)      ( ((Can_30_McanElmType*) (Can_30_Mcan_GetTXBAOfVirtualShmAdr(canHwChannel)  + GET_TXB_OFFSET (num))))
# else
# define ShmSIDF(num)      (*((t_30_McanSIFEType*) (Can_30_Mcan_GetSIDFAOfShmAdr(canHwChannel) + GET_SIDF_OFFSET(num))))
# define ShmXIDF(num)      (*((t_30_McanXIFEType*) (Can_30_Mcan_GetXIDFAOfShmAdr(canHwChannel) + GET_XIDF_OFFSET(num))))
# define ShmRXF0(num)      (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXF0AOfShmAdr(canHwChannel) + GET_RX0F_OFFSET(num)) )
# define ShmRXF1(num)      (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXF1AOfShmAdr(canHwChannel) + GET_RX1F_OFFSET(num)) )
# define ShmRXB(num)       (  (Can_30_McanElmType*)(Can_30_Mcan_GetRXBAOfShmAdr(canHwChannel)  + GET_RXB_OFFSET (num)) )
# define ShmTXEF(num)      (*((tTxEventFifoElmType*)(Can_30_Mcan_GetTXEFAOfShmAdr(canHwChannel) + GET_TXEF_OFFSET(num))))
# define ShmTXB(num)       (*((Can_30_McanElmType*) (Can_30_Mcan_GetTXBAOfShmAdr(canHwChannel)  + GET_TXB_OFFSET (num))))
# define pShmTXB(num)      ( ((Can_30_McanElmType*) (Can_30_Mcan_GetTXBAOfShmAdr(canHwChannel)  + GET_TXB_OFFSET (num))))
# endif
# define Can_30_Mcan_GetCanTXBRP(ch)                                Can_30_Mcan_GetTXBRPOfControllerData(ch)
# define Can_30_Mcan_GetCanBusOffNotification(ch)                   Can_30_Mcan_GetBusOffNotificationOfControllerData(ch)
#if defined ( CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING )
# define Can_30_Mcan_GetPSRValue(ch)                                Can_30_Mcan_GetPSRValueOfControllerData(ch)
#endif
# define Can_30_Mcan_GetCanIntEnable(ch)                            Can_30_Mcan_GetIntEnableOfControllerData(ch)
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#  define Can_30_Mcan_GetCanBasisAdr(hwch)                          Can_30_Mcan_GetVirtualBasisAdrOfControllerData(hwch)
# else
# define Can_30_Mcan_GetCanBasisAdr(hwch)                           Can_30_Mcan_GetBasisAdrOfControllerConfig(hwch)
# endif
# define Can_30_Mcan_GetCanPrevMode(ch)                             Can_30_Mcan_GetPrevModeOfControllerData(ch)
# define Can_30_Mcan_GetCanLastState(ch)                            Can_30_Mcan_GetLastStateOfControllerData(ch)

# define Can_30_Mcan_GetCanBTP(initObject)                          Can_30_Mcan_GetBTP(initObject)
# define Can_30_Mcan_GetCanFBTP(initObject)                         Can_30_Mcan_GetFBTP(initObject)
# define Can_30_Mcan_GetCanTDCR(initObject)                         Can_30_Mcan_GetTDCR(initObject)
# define Can_30_Mcan_GetCanGFC(ch)                                  Can_30_Mcan_GetGFC(ch)
# define Can_30_Mcan_GetCanXIDAM(ch)                                Can_30_Mcan_GetXIDAM(ch)
# define Can_30_Mcan_GetCanRXBC(ch)                                 Can_30_Mcan_GetRXBCOfBufferConfig(ch) 
# define Can_30_Mcan_GetCanTXBC(ch)                                 Can_30_Mcan_GetTXBCOfBufferConfig(ch) 
# define Can_30_Mcan_GetCanTXEFC(ch)                                Can_30_Mcan_GetTXEFCOfBufferConfig(ch) 
# define Can_30_Mcan_GetCanRXF0C(ch)                                Can_30_Mcan_GetRXF0COfBufferConfig(ch)
# define Can_30_Mcan_GetCanRXF1C(ch)                                Can_30_Mcan_GetRXF1COfBufferConfig(ch)
# define Can_30_Mcan_GetCanSIDFC_FLSSAOfCanSIDFC(ch)                Can_30_Mcan_GetFLSSAOfSIDFC(ch)
# define Can_30_Mcan_GetCanXIDFC_FLESAOfCanXIDFC(ch)                Can_30_Mcan_GetFLESAOfXIDFC(ch)
# define Can_30_Mcan_GetCanSIDFC_LSSOfCanSIDFC(ch)                  Can_30_Mcan_GetLSSOfSIDFC(ch)
# define Can_30_Mcan_GetCanXIDFC_LSEOfCanXIDFC(ch)                  Can_30_Mcan_GetLSEOfXIDFC(ch)
# define Can_30_Mcan_GetCanSIDFE(ch)                                Can_30_Mcan_GetSIDFE(ch)
# define Can_30_Mcan_GetCanXIDFE(ch)                                Can_30_Mcan_GetXIDFE(ch)
# define Can_30_Mcan_GetCanSIDFEStartIndex(ch)                      Can_30_Mcan_GetSIDFEStartIdxOfSIDFC(ch)
# define Can_30_Mcan_GetCanXIDFEStartIndex(ch)                      Can_30_Mcan_GetXIDFEStartIdxOfXIDFC(ch)
# define Can_30_Mcan_GetCanXIDFEEIDFE_0OfCanXIDFE(ch)               Can_30_Mcan_GetEIDFE_0OfXIDFE(ch)
# define Can_30_Mcan_GetCanXIDFEEIDFE_1OfCanXIDFE(ch)               Can_30_Mcan_GetEIDFE_1OfXIDFE(ch)

# if( CAN_30_MCAN_ISTTCANOFCONTROLLERCONFIG == STD_ON ) /* COV_CAN_HW_SPECIFIC */ 
#  define Can_30_Mcan_IsIsTTCan(ch)                                           Can_30_Mcan_IsIsTTCanOfControllerConfig(ch)
#  define C_30_MCAN_ENABLE_TTCAN_AVAILABLE
# endif
#else /* CAN_30_MCAN_GEN_COM_STACK_LIB */

# if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
#  define GET_TXRXBB_OFFSET(num, dli) (vuint32)((num) * (8u + CanLL_xES2Bytes[dli]))
#  define GET_N_BYTES_FROM_ES(elementSize) (CanLL_xES2Bytes[(elementSize)&0x7u])
#  define GET_RX0F_OFFSET(num) (GET_TXRXBB_OFFSET((num), Can_GetShmElementSize(canHwChannel)))
#  define GET_RX1F_OFFSET(num) (GET_TXRXBB_OFFSET((num), Can_GetShmElementSize(canHwChannel)))
#  define GET_RXB_OFFSET(num)  (GET_TXRXBB_OFFSET((num), Can_GetShmElementSize(canHwChannel)))
#  define GET_TXB_OFFSET(num)  (GET_TXRXBB_OFFSET((num), Can_GetShmElementSize(canHwChannel)))
# else
#  define GET_RX0F_OFFSET(num) ((num)<<4)
#  define GET_RX1F_OFFSET(num) ((num)<<4)
#  define GET_RXB_OFFSET(num)  ((num)<<4)
#  define GET_TXB_OFFSET(num)  ((num)<<4)
# endif

# if defined( C_30_MCAN_ENABLE_TTCAN_AVAILABLE )
#  define Can_30_Mcan_IsIsTTCan(ch)                                           Can_30_McanIsTTCanChannel[(ch)]
# else
#  define Can_30_Mcan_IsIsTTCan(ch)                                           0
# endif

# if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
#  define Can_GetStartAdrOfShmAdr(ch)                                 CAN_SHM_RAM_START
#  define Can_GetStopAdrOfShmAdr(ch)                                  CAN_SHM_RAM_END
# else
#  define Can_GetStartAdrOfShmAdr(ch)                                 CanShmStartEndAdr[(ch)].startAdr
#  define Can_GetStopAdrOfShmAdr(ch)                                  CanShmStartEndAdr[(ch)].endAdr
# endif

# define Can_GetCanBasisAdr(hwch)                                     CanBasisAdr[(hwch)]
# define Can_GetCanShmAdr(hwch)                                       CanShmAdr[(hwch)]
# define Can_GetCanShmAdr_SIDFAOfCanShmAdr(hwch)                      CanShmAdr[(hwch)].SIDFA
# define Can_GetCanShmAdr_XIDFAOfCanShmAdr(hwch)                      CanShmAdr[(hwch)].XIDFA

# define Can_GetF0DSOfShmElementSize(hwch)                            CanShmElementSize[hwch]
# define Can_GetF1DSOfShmElementSize(hwch)                            CanShmElementSize[hwch]
# define Can_GetRBDSOfShmElementSize(hwch)                            CanShmElementSize[hwch]
# define Can_GetTBDSOfShmElementSize(hwch)                            CanShmElementSize[hwch]

# define CAN_C_ENABLE_MPC5700_MCAN_MAJOR_CREL                         C_ENABLE_MPC5700_MCAN_MAJOR_CREL
# define Can_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL()                    C_ENABLE_MPC5700_MCAN_MAJOR_CREL
# if defined( C_ENABLE_MPC5700_MCAN_CREL_STEP ) /* COV_CAN_HW_SPECIFIC */
#  define CAN_C_ENABLE_MPC5700_MCAN_CREL_STEP                         C_ENABLE_MPC5700_MCAN_CREL_STEP
#  define Can_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()                    C_ENABLE_MPC5700_MCAN_CREL_STEP
#  define CAN_C_ENABLE_MPC5700_MCAN_CREL_SSTEP                        C_ENABLE_MPC5700_MCAN_CREL_SSTEP
#  define Can_GetC_ENABLE_MPC5700_MCAN_CREL_SSTEP()                   C_ENABLE_MPC5700_MCAN_CREL_SSTEP
# else
#  define CAN_C_ENABLE_MPC5700_MCAN_CREL_STEP                         0
#  define Can_GetC_ENABLE_MPC5700_MCAN_CREL_STEP()                    0
#  define CAN_C_ENABLE_MPC5700_MCAN_CREL_SSTEP                        0
#  define Can_GetC_ENABLE_MPC5700_MCAN_CREL_SSTEP()                   0
#  endif

# if defined( C_ENABLE_ARM_CORTEX_M ) /* COV_CAN_HW_SPECIFIC */
#  define CAN_C_ENABLE_ARM_CORTEX_M                         C_ENABLE_ARM_CORTEX_M
#  define Can_GetC_ENABLE_ARM_CORTEX_M()                              C_ENABLE_ARM_CORTEX_M
# endif
# if defined( CAN_FD_NISO )
#  define CAN_CAN_FD_NISO                                             CAN_FD_NISO
#  define Can_GetCAN_FD_NISO()                                        CAN_FD_NISO
# else
#  define CAN_CAN_FD_NISO                                             0
#  define Can_GetCAN_FD_NISO()                                        0
# endif

# if !defined( Can_GetRxBasicHandleMax ) 
#  define Can_GetRxBasicHandleMax(ch)      ( CAN_HL_MB_RX_BASIC_STOPINDEX(ch) - CAN_HL_MB_RX_BASIC_STARTINDEX(ch) )
# endif

# define Can_GetNonFdObjectsPendingFlag(ch)                 Can_NonFdObjectsPendingFlag[(ch)]


/* *** CAN_FD mode-2 **** */
# define Can_GetShmElementSize(ch)                          CanShmElementSize[ch]
/* *** CAN_FD mode-2 **** */

# define Can_GetCanPrevMode(ch)                             CanPrevMode[(ch)]
# define Can_GetCanLastState(ch)                            CanLastState[(ch)]
# define Can_GetCanTXBRP(ch)                                CanTXBRP[(ch)]
# define Can_GetCanBusOffNotification(ch)                   CanBusOffNotification[(ch)]
# define Can_GetCanIntEnable(ch)                            CanIntEnable[(ch)]
# define Can_GetCanBTP(initObject)                          CanBTP[(initObject)]
# define Can_GetCanFBTP(initObject)                         CanFBTP[(initObject)]
# define Can_GetCanTDCR(initObject)                         CanTDCR[(initObject)]
# define Can_GetCanGFC(ch)                                  CanGFC[(ch)]
# define Can_GetCanXIDAM(ch)                                CanXIDAM[(ch)]
# define Can_GetCanRXBC(ch)                                 CanRXBC[(ch)]
# define Can_GetCanTXBC(ch)                                 CanTXBC[(ch)]
# define Can_GetCanTXEFC(ch)                                CanTXEFC[(ch)]
# define Can_GetCanRXF0C(ch)                                CanRXF0C[(ch)]
# define Can_GetCanRXF1C(ch)                                CanRXF1C[(ch)]
# define Can_GetCanSIDFC_FLSSAOfCanSIDFC(ch)                CanSIDFC[(ch)].FLSSA
# define Can_GetCanXIDFC_FLESAOfCanXIDFC(ch)                CanXIDFC[(ch)].FLESA
# define Can_GetCanSIDFC_LSSOfCanSIDFC(ch)                  CanSIDFC[(ch)].LSS
# define Can_GetCanXIDFC_LSEOfCanXIDFC(ch)                  CanXIDFC[(ch)].LSE
# define Can_GetCanSIDFE(ch)                                CanSIDFE[(ch)]
# define Can_GetCanXIDFE(ch)                                CanXIDFE[(ch)]
# define Can_GetCanSIDFEStartIndex(ch)                      CanSIDFE_StartIndex[(ch)]
# define Can_GetCanXIDFEStartIndex(ch)                      CanXIDFE_StartIndex[(ch)]
# define Can_GetCanXIDFEEIDFE_0OfCanXIDFE(ch)               CanXIDFE[(ch)].EIDFE_0
# define Can_GetCanXIDFEEIDFE_1OfCanXIDFE(ch)               CanXIDFE[(ch)].EIDFE_1
# if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS )  /* COV_CAN_HW_SPECIFIC */
#  define Can_GetCanMcanSsBaseAddr(ch)                      Can_CanMcanSsBaseAddr[(ch)]
#  define Can_GetCanEccAggrBaseAddr(ch)                     Can_CanEccAggrBaseAddr[(ch)]
# endif


# if !defined(Can_IsMailboxIndivPolling)
#  define Can_IsMailboxIndivPolling(idx)                             (Can_Mailbox[idx].HwObjPolling != 0u)
# endif

# define Can_GetLastInitObject(ch)                            lastInitObject[(ch)]

# define Shm               (Can_GetCanShmAdr(canHwChannel))
# define ShmSIDF(num)      (*((tSIFEType*) (Shm.SIDFA + GET_SIDF_OFFSET(num))))
# define ShmXIDF(num)      (*((tXIFEType*) (Shm.XIDFA + GET_XIDF_OFFSET(num))))
# define ShmRXF0(num)      (  (CanElmType*)(Shm.RXF0A + GET_RX0F_OFFSET(num)) )
# define ShmRXF1(num)      (  (CanElmType*)(Shm.RXF1A + GET_RX1F_OFFSET(num)) )
# define ShmRXB(num)       (  (CanElmType*)(Shm.RXBA  + GET_RXB_OFFSET (num)) )
# define ShmTXEF(num)      (*((tTxEventFifoElmType*)(Shm.TXEFA + GET_TXEF_OFFSET(num))))
# define ShmTXB(num)       (*((CanElmType*) (Shm.TXBA  + GET_TXB_OFFSET (num))))
# define pShmTXB(num)      ( ((CanElmType*) (Shm.TXBA  + GET_TXB_OFFSET (num))))
#endif /* CAN_30_MCAN_GEN_COM_STACK_LIB */


/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
#define C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS

#define C_30_MCAN_HL_DISABLE_HW_RANGES_FILTER

#define C_30_MCAN_HL_ENABLE_IDTYPE_IN_ID


/* Specify the ID tables which contain the ID type */
# define C_LL_RX_IDTYPE_TABLE      CanRxId0
# define C_LL_TX_IDTYPE_TABLE      CanTxId0


#define C_30_MCAN_HL_DISABLE_DUMMY_FCT_CALL


#define C_30_MCAN_HL_DISABLE_TX_MSG_DESTROYED


#define C_30_MCAN_HL_DISABLE_CANCEL_IN_HW_TASK


#define C_30_MCAN_HL_ENABLE_CAN_IRQ_DISABLE

#define C_30_MCAN_HL_DISABLE_ADJUST_RXHANDLE

#define C_30_MCAN_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_30_MCAN_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_30_MCAN_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_30_MCAN_HL_ENABLE_REJECT_ILLEGAL_DLC

#define C_30_MCAN_HL_DISABLE_COPROCESSOR_SUPPORT



#define C_30_MCAN_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

/* Possibility to disable the prototypes of interrupt service routines in the driver header file */

#define C_30_MCAN_ENABLE_TX_ACTUAL_MACROS


/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#define kCan_30_McanNumberOfUsedCanRxIdTables 0x01u
#define kCan_30_McanNumberOfUsedCanTxIdTables 0x01u


#if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
# define CanGetMcanRevision(ch)         Can_McanRevision[(ch)] /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#if defined (MISRA_CHECK) /* COV_CAN_MISRA */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_30_Mcan_HwIsStop",                 0303           /* MD_Can_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_30_Mcan_HwIsPassive",              0303           /* MD_Can_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_30_Mcan_HwIsWarning",              0303           /* MD_Can_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_30_Mcan_HwIsBusOff",               0303           /* MD_Can_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "Can_30_McanTxActualErrorCounter",        0303           /* MD_Can_HwAccess */
# pragma PRQA_MACRO_MESSAGES_OFF "Can_30_McanRxActualErrorCounter",        0303           /* MD_Can_HwAccess */
#endif
/* macros to set DLC and ID in RX-,TX-structures -------------------------- */
#define MK_RX_RANGE_MASK_IDSTD0(id)   ( MK_STDID0((id)) )
#define MK_RX_RANGE_CODE_IDSTD0(id)   ( MK_STDID0((id)) )
#define MK_RX_RANGE_MASK_IDEXT0(id)   ( MK_EXTID0((id)) & (~(kCan_30_McanIdTypeExt)) )
#define MK_RX_RANGE_CODE_IDEXT0(id)   ( MK_EXTID0((id)) )
#define MK_STDID0(id)                 (vuint32) (((vuint32)(((vuint32)(id)) << 18))       & 0x1FFC0000u)    /* Tx/Rx-Buffer   */
#define MK_EXTID0(id)                 (vuint32) ((vuint32)((id) | (vuint32)kCan_30_McanIdTypeExt) & 0x5FFFFFFFu)    /* Tx/Rx-Buffer   */


#define MK_TX_DLC(dlc)       ((tCan_30_McanDlc)((tCan_30_McanDlc)(dlc) & (tCan_30_McanDlc)0xFu))                  /* return code has to be tCanDlc (Dlc in register format) */
#define MK_TX_DLC_EXT(dlc)   ((tCan_30_McanDlc)((tCan_30_McanDlc)(dlc) & (tCan_30_McanDlc)0xFu))                  /* return code has to be tCanDlc (Dlc in register format) */

/* extract  DLC from register format to logical format */
#define XT_TX_DLC(dlc)       ((vuint8)((dlc) & 0xFu))        /* return code has to be vuint8 */



/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/
# define CanRxActualIdRaw0(rxStruct)   ((vuint32)*((Can_30_McanChipMsgPtr32)((rxStruct)->pChipMsgObj)))

/* Macros for CAN message access within Appl_30_McanCanMsgReceived() or PreCopy() function */
#if defined( C_30_MCAN_ENABLE_EXTENDED_ID )
# define CanRxActualIdExtHi(rxStruct)      ((vuint8) ( ((rxStruct)->pChipMsgObj->uB0.B0) >> 24u) & 0x1Fu)   /* return code has to be vuint8 */  
# define CanRxActualIdExtMidHi(rxStruct)   ((vuint8) ( ((rxStruct)->pChipMsgObj->uB0.B0) >> 16u))           /* return code has to be vuint8 */
# define CanRxActualIdExtMidLo(rxStruct)   ((vuint8) ( ((rxStruct)->pChipMsgObj->uB0.B0) >>  8u))           /* return code has to be vuint8 */
# define CanRxActualIdExtLo(rxStruct)      ((vuint8) ( ((rxStruct)->pChipMsgObj->uB0.B0) ))                 /* return code has to be vuint8 */
#endif

#define Can_30_McanRxActualExtId(rxStruct)          (vuint32) ( ((rxStruct)->pChipMsgObj->uB0.B0) & 0x1FFFFFFFUL)
#define Can_30_McanRxActualStdId(rxStruct)          (vuint16) ((((rxStruct)->pChipMsgObj->uB0.B0) & 0x1FFC0000UL) >> 18u)
#define CanRxActualData(rxStruct, i)               (vuint8)  ((rxStruct)->pChipData[i])                                   /* return code has to be vuint8 */
#define Can_30_McanRxActualIdType(rxStruct)         (tCan_30_McanIdType) ( ((rxStruct)->pChipMsgObj->uB0.B0) & kCan_30_McanIdTypeExt)           /* return code has to be tCanIdType */
#define Can_30_McanRxActualFdType(rxStruct)         (tCan_30_McanFdType) ((((rxStruct)->pChipMsgObj->uB1.B1) >> 16u) & kCan_30_McanFdTypeFd)    /* return code has to be tCanFdType */
                                                                                              /* (tCan_30_McanFdType)((volatile tRXMsg*)((rxStruct)->pChipMsgObj))->uR1.R1.FDF
                                                                                              R1 Bit 21 EDL: 1 = CAN FD frame format (new DLC-coding and CRC)
                                                                                              R1 Bit 20 BRS: 1 = Frame received with bit rate switching    */
#define Can_30_McanRxActualDLC(rxStruct)       (vuint8)    CAN_30_MCAN_DLC2LEN((rxStruct)->pChipMsgObj->uB1.rb1.DLC)       /* return code has to be vuint8 */ 

#if defined (C_CPUTYPE_BITORDER_LSB2MSB) /* COV_CAN_CPUTYPE */
# define CanBswap32(x)                   (vuint32)(x)
#else /* endianess */
# define CanBswap32(x)                   (vuint32)  ((((vuint32)((x) & 0xFF000000UL)) >> 24u) | \
                                                    ( ((vuint32)((x) & 0x00FF0000UL)) >>  8u) | \
                                                    ( ((vuint32)((x) & 0x0000FF00UL)) <<  8u) | \
                                                    ( ((vuint32)((x) & 0x000000FFUL)) << 24u))      /* swap b4-b3-b2-b1 to b1-b2-b3-b4 */
#endif /* endianess */

/* support reading the error counters */
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
# define Can_30_McanTxActualErrorCounter()             (vuint8)((CnX(0)->ECR) & 0x000000FFUL)
# define Can_30_McanRxActualErrorCounter()             (vuint8)(((((CnX(0)->ECR) & 0x00008000UL )) == 0x00008000UL) ? (128u) : (((CnX(0)->ECR) >> 8u) & 0x0000007FUL))
#else
# define Can_30_McanTxActualErrorCounter(ch)           (vuint8)((CnX(ch)->ECR) & 0x000000FFUL)
# define Can_30_McanRxActualErrorCounter(ch)           (vuint8)(((((CnX(ch)->ECR) & 0x00008000UL )) == 0x00008000UL) ? (128u) : (((CnX(ch)->ECR) >> 8u) & 0x0000007FUL))
#endif /* C_30_MCAN_SINGLE_RECEIVE_CHANNEL */


#if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
/* Macros for Tx HW FiFO */
# define Can_30_McanGetTxHwFifoPutIndex(ch)  CnX(ch)->TXFQS.B.TFQPI
# define Can_30_McanGetTxHwFifoGetIndex(ch)  CnX(ch)->TXFQS.B.TFGI
# define Can_30_McanGetTxHwFifoFreeLevel(ch) CnX(ch)->TXFQS.B.TFFL
# define Can_30_McanIsTxHwFifoFull(ch)      (CnX(ch)->TXFQS.B.TFQF == 1u)
#endif


/* Macros for CAN message access within GenericConfirmation() function */
/* *** Only Mirror Mode *** */
#define Can_30_McanTxActualExtId(txConfStruct)         Can_30_McanRxActualExtId(txConfStruct) 
#define Can_30_McanTxActualStdId(txConfStruct)         Can_30_McanRxActualStdId(txConfStruct)
#define CanTxActualData(txConfStruct,i)               CanRxActualData(txConfStruct,i)
#define Can_30_McanTxActualIdType(txConfStruct)        Can_30_McanRxActualIdType(txConfStruct)
#define Can_30_McanTxActualFdType(txConfStruct)        Can_30_McanRxActualFdType(txConfStruct)      
#define Can_30_McanTxActualDLC(txConfStruct)           (vuint8)  CAN_30_MCAN_DLC2LEN((txConfStruct)->pChipMsgObj->uB1.tb1.DLC)

/* Macros for CAN message access within PreTransmit() function */


/* Macros for Message and CAN buffer access (mostly used by upper layers but also available for usage by the application) */
/* Message buffers (for each message ID) */



#define CAN_30_MCAN_HL_MIN(x, y) (((x)>(y)) ? (y) : (x))
#define CAN_30_MCAN_HL_MAX(x, y) (((x)<(y)) ? (y) : (x))

/***************************************************************************************************/
/* Macros for dummy statements */
#if !defined(CAN_30_MCAN_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_30_MCAN_DUMMY_STATEMENT(x) (x) = (x) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# else
#  define CAN_30_MCAN_DUMMY_STATEMENT(x)
# endif
#endif
#if !defined(CAN_30_MCAN_DUMMY_STATEMENT_CONST) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_30_MCAN_DUMMY_STATEMENT_CONST(x) (void)(x)
# else
#  define CAN_30_MCAN_DUMMY_STATEMENT_CONST(x)
# endif
#endif

/***************************************************************************************************/
/* Macros for DET and assertions */
#if (CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON) /* \trace SPEC-1404, SPEC-1696 */
/* \trace SPEC-1725, SPEC-1403, SPEC-1568 */
# define Can_30_Mcan_CallDetReportError(api, err) ((void) Det_ReportError(CAN_30_MCAN_MODULE_ID, CAN_30_MCAN_INSTANCE_ID, (api), (err)))
# define assertHardware(a, b, c)  if (!(a)) {Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_30_Mcan_CallDetReportError(CAN_30_MCAN_HW_ACCESS_ID, (c));}
# define C_30_MCAN_ENABLE_HARDWARE_CHECK
# define C_30_MCAN_ENABLE_INTERNAL_CHECK
# define C_30_MCAN_ENABLE_USER_CHECK
# define C_30_MCAN_ENABLE_GEN_CHECK
#else
# define Can_30_Mcan_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif

/***************************************************************************************************/
/* Macros for Critical Area 0 abstraction */

#define Can_30_McanDeclareGlobalInterruptOldStatus
/* CAN_30_MCAN_EXCLUSIVE_AREA_0 called only by LL code */
#define Can_30_McanSingleGlobalInterruptDisable()     SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()
#define Can_30_McanSingleGlobalInterruptRestore()     SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()
#define Can_30_McanGlobalInterruptDisable()           SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()
#define Can_30_McanGlobalInterruptRestore()           SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()
#define Can_30_McanNestedGlobalInterruptDisable()     SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()
#define Can_30_McanNestedGlobalInterruptRestore()     SchM_Exit_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0()

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */


/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* Defines / data types / structures / unions                              */
/***************************************************************************/
/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */
/* Note: When the M_CAN addresses the Message RAM it addresses 32-bit words, not single bytes. */

#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
# if( kCan_30_McanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
# elif ( kCan_30_McanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
# elif ( kCan_30_McanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
# elif ( kCan_30_McanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
# else
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
# endif
#endif

#if( kCan_30_McanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
#elif ( kCan_30_McanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
#elif ( kCan_30_McanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
#elif ( kCan_30_McanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
#else
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
#endif

/***************************************************************************/
/* Core - LowLevel API                                                     */
/***************************************************************************/
typedef struct sCan_30_McanRxInfoStruct
{
  Can_30_McanChipMsgPtr     pChipMsgObj;
  Can_30_McanChipDataPtr    pChipData;
  Can_30_McanObjectHandle   localMailboxHandle; 
  Can_IdType               localId; 
  uint8                    localDlc;
  /* LL specific part */
} tCan_30_McanRxInfoStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanRxInfoStruct, VAR_NOINIT) CanRxInfoStructPtr;

typedef struct sCan_30_McanTxConfInfoStruct
{
  Can_30_McanChipMsgPtr     pChipMsgObj;
  Can_30_McanChipDataPtr    pChipData;
  /* LL specific part */
  tAlign32bit     tmpTXB; /* PRQA S 0759 */ /* MD_Can_Union */
} tCan_30_McanTxConfInfoStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanTxConfInfoStruct, VAR_NOINIT) Can_30_McanTxConfInfoStructPtr;

typedef struct sCan_30_McanInitParaStruct
{
  Can_30_McanInitHandle     initObject;
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   hwObjHandle;
#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
  tCan_30_McanRxId0                idRaw0;
# if( kCan_30_McanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanRxId1                idRaw1;
# endif
# if( kCan_30_McanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanRxId2                idRaw2;
# endif
# if( kCan_30_McanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanRxId3                idRaw3;
# endif
# if( kCan_30_McanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanRxId4                idRaw4;
# endif
  tCan_30_McanIdType               idType;
#endif
#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
  uint8                    doRamCheck;
# if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
  uint8                    isChRamCheckFail;
# endif
#endif
  uint8                    isInitOk;
  /* LL specific part */
  vuint32 ie;     /* INT enable/disable control */
  vuint32 canInterruptOldStatus; /* Stores the current interrupt configuration when entering init */
  vuint32 txbtie; /* TXBTIE, TXBCIE enable/disable control */
  #if defined( C_30_MCAN_ENABLE_STD_ID )
  # if (kCanNumberOfStandardFilter > 0)  /* at least one std filter available */
  V_DEF_30_MCAN_P2CONST(V_NONE, Can_30_Mcan_SIDFEType, AUTOMATIC, CONST_PBCFG) pFS;
  # endif
  vuint16 stdFeCount;
  #endif
  #if defined( C_30_MCAN_ENABLE_EXTENDED_ID )
  vuint16 extFeCount;
  #endif
  vuint32 tmpVal;
  V_DEF_30_MCAN_P2VAR(V_NONE, Can_30_McanElmType, AUTOMATIC, VAR_NOINIT) pTXB; /* pointer to TxBuffer */
  
  
} tCan_30_McanInitParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanInitParaStruct, VAR_NOINIT) CanInitParaStructPtr;

#define TxDataPtr Can_SduPtrType /* CBD compatibility */
typedef struct sCan_30_McanTxTransmissionParaStruct
{
  /* logical formats */
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  Can_30_McanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  Can_30_McanObjectHandle   activeSendObject; /* index of the logical Tx mailbox (Tx * Element) */
  tCan_30_McanTxId0                idRaw0;
#if( kCan_30_McanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanTxId1                idRaw1;
#endif
#if( kCan_30_McanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanTxId2                idRaw2;
#endif
#if( kCan_30_McanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanTxId3                idRaw3;
#endif
#if( kCan_30_McanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCan_30_McanTxId4                idRaw4;
#endif
  tCan_30_McanDlc                  dlcRaw;
  TxDataPtr                CanMemCopySrcPtr;
#if defined( C_30_MCAN_ENABLE_CAN_FD_USED )
  tCan_30_McanFdType               fdType;
  tCan_30_McanFdBrsType            fdBrsType;
  uint8                    messageLen;
  uint8                    frameLen;
  uint8                    paddingVal;
#endif
  Can_PduType              pdu;
  /* LL specific part */
  Can_30_McanElmType*      lpTXB;
  #if defined( C_30_MCAN_ENABLE_PRETRANSMIT_FCT ) 
  tAlign32bit     tmpTXB; /* PRQA S 0759 */ /* MD_Can_Union */
  #endif
} tCan_30_McanTxTransmissionParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanTxTransmissionParaStruct, VAR_NOINIT) CanTxTransmissionParaStructPtr;

typedef struct sCan_30_McanRxBasicParaStruct
{
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   hwObjHandle;
#if !defined( C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS ) && defined( C_30_MCAN_ENABLE_OVERRUN )
#endif
  tCan_30_McanRxInfoStruct         rxStruct;
  /* LL specific part */
  V_DEF_30_MCAN_P2VAR(V_NONE,   Can_30_McanElmType, AUTOMATIC, VAR_NOINIT) pShm;        /* shared message RAM   */
  V_DEF_30_MCAN_P2VAR(volatile, vuint32,    AUTOMATIC, VAR_NOINIT) pFifoAck;    /* Fifo acknowledge register (RXFnA) */
  V_DEF_30_MCAN_P2VAR(volatile, t_30_McanRXFnS,     AUTOMATIC, VAR_NOINIT) pFifoStatus; /* Fifo status register (RXFnS) */
  Can_30_McanElmType fElm;
  vuint8     fGetIndex;
} tCan_30_McanRxBasicParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanRxBasicParaStruct, VAR_NOINIT) CanRxBasicParaStructPtr;

typedef struct sCan_30_McanRxFullParaStruct
{
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   hwObjHandle;
  tCan_30_McanRxInfoStruct         rxStruct;
  /* LL specific part */
  V_DEF_30_MCAN_P2VAR(V_NONE, Can_30_McanElmType, AUTOMATIC, VAR_NOINIT) pShm;        /* shared message RAM   */
  vuint16    objectNumber;
  Can_30_McanElmType bfElm;
} tCan_30_McanRxFullParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanRxFullParaStruct, VAR_NOINIT) CanRxFullParaStructPtr;

#if defined( C_30_MCAN_ENABLE_CANCEL_SUPPORT_API )
typedef struct
{
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  Can_30_McanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  Can_30_McanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
  Can_30_McanTransmitHandle   canHandleCurTxObj;
} tCan_30_McanTxCancellationParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanTxCancellationParaStruct, VAR_NOINIT) CanTxCancellationParaStructPtr;
#endif

typedef struct
{
  Can_30_McanObjectHandle   mailboxHandle;
  Can_30_McanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  Can_30_McanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  Can_30_McanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
  Can_30_McanTxConfInfoStructPtr   txStructConf;
#endif
  tAlign32bit tmpTXB; /* PRQA S 0759 */ /* MD_Can_Union */
} tCan_30_McanTxConfirmationParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanTxConfirmationParaStruct, VAR_NOINIT) CanTxConfirmationParaStructPtr;

typedef struct sCan_30_McanTaskParaStruct
{
  Can_30_McanObjectHandle mailboxHandle;
  Can_30_McanObjectHandle hwObjHandle;
  /* LL specific part */
} tCan_30_McanTaskParaStruct;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, tCan_30_McanTaskParaStruct, VAR_NOINIT) CanTaskParaStructPtr;
    
/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define CAN_30_MCAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
/************************************************************************************************************
 *  CanLL_30_Mcan_InitVirtualAddr()
 ***********************************************************************************************************/
/*! \brief         Initialize virtual address space
 *  \details       Initialize the virtual address space of the controller base address
 *  \param[in]     Controller       CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitVirtualAddr(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

# if defined (C_30_MCAN_ENABLE_CANSUBSYSTEMBASEADR) /* COV_CAN_HW_SPECIFIC */
/************************************************************************************************************
 *  CanLL_30_Mcan_InitSubSystemVirtualAddr()
 ***********************************************************************************************************/
/*! \brief         Initialize virtual address space
 *  \details       Initialize the virtual address space of the CAN subsystem(s).
 *  \param[in]     -
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitSubSystemVirtualAddr(void);
/* CODE CATEGORY 4 END */
# endif

# if defined (C_30_MCAN_ENABLE_CANGLOBALBASEADR) /* COV_CAN_HW_SPECIFIC */
/************************************************************************************************************
 *  CanLL_30_Mcan_InitGlobalVirtualAddr()
 ***********************************************************************************************************/
/*! \brief         Initialize virtual address space
 *  \details       Initialize the virtual address space of the global CAN module.
 *  \param[in]     -
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitGlobalVirtualAddr(void);
/* CODE CATEGORY 4 END */
# endif
#endif

/************************************************************************************************************
 *  CanLL_30_Mcan_WriteReg32()
 ***********************************************************************************************************/
/*! \brief         Write value and do RamCheck
 *  \details       Write the value of the hardware mailbox or controller register and read back for RamCheck. 
 *                 set initPara->isChRamCheckFail or initPara->isMbRamCheckFail in case of an HW issue to deactivate hardware.
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     regPtr           valid pointer to Register to be written.
 *  \param[in]     value            value to be written.
 *  \param[in]     readMask         mask to check the read back value.
 *  \param[in]     doRamCheck       execute the RAM check (kCan_30_McanExecuteRamCheck, kCan_30_McanSuppressRamCheck).
 *  \return        kCan_30_McanTrue         RamCheck failed.
 *  \return        kCan_30_McanFalse        RamCheck passed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_WriteReg32(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST Can_30_McanChipMsgPtr32 regPtr, vuint32 value, vuint32 readMask, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */


/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBegin()
 *********************************************************************************************************************/
/*! \brief         Starts the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBegin( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBeginIsRegisterCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanFalse           No corrupt register RAM found
 *                 kCan_30_McanTrue            Register RAM is considered corrupt or failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginIsRegisterCorrupt(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
/************************************************************************************************************
 *  CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       check the extra channel registers at the beginning of the initialization by write and read back patterns.
 *  \param[in]     Controller          CAN controller
 *  \return        kCan_30_McanTrue:    Channel is corrupt
 *  \return        kCan_30_McanFalse:   Channel is not corrupt  
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginIsRegisterCorrupt_REGEXT(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

#endif

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitBeginSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitBeginSetRegisters( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxTx()
 *********************************************************************************************************************/
/*! \brief         Initializes a transmit mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxTx( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxTxDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a transmit mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxTxDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif


#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxFullCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive FullCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxFullCan( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxFullCanDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a receive FullCAN mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxFullCanDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif

#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxBasicCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive BasicCAN mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxBasicCan( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if ((defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )))
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a receive BasicCAN mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMailboxRxBasicCanDeactivate( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEndIsRegisterCorrupt()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel register RAM check
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanFalse           No corrupt register RAM found
 *                 kCan_30_McanTrue            Register RAM is considered corrupt or failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEndIsRegisterCorrupt( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEndSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel register initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEndSetRegisters( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );  /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitEnd()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel initialization
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitEnd( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitIsMailboxCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the RAM check for a mailbox
 *  \details       Called by CanInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanInit()
 *  \return        kCan_30_McanFalse           Mailbox is not corrupt
 *                 kCan_30_McanTrue            Mailbox is considered corrupt or failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_30_Mcan_InitIsMailboxCorrupt( CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif


/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitPowerOn()
 *********************************************************************************************************************/
/*! \brief         Performs the hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitMemoryPowerOn()
 *********************************************************************************************************************/
/*! \brief         Internal function, called by Can_InitMemory().
 *  \details       Performs the platform specific memory initialization.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_InitMemoryPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_InitPowerOnChannelSpecific()
 *********************************************************************************************************************/
/*! \brief         Performs the channel dependent hardware specific global module initialization
 *  \details       Called by CanInitPowerOn()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_InitPowerOnChannelSpecific( CAN_30_MCAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxBegin()
 *********************************************************************************************************************/
/*! \brief         Perform start of transmission
 *  \details       Called by transmission to prepare send object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxSetMailbox()
 *********************************************************************************************************************/
/*! \brief         Set mailbox data for transmission
 *  \details       Called by transmission to set ID, DLC
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxSetMailbox(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxCopyToCan()
 *********************************************************************************************************************/
/*! \brief         Set mailbox data for transmission
 *  \details       Called by transmission to set data part in mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxCopyToCan(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxStart()
 *********************************************************************************************************************/
/*! \brief         Trigger mailbox to start the transmission
 *  \details       Called by transmission to start transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \return        kCan_30_McanOk              No issue
 *                 kCan_30_McanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_TxStart(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxEnd()
 *********************************************************************************************************************/
/*! \brief         Perform end handling of the transmission
 *  \details       Called by transmission to finish transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */
#if defined( C_30_MCAN_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxIsGlobalConfPending()
 *********************************************************************************************************************/
/*! \brief         Check global pending of transmission
 *  \details       Called by transmission to get global pending flag
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue            pending confirmation
 *                 kCan_30_McanFailed          no pending confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_TxIsGlobalConfPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check pending of transmission object
 *  \details       Called by transmission to get pending flag of mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of confirmation task
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
#endif
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfBegin()
 *********************************************************************************************************************/
/*! \brief         Perform start of confirmation
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfSetTxConfStruct()
 *********************************************************************************************************************/
/*! \brief         Set confirmation struct
 *  \details       Called by confirmation to set confirmation data struct
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfSetTxConfStruct(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#endif
/**********************************************************************************************************************
 *  CanLL_30_Mcan_TxConfSetTxConfStruct()
 *********************************************************************************************************************/
/*! \brief         Perform confirmation end handling
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_TxConfEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */

#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Perform BasicCAN receive begin
 *  \details       Called by reception to begin handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \return        kCan_30_McanOk              No Issue occur
 *                 kCan_30_McanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicMsgReceivedBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Release BasicCAN mailbox
 *  \details       Called by reception to release object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicReleaseObj(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Release BasicCAN receive end
 *  \details       Called by reception to finish handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicMsgReceivedEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */
# if defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Check BasicCAN receive global pending
 *  \details       Called by reception to get pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue            global pending
 *                 kCan_30_McanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicIsGlobalIndPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check BasicCAN receive pending
 *  \details       Called by reception to get mailbox pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \return        kCan_30_McanTrue            mailbox pending
 *                 kCan_30_McanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxBasicProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
# endif /* C_30_MCAN_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */
#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Perform FullCAN receive begin
 *  \details       Called by reception to begin handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \return        kCan_30_McanOk              No Issue occur
 *                 kCan_30_McanFailed          Issue occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxFullMsgReceivedBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Release FullCAN mailbox
 *  \details       Called by reception to release object
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullReleaseObj(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Release FullCAN receive end
 *  \details       Called by reception to finish handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullMsgReceivedEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */
# if defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Check FullCAN receive global pending
 *  \details       Called by reception to get pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue            global pending
 *                 kCan_30_McanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxFullIsGlobalIndPending(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxFullProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Check FullCAN receive pending
 *  \details       Called by reception to get mailbox pending state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \return        kCan_30_McanTrue            mailbox pending
 *                 kCan_30_McanFailed          no pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_RxFullProcessPendings(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
# endif /* C_30_MCAN_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING) 
/************************************************************************************************************
 *  CanLL_30_Mcan_GetLastErrorCode()
 ***********************************************************************************************************/
/*! \brief         Report last error code  
 *  \details       Check the value of the last error code in the protocol status register
 *  \param[in]     channel   Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanPSR_LEC_NO_ERROR          No Error
 *                 kCanPSR_LEC_Stuff_ERROR       Stuff Error
 *                 kCanPSR_LEC_FORM_ERROR        Form Error
 *                 kCanPSR_LEC_ACK_ERROR         Ack Error
 *                 kCanPSR_LEC_BIT1_ERROR        Bit1 Error
 *                 kCanPSR_LEC_BIT0_ERROR        Bit0 Error
 *                 kCanPSR_LEC_CRC_ERROR         CRC Error
 *                 kCanPSR_LEC_NO_UPDATE         No Change in PSR error state
 * \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_GetLastErrorCode(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorStatePassiveTransitionOccurred()
 *********************************************************************************************************************/
/*! \brief         Error state passive check
 *  \details       Checks if a transition to error state passive occurred
 *  \param[in]     channel   Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue    Transition to passive occurred
 *                 kCan_30_McanFailed  Transition to passive has not occurred 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_ErrorStatePassiveTransitionOccured(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorNotificationHandling()
 *********************************************************************************************************************/
/*! \brief         Perform error notification handling for IDsM
 *  \details       Checks the Rx and Tx Errors in the controller and reports to Core
 *  \param[in]     channel   Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorNotificationHandling(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#endif /* CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING */

/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorHandlingBegin()
 *********************************************************************************************************************/
/*! \brief         Perform error handling begin
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorHandlingBegin(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_BusOffOccured()
 *********************************************************************************************************************/
/*! \brief         Check BusOff occur
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue            BusOff occur
 *                 kCan_30_McanFailed          no BusOff occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_BusOffOccured(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

#if defined( C_30_MCAN_HL_ENABLE_OVERRUN_IN_STATUS )    /* COV_CAN_OVERRUN_IN_STATUS */
# if defined( C_30_MCAN_ENABLE_OVERRUN ) && defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS)
/**********************************************************************************************************************
 *  CanLL_30_Mcan_RxBasicCanOverrun()
 *********************************************************************************************************************/
/*! \brief         Check BasicCAN overrun occur
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCan_30_McanTrue            Overrun occur
 *                 kCan_30_McanFailed          no Overrun occur
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_RxBasicCanOverrun(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
# endif
#endif


/**********************************************************************************************************************
 *  CanLL_30_Mcan_ErrorHandlingEnd()
 *********************************************************************************************************************/
/*! \brief         Perform error handling end
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_ErrorHandlingEnd(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#if defined( C_30_MCAN_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_30_Mcan_GetStatusBegin()
 *********************************************************************************************************************/
/*! \brief         Perform read out of status information
 *  \details       Called by GetStatus API
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_GetStatusBegin(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 3 END */
#endif
/**********************************************************************************************************************
 *  CanLL_30_Mcan_ModeTransition()
 *********************************************************************************************************************/
/*! \brief         Perfrom mode change
 *  \details       Called by mode handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in]     mode                mode to be set
 *  \param[in]     busOffRecovery      BusOff recovery should be done or not
 *  \param[in]     ramCheck            RamCheck should be done or not
 *  \return        kCan_30_McanOk              Successfully completed
 *                 kCan_30_McanRequested       Mode not yet reached
 *                 kCan_30_McanFailed          Failure occurred
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck);
/* CODE CATEGORY 4 END */
/**********************************************************************************************************************
 *  CanLL_30_Mcan_StopReinit()
 *********************************************************************************************************************/
/*! \brief         Perform reinitialization for mode change
 *  \details       Called by mode handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_StopReinit(CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_CAN_CAN_INTERRUPT_CONTROL )   /* COV_CAN_LOCK_ISR_BY_APPL */
/************************************************************************************************************
 *  CanLL_30_Mcan_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         Disables CAN interrupts.
 *  \details       Stores current state and disables the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              CAN channel
 *  \param[out]    localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_CanInterruptDisable(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST tCan_30_McanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 1 END */

/************************************************************************************************************
 *  CanLL_30_Mcan_CanInterruptRestore()
 ***********************************************************************************************************/
/*! \brief         Restores CAN interrupts.
 *  \details       Restores the previous state of the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              CAN channel
 *  \param[in]     localInterruptOldFlag     Global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_CanInterruptRestore(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST tCan_30_McanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 1 END */
#endif





/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanBoschErratum_010()
 ***********************************************************************************************************/
/*! \brief         Restart Tx FSM after erratum_010 appeared (When CCCR.CCE is set while a Tx scan is in progress the Tx Handler FSM stops.)
 *  \details       1) Cancel all pending transmission requests, 
 *                 2) Issue a clock stop request
 *                 3) Wait until Clock Stop Acknowledge
 *                 4) Go back to Normal Operation (First reset CCCR.CSR, then reset CCCR.INIT)
 *                 5) Issue a second clock stop request
 *                 6) Await Clock Stop Acknowledge
 *                 7) Set CCCR.CCE and reset CCCR.CSR
 *  \param[in]     Controller   CAN controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
#if ( CAN_BOSCH_ERRATUM_010 == STD_ON ) /* COV_CAN_ERRATUM_OFF */
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanBoschErratum_010( CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY );
#endif
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetAllFilter()
 ***********************************************************************************************************/
/*! \brief         Write the hardware filters into the Message RAM
 *  \details       Write standard and extended filter information for each CAN channel into the Message RAM
 *  \param[in]     Controller   CAN controller
 *  \return        kCan_30_McanOk     Filters succesful set
 *  \return        kCan_30_McanFailed Filters could not be set
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8,   STATIC_CODE) CanLL_30_Mcan_SetAllFilter( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ); /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetAllRegister()
 ***********************************************************************************************************/
/*! \brief         Initialize MCAN configuration registers
 *  \details       Assure that MCAN is in configuration enable mode and fill in all configuration relevant registers
 *  \param[in]     Controller   CAN controller
 *  \param[in]     initInfo     CAN controller configuration data
 *  \return        kCan_30_McanOk     Registers succesful set
 *  \return        kCan_30_McanFailed Registers could not be set
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_SetAllRegister( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetRegisterMcanSS()
 ***********************************************************************************************************/
/*! \brief         Initialize McanSS specific registers
 *  \details       Assure that the platform specific additional functionality is configured correctly and that all aditional registers are initialized.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void,   STATIC_CODE) CanLL_30_Mcan_SetRegisterMcanSS( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo );
/* CODE CATEGORY 4 END */
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetRegisterSICanFD()
 ***********************************************************************************************************/
/*! \brief         Initialize SICanFD specific registers
 *  \details       Assure that the platform specific additional functionality is configured correctly and that all aditional registers are initialized.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void,   STATIC_CODE) CanLL_30_Mcan_SetRegisterSICanFD( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo );
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetRegisterTTCanFD()
 ***********************************************************************************************************/
/*! \brief         Initialize TTCanFD specific registers
 *  \details       Assure that the platform specific additional functionality is configured correctly and that all aditional registers are initialized.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void,   STATIC_CODE) CanLL_30_Mcan_SetRegisterTTCanFD( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo );
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_SHM_DATAQOS ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetRegisterDataQoS()
 ***********************************************************************************************************/
/*! \brief         Initialize Shared Message Ram Quality of Service Specific Registers
 *  \details       Assure that the platform specific additional functionality is configured correctly and that all aditional registers are initialized.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void,   STATIC_CODE) CanLL_30_Mcan_SetRegisterDataQoS( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr localInfo );
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetGlobalRegisterTTCanFD()
 ***********************************************************************************************************/
/*! \brief         Initialize TTCanFD SubSystems
 *  \details       Implement extra requirements related to initialization of CAN subsystems
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterTTCanFD(void);
/* CODE CATEGORY 4 END */
#endif

#if ( CAN_30_MCAN_SAFE_BSW == STD_ON ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_CheckGeneratedData()
 ***********************************************************************************************************/
/*! \brief         SAFE BSW checks
 *  \details       Check size of the generated tables in case of SAFE BSW 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_CheckGeneratedData(void);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetGlobalRegisterMcanAS1()
 ***********************************************************************************************************/
/*! \brief         Initialize McanAS1 SubSystems
 *  \details       Implement extra requirements related to initialization of CAN subsystems
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterMcanAS1(void);
/* CODE CATEGORY 4 END */
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetGlobalRegisterStmFdCan()
 ***********************************************************************************************************/
/*! \brief         Initialize StmFdCan CCU Global Register
 *  \details       Implement extra requirements related to initialization of CAN subsystems
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterStmFdCan(void);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TCC ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_SetGlobalRegisterTCC()
 ***********************************************************************************************************/
/*! \brief         Initialize TCC80XX Global Can CFG Register
 *  \details       Implement extra requirements related to initialization of CAN subsystems
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_30_Mcan_SetGlobalRegisterTCC(void);
/* CODE CATEGORY 4 END */
#endif

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_StartRequest()
 ***********************************************************************************************************/
/*! \brief         Start mode transition from STOP to NORMAL
 *  \details       Check the current state and trigger the transition to Normal Operation mode if necessary
 *  \param[in]     Controller       CAN controller
 *  \return        kCan_30_McanOk:          Normal Mode already reached
 *  \return        kCan_30_McanRequested:   Transition to Normal Mode requested 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StartRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined(C_30_MCAN_ENABLE_SILENT_MODE) 
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_StartSilentRequest()
 ***********************************************************************************************************/
/*! \brief         Start mode transition from STOP to NORMAL
 *  \details       Check the current state and trigger the transition to Normal/Silent Operation mode if necessary
 *  \param[in]     Controller       CAN controller
 *  \return        kCan_30_McanOk:          Normal/Silent Mode already reached
 *  \return        kCan_30_McanRequested:   Transition to Normal/Silent Mode requested 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StartSilentRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_StopRequest()
 ***********************************************************************************************************/
/*! \brief         Stop mode transition from NORMAL to STOP
 *  \details       Check the current state and trigger the transition to Stop mode if necessary
 *  \param[in]     Controller       CAN controller
 *  \return        kCan_30_McanOk:          Stop Mode already reached
 *  \return        kCan_30_McanRequested:   Transition to Stop Mode requested 
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_30_Mcan_StopRequest(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanLL_30_Mcan_if_TxIsObjConfPending()
 ***********************************************************************************************************/
/*! \brief         Check for pending Tx confirmations
 *  \details       Check all Tx objects within the configuration for any pending confirmation or cancellation
 *  \param[in]     Controller   CAN controller
 *  \param[in]     txBuffer     Buffer requests pending
 *  \return        kCan_30_McanTrue:    at least one request pending
 *  \return        kCan_30_McanFalse:   no request is pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
#if defined(C_30_MCAN_ENABLE_TX_POLLING)
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint32, STATIC_CODE) CanLL_30_Mcan_if_TxIsObjConfPending( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST vuint32 txBuffer );
#endif
/* CODE CATEGORY 4 END */

#if( CAN_BOSCH_ERRATUM_012 == STD_ON )  /* COV_CAN_ERRATUM_OFF */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanInterruptTimeoutCounter()
 ***********************************************************************************************************/
/*! \brief         Protocol exception handling
 *  \details       check for protocol error and try to proceed if an exception appeared
 *  \param[in]     Controller   CAN controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void,   STATIC_CODE) CanInterruptTimeoutCounter(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif /* End CAN_BOSCH_ERRATUM_012 */

/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanErrorHandlingBusOff()
 ***********************************************************************************************************/
/*! \brief         BusOff detection and handling 
 *  \details       check the MCAN BusOff state,Message RAM access error and failure handling
 *  \param[in]     Controller   CAN controller
 *  \return        kCan_30_McanTrue:    Channel is in BusOff state
 *  \return        kCan_30_McanFalse:   Channel is not in BusOff state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanErrorHandlingBusOff(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined( C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS )
# if !defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING ) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )         /* ISR necessary; no pure polling configuration */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanBasicInterruptRx()
 ***********************************************************************************************************/
/*! \brief         Rx interrupt detection and handling 
 *  \details       Check the Rx buffer and Rx FIFO(s) for new data and call the appropriate CanMsgReceived function.
 *  \param[in]     Controller   CAN controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanBasicInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif /* C_30_MCAN_ENABLE_RX_BASICCAN_POLLING || C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS )
# if !defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanInterruptFullRx()
 ***********************************************************************************************************/
/*! \brief         Rx interrupt detection and handling 
 *  \details       Check the Rx buffer and Rx FIFO(s) for new data and call the appropriate CanMsgReceived function.
 *  \param[in]     Controller   CAN controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanFullInterruptRx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif /* C_30_MCAN_ENABLE_RX_FULLCAN_POLLING || C_30_MCAN_ENABLE_INDIVIDUAL_POLLING */
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if !defined(C_30_MCAN_ENABLE_ERROR_POLLING)
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanInterruptErrorHandling()
 ***********************************************************************************************************/
/*! \brief         Error detection and handling
 *  \details       Check the MCAN error states and perform error handling
 *  \param[in]     Controller   CAN controller
 *  \return        kCan_30_McanOk:      No error detected for the channel
 *  \return        kCan_30_McanFailed:  Error detected for the channel
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanInterruptErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if !defined(C_30_MCAN_ENABLE_TX_POLLING) || defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  CanInterruptTx()
 ***********************************************************************************************************/
/*! \brief         Check the transmit status
 *  \details       Check the MCAN transmit status and perform status/transmission handling
 *  \param[in]     Controller   CAN controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanInterruptTx(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM ) /* COV_CAN_HW_SPECIFIC */
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Can_EccInit()
 ***********************************************************************************************************/
/*! \brief         Initialize the message RAM
 *  \details       Initializes the used parts of the message RAM for all active channels.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) Can_EccInit(void); /* PRQA S 3447 */ /* MD_Can_ExternalScope */
/* CODE CATEGORY 4 END */
#else
# define Can_EccInit() Appl_30_McanCanEccInit() /* Application Callout to init the CAN Message RAM */
#endif  /* C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM */

/************************************************************************************************************
 *  CanHL_30_Mcan_CleanUpSendState()
 ***********************************************************************************************************/
/*! \brief         Clean up send state
 *  \details       Reset active send state (semaphore blocking TX while send).
 *                 Called by Can_30_Mcan_SetControllerMode(), Can_30_Mcan_MainFunction_Mode() (CanHL_30_Mcan_ReInit() do same but without this call).
 *  \param[in]     Controller    CAN controller \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_CleanUpSendState(CAN_30_MCAN_CHANNEL_CANTYPE_ONLY);

# if (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_OFF)
/************************************************************************************************************
 *  Appl_30_McanCanTimerLoop()
 ***********************************************************************************************************/
/*! \brief         Time out monitoring
 *  \details       Service function to check (against generated maximum loop value) whether a hardware loop shall be continued or broken.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \return        CAN_NOT_OK  when loop shall be broken (observation stops) \n
 *                             CAN_NOT_OK should only be used in case of a time out occurs due to a hardware issue. \n
 *                             After this an appropriate error handling is needed (see chapter Hardware Loop Check / Time out Monitoring).
 *  \return        CAN_OK      when loop shall be continued (observation continues)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Please refer to chapter "Hardware Loop Check".
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) Appl_30_McanCanTimerLoop(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif

/************************************************************************************************************
 *  CanHL_30_Mcan_ModeTransition()
 ***********************************************************************************************************/
/*! \brief         Request mode transition
 *  \details       Handle/Request transition and wait asynchronous-short time.
 *                 Called by Can_30_Mcan_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     transitionRequest  transition request used to switch mode (kCan_30_McanModeInit, kCan_30_McanModeSleep, kCan_30_McanModeWakeupStopReinit, \n
 *                                    kCan_30_McanModeStopReinit, kCan_30_McanModeStopReinitFast, kCan_30_McanModeStart, kCan_30_McanModeStartReinit, kCan_30_McanModeSilent, \n
 *                                    kCan_30_McanModeResetBusOffStart, kCan_30_McanModeResetBusOffEnd). \n
 *  \param[in]     busOffRecovery     handling of the busoff behaviour (kCan_30_McanFinishBusOffRecovery, kCan_30_McanContinueBusOffRecovery). \n
 *  \param[in]     doRamCheck         do a RAM check while reinit or not (kCan_30_McanExecuteRamCheck, kCan_30_McanSuppressRamCheck). \n
 *  \return        kCan_30_McanFailed         transition rejected
 *  \return        kCan_30_McanRequested      transition requested but is ongoing asynchronous
 *  \return        kCan_30_McanOk             transition finished successful
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_ModeTransition(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck);

/************************************************************************************************************
 *  CanHL_30_Mcan_NotifyTransition()
 ***********************************************************************************************************/
/*! \brief         notify about sucessful mode transition
 *  \details       notify to upper layer.
 *                 Called by Can_30_Mcan_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     canState           CAN controller mode to be switched to (CAN_STATUS_STOP, CAN_STATUS_START, CAN_STATUS_SLEEP). \n
 *  \param[in]     canIfState         CAN controller mode to be switched to (CANIF_CS_STOPPED, CANIF_CS_STARTED, CANIF_CS_SLEEP). \n
 *  \param[in]     transitionState    transition request state (kCan_30_McanFailed, kCan_30_McanRequested, kCan_30_McanOk). \n
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_NotifyTransition(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState);


/************************************************************************************************************
 *  CanHL_30_Mcan_WritePrepare()
 ***********************************************************************************************************/
/*! \brief         TX preparation
 *  \details       Search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary.
 *                 calculate txPara member activeSendObject, and mailboxElement
 *                 Called by Can_30_Mcan_Write().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in,out] txPara           mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_WritePrepare(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

#if (defined(C_30_MCAN_ENABLE_TX_HW_FIFO) && defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/************************************************************************************************************
 *  CanHL_30_Mcan_WriteSavePduInfo()
 ***********************************************************************************************************/
/*! \brief         Save PduInfo before send
 *  \details       Cancellation or TxHwFifo need to save send data to get this information in confirmation context.
 *  \param[in,out] txPara                    mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_WriteSavePduInfo(CanTxTransmissionParaStructPtr txPara);
#endif


/************************************************************************************************************
 *  CanHL_30_Mcan_WriteStart()
 ***********************************************************************************************************/
/*! \brief         TX start
 *  \details       Write ID, DLC and Data to FullCAN or BasicCAN object and set transmit request
 *                 Called by Can_30_Mcan_Write().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in,out] txPara          mailbox information
 *  \return        CAN_NOT_OK      transmission failed.
 *  \return        CAN_OK          transmission successful.
 *  \return        CAN_BUSY        transition object busy - repeat it.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_30_Mcan_WriteStart(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

/************************************************************************************************************
 *  CanHL_30_Mcan_GetActiveSendObject()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        logical handle for the given hardware mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, Can_30_McanObjectHandle, STATIC_CODE) CanHL_30_Mcan_GetActiveSendObject(Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement);

#if (defined(C_30_MCAN_ENABLE_TX_HW_FIFO) && defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/************************************************************************************************************
 *  CanHL_30_Mcan_GetActiveSendData()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        start index in the data buffer for the given mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_30_Mcan_GetActiveSendData(Can_HwHandleType mailboxHandle, uint8 mailboxElement);
#endif

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_30_Mcan_RamCheckMailboxNotification()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \param[in]     htrh             Hrh or Hth of the hardware object
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RamCheckMailboxNotification(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_30_Mcan_InitBegin()
 ***********************************************************************************************************/
/*! \brief         Start Initialization
 *  \details       LL implementation see token CanLL_30_Mcan_InitBegin description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitBegin(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_30_Mcan_InitTxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX FullCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitTxFullCAN(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_30_Mcan_InitTxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX BasicCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitTxBasicCAN(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);


#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_30_Mcan_InitRxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX FullCAN
 *  \details       LL implementation see token CanLL_InitFullCANObj description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitRxFullCAN(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_30_Mcan_InitRxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX BasicCAN
 *  \details       LL implementation see token CanLL_InitBasicCANObj description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitRxBasicCAN(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_30_Mcan_InitEnd_InitMode()
 ***********************************************************************************************************/
/*! \brief         End Initialization
 *  \details       LL implementation see token CanLL_InitEnd_InitMode description.
 *                 Called by CanHL_30_Mcan_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_InitEnd_InitMode(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_30_Mcan_RxBasicCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN polling
 *  \details       RX BasicCAN polling handling.
 *                 Called by Can_30_Mcan_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxBasicCanPolling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_30_Mcan_RxFullCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN polling
 *  \details       RX FullCAN polling handling.
 *                 Called by Can_30_Mcan_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxFullCanPolling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_30_Mcan_RxMsgReceivedNotification()
 ***********************************************************************************************************/
/*! \brief         RX notification
 *  \details       RX queue and notification handling for BasicCAN and FullCAN reception.
 *                 Called by CanHL_30_Mcan_BasicCanMsgReceived(),CanHL_30_Mcan_FullCanMsgReceived().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxStructPtr     include general rx info and all LL specific data.
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_30_Mcan_RxMsgReceivedNotification(CAN_30_MCAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr);
#endif

#if defined(C_30_MCAN_ENABLE_RX_QUEUE)
/************************************************************************************************************
 *  CanHL_30_Mcan_RxQueueExecution()
 ***********************************************************************************************************/
/*! \brief         RX queue
 *  \details       RX queue execution and notification.
 *                 Called by Can_30_Mcan_MainFunction_Read().
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_RxQueueExecution(void);
#endif

#if defined(C_30_MCAN_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/************************************************************************************************************
 *  CanHL_30_Mcan_TxConfirmationPolling()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_TxConfirmationPolling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle mailboxHandle, Can_30_McanObjectHandle mailboxElement, Can_30_McanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_30_Mcan_TxConfirmation()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation handling
 *  \details       Called for a transmit or cancel event. Finish transmission by free send mailbox and call confirmation. \n
 *                 Called for FullCAN and BasicCAN handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     transmitted hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_TxConfirmation(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle mailboxHandle, Can_30_McanObjectHandle mailboxElement, Can_30_McanObjectHandle hwObjHandle);

#if defined(C_30_MCAN_ENABLE_TX_HW_FIFO)
/************************************************************************************************************
 *  CanHL_30_Mcan_GetNextTxHwFifoReadIndex()
 ***********************************************************************************************************/
/*! \brief         get TxHwFifo element and increment the read index
 *  \details       Called while confirmation handling to handle the TX hardware FIFO index. \n
 *  \param[in]     txConfPara          Pointer to local variables of confirmation
 *  \return        MailboxElement      index of the next mailbox element in the FIFO
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, Can_30_McanObjectHandle, STATIC_CODE) CanHL_30_Mcan_GetNextTxHwFifoReadIndex(CanTxConfirmationParaStructPtr txConfPara);

/************************************************************************************************************
 *  CanHL_30_Mcan_SetNextTxHwFifoWriteIndex()
 ***********************************************************************************************************/
/*! \brief         increment TxHwFifo write index
 *  \details       Called while transmission to handle the TX hardware FIFO index. \n
 *  \param[in]     txPara          Pointer to write parameters
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_SetNextTxHwFifoWriteIndex(CanTxTransmissionParaStructPtr txPara);
#endif

#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
/************************************************************************************************************
 *  CanHL_30_Mcan_SetCanPduInfo()
 ***********************************************************************************************************/
/*! \brief         copy the confirmation parameter info to the PduInfo struct
 *  \details       Called while confirmation handling to set data struct need for confirmation API2. \n
 *  \param[in,out] PduInfo             Pointer to local PduInfo struct
 *  \param[in]     txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_SetCanPduInfo(Can_30_Mcan_PduInfoPtrType_var PduInfo, CanTxConfirmationParaStructPtr txConfPara);
#endif

#if defined(C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_30_MCAN_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_30_Mcan_BasicCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_BasicCanMsgReceivedPolling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle);
# endif

/************************************************************************************************************
 *  CanHL_30_Mcan_BasicCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive BasicCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_BasicCanMsgReceived(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle);
#endif

#if defined(C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_30_MCAN_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_30_Mcan_FullCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_FullCanMsgReceivedPolling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle);
# endif

/************************************************************************************************************
 *  CanHL_30_Mcan_FullCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive FullCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_FullCanMsgReceived(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST Can_30_McanObjectHandle rxMailboxHandle, Can_30_McanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_30_Mcan_ErrorHandling()
 ***********************************************************************************************************/
/*! \brief         BUSOFF handling
 *  \details       Handler for bus off situation.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_30_Mcan_ErrorHandling(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);

#if defined (CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING)
/************************************************************************************************************
 *  CanHL_30_Mcan_ControllerErrorStatePassive()
 ***********************************************************************************************************/
/*! \brief         Security Event Reporting of Rx/Tx error counters
 *  \details       Forwards the Rx/Tx error counters to CanIf_ControllerErrorStatePassive()
 *  \param[in]     Controller       CAN controller (only if not using "Optimize for one controller")
 *  \param[in]     RxErrorCounter   Value of the Rx error counter
 *  \param[in]     TxErrorCounter   Value of the Tx error counter
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_ControllerErrorStatePassive( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint16 RxErrorCounter, uint16 TxErrorCounter );

/************************************************************************************************************
 *  CanHL_30_Mcan_ErrorNotification()
 ***********************************************************************************************************/
/*! \brief         Security Event Reporting of errors
 *  \details       Forwards the error type to CanIf_ErrorNotification()
 *  \param[in]     Controller       CAN controller (only if not using "Optimize for one controller")
 *  \param[in]     CanError         Reported CAN error
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_30_Mcan_ErrorNotification( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST Can_ErrorType CanError );
#endif /* CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING */



/************************************************************************************************************
 *  CanHL_30_Mcan_ReInit()
 ***********************************************************************************************************/
/*! \brief         Initialization of controller specific CAN hardware.
 *  \details       Initialization of the CAN controller hardware registers and CAN driver variables. \n
 *                 after that the controller is fully initialized and can be swtiched to "STOP Mode".
 *  \param[in]     Controller            CAN controller. \n
 *                                       (only if not using "Optimize for one controller")
 *  \param[in]     doRamCheck            RAM check exectuion (kCan_30_McanExecuteRamCheck, kCan_30_McanSuppressRamCheck).
 *  \return        error                 return kCan_30_McanFailed in case of issue or kCan_30_McanOk if initialization pass.
 *  \pre           controller is ready to be configured (INIT mode).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         no mode change must be done inside. No CAN bus depended hardware loops allowed.
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_30_Mcan_ReInit(CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck);

#define CAN_30_MCAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* CAN_30_MCAN_LOCAL_H */

/* End of channel */



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

