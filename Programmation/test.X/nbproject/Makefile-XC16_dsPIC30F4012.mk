#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-XC16_dsPIC30F4012.mk)" "nbproject/Makefile-local-XC16_dsPIC30F4012.mk"
include nbproject/Makefile-local-XC16_dsPIC30F4012.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC16_dsPIC30F4012
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c lib/periph_pwm.c lib/periph_tmr.c lib/LCDv3.c lib/periph_adc.c lib/fonctions_sup.c lib/ticks.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/lib/periph_pwm.o ${OBJECTDIR}/lib/periph_tmr.o ${OBJECTDIR}/lib/LCDv3.o ${OBJECTDIR}/lib/periph_adc.o ${OBJECTDIR}/lib/fonctions_sup.o ${OBJECTDIR}/lib/ticks.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/lib/periph_pwm.o.d ${OBJECTDIR}/lib/periph_tmr.o.d ${OBJECTDIR}/lib/LCDv3.o.d ${OBJECTDIR}/lib/periph_adc.o.d ${OBJECTDIR}/lib/fonctions_sup.o.d ${OBJECTDIR}/lib/ticks.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/lib/periph_pwm.o ${OBJECTDIR}/lib/periph_tmr.o ${OBJECTDIR}/lib/LCDv3.o ${OBJECTDIR}/lib/periph_adc.o ${OBJECTDIR}/lib/fonctions_sup.o ${OBJECTDIR}/lib/ticks.o

# Source Files
SOURCEFILES=main.c lib/periph_pwm.c lib/periph_tmr.c lib/LCDv3.c lib/periph_adc.c lib/fonctions_sup.c lib/ticks.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-XC16_dsPIC30F4012.mk ${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4012
MP_LINKER_FILE_OPTION=,--script=p30F4012.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/XC16_dsPIC30F4012/ea361e1430bfb3555a13d8512f47e9866e2711b1 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_pwm.o: lib/periph_pwm.c  .generated_files/flags/XC16_dsPIC30F4012/e4ec4330b7cbb6377ccd9d70bde25a971d994a7e .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_pwm.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_pwm.c  -o ${OBJECTDIR}/lib/periph_pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_tmr.o: lib/periph_tmr.c  .generated_files/flags/XC16_dsPIC30F4012/d56391e4c213d6e656636d55fdddf4999cb2bf29 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_tmr.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_tmr.c  -o ${OBJECTDIR}/lib/periph_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_tmr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/LCDv3.o: lib/LCDv3.c  .generated_files/flags/XC16_dsPIC30F4012/cf67b3e9eec4412d598ea5692b5231b414ae91b7 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/LCDv3.o.d 
	@${RM} ${OBJECTDIR}/lib/LCDv3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/LCDv3.c  -o ${OBJECTDIR}/lib/LCDv3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/LCDv3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_adc.o: lib/periph_adc.c  .generated_files/flags/XC16_dsPIC30F4012/edc78249a1227c17f1d33b31eec8d7d7bdbcca46 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_adc.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_adc.c  -o ${OBJECTDIR}/lib/periph_adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/fonctions_sup.o: lib/fonctions_sup.c  .generated_files/flags/XC16_dsPIC30F4012/2dc7d72046f80fbaf4e4348955052a0c180108d9 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/fonctions_sup.o.d 
	@${RM} ${OBJECTDIR}/lib/fonctions_sup.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/fonctions_sup.c  -o ${OBJECTDIR}/lib/fonctions_sup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/fonctions_sup.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/ticks.o: lib/ticks.c  .generated_files/flags/XC16_dsPIC30F4012/3e8d55a66ad2447100583d61a4b0086d716b133f .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/ticks.o.d 
	@${RM} ${OBJECTDIR}/lib/ticks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/ticks.c  -o ${OBJECTDIR}/lib/ticks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/ticks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1    -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/XC16_dsPIC30F4012/13f6c6d11a95b7d6c2dab552a0790af69a348bde .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_pwm.o: lib/periph_pwm.c  .generated_files/flags/XC16_dsPIC30F4012/c9868815bac9ce92726709d18ae7cfcca7852af2 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_pwm.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_pwm.c  -o ${OBJECTDIR}/lib/periph_pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_pwm.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_tmr.o: lib/periph_tmr.c  .generated_files/flags/XC16_dsPIC30F4012/b68715a2724aaeff1cc34d29bdfcb2f5ed6b980b .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_tmr.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_tmr.c  -o ${OBJECTDIR}/lib/periph_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_tmr.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/LCDv3.o: lib/LCDv3.c  .generated_files/flags/XC16_dsPIC30F4012/c365e4e37f61ba207ac5bbeb05b6c7f5bb5ab67c .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/LCDv3.o.d 
	@${RM} ${OBJECTDIR}/lib/LCDv3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/LCDv3.c  -o ${OBJECTDIR}/lib/LCDv3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/LCDv3.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/periph_adc.o: lib/periph_adc.c  .generated_files/flags/XC16_dsPIC30F4012/83794d02889b5d1f4a50972409e508836b0fa6f2 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/periph_adc.o.d 
	@${RM} ${OBJECTDIR}/lib/periph_adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/periph_adc.c  -o ${OBJECTDIR}/lib/periph_adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/periph_adc.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/fonctions_sup.o: lib/fonctions_sup.c  .generated_files/flags/XC16_dsPIC30F4012/5b647aa621bd2a22ed574074be446393e7f333c8 .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/fonctions_sup.o.d 
	@${RM} ${OBJECTDIR}/lib/fonctions_sup.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/fonctions_sup.c  -o ${OBJECTDIR}/lib/fonctions_sup.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/fonctions_sup.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib/ticks.o: lib/ticks.c  .generated_files/flags/XC16_dsPIC30F4012/323dcb5cb4cbc10c7385d443319df7fec400d8de .generated_files/flags/XC16_dsPIC30F4012/fd67b544a79261c2fe49714d5749bb13d89b49dc
	@${MKDIR} "${OBJECTDIR}/lib" 
	@${RM} ${OBJECTDIR}/lib/ticks.o.d 
	@${RM} ${OBJECTDIR}/lib/ticks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/ticks.c  -o ${OBJECTDIR}/lib/ticks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib/ticks.o.d"        -g -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD4=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_XC16_dsPIC30F4012=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
