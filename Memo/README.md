# Memo Project

This is a memo application with core document management functionality.

## Project Structure

- `engine/` - Core engine components
  - `core/` - Document model and core logic
  - `render/` - Rendering components
  - `storage/` - Storage management
  - `capi/` - C API interface
  - `tests/` - Unit tests

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- C++ compiler with C++17 support

### Setup Instructions

1. Open PowerShell as Administrator
2. Run the setup script:
   ```powershell
   .\setup_project.ps1
   ```

### Alternative Setup (Manual)
```powershell
mkdir build
cd build
"C:\Program Files\CMake\bin\cmake.exe" .. -G "Visual Studio 16 2019"
```

## Development Environment

The project uses CMake for cross-platform builds. The configuration in `.vscode/settings.json` and `.vscode/c_cpp_properties.json` should provide proper IntelliSense support in VS Code.

## Testing

Unit tests are included in the `engine/tests/` directory and can be built using the CMake configuration.

## Notes

This project requires a complete C++ development environment with standard library headers.
The current setup works with:
- Visual Studio 2019 or newer
- MSVC compiler toolchain