#include "Backend/backend.h"
#include "API/gl_backend.h"
#include "Backend/Window/glfw_window.h"
#include "Core/game_handler.h"
#include "common/error_handler.h"
#include "Asset/asset_manager.h"
#include "renderer.h"

namespace backend {

float last_frame = 0;
float current_frame = 0;
float delta_time = 0;

    bool Init(){
        if(!glfw::InitializeGLFW()){
            errorHandler::PrintError();
            return false;
        }

        if(!gl::InitializeGL()){
            errorHandler::PrintError();
            return false;
        }

        if(!asset::manager::Init()){
            errorHandler::PrintError();
            return false;
        }

        if(!gameHandler::Init()){
            errorHandler::PrintError();
            return false;
        }

        if(!glfw::PostInitGameHandler()){
            errorHandler::PrintError();
            return false;
        }

        return true;
    }

    bool Exit(){
        glfw::ExitGLFW();
        asset::manager::Exit();

        return true;
    }

    void BeginFrame(){
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        backend::glfw::BeginFrame(delta_time);
    }

    void UpdateFrame(){
        gl::ClearScreen();
        UpdateTestWorld(delta_time);
        renderer::UpdateFrame();
    }

    void EndFrame(){
        /* Swap front and back buffers */
        /* Poll for and process events */
        glfw::EndFrame();
    }

    void* GetWindow(){
        return glfw::GetWindow();
    }

    bool IsWindowClose(){
        return glfw::IsWindowClose();
    }

    void TestLoadWorld(){
        const glm::vec3 lightColor(1.0, 1.0, 1.f);

        // loads only one cube into the world
        auto& meshCube = asset::manager::LoadTestMesh();
        meshCube._program = asset::manager::GetProgram((uint)ProgramType::kDefault);
        meshCube._program->UseProgram();
        meshCube._program->SetFloat3("viewPos", gameHandler::GetCameraPosition());
        meshCube._textures2DId.emplace_back(
            asset::manager::Load2DTexture("../../../assets/container2.png", GL_RGBA));
        meshCube._textures2DId.emplace_back(
            asset::manager::Load2DTexture("../../../assets/container2-specular.png", GL_RGBA));
        // meshCube._textures2DId.emplace_back(
        //     asset::manager::Load2DTexture("../../../assets/container2-emission-map.png", GL_RGBA));
        meshCube.LoadCube(uint(graphic::VertexAttribute::kAll));

        auto& meshLight = asset::manager::LoadLightSourceTest();
        meshLight._program = asset::manager::GetProgram((uint)ProgramType::kLightSource);
        meshLight.LoadCube(uint(graphic::VertexAttribute::kPos));
        meshLight._program->UseProgram();
        meshLight._program->SetFloat3("lightColor",  lightColor.r, lightColor.g, lightColor.b);
    }

    void UpdateTestWorld(float delta_time){
        auto viewMatrix = gameHandler::getViewMatrix();
        auto projectionMatrix = gameHandler::getProjectionMatrix();
        auto cameraPosition = gameHandler::GetCameraPosition();
        asset::manager::UpdateMesh(viewMatrix, projectionMatrix, cameraPosition);
    }
} // namespace backend