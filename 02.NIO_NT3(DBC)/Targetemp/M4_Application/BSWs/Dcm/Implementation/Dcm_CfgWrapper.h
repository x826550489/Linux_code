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
/**        \file  Dcm_CfgWrapper.h
 *         \unit  CfgWrapper
 *        \brief  Contains public inline function definitions of CfgWrapper unit.
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
#if !defined(DCM_CFGWRAPPER_H)
# define DCM_CFGWRAPPER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_CfgWrapperInt.h"
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if !defined(DCM_NOUNIT_CFGWRAPPER)                                                                                                                 /* COV_DCM_NOUNIT TX */
#  if (DCM_SVC_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc01ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc01ServiceInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc01ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC01SERVICEINFOTABLE_SIZE))                                                                        /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pServiceInfo = &Dcm_CfgSvc01ServiceInfoTable[index];                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc06MidTidInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc06MidTidInfoGetEntry(                                                                 /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc06MidTidInfoPtrType, AUTOMATIC, AUTOMATIC) pMidTidInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC06MIDTIDINFOTABLE_SIZE))                                                                         /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pMidTidInfo = &Dcm_CfgSvc06MidTidInfoTable[index];                                                                                              /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_08_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc08ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc08ServiceInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc08ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC08SERVICEINFOTABLE_SIZE))                                                                        /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pServiceInfo = &Dcm_CfgSvc08ServiceInfoTable[index];                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_09_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc09ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc09ServiceInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc09ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC09SERVICEINFOTABLE_SIZE))                                                                        /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pServiceInfo = &Dcm_CfgSvc09ServiceInfoTable[index];                                                                                            /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc11SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc11SubFuncInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc11SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC11SUBFUNCINFO_SIZE))                                                                            /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pSubFuncInfo = &Dcm_CfgSvc11SubFuncInfo[index];                                                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc19SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc19SubFuncInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc19SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC19SUBFUNCINFO_SIZE))                                                                            /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pSubFuncInfo = &Dcm_CfgSvc19SubFuncInfo[index];                                                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc28SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc28SubFuncInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc28SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC28SUBFUNCINFO_SIZE))                                                                            /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pSubFuncInfo = &Dcm_CfgSvc28SubFuncInfo[index];                                                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc85SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc85SubFuncInfoGetEntry(                                                                /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc85SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_CFGSVC85SUBFUNCINFO_SIZE))                                                                            /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pSubFuncInfo = &Dcm_CfgSvc85SubFuncInfo[index];                                                                                                 /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_MODE_ROE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapModeRoEEventModeSwitchGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapModeRoEEventModeSwitchGetEntry(                                                          /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least index,
  CONSTP2VAR(Dcm_CfgModeRoEEventModeSwitchInfoPtrType, AUTOMATIC, AUTOMATIC) pModeSwitchInfo
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(index >= DCM_CFGMODEROEEVENTMODESWITCHINFOTABLE_SIZE))                                                              /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pModeSwitchInfo = &Dcm_CfgModeRoEEventModeSwitchInfoTable[index];                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_MODEMGR_CHECK_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapModeMgrRulesGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapModeMgrRulesGetEntry(                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8_least modeRuleRef,
  CONSTP2VAR(Dcm_ModeRuleFuncType, AUTOMATIC, AUTOMATIC) pModeRuleFunc,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(modeRuleRef >= DCM_CFGMODEMGRRULES_SIZE))                                                                          /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pModeRuleFunc = Dcm_CfgModeMgrRules[modeRuleRef];                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapRidMgrOpInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapRidMgrOpInfoGetEntry(                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint16_least index,
  CONSTP2VAR(Dcm_RidMgrOpInfoPtrType, AUTOMATIC, AUTOMATIC) pRidOpInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if (Dcm_DebugDetectRuntimeError(index >= DCM_CFGRIDMGROPINFO_SIZE))                                                                                /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pRidOpInfo = &Dcm_CfgRidMgrOpInfo[index];                                                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}
#  endif

#  if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrDidOpClassInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Dcm_CfgDidMgrDidOpClassInfoPtrType, DCM_CODE) Dcm_CfgWrapDidMgrDidOpClassInfoGetEntry(                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_CfgDidMgrDidOpClassHandleOptType opInfoRef
  )
{
  Dcm_CfgDidMgrDidOpClassInfoPtrType pOpClassInfo;

  if (Dcm_DebugDetectRuntimeError(opInfoRef >= DCM_CFGDIDMGRDIDOPCLASSINFO_SIZE))                                                                    /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    pOpClassInfo = &Dcm_CfgDidMgrDidOpClassInfo[0];
  }
  else
  {
    pOpClassInfo = &Dcm_CfgDidMgrDidOpClassInfo[opInfoRef];
  }

  return pOpClassInfo;
}

/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrSignalOpClassInfoGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapDidMgrSignalOpClassInfoGetEntry(                                                         /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_CfgDidMgrSignalOpClassRefOptType opInfoRef,
  CONSTP2VAR(Dcm_CfgDidMgrSignalOpClassInfoPtrType, AUTOMATIC, AUTOMATIC) pSignalOpClassInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lResult;

  if(Dcm_DebugDetectRuntimeError(opInfoRef >= DCM_CFGDIDMGRSIGNALOPCLASSINFO_SIZE))                                                                  /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);

    *ErrorCode = DCM_E_PANIC_NRC;                                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_NOT_OK;
  }
  else
  {
    *pSignalOpClassInfo = &Dcm_CfgDidMgrSignalOpClassInfo[opInfoRef];                                                                                /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = DCM_E_OK;
  }

  return lResult;
}

#   if (DCM_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrIoControlSenderReceiverHandlersGetEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Dcm_DidMgrIoCtrlSRHandlersPtrType, DCM_CODE) Dcm_CfgWrapDidMgrIoControlSenderReceiverHandlersGetEntry(                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_CfgDidMgrIoCtrlSRHandlersRefOptType ioControlSRHandlerRef
  )
{
  Dcm_DidMgrIoCtrlSRHandlersPtrType pIoControlSrHandlers;

  if(Dcm_DebugDetectRuntimeError(ioControlSRHandlerRef >= DCM_CFGDIDMGR_IOCONTROLSENDERRECEIVERHANDLERS_SIZE))                                       /* PRQA S 2992 */ /* MD_Dcm_ConstExpr */
  {
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_CRITICAL_ERROR);
    pIoControlSrHandlers = &(Dcm_CfgDidMgr_IOControlSenderReceiverHandlers[0]);
  }
  else
  {
    pIoControlSrHandlers = &(Dcm_CfgDidMgr_IOControlSenderReceiverHandlers[ioControlSRHandlerRef]);
  }

  return pIoControlSrHandlers;
}
#   endif
#  endif

# endif /* !defined(DCM_NOUNIT_CFGWRAPPER) */
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* !defined(DCM_CFGWRAPPER_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_CfgWrapper.h
 *********************************************************************************************************************/
