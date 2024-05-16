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
project(HarmonyLinkTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically add all .cpp and .h/.hpp files in the src directory
file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "src/*.h" "src/*.hpp")

# Add executable for static library
add_executable(HarmonyLinkTestStatic ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(HarmonyLinkTestStatic PRIVATE HarmonyLinkLibStatic)
target_compile_definitions(HarmonyLinkTestStatic PRIVATE HARMONYLINKLIB_STATIC)

# Add executable for shared library
add_executable(HarmonyLinkTestShared ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(HarmonyLinkTestShared PRIVATE HarmonyLinkLibShared)
target_compile_definitions(HarmonyLinkTestShared PRIVATE HARMONYLINKLIB_SHARED)

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)

    # Static test executable properties
    set_target_properties(HarmonyLinkTestStatic PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkTestStatic"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkTestStatic"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkTestStatic"
    )

    # Shared test executable properties
    set_target_properties(HarmonyLinkTestShared PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkTestShared"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkTestShared"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkTestShared"
    )
endforeach()

# Copy the DLL to the executable directory after building the shared test executable
add_custom_command(TARGET HarmonyLinkTestShared POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:HarmonyLinkLibShared>"
    "$<TARGET_FILE_DIR:HarmonyLinkTestShared>")
