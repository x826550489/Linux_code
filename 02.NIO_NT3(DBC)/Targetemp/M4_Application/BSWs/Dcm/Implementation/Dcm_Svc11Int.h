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
/**        \file  Dcm_Svc11Int.h
 *         \unit  Svc11
 *        \brief  Contains public function declarations and complex type definitions of Svc11 unit.
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
#if !defined(DCM_SVC11INT_H)
# define DCM_SVC11INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_Svc11Types.h"
# if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
#  include "Dcm_DiagTypes.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Diagnostic service 0x11 reset response types */
#  define DCM_SVC11_RESPONSE_BEFORE_RESET                            (Dcm_Svc11ResponseType)0 /*!< Send response before reset */
#  define DCM_SVC11_RESPONSE_AFTER_RESET                             (Dcm_Svc11ResponseType)1 /*!< Send response after reset */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Service 0x11 temporary processing context */
struct DCM_SVC11REPEATERPROXYCONTEXTTYPE_TAG
{
#  if (DCM_SVC_11_RST2BOOT_HIS_ENABLED == STD_ON)
  Dcm_ProgConditionsType         ProgConditions;     /*!< Programming condition for further processing steps */
#  endif
  uint8                          SubSvcId;           /*!< Sub-function ID of the current request */
  Dcm_DiagSubServiceRefMemType   SubSvcRef;          /*!< Reference to Dcm_CfgSvc11SubFuncInfo[] entry */
};
typedef struct DCM_SVC11REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc11RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc11RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc11RepeaterProxyContextPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_SVC_11_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_SVC11INT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Svc11Int.h
 *********************************************************************************************************************/