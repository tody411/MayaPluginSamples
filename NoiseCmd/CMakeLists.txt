cmake_minimum_required(VERSION 3.0.0)

# Cmake module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Set project name.
project(NoiseCmd)

# Find Maya package.
#   - Find from latest versions: find_package(Maya REQUIRED)
#   - Specify target version: find_package(Maya 2015)
find_package(Maya 2015)

# Set Visual Studio properties.
include(MSVCProperties)

# Include setting.
include_directories(${MAYA_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

# Plug-in entry point.
add_library( ${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR}/src/NoiseCmd.cpp )

# Link setting.
#   - Link all libraries: MAYA_LIBRARIES
#   - Link target libraries: MAYA_Foundation_LIBRARY, MAYA_OpenMaya_LIBRARY, etc.
target_link_libraries( ${PROJECT_NAME}
   ${MAYA_Foundation_LIBRARY} ${MAYA_OpenMaya_LIBRARY} ${MAYA_OpenMayaUI_LIBRARY}
)

# Output settings.
set_target_properties( ${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}${MAYA_VERSION}
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/plugins
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/plugins
  CLEAN_DIRECT_OUTPUT 1
)

# Common settings for Maya Plug-in.
#   - COMPILE_DEFINITIONS, COMPILE_FLAGS, LINK_FLAGS, etc.
Maya_set_target_properties( ${PROJECT_NAME} )