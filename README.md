## Usage

```bash
zipper <path/to/source/dir> <path/to/output/dir>
```

## Build

### Requirements

* [CMake](https://cmake.org/)
* [MinGW](https://www.mingw-w64.org) (if you are compiling for windows)

```bash
# On Linux
cmake . -B build

# On windows
cmake . -B build -G "MinGW Makefiles"

# Compile
cmake --buid build
```

