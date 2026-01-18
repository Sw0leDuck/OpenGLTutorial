#ifndef COMPILER_H
#define COMPILER_H

#include <glm/ext/vector_float3.hpp>
#include <string>
#include "common/types.h"
#include <map>

namespace compiler {
    struct Program {
        Program() : id(-1) {}
        Program(uint id);

        void SetInt(const char* name, uint value);
        void SetFloat(const char* name, float value);
        void SetFloat3(const char* name, float x1, float x2, float x3);
        void SetFloat3(const char* name, glm::vec3 value);
        void SetMatrix(const char* name, float* matrix);

        void UseProgram();
        
        uint id;
    };
    struct Context {
        std::map<uint, uint> _vertexShaderId;
        std::map<uint, uint> _fragmentShaderId;
        std::map<uint, Program> _programId;

        ~Context();
        bool Init();
        bool Exit();

        bool CompileShader(const char* filePath, uint shaderType, uint id);
        bool LinkProgram(uint id, uint vertexId, uint fragmentId);

        inline Program& GetProgram(uint id) { return _programId[id]; }
        inline void UseProgram(uint id) { _programId[id].UseProgram(); }

        void SetInt(const char* name, uint id, uint value);
        void SetFloat(const char* name, uint id, float value);
        void SetMatrix(const char* name, uint id, float* matrix);
    };

    bool Init();
    bool Exit();

    bool CompileShader(const char* filePath, uint shaderType, uint id);
    bool LinkProgram(uint id, uint vertexId, uint fragmentId);
    bool DeleteShaders();

    Program* GetProgram(uint id);

    std::string LoadGLSLsource(const char* filePath);

    bool CheckLinkStatus(uint programId, uint id);
    bool CheckCompilerStatus(uint shaderId, uint id);
} // namespace compiler

#endif