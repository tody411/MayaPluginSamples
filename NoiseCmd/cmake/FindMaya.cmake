# - Find Maya package for Windows.
#
# Inputs:
#  MAYA_LOCATION          If defined, it will be searched first for Maya location.
#
# Outputs:
#  MAYA_FOUND             Defined if a Maya is found.
#  MAYA_VERSION           Version of detected Maya (e.g. 2015).
#
#  MAYA_INCLUDE_DIRS      Path to Maya's include directories.
#
#  MAYA_LIBRARY_DIRS      Path to Maya's library directories.
#  MAYA_LIBRARIES         List of detected Maya libraries.
#  MAYA_<Lib>_FOUND       Defined if <Lib> is found.
#  MAYA_<Lib>_LIBRARY     <Lib> Path.
#
#  MAYA_EXE               Maya's executable path.
#  MAYA_PLUGIN_SUFFIX     Maya plug-in file extension.
#
#
# Macros:
#  Maya_set_target_properties  Set target properties for the target project name.
#                              COMPILE_DEFINITIONS, COMPILE_FLAGS, LINK_FLAGS, etc.
#

# Predefined variables
set(MAYA_PLUGIN_SUFFIX ".mll")

#=======================
# Macros
#=======================

# Set target properties for the target project name.
#  - COMPILE_DEFINITIONS, COMPILE_FLAGS, LINK_FLAGS, etc.
macro(Maya_set_target_properties target)
    set(MAYA_COMPILE_DEFINITIONS REQUIRE_IOSTREAM _BOOL _AFXDLL _MBCS NT_PLUGIN)
    set(MAYA_COMPILE_FLAGS "/MD")
    set(MAYA_LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin")

    set_target_properties( ${target} PROPERTIES
        COMPILE_DEFINITIONS "${MAYA_COMPILE_DEFINITIONS}"
        COMPILE_FLAGS "${MAYA_COMPILE_FLAGS}"
        LINK_FLAGS "${MAYA_LINK_FLAGS}"
        PREFIX ""
        SUFFIX ${MAYA_PLUGIN_SUFFIX}
    )

endmacro(Maya_set_target_properties)


# Create search list for versions.

set(_maya_VERSIONS)
foreach(version RANGE 2016 2008 -1)
    list(APPEND _maya_VERSIONS "${version}")
endforeach()

set(_maya_SEARCH_VERSIONS)

if(Maya_FIND_VERSION_EXACT)
    # for e.g. find_package(Maya 2015 EXACT)
    list(APPEND _maya_SEARCH_VERSIONS "${Maya_FIND_VERSION}")

else()
    if(Maya_FIND_VERSION)
        # for e.g. find_package(Maya 2015)
        foreach(version ${_maya_VERSIONS})
            if(NOT "${version}" VERSION_LESS "${Maya_FIND_VERSION}")
                list(APPEND _maya_SEARCH_VERSIONS "${version}")
            endif()
        endforeach()

    else()
        # find_package(Maya REQUIRED)
        set(_maya_SEARCH_VERSIONS ${_maya_VERSIONS})
    endif()

endif()


# Create search list for paths.

set(_maya_SEARCH_PATHS)

foreach(version ${_maya_SEARCH_VERSIONS})
    set(_maya_SEARCH_PATHS ${_maya_SEARCH_PATHS}
        "$ENV{PROGRAMFILES}/Autodesk/Maya${version}-x64"
        "$ENV{PROGRAMFILES}/Autodesk/Maya${version}"
        "C:/Program Files/Autodesk/Maya${version}-x64"
        "C:/Program Files/Autodesk/Maya${version}"
        "C:/Program Files (x86)/Autodesk/Maya${version}")
endforeach(version)

# Search Maya EXE path from the MAYA_LOCATION and _maya_SEARCH_PATHS.
find_program(MAYA_EXE maya
    PATHS $ENV{MAYA_LOCATION} ${_maya_SEARCH_PATHS}
    PATH_SUFFIXES bin
    NO_SYSTEM_ENVIRONMENT_PATH
    DOC "Maya EXE")

if(MAYA_EXE)
    # obtain MAYA_LOCATION, MAYA_VERSION from MAYA_EXE.
    string(REGEX REPLACE "/bin/maya.*" "" MAYA_LOCATION "${MAYA_EXE}")
    string(REGEX MATCH "20[0-9][0-9]" MAYA_VERSION "${MAYA_LOCATION}")

else()
    set(MAYA_LOCATION NOTFOUND)
    if(Maya_FIND_VERSION)
        message(FATAL_ERROR "Maya: failed to find version >= ${Maya_FIND_VERSION}")

    else()
        message(FATAL_ERROR "Maya: failed to find any versions")
    endif()
endif()

message(STATUS "Maya: location = ${MAYA_LOCATION}")

# Visual Studio Versions
if(${MAYA_VERSION} STREQUAL "2011")
    set(MAYA_MSVC_VERSION "9")
elseif(${MAYA_VERSION} STREQUAL "2012")
    set(MAYA_MSVC_VERSION  "9")
elseif(${MAYA_VERSION} STREQUAL "2013")
    set(MAYA_MSVC_VERSION  "10")
elseif(${MAYA_VERSION} STREQUAL "2014")
    set(MAYA_MSVC_VERSION  "10")
elseif(${MAYA_VERSION} STREQUAL "2015")
    set(MAYA_MSVC_VERSION  "11")
elseif(${MAYA_VERSION} STREQUAL "2016")
    set(MAYA_MSVC_VERSION  "11")
endif()

message(STATUS "Maya: Visual Studio Tool Version = ${MAYA_MSVC_VERSION}")

find_path(MAYA_INCLUDE_DIRS maya/MFn.h
    HINTS ${MAYA_LOCATION}
    PATH_SUFFIXES
        include
    DOC "Maya: include")

message(STATUS "Maya: include = ${MAYA_INCLUDE_DIRS}")

find_path(MAYA_LIBRARY_DIRS OpenMaya.lib
    HINTS ${MAYA_LOCATION}
    PATH_SUFFIXES
        lib
    DOC "Maya: library")

message(STATUS "Maya: library = ${MAYA_LIBRARY_DIRS}")

foreach(_maya_lib
    OpenMaya
    OpenMayaAnim
    OpenMayaFX
    OpenMayaRender
    OpenMayaUI
    Image
    Foundation
    IMFbase
    tbb)

    find_library(MAYA_${_maya_lib}_LIBRARY ${_maya_lib}
        HINTS ${MAYA_LOCATION}
        PATHS ${_maya_SEARCH_PATHS}
        PATH_SUFFIXES lib
        DOC "Maya: ${MAYA_LIB} library")
    list(APPEND MAYA_LIBRARIES ${MAYA_${_maya_lib}_LIBRARY})
endforeach()

# message(STATUS "Maya: libraries = ${MAYA_LIBRARIES}")

find_path(MAYA_USER_DIR
    NAMES ${MAYA_VERSION}-x64 ${MAYA_VERSION}
    PATHS
        $ENV{USERPROFILE}/Documents/maya
    DOC "Maya: user directory"
    NO_SYSTEM_ENVIRONMENT_PATH)

message(STATUS "Maya: user directory = ${MAYA_USER_DIR}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Maya DEFAULT_MSG
    MAYA_LIBRARIES MAYA_EXE MAYA_INCLUDE_DIRS
    MAYA_LIBRARY_DIRS MAYA_VERSION MAYA_PLUGIN_SUFFIX
    MAYA_USER_DIR)

