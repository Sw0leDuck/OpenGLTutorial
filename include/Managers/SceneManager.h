#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Core/Scene.h"
#include <unordered_map>

namespace tartarus {

    enum SceneId {
        kDefault = 0,
        kFinish = 1
    };

    struct SceneManager{
        bool Init();
        bool Exit();

        Scene& GetPrimaryScene();

        // FlyCamera _playerCamera;
        std::unordered_map<SceneId, Scene> _scenes;
    };

} // namespace tartarus

#endif 