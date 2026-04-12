@echo off
if "%1"=="" (
    set BUILD_NAME=pc/build32
) else (
    set BUILD_NAME=%1
)

if "%2"=="" (
    set MINGW32=C:/msys64/mingw32
) else (
    set MINGW32=%2
)

set PATH=%MINGW32%/bin;%PATH%
set SCRIPT_DIR=%~dp0
set BUILD_DIR=%SCRIPT_DIR%%BUILD_NAME%

echo "MINGW32 path: %MINGW32%"
echo "BUILD_DIR: %BUILD_DIR%"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

if not exist "Makefile" echo "=== Configuring CMake ===" && cmake %SCRIPT_DIR%/pc -G Ninja -DMINGW32=%MINGW32% -DCMAKE_TOOLCHAIN_FILE="%SCRIPT_DIR%/pc/cmake/Toolchain-ninja.cmake"

echo "=== Building PC port ==="
ninja