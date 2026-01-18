cmake_minimum_required(VERSION 3.10.0)
project(OpenGLTutorial VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
add_subdirectory(C:/Lib/glad  ${CMAKE_CURRENT_BINARY_DIR}/glad_library EXCLUDE_FROM_ALL)

add_executable(OpenGLTutorial 
    src/main.cpp 
    src/glsl_compiler.cpp
    src/mesh3D.cpp
    src/texture.cpp
    src/image_loader.cpp
    src/matrix.cpp
    src/Camera/camera.cpp
    src/Camera/fly_camera.cpp
    src/Camera/fps_camera.cpp
    src/Backend/Window/glfw_window.cpp
    src/Backend/backend.cpp
    src/API/gl_backend.cpp
    src/common/error_handler.cpp
    src/Core/game_handler.cpp
    src/Asset/asset.cpp
    src/Asset/asset_manager.cpp
    src/texture_manager.cpp
    src/mesh_manager.cpp
    src/renderer.cpp)

target_include_directories(OpenGLTutorial PUBLIC include)
target_include_directories(OpenGLTutorial PUBLIC third_party)

target_link_libraries(OpenGLTutorial PRIVATE glfw PUBLIC glad PRIVATE glm::glm)
