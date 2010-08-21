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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/physics_subsystem.o \
	${OBJECTDIR}/src/backend/GL/box_gl.o \
	${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o \
	${OBJECTDIR}/src/file.o \
	${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o \
	${OBJECTDIR}/src/backend/GL/bump_technique_gl.o \
	${OBJECTDIR}/src/backend/GL/base_mesh_gl.o \
	${OBJECTDIR}/src/backend/GL/light_gl.o \
	${OBJECTDIR}/src/backend/GL/texture2d_gl.o \
	${OBJECTDIR}/src/colossus_core.o \
	${OBJECTDIR}/src/shader.o \
	${OBJECTDIR}/src/backend/GL/texture_tech_gl.o \
	${OBJECTDIR}/src/base_mesh.o \
	${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o \
	${OBJECTDIR}/src/backend/GL/base_texture_gl.o \
	${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o \
	${OBJECTDIR}/src/backend/GL/backend_gl.o \
	${OBJECTDIR}/src/base_camera.o \
	${OBJECTDIR}/src/base_light.o \
	${OBJECTDIR}/src/orientation.o \
	${OBJECTDIR}/src/GLee.o \
	${OBJECTDIR}/src/base_3d_app.o \
	${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o \
	${OBJECTDIR}/src/md2_loader.o \
	${OBJECTDIR}/src/lighting_tech.o \
	${OBJECTDIR}/src/backend/GL/camera_gl.o \
	${OBJECTDIR}/src/backend_factory.o \
	${OBJECTDIR}/src/cubemap_tech.o \
	${OBJECTDIR}/src/frame_manager.o \
	${OBJECTDIR}/src/backend/GL/callbacks_gl.o \
	${OBJECTDIR}/src/colossus_math.o \
	${OBJECTDIR}/src/backend/GL/base_technique_gl.o


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
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libengine.a

dist/Release/GNU-Linux-x86/libengine.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${RM} dist/Release/GNU-Linux-x86/libengine.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/GNU-Linux-x86/libengine.a

${OBJECTDIR}/src/physics_subsystem.o: src/physics_subsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/physics_subsystem.o src/physics_subsystem.cpp

${OBJECTDIR}/src/backend/GL/box_gl.o: src/backend/GL/box_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/box_gl.o src/backend/GL/box_gl.cpp

${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o: src/backend/GL/mesh_sphere_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_sphere_gl.o src/backend/GL/mesh_sphere_gl.cpp

${OBJECTDIR}/src/file.o: src/file.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file.o src/file.cpp

${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o: src/backend/GL/mesh_3ds_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_3ds_gl.o src/backend/GL/mesh_3ds_gl.cpp

${OBJECTDIR}/src/backend/GL/bump_technique_gl.o: src/backend/GL/bump_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/bump_technique_gl.o src/backend/GL/bump_technique_gl.cpp

${OBJECTDIR}/src/backend/GL/base_mesh_gl.o: src/backend/GL/base_mesh_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_mesh_gl.o src/backend/GL/base_mesh_gl.cpp

${OBJECTDIR}/src/backend/GL/light_gl.o: src/backend/GL/light_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/light_gl.o src/backend/GL/light_gl.cpp

${OBJECTDIR}/src/backend/GL/texture2d_gl.o: src/backend/GL/texture2d_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/texture2d_gl.o src/backend/GL/texture2d_gl.cpp

${OBJECTDIR}/src/colossus_core.o: src/colossus_core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/colossus_core.o src/colossus_core.cpp

${OBJECTDIR}/src/shader.o: src/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader.o src/shader.cpp

${OBJECTDIR}/src/backend/GL/texture_tech_gl.o: src/backend/GL/texture_tech_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/texture_tech_gl.o src/backend/GL/texture_tech_gl.cpp

${OBJECTDIR}/src/base_mesh.o: src/base_mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_mesh.o src/base_mesh.cpp

${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o: src/backend/GL/mesh_md2_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/mesh_md2_gl.o src/backend/GL/mesh_md2_gl.cpp

${OBJECTDIR}/src/backend/GL/base_texture_gl.o: src/backend/GL/base_texture_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_texture_gl.o src/backend/GL/base_texture_gl.cpp

${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o: src/backend/GL/skybox_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/skybox_technique_gl.o src/backend/GL/skybox_technique_gl.cpp

${OBJECTDIR}/src/backend/GL/backend_gl.o: src/backend/GL/backend_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/backend_gl.o src/backend/GL/backend_gl.cpp

${OBJECTDIR}/src/base_camera.o: src/base_camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_camera.o src/base_camera.cpp

${OBJECTDIR}/src/base_light.o: src/base_light.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_light.o src/base_light.cpp

${OBJECTDIR}/src/orientation.o: src/orientation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/orientation.o src/orientation.cpp

${OBJECTDIR}/src/GLee.o: src/GLee.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/GLee.o src/GLee.c

${OBJECTDIR}/src/base_3d_app.o: src/base_3d_app.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/base_3d_app.o src/base_3d_app.cpp

${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o: src/backend/GL/cubemap_texture_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/cubemap_texture_gl.o src/backend/GL/cubemap_texture_gl.cpp

${OBJECTDIR}/src/md2_loader.o: src/md2_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/md2_loader.o src/md2_loader.cpp

${OBJECTDIR}/src/lighting_tech.o: src/lighting_tech.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lighting_tech.o src/lighting_tech.cpp

${OBJECTDIR}/src/backend/GL/camera_gl.o: src/backend/GL/camera_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/camera_gl.o src/backend/GL/camera_gl.cpp

${OBJECTDIR}/src/backend_factory.o: src/backend_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend_factory.o src/backend_factory.cpp

${OBJECTDIR}/src/cubemap_tech.o: src/cubemap_tech.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/cubemap_tech.o src/cubemap_tech.cpp

${OBJECTDIR}/src/frame_manager.o: src/frame_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frame_manager.o src/frame_manager.cpp

${OBJECTDIR}/src/backend/GL/callbacks_gl.o: src/backend/GL/callbacks_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/callbacks_gl.o src/backend/GL/callbacks_gl.cpp

${OBJECTDIR}/src/colossus_math.o: src/colossus_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/colossus_math.o src/colossus_math.cpp

${OBJECTDIR}/src/backend/GL/base_technique_gl.o: src/backend/GL/base_technique_gl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backend/GL
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backend/GL/base_technique_gl.o src/backend/GL/base_technique_gl.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libengine.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
