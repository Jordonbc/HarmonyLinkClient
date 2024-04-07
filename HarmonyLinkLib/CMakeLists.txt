cmake_minimum_required(VERSION 3.10)
project(HarmonyLinkLib VERSION 2.0.0)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1 # Specify the desired version of {fmt}
)

FetchContent_MakeAvailable(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  # Add fmt but exclude it from the ALL target, reducing IDE clutter
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set_target_properties(fmt PROPERTIES FOLDER External)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

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
    
    "include/FString.h"
    "include/HarmonyLinkLib.h"
    "include/Version.h"
    
    "src/Platform/IPlatformUtilities.h"
    "src/Platform/WineUtilities.h"

    "src//Utilities.h"
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

# Add library
add_library(HarmonyLinkLib SHARED ${LIB_SOURCES} ${LIB_INCLUDES})

target_include_directories(HarmonyLinkLib 
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/include"
)

target_compile_definitions(HarmonyLinkLib PRIVATE HARMONYLINKLIB_EXPORTS)

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/${PROJECT_NAME}"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/${PROJECT_NAME}"
    )
endforeach()

# Link fmt library
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
