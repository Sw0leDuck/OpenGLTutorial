#include "App/Realm.h"
#include "stdlib.h"

#include "Core/Objects/Static3D.h"
namespace tartarus{

int main(void) {
    // load object into heap, we dont need to deallocate because it should live 
    // for the whole run of the program
    tartarus::Realm* realm = (tartarus::Realm*)calloc(sizeof(tartarus::Realm), 1);

    if(!realm->Init())
        return -1;

    // lets load the primary scene with some static cube objects
    // auto scene = realm->GetPrimaryScene();

    // utilize the realm->_scnManagers variable to load the world

    realm->_gameHandler.GameLoop();

    // if everything went well, then call exit function
    return realm->Exit() ? 0 : -1;
}

}

int main(void){
    tartarus::main();
}