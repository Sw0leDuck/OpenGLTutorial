#include "Common/Logging.h"
#include "App/Realm.h"
#include "Common/Types.h"

namespace tartarus {

static constexpr uint g_defaultSceneCount = 4;

bool Realm::Init(){
    InitLoggingBuffer();

    if(!_backend.Init())
        return false;
    
    // probably make it a little prettier ?
    if(!_gameHandler.Init(
            static_cast<void*>(_backend._gpu.get()), 
            static_cast<void*>(&_backend._windowManager._inputManager),
            static_cast<void*>(&_backend._windowManager)))
        return false;

    if(!_scnManagers.Init())
        return false;

    return true;
}

bool Realm::Exit(){
    ExitLoggingBuffer();
    if(!_backend.Exit())
        return false;
    return true;
}

Shader& Realm::CompileShader(const char* vert, const char* frag){
    return _backend._gpu->CompileShader(vert, frag);
}

Scene& Realm::GetPrimaryScene(){
    return _scnManagers.GetPrimaryScene();
}
} // namespace tartarus