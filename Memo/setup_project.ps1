# Setup script for Memo Project
Write-Host "Setting up Memo Project environment..."

# Create build directory if it doesn't exist
if (!(Test-Path -Path "build")) {
    New-Item -ItemType Directory -Path "build"
}

# Configure with CMake
Write-Host "Configuring with CMake..."
Set-Location build

# Try different generators in order of preference
& "C:\Program Files\CMake\bin\cmake.exe" .. -G "Unix Makefiles"

if ($LASTEXITCODE -eq 0) {
    Write-Host "CMake configuration successful with Unix Makefiles!"
    Write-Host "You can now build the project with: make"
} else {
    Write-Host "Unix Makefiles failed, trying other generators..."

    # Try with a more generic generator
    & "C:\Program Files\CMake\bin\cmake.exe" .. -G "MinGW Makefiles"

    if ($LASTEXITCODE -eq 0) {
        Write-Host "CMake configuration successful with MinGW Makefiles!"
        Write-Host "You can now build the project with: make"
    } else {
        Write-Host "CMake configuration failed. Please ensure CMake is properly installed."
    }
}

Write-Host "Setup complete."
Read-Host "Press Enter to continue..."