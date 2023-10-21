cmake_minimum_required(VERSION 3.24)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_UNITY_BUILD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

project(jml-dev VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()
include(CTest)

find_package(sol2 REQUIRED)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY "https://github.com/juce-framework/JUCE" GIT_TAG "7.0.8")
FetchContent_MakeAvailable(JUCE)

set_directory_properties(PROPERTIES JUCE_COMPANY_COPYRIGHT "Copyright 2023 neo-sonar. All rights reserved.")
set_directory_properties(PROPERTIES JUCE_COMPANY_NAME "neo-sonar")

add_subdirectory(module)
add_subdirectory(tool/jml-viewer)
add_subdirectory(tool/jml-designer)
add_subdirectory(test)
