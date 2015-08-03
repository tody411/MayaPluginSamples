

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
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 11 Win64" OR CMAKE_GENERATOR STREQUAL "Visual Studio 10 2012 Win64")
    set(MSVC_TOOL_VERSION 11)
    set(MSVC_ARCH 64)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 12" OR CMAKE_GENERATOR STREQUAL "Visual Studio 12 2013")
    set(MSVC_TOOL_VERSION 12)
    set(MSVC_ARCH 32)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 12 Win64" OR CMAKE_GENERATOR STREQUAL "Visual Studio 12 2013 Win64")
    set(MSVC_TOOL_VERSION 12)
    set(MSVC_ARCH 32)
endif()

message(STATUS "Target Architecture ${MSVC_ARCH}")