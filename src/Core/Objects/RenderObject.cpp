#include "Core/Objects/RenderObject.h"

namespace tartarus {

void RenderObject::SetMeshBuffer(GLMeshBuffer* meshBuffer) {
    if(_meshBuffer)
        _meshBuffer->_used = false;
    _meshBuffer = meshBuffer;
    _meshBuffer->_used = true;
}

}