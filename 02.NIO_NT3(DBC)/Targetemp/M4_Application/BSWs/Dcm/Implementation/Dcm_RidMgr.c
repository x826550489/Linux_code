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
/**        \file  Dcm_RidMgr.c
 *         \unit  RidMgr
 *        \brief  Contains the implementation of RidMgr unit.
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
#define DCM_RIDMGR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dcm_RidMgr.h"
#if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
# include "Dcm_ObdIdMgr.h"
# include "Dcm_Utils.h"
# include "Dcm_State.h"
# include "Dcm_Debug.h"
# include "Dcm_CfgWrapper.h"
# include "Dcm_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Routine operation function prototype with no request and response data */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncNoParamsType)(
  Dcm_OpStatusType opStatus,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with only request data both with static length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncReqType)(
  Dcm_ReadOnlyMsgType data,
  Dcm_OpStatusType opStatus,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with request and response data with static length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncReqResType)(
  Dcm_ReadOnlyMsgType reqData,
  Dcm_OpStatusType opStatus,
  Dcm_MsgType resData,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with only response data with static length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncResType)(
  Dcm_OpStatusType opStatus,
  Dcm_MsgType data,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with only request data with dynamic length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncReqDynLenType)(
  Dcm_ReadOnlyMsgType data,
  Dcm_OpStatusType opStatus,
  Dcm_RidMgrRidLengthType Length,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with request data with dynamic length and response data with static length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncReqDynLenResType)(
  Dcm_ReadOnlyMsgType reqData,
  Dcm_OpStatusType opStatus,
  Dcm_MsgType resData,
  Dcm_RidMgrRidLengthType Length,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with request data with dynamic/static length and response data with dynamic length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncReqAnyLenResDynLenType)(
  Dcm_ReadOnlyMsgType reqData,
  Dcm_OpStatusType opStatus,
  Dcm_MsgType resData,
  Dcm_RidMgrRidLengthPtrType Length,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Routine operation function prototype with response data with dynamic length */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncResDynLenType)(
  Dcm_OpStatusType opStatus,
  Dcm_MsgType data,
  Dcm_RidMgrRidLengthPtrType Length,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/*! Generic routine operation function prototype which implementation will be generated depending on the RID configuration */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncWrapperType)(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_RidMgrRidLengthPtrType Length,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RidMgrRidLookUpFilter()
 *********************************************************************************************************************/
/*! \brief          Filters the RID look up result.
 *  \details        If the look-up has found a match, this filter may override this result and specify the RID as
 *                  not-supported.
 *  \param[in]      rid             The RID to be found
 *  \param[in]      ridInfoIdx      Index to the RID information
 *  \return         DCM_E_NOT_OK    No RID has been found
 *  \return         DCM_E_OK        Look up success
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_RidMgrRidLookUpFilter(
  uint16 rid,
  Dcm_CfgRidMgrInfoHandleOptType ridInfoIdx
  );
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CONST_8
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! RID sub-function ID to operation type value conversion map */
CONST(Dcm_RidMgrOpType, DCM_CONST) Dcm_RidMgrSubFunc2OpMap[4] =                                                                                      /* PRQA S 3218 */ /* MD_Dcm_CodingRule_3218 */
{
  DCM_RIDMGR_OP_NONE,
  DCM_RIDMGR_OP_START,
  DCM_RIDMGR_OP_STOP,
  DCM_RIDMGR_OP_REQRSLTS
};
# define DCM_STOP_SEC_CONST_8
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RidMgrRidLookUpFilter()
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
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_RidMgrRidLookUpFilter(
  uint16 rid,
  Dcm_CfgRidMgrInfoHandleOptType ridInfoIdx
  )
{
  Std_ReturnType lStdReturn = DCM_E_OK;

  DCM_IGNORE_UNREF_PARAM(rid);                                                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  DCM_IGNORE_UNREF_PARAM(ridInfoIdx);                                                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
# if (DCM_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON)
  if (Dcm_DiagIsEnabledInActiveVariants(Dcm_CfgRidMgrRidInfoExecCondRef(ridInfoIdx)) == FALSE)                                                       /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
  {
    lStdReturn = DCM_E_NOT_OK;
  }
  else
# endif
  /* check session state */
  if (!Dcm_StateIsSupportedInSession(Dcm_StateGetPreconditionStates(Dcm_CfgRidMgrRidInfoExecCondRef(ridInfoIdx))))
  {
    lStdReturn = DCM_E_NOT_OK;
  }
  else
  {
# if (DCM_SVC_31_OBD_CALIBRATION_ENABLED == STD_ON) && (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON)
    if( (rid >= (uint16)0xE000u)
      &&(rid <= (uint16)0xE1FFu) )
    {
      if(Dcm_ObdIdMgrIsIdEnabled(Dcm_UtiGetLoByte(rid),
                                 Dcm_CfgWrapSvc31SupportedIdMask(Dcm_CfgWrapSvc31SupportedIdMaskOffset(Dcm_UtiGetHiByte(rid)-(uint8)0xE0u))) == FALSE) /* SBSW_DCM_POINTER_FORWARD_GLOBAL */
      {
        lStdReturn = DCM_E_NOT_OK;
      }/* else - an enabled (WWH-)OBD RID */
    }/* else - a non (WWH-)OBD RID */
# endif
  }
  return lStdReturn;
}
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RidMgrGetOpInfo()
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
FUNC(Std_ReturnType, DCM_CODE) Dcm_RidMgrGetOpInfo(
  Dcm_CfgRidMgrInfoHandleOptType ridInfoIdx,
  Dcm_RidMgrOpType ridOp,
  Dcm_CfgRidMgrOpHandlePtrType pRidOpInfoIdx
  )
{
  Std_ReturnType lResult = DCM_E_NOT_OK;
  Dcm_RidMgrOpType lRidOp = ridOp;

  /* If the requested operation is supported at all */
  if ((Dcm_CfgRidMgrRidInfoOperations(ridInfoIdx) & lRidOp) != 0u)
  {
    Dcm_CfgRidMgrOpHandleOptType opHandle = Dcm_CfgRidMgrRidInfoOpBaseIdx(ridInfoIdx);
    do
    {
      lRidOp >>= 1;/* pre-decrement! */
      if ((Dcm_CfgRidMgrRidInfoOperations(ridInfoIdx) & lRidOp) != 0u)
      {
        ++opHandle;
      }
    }
    while (lRidOp != 0u);
    *pRidOpInfoIdx = opHandle;                                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_RidMgrExecuteRoutine()
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
FUNC(Std_ReturnType, DCM_CODE) Dcm_RidMgrExecuteRoutine(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode,
  Dcm_Svc31RepeaterProxyContextPtrType pRepContext                                                                                                   /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  )
{
  Std_ReturnType           lStdResult;
  Dcm_RidMgrOpInfoPtrType  pRidOpInfo;

  lStdResult = Dcm_CfgWrapRidMgrOpInfoGetEntry(pRepContext->RidOpInfoIdx, &pRidOpInfo, ErrorCode);                                                   /* SBSW_DCM_COMB_PTR_FORWARD */

  if(lStdResult == DCM_E_OK)                                                                                                                         /* PRQA S 2991, 2995 */ /* MD_Dcm_ConstExpr */ /* COV_DCM_RTM_RUNTIME_CHECK TX */
  {
    lStdResult = Dcm_UtiMsgContextVerifySize(pMsgContext, pRidOpInfo->ResMaxLength, ErrorCode);                                                      /* SBSW_DCM_PARAM_PTR_FORWARD */

    if(lStdResult == DCM_E_OK)                                                                                                                       /* PRQA S 2991, 2995 */ /* MD_Dcm_ConstExpr */ /* COV_DCM_RTM_RUNTIME_CHECK TX */
    {
      Dcm_RidMgrRidLengthType lReqResLen = (Dcm_RidMgrRidLengthType)(pMsgContext->reqDataLen - pRidOpInfo->ReqMinLength);

      /* Call appropriate function prototype */
      switch(pRidOpInfo->OpType)
      {
      case DCM_RIDMGR_OPTYPE_NONE:
        lStdResult = ((Dcm_RidMgrOpFuncNoParamsType)pRidOpInfo->OpFunc)(opStatus                                                                     /* PRQA S 0313 */ /* MD_Dcm_0313 */
                                                                       ,ErrorCode);                                                                  /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_REQ:
        lStdResult = ((Dcm_RidMgrOpFuncReqType)pRidOpInfo->OpFunc)(Dcm_UtiGetReqData(pMsgContext)                                                    /* PRQA S 0313, 2985 */ /* MD_Dcm_0313, MD_Dcm_Redundant_2985 */
                                                                  ,opStatus
                                                                  ,ErrorCode);                                                                       /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_REQ_RES:
        lStdResult = ((Dcm_RidMgrOpFuncReqResType)pRidOpInfo->OpFunc)(Dcm_UtiGetReqData(pMsgContext)                                                 /* PRQA S 0313, 2985 */ /* MD_Dcm_0313, MD_Dcm_Redundant_2985 */
                                                                     ,opStatus
                                                                     ,Dcm_UtiGetResData(pMsgContext)                                                 /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */ /* SBSW_DCM_PARAM_PTR_FORWARD */
                                                                     ,ErrorCode);                                                                    /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_RES:
        lStdResult = ((Dcm_RidMgrOpFuncResType)pRidOpInfo->OpFunc)(opStatus                                                                          /* PRQA S 0313 */ /* MD_Dcm_0313 */
                                                                  ,Dcm_UtiGetResData(pMsgContext)                                                    /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */ /* SBSW_DCM_PARAM_PTR_FORWARD */
                                                                  ,ErrorCode);                                                                       /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_REQ_DYNLEN:
        lStdResult = ((Dcm_RidMgrOpFuncReqDynLenType)pRidOpInfo->OpFunc)(Dcm_UtiGetReqData(pMsgContext)                                              /* PRQA S 0313, 2985 */ /* MD_Dcm_0313, MD_Dcm_Redundant_2985 */
                                                                        ,opStatus
                                                                        ,lReqResLen
                                                                        ,ErrorCode);                                                                 /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_REQ_DYNLEN_RES:
        lStdResult = ((Dcm_RidMgrOpFuncReqDynLenResType)pRidOpInfo->OpFunc)(Dcm_UtiGetReqData(pMsgContext)                                           /* PRQA S 0313, 2985 */ /* MD_Dcm_0313, MD_Dcm_Redundant_2985 */
                                                                           ,opStatus
                                                                           ,Dcm_UtiGetResData(pMsgContext)                                           /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */ /* SBSW_DCM_PARAM_PTR_FORWARD */
                                                                           ,lReqResLen
                                                                           ,ErrorCode);                                                              /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_RES_DYNLEN:
        lStdResult = ((Dcm_RidMgrOpFuncResDynLenType)pRidOpInfo->OpFunc)(opStatus                                                                    /* PRQA S 0313 */ /* MD_Dcm_0313 */
                                                                        ,Dcm_UtiGetResData(pMsgContext)                                              /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */ /* SBSW_DCM_PARAM_PTR_FORWARD */
                                                                        ,&lReqResLen
                                                                        ,ErrorCode);                                                                 /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_REQ_DYNLEN_RES_DYNLEN:
        /* fall through */
      case DCM_RIDMGR_OPTYPE_REQ_RES_DYNLEN:                                                                                                         /* PRQA S 2003 */ /* MD_Dcm_Optimize_2003 */
        lStdResult = ((Dcm_RidMgrOpFuncReqAnyLenResDynLenType)pRidOpInfo->OpFunc)(Dcm_UtiGetReqData(pMsgContext)                                     /* PRQA S 0313, 2985 */ /* MD_Dcm_0313, MD_Dcm_Redundant_2985 */
                                                                                 ,opStatus
                                                                                 ,Dcm_UtiGetResData(pMsgContext)                                     /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */ /* SBSW_DCM_PARAM_PTR_FORWARD */
                                                                                 ,&lReqResLen
                                                                                 ,ErrorCode);                                                        /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      case DCM_RIDMGR_OPTYPE_WRAPPER:
        lStdResult = ((Dcm_RidMgrOpFuncWrapperType)pRidOpInfo->OpFunc)(opStatus                                                                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
                                                                      ,pMsgContext
                                                                      ,&lReqResLen
                                                                      ,ErrorCode);                                                                   /* SBSW_DCM_CALL_FUNCPTR_SVC31OPFUNC */
        break;
      default:
        *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                /* SBSW_DCM_PARAM_PTR_WRITE */
        lStdResult = DCM_E_NOT_OK;
        Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_INVALID_CONFIG);
        break;
      }

      /* If the operation result is success: */
      if(lStdResult == DCM_E_OK)
      {
        /* Provide the data to the response message, including the variable length part */
        Dcm_UtiProvideResData(pMsgContext, Dcm_CfgRidMgrOpInfoResMinLength(pRepContext->RidOpInfoIdx));                                              /* SBSW_DCM_PARAM_PTR_FORWARD */

        if(pRidOpInfo->ResMinLength != pRidOpInfo->ResMaxLength)
        {
          Dcm_UtiProvideResData(pMsgContext, lReqResLen); /* Register response length of the last signal  */                                         /* SBSW_DCM_PARAM_PTR_FORWARD */
        }
      }

      /* Catch any RTE specific or unexpected errors in order to return a valid value to the core */
      if( (lStdResult != DCM_E_OK)
        &&(lStdResult != DCM_E_PENDING)
        &&(lStdResult != DCM_E_NOT_OK)
        &&(lStdResult != DCM_E_FORCE_RCRRP) )
      {
        Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_INTERFACE_RETURN_VALUE);
        *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                /* SBSW_DCM_PARAM_PTR_WRITE */
        lStdResult = DCM_E_NOT_OK;
      }

      Dcm_UtiHandleApplNrc(lStdResult, ErrorCode, DCM_E_CONDITIONSNOTCORRECT);                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
    }
  }

  return lStdResult;
}                                                                                                                                                    /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 *  Dcm_RidMgrRidLookUp()
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
FUNC(Std_ReturnType, DCM_CODE) Dcm_RidMgrRidLookUp(
  Dcm_OpStatusType opStatus,
  uint16 rid,
  Dcm_CfgRidMgrInfoHandlePtrType pRidInfoIdx
  )
{
  Std_ReturnType lStdReturn;
  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  lStdReturn = DCM_E_OK;

# if (DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
  if(opStatus == DCM_INITIAL)
# endif
  {
    sint16_least lResult;

    lResult = Dcm_UtiLookUpUint16(Dcm_CfgRidMgrRidLookUpTable, rid);                                                                                 /* SBSW_DCM_POINTER_FORWARD_GLOBAL */
    if(lResult >= 0)
    {
      *pRidInfoIdx = (Dcm_CfgRidMgrInfoHandleOptType)lResult;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
    }
    else
    {
      lStdReturn = DCM_E_NOT_OK;
    }
  }

# if (DCM_RIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
  if(lStdReturn == DCM_E_OK)
  {
    /* If RID is suppressed by application filter: */
    lStdReturn = Dcm_FilterRidLookUpResult(opStatus, rid);

    /* If that was last call (DCM_CANCEL), skip any further processing and return any valid value */
    if(opStatus == DCM_CANCEL)
    {
      /* Skip any further processing */
      lStdReturn = DCM_E_NOT_OK;
    }

    /* Catch any unexpected errors in order to return a valid value to the core */
    if(Dcm_DebugDetectError( (lStdReturn != DCM_E_OK)
                           &&(lStdReturn != DCM_E_PENDING)
                           &&(lStdReturn != DCM_E_NOT_OK) ))
    {
      Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_INTERFACE_RETURN_VALUE);
      lStdReturn = DCM_E_NOT_OK;
    }
  }/* else - DCM_E_NOT_OK */
# endif

  if(lStdReturn == DCM_E_OK)
  {
    lStdReturn = Dcm_RidMgrRidLookUpFilter(rid, *pRidInfoIdx);
  }/* else - DCM_E_NOT_OK, DCM_E_PENDING */
  return lStdReturn;
}
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_RidMgr.c
 *********************************************************************************************************************/
