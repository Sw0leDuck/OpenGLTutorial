#ifndef GL_MESH_BUFFER_H
#define GL_MESH_BUFFER_H
/**
 * Find a better name
 */
#include "API/OpenGL/GLBuffer.h"
#include "Common/Types.h"
#include "Common/Enums.h"
#include "vector"

namespace tartarus {

class GLBufferManager;

enum VertexAttributeFlag {
    kPos = (1<<0), // 3
    kNormalVector = (1<<1), // 3
    kColor = (1<<2), // 3
    kTextCoords = (1<<3), // 2
    kInstanceValues = (1<<4), // 2
    kCount = 5,
    kAll = (kColor<<1)-1
};

// Implemented using a VertexArray object
struct GLMeshBuffer {
    enum DrawType {
        kArray = 0,
        kElement = 1
    };

    bool Init(BufferName, GLBufferManager*);
    bool Exit();

    void BindBuffer();
    void UnbindBuffer();
    void Draw();
    void DrawInstanced(uint);
    void LoadData(GLBuffer::BufferData data, uint flags);

    uint _bufferId;
    VertexAttributeFlag _flags;
    DrawType _drawType;
    uint _triangleCount;
    GLBufferManager* _bufferManager;
    std::vector<GLBuffer*> _buffers;
    
    bool _valid = false;
    bool _used = false;
    BufferName _bufferName; 
};

}

#endif