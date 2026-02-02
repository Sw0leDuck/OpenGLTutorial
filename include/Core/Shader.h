#ifndef SHADER_H
#define SHADER_H
#include "Common/Types.h"
#include "unordered_map"
#include "string"

namespace tartarus {

class GLShaderManager;

struct Shader {
    enum UniformType {
        kInt = 0,
        kFloat = 1,
        kFloat3 = 2,
        kMatrix = 3,
        kSampled2D = 4
    };

    union UniformValue {
        uint _intValue;
        float _floatValue;
        float* _floatPtr;
        vec3 _f3Value;
    };

    std::unordered_map<
        const char*, std::pair<UniformType, UniformValue>> _uniforms;

    uint _fragmentShaderId = -1;
    uint _vertexShaderId = -1;
    uint _programId = -1;

    std::string _vertexSrc;
    std::string _fragmentSrc;

    
    void AddUniform(const char* name, std::pair<UniformType, UniformValue>);

    void UseProgam();
    void UpdateUniforms();
    void Reset();
    void SetInt(const char*, uint value);
    void SetFloat(const char*, float value);
    void SetFloat3(const char*, float x1, float x2, float x3);
    void SetFloat3(const char*, vec3 value);
    void SetMatrix(const char*, float* matrix);

    bool valid = false;

    GLShaderManager* _manager = nullptr;
};

}

#endif