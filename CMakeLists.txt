cmake_minimum_required(VERSION 3.26.3)

project(zipper VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(zstd GIT_REPOSITORY https://github.com/facebook/zstd.git GIT_TAG zstd-0.4.2)
FetchContent_Declare(libzip GIT_REPOSITORY https://github.com/nih-at/libzip.git GIT_TAG v1.10.1)
FetchContent_MakeAvailable(zstd libzip)

file(GLOB SOURCES "*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ZSTD_BUILD_STATIC ON)
set(BUILD_SHARED_LIBS OFF)

# add_subdirectory("zstd/build/cmake")

# add_library(zstd::libzstd_static ALIAS libzstd_static)

# add_subdirectory("libzip")

# target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "libzip/lib")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC libzip::zip)
