@echo off
setlocal enabledelayedexpansion

REM Clear the screen
cls

REM Define the color codes
set GREEN=
set NC=

REM Prompt the user to choose a compiler
echo %GREEN%Select the compiler to use:%NC%
echo 1^ ) MSBuild (default)
echo 2^ ) MinGW
echo 3^ ) Ninja
set /p choice=Enter the number of your choice: 

REM Set the generator and compiler based on the user's choice
if "%choice%"=="2" (
    set "GENERATOR=MinGW Makefiles"
    set "COMPILER_OPTION=-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"
) else if "%choice%"=="3" (
    set "GENERATOR=Ninja"
    set "COMPILER_OPTION="
) else (
    set "GENERATOR=Visual Studio 17 2022"
    set "COMPILER_OPTION=-A x64"
    set "choice=1"
)

echo Using generator: %GENERATOR%

REM Prompt the user to choose a build type
echo %GREEN%Select the build type:%NC%
echo 1^ ) Release (default)
echo 2^ ) Debug
set /p build_choice=Enter the number of your choice: 

REM Set the build type based on the user's choice
if "%build_choice%"=="2" (
    set "BUILD_TYPE=Debug"
) else (
    set "BUILD_TYPE=Release"
)

echo Build type: %BUILD_TYPE%

REM Create the build directory if it doesn't exist
if not exist "winbuild" (
    mkdir winbuild
)

cd winbuild

REM Get the number of processors
for /f "tokens=2 delims==" %%a in ('wmic cpu get NumberOfLogicalProcessors /value') do set "NUM_PROCESSORS=%%a"

REM Run CMake with the selected generator and build type
cmake -G "%GENERATOR%" %COMPILER_OPTION% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

REM Build the project
if "%choice%"=="1" (
    cmake --build . --config %BUILD_TYPE% -- /m:%NUM_PROCESSORS%
) else (
    cmake --build . --config %BUILD_TYPE% -- -j %NUM_PROCESSORS%
)

cd ..
