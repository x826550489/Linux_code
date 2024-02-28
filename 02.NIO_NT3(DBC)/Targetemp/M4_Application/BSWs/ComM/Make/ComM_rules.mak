############################################################################### 
# File Name  : ComM_rules.mak 
# Description: Rules makefile 
#-----------------------------------------------------------------------------
# COPYRIGHT
#-----------------------------------------------------------------------------
# Copyright (c) 2021 by Vector Informatik GmbH.  All rights reserved.
#-----------------------------------------------------------------------------
# REVISION HISTORY
#-----------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2012-07-13  vispet  Initial Version of Template (1.0)
# 1.01.00   2013-04-12  vismih  Added ComM_PBcfg.c (AR4-325)
# 1.01.01   2018-03-08  vismih  Removed unused definitions
# 1.02.00   2019-02-14  vircbl  Added support of component-based SIP structure
# 2.00.00   2021-04-26  vispps  Adapted generated source files
#-----------------------------------------------------------------------------
# TemplateVersion = 1.02
############################################################################### 

# Library Settings
LIBRARIES_TO_BUILD      += ComM
ComM_FILES              += ComM$(BSW_SRC_DIR)\ComM.c

# Component Files
CC_FILES_TO_BUILD       += ComM$(BSW_SRC_DIR)\ComM.c

ASM_FILES_TO_BUILD      +=

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automaticly 
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   +=

include $(GENDATA_DIR)\Make\ComM_rules_generated.mak

#e.g.: COMMON_SOURCE_FILES     += $(GENDATA_DIR)\v_par.c
COMMON_SOURCE_FILES     += 

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automaticly
# so in this clean-rule it is only necessary to define additional files which
# were not delete automaticly.
# e.g.: $(<PATH>)\can_test.c
#-------------------------------------------------------------------------------------------------
MAKE_CLEAN_RULES        +=
#MAKE_GENERATE_RULES     +=
#MAKE_COMPILER_RULES     +=
#MAKE_DEBUG_RULES        +=
#MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES          +=


###############################################################
# REQUIRED   (defined in BaseMake (Global.Makefile.target...))
#
# SSC_ROOT		(required)
# PROJECT_ROOT	(required)
#
# LIB_OUTPUT_PATH	(optional)
# OBJ_OUTPUT_PATH	(optional)
#
# OBJ_FILE_SUFFIX	
# LIB_FILE_SUFFIX
#
###############################################################


###############################################################
# PROVIDE   this Section can be used to define own additional rules
#
# In vendorx_can_cfg.mak:
# Please configure the project file:
#CAN_CONFIG_FILE = $(PROJECT_ROOT)\source\network\can\my_can_config.cfg

#In vendorx_can_config :
#generate_can_config:
	#$(SSC_ROOT)\core\com\can\tools\canconfiggen.exe -o $(CAN_CONFIG_FILE)


###############################################################
# SPECIFIC
#
# There are no rules defined for the Specific part of the 
# Rules-Makefile. Each author is free to create temporary 
# variables or to use other resources of GNU-MAKE
#
###############################################################


