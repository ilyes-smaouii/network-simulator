cmake_minimum_required(VERSION 3.10)
project(network-simulator LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put executables in bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(LIBS_DIR lib)
set(CPP_COMMON_SRC_DIR ${LIBS_DIR}/cpp-common)
set(SOURCE_DIR src)

# --- Library: cpp_common ---
file(GLOB CPP_COMMON_SOURCES
  ${CPP_COMMON_SRC_DIR}/*.cpp
  ${CPP_COMMON_SRC_DIR}/*.hpp
)

# Include CPP_COMMON_SOURCES when compiling cpp_common
# (cpp_common must have been added with add_executable() or add_library())
add_library(cpp_common ${CPP_COMMON_SOURCES})

target_include_directories(cpp_common PUBLIC
  ${LIBS_DIR}
)

# Collect all source files (update patterns as your project grows)
file(GLOB_RECURSE NW_SIM_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# Create a reusable library containing project sources
add_library(network_simulator_lib STATIC ${NW_SIM_SOURCES})

# Make the source tree available to users of the library
target_include_directories(network_simulator_lib PUBLIC
  ${SOURCE_DIR}
)

# tests

add_executable(test-notepad
  "${SOURCE_DIR}/tests/test-notepad.cpp"
  "${SOURCE_DIR}/L4_transport/TCP/tcp_specs.cpp"
  "${SOURCE_DIR}/L3_network/IP/ip_specs.cpp"
)

target_link_libraries(test-notepad PRIVATE network_simulator_lib cpp_common)

target_include_directories(test-notepad PRIVATE
  ${LIBS_DIR}
  ${SOURCE_DIR}
)
