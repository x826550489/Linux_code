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
/**        \file  Dcm_FblMgr.h
 *         \unit  FblMgr
 *        \brief  Contains public inline function definitions of FblMgr unit.
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
#if !defined(DCM_FBLMGR_H)
# define DCM_FBLMGR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_FblMgrInt.h"
# if (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
#  include "Dcm_Utils.h"

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
#  define DCM_START_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */
#  if !defined(DCM_NOUNIT_FBLMGR)                                                                                                                    /* COV_DCM_NOUNIT TX */
/**********************************************************************************************************************
 *  Dcm_FblMgrParseMemStream()
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
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_FblMgrParseMemStream(                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8 alfid,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_FblMgrMemBlockPtrType pMemBlock,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  uint8_least    lAddressLength;
  sint16_least   lIndex;
  Std_ReturnType lStdResult = DCM_E_OK;

  lAddressLength = Dcm_UtiGetMemBlockAddrSize(alfid);

  if (Dcm_UtiLookUpUint8IsEmpty(Dcm_CfgFblMgrTransferMidLookUpTable))                                                                                /* SBSW_DCM_POINTER_FORWARD_GLOBAL */
  {
    pMemBlock->Mid = 0;                                                                                                                              /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {
    --lAddressLength; /* skip mid */
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &(pMemBlock->Mid));                                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */

    lIndex = Dcm_UtiLookUpUint8(Dcm_CfgFblMgrTransferMidLookUpTable, pMemBlock->Mid);                                                                /* SBSW_DCM_COMB_PTR_FORWARD */

    /* Mid not valid */
    if (lIndex < 0)
    {
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
    }
  }

  if (lStdResult == DCM_E_OK)
  {
    /* extract address */
    pMemBlock->Address = (Dcm_FblMgrMemoryAddressType)Dcm_UtiDwordExtract(pMsgContext, lAddressLength);                                              /* SBSW_DCM_PARAM_PTR_WRITE */ /* SBSW_DCM_PARAM_PTR_FORWARD */

    /* extract size  */
    pMemBlock->Length = (Dcm_FblMgrMemorySizeType)Dcm_UtiDwordExtract(pMsgContext, Dcm_UtiGetMemBlockLenSize(alfid));                                /* SBSW_DCM_PARAM_PTR_WRITE */ /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_FblMgrValidateAndGetAlfid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_FblMgrValidateAndGetAlfid(                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8VarDataPtrType pAlfid,
  Dcm_Uint8VarDataPtrType pBlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_UtiValidateAndGetAlfid(pMsgContext, Dcm_CfgFblMgrTransferAlfidLookUpTable, pAlfid, pBlockLength, ErrorCode);                      /* SBSW_DCM_COMB_PTR_FORWARD */ /* SBSW_DCM_POINTER_FORWARD_STACK */

  return lStdResult;
}
#  endif /* !defined(DCM_NOUNIT_FBLMGR) */
#  define DCM_STOP_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_FBLMGR_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_FblMgr.h
 *********************************************************************************************************************/
