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

cmake_minimum_required(VERSION 3.22.1)
project(HarmonyLinkTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically add all .cpp and .h/.hpp files in the src directory
file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "src/*.h" "src/*.hpp")

# Enable all compiler warnings and errors
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Add executable for static library
add_executable(HarmonyLinkTestStatic_CPP ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(HarmonyLinkTestStatic_CPP PRIVATE LibHarmonyLinkStatic)
target_compile_definitions(HarmonyLinkTestStatic_CPP PRIVATE HARMONYLINK_STATIC)

# Add executable for shared library
add_executable(HarmonyLinkTestShared_CPP ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(HarmonyLinkTestShared_CPP PRIVATE LibHarmonyLinkShared)
target_compile_definitions(HarmonyLinkTestShared_CPP PRIVATE HARMONYLINK_SHARED)

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)

    # Static test executable properties
    set_target_properties(HarmonyLinkTestStatic_CPP PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkTestStatic_CPP"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkTestStatic_CPP"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkTestStatic_CPP"
    )

    # Shared test executable properties
    set_target_properties(HarmonyLinkTestShared_CPP PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/HarmonyLinkTestShared_CPP"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/lib/${TYPE}/HarmonyLinkTestShared_CPP"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/archive/${TYPE}/HarmonyLinkTestShared_CPP"
    )
endforeach()

# Copy the DLL to the executable directory after building the shared test executable
add_custom_command(TARGET HarmonyLinkTestShared_CPP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:LibHarmonyLinkShared>"
    "$<TARGET_FILE_DIR:HarmonyLinkTestShared_CPP>")
