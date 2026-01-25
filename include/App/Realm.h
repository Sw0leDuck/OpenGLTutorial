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


    Backend _backend;
    std::vector<SceneManager> _scnManagers;
    GameHandler _gameHandler;
};

} // namespace tartarus


#endif