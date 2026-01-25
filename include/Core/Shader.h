#ifndef SHADER_H
#define SHADER_H
#include "Common/types.h"

namespace tartarus {

struct Shader {
    uint _fragmentShaderId;
    uint _vertexShaderId;
    uint _programId;

    bool valid;
};

}

#endif