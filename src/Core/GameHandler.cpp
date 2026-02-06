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
    _nowTime = _lastTime = glfwGetTime();

    _simulation._movementHandler._camera = 
        _simulation.GetMainCamera();

    while(_simulation.Run()){
        _nowTime = glfwGetTime();
        _delta = _nowTime - _lastTime;
        _lastTime = _nowTime;

        PreFrame();
        _simulation.BeginFrame(_delta);

        // update camera
        // simulate
        _simulation.UpdateFrame(_delta);
        
        // clean resources or somethings else
        _simulation.ExitFrame(_delta);
        PostFrame();
    }
}

void GameHandler::PreFrame(){
    if(_windowManager->needResizeViewport){
        _simulation._gpu->UpdateViewPort(
            _windowManager->_width, 
            _windowManager->_height);
        _simulation.UpdateCameraAspect(_windowManager->_width, _windowManager->_height);
    }
    
    _simulation._gpu->ClearScreen();
}

void GameHandler::PostFrame(){
    _windowManager->_mainWindow->EndFrameWork();
}

} // gameHandler