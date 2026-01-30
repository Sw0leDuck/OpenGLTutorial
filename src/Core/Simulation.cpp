#include "Core/Simulation.h"
#include "assert.h"

namespace tartarus {

bool Simulation::Init(void* gpu_ptr, void* moveHandler_pt){
    _gpu = static_cast<OpenGL*>(gpu_ptr);
    assert(_gpu->IsValid());

    _movementHandler.Init(moveHandler_pt);

    return true;
}

bool Simulation::Run(){
    return !_movementHandler._stopSimulation;
}


// Update MovementState
void Simulation::BeginFrame(float delta){
    _movementHandler.BeginFrame(delta);
}

void Simulation::UpdateFrame(float delta){
    // iterate the currentScene game objects
    _currentScene->UpdateFrame(delta);
}

void Simulation::ExitFrame(float delta){
    _movementHandler._movementState = CAMERA_MOVEMENT::kNothing;
}

void Simulation::SetCurrentScene(Scene* scene){
    _currentScene = scene;
}

}