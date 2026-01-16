#include "Backend/backend.h"
#include "API/gl_backend.h"
#include "Backend/Window/glfw_window.h"
#include "Core/game_handler.h"
#include "common/error_handler.h"

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

        if(!gameHandler::Init()){
            errorHandler::PrintError();
            return false;
        }

        return true;
    }

    bool Exit(){
        glfw::ExitGLFW();

        return true;
    }

    void BeginFrame(){
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
    }

    void UpdateFrame(){
        gl::ClearScreen();
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
} // namespace backend