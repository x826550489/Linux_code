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
/*!        \file  Com_LMgt.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#if !defined (COM_LMGT_H)
# define COM_LMGT_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitRxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a rx I-PDU.
    \details      -
    \pre          -
    \param[in]    rxPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitRxIpdu(Com_RxPduInfoIterType rxPduId);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitTxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a tx I-PDU.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitTxIpdu(Com_TxPduInfoIterType ComPduId);
# endif

# if (COM_RXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitRx
**********************************************************************************************************************/
/*! \brief        This function initializes Rx IPdus and related parameters.
    \details      -
    \pre          -
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      Com_InitRx shall not pre-empt any COM function.
                  The rest of the system must guarantee that Com_InitRx is not called in such a way.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitRx(void);
# endif

# if (COM_TXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_InitTx
**********************************************************************************************************************/
/*! \brief        This function initializes Tx IPdus and related parameters.
    \details      -
    \pre          -
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
    \warning      Com_InitTx shall not pre-empt any COM function.
                  The rest of the system must guarantee that Com_InitTx is not called in such a way.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_LMgt_InitTx(void);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_LMGT_H */
/**********************************************************************************************************************
  END OF FILE: Com_LMgt.h
**********************************************************************************************************************/
