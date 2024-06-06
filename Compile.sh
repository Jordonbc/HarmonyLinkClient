#!/bin/bash

set -e

clear

# Define color codes
GREEN='\033[0;32m'
NC='\033[0m' # No Color
PURPLE='\033[0;35m'
GRAY='\033[1;30m'

# Ensure dialog is installed
if ! command -v dialog &> /dev/null
then
    echo "dialog could not be found. Please install it to use this script."
    exit
fi

# Function to check if a compiler is installed
check_compiler() {
    if command -v $1 &> /dev/null
    then
        COMPILER_OPTIONS+=("$2" "$3" "$4")
    fi
}

# Array to store the menu options
COMPILER_OPTIONS=()

# Add available compilers to the options array
check_compiler g++ "1" "g++ (default)" "on"
check_compiler clang++ "2" "clang++" "off"
check_compiler clang++-15 "3" "clang++ 15" "off"
check_compiler clang++-16 "4" "clang++ 16" "off"
check_compiler clang++-17 "5" "clang++ 17" "off"

# Debug: print the compiler options
echo "Compiler options: ${COMPILER_OPTIONS[@]}"

# Check if any compilers are available
if [ ${#COMPILER_OPTIONS[@]} -eq 0 ]; then
    dialog --msgbox "No compilers found. Please install a compiler to use this script." 10 40
    exit
fi

# Prompt the user to choose one or more compilers
compiler_choices=$(dialog --colors --title "\Zb\Z5Select Compiler\Zn" --checklist "\nChoose one or more compilers:" 15 60 ${#COMPILER_OPTIONS[@]} "${COMPILER_OPTIONS[@]}" 3>&1 1>&2 2>&3)

# Process the selected compilers
C_COMPILERS=()
CXX_COMPILERS=()

# Debug: print the compiler choices
echo "Compiler choices: $compiler_choices"

for choice in $compiler_choices; do
    case $choice in
        1)
            C_COMPILERS+=("gcc")
            CXX_COMPILERS+=("g++")
            ;;
        2)
            C_COMPILERS+=("clang")
            CXX_COMPILERS+=("clang++")
            ;;
        3)
            C_COMPILERS+=("clang-15")
            CXX_COMPILERS+=("clang++-15")
            ;;
        4)
            C_COMPILERS+=("clang-16")
            CXX_COMPILERS+=("clang++-16")
            ;;
        5)
            C_COMPILERS+=("clang-17")
            CXX_COMPILERS+=("clang++-17")
            ;;
    esac
done

# Output the chosen compilers
msg="Chosen compilers:\n"
for i in "${!C_COMPILERS[@]}"; do
    msg+="C compiler: ${C_COMPILERS[$i]}, C++ compiler: ${CXX_COMPILERS[$i]}\n"
done

dialog --colors --msgbox "\Zb\Z5$msg\Zn" 20 60

# Prompt the user to choose a build type
build_choice=$(dialog --colors --title "\Zb\Z5Select Build Type\Zn" --menu "\nChoose a build type:" 10 40 2 \
1 "Release (default)" \
2 "Debug" 3>&1 1>&2 2>&3)

# Set the build type based on the user's choice
case $build_choice in
    2)
        BUILD_TYPE=Debug
        ;;
    *)
        BUILD_TYPE=Release
        ;;
esac

# Output the chosen build type
dialog --colors --msgbox "\Zb\Z5Build type:\Zn $BUILD_TYPE" 10 40

clear

# Create the build directory if it doesn't exist
if [ ! -d "linuxbuild" ]; then
    mkdir linuxbuild
fi

cd linuxbuild

# Run CMake with the selected compilers and build type
for i in "${!C_COMPILERS[@]}"; do
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_C_COMPILER=${C_COMPILERS[$i]} -DCMAKE_CXX_COMPILER=${CXX_COMPILERS[$i]} ..
    # Build the project
    cmake --build . --config $BUILD_TYPE -j 15 #--clean-first #--verbose
done

cd ..

# End with a success message
dialog --colors --msgbox "\Zb\Z5Build(s) completed successfully!\Zn" 10 40
