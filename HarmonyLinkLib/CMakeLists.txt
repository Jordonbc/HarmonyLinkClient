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
project(HarmonyLinkLib VERSION 2.1.2 LANGUAGES CXX)

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

# Fetch ghc library
FetchContent_Declare(
  ghc_filesystem
  GIT_REPOSITORY https://github.com/gulrak/filesystem.git
  GIT_TAG v1.5.14 # Specify the desired version of ghc
)

FetchContent_MakeAvailable(ghc_filesystem)

set_target_properties(ghc_filesystem PROPERTIES FOLDER External)
set_target_properties(ghc_filesystem PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

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
set(CMAKE_CXX_STANDARD 17)
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
  add_definitions(-DBUILD_WINDOWS)
elseif(UNIX)
  if(APPLE)
    add_definitions(-DBUILD_MACOS)
  else()
    add_definitions(-DBUILD_LINUX)
  endif()
  add_definitions(-DBUILD_UNIX)
endif()

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

# Detect the compiler name
get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)

# Replace forbidden characters in file names (optional, if needed)
string(REPLACE "." "_" COMPILER_NAME ${COMPILER_NAME})
string(REPLACE "/" "_" COMPILER_NAME ${COMPILER_NAME})
string(REPLACE "\\" "_" COMPILER_NAME ${COMPILER_NAME})

# Create the shared library
add_library(HarmonyLinkLibShared SHARED ${LIB_SOURCES} ${SHARED_SOURCES} ${LIB_INCLUDES})
target_include_directories(HarmonyLinkLibShared 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(HarmonyLinkLibShared PRIVATE HARMONYLINKLIB_SHARED)
set_target_properties(HarmonyLinkLibShared PROPERTIES OUTPUT_NAME "HarmonyLinkLibShared_${COMPILER_NAME}")

# Create the static library
add_library(HarmonyLinkLibStatic STATIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(HarmonyLinkLibStatic 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)
target_compile_definitions(HarmonyLinkLibStatic PRIVATE HARMONYLINKLIB_STATIC)
set_target_properties(HarmonyLinkLibStatic PROPERTIES OUTPUT_NAME "HarmonyLinkLibStatic_${COMPILER_NAME}")

# Set output directories for all build types
#foreach(TYPE IN ITEMS DEBUG RELEASE)
#    string(TOUPPER ${TYPE} TYPE_UPPER)
#    set_target_properties(HarmonyLinkLibShared PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkLib"
#        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkLib"
#        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLib"
#    )
#    set_target_properties(HarmonyLinkLibStatic PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkLibStatic"
#    )
#endforeach()

# Link fmt to HarmonyLinkLib
target_link_libraries(HarmonyLinkLibStatic PRIVATE fmt::fmt-header-only)
target_link_libraries(HarmonyLinkLibShared PRIVATE fmt::fmt-header-only)

# Link ghc to HarmonyLinkLib
target_link_libraries(HarmonyLinkLibStatic PRIVATE ghc_filesystem)
target_link_libraries(HarmonyLinkLibShared PRIVATE ghc_filesystem)

# Determine the compiler and set appropriate flags for libc++
#if (UNIX AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#    # Use libc++ instead of libstdc++ with Clang
#    target_compile_options(HarmonyLinkLibStatic PRIVATE -stdlib=libc++)
#    target_compile_options(HarmonyLinkLibShared PRIVATE -stdlib=libc++)
#    target_link_options(HarmonyLinkLibStatic PRIVATE -stdlib=libc++)
#    target_link_options(HarmonyLinkLibShared PRIVATE -stdlib=libc++)
#
#    # Ensure the proper include paths for libc++
#    target_include_directories(HarmonyLinkLibStatic SYSTEM PRIVATE
#        /usr/include/c++/v1
#        /usr/local/include/c++/v1
#        /usr/include
#    )
#    target_include_directories(HarmonyLinkLibShared SYSTEM PRIVATE
#        /usr/include/c++/v1
#        /usr/local/include/c++/v1
#        /usr/include
#    )
#
#    # Link against the libc++ library and the filesystem library
#    target_link_libraries(HarmonyLinkLibStatic PRIVATE c++ c++abi c++experimental)
#    target_link_libraries(HarmonyLinkLibShared PRIVATE c++ c++abi c++experimental)
#elseif (UNIX AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#    # Use libstdc++ with GCC
#    target_link_options(HarmonyLinkLibStatic PRIVATE -static-libgcc -static-libstdc++)
#    target_link_options(HarmonyLinkLibShared PRIVATE -static-libgcc -static-libstdc++)
#
#    # Link against the libstdc++ filesystem library if necessary
#    target_link_libraries(HarmonyLinkLibStatic PRIVATE stdc++fs)
#    target_link_libraries(HarmonyLinkLibShared PRIVATE stdc++fs)
#endif()
