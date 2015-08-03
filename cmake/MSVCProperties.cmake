# - Visual Studio setting from CMake generator option.
#
# MSVC
#
# Inputs:
#  cmake -G <CMAKE_GENERATOR>    Specified generator from cmake command. e.g. "Visual Studio 11 Win64".
#
# Outputs:
#  MSVC_TOOL_VERSION             Visual Studio Version. Return 11 if "Visual Studio 11 Win64".
#  MSVC_ARCH                     Target architecture. 32: 32bit. 64: 64bit.

if (MSVC)
    message(STATUS "============================")
    message(STATUS "Visual Studio setting")
    message(STATUS "============================")
else()
    message(WARNING "Visual Studio: generator is not Visual Studio")
endif()

if(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
    set(MSVC_TOOL_VERSION 9)
    set(MSVC_ARCH 32)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008 Win64")
    set(MSVC_TOOL_VERSION 9)
    set(MSVC_ARCH 64)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 10" OR CMAKE_GENERATOR STREQUAL "Visual Studio 10 2010")
    set(MSVC_TOOL_VERSION 10)
    set(MSVC_ARCH 32)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 10 Win64" OR CMAKE_GENERATOR STREQUAL "Visual Studio 10 2010 Win64")
    set(MSVC_TOOL_VERSION 10)
    set(MSVC_ARCH 64)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 11" OR CMAKE_GENERATOR STREQUAL "Visual Studio 11 2012")
    set(MSVC_TOOL_VERSION 11)
    set(MSVC_ARCH 32)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 11 Win64" OR CMAKE_GENERATOR STREQUAL "Visual Studio 11 2012 Win64")
    set(MSVC_TOOL_VERSION 11)
    set(MSVC_ARCH 64)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 12" OR CMAKE_GENERATOR STREQUAL "Visual Studio 12 2013")
    set(MSVC_TOOL_VERSION 12)
    set(MSVC_ARCH 32)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 12 Win64" OR CMAKE_GENERATOR STREQUAL "Visual Studio 12 2013 Win64")
    set(MSVC_TOOL_VERSION 12)
    set(MSVC_ARCH 64)
endif()

message(STATUS "Visual Studio: Tool Version = ${MSVC_TOOL_VERSION}")
message(STATUS "Visual Studio: Architecture = ${MSVC_ARCH}")
message(STATUS "")