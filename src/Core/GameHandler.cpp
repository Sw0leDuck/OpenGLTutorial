#include "Core/GameHandler.h"

namespace tartarus {

bool GameHandler::Init(void* gpu_ptr){
    _state = gameState::kLoading;

    if(!_simulation.Init(gpu_ptr))
        return false;

    _state = gameState::kReady;
    return true;
}

bool GameHandler::Exit(){
    return true;
}

void GameHandler::GameLoop(){
    float delta = 0;

    while(_state != gameState::kExit){
        // handle input
        _simulation.BeginFrame(delta);
        
        // update camera
        // simulate
        _simulation.UpdateFrame(delta);
        
        // swap buffers
        _simulation.ExitFrame(delta);
    }
}

} // gameHandler