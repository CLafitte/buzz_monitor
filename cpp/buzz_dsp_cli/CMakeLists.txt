cmake_minimum_required(VERSION 3.10)
project(buzz_dsp_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
)

# Add executable
add_executable(buzz_dsp_cli ${SOURCES})

# Optional: include directories (for future dsp.hpp etc.)
target_include_directories(buzz_dsp_cli PRIVATE include)
