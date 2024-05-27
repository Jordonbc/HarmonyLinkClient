# Copyright (c) 2024 Jordon Brooks
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#   http://www.apache.org/licenses/LICENSE-2.0#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.10)
project(LibHarmonyLink VERSION 2.1.1)

# Specify the C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find the current Git branch and the last commit timestamp
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%ct
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_TIMESTAMP
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_BRANCH_NAME "Unknown")
    set(GIT_COMMIT_TIMESTAMP "Unknown")
endif()

configure_file(include/Version.h.in Version.generated.h)

# Define metadata variables
set(FILE_DESCRIPTION "Enhances handheld gaming with intelligent hardware recognition, dynamic adaptability, and robust API access for Windows and Linux, including Steam Deck and Wine support.")
set(INTERNAL_NAME "LibHarmonyLink")
set(ORIGINAL_FILENAME "LibHarmonyLink.dll")
set(PRODUCT_NAME "LibHarmonyLink")
set(COMMENTS "")

# Configure version.rc file for shared library
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)

# Explicitly list source files
set(COMMON_SOURCES
    src/HarmonyLinkLib.c
    src/Version.c
    src/Utilities.c

    src/Structs/Battery.c
    src/Structs/CPUInfo.c
    src/Structs/StringArray.c
    src/Structs/Device.c
    src/Structs/OSInfo.C
)

# Explicitly list include files
set(COMMON_INCLUDES
    include/Core.h
    include/HarmonyLinkLib.h
    include/Version.h
    include/Utilities.h
    
    include/Enums/Device.h
    include/Enums/Platform.h
    include/Enums/SteamDeck.h
    
    include/Structs/Battery.h
    include/Structs/CPUInfo.h
    include/Structs/StringArray.h
    include/Structs/Device.h
    include/Structs/OSInfo.h
)

set(WINDOWS_SOURCES
)

set(WINDOWS_INCLUDES
)

set(LINUX_SOURCES
)

set(LINUX_INCLUDES

)

set(MAC_SOURCES
)

set(MAC_INCLUDES
)

# Platform-specific definitions
if(WIN32)
    message(STATUS "Compiling for Windows...")
    list(APPEND LIB_SOURCES ${COMMON_SOURCES} ${WINDOWS_SOURCES})
    list(APPEND LIB_INCLUDES ${COMMON_INCLUDES} ${WINDOWS_INCLUDES})
    list(APPEND SHARED_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
elseif(UNIX)
    message(STATUS "Compiling for Unix-based systems...")
    if(APPLE)
        message(STATUS "Compiling for Mac...")
        list(APPEND LIB_SOURCES ${COMMON_SOURCES} ${MAC_SOURCES})
        list(APPEND LIB_INCLUDES ${COMMON_INCLUDES} ${MAC_INCLUDES})
    else()
        message(STATUS "Compiling for Linux...")
        list(APPEND LIB_SOURCES ${COMMON_SOURCES} ${LINUX_SOURCES})
        list(APPEND LIB_INCLUDES ${COMMON_INCLUDES} ${LINUX_INCLUDES})
    endif()
endif()

# Create the shared library
add_library(LibHarmonyLinkShared SHARED ${LIB_SOURCES} ${LIB_INCLUDES} ${SHARED_SOURCES})
target_include_directories(LibHarmonyLinkShared 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(LibHarmonyLinkShared PRIVATE HARMONYLINK_SHARED)

# Create the static library
add_library(LibHarmonyLinkStatic STATIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(LibHarmonyLinkStatic
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(LibHarmonyLinkStatic PRIVATE HARMONYLINK_STATIC)

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)
    set_target_properties(LibHarmonyLinkShared PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkLib"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkLib"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLib"
    )
    set_target_properties(LibHarmonyLinkStatic PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLibStatic"
    )
endforeach()
