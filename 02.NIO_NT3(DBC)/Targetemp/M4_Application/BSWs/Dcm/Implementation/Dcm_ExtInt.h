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
/**        \file  Dcm_ExtInt.h
 *         \unit  NoUnit
 *        \brief  Private data type definition and interface of DCM
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
#if !defined(DCM_EXTINT_H)
# define DCM_EXTINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Determines when the RoE task in the DCM extension is needed */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  define DCM_EXT_TSK_NUM_ROE                                        1u
# else
#  define DCM_EXT_TSK_NUM_ROE                                        0u /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif

# if (DCM_EXT_TSK_NUM_ROE > 0u)
/*! Events of Dcm_ExtSvc86Task() (task located in the DCM extension part) */
#  define DCM_EXT_TSK_EV_ROE_SCHEDULER_RATE_ELAPSED                  ((Dcm_TskTaskEvMemType)0x01u)  /*!< RoE scheduler rate elapsed */
#  define DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_DETECTED              ((Dcm_TskTaskEvMemType)0x02u)  /*!< Relevant change in status of DTC detected */
#  define DCM_EXT_TSK_EV_ROE_DTC_STATUS_CHANGE_SEND_STRT             ((Dcm_TskTaskEvMemType)0x04u)  /*!< Trigger STRT for subfunction 0x01 */
#  define DCM_EXT_TSK_EV_ROE_86_03_DID_SAMPLE_AND_COMPARE            ((Dcm_TskTaskEvMemType)0x08u)  /*!< Read the setup DID and compare its data with the stored reference for subfunction 0x03 */
#  define DCM_EXT_TSK_EV_ROE_86_03_DID_SEND_STRT                     ((Dcm_TskTaskEvMemType)0x10u)  /*!< Trigger STRT for subfunction 0x03 */
#  define DCM_EXT_TSK_EV_ROE_86_07_DID_SAMPLE_AND_COMPARE            ((Dcm_TskTaskEvMemType)0x20u)  /*!< Read the setup DID and compare its data with the stored reference for subfunction 0x07 */
#  define DCM_EXT_TSK_EV_ROE_86_07_DID_SEND_STRT                     ((Dcm_TskTaskEvMemType)0x40u)  /*!< Trigger STRT for subfunction 0x07 */

/*! Configures the RoE task as a one with a single activation within a single Dcm_MainFunction(Worker) activation since no chaining of complex activities is used */
#  define DCM_EXT_TSK_ATR_ROE_EXEC                                   DCM_TSK_ATR_EXEC_ONCE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  define Dcm_ExtSvc86TxEnd()                                        /* not used */
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/*! Service 0x86 temporary processing context */
struct DCM_SVC86REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ExtSvc86NvMDataType         SessionContext;   /*!< Temporary session context */
#  if ((DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || (DCM_SVC_86_07_SUPPORT_ENABLED == STD_ON))
  Dcm_DidMgrDidInfoContextType    DidInfoContext;   /*!< DID information context */
  Dcm_DidMgrDidOpTypeContextType  DidOpTypeContext; /*!< Did configuration operation context */
#  endif
  Dcm_DiagSubServiceRefMemType    SubSvcRef;        /*!< Index of the requested subfunction */
  boolean                         StoreState;       /*!< Whether the storageState Bit 6 was set */
};
typedef struct DCM_SVC86REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc86RepeaterProxyContextType;

typedef P2VAR(Dcm_Svc86RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc86RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc86RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc86RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
  Dcm_ExtService86Init()
 **********************************************************************************************************************/
/*! \brief          Initialization function.
 *  \details        Service 0x86 initializer.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtService86Init(
  void
  );
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_EXTINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_ExtInt.h
 *********************************************************************************************************************/
