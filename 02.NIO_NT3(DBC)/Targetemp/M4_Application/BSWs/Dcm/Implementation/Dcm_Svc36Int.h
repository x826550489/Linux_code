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
/**        \file  Dcm_Svc36Int.h
 *         \unit  Svc36
 *        \brief  Contains public function declarations and complex type definitions of Svc36 unit.
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
#if !defined(DCM_SVC36INT_H)
# define DCM_SVC36INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_Svc36Types.h"
# if (DCM_SVC_36_SUPPORT_ENABLED == STD_ON)
#  include "Dcm_FblMgrInt.h"

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
/*! Service 0x36 temporary processing context */
struct DCM_SVC36REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_FblMgrBlockSequenceCounterType  BlockSequenceCounterNew;  /*!< New block sequence counter */
};
typedef struct DCM_SVC36REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc36RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc36RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc36RepeaterProxyContextPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_SVC_36_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_SVC36INT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Svc36Int.h
 *********************************************************************************************************************/