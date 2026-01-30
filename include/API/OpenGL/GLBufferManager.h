#ifndef GL_BUFFER_MANAGER_H
#define GL_BUFFER_MANAGER_H
#include "API/OpenGL/GLBuffer.h"
#include "API/OpenGL/GLMeshBuffer.h"
#include "vector"

namespace tartarus {

class GLBuffer;

struct GLBufferManager {
    bool Init();
    bool Exit();

    bool AllocateGLBuffers();
    bool AllocateGLVertexArrays();

    GLBuffer* GetNextBuffer(GLBuffer::BufferType type);
    GLMeshBuffer* GetNextMeshBuffer();

    std::vector<GLBuffer> _buffers;
    std::vector<GLMeshBuffer> _meshBuffers;
};

}

#endif