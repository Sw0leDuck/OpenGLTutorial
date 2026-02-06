#include "Core/Scene.h"
#include "Core/Objects/RenderObject.h"

namespace tartarus {

bool Scene::Init(){
    return true;
}

bool Scene::Exit(){
    return true;
}

Camera* Scene::GenerateCamera(){
    _camera = std::make_unique<Camera>();
    return _camera->AsType<Camera>();
}

void Scene::UpdateFrame(float delta){
    UpdateCamera(delta);
    SimulateLights(delta);
    SimulateObjects(delta);
}

void Scene::SimulateObjects(float delta){
    auto viewMatrix = _camera->AsType<Camera>()->GetView();
    auto projMatrix = _camera->AsType<Camera>()->GetProjection();


    // Update the Shaders with the new view/proj matrices
    for(auto& iter : _objects){
        iter->_viewMatrix = viewMatrix;
        iter->_projectionMatrix = projMatrix;
        
        iter->Update(delta);
        // draw because the values are still in the cpu cache ???
        iter->Draw(delta);
    }
}

void Scene::UpdateCamera(float delta){
    _camera->Update(delta);
    for(auto& iter : _objects){
        auto x = iter->AsType<RenderObject>();
        // dirty way
        if(x){
            x->_cameraPosition.x = _camera->AsType<Camera>()->_position.x;
            x->_cameraPosition.y = _camera->AsType<Camera>()->_position.y;
            x->_cameraPosition.z = _camera->AsType<Camera>()->_position.z;
        }
    }
}

void Scene::SimulateLights(float delta){

}




}