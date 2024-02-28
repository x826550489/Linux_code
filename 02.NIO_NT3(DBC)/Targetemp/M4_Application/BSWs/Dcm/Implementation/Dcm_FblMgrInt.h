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
/**        \file  Dcm_FblMgrInt.h
 *         \unit  FblMgr
 *        \brief  Contains public function declarations and complex type definitions of FblMgr unit.
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
#if !defined(DCM_FBLMGRINT_H)
# define DCM_FBLMGRINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_FblMgrTypes.h"
# if (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Download states */
#  define DCM_FBL_DOWNLOAD_STATE_IDLE                                ((Dcm_FblMgrDownloadStateType)0x00u) /*!< Setup download */
#  define DCM_FBL_DOWNLOAD_STATE_READY_FOR_TRANSFER                  ((Dcm_FblMgrDownloadStateType)0x01u) /*!< Ready and waiting for transfer */
#  define DCM_FBL_DOWNLOAD_STATE_TRANSFER_IN_PROGRESS                ((Dcm_FblMgrDownloadStateType)0x02u) /*!< Transfer and write the data to the memory */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct DCM_FBLMGRMEMBLOCKTYPE_TAG
{
  Dcm_FblMgrMemoryAddressType  Address;  /*!< The address to access */
  Dcm_FblMgrMemorySizeType     Length;   /*!< The number of bytes requested */
  Dcm_FblMgrMidType            Mid;      /*!< The memory identifier */
};
typedef struct DCM_FBLMGRMEMBLOCKTYPE_TAG Dcm_FblMgrMemBlockType;
typedef P2VAR(Dcm_FblMgrMemBlockType, TYPEDEF, DCM_VAR_NOINIT)   Dcm_FblMgrMemBlockPtrType;
typedef P2CONST(Dcm_FblMgrMemBlockType, TYPEDEF, DCM_VAR_NOINIT) Dcm_FblMgrMemBlockConstPtrType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#  define DCM_START_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_FblMgrParseMemStream()
 *********************************************************************************************************************/
/*! \brief          Validates the MID and reads the memory block information.
 *  \details        -
 *  \param[in]      alfid         Requested ALFID byte
 *  \param[in,out]  pMsgContext   Current message context with the memory address and size byte stream
 *  \param[out]     pMemBlock     Interpreted memory block information
 *  \param[out]     ErrorCode     The NRC
 *  \return         DCM_E_OK      no error found
 *  \return         DCM_E_NOT_OK  invalid MID (NRC is set to ErrorCode)
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            It shall be assured that the ALFID value matches the length of the data stream to be parsed.
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_FblMgrParseMemStream(
  uint8 alfid,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_FblMgrMemBlockPtrType pMemBlock,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrValidateAndGetAlfid()
 *********************************************************************************************************************/
/*! \brief          Validates the request transfer memory ALFID and extracts it from request.
 *  \details        -
 *  \param[in,out]  pMsgContext        Requested memory data starting with the ALFID byte.
 *  \param[out]     pAlfid             ALFID byte
 *  \param[out]     pBlockLength       Returns the left part of the stream (i.e. without protocol header)
 *  \param[out]     ErrorCode          The NRC
 *  \return         DCM_E_OK           no error found
 *  \return         DCM_E_NOT_OK       invalid ALFID (NRC is set to ErrorCode)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            The request data within the pMsgContext must contain an ALFID byte.
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_FblMgrValidateAndGetAlfid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8VarDataPtrType pAlfid,
  Dcm_Uint8VarDataPtrType pBlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
#  define DCM_STOP_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

#  define DCM_START_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_FblMgrReset()
 *********************************************************************************************************************/
/*! \brief          Reset download data elements
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_FblMgrReset(
  void
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrGetMemoryBlock()
 *********************************************************************************************************************/
/*! \brief          Get the current MemoryBlock struct.
 *  \details        -
 *  \return         Memory block
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_FblMgrMemBlockPtrType, DCM_CODE) Dcm_FblMgrGetMemoryBlock(
  void
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrSetMemoryBlock()
 *********************************************************************************************************************/
/*! \brief          Set the memory block.
 *  \details        -
 *  \param[in]      memoryBlock            Pointer to a memory block.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_FblMgrSetMemoryBlock(
  Dcm_FblMgrMemBlockConstPtrType memoryBlock
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrGetMaxBlockLength()
 *********************************************************************************************************************/
/*! \brief          Get the maximum length of a data block.
 *  \details        -
 *  \return         Block length
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_FblMgrBlockLengthType, DCM_CODE) Dcm_FblMgrGetMaxBlockLength(
  void
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrSetMaxBlockLength()
 *********************************************************************************************************************/
/*! \brief          Set the maximal block length.
 *  \details        -
 *  \param[in]      blockLength            The length of a data block.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_FblMgrSetMaxBlockLength(
  Dcm_FblMgrBlockLengthType blockLength
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrGetBlockSequenceCounter()
 *********************************************************************************************************************/
/*! \brief          Get the current block sequence counter.
 *  \details        -
 *  \return         Block sequence counter
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_FblMgrBlockSequenceCounterType, DCM_CODE) Dcm_FblMgrGetBlockSequenceCounter(
  void
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrSetBlockSequenceCounter()
 *********************************************************************************************************************/
/*! \brief          Set the old block sequence counter.
 *  \details        -
 *  \param[in]      blockSequenceCounter   The counter of the current download block sequence.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_FblMgrSetBlockSequenceCounter(
  Dcm_FblMgrBlockSequenceCounterType blockSequenceCounter
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrGetDownloadState()
 *********************************************************************************************************************/
/*! \brief          Get the current download state.
 *  \details        -
 *  \return         DCM_FBL_DOWNLOAD_STATE_IDLE                  No data transfer ongoing.
 *  \return         DCM_FBL_DOWNLOAD_STATE_READY_FOR_TRANSFER    Ready to start a data transfer.
 *  \return         DCM_FBL_DOWNLOAD_STATE_TRANSFER_IN_PROGRESS  Data transfer is currently in progress.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_FblMgrDownloadStateType, DCM_CODE) Dcm_FblMgrGetDownloadState(
  void
  );

/**********************************************************************************************************************
 *  Dcm_FblMgrSetDownloadState()
 *********************************************************************************************************************/
/*! \brief          Set the current download state.
 *  \details        -
 *  \param[in]      downloadState          The current download state of the process.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_FblMgrSetDownloadState(
  Dcm_FblMgrDownloadStateType downloadState
  );
#  define DCM_STOP_SEC_CODE
#  include "Dcm_MemMap.h"                                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

# endif /* (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_FBLMGRINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_FblMgrInt.h
 *********************************************************************************************************************/
