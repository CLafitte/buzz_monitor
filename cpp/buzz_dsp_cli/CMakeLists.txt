cmake_minimum_required(VERSION 3.10)
project(buzz_dsp_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB SOURCES src/*.cpp)

# Add executable
add_executable(buzz_dsp_cli ${SOURCES})

# Include headers
target_include_directories(buzz_dsp_cli PRIVATE include)

# Optional install rule
install(TARGETS buzz_dsp_cli DESTINATION bin)
