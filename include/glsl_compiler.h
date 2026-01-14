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

    struct Program {
        Program() : id(-1) {}
        Program(uint id);

        void setInt(const std::string& name, uint value);
        void setFloat(const std::string& name, float value);
        void setMatrix(const std::string& name, float* matrix);

        inline void useProgram() { glUseProgram(id); }
        
        uint id;
    };
    struct Context {
        std::map<uint, uint> _ShaderId;
        std::map<uint, Program> _programId;

        ~Context();

        bool compileShader(std::string filePath, uint shaderType, uint id);
        bool linkProgram(uint id, uint vertexId, uint fragmentId);

        inline Program& getProgram(uint id) { return _programId[id]; }
        inline void useProgram(uint id) { _programId[id].useProgram(); }

        void setInt(const std::string& name, uint id, uint value);
        void setFloat(const std::string& name, uint id, float value);
        void setMatrix(const std::string& name, uint id, float* matrix);
    };

} // namespace compiler

#endif