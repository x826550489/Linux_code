/* Kernbauer Version: 1.16 Konfiguration: DrvTransCan Erzeugungsgangnummer: 108 */



/**********************************************************************************************************************
 |               C O P Y R I G H T
 |-----------------------------------------------------------------------
 |------  Copyright (c) 2000-2016 by Vector Informatik GmbH, all rights 
 |reserved
 |
 | Please note, that this file contains an implementation example for 
 | CanTrcv. This code may influence the behaviour of the CanTrcv
 | in principle. Therefore, great care must be taken to verify
 | the correctness of the implementation.
 |
 | The contents of the originally delivered files are only examples resp. 
 | implementation proposals. With regard to the fact that these functions 
 | are meant for demonstration purposes only, Vector Informatik's 
 | liability shall be expressly excluded in cases of ordinary negligence, 
 | to the extent admissible by law or statute.
 |  -------------------------------------------------------------------------------------------------------------------
 |  FILE DESCRIPTION
 |  -------------------------------------------------------------------------------------------------------------------
 |         File:  CanTrcv_30_Sbc.h
 |      Project:  MICROSAR
 |       Module:  CAN Transceiver driver
 |    Generator:  DaVinci Configurator 5
 |  Description:  Header of the MICROSAR CAN Transceiver Driver.
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Senol Cendere                 Ces           Vector Informatik GmbH
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Robert Schelkle               Rse           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2014-08-09  Rse     -             First Implementation
 *  1.01.00   2015-09-21  Rse     ESCAN00085405 Add support for Partial Networking
 *  2.00.00   2016-01-18  Rse     -             Update to newest template 3.04.00
 *                        Rse     ESCAN00088131 Support application callback functions for Sbc service calls
 *  2.00.01   2016-03-08  Rse     ESCAN00088788 Compiler error: Expected an expression
 *  2.01.00   2016-04-21  Rse     ESCAN00089664 Support SafeBSW
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-02-25  Fn      -             Intitial revision of the core implementation
 *  01.00.01  2008-04-17  Fn      -             Update of the include file names
 *  01.01.00  2008-06-26  Ou      ESCAN00027616 Various compile errors, problems with Organi
 *  01.02.00  2008-09-12  Ou      ESCAN00029980 Compiler failure due to wrong definition of SW version
 *  01.03.00  2008-10-07  Ou      ESCAN00028298 Several warnings due to unreferenced local variables
 *                        Ou      ESCAN00029572 DrvTrans__coreCanxAsr raise DET error if CanTrcv_SetOpMode is called with invalid TrcvWakeupMode
 *                        Ou      ESCAN00030536 Compile error at extended version check
 *  01.04.00  2008-12-11  Ou      ESCAN00031771 Adjust wakeup by bus handling for platforms which cannot be woken up with a CAN frame
 *  01.05.00  2009-02-19  Tvi     ESCAN00033258 GetBusWuReason may return an invalid value
 *  01.06.00  2009-02-26  Tvi     ESCAN00033383 Don't throw DET error in case the same mode is requested again
 *                        Tvi     ESCAN00033398 Compiler warnings when using different transceiver types within the same stack
 *                        Tvi     ESCAN00033413 Possible out of bounds access in SetOpMode if DET is enabled
 *  02.00.00  2009-06-29  Fn      ESCAN00035913 CAN Transceiver channel does not wake up
 *  02.00.01  2009-10-15  Tvi     ESCAN00038495 Compile error: unknown type definitions in dio.h
 *  02.01.00  2009-11-04  Tvi     ESCAN00036841 OP_MODE_SLEEP should be independent of GENERAL_WAKE_UP_SUPPORT
 *                        Tvi     ESCAN00038945 Use different DioPins tokens for GetOpMode and CHECK_WA
 *                        Tvi     ESCAN00038946 Rename filenames to match BSW00347
 *                        Tvi     ESCAN00038947 CanTrcv087 has to be implemented the correct way
 *                        Tvi     ESCAN00039039 Add support for timers
 *                        Tvi     ESCAN00039041 Allow transition to OP_MODE_NORMAL even if it is the current OpMode
 *                        Tvi     ESCAN00039043 Implement an initialization via OP_MODE_NORMAL
 *                        Tvi     ESCAN00039194 Disable IcuNotification when entering Normal mode in Init and SetOpMode
 *  02.02.00  2010-05-04  Tvi     ESCAN00040088 Compiler Warning: unused parameter 'TrcvWakeupMode'
 *  02.20.00  2010-07-01  Tvi     ESCAN00046512 Add support for partial network transceivers
 *            2010-11-29  Tvi     ESCAN00046781 Support Multiple Identity Configuration
 *                                ESCAN00045601 "Channel Used" parameter not well implemented
 *                                ESCAN00046813 Adapt AUTOSAR version check
 *                                ESCAN00047668 Critical areas should be Trcv specific
 *  02.20.01  2011-02-08  Tvi     ESCAN00048498 Wrong DEM Events used
 *  02.20.02  2011-03-11  Tvi     ESCAN00049830 Remove ASR Version check for SPI / DIO
 *                        Tvi     ESCAN00049831 [PN only] Store wakeup event and report them if Trcv is in Standby mode
 *  03.00.00  2011-05-05  Tvi     ESCAN00051930 Add support for ASR3.2.1
 *                                ESCAN00051564 Remove the AUTOSAR Release Version Check
 *  03.01.00  2011-11-22  Tvi     ESCAN00054349 AR3-1738: Add support for asynchronous transceiver driver
 *                                ESCAN00053272 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053265 AR3-2069: Remove non-SchM code for critical section handling
 *  03.01.01  2012-02-12  Tvi     ESCAN00057892 [PN only] CanTrcv does not wakeup when Synchronous SPI is being used
 *                        Tvi     ESCAN00056788 Compiler error/warning: DRVTRANS__CORECANXASR_RELEASE_VERSION' redefined
 *  04.00.00  2012-05-21  Tvi     ESCAN00058641 AR4-95: Provide CanTrcv according ASR 4, Asynchronous Transceiver Mode Changes
 *                                ESCAN00059656 Add support for SetPNActivationState according to ASR4
 *                                ESCAN00060455 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  04.00.01  2012-09-27  Tvi     ESCAN00061779 [CFG5/ASR4 only]: Compiler error about unkown struct member instanceID
 *  04.01.00  2012-10-08  Tvi     ESCAN00062121 Report DEM if PN is not available
 *                        Tvi     ESCAN00066283 AR4-352: Support partial networking 
 *  04.02.00  2013-11-20  Tvi     ESCAN00071370 AR4-569: [CanTrcv]  Incompatible  argument  in call to EcuM_SetWakeupEvent() 
 *  04.03.00  2014-01-10  Tvi     ESCAN00073861 AR4-345: Implement PF4_PostBuildSelectable
 *  05.00.00  2014-09-24  Seu     ESCAN00076622 AR4-698: Post-Build Selectable (Identity Manager)
 *  05.00.01  2014-11-13  Seu     -             MISRA deviation comment for rule 6080 added (APIs: *_ClearTrcvWufFlag() and *_CheckWakeFlag())
 *  05.01.00  2015-05-04  Seu     ESCAN00077814 Support for CAN Transceiver on System-Basis Chips (SBCs)
 *            2015-07-23  Seu     ESCAN00084154 Only since R13: Compiler error: C2059: syntax error : '{'
 *            2015-07-23  Seu     ESCAN00083583 Adapt in order to fix ESCAN00083361 / ESCAN00083362
 *            2015-07-23  Seu     ESCAN00083395 Compiler warning: parameter is never used
 *  05.01.01  2015-09-24  Seu     ESCAN00085451 Support usage of Partial Networking for SBCs.
 *  05.01.02  2015-10-06  Seu     ESCAN00085678 Initialize requestState in case of INTERFACE_SBC and PN is used
 *  05.02.00  2015-02-04  Seu     ESCAN00080310 FEAT-427: SafeBSW Step I
 *            2015-10-05  Seu     ESCAN00081795 FEAT-1275: SafeBSW Step 2
 *            2015-10-05  Seu     ESCAN00085154 FEAT-1527: SafeBSW Step 3
 *  05.03.00  2016-01-16  Seu     ESCAN00087580 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088810 Add Postbuild Loadable Support for CanTrcvDrv
 *  05.04.00  2016-04-05  Seu     ESCAN00087813 FEAT-1688: SafeBSW Step 4
 *            2016-05-19  Seu     ESCAN00090097 Compiler error: Syntax Error caused by undefined compiler class
 *  05.04.01  2016-08-02  Seu     ESCAN00091270 MISRA deviation: MISRA-C:2004 Rule 8.8
 *            2016-08-17  Seu     ESCAN00091505 Improve code coverage and doxygen comments
 *            2016-10-17  Seu     ESCAN00091616 Compiler error: identifier index not declared
 * *******************************************************************************************************************/
#if !defined (CANTRCV_30_SBC_API_H)
# define CANTRCV_30_SBC_API_H

/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 0777 EOF */ /* MD_CanTrcv_30_Sbc_0777 */

# define V_CANTRCV_30_SBC_HEADER

/* ********************************************************************************************************************
 * INCLUDES
 * *******************************************************************************************************************/
# include "CanTrcv_30_Sbc_Cfg.h" /* SREQ00010148,SREQ00007523 */

# include "SchM_CanTrcv_30_Sbc.h"

/* ********************************************************************************************************************
 * Module version
 * *******************************************************************************************************************/

# define CANTRCV_30_SBC_AR_RELEASE_MAJOR_VERSION      4
# define CANTRCV_30_SBC_AR_RELEASE_MINOR_VERSION      0
# define CANTRCV_30_SBC_AR_RELEASE_REVISION_VERSION   3
# define CANTRCV_30_SBC_AUTOSARVERSION_4X             0x403


/* ##V_CFG_MANAGEMENT ##CQProject : DrvTrans_SbcCanAsr CQComponent : Implementation */
# define DRVTRANS_SBCCANASR_VERSION                 0x0201u
# define DRVTRANS_SBCCANASR_RELEASE_VERSION         0x00u

#if defined(CANTRCV_30_SBC_INCLUDE_INTERNAL) /* COV_CANTRCV_HL_SBC_VARCOV_AVOID_COREVER_REDEF */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvTrans__coreCanxAsr CQComponent : Implementation */
# define DRVTRANS__CORECANXASR_VERSION                         0x0504u
# define DRVTRANS__CORECANXASR_RELEASE_VERSION                 0x01u
#endif

#  define CANTRCV_30_SBC_SW_MAJOR_VERSION               ((DRVTRANS_SBCCANASR_VERSION & 0xFF00u) >> 8)
#  define CANTRCV_30_SBC_SW_MINOR_VERSION               (DRVTRANS_SBCCANASR_VERSION & 0x00FFu)
#  define CANTRCV_30_SBC_SW_PATCH_VERSION               DRVTRANS_SBCCANASR_RELEASE_VERSION




#define CANTRCV_30_SBC_SUPPORTS_MODE_STANDBY




#define CANTRCV_30_SBC_SUPPORTS_PARTIAL_NETWORKING

#define CANTRCV_30_SBC_GETTRCVSYSTEMDATA_RAW


/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 * *******************************************************************************************************************/ 
# define CANTRCV_30_SBC_VENDOR_ID                      30
# define CANTRCV_30_SBC_MODULE_ID                      70

/* API IDs for Error Reporting */
# define CANTRCV_30_SBC_INIT_ID                        0x00
# define CANTRCV_30_SBC_SETOPMODE_ID                   0x01
# define CANTRCV_30_SBC_GETOPMODE_ID                   0x02
# define CANTRCV_30_SBC_GETBUSWUREASON_ID              0x03
# define CANTRCV_30_SBC_GETVERSIONINFO_ID              0x04
# define CANTRCV_30_SBC_SETWAKEUPMODE_ID               0x05
# define CANTRCV_30_SBC_MAINFUNCTION_ID                0x06
# define CANTRCV_30_SBC_CHECKWAKEUP_ID                 0x07 
# define CANTRCV_30_SBC_MAINFUNCTIONDIAGNOSTICS        0x08
# define CANTRCV_30_SBC_GETTRCVSYSTEMDATA_ID           0x09
# define CANTRCV_30_SBC_CLEARTRCVWUFFLAG_ID            0x0A
# define CANTRCV_30_SBC_READTRCVTIMEOUTFLAG_ID         0x0B
# define CANTRCV_30_SBC_CLEARTRCVTIMEOUTFLAG_ID        0x0C
# define CANTRCV_30_SBC_READTRCVSILENCEFLAG_ID         0x0D
# define CANTRCV_30_SBC_CHECKWAKEFLAG_ID               0x0E
# define CANTRCV_30_SBC_SETPNACTIVATIONSTATE_ID        0x0F
# define CANTRCV_30_SBC_SPIINDICATION_ID               0x10


# define CANTRCV_30_SBC_OP_MODE_NORMAL                 CANTRCV_TRCVMODE_NORMAL
# define CANTRCV_30_SBC_OP_MODE_STANDBY                CANTRCV_TRCVMODE_STANDBY 
# define CANTRCV_30_SBC_OP_MODE_SLEEP                  CANTRCV_TRCVMODE_SLEEP

# define CANTRCV_30_SBC_WU_ENABLE                      CANTRCV_WUMODE_ENABLE
# define CANTRCV_30_SBC_WU_DISABLE                     CANTRCV_WUMODE_DISABLE
# define CANTRCV_30_SBC_WU_CLEAR                       CANTRCV_WUMODE_CLEAR

# define CANTRCV_30_SBC_WU_ERROR                       CANTRCV_WU_ERROR
# define CANTRCV_30_SBC_WU_NOT_SUPPORTED               CANTRCV_WU_NOT_SUPPORTED
# define CANTRCV_30_SBC_WU_BY_BUS                      CANTRCV_WU_BY_BUS
# define CANTRCV_30_SBC_WU_INTERNALLY                  CANTRCV_WU_INTERNALLY
# define CANTRCV_30_SBC_WU_RESET                       CANTRCV_WU_RESET
# define CANTRCV_30_SBC_WU_POWER_ON                    CANTRCV_WU_POWER_ON
# define CANTRCV_30_SBC_WU_BY_PIN                      CANTRCV_WU_BY_PIN
# define CANTRCV_30_SBC_WU_BY_SYSERR                   CANTRCV_WU_BY_SYSERR

# define CANTRCV_30_SBC_E_NO_ERROR                     0x00
# define CANTRCV_30_SBC_E_INVALID_CAN_NETWORK          0x01
/* SREQ00010156: Keep the invalid CAN Network switch for compatibility reason. */
# define CANTRCV_30_SBC_E_INVALID_TRANSCEIVER         CANTRCV_30_SBC_E_INVALID_CAN_NETWORK
# define CANTRCV_30_SBC_E_PARAM_POINTER                0x02
# define CANTRCV_30_SBC_E_UNINIT                       0x11
# define CANTRCV_30_SBC_E_TRCV_NOT_STANDBY             0x21
# define CANTRCV_30_SBC_E_TRCV_NOT_NORMAL              0x22
# define CANTRCV_30_SBC_E_PARAM_TRCV_WAKEUP_MODE       0x23
# define CANTRCV_30_SBC_E_PARAM_TRCV_OP_MODE           0x24
# define CANTRCV_30_SBC_E_BAUDRATE_NOT_SUPPORTED       0x25
# define CANTRCV_30_SBC_E_CLR_TRCV_WUF_NOT_CALLED      0x30
# define CANTRCV_30_SBC_E_NO_TRCV_CONTROL             0x40 /* SREQ00010156: Actual ID is unspecified in SWS! */


# define CANTRCV_30_SBC_WAKEUP_NOT_SUPPORTED          0
# define CANTRCV_30_SBC_WAKEUP_BY_POLLING             1
# define CANTRCV_30_SBC_WAKEUP_BY_ISR                 2
/* Compatibility defines... */
# define CANTRCV_30_SBC_WAKEUP_NONE                   CANTRCV_30_SBC_WAKEUP_NOT_SUPPORTED
# define CANTRCV_30_SBC_WAKEUP_POLLING                CANTRCV_30_SBC_WAKEUP_BY_POLLING
# define CANTRCV_30_SBC_WAKEUP_ISR                    CANTRCV_30_SBC_WAKEUP_BY_ISR                 

# define CanTrcv_30_Sbc_TrcvModeType                  CanTrcv_TrcvModeType
# define CanTrcv_30_Sbc_TrcvWakeupModeType            CanTrcv_TrcvWakeupModeType
# define CanTrcv_30_Sbc_TrcvWakeupReasonType          CanTrcv_TrcvWakeupReasonType


/* Timer configuration */


# define CANTRCV_30_SBC_USE_TIMERS                    STD_OFF

/* Predefined timer indexes (0x01 - 0x0f)                                   */
# define kCanTrcv_30_Sbc_LoopInit                          0x01






/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 * *******************************************************************************************************************/
/* SREQ00007522 */
typedef enum
{
  CANTRCV_30_SBC_FLAG_SET,
  CANTRCV_30_SBC_FLAG_CLEARED
}
CanTrcv_30_Sbc_TrcvFlagStateType;

typedef enum
{
  CANTRCV_30_SBC_PN_ENABLED,
  CANTRCV_30_SBC_PN_DISABLED
} CanTrcv_30_Sbc_PNActivationType;

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 * *******************************************************************************************************************/
/* for callback function prototypes see CanTrcv_Cbk.h */
# define CANTRCV_30_SBC_START_SEC_CODE
# include "MemMap.h"


/************************************************************************************************************
 | NAME:  CanTrcv_30_Sbc_Init()
 ***********************************************************************************************************/
/*! \brief         Initializes the CAN transceiver module.
 *  \details       This function initializes all active channels of the CAN transceiver driver which are configured in the configuration tool.
 *                 This function has the service id 0x00.
 *  \param[in]     ConfigPtr - Pointer to the CanTrcv_30_Sbc_Config structure.
 *                 If multiple configurations are available, the active configuration can be selected by using the related CanTrcv_30_Sbc_Config_<IdentityName> structure.
 *  \pre           The function CanTrcv_30_Sbc_InitMemory must be called before the function CanTrcv_30_Sbc_Init can be called.
 *                 This function must be called before any other service functionality of the transceiver driver
 *                 The SPI/DIO driver must be initialized
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Init( P2CONST(CanTrcv_30_Sbc_ConfigType, AUTOMATIC, CANTRCV_30_SBC_CONST) ConfigPtr );


/***********************************************************************************************************************
 | NAME:  CanTrcv_30_Sbc_InitMemory
 **********************************************************************************************************************/
/*! \brief         Initialization of memory of the CAN transceiver module.
 *  \details       -
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_InitMemory(void);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetOpMode
 **********************************************************************************************************************/
/*! \brief       Change the transceiver state into the requested mode.
 *  \details     This function has the service id 0x01.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   OpMode: Requested mode to which the transceiver state has to be changed.
 *  \return      E_OK: If transceiver state was changed into the requested mode.
 *  \return      E_NOT_OK: If transceiver state failed to change or mode parameter is invalid.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetOpMode
 **********************************************************************************************************************/
/*! \brief       Detect the current transceiver operation mode and store it.
 *  \details     DIO transceiver: The mode is determined from status of PINs of the transceiver hardware.
 *               SPI transceiver: The mode is read from state variable. No access to transceiver hardware is performed.
 *               This function has the service id 0x02.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  OpMode: Pointer to buffer where the current operation mode is stored.
 *  \return      E_OK: If current transceiver operation mode was detected.
 *  \return      E_NOT_OK: If transceiver operation mode is not initialized.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) OpMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetBusWuReason
 **********************************************************************************************************************/
/*! \brief       Detect and store the bus wake-up reason.
 *  \details     The wake-up reason is read from state variable. No access to transceiver hardware is performed.
 *               This function has the service id 0x03.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  Reason: Pointer to buffer where the bus wake-up reason is stored.
 *  \return      E_OK: If bus wake-up reason was detected.
 *  \return      E_NOT_OK: If bus wake-up reason is not detected or feature is not supported.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) Reason);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetWakeupMode
 **********************************************************************************************************************/
/*! \brief       Change the wake-up mode to the requested mode.
 *  \details     For more information about possible wake-up modes please see the description of type <CanTrcv_TrcvWakeupModeType>.
 *               This function has the service id 0x05.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   TrcvWakeupMode: Requested wake-up mode for the transceiver channel (CanTrcvIndex).
 *  \return      E_OK: If wake-up mode is changed to the requested mode.
 *  \return      E_NOT_OK: If the wake-up mode change has failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeup
 **********************************************************************************************************************/
/*! \brief       Checks if a wake-up event was detected.
 *  \details     This function has the service id 0x07.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: If a wake-up was detected / the request to check for wake-up was accepted (only asynchronous SPI-interface).
 *  \return      E_NOT_OK: If NO wake-up was detected / the request to check for wake-up was rejected (only asynchronous SPI-interface).
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeup(uint8 CanTrcvIndex);


#if (CANTRCV_30_SBC_GET_VERSION_INFO == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Get the version info of the CAN transceiver module
 *  \details     The versions are stored into the structure pointed by VersionInfo.
 *               This function has the service id 0x04.
 *  \param[out]  VersionInfo: Structure pointer for storing of version info
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_GET_VERSION_INFO == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) VersionInfo);
#endif /* (CANTRCV_30_SBC_GET_VERSION_INFO == STD_ON) */

/* SREQ00007670 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_GetTrcvSystemData
 **********************************************************************************************************************/
/*! \brief       Reads the transceiver configuration / status data and returns it via the parameter TrcvSysData.
 *  \details     This function has the service id 0x09.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  TrcvSysData: Configuration / status data of the transceiver.
 *  \return      E_OK: Status was read successfully.
                 E_NOT_OK: Status data is not available or DET/DEM occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_GetTrcvSystemData(uint8 CanTrcvIndex, P2VAR(uint32, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) TrcvSysData );

#if (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) /* SREQ00007670 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ClearTrcvWufFlag
 **********************************************************************************************************************/
/*! \brief       Requests to clear the WUF flag of a transceiver channel (CanTrcvIndex).
 *  \details     This function has the service id 0x0A.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: The request to clear the WUF was accepted.
                 E_NOT_OK: The request to clear the WUF was rejected.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvWufFlag(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReadTrcvTimeoutFlag
 **********************************************************************************************************************/
/*! \brief       Reads the status of the timeout flag from the transceiver hardware.
 *  \details     This function has the service id 0x0B.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  FlagState: State of the timeout flag.
 *  \return      E_OK: Status was successfully read.
                 E_NOT_OK: Status could not be read or DET occurred.
 *  \pre         -
 *  \context     ANY
  * \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReadTrcvTimeoutFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Sbc_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) FlagState);


/***********************************************************************************************************************
 | NAME:  CanTrcv_30_Sbc_ClearTrcvTimeoutFlag
 **********************************************************************************************************************/
/*! \brief       Clears the status of the timeout flag in the transceiver hardware.
 *  \details     This function has the service id 0x0C.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Timeout flag cleared successfully.
                 E_NOT_OK: Timeout flag could not be cleared or DET occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ClearTrcvTimeoutFlag(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_ReadTrcvSilenceFlag
 **********************************************************************************************************************/
/*! \brief       Reads the status of the silence flag from the transceiver hardware.
 *  \details     This function has the service id 0x0D.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  FlagState: State of the silence flag.
 *  \return      E_OK: Status was read successfully.
                 E_NOT_OK: Status could not be read or DET occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_ReadTrcvSilenceFlag(uint8 CanTrcvIndex, P2VAR(CanTrcv_30_Sbc_TrcvFlagStateType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) FlagState);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_CheckWakeFlag
 **********************************************************************************************************************/
/*! \brief       Requests to check the status of the wake-up flag from the transceiver hardware.
 *  \details     This function has the service id 0x0E.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Request has been accepted.
                 E_NOT_OK: Request has not been accepted or DET occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_CheckWakeFlag(uint8 CanTrcvIndex);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_SetPNActivationState
 **********************************************************************************************************************/
/*! \brief       Enables / disables selective wake-up for all transceiver channels.
 *  \details     This function has the service id 0x0F.
 *  \param[in]   ActivationState: State of PN-mode to be applied for all transceiver channels.
 *               <ENABLE>: Selective wake-up for all channels where PN is configured shall be enabled.
 *               <DISABLE>: Disable the selective wake-up functionality on all transceiver channels.
 *  \return      E_OK: If PN-mode was changed successfully.
 *               E_NOT_OK: PN-mode change was NOT accepted or DET occurred.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_SetPNActivationState(CanTrcv_30_Sbc_PNActivationType ActivationState);
#endif /* (CANTRCV_30_SBC_HW_PN_SUPPORT == STD_ON) */


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Sbc_MainFunction
 **********************************************************************************************************************/
/*! \brief       Service to scan all buses for wake up events and perform these event.
 *  \details     This function has the service id 0x06.
 *  \param[in]   -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_SBC_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
/* FUNC(void, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_MainFunction(void); */ /* ESCAN00091270 */


#if !defined (CANTRCV_30_SBC_CALLBACK_FUNCTIONS)
# define CANTRCV_30_SBC_CALLBACK_FUNCTIONS STD_OFF
#endif

#if (CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_ON)
/************************************************************************************************************
 *  CanTrcv_30_Sbc_Hw_SetMode()
 ***********************************************************************************************************/
/*! \brief       Callback function to change CAN transceiver hardware Mode.
 *  \details     Application callback function which changes the hardware Mode of the CAN transceiver.
 *  \param[in]   id: Peripheral id of the CAN transceiver.
 *  \param[in]   mode: Requested mode.
 *  \return      E_OK: If transceiver Mode change was successful.
 *  \return      E_NOT_OK: If transceiver Mode change failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_ON
***********************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Hw_SetMode(Sbc_PeripheralIdType id, Sbc_CanTrcvModeType mode);

/************************************************************************************************************
 *  CanTrcv_30_Sbc_Hw_ReadStatus()
 ***********************************************************************************************************/
/*! \brief       Callback function to read the status of CAN transceiver hardware.
 *  \details     Application callback function which reads the hardware status CAN transceiver.
 *  \param[in]   id: Peripheral id of the CAN transceiver.
 *  \param[out]  status: Pointer to store status information.
 *  \return      E_OK: If transceiver status was read successfully.
 *  \return      E_NOT_OK: If transceiver status was not read successfully.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_ON
***********************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Hw_ReadStatus(Sbc_PeripheralIdType id, P2VAR(Sbc_CanTrcvStatusType, AUTOMATIC, CANTRCV_30_SBC_APPL_VAR) status);

/************************************************************************************************************
 *  CanTrcv_30_Sbc_Hw_ClearEvents()
 ***********************************************************************************************************/
/*! \brief       Callback function to clear CAN transceiver hardware Events.
 *  \details     Application callback function which clears the hardware Events of the CAN transceiver.
 *  \param[in]   id: Peripheral id of the CAN transceiver.
 *  \param[in]   events: Events that are cleared.
 *  \return      E_OK: If transceiver Events are cleared successfully.
 *  \return      E_NOT_OK: If transceiver Events are not cleared successfully.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_ON
***********************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Hw_ClearEvents(Sbc_PeripheralIdType id, Sbc_CanTrcvEventType events);

/************************************************************************************************************
 *  CanTrcv_30_Sbc_Hw_WritePnConfig()
 ***********************************************************************************************************/
/*! \brief       Callback function to write PN configuration to hardware.
 *  \details     Application callback function writes the PN configuration to hardware.
 *  \param[in]   id: Peripheral id of the CAN transceiver.
 *  \return      E_OK: If PN configuration was written successful.
 *  \return      E_NOT_OK: If PN configuration failed.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_SBC_CALLBACK_FUNCTIONS == STD_ON
***********************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_SBC_CODE) CanTrcv_30_Sbc_Hw_WritePnConfig(Sbc_PeripheralIdType id);
#endif

# define CANTRCV_30_SBC_STOP_SEC_CODE
# include "MemMap.h"



/*! 
* \exclusivearea CANTRCV_SBC_EXCLUSIVE_AREA_0
* Ensures consistent handling of CanTrcv-hardware via the SBC-driver-interface.
* \protects Atomic / consistent usage of SBC-driver-interface.
* \usedin CanTrcv_30_Sbc_Init(), CanTrcv_30_Sbc_SetOpMode(), CanTrcv_30_Sbc_GetOpMode(), CanTrcv_30_Sbc_CheckWakeup() and CanTrcv_30_Sbc_MainFunction().
* \exclude call of: CanTrcv-driver APIs: CanTrcv_30_Sbc_Init(), CanTrcv_30_Sbc_SetOpMode(), CanTrcv_30_Sbc_GetOpMode(), CanTrcv_30_Sbc_CheckWakeup() 
*                   and CanTrcv_30_Sbc_MainFunction().
* \length LONG Call to SBC module.
* \endexclusivearea
*/

#endif /* CANTRCV_30_SBC_API_H */

/* ********************************************************************************************************************
 *  END OF FILE
 * *******************************************************************************************************************/
