cmake_minimum_required(VERSION 3.10.0)
project(OpenGLTutorial VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
add_subdirectory(C:/Lib/glad  ${CMAKE_CURRENT_BINARY_DIR}/glad_library EXCLUDE_FROM_ALL)

add_executable(OpenGLTutorial 
    src/API/OpenGL_Backend.cpp
    src/App/main.cpp
    src/App/Realm.cpp
    # src/Asset/asset.cpp
    # src/Asset/asset_manager.cpp
    src/Backend/Backend.cpp
    src/Backend/Window/PrimaryWindow.cpp
    # src/Camera/camera.cpp
    # src/Camera/fly_camera.cpp
    # src/Camera/fps_camera.cpp
    src/Common/Logging.cpp
    src/Core/GameHandler.cpp
    src/Core/MovementHandler.cpp
    src/Core/Simulation.cpp
    src/Managers/InputManager.cpp
    src/Managers/SceneManager.cpp
    src/Managers/ShaderManager.cpp
    src/Managers/WindowManager.cpp
    # src/glsl_compiler.cpp
    # src/image_loader.cpp
    # src/matrix.cpp
    # src/mesh3D.cpp
    # src/mesh_manager.cpp
    # src/renderer.cpp
    # src/texture.cpp
    # src/texture_manager.cpp
    )

target_include_directories(OpenGLTutorial PUBLIC include)
target_include_directories(OpenGLTutorial PUBLIC third_party)

target_link_libraries(OpenGLTutorial PRIVATE glfw PUBLIC glad PRIVATE glm::glm)
