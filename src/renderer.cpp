#include "renderer.h"
#include "Asset/asset_manager.h"

namespace renderer{

Renderer g_renderer;

bool Init(){
    return g_renderer.Init();
}

void UpdateFrame(){
    // take all the asset manager meshes and draw them?
    asset::manager::DrawMesh();
}

bool Renderer::Init(){
    return true;
}

}