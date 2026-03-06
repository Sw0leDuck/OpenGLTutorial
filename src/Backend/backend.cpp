#include "Backend/Backend.h"
#include "API/OpenGL/GLBackend.h"


#define OPEN_GL_CONTEXT

namespace tartarus {

float last_frame = 0;
float current_frame = 0;
float delta_time = 0;

bool Backend::Init(){
    if(!_windowManager.Init("Tartarus")){
        return false;
    }

    _gpu = std::make_unique<OpenGL>();
    if(!_gpu->Init()){
        return false;
    }

    return true;
}

bool Backend::Exit(){
    _windowManager.Exit();
    _gpu->Exit();
    _gpu.reset();
    return true;
}

void Backend::LoadEditor(){
    _windowManager.StartEditor();
}

} // namespace backend