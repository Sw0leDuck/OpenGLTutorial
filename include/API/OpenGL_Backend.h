#ifndef GL_BACKEND_H
#define GL_BACKEND_H
#include "Gpu_Backend.h"


namespace tartarus {

struct OpenGL : Gpu {
    bool Init() override;
    bool Exit() override;
    bool IsValid() override { return true; }

    void ClearScreen() override;
    void UpdateViewPort(uint, uint) override;
    
};

} // namespace tartarus::gl

#endif