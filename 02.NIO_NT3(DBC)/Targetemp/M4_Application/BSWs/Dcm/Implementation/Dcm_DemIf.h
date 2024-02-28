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
/**        \file  Dcm_DemIf.h
 *         \unit  DemIf
 *        \brief  Contains public inline function definitions of DemIf unit.
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
#if !defined(DCM_DEMIF_H)
# define DCM_DEMIF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_DemIfInt.h"
# include "Dcm_UtilsInt.h"

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
# if !defined(DCM_NOUNIT_DEMIF)                                                                                                                      /* COV_DCM_NOUNIT TX */
#  if (DCM_SVC_02_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemIfGetDTCOfOBDFreezeFrame()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DemIfGetDTCOfOBDFreezeFrame(                                                                    /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8 frameNumber,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) dtc,
  Dem_DTCFormatType dtcFormat
  )
{
  Std_ReturnType lDemResult;
  DCM_IGNORE_UNREF_PARAM(dtcFormat);                                                                                                                 /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  lDemResult = Dem_DcmGetDTCOfOBDFreezeFrame(frameNumber
    , dtc
#   if (DCM_DEMIF_421_ENABLED == STD_OFF)
    , dtcFormat
#   endif
    );                                                                                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */

  return lDemResult;
}
#  endif

#  if (DCM_SVC_02_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemIfReadDataOfOBDFreezeFrame()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DemIfReadDataOfOBDFreezeFrame(                                                                  /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint8 pid,
  uint8 dataElementIndexOfPid,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) destBuffer,
  P2VAR(Dcm_MsgLenType, AUTOMATIC, AUTOMATIC) bufSize
  )
{
  Std_ReturnType lDemResult;

  /* Calculate maximum possible buffer size */
#   if (DCM_DEMIF_421_ENABLED == STD_ON)
  uint8 lBufSize;
  lBufSize = (uint8)Dcm_UtiMathMin(*bufSize, 0xFFu);
#   else
  uint16 lBufSize;
  lBufSize = (uint16)Dcm_UtiMathMin(*bufSize, 0xFFFFu);
#   endif

  lDemResult = Dem_DcmReadDataOfOBDFreezeFrame(pid
    , dataElementIndexOfPid
    , destBuffer
    , &lBufSize);                                                                                                                                    /* SBSW_DCM_PARAM_PTR_FORWARD */

  *bufSize = lBufSize;                                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */

  return lDemResult;
}
#  endif
# endif /* !defined(DCM_NOUNIT_DEMIF) */
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* !defined(DCM_DEMIF_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_DemIf.h
 *********************************************************************************************************************/
