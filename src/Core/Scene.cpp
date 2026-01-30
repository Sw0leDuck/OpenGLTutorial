#include "Core/Scene.h"

namespace tartarus {

bool Scene::Init(){
    return true;
}

bool Scene::Exit(){
    return true;
}

void Scene::InsertObject(GameObject&& object){
    _objects.emplace_back(std::move(object));
}


void Scene::InsertCamera(Camera& camera){
    _camera = std::move(camera);
}

void Scene::InsertLight(Light& light){
    _lights.emplace_back(std::move(light));
}

void Scene::UpdateFrame(float delta){
    UpdateCamera(delta);
    UpdateLights(delta);
    UpdateObjects(delta);
}

void Scene::UpdateObjects(float delta){

}

void Scene::UpdateCamera(float delta){
    _camera.Update(delta);
}

void Scene::UpdateLights(float delta){

}




}