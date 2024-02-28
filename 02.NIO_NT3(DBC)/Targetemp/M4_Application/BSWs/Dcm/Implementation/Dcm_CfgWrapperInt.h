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
/**        \file  Dcm_CfgWrapperInt.h
 *         \unit  CfgWrapper
 *        \brief  Contains public function declarations and complex type definitions of CfgWrapper unit.
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
#if !defined(DCM_CFGWRAPPERINT_H)
# define DCM_CFGWRAPPERINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_CfgWrapperTypes.h"
# include "Dcm_Debug.h"

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
# if (DCM_MODE_ROE_ENABLED == STD_ON)
typedef P2CONST(Dcm_CfgModeRoEEventModeSwitchInfoType, TYPEDEF, DCM_CONST) Dcm_CfgModeRoEEventModeSwitchInfoPtrType;
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_01_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc01ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get service info descriptor.
 *  \details        -
 *  \param[in]      index           Index to a service info descriptor
 *  \param[out]     pServiceInfo    The service info descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc01ServiceInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc01ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc06MidTidInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get Mid Tid info descriptor.
 *  \details        -
 *  \param[in]      index           Index to a service info descriptor
 *  \param[out]     pMidTidInfo     The Mid Tid info descriptor.
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc06MidTidInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc06MidTidInfoPtrType, AUTOMATIC, AUTOMATIC) pMidTidInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_08_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc08ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get service info descriptor.
 *  \details        -
 *  \param[in]      index           Index to a service info descriptor
 *  \param[out]     pServiceInfo    The service info descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc08ServiceInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc08ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_09_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc09ServiceInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get service info descriptor.
 *  \details        -
 *  \param[in]      index           Index to a service info descriptor
 *  \param[out]     pServiceInfo    The service info descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc09ServiceInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc09ServiceInfoPtrType, AUTOMATIC, AUTOMATIC) pServiceInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc11SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get subfunction descriptor.
 *  \details        -
 *  \param[in]      index           Index to a subfunction descriptor
 *  \param[out]     pSubFuncInfo    The subfunction descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc11SubFuncInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc11SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc19SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get subfunction descriptor.
 *  \details        -
 *  \param[in]      index           Index to a subfunction descriptor
 *  \param[out]     pSubFuncInfo    The subfunction descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc19SubFuncInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc19SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc28SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get subfunction descriptor.
 *  \details        -
 *  \param[in]      index           Index to a subfunction descriptor
 *  \param[out]     pSubFuncInfo    The subfunction descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc28SubFuncInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc28SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapSvc85SubFuncInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get subfunction descriptor.
 *  \details        -
 *  \param[in]      index           Index to a subfunction descriptor
 *  \param[out]     pSubFuncInfo    The subfunction descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapSvc85SubFuncInfoGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgSvc85SubFuncInfoPtrType, AUTOMATIC, AUTOMATIC) pSubFuncInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_MODE_ROE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapModeRoEEventModeSwitchGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get mode switch info descriptor.
 *  \details        -
 *  \param[in]      index           Index to a RoE mode mode switch info descriptor
 *  \param[out]     pModeSwitchInfo The mode switch info descriptor
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapModeRoEEventModeSwitchGetEntry(
  uint8_least index,
  CONSTP2VAR(Dcm_CfgModeRoEEventModeSwitchInfoPtrType, AUTOMATIC, AUTOMATIC) pModeSwitchInfo
  );
# endif

# if (DCM_MODEMGR_CHECK_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapModeMgrRulesGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get module rule.
 *  \details        -
 *  \param[in]      modeRuleRef     A reference to a mode rule
 *  \param[out]     pModeRuleFunc   The mode rule function
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapModeMgrRulesGetEntry(
  uint8_least modeRuleRef,
  CONSTP2VAR(Dcm_ModeRuleFuncType, AUTOMATIC, AUTOMATIC) pModeRuleFunc,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapRidMgrOpInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Get operation descriptor.
 *  \details        -
 *  \param[in]      index           Index to a operation descriptor of a RID operation
 *  \param[out]     pRidOpInfo      The operation descriptor
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapRidMgrOpInfoGetEntry(
  uint16_least index,
  CONSTP2VAR(Dcm_RidMgrOpInfoPtrType, AUTOMATIC, AUTOMATIC) pRidOpInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrDidOpClassInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Returns a DID operation class info element of the given index.
 *  \details        -
 *  \param[in]      opInfoRef  The index of the operation class info
 *  \return         Operation class info entry
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Dcm_CfgDidMgrDidOpClassInfoPtrType, DCM_CODE) Dcm_CfgWrapDidMgrDidOpClassInfoGetEntry(
  Dcm_CfgDidMgrDidOpClassHandleOptType opInfoRef
  );

/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrSignalOpClassInfoGetEntry()
 *********************************************************************************************************************/
/*! \brief          Returns a signal operation class info element of the given index.
 *  \details        -
 *  \param[in]      opInfoRef            The index of the signal operation class info
 *  \param[out]     pSignalOpClassInfo   The signal operation class info element of the given index
 *  \param[out]     ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        The operation was successful
 *  \return         DCM_E_NOT_OK    The given index was invalid (if runtime checks enabled)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgWrapDidMgrSignalOpClassInfoGetEntry(
  Dcm_CfgDidMgrSignalOpClassRefOptType opInfoRef,
  CONSTP2VAR(Dcm_CfgDidMgrSignalOpClassInfoPtrType, AUTOMATIC, AUTOMATIC) pSignalOpClassInfo,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

#  if (DCM_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_CfgWrapDidMgrIoControlSenderReceiverHandlersGetEntry()
 *********************************************************************************************************************/
/*! \brief          Returns a pointer to a struct of SR IO-control handlers.
 *  \details        -
 *  \param[in]      ioControlSRHandlerRef  The index of the IO control handlers
 *  \return         Pointer to a struct of SR IO-control handlers
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Dcm_DidMgrIoCtrlSRHandlersPtrType, DCM_CODE) Dcm_CfgWrapDidMgrIoControlSenderReceiverHandlersGetEntry(
  Dcm_CfgDidMgrIoCtrlSRHandlersRefOptType ioControlSRHandlerRef
  );
#  endif
# endif
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_CFGWRAPPERINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_CfgWrapperInt.h
 *********************************************************************************************************************/
