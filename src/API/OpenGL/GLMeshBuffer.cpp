#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLMeshBuffer.h"
#include "API/OpenGL/GLBufferManager.h"

namespace tartarus {

void SetVertexAttribute(bool set, uint& index, uint size, 
            uint type, uint normalized, 
            uint stride, uint& offset){
    if(set){
        GL_CHECK_CALL(glVertexAttribPointer(index, size, type, normalized, stride, 
            (void*)((ull)offset)))
        GL_CHECK_CALL(glEnableVertexAttribArray(index))
        index++;
        // Hardcoded float value, up to now, the only
        // type passed is GL_FLOAT
        offset += (size * sizeof(float));
    }
}

uint ComputeStrideFromFlags(uint flags){
    uint stride = 0;
    if(flags & (uint)VertexAttributeFlag::kPos)
        stride += 3*sizeof(float);

    if(flags & (uint)VertexAttributeFlag::kNormalVector)
        stride += 3*sizeof(float);

    if(flags & (uint)VertexAttributeFlag::kColor)
        stride += 3*sizeof(float);

    if(flags & (uint)VertexAttributeFlag::kTextCoords)
        stride += 2*sizeof(float);

    return stride;
}

bool GLMeshBuffer::Init(BufferName id, GLBufferManager* bufferManager){
    _bufferName = id;
    _valid = false;
    _bufferManager = bufferManager;
    _buffers.reserve(2);

    GL_CHECK_CALL(glGenVertexArrays(1, &_bufferId))

    return true;
}

bool GLMeshBuffer::Exit(){
    _buffers.clear();
    _bufferManager = nullptr;
    GL_CHECK_CALL(glDeleteVertexArrays(1, &_bufferId))
    return true;
}

void GLMeshBuffer::BindBuffer(){
    GL_CHECK_CALL(glBindVertexArray(_bufferId))
}

void GLMeshBuffer::UnbindBuffer(){
    GL_CHECK_CALL(glBindVertexArray(0))
}

void GLMeshBuffer::Draw(){
    CHECK(_valid && _used)
    GL_CHECK_CALL(glBindVertexArray(_bufferId))
    switch(_drawType){
        case DrawType::kArray:
            GL_CHECK_CALL(glDrawArrays(GL_TRIANGLES, 0, _triangleCount))
            break;
        case DrawType::kElement:
            GL_CHECK_CALL(glDrawElements(GL_TRIANGLES, _triangleCount, GL_UNSIGNED_INT, 0))
            break;
    }
    GL_CHECK_CALL(glBindVertexArray(0))
}

void GLMeshBuffer::LoadData(GLBuffer::BufferData data, uint flags){
    this->BindBuffer();
        
    if(data._vertices){
        _buffers.emplace_back(
            _bufferManager->GetGpuArrayBuffer(_bufferName));
        _buffers.back()->_bufferData = data;
        _buffers.back()->LoadArrayBuffer(GL_STATIC_DRAW);
        _drawType = DrawType::kArray;
    }

    if(data._indices){
        _buffers.emplace_back(
            _bufferManager->GetGpuIndexBuffer(_bufferName));
        _buffers.back()->_bufferData = data;
        _buffers.back()->LoadElementBuffer(GL_STATIC_DRAW);
        _drawType = DrawType::kElement;
    }

    for(auto& iter : _buffers)
        iter->BindBuffer();

    uint stride = ComputeStrideFromFlags(flags);
    uint index = 0, offset = 0;

    for(uint j=0; j<(uint)VertexAttributeFlag::kCount; j++){
        // kTexCoords is represented only with 2 floats
        // all the others attributes need 3
        uint size = j == 3  ? 2 : 3;
        SetVertexAttribute(flags & (uint)(1<<j),
            index, 
            size, 
            GL_FLOAT, 
            GL_FALSE, 
            stride, 
            offset);
    }

    _triangleCount = data._indexSize != -1 ? 
        data._indexSize/sizeof(uint) : 
        data._vertSize / stride;
    
    CHECK((data._vertSize % stride == 0) || 
        (data._indexSize % sizeof(uint) == 0))

    for(auto& iter : _buffers)
        iter->UnbindBuffer();

    this->UnbindBuffer();
    _valid = true;
}

}