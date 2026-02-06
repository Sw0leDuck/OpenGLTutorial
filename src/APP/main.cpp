#include "App/Realm.h"
#include "stdlib.h"
#include "Core/Objects/Static3D.h"
#include "Camera/Camera.h"

namespace tartarus{

int main(void) {
    // load object into heap, we dont need to deallocate because it should live 
    // for the whole run of the program
    tartarus::Realm* realm = (tartarus::Realm*)calloc(
        sizeof(tartarus::Realm), 1);

    if(!realm->Init())
        return -1;
    
    auto gpu = realm->GetAPI();
    realm->_gameHandler.SetFPS(60.f);

    // lets load the primary scene with some static cube objects
    auto& scene = realm->GetPrimaryScene();

    auto* camera = scene.GenerateCamera();
    camera->Init({0,0,3});
    camera->UpdateScreenAspect(realm->_backend._windowManager._width,
        realm->_backend._windowManager._height);

    // utilize the realm->_scnManagers variable to load the world
    {
        Static3D* object = scene.GenerateObject<Static3D>(); 
        object->SetWorldPosition(CreateWorldPositionMatrix(0,-0.5f, 0));
        object->ScaleWorldPosition({10, 0.1, 10});

        object->SetMeshBuffer(
            gpu->GetMeshBuffer(BufferName::kRectangleTextureNorm));

        object->SetShader(gpu->GetShader(ShaderName::kDefault));

        object->InsertTexture(gpu->GetTexture(AssetName::kFloor_0));
    }

    {
        Static3D* object = scene.GenerateObject<Static3D>(); 
        object->SetWorldPosition(CreateWorldPositionMatrix(0, 0, 0));
        object->ScaleWorldPosition({0.3, 0.3, 0.3});
        object->TranslateWorldPosition({0,-1.f,0});

        object->SetMeshBuffer(
            gpu->GetMeshBuffer(BufferName::kRectangleTextureNorm));

        object->SetShader(gpu->GetShader(ShaderName::kDefault));

        object->InsertTexture(gpu->GetTexture(AssetName::kBarrel_0));
    }

    {
        Static3D* object = scene.GenerateObject<Static3D>(); 
        object->SetWorldPosition(CreateWorldPositionMatrix(0, 0, 0));
        object->ScaleWorldPosition({0.3, 0.3, 0.3});
        object->RotateWorldPosition(30.f, {0,1,0});

        object->SetMeshBuffer(
            gpu->GetMeshBuffer(BufferName::kRectangleTextureNorm));

        object->SetShader(gpu->GetShader(ShaderName::kDefault));

        object->InsertTexture(gpu->GetTexture(AssetName::kBarrel_0));
    }

    realm->_gameHandler._simulation.SetCurrentScene(&scene);

    realm->_gameHandler.GameLoop();

    // if everything went well, then call exit function
    return realm->Exit() ? 0 : -1;
}

}

int main(void){
    tartarus::main();
}