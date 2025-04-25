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
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glfw3 REQUIRED)


# SOURCE/HEADER FILES
set(SOURCES
  src/main.c
)

# LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# EXECUTABLE
add_executable(orbgen ${SOURCES})

target_compile_options(orbgen PRIVATE
  -g          # Debug info
  -Wall       # Enable most common warnings
  -Wextra     # Enable extra warnings
  -Werror     # Treat all warnings as errors
)

# EXTERNAL LIB INCLUDE DIRECTORIES
target_include_directories(orbgen PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${GLEW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS}
  ${GLFW3_INCLUDE_DIRS}
)

# LINK LIBS
target_link_libraries(orbgen PRIVATE
  GLEW::GLEW
  ${OPENGL_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${GLFW3_LIBRARIES}
)
