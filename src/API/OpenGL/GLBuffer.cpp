#include "glad/glad.h"
#include <cstdlib>
#include "API/OpenGL/GLBuffer.h"

namespace tartarus {

void LoadBuffer(void* data, uint size, uint target, uint usage, uint bufferId);

bool GLBuffer::Init(BufferType type){
    // this->_bufferManagerPtr = bufferManagerPtr;
    _type = type;
    glGenBuffers(1, &_bufferId);
    return true;
}

bool GLBuffer::Exit(){
    glDeleteBuffers(1, &_bufferId);
    return true;
}

void GLBuffer::LoadArrayBuffer(uint usage){
    _glBufferArguments._usage = usage;
    _glBufferArguments._target = GL_ARRAY_BUFFER;

    LoadBuffer(_bufferData._vertices, _bufferData._vertSize, 
        _glBufferArguments._target, _glBufferArguments._usage, _bufferId);

    if(_bufferData._mallocUsed)
        free(_bufferData._vertices);
}

void GLBuffer::LoadElementBuffer(uint usage){
    _glBufferArguments._usage = usage;
    _glBufferArguments._target = GL_ELEMENT_ARRAY_BUFFER;

    LoadBuffer(_bufferData._indices, _bufferData._indexSize, 
        _glBufferArguments._target, _glBufferArguments._usage, _bufferId);

    if(_bufferData._mallocUsed)
        free(_bufferData._indices);
}

void GLBuffer::BindBuffer(){
    glBindBuffer(_glBufferArguments._target, _bufferId);
}

void GLBuffer::UnbindBuffer(){
    glBindBuffer(_glBufferArguments._target, 0);
}

void LoadBuffer(void* data, uint size, uint target, uint usage, uint bufferId){
    glBindBuffer(target, bufferId);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
}

}