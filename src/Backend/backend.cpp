#include "Backend/Backend.h"
#include "API/OpenGL_Backend.h"
#include "Backend/Window/PrimaryWindow.h"
#include "assert.h"

#define OPEN_GL_CONTEXT

namespace tartarus {

float last_frame = 0;
float current_frame = 0;
float delta_time = 0;

bool Backend::Init(){
    // this is passed so that the _windowManager can callback to this function
    if(!_windowManager.Init("Tartarus")){
        return false;
    }

#ifdef OPEN_GL_CONTEXT
    _gpu = std::make_unique<OpenGL>();
#elif VULKAN_CONTEXT
    void(0); // void for now
#endif
    assert(_gpu != nullptr);
    if(!_gpu->Init()){
        return false;
    }

    return true;
}

bool Backend::Exit(){
    glfw::ExitGLFW();
    _gpu->Exit();
    _gpu.reset();
    // asset::manager::Exit();
    return true;
}

void Backend::BeginFrame(){
    current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    glfw::BeginFrame(delta_time);
}

void Backend::UpdateFrame(){
    _gpu->ClearScreen();
    UpdateTestWorld(delta_time);
    // renderer::UpdateFrame();
}

void Backend::EndFrame(){
    /* Swap front and back buffers */
    /* Poll for and process events */
    glfw::EndFrame();
}

void* Backend::GetWindow(){
    return glfw::GetWindow();
}

bool Backend::IsWindowClose(){
    return glfw::IsWindowClose();
}

// void Backend::TestLoadWorld(){
//     const glm::vec3 lightColor(1.0, 1.0, 1.f);
//     // loads only one cube into the world
//     auto& meshCube = asset::manager::LoadTestMesh();
//     meshCube._program = asset::manager::GetProgram((uint)ProgramType::kDefault);
//     meshCube._program->UseProgram();
//     meshCube._program->SetFloat3("viewPos", gameHandler::GetCameraPosition());
//     meshCube._textures2DId.emplace_back(
//         asset::manager::Load2DTexture("../../assets/container2.png", GL_RGBA));
//     meshCube._textures2DId.emplace_back(
//         asset::manager::Load2DTexture("../../assets/container2-specular.png", GL_RGBA));
//     // meshCube._textures2DId.emplace_back(
//     //     asset::manager::Load2DTexture("../../../assets/container2-emission-map.png", GL_RGBA));
//     meshCube.LoadCube(uint(graphic::VertexAttribute::kAll));
//     for(uint i=0; i<4; i++){
//         auto& meshLight = asset::manager::LoadLightSourceTest();
//         meshLight._program = asset::manager::GetProgram((uint)ProgramType::kLightSource);
//         meshLight.LoadCube(uint(graphic::VertexAttribute::kPos));
//         meshLight._objectColor = lightColor;
//     }
// }

// void Backend::UpdateTestWorld(float delta_time){
//     auto viewMatrix = gameHandler::getViewMatrix();
//     auto projectionMatrix = gameHandler::getProjectionMatrix();
//     auto cameraPosition = gameHandler::GetCameraPosition();
//     auto cameraDirection = gameHandler::GetCameraDirection();
//     asset::manager::UpdateMesh(viewMatrix, projectionMatrix, cameraPosition, cameraDirection);
// }

} // namespace backend