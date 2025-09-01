cmake_minimum_required(VERSION 3.10)
project(PolynomialSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
# 1. nlohmann/json: Assumed to be in an 'include' directory
# 2. GMP: Find the system-installed library

find_package(GMP REQUIRED)

# --- Executable Target ---
add_executable(solver main.cpp)

# --- Include Directories ---
target_include_directories(solver PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include # For nlohmann/json
    ${GMP_INCLUDE_DIRS}
)

# --- Link Libraries ---
target_link_libraries(solver PRIVATE ${GMP_LIBRARIES})
