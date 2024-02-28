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
/**        \file  Dcm_Svc31Int.h
 *         \unit  Svc31
 *        \brief  Contains public function declarations and complex type definitions of Svc31 unit.
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
#if !defined(DCM_SVC31INT_H)
# define DCM_SVC31INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_Svc31Types.h"
# if (DCM_SVC_31_SUPPORT_ENABLED == STD_ON)
#  include "Dcm.h"

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
/*! Service 0x31 temporary processing context */
struct DCM_SVC31REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_CfgRidMgrInfoHandleOptType RidInfoIdx;      /*!< Reference to Dcm_CfgRidMgrRidInfo[] entry */
  Dcm_CfgRidMgrOpHandleOptType   RidOpInfoIdx;    /*!< Reference to Dcm_CfgRidMgrOpInfo[] entry */
  uint16                         Rid;             /*!< Rid to be handled */
};
typedef struct DCM_SVC31REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc31RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc31RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc31RepeaterProxyContextPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_SVC_31_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_SVC31INT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Svc31Int.h
 *********************************************************************************************************************/