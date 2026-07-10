cmake_minimum_required(VERSION 3.10)
project(network-simulator LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put executables in bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(LIB_DIR lib)
set(CPP_COMMON_SRC_DIR ${LIB_DIR}/cpp-common)
set(SOURCE_DIR src)

# --- Library: cpp_common ---
file(GLOB CPP_COMMON_SOURCES
  ${CPP_COMMON_SRC_DIR}/*.cpp
  ${CPP_COMMON_SRC_DIR}/*.hpp
)

# Include CPP_COMMON_SOURCES when compiling cpp_common
# (cpp_common must have been added with add_executable() or add_library())
add_library(cpp-common ${CPP_COMMON_SOURCES})

target_include_directories(cpp-common PUBLIC
  ${LIB_DIR}
)

# Collect all source files (update patterns as your project grows)
file(GLOB_RECURSE NW_SIM_SOURCES CONFIGURE_DEPENDS
  "${SOURCE_DIR}/*.cpp"
  "${SOURCE_DIR}/*.hpp"
)

# Create a reusable library containing project sources
add_library(network-simulator-lib SHARED ${NW_SIM_SOURCES})

target_link_libraries(network-simulator-lib PUBLIC cpp-common)

# Make the source tree available to users of the library
target_include_directories(network-simulator-lib PUBLIC
  ${SOURCE_DIR}
  # ${LIB_DIR}
)

# tests

add_executable(test-notepad
  "${SOURCE_DIR}/../tests/test-notepad.cpp"
  # "${SOURCE_DIR}/L2_datalink/MAC/mac-specs.cpp"
  # "${SOURCE_DIR}/L4_transport/TCP/tcp-specs.cpp"
  # "${SOURCE_DIR}/L3_network/IP/ip-specs.cpp"
  # "${SOURCE_DIR}/L3_network/IP/ip-handler.cpp"
)

target_link_libraries(test-notepad PUBLIC network-simulator-lib)

target_include_directories(test-notepad PUBLIC
  ${SOURCE_DIR}
)
