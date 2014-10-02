#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CApp.o \
	${OBJECTDIR}/CBaseBlackAndWhite.o \
	${OBJECTDIR}/CBaseCanny.o \
	${OBJECTDIR}/CBaseEmboss.o \
	${OBJECTDIR}/CBenchmarkDlg.o \
	${OBJECTDIR}/CBlackAndWhite.o \
	${OBJECTDIR}/CCanny.o \
	${OBJECTDIR}/CDocument.o \
	${OBJECTDIR}/CDocumentObserver.o \
	${OBJECTDIR}/CEmboss.o \
	${OBJECTDIR}/CFrame.o \
	${OBJECTDIR}/CIdDlg.o \
	${OBJECTDIR}/CMoments.o \
	${OBJECTDIR}/CMomentsDlg.o \
	${OBJECTDIR}/CPicture.o \
	${OBJECTDIR}/CProcessingDlg.o \
	${OBJECTDIR}/CProcessor.o \
	${OBJECTDIR}/CProgressCtrl.o \
	${OBJECTDIR}/CTestDlg.o \
	${OBJECTDIR}/CViewEdit.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imager

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imager: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imager ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/CApp.o: CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CApp.o CApp.cpp

${OBJECTDIR}/CBaseBlackAndWhite.o: CBaseBlackAndWhite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBaseBlackAndWhite.o CBaseBlackAndWhite.cpp

${OBJECTDIR}/CBaseCanny.o: CBaseCanny.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBaseCanny.o CBaseCanny.cpp

${OBJECTDIR}/CBaseEmboss.o: CBaseEmboss.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBaseEmboss.o CBaseEmboss.cpp

${OBJECTDIR}/CBenchmarkDlg.o: CBenchmarkDlg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBenchmarkDlg.o CBenchmarkDlg.cpp

${OBJECTDIR}/CBlackAndWhite.o: CBlackAndWhite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBlackAndWhite.o CBlackAndWhite.cpp

${OBJECTDIR}/CCanny.o: CCanny.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CCanny.o CCanny.cpp

${OBJECTDIR}/CDocument.o: CDocument.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDocument.o CDocument.cpp

${OBJECTDIR}/CDocumentObserver.o: CDocumentObserver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDocumentObserver.o CDocumentObserver.cpp

${OBJECTDIR}/CEmboss.o: CEmboss.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEmboss.o CEmboss.cpp

${OBJECTDIR}/CFrame.o: CFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFrame.o CFrame.cpp

${OBJECTDIR}/CIdDlg.o: CIdDlg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CIdDlg.o CIdDlg.cpp

${OBJECTDIR}/CMoments.o: CMoments.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMoments.o CMoments.cpp

${OBJECTDIR}/CMomentsDlg.o: CMomentsDlg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMomentsDlg.o CMomentsDlg.cpp

${OBJECTDIR}/CPicture.o: CPicture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPicture.o CPicture.cpp

${OBJECTDIR}/CProcessingDlg.o: CProcessingDlg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CProcessingDlg.o CProcessingDlg.cpp

${OBJECTDIR}/CProcessor.o: CProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CProcessor.o CProcessor.cpp

${OBJECTDIR}/CProgressCtrl.o: CProgressCtrl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CProgressCtrl.o CProgressCtrl.cpp

${OBJECTDIR}/CTestDlg.o: CTestDlg.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CTestDlg.o CTestDlg.cpp

${OBJECTDIR}/CViewEdit.o: CViewEdit.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CViewEdit.o CViewEdit.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/imager

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
