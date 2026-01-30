#include "Managers/SceneManager.h"

namespace tartarus {

bool SceneManager::Init(){
    
    return true;
}

bool SceneManager::Exit(){
    return true;
}

Scene& SceneManager::GetPrimaryScene(){
    return _scenes[SceneId::kDefault];
}

} // namespace tartarus