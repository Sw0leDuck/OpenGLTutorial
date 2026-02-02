#ifndef GL_BUFFER_MANAGER_H
#define GL_BUFFER_MANAGER_H
#include "API/OpenGL/GLBuffer.h"
#include "API/OpenGL/GLMeshBuffer.h"
#include "unordered_map"

namespace tartarus {

class GLBuffer;

struct GLBufferManager {
    bool Init();
    bool Exit();

    GLBuffer* GetGpuArrayBuffer(BufferName);
    GLBuffer* GetGpuIndexBuffer(BufferName);
    GLMeshBuffer* GetCreateMeshBuffer(BufferName);

    std::unordered_map<BufferName, GLBuffer> _vertexBuffers;
    std::unordered_map<BufferName, GLBuffer> _indexBuffers;
    std::unordered_map<BufferName, GLMeshBuffer> _meshBuffers;
};

}

#endif