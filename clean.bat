@echo off
setlocal

:: Handle argument
set CONFIG=%1

:: Default to Debug and Release if no arg
if "%CONFIG%"=="" (
    echo Cleaning both Debug and Release build folders...
    if exist build-Debug rmdir /s /q build-Debug
    if exist build-Release rmdir /s /q build-Release
    echo Clean complete.
    exit /b 0
)

:: Validate argument
if /I not "%CONFIG%"=="Debug" if /I not "%CONFIG%"=="Release" (
    echo Error: Invalid config "%CONFIG%" for clean.
    echo Usage: clean.bat ^(Debug^|Release^)
    exit /b 1
)

:: Clean single config folder
echo Cleaning %CONFIG% build folder...
if exist build-%CONFIG% rmdir /s /q build-%CONFIG%
echo Clean complete.