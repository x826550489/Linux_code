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
/**        \file  Dcm_NetworkInt.h
 *         \unit  Network
 *        \brief  Contains public function declarations and complex type definitions of Network unit.
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
#if !defined(DCM_NETWORKINT_H)
# define DCM_NETWORKINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_NetworkTypes.h"
# include "Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if (DCM_SVC_11_ECU_RESET_ENABLED == STD_ON) || \
     (DCM_SVC_10_RESET_AFTER_RESPONSE == STD_ON) || \
     (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
#  define DCM_NET_RX_BLOCKING_ENABLED                                STD_ON
# else
#  define DCM_NET_RX_BLOCKING_ENABLED                                STD_OFF
# endif

# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON)
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_ON
# else
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_OFF
# endif

/*! Calculate the maximum number of events related to USDT transport objects, needed by a network related task */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       32u                            /*!< Take the worst case, limited to 32 for a bit mask usage (i.e. task events) */
# else
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       DCM_NET_MAX_NUM_TRANSP_OBJECTS /*!< Allocate as many as needed by the concrete configuration */
# endif

/*! ComM channel message communication ability states */
# define DCM_NET_COMM_STATE_FLAG_RX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message reception is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message transmission is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_EN                               ((Dcm_NetComMStateType)0x01u ) /*!< Message transmission is enabled */
# define DCM_NET_COMM_STATE_FLAG_RX_EN                               ((Dcm_NetComMStateType)0x02u ) /*!< Message reception is enabled */

/*! Calculates a combined reception and transmission message communication state */
# define DCM_NET_COMM_STATE_COMPOSER(rx,tx)                          ((Dcm_NetComMStateType)((rx)|(tx)))                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Presets of all possible message communication states in both directions (Rx and Tx) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_DIS                            (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception and transmission are disabled (NoCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_EN                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception is disabled, but transmission is enabled */
# define DCM_NET_COMM_STATE_RX_EN_TX_DIS                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception is enabled, but transmission is disabled (SilentCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_EN_TX_EN                              (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception and transmission are enabled (FullCommunicationMode) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*! Network variant/non-variant configuration abstraction */
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       ((comVariant)->NumRxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       ((comVariant)->NumTxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMin)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMax)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    ((comVariant)->NumCanTpRxPduIds)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   ((comVariant)->NumPerTxObjects)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumConnections(comVariant)                    ((comVariant)->NumConnections)                                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      ((comVariant)->NumProtocols)                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   ((comVariant)->NumComMChannels)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        ((comVariant)->NumBuffers)                                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  ((comVariant)->NumTranspObjects)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                ((comVariant)->NumAllComMChannels)                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         ((comVariant)->RxPduIdTable)                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    ((comVariant)->ConnectionTable)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      ((comVariant)->ProtocolTable)                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             ((comVariant)->NetConnComMChannelMap)                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  ((comVariant)->NetworkHandleLookUpTable)                                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     ((comVariant)->TxPduIdMap)                                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  ((comVariant)->PerTxPduIdMap)                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    ((comVariant)->PerTxPduIdTable)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             ((comVariant)->ComCtrlChannelListAll)                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              ((comVariant)->NetAllComMChannelMap)                                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               ((comVariant)->CanTp2DcmRxPduIdMap)                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# else
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       DCM_NET_NUM_RX_PDUIDS
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       DCM_NET_NUM_TX_PDUIDS
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MIN
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MAX
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    DCM_NET_NUM_CANTP_RX_PDUIDS
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   DCM_NET_MAX_NUM_PERIODIC_TX_OBJ
#  define Dcm_NetCfgGetNumConnections(comVariant)                    DCM_NET_MAX_NUM_CONNECTIONS
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      DCM_NET_NUM_PROTOCOLS
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   DCM_NET_MAX_NUM_COMM_CHANNELS
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        DCM_NET_NUM_BUFFERS
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  DCM_NET_MAX_NUM_TRANSP_OBJECTS
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                DCM_NET_MAX_NUM_ALL_COMM_CHANNELS

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         Dcm_CfgNetRxPduInfo
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    Dcm_CfgNetConnectionInfo
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      Dcm_CfgNetProtocolInfo
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             Dcm_CfgNetConnComMChannelMap
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  Dcm_CfgNetNetworkHandleLookUpTable
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     Dcm_CfgNetTxPduInfo
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  Dcm_CfgNetPeriodicTxPduInfo
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    Dcm_CfgNetPeriodicTxPduIds
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             Dcm_CfgNetComCtrlChannelListAll
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              Dcm_CfgNetAllComMChannelMap
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               Dcm_CfgNetCanTp2DcmRxPduIdMap
# endif

/*! Returns the diagnostic client connection ID from a DcmRxPduID */
# define Dcm_NetCfgGetConnHdlOfRxPduId(comVariant, rxPduId)          (Dcm_NetCfgGetRxPduInfo(comVariant)[(rxPduId)].ConnRef)                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the diagnostic client's network address from its connection ID */
# define Dcm_NetCfgGetTesterAddressOfConnHdl(comVariant, connHdl)    (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].ClientSrcAddr)              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Provides the ECUs network address of a specific client connection */
# define Dcm_NetCfgGetEcuAddressOfConnHdl(comVariant, connHdl)       (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].EcuAddress)                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# if (DCM_NET_GENERIC_CONNECTION_ENABLED == STD_ON)
/*! Indicates whether a connection is generic */
#  define Dcm_NetCfgIsGenericConnection(comVariant, connHdl)         (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].MetaDataLength == DCM_NET_METADATA_LENGTH) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif

/*! Returns the diagnostic client's network address from one of its DcmRxPduIDs */
# define Dcm_NetCfgGetTesterAddressOfRxPduId(comVariant, rxPduId)    (Dcm_NetCfgGetTesterAddressOfConnHdl((comVariant), Dcm_NetCfgGetConnHdlOfRxPduId((comVariant), (rxPduId)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the ECUs network address of a specific client connection from one of its DcmRxPduIDs */
# define Dcm_NetCfgGetEcuAddressOfRxPduId(comVariant, rxPduId)       (Dcm_NetCfgGetEcuAddressOfConnHdl((comVariant), Dcm_NetCfgGetConnHdlOfRxPduId((comVariant), (rxPduId)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_PbCfgNetGetConnectionInfo()
 *********************************************************************************************************************/
/*! \brief          Gets the connection table entry.
 *  \details        -
 *  \return         Network connection table entry
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CfgNetConnectionInfoType, DCM_CODE) Dcm_PbCfgNetGetConnectionInfo(
  uint8_least index
  );

/**********************************************************************************************************************
 *  Dcm_PbCfgNetGetConnComMChannelMap()
 *********************************************************************************************************************/
/*! \brief          Gets the network handles table entry.
 *  \details        -
 *  \return         Network handles table entry
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CfgNetNetIdRefMemType, DCM_CODE) Dcm_PbCfgNetGetConnComMChannelMap(
  uint8_least index
  );

# if (DCM_NET_COMCTRL_ALLNET_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
*  Dcm_PbCfgNetGetComCtrlChannelListAll()
*********************************************************************************************************************/
/*! \brief         Gets the list of all ComM channels.
*  \details        -
*  \return         List of all ComM channels
*  \context        TASK
*  \reentrant      TRUE
*  \synchronous    TRUE
*  \pre            -
*********************************************************************************************************************/
FUNC(Dcm_CfgNetNetIdRefMemType, DCM_CODE) Dcm_PbCfgNetGetComCtrlChannelListAll(
  uint8_least index
  );
# endif

/**********************************************************************************************************************
 *  Dcm_PbCfgNetGetNumAllComMChannels()
 *********************************************************************************************************************/
/*! \brief          Gets the number of channels from main connections and ComControl channels.
 *  \details        -
 *  \return         Number of channels
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(NetworkHandleType, DCM_CODE) Dcm_PbCfgNetGetNumAllComMChannels(void);

# if (DCM_MODE_COMMCTRL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_PbRamNetGetComCtrlChannels()
 *********************************************************************************************************************/
/*! \brief          Gets the communication state [Rx/Tx][On/Off] of each ComM channel known to DCM.
 *  \details        -
 *  \return         Communication state
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_CommunicationModeType, DCM_CODE) Dcm_PbRamNetGetComCtrlChannels(
  uint8_least index
  );
# endif

# if (DCM_NET_COMMCTRL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetSetComControlChannelState()
 *********************************************************************************************************************/
/*! \brief          Sets the state of a communication control channel of the given index.
 *  \details        -
 *  \param[in]      index    Index to the communication control channel
 *  \param[in]      value    New communication mode
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_NetSetComControlChannelState(
  uint8_least index,
  Dcm_CommunicationModeType value
  );
# endif

/**********************************************************************************************************************
*  Dcm_NetGetTransportObject()
*********************************************************************************************************************/
/*! \brief          Returns a transport object element of the given index.
*   \details        -
*   \param[in]      index    Unique handle to a transport object
*   \return         Transport object
*   \context        ISR1|ISR2|TASK
*   \reentrant      TRUE
*   \pre            -
*********************************************************************************************************************/
FUNC(Dcm_NetTransportObjectPtrType, DCM_CODE) Dcm_NetGetTransportObject(
  Dcm_CfgNetTObjHandleOptType index
  );

# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetGetActiveComVariant()
 *********************************************************************************************************************/
/*! \brief          Returns currently set variant.
 *  \details        Returns currently active communication variant.
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (Dcm_CfgVarMgrComVariantType, DCM_CODE) Dcm_NetGetActiveComVariant(void);
# endif

# if (DCM_NET_RX_BLOCKING_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetSetRxAllowed()
 *********************************************************************************************************************/
/*! \brief          Sets the RxAllowed value.
 *  \details        -
 *  \param[in]      rxAllowed    Value to be set.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (void, DCM_CODE) Dcm_NetSetRxAllowed(
  boolean rxAllowed
  );
# endif

# if (DCM_MODE_COMMCTRL_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_PbCfgNetAllComMChannelMapGetEntry()
 *********************************************************************************************************************/
/*! \brief          Sets the RxAllowed value.
 *  \details        -
 *  \param[in]      index    Index to a network handle
 *  \return         Network handle entry
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (NetworkHandleType, DCM_CODE) Dcm_PbCfgNetAllComMChannelMapGetEntry(
  Dcm_CfgNetNetIdRefOptType index
  );
# endif

# if (DCM_SVC_10_JMP2BOOT_ENABLED == STD_ON) || \
     (DCM_SVC_11_ECU_RESET_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetGetHasRespPendOnBoot()
 *********************************************************************************************************************/
/*! \brief          Returns the HasRespPendOnBoot value.
 *  \details        -
 *  \param[in]      pContext   Pointer to the context
 *  \return         HasRespPendOnBoot value
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (boolean, DCM_CODE) Dcm_NetGetHasRespPendOnBoot(
  Dcm_ContextPtrType pContext
  );
# endif

# if (DCM_NET_INTERNAL_REQ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetRxIndInternal()
 *********************************************************************************************************************/
/*! \brief          Provides a means for virtual/internal diagnostic request.
 *  \details        This API is generally used for RoE (SID 0x86) purposes.
 *  \param[in]      rxPduId            The RxPDUID of the request
 *  \param[in]      sourceAddress      Client or tester address
 *  \param[in]      data               The data of the request
 *  \param[in]      length             The length of the request
 *  \return         DCM_E_OK           Reception was successful
 *  \return         DCM_E_NOT_OK       Reception was not successful
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_NetRxIndInternal(
  PduIdType rxPduId,
  uint16 sourceAddress,
  Dcm_MsgType data,
  PduLengthType length
  );
# endif

/**********************************************************************************************************************
 *  Dcm_NetGetComState()
 *********************************************************************************************************************/
/*! \brief          Returns the communication state for the given RxPduId.
 *  \details        -
 *  \param[in]      rxPduId    The RxPDUID of the request
 *  \return         The communication state
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_NetComMStateType, DCM_CODE) Dcm_NetGetComState(
  PduIdType rxPduId
  );
# define DCM_STOP_SEC_CODE
# include "Dcm_MemMap.h"                                                                                                                             /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_NETWORKINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_NetworkInt.h
 *********************************************************************************************************************/
