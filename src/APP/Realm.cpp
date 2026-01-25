#include "Common/Logging.h"
#include "App/Realm.h"
#include "Common/types.h"

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

    if(!_shaderManager.Init(_backend._gpu.get()))
        return false;

    _scnManagers.reserve(g_defaultSceneCount);
    return true;
}

bool Realm::Exit(){
    ExitLoggingBuffer();
    if(!_backend.Exit())
        return false;
    return true;
}
} // namespace tartarus