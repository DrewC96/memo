#!/bin/bash

echo "Setting up Memo Project environment..."

# Create build directory if it doesn't exist
mkdir -p build

# Configure with CMake
echo "Configuring with CMake..."
cd build
cmake .. -G "Unix Makefiles"

if [ $? -eq 0 ]; then
    echo "CMake configuration successful!"
    echo "You can now build the project with: make"
else
    echo "CMake configuration failed. Please ensure CMake is properly installed."
fi

echo "Setup complete."