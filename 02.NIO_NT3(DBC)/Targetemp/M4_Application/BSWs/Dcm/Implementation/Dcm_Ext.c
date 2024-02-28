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
/**        \file  Dcm_Ext.c
 *         \unit  NoUnit
 *        \brief  Implementation of DCM extensions
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define DCM_EXT_SOURCE

#ifdef __PRQA__                                                                                                                                      /* COV_DCM_UNSUPPORTED XF */
# pragma PRQA_MACRO_MESSAGES_OFF "Dcm_UtiGetReqData" 2985 /* MD_Dcm_Redundant_2985 */
                                                                                                                                                     /* PRQA S 2991 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2992 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2995 EOF */ /* MD_Dcm_ConstExpr */
                                                                                                                                                     /* PRQA S 2996 EOF */ /* MD_Dcm_ConstExpr */
#endif
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_TskMgrInt.h"
#if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
# include "NvM.h"
#endif /* (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON) */
#include "Dcm_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (DCM_EXTENSION_ID != 0x96ACD543u)
# error "Mismatching OEMs between static and generated code"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/*! States of the RoE service handler */
# define DCM_SVC86_ROE_STATE_STOPPED                                 ((Dcm_Svc86RoeStateType)0x00)
# define DCM_SVC86_ROE_STATE_STARTED                                 ((Dcm_Svc86RoeStateType)0x01)
# define DCM_SVC86_ROE_STATE_STARTED_PERSISTENTLY                    ((Dcm_Svc86RoeStateType)0x02)

/*! Event setup states */
# define DCM_SVC86_EVENT_STATE_CLEARED                               ((Dcm_Svc86EventStateType)0x00u)
# define DCM_SVC86_EVENT_STATE_ACTIVE                                ((Dcm_Svc86EventStateType)0x01u)

/*! DID reference states */
# define DCM_SVC86_DID_REFERENCE_STATE_INVALID                       ((Dcm_Svc86DidReferenceStateType)0x00u)
# define DCM_SVC86_DID_REFERENCE_STATE_VALID                         ((Dcm_Svc86DidReferenceStateType)0x01u)

/*! Service 0x86 0x03 sub-repeater IDs */
# define DCM_SVC86_03_SUBPROGRESS_INITIAL                            ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 0u)
# define DCM_SVC86_03_SUBPROGRESS_DIDLOOKUP                          ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 1u)
# define DCM_SVC86_03_SUBPROGRESS_DIDCHECKCONDITIONS                 ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 2u)
# define DCM_SVC86_03_SUBPROGRESS_DIDGETLENGTH                       ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 3u)

/*! Service 0x86 0x05 sub-repeater IDs */
# define DCM_SVC86_05_SUBPROGRESS_INITIAL                            ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 0u)
# define DCM_SVC86_05_SUBPROGRESS_UPDATE_NVM                         ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 1u)

/*! Service 0x86 0x07 sub-repeater IDs */
# define DCM_SVC86_07_SUBPROGRESS_INITIAL                            ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 0u)
# define DCM_SVC86_07_SUBPROGRESS_DIDLOOKUP                          ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 1u)
# define DCM_SVC86_07_SUBPROGRESS_DIDCHECKCONDITIONS                 ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 2u)
# define DCM_SVC86_07_SUBPROGRESS_DIDGETLENGTH                       ((Dcm_RepeaterProgressType)DCM_REPEATER_PROGRESS_INITIAL + 3u)

/*! Event window time values */
# define DCM_SVC86_EWT_INFINITE                                      0x02u

/*! Indication that no DID event has occured yet */
# define DCM_SVC86_DID_EVENT_NO_WINNER                               DCM_SVC_86_MAX_NUM_CHANGE_OF_DID_EVENTS

/*! Comparison logic parameters for subfunction 0x07 */
# define DCM_SVC_86_07_COMPARISON_LESS_THAN_MEASURED                 (1u)
# define DCM_SVC_86_07_COMPARISON_MORE_THAN_MEASURED                 (2u)
# define DCM_SVC_86_07_COMPARISON_EQUAL_MEASURED                     (3u)
# define DCM_SVC_86_07_COMPARISON_UNEQUAL_MEASURED                   (4u)

/*! Maximum allowed STRT length for subfunction 0x07 (maximum request length of service 0x22: SID + 2 * NumOfDIDs) */
# define DCM_SVC_86_07_MAX_SUPPORTED_STRT_LENGTH                     (1u + (2u * DCM_SVC_22_MAX_DID_LIST_LEN))

/*! Maximum allowed Buffer size for comparing Data for subfunction 0x07 */
# define DCM_SVC_86_07_MAX_SUPPORTED_COMPARE_LENGTH                  ((128u) + (DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH))

/*! Mapping of current session context to NvM data. The context of any non-default session will never be stored into NvM */
# define Dcm_Svc86CurrentSession                                     Dcm_Svc86NvMData
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/*! Service 0x86 subfunction 0x03 scheduler data */
struct DCM_SVC86ONDIDCHANGESCHEDULERTYPE_TAG
{
  Dcm_DidMgrDidOpTypeContextType DidOpTypeContext;                            /*!< Information about operations on current DID */
  Dcm_MsgItemType                Buffer[DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH]; /*!< Buffer for reading the DID data during scheduling */
  Dcm_MsgLenType                 ReadIndex;                                   /*!< Number of bytes that were already read */
  Dcm_OpStatusType               OpStatus;                                    /*!< Current operation status */
  uint8                          DidIndex;                                    /*!< Scheduler table entry that is currently processed */
  uint8                          DidIndexWinner;                              /*!< Index to scheduler table entry of the first detected event */
};
typedef struct DCM_SVC86ONDIDCHANGESCHEDULERTYPE_TAG Dcm_Svc86OnDidChangeSchedulerType;
# endif

/*! Service 0x86 subfunction 0x07 scheduler data */
# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
struct DCM_SVC86ONCOMPOFVALSCHEDULERTYPE_TAG
{
  Dcm_DidMgrDidOpTypeContextType DidOpTypeContext;                            /*!< Information about operations on current DID */
  Dcm_MsgItemType                Buffer[DCM_SVC_86_07_MAX_SUPPORTED_COMPARE_LENGTH]; /*!< Buffer for reading the DID data during scheduling */
  Dcm_MsgLenType                 ReadIndex;                                   /*!< Number of bytes that were already read */
  Dcm_OpStatusType               OpStatus;                                    /*!< Current operation status */
  uint8                          DidIndex;                                    /*!< Scheduler table entry that is currently processed */
  uint8                          DidIndexWinner;                              /*!< Index to scheduler table entry of the first detected event */
};
typedef struct DCM_SVC86ONCOMPOFVALSCHEDULERTYPE_TAG Dcm_Svc86OnCompOfValSchedulerType;
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/*! Service 0x86 scheduler data */
struct DCM_SVC86SCHEDULERTYPE_TAG
{
#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86OnCompOfValSchedulerType OnCompOfVal;  /*!< Service 0x86 subfunction 0x07 scheduler data */
#  endif
#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86OnDidChangeSchedulerType OnDidChange;  /*!< Service 0x86 subfunction 0x03 scheduler data */
#  endif
};
typedef struct DCM_SVC86SCHEDULERTYPE_TAG Dcm_Svc86SchedulerType;
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03GetDidRecord()
 *********************************************************************************************************************/
/*! \brief          Returns a pointer to a Did record of the given index.
 *  \details        -
 *  \param[in]      index    Index to a Did record
 *  \return         The Did record
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_Svc86OnDidChangeDidRecordPtrType, DCM_CODE) Dcm_Svc86_03GetDidRecord(
  uint8_least index
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07GetDidRecord()
 *********************************************************************************************************************/
/*! \brief          Returns a pointer to a Did record of the given index.
 *  \details        -
 *  \param[in]      index    Index to a Did record
 *  \return         The Did record
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_Svc86OnCompOfValDidRecordPtrType, DCM_CODE) Dcm_Svc86_07GetDidRecord(
  uint8_least index
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86EventRecordInit()
 *********************************************************************************************************************/
/*! \brief          Initializes all event records.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86EventRecordInit(
  void
  );
# endif

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnDTCStatusChange()
 *********************************************************************************************************************/
/*! \brief          Tries to send ServiceToRespondTo for onDTCStatusChange.
 *  \details        -
 *  \return         DCM_E_OK        Trigger of STRT was successful
 *  \return         DCM_E_NOT_OK    Trigger of STRT was not successful
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnDTCStatusChange(
  void
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnChangeOfDid()
 *********************************************************************************************************************/
/*! \brief          Tries to send ServiceToRespondTo for onChangeOfDataIdentifier.
 *  \details        -
 *  \return         DCM_E_OK        Trigger of STRT was successful
 *  \return         DCM_E_NOT_OK    Trigger of STRT was not successful
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnChangeOfDid(
  void
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnComparisonOfValues()
 *********************************************************************************************************************/
/*! \brief          Tries to send ServiceToRespondTo for OnComparisonOfValues.
 *  \details        -
 *  \return         DCM_E_OK        Trigger of STRT was successful
 *  \return         DCM_E_NOT_OK    Trigger of STRT was not successful
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnComparisonOfValues(
  void
  );
# endif

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnDTCStatusChange()
 *********************************************************************************************************************/
/*! \brief          Processes task events related to onDTCStatusChange
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnDTCStatusChange(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerSample()
 *********************************************************************************************************************/
/*! \brief          Samples multiple DID records for subfunction 0x03.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_03SchedulerSample(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerSample()
 *********************************************************************************************************************/
/*! \brief          Samples multiple DID records for subfunction 0x07.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_07SchedulerSample(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnChangeOfDID()
 *********************************************************************************************************************/
/*! \brief          Processes task events related to onChangeOfDataIdentifier
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnChangeOfDID(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnComparisonOfValues()
 *********************************************************************************************************************/
/*! \brief          Processes task events related to onComparisonOfValues
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnComparisonOfValues(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerInitOperation()
 *********************************************************************************************************************/
/*! \brief          Initialize scheduler for next to be read DID.
 *  \details        -
 *  \param[in]      did              The DID that is about to be read
 *  \return         DCM_E_OK         Continue processing
 *  \return         DCM_E_PENDING    DID is currently in use by another service
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerInitOperation(
  uint16 did
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerInitOperation()
 *********************************************************************************************************************/
/*! \brief          Initialize scheduler for next to be read DID.
 *  \details        -
 *  \param[in]      did              The DID that is about to be read
 *  \return         DCM_E_OK         Continue processing
 *  \return         DCM_E_PENDING    DID is currently in use by another service
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerInitOperation(
  uint16 did
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerDetectChange()
 *********************************************************************************************************************/
/*! \brief          Compares the data read by the scheduler with the stored reference data for subfunction 0x03.
 *  \details        -
 *  \param[in]      pDidRecord    The record of the DID that was read
 *  \return         DCM_E_OK      A change of the data was detected and the reference is updated
 *  \return         DCM_E_NOT_OK  The data is equal
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerDetectChange(
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerDetectChange()
 *********************************************************************************************************************/
/*! \brief          Compares the data read by the scheduler with the stored reference data for subfunction 0x07.
 *  \details        -
 *  \param[in]      pDidRecord    The record of the DID that was read
 *  \return         DCM_E_OK      A change of the data was detected and the reference is updated
 *  \return         DCM_E_NOT_OK  The data is equal
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerDetectChange(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07CompareLogicDidChange()
 *********************************************************************************************************************/
/*! \brief          Compares the data read by the scheduler with the stored reference data for subfunction 0x07.
 *  \details        -
 *  \param[in]      pDidRecord    The record of the DID that was read
 *  \return         DCM_E_OK      A change of the data was detected and the reference is updated
 *  \return         DCM_E_NOT_OK  The data is equal
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07CompareLogicDidChange(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07UnsignedComparison()
 *********************************************************************************************************************/
/*! \brief         Compares the unsigned data read for subfunction 0x07.
 *  \details        -
 *  \param[in]      pDidRecord    The record of the DID that was read
 *  \return         DCM_E_OK      A change of the data was detected and the reference is updated
 *  \return         DCM_E_NOT_OK  The data is equal
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07UnsignedComparison(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord,
  uint32  measuredData
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SignedComparison()
 *********************************************************************************************************************/
/*! \brief         Compares the signed data read for subfunction 0x07.
 *  \details        -
 *  \param[in]      pDidRecord    The record of the DID that was read
 *  \return         DCM_E_OK      A change of the data was detected and the reference is updated
 *  \return         DCM_E_NOT_OK  The data is equal
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SignedComparison(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord,
  uint32  measuredData,
  uint32  bitLengh
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerProcessEntry()
 *********************************************************************************************************************/
/*! \brief          Reads a specific DID and compares the data to the reference data for subfuction 0x03.
 *  \details        -
 *  \param[in]      pDidRecord      The record of the DID that is about to be read
 *  \return         DCM_E_OK        Continue processing
 *  \return         DCM_E_PENDING   Processing was postponed
 *  \return         DCM_E_NOT_OK    Something went wrong or DID data has not changed
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerProcessEntry(
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerProcessEntry()
 *********************************************************************************************************************/
/*! \brief          Reads a specific DID and compares the data to the reference data for subfunction 0x07.
 *  \details        -
 *  \param[in]      pDidRecord      The record of the DID that is about to be read
 *  \return         DCM_E_OK        Continue processing
 *  \return         DCM_E_PENDING   Processing was postponed
 *  \return         DCM_E_NOT_OK    Something went wrong or DID data has not changed
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerProcessEntry(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerCancel()
 *********************************************************************************************************************/
/*! \brief          Cancels the scheduled DID for subfunction 0x03.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_03SchedulerCancel(
  void
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerCancel()
 *********************************************************************************************************************/
/*! \brief          Cancels the scheduled DID for subfunction 0x07.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_07SchedulerCancel(
  void
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SchedulerCancel()
 *********************************************************************************************************************/
/*! \brief          Cancels all ongoing DID operations.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86SchedulerCancel(
  void
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SchedulerInit()
 *********************************************************************************************************************/
/*! \brief          Initializes the scheduler.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86SchedulerInit(
  void
  );
# endif

/**********************************************************************************************************************
 *  Dcm_Svc86StopAll()
 *********************************************************************************************************************/
/*! \brief          Stops all activities regarding event processing and scheduling.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86StopAll(
  void
  );

/**********************************************************************************************************************
 *  Dcm_Svc86StartAll()
 *********************************************************************************************************************/
/*! \brief          Starts the scheduling.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86StartAll(
  void
  );

/**********************************************************************************************************************
 *  Dcm_Svc86ClearAll()
 *********************************************************************************************************************/
/*! \brief          Clears all setup events.
 *  \details        Stops all activities regarding event processing and scheduling before clearing.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86ClearAll(
  void
  );

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86RemovePersistedStart()
 *********************************************************************************************************************/
/*! \brief          Removes the persisted start for response on event.
 *  \details        Setting up a new event, clearing or stopping the response on event service, shall remove the 
 *                  persisted start for response of event after reset or power on of the server.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86RemovePersistedStart(
  void
  );
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03Handler()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 0x03 Handler.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK    Send negative response
 *  \return         DCM_E_LOOP      Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidLookUp()
 *********************************************************************************************************************/
/*! \brief          Look up for the requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \return         DCM_E_LOOP       Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidLookUp(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidCheckCondition()
 *********************************************************************************************************************/
/*! \brief          Checks the preconditions of the requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \return         DCM_E_LOOP       Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidCheckCondition(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidGetLength()
 *********************************************************************************************************************/
/*! \brief          Reads the length of a requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidGetLength(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

/**********************************************************************************************************************
 *  Dcm_Svc86_05Handler()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 0x05 Handler.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK    Send negative response
 *  \return         DCM_E_LOOP      Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_05Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );

/**********************************************************************************************************************
 *  Dcm_Svc86_05UpdateNvM()
 *********************************************************************************************************************/
/*! \brief          Stores the data into non-volatile memory (if requested) and finalizes service processing.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_OK         Send positive response
 *  \return         DCM_E_PENDING    Retry later
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_05UpdateNvM(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07Handler()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 0x07 Handler.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK    Send negative response
 *  \return         DCM_E_LOOP      Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidLookUp()
 *********************************************************************************************************************/
/*! \brief          Look up for the requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \return         DCM_E_LOOP       Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidLookUp(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidCheckCondition()
 *********************************************************************************************************************/
/*! \brief          Checks the preconditions of the requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \return         DCM_E_LOOP       Repeat Repeater Proxy immediately
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidCheckCondition(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidGetLength()
 *********************************************************************************************************************/
/*! \brief          Reads the length of a requested DID.
 *  \details        -
 *  \param[in]      pContext       Pointer to the context
 *  \param[in]      opStatus       The operations status
 *  \param[in,out]  pMsgContext    Current message context
 *  \param[out]     ErrorCode      The NRC
 *  \param[in,out]  pRepContext    Current repeater proxy context
 *  \return         DCM_E_NOT_OK     Send negative response
 *  \return         DCM_E_PENDING    Retry later
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidGetLength(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  );
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/*! Public RoE context used by NvM for later restoring */
VAR(Dcm_ExtSvc86NvMDataType, DCM_VAR_NOINIT) Dcm_Svc86NvMData;

/*! RoE context in default session */
DCM_LOCAL VAR(Dcm_ExtSvc86NvMDataType, DCM_VAR_NOINIT) Dcm_Svc86DefaultSession;                                                                      /* PRQA S 3218 */ /* MD_Dcm_CodingRule_3218 */

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/*! Scheduler for periodic sampling */
DCM_LOCAL VAR(Dcm_Svc86SchedulerType, DCM_VAR_NOINIT) Dcm_Svc86Scheduler;
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/*! Default session context */
CONST(Dcm_ExtSvc86NvMDataType, DCM_CONST) Dcm_Svc86DefaultNvMData =                                                                                  /* PRQA S 1514 */ /* MD_Dcm_ObjectOnlyAccessedOnce */
{
   { 0 }                       /* EventRecord */
 , 0x00u                       /* ClientSrcAddr */
 , 0u                          /* MagicNumber */
#  if (DCM_VARMGR_MULTI_SVC_EXCLUSIVE_ENABLED == STD_ON)
 , 0u                          /* CfgVariantId */
#  endif
 , 0u                          /* RxPduId */
 , DCM_SVC86_ROE_STATE_STOPPED /* RoEState */
};
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03GetDidRecord()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Dcm_Svc86OnDidChangeDidRecordPtrType, DCM_CODE) Dcm_Svc86_03GetDidRecord(
  uint8_least index
  )
{
  Dcm_Svc86OnDidChangeDidRecordPtrType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_SVC_86_MAX_NUM_CHANGE_OF_DID_EVENTS))
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    lResult = &Dcm_Svc86CurrentSession.EventRecord.OnDidChange.DidRecord[0];
  }
  else
  {
    lResult = &Dcm_Svc86CurrentSession.EventRecord.OnDidChange.DidRecord[index];
  }

  return lResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07GetDidRecord()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Dcm_Svc86OnCompOfValDidRecordPtrType, DCM_CODE) Dcm_Svc86_07GetDidRecord(
  uint8_least index
  )
{
  Dcm_Svc86OnCompOfValDidRecordPtrType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_SVC_86_MAX_NUM_COMPARISON_OF_VALUE_EVENTS))
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    lResult = &Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.DidRecord[0];
  }
  else
  {
    lResult = &Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.DidRecord[index];
  }

  return lResult;
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86EventRecordInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86EventRecordInit(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least lIndex;

  /* ----- Implementation ----------------------------------------------- */

#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  for (lIndex = 0; lIndex < Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords; ++lIndex)
  {
    Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord = Dcm_Svc86_03GetDidRecord(lIndex);

    pDidRecord->RefState = DCM_SVC86_DID_REFERENCE_STATE_INVALID;                                                                                    /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
  }
#  endif

#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  for (lIndex = 0; lIndex < Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords; ++lIndex)
  {
    Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord = Dcm_Svc86_07GetDidRecord(lIndex);

    pDidRecord->TriggerActive = TRUE;                                                                                                                /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
  }
#  endif
}
# endif

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnDTCStatusChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnDTCStatusChange(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  return Dcm_NetRxIndInternal(Dcm_Svc86CurrentSession.RxPduId
                             ,Dcm_Svc86CurrentSession.ClientSrcAddr
                             ,Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRT
                             ,Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRTLength);                                                 /* SBSW_DCM_POINTER_READ_86DTCRECORD */
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnChangeOfDid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnChangeOfDid(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord;

  /* ----- Implementation ----------------------------------------------- */
  pDidRecord = Dcm_Svc86_03GetDidRecord(Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner);

  return Dcm_NetRxIndInternal(Dcm_Svc86CurrentSession.RxPduId
                             ,Dcm_Svc86CurrentSession.ClientSrcAddr
                             ,pDidRecord->STRT
                             ,pDidRecord->STRTLength);                                                                                               /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SendSTRT_OnComparisonOfValues()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86SendSTRT_OnComparisonOfValues(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord;

  /* ----- Implementation ----------------------------------------------- */
  pDidRecord = Dcm_Svc86_07GetDidRecord(Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner);

  return Dcm_NetRxIndInternal(Dcm_Svc86CurrentSession.RxPduId
                             ,Dcm_Svc86CurrentSession.ClientSrcAddr
                             ,pDidRecord->STRT
                             ,pDidRecord->STRTLength);                                                                                               /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
}
# endif

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnDTCStatusChange()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnDTCStatusChange(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED))
  {
    if(Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED))
    {
      /* Scheduler rate elapsed, trigger STRT */
      Dcm_TskSetLocalEvent(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT);                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      /* Scheduler rate not yet elapsed, postpone sending */
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED);                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT))
  {
    Std_ReturnType lStdResult;

    lStdResult = Dcm_Svc86SendSTRT_OnDTCStatusChange();

    if (lStdResult != DCM_E_OK)
    {
      /* Set STRT state to SENDING and retry sending next task cycle */
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT);                                                   /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerSample()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_03SchedulerSample(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                       lStdReturn;
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  do
  {
    pDidRecord = Dcm_Svc86_03GetDidRecord(Dcm_Svc86Scheduler.OnDidChange.DidIndex);

    lStdReturn = Dcm_Svc86_03SchedulerProcessEntry(pDidRecord);                                                                                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

    if (lStdReturn == DCM_E_PENDING)
    {
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_86_03_DID_SAMPLE_AND_COMPARE);                                                  /* SBSW_DCM_PARAM_PTR_WRITE */
      break;
    }

    if (lStdReturn == DCM_E_OK)
    {
      if (Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner == DCM_SVC86_DID_EVENT_NO_WINNER)
      {
        Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner = Dcm_Svc86Scheduler.OnDidChange.DidIndex;
      }
    }

    ++Dcm_Svc86Scheduler.OnDidChange.DidIndex;

    Dcm_Svc86Scheduler.OnDidChange.DidIndex %= Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords;
  }
  while (Dcm_Svc86Scheduler.OnDidChange.DidIndex != 0u);

  if ( (lStdReturn != DCM_E_PENDING)
    && (Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner != DCM_SVC86_DID_EVENT_NO_WINNER) )
  {
    Dcm_TskSetLocalEvent(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_03_DID_SEND_STRT);                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
  }
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerSample()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_07SchedulerSample(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                       lStdReturn;
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  do
  {
    pDidRecord = Dcm_Svc86_07GetDidRecord(Dcm_Svc86Scheduler.OnCompOfVal.DidIndex);

    lStdReturn = Dcm_Svc86_07SchedulerProcessEntry(pDidRecord);                                                                                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

    if (lStdReturn == DCM_E_PENDING)
    {
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_86_07_DID_SAMPLE_AND_COMPARE);                                                  /* SBSW_DCM_PARAM_PTR_WRITE */
    }

    if (lStdReturn == DCM_E_OK)
    {
      if (Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner == DCM_SVC86_DID_EVENT_NO_WINNER)
      {
        Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner = Dcm_Svc86Scheduler.OnCompOfVal.DidIndex;
        Dcm_Svc86Scheduler.OnCompOfVal.DidIndex = 0u;
      }
    }

    if ((lStdReturn == DCM_E_PENDING) || (Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner != DCM_SVC86_DID_EVENT_NO_WINNER))
    {
      break;
    }

    ++Dcm_Svc86Scheduler.OnCompOfVal.DidIndex;

    Dcm_Svc86Scheduler.OnCompOfVal.DidIndex %= Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords;
  } while (Dcm_Svc86Scheduler.OnCompOfVal.DidIndex != 0u);

  if ((lStdReturn != DCM_E_PENDING)
    && (Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner != DCM_SVC86_DID_EVENT_NO_WINNER))
  {
    Dcm_TskSetLocalEvent(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_07_DID_SEND_STRT);                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
  }
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnChangeOfDID()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnChangeOfDID(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED))
  {
    if (Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords != 0u)
    {
      Dcm_TskSetLocalEvent(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_03_DID_SAMPLE_AND_COMPARE);                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_03_DID_SAMPLE_AND_COMPARE))
  {
    Dcm_Svc86_03SchedulerSample(pContext, pEventContext);                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  if(Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_03_DID_SEND_STRT))
  {
    Std_ReturnType lStdResult;

    lStdResult = Dcm_Svc86SendSTRT_OnChangeOfDid();

    if (lStdResult == DCM_E_OK)
    {
      Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner = DCM_SVC86_DID_EVENT_NO_WINNER;
    }
    else
    {
      /* Set STRT state to SENDING and retry sending next task cycle */
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_86_03_DID_SEND_STRT);                                                           /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86TaskOnComparisonOfValues()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86TaskOnComparisonOfValues(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED))
  {
    if (Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords != 0u)
    {
      Dcm_TskSetLocalEvent(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_07_DID_SAMPLE_AND_COMPARE);                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_07_DID_SAMPLE_AND_COMPARE))
  {
    Dcm_Svc86_07SchedulerSample(pContext, pEventContext);                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  if (Dcm_TskIsLocalEventSet(pEventContext->Ev, DCM_EXT_TSK_EV_ROE_86_07_DID_SEND_STRT))
  {
    Std_ReturnType lStdResult;

    lStdResult = Dcm_Svc86SendSTRT_OnComparisonOfValues();

    if (lStdResult == DCM_E_OK)
    {
      Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner = DCM_SVC86_DID_EVENT_NO_WINNER;
    }
    else
    {
      /* Set STRT state to SENDING and retry sending next task cycle */
      Dcm_TskSetLocalEvent(pEventContext->PostEv, DCM_EXT_TSK_EV_ROE_86_07_DID_SEND_STRT);                                                           /* SBSW_DCM_PARAM_PTR_WRITE */
    }
  }

}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerInitOperation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerInitOperation(
  uint16 did
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_RsrcMgrGetDidLock(DCM_INITIAL, did, DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03);

  if(lStdResult == DCM_E_OK)
  {
    Dcm_Svc86Scheduler.OnDidChange.OpStatus  = DCM_INITIAL;
    Dcm_Svc86Scheduler.OnDidChange.ReadIndex = 0u;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerInitOperation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerInitOperation(
  uint16 did
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_RsrcMgrGetDidLock(DCM_INITIAL, did, DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07);

  if (lStdResult == DCM_E_OK)
  {
    Dcm_Svc86Scheduler.OnCompOfVal.OpStatus = DCM_INITIAL;
    Dcm_Svc86Scheduler.OnCompOfVal.ReadIndex = 0u;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerDetectChange()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerDetectChange(
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  lStdResult = DCM_E_NOT_OK;
  boolean         lUpdateRef = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if (pDidRecord->RefState == DCM_SVC86_DID_REFERENCE_STATE_INVALID)
  {
    pDidRecord->RefState = DCM_SVC86_DID_REFERENCE_STATE_VALID;                                                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
    lUpdateRef = TRUE;
  }
  else
  {
    Dcm_DidMgrDidLengthType lIndex;

    for (lIndex = 0; lIndex < pDidRecord->DidInfoContext.DidLength; ++lIndex)
    {
      if (pDidRecord->RefDidData[lIndex] != Dcm_Svc86Scheduler.OnDidChange.Buffer[lIndex])
      {
        lUpdateRef = TRUE;
        lStdResult = DCM_E_OK;
        break;
      }
    }
  }

  if (lUpdateRef == TRUE)
  {
    /* Change detected, update reference */
    Dcm_UtiMemCopySafe(Dcm_Svc86Scheduler.OnDidChange.Buffer
                      ,pDidRecord->RefDidData
                      ,0u
                      ,DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH
                      ,pDidRecord->DidInfoContext.DidLength);                                                                                        /* SBSW_DCM_COMB_PTR_FORWARD */
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerDetectChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerDetectChange(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_Svc86_07CompareLogicDidChange(pDidRecord);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07CompareLogicDidChange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07CompareLogicDidChange(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32          lMeasuredData;
  uint32          lTempVal = 0u;
  Std_ReturnType  lStdResult = DCM_E_NOT_OK;
  uint8           lTempMask = 0u;
  uint8           lStartByteOffset;
  uint8           lEndByteOffset;
  uint8           lShiftIteration;

  /* ----- Implementation ----------------------------------------------- */
  /* Offset calculation */
  lStartByteOffset = (uint8)(pDidRecord->Offset / 8u);
  lEndByteOffset   = lStartByteOffset + 4u;
  lShiftIteration  = (uint8)(pDidRecord->Offset % 8u);

  lMeasuredData = Dcm_UtiMake32Bit((Dcm_Svc86Scheduler.OnCompOfVal.Buffer[lStartByteOffset + 0u])                                                    /* PRQA S 2985 */ /* MD_Dcm_Redundant_2986 */
                                  ,(Dcm_Svc86Scheduler.OnCompOfVal.Buffer[lStartByteOffset + 1u])
                                  ,(Dcm_Svc86Scheduler.OnCompOfVal.Buffer[lStartByteOffset + 2u])
                                  ,(Dcm_Svc86Scheduler.OnCompOfVal.Buffer[lStartByteOffset + 3u]));


  lMeasuredData = (lMeasuredData << lShiftIteration);

  /* extract the last shifted bits from the end byte offset */
  if (pDidRecord->Offset != 0u)
  {
    lTempMask = (0xFFu << (8u - lShiftIteration));
    lTempVal = (uint32)(Dcm_Svc86Scheduler.OnCompOfVal.Buffer[lEndByteOffset]) & (uint32)(lTempMask);
    lTempVal = lTempVal >> (8u - lShiftIteration);
    lMeasuredData |= lTempVal;
  }

  /* Bit length check */
  if (pDidRecord->BitLength != 0u)
  {
    lMeasuredData = (lMeasuredData >> (32u - (pDidRecord->BitLength)));
  }

  /* Sign check */
  if (pDidRecord->Signedness == TRUE) /* signed comparison */
  {
    lStdResult = Dcm_Svc86_07SignedComparison(pDidRecord, lMeasuredData, pDidRecord->BitLength);                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
  else
  {
    lStdResult = Dcm_Svc86_07UnsignedComparison(pDidRecord, lMeasuredData);                                                                          /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07UnsignedComparison()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07UnsignedComparison(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord,
  uint32  measuredData
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType         lStdResult = DCM_E_NOT_OK;
  uint32                 lHysteresisVal;

  /* ----- Implementation ----------------------------------------------- */

  /* Hysteresis calculation */
  if (pDidRecord->RawRefCompVal == 0u)
  {
    lHysteresisVal = (uint32)(pDidRecord->HysteresisPercentage); /* absolute value */
  }
  else
  {
    lHysteresisVal = (uint32)(((pDidRecord->HysteresisPercentage) * (pDidRecord->RawRefCompVal)) / (100u));
  }

  switch (pDidRecord->ComparisonLogic)
  {
  case DCM_SVC_86_07_COMPARISON_LESS_THAN_MEASURED:
  {
    if ( (pDidRecord->TriggerActive == TRUE)
       &&(pDidRecord->RawRefCompVal < measuredData) )
    {
      pDidRecord->TriggerActive = FALSE;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_OK;
    }
    else /* Hysteresis is not active or measured value is less than the comparison value limit */
    {
      if ((pDidRecord->RawRefCompVal - lHysteresisVal) > measuredData) /* measured data below Hysteresis value */
      {
        pDidRecord->TriggerActive = TRUE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
      }
    }
    break;
  }
  case DCM_SVC_86_07_COMPARISON_MORE_THAN_MEASURED:
  {
    if ( (pDidRecord->TriggerActive == TRUE)
       &&(pDidRecord->RawRefCompVal > measuredData) )
    {
      pDidRecord->TriggerActive = FALSE;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_OK;
    }
    else /* Hysteres is not active or measured value is greater than the comparison value limit */
    {
      if ((pDidRecord->RawRefCompVal + lHysteresisVal) < measuredData)
      {
        pDidRecord->TriggerActive = TRUE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
      }
    }
    break;
  }
  case DCM_SVC_86_07_COMPARISON_EQUAL_MEASURED:
    if (pDidRecord->RawRefCompVal == measuredData)
    {
      lStdResult = DCM_E_OK;
    }
    break;
  case DCM_SVC_86_07_COMPARISON_UNEQUAL_MEASURED:
    if (pDidRecord->RawRefCompVal != measuredData)
    {
      lStdResult = DCM_E_OK;
    }
    break;
  default:                                                                                                                                           /* COV_DCM_RTM_UNREACHABLE X */
    lStdResult = DCM_E_NOT_OK;
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);
    break;
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6030 */ /* MD_MSR_STCYC */
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SignedComparison()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SignedComparison(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord,
  uint32  measuredData,
  uint32  bitLengh
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_NOT_OK;
  sint32         lMeasuredData;
  sint32         lRawRefCompVal;
  uint32         lHysteresisVal;

  /* ----- Implementation ----------------------------------------------- */
  if (bitLengh == 8u)
  {
    lMeasuredData = (sint8)measuredData;
    lRawRefCompVal = (sint8)pDidRecord->RawRefCompVal;
  }
  else if (bitLengh == 16u)
  {
    lMeasuredData = (sint16)measuredData;
    lRawRefCompVal = (sint16)pDidRecord->RawRefCompVal;
  }
  else
  {
    /* 32 bits */
    lMeasuredData = (sint32)measuredData;
    lRawRefCompVal = (sint32)pDidRecord->RawRefCompVal;
  }

  /* Hysteresis calculation */
  if (lRawRefCompVal == 0)
  {
    lHysteresisVal = pDidRecord->HysteresisPercentage; /* absolute value */
  }
  else
  {
    sint32 lAbsRawRefCompVal = Dcm_UtiMathAbs(lRawRefCompVal);

    lHysteresisVal = ((uint32)lAbsRawRefCompVal * pDidRecord->HysteresisPercentage) / 100u;
  }

  switch (pDidRecord->ComparisonLogic)
  {
  case DCM_SVC_86_07_COMPARISON_LESS_THAN_MEASURED:
  {
    if ( (pDidRecord->TriggerActive == TRUE)
       &&(lRawRefCompVal < lMeasuredData) )
    {
      pDidRecord->TriggerActive = FALSE;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_OK;
    }
    else /* Hysteresis is not active or measured value is less than the comparison value limit */
    {
      if ((lRawRefCompVal - (sint32)lHysteresisVal) > lMeasuredData) /* measured data below Hysteresis value */
      {
        pDidRecord->TriggerActive = TRUE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
      }
      else
      {
        /* Hysteresis limit is not reached yet */
      }
    }
    break;
  }
  case DCM_SVC_86_07_COMPARISON_MORE_THAN_MEASURED:
  {
    if ( (pDidRecord->TriggerActive == TRUE)
       &&(lRawRefCompVal > lMeasuredData) )
    {
      pDidRecord->TriggerActive = FALSE;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_OK;
    }
    else /* Hysteres is not active or measured value is greater than the comparison value limit */
    {
      if ((lRawRefCompVal + (sint32)lHysteresisVal) < lMeasuredData)
      {
        pDidRecord->TriggerActive = TRUE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
      }
      else
      {
        /* Hysteresis limit is not reached yet */
      }
    }
    break;
  }
  case DCM_SVC_86_07_COMPARISON_EQUAL_MEASURED:
    if (lRawRefCompVal == lMeasuredData)
    {
      lStdResult = DCM_E_OK;
    }
    break;
  case DCM_SVC_86_07_COMPARISON_UNEQUAL_MEASURED:
    if (lRawRefCompVal != lMeasuredData)
    {
      lStdResult = DCM_E_OK;
    }
    break;
  default:                                                                                                                                           /* COV_DCM_RTM_UNREACHABLE X */
    lStdResult = DCM_E_NOT_OK;
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);
    break;
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6030 */ /* MD_MSR_STCYC */
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerProcessEntry()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03SchedulerProcessEntry(
  Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if (Dcm_RsrcMgrHasDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03) == FALSE)
  {
    lStdResult = Dcm_Svc86_03SchedulerInitOperation(pDidRecord->DidInfoContext.Did);
  }

  if (lStdResult == DCM_E_OK)
  {
    Dcm_DiagDataContextType      lDataContext;
    Dcm_NegativeResponseCodeType lNrc; /* Unused since no NR possible */

    Dcm_UtiInitDataContext(&lDataContext
                          ,Dcm_Svc86Scheduler.OnDidChange.Buffer
                          ,DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH);                                                                                     /* SBSW_DCM_POINTER_INIT_DATA_CONTEXT */

    Dcm_UtiCommitData(&lDataContext, Dcm_Svc86Scheduler.OnDidChange.ReadIndex);                                                                      /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */

    lStdResult = Dcm_DidMgrReadDid(Dcm_Svc86Scheduler.OnDidChange.OpStatus
                                  ,&lDataContext
                                  ,&(pDidRecord->DidInfoContext)
                                  ,&(Dcm_Svc86Scheduler.OnDidChange.DidOpTypeContext)
                                  ,&lNrc);                                                                                                           /* SBSW_DCM_COMB_PTR_FORWARD */

    switch(lStdResult)
    {
    case DCM_E_OK:
      lStdResult = Dcm_Svc86_03SchedulerDetectChange(pDidRecord);                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */

      Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03);
      break;
    case DCM_E_PENDING:
      Dcm_Svc86Scheduler.OnDidChange.OpStatus  = DCM_PENDING;
      Dcm_Svc86Scheduler.OnDidChange.ReadIndex = lDataContext.Usage;
      break;
    default: /* DCM_E_NOT_OK */
      Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03);
      break;
    }
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerProcessEntry()
 *********************************************************************************************************************/
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
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07SchedulerProcessEntry(
  Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  /* ----- Implementation ----------------------------------------------- */
  if (Dcm_RsrcMgrHasDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07) == FALSE)
  {
    lStdResult = Dcm_Svc86_07SchedulerInitOperation(pDidRecord->DidInfoContext.Did);
  }

  if (lStdResult == DCM_E_OK)
  {
    Dcm_DiagDataContextType      lDataContext;
    Dcm_NegativeResponseCodeType lNrc; /* Unused since no NR possible */

    Dcm_UtiInitDataContext(&lDataContext
                          ,Dcm_Svc86Scheduler.OnCompOfVal.Buffer
                          ,DCM_SVC_86_07_MAX_SUPPORTED_COMPARE_LENGTH);                                                                              /* SBSW_DCM_POINTER_INIT_DATA_CONTEXT */

    Dcm_UtiCommitData(&lDataContext, Dcm_Svc86Scheduler.OnCompOfVal.ReadIndex);                                                                      /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */

    lStdResult = Dcm_DidMgrReadDid(Dcm_Svc86Scheduler.OnCompOfVal.OpStatus
                                  ,&lDataContext
                                  ,&(pDidRecord->DidInfoContext)
                                  ,&(Dcm_Svc86Scheduler.OnCompOfVal.DidOpTypeContext)
                                  ,&lNrc);                                                                                                           /* SBSW_DCM_COMB_PTR_FORWARD */

    switch (lStdResult)
    {
    case DCM_E_OK:
      lStdResult = Dcm_Svc86_07SchedulerDetectChange(pDidRecord);                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */

      Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07);
      break;
    case DCM_E_PENDING:
      Dcm_Svc86Scheduler.OnCompOfVal.OpStatus = DCM_PENDING;
      Dcm_Svc86Scheduler.OnCompOfVal.ReadIndex = lDataContext.Usage;
      break;
    default: /* DCM_E_NOT_OK */
      Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07);
      break;
    }
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03SchedulerCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_03SchedulerCancel(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  if(Dcm_RsrcMgrHasDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03) == TRUE)
  {
    Dcm_Svc86OnDidChangeDidRecordPtrType  pDidRecord;
    Dcm_NegativeResponseCodeType          lNrc;/* not evaluated after the API call */
    Dcm_DiagDataContextType               lDataContext;

    pDidRecord = Dcm_Svc86_03GetDidRecord(Dcm_Svc86Scheduler.OnDidChange.DidIndex);

    Dcm_UtiInitDataContext(&lDataContext
                          ,Dcm_Svc86Scheduler.OnDidChange.Buffer
                          ,DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH);                                                                                     /* SBSW_DCM_POINTER_INIT_DATA_CONTEXT */

    /* Cancel ongoing operation immediately  */
    (void)Dcm_DidMgrReadDid(DCM_CANCEL
                           ,&lDataContext
                           ,&(pDidRecord->DidInfoContext)
                           ,&(Dcm_Svc86Scheduler.OnDidChange.DidOpTypeContext)
                           ,&lNrc);                                                                                                                  /* SBSW_DCM_COMB_PTR_FORWARD */

    Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_03);
  }
}
# endif


# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07SchedulerCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86_07SchedulerCancel(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  if (Dcm_RsrcMgrHasDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07) == TRUE)
  {
    Dcm_Svc86OnCompOfValDidRecordPtrType  pDidRecord;
    Dcm_NegativeResponseCodeType          lNrc;/* not evaluated after the API call */
    Dcm_DiagDataContextType               lDataContext;

    pDidRecord = Dcm_Svc86_07GetDidRecord(Dcm_Svc86Scheduler.OnCompOfVal.DidIndex);

    Dcm_UtiInitDataContext(&lDataContext
                          ,Dcm_Svc86Scheduler.OnCompOfVal.Buffer
                          ,DCM_SVC_86_07_MAX_SUPPORTED_COMPARE_LENGTH);                                                                              /* SBSW_DCM_POINTER_INIT_DATA_CONTEXT */

    /* Cancel ongoing operation immediately  */
    (void)Dcm_DidMgrReadDid(DCM_CANCEL
                           ,&lDataContext
                           ,&(pDidRecord->DidInfoContext)
                           ,&(Dcm_Svc86Scheduler.OnCompOfVal.DidOpTypeContext)
                           ,&lNrc);                                                                                                                  /* SBSW_DCM_COMB_PTR_FORWARD */

    Dcm_RsrcMgrReleaseDidLock(DCM_RSRCMGR_DIDLOCK_OWNER_SID86_07);
  }
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SchedulerCancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86SchedulerCancel(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86_03SchedulerCancel();
#  endif

#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86_07SchedulerCancel();
#  endif
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86SchedulerInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86SchedulerInit(
  void
  )
{
#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86Scheduler.OnDidChange.DidIndex       = 0u;
  Dcm_Svc86Scheduler.OnDidChange.DidIndexWinner = DCM_SVC86_DID_EVENT_NO_WINNER;
#  endif

#  if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86Scheduler.OnCompOfVal.DidIndex = 0u;
  Dcm_Svc86Scheduler.OnCompOfVal.DidIndexWinner = DCM_SVC86_DID_EVENT_NO_WINNER;
#  endif
}
# endif

/**********************************************************************************************************************
 *  Dcm_Svc86StopAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86StopAll(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  Dcm_Svc86CurrentSession.RoEState = DCM_SVC86_ROE_STATE_STOPPED;

  Dcm_TmrStopTimer(DCM_TMR_ID_SVC86_SCHEDULER);

  Dcm_TskClrEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED
                                | DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED
                                | DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT
                                | DCM_EXT_TSK_EV_ROE_86_03_DID_SAMPLE_AND_COMPARE
                                | DCM_EXT_TSK_EV_ROE_86_03_DID_SEND_STRT
                                | DCM_EXT_TSK_EV_ROE_86_07_DID_SAMPLE_AND_COMPARE
                                | DCM_EXT_TSK_EV_ROE_86_07_DID_SEND_STRT);

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86SchedulerCancel();
# endif
}

/**********************************************************************************************************************
 *  Dcm_Svc86StartAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86StartAll(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86EventRecordInit();
  Dcm_Svc86SchedulerInit();
# endif

  Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED);

  Dcm_TmrStartTimer(DCM_TMR_ID_SVC86_SCHEDULER, DCM_SVC_86_SCHEDULER_RATE);

}

/**********************************************************************************************************************
 *  Dcm_Svc86ClearAll()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86ClearAll(
  void
  )
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  Dcm_Svc86StopAll();

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcEventState = DCM_SVC86_EVENT_STATE_CLEARED;
# endif
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords = 0u;
# endif
# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords = 0u;
# endif
}

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86RemovePersistedStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_Svc86RemovePersistedStart(
  void
  )
{
  if (Dcm_Svc86CurrentSession.RoEState == DCM_SVC86_ROE_STATE_STARTED_PERSISTENTLY)
  {
    Dcm_Svc86CurrentSession.RoEState = DCM_SVC86_ROE_STATE_STARTED;
    Dcm_UtiNvMSetRamBlockStatus((uint16)DCM_EXT_SVC_86_NVRAM_BLOCKID);
  }
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03Handler()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;
  uint8          lEventWindowTime;
  uint16         lDidOfEventTypeRecord;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if (pMsgContext->reqDataLen >= 6u)
  {
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU16(pMsgContext, &lDidOfEventTypeRecord);                                                                                 /* SBSW_DCM_COMB_PTR_FORWARD */

    if ( (pRepContext->StoreState == TRUE)
       ||(Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords == DCM_SVC_86_MAX_NUM_CHANGE_OF_DID_EVENTS)
       ||(Dcm_UtiGetReqDataAsU8(pMsgContext) != 0x22u) /* Only SID 0x22 is allowed as STRT */                                                        /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
       ||(pMsgContext->reqDataLen > DCM_SVC_86_03_MAX_SUPPORTED_STRT_LENGTH) )
    {
      lStdResult = DCM_E_NOT_OK;
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord;

      pDidRecord = Dcm_Svc86_03GetDidRecord(Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords);

      pRepContext->DidInfoContext.Did = lDidOfEventTypeRecord; /* DID to observe */                                                                  /* SBSW_DCM_PARAM_PTR_WRITE */

      pDidRecord->STRTLength = (uint8)pMsgContext->reqDataLen;                                                                                       /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

      Dcm_UtiConsumeReqDataAsUN(pMsgContext
                               ,pDidRecord->STRT
                               ,DCM_SVC_86_03_MAX_SUPPORTED_STRT_LENGTH
                               ,pMsgContext->reqDataLen);                                                                                            /* SBSW_DCM_COMB_PTR_FORWARD */

      /* Prepare response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u); /* Number of activated elements is always zero */                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU16(pMsgContext, lDidOfEventTypeRecord);                                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsUN(pMsgContext
                               ,pDidRecord->STRT
                               ,pDidRecord->STRTLength);                                                                                             /* SBSW_DCM_COMB_PTR_FORWARD */

      Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_03_SUBPROGRESS_DIDLOOKUP);                                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */
      lStdResult = DCM_E_LOOP;
    }
  }
  else
  {
    *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidLookUp()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidLookUp(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_DidMgrGetDidInfo(opStatus
                                   ,&pRepContext->DidInfoContext
                                   ,&pRepContext->DidOpTypeContext
                                   ,DCM_DIDMGR_OP_READ);                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */

  switch(lStdResult)
  {
  case DCM_E_OK:
    if(Dcm_DidMgrIsOpSupported(Dcm_CfgDidMgrGetDidInfo(&(pRepContext->DidInfoContext)), DCM_DIDMGR_OP_DEFINE))
    {
      /* No DynDID may be referenced! */
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
    }
    else
    {
#  if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
      Dcm_CfgVarMgrComVariantType pComVariant = Dcm_NetGetActiveComVariant();
#  endif

      lStdResult = Dcm_StateCheckDID(Dcm_NetCfgGetRxPduInfo(pComVariant)[pMsgContext->rxPduId].ConnRef                                               /* PRQA S 2841 */ /* MD_Dcm_DerefInvalidPointer */
                                    ,pRepContext->DidInfoContext.Did
                                    ,DCM_DIDMGR_OP_READ
                                    ,Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext))->ExecCondRef
                                    ,ErrorCode);                                                                                                     /* SBSW_DCM_COMB_PTR_FORWARD */

      if(lStdResult == DCM_E_OK)
      {
        Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_03_SUBPROGRESS_DIDCHECKCONDITIONS);                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
        lStdResult = DCM_E_LOOP;
      } /* else DCM_E_NOT_OK (ErrorCode already set) */
    }
    break;
  case DCM_E_PENDING:
    /* lStdResult is already set */
    break;
  default: /* DCM_E_NOT_OK */
    /* source DID is not supported */
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
    break;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidCheckCondition()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidCheckCondition(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_LOOP;

  DCM_IGNORE_UNREF_PARAM(pMsgContext);                                                                                                               /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if(Dcm_DidMgrIsOpTypeSupported(Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext))
                                ,DCM_DIDMGR_OPTYPE_READCHKCOND))
  {
    /* Check condition on this DID */
    Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READCHKCOND);                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */

    lStdResult = Dcm_DidMgrReadCheckCond(opStatus
                                        ,&(pRepContext->DidInfoContext)
                                        ,&(pRepContext->DidOpTypeContext)
                                        ,ErrorCode);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */

    switch(lStdResult)
    {
    case DCM_E_OK:
      lStdResult = DCM_E_LOOP;
      break; /* go on with next DID */
    case DCM_E_PENDING:
      break;
    default: /* DCM_E_NOT_OK */
      break; /* finish service processing immediately */
    }
  }/* else - not supported operation - go on with getLength */

  if(lStdResult == DCM_E_LOOP)
  {
    Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_03_SUBPROGRESS_DIDGETLENGTH);                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  return lStdResult; /* speed up processing */
}
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_03DidGetLength()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_03DidGetLength(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(pMsgContext);                                                                                                               /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if(Dcm_DidMgrIsOpTypeSupported(Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext)), DCM_DIDMGR_OPTYPE_READLENGTH))
  {
    Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READLENGTH);                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */

    lStdResult = Dcm_DidMgrReadLength(opStatus
                                     ,&(pRepContext->DidInfoContext)
                                     ,&(pRepContext->DidOpTypeContext)
                                     ,ErrorCode);                                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  if (lStdResult == DCM_E_OK)
  {
    if (pRepContext->DidInfoContext.ReservedLength > DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH)
    {
      lStdResult = DCM_E_NOT_OK;
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      Dcm_Svc86OnDidChangeDidRecordPtrType pDidRecord;

      /* Add scheduler job - set the operation now since not changed later */
      Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READ);                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */

      pDidRecord = Dcm_Svc86_03GetDidRecord(Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords);

      pDidRecord->DidInfoContext = pRepContext->DidInfoContext;                                                                                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->RefState       = DCM_SVC86_DID_REFERENCE_STATE_INVALID;                                                                            /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

      ++Dcm_Svc86CurrentSession.EventRecord.OnDidChange.NumDidRecords;

#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_Svc86RemovePersistedStart();
#  endif
    }
  }

  return lStdResult;
}
# endif

/**********************************************************************************************************************
 *  Dcm_Svc86_05Handler()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_05Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  lStdResult;
  uint8           lEventWindowTime;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                         /* SBSW_DCM_COMB_PTR_FORWARD */

  if ( (lEventWindowTime != DCM_SVC86_EWT_INFINITE)
     ||( (pRepContext->StoreState == TRUE)
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
       &&(Dcm_StateIsDefaultSessionActive() == FALSE)                                                                                                /* PRQA S 3415 */ /* MD_Dcm_Rule13.5 */
# endif
       ) )
  {
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {
    Dcm_NetTransportObjectConstPtrType pTranspObj;

    pTranspObj = Dcm_NetGetTransportObject(pContext->Diag.TObjHdl);

    pRepContext->SessionContext = Dcm_Svc86CurrentSession;                                                                                           /* SBSW_DCM_PARAM_PTR_WRITE */

    /* Store the source address, the latest client will receive the STRTs */
    pRepContext->SessionContext.RxPduId       = pMsgContext->rxPduId;                                                                                /* SBSW_DCM_PARAM_PTR_WRITE */
    pRepContext->SessionContext.ClientSrcAddr = pTranspObj->ClientSrcAddr;                                                                           /* SBSW_DCM_PARAM_PTR_WRITE */

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    if (pRepContext->StoreState == TRUE)
    {
      pRepContext->SessionContext.RoEState = DCM_SVC86_ROE_STATE_STARTED_PERSISTENTLY;                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
# endif
    {
      pRepContext->SessionContext.RoEState = DCM_SVC86_ROE_STATE_STARTED;                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    }

    Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */

    Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_05_SUBPROGRESS_UPDATE_NVM);                                                                          /* SBSW_DCM_PARAM_PTR_FORWARD */
    lStdResult = DCM_E_LOOP;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_Svc86_05UpdateNvM()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_05UpdateNvM(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,                                                                                                         /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext                                                                                                   /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(pMsgContext);                                                                                                               /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(ErrorCode);                                                                                                                 /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
  if (pRepContext->StoreState == TRUE)
  {
    lStdResult = Dcm_UtiNvMWrite(opStatus, &(pRepContext->SessionContext), DCM_EXT_SVC_86_NVRAM_BLOCKID);                                            /* SBSW_DCM_ROE_NV_ACCESS */ /* PRQA S 0315 */ /* MD_MSR_Dir1.1 */
  }
  else
  {
    Dcm_Svc86RemovePersistedStart();
  }

  if (lStdResult == DCM_E_NOT_OK)
  {
    /* NvM storage failed */
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;                                                                                                         /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }
  else if (lStdResult == DCM_E_PENDING)
  {
    /* Just try later */
  }
  else /* DCM_E_OK */
# endif
  {
    Dcm_Svc86RoeStateType lOldRoEState = Dcm_Svc86CurrentSession.RoEState;

    /* Commit the temporarily stored session context */
    Dcm_Svc86CurrentSession = pRepContext->SessionContext;

    if (lOldRoEState == DCM_SVC86_ROE_STATE_STOPPED)
    {
      Dcm_Svc86StartAll();
    }
  }

  return lStdResult;
}

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07Handler()
 *********************************************************************************************************************/
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
 */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07Handler(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean        lSignedComparison;
  Std_ReturnType lStdResult;
  uint8          lEventWindowTime;
  uint8          lComparisonLogic;
  uint8          lHysteresisPercentage;
  uint8          lRawRefCompVal[4];
  uint8          lBitLength;
  uint16         lOffset;
  uint16         lDidOfEventTypeRecord;
  uint16         lLocalization;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if (pMsgContext->reqDataLen >= 14u)
  {
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU16(pMsgContext, &lDidOfEventTypeRecord);                                                                                 /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lComparisonLogic);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsUN(pMsgContext, lRawRefCompVal, 4u, 4u);                                                                                  /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lHysteresisPercentage);                                                                                  /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU16(pMsgContext, &lLocalization);                                                                                         /* SBSW_DCM_COMB_PTR_FORWARD */

    lOffset           = lLocalization & 0x03FFu;                    /* mask the first 10 bits of the localization (Offset) */
    lBitLength        = (uint8)((lLocalization & 0x7C00u) >> 10u);  /* mask 5 bits of the bit length (bits 10-14) */
    lSignedComparison = (boolean)((lLocalization & 0x8000u) != 0u); /* mask 1 bit that represent if comparison is with sign or not  (bit 15) */

    if ((pRepContext->StoreState == TRUE)
      || (Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords == DCM_SVC_86_MAX_NUM_COMPARISON_OF_VALUE_EVENTS)                            /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
      || (Dcm_UtiGetReqDataAsU8(pMsgContext) != 0x22u) /* Only SID 0x22 is allowed as STRT */                                                        /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
      || (pMsgContext->reqDataLen > DCM_SVC_86_07_MAX_SUPPORTED_STRT_LENGTH)
      || ((lComparisonLogic < 1u) || (lComparisonLogic > 4u)) /* comparison logic should be between 1 to 4 */
      || (lHysteresisPercentage > 100u) /* hysteresis value should be between 0x00 (0%) to 0x64 (100%) */
      || ((lSignedComparison == TRUE) && (((lBitLength % 8u) != 0u) || (lBitLength == 24u))))
    {
      lStdResult = DCM_E_NOT_OK;
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord;

      pDidRecord = Dcm_Svc86_07GetDidRecord(Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords);
      pRepContext->DidInfoContext.Did = lDidOfEventTypeRecord; /* DID to observe */                                                                  /* SBSW_DCM_PARAM_PTR_WRITE */
      pDidRecord->STRTLength = (uint8)pMsgContext->reqDataLen;                                                                                       /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->ComparisonLogic = lComparisonLogic;                                                                                                /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->HysteresisPercentage = lHysteresisPercentage;                                                                                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->TriggerActive = TRUE;                                                                                                              /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->Offset = lOffset;                                                                                                                  /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->BitLength = lBitLength;                                                                                                            /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->Signedness = lSignedComparison;                                                                                                    /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */
      pDidRecord->RawRefCompVal = Dcm_UtiMake32Bit(lRawRefCompVal[0], lRawRefCompVal[1], lRawRefCompVal[2], lRawRefCompVal[3]);                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

      Dcm_UtiConsumeReqDataAsUN(pMsgContext, pDidRecord->STRT, DCM_SVC_86_07_MAX_SUPPORTED_STRT_LENGTH, pMsgContext->reqDataLen);                    /* SBSW_DCM_COMB_PTR_FORWARD */

      /* Prepare response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u); /* Number of activated elements is always zero */                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU16(pMsgContext, lDidOfEventTypeRecord);                                                                                /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, pDidRecord->ComparisonLogic);                                                                           /* SBSW_DCM_COMB_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU32(pMsgContext, pDidRecord->RawRefCompVal);                                                                            /* SBSW_DCM_COMB_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, pDidRecord->HysteresisPercentage);                                                                      /* SBSW_DCM_COMB_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU16(pMsgContext, lLocalization);                                                                                        /* SBSW_DCM_COMB_PTR_FORWARD */
      Dcm_UtiProvideResDataAsUN(pMsgContext, pDidRecord->STRT, pDidRecord->STRTLength);                                                              /* SBSW_DCM_COMB_PTR_FORWARD */

      Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_07_SUBPROGRESS_DIDLOOKUP);                                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */
      lStdResult = DCM_E_LOOP;
    }
  }
  else
  {
    *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidLookUp()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidLookUp(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult;

  /* ----- Implementation ----------------------------------------------- */
  lStdResult = Dcm_DidMgrGetDidInfo(opStatus, &pRepContext->DidInfoContext, &pRepContext->DidOpTypeContext, DCM_DIDMGR_OP_READ);                     /* SBSW_DCM_PARAM_PTR_FORWARD */

  switch (lStdResult)
  {
  case DCM_E_OK:
    if (Dcm_DidMgrIsOpSupported(Dcm_CfgDidMgrGetDidInfo(&(pRepContext->DidInfoContext)), DCM_DIDMGR_OP_DEFINE))
    {
      /* No DynDID may be referenced! */
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
    }
    else
    {
#  if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
      Dcm_CfgVarMgrComVariantType pComVariant = Dcm_NetGetActiveComVariant();
#  endif

      lStdResult = Dcm_StateCheckDID(Dcm_NetCfgGetRxPduInfo(pComVariant)[pMsgContext->rxPduId].ConnRef                                               /* PRQA S 2841 */ /* MD_Dcm_DerefInvalidPointer */
                                    ,pRepContext->DidInfoContext.Did
                                    ,DCM_DIDMGR_OP_READ
                                    ,Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext))->ExecCondRef
                                    ,ErrorCode);                                                                                                     /* SBSW_DCM_COMB_PTR_FORWARD */

      if (lStdResult == DCM_E_OK)
      {
        Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_07_SUBPROGRESS_DIDCHECKCONDITIONS);                                                              /* SBSW_DCM_PARAM_PTR_FORWARD */
        lStdResult = DCM_E_LOOP;
      } /* else DCM_E_NOT_OK (ErrorCode already set) */
    }
    break;
  case DCM_E_PENDING:
    /* lStdResult is already set */
    break;
  default: /* DCM_E_NOT_OK */
    /* source DID is not supported */
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
    break;
  }

  return lStdResult;
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidCheckCondition()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidCheckCondition(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_LOOP;

  DCM_IGNORE_UNREF_PARAM(pMsgContext);                                                                                                               /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if (Dcm_DidMgrIsOpTypeSupported(Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext))
     ,DCM_DIDMGR_OPTYPE_READCHKCOND))
  {
    /* Check condition on this DID */
    Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READCHKCOND);                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */

    lStdResult = Dcm_DidMgrReadCheckCond(opStatus
                                        ,&(pRepContext->DidInfoContext)
                                        ,&(pRepContext->DidOpTypeContext)
                                        ,ErrorCode);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */

    switch (lStdResult)
    {
    case DCM_E_OK:
      lStdResult = DCM_E_LOOP;
      break; /* go on with next DID */
    case DCM_E_PENDING:
      break;
    default: /* DCM_E_NOT_OK */
      break; /* finish service processing immediately */
    }
  }/* else - not supported operation - go on with getLength */

  if (lStdResult == DCM_E_LOOP)
  {
    Dcm_RepeaterNextSubStep(pContext, DCM_SVC86_07_SUBPROGRESS_DIDGETLENGTH);                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  return lStdResult; /* speed up processing */
}
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc86_07DidGetLength()
 *********************************************************************************************************************/
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
DCM_LOCAL FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc86_07DidGetLength(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,                                                                                                                 /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc86RepeaterProxyContextPtrType pRepContext
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType lStdResult = DCM_E_OK;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(pMsgContext);                                                                                                               /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  if (Dcm_DidMgrIsOpTypeSupported(Dcm_CfgDidMgrGetDidOpInfo(&(pRepContext->DidInfoContext)), DCM_DIDMGR_OPTYPE_READLENGTH))
  {
    Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READLENGTH);                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */

    lStdResult = Dcm_DidMgrReadLength(opStatus
                                     ,&(pRepContext->DidInfoContext)
                                     ,&(pRepContext->DidOpTypeContext)
                                     ,ErrorCode);                                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  if (lStdResult == DCM_E_OK)
  {
    Dcm_Svc86OnCompOfValDidRecordPtrType pDidRecord;

    pDidRecord = Dcm_Svc86_07GetDidRecord(Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords);

    if ( (pRepContext->DidInfoContext.ReservedLength > DCM_SVC_86_MAX_SUPPORTED_DID_LENGTH)
      || (((uint32)pDidRecord->Offset + pDidRecord->BitLength) > ((uint32)pRepContext->DidInfoContext.DidLength * 8u)) )
    {
      lStdResult = DCM_E_NOT_OK;
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      /* Add scheduler job - set the operation now since not changed later */
      Dcm_DidMgrInitOpClassInfo(&(pRepContext->DidInfoContext), DCM_DIDMGR_OPTYPE_READ);                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */

      pDidRecord->DidInfoContext = pRepContext->DidInfoContext;                                                                                      /* SBSW_DCM_POINTER_WRITE_86DIDRECORD */

      ++Dcm_Svc86CurrentSession.EventRecord.OnCompOfVal.NumDidRecords;

#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_Svc86RemovePersistedStart();
#  endif
    }
  }

  return lStdResult;
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemTriggerOnDTCStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew
  )
{
  uint8 lErrorId = DCM_E_NO_ERROR;

  /* ----- Development Error Checks ---------------------------------------- */
  if(Dcm_DebugDetectError(Dcm_DebugIsModuleInitialized() == FALSE))
  {
    lErrorId = DCM_E_UNINIT;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------ */
    Dcm_UtiEnterCriticalSection();
    /*=================================*
      BEGIN CRITICAL SECTION
     *=================================*/
    if( (Dcm_Svc86CurrentSession.RoEState != DCM_SVC86_ROE_STATE_STOPPED)
      &&(Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcEventState == DCM_SVC86_EVENT_STATE_ACTIVE)
      &&(((DTCStatusOld ^ DTCStatusNew) & Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.DTCStatusMask) != 0u) )
    {
      /* bit changes 0->1 or 1->0 */
      Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED);
    }
    /*=================================*
      END CRITICAL SECTION
     *=================================*/
    Dcm_UtiLeaveCriticalSection();
  }

  /* ----- Development Error Report ---------------------------------------- */
  Dcm_DebugReportError(DCM_SID_DEMTRIGGERONDTCSTATUS, lErrorId);

  DCM_IGNORE_UNREF_PARAM(DTC);                                                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  return DCM_E_OK;
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_ExtService86Init(
  void
  )
{
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
  if( (Dcm_Svc86CurrentSession.MagicNumber == DCM_CFG_FINAL_MAGIC_NUMBER)
#  if (DCM_VARMGR_MULTI_SVC_EXCLUSIVE_ENABLED == STD_ON)
    &&(Dcm_Svc86CurrentSession.CfgVariantId == Dcm_VarMgrGetActiveCfgVariantId())                                                                    /* PRQA S 3415 */ /* MD_Dcm_Rule13.5 */
#  endif
    &&(Dcm_Svc86CurrentSession.RoEState == DCM_SVC86_ROE_STATE_STARTED_PERSISTENTLY) )
  {
    Dcm_Svc86StartAll();
  }
  else
# endif
  {
    /* Just clear RoE. Initalization of the scheduler will be done when RoE is started */
    Dcm_Svc86ClearAll();

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    Dcm_Svc86CurrentSession.MagicNumber = DCM_CFG_FINAL_MAGIC_NUMBER;
#  if (DCM_VARMGR_MULTI_SVC_EXCLUSIVE_ENABLED == STD_ON)
    Dcm_Svc86CurrentSession.CfgVariantId = Dcm_VarMgrGetActiveCfgVariantId();
#  endif
# endif
  }
}

/**********************************************************************************************************************
 *  Dcm_ExtSvc86Task()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_ExtSvc86Task(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_TskEventContextPtrType pEventContext
  )
{
# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86TaskOnDTCStatusChange(pContext, pEventContext);                                                                                           /* SBSW_DCM_PARAM_PTR_FORWARD */
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86TaskOnChangeOfDID(pContext, pEventContext);                                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
# endif

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86TaskOnComparisonOfValues(pContext, pEventContext);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
# endif

}

/**********************************************************************************************************************
 *  Dcm_ExtOnTimeoutSvc86Scheduler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Dcm_TmrTimerCntrMemType, DCM_CODE) Dcm_ExtOnTimeoutSvc86Scheduler(
  Dcm_ThreadIdMemType threadId
  )
{
  DCM_IGNORE_UNREF_PARAM(threadId);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED);

  return DCM_SVC_86_SCHEDULER_RATE;
}

/**********************************************************************************************************************
 *  Dcm_ExtSvc86OnChangeSession()
 *********************************************************************************************************************/
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
FUNC(void, DCM_CODE) Dcm_ExtSvc86OnChangeSession(
  Dcm_CfgStateGroupOptType oldSession,
  Dcm_CfgStateGroupOptType newSession
  )
{
  /* If it is NOT a transition from default to default session */
  if ((oldSession != DCM_STATE_VALUE_SESSION_INIT) || (newSession != DCM_STATE_VALUE_SESSION_INIT))
  {
    if (oldSession == DCM_STATE_VALUE_SESSION_INIT)
    {
      /* Default session is left; save context */
      Dcm_Svc86DefaultSession = Dcm_Svc86CurrentSession;
    }

    /* Stop RoE, clear task events and cancel any ongoing DID scheduling. Clear RoE setup. */
    Dcm_Svc86ClearAll();

    if (newSession == DCM_STATE_VALUE_SESSION_INIT)
    {
      /* Restore default session context always */
      Dcm_Svc86CurrentSession = Dcm_Svc86DefaultSession;

      if (Dcm_Svc86DefaultSession.RoEState != DCM_SVC86_ROE_STATE_STOPPED)
      {
        Dcm_Svc86StartAll();
      }
    }
  }
}
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DCM_START_SEC_CALLOUT_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_00Processor()
 *********************************************************************************************************************/
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
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_00Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                            lStdResult = DCM_E_OK;
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Repeater.Context.Svc86;

  if(pRepContext->StoreState == TRUE)
  {
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {
    uint8 lEventWindowTime;

    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */

    /* Prepare response data */
    Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */

    if (Dcm_Svc86CurrentSession.RoEState != DCM_SVC86_ROE_STATE_STOPPED)
    {
# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_Svc86RemovePersistedStart();
# endif
      Dcm_Svc86StopAll();
    }
  }

  return lStdResult;
}

# if (DCM_SVC_86_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_01Processor()
 *********************************************************************************************************************/
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
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_01Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                            lStdResult;
  uint8                                     lEventWindowTime;
  uint8                                     lDtcStatusMask;
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext;

  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Repeater.Context.Svc86;

  if (pMsgContext->reqDataLen >= 4u)
  {
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lDtcStatusMask);                                                                                         /* SBSW_DCM_COMB_PTR_FORWARD */

    if ( (pRepContext->StoreState == TRUE)
       ||(Dcm_UtiGetReqDataAsU8(pMsgContext) != 0x19u) /* Only SID 0x19 is allowed as STRT */                                                        /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */
       ||((Dcm_UtiGetReqDataAsU8Rel(pMsgContext, 1u) & 0x80u) != 0u) /* SPRMIB is not allowed for STRT */
       ||(pMsgContext->reqDataLen > DCM_SVC_86_01_MAX_SUPPORTED_STRT_LENGTH) )
    {
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
    }
    else
    {
      Dcm_TskClrEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED
                                    | DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT);

      Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRTLength = (uint8)pMsgContext->reqDataLen;

      Dcm_UtiConsumeReqDataAsUN(pMsgContext
                               ,Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRT
                               ,DCM_SVC_86_01_MAX_SUPPORTED_STRT_LENGTH
                               ,pMsgContext->reqDataLen);                                                                                            /* SBSW_DCM_COMB_PTR_FORWARD */

      Dcm_UtiEnterCriticalSection();
      /*=================================*
        BEGIN CRITICAL SECTION
       *=================================*/
      Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.DTCStatusMask = lDtcStatusMask;
      Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcEventState           = DCM_SVC86_EVENT_STATE_ACTIVE;
      /*=================================*
        END CRITICAL SECTION
       *=================================*/
      Dcm_UtiLeaveCriticalSection();

      /* Report response data */
      Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                 /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsU8(pMsgContext, lDtcStatusMask);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
      Dcm_UtiProvideResDataAsUN(pMsgContext
                               ,Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRT
                               ,Dcm_Svc86CurrentSession.EventRecord.OnDtcChange.DtcRecord.STRTLength);                                               /* SBSW_DCM_COMB_PTR_FORWARD */

#  if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_Svc86RemovePersistedStart();
#  endif

      lStdResult = DCM_E_OK;
    }
  }
  else
  {
    *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
    lStdResult = DCM_E_NOT_OK;
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif

# if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_03Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_03Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  Dcm_Svc86RepeaterProxyContextPtrType pRepContext = &pContext->Repeater.Context.Svc86;

  switch (Dcm_RepeaterGetSubProgress(pContext))
  {
  case DCM_SVC86_03_SUBPROGRESS_INITIAL:
    lStdResult = Dcm_Svc86_03Handler(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_03_SUBPROGRESS_DIDLOOKUP:
    lStdResult = Dcm_Svc86_03DidLookUp(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                     /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_03_SUBPROGRESS_DIDCHECKCONDITIONS:
    lStdResult = Dcm_Svc86_03DidCheckCondition(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                             /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_03_SUBPROGRESS_DIDGETLENGTH:
    lStdResult = Dcm_Svc86_03DidGetLength(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                  /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  default:                                                                                                                                           /* COV_DCM_RTM_UNREACHABLE X */
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);
    break;
  }

  return lStdResult;
}
# endif

/**********************************************************************************************************************
 *  Dcm_ExtService86_05Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_05Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  Dcm_Svc86RepeaterProxyContextPtrType pRepContext = &pContext->Repeater.Context.Svc86;

  switch (Dcm_RepeaterGetSubProgress(pContext))
  {
  case DCM_SVC86_05_SUBPROGRESS_INITIAL:
    lStdResult = Dcm_Svc86_05Handler(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_05_SUBPROGRESS_UPDATE_NVM:
    lStdResult = Dcm_Svc86_05UpdateNvM(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                     /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  default:                                                                                                                                           /* COV_DCM_RTM_UNREACHABLE X */
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);
    break;
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_ExtService86_06Processor()
 *********************************************************************************************************************/
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
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_06Processor(
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                            lStdResult = DCM_E_OK;
  Dcm_Svc86RepeaterProxyContextConstPtrType pRepContext;

  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Implementation ----------------------------------------------- */
  pRepContext = &pContext->Repeater.Context.Svc86;

  if (pRepContext->StoreState == TRUE)
  {
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {
    uint8 lEventWindowTime;

    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &lEventWindowTime);                                                                                       /* SBSW_DCM_COMB_PTR_FORWARD */

# if (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
    Dcm_Svc86RemovePersistedStart();
# endif
    Dcm_Svc86ClearAll();

    Dcm_UtiProvideResDataAsU8(pMsgContext, 0x00u);                                                                                                   /* SBSW_DCM_PARAM_PTR_FORWARD */
    Dcm_UtiProvideResDataAsU8(pMsgContext, lEventWindowTime);                                                                                        /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6050 */ /* MD_MSR_STCAL */

# if (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtService86_07Processor()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ExtService86_07Processor(
  Dcm_ContextPtrType pContext,
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  Dcm_Svc86RepeaterProxyContextPtrType pRepContext = &pContext->Repeater.Context.Svc86;

  switch (Dcm_RepeaterGetSubProgress(pContext))
  {
  case DCM_SVC86_07_SUBPROGRESS_INITIAL:
    lStdResult = Dcm_Svc86_07Handler(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                       /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_07_SUBPROGRESS_DIDLOOKUP:
    lStdResult = Dcm_Svc86_07DidLookUp(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                     /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_07_SUBPROGRESS_DIDCHECKCONDITIONS:
    lStdResult = Dcm_Svc86_07DidCheckCondition(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                             /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  case DCM_SVC86_07_SUBPROGRESS_DIDGETLENGTH:
    lStdResult = Dcm_Svc86_07DidGetLength(pContext, opStatus, pMsgContext, ErrorCode, pRepContext);                                                  /* SBSW_DCM_COMB_PTR_FORWARD */
    break;
  default:                                                                                                                                           /* COV_DCM_RTM_UNREACHABLE X */
    lStdResult = DCM_E_NOT_OK;
    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);
    break;
  }

  return lStdResult;
}
# endif
#endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CALLOUT_CODE
#include "Dcm_MemMap.h"                                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Ext.c
 *********************************************************************************************************************/
