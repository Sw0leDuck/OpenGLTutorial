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

    Scene& GetPrimaryScene();

    OpenGL* GetAPI() { return _backend._gpu.get(); }

    Backend _backend;
    std::unique_ptr<SceneManager> _scnManagers;
    GameHandler _gameHandler;
    std::unique_ptr<LoaderManager> _loader;
};

} // namespace tartarus


#endif