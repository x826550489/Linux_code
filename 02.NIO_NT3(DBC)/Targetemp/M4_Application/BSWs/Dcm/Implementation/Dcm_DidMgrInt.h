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
/**        \file  Dcm_DidMgrInt.h
 *         \unit  DidMgr
 *        \brief  Contains public function declarations and complex type definitions of DidMgr unit.
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
#if !defined(DCM_DIDMGRINT_H)
# define DCM_DIDMGRINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_DidMgrTypes.h"
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
#  include "Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#  if (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_OFF
#  endif

#  if (DCM_SVC_24_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_OFF
#  endif

#  if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_OFF
#  endif

#  if (DCM_DIDMGR_DYNDID_SRCITEM_CHECK_STATE_ENABLED == STD_ON) && \
      (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED    == STD_OFF)
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_ON
#  else
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_OFF
#  endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#  define Dcm_DidMgrIsOpSupported(pDidInfo,   op)                    (((op) & (pDidInfo)->Operations) != 0u)                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_DidMgrIsOpTypeSupported(pDidOpInfo, opType)            (((opType) & (pDidOpInfo)->CallTypes) != 0u)                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_DidMgrOpInfoRedirector(opRef, opRefType)               (Dcm_CfgWrapDidMgrOpInfoCombined((opRef)).opRefType)                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_CfgDidMgrGetDidInfo(pDidInfoContext)                   (Dcm_CfgWrapDidMgrDidInfo((pDidInfoContext)->Descriptor.DidInfoIdx))            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_CfgDidMgrGetDidOpInfo(pDidInfoContext)                 (Dcm_CfgWrapDidMgrDidOpInfo((pDidInfoContext)->Descriptor.DidOpInfoIdx))        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_CfgDidMgrGetDidOpClassInfo(pDidInfoContext)            (Dcm_CfgWrapDidMgrDidOpClassInfo((pDidInfoContext)->Descriptor.DidOpClassInfoIdx)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_DidMgrGetRoeEventId(pDidInfo)                          (Dcm_CfgDidMgrOpInfoRoE[Dcm_DidMgrOpInfoRedirector((pDidInfo)->OpRef, OpRefRoE)].EventId) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  if (DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED == STD_ON)
/* a real function is used for optimal code size */
#  else
#   define Dcm_DidMgrDynDidStateCheck(connHdl, pDidInfoContext, pErroCode) (Dcm_DidMgrStaticDidStateCheck(connHdl, (pDidInfoContext)->Did, DCM_DIDMGR_OP_READ, Dcm_CfgDidMgrGetDidOpInfo(pDidInfoContext)->ExecCondRef, (pErroCode))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
#  define Dcm_DidMgrStaticDidStateCheck(connHdl, did, didOpMask, ExecCondRef, pErroCode) (Dcm_StateCheckDID((connHdl), (did), (didOpMask), (ExecCondRef), (pErroCode))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_DidMgrStaticDidNoAuthStateCheck(ExecCondRef, pErroCode) (Dcm_StateCheck((ExecCondRef), DCM_DIAG_CHK_LVL_PARAMETER, (pErroCode)))       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_DidMgrGetCtrlEnblMaskLength(pDidInfo)                  (Dcm_CfgWrapDidMgrOpInfoIoControl(Dcm_DidMgrOpInfoRedirector((pDidInfo)->OpRef, OpRefIoControl)).CtrlEnblMaskLength) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  if (DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON)
#   define Dcm_DidMgrGetCtrlOpInfoRef(opRef)                         (Dcm_CfgWrapDidMgrOpInfoIoControl((opRef)).RetCtrlToEcuOpRef)                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

#  define Dcm_DidMgrGetCtrlOpExecCondRef(opRef)                      (Dcm_CfgWrapDidMgrOpInfoIoControl((opRef)).CtrlExecCondRef)                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_DidMgrGetDynDidSize(dynDidHandle)                      (Dcm_CfgDidMgrOpInfoDefine[(dynDidHandle)].NumItems)                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_DidMgrGetDynDidSrcItemStartRef(dynDidHandle)           (Dcm_CfgDidMgrOpInfoDefine[(dynDidHandle)].SrcItemRef)                          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  if (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED == STD_ON)
#   define Dcm_DidMgrGetDynDidReadExecPrecond(dynDidHandle)          (Dcm_CfgDidMgrOpInfoDefine[(dynDidHandle)].ReadExecCondRef)                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
#  if (DCM_DIDMGR_PERIODICDYNDID_ENABLED == STD_ON)
#   define Dcm_DidMgrGetDynDidIdFromHandle(dynDidHandle)             ((Dcm_CfgDidMgrOpInfoDefine[(dynDidHandle)].Did))                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Context information of a Did processing */
struct DCM_DIDMGRDIDOPTYPEWORKCONTEXTTYPE_TAG
{
  Dcm_CfgDidMgrSignalOpClassRefMemType  SignalOpClassInfoRef;  /*!< Reference to Dcm_CfgDidMgrSignalOpClassInfo[] entry */
  Dcm_CfgDidMgrSignalIterMemType        NumSignals;            /*!< Number of DID signals */
};
typedef struct DCM_DIDMGRDIDOPTYPEWORKCONTEXTTYPE_TAG Dcm_DidMgrDidOpTypeBaseContextType;

/*! Context information of the read operation */
struct DCM_DIDMGROPTYPEREADCONTEXTTYPE_TAG
{
  Dcm_CfgDidMgrOptimizedDidLengthType  Progress;         /*!< Read progress of the current signal */
  Dcm_OpStatusType                     OpStatus;         /*!< Current operation status */
};
typedef struct DCM_DIDMGROPTYPEREADCONTEXTTYPE_TAG Dcm_DidMgrOpTypeReadContextType;

typedef uint8 Dcm_DidMgrDidLookUpStateType;
/*! Context information of the Did lookup state */
struct DCM_DIDMGRLOOKUPCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidLookUpStateType State;  /*!< Lookup state (range/concrete/external filtered) of a Did */
};
typedef struct DCM_DIDMGRLOOKUPCONTEXTTYPE_TAG Dcm_DidMgrLookUpContextType;

/*! Context information of the IO operation */
struct DCM_DIDMGROPTYPEIOCONTEXTTYPE_TAG
{
  Dcm_ReadOnlyMsgType             EnableMaskPtr;            /*!< Pointer to CEMR of request */
  uint32                          ControlEnableMaskRecord;  /*!< CEMR as a value */
  boolean                         OperExecuted;             /*!< Operation executed flag */
  Dcm_CfgDidMgrSignalIterMemType  SignalIter;               /*!< IODID signal iterator */
  Dcm_MsgItemType                 BitScanner;               /*!< Currently scanned bit of CEMR */
};
typedef struct DCM_DIDMGROPTYPEIOCONTEXTTYPE_TAG Dcm_DidMgrOpTypeIoContextType;

/*! Context information of the shared Did operations */
union DCM_DIDMGRDIDSHAREDOPTYPECONTEXTTYPE_TAG
{                                                                                                                                                    /* PRQA S 0750 */ /* MD_Dcm_Rule19.2 */
  Dcm_DidMgrOpTypeReadContextType           Read;    /*!< Context information of the read operation */
  Dcm_DidMgrLookUpContextType               LookUp;  /*!< Context information of the Did lookup state */
  Dcm_DidMgrOpTypeIoContextType             Io;      /*!< Context information of the Io operation */
};
typedef union DCM_DIDMGRDIDSHAREDOPTYPECONTEXTTYPE_TAG Dcm_DidMgrDidSharedOpTypeContextType;

/*! Context information of the Did operation */
struct DCM_DIDMGRDIDOPTYPECONTEXTTYPE_TAG
{
  Dcm_DidMgrDidOpTypeBaseContextType    Base;    /*!< Context of Did processing */
  Dcm_DidMgrDidSharedOpTypeContextType  OpType;  /*!< Operation context of a Did */
};
typedef struct DCM_DIDMGRDIDOPTYPECONTEXTTYPE_TAG Dcm_DidMgrDidOpTypeContextType;
typedef P2VAR(Dcm_DidMgrDidOpTypeContextType, TYPEDEF, DCM_VAR_NOINIT)   Dcm_DidMgrDidOpTypeContextPtrType;
typedef P2CONST(Dcm_DidMgrDidOpTypeContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_DidMgrDidOpTypeContextConstPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#  define DCM_START_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_DidMgrInit()
 *********************************************************************************************************************/
/*! \brief          Initializes the DID manager sub-component.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            Global interrupts shall be disabled.
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DidMgrInit(
  void
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrInitOpInfo()
 *********************************************************************************************************************/
/*! \brief          Initializes the index to Dcm_CfgDidMgrDidOpInfo[].
 *  \details        -
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      didOp              The required DID operation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DidMgrInitOpInfo(
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrOpOptType didOp
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrInitOpTypeHandler()
 *********************************************************************************************************************/
/*! \brief          Initialization function of the  DID handler.
 *  \details        Prepare DID for multi signal processing for a specific operation type (i.e. Read, ReadCheckCond,
 *                  Write, etc.)
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      pDidOpTypeContext  The DID operation context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DidMgrInitOpTypeHandler(
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrGetDidInfo()
 *********************************************************************************************************************/
/*! \brief          Returns some information of a specific DID.
 *  \details        Looks for the DID to get its corresponding DidInfo and DidOpInfo (up to 32767 items).
 *  \param[in]      opStatus             The current operation status
 *  \param[in,out]  pDidInfoContext      Contains DID Information
 *  \param[in,out]  pDidOpTypeContext    Contains DID operation state
 *  \param[in]      didOp                The lookup DID operation context
 *  \return         DCM_E_OK             Positive look up result
 *  \return         DCM_E_NOT_OK         Negative look up result
 *  \return         DCM_E_PENDING        Final result is pending, retry later
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *  \pre            The DID number must be set by the caller (pDidInfoContext->Did is valid).
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrGetDidInfo(
  Dcm_OpStatusType opStatus,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_DidMgrOpOptType didOp
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrInitOpClassInfo()
 *********************************************************************************************************************/
/*! \brief          Initializes the index to Dcm_CfgDidMgrDidOpClassInfo[].
 *  \details        -
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      opType             Operation type
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DidMgrInitOpClassInfo(
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrOpCallOptType opType
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrReadCheckCond()
 *********************************************************************************************************************/
/*! \brief          Returns the check condition of a specific DID.
 *  \details        -
 *  \param[in]      opStatus           The operation status
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      pDidOpTypeContext  The DID operation context
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         The result of the operation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrReadCheckCond(
  Dcm_OpStatusType opStatus,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrReadDid()
 *********************************************************************************************************************/
/*! \brief          Reads a DID for service 0x22.
 *  \details        -
 *  \param[in]      opStatus           The operation status
 *  \param[in,out]  pDataContext       The pointer to the data context
 *  \param[in,out]  pDidInfoContext    The DID configuration context
 *  \param[in,out]  pDidOpTypeContext  The DID configuration operation context
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         The result of the operation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrReadDid(
  Dcm_OpStatusType opStatus,
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrReadLength()
 *********************************************************************************************************************/
/*! \brief          Returns the length of a specific DID.
 *  \details        -
 *  \param[in]      opStatus           The operation status
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      pDidOpTypeContext  The DID operation context
 *  \param[out]     ErrorCode          The error code
 *  \return         The result of the operation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrReadLength(
  Dcm_OpStatusType opStatus,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_DidMgrConcreteDidLookUp()
 *********************************************************************************************************************/
/*! \brief          Look up for a concrete DID number (no range).
 *  \details        -
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[in]      didOp              The lookup DID operation context
 *  \return         DCM_E_OK           Positive look up result
 *  \return         DCM_E_NOT_OK       Negative look up result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrConcreteDidLookUp(
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrOpOptType didOp
  );

#  if (DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrIoControlRtrnCtrl2Ecu()
 *********************************************************************************************************************/
/*! \brief          Optimized function for ReturnControlToEcu only!.
 *  \details        -
 *  \param[in]      opInfoRef    Operation information
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DidMgrIoControlRtrnCtrl2Ecu(
  Dcm_CfgDidMgrDidOpClassHandleOptType opInfoRef
  );
#  endif

#  if (DCM_SVC_2F_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrIoControl()
 *********************************************************************************************************************/
/*! \brief          DID IO control operator.
 *  \details        -
 *  \param[in]      opStatus           The operation status
 *  \param[in,out]  pMsgContext        The current request context
 *  \param[in,out]  pDidInfoContext    The context of the DID configuration
 *  \param[in,out]  pDidOpTypeContext  The context of the DID operation
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrIoControl(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#  endif

#  if (DCM_DIDMGR_OPTYPE_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrWrite()
 *********************************************************************************************************************/
/*! \brief          Executes DID writing.
 *  \details        Iterates over all signals of a DID.
 *  \param[in]      opStatus           The operation status
 *  \param[in,out]  pMsgContext        The current request context
 *  \param[in,out]  pDidInfoContext    The context of the DID configuration
 *  \param[in,out]  pDidOpTypeContext  The context of the DID operation
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrWrite(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#  endif

#  if (DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrGetScalingInfo()
 *********************************************************************************************************************/
/*! \brief          Returns the scaling information of a given DID.
 *  \details        Iterates over all signals of a DID.
 *  \param[in]      opStatus           The operation status
 *  \param[in,out]  pMsgContext        The current request context
 *  \param[in,out]  pDidInfoContext    The context of the DID configuration
 *  \param[in,out]  pDidOpTypeContext  The context of the DID operation
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrGetScalingInfo(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_DidMgrDidOpTypeContextPtrType pDidOpTypeContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#  endif

#  if (DCM_AUTHMGR_WHITELIST_SERVICES_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrGetSidFromOp()
 *********************************************************************************************************************/
/*! \brief          Get the SID of the did operation.
 *  \details        -
 *  \param[in]      didOp              The DID operation
 *  \return         SID                The service Id
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_DidMgrGetSidFromOp(
  Dcm_DidOpType didOp
  );
#  endif

#  if (DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrDynDidStateCheck()
 *********************************************************************************************************************/
/*! \brief          Checks the state of a specific DID.
 *  \details        Checks a DID operation info considering DynDID content.
 *  \param[in]      connHdl            The connection identifier
 *  \param[in]      pDidInfoContext    The DID configuration context
 *  \param[out]     ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK           State check was successful
 *  \return         DCM_E_NOT_OK       State check was not successful
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrDynDidStateCheck(
  Dcm_NetConnRefMemType connHdl,
  Dcm_DidMgrDidInfoContextPtrType pDidInfoContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#  else
/* a function like macro is used for optimal code size */
#  endif
#  define DCM_STOP_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_DIDMGRINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_DidMgrInt.h
 *********************************************************************************************************************/
