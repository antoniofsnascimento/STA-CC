cmake_minimum_required(VERSION 3.20)

project(STA_CC
    VERSION 0.1.0
    DESCRIPTION "High-performance C++20 Static Timing Analysis Engine and Circuit Compiler"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Exportar base de dados para o clangd no VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable ASan and UBSan" ON)

# --- 1. Core Engine Static Library (stacc_core) ---
add_library(stacc_core STATIC
    src/circuit.cpp
    src/netlist_parser.cpp
    src/timing_engine.cpp
)

target_include_directories(stacc_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(stacc_core PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wnon-virtual-dtor -Werror
)

if(ENABLE_SANITIZERS)
    target_compile_options(stacc_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(stacc_core PUBLIC -fsanitize=address,undefined)
endif()

# --- 2. CLI Executable Target (stacc_cli) ---
add_executable(stacc_cli main.cpp)
target_link_libraries(stacc_cli PRIVATE stacc_core)

# --- 3. Unit Test Suite Target (test_graph) ---
enable_testing()
add_executable(test_graph tests/test_graph.cpp)
target_link_libraries(test_graph PRIVATE stacc_core)
add_test(NAME CoreGraphTests COMMAND test_graph)
