#ifndef BACKEND_H
#define BACKEND_H

#include "Managers/WindowManager.h"
#include "API/OpenGL/GLBackend.h"
#include <memory>
namespace tartarus {

    struct Backend {
        bool Init();
        bool Exit();
    
        void BeginFrame();
        void UpdateFrame();
        void EndFrame();
    
        // GLFW Window methods
        void* GetWindow();
        bool IsWindowClose();
    
        void TestLoadWorld();
        void UpdateTestWorld(float delta_time);

        WindowManager _windowManager;
        std::unique_ptr<OpenGL> _gpu;
    };

} // namespace backend

#endif