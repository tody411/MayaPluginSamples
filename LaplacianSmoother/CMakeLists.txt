cmake_minimum_required(VERSION 3.0.0)

#=======================
# CMake module path
#=======================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake")

#=======================
# Project setting
#=======================
project(LaplacianSmoother)
# set(_project_SOURCE ${PROJECT_SOURCE_DIR}/src/InitPlugin.cpp)
aux_source_directory(${PROJECT_SOURCE_DIR}/src _project_SOURCE)
# set(_project_SOURCE ${PROJECT_SOURCE_DIR}/src/InitPlugin.cpp ${_project_SOURCE})

#=======================
# Setup External Libraries
#=======================
include(SetupExtLibs)

#=======================
# Find Maya
#=======================
#  - Find from latest versions: find_package(Maya REQUIRED)
#  - Specify target version: find_package(Maya 2015)
find_package(Maya REQUIRED)

#=======================
# Find Eigen
#=======================
# SET(EIGEN_LOCATION "C:/Users/tody/Documents/todySVN/development/ext_lib/Eigen")
find_package(Eigen REQUIRED)

#=======================
# Visual Studio setting
#=======================
include(MSVCProperties)

#=======================
# Check Visual Studio versions
#=======================
message(STATUS "============================")
message(STATUS "Check Visual Studio versions")
message(STATUS "============================")
if (${MAYA_MSVC_VERSION} STREQUAL ${MSVC_TOOL_VERSION})
    message(STATUS "Maya Visutal Studio version == Generator setting")
else()
    message(WARNING "Maya Visutal Studio version != Generator setting")
    message(STATUS "WARNING: Maya Visutal Studio version != Generator setting")
endif()
message(STATUS "")

#=======================
# Include setting
#=======================
include_directories(${MAYA_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

#=======================
# Plug-in entry point
#=======================
add_library( ${PROJECT_NAME} SHARED ${_project_SOURCE} )

#=======================
# Link setting
#=======================
#  - Link all libraries: MAYA_LIBRARIES
#  - Link target libraries: MAYA_Foundation_LIBRARY, MAYA_OpenMaya_LIBRARY, etc.
target_link_libraries( ${PROJECT_NAME}
   ${MAYA_LIBRARIES}
   #${MAYA_Foundation_LIBRARY} ${MAYA_OpenMaya_LIBRARY} ${MAYA_OpenMayaUI_LIBRARY}
)

#=======================
# Output setting
#=======================
#  Project setting.
set(_plugin_NAME ${PROJECT_NAME}${MAYA_VERSION})
set(_plugin_DIR ${CMAKE_SOURCE_DIR}/plugins)
set_target_properties( ${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME ${_plugin_NAME}
  RUNTIME_OUTPUT_DIRECTORY ${_plugin_DIR}
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${_plugin_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${_plugin_DIR}
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