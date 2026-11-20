# Tests Documentation

This directory contains unit tests for the Memo application components.

## Building and Running Tests

To build and run the tests, follow these steps:

1. **Ensure dependencies are installed:**
   - GoogleTest (gtest)
   - SQLite3
   - CMake 3.16 or higher

2. **Build using CMake:**
```bash
cd Memo/engine/tests
mkdir build && cd build
cmake ..
make
```

3. **Run the tests:**
```bash
./DocumentTest
```

## Test Structure

The test file `DocumentTest.cpp` contains basic unit tests for the Document class:

- `CreateDocument`: Tests document creation with a title
- `SetTitle`: Tests setting and getting document title
- `SetContent`: Tests setting and getting document content  
- `AddStroke`: Tests stroke handling (interface test)
- `UndoRedo`: Tests undo/redo functionality

## Notes

- The tests are currently stubbed out to verify compilation and basic structure
- Full implementation of Document methods will be needed for complete testing
- Tests assume proper linking with core engine components