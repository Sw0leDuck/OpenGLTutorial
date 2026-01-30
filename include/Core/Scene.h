#ifndef SCENE_H
#define SCENE_H
#include "Objects/GameObject.h"
#include "Camera/Camera.h"
#include "Objects/Light.h"

namespace tartarus {

    struct Scene {
        bool Init();
        bool Exit();

        void InsertObject(GameObject&&);
        void InsertCamera(Camera&);
        void InsertLight(Light&);

        void UpdateFrame(float);
        void UpdateObjects(float);
        void UpdateCamera(float);
        void UpdateLights(float);


        std::vector<GameObject> _objects;
        GameObject _camera;
        std::vector<GameObject> _lights;
    };

} // namespace tartarus

#endif