cmake_minimum_required(VERSION 3.0.0)

#=======================
# CMake module path
#=======================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake")

#=======================
# Project setting
#=======================
project(NoiseCmd)

#=======================
# Find Maya
#=======================
#  - Find from latest versions: find_package(Maya REQUIRED)
#  - Specify target version: find_package(Maya 2015)
find_package(Maya REQUIRED)

#=======================
# Visual Studio setting
#=======================
include(MSVCProperties)

#=======================
# Include setting
#=======================
include_directories(${MAYA_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

#=======================
# Plug-in entry point
#=======================
add_library( ${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR}/src/NoiseCmd.cpp )

#=======================
# Link setting
#=======================
#  - Link all libraries: MAYA_LIBRARIES
#  - Link target libraries: MAYA_Foundation_LIBRARY, MAYA_OpenMaya_LIBRARY, etc.
target_link_libraries( ${PROJECT_NAME}
   ${MAYA_Foundation_LIBRARY} ${MAYA_OpenMaya_LIBRARY} ${MAYA_OpenMayaUI_LIBRARY}
)

#=======================
# Output setting
#=======================
#  Project setting.
set(_plugin_NAME ${PROJECT_NAME}${MAYA_VERSION})
set(_plugin_DIR ${PROJECT_SOURCE_DIR}/plugins)
set_target_properties( ${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}${MAYA_VERSION}
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/plugins
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/plugins
  CLEAN_DIRECT_OUTPUT 1
)

message(STATUS "============================")
message(STATUS "Project setting")
message(STATUS "============================")
message(STATUS "Project: project name = ${PROJECT_NAME}")
message(STATUS "Project: plug-in name = ${_plugin_NAME}${MAYA_PLUGIN_SUFFIX}")
message(STATUS "Project: output directory = ${_plugin_DIR}")
message(STATUS "")

# Maya Plug-in settings.
#   - COMPILE_DEFINITIONS, COMPILE_FLAGS, LINK_FLAGS, etc.
Maya_set_target_properties( ${PROJECT_NAME} )