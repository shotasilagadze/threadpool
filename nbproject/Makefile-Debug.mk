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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Channel.o \
	${OBJECTDIR}/PriorityQueue.o \
	${OBJECTDIR}/Stack.o \
	${OBJECTDIR}/Task.o \
	${OBJECTDIR}/TaskManager.o \
	${OBJECTDIR}/ThreadPool.o


# C Compiler Flags
CFLAGS=-pthread

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libthreadpool.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libthreadpool.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libthreadpool.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -dynamiclib -install_name libthreadpool.${CND_DLIB_EXT} -fPIC

${OBJECTDIR}/Channel.o: Channel.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Channel.o Channel.c

${OBJECTDIR}/PriorityQueue.o: PriorityQueue.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PriorityQueue.o PriorityQueue.c

${OBJECTDIR}/Stack.o: Stack.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Stack.o Stack.c

${OBJECTDIR}/Stack.h.gch: Stack.h nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o "$@" Stack.h

${OBJECTDIR}/Task.o: Task.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Task.o Task.c

${OBJECTDIR}/TaskManager.o: TaskManager.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TaskManager.o TaskManager.c

${OBJECTDIR}/ThreadPool.o: ThreadPool.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ThreadPool.o ThreadPool.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
