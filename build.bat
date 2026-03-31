@echo off
setlocal

:: Handle argument
set CONFIG=%1

:: Default to Debug if no arg
if "%CONFIG%"=="" set CONFIG=Debug

:: Validate input
if /I not "%CONFIG%"=="Debug" if /I not "%CONFIG%"=="Release" (
    echo Error: Invalid build type "%1"
    echo.
    exit /b 1
)

set BUILD_DIR=build-%CONFIG%

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

cd %BUILD_DIR%

echo Building %CONFIG%...

cmake .. -A x64
cmake --build . --config %CONFIG%

cd .. 

echo Built %CONFIG% in %BUILD_DIR%
