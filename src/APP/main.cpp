#include "App/Realm.h"
#include "stdlib.h"

int main(void) {
    // load object into heap, we dont need to deallocate because it should live 
    // for the whole run of the program
    tartarus::Realm* realm = (tartarus::Realm*)malloc(sizeof(tartarus::Realm));

    if(!realm->Init())
        return -1;

    // utilize the realm->_scnManagers variable to load the world

    realm->_gameHandler.GameLoop();

    // if everything went well, then call exit function
    return realm->Exit() ? 0 : -1;
}