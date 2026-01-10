#ifndef COMPILER_H
#define COMPILER_H
#include <glad/glad.h>

#include <string>
#include "common/types.h"
#include <map>

namespace compiler {

    std::string loadGLSLsource(std::string filePath);

    bool checkLinkStatus(uint programId, uint id);
    bool checkCompilerStatus(uint shaderId, uint id);

    struct context {
        std::map<uint, uint> _ShaderId;
        std::map<uint, uint> _programId;

        ~context();

        bool compileShader(std::string filePath, uint shaderType, uint id);
        bool linkProgram(uint id, uint vertexId, uint fragmentId);

        inline void useProgram(uint id) { glUseProgram(_programId[id]); }

        void setInt(const std::string& name, uint id, uint value);
        void setFloat(const std::string& name, uint id, float value);
    };

} // namespace compiler

#endif