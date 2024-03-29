/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Com_SignalIf.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_SIGNALIF_SOURCE

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA  S 2741 EOF */ /* MD_CSL_ReducedToDefine */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_Buffers.h"
#include "Com_SignalIf.h"
#include "Com_TxModeHdlr.h"
#include "Com_Serializer.h"
#include "Com_SignalFilterHdlr.h"
#include "SchM_Com.h"
#include "vstdlib.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

#if (COM_TXSIGGRPINFO == STD_ON)
/*!
  \defgroup  Com_SigGrpEventFlagBits  Com Tx Signal Group Event Flags
  \brief  These defines are used to get and set flags in Com_SigGrpEventFlag.
  \details  -
  \pre      -
    \{
*/
# define COM_TX_SIGIF_GROUPEVENTFLAG        1u  /**< indicates a trigger (trigger flag)*/
# define COM_TX_SIGIF_GROUPREPETITION       2u  /**< indicates repetitions (repetition flag)*/
# define COM_TX_SIGIF_GROUPEVENTREPETITION  3u  /**< indicates a trigger with repetition */
# define COM_TX_SIGIF_TRIGGERED_BIT          1u
# define COM_TX_SIGIF_WITHOUT_REPETITION_BIT 2u
# define COM_TX_SIGIF_ON_CHANGE_BIT          4u
/*!
  \}
*/
#endif

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if !defined (COM_LOCAL_INLINE)
# define COM_LOCAL_INLINE LOCAL_INLINE
#endif

#if (COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_TxSigIf_IsTxSigGrpInfoTriggered
**********************************************************************************************************************/
/*! \brief        This function checks if the transferProperty of the provided signal group can trigger a transmission (
 *                not PENDING).
 *  \details      -
    \pre          -
    \param[in]    ComTxSigGrpInfoObj - Id of SignalGroup
    \return       boolean
                    TRUE if no SignalGroup can trigger transmission
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_TxSigIf_IsTxSigGrpInfoTriggered(ComTxSigGrpInfoObj)  ((Com_GetTransferPropertyOfTxSigGrpInfo(ComTxSigGrpInfoObj) & COM_TX_SIGIF_TRIGGERED_BIT) == COM_TX_SIGIF_TRIGGERED_BIT)

/**********************************************************************************************************************
  Com_TxSigIf_IsTxSigGrpInfoOnChange
**********************************************************************************************************************/
/*! \brief        This function checks if provided signal group has any *ON_CHANGE transferProperty.
 *  \details      -
    \pre          -
    \param[in]    ComTxSigGrpInfoObj - Id of SignalGroup
    \return       boolean
                    TRUE if no SignalGroup has ON-CHANGE transferProperty.
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_TxSigIf_IsTxSigGrpInfoOnChange(ComTxSigGrpInfoObj)  ((Com_GetTransferPropertyOfTxSigGrpInfo(ComTxSigGrpInfoObj) & COM_TX_SIGIF_ON_CHANGE_BIT) == COM_TX_SIGIF_ON_CHANGE_BIT)

/**********************************************************************************************************************
  Com_TxSigIf_IsTxSigGrpInfoWithoutRepetition
**********************************************************************************************************************/
/*! \brief        This function checks if provided signal group does not permit repetitive transmission (transferProperty is
 *                is *WITHOUTREPETITION) .
 *  \details      -
    \pre          -
    \param[in]    ComTxSigGrpInfoObj - Id of SignalGroup
    \return       boolean
                    TRUE if no SignalGroup does not permit repetitive transmission.
                    FALSE otherwise
**********************************************************************************************************************/
# define Com_TxSigIf_IsTxSigGrpInfoWithoutRepetition(ComTxSigGrpInfoObj)  ((Com_GetTransferPropertyOfTxSigGrpInfo(ComTxSigGrpInfoObj) & COM_TX_SIGIF_WITHOUT_REPETITION_BIT) == COM_TX_SIGIF_WITHOUT_REPETITION_BIT)
#endif
/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_ReadGroupSignalFromShadowBuffer
**********************************************************************************************************************/
/*! \brief        This function copies the value of the shadow buffer to the related ComGroupSignal buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo Index of RxAccessInfo.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ReadGroupSignalFromShadowBuffer(Com_RxAccessInfoIterType idxRxAccessInfo);
#endif

#if ((COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_EvaluateSignalTriggerConditionAndRequestTransmit
**********************************************************************************************************************/
/*! \brief        This method evaluates the trigger conditions according to the configured transferProperty and
                  and the currently active TxModeMode. On valid trigger conditions a transmit request is set.
    \details      -
    \pre          -
    \param[in]    idxTxPduInfo      Index of TxPduInfo
    \param[in]    idxTxSigInfo      Index of TxSigInfo
    \param[in]    newValuePtr       reference to the new signal value
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_EvaluateSignalTriggerConditionAndRequestTransmit(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr,
                                                                                                      Com_TxPduInfoIterType idxTxPduInfo);
#endif

#if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_EvaluateGroupSignalTriggerConditionAndRequestTransmit
**********************************************************************************************************************/
/*! \brief        This method evaluates the trigger conditions according to the configured transferProperty and
                  and the currently active TxModeMode. The signal group flag is set to indicate a possible transmit.
    \details      -
    \pre          -
    \param[in]    idxTxPduInfo      Index of TxPduInfo
    \param[in]    idxTxGrpSigInfo   Index of TxGrpSigInfo
    \param[in]    newValuePtr       reference to the new signal value
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_EvaluateGroupSignalTriggerConditionAndRequestTransmit(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr);
#endif

#if (COM_TXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalIf_WriteSignal
**********************************************************************************************************************/
/*! \brief        This method updates the signal object identified by SignalId
                  with the signal data referenced by the SignalDataPtr parameter. The Length parameter is evaluated for
                  dynamic length signals.
    \details      -
    \pre          -
    \param[in]    idxTxPduInfo    Index of Tx Signal Info
    \param[in]    idxTxSigInfo    Reference to the signal data to be transmitted.
    \param[in]    Length          Signal length, only required for dynamic length signals.
    \param[in]    SignalDataPtr
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalIf_WriteSignal(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length,
                                                               Com_TxPduInfoIterType idxTxPduInfo);
#endif

#if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalIf_WriteGroupSignal
**********************************************************************************************************************/
/*! \brief        This method updates the group signal object identified by grpSignalId
                  with the signal data referenced by the SignalDataPtr parameter. The Length parameter is evaluated for
                  dynamic length signals.
    \details      -
    \pre          -
    \param[in]    idxTxGrpSigInfo Index of Tx Group Signal Info
    \param[in]    idxTxPduInfo    Reference to the signal data to be transmitted.
    \param[in]    Length          Signal length, only required for dynamic length signals.
    \param[in]    SignalDataPtr
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalIf_WriteGroupSignal(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length,
                                                                    Com_TxPduInfoIterType idxTxPduInfo);
#endif

#if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroup_TriggerEventProcessing
**********************************************************************************************************************/
/*! \brief        This method sets the internal transmit request flag and the I-PDU is transmitted once or multiple.
    \details      -
    \pre          -
    \param[in]    idxTxSigGrpInfo
    \param[in]    idxTxPduInfo
    \return       E_OK                        if service is accepted.
                  COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(uint8, COM_CODE) Com_SendSignalGroup_TriggerEventProcessing(
# if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
                                                                                   Com_SignalIdType idxTxSigGrpInfo,
# endif
                                                                                   PduIdType idxTxPduInfo);
#endif

#if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_SetSigGrpEventFlag
**********************************************************************************************************************/
/*! \brief        This method wraps the function Com_SetSigGrpEventFlag in dependency of the input parameter TriggerWithoutRepetition
    \details      -
    \pre          -
    \param[in]    TriggerWithoutRepetition      TRUE if signal or group signal has any '*_WITHOUT_REPETITION' transfer property
    \param[in]    idxTxSigGrpInfo               Index of the Tx SigGrpInfo
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_SetSigGrpEventFlag(Com_TxSigGrpInfoIdxOfTxGrpSigInfoType idxTxSigGrpInfo, boolean TriggerWithoutRepetition);
#endif

#if (COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_CheckSignalFilter
**********************************************************************************************************************/
/*! \brief        If the Tx-Signal is configured to be filtered, this function evaluates the filters and updates the filter
 *                state.
    \details      -
    \pre          -
    \param[in]    idxTxSigInfo  ID of the Tx signal.
    \param[in]    newValuePtr Pointer to the new value
    \param[in]    idxTxPduInfo  ID of Tx I-PDU.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_CheckSignalFilter(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr, Com_TxPduInfoIterType idxTxPduInfo);
#endif

#if (COM_FILTERINFOUSEDOFTXGRPSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_CheckGroupSignalFilter
**********************************************************************************************************************/
/*! \brief        If the Tx-GroupSignal is configured to be filtered, this function evaluates the filters and updates the filter
 *                state.
    \details      -
    \pre          -
    \param[in]    idxTxGrpSigInfo  ID of the Tx Group signal.
    \param[in]    newValuePtr Pointer to the new value
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_CheckGroupSignalFilter(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr);
#endif

#if ((COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON) && ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON)) && ((COM_TXSIGGRPONCHANGEMASKONCHANGEUSEDOFTXSIGGRPINFO == STD_ON) || (COM_TXSIGGRPONCHANGEMASKONCHANGEWITHOUTREPUSEDOFTXSIGGRPINFO == STD_ON)))
/**********************************************************************************************************************
  Com_SendSignalGroupArrayHasChanged
**********************************************************************************************************************/
/*! \brief        This function checks if the content of the SignalGroup in the group array  has changed.
    \details      -
    \pre          -
    \param[in]    SignalGroupArrayPtr         Reference to the signal group array
    \param[in]    maskPtr                     Pointer to OnChange Mask
    \param[in]    pIpduBuf                    Pointer to iPduBuffer
    \param[in]    MaskLength                  Length of the mask
    \return       uint8
                    true                        if content has changed
                    false                       otherwise
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_SendSignalGroupArrayHasChanged(P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr, P2CONST(uint8, AUTOMATIC, COM_VAR_NO_INIT) pIpduBuf, uint32 MaskLength);
#endif

#if(COM_SIGGRPARRAYFILTERINFO == STD_ON)
/**********************************************************************************************************************
  Com_EvaluateSigGrpArrFilterProcessing
**********************************************************************************************************************/
/*! \brief        This function evaluates the filter bytewise for SignalGroups with ArrayAccess enabled.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo               Index of related SignalGroup Array filter info
    \param[in]    maskPtr                     Pointer to the configured filter mask
    \param[in]    filterValueXPtr             Pointer to the configured filter value X
    \param[in]    newValuePtr                 Reference to the signal group array.
    \param[in]    maskLength                  Length of the mask
    \return       boolean                     TRUE, if filter condition is passed, FALSE otherwise.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_EvaluateSigGrpArrFilterProcessing(Com_SigGrpArrayFilterInfoIterType idxFilterInfo,
                                                                               P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr,
                                                                               P2CONST(uint8, AUTOMATIC, COM_PBCFG) filterValueXPtr,
                                                                               P2CONST(uint8, AUTOMATIC, COM_VAR_NO_INIT) newValuePtr, uint32 maskLength);
#endif

#if(COM_SIGGRPARRAYFILTERINFOUSEDOFTXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_EvaluateSigGrpArrFilter
**********************************************************************************************************************/
/*! \brief        This function updates the filter state value.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo               Index of related SignalGroup Array filter info
    \param[in]    newValuePtr                 Reference to the signal group array.
    \return       boolean                     TRUE, if filter condition is passed, FALSE otherwise.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_EvaluateSigGrpArrFilter(Com_SigGrpArrayFilterInfoIterType idxFilterInfo, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) newValuePtr);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_ReadGroupSignalFromShadowBuffer
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_ReadGroupSignalFromShadowBuffer(Com_RxAccessInfoIterType idxRxAccessInfo)
{
  /* #10 Copy the shadow buffer to the ComGroupSignal buffer, the destination buffer depends on the ComGroupSignal ApplType */
# if(COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsBufferUsedOfRxAccessInfo(idxRxAccessInfo) && Com_IsShdBufferUsedOfRxAccessInfo(idxRxAccessInfo))    /* COV_COM_CSL03_ISUSED_OPTIONAL_INDIRECTION */
  {
    switch (Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
    {
      /* Hint: Check for Uint8 appl type is needed as signalGroups with Array Access enabled are using the same buffer */
# if ((COM_TMPRXSHDBUFFERUINT8 == STD_ON) && (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
      case COM_UINT8_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT8_BUFFEROFRXACCESSINFO) && 
          (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT8_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferUInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferUInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT8 == STD_ON)
      case COM_SINT8_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT8_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT8_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferSInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferSInt8(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));  /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT16 == STD_ON)
      case COM_UINT16_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT16_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT16_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferUInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferUInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT16 == STD_ON)
      case COM_SINT16_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT16_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT16_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferSInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferSInt16(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT32 == STD_ON)
      case COM_UINT32_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT32_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT32_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferUInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferUInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT32 == STD_ON)
      case COM_SINT32_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT32_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT32_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferSInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferSInt32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERUINT64 == STD_ON)
      case COM_UINT64_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT64_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERUINT64_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferUInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferUInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERSINT64 == STD_ON)
      case COM_SINT64_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT64_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERSINT64_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferSInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferSInt64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));        /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT32 == STD_ON)
      case COM_FLOAT32_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERFLOAT32_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERFLOAT32_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferFloat32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferFloat32(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
# if (COM_TMPRXSHDBUFFERFLOAT64 == STD_ON)
      case COM_FLOAT64_APPLTYPEOFRXACCESSINFO:
      {
        if((Com_GetBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERFLOAT64_BUFFEROFRXACCESSINFO) && 
           (Com_GetShdBufferOfRxAccessInfo(idxRxAccessInfo) == COM_RXSIGBUFFERFLOAT64_SHDBUFFEROFRXACCESSINFO))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ 
        {
          Com_SetRxSigBufferFloat64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo), Com_GetRxSigBufferFloat64(Com_GetShdBufferIdxOfRxAccessInfo(idxRxAccessInfo)));      /* SBSW_COM_CSL04 */
        }
        break;
      }
# endif
      default:   /* COV_COM_MISRA */
        break;
    }
  }
# endif  
# if (COM_TMPRXSHDBUFFERARRAYBASED == STD_ON)
  switch(Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo))
  {
#  if (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)
    case COM_UINT8_N_APPLTYPEOFRXACCESSINFO:
    {
      VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetRxSigBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo)); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_CSL03 */
      break;
    }
#  endif
#  if (COM_RXDYNSIGNALTMPLENGTHFORSIGNALGROUPS == STD_ON)
    case COM_UINT8_DYN_APPLTYPEOFRXACCESSINFO:
    {
      PduLengthType dynLength;
      Com_RxTpInfoIdxOfRxPduInfoType rxTpPduInfoIdx = Com_GetRxTpInfoIdxOfRxPduInfo(Com_GetRxPduInfoIdxOfRxAccessInfo(idxRxAccessInfo));
      dynLength = Com_GetRxDynSignalTmpLengthForSignalGroups(rxTpPduInfoIdx);
      if(dynLength <= Com_GetRxSigBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo))  /* COV_COM_SILENT_TX */
      {
        Com_SetRxDynSignalLength(rxTpPduInfoIdx, dynLength);    /* SBSW_COM_CSL02 */
        VStdMemCpyRamToRam(Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedShdBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), dynLength);     /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
      }
      break;
    }
#  endif
    default:   /* COV_COM_MISRA */
      break;
  }
# endif
}        /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */
#endif

#if ((COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_EvaluateSignalTriggerConditionAndRequestTransmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_EvaluateSignalTriggerConditionAndRequestTransmit(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr,
                                                                                                      Com_TxPduInfoIterType idxTxPduInfo)
{
  boolean TriggerWithoutRepetition = FALSE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the passed Tx ComSignal has a configured WITHOUT_REPETITION transfer property, the transmission is performed without repetitions */
# if (COM_WITHOUTREPOFTXSIGINFO == STD_ON)
  if(Com_IsWithoutRepOfTxSigInfo(idxTxSigInfo))
  {
    TriggerWithoutRepetition = TRUE;
  }
# endif
# if (COM_TRIGGEREDOFTXSIGINFO == STD_ON)
  /* #20 If the passed Tx ComSignal has a triggered transfer property */
  if(Com_IsTriggeredOfTxSigInfo(idxTxSigInfo))  /* PRQA S 2842 */ /* MD_Com_2842 */ /* COV_COM_ONLY_TRIGGERED_SIG */
  {
    /* #30 Trigger the deferred ComIPdu transmission */
    Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(idxTxPduInfo, TriggerWithoutRepetition);
  }
  else
# endif
# if (COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON)
    /* #40 If the passed Tx ComSignal has a triggered on change transfer property and if the value has changed */
  if(Com_IsOnChangeUsedOfTxSigInfo(idxTxSigInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_OnChangeIdxOfTxSigInfoType idxFilterInfo = Com_GetOnChangeIdxOfTxSigInfo(idxTxSigInfo);
    /* Info: OnChange is indirection to FilterInfo */
    if(TRUE == Com_TxSignal_EvaluateFilter(idxTxSigInfo, (uint32) idxFilterInfo, newValuePtr, FALSE))   /* SBSW_COM_FCTCALL_WITH_P2CONST */
    {
      /* #50 Trigger the deferred ComIPdu transmission */
      Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(idxTxPduInfo, TriggerWithoutRepetition);
    }
  }
  else
# endif
  {
    /* #60 If the Signal has PENDING transfer property, do nothing */
  }
  COM_DUMMY_STATEMENT(TriggerWithoutRepetition);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValuePtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_EvaluateGroupSignalTriggerConditionAndRequestTransmit
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_EvaluateGroupSignalTriggerConditionAndRequestTransmit(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr)
{
  boolean TriggerWithoutRepetition = FALSE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the passed Tx ComGroupSignal has a configured WITHOUT_REPETITION transfer property, the transmission is performed without repetitions */
# if (COM_WITHOUTREPOFTXGRPSIGINFO == STD_ON)
  if(Com_IsWithoutRepOfTxGrpSigInfo(idxTxGrpSigInfo))
  {
    TriggerWithoutRepetition = TRUE;
  }
# endif
# if (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON)
  /* #20 If the passed Tx ComGroupSignal has a triggered transfer property */
  if(Com_IsTriggeredOfTxGrpSigInfo(idxTxGrpSigInfo))    /* PRQA S 2842 */ /* MD_Com_2842 */ /* COV_COM_ONLY_TRIGGERED_SIG */
  {
    /* #30 Set the signal group event flag */
    Com_SendSignal_SetSigGrpEventFlag(Com_GetTxSigGrpInfoIdxOfTxGrpSigInfo(idxTxGrpSigInfo), TriggerWithoutRepetition);
  }
  else
# endif
# if (COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON)
    /* #40 If the passed Tx ComSignal has a triggered on change transfer property and if the value has changed */
  if(Com_IsOnChangeUsedOfTxGrpSigInfo(idxTxGrpSigInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_OnChangeIdxOfTxGrpSigInfoType idxFilterInfo = Com_GetOnChangeIdxOfTxGrpSigInfo(idxTxGrpSigInfo);
    /* Info: OnChange is indirection to FilterInfo */
    if(TRUE == Com_TxGroupSignal_EvaluateFilter(idxTxGrpSigInfo, (uint32) idxFilterInfo, newValuePtr, FALSE))   /* SBSW_COM_FCTCALL_WITH_P2CONST */
    {
      /* #50 Set the signal group event flag */
      Com_SendSignal_SetSigGrpEventFlag(Com_GetTxSigGrpInfoIdxOfTxGrpSigInfo(idxTxGrpSigInfo), TriggerWithoutRepetition);
    }
  }
  else
# endif
  {
    /* #60 If the passed Tx ComGroupSignal has a PENDING transfer property, do nothing */
  }
  COM_DUMMY_STATEMENT(TriggerWithoutRepetition);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValuePtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SendSignal_SetSigGrpEventFlag
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_SetSigGrpEventFlag(Com_TxSigGrpInfoIdxOfTxGrpSigInfoType idxTxSigGrpInfo, boolean TriggerWithoutRepetition)
{
# if (COM_WITHOUTREPOFTXGRPSIGINFO == STD_ON)
  /* #10 If the passed Tx ComSignalGroup has a _WITHOUT_REPETITION transfer property, set the TRANSMIT signal group event flag */
  if(TriggerWithoutRepetition == TRUE)
  {
    Com_SetSigGrpEventFlag(idxTxSigGrpInfo,     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
                           (Com_GetSigGrpEventFlag(idxTxSigGrpInfo) | COM_TX_SIGIF_GROUPEVENTFLAG));
  }
  /* #20 Otherwise, set the TRANSMIT and WITH_REPETITION signal group event flags */
  else
# endif
  {
    Com_SetSigGrpEventFlag(idxTxSigGrpInfo,     /* SBSW_COM_IDXPARAM_INTERNALFCT_CSL02 */
                           (Com_GetSigGrpEventFlag(idxTxSigGrpInfo) | COM_TX_SIGIF_GROUPEVENTREPETITION));
  }

  COM_DUMMY_STATEMENT(TriggerWithoutRepetition);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_TXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalIf_WriteSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalIf_WriteSignal(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length, Com_TxPduInfoIterType idxTxPduInfo)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
# if (COM_UBMASKUSEDOFTXSIGINFO == STD_ON)
  /* #10 If the passed ComSignal has an UpdateBit, set the UpdateBit in the Tx ComIPdu buffer */
  if(Com_IsUbMaskUsedOfTxSigInfo(idxTxSigInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_IsTxBufferUbIdxInTxBufferUsedOfTxSigInfo(idxTxSigInfo) && (Com_GetUbMaskOfTxSigInfo(idxTxSigInfo) == COM_CONSTVALUEUINT8_UBMASKOFTXSIGINFO)) /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ /* TxBufferUbIdx is always present if a UbMask exists. The Mask is always uint8 */
    {
      Com_TxBufferEndIdxOfTxPduInfoType ubIdx = Com_GetTxBufferUbIdxInTxBufferIdxOfTxSigInfo(idxTxSigInfo);
      uint8 temp = Com_GetTxBuffer(ubIdx);
      Com_SetTxBuffer(ubIdx, (temp | Com_GetConstValueUInt8(Com_GetUbMaskIdxOfTxSigInfo(idxTxSigInfo))));       /* SBSW_COM_CSL03 */
    }
  }
# endif
# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON))
  if(Com_IsTxTpInfoUsedOfTxPduInfo(idxTxPduInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #20 If the passed ComSignal is a dynamic length signal, update the temp and the normal Tx ComIPdu length */
    if(Com_GetApplTypeOfTxSigInfo(idxTxSigInfo) == COM_UINT8_DYN_APPLTYPEOFTXSIGINFO)   /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
    {
      Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(idxTxPduInfo);
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
      Com_SetTxSduLength(idxTxPduInfo, (Com_TxSduLengthType) (Com_GetBytePositionOfTxSigInfo(idxTxSigInfo) + Length));  /* PRQA S 2986 */ /* MD_Com_2985_2986 */ /* SBSW_COM_CSL02 */
#  else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      Com_SetTxSduLength(idxTxPduInfo, Com_GetStartByteInPduPositionOfTxSigInfo(idxTxSigInfo) + Length);        /* SBSW_COM_CSL02 */
#  endif
      Com_SetTxDynSignalLength(txTpPduInfoIdx, (Com_TxDynSignalLengthType) Length);     /* SBSW_COM_CSL02 */
    }
  }
# endif
# if (COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON)
  /* #30 If a TxBuffer exists for the TxSignal, copy the passed signal data to the Tx ComIPdu buffer */
  if(Com_IsTxBufferUsedOfTxSigInfo(idxTxSigInfo))       /* COV_COM_CSL03_ISUSED_OPTIONAL_INDIRECTION */
  {
    Com_Serializer_WriteSignal(idxTxSigInfo, (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr); /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
  }
# endif

  COM_DUMMY_STATEMENT(Length);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxTxPduInfo);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxTxSigInfo);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalIf_WriteGroupSignal
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SignalIf_WriteGroupSignal(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length, Com_TxPduInfoIterType idxTxPduInfo) /* PRQA S 3206 */ /* MD_Com_3206 */
{
# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXGRPSIGINFO == STD_ON))
  if(Com_IsTxTpInfoUsedOfTxPduInfo(idxTxPduInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #10 If the passed ComGroupSignal is a dynamic length signal, update the temp length of the related ComIPdu */
    if(Com_GetApplTypeOfTxGrpSigInfo(idxTxGrpSigInfo) == COM_UINT8_DYN_APPLTYPEOFTXGRPSIGINFO)  /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */ /* COV_COM_UINT8_DYN_APPLTYPE */
    {
      Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(idxTxPduInfo);
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
      Com_SetTxTmpTpPduLength(txTpPduInfoIdx, (Com_TxSduLengthType) (Com_GetBytePositionOfTxGrpSigInfo(idxTxGrpSigInfo) + Length));     /* PRQA S 2986 */ /* MD_Com_2985_2986 */ /* SBSW_COM_CSL02 */
#  else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      Com_SetTxTmpTpPduLength(txTpPduInfoIdx, (Com_TxSduLengthType) (Com_GetStartByteInPduPositionOfTxGrpSigInfo(idxTxGrpSigInfo) + Length));   /* SBSW_COM_CSL02 */
#  endif
      Com_SetTxDynSignalLength(txTpPduInfoIdx, (Com_TxDynSignalLengthType) Length);     /* SBSW_COM_CSL02 */
    }
  }
# endif
# if (COM_TXBUFFERUSEDOFTXSIGGRPINFO == STD_ON)
  /* #20 If a shadow buffer is used, copy the passed signal data to the shadow buffer */
  if(Com_IsTxBufferUsedOfTxSigGrpInfo(Com_GetTxSigGrpInfoIdxOfTxGrpSigInfo(idxTxGrpSigInfo)))   /* COV_COM_CSL03_ISUSED_OPTIONAL_INDIRECTION */ /* PRQA S 2842 */ /* MD_Com_2842 */ /* 2842: Index idxTxGrpSigInfo originates from Com_SendSignal_Processing(). It is retrieved via the optional indirection Com_GetTxGrpSigInfoIdxOfTxAccessInfo with a prior isUsed check. TxSigGrpInfoIdxOfTxGrpSigInfo is a mandatory indirection */
  {
    Com_Serializer_WriteGroupSignal(idxTxGrpSigInfo, (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr); /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
  }
# endif

  COM_DUMMY_STATEMENT(Length);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(SignalDataPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxTxPduInfo);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxTxGrpSigInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroup_TriggerEventProcessing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(uint8, COM_CODE) Com_SendSignalGroup_TriggerEventProcessing(
# if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
                                                                                   Com_SignalIdType idxTxSigGrpInfo,
# endif
                                                                                   PduIdType idxTxPduInfo)
{
  uint8 retVal = E_OK;          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the passed Tx ComIPdu is active */
  if(Com_IsTxPduGrpActive(idxTxPduInfo))        /* COV_COM_NO_IPDUGROUPS */
  {
# if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
    /* #20 If at least one related ComGroupSignal was triggered, set the deferred transmit event */
    if(0u < Com_GetSigGrpEventFlag(idxTxSigGrpInfo))    /* COV_COM_ONLY_TRIGGERED_SIGGRP */
    {
      boolean TriggerWithoutRepetition;
#  if (COM_WITHOUTREPOFTXGRPSIGINFO == STD_ON)
      /* #30 If at least one ComGroupSignal with TRIGGERED transfer property was triggered, trigger the transmission with repetitions */
      if((Com_GetSigGrpEventFlag(idxTxSigGrpInfo) & COM_TX_SIGIF_GROUPREPETITION) == 0u)
      {
        TriggerWithoutRepetition = TRUE;
      }
      else
#  endif
      {
        TriggerWithoutRepetition = FALSE;
      }

      Com_TxModeHdlr_TriggerDeferredTransmitAndSetTimer(idxTxPduInfo, TriggerWithoutRepetition);
      Com_SetSigGrpEventFlag(idxTxSigGrpInfo, 0u);      /* SBSW_COM_IDXPARAM_INTERNALFCT_DET_CSL02 */
    }
# endif
    /* #40 Return E_OK */
  }
  /* #50 Otherwise, return COM_SERVICE_NOT_AVAILABLE */
  else
  {
    retVal = COM_SERVICE_NOT_AVAILABLE;
  }
  return retVal;
}
#endif

#if (COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_CheckSignalFilter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 ***********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_CheckSignalFilter(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr, Com_TxPduInfoIterType idxTxPduInfo)
{
  /* #10 If the passed Tx ComSignal has filter */
  if(Com_IsFilterInfoUsedOfTxSigInfo(idxTxSigInfo) && Com_IsTxFilterInitStateUsedOfTxSigInfo(idxTxSigInfo))     /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */
  {
    Com_FilterInfoIdxOfTxSigInfoType idxFilterInfo = Com_GetFilterInfoIdxOfTxSigInfo(idxTxSigInfo);

    /* #20 Evaluate the filter state */
    boolean filterState = Com_TxSignal_EvaluateFilter(idxTxSigInfo, (uint32) idxFilterInfo, newValuePtr, TRUE); /* SBSW_COM_FCTCALL_WITH_P2CONST */
    boolean oldFilterState = Com_IsTxFilterState(Com_GetTxFilterInitStateIdxOfTxSigInfo(idxTxSigInfo));

    /* #30 Update the tx filter state */
    Com_SetTxFilterState(Com_GetTxFilterInitStateIdxOfTxSigInfo(idxTxSigInfo), filterState);    /* SBSW_COM_CSL02_CSL03 */

    /* #40 If filter state is different to the current filter state, update the transition mode state */
    if(oldFilterState != filterState)   /* COV_COM_FILTERSTATE */
    {
      Com_TxModeHdlr_UpdateTMS(idxTxPduInfo);
    }
  }
}
#endif

#if (COM_FILTERINFOUSEDOFTXGRPSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_CheckGroupSignalFilter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 ***********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_SendSignal_CheckGroupSignalFilter(Com_TxGrpSigInfoIterType idxTxGrpSigInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr)
{
  /* #10 If the passed Tx ComGroupSignal has a filter */
  if(Com_IsFilterInfoUsedOfTxGrpSigInfo(idxTxGrpSigInfo) && Com_IsTxFilterInitStateUsedOfTxGrpSigInfo(idxTxGrpSigInfo)) /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */
  {
    Com_FilterInfoIdxOfTxGrpSigInfoType idxFilterInfo = Com_GetFilterInfoIdxOfTxGrpSigInfo(idxTxGrpSigInfo);

    /* #20 Evaluate the filter state */
    boolean filterState = Com_TxGroupSignal_EvaluateFilter(idxTxGrpSigInfo, (uint32) idxFilterInfo, newValuePtr, TRUE); /* SBSW_COM_FCTCALL_WITH_P2CONST */

    /* #30 Update the tx filter state */
    Com_SetTxFilterState(Com_GetTxFilterInitStateIdxOfTxGrpSigInfo(idxTxGrpSigInfo), filterState);      /* SBSW_COM_CSL02_CSL03 */
  }
}
#endif


#if ((COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON) && ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON)) && ((COM_TXSIGGRPONCHANGEMASKONCHANGEUSEDOFTXSIGGRPINFO == STD_ON) || (COM_TXSIGGRPONCHANGEMASKONCHANGEWITHOUTREPUSEDOFTXSIGGRPINFO == STD_ON)))
/**********************************************************************************************************************
  Com_SendSignalGroupArrayHasChanged
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_SendSignalGroupArrayHasChanged(P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr, P2CONST(uint8, AUTOMATIC, COM_VAR_NO_INIT) pIpduBuf, uint32 MaskLength)
{
  boolean retVal = FALSE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint32 i;
  /* #10 Bytewise comparison of signal group array and ipdu-buffer, if any change has occurred */
  for(i = 0; i < MaskLength; i++)
  {
    /* Bits that to do not belong to a group signal with a certain transfer property are masked out with the provided mask. */
    if((pIpduBuf[i] & maskPtr[i]) != (SignalGroupArrayPtr[i] & maskPtr[i]))
    {
      retVal = TRUE;
      break;
    }
  }
  return retVal;
}
#endif

#if(COM_SIGGRPARRAYFILTERINFO == STD_ON)
/**********************************************************************************************************************
  Com_EvaluateSigGrpArrFilterProcessing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_EvaluateSigGrpArrFilterProcessing(Com_SigGrpArrayFilterInfoIterType idxFilterInfo,
                                                                               P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr,
                                                                               P2CONST(uint8, AUTOMATIC, COM_PBCFG) filterValueXPtr, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) newValuePtr,
                                                                               uint32 maskLength)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint32 i;

  /* #10 Bytewise evaluation of SignalGroup Filter with ArrayAccess enabled */
  switch (Com_GetFilterAlgoOfSigGrpArrayFilterInfo(idxFilterInfo))
  {

# if(COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFSIGGRPARRAYFILTERINFO == STD_ON)
      /* #20 Evaluate SignalGroup Array according to MASK_NEW_EQUALS_X filterAlgorithm */
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFSIGGRPARRAYFILTERINFO:
    {
      for(i = 0; i < maskLength; i++)
      {
        /* #30 Stop filter evaluation if at least one byte evaluates to TRUE */
        if((newValuePtr[i] & maskPtr[i]) != filterValueXPtr[i])
        {
          filterState = TRUE;
          break;
        }
      }
    }
      break;
# endif
# if(COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFSIGGRPARRAYFILTERINFO == STD_ON)
      /* #40 Evaluate SignalGroup Array according to MASK_DIFFERS_X filterAlgorithm */
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFSIGGRPARRAYFILTERINFO:
    {
      filterState = TRUE;
      for(i = 0; i < maskLength; i++)
      {
        /* #50 Stop filter evaluation if at least one byte evaluates to TRUE */
        if((newValuePtr[i] & maskPtr[i]) != filterValueXPtr[i])
        {
          filterState = FALSE;
          break;
        }
      }
    }
      break;
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  return filterState;
}
#endif

#if(COM_SIGGRPARRAYFILTERINFOUSEDOFTXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_EvaluateSigGrpArrFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_EvaluateSigGrpArrFilter(Com_SigGrpArrayFilterInfoIterType idxFilterInfo, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) newValuePtr)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint32 maskLength = Com_GetConstValueUInt8FilterMaskLengthOfSigGrpArrayFilterInfo(idxFilterInfo);
  Com_ConstValueUInt8FilterMaskStartIdxOfSigGrpArrayFilterInfoType idxConstValueUInt8FilterMask = Com_GetConstValueUInt8FilterMaskStartIdxOfSigGrpArrayFilterInfo(idxFilterInfo);
  Com_ConstValueUInt8FilterValueXStartIdxOfSigGrpArrayFilterInfoType idxConstValueUInt8FilterValueX = Com_GetConstValueUInt8FilterValueXStartIdxOfSigGrpArrayFilterInfo(idxFilterInfo);

  P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr = Com_GetAddrConstValueUInt8(idxConstValueUInt8FilterMask);
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) filterValueXPtr = Com_GetAddrConstValueUInt8(idxConstValueUInt8FilterValueX);

  /* #10 Evaluate filter state */
  filterState = Com_EvaluateSigGrpArrFilterProcessing(idxFilterInfo, maskPtr, filterValueXPtr, newValuePtr, maskLength);        /* SBSW_COM_CSL02 */

  return filterState;
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if ((COM_RXACCESSINFO == STD_ON) && ((COM_BUFFERUSEDOFRXACCESSINFO == STD_ON) || (COM_RXSIGBUFFERARRAYBASEDBUFFERUSEDOFRXACCESSINFO == STD_ON)))
/**********************************************************************************************************************
  Com_ReceiveSignal_GetRxSigBuffer
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReceiveSignal_GetRxSigBuffer(Com_SignalIdType idxRxAccessInfo, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr)
{
  /* #10 If the passed ComSignal uses a buffer, copy the currently stored value to passed SignalDataPtr */
# if(COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
  if(Com_IsBufferUsedOfRxAccessInfo(idxRxAccessInfo))       /* COV_COM_CSL03_ISUSED_OPTIONAL_INDIRECTION */
  {
    switch (Com_GetBufferOfRxAccessInfo(idxRxAccessInfo))
    {
#  if (COM_EXISTS_RXSIGBUFFERUINT8_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERUINT8_BUFFEROFRXACCESSINFO:
      {
        *((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferUInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));  /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERSINT8_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERSINT8_BUFFEROFRXACCESSINFO:
      {
        *((P2VAR(sint8, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferSInt8(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));  /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERUINT16_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERUINT16_BUFFEROFRXACCESSINFO:
      {
        *((P2VAR(uint16, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferUInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERSINT16_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERSINT16_BUFFEROFRXACCESSINFO:
      {
        *((P2VAR(sint16, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferSInt16(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERUINT32_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERUINT32_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(uint32, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferUInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERSINT32_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERSINT32_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(sint32, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferSInt32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERUINT64_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERUINT64_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(uint64, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferUInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERSINT64_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERSINT64_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(sint64, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferSInt64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));        /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERFLOAT32_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERFLOAT32_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(float32, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferFloat32(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));      /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
#  if (COM_EXISTS_RXSIGBUFFERFLOAT64_BUFFEROFRXACCESSINFO == STD_ON)
      case COM_RXSIGBUFFERFLOAT64_BUFFEROFRXACCESSINFO:
      {
        SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
        *((P2VAR(float64, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr) = Com_GetRxSigBufferFloat64(Com_GetBufferIdxOfRxAccessInfo(idxRxAccessInfo));      /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
        SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
        break;
      }
#  endif
      default:   /* COV_COM_MISRA */
        break;
    }
  }
# endif
# if (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON)
  if(Com_GetApplTypeOfRxAccessInfo(idxRxAccessInfo) == COM_UINT8_N_APPLTYPEOFRXACCESSINFO)  /* COV_COM_ONLY_ARRAYBASED_RX_SIGGRP_SIG_01 */
  {
    SchM_Enter_Com_COM_EXCLUSIVE_AREA_RX();
    VStdMemCpyRamToRam((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) SignalDataPtr, Com_GetAddrRxSigBufferArrayBased(Com_GetRxSigBufferArrayBasedBufferStartIdxOfRxAccessInfo(idxRxAccessInfo)), Com_GetRxSigBufferArrayBasedBufferLengthOfRxAccessInfo(idxRxAccessInfo));  /* PRQA S 0315, 0316 */ /* MD_MSR_VStdLibCopy, MD_Com_0316_0317 */ /* SBSW_COM_PTR_API */
    SchM_Exit_Com_COM_EXCLUSIVE_AREA_RX();
  }
# endif
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


#if (COM_SHDBUFFERREQUIREDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_ReadSignalGroupData
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ReadSignalGroupData(Com_SignalGroupIdType SignalGroupId)
{
  /* #10 Copy the values of all ComGroupSignals of the passed ComSignalsGroup from the shadow buffer to the ComGroupSignal buffer */
  Com_RxAccessInfoIterType rxAccessInfoIndidx = Com_GetRxAccessInfoGrpSigIndStartIdxOfRxSigGrpInfo(SignalGroupId);      /* PRQA S 2842 */ /* MD_Com_2842 */
  for(; rxAccessInfoIndidx < Com_GetRxAccessInfoGrpSigIndEndIdxOfRxSigGrpInfo(SignalGroupId); rxAccessInfoIndidx++)
  {
    Com_RxAccessInfoIterType idxRxAccessInfo = Com_GetRxAccessInfoGrpSigInd(rxAccessInfoIndidx);
    Com_ReadGroupSignalFromShadowBuffer(idxRxAccessInfo);
  }

  COM_DUMMY_STATEMENT(SignalGroupId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (COM_TXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroup_Processing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroup_Processing(Com_SignalIdType idxTxSigGrpInfo, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) ShadowBufferPtr)
{
  Com_TxPduInfoIdxOfTxSigGrpInfoType idxTxPduInfo = Com_GetTxPduInfoIdxOfTxSigGrpInfo(idxTxSigGrpInfo);
  uint8 retVal = E_OK;          /* PRQA S 2981 */ /* MD_MSR_RetVal */

# if (COM_TXFILTERINITSTATEUSEDOFTXMODEINFO == STD_ON)
  /* #10 If the passed Tx ComSignalGroup has filter, update the transition mode state */
  if(Com_IsTxFilterInitStateUsedOfTxModeInfo(idxTxPduInfo))     /* COV_COM_NO_GRPSIG_FILTER_PRESENT */
  {
    Com_TxModeHdlr_UpdateTMS((PduIdType) idxTxPduInfo);
  }
# endif
# if (COM_UBMASKUSEDOFTXSIGGRPINFO == STD_ON)
  /* #20 If the passed Tx ComSingalGroup has an UpdateBit, set the UpdateBit in the related Tx ComIPdu buffer */
  if(Com_IsUbMaskUsedOfTxSigGrpInfo(idxTxSigGrpInfo))   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    if(Com_IsTxBufferUbIdxInTxBufferUsedOfTxSigGrpInfo(idxTxSigGrpInfo) && (Com_GetUbMaskOfTxSigGrpInfo(idxTxSigGrpInfo) == COM_CONSTVALUEUINT8_UBMASKOFTXSIGGRPINFO))  /* COV_COM_CSL04_DESTINATION_ENUM_CHECK */ /* TxBufferUbIdx is always present if a UbMask exists. The Mask is always uint8 */
    {
      Com_TxBufferEndIdxOfTxPduInfoType ubIdx = Com_GetTxBufferUbIdxInTxBufferIdxOfTxSigGrpInfo(idxTxSigGrpInfo);
      uint8 temp = Com_GetTxBuffer(ubIdx);
      Com_SetTxBuffer(ubIdx, (temp | Com_GetConstValueUInt8(Com_GetUbMaskIdxOfTxSigGrpInfo(idxTxSigGrpInfo)))); /* SBSW_COM_CSL03 */
    }
  }
# endif

# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  if(Com_IsTxTpInfoUsedOfTxPduInfo(idxTxPduInfo))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    /* #30 If the passed Tx ComIPdu is a Tp Pdu and the Tp ComIPdu is in READY state, update the shadow and set the Tx ComIPdu length to the stored temp length for dynamic length signals */
    Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(idxTxPduInfo);
    if(Com_GetTxTpConnectionState(txTpPduInfoIdx) == COM_READY_TXTPCONNECTIONSTATE)
    {
#  if (COM_TXSIGGRPMASK == STD_ON)
      Com_TxBuffer_WriteSignalGroup(idxTxSigGrpInfo, ShadowBufferPtr);  /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
#  if (COM_TXACCESSINFODYNSIGUSEDOFTXTPINFO == STD_ON)
      if(Com_IsTxAccessInfoDynSigUsedOfTxTpInfo(txTpPduInfoIdx))        /* COV_COM_UINT8_DYN_APPLTYPE */
      {
        Com_SetTxSduLength(idxTxPduInfo, Com_GetTxTmpTpPduLength(txTpPduInfoIdx));      /* SBSW_COM_CSL02 */
      }
#  endif
    }
    /* #40 Otherwise, return COM_BUSY */
    else
    {
      retVal = COM_BUSY;
    }
  }
  else
# endif
  {
# if (COM_TXSIGGRPMASK == STD_ON)
    /* #50 Copy the shadow buffer to the related Tx ComIPdu buffer */
    Com_TxBuffer_WriteSignalGroup(idxTxSigGrpInfo, ShadowBufferPtr);    /* SBSW_COM_FCTCALL_WITH_P2CONST */
# endif
  }
# if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
  if(retVal == E_OK)
# endif
  {
    /* #60 Do trigger event processing */
    retVal = Com_SendSignalGroup_TriggerEventProcessing(
# if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
                                                         idxTxSigGrpInfo,
# endif
                                                         (PduIdType) idxTxPduInfo);
  }

  COM_DUMMY_STATEMENT(ShadowBufferPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

#if (COM_TXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal_Processing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignal_Processing(Com_TxAccessInfoIterType txAccessInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length)
{
  uint8 retVal = E_OK;          /* PRQA S 2981 */ /* MD_MSR_RetVal */
  P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) SignalDataPtr;

# if(COM_TXSIGINFO == STD_ON)
  if(Com_IsTxSigInfoUsedOfTxAccessInfo(txAccessInfo))   /* COV_COM_ONLY_SIG_PRESENT */
  {
    Com_TxSigInfoIterType txSignalId = Com_GetTxSigInfoIdxOfTxAccessInfo(txAccessInfo);
    Com_TxPduInfoIterType idxTxPduInfo = Com_GetTxPduInfoIdxOfTxSigInfo(txSignalId);

#  if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
    /* #10 If the passed Tx ComIPdu is a Tp Pdu, check if the Tp connection is in READY state, if not return COM_BUSY */
    if(Com_IsTxTpInfoUsedOfTxPduInfo(idxTxPduInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(idxTxPduInfo);
      if(Com_GetTxTpConnectionState(txTpPduInfoIdx) != COM_READY_TXTPCONNECTIONSTATE)
      {
        /* \trace SPEC-2736898 */ /* \trace SPEC-2736899 */
        retVal = COM_BUSY;
      }
    }
#  endif

    if(retVal == E_OK)  /* COV_COM_NO_TP */ /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
    {
#  if (COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON)
      /* #30 Check the filter state of the passed Tx ComSignal and update the transition mode state if required */
      Com_SendSignal_CheckSignalFilter(txSignalId, newValuePtr, idxTxPduInfo);  /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
      Com_SignalIf_WriteSignal(txSignalId, SignalDataPtr, Length, idxTxPduInfo);        /* SBSW_COM_FCTCALL_WITH_P2CONST */

      /* #60 If the Tx ComIPdu is active, evaluate the trigger conditions, otherwise return COM_SERVICE_NOT_AVAILABLE */
      if(Com_IsTxPduGrpActive(idxTxPduInfo))    /* COV_COM_NO_IPDUGROUPS */
      {
#  if ((COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXSIGINFO == STD_ON))
        Com_SendSignal_EvaluateSignalTriggerConditionAndRequestTransmit(txSignalId, newValuePtr, idxTxPduInfo); /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
      }
      else
      {
        retVal = COM_SERVICE_NOT_AVAILABLE;
      }
#  if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_FILTERINITVALUEIDXOFTXSIGINFO == STD_ON))
      /* #70 Update the filter old value of the signal */
      Com_SetTxSignalFilterOldValueX(txSignalId, SignalDataPtr, Length);        /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
    }
  }
# endif

# if(COM_TXGRPSIGINFOUSEDOFTXACCESSINFO == STD_ON)
  if(Com_IsTxGrpSigInfoUsedOfTxAccessInfo(txAccessInfo))        /* COV_COM_ONLY_SIGGRP_PRESENT */
  {
    Com_TxGrpSigInfoIterType txGrpSigId = Com_GetTxGrpSigInfoIdxOfTxAccessInfo(txAccessInfo);
    Com_TxPduInfoIterType idxTxPduInfo = Com_GetTxPduInfoIdxOfTxGrpSigInfo(txGrpSigId);
#  if (COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON)
    /* #10 If the passed Tx ComIPdu is a Tp Pdu, check if the Tp connection is in READY state, if not return COM_BUSY */
    if(Com_IsTxTpInfoUsedOfTxPduInfo(idxTxPduInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
    {
      Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(idxTxPduInfo);
      if(Com_GetTxTpConnectionState(txTpPduInfoIdx) != COM_READY_TXTPCONNECTIONSTATE)
      {
        /* \trace SPEC-2736898 */ /* \trace SPEC-2736899 */
        retVal = COM_BUSY;
      }
    }
#  endif

    if(retVal == E_OK)  /* COV_COM_NO_TP */ /* PRQA S 2991, 2995 */ /* MD_Com_2991, MD_Com_2995 */
    {
#  if (COM_FILTERINFOUSEDOFTXGRPSIGINFO == STD_ON)
      /* #40 Check the filter state of the passed Tx ComGroupSignal */
      Com_SendSignal_CheckGroupSignalFilter(txGrpSigId, newValuePtr);   /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
      /* #50 Write the passed signal or groupSignal data */
      Com_SignalIf_WriteGroupSignal(txGrpSigId, SignalDataPtr, Length, idxTxPduInfo);   /* SBSW_COM_FCTCALL_WITH_P2CONST */

      /* #60 If the Tx ComIPdu is active, evaluate the trigger conditions, otherwise return COM_SERVICE_NOT_AVAILABLE */
      if(Com_IsTxPduGrpActive(idxTxPduInfo))    /* COV_COM_NO_IPDUGROUPS */
      {
#  if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
        Com_SendSignal_EvaluateGroupSignalTriggerConditionAndRequestTransmit(txGrpSigId, newValuePtr);  /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
      }
      else
      {
        retVal = COM_SERVICE_NOT_AVAILABLE;
      }
#  if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_FILTERINITVALUEUSEDOFTXGRPSIGINFO == STD_ON))
      /* #80 Update the filter old value of the group signal */
      Com_SetTxGroupSignalFilterOldValueX(txGrpSigId, SignalDataPtr, Length);   /* SBSW_COM_FCTCALL_WITH_P2CONST */
#  endif
    }
  }

# endif

  COM_DUMMY_STATEMENT(newValuePtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}       /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (COM_ARRAYACCESSUSEDOFTXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroupArray_Processing
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_SendSignalGroupArray_Processing(Com_SignalGroupIdType SignalGroupId, P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalGroupArrayPtr)
{
# if(COM_SIGGRPARRAYFILTERINFOUSEDOFTXSIGGRPINFO == STD_ON)
  /* #10 If filter is configured, evaluate and update the filter state */
  if(Com_IsSigGrpArrayFilterInfoUsedOfTxSigGrpInfo(SignalGroupId) && Com_IsTxFilterInitStateUsedOfTxSigGrpInfo(SignalGroupId))  /* COV_COM_CSL03_ISUSED_OPTIONAL_INDIRECTION */ /* SigGrpArrayFilterInfo and TxFilterInitState are always either both present or both absent. The second expression is therefore never evaluated. */
  {
    Com_SigGrpArrayFilterInfoIterType idxFilterInfo = Com_GetSigGrpArrayFilterInfoStartIdxOfTxSigGrpInfo(SignalGroupId);

    Com_TxFilterInitStateIterType idxTxFilterInitState = Com_GetTxFilterInitStateStartIdxOfTxSigGrpInfo(SignalGroupId);
    boolean filterState = FALSE;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

    for(; idxFilterInfo < Com_GetSigGrpArrayFilterInfoEndIdxOfTxSigGrpInfo(SignalGroupId); idxFilterInfo++)
    {
      filterState = Com_EvaluateSigGrpArrFilter(idxFilterInfo, &(SignalGroupArrayPtr[Com_GetOffsetInSignalGroupOfSigGrpArrayFilterInfo(idxFilterInfo)]));       /* SBSW_COM_CSL02 */
      if(filterState == TRUE)
      {
        break;
      }
    }

    /* Update the tx filterState of the SignalGroup for each GroupSignal */
    for(; idxTxFilterInitState < Com_GetTxFilterInitStateEndIdxOfTxSigGrpInfo(SignalGroupId); idxTxFilterInitState++)
    {
      Com_SetTxFilterState(idxTxFilterInitState, filterState);  /* SBSW_COM_CSL02 */
    }
  }
# endif

# if ((COM_ONCHANGEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_TRIGGEREDOFTXGRPSIGINFO == STD_ON))
  /* #20 If TRIGGERED BIT is set for the signal group */
  if(Com_TxSigIf_IsTxSigGrpInfoTriggered(SignalGroupId))        /* COV_COM_ONLY_TRIGGERED_SIGGRP */
  {
    boolean doTrigger = FALSE;
    boolean withoutRepetition = TRUE;   /* Will only be evaluated for COM_WITHOUTREPOFTXSIGINFO == STD_ON */ /* PRQA S 2981 */ /* MD_MSR_RetVal */

    /* #30 If transmission property of signal group equals TRIGGERED_ON_CHANGE or TRIGGERED_ON_CHANGE_WITHOUT_REPETITION */
    if(Com_TxSigIf_IsTxSigGrpInfoOnChange(SignalGroupId))       /* COV_COM_TRIGGERED_ONCHG_SIGGRP */
    {
#  if ((COM_TXSIGGRPONCHANGEMASKONCHANGEUSEDOFTXSIGGRPINFO == STD_ON) || (COM_TXSIGGRPONCHANGEMASKONCHANGEWITHOUTREPUSEDOFTXSIGGRPINFO == STD_ON))
      Com_TxPduInfoIdxOfTxSigGrpInfoType ipdu = Com_GetTxPduInfoIdxOfTxSigGrpInfo(SignalGroupId);
#  endif

#  if (COM_TXSIGGRPONCHANGEMASKONCHANGEUSEDOFTXSIGGRPINFO == STD_ON)    /* Evaluate onChange */
      /* #40 If signal group contains group signals with transmission property TRIGGERED_ON_CHANGE (if COM_TXSIGGRPONCHANGEMASKONCHANGEUSEDOFTXSIGGRPINFO is enabled) */
      if(Com_IsTxSigGrpOnChangeMaskOnChangeUsedOfTxSigGrpInfo(SignalGroupId))   /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        /* Get the indirection to the mask to evaluate if any of the contained group signals has changed */
        P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr = Com_GetAddrTxSigGrpOnChangeMask(Com_GetTxSigGrpOnChangeMaskOnChangeStartIdxOfTxSigGrpInfo(SignalGroupId));

        /* Calculate the position of the first group signal with the transmission property TRIGGERED_ON_CHANGE within the ipdu buffer to compare the stored values */
        P2CONST(uint8, AUTOMATIC, COM_VAR_NO_INIT) pIpduBuf = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxPduInfo(ipdu) + Com_GetSigGroupOnChangeStartPositionOfTxSigGrpInfo(SignalGroupId));

        /* Get the length of the triggered on change mask */
        Com_TxSigGrpOnChangeMaskOnChangeLengthOfTxSigGrpInfoType MaskLength = Com_GetTxSigGrpOnChangeMaskOnChangeLengthOfTxSigGrpInfo(SignalGroupId);

        /* #50 Perform check if any group signal with transmission property TRIGGERED_ON_CHANGE has changed and set transmission initiation flag accordingly */
        doTrigger = Com_SendSignalGroupArrayHasChanged(&(SignalGroupArrayPtr[Com_GetSigGroupOnChangeOffsetOfTxSigGrpInfo(SignalGroupId)]), maskPtr, pIpduBuf, MaskLength);      /* SBSW_COM_COMST_PTR */
      }
#  endif

#  if (COM_TXSIGGRPONCHANGEMASKONCHANGEWITHOUTREPUSEDOFTXSIGGRPINFO == STD_ON)  /* Evaluate onChangeWithoutRepetition */
      /* #60 If no group signal with transmission property TRIGGERED_ON_CHANGE has changed (if COM_TXSIGGRPONCHANGEMASKONCHANGEWITHOUTREPUSEDOFTXSIGGRPINFO is enabled) */
      if(doTrigger == FALSE)
      {
        /* #70 If signal group contains any group signal with transmission property TRIGGERED_ON_CHANGE_WITHOUT_REPETITION */
        if(Com_IsTxSigGrpOnChangeMaskOnChangeWithoutRepUsedOfTxSigGrpInfo(SignalGroupId))       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
        {
          /* Get the indirection to the mask to evaluate if any of the contained group signals with transmission property TRIGGERED_ON_CHANGE_WITHOUT_REPETITION has changed */
          P2CONST(uint8, AUTOMATIC, COM_PBCFG) maskPtr = Com_GetAddrTxSigGrpOnChangeMask(Com_GetTxSigGrpOnChangeMaskOnChangeWithoutRepStartIdxOfTxSigGrpInfo(SignalGroupId));

          /* Calculate the position of the first group signal with the transmission property TRIGGERED_ON_CHANGE_WITHOUT_REPETITION within the ipdu buffer to compare the stored values */
          P2CONST(uint8, AUTOMATIC, COM_VAR_NO_INIT) pIpduBuf =
            Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxPduInfo(ipdu) + Com_GetSigGroupOnChangeWithoutRepStartPositionOfTxSigGrpInfo(SignalGroupId));

          /* Get the length of the triggered on change without repetition mask */
          Com_TxSigGrpOnChangeMaskOnChangeWithoutRepLengthOfTxSigGrpInfoType MaskLength = Com_GetTxSigGrpOnChangeMaskOnChangeWithoutRepLengthOfTxSigGrpInfo(SignalGroupId);

          /* #80 Perform check if any group signal with transmission property TRIGGERED_ON_CHANGE_WITHOUT_REPETITION has changed and set transmission initiation flag accordingly */
          doTrigger = Com_SendSignalGroupArrayHasChanged(&(SignalGroupArrayPtr[Com_GetSigGroupOnChangeWithoutRepOffsetOfTxSigGrpInfo(SignalGroupId)]), maskPtr, pIpduBuf, MaskLength);  /* SBSW_COM_COMST_PTR */
        }
      }
      else
#  endif
      {
#  if (COM_WITHOUTREPOFTXGRPSIGINFO == STD_ON)
        /* #90 Otherwise set the without repetition flag to false to indicate that transmission should be performed with configured amount of repetitions */
        withoutRepetition = FALSE;
#  endif
      }
    }
    /* #100 Otherwise transmission property is assumed to be TRIGGERED or TRIGGERED_WITHOUT_REPETITION */
    else
    {
      /* set transmission initiation flag to true */
      doTrigger = TRUE;
#  if (COM_WITHOUTREPOFTXGRPSIGINFO == STD_ON)
      /* set without repetition flag accordingly to the configured transmission property (if configured) */
      withoutRepetition = Com_TxSigIf_IsTxSigGrpInfoWithoutRepetition(SignalGroupId);
#  endif
    }

    /* #110 If transmission is requested, set group event flag */
    if(doTrigger == TRUE)       /* COV_COM_ONLY_TRIGGERED_SIGGRP */
    {
      Com_SendSignal_SetSigGrpEventFlag((Com_TxSigGrpInfoIdxOfTxGrpSigInfoType) SignalGroupId, withoutRepetition);
    }
    COM_DUMMY_STATEMENT(withoutRepetition);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  }
# endif
  /* #120 Copy the content of the associated signal group array to the associated I-PDU buffer (if COM_TXSIGGRPMASK enabled). */
  return Com_SendSignalGroup_Processing(SignalGroupId, SignalGroupArrayPtr);    /* SBSW_COM_FCTCALL_WITH_P2CONST */
}
#endif

#if ((COM_INVVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_InvalidateSignal_SendSignal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignal_SendSignal(Com_TxAccessInfoIterType txAccessInfo)    /* COV_COM_SIGNALINVALIDATION_ARRAYACCESS */
{
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Com_TxSigInfoIterType idxTxSigInfo = Com_GetTxSigInfoIdxOfTxAccessInfo(txAccessInfo);

  /* #10 Send signal with the invalid value, the invalid value is stored in an ApplType dependent buffer */
# if (COM_INVVALUEUSEDOFTXSIGINFO == STD_ON)
  if(Com_IsInvValueUsedOfTxSigInfo(idxTxSigInfo))     /* PRQA S 2842 */ /* MD_Com_2842 */ /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_InvValueIdxOfTxSigInfoType idxInvValue = Com_GetInvValueIdxOfTxSigInfo(idxTxSigInfo); /* PRQA S 2842 */ /* MD_Com_2842 */ /* idxTxSigInfo is retrieved from the optional indirection via Com_GetTxSigInfoIdxOfTxAccessInfo and is check for validity */
    switch (Com_GetInvValueOfTxSigInfo(idxTxSigInfo))
    {
#  if (COM_EXISTS_CONSTVALUEUINT8_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT8_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt8(idxInvValue), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT8_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUESINT8_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt8(idxInvValue), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT16_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT16_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt16(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT16_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUESINT16_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt16(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT32_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT32_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt32(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT32_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUESINT32_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt32(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT64_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT64_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt64(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT64_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUESINT64_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt64(idxInvValue), 0);      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEFLOAT32_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEFLOAT32_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueFloat32(idxInvValue), 0);     /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEFLOAT64_INVVALUEOFTXSIGINFO == STD_ON)
      case COM_CONSTVALUEFLOAT64_INVVALUEOFTXSIGINFO:
      {
        retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueFloat64(idxInvValue), 0);     /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
      default:       /* COV_COM_MISRA */
        break;
    }
  }
# endif
# if (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFTXSIGINFO == STD_ON)
  if(Com_IsConstValueArrayBasedInvValueUsedOfTxSigInfo(idxTxSigInfo)) /* COV_COM_SIGNALINVALIDATION_ARRAYACCESS_01 */
  {
    Com_ConstValueArrayBasedInvValueEndIdxOfTxSigInfoType idxInvValue = Com_GetConstValueArrayBasedInvValueStartIdxOfTxSigInfo(idxTxSigInfo);
    retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueArrayBased(idxInvValue), (uint16) Com_GetConstValueArrayBasedInvValueLengthOfTxSigInfo(idxTxSigInfo));      /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
  }
# endif

  return retVal;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if ((COM_INVVALUEUSEDOFTXGRPSIGINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFTXGRPSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_InvalidateSignal_SendGroupSignal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InvalidateSignal_SendGroupSignal(Com_TxAccessInfoIterType txAccessInfo)       /* COV_COM_SIGNALINVALIDATION_ARRAYACCESS */
{
  uint8 retVal = COM_SERVICE_NOT_AVAILABLE;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Com_TxGrpSigInfoIterType idxTxGrpSigInfo = Com_GetTxGrpSigInfoIdxOfTxAccessInfo(txAccessInfo);

  /* #10 Send signal with the invalid value, the invalid value is stored in an ApplType dependent buffer */
# if (COM_INVVALUEUSEDOFTXGRPSIGINFO == STD_ON)
  if(Com_IsInvValueUsedOfTxGrpSigInfo(idxTxGrpSigInfo))       /* PRQA S 2842 */ /* MD_Com_2842 */ /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_InvValueIdxOfTxGrpSigInfoType idxInvValue = Com_GetInvValueIdxOfTxGrpSigInfo(idxTxGrpSigInfo);
    switch (Com_GetInvValueOfTxGrpSigInfo(idxTxGrpSigInfo))
    {
#  if (COM_EXISTS_CONSTVALUEUINT8_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT8_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt8(idxInvValue), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT8_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUESINT8_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt8(idxInvValue), 0); /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT16_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT16_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt16(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT16_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUESINT16_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt16(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT32_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT32_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt32(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT32_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUESINT32_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt32(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEUINT64_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEUINT64_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueUInt64(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUESINT64_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUESINT64_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueSInt64(idxInvValue), 0);        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEFLOAT32_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEFLOAT32_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueFloat32(idxInvValue), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
#  if (COM_EXISTS_CONSTVALUEFLOAT64_INVVALUEOFTXGRPSIGINFO == STD_ON)
      case COM_CONSTVALUEFLOAT64_INVVALUEOFTXGRPSIGINFO:
      {
        (void) Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueFloat64(idxInvValue), 0);       /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
        break;
      }
#  endif
      default:       /* COV_COM_MISRA */
        break;
    }
  }
# endif

# if (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFTXGRPSIGINFO == STD_ON)
  if(Com_IsConstValueArrayBasedInvValueUsedOfTxGrpSigInfo(idxTxGrpSigInfo))   /* COV_COM_SIGNALINVALIDATION_ARRAYACCESS_01 */
  {
    Com_ConstValueArrayBasedInvValueEndIdxOfTxGrpSigInfoType idxInvValue = Com_GetConstValueArrayBasedInvValueStartIdxOfTxGrpSigInfo(idxTxGrpSigInfo);
    retVal = Com_SendSignal_Processing(txAccessInfo, Com_GetAddrConstValueArrayBased(idxInvValue), (uint16) Com_GetConstValueArrayBasedInvValueLengthOfTxGrpSigInfo(idxTxGrpSigInfo));        /* PRQA S 0315 */ /* MD_Com_0314_0315 */ /* SBSW_COM_FCTCALL_WITH_P2CONST */
  }
# endif
  return retVal;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
   MD_Com_0314_0315: Misra Dir 1.1
     Reason:     A void pointer is used because it depends on the configuration of which type the pointer is. It is easier to use a void pointer insead of different functions for different pointer types.
     Risk:       No risk, because the underlying pointer type is known via the configuration.
     Prevention: No prevention necessary.
*/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* START_COVERAGE_JUSTIFICATION

END_COVERAGE_JUSTIFICATION */
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  END OF FILE: Com_SignalIf.c
 *********************************************************************************************************************/
