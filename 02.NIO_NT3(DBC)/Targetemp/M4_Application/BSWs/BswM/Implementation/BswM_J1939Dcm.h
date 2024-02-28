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
/**        \file  BswM_J1939Dcm.h
 *        \brief  MICROSAR Basic Software Mode Manager
 *
 *      \details  Callback header for J1939Dcm.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined BSWM_J1939DCM_H
# define BSWM_J1939DCM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "J1939Dcm.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT VERSIONS
 *********************************************************************************************************************/
# define BSWM_J1939_BROADCAST_ENABLED   1u
# define BSWM_J1939_BROADCAST_DISABLED  0u

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
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "BswM_MemMap.h" 

/**********************************************************************************************************************
 *  BswM_J1939DcmBroadcastStatus()
 *********************************************************************************************************************/
/*! \brief      Function called by J1939 DCM to indicate the communication status of the available networks.
 * \details     Passed network state is stored and depending rules are arbitrated.
 * \param[in]   NetworkMask   Mask containing one bit for each available network.
 *                            1: Network enabled - 0: Network disabled
 * \pre         -
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \config      BSWM_ENABLE_J1939DCM
 */
extern FUNC(void, BSWM_CODE) BswM_J1939DcmBroadcastStatus(uint16 NetworkMask);

# define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "BswM_MemMap.h" 

#endif  /* BSWM_J1939DCM_H */

/**********************************************************************************************************************
 *  END OF FILE: BswM_CanSM.h
 *********************************************************************************************************************/
