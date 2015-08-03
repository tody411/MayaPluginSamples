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
#  MAYA_<lib>_FOUND       Defined if <lib> is found.
#  MAYA_<lib>_LIBRARY     <lib> Path to <lib> library
#
#  MAYA_EXE               Path to Maya's executable
#  MAYA_PLUGIN_SUFFIX     File extension of the maya plugin.
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


set(_maya_SEARCH_VERSIONS)
set(_maya_VERSIONS "2016" "2015" "2014" "2013" "2012" "2011" "2010" "2009" "2008")

# Create search list for versions.
if(Maya_FIND_VERSION_EXACT)
    list(APPEND _maya_SEARCH_VERSIONS "${Maya_FIND_VERSION}")
else()
    # exact version not requested. we have some wiggle room
    if(Maya_FIND_VERSION)
        # loop through known versions and find anything >= requested
        foreach(version ${_maya_VERSIONS})
            if(NOT "${version}" VERSION_LESS "${Maya_FIND_VERSION}")
                list(APPEND _maya_SEARCH_VERSIONS "${version}")
            endif()
        endforeach()
    else()
        # no version specified: test everything
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

    if(Maya_FIND_VERSION)
        # test that we've found a valid version
        list(FIND _maya_SEARCH_VERSIONS ${MAYA_VERSION} _maya_FOUND_INDEX)
        if(${_maya_FOUND_INDEX} EQUAL -1)
            message(STATUS "Found Maya version ${MAYA_VERSION}, but requested at least ${Maya_FIND_VERSION}. Re-searching without environment variables...")
            set(MAYA_LOCATION NOTFOUND)
            # search again, but don't use environment variables
            # (these should be only paths we constructed based on requested version)
            find_path(MAYA_LOCATION maya
                PATHS ${_maya_SEARCH_PATHS}
                PATH_SUFFIXES bin
                DOC "Maya's Base Directory"
                NO_SYSTEM_ENVIRONMENT_PATH)
            set(MAYA_EXE "${MAYA_LOCATION}/bin/maya"
                CACHE PATH "Maya's executable path")
            string(REGEX MATCH "20[0-9][0-9]" MAYA_VERSION "${MAYA_LOCATION}")

        endif()
    endif()
endif()

message(STATUS "Maya location: ${MAYA_LOCATION}")

# Visual Studio Versions
if(${MAYA_VERSION} STREQUAL "2011")
    set(MAYA_VS_VERSION CACHE STRING "2008")
elseif(${MAYA_VERSION} STREQUAL "2012")
    set(MAYA_VS_VERSION CACHE STRING "2008")
elseif(${MAYA_VERSION} STREQUAL "2013")
    set(MAYA_VS_VERSION CACHE STRING "2010")
elseif(${MAYA_VERSION} STREQUAL "2014")
    set(MAYA_VS_VERSION CACHE STRING "2010")
elseif(${MAYA_VERSION} STREQUAL "2015")
    set(MAYA_VS_VERSION CACHE STRING "2012")
elseif(${MAYA_VERSION} STREQUAL "2016")
    set(MAYA_VS_VERSION CACHE STRING "2012")
endif()

message(STATUS "Visual Studio Version: ${MAYA_VS_VERSION}")


find_path(MAYA_INCLUDE_DIRS maya/MFn.h
    HINTS ${MAYA_LOCATION}
    PATH_SUFFIXES
        include
    DOC "Maya Include")

find_path(MAYA_LIBRARY_DIRS libOpenMaya.dylib libOpenMaya.so OpenMaya.lib
    HINTS ${MAYA_LOCATION}
    PATH_SUFFIXES
        lib    # linux and windows
    DOC "Maya Library")

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
        DOC "Maya's ${MAYA_LIB} library path")
    list(APPEND MAYA_LIBRARIES ${MAYA_${_maya_lib}_LIBRARY})
endforeach()

find_path(MAYA_USER_DIR
    NAMES ${MAYA_VERSION}-x64 ${MAYA_VERSION}
    PATHS
        $ENV{USERPROFILE}/Documents/maya
    DOC "Maya user home directory"
    NO_SYSTEM_ENVIRONMENT_PATH)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Maya DEFAULT_MSG
    MAYA_LIBRARIES MAYA_EXE MAYA_INCLUDE_DIRS
    MAYA_LIBRARY_DIRS MAYA_VERSION MAYA_PLUGIN_SUFFIX
    MAYA_USER_DIR)

