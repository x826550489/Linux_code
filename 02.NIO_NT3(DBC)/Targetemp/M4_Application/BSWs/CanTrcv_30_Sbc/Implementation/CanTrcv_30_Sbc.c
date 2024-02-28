/* Kernbauer Version: 1.16 Konfiguration: DrvTransCan Erzeugungsgangnummer: 108 */



/**********************************************************************************************************************
 |               C O P Y R I G H T
 |-----------------------------------------------------------------------
 |------  Copyright (c) 2000-2016 by Vector Informatik GmbH, all rights 
 |reserved
 |
 | Please note, that this file contains an implementation example for 
 | CanTrcv. This code may influence the behaviour of the CanTrcv
 | in principle. Therefore, great care must be taken to verify
 | the correctness of the implementation.
 |
 | The contents of the originally delivered files are only examples resp. 
 | implementation proposals. With regard to the fact that these functions 
 | are meant for demonstration purposes only, Vector Informatik's 
 | liability shall be expressly excluded in cases of ordinary negligence, 
 | to the extent admissible by law or statute.
 |  -------------------------------------------------------------------------------------------------------------------
 |  FILE DESCRIPTION
 |  -------------------------------------------------------------------------------------------------------------------
 |         File:  CanTrcv_30_Sbc.c
 |      Project:  MICROSAR
 |       Module:  CAN Transceiver driver
 |    Generator:  DaVinci Configurator 5
 |  Description:  Implementation of the MICROSAR CAN Transceiver Driver.
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Senol Cendere                 Ces           Vector Informatik GmbH
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Robert Schelkle               Rse           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2014-08-09  Rse     -             First Implementation
 *  1.01.00   2015-09-21  Rse     ESCAN00085405 Add support for Partial Networking
 *  2.00.00   2016-01-18  Rse     -             Update to newest template 3.04.00
 *                        Rse     ESCAN00088131 Support application callback functions for Sbc service calls
 *  2.00.01   2016-03-08  Rse     ESCAN00088788 Compiler error: Expected an expression
 *  2.01.00   2016-04-21  Rse     ESCAN00089664 Support SafeBSW
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-02-25  Fn      -             Intitial revision of the core implementation
 *  01.00.01  2008-04-17  Fn      -             Update of the include file names
 *  01.01.00  2008-06-26  Ou      ESCAN00027616 Various compile errors, problems with Organi
 *  01.02.00  2008-09-12  Ou      ESCAN00029980 Compiler failure due to wrong definition of SW version
 *  01.03.00  2008-10-07  Ou      ESCAN00028298 Several warnings due to unreferenced local variables
 *                        Ou      ESCAN00029572 DrvTrans__coreCanxAsr raise DET error if CanTrcv_SetOpMode is called with invalid TrcvWakeupMode
 *                        Ou      ESCAN00030536 Compile error at extended version check
 *  01.04.00  2008-12-11  Ou      ESCAN00031771 Adjust wakeup by bus handling for platforms which cannot be woken up with a CAN frame
 *  01.05.00  2009-02-19  Tvi     ESCAN00033258 GetBusWuReason may return an invalid value
 *  01.06.00  2009-02-26  Tvi     ESCAN00033383 Don't throw DET error in case the same mode is requested again
 *                        Tvi     ESCAN00033398 Compiler warnings when using different transceiver types within the same stack
 *                        Tvi     ESCAN00033413 Possible out of bounds access in SetOpMode if DET is enabled
 *  02.00.00  2009-06-29  Fn      ESCAN00035913 CAN Transceiver channel does not wake up
 *  02.00.01  2009-10-15  Tvi     ESCAN00038495 Compile error: unknown type definitions in dio.h
 *  02.01.00  2009-11-04  Tvi     ESCAN00036841 OP_MODE_SLEEP should be independent of GENERAL_WAKE_UP_SUPPORT
 *                        Tvi     ESCAN00038945 Use different DioPins tokens for GetOpMode and CHECK_WA
 *                        Tvi     ESCAN00038946 Rename filenames to match BSW00347
 *                        Tvi     ESCAN00038947 CanTrcv087 has to be implemented the correct way
 *                        Tvi     ESCAN00039039 Add support for timers
 *                        Tvi     ESCAN00039041 Allow transition to OP_MODE_NORMAL even if it is the current OpMode
 *                        Tvi     ESCAN00039043 Implement an initialization via OP_MODE_NORMAL
 *                        Tvi     ESCAN00039194 Disable IcuNotification when entering Normal mode in Init and SetOpMode
 *  02.02.00  2010-05-04  Tvi     ESCAN00040088 Compiler Warning: unused parameter 'TrcvWakeupMode'
 *  02.20.00  2010-07-01  Tvi     ESCAN00046512 Add support for partial network transceivers
 *            2010-11-29  Tvi     ESCAN00046781 Support Multiple Identity Configuration
 *                                ESCAN00045601 "Channel Used" parameter not well implemented
 *                                ESCAN00046813 Adapt AUTOSAR version check
 *                                ESCAN00047668 Critical areas should be Trcv specific
 *  02.20.01  2011-02-08  Tvi     ESCAN00048498 Wrong DEM Events used
 *  02.20.02  2011-03-11  Tvi     ESCAN00049830 Remove ASR Version check for SPI / DIO
 *                                ESCAN00049831 [PN only] Store wakeup event and report them if Trcv is in Standby mode
 *  03.00.00  2011-05-05  Tvi     ESCAN00051930 Add support for ASR3.2.1
 *                                ESCAN00051564 Remove the AUTOSAR Release Version Check
 *  03.01.00  2011-11-22  Tvi     ESCAN00054349 AR3-1738: Add support for asynchronous transceiver driver
 *                                ESCAN00053272 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053265 AR3-2069: Remove non-SchM code for critical section handling
 *  03.01.01  2012-02-12  Tvi     ESCAN00057892 [PN only] CanTrcv does not wakeup when Synchronous SPI is being used
 *                        Tvi     ESCAN00056788 Compiler error/warning: DRVTRANS__CORECANXASR_RELEASE_VERSION' redefined
 *  04.00.00  2012-05-21  Tvi     ESCAN00058641 AR4-95: Provide CanTrcv according ASR 4, Asynchronous Transceiver Mode Changes
 *                                ESCAN00059656 Add support for SetPNActivationState according to ASR4
 *                                ESCAN00060455 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  04.00.01  2012-09-27  Tvi     ESCAN00061779 [CFG5/ASR4 only]: Compiler error about unkown struct member instanceID
 *  04.01.00  2012-10-08  Tvi     ESCAN00062121 Report DEM if PN is not available
 *                        Tvi     ESCAN00066283 AR4-352: Support partial networking
 *  04.02.00  2013-11-20  Tvi     ESCAN00071370 AR4-569: [CanTrcv]  Incompatible  argument  in call to EcuM_SetWakeupEvent()
 *  04.03.00  2014-01-10  Tvi     ESCAN00073861 AR4-345: Implement PF4_PostBuildSelectable
 *  05.00.00  2014-09-24  Seu     ESCAN00076622 AR4-698: Post-Build Selectable (Identity Manager)
 *  05.00.01  2014-11-13  Seu     -             MISRA deviation comment for rule 6080 added (APIs: *_ClearTrcvWufFlag() and *_CheckWakeFlag())
 *  05.01.00  2015-05-04  Seu     ESCAN00077814 Support for CAN Transceiver on System-Basis Chips (SBCs)
 *            2015-07-23  Seu     ESCAN00084154 Only since R13: Compiler error: C2059: syntax error : '{'
 *            2015-07-23  Seu     ESCAN00083583 Adapt in order to fix ESCAN00083361 / ESCAN00083362
 *            2015-07-23  Seu     ESCAN00083395 Compiler warning: parameter is never used
 *  05.01.01  2015-09-24  Seu     ESCAN00085451 Support usage of Partial Networking for SBCs.
 *  05.01.02  2015-10-06  Seu     ESCAN00085678 Initialize requestState in case of INTERFACE_SBC and PN is used
 *  05.02.00  2015-02-04  Seu     ESCAN00080310 FEAT-427: SafeBSW Step I
 *            2015-10-05  Seu     ESCAN00081795 FEAT-1275: SafeBSW Step 2
 *            2015-10-05  Seu     ESCAN00085154 FEAT-1527: SafeBSW Step 3
 *  05.03.00  2016-01-16  Seu     ESCAN00087580 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088810 Add Postbuild Loadable Support for CanTrcvDrv
 *  05.04.00  2016-04-05  Seu     ESCAN00087813 FEAT-1688: SafeBSW Step 4
 *            2016-05-19  Seu     ESCAN00090097 Compiler error: Syntax Error caused by undefined compiler class
 *  05.04.01  2016-08-02  Seu     ESCAN00091270 MISRA deviation: MISRA-C:2004 Rule 8.8
 *            2016-08-17  Seu     ESCAN00091505 Improve code coverage and doxygen comments
 *            2016-10-17  Seu     ESCAN00091616 Compiler error: identifier index not declared
 * *******************************************************************************************************************/

/* PRQA S 0715 EOF */ /* MD_CanTrcv_30_Sbc_0715 */
/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 0777 EOF */ /* MD_CanTrcv_30_Sbc_0777 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* PRQA S 0779 EOF */ /* MD_CanTrcv_30_Sbc_0779 */

/* ********************************************************************************************************************
 *  INCLUDES
 * *******************************************************************************************************************/
#define CANTRCV_30_SBC_INCLUDE_INTERNAL
#define V_CANTRCV_30_SBC_SOURCE

/* \trace SPEC-19973, SPEC-20008, SPEC-19954, SPEC-19965 */
/* \trace SPEC-14977, SPEC-15093, SPEC-15086, SPEC-14969 */
#include "CanTrcv_30_Sbc.h"



#include "CanIf.h"

#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif

#include "EcuM.h"


/* *********************************************************************************************************************
 *  VERSION CHECK
 * ********************************************************************************************************************/

#if (DRVTRANS__CORECANXASR_VERSION                             != 0x0504u)
# error "Module CanTrcv_30_Sbc: Source and Header files are inconsistent!"
#endif
#if (DRVTRANS__CORECANXASR_RELEASE_VERSION                     != 0x01u)
# error "Module CanTrcv_30_Sbc: Source and Header files are inconsistent!"
#endif


/* ** Version Check: CFG5 - Base part ** */
#define CANTRCV_30_SBC_BASE_GENDATA_COMP_VERSION     0x0104u

#if (CANTRCV_30_SBC_GENTOOL_CFG5_BASE_COMP_VERSION != CANTRCV_30_SBC_BASE_GENDATA_COMP_VERSION)
# error "Module CanTrcv_30_Sbc: Source and Generated Header files are inconsistent! [BASE]"
#endif




# if (DRVTRANS_SBCCANASR_VERSION                    != 0x0201u)
#  error "Module CanTrcv_30_Sbc: Source and Header files are inconsistent!"
# endif
# if (DRVTRANS_SBCCANASR_RELEASE_VERSION            != 0x00u)
#  error "Module CanTrcv_30_Sbc: Source and Header files are inconsistent!"
# endif

/* ** Version Check: CFG5 - HW specific part ** */
#if (CANTRCV_30_SBC_GENTOOL_CFG5_HW_COMP_VERSION != 0x0101u)
# error "Module CanTrcv_30_Sbc: Source and Generated Header files are inconsistent!"
#endif






/* ********************************************************************************************************************
 *  LOCAL DEFINES
 * ********************************************************************************************************************/


#if !defined (CANTRCV_30_SBC_LOCAL)
# define CANTRCV_30_SBC_LOCAL             static
#endif

#if !defined (CANTRCV_30_SBC_LOCAL_INLINE)
# define CANTRCV_30_SBC_LOCAL_INLINE      LOCAL_INLINE
#endif


#define CanTrcvCfg_IsChannelUsed(ch)                   CanTrcv_30_Sbc_IsChannelUsed(ch)
#define CanTrcvCfg_IsWakeupByBusUsed(ch)               CanTrcv_30_Sbc_IsWakeupByBusUsed(ch)
#define CanTrcvCfg_GetWakeupSource(ch)                 CanTrcv_30_Sbc_GetWakeupSource(ch)
#define CanTrcvCfg_GetWakeupSourceSyserr(ch)           CanTrcv_30_Sbc_GetWuSrcSyserr(ch)
#define CanTrcvCfg_GetWakeupSourcePor(ch)              CanTrcv_30_Sbc_GetWuSrcPor(ch)
#define CanTrcvCfg_IsIcuChannelSet(ch)                 CanTrcv_30_Sbc_IsIcuChannelSetOfChannel(ch)
#define CanTrcvCfg_GetIcuChannel(ch)                   CanTrcv_30_Sbc_GetIcuChannelOfChannel(ch)
#define CanTrcvCfg_GetMagicNumber()                    CanTrcv_30_Sbc_GetFinalMagicNumber()
#define CanTrcvCfg_GetGeneratorCompatibilityVersion()  CanTrcv_30_Sbc_GetGeneratorCompatibilityVersion()

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
# define CanTrcvCfg_IsPnEnabled(ch)               CanTrcv_30_Sbc_IsPnEnabled(ch)
#endif



/* --- Flags to handle any kind of requests --- */
# define CanTrcv_30_Sbc_Req_None                  0x00000000u   /* No request pending                     */


# if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
#  define CanTrcv_30_Sbc_Req_OpModeNormalPn        0x00000008u   /* Special mode with Pn enabled in Normal */

#  define CanTrcv_30_Sbc_Req_ClrWufFlag            0x00000010u   /* Request to execute ClearTrcvWufFlag    */
#  define CanTrcv_30_Sbc_Req_ChkWakFlag            0x00000020u   /* Request to execute CheckWakeFlag       */

# endif /* PN */


/* --- Macros to set/get/clear pending requests ---                                */

/* !!! DO NOT use Set* / Clr* in HW specific parts unless stated otherwise     !!! */
/* !!! Ensure data consistency when using Set* / Clr* by using interrupt locks !!! */

/* Check if ANY request is pending. Returns TRUE if at least one of the requests above is pending  */
# define CanTrcv_30_Sbc_IsReqFlagPnd(index) (CanTrcv_30_Sbc_Prob[index].requestState != CanTrcv_30_Sbc_Req_None)

/* Generic macros. DO NOT use. Use the explicit macros instead. Behavior may change in future      */
# define CanTrcv_30_Sbc_SetFlagReq(index, flag) CanTrcv_30_Sbc_Prob[index].requestState   |= (flag)
# define CanTrcv_30_Sbc_ClrFlagReq(index, flag) CanTrcv_30_Sbc_Prob[index].requestState   &= (uint32)(~(flag))
# define CanTrcv_30_Sbc_GetFlagReq(index, flag) ( CanTrcv_30_Sbc_Prob[index].requestState &  (flag) )


# if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
/* Set/Get/Clear a request to process a call to CanTrcv_30_Sbc_ClearTrcvWufFlag */
#  define CanTrcv_30_Sbc_SetClrWufFlagReq(index) CanTrcv_30_Sbc_SetFlagReq(index, CanTrcv_30_Sbc_Req_ClrWufFlag)
#  define CanTrcv_30_Sbc_ClrClrWufFlagReq(index) CanTrcv_30_Sbc_ClrFlagReq(index, CanTrcv_30_Sbc_Req_ClrWufFlag)
#  define CanTrcv_30_Sbc_GetClrWufFlagReq(index) CanTrcv_30_Sbc_GetFlagReq(index, CanTrcv_30_Sbc_Req_ClrWufFlag)

/* Set/Get/Clear a request to process a call to CanTrcv_30_Sbc_CheckWakeFlag */
#  define CanTrcv_30_Sbc_SetChkWakFlagReq(index) CanTrcv_30_Sbc_SetFlagReq(index, CanTrcv_30_Sbc_Req_ChkWakFlag)
#  define CanTrcv_30_Sbc_ClrChkWakFlagReq(index) CanTrcv_30_Sbc_ClrFlagReq(index, CanTrcv_30_Sbc_Req_ChkWakFlag)
#  define CanTrcv_30_Sbc_GetChkWakFlagReq(index) CanTrcv_30_Sbc_GetFlagReq(index, CanTrcv_30_Sbc_Req_ChkWakFlag)

# endif /* PN */




/* ********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 * ********************************************************************************************************************/
#define CANTRCV_30_SBC_IS_INIT                         1
#define CANTRCV_30_SBC_IS_NOT_INIT                     0

/* ********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 * ********************************************************************************************************************/
#define CanTrcv_EnterCritical() SchM_Enter_CanTrcv_30_Sbc_CANTRCV_30_SBC_EXCLUSIVE_AREA_0()
#define CanTrcv_LeaveCritical() SchM_Exit_CanTrcv_30_Sbc_CANTRCV_30_SBC_EXCLUSIVE_AREA_0()



#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
# define CanTrcv_DetReportError(apiId, errorId)  ((void)Det_ReportError((CANTRCV_30_SBC_MODULE_ID), (CANTRCV_30_SBC_INSTANCE_ID), (apiId), (errorId)))
#else
# define CanTrcv_DetReportError(apiId, errorId)
#endif


#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
#  define CanTrcv_ReportErrorNoTrcvControl(apiId) CanTrcv_DetReportError( (apiId), CANTRCV_30_SBC_E_NO_TRCV_CONTROL)
#endif


/* If no errors should be reported */
#if defined(CanTrcv_ReportErrorNoTrcvControl)
#else
# define CanTrcv_ReportErrorNoTrcvControl(apiId)
#endif



# define CANTRCV_30_SBC_SF_WUP_BUS  0x0001u
# define CANTRCV_30_SBC_SF_WUP_PIN  0x0002u
# define CANTRCV_30_SBC_SF_WUP_POR  0x0004u
# define CANTRCV_30_SBC_SF_ERR_BUS  0x0100u
# define CANTRCV_30_SBC_SF_ERR_SYS  0x0200u
# define CANTRCV_30_SBC_SF_ERR_CFG  0x0400u

# define CANTRCV_30_SBC_GET_SF_INIT (CANTRCV_30_SBC_SF_WUP_BUS|CANTRCV_30_SBC_SF_WUP_PIN|CANTRCV_30_SBC_SF_WUP_POR|CANTRCV_30_SBC_SF_ERR_SYS|CANTRCV_30_SBC_SF_ERR_CFG)
# define CANTRCV_30_SBC_GET_SF_SETOPMODE (CANTRCV_30_SBC_SF_ERR_SYS|CANTRCV_30_SBC_SF_ERR_CFG)
# define CANTRCV_30_SBC_GET_SF_CBWAKEUPBYBUS (CANTRCV_30_SBC_SF_WUP_BUS|CANTRCV_30_SBC_SF_WUP_PIN|CANTRCV_30_SBC_SF_ERR_SYS)
# define CANTRCV_30_SBC_GET_SF_MAINFUNCTIONDIAGNOSTICS (CANTRCV_30_SBC_SF_ERR_BUS)
# define CANTRCV_30_SBC_GET_SF_MAINFUNCTION (CANTRCV_30_SBC_SF_WUP_PIN|CANTRCV_30_SBC_SF_WUP_BUS)


#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
# define CANTRCV_30_SBC_IS_INITIALIZED(channel) \
                  ( (CanTrcv_30_Sbc_IsInitialized == CANTRCV_30_SBC_IS_INIT) \
                    && (CanTrcv_30_Sbc_Prob[channel].isInit == CANTRCV_30_SBC_IS_INIT) \
                  )
#endif



# define CanTrcv_30_Sbc_StateWupIsBus(statusFlags)   ( Sbc_Can_Ev_IsWakeup(statusFlags))
# define CanTrcv_30_Sbc_StateWupIsValid(statusFlags) ( CanTrcv_30_Sbc_StateWupIsBus(statusFlags) )


# define CanTrcv_30_Sbc_StateErrIsBus(statusFlags)   ( Sbc_Can_Ev_IsBuserr(statusFlags) )
# define CanTrcv_30_Sbc_StateErrIsSys(statusFlags)   ( Sbc_Can_Ev_IsSyserr(statusFlags) )
# define CanTrcv_30_Sbc_StateErrIsCfg(statusFlags)   ( Sbc_Can_St_GetPncok(statusFlags) == 0u )


#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
# define CANTRCV_30_SBC_CHECK_BAUDRATE(index)       E_OK
#endif /* CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */

#define CanTrcvCfg_GetMappingID(ch)               CanTrcv_30_Sbc_GetChannelIdOfChannelIdMapping(ch)

#if (CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_OFF)
# define CanTrcv_30_Sbc_Hw_SetMode(id, mode)       Sbc_CanTrcv_SetMode(id, mode)
# define CanTrcv_30_Sbc_Hw_ReadStatus(id, flagPtr) Sbc_CanTrcv_ReadStatus(id, flagPtr)
# define CanTrcv_30_Sbc_Hw_ClearEvents(id, event)  Sbc_CanTrcv_ClearEvents(id, event)
# define CanTrcv_30_Sbc_Hw_WritePnConfig(id)       Sbc_CanTrcv_WritePnConfig(id)
#endif

/* ********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 * ********************************************************************************************************************/


typedef Sbc_CanTrcvStatusType CanTrcv_30_Sbc_StatusFlagsType; /* PRQA S 3448 */ /* MD_CanTrcv_30_Sbc_3448 */


/* The following type includes CAN transceiver channel specific settings. */
typedef struct
{
  /* ---- Common attributes ---- */

  /* Last detected wakeup reason */
  CanTrcv_30_Sbc_TrcvWakeupReasonType wakeUpReason;

  /* Specifies whether or not to report wakeups */
  CanTrcv_30_Sbc_TrcvWakeupModeType wakeUpReport;

  /* Holds the last read statusFlags.. only valid if statusFlagsRdy == TRUE */
  CanTrcv_30_Sbc_StatusFlagsType statusFlags;

#if ((CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)) 
  /* Holds the current request state */
  uint32 requestState;
#endif /* SPI_COMMENT / (SBC_COMMENT + PN) */


#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
  /* Indicates if pn is currently available in HW */
  boolean pnAvailable;

  /* Indicates if pn is enabled in software */
  boolean isPnEnabled;
#endif

  /* Specifies whether the transceiver is initialized, this member is not needed in case of DIO because IsUsed == IsInit */
  uint8 isInit;

  /* HW specific attributes */

} CanTrcv_30_Sbc_Prob_Type; /* PRQA S 3448 */ /* MD_CanTrcv_30_Sbc_3448 */

/* ********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 * ********************************************************************************************************************/

#define CANTRCV_30_SBC_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
 /*
 * Specifies whether the CanTrcv module is initialized.
 */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
CANTRCV_30_SBC_LOCAL VAR(uint8, CANTRCV_30_SBC_VAR_INIT) CanTrcv_30_Sbc_IsInitialized = CANTRCV_30_SBC_IS_NOT_INIT;
# endif

#define CANTRCV_30_SBC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



#define CANTRCV_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*
 * In following variable CAN transceiver channel specific settings are stored e.g. the wake-up reason or the current operating mode. 
 * For more information see the description of type: CanTrcv_30_Sbc_Prob_Type.
 */
VAR(CanTrcv_30_Sbc_Prob_Type, CANTRCV_30_SBC_VAR_NOINIT) CanTrcv_30_Sbc_Prob[CANTRCV_30_SBC_MAX_CHANNEL]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Sbc_3408 */


#if (CANTRCV_30_SBC_USE_INIT_POINTER == STD_ON)
/* In following variable the configuration is stored during the initialization of the CAN transceiver driver in case of a Post-build loadable / selectable configuration. */
/* PRQA S 3218 1 */ /* MD_CanTrcv_30_Sbc_8.7 */
CANTRCV_30_SBC_LOCAL P2CONST(CanTrcv_30_Sbc_ConfigType, CANTRCV_30_SBC_VAR_NOINIT, CANTRCV_30_SBC_INIT_DATA) CanTrcv_30_Sbc_ConfigDataPtr;
#endif

#define CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define CANTRCV_30_SBC_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ********************************************************************************************************************
 *  LOCAL FUNCTIONS
 * ********************************************************************************************************************/
/* Local function declarations */

# if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeFlagIndication
 **********************************************************************************************************************/
/*! \brief       Indication to be called by SeqEndNotification of the SPI-driver.
 *  \details     This function has no service id. Called by transceiver driver within: CanTrcv_30_Sbc_CheckWakeFlag().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_SBC_MAX_CHANNEL.
 *  \context     TASK|ISR
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeFlagIndication(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ClearTrcvWufFlagIndication
 **********************************************************************************************************************/
/*! \brief       Indication to be called by SeqEndNotification of the SPI-driver.
 *  \details     This function has no service id. Called by transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_SBC_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvWufFlagIndication(uint8 CanTrcvIndex);
# endif /* PN */



#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReportWakeup
 **********************************************************************************************************************/
/*! \brief       Report the wake-up reason to the upper layer.
 *  \details     This function has no service id. Called by transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_SBC_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReportWakeup(uint8 CanTrcvIndex);
#endif

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! \brief       LL: LL-specific channel initialization.
 *  \details     This function is called for ALL channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               Called by transceiver driver within: CanTrcv_30_Sbc_Init().
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_SBC_MAX_CHANNEL.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_LL_InitChannel
 **********************************************************************************************************************/
/*! \brief       LL: LL-specific channel initialization.
 *  \details     This function is called only for "used" (== activated) channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_SBC_MAX_CHANNEL.
 *               Called by transceiver driver within: CanTrcv_30_Sbc_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_LL_InitChannel(uint8 CanTrcvIndex);

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_InitSubInitPn
 **********************************************************************************************************************/
/*! \brief       Initialization of PN-data.
 *  \details     This function is called only for "used" (== activated) channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_SBC_MAX_CHANNEL.
 *               Called by transceiver driver within: CanTrcv_30_Sbc_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   getStatusFlagRetVal: Status of determination of CAN transceiver HW status flags.
 *  \param[in]   pnEnabled: Status of partial networking within the configuration. TRUE: enabled, FALSE: disabled.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_InitSubInitPn(uint8 CanTrcvIndex, Std_ReturnType getStatusFlagRetVal, boolean pnEnabled);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckPnAvailability
 **********************************************************************************************************************/
/*! \brief       This API checks whether PN-functionality is available by HW or not and adapts the internal state 
*                variable accordingly.
 *  \details     The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_SBC_MAX_CHANNEL.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckPnAvailability(uint8 CanTrcvIndex);
#endif /* CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */



/* ********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 * ********************************************************************************************************************/

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_InitMemory(void)
{
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #100 Mark driver as uninitialized. */
  CanTrcv_30_Sbc_IsInitialized = CANTRCV_30_SBC_IS_NOT_INIT;
#endif
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex)
{
  /* #100 Initialize the CAN transceiver channel-specific settings (independent active or inactive one) (LL-specific). */
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_LL_InitChannel
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_LL_InitChannel(uint8 CanTrcvIndex)
{

  /* #100 Initialize the CAN transceiver channel-specific settings (only active one) (LL-specific). */
}


#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
/**********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_LL_InitChannelPnData
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_InitSubInitPn(uint8 CanTrcvIndex, Std_ReturnType getStatusFlagRetVal, boolean pnEnabled)
{
  /* #100 Initialize the PN-configuration only if PN is enabled within the configuration and determination of status flags from CAN transceiver HW succeeded. */
  if ((pnEnabled == TRUE) && (getStatusFlagRetVal == E_OK))
  {
    /* #110 Determine and store (overwrite the wake-up reason) whether POR or SYSERR is set. If one of them is set the PN configuration must be re-loaded. */
    if (
        (CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)) ||
        (CanTrcv_30_Sbc_StateErrIsCfg(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)) )  /* ASR extension: CFGERR has to be checked too! */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_WU_POWER_ON */
    {
      Std_ReturnType retVal = E_OK;

      if (CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)) /* COV_CANTRCV_HL_LL_SBC_CODECOV_WU_POWER_ON */
      {
        /* Store / overwrite the wake-up reason: BY_SYSERR */
        CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_BY_SYSERR; /* \trace SPEC-15005 */ /* SBSW_CANTRCV_HL_SBC_1 */
      }

      {
        /* \trace SPEC-15068 */
        retVal = CanTrcv_30_Sbc_Hw_WritePnConfig(CanTrcvCfg_GetMappingID(CanTrcvIndex));
      }

      /* #120 Verify if channel specific initialization of PN was successful. If fails report error and disable PN functionality in SW. */
      if (retVal != E_OK)
      {
        /* \trace SPEC-20013 */
        CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_SBC_INIT_ID);

        CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
      }

      /* Dummy statement to prevent compiler warnings */
      CANTRCV_30_SBC_DUMMY_STATEMENT(retVal);

    } /* porFlag == CANTRCV_30_SBC_FLAG_SET || sysErrFlag == CANTRCV_30_SBC_FLAG_SET */
  }
  else /* pnEnabled == TRUE  */
  {
    /* if pn is disabled, data is considered as always valid */
  }
}


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckPnAvailability
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckPnAvailability(uint8 CanTrcvIndex)
{
  if ((CanTrcv_30_Sbc_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
      (!(CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags))) &&
      (!(CanTrcv_30_Sbc_StateErrIsCfg(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)))) /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
  {
    /* #100 If PN functionality is available in HW: Inform the CanIf about this and set internally that PN is available in HW. */

    /* \trace SPEC-15087, SPEC-19956 */
    CanIf_30_Sbc_ConfirmPnAvailability(CanTrcvIndex);

    /* Report that PN is available again */
    CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable = TRUE; /* SBSW_CANTRCV_HL_SBC_1 */
  }
  else
  {
    /* ESCAN00083583 */
    if ((CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)) ||
        (CanTrcv_30_Sbc_StateErrIsCfg(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags))) /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
    {
      /* PN does NOT work due to CFGERR or SYSERR occurred */

      /* #110 If PN-functionality is NOT available in HW: set internally that PN is NOT available in HW. */
      CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
    }
  }
}
#endif /* CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */


/**********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Init( P2CONST(CanTrcv_30_Sbc_ConfigType, AUTOMATIC, CANTRCV_30_SBC_INIT_DATA) ConfigPtr )
{
  /* \trace SPEC-14971 */

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* ESCAN00076622 */
#if (CANTRCV_30_SBC_USE_INIT_POINTER == STD_ON)
  /* #100 Store the configuration pointer. (Required before any check especially for PBL-configurations due to access to GeneratorCompatibilityVersion and MagicNumber via the ConfigPtr.) */
  CanTrcv_30_Sbc_ConfigDataPtr = ConfigPtr;

# if ((CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)) /* COV_CANTRCV_HL_LL_SBC_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #10 Check if parameter ConfigPtr is valid. */
  if (ConfigPtr == NULL_PTR)
  {
#  if (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_SBC_VARCOV_SW_FEAT_NOT_SUPPORTED */
    EcuM_BswErrorHook((uint16) CANTRCV_30_SBC_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
#  endif /* (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */

#  if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) /* COV_CANTRCV_HL_LL_SBC_VARCOV_SW_FEAT_NOT_SUPPORTED */
    /* \trace SPEC-14948 */
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
#  endif /* (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) */
  }
  else
# endif /* (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
# if (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_SBC_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #20 Check the generator compatibility version */
  if (CanTrcvCfg_GetGeneratorCompatibilityVersion() != (uint32)((CANTRCV_30_SBC_BASE_GENDATA_COMP_VERSION << 16u) | CANTRCV_30_SBC_HW_GENDATA_COMP_VERSION)) /* COV_CANTRCV_HL_LL_SBC_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_SBC_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  /* #30 Check the magic number */
  else if (CanTrcvCfg_GetMagicNumber() != CANTRCV_30_SBC_FINAL_MAGIC_NUMBER) /* COV_CANTRCV_HL_LL_SBC_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_SBC_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
# endif /* (CANTRCV_30_SBC_CONFIGURATION_VARIANT == CANTRCV_30_SBC_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
#endif /* (CANTRCV_30_SBC_USE_INIT_POINTER == STD_ON) */
  {
    uint8_least index;





#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
    /* #110 Set transceiver driver as initialized at all. */
    CanTrcv_30_Sbc_IsInitialized = CANTRCV_30_SBC_IS_INIT;
#endif

    /* #120 Run through all transceiver channels and initialize them.*/
    for(index = 0; index < CANTRCV_30_SBC_MAX_CHANNEL; ++index)
    {

      /* Initialize variables */

      /* Initialize LL */
      CanTrcv_30_Sbc_LL_InitMemoryChannelBegin((uint8)index);

      /* #130 Set the channel states concerning: initialization, wake-up report and wake-up reason to default values. */
      CanTrcv_30_Sbc_Prob[index].isInit = CANTRCV_30_SBC_IS_NOT_INIT; /* SBSW_CANTRCV_HL_SBC_1 */
      CanTrcv_30_Sbc_Prob[index].wakeUpReport = CANTRCV_30_SBC_WU_ENABLE; /* SBSW_CANTRCV_HL_SBC_1 */
      CanTrcv_30_Sbc_Prob[index].wakeUpReason = CANTRCV_30_SBC_WU_ERROR; /* SBSW_CANTRCV_HL_SBC_1 */

      /* #140 Set the channel state concerning: request state to default values (only SPI-interface or SBC-interface with PN). */
#if ((CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)) 
      CanTrcv_30_Sbc_Prob[index].requestState = CanTrcv_30_Sbc_Req_None; /* SBSW_CANTRCV_HL_SBC_1 */
#endif


#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
      /* #170 Set the channel states concerning: Partial networking to default values (only PN). */
      CanTrcv_30_Sbc_Prob[index].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
      CanTrcv_30_Sbc_Prob[index].isPnEnabled = FALSE; /* is configured in _Init() */ /* SBSW_CANTRCV_HL_SBC_1 */
#endif


      /* ----- Implementation ----------------------------------------------- */

      /* #190 Initialize next parameters only for active transceiver channels. */
      if(CanTrcvCfg_IsChannelUsed(index))
      {
#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
        uint8 pnEnabled = FALSE;
#endif

# if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
    ( (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) ) 
        Std_ReturnType getStatusFlagRetVal = E_NOT_OK;
# endif

        Std_ReturnType modeSet = E_NOT_OK;

        /* #200 If no wake-up event occurred during initialization the default reason is RESET. */
        CanTrcv_30_Sbc_Prob[index].wakeUpReason = CANTRCV_30_SBC_WU_RESET; /* SBSW_CANTRCV_HL_SBC_1 */

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
        pnEnabled = CanTrcvCfg_IsPnEnabled(index);

        /* #210 Set the channel states concerning: partial networking to configured values (only PN). */
        CanTrcv_30_Sbc_Prob[index].pnAvailable = pnEnabled; /* SBSW_CANTRCV_HL_SBC_1 */
        CanTrcv_30_Sbc_Prob[index].isPnEnabled = pnEnabled; /* SBSW_CANTRCV_HL_SBC_1 */
#endif

        /* #220 Do additional checks: wake-up event, HW status, PN configuration. (critical section is used). */
        CanTrcv_EnterCritical();
#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
    ( (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) ) 
        /* \trace SPEC-14953 */


          /* #230 Check general status flags. If fails report error. */
        getStatusFlagRetVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(index), &CanTrcv_30_Sbc_Prob[index].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
        if ((getStatusFlagRetVal == E_NOT_OK))
        {
          /* \trace SPEC-20013 */
          CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_SBC_INIT_ID);
        }
#endif /* CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON || CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */

        /* #240 Determine whether a wake-up event (BY_BUS, BY_PIN) occurred or NOT. If occurred store it. */
#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON)
        if ((getStatusFlagRetVal == E_OK))
        {
          if (CanTrcv_30_Sbc_StateWupIsBus(CanTrcv_30_Sbc_Prob[index].statusFlags))
          {
            /* A wakeup occurred. The reason is: BY_BUS */
            CanTrcv_30_Sbc_Prob[index].wakeUpReason = CANTRCV_30_SBC_WU_BY_BUS; /* SBSW_CANTRCV_HL_SBC_1 */
          }
        }
#endif /* CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON */

        CanTrcv_LeaveCritical();

        /* Do some generic initialization of LL */
        CanTrcv_30_Sbc_LL_InitChannel((uint8)index);

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
        /* #250 Initialize the CAN transceiver HW according partial networking configuration. */
        CanTrcv_30_Sbc_InitSubInitPn((uint8)index, getStatusFlagRetVal, pnEnabled);
#endif /* CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */

#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
        /* #260 Report the detected wake-up event to the upper layer. */
        CanTrcv_30_Sbc_ReportWakeup((uint8)index);
#endif

        /* #270 Set the operating mode to NORMAL. In case of SPI-interface always synchronous. (critical section used) */
        CanTrcv_EnterCritical();

#if (CANTRCV_30_SBC_USE_ICU == STD_ON)
        if (CanTrcvCfg_IsIcuChannelSet(index)) /* \trace SPEC-14950 */
        {
          Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(index) ); /* \trace SPEC-14973*/
        }
#endif

        
        modeSet = CanTrcv_30_Sbc_Hw_SetMode(CanTrcvCfg_GetMappingID(index), SBC_CANTRCV_MODE_NORMAL);

        CanTrcv_LeaveCritical();



        /* #300 Check if setting of operating mode was successful. */
        if (modeSet == E_OK) /* PRQA S 3355, 3358 */ /* MD_CanTrcv_30_Sbc_335X, MD_CanTrcv_30_Sbc_335X */
        {
          /* #330 Mode change was successful: Set current transceiver channel to initialized. */
          CanTrcv_30_Sbc_Prob[index].isInit = CANTRCV_30_SBC_IS_INIT; /* SBSW_CANTRCV_HL_SBC_1 */
        }
        else
        { /* PRQA S 3201 */ /* MD_CanTrcv_30_Sbc_3201 */
          /* \trace SPEC-20013 */
          /* #340 Mode change was NOT successful: Report error. */
          errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
        }
      } /* CanTrcvChannelUsed == TRUE */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) && (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
      else
      {
        /* Just to prevent MISRA violations */
      }
#endif
    } /* for (...) */
  } /* if (ConfigPtr == NULL_PTR) .. else */

#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR) /* PRQA S 3356, 3359 */ /* MD_CanTrcv_30_Sbc_335X, MD_CanTrcv_30_Sbc_335X */ /* COV_CANTRCV_HL_SBC_CODECOV_NOT_EACH_CONFIG */
  { /* PRQA S 3201 */ /* MD_CanTrcv_30_Sbc_3201 */
    CanTrcv_DetReportError(CANTRCV_30_SBC_INIT_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif
  
#if (CANTRCV_30_SBC_USE_INIT_POINTER == STD_OFF)
  CANTRCV_30_SBC_DUMMY_STATEMENT(ConfigPtr);
#endif
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetOpMode
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  Std_ReturnType modeSet = E_NOT_OK;

  CanTrcv_30_Sbc_TrcvModeType currentOpMode;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19976 */  
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19976 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15064 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute transition of operating mode only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #110 Check if the current operating mode equals the requested one. */
      (void)CanTrcv_30_Sbc_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_SBC_3 */

      if (currentOpMode == OpMode) /* \trace SPEC-15090 */
      {
        /* \trace SPEC-19955 */
        returnVal = E_OK;
        /* The mode was verified within GetOpMode, so the mode was set */
        modeSet = E_OK;

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
        /* #130 The requested one equals the current one. Do NOT execute the mode change request. */
        if ((currentOpMode == CANTRCV_30_SBC_OP_MODE_NORMAL) &&
            (CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable == TRUE) && (CanTrcv_30_Sbc_Prob[CanTrcvIndex].isPnEnabled == TRUE))
        {
          /* #140 The requested one equals the current one. If PN is available and enabled confirm the PN availability. (only PN) */
          CanIf_30_Sbc_ConfirmPnAvailability(CanTrcvIndex); /* \trace SPEC-15087, SPEC-19956 */
        }
#endif

      }
      else
      {
        /* #160 The requested one does NOT equal the current one. Execute the requested mode change. (critical section is used) */
        /* \trace SPEC-19962 */
        switch(OpMode)
        {
          /* #200 Mode change request to NORMAL. */
          case CANTRCV_30_SBC_OP_MODE_NORMAL:

            /* #210 Check whether it is an internal wake-up. If yes store the wake-up reason. */         
            if(
               (CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_SBC_WU_ERROR))
            {
              /* Transceiver is switched from STANDBY/SLEEP -> NORMAL and has not detected any wakeup.
                 This is considered as internal wakeup. */
              CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_INTERNALLY; /* SBSW_CANTRCV_HL_SBC_1 */
            }
            
            CanTrcv_EnterCritical();

            /* #220 If ICU is configured, disable ICU. */
# if (CANTRCV_30_SBC_USE_ICU == STD_ON)
            if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
            {
              Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-14973 */
            }
# endif
            
            {
              /* #240 No mode request is currently pending. Store the current mode request. (only SPI-interface) */
              /* #250 Execute operating mode change request to NORMAL. */
              
              modeSet = CanTrcv_30_Sbc_Hw_SetMode(CanTrcvCfg_GetMappingID(CanTrcvIndex), SBC_CANTRCV_MODE_NORMAL);

# if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
              if (modeSet == E_OK)
              {
                Std_ReturnType stateRead;
                stateRead = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
                if (stateRead == E_OK)
                {
                  CanTrcv_30_Sbc_CheckPnAvailability(CanTrcvIndex);
                }
                else
                {
                  /* no hw access is available so pnAvailable is FALSE */
                  CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
                  
                  CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_SBC_SETOPMODE_ID);
                }
              }
# endif
            }

            CanTrcv_LeaveCritical();
            returnVal = E_OK;
            break;

          case CANTRCV_30_SBC_OP_MODE_STANDBY:
             /* #300 Mode change request to STANDBY. (only if supported by HW) */
            {
              /* #320 Current mode is NORMAL: Execute mode request. */
              CanTrcv_EnterCritical();

              /* #330 If ICU is configured, disable ICU. */
# if (CANTRCV_30_SBC_USE_ICU == STD_ON)
              if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
              {
                Icu_EnableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-15004 */
              }
# endif
              /* #340 Reset wake-up reason. */
              CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_ERROR; /* SBSW_CANTRCV_HL_SBC_1 */

              {
                /* #360 No mode request is currently pending. Store the mode request. (only SPI-interface) */
                /* #370 Execute operating mode change request to STANDBY. */
                
                modeSet = CanTrcv_30_Sbc_Hw_SetMode(CanTrcvCfg_GetMappingID(CanTrcvIndex), SBC_CANTRCV_MODE_STANDBY);
              }

              CanTrcv_LeaveCritical();
              returnVal = E_OK;
            }
            break;

          case CANTRCV_30_SBC_OP_MODE_SLEEP:
            /* #400 Mode change request to SLEEP. (only if supported by HW) */
            /* Sleep mode is not supported */
            returnVal = E_NOT_OK; /* \trace SPEC-15020 */
            break;

          default: /* PRQA S 2018 */ /* MD_MSR_14.1 */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
            /* \trace SPEC-14963 */
            /* #40 Check if parameter OpMode is valid. */
            errorId = CANTRCV_30_SBC_E_PARAM_TRCV_OP_MODE;
#endif
            break;
          } /* switch() */
      } /* currentOpMode == OpMode */

      /* #600 If mode request executed successfully then inform the CanIf else report error. */
      if (returnVal == E_OK)
      {
        if(modeSet == E_OK)
        {
          /* SBC ensures with modeSet == E_OK that requested mode was set */
          CanIf_30_Sbc_TrcvModeIndication(CanTrcvIndex, OpMode); /* \trace SPEC-20006 */
        }
        else
        {
          /* \trace SPEC-20011 */
          errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;

          returnVal = E_NOT_OK;
        } /* currentOpMode != OpMode */
      } /* returnVal == E_OK */
    } /* channelUsed == TRUE */
  }

#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_SETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif
  return returnVal;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetOpMode
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;



  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter OpMode is valid. */
  if(OpMode == NULL_PTR)
  {
    /* \trace SPEC-14958 */
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15042 */
    errorId =  CANTRCV_30_SBC_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #200 DIO-interface: Read the mode from status of PINs of underlying HW. (critical section used) */
      /* #201 SPI-interface: Read the mode from state variable. */
      /* #202 SBC-interface: Read the mode via SBC module API. (critical section used) */
      CanTrcv_EnterCritical();

      
      returnVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
      

      CanTrcv_LeaveCritical();

      if (returnVal == E_OK)
      {
        /* \trace SPEC-19974 */

        if(Sbc_Can_St_GetMode(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags) == SBC_CANTRCV_MODE_NORMAL)
        {
          /* CAN transceiver is in normal operation mode */
          *OpMode = CANTRCV_30_SBC_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_SBC_2 */
          returnVal = E_OK;
        }


        if(Sbc_Can_St_GetMode(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags) == SBC_CANTRCV_MODE_STANDBY)
        {
          /* CAN transceiver is in standby mode */
          *OpMode = CANTRCV_30_SBC_OP_MODE_STANDBY; /* SBSW_CANTRCV_HL_SBC_2 */
          returnVal = E_OK;
        }
      }

      /* #210 If reading of operating mode NOT succeeded report error. */
      if (returnVal == E_NOT_OK) /* PRQA S 3356,3359 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
      { /* PRQA S 3201 */ /* MD_CanTrcv_30_Sbc_3201 */
        /* \trace SPEC-19940 */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
    } /* Channel is used */
  } /* DET checks passed */
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_GETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif

 return returnVal;
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetBusWuReason
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) Reason)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;

#if (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_SBC_WAKEUP_NONE) 
  CanTrcv_30_Sbc_TrcvModeType currentOpMode;
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if the return-parameter Reason is valid. */
  if(Reason == NULL_PTR)
  {
    /* \trace SPEC-15063 */
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15059 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* UREQ00015010 */
      /* #200 Check the wake-up reason for validity. */
#if (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_SBC_WAKEUP_NONE) 
      if(CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_SBC_WU_ERROR)
      {
        /* #300 If wake-up reason is invalid return WU_ERROR. */
        *Reason = CANTRCV_30_SBC_WU_ERROR; /* SBSW_CANTRCV_HL_SBC_2 */

        /* #310 Wake-up reason is invalid (WU_ERROR). This is OK only in case of transceiver channel is in NORMAL mode. */
        (void)CanTrcv_30_Sbc_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_SBC_3 */

        if(currentOpMode != CANTRCV_30_SBC_OP_MODE_NORMAL)
        {
          /* \trace SPEC-19980 */
          /* #320 Being in any mode except NORMAL with WU_ERROR is an error hence report it. */
          errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
        }
      }
      else
      {
        /* #400 Wake-up reason is valid (neither WU_ERROR nor WU_NOT_SUPPORTED). Return the current wake-up reason.*/
        *Reason = CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason; /* SBSW_CANTRCV_HL_SBC_2 */
        returnVal = E_OK;
      }
#else /* (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_SBC_WAKEUP_NONE) */
      *Reason = CANTRCV_30_SBC_WU_NOT_SUPPORTED; /* SBSW_CANTRCV_HL_SBC_2 */
#endif /* (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_SBC_WAKEUP_NONE) */
    } /* IsChannelUsed */
  }
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_GETBUSWUREASON_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif
  
  return returnVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetWakeupMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15077 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_SBC_WAKEUP_NONE) 
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      /* #200 Set the requested wake-up mode. */
      switch(TrcvWakeupMode)
      {
        case CANTRCV_30_SBC_WU_ENABLE:
             /* \trace SPEC-19990 */
             CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_SBC_WU_ENABLE; /* SBSW_CANTRCV_HL_SBC_1 */

             /* #300 In addition: If requested wake-up mode is WU_ENABLE report if wake-up event(s) is/are pending. */
# if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
     (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
             CanTrcv_30_Sbc_ReportWakeup(CanTrcvIndex);
# endif

             returnVal = E_OK;
             break;

        case CANTRCV_30_SBC_WU_DISABLE:
             /* \trace SPEC-20012 */
             CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_SBC_WU_DISABLE; /* SBSW_CANTRCV_HL_SBC_1 */

             returnVal = E_OK;
             break;

        case CANTRCV_30_SBC_WU_CLEAR:
             /* \trace SPEC-19961 */
             /* #500 In addition: If requested wake-up mode is WU_CLEAR clear the wake-up reason and all detected wake-up events. */
             CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_ERROR; /* SBSW_CANTRCV_HL_SBC_1 */
             returnVal = E_OK;

             break;
        default:  /* PRQA S 2018 */ /* MD_MSR_14.1 */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
             /* #40 Check if parameter TrcvWakeupMode is valid. */
             errorId = CANTRCV_30_SBC_E_PARAM_TRCV_WAKEUP_MODE; /* \trace SPEC-15036 */
# endif
             break;
      }
    }
#endif /* CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_SBC_WAKEUP_NONE */
  }
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_SETWAKEUPMODE_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif  
  
#if (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_SBC_WAKEUP_NONE) 
  CANTRCV_30_SBC_DUMMY_STATEMENT(TrcvWakeupMode);
# if(CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
  CANTRCV_30_SBC_DUMMY_STATEMENT(CanTrcvIndex);
# endif
#endif
  /* \trace SPEC-19978: Not implemented as no need to query HW at this place. */

  return returnVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeup
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeup(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;



  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-19994 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON)
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active and wake-up detection is enabled. (critical section used) */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      if(CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex) &&
         (CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReport == CANTRCV_30_SBC_WU_ENABLE)) /* COV_CANTRCV_HL_SBC_CODECOV_IS_WU_BY_BUS_USED */
      {
        CanTrcv_30_Sbc_TrcvModeType currentOpMode;
        CanTrcv_EnterCritical();

        /* #110 Is the transceiver channel in NORMAL? (only DIO-/SBC-interface) */
        (void)CanTrcv_30_Sbc_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_SBC_3 */

        if (currentOpMode == CANTRCV_30_SBC_OP_MODE_NORMAL)
        {
          /* #120 Operating mode NORMAL: No valid wake-up event detected. (only DIO-/SBC-interface)*/
          returnVal = E_NOT_OK;
        }
        else
        {
          /* #400 No pending wake-up flags. Request the underlying HW for wake-up flags. */


          returnVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
          /* --> Flags will be processed in GetStatusFlagsIndication + CbWakeupByBusIndication */


          /* #500 If any wake-up event detected determine the wake-up reason (e.g BY_BUS, BY_PIN). (only DIO-interface or SBC-interface) */
          if (returnVal == E_OK)
          {
            if (CanTrcv_30_Sbc_StateWupIsBus(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags))
            {
              CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_BY_BUS; /* SBSW_CANTRCV_HL_SBC_1 */
              CanTrcv_30_Sbc_ReportWakeup(CanTrcvIndex);

              returnVal = E_OK; /* Wakeup detected */
            }
            else
            {
              returnVal = E_NOT_OK; /* No Wakeup detected */
            }
          }

        }

        CanTrcv_LeaveCritical();

      }
    }
#else
    returnVal = E_NOT_OK;
#endif /* CANTRCV_30_SBC_WAKEUP_BY_BUS_USED */
  }
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_CHECKWAKEUP_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif  
  
#if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF) && (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_OFF)
  CANTRCV_30_SBC_DUMMY_STATEMENT(CanTrcvIndex);
#endif
  return returnVal;
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */




#if (CANTRCV_30_SBC_GET_VERSION_INFO == STD_ON) /* \trace SPEC-15105 */
/* \trace SPEC-19953 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter VersionInfo is valid. */
  if(VersionInfo == NULL_PTR)
  {
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  else
# endif /* CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* \trace SPEC-14986, SPEC-15032 */
    /* #100 Retrieve the version information: VENDOR_ID, MODULE_ID, SW_MAJOR-, SW_MINOR- and SW_PATCH-version. */
    VersionInfo->vendorID = CANTRCV_30_SBC_VENDOR_ID; /* SBSW_CANTRCV_HL_SBC_2 */
    VersionInfo->moduleID = CANTRCV_30_SBC_MODULE_ID; /* SBSW_CANTRCV_HL_SBC_2 */

    VersionInfo->sw_major_version = CANTRCV_30_SBC_SW_MAJOR_VERSION; /* SBSW_CANTRCV_HL_SBC_2 */
    VersionInfo->sw_minor_version = CANTRCV_30_SBC_SW_MINOR_VERSION; /* SBSW_CANTRCV_HL_SBC_2 */
    VersionInfo->sw_patch_version = CANTRCV_30_SBC_SW_PATCH_VERSION; /* SBSW_CANTRCV_HL_SBC_2 */
  }
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_GETVERSIONINFO_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif 
}
#endif /* CANTRCV_30_SBC_GET_VERSION_INFO == STD_ON */




/* \trace SPEC-19989 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetTrcvSystemData
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetTrcvSystemData(uint8 CanTrcvIndex, P2VAR(uint32, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) TrcvSysData )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19942 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19942 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15025 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  /* #40 Check if parameter TrcvSysData is valid. */
  else if(TrcvSysData == NULL_PTR)
  {
    /* \trace SPEC-15098*/
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  else
# endif /* CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      {
        uint32          regVal;

        Sbc_CanTrcvStatusType tmpStatus;


        /* #300 SPI is NOT busy: Read the value of the diagnostic register. (critical section used) */
        CanTrcv_EnterCritical();
        /* \trace SPEC-15026 */
        retVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
        
        tmpStatus = CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags;
        regVal = (uint32)((((uint32)tmpStatus.Events) << 16) | (((uint32)tmpStatus.States) << 8) | (uint32)tmpStatus.Mode);
        CanTrcv_LeaveCritical();

        if (retVal == E_OK)
        {
          *TrcvSysData = regVal; /* SBSW_CANTRCV_HL_SBC_2 */
        }
        else
        {
          /* retVal is already E_NOT_OK, no need to overwrite it here */
          /* \trace SPEC-19997 */
          /* #310 If reading of diagnostic register failed, report error. */
          errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
        }
      }
    } /* IsChannelUsed */
  }
  
# if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_GETTRCVSYSTEMDATA_ID, errorId);
  }
# else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
# endif  
  
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ClearTrcvWufFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvWufFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19970 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19970 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15018 */
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if( CanTrcvCfg_IsChannelUsed(CanTrcvIndex) )
# endif
    {

      CanTrcv_EnterCritical();

      /* #110 Clear wake-up reason and all wake-up events detected during initialization. */
      CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_SBC_WU_ERROR; /* SBSW_CANTRCV_HL_SBC_1 */

      /* #120 Store the current request. It will be cleared within indication. */
      CanTrcv_30_Sbc_SetClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */

      /* \trace SPEC-14997 */
      retVal = CanTrcv_30_Sbc_Hw_ClearEvents(CanTrcvCfg_GetMappingID(CanTrcvIndex), SBC_CAN_EV_WAKEUP);
      if (retVal == E_OK)
      {
        CanTrcv_30_Sbc_ClearTrcvWufFlagIndication(CanTrcvIndex);
      }

      if (retVal == E_NOT_OK)
      {
        /* #130 If unable to clear the wake-up flag, clear this request. */
        CanTrcv_30_Sbc_ClrClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */
      }

      CanTrcv_LeaveCritical();

      /* The indication is called from the SPI-callback */

      if (retVal == E_NOT_OK)
      {
        /* retVal is already E_NOT_OK, no need to overwrite it here */
        /* \trace SPEC-19943 */
        /* #140 If unable to clear the wake-up flag, report error. */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
    } /* IsChannelUsed */
  }
  
#if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_CLEARTRCVWUFFLAG_ID, errorId);
  }
#else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
#endif  
  
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ClearTrcvWufFlagIndication
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvWufFlagIndication(uint8 CanTrcvIndex)
{
  /* #100 Clear the request to clear the wake-up flag in HW. */
  CanTrcv_EnterCritical();
  CanTrcv_30_Sbc_ClrClrWufFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */
  CanTrcv_LeaveCritical();

  /* #110 Inform CanIf about successful completion of request. */
  CanIf_30_Sbc_ClearTrcvWufFlagIndication(CanTrcvIndex); /* \trace SPEC-19983 */
}


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReadTrcvTimeoutFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReadTrcvTimeoutFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Sbc_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) FlagState)  /* PRQA S 3673 */ /* MD_CanTrcv_30_Sbc_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19984 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19984 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK; 
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  /* #40 Check if parameter FlagState is valid. */
  else if(FlagState == NULL_PTR)
  {
    /* \trace SPEC-14943 */
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  else
# endif /* (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON) */
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
    {
      /* #300 SPI is NOT busy: Read the value of the time-out flag. (critical section is used) */
      CanTrcv_EnterCritical();
      /* \trace SPEC-20010 */
      retVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
      if (Sbc_Can_Ev_IsTimeout(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags))
      {
        (*FlagState) = CANTRCV_30_SBC_FLAG_SET; /* SBSW_CANTRCV_HL_SBC_2 */
      }
      else
      {
        (*FlagState) = CANTRCV_30_SBC_FLAG_CLEARED; /* SBSW_CANTRCV_HL_SBC_2 */
      }
      CanTrcv_LeaveCritical();

      if (retVal == E_NOT_OK)  /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
      {
        /* #310 If reading of time-out flag failed, report error. */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR) /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_READTRCVTIMEOUTFLAG_ID, errorId);
  }
# else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
# endif  

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ClearTrcvTimeoutFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvTimeoutFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-19948 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19948 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
    {
      /* #300 SPI is NOT busy: Clear the value of the time-out flag. (critical section is used) */
      CanTrcv_EnterCritical();
      /* \trace SPEC-19996 */
      retVal = CanTrcv_30_Sbc_Hw_ClearEvents(CanTrcvCfg_GetMappingID(CanTrcvIndex), SBC_CAN_EV_TIMEOUT);
      CanTrcv_LeaveCritical();

      if (retVal == E_NOT_OK)  /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
      {
        /* #310 If clearing of the time-out flag failed, report error. */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR) /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_CLEARTRCVTIMEOUTFLAG_ID, errorId);
  }
# else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
# endif  

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReadTrcvSilenceFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReadTrcvSilenceFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Sbc_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) FlagState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-20000 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20000 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  /* #40 Check if parameter FlagState is valid. */
  else if(FlagState == NULL_PTR)
  {
    /* \trace SPEC-15062*/
    errorId = CANTRCV_30_SBC_E_PARAM_POINTER;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
  /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
  if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
  {
    {
      /* #300 SPI is NOT busy: Read the value of the silence flag. (critical section used) */
      CanTrcv_EnterCritical();
      /* \trace SPEC-19999 */
      retVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
      if (Sbc_Can_St_GetSilent(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags) != 0u)
      {
        (*FlagState) = CANTRCV_30_SBC_FLAG_SET; /* SBSW_CANTRCV_HL_SBC_2 */
      }
      else
      {
        (*FlagState) = CANTRCV_30_SBC_FLAG_CLEARED; /* SBSW_CANTRCV_HL_SBC_2 */
      }
      CanTrcv_LeaveCritical();

      if (retVal == E_NOT_OK)  /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
      {
        /* #310 If reading of the silence flag failed, report error. */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
    }
  } /* IsChannelUsed */

# if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR) /* PRQA S 3355,3358 */ /* MD_CanTrcv_30_Sbc_13.7 */ /* COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC */
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_READTRCVSILENCEFLAG_ID, errorId);
  }
# else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
# endif  

  return retVal;
} /* PRQA S 3673,6080 */ /* MD_CanTrcv_30_Sbc_3673,MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeFlag(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_SBC_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_SBC_MAX_CHANNEL)
  {
    /* \trace SPEC-20005 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20005 */
    errorId = CANTRCV_30_SBC_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_SBC_IS_INITIALIZED(CanTrcvIndex))
  {
    errorId = CANTRCV_30_SBC_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. (critical section used) */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      CanTrcv_EnterCritical();

      /* \trace SPEC-20015 */
      {
        /* #300 Get and evaluate status flags. (synchronous SPI-interface) Request most current status flags. (asynchronous SPI-interface) */

        /* Store the request. it will be reset on indication */
        CanTrcv_30_Sbc_SetChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */

        /* This code should read and clear the wake flags within one step */
        retVal = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(CanTrcvIndex), &CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
        if (retVal == E_OK)
        {
          CanTrcv_30_Sbc_CheckWakeFlagIndication(CanTrcvIndex);
        }

        if (retVal == E_NOT_OK)
        {
          /* No indication will occur. Clear request flag */
          CanTrcv_30_Sbc_ClrChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */
        }
      }
      CanTrcv_LeaveCritical();

      if (retVal == E_NOT_OK)
      {
        /* #310 If getting / requesting of status flags fails, report error. */
        errorId = CANTRCV_30_SBC_E_NO_TRCV_CONTROL;
      }
      /* --> CheckWakeFlagIndication will be called from the SPI callback */
    } /* IsChannelUsed */
  } /* DET checks passed */

# if (CANTRCV_30_SBC_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_SBC_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_SBC_CHECKWAKEFLAG_ID, errorId);
  }
# else
  CANTRCV_30_SBC_DUMMY_STATEMENT(errorId);
# endif  
  
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeFlagIndication
 **********************************************************************************************************************/
/*! Internal comment removed. *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeFlagIndication(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanTrcv_30_Sbc_TrcvWakeupReasonType localWakeUpReason = CANTRCV_30_SBC_WU_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  CanTrcv_EnterCritical();


  /* #100 Determine the wake-up reason: BY_SYSERR (only PN), BY_BUS or BY_PIN. (critical section used) */
  if ((CanTrcv_30_Sbc_Prob[CanTrcvIndex].pnAvailable == TRUE) && (CanTrcv_30_Sbc_Prob[CanTrcvIndex].isPnEnabled == TRUE) &&
      (CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)))
  {
    localWakeUpReason = CANTRCV_30_SBC_WU_BY_SYSERR;
  }
  else if ((CanTrcv_30_Sbc_StateWupIsBus(CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags)))
  {
    localWakeUpReason = CANTRCV_30_SBC_WU_BY_BUS;
  }
  else
  {
    /* Nothing. */
  }

  if (localWakeUpReason != CANTRCV_30_SBC_WU_ERROR)
  {
    /* #110 If any wake-up event was detected, store the wake-up reason and inform the EcuM. */
    CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason = localWakeUpReason; /* SBSW_CANTRCV_HL_SBC_1 */
    CanTrcv_30_Sbc_ReportWakeup(CanTrcvIndex);
  }

  /* Release request */
  CanTrcv_30_Sbc_ClrChkWakFlagReq(CanTrcvIndex); /* SBSW_CANTRCV_HL_SBC_1 */

  CanTrcv_LeaveCritical();

  /* \trace SPEC-19979 */ 
  /* #120 Inform CanIf about successful execution of request to check for wake-up event(s). */
  CanIf_30_Sbc_CheckTrcvWakeFlagIndication(CanTrcvIndex);
}
# endif /* CANTRCV_30_SBC_HW_PN_SUPPORT */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_MainFunction
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least index;
  
  /* ----- Implementation ----------------------------------------------- */
  /* \trace SPEC-15067, SPEC-15085 */
  /* #100 Run through all transceiver channels. */
  for(index = 0; index < CANTRCV_30_SBC_MAX_CHANNEL; ++index)
  {
    if (CanTrcvCfg_IsChannelUsed(index))
    {
      if(CanTrcv_30_Sbc_Prob[index].isInit == CANTRCV_30_SBC_IS_INIT)
      {
        /* #200 Execute only if transceiver channel is active and initialized. */
        CanTrcv_30_Sbc_TrcvModeType currentOpMode;

        (void)CanTrcv_30_Sbc_GetOpMode((uint8)index, &currentOpMode); /* SBSW_CANTRCV_HL_SBC_3 */

        /* #300 Execute only if transceiver channel is in power-down mode (STANDBY / SLEEP). (only DIO- or SBC-interface) */
        if (currentOpMode != CANTRCV_30_SBC_OP_MODE_NORMAL)
        {
#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) && (CANTRCV_30_SBC_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_SBC_WAKEUP_POLLING) 
          if (CanTrcvCfg_IsWakeupByBusUsed(index)) /* COV_CANTRCV_HL_SBC_CODECOV_IS_WU_BY_BUS_USED */
          {
            {
              /* #210 Transceiver channel is in power-down mode (STANDBY / SLEEP) and has wake-up support enabled: Check if a wake-up event occurred. (critical section used) */
              Std_ReturnType retval = E_NOT_OK;

              CanTrcv_TrcvWakeupReasonType wakeupReason = CANTRCV_30_SBC_WU_ERROR;

              CanTrcv_EnterCritical();
              /* #430 Determine whether a wake-up event occurred or NOT from status flags read via SPI. (only SPI- / SBC-interface) */
              /* Check for status bits */
              {
                 /* #440 If NO most current status flags are available, request them via SPI. (only SPI-interface) */

                 /* No request pending.. its safe to request diagnostic registers here..
                 * unread data will be marked as dirty. This request may be
                 * interrupted by any other request..
                 */
                retval = CanTrcv_30_Sbc_Hw_ReadStatus(CanTrcvCfg_GetMappingID(index), &CanTrcv_30_Sbc_Prob[index].statusFlags); /* SBSW_CANTRCV_LL_SBC_1 */
              }
              if (retval == E_OK)
              {

                /* #460 If most current flags are available process them and if any wake-up event occurred determine the wake-up reason (BY_SYSERR (only PN), BY_BUS or BY_PIN). (only SPI- or SBC-interface) */
#  if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
                if ((CanTrcv_30_Sbc_Prob[index].pnAvailable == TRUE) && (CanTrcv_30_Sbc_Prob[index].isPnEnabled == TRUE) &&
                    (CanTrcv_30_Sbc_StateErrIsSys(CanTrcv_30_Sbc_Prob[index].statusFlags)))
                {
                  wakeupReason = CANTRCV_30_SBC_WU_BY_SYSERR;
                }
                else
#  endif
                if (CanTrcv_30_Sbc_StateWupIsBus(CanTrcv_30_Sbc_Prob[index].statusFlags))
                {
                  wakeupReason = CANTRCV_30_SBC_WU_BY_BUS;
                }
                else
                {
                  /* Nothing */
                }

                retval = E_OK;
              }

              if (retval == E_NOT_OK) /* PRQA S 3356,3359 */ /* MD_CanTrcv_30_Sbc_13.7 */
              { /* PRQA S 3201 */ /* MD_CanTrcv_30_Sbc_3201 */
                /* #470 If the check for wake-up events fails, report error. (only SPI- / SBC-interface) */
                CanTrcv_ReportErrorNoTrcvControl(CANTRCV_30_SBC_MAINFUNCTION_ID);
              }

              if (wakeupReason != CANTRCV_30_SBC_WU_ERROR)
              {
                /* #500 If any wake-up event detected, store the wake-up event. */
                CanTrcv_30_Sbc_Prob[index].wakeUpReason = wakeupReason; /* SBSW_CANTRCV_HL_SBC_1 */

                if (CanTrcv_30_Sbc_Prob[index].wakeUpReport == CANTRCV_30_SBC_WU_ENABLE)
                {
                  /* #510 If any wake-up event detected and wake-up detection is enabled, inform the EcuM to check for wake-up event(s). */
                  EcuM_CheckWakeup( CanTrcvCfg_GetWakeupSource(index) );
                }
              }

#  if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_OFF)
              CANTRCV_30_SBC_DUMMY_STATEMENT(retval);
#  endif
              CanTrcv_LeaveCritical();
            } /* (!CanTrcv_30_Sbc_IsReqFlagPnd(index)) */
          }
# endif /* (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) */
        } /* CanTrcv_30_Sbc_Prob[index].curOpMode != CANTRCV_30_SBC_OP_MODE_NORMAL */
      } /* CanTrcv_30_Sbc_Prob[index].isInit != CANTRCV_30_SBC_IS_INIT */
    } /*  CanTrcvCfg_IsChannelUsed(index)  */
  } /* for ... */
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */




#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetPNActivationState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetPNActivationState(CanTrcv_30_Sbc_PNActivationType ActivationState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_OK;
  uint8_least index, numberOfConfigurationChanges;

  numberOfConfigurationChanges = 0;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 Run through all transceiver channels. */
  for(index=0; index < CANTRCV_30_SBC_MAX_CHANNEL; index++)
  {
    if (CanTrcvCfg_IsChannelUsed(index))
    {
      /* #200 Do execute only if transceiver channel is active. */
# if (CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON)
      /* #10 Check if transceiver channel is initialized. */
      if (CanTrcv_30_Sbc_Prob[index].isInit != CANTRCV_30_SBC_IS_INIT)
      {
        /* \trace SPEC-20019 */
        CanTrcv_DetReportError(CANTRCV_30_SBC_SETPNACTIVATIONSTATE_ID, CANTRCV_30_SBC_E_UNINIT);
        retval = E_NOT_OK;
      }
# endif
      if (CanTrcvCfg_IsPnEnabled(index))
      {
        /* #210 Transceiver channel has enabled PN functionality: Adapt the setting of PN functionality according to ActivationState. */
        if (ActivationState == CANTRCV_30_SBC_PN_ENABLED)
        {
          CanTrcv_30_Sbc_Prob[index].isPnEnabled = TRUE; /* SBSW_CANTRCV_HL_SBC_1 */
        }
        else
        {
          CanTrcv_30_Sbc_Prob[index].isPnEnabled = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
        }

        ++numberOfConfigurationChanges;
      }
      else
      {
        /* #220 Transceiver channel has DISABLED PN functionality: Set PN functionality to DISABLED. */
        CanTrcv_30_Sbc_Prob[index].isPnEnabled = FALSE; /* SBSW_CANTRCV_HL_SBC_1 */
      }
    } /* IsChannelUsed */
  } /* for ... */

  if (numberOfConfigurationChanges == 0)
  {
    /* #230 If no PN functionality was adapted according to ActivationState at all return E_NOT_OK. */
    retval = E_NOT_OK;
  }

  return retval;
}
#endif /* CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON */






#if (CANTRCV_30_SBC_WAKEUP_BY_BUS_USED == STD_ON) || \
    (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReportWakeup
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_SBC_LOCAL_INLINE FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReportWakeup(uint8 CanTrcvIndex)
{
  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 If any wake-up event occurred, report it to EcuM. */
  /* #110 Depending on configuration report to EcuM the wake-up source which belongs to occurred wake-up reason (POWER_ON, BY_SYSERR (only PN), BY_BUS, BY_PIN). */
  switch(CanTrcv_30_Sbc_Prob[CanTrcvIndex].wakeUpReason)
  {
#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) 
  case CANTRCV_30_SBC_WU_BY_SYSERR:
# if (CANTRCV_30_SBC_USE_EXTENDED_WU_SRC == STD_ON) 
    /* \trace SPEC-15081, SPEC-46898 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSourceSyserr(CanTrcvIndex) );
    break;
# endif
#endif
  case CANTRCV_30_SBC_WU_BY_BUS:
    /* \trace SPEC-14953 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) );
    break;

  default:
    /* No valid or an internal wakeup. Do not report this as wakeup event */
    break;
  }
}
#endif




#define CANTRCV_30_SBC_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* **************************************************************************/
/*  MISRA deviations                                                        */
/* **************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_CanTrcv_30_Sbc_0715:
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_CanTrcv_30_Sbc_0777:
  Reason: ASR requires that all externals and APIs have the format <Msn>_<xyz>, while <Msn> has the
          format <BswmModuleName>_<VendorId>_<VendorApiInfix> for external hardware. Because of this
          requirement the first chars are same for all external declartations.
  Risk: Non-conforming Code.
  Prevention: Multiple configuration aspects used in component test.

MD_CanTrcv_30_Sbc_0779
  Reason: Code which is much better and easier to maintain.
  Risk: Compiler and preprocessor do not support identifiers with more than 31 characters.
  Prevention: Test of software with real compiler and preprocessor on real MCU-target.

MD_CanTrcv_30_Sbc_13.7:
  Reason: Result or value is always true or false depend on configuration aspect and used HW specific implementation
  Risk: Incorrect value return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanTrcv_30_Sbc_3201:
  Reason: For some configuration variants code may be unreachable.
  Risk: Code is not executed.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanTrcv_30_Sbc_8.7:
  Reason: Definition of CanIfState in global section because of better over-view.
  Risk: Name conflict.
  Prevention: Check for name conflicts.

MD_CanTrcv_30_Sbc_3673:
  Reason: Depending on the configuration the feature may be unsupported by the underlying CanTrcv hardware.
  Risk: None.
  Prevention: None.

MD_CanTrcv_30_Sbc_3408:
  Reason: Some local variables are declared without static declaration to allow better debugging.
  Risk: Name conflict.
  Prevention: All external variables are prefixed with <Msn>

MD_CanTrcv_30_Sbc_3448:
  Reason: Variables are declared with external linkage in order to allow XCP debugging. These must not be accessed
          from outside. So the types shall remain internal.
  Risk: None.
  Prevention: None.

 MD_CanTrcv_30_Sbc_335X:
  Reason: Caused by High-level Low-level concept of CAN transceiver driver while the High-level must offer maximum flexibility for the Low-level.
          This concept may lead to fact that NOT every condition may be stimulated / required by the Low-level.
  Risk: Code is not executed.
  Prevention: Every High-level + Low-level is tested and reviewed separately.


*/


/* **************************************************************************/
/*  SILENT justifications                                                   */
/* **************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CANTRCV_HL_SBC_1
\DESCRIPTION The variable "CanTrcv_30_Sbc_Prob[]" must be accessed with index which is < CANTRCV_30_SBC_MAX_CHANNEL. 
\COUNTERMEASURE \N In case of an internal access initiated by the CanTrcv-driver itself this is ensured by the driver itself. The internal
access index is generated by a FOR-loop-count-index which runs from "0" until "CANTRCV_30_SBC_MAX_CHANNEL-1".
In case of an external access initiated by an upper layer e.g. CanIf this is ensured if CANTRCV_30_SBC_DEV_ERROR_DETECT == STD_ON.


\ID SBSW_CANTRCV_HL_SBC_2
\DESCRIPTION Write access to a pointer passed by an upper layer e.g. CanIf. Source data is of the same type as the destination data.
\COUNTERMEASURE \N The caller ensures that a valid pointer is passed. By the way compiler ensures that no memory violation occurs.


\ID SBSW_CANTRCV_HL_SBC_3
\DESCRIPTION Function call with passed pointer as parameter.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid pointer is passed. By the way the compiler ensures that no memory violation occurs.


\ID SBSW_CANTRCV_HL_SBC_4
\DESCRIPTION Function pointer call.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid function pointer is used. Used function pointer is retrieved from a constant table which is NOT generated. 
                   By the way the compiler ensures that no memory violation occurs.


\ID SBSW_CANTRCV_LL_SBC_1
  \DESCRIPTION The function CanTrcv_30_Sbc_Hw_ReadStatus is called with a pointer to 
               global variable CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags as parameter.
  \COUNTERMEASURE \N It must be ensured that the address of CanTrcv_30_Sbc_Prob[CanTrcvIndex].statusFlags is valid.
        This means that the array index must be secured.
        The array element is identified by CanTrcvIndex, the array is limited by the define CANTRCV_30_SBC_MAX_CHANNEL.
        In the API CanTrcv_30_Sbc_MainFunction and CanTrcv_30_Sbc_Init the CanTrcvIndex is secured
        by the for loop (from zero to CANTRCV_30_SBC_MAX_CHANNEL).
        For all other APIs in which this function is called the CanTrcvIndex is secured by a DET check with
        errorId CANTRCV_30_SBC_E_INVALID_CAN_NETWORK.

SBSW_JUSTIFICATION_END */


/* **************************************************************************/
/*  COVERAGE justifications                                                 */
/* **************************************************************************/
/* START_COVERAGE_JUSTIFICATION


\ID COV_CANTRCV_HL_SBC_VARCOV_AVOID_COREVER_REDEF
  \ACCEPT TX
  \REASON Avoids the re-definition of CORE-version in case of multiple CanTrcv-driver are used. Hence decision "F" can NOT be fulfilled. Correct functionality is ensured by code-review.


\ID COV_CANTRCV_HL_SBC_CODECOV_NOT_EACH_CONFIG
  \ACCEPT XF
  \REASON The stimulation is not possible in each configuration. It will be ensured by inspection that both decisions are covered
          in at least one configuration. In addition correct functionality is verified by code review.


\ID COV_CANTRCV_HL_SBC_CODECOV_DEFENSIVE_CODING_STYLE
  \ACCEPT TX
  \REASON The code is required due to HL-LL-concept and in order to prevent malfunctions in case of programming of LL. 
          Hence the stimulation is not possible in case of correct programming of LL. The correct functionality is verified by code review.


\ID COV_CANTRCV_HL_SBC_CODECOV_IS_WU_BY_BUS_USED
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Condition / decision not covered by automatic tests. Affected code has low complexity because no else-path is available. 
          The code is verified by code inspection.


\ID COV_CANTRCV_HL_SBC_CODECOV_OP_MODE_REQ_NONE
  \ACCEPT TF tf tx
  \REASON Condition not covered by automatic tests but both decisions are covered. Affected code has low complexity. 
          The code is verified by code inspection.



\ID COV_CANTRCV_HL_LL_SBC_CODECOV_WU_POWER_ON
  \REASON Generally all condition-decision variants are covered.

\ID COV_CANTRCV_HL_LL_SBC_VARCOV_SW_FEAT_NOT_SUPPORTED
  \ACCEPT TX tx xf
  \ACCEPT TF tf xf
  \ACCEPT XF
  \ACCEPT TX
  \REASON Post-build loadable is not supported by this driver.

\ID COV_CANTRCV_HL_LL_SBC_CODECOV_INVALID_GENDATA
  \ACCEPT XF xf xf tx xx
  \ACCEPT TX
  \REASON Not all condition-decision variants can be stimulated, because therefore the generated data must be manipulated which is NOT applicable.
          Correct functionality is ensured by code-review.

\ID COV_CANTRCV_HL_LL_SBC_CODECOV_HW_SPECIFIC
  \ACCEPT XF
  \REASON Depending on used HW and due to HL-LL-concept NOT all condition-decision variants can be stimulated.
          Correct functionality is ensured by code-review.



END_COVERAGE_JUSTIFICATION */ 

/* ********************************************************************************************************************
 *  END OF FILE
 * *******************************************************************************************************************/
