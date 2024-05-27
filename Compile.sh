#!/bin/sh

set -e

clear

# Define the color codes
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Prompt the user to choose a compiler
echo "${GREEN}Select the compiler to use:${NC}"
echo "1) g++ (default)"
echo "2) clang++"
echo "3) clang++ 15"
echo "4) clang++ 16"
read -p "Enter the number of your choice: " choice

# Set the compiler based on the user's choice
case $choice in
    2)
        C_COMPILER=clang
        CXX_COMPILER=clang++
        ;;
    3)
        C_COMPILER=clang-15
        CXX_COMPILER=clang++-15
        ;;
    4)
        C_COMPILER=clang-16
        CXX_COMPILER=clang++-16
        ;;
    *)
        C_COMPILER=gcc
        CXX_COMPILER=g++
        ;;
esac

echo "Using C compiler: $C_COMPILER"
echo "Using C++ compiler: $CXX_COMPILER"

# Prompt the user to choose a build type
echo "${GREEN}Select the build type:${NC}"
echo "1) Release (default)"
echo "2) Debug"
read -p "Enter the number of your choice: " build_choice

# Set the build type based on the user's choice
case $build_choice in
    2)
        BUILD_TYPE=Debug
        ;;
    *)
        BUILD_TYPE=Release
        ;;
esac

echo "Build type: $BUILD_TYPE"

# Create the build directory if it doesn't exist
if [ ! -d "linuxbuild" ]; then
    mkdir linuxbuild
fi

cd linuxbuild

# Run CMake with the selected compiler and build type
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_C_COMPILER=$C_COMPILER -DCMAKE_CXX_COMPILER=$CXX_COMPILER ..

# Build the project
cmake --build . --config $BUILD_TYPE --clean-first -j 15 --verbose

cd ..
