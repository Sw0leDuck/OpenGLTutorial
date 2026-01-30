#ifndef GL_MESH_BUFFER_H
#define GL_MESH_BUFFER_H
/**
 * Find a better name
 */
#include "API/OpenGL/GLBuffer.h"
#include "Common/Types.h"
#include "vector"

namespace tartarus {

class GLBufferManager;

enum VertexAttributeFlag {
    kPos = (1<<0), // 3
    kTextCoords = (1<<1), // 2
    kColor = (1<<2), // 3
    kNormalVector = (1<<3), // 3
    kCount = 4,
    kAll = (kColor<<1)-1
};

// Implemented using a VertexArray object
struct GLMeshBuffer {
    enum DrawType {
        kArray = 0,
        kElement = 1
    };

    bool Init(uint, GLBufferManager*);
    bool Exit();

    void BindBuffer();
    void UnbindBuffer();
    void Draw();
    void LoadData(GLBuffer::BufferData data, uint flags);

    uint _bufferId;
    VertexAttributeFlag _flags;
    uint _triangleCount;
    DrawType _drawType;
    bool _valid = false;
    bool _used = false; 
    GLBufferManager* _bufferManager;
    std::vector<GLBuffer*> _buffers;
};

}

#endif