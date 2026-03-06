#ifndef BACKEND_H
#define BACKEND_H

#include "Managers/WindowManager.h"
#include "API/OpenGL/GLBackend.h"
#include <memory>

namespace tartarus {

    struct Backend {
        bool Init();
        bool Exit();
    
        // GLFW Window methods
        void* GetWindow();
        bool IsWindowClose();

        void LoadEditor();

        WindowManager _windowManager;
        std::unique_ptr<OpenGL> _gpu;
    };

} // namespace backend

#endif