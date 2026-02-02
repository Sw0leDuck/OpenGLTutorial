#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "Common/Types.h"

namespace tartarus {

struct GLBuffer {
    enum BufferType {
        kInvalid = 0,
        kArrayBuffer = 1,
        kIndexBuffer = 2
    };

    struct OpenGLArguments {
        uint _target;
        uint _usage;
    };

    // This should be handled by us
    // We could free them after uploading 
    // them to the GPU
    struct BufferData {
        BufferData(
            void* vertices = nullptr, 
            uint verSize = -1,
            void* indices = nullptr,
            uint indexSize = -1,
            bool mallocUse = false) : 
        _vertices(vertices), 
        _vertSize(verSize),
        _indices(indices),
        _indexSize(indexSize),
        _mallocUsed(mallocUse) {}

        void* _vertices = nullptr;
        uint _vertSize = -1;

        void* _indices = nullptr;
        uint _indexSize = -1;

        bool _mallocUsed = false;
    };

    bool Init(BufferType);
    bool Exit();

    bool IsValid() { return true; }
    bool IsUsed() { return _used; }

    void LoadArrayBuffer(uint usage);
    void LoadElementBuffer(uint usage);

    void BindBuffer();
    void UnbindBuffer();

    OpenGLArguments _glBufferArguments;
    uint _bufferId = -1;
    BufferType _type;
    BufferData _bufferData;

    bool _used = false;
};

}

#endif