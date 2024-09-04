## Usage

```bash
zipper [path/to/source/dir] [path/to/output/dir]

# To list all the options
zipper -h
```

## Build

### Requirements

* [CMake](https://cmake.org/)
* [MinGW](https://www.mingw-w64.org)

```bash
# Build the cmake files
cmake . -B build -G "MinGW Makefiles"

# Compile
cmake --buid build
```

