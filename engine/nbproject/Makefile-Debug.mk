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
	${OBJECTDIR}/src/shader.o \
	${OBJECTDIR}/src/backend/GL/box_gl.o \
	${OBJECTDIR}/src/base_mesh.o \
	${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o \
	${OBJECTDIR}/src/base_camera.o \
	${OBJECTDIR}/src/GLee.o \
	${OBJECTDIR}/src/physics_subsystem.o \
	${OBJECTDIR}/src/base_light.o \
	${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o \
	${OBJECTDIR}/src/backend/GL/base_mesh_gl.o \
	${OBJECTDIR}/src/lighting_tech.o \
	${OBJECTDIR}/src/backend_factory.o \
	${OBJECTDIR}/src/backend/GL/backend_gl.o \
	${OBJECTDIR}/src/orientation.o \
	${OBJECTDIR}/src/md2_loader.o \
	${OBJECTDIR}/src/base_3d_app.o \
	${OBJECTDIR}/src/backend/GL/bump_technique_gl.o \
	${OBJECTDIR}/src/colossus_math.o \
	${OBJECTDIR}/src/colossus_core.o \
	${OBJECTDIR}/src/backend/GL/texture_tech_gl.o \
	${OBJECTDIR}/src/backend/GL/light_gl.o \
	${OBJECTDIR}/src/backend/GL/base_texture_gl.o \
	${OBJECTDIR}/src/backend/GL/callbacks_gl.o \
	${OBJECTDIR}/src/file.o \
	${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o \
	${OBJECTDIR}/src/cubemap_tech.o \
	${OBJECTDIR}/src/backend/GL/camera_gl.o \
	${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o \
	${OBJECTDIR}/src/backend/GL/texture2d_gl.o \
	${OBJECTDIR}/src/frame_manager.o \
	${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o \
	${OBJECTDIR}/src/backend/GL/base_technique_gl.o

# C Compiler Flags
CFLAGS=-m32

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libengine.a

dist/Debug/GNU-Linux-x86/libengine.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${RM} dist/Debug/GNU-Linux-x86/libengine.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/GNU-Linux-x86/libengine.a

${OBJECTDIR}/src/shader.o: nbproject/Makefile-${CND_CONF}.mk src/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader.o src/shader.cpp

${OBJECTDIR}/src/backend/GL/box_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/box_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/box_gl.o src/backend/GL/box_gl.cpp

${OBJECTDIR}/src/base_mesh.o: nbproject/Makefile-${CND_CONF}.mk src/base_mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_mesh.o src/base_mesh.cpp

${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/cubemap_texture_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o src/backend/GL/cubemap_texture_gl.cpp

${OBJECTDIR}/src/base_camera.o: nbproject/Makefile-${CND_CONF}.mk src/base_camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_camera.o src/base_camera.cpp

${OBJECTDIR}/src/GLee.o: nbproject/Makefile-${CND_CONF}.mk src/GLee.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/GLee.o src/GLee.c

${OBJECTDIR}/src/physics_subsystem.o: nbproject/Makefile-${CND_CONF}.mk src/physics_subsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physics_subsystem.o src/physics_subsystem.cpp

${OBJECTDIR}/src/base_light.o: nbproject/Makefile-${CND_CONF}.mk src/base_light.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_light.o src/base_light.cpp

${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/mesh_sphere_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o src/backend/GL/mesh_sphere_gl.cpp

${OBJECTDIR}/src/backend/GL/base_mesh_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/base_mesh_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_mesh_gl.o src/backend/GL/base_mesh_gl.cpp

${OBJECTDIR}/src/lighting_tech.o: nbproject/Makefile-${CND_CONF}.mk src/lighting_tech.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lighting_tech.o src/lighting_tech.cpp

${OBJECTDIR}/src/backend_factory.o: nbproject/Makefile-${CND_CONF}.mk src/backend_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend_factory.o src/backend_factory.cpp

${OBJECTDIR}/src/backend/GL/backend_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/backend_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/backend_gl.o src/backend/GL/backend_gl.cpp

${OBJECTDIR}/src/orientation.o: nbproject/Makefile-${CND_CONF}.mk src/orientation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/orientation.o src/orientation.cpp

${OBJECTDIR}/src/md2_loader.o: nbproject/Makefile-${CND_CONF}.mk src/md2_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/md2_loader.o src/md2_loader.cpp

${OBJECTDIR}/src/base_3d_app.o: nbproject/Makefile-${CND_CONF}.mk src/base_3d_app.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_3d_app.o src/base_3d_app.cpp

${OBJECTDIR}/src/backend/GL/bump_technique_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/bump_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/bump_technique_gl.o src/backend/GL/bump_technique_gl.cpp

${OBJECTDIR}/src/colossus_math.o: nbproject/Makefile-${CND_CONF}.mk src/colossus_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/colossus_math.o src/colossus_math.cpp

${OBJECTDIR}/src/colossus_core.o: nbproject/Makefile-${CND_CONF}.mk src/colossus_core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/colossus_core.o src/colossus_core.cpp

${OBJECTDIR}/src/backend/GL/texture_tech_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/texture_tech_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/texture_tech_gl.o src/backend/GL/texture_tech_gl.cpp

${OBJECTDIR}/src/backend/GL/light_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/light_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/light_gl.o src/backend/GL/light_gl.cpp

${OBJECTDIR}/src/backend/GL/base_texture_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/base_texture_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_texture_gl.o src/backend/GL/base_texture_gl.cpp

${OBJECTDIR}/src/backend/GL/callbacks_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/callbacks_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/callbacks_gl.o src/backend/GL/callbacks_gl.cpp

${OBJECTDIR}/src/file.o: nbproject/Makefile-${CND_CONF}.mk src/file.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file.o src/file.cpp

${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/mesh_3ds_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o src/backend/GL/mesh_3ds_gl.cpp

${OBJECTDIR}/src/cubemap_tech.o: nbproject/Makefile-${CND_CONF}.mk src/cubemap_tech.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/cubemap_tech.o src/cubemap_tech.cpp

${OBJECTDIR}/src/backend/GL/camera_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/camera_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/camera_gl.o src/backend/GL/camera_gl.cpp

${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/skybox_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o src/backend/GL/skybox_technique_gl.cpp

${OBJECTDIR}/src/backend/GL/texture2d_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/texture2d_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/texture2d_gl.o src/backend/GL/texture2d_gl.cpp

${OBJECTDIR}/src/frame_manager.o: nbproject/Makefile-${CND_CONF}.mk src/frame_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame_manager.o src/frame_manager.cpp

${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/mesh_md2_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o src/backend/GL/mesh_md2_gl.cpp

${OBJECTDIR}/src/backend/GL/base_technique_gl.o: nbproject/Makefile-${CND_CONF}.mk src/backend/GL/base_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_technique_gl.o src/backend/GL/base_technique_gl.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libengine.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
