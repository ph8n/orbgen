# VERSION
cmake_minimum_required(VERSION 3.10)

# PROJECT
project(orbgen C)

# C STANDARD
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

# COMPILER
set(CMAKE_C_COMPILER clang)

# EXTERNAL LIBS
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

# SOURCE/HEADER FILES
set(SOURCES
  src/main.c
)

# LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# EXECUTABLE
add_executable(orbgen ${SOURCES})

# COMPILER FLAGS
target_compile_options(orbgen PRIVATE
  -Wall       # Enable most common warnings
  -Wextra     # Enable extra warnings
  -Werror     # Treat all warnings as errors
  -fsanitize=address # Enable address sanitizer
)

# EXTERNAL LIB INCLUDE DIRECTORIES
target_include_directories(orbgen PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Vulkan_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS}
)

# LINK LIBS
target_link_libraries(orbgen PRIVATE
  ${Vulkan_LIBRARIES}
  ${SDL2_LIBRARIES}
)
