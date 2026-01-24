#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <vector>
#include "asset.h"
#include "Common/types.h"
#include "texture_manager.h"
#include "mesh_manager.h"


namespace tartarus {

    bool Init();
    bool Exit();
    void DrawMesh();
    void UpdateMesh(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection);

    compiler::Program* GetProgram(uint id);

    std::pair<uint, uint> Load2DTexture(const char* filePath, uint type);
    void LoadMesh();
    graphic::Mesh3D& LoadTestMesh();
    graphic::Mesh3D& LoadLightSourceTest();

    struct AssetManager {
        bool Init();
        bool Exit();

        std::vector<Asset> _assets;
        texture::manager::TextureManager _textureManager;
        mesh::manager::MeshManager _meshManager;
    };

} // namespace asset::manager

#endif