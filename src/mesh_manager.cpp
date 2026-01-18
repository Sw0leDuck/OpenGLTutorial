#include "mesh_manager.h"

namespace mesh::manager {

bool MeshManager::Init(){
    return true;
}

bool MeshManager::Exit(){
    for(auto& iter : _meshes)
        iter.Exit();
    return true;    
}

void MeshManager::LoadMesh(){
    void(0);
}

graphic::Mesh3D& MeshManager::LoadTestMesh(){
    auto& iter = _meshes.emplace_back(graphic::Mesh3D());
    iter.Init();
    return iter;
}

graphic::Mesh3D& MeshManager::LoadLightSourceTest(){
    auto& iter = _lightSources.emplace_back(graphic::Mesh3D());
    iter.Init();
    return iter;
}

}