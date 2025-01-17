cmake_minimum_required(VERSION 3.10)
project(Uno-C)

# Ensure CMake's FetchContent module is available
include(FetchContent)

# Declare Raylib as a fetchable content
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master  # You can specify a specific tag or branch
)

# Make Raylib available for building
FetchContent_MakeAvailable(raylib)

# Set the C++ standard (if needed)
set(CMAKE_CXX_STANDARD 11)

# Find all .c files in the 'src' directory (adjust this to match your structure)
file(GLOB SOURCES "src/*.c" "src/**/*.c")

# Add the executable
add_executable(Uno-C ${SOURCES})

# Link Raylib to your project
target_link_libraries(Uno-C raylib)

# Copy the assets directory into the build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
