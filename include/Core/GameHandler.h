#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
#include "Core/Simulation.h"

namespace tartarus {

    enum gameState {
        kLoading = 0,
        kReady = 0,
        kExit
    };

    struct GameHandler {
        bool Init(void*);
        bool Exit();

        void GameLoop();

        Simulation _simulation;
        gameState _state;
    };

} // namespace gameHandler

#endif