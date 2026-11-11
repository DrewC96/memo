@echo off
echo Setting up Memo Project environment...

REM Create build directory if it doesn't exist
mkdir build 2>nul

REM Configure with CMake
echo Configuring with CMake...
cd build

REM Try different generators in order of preference
"C:\Program Files\CMake\bin\cmake.exe" .. -G "Unix Makefiles"

if %errorlevel% equ 0 (
    echo CMake configuration successful with Unix Makefiles!
    echo You can now build the project with: make
) else (
    echo Unix Makefiles failed, trying MinGW Makefiles...
    "C:\Program Files\CMake\bin\cmake.exe" .. -G "MinGW Makefiles"

    if %errorlevel% equ 0 (
        echo CMake configuration successful with MinGW Makefiles!
        echo You can now build the project with: make
    ) else (
        echo CMake configuration failed. Please ensure CMake is properly installed.
    )
)

echo Setup complete.
pause