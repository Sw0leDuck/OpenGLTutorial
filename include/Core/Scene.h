#ifndef SCENE_H
#define SCENE_H
#include "Objects/GameObject.h"
#include "Camera/Camera.h"
// #include "Objects/Light.h"
#include <memory>

namespace tartarus {

struct Static3D;

struct Scene {
    bool Init();
    bool Exit();

    template<typename T>
    T* GenerateObject(){
        _objects.emplace_back(std::move(std::make_unique<T>()));
        _objects.back()->Init();
        return _objects.back()->AsType<T>();
    }
    Camera* GenerateCamera();
    
    GameObject* GenerateMainLight();

    template<typename T>
    T* GenerateLight(){
        _lights.emplace_back(std::move(std::make_unique<T>()));
        _lights.back()->Init();
        return _lights.back()->AsType<T>();
    }
    
    void UpdateFrame(float);
    void SimulateObjects(float);
    void UpdateCamera(float);
    void SimulateLights(float);
    
    std::vector<std::unique_ptr<GameObject>> _objects;
    std::unique_ptr<GameObject> _mainLight;
    std::unique_ptr<GameObject> _camera;
    std::vector<std::unique_ptr<GameObject>> _lights;
};

} // namespace tartarus

#endif