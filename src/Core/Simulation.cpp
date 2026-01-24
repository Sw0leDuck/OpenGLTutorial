#include "Core/Simulation.h"
#include "assert.h"

namespace tartarus {

bool Simulation::Init(void* gpu_ptr){
    _gpu = static_cast<Gpu*>(gpu_ptr);
    assert(_gpu->IsValid());

    return true;
}


void Simulation::BeginFrame(float delta){

}

void Simulation::UpdateFrame(float delta){
    // iterate the currentScene game objects
}

void Simulation::ExitFrame(float delta){

}

void Simulation::SetCurrentScene(Scene* scene){
    _currentScene = scene;
}

}