cmake_minimum_required(VERSION 3.10)
project(HarmonyLinkProject)

# Check the build type and display a message accordingly
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building for Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Building for Release")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    message(STATUS "Building for MinSizeRel")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message(STATUS "Building for RelWithDebInfo")
else()
    message(STATUS "Building with unspecified build type")
endif()

add_compile_definitions($<$<CONFIG:Debug>:DEBUG_MODE>)

#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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

# Set global output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}")
endforeach()

# Add the library and executable directories

add_subdirectory(HarmonyLinkLib)
add_subdirectory(HarmonyLinkTest)

# Add Google Test as a subdirectory
#add_subdirectory(ThirdParty/googletest)

# Enable testing
#enable_testing()

# Include Google Test's include directory
#include_directories(ThirdParty/googletest/googletest/include)

# Define your test executable
#file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
#add_executable(Testing ${TEST_SOURCES})

# Set HarmonyLinkTest as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HarmonyLinkTest)

# Link Google Test and HarmonyLink library to the test executable
#target_link_libraries(Testing gtest gtest_main gmock HarmonyLinkLib)

#add_custom_command(TARGET Testing POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    "$<TARGET_FILE:HarmonyLinkLib>"
#    "$<TARGET_FILE_DIR:Testing>")

# Discover tests
#include(GoogleTest)
#gtest_discover_tests(Testing)
