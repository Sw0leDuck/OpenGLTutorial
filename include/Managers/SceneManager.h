#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Core/Scene.h"
#include <map>
// #include "Camera/fly_camera.h"

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
        std::map<SceneId, Scene> _scenes;
    };

} // namespace tartarus

#endif 