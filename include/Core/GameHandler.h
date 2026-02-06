#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
#include "Managers/WindowManager.h"
#include "Core/Simulation.h"

namespace tartarus {

    struct GameHandler {
        bool Init(void*, void*, void*);
        bool Exit();

        void PreFrame();
        void PostFrame();
        void GameLoop();

        void SetFPS(float value) { _limitFPS = 1.f/value; };

        Simulation _simulation;
        WindowManager* _windowManager;

        float _nowTime;
        float _lastTime;
        float _delta;
        float _limitFPS;
    };

} // namespace gameHandler

#endif