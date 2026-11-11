# Simple toolchain file for cross-compilation or specific settings

# Set the target system
set(CMAKE_SYSTEM_NAME Windows)

# Specify the cross-compilation tools
# set(CMAKE_C_COMPILER clang)
# set(CMAKE_CXX_COMPILER clang++)

# Where to look for libraries and headers
# set(CMAKE_FIND_ROOT_PATH /usr/local/cross-tools)

# Adjust the default behavior of the FIND_XXX commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# search headers in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)