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
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/md2_viewer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/lib32/libGL.so /usr/lib32/libglut.so /usr/lib32/libILUT.so.1 /usr/local/lib/lib3ds.so /usr/lib32/libmng.so ../../engine/dist/Debug/GNU-Linux-x86/libengine.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/md2viewer

dist/Debug/GNU-Linux-x86/md2viewer: /usr/lib32/libGL.so

dist/Debug/GNU-Linux-x86/md2viewer: /usr/lib32/libglut.so

dist/Debug/GNU-Linux-x86/md2viewer: /usr/lib32/libILUT.so.1

dist/Debug/GNU-Linux-x86/md2viewer: /usr/local/lib/lib3ds.so

dist/Debug/GNU-Linux-x86/md2viewer: /usr/lib32/libmng.so

dist/Debug/GNU-Linux-x86/md2viewer: ../../engine/dist/Debug/GNU-Linux-x86/libengine.a

dist/Debug/GNU-Linux-x86/md2viewer: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -m32 -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/md2viewer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/md2_viewer.o: md2_viewer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../engine/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/md2_viewer.o md2_viewer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/md2viewer

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
