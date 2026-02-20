#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLMeshBuffer.h"
#include "API/OpenGL/GLBufferManager.h"

namespace tartarus {

void SetVertexAttribute(uint& index, uint size, 
            uint type, uint normalized, 
            uint stride, uint& offset){
    GL_CHECK_CALL(glVertexAttribPointer(index, size, type, normalized, stride, 
        (void*)((ull)offset)))
    GL_CHECK_CALL(glEnableVertexAttribArray(index))
    index++;
    // Hardcoded float value, up to now, the only
    // type passed is GL_FLOAT
    offset += (size * sizeof(float));
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

void GLMeshBuffer::DrawInstanced(uint count){
    CHECK(_valid && _used)
    GL_CHECK_CALL(glBindVertexArray(_bufferId))
    switch(_drawType){
        case DrawType::kArray:
            GL_CHECK_CALL(glDrawArraysInstanced(GL_TRIANGLES, 0, _triangleCount, count))
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

    // interesting code??? wtf is goind on here
    // it will work for the case of only creating a vertex mesh buffer
    // what about the element one?
    for(auto& iter : _buffers)
        iter->BindBuffer();

    uint stride = ComputeStrideFromFlags(flags);
    uint index = 0, offset = 0;

    if(flags & (uint)VertexAttributeFlag::kPos)
        SetVertexAttribute(index, 3, GL_FLOAT, GL_FALSE, stride, offset);

    if(flags & (uint)VertexAttributeFlag::kNormalVector)
        SetVertexAttribute(index, 3, GL_FLOAT, GL_FALSE, stride, offset);

    if(flags & (uint)VertexAttributeFlag::kColor)
        SetVertexAttribute(index, 3, GL_FLOAT, GL_FALSE, stride, offset);

    if(flags & (uint)VertexAttributeFlag::kTextCoords)
        SetVertexAttribute(index, 2, GL_FLOAT, GL_FALSE, stride, offset);
    
    if(flags & (uint)VertexAttributeFlag::kInstanceValues){
        uint tmp = 0;
        _buffers.emplace_back(_bufferManager->GetCreateInstanceBuffer(data._instanceCount));

        auto iter = _buffers.back();
        // malloc ?
        // _vertices is not longer used in this point
        data._vertSize = sizeof(vec3)*data._instanceCount*data._instanceCount;
        data._vertices = (vec3*)malloc(data._vertSize);
        // let the function free the buffer
        data._mallocUsed = true;

        // build the buffer
        {
            vec3* bufferData = reinterpret_cast<vec3*>(data._vertices);
            for(int z=-data._instanceCount; z<data._instanceCount; z+=2){
                for(int x=-data._instanceCount; x<data._instanceCount; x+=2){
                    bufferData->x = ((float)x / (float)2.f);
                    bufferData->y = 0;
                    bufferData->z = ((float)z / (float)2.f);
                    bufferData++;
                }
            }

            iter->_bufferData = data;
            iter->LoadArrayBuffer(GL_STATIC_DRAW);
            _drawType = DrawType::kArray;

            data._mallocUsed = false; // in case we insert something down the line
        }

        iter->BindBuffer();
        
        SetVertexAttribute(index, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), tmp);
        // index-1 because index was increased above
        GL_CHECK_CALL(glVertexAttribDivisor(index-1, 1))
        iter->UnbindBuffer();
    }

    _triangleCount = data._indexSize != 0 ? 
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