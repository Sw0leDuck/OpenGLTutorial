#include "API/OpenGL/GLBufferManager.h"
#include "Common/ConstVertices.h"
#include "Common/Enums.h"

namespace tartarus {

bool GLBufferManager::Init(){
    // Bypass uaf bugs for now, should create a personal stl that does not
    // deallocate memory
    _vertexBuffers.reserve(10);
    _indexBuffers.reserve(10);
    _meshBuffers.reserve(10);
    _instancedBuffers.reserve(10);

    // lets allocate some important buffers
    GetCreateMeshBuffer(BufferName::kCubeTextureNorm)->LoadData(
        {(void*)vertices::CubeNormTexture, sizeof(vertices::CubeNormTexture)},
        VertexAttributeFlag::kPos | 
        VertexAttributeFlag::kNormalVector | 
        VertexAttributeFlag::kTextCoords);

    GetCreateMeshBuffer(BufferName::kCubeTexture)->LoadData(
        {(void*)vertices::CubeTexture, sizeof(vertices::CubeTexture)},
        VertexAttributeFlag::kPos | 
        VertexAttributeFlag::kTextCoords);

    GetCreateMeshBuffer(BufferName::kRectangleTextureNormInstanced)->LoadData(
        {(void*)vertices::RectangleTextureNorm, sizeof(vertices::RectangleTextureNorm),
        nullptr, 0, false, 8},
        VertexAttributeFlag::kPos | 
        VertexAttributeFlag::kNormalVector |
        VertexAttributeFlag::kTextCoords |
        VertexAttributeFlag::kInstanceValues); 

    return true;
}

bool GLBufferManager::Exit(){
    for(auto& iter : _vertexBuffers){
        iter.second.Exit();
    }
    _vertexBuffers.clear();

    for(auto& iter : _indexBuffers){
        iter.second.Exit();
    }
    _indexBuffers.clear();

    for(auto& iter : _instancedBuffers){
        iter.second.Exit();
    }
    _instancedBuffers.clear();

    for(auto& iter : _meshBuffers){
        iter.second.Exit();
    }
    _meshBuffers.clear();
    
    return true;
}

// TODO: CRITICAL : The following will trigger UAF bugs across the program
// Solution, implement a costum std::vector container that is strong against
// multiple reallocation, the same must be done for the ShaderManager
// Solution: change vector -> unordered_map ?? done ??
GLBuffer* GLBufferManager::GetGpuArrayBuffer(BufferName id){
    auto iter = _vertexBuffers.find(id);
    if(iter == _vertexBuffers.end()){
        auto pair = _vertexBuffers.emplace(id, GLBuffer());
        pair.first->second.Init(GLBuffer::BufferType::kArrayBuffer);
        return &pair.first->second;
    }
    return &iter->second;
}

GLBuffer* GLBufferManager::GetGpuIndexBuffer(BufferName id){
    auto iter = _indexBuffers.find(id);
    if(iter == _indexBuffers.end()){
        auto pair = _indexBuffers.emplace(id, GLBuffer());
        pair.first->second.Init(GLBuffer::BufferType::kIndexBuffer);
        return &pair.first->second;
    }
    return &iter->second;
}


GLMeshBuffer* GLBufferManager::GetCreateMeshBuffer(BufferName id){
    auto iter = _meshBuffers.find(id);
    if(iter == _meshBuffers.end()){
        auto pair = _meshBuffers.emplace(id, GLMeshBuffer());
        pair.first->second.Init(id, this);
        return &pair.first->second;
    }
    return &iter->second;
}

GLBuffer* GLBufferManager::GetCreateInstanceBuffer(int count){
    auto iter = _instancedBuffers.find(count);
    if(iter != _instancedBuffers.end())
        return &iter->second;

    auto elem = &_instancedBuffers.emplace(count, GLBuffer()).first->second;
    elem->Init(GLBuffer::BufferType::kArrayBuffer);
    return elem;
}

}