cmake_minimum_required(VERSION 3.26.3)

project(zipper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ZSTD_BUILD_STATIC ON)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(zstd GIT_REPOSITORY https://github.com/facebook/zstd.git GIT_TAG zstd-0.4.2)
FetchContent_Declare(libzip GIT_REPOSITORY https://github.com/nih-at/libzip.git GIT_TAG v1.10.1)
FetchContent_MakeAvailable(zstd libzip)

add_executable(
    ${CMAKE_PROJECT_NAME} 
    main.cpp
    utils.cpp
    ArgsParser.cpp
    Zipper.cpp
    ProgressBar.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC libzip::zip -static)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif (MINGW)
