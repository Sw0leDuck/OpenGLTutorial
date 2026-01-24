#ifndef REALM_H
#define REALM_H

#include "Core/GameHandler.h"
#include "Backend/Backend.h"
#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"

namespace tartarus {

// safe as there can be ONLY 1 realm and will not be changed

struct Realm {
    bool Init();
    bool Exit();


    Backend _backend;
    ShaderManager _shaderManager;
    std::vector<SceneManager> _scnManagers;
    GameHandler _gameHandler;
};

} // namespace tartarus


#endif