#ifndef REALM_H
#define REALM_H

#include "Core/GameHandler.h"
#include "Backend/Backend.h"
#include "Managers/SceneManager.h"

namespace tartarus {

// safe as there can be ONLY 1 realm and will not be changed

struct Realm {
    bool Init();
    bool Exit();

    Shader& CompileShader(const char* vert, const char* frag);
    Scene& GetPrimaryScene();

    Backend _backend;
    SceneManager _scnManagers;
    GameHandler _gameHandler;
};

} // namespace tartarus


#endif