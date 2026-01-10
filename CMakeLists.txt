cmake_minimum_required(VERSION 3.10.0)
project(OpenGLTutorial VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
add_subdirectory(C:/Lib/glad  ${CMAKE_CURRENT_BINARY_DIR}/glad_library EXCLUDE_FROM_ALL)

add_executable(OpenGLTutorial 
    src/main.cpp 
    src/glsl_compiler.cpp
    src/mesh.cpp)

target_include_directories(OpenGLTutorial PUBLIC include)

target_link_libraries(OpenGLTutorial PRIVATE glfw PUBLIC glad)
