#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>
#include "Core/Scene.h"
#include "Camera/fly_camera.h"

namespace tartarus {

    struct SceneManager{
        FlyCamera _playerCamera;
        std::vector<Scene> _scenes;
    };

} // namespace tartarus

#endif 