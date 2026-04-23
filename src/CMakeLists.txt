cmake_minimum_required(VERSION 3.10)
project(network-simulator LANGUAGES CXX)

project(network_simulator LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put executables in bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

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

# Optional lightweight example: if a top-level example source exists, build it and link the library
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/first_cpp.cpp")
  add_executable(example_runner "${CMAKE_CURRENT_SOURCE_DIR}/first_cpp.cpp")
  target_link_libraries(example_runner PRIVATE network_simulator_lib)
  target_include_directories(example_runner PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()
target_include_directories(quantxp_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# ------------------------------------------------------------
# Tests
# ------------------------------------------------------------

# ------------------------------------------------------------
# Optional: Enable warnings
# ------------------------------------------------------------

if(MSVC)
  target_compile_options(quantxp_lib PRIVATE /W4)
else()
  target_compile_options(quantxp_lib PRIVATE -O3 -Wall -Wextra -Wpedantic)
endif()
