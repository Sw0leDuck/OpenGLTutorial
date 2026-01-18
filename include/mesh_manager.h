#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H
#include <vector>
#include "mesh3D.h"

namespace mesh::manager {

    struct MeshManager {
        bool Init();
        bool Exit();

        void LoadMesh();
        graphic::Mesh3D& LoadTestMesh();
        graphic::Mesh3D& LoadLightSourceTest();

        std::vector<graphic::Mesh3D> _meshes;
        std::vector<graphic::Mesh3D> _lightSources;
    };
} // mesh::manager

#endif