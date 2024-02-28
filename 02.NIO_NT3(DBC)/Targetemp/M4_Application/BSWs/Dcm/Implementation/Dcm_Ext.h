/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_Ext.h
 *         \unit  NoUnit
 *        \brief  Public interface of DCM extensions for other components
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/* *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author     Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-08-20                           No relevant changes
 *  01.01.00  2012-09-20                           No relevant changes
 *  01.01.01  2012-10-12                           No relevant changes
 *  01.02.00  2013-01-31                           No relevant changes
 *  01.03.00  2013-04-17                           No relevant changes
 *  01.03.01  2013-05-28                           No relevant changes
 *  01.04.00  2013-06-17                           No relevant changes
 *  01.05.00  2013-07-26                           No relevant changes
 *  02.00.00  2013-07-18  vissa      ESCAN00068413 AR4-462: Support of GM Diagnostic specification(s)
 *                        vissa      ESCAN00068551 AR4-231: Implement ROE according to GM norms
 *  02.00.01  2013-12-05  vissa      ESCAN00071467 Dcm causes DET invocation in DEM during ECU power down phase
 *                        vissa      ESCAN00072154 Compiler warning: Dcm does not always use the compiler abstraction for pointers
 *                        vissa      ESCAN00072524 SID 0x86: No RoE responses on multi protocol configurations with enabled declined second request feature
 *                        vissa      ESCAN00072530 SID 0x86: Compiler optimized session specific context switch
 *  02.01.00  2013-12-03                           No relevant changes
 *  02.02.00  2014-04-11                           No relevant changes
 *  02.02.01  2014-07-31                           No relevant changes
 *  02.02.02  2014-08-11                           No relevant changes
 *  03.00.00  2014-10-30  vissa      ESCAN00078136 Diagnostic client cannot communicate with the ECU
 *  03.01.00  2014-11-11                           No relevant changes
 *  04.00.00  2015-01-30                           No relevant changes
 *  04.01.00  2015-04-07                           No relevant changes
 *  04.01.01  2015-09-10                           No relevant changes
 *  05.00.00  2015-11-27                           No relevant changes
 *  05.01.00  2016-02-28  vissat     ESCAN00087636 FEAT-1472: Implement Service 0x86 (RoE)
 *  05.02.00  2016-04-07                           No relevant changes
 *  07.00.00  2016-05-02  vissat     ESCAN00090614 Service 0x86: No RoE message is sent
 *  07.01.00  2016-09-22                           No relevant changes
 *  07.02.00  2017-01-03                           No relevant changes
 *  08.00.00  2017-04-04                           No relevant changes
 *  08.01.00  2017-04-19                           No relevant changes
 *  08.02.00  2017-05-19                           No relevant changes
 *  08.03.00  2017-06-19                           No relevant changes
 *  08.04.00  2017-07-13                           No relevant changes
 *  08.05.00  2017-08-07                           No relevant changes
 *  08.06.00  2017-09-20                           No relevant changes
 *  09.00.00  2017-10-25                           No relevant changes
 *  09.01.00  2017-11-06                           No relevant changes
 *  09.02.00  2017-11-29                           No relevant changes
 *  09.03.00  2018-01-05                           No relevant changes
 *  09.04.00  2018-01-23  visahe     STORYC-3192   DCM: RoE - Release
 *  09.05.00  2018-02-19                           No relevant changes
 *  10.00.00  2018-03-29                           No relevant changes
 *  10.01.00  2018-05-09                           No relevant changes
 *  10.02.00  2018-06-14                           No relevant changes
 *  10.03.00  2018-07-09                           No relevant changes
 *  10.04.00  2018-08-06                           No relevant changes
 *  11.00.00  2018-09-03                           No relevant changes
 *  11.01.00  2018-10-01                           No relevant changes
 *  11.02.00  2018-10-26                           No relevant changes
 *  11.03.00  2018-11-23                           No relevant changes
 *  11.04.00  2018-12-20                           No relevant changes
 *  11.05.00  2019-01-18  visahe     STORY-6107    Parallel OBD/UDS protocol processing - Multi thread handling
 *  11.06.00  2019-02-18                           No relevant changes
 *  12.00.00  2019-03-15                           No relevant changes
 *  12.01.00  2019-04-15                           No relevant changes
 *  12.02.00  2019-05-13                           No relevant changes
 *  12.03.00  2019-06-11                           No relevant changes
 *  12.04.00  2019-07-08                           No relevant changes
 *  12.05.00  2019-08-02                           No relevant changes
 *  13.00.00  2019-08-30                           No relevant changes
 *  13.01.00  2019-09-27                           No relevant changes
 *  13.02.00  2019-10-25                           No relevant changes
 *  13.03.00  2019-11-22                           No relevant changes
 *  13.04.00  2020-01-16                           No relevant changes
 *  13.05.00  2020-02-14                           No relevant changes
 *  14.00.00  2020-03-13                           No relevant changes
 *  14.01.00  2020-04-20                           No relevant changes
 *  14.02.00  2020-05-11                           No relevant changes
 *  14.03.00  2020-06-05                           No relevant changes
 *  14.04.00  2020-06-26                           No relevant changes
 *  14.05.00  2020-08-03                           No relevant changes
 *  15.00.00  2020-08-31                           No relevant changes
 *  15.01.00  2020-10-01                           No relevant changes
 *  15.02.00  2020-10-23                           No relevant changes
 *  15.03.00  2020-10-29                           No relevant changes
 *  15.04.00  2020-11-23                           No relevant changes
 *  15.05.00  2020-11-23  visahe     DCM-2594      Service 0x86: Support new start/stop behavior according to ISO14229-1:2020
 *                        visvkr     DCM-3638      Service 0x86: Support new start/stop behavior according to ISO14229-1:2020 - Part II
 *  15.06.00  2020-12-22                           No relevant changes
 *  15.07.00  2021-01-21  visvkr     DCM-3696      Service 0x86: Adapt sub-function 0x03 to ISO 14229-1 (2020)
 *                        visvkr     DCM-3698      Service 0x86: Adapt sub-function 0x01 to ISO 14229-1 (2020)
 *  15.08.00  2021-02-15  visvkr     DCM-2597      Service 0x86: Support multiple events for sub-function 0x03
 *  16.00.00  2021-03-15                           No relevant changes
 *  16.01.00  2021-04-12                           No relevant changes
 *  16.02.00  2021-05-07                           No relevant changes
 *  16.03.00  2021-06-02                           No relevant changes
 *  16.04.00  2021-07-05  visvkr     DCM-4560      Service 0x86: Support STRT 0x19 for sub-function 0x01
 *                        visvkr     ESCAN00109790 Compiler error: Parse error near 'Dcm_NegativeResponseCodeType'
 *  16.05.00  2021-08-02  visvkr     DCM-4562      Service 0x86: Support STRT 0x22 with any DID for sub-function 0x03
 *  17.00.00  2021-08-26                           No relevant changes
 *  17.01.00  2021-09-27  visvkr     DCM-5011      Service 0x86: Update to revised version of ISO 14229-1 (2020)
 *  17.02.00  2021-10-22                           No relevant changes
 *  17.03.00  2021-11-19                           No relevant changes
 *  17.04.00  2021-12-20  visahe     DCM-2601      Service 0x86: Support sub-function 0x07
 *                        visvkr     DCM-4564      Service 0x86: Support NvM storage
 *  17.05.00  2022-02-16                           No relevant changes
 *********************************************************************************************************************/
#if !defined(DCM_EXT_H)
# define DCM_EXT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/*! Maximum allowed STRT length for subfunction 0x01 (maximum request length of service 0x19) */
#  define DCM_SVC_86_01_MAX_SUPPORTED_STRT_LENGTH                    7u

/*! Maximum allowed STRT length for subfunction 0x03 (maximum request length of service 0x22: SID + 2 * NumOfDIDs) */
#  define DCM_SVC_86_03_MAX_SUPPORTED_STRT_LENGTH                    (1u + (2u * DCM_SVC_22_MAX_DID_LIST_LEN))

/*! Maximum allowed STRT length for subfunction 0x07 (maximum request length of service 0x22: SID + 2 * NumOfDIDs) */
#  define DCM_SVC_86_07_MAX_SUPPORTED_STRT_LENGTH                    (1u + (2u * DCM_SVC_22_MAX_DID_LIST_LEN))
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/*! Record for event management of subfunction 0x01 */
struct DCM_SVC86DTCRECORDTYPE_TAG
{
  uint8 STRT[DCM_SVC_86_01_MAX_SUPPORTED_STRT_LENGTH]; /*!< The serviceToRespondToRecord */
  uint8 STRTLength;                                    /*!< The length of the serviceToRespondToRecord */
  uint8 DTCStatusMask;                                 /*!< DTCStatusMask of the eventTypeRecord */
};
typedef struct DCM_SVC86DTCRECORDTYPE_TAG Dcm_Svc86DtcRecordType;
#  endif

#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/*! Record of a single DID event of subfunction 0x03 */
struct DCM_SVC86ONDIDCHANGEDIDRECORDTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType   DidInfoContext;                                  /*!< Information about the scheduled DID */
  uint8                          STRT[DCM_SVC_86_03_MAX_SUPPORTED_STRT_LENGTH];   /*!< The serviceToRespondToRecord */
  uint8                          STRTLength;                                      /*!< The length of the serviceToRespondToRecord */
  Dcm_Svc86DidReferenceStateType RefState;                                        /*!< Status of the DID reference */
  Dcm_MsgItemType                RefDidData[DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH]; /*!< Last read DID data */
};
typedef struct DCM_SVC86ONDIDCHANGEDIDRECORDTYPE_TAG Dcm_Svc86OnDidChangeDidRecordType;
typedef P2VAR(Dcm_Svc86OnDidChangeDidRecordType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc86OnDidChangeDidRecordPtrType;
#  endif

#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/*! Record of a single DID event of subfunction 0x07 */
struct DCM_SVC86ONCOMPOFVALDIDRECORDTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType  DidInfoContext;                                  /*!< Information about the scheduled DID */
  uint32                        RawRefCompVal;                                   /*!< Raw reference value */
  uint16                        Offset;                                          /*!< Start bit number offset within the Did */
  Dcm_MsgItemType               RefDidData[DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH]; /*!< Last read DID data */
  uint8                         STRT[DCM_SVC_86_07_MAX_SUPPORTED_STRT_LENGTH];   /*!< The serviceToRespondToRecord */
  uint8                         STRTLength;                                      /*!< The length of the serviceToRespondToRecord */
  uint8                         BitLength;                                       /*!< Length of compared Did values */
  uint8                         ComparisonLogic;                                 /*!< Logic of the comparison method of a DID */
  uint8                         HysteresisPercentage;                            /*!< Percentage of the acceptable deviation between comparison and measured values */
  boolean                       Signedness;                                      /*!< Sign of the comparison (signed or unsigned) */
  boolean                       TriggerActive;                                   /*!< Trigger if Hysteresis limit is reached or not */
};
typedef struct DCM_SVC86ONCOMPOFVALDIDRECORDTYPE_TAG Dcm_Svc86OnCompOfValDidRecordType;
typedef P2VAR(Dcm_Svc86OnCompOfValDidRecordType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc86OnCompOfValDidRecordPtrType;
#  endif

#  if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/*! Information about event records for Service 0x86 subfunction 0x01 */
struct DCM_SVC86ONDTCCHANGEEVENTRECORDTYPE_TAG
{
  Dcm_Svc86DtcRecordType  DtcRecord;                                          /*!< Record for DTC events */
  Dcm_Svc86EventStateType DtcEventState;                                      /*!< Status of the DTC event */
};
typedef struct DCM_SVC86ONDTCCHANGEEVENTRECORDTYPE_TAG Dcm_Svc86OnDtcChangeEventRecordType;
#  endif

#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/*! Information about event records for Service 0x86 subfunction 0x03 */
struct DCM_SVC86ONDIDCHANGEEVENTRECORDTYPE_TAG
{
  Dcm_Svc86OnDidChangeDidRecordType  DidRecord[DCM_SVC_86_MAX_NUM_CHANGE_OF_DID_EVENTS]; /*!< Records for DID events for subfunction 0x03 */
  uint8                              NumDidRecords;                                      /*!< Number of DID records */
};
typedef struct DCM_SVC86ONDIDCHANGEEVENTRECORDTYPE_TAG Dcm_Svc86OnDidChangeEventRecordType;
#  endif

#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/*! Information about event records for Service 0x86 subfunction 0x07 */
struct DCM_SVC86ONCOMPOFVALEVENTRECORDTYPE_TAG
{
  Dcm_Svc86OnCompOfValDidRecordType  DidRecord[DCM_SVC_86_MAX_NUM_COMPARISON_OF_VALUE_EVENTS]; /*!< Records for DID events for subfunction 0x07 */
  uint8                              NumDidRecords;                                            /*!< Number of DID records */
};
typedef struct DCM_SVC86ONCOMPOFVALEVENTRECORDTYPE_TAG Dcm_Svc86OnCompOfValEventRecordType;
#  endif

/*! Information about event records */
struct DCM_SVC86EVENTRECORDTYPE_TAG
{
#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86OnCompOfValEventRecordType OnCompOfVal;  /*!< Event records for sub-function 0x07 */
#  endif

#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86OnDidChangeEventRecordType OnDidChange;  /*!< Event records for sub-function 0x03 */
#  endif

#  if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86OnDtcChangeEventRecordType OnDtcChange;  /*!< Event records for sub-function 0x01 */
#  endif
};
typedef struct DCM_SVC86EVENTRECORDTYPE_TAG Dcm_Svc86EventRecordType;

/*! Information used for block size calculation of NvM RoE storage */
struct DCM_EXTSVC86NVMDATATYPE_TAG
{
  Dcm_Svc86EventRecordType           EventRecord;    /*!< General event record set up */
  uint16                             ClientSrcAddr;  /*!< The testers source identifier */
#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
  uint16                             MagicNumber;    /*!< Magic number for configuration verification */
#   if (DCM_VARMGR_MULTI_SVC_EXCLUSIVE_ENABLED == STD_ON)
  Dcm_CfgVarMgrDiagVariantIdMemType  CfgVariantId;   /*!< Contains the CFG-criteria ID */
#   endif
#  endif
  PduIdType                          RxPduId;        /*!< Id of connection currently requesting RoE */
  Dcm_Svc86RoeStateType              RoEState;       /*!< Whether the event logic is activated or not */
};
typedef struct DCM_EXTSVC86NVMDATATYPE_TAG Dcm_ExtSvc86NvMDataType;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemTriggerOnDTCStatus()
 *********************************************************************************************************************/
/*! \brief          Notifies DCM RoE handler for a DTC status change.
 *  \details        Triggers a ROE event for sub-service OnDTCStatusChanged if the requested DTCStatusMask is matched.
 *  \param[in]      DTC               This is the DTC the change is assigned to
 *  \param[in]      DTCStatusOld      DTC status before change
 *  \param[in]      DTCStatusNew      DTC status after change
 *  \return         DCM_E_OK          This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SVC_86_01_SUPPORT_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew
  );
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
extern VAR(Dcm_ExtSvc86NvMDataType, DCM_VAR_NOINIT) Dcm_Svc86NvMData;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DCM_START_SEC_CONST_UNSPECIFIED
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
extern CONST(Dcm_ExtSvc86NvMDataType, DCM_CONST) Dcm_Svc86DefaultNvMData;
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CONST_UNSPECIFIED
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_EXT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Ext.h
 *********************************************************************************************************************/
