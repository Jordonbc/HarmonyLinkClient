cmake_minimum_required(VERSION 3.10)
project(HarmonyLinkTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically add all .cpp and .h/.hpp files in the src directory
file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "src/*.h" "src/*.hpp")

# Add executable
add_executable(HarmonyLinkTest ${TEST_SOURCES} ${TEST_HEADERS})

# Link the HarmonyLinkLib with HarmonyLinkTest
target_link_libraries(HarmonyLinkTest PRIVATE HarmonyLinkLib)

# Set output directories for all build types
foreach(TYPE IN ITEMS DEBUG RELEASE)
    string(TOUPPER ${TYPE} TYPE_UPPER)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/${PROJECT_NAME}"
        ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} "${CMAKE_BINARY_DIR}/bin/${TYPE}/${PROJECT_NAME}"
    )
endforeach()

add_custom_command(TARGET HarmonyLinkTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:HarmonyLinkLib>"
    "$<TARGET_FILE_DIR:HarmonyLinkTest>")
