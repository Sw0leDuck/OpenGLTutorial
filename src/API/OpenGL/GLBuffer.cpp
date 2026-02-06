#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLBuffer.h"

namespace tartarus {

void LoadBuffer(void* data, uint size, uint target, uint usage, uint bufferId);

bool GLBuffer::Init(BufferType type){
    // this->_bufferManagerPtr = bufferManagerPtr;
    _type = type;
    GL_CHECK_CALL(glGenBuffers(1, &_bufferId))
    return true;
}

bool GLBuffer::Exit(){
    GL_CHECK_CALL(glDeleteBuffers(1, &_bufferId))
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
    GL_CHECK_CALL(glBindBuffer(_glBufferArguments._target, _bufferId))
}

void GLBuffer::UnbindBuffer(){
    GL_CHECK_CALL(glBindBuffer(_glBufferArguments._target, 0))
}

void LoadBuffer(void* data, uint size, uint target, uint usage, uint bufferId){
    GL_CHECK_CALL(glBindBuffer(target, bufferId))
    GL_CHECK_CALL(glBufferData(target, size, data, usage))
    GL_CHECK_CALL(glBindBuffer(target, 0))
}

}