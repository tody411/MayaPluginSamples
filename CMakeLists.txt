cmake_minimum_required(VERSION 3.0.0)

#=======================
# CMake module path
#=======================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#=======================
# Project setting
#=======================
project(MayaSmaplePlugins)

# Add plug-in directories.
add_subdirectory(NoiseCmd)
add_subdirectory(NoiseDeformer)
add_subdirectory(LaplacianSmoother)
