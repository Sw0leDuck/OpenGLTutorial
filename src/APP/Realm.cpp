#include "App/Realm.h"
#include "Common/types.h"

namespace tartarus {

static constexpr uint g_defaultSceneCount = 4;

bool Realm::Init(){

    if(!_backend.Init())
        return false;
    
    if(!_gameHandler.Init(static_cast<void*>(_backend._gpu.get())))
        return false;

    _scnManagers.reserve(g_defaultSceneCount);
    return true;
}

bool Realm::Exit(){
    if(!_backend.Exit())
        return false;
    return true;
}
} // namespace tartarus