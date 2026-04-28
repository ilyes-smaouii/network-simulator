cmake_minimum_required(VERSION 3.10)
project(network-simulator LANGUAGES CXX)

project(network_simulator LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put executables in bin/

set(CPP_COMMON_SRC_DIR ../../lib/cpp-common)

# --- Library: cpp_common ---
file(GLOB CPP_COMMON_SOURCES
    ${CPP_COMMON_SOURCE_DIR}/*.cpp
    ${CPP_COMMON_SOURCE_DIR}/*.hpp
)

# Include CPP_COMMON_SOURCES when compiling cpp_common
# (cpp_common must have been added with add_executable() or add_library())
add_library(cpp_common ${CPP_COMMON_SOURCES})

target_include_directories(cpp_common PUBLIC
    ${CPP_COMMON_SOURCE_DIR}/..
)

# Collect all source files (update patterns as your project grows)
file(GLOB_RECURSE NS_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# Create a reusable library containing project sources
add_library(network_simulator_lib STATIC ${NS_SOURCES})

# Make the source tree available to users of the library
target_include_directories(network_simulator_lib PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
