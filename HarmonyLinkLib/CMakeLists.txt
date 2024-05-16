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
project(HarmonyLinkLib VERSION 2.1.1)

include(FetchContent)

# Fetch fmt library
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1 # Specify the desired version of {fmt}
)

FetchContent_MakeAvailable(fmt)

set_target_properties(fmt PROPERTIES FOLDER External)
set_target_properties(fmt PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

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

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define metadata variables
set(FILE_DESCRIPTION "Enhances handheld gaming with intelligent hardware recognition, dynamic adaptability, and robust API access for Windows and Linux, including Steam Deck and Wine support.")
set(INTERNAL_NAME "HarmonyLinkLib")
set(ORIGINAL_FILENAME "HarmonyLinkLib.dll")
set(PRODUCT_NAME "HarmonyLinkLib")
set(COMMENTS "")

# Configure version.rc file for shared library
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)

# Explicitly list source files
set(COMMON_SOURCES
    "src/Platform/IPlatformUtilities.cpp"
    "src/HarmonyLinkLib.cpp"
    "src/Version.cpp"
    "src/dllmain.cpp"
    "src/Platform/WineUtilities.cpp"
    "src/Utilities.cpp"
)

# Explicitly list include files
set(COMMON_INCLUDES
    "include/Core.h"
    "include/Structs/FBattery.h"
    "include/Structs/FOSVerInfo.h"
    "include/Structs/FDevice.h"
    "include/Structs/FCPUInfo.h"
    "include/Enums/EDevice.h"
    "include/Enums/EPlatform.h"
    "include/Enums/ESteamDeck.h"
    "include/FString.h"
    "include/HarmonyLinkLib.h"
    "include/Version.h"
    "src/Platform/IPlatformUtilities.h"
    "src/Platform/WineUtilities.h"
    "src/Utilities.h"
)

# Adding fmt headers explicitly
set(FMT_HEADERS
    "${fmt_SOURCE_DIR}/include/fmt/args.h"
    "${fmt_SOURCE_DIR}/include/fmt/chrono.h"
    "${fmt_SOURCE_DIR}/include/fmt/color.h"
    "${fmt_SOURCE_DIR}/include/fmt/compile.h"
    "${fmt_SOURCE_DIR}/include/fmt/core.h"
    "${fmt_SOURCE_DIR}/include/fmt/format.h"
    "${fmt_SOURCE_DIR}/include/fmt/format-inl.h"
    "${fmt_SOURCE_DIR}/include/fmt/os.h"
    "${fmt_SOURCE_DIR}/include/fmt/ostream.h"
    "${fmt_SOURCE_DIR}/include/fmt/printf.h"
    "${fmt_SOURCE_DIR}/include/fmt/ranges.h"
    "${fmt_SOURCE_DIR}/include/fmt/std.h"
    "${fmt_SOURCE_DIR}/include/fmt/xchar.h"
)

set(WINDOWS_SOURCES
    "src/Platform/Windows/WindowsUtilities.cpp"
)

set(WINDOWS_INCLUDES
    "src/Platform/Windows/WindowsUtilities.h"
)

set(LINUX_SOURCES
    "src/Platform/Unix/Linux/LinuxUtilities.cpp"
    "src/Platform/Unix/UnixUtilities.cpp"
)

set(LINUX_INCLUDES
    "src/Platform/Unix/Linux/LinuxUtilities.h"
    "src/Platform/Unix/UnixUtilities.h"
)

set(MAC_SOURCES
    "src/Platform/Unix/Mac/MacUtilities.cpp"
    "src/Platform/Unix/UnixUtilities.cpp"
)

set(MAC_INCLUDES
    "src/Platform/Unix/Mac/MacUtilities.h"
    "src/Platform/Unix/UnixUtilities.h"
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
add_library(HarmonyLinkLibShared SHARED ${LIB_SOURCES} ${SHARED_SOURCES})
target_include_directories(HarmonyLinkLibShared 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(HarmonyLinkLibShared PRIVATE HARMONYLINKLIB_SHARED)

# Create the static library
add_library(HarmonyLinkLibStatic STATIC ${LIB_SOURCES})
target_include_directories(HarmonyLinkLibStatic 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(HarmonyLinkLibStatic PRIVATE HARMONYLINKLIB_STATIC)

# Include fmt headers
target_include_directories(HarmonyLinkLibStatic PUBLIC ${FMT_HEADERS})

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)
    set_target_properties(HarmonyLinkLibShared PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkLib"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkLib"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLib"
    )
    set_target_properties(HarmonyLinkLibStatic PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLibStatic"
    )
endforeach()

# Link fmt library to both shared and static libraries
target_link_libraries(HarmonyLinkLibShared PRIVATE fmt::fmt-header-only)
target_link_libraries(HarmonyLinkLibStatic PRIVATE fmt::fmt-header-only)
