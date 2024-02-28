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
/**        \file  Dcm_MemMgr.h
 *         \unit  MemMgr
 *        \brief  Contains public inline function definitions of MemMgr unit.
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
#if !defined(DCM_MEMMGR_H)
# define DCM_MEMMGR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_MemMgrInt.h"
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
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
#  if !defined(DCM_NOUNIT_MEMMGR)                                                                                                                    /* COV_DCM_NOUNIT TX */
/**********************************************************************************************************************
*  Dcm_MemMgrValidateAndGetAlfid()
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
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_MemMgrValidateAndGetAlfid(                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8VarDataPtrType pAlfid,
  Dcm_Uint8VarDataPtrType pBlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
)
{
  Std_ReturnType lStdResult;

  lStdResult = Dcm_UtiValidateAndGetAlfid(pMsgContext, Dcm_CfgMemMgrAlfidLookUpTable, pAlfid, pBlockLength, ErrorCode);                              /* SBSW_DCM_COMB_PTR_FORWARD */ /* SBSW_DCM_POINTER_FORWARD_STACK */

  if (lStdResult == DCM_E_OK)
  {
    if (*pBlockLength > pMsgContext->reqDataLen)
    {
      *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;                                                                                      /* SBSW_DCM_PARAM_PTR_WRITE */
      lStdResult = DCM_E_NOT_OK;
    }
  }

  return lStdResult;
}

/**********************************************************************************************************************
*  Dcm_MemMgrParseMemStream()
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
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_MemMgrParseMemStream(                                                                                     /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8 alfid,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MemMgrMemBlockPtrType pMemBlock
)
{
  uint8_least lAddressLength;

  lAddressLength = Dcm_UtiGetMemBlockAddrSize(alfid);

  if (Dcm_UtiLookUpUint8IsEmpty(Dcm_CfgMemMgrMidLookUpTable))                                                                                        /* SBSW_DCM_POINTER_FORWARD_GLOBAL */
  {
    pMemBlock->Mid = 0;                                                                                                                              /* SBSW_DCM_PARAM_PTR_WRITE */
  }
  else
  {
    --lAddressLength; /* skip mid */
    Dcm_UtiConsumeReqDataAsU8(pMsgContext, &(pMemBlock->Mid));                                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  }

  /* extract address */
  pMemBlock->Address = (Dcm_CfgMemMgrReqAddrType)Dcm_UtiDwordExtract(pMsgContext, lAddressLength);                                                   /* SBSW_DCM_PARAM_PTR_WRITE */ /* SBSW_DCM_PARAM_PTR_FORWARD */

  /* extract size  */
  pMemBlock->Length = (Dcm_CfgMemMgrReqSizeType)Dcm_UtiDwordExtract(pMsgContext, Dcm_UtiGetMemBlockLenSize(alfid));                                  /* SBSW_DCM_PARAM_PTR_WRITE */ /* SBSW_DCM_PARAM_PTR_FORWARD */
}
#  endif /* !defined(DCM_NOUNIT_MEMMGR) */
#  define DCM_STOP_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_MEMMGR_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_MemMgr.h
 *********************************************************************************************************************/
