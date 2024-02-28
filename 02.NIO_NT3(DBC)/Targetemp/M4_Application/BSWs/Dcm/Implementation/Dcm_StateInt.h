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
/**        \file  Dcm_StateInt.h
 *         \unit  State
 *        \brief  Contains public function declarations and complex type definitions of State unit.
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
#if !defined(DCM_STATEINT_H)
# define DCM_STATEINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_StateTypes.h"
# include "Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*! Synchronizes both pending and committed (active) diagnostic session to have the same state (i.e. the pending session becomes the state of the last valid diagnostic session */
# define Dcm_StateSyncPendingSession()                               (Dcm_StateSetPendingSession(Dcm_StateGetSession()))                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# if (DCM_STATE_AUTHENTICATION_ENABLED == STD_ON)
/*! Returns TRUE if the authentication role pre-condition of a diagnostic entity is met */
#  define Dcm_StateIsSupportedInRole(precondPckgRef, authInfoRef)    ((Dcm_AuthMgrActiveRole(authInfoRef) & (precondPckgRef).AuthRole) != 0u)        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif
/*! Returns the diagnostic state related pre-conditions of a diagnostic entity */
# define Dcm_StateGetPreconditionStates(precondPckgRef)              (Dcm_CfgWrapStatePreconditions((precondPckgRef)).States)                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the diagnostic session pre-condition(s) of a diagnostic entity */
# define Dcm_StateGetPreconditionSession(precondPckgRef)             (Dcm_StateGetPreconditionStates(precondPckgRef).Session)                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# if (DCM_STATE_SECURITY_ENABLED == STD_ON)
/*! Returns the security access pre-condition(s) of a diagnostic entity */
#  define Dcm_StateGetPreconditionSecurity(precondPckgRef)           (Dcm_StateGetPreconditionStates(precondPckgRef).Security)                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif
/*! Returns TRUE if current (committed) diagnostic session is the Default-Session. Otherwise returns FALSE */
# define Dcm_StateIsDefaultSessionActive()                           ((Dcm_StateGetSession() & DCM_STATE_VALUE_SESSION_INIT) != 0u)                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if the diagnostic session precondition of a diagnostic entity is met */
# define Dcm_StateIsSupportedInSession(preconditionPackage)          ((Dcm_StateGetSession() & (preconditionPackage).Session) != 0u)                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the diagnostic session ID of the diagnostic session state */
# define Dcm_StateGetSessionValue(stateIdx)                          (Dcm_CfgStateSessionInfo[stateIdx].Value)                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# if (DCM_STATE_SECURITY_ENABLED == STD_ON)
/*! Returns TRUE if current security level is the Locked-Level. Otherwise returns FALSE */
#  define Dcm_StateIsSecurityLocked()                                ((Dcm_StateGetSecurity() & DCM_STATE_VALUE_SECURITY_INIT) != 0u)                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if the security access pre-condition of a diagnostic entity is met */
#  define Dcm_StateIsSupportedInSecurityLevel(preconditionPackage)   ((Dcm_StateGetSecurity() & (preconditionPackage).Security) != 0u)               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the security access level ID of the security access state */
#  define Dcm_StateGetSecurityValue(stateIdx)                        ((Dcm_SecLevelType)(((stateIdx) == 0u)?0u:Dcm_CfgStateSecurityInfo[(stateIdx)-1u].Value)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif

# if (DCM_STATE_SECURITY_FIXED_BYTES_ENABLED == STD_ON)  &&  \
     (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
#  if (DCM_STATE_MULTIPLE_SECURITYFIXEDBYTES_ENABLED == STD_ON)
#   define Dcm_StateGetVsgMaskInfoIdx(stateIdx)                      (Dcm_CfgStateVsgSecurityFixedByteInfo[(stateIdx)])                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define Dcm_StateGetNumberOfVsgs(stateIdx)                        ((Dcm_VsgSizeType)(Dcm_CfgStateVsgSecurityFixedByteInfo[(stateIdx) + 1u]) - (Dcm_VsgSizeType)(Dcm_CfgStateVsgSecurityFixedByteInfo[(stateIdx) + 0u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   define Dcm_StateGetVsgMaskInfoIdx(stateIdx)                      (stateIdx)                                                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define Dcm_StateGetNumberOfVsgs(stateIdx)                        ((((Dcm_VsgSizeType)(Dcm_CfgStateSecurityFixedByteInfo[(stateIdx) + 1u]) - (Dcm_VsgSizeType)(Dcm_CfgStateSecurityFixedByteInfo[(stateIdx) + 0u])) > 0u)?1u:0u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
# endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_StateCheckDID()
 *********************************************************************************************************************/
/*! \brief          Performs a DID state rule check.
 *  \details        -
 *  \param[in]      connHdl                   The connection identifier
 *  \param[in]      did                       The DID identifier
 *  \param[in]      didOpMask                 The DID operation
 *  \param[in]      stateRef                  Reference to the state precondition table
 *  \param[out]     ErrorCode                 The NRC
 *  \return         DCM_E_OK                  State rule check was sucessful
 *  \return         DCM_E_NOT_OK              State rule check was not sucessful
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_StateCheckDID(
  Dcm_NetConnRefMemType connHdl,
  uint16 did,
  Dcm_DidOpType didOpMask,
  Dcm_CfgStateRefOptType stateRef,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_StateCheckRID()
 *********************************************************************************************************************/
/*! \brief          Performs a RID state rule check.
 *  \details        -
 *  \param[in]      pContext                Pointer to the context
 *  \param[in]      rid                     The RID identifier
 *  \param[in]      ridSubfunc              The routine control subfunction
 *  \param[in]      stateRef                Reference to the state precondition table
 *  \param[out]     ErrorCode               The NRC
 *  \return         DCM_E_OK                State rule check was sucessful
 *  \return         DCM_E_NOT_OK            State rule check was not sucessful
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_StateCheckRID(
  Dcm_ContextPtrType pContext,
  uint16 rid,
  uint8 ridSubfunc,
  Dcm_CfgStateRefOptType stateRef,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

/**********************************************************************************************************************
*  Dcm_StateCheck()
*********************************************************************************************************************/
/*! \brief          Performs a state rule check.
*  \details        -
*  \param[in]      stateRef                  Reference to the state precondition table
*  \param[in]      chkLevel                  State level check
*  \param[out]     ErrorCode                 The NRC
*  \return         DCM_E_OK                  State rule check was sucessful
*  \return         DCM_E_NOT_OK              State rule check was not sucessful
*  \context        TASK
*  \reentrant      FALSE
*  \pre            -
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_StateCheck(
  Dcm_CfgStateRefOptType stateRef,
  Dcm_DiagCheckLvlType chkLevel,
  Dcm_NegativeResponseCodePtrType ErrorCode
);

/**********************************************************************************************************************
 *  Dcm_StateGetSession()
 *********************************************************************************************************************/
/*! \brief          Get the current session.
 *  \details        -
 *  \return         Session state
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CfgStateGroupMemType, DCM_CODE) Dcm_StateGetSession(
  void
  );

# if (DCM_STATE_SECURITY_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_StateGetSecurity()
 *********************************************************************************************************************/
/*! \brief          Get the current security state.
 *  \details        -
 *  \return         Security state
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CfgStateGroupMemType, DCM_CODE) Dcm_StateGetSecurity(
  void
  );
# endif

/**********************************************************************************************************************
 *  Dcm_StateSetPendingSession()
 *********************************************************************************************************************/
/*! \brief          Set the pending session.
 *  \details        -
 *  \param[in]      session                  The next pending session.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_StateSetPendingSession(
  Dcm_CfgStateGroupMemType session
  );

/**********************************************************************************************************************
 *  Dcm_StateGetPendingSession()
 *********************************************************************************************************************/
/*! \brief          Get the pending session.
 *  \details        -
 *  \return         Pending session
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CfgStateGroupMemType, DCM_CODE) Dcm_StateGetPendingSession(
  void
  );
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_STATEINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_StateInt.h
 *********************************************************************************************************************/
