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
/**        \file  Dcm_Svc14Int.h
 *         \unit  Svc14
 *        \brief  Contains public function declarations and complex type definitions of Svc14 unit.
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
#if !defined(DCM_SVC14INT_H)
# define DCM_SVC14INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_Svc14Types.h"
# if (DCM_SVC_14_SUPPORT_ENABLED == STD_ON)
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
/*! Service 0x14 temporary processing context */
struct DCM_SVC14REPEATERPROXYCONTEXTTYPE_TAG
{
  uint32  Dtc;         /*!< Requested DTC for futher DEM interaction */
  uint16  UserMemId;   /*!< Id of User Defined Memory */
  uint8   DemClientId; /*!< DEM ClientId */
};
typedef struct DCM_SVC14REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc14RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc14RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc14RepeaterProxyContextPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_SVC14INT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Svc14Int.h
 *********************************************************************************************************************/
