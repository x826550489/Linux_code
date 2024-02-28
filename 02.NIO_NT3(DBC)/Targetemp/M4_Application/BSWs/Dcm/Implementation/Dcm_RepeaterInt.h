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
/**        \file  Dcm_RepeaterInt.h
 *         \unit  Repeater
 *        \brief  Contains public function declarations and complex type definitions of Repeater unit.
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
#if !defined(DCM_REPEATERINT_H)
# define DCM_REPEATERINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_RepeaterTypes.h"
# include "Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define DCM_REPEATER_PROGRESS_INITIAL                               ((Dcm_RepeaterProgressType)0)

# define DCM_REPEATER_PROGRESS_USERS_FIRST                           ((Dcm_RepeaterProgressType)1)
# define DCM_REPEATER_PROGRESS_USERS_LAST                            ((Dcm_RepeaterProgressType)254)
# define DCM_REPEATER_PROGRESS_INVALID                               ((Dcm_RepeaterProgressType)255)
/* all other progress types are client /service processor specific and shall start with DCM_REPEATER_PROGRESS_USERS_FIRST and end with DCM_REPEATER_PROGRESS_USERS_LAST */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define Dcm_RepeaterResetOpStatus(pContext)                         (pContext->Repeater.OpStatus = DCM_INITIAL)                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_RepeaterGetProgress(pContext)                           (pContext->Repeater.Progress)                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_RepeaterGetSubProgress(pContext)                        (pContext->Repeater.SubProgress)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RepeaterNextSubStep()
 *********************************************************************************************************************/
/*! \brief          Sets next substep of repeater proxy.
 *  \details        -
 *  \param[in]      pContext    Pointer to the context
 *  \param[in]      nextSubStep Next substep to be processed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
*********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RepeaterNextSubStep(                                                                                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ContextPtrType pContext,
  Dcm_RepeaterProgressType nextSubStep
  );

/**********************************************************************************************************************
 *  Dcm_RepeaterNextStep()
 *********************************************************************************************************************/
/*! \brief          Sets next step of repeater proxy.
 *  \details        -
 *  \param[in]      pContext    Pointer to the context
 *  \param[in]      nextStep    Next step to be processed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
*********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RepeaterNextStep(                                                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ContextPtrType pContext,
  Dcm_RepeaterProgressType nextStep
  );

/**********************************************************************************************************************
 *  Dcm_RepeaterSetCallee()
 *********************************************************************************************************************/
/*! \brief          Sets a new callee for the repeater proxy.
 *  \details        -
 *  \param[in]      pContext               Pointer to the context
 *  \param[in]      serviceProcessorIdx    The proxy callee
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RepeaterSetCallee(
  Dcm_ContextPtrType pContext,
  uint8 serviceProcessorIdx
  );

/**********************************************************************************************************************
 *  Dcm_RepeaterExecute()
 *********************************************************************************************************************/
/*! \brief          Starts polling a repeater proxy.
 *  \details        -
 *  \param[in]      pContext    Pointer to the context
 *  \param[out]     ErrorCode   The NRC
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_RepeaterExecute(
  Dcm_ContextPtrType pContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_REPEATERINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_RepeaterInt.h
 *********************************************************************************************************************/
