/* Kernbauer Version: 1.14 Konfiguration: DrvCan_Arm32Mcan Erzeugungsgangnummer: 691 */

/*        STARTSINGLE_OF_MULTIPLE_COMMENT      */

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
/*  \file     Can_30_Mcan.h
 *  \brief    Interface header file of the CAN-Driver
 *  \details  Declaration of functions, variables, and constants as user API.
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
| 2019-03-14 5.00.00  Her - STORYC-7220  : from CBD/RI2.0 to AR/R21,22 adaptation
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

/*****************************************************************************
|-----------------------------------------------------------------------------
|       C O R E    R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2005-09-15 0.01.00 Bir  - Creation
| 2005-11-17 1.00.00 Bir  - Finish CANoe, M32C
|                         - Change include structure and naming
| 2005-11-23 1.01.00 Bir  - some minor changes
| 2005-12-01 1.02.00 Bir  - Global Interrupt handling via OSEK supported
| 2006-01-19 1.03.00 Bir  - Wrong handle found and DET occur in CanHL_30_Mcan_FullCanMsgReceived
|                         - C_DISABLE_RESET_CAN_BUSOFF set (baud rate out of CANoe)
| 2006-03-16 1.04.00 Wr   - Added channel compatibility defines
|                         - Removed local parameter canHwChannels
|                         - Changed order of CanLL_TransmitLocalParameter
|                           and CanLL_TxTransmissionLocalParameter in Can_30_Mcan_Write()
|                         - Rename CanWakeup() to CanHL_30_Mcan_WakeupHandling()
|                         - Added support for NEC V850 aFCAN
|                         - Added CanLL_GeneratedStructureH for platform C_COMP_GHS_V85X  
|                         - Added general return value defines
|                         - Defined APPL_30_MCAN_CAN_WAKEUP() to CanHL_30_Mcan_WakeUpHandling()
|                         - Mapping of Can_30_McanWakeUp() to Can_30_Mcan_SetControllerMode(Controller, CAN_T_WAKEUP)
| 2006-04-19 1.05.00 Wr   - Added V850 specific handling for transition to SLEEP
|                         - Add switches to enable OSEK ISR handling for platform C_COMP_GHS_V85X
| 2006-05-22 2.00.00 Bir  - Support for AutoSar 2.0
|                         - Can.h and can_types.h connected
|                         - Include structure update
|                         - DET - switch change
|                         - API changes Can_30_Mcan_Init(), Can_30_Mcan_Write()
|                         - add Can_30_Mcan_GetVersionInfo()
| 2006-06-06 2.01.00 Bir  - internal naming corrections for version defines
|                         - API for Det_ReportError changed (add parameter)
| 2006-06-12 2.02.00 Bir  - CaninitObject calculation changed
|                         - TriCore update for Interrupt priority defines
| 2006-06-12 2.03.00 Bir  - SetControllerMode return OK for unsupported STOP/START or SLEEP/WAKEUP
|                         - CaninitObject calculation changed
| 2006-06-12 2.04.00 Bir  - kCanNotSupported defined to 0x02 to avoid CAN_NOT_OK for that case
|                         - define for MEMORY_ROM (compatibility)
| 2006-07-05 2.05.00 Bir  - Can_HwHandleType as uint8
|                         - Review rework
| 2006-07-10 2.06.00 Bir  - Can_30_Mcan_Write try/send also in case busy
| 2006-08-15 2.07.00 Bir  - mapping of CanSingleGlobalInterruptX changed
| 2006-09-04 2.08.00 Bir  - minor change in Can.h: ControllerName length expand to 20
| 2006-09-04 2.09.00 Bir  - minor change for MISRA compliance
|                         - add canStatus for initialization info
|                         - minor changes for MAC71xx
|                         - No interrupt lock inside "CanHL_30_Mcan_BasicCanMsgReceived"
|                         - Add FullCAN TX
|                         - Add TX Polling
|                         - Add Hardware Loop and DEM call
|                         - DET call for initialized call of Can_30_Mcan_Init()
|                         - Add Can_30_Mcan_InitMemory function
| 2006-11-06 2.10.00 Bir  - review rework
| 2006-11-08 2.11.00 Ces/Bir - Add Platform Mcs12x
|                         - Add local variable Controller in function Can_30_Mcan_InitMemory()
|                         - Add define C_30_MCAN_ENABLE_COPY_TX_DATA in header
| 2006-11-09 2.12.00 Bir  - Prepare for Post-build structure (ORGANI switch "C_30_MCAN_HL_ENABLE_ASR_POSTBUILD_STRUCT" added)
| 2006-11-11 2.13.00 Pl   - Add Platform TMS470_DCAN
|                    Bir  - Move FullCAN Overrun notification token behind FullCAN Begin token
| 2006-11-15 2.14.00 Bir  - Post-build changes
|                         - Review changes
|                         - change CAN_HL_TX_OFFSET_HW_TO_LOG and logTxObjHandle value
|                         - ESCAN00018785: Send out of confirmation (TX Queue)
|                         - ESCAN00018915: Change multiple-include define
| 2007-01-15 2.15.00 Bir  - ESCAN00018896: wrong call to Dem_SetEventStatus
|                         - deactivate "CanOverrunNotification" due to no more need since ASR2.0
|                         - Support "Can_30_Mcan_MainFunction_BusOff"
|                         - call Can_30_Mcan_InitController in case of change mode from BUSOFF to START
|                         - Add SchM_Enter_Can_30_Mcan_), SchM_Exit_Can_30_Mcan_) / interrupt mapping over VStdLib or SchM
|                         - Change Version Scan Information
|                         - Remove V850 specific parts (shift to LL)
|                         - Remove Re-initialize DET report out of Can_30_Mcan_InitController()
| 2007-02-20 2.16.00 Bir  - minor improvements
|                         - ESCAN00019720: WAKEUP does not appear after set SLEEP mode
| 2007-03-09 2.20.00 Bir  - ESCAN00019889: Update to ASR2.1
|                         - ESCAN00019889: change calculation of CAN_HL_TX_OFFSET_HW_TO_LOG (because multiplexed TX)
|                         - remove FullCAN switches to secure Post-build functionality without compile with FullCANs
|                         - ESCAN00020129: Compiler error: identifier "i" is undefined
|                         - Reduce BasicCAN logical mailbox to real BasicCAN (DLC_FIFO include size of Basic CAN)
|                         - Reduce Unused mailboxes logical mailbox to amount of sections (DLC_FIFO include size)
|                         - Move all version defines from Proto.h to Can.h (license scanning)
|                         - Add CAN_AR_*_VERSION
|                         - remove PduId out of mailbox (old from CANIf)
|                         - set "C_30_MCAN_ENABLE_OSEK_OS_INTCAT2" if not defined "C_30_MCAN_ENABLE_INT_OSCAT1"
|                         - set DLC also for FullCAN TX objects
|                         - generated Tables: CanActiveSendPdu,CanActiveSendState (size matter at link time)
|                         - return not OK for try to set SLEEP mode but failed in HW
|                         - move multichannel API define to Can.h
|                         - set "C_30_MCAN_ENABLE_OSEK_OS_INTCAT2" if not defined "C_30_MCAN_ENABLE_INT_OSCAT1"
|                         - do "CanLL_30_Mcan_InitPowerOn" before "CanLL_30_Mcan_InitPowerOnChannelSpecific"
|                         - move OSEK-switches out of irq.c
|                         - add CanLL_30_Mcan_InitMemoryPowerOn token for special ll initialization
| 2007-08-28 2.21.00 Bir  - ESCAN00022112: RX Basic CAN used with wrong stop index
|                         - renaming "CaninitObject" to "Can_Init_CtrlIdx" (no runtime effect)
|                         - ESCAN00022168: Driver does not enter STOP mode for Sleep request (when SLEEP is not sup.)
|                         - ESCAN00022232: Add STOP-mode compatibility for FNOS-RP migration
|                         - ESCAN00022262: CanResetBusOffEnd() used with only one parameter
|                         - Add new Token "CanLL_RxFull_SearchHandle" for special HW-support (XGate)
|                         - ESCAN00022390: HW start-stop-index changed to RAM-table
| 2007-10-15 2.22.00 Bir  - ESCAN00022773: use of #ifndef instead of #if !defined
|                         - ESCAN00022774: improve runtime while change mode (STOP to SLEEP)
|                         - ESCAN00023040: minor improvements (add SPEC-1721, SPEC-1767, SPEC-1784, SPEC-1780, SPEC-1781)
|                         - ESCAN00023040: remove Interrupt locking in Can_30_Mcan_Write() due to CanIf do this
|                         - ESCAN00023038: Multiple ECU
|                         - ESCAN00023047: Add version check
|                         - ESCAN00023049: change API of Can_30_Mcan_Init() to one parameter, Add constant in Can_30_Mcan_InitController() + Add Can_InitStruct API
|                         - ESCAN00023127: compiler warnings due to dummy assignments (used to satisfy other compilers)
|                         - ESCAN00023265: remove brackets around Can_30_Mcan_EnterCritical
|                         - QAC / MISRA reworks
|                         - Add memory qualifiers
|                         - add v_def.h include (remove define of V_MEM..)
|                         - Review reworks
| 2007-12-14 2.23.00 Bir  - ESCAN00023442: Add extended Id support
|                         - some small changes for cancellation (cancel only less priority objects - more efficient)
|                         - protect Can_30_Mcan_MainFunction_Read against re-entrant (ASR specification)
|                         - ESCAN00024354: Ignore API call with controller deactivated by identity
|                         - review rework
| 2008-02-06 3.00.00 Bir  - ESCAN00024406: ASR3.0
| 2008-03-25 3.01.00 Bir  - Add dummy assignment in "ResetBusOffEnd" avoid compiler warnings
|                         - ESCAN00025672: review reworks
|                         - ESCAN00025664: Message send with wrong ID type
|                         - ESCAN00026087: Case sensitive naming for all File names (and includes)
|                         - ESCAN00026186: Extension for MSR3.0 Link-time checks
|                         - ESCAN00025957: No access on "DEM-events" via DEM created and exported constant values
|                         - Move compatibility section (switches needed earlier)
| 2008-05-14 3.02.00 Bir  - ESCAN00026859: V_MEMRAM0 not allowed for type cast
|                         - ESCAN00026861: Token external declaration added
|                         - ESCAN00026990: Add LL-Token to reject Remote frames
|                         - (see ES_CAN00029839) Change naming: "INTERRUPT" and "POLLING" add prefix "CAN_*"
|                         - (see ES_CAN00029826) Remove include of v_cfg.h and v_def.h (will be generated)
|                         - ESCAN00030521: Linker error because of missing Interrupt service routine
|                         - Move include section to top of file (need before version defines)
| 2008-06-30 3.03.00 Bir  - ESCAN00027986 +(ESCAN00025773): Code optimization (save ROM and runtime)
|                           + Start/StopLoop as macro
|                           + Max Loop counter define move to LL
|                           + Add some FullCAN switches to ORGANI Basic CAN controllers
|                           + Multiple Search for Basic CAN HW object
|                           + CanInterrupt Lock only in nested interrupt case (CAN_NESTED_INTERRUPTS)
|                           + remove some HW-start/stop indexes and there calculation use instead info from mailbox-table
|                         - ESCAN00028069: change controller amount to library capable setting
|                         - ESCAN00026596: Extension for MSR3.0 generator version checks
| 2008-08-19 3.03.01 Bir  - minor review changes
|                         - ESCAN00029385: change naming finishFullCan to finishRxFullCan (CAN-bedded compliance)
| 2008-09-11 3.04.00 Bir  - ESCAN00029942: Generator Version Check failed
| 2008-09-18 3.05.00 Bir  - ESCAN00029830: Add Link-time/Post-build configure CRC check
|                         - ESCAN00029434: rename "INTERRUPT" and "POLLING" switch
| 2008-10-15 3.06.00 Bir  - remove CAN_30_MCAN_HL_HW_x_STOPINDEX -> not used in HL and does not work for LL
|                         - ESCAN00029707: change transition from uninitialized->START->STOP to uninitialized->STOP
|                         - ESCAN00029129: Source of HW loop timer is not available to application
|                         - ESCAN00030728: move platform typedefs to Can.h
| 2008-10-28 3.06.01 Bir  - ESCAN00030926: lock interrupts while TX confirmation.
|                         - Add include protection for canproto.h
| 2008-10-28 3.07.00 Bir  - ESCAN00032401: CAN driver stays in an endless loop
|                         - ESCAN00032291: BUSOFF handling took some time with locked interrupts
|                         - ESCAN00032612: Support Individual Polling
|                         - ESCAN00032614: Add new memory qualifier V_MEMROM4_CFG for Post-build data access
| 2009-03-16 3.07.01 Bir  - ESCAN00033874: Add LL-token "CanLL_tCan_30_McanRxInfoStruct" for structure tCan_30_McanRxInfoStruct
| 2009-04-03 3.07.02 Bir  - ESCAN00034409: Add PRQA comments for MISRA justification
|                         - ESCAN00034551: Add support for reverse RX Basic CAN polling
|                         - ESCAN00034552: Optimize RX Basic CAN polling loop
|                         - ESCAN00034773: Add cancel TX in Hardware within TX polling task
| 2009-04-20 3.08.00 Bir  - ESCAN00034118: Add compiler abstraction
|                         - ESCAN00034119: Add memory abstraction
|                         - ESCAN00035606: Report DEM as DET "CAN_DEV_TIMEOUT_DETECT"
|                         - (see ES_CAN00035490) Report DEM as DET "CAN_DEV_TIMEOUT_DETECT"
|                         - ESCAN00036041: compiler warning label not referenced
| 2009-07-08 3.09.00 Bir  - ESCAN00034780: Confirmation without critical section
| 2009-07-22 3.09.01 Bir  - ESCAN00036593: compile error (variable declaration after assignment)
| 2009-08-03 3.09.02 Bir  - ESCAN00036822: TX data inconsistency
| 2009-08-24 3.09.03 Bir  - ESCAN00037276: Compiler warning "function declared implicitly"
| 2009-09-15 3.10.00 Bir  - ESCAN00037784: Add Generic Confirmation function
|                         - ESCAN00037789: Add feature RX Queue
|                         - change order of RX-DLC and "CanLL_RxBasicGetCANDataPtr" (support for mailbox in RAM)
|                         - ESCAN00038814: Wrong pointer class for TX data used
| 2010-01-19 3.11.00 Bir  - ESCAN00040258: Use Can_HwHandleType instead of uint8
|                         - ESCAN00040432: Code optimization for 1 controller systems
|                         - ESCAN00040433: Support dynamic FullCAN id
|                         - ESCAN00040234: remove v_cfg.h include (already done in can_30_Mcan_cfg.h)
| 2010-03-03 3.11.01 Bir  - small review reworks
|                         - ESCAN00041364: Optimize Runtime of Can_30_Mcan_SetControllerMode
|                         - ESCAN00041432: Declaration for ISRs missing in case of Full Polling with Individual Polling
| 2010-03-03 3.12.00 Bir  - ESCAN00041791: Suppress unexpected WAKEUP notification
|                         - ESCAN00041984: Support Common CAN
|                         - ESCAN00041996: Split Critical Sections
|                         - ESCAN00042333: Add Hardware assertion notification to DET
|                         - ESCAN00042459: Support WAKEUP-switch-off (no SLEEP mode - STOP mode instead)
|                         - ESCAN00043085: Compiler warnings due to missing cast
|                         - ESCAN00043224: New API Can_30_Mcan_GetStatus()
|                         - ESCAN00043250: Add Application Interrupt lock functions
|                         - canWakeUp() call changed to CAN_30_MCAN_WAKEUP() - used for LL
|                         - ESCAN00047602: compiler warning: "comparison between signed and unsigned"
|                         - ESCAN00044114: Stop sending messages after transition to STOP mode (and back to started)
| 2010-11-23 3.13.00 Bir  - ESCAN00043999: Support usage without v_def.h
|                         - ESCAN00044276: Reject unwanted ID types (software Filter)
|                         - ESCAN00045682: Compiler warning: dead assignment to "X" eliminated
|                         - ESCAN00045883: Can_30_Mcan_SetControllerMode doesn't return CAN_NOT_OK when called with invalid Transition parameter
|                         - ESCAN00045884: Can_30_Mcan_CheckWakeup doesn't raise the CAN_E_UNINIT development error
|                         - ESCAN00046363: Adapt AUTOSAR version check
|                         - rename "canInterruptCounter" to "canCanInterruptCounter" CBD compatibility
|                         - ESCAN00047875: Add support for partial network
|                         - ESCAN00047951: Compile error, if the feature "Optimize for one controller" is used
| 2011-03-11 4.00.00  Bir - ESCAN00043688: Support AUTOSAR 4.0 R1
|                         - ESCAN00043998: Add GenData checker
|                         - ESCAN00044010: Add Notification for Overrun detection
|                         - ESCAN00047111: Support RAM check
|                         - ESCAN00046778: Support Multiple Identity Configuration
| 2011-04-05 4.00.01  Bir - void cast DET call for MSR40 + review reworks (minors)
|                         - ESCAN00049572: RAM-check: communication is not deactivated
|                         - ESCAN00050862: EcuM_CheckWakeup is not called in case of WAKEUP Polling
|                         - ESCAN00051562: Remove the AUTOSAR Release Version Check
|                         - ESCAN00047929: Can_30_Mcan_Init() does not initialize CAN controllers - but Can Interface do this
|                         - ESCAN00049613: AR Version is not correct (2.2.0 instead of 2.2.1)
| 2011-06-21 4.01.00  Bir - ESCAN00050960: Provide API for Generic Pretransmit (AR3-1654 )
|                         - ESCAN00051102: Compiler warning: narrowing or signed-to-unsigned type conversion found: int to unsigned char
|                         - ESCAN00052324: Compile error if the feature "Optimize for one controller" and "RX Queue" is used
|                         - ESCAN00054829: Fault tolerant API: Do not throw DET in case of MultipleEcuConfig inactive controller for 'Can_30_Mcan_CheckWakeup'
|                         - ESCAN00053648: Wrong Define name used "CAN_DEACTIVATE_COMMUNICATION"
|                         - ESCAN00053270: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
|                         - ESCAN00053263: AR3-2069: Remove non-SchM code for critical section handling
|                         - ESCAN00054038: Compiler warning: variable "canApiContext" was set but never used
|                         - ESCAN00054813: Add Mirror functionality
| 2011-11-21 4.01.01  Bir - ESCAN00055001: Support Transition HW-Loops for MSR30
|                         - ESCAN00055076: MISRA compliance
| 2011-12-14 4.01.02  Bir - ESCAN00055566: Include of DET with camel case spelling
| 2011-12-15 4.01.03  Bir - ESCAN00055589: SPEC-1761
|                         - ESCAN00056004: Add Code Trace ability to AutoSar SWS
|                         - Add explicit type casts to satisfy COSMIC compilers (MCS12x)
|                         - ESCAN00056185: Change Version Check
| 2012-01-20 4.02.00  Bir - ESCAN00055076: MISRA compliance
|                         - Use !CAN_USE_VECTOR_IF instead of VGEN_GENERATOR_GENY (also support CFG5 in mixed systems)
|                         - ESCAN00057438: AR3-2383: Implement handling of call to Dem_ReportErrorStatus
|                         - ESCAN00057164: WAKEUP while Re-Initialization ASR3.2.1
|                         - ESCAN00054830: Can_30_Mcan_SetControllerMode() return failed
| 2012-05-31 4.02.01  Bir - ESCAN00059203: Compiler error: missing variable canHwChannel in Can_30_Mcan_CleanUpSendState()
|                         - ESCAN00059265: Compiler error: hardware loop index is not available as define for API
| 2012-06-12 4.03.00  Bir - ESCAN00057437: AR3-2374: Implement Silent BSW
|                         - ESCAN00059412: AR4-135: support MSR 4 R5
|                         - ESCAN00059488: Compiler error: identifier "Can_ConfigDataPtr" is undefined
|                         - ESCAN00060494: Compiler error: SchM_Enter_Can((area)) causes Compiler Error with external SchM Usage
| 2012-09-03 4.03.01  Bir - Improve MISRA compliance
|                         - ESCAN00061352: Endless Loop
| 2012-09-03 4.04.00  Bir - ESCAN00061042: AR3-2378: Implement AMD time measurement support
|                         - ESCAN00060586: AR3-2446: Update Code analysis and change analysis UUIDs (like described in Silent design)
|                         - ESCAN00060554: AR3-2443: Implement Silent Checks in BSW module code
|                         - Add support for FullCAN TX cancellation only
|                         - ESCAN00062679: Add source defines according to MICROSAR template source file
| 2012-12-10 4.04.01  Bir - Rework Silent BSW
| 2013-01-28 4.04.02  Bir - ESCAN00064474: Modify Hook_On (code can be removed by integration ORGANI)
| 2013-02-02 4.05.00  Bir - optimize token StopReinit usage
|                         - move some global compatibility defines from proto.h to Can.h
|                         - ESCAN00063652: RxQueue extension to 16bit size
|                         - ESCAN00064324: AR4-325: Implement Post-Build Loadable
|                         - ESCAN00066278: Incorrect comment description for function Can_30_Mcan_CheckWakeup / Can_Cbk_CheckWakeup
| 2013-06-11 4.05.01  Bir - ESCAN00067936: Can_30_Mcan_GetStatus wrongly returns CAN_STATUS_INCONSISTENT
|                         - Add QAC deviations for 6010, 6030, 6050, 6080
| 2013-06-12 4.06.00  Tvi/Bir - ESCAN00069107: AR4-397: Implement support for CAN-FD according to ASR4.1.1
|                         - ESCAN00070197: Compiler warning: variable Can_ConfigDataPtr was declared but never referenced
|                         - ESCAN00068900: Compiler warning
|                         - ESCAN00067711: AR4-328 / RTM measurement R8
|                         - ESCAN00070625: Adapt usage of CanResetBusOffEnd
|                         - ESCAN00071048: Support null_ptr data in Can_30_Mcan_Write() for DLC==0
|                         - Add DOXYGEN comments to be used by API scanner
|                         - move some global compatibility defines from proto.h to Can.h
| 2013-10-25 4.06.01  Bir - R9 version / some minor MISRA improvements
|                         - ESCAN00073272: Support Can_30_Mcan_InitController() failure in LL
|                         - ESCAN00073676: Its not possible to switch off MIRROR mode for reception when using RxQueue
|                         - ESCAN00073516: MIRROR_MODE add CAN interrupt lock around confirmation
| 2014-06-23 4.06.02  Bir - ESCAN00076374: Add TX Request cancellation in case of HW-loop break
| 2014-06-23 4.07.00  Bir - R10 ComStackLibAbtraction
|                         - ESCAN00074371: AR4-457: Support CAN-FD mode 2
| 2014-07-01 5.00.00  Bir - R11
|                         - ESCAN00076631: Post-build selectable (+loadable)
|                         - ESCAN00076498: CAN FD mode2
|                         - ESCAN00076634: Multiple CAN driver support
|                         - ESCAN00078089: RAM Check also for emulated SLEEP
|                         - ESCAN00079232: rename canProto.h to Can_30_Mcan_Local.h
| 2014-11-24 5.00.01  Bir - coverage improvements
|                         - ESCAN00079480: support GENy (ComStackLib abstraction)
| 2014-12-14 5.01.00  Bir - ESCAN00079794: CAN-FD configured padding
|                         - ESCAN00080453: mask out FD-Bit in GenericPrecopy
|                         - ESCAN00080757: Limit DLC to 8 for Classic CAN RX-Frames
|                         - Support TxIndirectionHwToLog and LogToHw (platforms that use hwHandles for TX shadow buffers)
|                         - ESCAN00081930: DET error (CAN_INITCTR_ID, CAN_E_PARAM_CONTROLLER) occur
|                         - ESCAN00082533: BasicCAN message cancelled out of hardware but is not configured
| 2015-01-19 5.02.00  Bir - ESCAN00080306: FEAT-427 SafeBSW
|                           ESCAN00081793: FEAT-1275 SafeBSW step2
|                           + Merge API and Core history and move it to Can.h
|                           + add code design comments / rework comments in general
|                           + rework DET and SilentDet handling (SilentDet is now DET, no more MACRO)
|                           + split large functions in INLINE functions to reduce CYC
|                           ESCAN00073798: disable CAN interrupts while polling
|                           ESCAN00082042: API description Appl_GenericPrecopy
|                           ESCAN00082274: FEAT-1379: Optimized copy operation for large data
|                           ESCAN00082688: DET error (CAN_MAINFCT_*_ID, CAN_E_PARAM_CONTROLLER) occur
| 2015-07-30 5.02.01  Bir - remove goto/labels for HL - add it for LL
|                           shift CanLL_DefinesDataTypesStructsUnions from Can.c to Can_30_Mcan_Local.h
|                           typedef Can_ControllerConfigPtrType from Can_Cfg.h in case of postbuild
|                           include det.h only for report level not detection (from 5.02.00)
|                           ESCAN00084263, ESCAN00084264: reject illegal DLC
| 2015-11-09 5.02.02  Bir - ESCAN00086345: BasicCAN RX message not received
| 2015-10-27 5.03.00  Bir - ESCAN00085666: Gateway - multiple BasicCAN Tx
|                           Add CanHL_30_Mcan_StopReinit, CanHL_30_Mcan_RxBasicCanPolling, CanHL_30_Mcan_RxFullCanPolling
|                           remove Copyright info from Core use LL Copyright instead
| 2015-12-21 5.03.01  Bir - ESCAN00087253: preprocessor directives error in CanHL_30_Mcan_WakeupTransition() or CanHL_30_Mcan_SleepTransition()
| 2016-01-15 5.03.02  Bir - ESCAN00087518: Illegal pointer access when driver is not initialized
|                           test coverage improvements / minor MISRA improvements
|                           remove some _COMMEN_T postfixes for ORGANI (HW-layout may be TOOL dependent)
| 2016-01-29 5.04.00  Bir - test coverage improvements / minor MISRA improvements
|                           ESCAN00088335: FEAT-598: Extended RAM Check / SelfDiag
|                           ESCAN00087810: FEAT-1688: SafeBSW Step 4
|                           ESCAN00089399: Compiler error: 0=0 assignment
| 2016-04-14 5.04.01  Bir - review rework from 5.04.00
|                           rework traceability, rework coverage comments
|                           ESCAN00089754: Compile error overrun notification by DET without DET enabled (MSR401 only)
| 2016-06-21 5.05.00  Bir - ESCAN00089632: FEAT-1908: Access to Interrupt Control Register via OS
|                           ESCAN00089592: FEAT-1513: Release of CAN-FD
|                           FEAT-1602: Release of MultiBasicCAN-Tx (Gateway)
| 2016-08-24 5.05.01  Bir - ESCAN00091600: support MultiBasicCanTx with HW size > 1
| 2016-08-25 5.05.02  Bir - minor design improvement because of SafetyCheck
|                           ESCAN00091764: mode transition will be fully synchronous
| 2016-10-13 5.05.03  Bir - Add infix for local data and code (test without static to stimulate internal interfaces)
|                         - some minor COV comment improvements
| 2017-02-17 5.05.04  Bir - ESCAN00094060: Define CAN_H renamed (linux reuse)
|                           add infix to CAN_DUMMY_STATEMENT
|                           add coverage comment for Flexcan2 usage
|                           split in Can_30_Mcan_MainFunction_Write -> add CanHL_30_Mcan_TxTaskConfirmationHandling and CanHL_30_Mcan_TxTaskCancelationHandling
| 2017-02-23 5.05.05  Bir - Minor Improvements relating COV and MISRA deviations
| 2017-03-29 5.06.00  Bir - FEATC-382: remove saturation
|                           ESCAN00094638: MICROSAR3 only: No RAM Check during wakeup or explicite call of Can_30_Mcan_RamCheckExecute()
|                           ESCAN00095298: No transmit cancellation when calling Can_30_Mcan_CancelTx() / CanIf_TransmitCancellation()
| 2017-05-29 5.07.00  Bir - STORYC-140: support silent mode
|                           STORYC-645: selective MultiplexedTx
| 2017-08-22 5.07.01  Bir - ESCAN00096086: compiler error: undefined Symbol Can_GetMailbox*IdxOfControllerConfig
|                           ESCAN00096369: Can_30_Mcan_Write() return CAN_NOT_OK instead of CAN_BUSY in case of BO
|                           ESCAN00096391: Compiler error: function "CanHL_30_Mcan_WakeupProcessed" / "CanHL_30_Mcan_SleepProcessed" was referenced but not defined
| 2017-09-04 6.00.00  Bir - STORYC-2176: Remove "Tracing" feature
|                           ESCAN00096367: CAN driver does not recover from BusOff and stop communication.
|                           ESCAN00097096: Compiler error calling VStdMemCpy
|                           FEAT: Compiler error calling VStdMemCpy
|                           STORYC-3057 / ESCAN00098096: GenericPrecopy with FD-bit, GenericConfirmation(API2) with Len (instead of DLC) and FD-bit
|                                         ESCAN00098095: GenericConfirmation(API2) with Len instead of DLC
|                           STORYC-3329: MICROSAR3 Core Adaptation
|                           ESCAN00098892: Compiler warning: transitionRequest
| 2018-04-19 6.00.01  Bir - Minor Improvements relating COV
| 2018-04-23 7.00.00  Bir - Support new functional LL interface / support reduced to MSR403 only
|                           STORYC-4934: TxHwFifo
|                           STORYC-4935: TxHwFifo
|                           ESCAN00095187: support CAN_BUSY enum
| 2018-04-23 7.00.01  Bir - R21 final SafeBSW
| 2018-09-24 8.00.00  Bir - R22
|                           reworks because of QAC metrics
|                           ESCAN00094289: Can_30_Mcan_CheckWakeup has to return CAN_OK/CAN_NOT_OK (CAN360)
|                           TASK-91350: Review reworks
|                           ESCAN00101151: internal PIA failed
|                           STORYC-6510: Accept longer DLCs
|                           STORYC-6843: support more than 3 Baudrate configurations 
|                           STORYC-7257: BusMirroring - GetControllerMode/State/ErrorCounter
|                           STORYC-6846: MISRA 2012
| 2019-03-27 8.00.01  Bir - minor platform specific QAC findings fixed
|                           CM syntax fixed
|                           STORYC-8102: reduce STPH in CanHL_TxConfirmation
| 2019-04-29 9.00.00  Bir - R23 (no feature change here)
|                           minor platform specific QAC COV and SBSW findings fixed
|                           RAM_CHECK readback failure for mailboxes not notified
| 2019-09-09 9.00.01  Bir - R23/R24 (no feature change here)
|                           QAC reworks
|                           Infix in comments (Critical Section description)
|                           CanHL_30_Mcan_ReInit with return failed in case of DET issue
| 2020-12-11 10.00.00 Hum - CAN-1572: R26 - Support reporting of security events
| 2021-04-28 10.00.01 Bir - Unnecessary DET check for controller (already done in caller)
|                           Single-/Multi-channel API improvements
|                           MISRA comment rework
| 2021-06-30 10.00.02 Bir - mark Can_Write() as reentrant
|                           Add MISRA comment
|                           ESCAN00109136: remove global AREA_3 for Appl_GenericConfirmation() and CanIf_TxConfirmation()
|                                          copy to temp buffer before call Appl_GenericConfirmation()
|                           ESCAN00110429: compiler warning: undefined order of volatile access
| 2021-06-30 10.00.03 Bir - ESCAN00110573: call of Appl_GenericConfirmation() with wrong DLC
|****************************************************************************/

#if !defined(CAN_30_MCAN_API_H)
#define CAN_30_MCAN_API_H /* refer to ESCAN00094060 */

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
/* \trace SPEC-1408 */
#include "Can_30_Mcan_Cfg.h"

#if (CAN_30_MCAN_MIRROR_MODE == STD_ON)
# include "CDDMirror.h"
# define C_30_MCAN_ENABLE_MIRROR_MODE
#endif

/***************************************************************************/
/* Version                                                                 */
/***************************************************************************/
/* Vector module version */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan_MPC5700MCANASR CQComponent : Implementation */
#define DRVCAN_MPC5700MCANASR_VERSION         0x0510u
#define DRVCAN_MPC5700MCANASR_RELEASE_VERSION 0x04u

/* internal Core Version */
#define CAN_30_MCAN_COREVERSION           0x1000u
#define CAN_30_MCAN_RELEASE_COREVERSION   0x03u

/* AutoSar Version for API */
/* BR:013, BR:014 */
#define CAN_30_MCAN_AR_RELEASE_MAJOR_VERSION      4u
#define CAN_30_MCAN_AR_RELEASE_MINOR_VERSION      0u
#define CAN_30_MCAN_AR_RELEASE_REVISION_VERSION   3u

/* AutoSar module version */
#define CAN_30_MCAN_SW_MAJOR_VERSION   ((DRVCAN_MPC5700MCANASR_VERSION & 0xFF00u) >> 8)
#define CAN_30_MCAN_SW_MINOR_VERSION   (DRVCAN_MPC5700MCANASR_VERSION & 0x00FFu)
#define CAN_30_MCAN_SW_PATCH_VERSION   (DRVCAN_MPC5700MCANASR_RELEASE_VERSION & 0xFFu)

#define CAN_30_MCAN_VENDOR_ID   30u
#define CAN_30_MCAN_MODULE_ID   80u

/***************************************************************************/
/* Defines and Macros                                                      */
/***************************************************************************/
/* Module Id's */
#define CAN_30_MCAN_INIT_ID            0x00u
#define CAN_30_MCAN_INITCTR_ID         0x02u
#define CAN_30_MCAN_SETCTR_ID          0x03u
#define CAN_30_MCAN_DIINT_ID           0x04u
#define CAN_30_MCAN_ENINT_ID           0x05u
#define CAN_30_MCAN_WRITE_ID           0x06u
#define CAN_30_MCAN_VERSION_ID         0x07u
#define CAN_30_MCAN_MAINFCT_WRITE_ID   0x01u
#define CAN_30_MCAN_MAINFCT_READ_ID    0x08u
#define CAN_30_MCAN_MAINFCT_BO_ID      0x09u
#define CAN_30_MCAN_MAINFCT_WU_ID      0x0Au
#define CAN_30_MCAN_MAINFCT_MODE_ID    0x0Cu
#define CAN_30_MCAN_CKWAKEUP_ID        0x0Bu
#define CAN_30_MCAN_CHANGE_BR_ID       0x0Du
#define CAN_30_MCAN_CHECK_BR_ID        0x0Eu
#define CAN_30_MCAN_SET_BR_ID          0x0Fu
#define CAN_30_MCAN_GETCTR_STATE_ID    0x11u
#define CAN_30_MCAN_GETCTR_MODE_ID     0x12u
#define CAN_30_MCAN_GETCTR_RXCNT_ID    0x30u
#define CAN_30_MCAN_GETCTR_TXCNT_ID    0x31u

/* Internal Id's */
#define CAN_30_MCAN_RXINDI_ID          0x50u
#define CAN_30_MCAN_TXCNF_ID           0x51u
#define CAN_30_MCAN_CTRWAKEUP_ID       0x52u
#define CAN_30_MCAN_CTRBUSOFF_ID       0x53u
#define CAN_30_MCAN_HW_ACCESS_ID       0x60u

/* \trace SPEC-1702, SPEC-1401, SPEC-50568, SPEC-1568 */
/* Error Codes */
#define CAN_30_MCAN_E_NO_ERROR              (uint8)0x00u
#define CAN_30_MCAN_E_PARAM_POINTER         (uint8)0x01u
#define CAN_30_MCAN_E_PARAM_HANDLE          (uint8)0x02u
#define CAN_30_MCAN_E_PARAM_DLC             (uint8)0x03u
#define CAN_30_MCAN_E_PARAM_CONTROLLER      (uint8)0x04u
#define CAN_30_MCAN_E_UNINIT                (uint8)0x05u
#define CAN_30_MCAN_E_TRANSITION            (uint8)0x06u
#define CAN_30_MCAN_E_DATALOST              (uint8)0x07u   /* for MSR30 extension */
#define CAN_30_MCAN_E_PARAM_BAUDRATE        (uint8)0x08u   /* MRS403 only */
#define CAN_30_MCAN_E_RXQUEUE               (uint8)0x10u   /* extension */
#define CAN_30_MCAN_E_TIMEOUT_DET           (uint8)0x11u   /* extension */
#define CAN_30_MCAN_E_GENDATA               (uint8)0x12u   /* extension - used by LL to throw standardized issue for inconsistent generated data */
/* Error Codes Platform Specific */
#define CAN_30_MCAN_E_MRAF               (uint8)0x13u   /* extension - Mcan specific Det to signal a Message RAM access failure */
/* error numbers for User Assertions 0x20-0x3f - hardware dependent */
#define kCanErrorDisabledChannel                  ((vuint8)0x20)
/* error numbers for Generation tool Assertions 0x60-0x7f - hardware dependent */
/* error numbers for Hardware Assertions 0xA0-0xBF - hardware dependent */
# define kCanErrorWrongBaseAddress                ((vuint8)0xA0)
# define kCanErrorCanSleepFromReset               ((vuint8)0xA1)
# define kCanErrorMcanRevision                    ((vuint8)0xA2)
# define kCanErrorMcanMessageRAMOverflow          ((vuint8)0xA3)
# define kCanErrorChannelHdlTooLarge              ((vuint8)0xA4)
# define kCanErrorSICANFDKeyRejected              ((vuint8)0xA5)
# define kCanErrorUnexpectedConfirmation          ((vuint8)0xA6)
# define kCanErrorMcanMrafOccure                  ((vuint8)0xA7)
# define kCanErrorPwdRejected                     ((vuint8)0xA8)
/* error numbers for Internal Assertions 0xe0-0xff - hardware dependent */
# define kCanErrorUndefinedStatus                 ((vuint8)0xE0)

/* Return values Can_30_Mcan_GetStatus() */
#define CAN_30_MCAN_STATUS_UNINIT           ((uint8)0x00u) /* ASR extension */
#define CAN_30_MCAN_STATUS_START            ((uint8)0x01u) /* ASR extension (kCanTxOn) */
#define CAN_30_MCAN_STATUS_STOP             ((uint8)0x02u) /* STOP */
#define CAN_30_MCAN_STATUS_INIT             ((uint8)0x04u) /* Initialized */
#define CAN_30_MCAN_STATUS_INCONSISTENT     ((uint8)0x08u) /* Inconsistent      used for common CAN */
#define CAN_30_MCAN_STATUS_WARNING          ((uint8)0x10u) /* WARNING */
#define CAN_30_MCAN_STATUS_PASSIVE          ((uint8)0x20u) /* PASSIVE */
#define CAN_30_MCAN_STATUS_BUSOFF           ((uint8)0x40u) /* BUSOFF */
#define CAN_30_MCAN_STATUS_SLEEP            ((uint8)0x80u) /* SLEEP */
#define CAN_30_MCAN_STATUS_MASK_NOMODE      ((uint8)0x0Cu) /* Initialized & Inconsistent/DEACTIVATE */

#if defined(C_DRV_30_MCAN_INTERNAL) /* just for internal usage */ /* COV_CAN_INTERNAL */
/* mode transition requests */
# define kCan_30_McanModeSleep                 ((uint8)0x01u)
/* used by HLL: define kCan_30_McanModeWakeupStart          ((uint8)0x02u) */
# define kCan_30_McanModeStopReinitFast        ((uint8)0x03u)
# define kCan_30_McanModeStopReinit            ((uint8)0x04u)
# define kCan_30_McanModeStart                 ((uint8)0x05u)
# define kCan_30_McanModeStartReinit           ((uint8)0x06u)
# define kCan_30_McanModeWakeupStopReinit      ((uint8)0x07u)
# define kCan_30_McanModeSilent                ((uint8)0x08u)
# define kCan_30_McanModeResetBusOffStart      ((uint8)0x09u)
# define kCan_30_McanModeResetBusOffEnd        ((uint8)0x0Au)
# define kCan_30_McanModeNone                  ((uint8)0x10u)
/* precondition for mode transition */
# define kCan_30_McanContinueBusOffRecovery    ((uint8)0x00u)
# define kCan_30_McanFinishBusOffRecovery      ((uint8)0x01u)
/* re-initialization */
# define kCan_30_McanExecuteRamCheck           kCan_30_McanTrue
# define kCan_30_McanSuppressRamCheck          kCan_30_McanFalse
#endif

/* Macros to use Can_30_Mcan_GetStatus() */
/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */
#define CAN_30_MCAN_HW_IS_OK(state)                     (((state) & (CAN_30_MCAN_STATUS_WARNING |  \
                                                          CAN_30_MCAN_STATUS_PASSIVE |  \
                                                          CAN_30_MCAN_STATUS_BUSOFF) )    == 0u)
#define CAN_30_MCAN_HW_IS_WARNING(state)                (((state) & CAN_30_MCAN_STATUS_WARNING)      != (uint8)0u)
#define CAN_30_MCAN_HW_IS_PASSIVE(state)                (((state) & CAN_30_MCAN_STATUS_PASSIVE)      != (uint8)0u)
#define CAN_30_MCAN_HW_IS_BUSOFF(state)                 (((state) & CAN_30_MCAN_STATUS_BUSOFF)       != (uint8)0u)
#define CAN_30_MCAN_HW_IS_WAKEUP(state)                 (((state) & CAN_30_MCAN_STATUS_SLEEP)        == (uint8)0u)
#define CAN_30_MCAN_HW_IS_SLEEP(state)                  (((state) & CAN_30_MCAN_STATUS_SLEEP)        != (uint8)0u)
#define CAN_30_MCAN_HW_IS_STOP(state)                   (((state) & CAN_30_MCAN_STATUS_STOP)         != (uint8)0u)
#define CAN_30_MCAN_HW_IS_START(state)                  (((state) & CAN_30_MCAN_STATUS_START)        != (uint8)0u)
#define CAN_30_MCAN_HW_IS_INCONSISTENT(state)           (((state) & CAN_30_MCAN_STATUS_INCONSISTENT) != (uint8)0u)
/* PRQA L:FctLikeMacroLabel */

/* Hardware Loop defines used by LowLevel for documentation (Core use it for loop check) */
#define kCan_30_McanLoopMode CAN_30_MCAN_LOOP_MAX

/* compatibility (LL may need this for check against current status)  */
#define kCan_30_McanHwIsInit CAN_30_MCAN_STATUS_INIT
#define kCan_30_McanHwIsSleep CAN_30_MCAN_STATUS_SLEEP

/* results of CAN RAM check */
#define CAN_30_MCAN_DEACTIVATE_CONTROLLER               CAN_30_MCAN_STATUS_INCONSISTENT
#define CAN_30_MCAN_ACTIVATE_CONTROLLER                 ((uint8)0x00u)

/***************************************************************************/
/* GenTool abstraction                                                     */
/***************************************************************************/

#define C_30_MCAN_ENABLE_STOP /* COV_CAN_COMPATIBILITY */
#if defined(V_OSTYPE_OSEK) || defined(V_OSTYPE_AUTOSAR) /* COV_CAN_OS_USAGE */
# define C_30_MCAN_ENABLE_OSEK_OS
#endif
#if (CAN_30_MCAN_TX_PROCESSING == CAN_30_MCAN_POLLING) /* COV_CAN_TX_POLLING */
# define C_30_MCAN_ENABLE_TX_POLLING
#endif
#if (CAN_30_MCAN_RX_PROCESSING == CAN_30_MCAN_POLLING) /* COV_CAN_RX_POLLING */
# define C_30_MCAN_ENABLE_RX_BASICCAN_POLLING
# define C_30_MCAN_ENABLE_RX_FULLCAN_POLLING
# define C_30_MCAN_ENABLE_RX_POLLING
#endif
#if (CAN_30_MCAN_BUSOFF_PROCESSING == CAN_30_MCAN_POLLING) /* COV_CAN_ERROR_POLLING */
# define C_30_MCAN_ENABLE_ERROR_POLLING
#endif
#if (CAN_30_MCAN_WAKEUP_PROCESSING == CAN_30_MCAN_POLLING) /* COV_CAN_WAKEUP_POLLING */
# define C_30_MCAN_ENABLE_WAKEUP_POLLING
#endif
#if (CAN_30_MCAN_INDIVIDUAL_PROCESSING == STD_ON) /* COV_CAN_INDIVIDUAL_POLLING */
# define C_30_MCAN_ENABLE_INDIVIDUAL_POLLING
#endif
#if (CAN_30_MCAN_MULTIPLE_BASICCAN == STD_ON) /* COV_CAN_MULTIPLE_BASICCAN */
# define C_30_MCAN_ENABLE_MULTIPLE_BASICCAN
#endif
#if (CAN_30_MCAN_MULTIPLE_BASICCAN_TX == STD_ON) /* COV_CAN_MULTIPLE_BASICCAN_TX */
# define C_30_MCAN_ENABLE_MULTIPLE_BASICCAN_TX
#endif
#if (CAN_30_MCAN_TX_FULLCAN_OBJECTS == STD_ON) /* COV_CAN_TX_FULLCAN_OBJECTS */
# define C_30_MCAN_ENABLE_TX_FULLCAN_OBJECTS
#endif
#if (CAN_30_MCAN_RX_FULLCAN_OBJECTS == STD_ON) /* COV_CAN_RX_FULLCAN_OBJECTS */
# define C_30_MCAN_ENABLE_RX_FULLCAN_OBJECTS
#endif
#if (CAN_30_MCAN_RX_BASICCAN_OBJECTS == STD_ON)
# define C_30_MCAN_ENABLE_RX_BASICCAN_OBJECTS
#endif
#if (CAN_30_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON) /* COV_CAN_HW_TRANSMIT_CANCELLATION */
# define C_30_MCAN_ENABLE_CANCEL_IN_HW
#endif
/* C_30_MCAN_ENABLE_CANCEL_FULLCAN_IN_HW may be user defined */
#if (CAN_30_MCAN_CANCEL_SUPPORT_API == STD_ON)
# define C_30_MCAN_ENABLE_CANCEL_SUPPORT_API
#endif
#if (CAN_30_MCAN_HARDWARE_CANCELLATION == STD_ON) /* COV_CAN_HARDWARE_CANCELLATION */
#define C_30_MCAN_ENABLE_HW_LOOP_TIMER
#endif
#if (CAN_30_MCAN_EXTENDED_ID == STD_ON) /* COV_CAN_EXTENDED_ID */
# define C_30_MCAN_ENABLE_EXTENDED_ID
#endif
#if (CAN_30_MCAN_MIXED_ID == STD_ON) /* COV_CAN_MIXED_ID */
# define C_30_MCAN_ENABLE_MIXED_ID
#endif
#if (CAN_30_MCAN_SLEEP_SUPPORT == STD_ON) /* COV_CAN_SLEEP_SUPPORT */
# if (CAN_30_MCAN_WAKEUP_SUPPORT == STD_ON) /* COV_CAN_WAKEUP_SUPPORT */
/* before version 3.12 this switches occur always synchronous both to ON or OFF (C_30_MCAN_ENABLE_WAKEUP no more used) */
/* if CAN_30_MCAN_WAKEUP_SUPPORT is switched off, STOP mode will be used instead of SLEEP (see AUTOSAR specification) */
# define C_30_MCAN_ENABLE_SLEEP_WAKEUP
# endif
#endif
#if (CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_APPL) /* COV_CAN_OVERRUN_NOTIFICATION */
# define C_30_MCAN_ENABLE_OVERRUN
# define C_30_MCAN_ENABLE_FULLCAN_OVERRUN
#endif
#if (CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_DET) /* COV_CAN_OVERRUN_NOTIFICATION */
# define C_30_MCAN_ENABLE_OVERRUN
# define C_30_MCAN_ENABLE_FULLCAN_OVERRUN
# if (CAN_30_MCAN_DEV_ERROR_REPORT != STD_ON) /* COV_CAN_COMPATIBILITY */
#  error "CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_DET need CAN_30_MCAN_DEV_ERROR_REPORT == STD_ON"
# endif
#endif
#if (CAN_30_MCAN_MULTIPLEXED_TRANSMISSION == STD_ON) /* COV_CAN_MULTIPLEXED_TRANSMISSION */
# define C_30_MCAN_ENABLE_MULTIPLEXED_TRANSMISSION
#endif
#if (CAN_30_MCAN_TX_HW_FIFO == STD_ON) /* COV_CAN_TX_HW_FIFO */
# define C_30_MCAN_ENABLE_TX_HW_FIFO
#endif
#if (CAN_30_MCAN_RX_QUEUE == STD_ON) /* COV_CAN_RX_QUEUE */
# define C_30_MCAN_ENABLE_RX_QUEUE
#endif
#if (CAN_30_MCAN_GENERIC_CONFIRMATION == STD_ON)
# define CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API1
#endif
#if (CAN_30_MCAN_GENERIC_CONFIRMATION == CAN_30_MCAN_API2) /* COV_CAN_GENERIC_CONFIRMATION_API2 */
# define CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2
#endif
#if (CAN_30_MCAN_GENERIC_PRETRANSMIT == STD_ON)
# define C_30_MCAN_ENABLE_PRETRANSMIT_FCT
#endif
#if (CAN_30_MCAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON)
# define C_30_MCAN_SINGLE_RECEIVE_CHANNEL
# define C_30_MCAN_DISABLE_MULTICHANNEL_API
# define CAN_30_MCAN_CHANNEL_CANTYPE_ONLY         void
# define CAN_30_MCAN_CHANNEL_CANTYPE_FIRST
# define CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL
# define CAN_30_MCAN_CHANNEL_CANPARA_ONLY
# define CAN_30_MCAN_CHANNEL_CANPARA_FIRST
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY      void
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_LOCAL
# define CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY
# define CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY    void
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST
# define CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT
# define CAN_30_MCAN_HW_CHANNEL_DUMMY_STATEMENT
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT
#else
# define C_30_MCAN_MULTIPLE_RECEIVE_CHANNEL
# define C_30_MCAN_ENABLE_MULTICHANNEL_API
# define CAN_30_MCAN_CHANNEL_CANTYPE_ONLY         Can_30_McanChannelHandle  Controller
# define CAN_30_MCAN_CHANNEL_CANTYPE_FIRST        Can_30_McanChannelHandle  Controller,
# define CAN_30_MCAN_CHANNEL_CANTYPE_LOCAL        Can_30_McanChannelHandle  Controller;
# define CAN_30_MCAN_CHANNEL_CANPARA_ONLY         (Can_30_McanChannelHandle) Controller
# define CAN_30_MCAN_CHANNEL_CANPARA_FIRST        (Can_30_McanChannelHandle) Controller,
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY      Can_30_McanChannelHandle  Controller
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_FIRST     Can_30_McanChannelHandle  Controller,
# define CAN_30_MCAN_HW_CHANNEL_CANTYPE_LOCAL     Can_30_McanChannelHandle  Controller;
# define CAN_30_MCAN_HW_CHANNEL_CANPARA_ONLY      (Can_30_McanChannelHandle) Controller
# define CAN_30_MCAN_HW_CHANNEL_CANPARA_FIRST     (Can_30_McanChannelHandle) Controller,
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY   Can_30_McanChannelHandle Controller
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST  Can_30_McanChannelHandle Controller,
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY   Controller
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST  Controller,
# define CAN_30_MCAN_CHANNEL_DUMMY_STATEMENT                 CAN_30_MCAN_DUMMY_STATEMENT(Controller)
# define CAN_30_MCAN_HW_CHANNEL_DUMMY_STATEMENT              CAN_30_MCAN_DUMMY_STATEMENT(Controller)
# define CAN_30_MCAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT  CAN_30_MCAN_DUMMY_STATEMENT(Controller)
#endif
#if (CAN_30_MCAN_GET_STATUS == STD_ON)
# define C_30_MCAN_ENABLE_EXTENDED_STATUS
#endif
#if (CAN_30_MCAN_RAM_CHECK == CAN_30_MCAN_NOTIFY_ISSUE) /* COV_CAN_RAM_CHECK */
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK_WAKEUP
#endif
#if (CAN_30_MCAN_RAM_CHECK == CAN_30_MCAN_NOTIFY_MAILBOX) /* COV_CAN_RAM_CHECK */
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK_WAKEUP
# define C_30_MCAN_ENABLE_NOTIFY_CORRUPT_MAILBOX
#endif
#if (CAN_30_MCAN_RAM_CHECK == CAN_30_MCAN_EXTENDED) /* COV_CAN_RAM_CHECK_EXTENDED */
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK
# define C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED
#endif
#if (CAN_30_MCAN_FD_SUPPORT != CAN_30_MCAN_NONE) /* COV_CAN_FD_SUPPORT */
# define C_30_MCAN_ENABLE_CAN_FD_USED
# if (CAN_30_MCAN_FD_SUPPORT == CAN_30_MCAN_BRS) /* COV_CAN_FD_SUPPORT */
#  define C_30_MCAN_ENABLE_CAN_FD_BRS
# endif
# if (CAN_30_MCAN_FD_SUPPORT == CAN_30_MCAN_FULL) /* COV_CAN_FD_SUPPORT */
#  define C_30_MCAN_ENABLE_CAN_FD_FULL
# endif
#endif
#if (CAN_30_MCAN_USE_INIT_POINTER == STD_ON) /* InitPointer may not be used in variant system for symmetric configuration */
# define CAN_30_MCAN_ENABLE_USE_INIT_ROOT_POINTER
#endif
#if (CAN_30_MCAN_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# define CAN_30_MCAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK
#endif
#if (CAN_30_MCAN_USE_OS_INTERRUPT_CONTROL == STD_ON) /* COV_CAN_COMPATIBILITY */
# define C_30_MCAN_ENABLE_USE_OS_INTERRUPT_CONTROL
#endif
#if (CAN_30_MCAN_SILENT_MODE == STD_ON) /* COV_CAN_COMPATIBILITY */
# define C_30_MCAN_ENABLE_SILENT_MODE
#endif
#if ((CAN_30_MCAN_INTLOCK == CAN_30_MCAN_DRIVER) || (CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH)) /* COV_CAN_LOCK_ISR_BY_APPL */
# define C_30_MCAN_ENABLE_CAN_CAN_INTERRUPT_CONTROL
#endif  
#if ( CAN_30_MCAN_PROTECTED_MODE == STD_ON ) /* COV_CAN_COMPATIBILITY */
# define C_30_MCAN_ENABLE_USER_MODE_OS
#endif
#if ( CAN_30_MCAN_FD_HW_BUFFER_OPTIMIZATION == STD_ON ) /* COV_CAN_COMPATIBILITY */
# define C_30_MCAN_ENABLE_CAN_FD_HW_BUFFER_OPTIMIZATION
#endif
#if (CAN_30_MCAN_CHECK_WAKEUP_CAN_RET_TYPE == STD_ON) /* COV_CAN_COMPATIBILITY */
# define C_30_MCAN_ENABLE_CHECK_WAKEUP_CAN_RET_TYPE
#endif
#if (CAN_30_MCAN_SECURITY_EVENT_REPORTING == STD_ON)
# define CAN_30_MCAN_ENABLE_SECURITY_EVENT_REPORTING
#endif

/***************************************************************************/
/* Compiler abstraction                                                    */
/***************************************************************************/
#if !defined(V_NULL) /* COV_CAN_COMPATIBILITY */
# define V_NULL          NULL_PTR
#endif
#if !defined(V_NONE) /* COV_CAN_COMPATIBILITY */
# define V_NONE       /* empty used instead of external, STATIC, volatile... */
# define CAN_AUTOMATIC    AUTOMATIC
# define CAN_TYPEDEF      TYPEDEF
#endif
#if !defined(CAN_STATIC) /* COV_CAN_COMPATIBILITY */
# if defined(STATIC) /* COV_CAN_COMPATIBILITY */
#  define CAN_STATIC  STATIC   /* standard by AutoSar 3.x */
# else
#  define CAN_STATIC  static   /* standard AutoSar 4.x define */
# endif
#endif
#if !defined(CAN_LOCAL_INLINE) /* COV_CAN_COMPATIBILITY */
# if defined(LOCAL_INLINE) /* COV_CAN_COMPATIBILITY */
#  define CAN_LOCAL_INLINE  LOCAL_INLINE
# else
#  define CAN_LOCAL_INLINE  
# endif
#endif

/* PRQA S 0342,3453 CompilerAbstractionLabel */ /* MD_Can_CompilerAbstraction,MD_MSR_FctLikeMacro */
#define V_DEF_30_MCAN_VAR(storage, vartype, memclass)                    storage VAR(vartype, CAN_30_MCAN_##memclass)
#define V_DEF_30_MCAN_VAR_FAR(storage, vartype)                          storage VAR(vartype, CAN_30_MCAN_VAR_FAR)
#define V_DEF_30_MCAN_VAR_NEAR(storage, vartype)                         storage VAR(vartype, CAN_30_MCAN_VAR_NEAR)
#define V_DEF_30_MCAN_VAR_TYPE(storage, vartype)                         typedef storage VAR(vartype, TYPEDEF)
#define V_DEF_30_MCAN_P2VAR(storage, ptrtype, memclass, ptrclass)        storage P2VAR(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_P2VAR_TYPE(storage, ptrtype, ptrclass)             typedef storage P2VAR(ptrtype, TYPEDEF, CAN_30_MCAN_##ptrclass )
#define V_DEF_30_MCAN_P2VAR_PARA(storage, ptrtype, memclass, ptrclass)   storage P2VAR(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_P2SFR_CAN(storage, ptrtype, memclass)              storage P2VAR(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_REG_CANCELL)
#define V_DEF_30_MCAN_P2SFR_CAN_TYPE(storage, ptrtype)                   typedef storage P2VAR(ptrtype, TYPEDEF, CAN_30_MCAN_REG_CANCELL)
#define V_DEF_30_MCAN_CONSTP2VAR(storage, ptrtype, memclass, ptrclass)   storage CONSTP2VAR(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_CONST(storage, type, memclass)                     storage CONST(type, CAN_30_MCAN_##memclass)
#define V_DEF_30_MCAN_CONST_TYPE(storage, type, memclass)                typedef storage CONST(type, TYPEDEF)
#define V_DEF_30_MCAN_P2CONST(storage, ptrtype, memclass, ptrclass)      storage P2CONST(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_P2CONST_TYPE(storage, ptrtype, ptrclass)           typedef storage P2CONST(ptrtype, TYPEDEF, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_P2CONST_PARA(storage, ptrtype, memclass, ptrclass) storage P2CONST(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_CONSTP2CONST(storage, ptrtype, memclass, ptrclass) storage CONSTP2CONST(ptrtype, CAN_30_MCAN_##memclass, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_CONSTP2CONST_TYPE(storage, ptrtype, ptrclass)      typedef storage CONSTP2CONST(ptrtype, TYPEDEF, CAN_30_MCAN_##ptrclass)
#define V_DEF_30_MCAN_FUNC(storage, rettype, memclass)                   storage FUNC(rettype, CAN_30_MCAN_##memclass)
#define V_DEF_30_MCAN_FUNC_API(storage, rettype, memclass)               storage FUNC(rettype, CAN_30_MCAN_##memclass)
#define V_DEF_30_MCAN_FUNC_CBK(storage, rettype, memclass)               storage FUNC(rettype, CAN_30_MCAN_##memclass)
#define V_DEF_30_MCAN_P2FUNC(storage, rettype, ptrclass, fctname)        storage P2FUNC(rettype, CAN_30_MCAN_##ptrclass, fctname)
/* PRQA L:CompilerAbstractionLabel */

/* only use internal when not defined before */
#if !defined(vuint8) /* COV_CAN_COMPATIBILITY */
# define CAN_30_MCAN_HL_NO_V_DEF
# define vuint8 uint8
#endif
#if !defined(vsint8) /* COV_CAN_COMPATIBILITY */
# define vsint8 sint8
#endif
#if !defined(vuint16) /* COV_CAN_COMPATIBILITY */
# define vuint16 uint16
#endif
#if !defined(vsint16) /* COV_CAN_COMPATIBILITY */
# define vsint16 sint16
#endif
#if !defined(vuint32) /* COV_CAN_COMPATIBILITY */
# define vuint32 uint32
#endif
#if !defined(vsint32) /* COV_CAN_COMPATIBILITY */
# define vsint32 sint32
#endif

/***************************************************************************/
/* LL return values                                                        */
/***************************************************************************/

/* return values of Can_30_McanRxActualIdType */
#define kCan_30_McanIdTypeStd       (0x00U)
#define kCan_30_McanIdTypeExt       (0x40000000UL)
#define kCan_30_McanFdTypeClassic   ((vuint8)0x00U)
#define kCan_30_McanFdTypeFd        ((vuint8)0x20U)   /* EDL(FDF) */
#define kCan_30_McanFdBrsTypeTrue   ((vuint8)0x10u)   /* BRS */
#define kCan_30_McanFdBrsTypeFalse  ((vuint8)0x00u)


/* Switches are generated directly with Geny */
#if (CAN_30_MCAN_REGEXT_MCMCAN == STD_ON)             /* COV_CAN_HW_SPECIFIC */
# define C_30_MCAN_ENABLE_REGEXT_MCMCAN
#else
# define C_30_MCAN_DISABLE_REGEXT_MCMCAN
#endif

#if (CAN_30_MCAN_REGEXT_MCANSS == STD_ON)             /* COV_CAN_HW_SPECIFIC */
# define C_30_MCAN_ENABLE_REGEXT_MCANSS
#else
# define C_30_MCAN_DISABLE_REGEXT_MCANSS
#endif /* CAN_30_MCAN_REGEXT_MCANSS */

#if defined (C_30_MCAN_ENABLE_REGEXT_MCANSS)          /* COV_CAN_HW_SPECIFIC */

# if (CAN_30_MCAN_MCANSS_ECC_EOI == STD_ON)           /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_ECC_EOI
# else
#  define C_30_MCAN_DISABLE_MCANSS_ECC_EOI
# endif /* CAN_30_MCAN_MCANSS_ECC_EOI  */

# if (CAN_30_MCAN_MCANSS_CTRL_0 == STD_ON)            /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_CTRL_0
# else
#  define C_30_MCAN_DISABLE_MCANSS_CTRL_0
# endif /* CAN_30_MCAN_MCANSS_CTRL_0 */

# if (CAN_30_MCAN_MCANSS_CTRL_1 == STD_ON)            /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_CTRL_1
# else
#  define C_30_MCAN_DISABLE_MCANSS_CTRL_1
# endif /* CAN_30_MCAN_MCANSS_CTRL_1 */

# if (CAN_30_MCAN_MCANSS_EOI == STD_ON)               /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_EOI
# else
#  define C_30_MCAN_DISABLE_MCANSS_EOI
# endif /* CAN_30_MCAN_MCANSS_EOI */

# if (CAN_30_MCAN_MCANSS_ECC_AGGR == STD_ON)          /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_ECC_AGGR
# else
#  define C_30_MCAN_DISABLE_MCANSS_ECC_AGGR
# endif /* CAN_30_MCAN_MCANSS_ECC_AGGR */

# if (CAN_30_MCAN_MCANSS_ECC_VBUSS == STD_ON)         /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_MCANSS_ECC_VBUSS
# else
#  define C_30_MCAN_DISABLE_MCANSS_ECC_VBUSS
# endif /* CAN_30_MCAN_MCANSS_ECC_VBUSS */

#endif /* C_30_MCAN_ENABLE_REGEXT_MCANSS */

# if (CAN_30_MCAN_REGEXT_SICANFD == STD_ON)           /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_REGEXT_SICANFD
# else
#  define C_30_MCAN_DISABLE_REGEXT_SICANFD
# endif

# if (CAN_30_MCAN_REGEXT_TTCANFD == STD_ON)           /* COV_CAN_HW_SPECIFIC */
#   define C_30_MCAN_ENABLE_REGEXT_TTCANFD
# else
#   define C_30_MCAN_DISABLE_REGEXT_TTCANFD
# endif

# if (CAN_30_MCAN_SHM_DATAQOS == STD_ON)              /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_SHM_DATAQOS
# else
#  define C_30_MCAN_DISABLE_SHM_DATAQOS
# endif


# if (CAN_30_MCAN_REGEXT_MCANAS1 == STD_ON)           /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_REGEXT_MCANAS1
# else
#  define C_30_MCAN_DISABLE_REGEXT_MCANAS1
# endif


# if (CAN_30_MCAN_REGEXT_STMFDCAN == STD_ON)          /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_REGEXT_STMFDCAN
# else
#  define C_30_MCAN_DISABLE_REGEXT_STMFDCAN
# endif

# if (CAN_30_MCAN_REGEXT_TCC == STD_ON)               /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_REGEXT_TCC
# else
#  define C_30_MCAN_DISABLE_REGEXT_TCC
# endif

# if (CAN_30_MCAN_REGEXT_TCC_PWD == STD_ON)           /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_REGEXT_TCC_PWD
# else
#  define C_30_MCAN_DISABLE_REGEXT_TCC_PWD
# endif


# if (CAN_30_MCAN_PARITY_INTERRUPT == STD_ON)         /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_PARITY_INTERRUPT
# else
#  define C_30_MCAN_DISABLE_PARITY_INTERRUPT
# endif

# if ( CAN_30_MCAN_ECC_INIT_SHM == STD_ON )           /* COV_CAN_COMPATIBILITY */
#  define C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM
# else
#  define C_30_MCAN_DISABLE_CAN_ECC_INIT_SHM
# endif

# if defined (CAN_30_MCAN_CANSUBSYSTEMBASEADR)                /* COV_CAN_HW_SPECIFIC */
#  if ( CAN_30_MCAN_CANSUBSYSTEMBASEADR == STD_ON )           /* COV_CAN_COMPATIBILITY */
#   define C_30_MCAN_ENABLE_CANSUBSYSTEMBASEADR
#  else
#   define C_30_MCAN_DISABLE_CANSUBSYSTEMBASEADR
#  endif
# else 
#  define C_30_MCAN_DISABLE_CANSUBSYSTEMBASEADR
# endif

# if defined (CAN_30_MCAN_CANGLOBALBASEADR)                /* COV_CAN_HW_SPECIFIC */
#  if ( CAN_30_MCAN_CANGLOBALBASEADR == STD_ON )           /* COV_CAN_COMPATIBILITY */
#   define C_30_MCAN_ENABLE_CANGLOBALBASEADR
#  else
#   define C_30_MCAN_DISABLE_CANGLOBALBASEADR
#  endif
# else 
#  define C_30_MCAN_DISABLE_CANGLOBALBASEADR
# endif

# if ( CAN_30_MCAN_UPDATE_BASE_ADDRESS == STD_ON )           /* COV_CAN_COMPATIBILITY */
#  define C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS
# else
#  define C_30_MCAN_DISABLE_UPDATE_BASE_ADDRESS
# endif


/***************************************************************************/
/* LL parameter values                                                     */
/***************************************************************************/

/* PRQA S 3453 EOF */ /* MD_MSR_FctLikeMacro */
/* parameter for Appl_30_McanCanTimerStart(),-End(), -Loop() */
# define kCan_30_McanLoopInit          ((vuint8)0x00u)
# define kCan_30_McanLoopRxFifo        ((vuint8)0x01u)
# define kCan_30_McanLoopClockStop     ((vuint8)0x02u)
#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
# define kCan_30_McanStmFdLoopInit     ((vuint8)0x05u)
#endif

/* \trace SPEC-1399 */
/***************************************************************************/
/* data types need for API                                                 */
/***************************************************************************/
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, Std_VersionInfoType, APPL_VAR) Can_30_Mcan_VersionInfoPtrType;
V_DEF_30_MCAN_P2CONST_TYPE(V_NONE, Can_30_Mcan_ConfigType, CONST_PBCFG) Can_30_Mcan_ConfigPtrType;
V_DEF_30_MCAN_P2CONST_TYPE(V_NONE, Can_PduType, APPL_VAR)           Can_30_Mcan_PduInfoPtrType;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, Can_PduType, APPL_VAR)             Can_30_Mcan_PduInfoPtrType_var;
V_DEF_30_MCAN_P2CONST_TYPE(V_NONE, uint8, RX_TX_DATA)               Can_30_Mcan_DataPtrType;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, uint8, APPL_VAR)                   Can_30_Mcan_ErrorCounterPtrType;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, Can_ControllerStateType, APPL_VAR) Can_30_Mcan_ControllerStatePtrType;
V_DEF_30_MCAN_P2VAR_TYPE(V_NONE, Can_ErrorStateType, APPL_VAR)      Can_30_Mcan_ErrorStatePtrType;

/* data types for driver function parameters */

/* Can_30_McanObjectHandle has to be unsigned! */
# define Can_30_McanObjectHandle  Can_HwHandleType

V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint16) Can_30_McanTransmitHandle;
V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint16) Can_30_McanReceiveHandle;

V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint16) Can_30_McanInitHandle;

V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint32) tCan_30_McanRxId0;
V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint32) tCan_30_McanTxId0;


/* Pointer to msg object and message data used in precopy functions */

V_DEF_30_MCAN_P2SFR_CAN_TYPE(volatile, vuint8)  Can_30_McanChipDataPtr;
V_DEF_30_MCAN_P2SFR_CAN_TYPE(volatile, vuint8)  Can_30_McanChipMsgPtr8;
V_DEF_30_MCAN_P2SFR_CAN_TYPE(volatile, vuint16) Can_30_McanChipMsgPtr16;
V_DEF_30_MCAN_P2SFR_CAN_TYPE(volatile, vuint32) Can_30_McanChipMsgPtr32;

typedef vuint32 tCan_30_McanDlc;

typedef struct tShiftMultiplyValueTypeTag 
{ /* CAN FD calculation values */
  vuint8 v1;
  vuint8 v2;
  vuint8 v3;
} tShiftMultiplyValueType;

typedef volatile struct t_30_McanSIFETypeTag 
{ /* Std filter element */
  volatile vuint32 S0;
} t_30_McanSIFEType;

typedef volatile struct t_30_McanXIFETypeTag
{ /* Ext filter element */
  volatile vuint32 F0;
  volatile vuint32 F1;
} t_30_McanXIFEType;

typedef union
{ /* PRQA S 0750 1 */ /* MD_MSR_18.4 */
  vuint8   b[4];
  vuint16  w[2];
  vuint32  dw;
} tAlignCopyElem;

typedef union
{ /* PRQA S 0750 1 */ /* MD_MSR_18.4 */
  vuint32  dw[2];
#if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
volatile vuint32  data[64/4]; /* this address must 32-bit aligned */
# else
volatile vuint32  data[8/4];  /* this address must 32-bit aligned */
#endif
} tAlign32bit;

typedef volatile struct t_30_McanElmTypeTag
{ /* Buffer and Fifo element */
 volatile vuint32 E0;               /* +0  Bit 31     ESI: Error State Indicator (0=Transmitting node is error active, 1=Transmitting node is error passive)
                                           Bit 30     XTD: 0=11-bit standard identifier, 1=29-bit extended identifier
                                           Bit 29     RTR: 0=data frame, 1=remote frame 
                                           Bit 28:0   ID[28:0]: ExtId, ID[28:18] StdId (depending on bit XTD) */
 volatile vuint32 E1;               /* +4  Bit 31     ANMF: 0=Received frame matching filter index FIDX, 1=Received frame did not match any Rx filter element
                                           Bit 30:24  FIDX[6:0]: 0-127=Index of matching Rx acceptance filter element (invalid if ANMF = '1')
                                           Bit 21     EDL: Extended Data Length, (0=Standard frame format, 1=CAN FD frame format (new DLC-coding and CRC))
                                           Bit 20     BRS: Bit Rate Switch (0=Frame received without bit rate switching, 1=Frame received with bit rate switching)
                                           Bit 19:16  DLC[3:0] : 0-8  =Received frame has 0-8 data bytes, 9-15 =Received frame has 8 data bytes
                                           Bit 15:0   RXTS[15:0]: Rx Timestamp Counter value captured on start of frame reception (Resolution depends on Prescaler TSCC[TCP] */
#if defined(C_30_MCAN_ENABLE_CAN_FD_FULL)
volatile vuint32  data[64/4];      /* +8  R2: Data byte 3-0 ... */
# else
volatile vuint32  data[8/4];       /* +8  R2: Data byte 3-0 ... */
#endif
} t_30_McanElmType;
V_DEF_30_MCAN_VAR_TYPE(V_NONE, t_30_McanElmType) Can_30_McanElmType;
typedef volatile struct tTxEventFifoElmTypeTag
{ /* Tx Event Fifo element */
 volatile vuint32 E0;               /* +0  Bit 30     XTD: 0=11-bit standard identifier, 1=29-bit extended identifier
                                           Bit 29     RTR: 0=Data frame transmitted, 1=Remote frame transmitted
                                           Bit 28:0   ID[28:0]= ExtId, ID[28:18]= StdId (depending on bit XTD) */
 volatile vuint32 E1;               /* +4  Bit 31:24  MM[7:0]: Message Marker - Copied from Tx Buffer into Tx Event FIFO element for identification of Tx message status
                                           Bit 23:22  ET[1:0]: Event Type - 00,11=Reserved, 01=Tx event, 10=Transmission in spite of cancellation (always set for transmissions in DAR mode)
                                           Bit 19:16  DLC[3:0] 0-8 =Frame with 0-8 data bytes transmitted, 9-15 =Frame with 8 data bytes transmitted
                                           Bit 15:0   TXTS[15:0]: Tx Timestamp Counter value captured on start of frame transmission (Resolution depends on Prescaler TSCC[TCP] */
} tTxEventFifoElmType;


/* type of variable for ID type kCan_30_McanIdTypeExt or kCan_30_McanIdTypeStd will be assigned to
   a variable of this type */
V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint32) tCan_30_McanIdType;
V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint32) tCan_30_McanFdType;
V_DEF_30_MCAN_VAR_TYPE(V_NONE, vuint32) tCan_30_McanFdBrsType;

typedef tCan_30_McanLLCanIntOld *tCan_30_McanLLCanIntOldPtr;


# if !defined(CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT) /* COV_CAN_COMPATIBILITY */
#  define CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT STD_OFF
# endif

#if defined(CAN_30_MCAN_GEN_COM_STACK_LIB) /* COV_CAN_MICROSAR_VERSION */
# if (CAN_30_MCAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
#  define CAN_30_MCAN_USE_PHYSTOLOG_MAPPING
# endif
#else
# if defined(C_30_MCAN_ENABLE_MULTI_ECU_CONFIG)
#  define CAN_30_MCAN_USE_PHYSTOLOG_MAPPING
# endif
#endif

/* CAN Macro accessor */
#define Cn          ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetCanBasisAdr(channel)))
#if defined( C_30_MCAN_SINGLE_RECEIVE_CHANNEL )
# define CnX(ch)    ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetCanBasisAdr(0)))
#else
# define CnX(ch)    ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetCanBasisAdr((ch))))
#endif


#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS )  /* COV_CAN_HW_SPECIFIC */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#  define McanExtraGlobalReg(ch)  ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMCanSsGlobalRegObjType, AUTOMATIC)) (Can_30_Mcan_GetCanVirtualMcanSsBaseAddr(ch))) /* MCANSS Control extra registers pointer layout */
#  define McanEccReg(ch)          ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMCanSsCanEccRegObjType, AUTOMATIC)) (Can_30_Mcan_GetCanVirtualMcanEccBaseAddr(ch))) /* MCANSS ECC extra registers pointer layout */
# else
#  define McanExtraGlobalReg(ch)  ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMCanSsGlobalRegObjType, AUTOMATIC)) (Can_30_Mcan_GetCanMcanSsBaseAddr(ch))) /* MCANSS Control extra registers pointer layout */

#  define McanEccReg(ch)          ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMCanSsCanEccRegObjType, AUTOMATIC)) (Can_30_Mcan_GetCanEccAggrBaseAddr(ch))) /* MCANSS ECC extra registers pointer layout */
# endif
#endif /* C_30_MCAN_ENABLE_REGEXT_MCANSS */

#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
# define SICANFD(ch)   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanSICanFDCanGlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanBasisAdr(ch)+SICANFD_FS_ECC_ADDR_OFFSET)) /* Base Address of Functional Safety Registers for SICANFD */
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
# define TTCANFD(ch)        ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanTTCanFDCanGlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanBasisAdr(ch)+TTCANFD_RXFTOP_CTL_ADDR_OFFSET)) /* Traveo2 Channel Specific Base */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#  define TTCANFD_SUB(sub) ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanTTCanFDSubSystemCanGlobalObjType, AUTOMATIC)) Can_30_Mcan_GetCanVirtualSubSystemBaseAdr(Index))
# else
# define TTCANFD_SUB(sub)   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanTTCanFDSubSystemCanGlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanSubSystemBaseAdr(sub)))
# endif
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC_FUNCTIONALITY */
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#  define MCANAS1_FSECC   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMcanAs1GlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanVirtualGlobalBaseAdr() + MCANAS1_FS_ECC_ADDR_OFFSET)) /* Base Address of Functional Safety Registers for MCANAS1 */
# else
#  define MCANAS1_FSECC   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanMcanAs1GlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanGlobalBaseAdr() + MCANAS1_FS_ECC_ADDR_OFFSET)) /* Base Address of Functional Safety Registers for MCANAS1 */
# endif
# define MCANAS1_CLRIRCAUSE(bit) *(vuint32*)MCANAS1_G24IRCLR_ADDR= (1<<bit)
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
# define STMFD_OFFSET_GLOBAL_MCAN0  0x800
# if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#  define STMFDCAN_CCU   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanStmFdCanGlobalObjType, AUTOMATIC))Can_30_Mcan_GetCanVirtualGlobalBaseAdr()) /* STM32 FDCAN */
#  define STMFDCAN_MCAN0 ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC)) (Can_30_Mcan_GetCanVirtualGlobalBaseAdr() - STMFD_OFFSET_GLOBAL_MCAN0))
# else 
#  define STMFDCAN_CCU   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanStmFdCanGlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanGlobalBaseAdr())) /* STM32 FDCAN */
# define STMFDCAN_MCAN0  ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetCanGlobalBaseAdr() - STMFD_OFFSET_GLOBAL_MCAN0))
# endif
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TCC ) /* COV_CAN_HW_SPECIFIC */
#  if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#   define TCC_CFG   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanTCC80XXCfgGlobalObjType, AUTOMATIC)) Can_30_Mcan_GetCanVirtualGlobalBaseAdr())
#  else
 # define TCC_CFG   ((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanTCC80XXCfgGlobalObjType, AUTOMATIC))(Can_30_Mcan_GetCanGlobalBaseAdr())) /* TCC80XX */
#  endif
#endif

#define GET_SIDF_OFFSET(num) ((vuint32)(num) << 2u)
#define GET_XIDF_OFFSET(num) ((vuint32)(num) << 3u)
#define GET_TXEF_OFFSET(num) ((vuint32)(num) << 3u)


/* PRQA S 0635 QAC_Can_635 */ /* MD_Can_0635 */
/* PRQA S 0750 QAC_Can_635 */ /* MD_MSR_18.4 */
#if defined (C_CPUTYPE_BITORDER_MSB2LSB) /* COV_CAN_CPUTYPE */
typedef volatile struct t_30_McanCanChipMsgPtrTag    /*! MCAN Message RAM Rx Buffer structure */
{
  union
  {
    struct                                 /*! MCAN Message RAM Rx Buffer R0 structure */
    {
      volatile vuint32 ESI:1;  /*! Error State Indicator */
      volatile vuint32 XTD:1;  /*! Extended Identifier */
      volatile vuint32 RTR:1;  /*! Remote Transmission Request */
      volatile vuint32 ID:29;  /*! CAN Identifier */
    } b0;
    volatile vuint32 B0;
  } uB0;
  union
  {
    struct                                 /*! MCAN Message RAM Rx Buffer R1 structure */
    {
      volatile vuint32 ANMF:1; /*! Accepted Non-matching Frame */
      volatile vuint32 FIDX:7; /*! Filter Index */
      volatile vuint32 r0:2;   /*! reserved */
      volatile vuint32 FDF:1;  /*! FD Format */
      volatile vuint32 BRS:1;  /*! Bit Rate Switch */
      volatile vuint32 DLC:4;  /*! Data Length Code */
      volatile vuint32 RXTS:16;/*! Rx Timestamp */
    } rb1;
    struct                                 /*! MCAN Message RAM Tx Buffer T1 structure */
    {
      volatile vuint32 MM:8;     /*! Message Marker */
      volatile vuint32 EFC:1;    /*! Event Fifo Control */
      volatile vuint32 r0:1;     /*! reserved */
      volatile vuint32 FDF:1;    /*! FD Format */
      volatile vuint32 BRS:1;    /*! Bit Rate Switch */
      volatile vuint32 DLC:4;    /*! Data Length Code */
      volatile vuint32 r1:16;    /*! reserved */
    } tb1;
    volatile vuint32 B1;
  } uB1;
# if defined( C_30_MCAN_ENABLE_CAN_FD_FULL )
volatile vuint32  data[64/4];      /* +8  R2: Data byte 3-0 ... */
# else
volatile vuint32  data[8/4];       /* +8  R2: Data byte 3-0 ... */
# endif
} t_30_McanCanChipMsgPtr;

V_DEF_30_MCAN_P2SFR_CAN_TYPE(V_NONE, t_30_McanCanChipMsgPtr) Can_30_McanChipMsgPtr;

typedef union t_30_McanRXFnSTag
{  /*! MCAN RXF(0/1)S register Fifo structure */
  vuint32 R;
  struct
  {
    vuint32 r0:6;     /*! reserved */
    vuint32 RFnL:1;   /*! Fifo Message Lost */
    vuint32 FnF:1;    /*! Fifo Full */
    vuint32 r1:10;    /*! reserved (F(0/1)PI unused) */
    vuint32 FnGI:6;   /*! Fifo Get index */
    vuint32 r2:1;     /*! reserved */
    vuint32 FnFL:7;   /*! Fifo Fill Level */
  } B;
} t_30_McanRXFnS;

typedef union t_30_McanRXFnCTag
{  /*! MCAN RXF(0/1)C register Fifo structure */
  vuint32 R;
  struct
  {
    vuint32:1;        /*! FIFO 0 Operation Mode */
    vuint32 F0WM:7;   /*! Fifo Watermark */
    vuint32:1;        /*! reserved */
    vuint32 F0S:7;    /*! Fifo Size */
    vuint32 FOSA:14;  /*! Fifo Start Address */
    vuint32:2;        /*! reserved */
  } B;
} t_30_McanRXFnC;

typedef union t_30_McanRXESCTag
{ /*! Rx Buffer/Fifo Element Size Configuration */
  vuint32 R;
  struct
  {
    vuint32:21;     /*! reserved */
    vuint32 RBDS:3; /*! Rx Buffer Data Field Size */
    vuint32:1;      /*! reserved */
    vuint32 F1DS:3; /*! Rx FIFO 1 Data Field Size */
    vuint32:1;      /*! reserved */
    vuint32 F0DS:3; /*! Rx FIFO 0 Data Field Size */
  } B;
} t_30_McanRXESC;

typedef union t_30_McanTXFQSTag
{ /*! Tx FIFO/Queue Status */
  vuint32 R;
  struct
  {
    vuint32:10;      /*! reserved */
    vuint32 TFQF:1;  /*! Tx FIFO/Queue Full */
    vuint32 TFQPI:5; /*! Tx FIFO/Queue Put Index */
    vuint32:3;       /*! reserved */
    vuint32 TFGI:5;  /*! Tx FIFO Get Index */
    vuint32:2;       /*! reserved */
    vuint32 TFFL:6;  /*! Tx FIFO Free Level */
  } B;
} t_30_McanTXFQS;

typedef union t_30_McanTXEFSTag
{  /*! Tx Event FIFO Status */
  vuint32 R;
  struct
  {
      vuint32:6;      /*! reserved */
      vuint32 TEFL:1; /*! Tx Event FIFO Element Lost */
      vuint32 EFF:1;  /*! Event FIFO Full */
      vuint32:11;     /*! Event FIFO Put Index, reserved  */
      vuint32 EFGI:5; /*! Event FIFO Get Index */
      vuint32:2;      /*! reserved */
      vuint32 EFFL:6; /*! Event FIFO Fill Level */
  } B;
} t_30_McanTXEFS;

#else  /* C_CPUTYPE_BITORDER_MSB2LSB */

typedef volatile struct t_30_McanCanChipMsgPtrTag
{ /*! MCAN Message RAM Rx Buffer R0 structure */
  union
  {
    struct
    {
      volatile vuint32 ID:29;  /*! CAN Identifier */
      volatile vuint32 RTR:1;  /*! Remote Transmission Request */
      volatile vuint32 XTD:1;  /*! Extended Identifier */
      volatile vuint32 ESI:1;  /*! Error State Indicator */
    } b0;
    volatile vuint32 B0;
  } uB0;
  union
  {
    struct
    {  /*! MCAN Message RAM Rx Buffer R1 structure */
      volatile vuint32 RXTS:16;/*! Rx Timestamp */
      volatile vuint32 DLC:4;  /*! Data Length Code */
      volatile vuint32 BRS:1;  /*! Bit Rate Switch */
      volatile vuint32 FDF:1;  /*! FD Format */
      volatile vuint32 r0:2;   /*! reserved */
      volatile vuint32 FIDX:7; /*! Filter Index */
      volatile vuint32 ANMF:1; /*! Accepted Non-matching Frame */
    } rb1;
    struct
    { /*! MCAN Message RAM Tx Buffer T1 structure */
      volatile vuint32 r1:16;  /*! reserved */
      volatile vuint32 DLC:4;  /*! Data Length Code */
      volatile vuint32 BRS:1;  /*! Bit Rate Switch */
      volatile vuint32 FDF:1;  /*! FD Format */
      volatile vuint32 r0:1;   /*! reserved */
      volatile vuint32 EFC:1;  /*! Event Fifo Control */
      volatile vuint32 MM:8;   /*! Message Marker */
    } tb1;
    vuint32 B1;
  } uB1;
# if defined( C_30_MCAN_ENABLE_CAN_FD_FULL )
volatile vuint32  data[64/4];      /* +8  R2: Data byte 3-0 ... */
# else
volatile vuint32  data[8/4];       /* +8  R2: Data byte 3-0 ... */
# endif
} t_30_McanCanChipMsgPtr;

V_DEF_30_MCAN_P2SFR_CAN_TYPE(V_NONE, t_30_McanCanChipMsgPtr) Can_30_McanChipMsgPtr;

typedef union t_30_McanRXFnSTag
{ /*! MCAN RXF(0/1)S register Fifo structure */
  vuint32 R;
  struct
  {
    vuint32 FnFL:7; /*! Fifo Fill Level */
    vuint32 r2:1;   /*! reserved */
    vuint32 FnGI:6; /*! Fifo Get index */
    vuint32 r1:10;  /*! reserved (F(0/1)PI unused) */
    vuint32 FnF:1;  /*! Fifo Full */
    vuint32 RFnL:1; /*! Fifo Message Lost */
    vuint32 r0:6;   /*! reserved */
  } B;
} t_30_McanRXFnS;

typedef union t_30_McanRXFnCTag
{ /*! MCAN RXF(0/1)C register Fifo structure */
  vuint32 R;
  struct
  {
    vuint32:2;        /*! reserved */
    vuint32 FOSA:14;  /*! Fifo Start Address */
    vuint32 F0S:7;    /*! Fifo Size */
    vuint32:1;        /*! reserved */
    vuint32 F0WM:7;   /*! Fifo Watermark */
    vuint32:1;        /*! FIFO 0 Operation Mode */
  } B;
} t_30_McanRXFnC;


typedef union t_30_McanRXESCTag
{ /*! Rx Buffer/Fifo Element Size Configuration */
  vuint32 R;
  struct
  {
    vuint32 F0DS:3; /*! Rx FIFO 0 Data Field Size */
    vuint32:1;      /*! reserved */
    vuint32 F1DS:3; /*! Rx FIFO 1 Data Field Size */
    vuint32:1;      /*! reserved */
    vuint32 RBDS:3; /*! Rx Buffer Data Field Size */
    vuint32:21;     /*! reserved */
  } B;
} t_30_McanRXESC;

typedef union t_30_McanTXFQSTag
{ /*! Tx FIFO/Queue Status */
  vuint32 R;
  struct
  {
    vuint32 TFFL:6;  /*! Tx FIFO Free Level */
    vuint32:2;       /*! reserved */
    vuint32 TFGI:5;  /*! Tx FIFO Get Index */
    vuint32:3;       /*! reserved */
    vuint32 TFQPI:5; /*! Tx FIFO/Queue Put Index */
    vuint32 TFQF:1;  /*! Tx FIFO/Queue Full */
    vuint32:10;      /*! reserved */
  } B;
} t_30_McanTXFQS;

typedef union t_30_McanTXEFSTag
{  /*! Tx Event FIFO Status */
  vuint32 R;
  struct
  {
      vuint32 EFFL:6; /*! Event FIFO Fill Level */
      vuint32 r1:2;   /*! reserved */
      vuint32 EFGI:5; /*! Event FIFO Get Index */
      vuint32:11;     /*! Event FIFO Put Index, reserved  */
      vuint32 EFF:1;  /*! Event FIFO Full */
      vuint32 TEFL:1; /*! Tx Event FIFO Element Lost */
      vuint32 r0:6;   /*! reserved */
  } B;
} t_30_McanTXEFS;

#endif  /* C_CPUTYPE_BITORDER_MSB2LSB */
/* PRQA  L:QAC_Can_635 */


typedef volatile struct tCan_30_McanObjTypeTag
{ /*! Can module structure */
  volatile vuint32 CREL;            /*! 0x0000         Core Release Register  */
  volatile vuint32 ENDN;            /*! 0x0004         Endian Register        */
# if defined(C_30_MCAN_ENABLE_SHM_DATAQOS) /* COV_CAN_HW_SPECIFIC_FUNCTIONALITY */
  volatile vuint32 MRCFG;           /*! 0x0008         Message RAM Configuration */
# else
  volatile vuint32 res0[1];         /*! 0x0008         Reserved */
# endif
  volatile vuint32 FBTP;            /*! 0x000C(RP)     Fast Bit Timing and Prescaler Register
                                                       Since MCAN Rev. 3.1.0: FBTP renamed to DBTP and restructured
                                                       - TDCO (bit 28:24) moved to new register TDCR
                                                       - increased confguration range for data bit timing */
  volatile vuint32 TEST;            /*! 0x0010         Test Register          */
  volatile vuint32 RWD;             /*! 0x0014(RP)     RAM Watchdog Register  */
  volatile vuint32 CCCR;            /*! 0x0018(RP)     CC Control Register    */
  volatile vuint32 BTP;             /*! 0x001C(RP)     Bit Timing and Prescaler Register, renamed to NBTP with Revision 3.1.0 */
  volatile vuint32 TSCC;            /*! 0x0020(RP)     Timestamp Counter Configuration    */
  volatile vuint32 TSCV;            /*! 0x0024         Timestamp Counter Value Register   */
  volatile vuint32 TOCC;            /*! 0x0028(RP)     Timeout Counter Configuration      */
  volatile vuint32 TOCV;            /*! 0x002C         Timeout Counter Value Register     */
           vuint32 res1[4];         /*! 0x0030-0x003C  Reserved */
  volatile vuint32 ECR;             /*! 0x0040         Error Counter Register    */
  volatile vuint32 PSR;             /*! 0x0044         Protocol Status Register  */
#if ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_MAJOR_CREL() >= 3u ) && ( Can_30_Mcan_GetC_ENABLE_MPC5700_MCAN_CREL_STEP() >= 1u ) /* COV_CAN_HW_SPECIFIC */
  /*! since MCAN Rev. 3.1.0 TDCO moved to new register TDCR */
  volatile vuint32 TDCR;            /*! 0x0048         Transmitter Delay Compensation     */
           vuint32 res2;            /*! 0x004C         Reserved */
#else
           vuint32 res2[2];         /*! 0x0048-0x004C  Reserved */
#endif
  volatile vuint32 IR;              /*! 0x0050         Interrupt Register        */
  volatile vuint32 IE;              /*! 0x0054         Interrupt Enable Register */
  volatile vuint32 ILS;             /*! 0x0058         Interrupt Line Select     */
  volatile vuint32 ILE;             /*! 0x005C         Interrupt Line Enable     */
           vuint32 res3[8];         /*! 0x0060-0x007C  Reserved */
  volatile vuint32 GFC;             /*! 0x0080(RP)     Global Filter Configuration        */
  volatile vuint32 SIDFC;           /*! 0x0084(RP)     Standard ID Filter Configuration   */
  volatile vuint32 XIDFC;           /*! 0x0088(RP)     Extended ID Filter Configuration   */
           vuint32 res4;            /*! 0x008C         Reserved */
  volatile vuint32 XIDAM;           /*! 0x0090(RP)     Extended ID AND Mask               */
  volatile vuint32 HPMS;            /*! 0x0094         High Priority Message Status       */
  volatile vuint32 NDATA[2];        /*! 0x0098         NDAT1-New Data 1 Register          */
                                    /*! 0x009C         NDAT2-New Data 2 Register          */
  volatile t_30_McanRXFnC  RXF0C;           /*! 0x00A0(RP)     Rx FIFO 0 Configuration            */
  volatile t_30_McanRXFnS  RXF0S;           /*! 0x00A4         Rx FIFO 0 Status                   */
  volatile vuint32 RXF0A;           /*! 0x00A8         Rx FIFO 0 Acknowledge              */
  volatile vuint32 RXBC;            /*! 0x00AC         Rx Buffer Configuration Register */
  volatile t_30_McanRXFnC  RXF1C;           /*! 0x00B0(RP)     Rx FIFO 1 Configuration            */
  volatile t_30_McanRXFnS  RXF1S;           /*! 0x00B4         Rx FIFO 1 Status                   */
  volatile vuint32 RXF1A;           /*! 0x00B8         Rx FIFO 1 Acknowledge              */
  volatile t_30_McanRXESC  RXESC;           /*! 0x00BC         Rx element size configuration      */
  volatile vuint32 TXBC;            /*! 0x00C0(RP)     Tx Buffer Configuration            */
  volatile t_30_McanTXFQS TXFQS;     /*! 0x00C4         Tx FIFO/Queue Status               */
  volatile vuint32 TXESC;           /*! 0x00C8         Tx element size configuration      */
  volatile vuint32 TXBRP;           /*! 0x00CC         Tx Buffer Request Pending          */
  volatile vuint32 TXBAR;           /*! 0x00D0         Tx Buffer Add Request              */
  volatile vuint32 TXBCR;           /*! 0x00D4         Tx Buffer Cancellation             */
  volatile vuint32 TXBTO;           /*! 0x00D8         Tx Buffer Transmission Occurred    */
  volatile vuint32 TXBCF;           /*! 0x00DC         Tx Buffer Cancellation Finished    */
  volatile vuint32 TXBTIE;          /*! 0x00E0         Tx Buffer Transmission Interrupt Enable */
  volatile vuint32 TXBCIE;          /*! 0x00E4         Tx Buffer Cancellation Finished Interrupt Enable */
           vuint32 res9[2];         /*! 0x00E8-0x00EC  Reserved */
  volatile vuint32 TXEFC;           /*! 0x00F0(RP)     Tx Event FIFO Configuration        */
  volatile t_30_McanTXEFS  TXEFS;           /*! 0x00F4         Tx Event FIFO Status               */
  volatile vuint32 TXEFA;           /*! 0x00F8         Tx Event FIFO Acknowledge          */
           vuint32 resA;            /*! 0x00FC         Reserved */
  volatile vuint32 TTTMC;           /*! 0x100          Trigger Memory Configuration, start of NOT SUPPORTED TTCAN registers */
  volatile vuint32 TTRMC;           /*! 0x104          Reference Message Configuration    */
  volatile vuint32 TTOCF;           /*! 0x108          Operation Configuration Register   */
}tCan_30_McanObjType;

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANSS ) /* COV_CAN_HW_SPECIFIC */

typedef volatile struct tCan_30_McanMCanSsGlobalRegObjTypeTag
{
  volatile vuint32 MCANSS_PID;                          /*!                Revision Register */
  volatile vuint32 MCANSS_CTRL;                         /*!                Control Register */
  volatile vuint32 MCANSS_STAT;                         /*!                Status Register */
  volatile vuint32 MCANSS_ICS;                          /*!                Interrupt Clear Shadow Register */
  volatile vuint32 MCANSS_IRS;                          /*!                Interrupt Raw Status Register */
  volatile vuint32 MCANSS_IECS;                         /*!                Interrupt Enable Clear Shadow Register */
  volatile vuint32 MCANSS_IE;                           /*!                Interrupt Enable Register */
  volatile vuint32 MCANSS_IES;                          /*!                Interrupt Enable Status Register */
  volatile vuint32 MCANSS_EOI;                          /*!                End Of Interrupt Register */
  volatile vuint32 MCANSS_EXT_TS_PRESCALER;             /*!                External Timestamp PreScaler Register */
  volatile vuint32 MCANSS_EXT_TS_UNSERVICED_INTR_CNTR;  /*!                External Timestamp Unserviced Interrupts Register */

# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_EOI) /* COV_CAN_HW_SPECIFIC */
  volatile vuint32 unused1[21];                                 /*!                Reserved */
  volatile vuint32 MCANSS_ECC_EOI;                      /*!                End Of Interrupt for ECC Interrupt Register */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_EOI */

}tCan_30_McanMCanSsGlobalRegObjType;

typedef volatile struct t_30_McanMCanSsCanEccRegObjTypeTag
{
  volatile vuint32 MCANSS_ECC_AGGR_REVISION;                          /*!                Aggregator Revision Register */
  volatile vuint32 unused1[1];                                                                 /*!                Reserved */
  volatile vuint32 MCANSS_ECC_VECTOR;                                           /*!                ECC Vector Register */
  volatile vuint32 MCANSS_ECC_MISC_STATUS;                                 /*!                Misc Status Register */
  volatile vuint32 unused2[11];                                                                /*!                Reserved */
  volatile vuint32 MCANSS_ECC_SEC_EOI_REG;                                 /*!                End Of Interrupt Register */
  volatile vuint32 MCANSS_ECC_SEC_STATUS_REG0;                      /*!                       Interrupt Status0 Register */
  volatile vuint32 unused3[15];                                                               /*!                Reserved */
  volatile vuint32 MCANSS_ECC_SEC_ENABLE_SET_REG0;            /*!                Interrupt Enable Set0 Register */
  volatile vuint32 unused4[15];                                                               /*!                Reserved */
  volatile vuint32 MCANSS_ECC_SEC_ENABLE_CLR_REG0;           /*!                Interrupt Enable Clear0 Register */
  volatile vuint32 unused5[30];                                                              /*!                Reserved */
  volatile vuint32 MCANSS_ECC_DED_EOI_REG;                              /*!                End Of Interrupt Register */
  volatile vuint32 MCANSS_ECC_DED_STATUS_REG0;                  /*!                Interrupt Status0 Register */
  volatile vuint32 unused6[15];                                                             /*!                Reserved */
  volatile vuint32 MCANSS_ECC_DED_ENABLE_SET_REG0;        /*!                Interrupt Enable Set0 Register */
  volatile vuint32 unused7[15];                                                           /*!                Reserved */
  volatile vuint32 MCANSS_ECC_DED_ENABLE_CLR_REG0;       /*!                Interrupt Enable Clear0 Register */

# if defined (C_30_MCAN_ENABLE_MCANSS_ECC_AGGR)    /* COV_CAN_HW_SPECIFIC */
  volatile vuint32 unused8[15];                                                         /*!                Reserved */
  volatile vuint32 MCANSS_ECC_AGGR_ENABLE_SET;             /*!                Aggregator Interrupt Enable Set Register */
  volatile vuint32 MCANSS_ECC_AGGR_ENABLE_CLR;            /*!                Aggregator Interrupt Enable Clear Register */
  volatile vuint32 MCANSS_ECC_AGGR_STATUS_SET;             /*!                Aggregator Interrupt Status Set Register */
  volatile vuint32 MCANSS_ECC_AGGR_STATUS_CLR;            /*!                Aggregator Interrupt Status Clear Register */
# endif /* C_30_MCAN_ENABLE_MCANSS_ECC_AGGR */

}tCan_30_McanMCanSsCanEccRegObjType;

#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_SICANFD ) /* COV_CAN_HW_SPECIFIC */
typedef volatile struct tCan_30_McanSICanFDCanGlobalObjTypeTag
{ /*! Visconti5 Safe Island CANFD global register structure */
  volatile vuint32 SICANFD_AL_SET_DCLS;                 /*!                DCLS Fault Injection Configuration Register */
  volatile vuint32 SICANFD_AL_SET_ECC;                  /*!                ECC Fault Injection Setting Register */
  volatile vuint32 SICANFD_AL_CLR;                      /*!                Fault Flag Clear Register */
  volatile vuint32 SICANFD_AL_KEYCD;                    /*!                Fault Injection Setting Key Code Setting Register */
  volatile vuint32 SICANFD_AL_KEYST;                    /*!                Fault Injection Setting Key Status Register */
  volatile vuint32 SICANFD_FI_DATA_D;                   /*!                ECC Fault Injection Position Setting Register(data) */
  volatile vuint32 SICANFD_FI_DATA_E;                   /*!                ECC Fault Injection Position Setting Register(ECC) */
  volatile vuint32 SICANFD_FLG_ALARM;                   /*!                Alarm Detection Flag Register */
  volatile vuint32 SICANFD_DEDADR;                      /*!                DED Address Register */
  volatile vuint32 SICANFD_SECADR;                      /*!                SEC Address Register */
}tCan_30_McanSICanFDCanGlobalObjType;
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_MCANAS1 ) /* COV_CAN_HW_SPECIFIC */
typedef volatile struct tCan_30_McanMcanAs1GlobalObjTypeTag
{ /*! Panasonic Global Functional Safety and ECC Function register structure */
  volatile vuint32 MCANAS1_PROTECT_KEY;                 /*!                Write Control key for functional safety register */
  volatile vuint32 unused2[51];                         /*!                Reserved */
  volatile vuint32 MCANAS1_ECCCTRL;                             /*!                ECC function setting register */
  volatile vuint32 MCANAS1_ECCST;                               /*!                ECC error detection flag register */
  volatile vuint32 MCANAS1_ECCRAM_DBGSEL;                       /*!                ECCRAM debug area selection register */
  volatile vuint32 MCANAS1_ECCRAM_DBG;                          /*!                ECCRAM debug register */
} tCan_30_McanMcanAs1GlobalObjType;
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TTCANFD ) /* COV_CAN_HW_SPECIFIC */
typedef volatile struct tCan_30_McanTTCanFDCanGlobalObjTypeTag        /* Channel Model */
{
  volatile vuint32 TTCANFD_CAN_CH_RXFTOP_CTL;           /*!                Receive FIFO Top control*/
  volatile vuint32 unused2[7];                  /*!                Reserved */
  volatile vuint32 TTCANFD_CAN_CH_RXFTOP0_STAT;         /*!                Receive FIFO 0 Top Status*/
  volatile vuint32 unused3[1];                  /*!                Reserved*/
  volatile vuint32 TTCANFD_CAN_CH_RXFTOP0_DATA;         /*!                Receive FIFO 0 Top Data*/
  volatile vuint32 unused4[1];                  /*!                Reserved*/
  volatile vuint32 TTCANFD_CAN_CH_RXFTOP1_STAT;         /*!                Receive FIFO 1 Top Status*/
  volatile vuint32 unused5[1];                  /*!                Reserved*/
  volatile vuint32 TTCANFD_CAN_CH_RXFTOP1_DATA;         /*!                Receive FIFO 1 Top Data*/
}tCan_30_McanTTCanFDCanGlobalObjType;

typedef volatile struct tCan_30_McanTTCanFDSubSystemCanGlobalObjTypeTag    /* Group Model */
{
  volatile vuint32 TTCANFD_CAN_CTL;              /*!         Global CAN control register*/
  volatile vuint32 TTCANFD_CAN_STATUS;           /*!         Global CAN status register*/
  volatile vuint32 TTCANFD_CAN_DESIGN_CFG;       /*!         Design time configuration*/
  volatile vuint32 unused4[1];                   /*!         Reserved*/
  volatile vuint32 TTCANFD_CAN_INTR0_CAUSE;      /*!         Consolidated interrupt 0 cause register*/
  volatile vuint32 TTCANFD_CAN_INTR1_CAUSE;      /*!         Consolidated interrupt 1 cause register*/
  volatile vuint32 unused5[2];                   /*!         Reserved*/
  volatile vuint32 TTCANFD_CAN_TS_CTL;           /*!         Time Stamp control register*/
  volatile vuint32 TTCANFD_CAN_TS_CNT;           /*!         Time Stamp counter value*/
  volatile vuint32 unused6[22];                  /*!         Reserved*/
  volatile vuint32 TTCANFD_CAN_ECC_CTL;          /*!         ECC control*/
  volatile vuint32 TTCANFD_CAN_ECC_ERR_INJ;      /*!         ECC error injection*/
}tCan_30_McanTTCanFDSubSystemCanGlobalObjType;
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_STMFDCAN ) /* COV_CAN_HW_SPECIFIC */
typedef volatile struct tCan_30_McanStmFdCanGlobalObjTypeTag
{
  volatile vuint32 STMFDCAN_CCU_CREL;              /*!          Clock calibration unit core release register*/
  volatile vuint32 STMFDCAN_CCU_CCFG;              /*!          Calibration configuration register */
  volatile vuint32 STMFDCAN_CCU_CSTAT;             /*!          Calibration status register*/
  volatile vuint16 STMFDCAN_CCU_CWD;               /*!          Calibration watchdog register*/
  volatile vuint16 unused1;                        /*!          Calibration watchdog register ReadOnly bits*/
  volatile vuint32 STMFDCAN_CCU_IR;                /*!          Clock calibration unit interrupt register*/
  volatile vuint32 STMFDCAN_CCU_IE;                /*!          Clock calibration unit interrupt enable register*/
} tCan_30_McanStmFdCanGlobalObjType;
#endif

#if defined( C_30_MCAN_ENABLE_REGEXT_TCC ) /* COV_CAN_HW_SPECIFIC */
typedef volatile struct tCan_30_McanTCC80XXCfgGlobalObjTypeTag
{
  volatile vuint32 CFG0_MRAM_ADDR;              /*!      CFG0 register should be 0 */
  volatile vuint32 CFG1_MRAM_ADDR;              /*!      CFG1 register describes high 16 bits of CAN channel 0 Message RAM address */
  volatile vuint32 CFG2_MRAM_ADDR;              /*!      CFG2 register describes high 16 bits of CAN channel 1 Message RAM address */
  volatile vuint32 CFG3_MRAM_ADDR;              /*!      CFG2 register describes high 16 bits of CAN channel 2 Message RAM address */
#if defined( C_30_MCAN_ENABLE_REGEXT_TCC_PWD )
  volatile vuint32 unused[4];                   /*!      Reserved */
  volatile vuint32 CAN_CFG_WR_PW;               /*!      CAN Configuration Write Password Register */
  volatile vuint32 CAN_CFG_WR_LOCK;             /*!      CAN Configuration Write Lock Register */
#endif
} tCan_30_McanTCC80XXCfgGlobalObjType;
#endif

/* Internal Flags */

/* \trace SPEC-1400 */
/***************************************************************************/
/* function prototypes / API                                               */
/***************************************************************************/
#define CAN_30_MCAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/************************************************************************************************************
 *  Can_30_Mcan_InitMemory()
 ***********************************************************************************************************/
/*! \brief         Power-up memory initialization
 *  \details       Initializes component variables in *_INIT_* sections at power up. \n
 *                 Use this to re-run the system without performing a new start from power on. \n
 *                 (E.g.: used to support an ongoing debug session without a complete re-initialization.) \n
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Use this function in case these variables are not initialized by the 
 *                 start up code. \n
 *                 Must be followed by a call to "Can_30_Mcan_Init()".
 *  \trace         CREQ-970
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_InitMemory( void );

/************************************************************************************************************
 *  Can_30_Mcan_Init()
 ***********************************************************************************************************/
/*! \brief         Initializes component
 *  \details       Initializes all component variables and sets the component state to initialized.
 *  \param[in]     ConfigPtr          Component configuration structure
 *  \pre           Interrupts are disabled.
 *  \pre           Module is uninitialized.
 *  \pre           Can_30_Mcan_InitMemory() has been called unless CAN Module is initialized by start up code.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Parameter "ConfigPtr" will be taken into account only for "Multiple ECU Configuration" and in Post-Build variant. \n
 *  \trace         CREQ-969
************************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_Init( Can_30_Mcan_ConfigPtrType ConfigPtr );

#if ((CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_30_MCAN_SET_BAUDRATE_API == STD_OFF))
/************************************************************************************************************
 *  Can_30_Mcan_ChangeBaudrate()
 ***********************************************************************************************************/
/*! \brief         Change baud rate
 *  \details       This service shall change the baud rate and reinitialize the CAN controller.
 *  \param[in]     Controller    CAN controller to be changed
 *  \param[in]     Baudrate      Baud rate to be set
 *  \return        E_NOT_OK      Baud rate is not set
 *  \return        E_OK          Baud rate is set
 *  \pre           The CAN controller must be in "STOP Mode".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        (CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_30_MCAN_SET_BAUDRATE_API == STD_OFF)
 *  \notes         Has to be called during the start up sequence before CAN communication takes place but after calling "Can_30_Mcan_Init()".
 *  \trace         CREQ-995
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_ChangeBaudrate( uint8 Controller, V_DEF_30_MCAN_CONST(V_NONE, uint16, APPL_CONST) Baudrate );
#endif

#if (CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON)
/************************************************************************************************************
 *  Can_30_Mcan_CheckBaudrate()
 ***********************************************************************************************************/
/*! \brief         Checks baud rate
 *  \details       This service shall check if the given baud rate is supported of the CAN controller.
 *  \param[in]     Controller    CAN controller to be checked
 *  \param[in]     Baudrate      Baud rate to be checked
 *  \return        E_NOT_OK      Baud rate is not available
 *  \return        E_OK          Baud rate is available
 *  \pre           The CAN controller must be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_CHANGE_BAUDRATE_API == STD_ON
 *  \trace         CREQ-995
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_CheckBaudrate( uint8 Controller, V_DEF_30_MCAN_CONST(V_NONE, uint16, APPL_CONST) Baudrate );
#endif

#if (CAN_30_MCAN_SET_BAUDRATE_API == STD_ON)
/************************************************************************************************************
 *  Can_30_Mcan_SetBaudrate()
 ***********************************************************************************************************/
/*! \brief         Set baud rate
 *  \details       This service shall change the baud rate and reinitialize the CAN controller. \n
 *                 (Similar to Can_30_Mcan_ChangeBaudrate() but used when identical baud rates are used for different CAN FD settings).
 *  \param[in]     Controller        CAN controller to be set
 *  \param[in]     BaudRateConfigID  Identity of the configured baud rate (available as Symbolic Name)
 *  \return        E_NOT_OK      Baud rate is not set
 *  \return        E_OK          Baud rate is set
 *  \pre           The CAN controller must be in "STOP Mode".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_SET_BAUDRATE_API == STD_ON
 *  \trace         CREQ-995
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
#endif


#if (CAN_30_MCAN_VERSION_INFO_API == STD_ON) /* BR:007 */
/************************************************************************************************************
 *  Can_30_Mcan_GetVersionInfo()
 ***********************************************************************************************************/
/*! \brief         Returns the version information
 *  \details       Returns version information (MICROSAR3: BCD coded), vendor ID and AUTOSAR module ID.
 *  \param[out]    VersionInfo    Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_VERSION_INFO_API == STD_ON
 *  \trace         CREQ-991
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_GetVersionInfo( Can_30_Mcan_VersionInfoPtrType VersionInfo );
#endif

#if (CAN_30_MCAN_GET_STATUS == STD_ON)
/************************************************************************************************************
 *  Can_30_Mcan_GetStatus()
 ***********************************************************************************************************/
/*! \brief         Get status/mode of the given controller
 *  \details       Delivers the status of the hardware, as a bit coded value where multiple bits may be set.
 *  \param[in]     Controller   CAN controller requested for status information
 *  \return        CAN_30_MCAN_STATUS_START            START mode
 *  \return        CAN_30_MCAN_STATUS_STOP             STOP mode
 *  \return        CAN_30_MCAN_STATUS_INIT             Initialized controller
 *  \return        CAN_30_MCAN_STATUS_INCONSISTENT     STOP or SLEEP are inconsistent over common CAN controllers
 *  \return        CAN_30_MCAN_DEACTIVATE_CONTROLLER   RAM check failed CAN controller is deactivated
 *  \return        CAN_30_MCAN_STATUS_WARNING          WARNING state
 *  \return        CAN_30_MCAN_STATUS_PASSIVE          PASSIVE state
 *  \return        CAN_30_MCAN_STATUS_BUSOFF           BUSOFF mode
 *  \return        CAN_30_MCAN_STATUS_SLEEP            SLEEP mode
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GET_STATUS == STD_ON
 *  \notes         the return value can be analysed using the provided API macros: \n
                   CAN_30_MCAN_HW_IS_OK(), CAN_30_MCAN_HW_IS_WARNING(), CAN_30_MCAN_HW_IS_PASSIVE() \n
                   CAN_30_MCAN_HW_IS_BUSOFF(), CAN_30_MCAN_HW_IS_WAKEUP(), CAN_30_MCAN_HW_IS_SLEEP()\n
                   CAN_30_MCAN_HW_IS_STOP(), CAN_30_MCAN_HW_IS_START(), CAN_30_MCAN_HW_IS_INCONSISTENT()\n
                   None AUTOSAR API
 *  \trace         CREQ-978
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, uint8, CODE) Can_30_Mcan_GetStatus( uint8 Controller );

/************************************************************************************************************
 *  Can_30_Mcan_GetControllerMode()
 ***********************************************************************************************************/
/*! \brief         Get mode of the given controller
 *  \details       Delivers the controllers mode.
 *  \param[in]     Controller         CAN controller requested for status information
 *  \param[out]    ControllerModePtr  pointer to variable to store CAN controllers mode. Parameter must not be NULL.
 *  \return        E_NOT_OK           Controller mode request has not been accepted
 *  \return        E_OK               Controller mode request has been accepted
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GET_STATUS == STD_ON
 *  \trace         CREQ-178460
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerMode( uint8 Controller, Can_30_Mcan_ControllerStatePtrType ControllerModePtr );

/************************************************************************************************************
 *  Can_30_Mcan_GetControllerErrorState()
 ***********************************************************************************************************/
/*! \brief         Get status of the given controller
 *  \details       Delivers the controllers error state.
 *  \param[in]     Controller         CAN controller requested for status information
 *  \param[out]    ErrorStatePtr      pointer to variable to store AN controllers error state. Parameter must not be NULL.
 *  \return        E_NOT_OK           Controller state request has not been accepted
 *  \return        E_OK               Controller state request has been accepted
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GET_STATUS == STD_ON
 *  \trace         CREQ-178459
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerErrorState( uint8 Controller, Can_30_Mcan_ErrorStatePtrType ErrorStatePtr );

/************************************************************************************************************
 *  Can_30_Mcan_GetControllerTxErrorCounter()
 ***********************************************************************************************************/
/*! \brief         Get status of the given controller
 *  \details       Delivers the controllers TX error counter.
 *  \param[in]     Controller         CAN controller requested for TX error counter.
 *  \param[out]    TxErrorCounterPtr  pointer to variable to store CAN controllers TX error counter. Parameter must not be NULL.
 *  \return        E_NOT_OK           Controller TX error counter not available
 *  \return        E_OK               Controller TX error counter available
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GET_STATUS == STD_ON
 *  \trace         CREQ-178459
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerTxErrorCounter( uint8 Controller, Can_30_Mcan_ErrorCounterPtrType TxErrorCounterPtr );

/************************************************************************************************************
 *  Can_30_Mcan_GetControllerRxErrorCounter()
 ***********************************************************************************************************/
/*! \brief         Get status of the given controller
 *  \details       Delivers the controllers RX error counter.
 *  \param[in]     Controller         CAN controller requested for RX error counter.
 *  \param[out]    RxErrorCounterPtr  pointer to variable to store CAN controllers RX error counter. Parameter must not be NULL.
 *  \return        E_NOT_OK           Controller RX error counter not available
 *  \return        E_OK               Controller RX error counter available
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GET_STATUS == STD_ON
 *  \trace         CREQ-178459
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_GetControllerRxErrorCounter( uint8 Controller, Can_30_Mcan_ErrorCounterPtrType RxErrorCounterPtr );

#endif

/************************************************************************************************************
 *  Can_30_Mcan_SetControllerMode()
 ***********************************************************************************************************/
/*! \brief         Change the controller mode
 *  \details       Request a mode transition that will be processed a short time synchronous, \n
 *                 (may be finished ansynconous in Can_30_Mcan_MainFunction_Mode()) and call a notification when successful. \n
 *                 BUSOFF, WAKEUP and RAM check will be handled as well.
 *  \param[in]     Controller    CAN controller to be set
 *  \param[in]     Transition    Requested transition to destination mode CAN_T_START, CAN_T_STOP, CAN_T_SLEEP, CAN_T_WAKEUP
 *  \return        CAN_NOT_OK    transition request rejected
 *  \return        CAN_OK        transition request accepted
 *  \pre           Interrupts locked
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \notes         Must not be called within CAN driver context like RX, TX or BUSOFF call out.
 *  \trace         CREQ-978
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );

/************************************************************************************************************
 *  Can_30_Mcan_Write()
 ***********************************************************************************************************/
/*! \brief         Send a CAN message
 *  \details       copy data, DLC and ID to the send mailbox and request a transmission.
 *  \param[in]     Hth           Handle of the mailbox intended to send the message
 *  \param[in]     PduInfo       Information about the outgoing message (ID, dataLength, data)
 *  \return        CAN_NOT_OK    transmit request rejected
 *  \return        CAN_OK        transmit request successful
 *  \return        CAN_BUSY      transmit request could not be accomplished due to the controller is busy.
 *  \pre           disabled CAN interrupts / interrupts locked (Refer to critical section).
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \trace         CREQ-971
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_Write( Can_HwHandleType Hth, Can_30_Mcan_PduInfoPtrType PduInfo );

/************************************************************************************************************
 *  Can_30_Mcan_CancelTx()
 ***********************************************************************************************************/
/*! \brief         Cancel TX message
 *  \details       Cancel the TX message in the hardware buffer (if possible) or mark the message as not to be confirmed \n
 *                 in case of the cancellation is unsuccessful.
 *  \param[in]     Hth     Handle of the mailbox intended to be cancelled.
 *  \param[in]     PduId   PDU identifier
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Do not call this API within TX confirmation context. Otherwise confirmation will occur for already
 *                 cancelled messages. Only one message will be cancelled, if there are multiple requests also multiple cancellations expected.\n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_CancelTx( Can_HwHandleType Hth, PduIdType PduId );

#if defined(C_30_MCAN_ENABLE_MIRROR_MODE)
/************************************************************************************************************
 *  Can_30_Mcan_SetMirrorMode()
 ***********************************************************************************************************/
/*! \brief         Activate mirror mode 
 *  \details       Switch the Appl_GenericPreCopy/Confirmation function ON or OFF.
 *  \param[in]     Controller   CAN controller
 *  \param[in]     mirrorMode   Activate or deactivate the mirror mode.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        C_30_MCAN_ENABLE_MIRROR_MODE (user configuration file)
 *  \notes         Called by "Mirror Mode" CDD.\n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_SetMirrorMode( uint8 Controller, CddMirror_MirrorModeType mirrorMode );
#endif

#if defined(C_30_MCAN_ENABLE_SILENT_MODE)
/************************************************************************************************************
 *  Can_30_Mcan_SetSilentMode()
 ***********************************************************************************************************/
/*! \brief         Activate and deactivate the silent mode
 *  \details       Switch to silent mode, as a listen only mode without ACK. Also deactivate this mode again.
 *  \param[in]     Controller   CAN controller
 *  \param[in]     silentMode   Activate or deactivate the silent mode CAN_SILENT_INACTIVE, CAN_SILENT_ACTIVE (Enumaration).
 *  \return        E_OK         mode change successful
 *  \return        E_NOT_OK     mode change failed
 *  \pre           The CAN controller must be in "STOP Mode".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_SILENT_MODE == STD_ON
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_SetSilentMode( uint8 Controller, Can_30_Mcan_SilentModeType silentMode );
#endif

/************************************************************************************************************
 *  Can_30_Mcan_CheckWakeup()
 ***********************************************************************************************************/
/*! \brief         Check WAKEUP occur
 *  \details       Check the occurrence of WAKEUP events for the given controller \n
 *                 (used as WAKEUP callback for higher layers).
 *  \param[in]     Controller           CAN controller to be checked for WAKEUP events.
 *  \return        E_OK/CAN_OK          the given controller caused a WAKEUP before.
 *  \return        E_NOT_OK/CAN_NOT_OK  the given controller caused no WAKEUP before.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-983
 *  \config        return type depend on CAN_30_MCAN_CHECK_WAKEUP_CAN_RET_TYPE
************************************************************************************************************/
#if defined(C_30_MCAN_ENABLE_CHECK_WAKEUP_CAN_RET_TYPE) /* COV_CAN_COMPATIBILITY */
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, CODE) Can_30_Mcan_CheckWakeup( uint8 Controller );
#else
V_DEF_30_MCAN_FUNC(V_NONE, Std_ReturnType, CODE) Can_30_Mcan_CheckWakeup( uint8 Controller );
#endif

/************************************************************************************************************
 *  Can_30_Mcan_DisableControllerInterrupts()
 ***********************************************************************************************************/
/*! \brief         Disable CAN interrupts
 *  \details       Disable the CAN interrupt for the given controller (e.g. due to data consistency reasons).
 *  \param[in]     Controller    CAN controller to disable interrupts for.
 *  \pre           Must not be called while CAN controller is in SLEEP mode.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Called within Critical Area handling or out of Application code.
 *  \trace         CREQ-988
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_DisableControllerInterrupts( uint8 Controller );

/************************************************************************************************************
 *  Can_30_Mcan_EnableControllerInterrupts()
 ***********************************************************************************************************/
/*! \brief         Enable CAN interrupts
 *  \details       Re-enable the CAN interrupt for the given controller (e.g. due to data consistency reasons).
 *  \param[in]     Controller    CAN controller to enable interrupts for.
 *  \pre           Must not be called while CAN controller is in SLEEP mode.
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Called within Critical Area handling or out of Application code.
 *  \trace         CREQ-988
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_EnableControllerInterrupts( uint8 Controller );

/* polling functions (always available for non polled systems also) */
/************************************************************************************************************
 *  Can_30_Mcan_MainFunction_Write()
 ***********************************************************************************************************/
/*! \brief         TX message observation
 *  \details       Polling TX events (confirmation, cancellation) for all controllers and all TX mailboxes \n
 *                 to accomplish the TX confirmation handling (like CanInterface notification).
 *  \pre           Must not interrupt the call of Can_30_Mcan_Write(). CAN driver has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Empty function in case no polling is active.
 *  \trace         CREQ-979
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, CODE) Can_30_Mcan_MainFunction_Write( void ); /* PRQA S 3449, 3451 */ /* MD_Can_HL_ExternalDeclaration */

/************************************************************************************************************
 *  Can_30_Mcan_MainFunction_Read()
 ***********************************************************************************************************/
/*! \brief         RX message observation
 *  \details       Polling RX events for all controllers and all RX mailboxes to accomplish the \n
 *                 RX indication handling (like CanInterface notification). \n
 *                 Also used for a delayed read (from task level) of the RX Queue messages which were queued from interrupt context.
 *  \pre           CAN driver has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Empty function in case no polling is active.
 *  \trace         CREQ-979
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, CODE) Can_30_Mcan_MainFunction_Read( void ); /* PRQA S 3449, 3451 */ /* MD_Can_HL_ExternalDeclaration */

/************************************************************************************************************
 *  Can_30_Mcan_MainFunction_BusOff()
 ***********************************************************************************************************/
/*! \brief         BUSOFF observation
 *  \details       Polling of BUSOFF events to accomplish the BUSOFF handling.
 *                 Service function to poll BUSOFF events for all controllers to accomplish the BUSOFF handling \n
 *                 (like calling of CanIf_30_Mcan_ControllerBusOff() in case of BUSOFF occurrence).
 *  \pre           CAN driver has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Empty function in case no polling is active.
 *  \trace         CREQ-979
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, CODE) Can_30_Mcan_MainFunction_BusOff( void ); /* PRQA S 3449, 3451 */ /* MD_Can_HL_ExternalDeclaration */

/************************************************************************************************************
 *  Can_30_Mcan_MainFunction_Wakeup()
 ***********************************************************************************************************/
/*! \brief         WAKEUP observation
 *  \details       Polling WAKEUP events for all controllers to accomplish the WAKEUP handling \n
 *                 (like calling of "CanIf_30_Mcan_SetWakeupEvent()" in case of WAKEUP occurrence).
 *  \pre           CAN driver has to be initialized.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Empty function in case no polling is active.
 *  \trace         CREQ-983
 *  \trace         CREQ-979
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, CODE) Can_30_Mcan_MainFunction_Wakeup( void ); /* PRQA S 3449, 3451 */ /* MD_Can_HL_ExternalDeclaration */

/************************************************************************************************************
 *  Can_30_Mcan_MainFunction_Mode()
 ***********************************************************************************************************/
/*! \brief         Mode transition observation
 *  \details       Polling Mode changes over all controllers. \n
                   (This is handled asynchronous if not accomplished in "Can_30_Mcan_SetControllerMode()")
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \trace         CREQ-978
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, CODE) Can_30_Mcan_MainFunction_Mode( void ); /* PRQA S 3449, 3451 */ /* MD_Can_HL_ExternalDeclaration */

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED)
/************************************************************************************************************
 *  Can_30_Mcan_RamCheckExecute()
 ***********************************************************************************************************/
/*! \brief         Start checking the CAN cells RAM
 *  \details       Check all controller specific and mailbox specific registers by write patterns and read back.
 *                 Issue notification will appear in this context.
 *  \param[in]     Controller    CAN controller to be checked.
 *  \pre           Has to be called within STOP mode.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_RAM_CHECK == CAN_EXTENDED
 *  \trace         CREQ-106641
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckExecute( uint8 Controller );

/************************************************************************************************************
 *  Can_30_Mcan_RamCheckEnableMailbox()
 ***********************************************************************************************************/
/*! \brief         Reactivate a mailbox after RamCheck failed.
 *  \details       Mailbox will be reactivated by clear deactivation flag.
 *  \param[in]     htrh    CAN mailbox to be reactivated.
 *  \pre           Has to be called within STOP mode after RamCheck failed (controller is deactivated).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         must be followed by Can_30_Mcan_RamCheckEnableController() to activate mailbox and controller.
 *  \config        CAN_RAM_CHECK == CAN_EXTENDED
 *  \trace         CREQ-106641
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckEnableMailbox( Can_HwHandleType htrh );

/************************************************************************************************************
 *  Can_30_Mcan_RamCheckEnableController()
 ***********************************************************************************************************/
/*! \brief         Reactivate CAN cells after RamCheck failed.
 *  \details       CAN cell will be reactivated by execute reinitialization.
 *  \param[in]     Controller    CAN controller to be reactivated.
 *  \pre           Has to be called within STOP mode after RamCheck failed (controller is deactivated).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_RAM_CHECK == CAN_EXTENDED
 *  \trace         CREQ-106641
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_Mcan_RamCheckEnableController( uint8 Controller );
#endif

/* Platform specific API */


/* ISR prototypes (see can_irq.c) */

/* Possibility to disable the prototypes of interrupt service routines in the driver configuration header file.  */

/* Default switch C_30_MCAN_ENABLE_ISR_PROTOTYPE is located here due only this token is used in the specific ASR header file. */
#if ( (!defined( C_30_MCAN_ENABLE_ISR_PROTOTYPE )) && (!defined( C_30_MCAN_DISABLE_ISR_PROTOTYPE )) ) /* COV_CAN_ISR_PROTOTYPE */
# define C_30_MCAN_ENABLE_ISR_PROTOTYPE  /* default while not overwritten by user config */
#endif

#if defined( C_30_MCAN_ENABLE_TX_POLLING )          && \
    defined( C_30_MCAN_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_30_MCAN_ENABLE_RX_FULLCAN_POLLING )  && \
    defined( C_30_MCAN_ENABLE_ERROR_POLLING )       && \
    !defined( C_30_MCAN_ENABLE_INDIVIDUAL_POLLING )
# define C_30_MCAN_DISABLE_ISR_MANDATORY
#else
# define C_30_MCAN_ENABLE_ISR_MANDATORY
#endif

#if defined( CAN_30_MCAN_GEN_COM_STACK_LIB )  /* COV_CAN_COMPATIBILITY */
# if (CAN_30_MCAN_ISR_ALL_CHAN == STD_ON)      /* COV_CAN_HW_SPECIFIC */
#  define C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN
#  if defined(CAN_30_MCAN_IRQ_SOURCE) /* COV_CAN_INTERNAL */
#   if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
#    define Can_30_Mcan_GetCanBasisAdr(hwch)                           Can_30_Mcan_GetVirtualBasisAdrOfControllerData(hwch)
#   else
#    define Can_30_Mcan_GetCanBasisAdr(hwch)                           Can_30_Mcan_GetBasisAdrOfControllerConfig(hwch)  /* only required for this specific additional channel detection */
#   endif
#  endif
# else
#  define C_30_MCAN_DISABLE_CAN_ISR_ALL_CHAN
# endif
#endif /* CAN_30_MCAN_GEN_COM_STACK_LIB */

#if defined (C_30_MCAN_ENABLE_ISR_PROTOTYPE) /* COV_CAN_HW_SPECIFIC */
# if defined(C_30_MCAN_ENABLE_OSEK_OS)&&  defined(C_30_MCAN_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
/* ISR prototypes must be provided by OSEK header file */
# else   /* (C_30_MCAN_ENABLE_OSEK_OS) && (C_30_MCAN_ENABLE_OSEK_OS_INTCAT2) */
#  if defined( C_30_MCAN_ENABLE_ISR_MANDATORY ) /* ISR necessary; no pure polling configuration */
#   if defined( C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN ) /* COV_CAN_HW_SPECIFIC */
/************************************************************************************************************
 *  Can_30_McanIsr_MCAN
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on all CANs.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
/* MPC5777C with one interrupt vector for all CAN channels */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_MCAN( void );
#   else     /* C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN */
/************************************************************************************************************
 *  Can_30_McanIsr_0
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_0.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_0 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_0( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_1
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_1.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_1 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_1( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_2
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_2.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_2 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_2( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_3
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_3.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_3 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_3( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_4
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_4.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_4 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_4( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_5
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_5.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_5 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_5( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_6
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_6.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_6 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_6( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_7
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_7.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_7 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_7( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_8
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_8.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_8 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_8( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_9
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_9.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_9 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_9( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_10
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_10.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_10 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_10( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_11
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_11.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_11 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_11( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_12
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_12.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_12 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_12( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_13
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_13.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_13 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_13( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_14
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_14.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_14 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_14( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_15
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_15.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_15 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_15( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_16
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_16.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_16 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_16( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_17
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_17.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_17 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_17( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_18
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_18.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_18 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_18( void );
#    endif
/************************************************************************************************************
 *  Can_30_McanIsr_19
 ***********************************************************************************************************/
/*! \brief         Interrupt service function for MCAN interrupts on CAN_19.
 *  \details       Calls the interrupt handler.
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************/
#    if defined( kCan_30_McanPhysToLogChannelIndex_19 ) /* COV_CAN_EQUAL_CHANNEL_LAYOUT */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) Can_30_McanIsr_19( void );
#    endif
#   endif /* C_30_MCAN_ENABLE_CAN_ISR_ALL_CHAN */
#  endif /* C_30_MCAN_ENABLE_ISR_MANDATORY no pure polling configuration */
# endif /* C_30_MCAN_ENABLE_OSEK_OS && C_30_MCAN_ENABLE_OSEK_OS_INTCAT2 */
#endif /* C_30_MCAN_ENABLE_ISR_PROTOTYPE */

/************************************************************************************************************
 *  CanInterrupt_30_Mcan()
 ***********************************************************************************************************/
/*! \brief         Handles channel specific interrupts.
 *  \details       Calls the confirmation, indication, error handling and wakeup functions.
 *  \param[in]     canHwChannel        CAN channel (configuration dependent)
 *  \context       ISR1|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        Interrupt configurations.
 *  \pre           -
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) CanInterrupt_30_Mcan(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */

#define CAN_30_MCAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CAN_30_MCAN_START_SEC_CODE_APPL  /*----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (CAN_30_MCAN_GENERIC_PRECOPY == STD_ON)
/************************************************************************************************************
 *  Appl_30_Mcan_GenericPrecopy()
 ***********************************************************************************************************/
/*! \brief         Common RX indication callback that will be called before message specific callback will be called.
 *  \details       Application callback function which informs about all incoming RX messages including the contained data. \n
 *                 It can be used to block notification to upper layer. E.g. to filter incoming messages or route it for special handling.
 *  \param[in]     Controller   CAN controller which received the message.
 *  \param[in]     ID           ID of the received message (include IDE,FD). \n
 *                              In case of extended or mixed ID systems the highest bit (bit 31) is set to mark an extended ID. \n
 *                              FD-bit (bit 30) can be masked out with a define CAN_30_MCAN_ID_MASK_IN_GENERIC_CALLOUT in the user config file.
 *  \param[in]     DataLength   Data length of the received message.
 *  \param[in]     pData        Pointer to the data of the received message (read only).
 *  \return        CAN_OK       Higher layer indication will be called afterwards (CanIf_RxIndication()).
 *  \return        CAN_NOT_OK   Higher layer indication will not be called afterwards.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GENERIC_PRECOPY == STD_ON
 *  \notes         "pData" is read only and must not be accessed for further write operations. \n
 *                 The parameter DataLength refers to the received data length by the CAN controller hardware.\n
 *                 Note, that the CAN protocol allows the usage of data length values greater than eight (CAN-FD).\n
 *                 Depending on the implementation of this callback it may be necessary to consider this special case (e.g. if the data length is used as index value in a buffer write access).
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_30_Mcan_GenericPrecopy( uint8 Controller, Can_IdType ID, uint8 DataLength, Can_30_Mcan_DataPtrType DataPtr );
#endif

#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API1)
/************************************************************************************************************
 *  Appl_30_Mcan_GenericConfirmation()
 ***********************************************************************************************************/
/*! \brief         Common TX notification callback that will be called before message specific callback will be called.
 *  \details       Application callback function which informs about TX messages being sent to the CAN bus.
 *                 It can be used to block confirmation or route the information to other layer as well.
 *  \param[in]     PduId       Handle of the PDU specifying the message.
 *  \return        CAN_OK      Higher layer confirmation will be called afterwards (CanIf_TxConfirmation()).
 *  \return        CAN_NOT_OK  Higher layer confirmation will not be called afterwards.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GENERIC_CONFIRMATION == STD_ON
 *  \notes         "PduId" is read only and must not be accessed for further write operations. \n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_30_Mcan_GenericConfirmation( PduIdType PduId );
#endif

#if defined(CAN_30_MCAN_ENABLE_GENERIC_CONFIRMATION_API2)
/************************************************************************************************************
 *  Appl_30_Mcan_GenericConfirmation()
 ***********************************************************************************************************/
/*! \brief         Common TX notification callback that will be called before message specific callback will be called.
 *  \details       Application callback function which informs about TX messages being sent to the CAN bus.
 *                 It can be used to block confirmation or route the information to other layer as well.
 *  \param[in]     Controller  CAN controller which send the message.
 *  \param[in]     DataPtr     Pointer to a Can_PduType structure including ID (contain IDE,FD bit), DataLength, PDU and data pointer.
 *  \return        CAN_OK      Higher layer (CanInterface) confirmation will be called.
 *  \return        CAN_NOT_OK  No further higher layer (CanInterface) confirmation will be called.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GENERIC_CONFIRMATION == CAN_30_MCAN_API2
 *  \notes         A new transmission within this call out will corrupt the DataPtr context, if the CanHardwareObject is a FIFO object and the FIFO is full. \n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_30_Mcan_GenericConfirmation( uint8 Controller, Can_30_Mcan_PduInfoPtrType DataPtr );
#endif

#if defined(C_30_MCAN_ENABLE_PRETRANSMIT_FCT)
/************************************************************************************************************
 *  Appl_30_Mcan_GenericPreTransmit()
 ***********************************************************************************************************/
/*! \brief         Common transmit callback.
 *  \details       Application callback function allowing the modification of the data to be transmitted (e.g.: add CRC).
 *  \param[in]     Controller  CAN controller on which the message will be send.
 *  \param[in]     DataPtr     Pointer to a Can_PduType structure including ID (contain IDE,FD bit), DataLength, PDU and data pointer.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_GENERIC_PRETRANSMIT == STD_ON
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_Mcan_GenericPreTransmit( uint8 Controller, Can_30_Mcan_PduInfoPtrType_var DataPtr );
#endif

# if (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON)
/************************************************************************************************************
 *  Appl_30_McanCanTimerStart()
 ***********************************************************************************************************/
/*! \brief         Start time out monitoring
 *  \details       Service function to start an observation timer.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON) && (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON)
 *  \notes         Please refer to chapter "Hardware Loop Check". \n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, APPL_CODE) Appl_30_McanCanTimerStart( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 source );

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
 *  \config        (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON) && (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON)
 *  \notes         Please refer to chapter "Hardware Loop Check". \n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, Can_ReturnType, APPL_CODE) Appl_30_McanCanTimerLoop( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 source );

/************************************************************************************************************
 *  Appl_30_McanCanTimerEnd()
 ***********************************************************************************************************/
/*! \brief         Stop time out monitoring
 *  \details       Service function to to end an observation timer.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON) && (CAN_30_MCAN_HW_LOOP_SUPPORT_API == STD_ON)
 *  \notes         Please refer to chapter "Hardware Loop Check". \n
 *                 None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, APPL_CODE) Appl_30_McanCanTimerEnd( CAN_30_MCAN_CHANNEL_CANTYPE_FIRST uint8 source );
# endif

#if (CAN_30_MCAN_INTLOCK != CAN_30_MCAN_DRIVER)
/************************************************************************************************************
 *  Appl_30_McanCanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         CAN interrupt disabling by application
 *  \details       Disabling of CAN Interrupts by the application. \n
 *                 E.g.: the CAN driver itself should not access the common Interrupt Controller due to application \n
 *                 specific restrictions (like security level). Or the application like to be informed because of \n
 *                 an CAN interrupt lock. called by Can_30_Mcan_DisableControllerInterrupts().
 *  \param[in]     Controller   CAN controller for the CAN interrupt lock.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_INTLOCK == CAN_30_MCAN_APPL || CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_McanCanInterruptDisable( uint8 Controller );

/************************************************************************************************************
 *  Appl_30_McanCanInterruptRestore()
 ***********************************************************************************************************/
/*! \brief         CAN interrupt restore by application
 *  \details       Re-enabling of CAN Interrupts by the application. \n
                   E.g.: the CAN driver itself should not access the common Interrupt Controller due to application \n
                   specific restrictions (like security level). Or the application like to be informed because of \n
                   an CAN interrupt lock. called by Can_30_Mcan_EnableControllerInterrupts().
 *  \param[in]     Controller   CAN controller for the CAN interrupt unlock.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_INTLOCK == CAN_30_MCAN_APPL || CAN_30_MCAN_INTLOCK == CAN_30_MCAN_BOTH
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_McanCanInterruptRestore( uint8 Controller );
#endif

#if (CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_APPL)
/************************************************************************************************************
 *  Appl_30_Mcan_CanOverrun()
 ***********************************************************************************************************/
/*! \brief         Overrun detection
 *  \details       Called when an overrun is detected for a BasicCAN mailbox. \n
 *                 Alternatively a DET call can be selected instead of ("CanOverrunNotification" is set to "DET").
 *  \param[in]     Controller   CAN controller for which the overrun was detected.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_APPL
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_Mcan_CanOverrun ( uint8 Controller );

/************************************************************************************************************
 *  Appl_30_Mcan_CanFullCanOverrun()
 ***********************************************************************************************************/
/*! \brief         Overrun detection
 *  \details       Called when an overrun is detected for a FullCAN mailbox. \n
 *                 Alternatively a DET call can be selected instead of ("CanOverrunNotification" is set to "DET").
 *  \param[in]     Controller   CAN controller for which the overrun was detected.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_OVERRUN_NOTIFICATION == CAN_30_MCAN_APPL
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_Mcan_CanFullCanOverrun ( uint8 Controller );
#endif

#if defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK)
# if !defined(C_30_MCAN_ENABLE_CAN_RAM_CHECK_EXTENDED) /* standard RAM_CHECK */
#  if defined(C_30_MCAN_ENABLE_NOTIFY_CORRUPT_MAILBOX)
/************************************************************************************************************
 *  Appl_30_Mcan_CanCorruptMailbox()
 ***********************************************************************************************************/
/*! \brief         Mailbox notification in case of RAM check failure.
 *  \details       Will notify the application (during re-initialization) about a defect mailbox within the CAN cell.
 *  \param[in]     Controller   CAN controller for which the check failed.
 *  \param[in]     hwObjHandle  Hardware handle of the defect mailbox.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_RAM_CHECK == CAN_30_MCAN_NOTIFY_MAILBOX
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, void, APPL_CODE) Appl_30_Mcan_CanCorruptMailbox(uint8 Controller, Can_HwHandleType hwObjHandle);
#  endif

/************************************************************************************************************
 *  Appl_30_Mcan_CanRamCheckFailed()
 ***********************************************************************************************************/
/*! \brief         CAN controller notification in case of RAM check failure
 *  \details       will notify the application (during re-initialization) about a defect CAN controller \n
 *                 due to a previous failed mailbox check. The return value decide how to proceed with the initialization.
 *  \param[in]     Controller   CAN controller for which the check failed.
 *  \return        CAN_30_MCAN_DEACTIVATE_CONTROLLER   deactivate the controller
 *  \return        CAN_30_MCAN_ACTIVATE_CONTROLLER     activate the controller
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        CAN_30_MCAN_RAM_CHECK == CAN_30_MCAN_NOTIFY_MAILBOX / CAN_30_MCAN_NOTIFY_ISSUE
 *  \notes         None AUTOSAR API
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, uint8, APPL_CODE) Appl_30_Mcan_CanRamCheckFailed(uint8 Controller);
# endif /* standard RAM_CHECK */
#endif



/* \trace SPEC-1588 */

#if !defined ApplCan_30_McanClockStop
# define C_30_MCAN_DISABLE_APPL_CAN_CLOCK_STOP
# define ApplCan_30_McanClockStop(hwCh)     /* unused user callback */
#else
# define C_30_MCAN_ENABLE_APPL_CAN_CLOCK_STOP
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  ApplCan_30_McanClockStop()
 ***********************************************************************************************************/
/*! \brief         Application call to turn off MCAN clock
 *  \details       This will be called when the application is allowed to turn off the clocks for CAN and Host.
 *  \param[in]     channel       CAN controller
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) ApplCan_30_McanClockStop(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);   /* PRQA S 3408 */ /* MD_Can_ExternalScope */
/* CODE CATEGORY 4 END */
#endif

#if !defined ApplCan_30_McanClockStart
# define ApplCan_30_McanClockStart(hwCh)    /* unused user callback */
#else
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  ApplCan_30_McanClockStart()
 ***********************************************************************************************************/
/*! \brief         Application call to turn on MCAN clock
 *  \details       This will be called when the application shall turn on the clocks for CAN and Host before communication is started.
 *  \param[in]     channel       CAN controller
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, CODE) ApplCan_30_McanClockStart(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);  /* PRQA S 3408 */ /* MD_Can_ExternalScope */
/* CODE CATEGORY 4 END */
#endif

#if !defined( C_30_MCAN_ENABLE_CAN_ECC_INIT_SHM )
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Appl_30_McanCanEccInit()
 ***********************************************************************************************************/
/*! \brief         Application call Intialize the Can Message RAM
 *  \details       This will be called when the application shall initialize the Can message RAM.
 *  \param[in]     void
 *  \return        kCan_30_McanOk      Initialization of the CAN Message RAM was successful
 *  \return        kCan_30_McanFailed  Initialization of the CAN Mesaage RAM failed
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, vuint8, CODE) Appl_30_McanCanEccInit(void);  /* PRQA S 3408 */ /* MD_Can_ExternalScope */
/* CODE CATEGORY 4 END */
#endif

#if defined (C_30_MCAN_ENABLE_UPDATE_BASE_ADDRESS)
/* CODE CATEGORY 4 START */
/************************************************************************************************************
 *  Appl_30_McanCanPowerOnGetBaseAddress()
 ***********************************************************************************************************/
/*! \brief         Application call Intialize the Virtual Base Addresses
 *  \details       This will be called when the application shall make the Power On.
 *  \param[in]     physAddr   Physical address that would be returned
 *  \param[in]     size       Size for the Virtual address
 *  \return        uint32     Physical Address
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_30_MCAN_FUNC(extern, uint32, CODE) Appl_30_McanCanPowerOnGetBaseAddress(uint32 physAddr, vuint16 size);  /* PRQA S 3408 */ /* MD_Can_ExternalScope */
/* CODE CATEGORY 4 END */
#endif


# if defined( C_30_MCAN_ENABLE_INIT_POST_PROCESS )
# define CanBtpReg(ch)               (((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetBasisAdrOfControllerConfig(ch)))->BTP)     /* PRQA S 3453  */ /* MD_MSR_FctLikeMacro */
# define CanRxBCReg(ch)              (((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetBasisAdrOfControllerConfig(ch)))->RXBC)    /* PRQA S 3453  */ /* MD_MSR_FctLikeMacro */
# define CanRxESCReg(ch)             (((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetBasisAdrOfControllerConfig(ch)))->RXESC.R) /* PRQA S 3453  */ /* MD_MSR_FctLikeMacro */
# define CanTxESCReg(ch)             (((V_DEF_30_MCAN_P2SFR_CAN(V_NONE, tCan_30_McanObjType, AUTOMATIC))(Can_30_Mcan_GetBasisAdrOfControllerConfig(ch)))->TXESC)   /* PRQA S 3453  */ /* MD_MSR_FctLikeMacro */
#  if defined( C_30_MCAN_ENABLE_DYNAMIC_MCAN_REVISION )
V_DEF_30_MCAN_VAR(extern, vuint16, VAR_NOINIT)   Can_McanRevision[];     /* PRQA S 3684 */ /* MD_Can_3684 */
#  endif
# endif

# if defined( C_30_MCAN_ENABLE_INIT_POST_PROCESS )
/************************************************************************************************************
 *  Appl_30_McanCanInitPostProcessing()
 ***********************************************************************************************************/
/*! \brief          Service function to overwrite the previously set initialization values
 *  \details        Service function to overwrite the previously set initialization values for the bit timing, taken from the generated data, \n
 *                  with customer specific values. \n
 *                  For your convenience the following access function is supported: \n
 *                  - CanBtpReg(controller):  -  the BTP register of the specified CAN channel can be set according to the register definition \n
 *                  as specified in the Hardware Manufacturer Document ((see ch. 2).  \n
 *                  Example: CanBtpReg(Controller) = 0x00070F70u;  \n
 *                  or    CanBtpReg(0)             = 0x00070F70u; (when using 'Optimize for one controller')
 *  \param[in]      Controller  Number of the controller for which the check failed
 *  \note           Called by CAN driver.
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \notes          Called within controller initialization.
 *  \availability   Only available if  'C_30_MCAN_ENABLE_INIT_POST_PROCESS' is defined via a user-config file.
 *  \warning        None AUTOSAR API \n
 *                  It is the responsibility of the application to assure that the register values are consistent with the release of the underlying derivative.
**********************************************************************************************************************/
V_DEF_30_MCAN_FUNC(V_NONE, void, APPL_CODE) Appl_30_McanCanInitPostProcessing(CAN_30_MCAN_HW_CHANNEL_CANTYPE_ONLY);
# endif




#define CAN_30_MCAN_STOP_SEC_CODE_APPL  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if !defined(C_DRV_30_MCAN_INTERNAL) /* COV_CAN_INTERNAL */
# if defined(CAN_30_MCAN_HL_NO_V_DEF) /* COV_CAN_INTERNAL */
/* only use internal when not defined before - undef to get no conflict in CBD - MSR mixed systems */
#  undef vuint8   /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
#  undef vsint8   /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
#  undef vuint16  /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
#  undef vsint16  /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
#  undef vuint32  /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
#  undef vsint32  /* PRQA S 0841 */ /* MD_Can_HL_UndefTypes */
# endif
#endif

/*!
 * \exclusivearea CAN_EXCLUSIVE_AREA_1
 * Ensures consistency while modifying the interrupt counter and CAN interrupt lock registers.
 * \protects canCanInterruptCounter, CAN interrupt registers
 * \usedin Can_30_Mcan_EnableControllerInterrupts, Can_30_Mcan_DisableControllerInterrupts
 * \exclude All functions provided by Can.
 * \length SHORT The interrupt registers and a counter variable are modified.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_2
 * Ensures consistency while modifying the TX mailbox states and lock registers.
 * \protects Can_30_Mcan_ActiveSendState, CAN mailbox registers
 * \usedin Can_30_Mcan_Write
 * \exclude Can_30_Mcan_Write, Can_30_Mcan_MainFunction_Write, Can TX Interrupt
 * \length MEDIUM Multiplexed TX and cancellation handling. Cancellation handling by CAN Interface triggered. CAN TX mailbox registers and semaphore for locked mailbox modified.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_3
 * Ensures send order (PIA) while CanIf TX buffer reload.
 * \protects Canif_CancelTxConfirmation processing against Can_30_Mcan_Write call inbetween to secure the send order.
 * \usedin Can_30_Mcan_MainFunction_Write, Can TX Interrupt
 * \exclude Can_30_Mcan_Write, Can_30_Mcan_MainFunction_Write, Can TX Interrupt
 * \length MEDIUM CanIf_CancelTxConfirmation. Cancellation handling and follow up CanIf TX buffer reload by CAN Interface triggered.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_4
 * Ensures consistency of RX Queue.
 * \protects RX Queue counter and data
 * \usedin Can_30_Mcan_MainFunction_Read, Can RX Interrupt
 * \exclude Can_30_Mcan_MainFunction_Read, Can RX Interrupt
 * \length SHORT Modify queue counter and copy data to queue.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_5
 * Ensures atomic wakeup mode transition. Do not use CAN interrupt locks because CAN interrupt status may be changed within.
 * \protects wakeup transition
 * \usedin Can_30_Mcan_MainFunction_Wakeup
 * \exclude Can_30_Mcan_SetControllerMode, Can BusOff Interrupt, Can Wakeup, Can_30_Mcan_MainFunction_Wakeup.
 * \length MEDIUM wakeup mode transition will be performed.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_6
 * Ensures atomic mode transition.
 * \protects mode transition
 * \usedin Can_30_Mcan_MainFunction_Mode, Can_30_Mcan_SetControllerMode, Can_30_Mcan_MainFunction_BusOff, Can BusOff Interrupt
 * \exclude Can_30_Mcan_MainFunction_Mode, Can_30_Mcan_SetControllerMode, Can_30_Mcan_MainFunction_BusOff, Can BusOff Interrupt, Can_30_Mcan_MainFunction_Wakeup.
 * \length MEDIUM mode transition will be performed.
 * \endexclusivearea
 *
 * \exclusivearea CAN_EXCLUSIVE_AREA_7
 * Ensures consistency of TX HW FIFO.
 * \protects TX FIFO counter and data
 * \usedin Can_30_Mcan_MainFunction_Write, Can TX Interrupt
 * \exclude Can_30_Mcan_MainFunction_Write, Can TX Interrupt
 * \length SHORT Modify queue counter and copy data to queue.
 * \endexclusivearea
 */

#endif /* end file */
/*  STOPSINGLE_OF_MULTIPLE_COMMENT  */

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


