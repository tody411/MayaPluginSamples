cmake_minimum_required(VERSION 3.0.0)

#=======================
# CMake module path
#=======================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake")

#=======================
# Project setting
#=======================
project(NoiseCmd)
file(GLOB _project_SOURCE ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)

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
include_directories(${MAYA_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

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
   ${MAYA_Foundation_LIBRARY} ${MAYA_OpenMaya_LIBRARY} ${MAYA_OpenMayaUI_LIBRARY}
)

#=======================
# Maya Plug-in settings.
#=======================
Maya_set_target_properties( ${PROJECT_NAME} )