#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
#include "Managers/WindowManager.h"
#include "Core/Simulation.h"

namespace tartarus {

    struct GameHandler {
        bool Init(void*, void*, void*);
        bool Exit();

        void GameLoop();

        Simulation _simulation;
        WindowManager* _windowManager;
    };

} // namespace gameHandler

#endif