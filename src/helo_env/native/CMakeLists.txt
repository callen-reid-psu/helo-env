cmake_minimum_required(VERSION 3.15)
project(helo_model C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Build as a shared library so it can be loaded via ctypes from Python.
file(GLOB HELO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

if(NOT HELO_SOURCES)
    message(WARNING "No .c files found in native/src/. Add the advisor's C model source there.")
endif()

add_library(helo_model SHARED ${HELO_SOURCES})

target_include_directories(helo_model PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Output directly into native/build so bindings.py can find it without
# guessing CMake's per-generator subdirectories.
set_target_properties(helo_model PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
)

if(MSVC)
    target_compile_options(helo_model PRIVATE /W4)
else()
    target_compile_options(helo_model PRIVATE -Wall -Wextra -O2)
endif()
