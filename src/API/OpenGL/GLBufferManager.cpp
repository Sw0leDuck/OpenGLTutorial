#include "glad/glad.h"
#include "API/OpenGL/GLBufferManager.h"
#include "API/OpenGL/GLBuffer.h"
#include "Common/Types.h"

namespace tartarus {

bool GLBufferManager::Init(){
    // hardcode value that the program will use at most 20 different buffers
    _buffers.reserve(20);
    _meshBuffers.reserve(20);
    AllocateGLBuffers();
    AllocateGLVertexArrays();
    return true;
}

bool GLBufferManager::Exit(){
    std::vector<uint> bufferIds;
    bufferIds.reserve(_buffers.size());
    for(auto& iter : _buffers){
        bufferIds.emplace_back(iter._bufferId);
        iter.Exit();
    }

    if(bufferIds.size())
        glDeleteBuffers(bufferIds.size(), bufferIds.data());

    bufferIds.clear();

    bufferIds.reserve(_meshBuffers.size());
    for(auto& iter : _meshBuffers){
        bufferIds.emplace_back(iter._bufferId);
        iter.Exit();
    }

    if(bufferIds.size())
        glDeleteVertexArrays(bufferIds.size(), bufferIds.data());
    
    return true;
}

// TODO: CRITICAL : The following will trigger UAF bugs across the program
// Solution, implement a costum std::vector container that is strong against
// multiple reallocation, the same must be done for the ShaderManager
GLBuffer* GLBufferManager::GetNextBuffer(GLBuffer::BufferType type){
    for(auto& iter : _buffers){
        if((iter._type == GLBuffer::BufferType::kInvalid) || (iter._used == false)){
            iter._type = type;
            iter._used = true;
            return &(iter);
        }
    }
    AllocateGLBuffers();

    // immediately take a GLBuffer that is not used 100%
    _buffers.back()._type = type;
    _buffers.back()._used = true;
    return &(_buffers.back());
}

GLMeshBuffer* GLBufferManager::GetNextMeshBuffer(){
    for(auto& iter : _meshBuffers){
        if((!iter._valid) || (!iter._used)){
            iter._used = true;
            return &(iter);
        }
    }
    AllocateGLBuffers();

    // immediately take a GLBuffer that is not used 100%
    _meshBuffers.back()._used = true;
    return &(_meshBuffers.back());
}

bool GLBufferManager::AllocateGLBuffers(){

    {
        uint tmpBufferId[20];

        glGenBuffers(20, tmpBufferId);

        for(uint index=0; index < 20; index++){
            auto& iter = _buffers.emplace_back(GLBuffer{});
            iter.Init(tmpBufferId[index],
                GLBuffer::BufferType::kInvalid); 
        }
    }

    return true;
}

bool GLBufferManager::AllocateGLVertexArrays(){
    {
        uint tmpBufferId[20];

        glGenVertexArrays(20, tmpBufferId);

        for(uint index=0; index < 20; index++){
            auto& iter = _meshBuffers.emplace_back(GLMeshBuffer{});
            iter.Init(tmpBufferId[index], this); 
        }
    }

    return true;
}

}