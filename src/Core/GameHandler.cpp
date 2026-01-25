#include "Common/Logging.h"
#include "Core/GameHandler.h"

namespace tartarus {

bool GameHandler::Init(void* gpu_ptr, void* moveHandler, void* windowManager_ptr){

    if(!_simulation.Init(gpu_ptr, moveHandler))
        return false;

    _windowManager = static_cast<WindowManager*>(windowManager_ptr);

    return true;
}

bool GameHandler::Exit(){
    return true;
}

void GameHandler::GameLoop(){
    float delta = 0;

    while(_simulation.Run()){
        if(_windowManager->needResizeViewport)
            _simulation._gpu->UpdateViewPort(
                _windowManager->_width, 
                _windowManager->_height);

        // handle input
        _simulation.BeginFrame(delta);
        
        // update camera
        // simulate
        _simulation.UpdateFrame(delta);
        
        // clean resources or somethings else
        _simulation.ExitFrame(delta);

        _windowManager->_mainWindow->EndFrameWork();
    }
}

} // gameHandler