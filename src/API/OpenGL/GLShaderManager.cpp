#include "API/OpenGL/GLUtil.h"
#include "API/OpenGL/GLShaderManager.h"
#include "fstream"
namespace tartarus {

std::string ShaderLoader::LoadGLSLsource(const char* filePath) {
    std::string source{};
    std::ifstream inFile{filePath};

    if(!inFile){
        LOG(ERROR, "File %s not found", filePath);
        return source;
    }

    std::string line{};
    while (std::getline(inFile, line)){
        line += '\n';
        source.operator+=(line);
    }

    return source;
}

bool CheckCompilerStatus(uint shaderId);
bool CheckLinkStatus(uint programId);

// TODO: DEFINETELY REWRITE THIS SHIT
bool GLShaderManager::Init() {
    _shaders.reserve(10);
    Shader* ptr;

    CompileShader(ShaderName::kDefault, 
        "../../shaders/default.vert", "../../shaders/default.frag");
    
    ptr = GetShader(ShaderName::kDefault);
    ptr->InitUniformName("modelMatrix");
    ptr->InitUniformName("viewMatrix");
    ptr->InitUniformName("projectionMatrix");
    ptr->InitUniformName("modelInverseTransposeMatrix");

    ptr->InitUniformName("viewPos");

    ptr->InitUniformName("material.ambient");
    ptr->InitUniformName("material.diffuse");
    ptr->InitUniformName("material.specular");
    ptr->InitUniformName("material.emission");
    ptr->InitUniformName("material.shininess");

    ptr->InitUniformName("dirLight.direction");
    ptr->InitUniformName("dirLight.ambient");
    ptr->InitUniformName("dirLight.diffuse");
    ptr->InitUniformName("dirLight.specular");

    ptr->InitUniformName("pointLight[0].position");
    ptr->InitUniformName("pointLight[0].ambient");
    ptr->InitUniformName("pointLight[0].diffuse");
    ptr->InitUniformName("pointLight[0].specular");
    ptr->InitUniformName("pointLight[0].constant");
    ptr->InitUniformName("pointLight[0].linear");
    ptr->InitUniformName("pointLight[0].quadratic");

    ptr->InitUniformName("pointLight[1].position");
    ptr->InitUniformName("pointLight[1].ambient");
    ptr->InitUniformName("pointLight[1].diffuse");
    ptr->InitUniformName("pointLight[1].specular");
    ptr->InitUniformName("pointLight[1].constant");
    ptr->InitUniformName("pointLight[1].linear");
    ptr->InitUniformName("pointLight[1].quadratic");

    ptr->InitUniformName("pointLight[2].position");
    ptr->InitUniformName("pointLight[2].ambient");
    ptr->InitUniformName("pointLight[2].diffuse");
    ptr->InitUniformName("pointLight[2].specular");
    ptr->InitUniformName("pointLight[2].constant");
    ptr->InitUniformName("pointLight[2].linear");
    ptr->InitUniformName("pointLight[2].quadratic");

    ptr->InitUniformName("pointLight[3].position");
    ptr->InitUniformName("pointLight[3].ambient");
    ptr->InitUniformName("pointLight[3].diffuse");
    ptr->InitUniformName("pointLight[3].specular");
    ptr->InitUniformName("pointLight[3].constant");
    ptr->InitUniformName("pointLight[3].linear");
    ptr->InitUniformName("pointLight[3].quadratic");

    // ####################################################################

    CompileShader(ShaderName::kPointLight, 
        "../../shaders/default.vert", "../../shaders/light_source.frag");
    ptr = GetShader(ShaderName::kPointLight);
    ptr->InitUniformName("modelMatrix");
    ptr->InitUniformName("viewMatrix");
    ptr->InitUniformName("projectionMatrix");
    ptr->InitUniformName("modelInverseTransposeMatrix");

    ptr->InitUniformName("lightColor");

    // ####################################################################

    CompileShader(ShaderName::kInstanced, 
        "../../shaders/defaultInstanced.vert", "../../shaders/default.frag");
    
    ptr = GetShader(ShaderName::kInstanced);
    ptr->InitUniformName("modelMatrix");
    ptr->InitUniformName("viewMatrix");
    ptr->InitUniformName("projectionMatrix");
    ptr->InitUniformName("modelInverseTransposeMatrix");

    ptr->InitUniformName("viewPos");

    ptr->InitUniformName("material.ambient");
    ptr->InitUniformName("material.diffuse");
    ptr->InitUniformName("material.specular");
    ptr->InitUniformName("material.emission");
    ptr->InitUniformName("material.shininess");

    ptr->InitUniformName("dirLight.direction");
    ptr->InitUniformName("dirLight.ambient");
    ptr->InitUniformName("dirLight.diffuse");
    ptr->InitUniformName("dirLight.specular");

    ptr->InitUniformName("pointLight[0].position");
    ptr->InitUniformName("pointLight[0].ambient");
    ptr->InitUniformName("pointLight[0].diffuse");
    ptr->InitUniformName("pointLight[0].specular");
    ptr->InitUniformName("pointLight[0].constant");
    ptr->InitUniformName("pointLight[0].linear");
    ptr->InitUniformName("pointLight[0].quadratic");

    ptr->InitUniformName("pointLight[1].position");
    ptr->InitUniformName("pointLight[1].ambient");
    ptr->InitUniformName("pointLight[1].diffuse");
    ptr->InitUniformName("pointLight[1].specular");
    ptr->InitUniformName("pointLight[1].constant");
    ptr->InitUniformName("pointLight[1].linear");
    ptr->InitUniformName("pointLight[1].quadratic");

    ptr->InitUniformName("pointLight[2].position");
    ptr->InitUniformName("pointLight[2].ambient");
    ptr->InitUniformName("pointLight[2].diffuse");
    ptr->InitUniformName("pointLight[2].specular");
    ptr->InitUniformName("pointLight[2].constant");
    ptr->InitUniformName("pointLight[2].linear");
    ptr->InitUniformName("pointLight[2].quadratic");

    ptr->InitUniformName("pointLight[3].position");
    ptr->InitUniformName("pointLight[3].ambient");
    ptr->InitUniformName("pointLight[3].diffuse");
    ptr->InitUniformName("pointLight[3].specular");
    ptr->InitUniformName("pointLight[3].constant");
    ptr->InitUniformName("pointLight[3].linear");
    ptr->InitUniformName("pointLight[3].quadratic");

    return true;
}

bool GLShaderManager::Exit() {
    for(auto& iter : _shaders){
        // Handled in CompileShader
        // glDeleteShader(iter._vertexShaderId); 
        // glDeleteShader(iter._fragmentShaderId);
        GL_CHECK_CALL(glDeleteProgram(iter.second._programId))
        iter.second._manager = nullptr;
    }
    _shaders.clear();
    return true;
}

void GLShaderManager::CompileShader(ShaderName id,
                                const char* vert, const char* frag){
    auto& iter = _shaders[id];
    iter._manager = nullptr;

    {
        GL_CHECK_SET_CALL(iter._vertexShaderId, glCreateShader(GL_VERTEX_SHADER))
        auto source = _loader.LoadGLSLsource(vert);
        if(source.empty()){
            GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
            iter.valid = false;
            LOG(INFO, "Vertex Shader %s could not be compiled", 
                GetShaderName(id));
            return;
        }
        auto src = source.c_str();
        GL_CHECK_CALL(glShaderSource(iter._vertexShaderId, 1, &src, nullptr))
        
        GL_CHECK_CALL(glCompileShader(iter._vertexShaderId))
        if(!CheckCompilerStatus(iter._vertexShaderId)){
            GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
            iter.valid = false;
            return;
        }

    }

    {
        GL_CHECK_SET_CALL(iter._fragmentShaderId, glCreateShader(GL_FRAGMENT_SHADER))
        auto source = _loader.LoadGLSLsource(frag);
        if(source.empty()){
            GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
            GL_CHECK_CALL(glDeleteShader(iter._fragmentShaderId))
            iter.valid = false;
            LOG(INFO, "Fragment Shader %s could not be compiled", 
                GetShaderName(id));
        }
        auto src = source.c_str();
        GL_CHECK_CALL(glShaderSource(iter._fragmentShaderId, 1, &src, nullptr))
        
        GL_CHECK_CALL(glCompileShader(iter._fragmentShaderId))
        if(!CheckCompilerStatus(iter._fragmentShaderId)){
            GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
            GL_CHECK_CALL(glDeleteShader(iter._fragmentShaderId))
            iter.valid = false;
            SCREAM("...");
            return;
        }
    }

    {
        GL_CHECK_SET_CALL(iter._programId, glCreateProgram())

        GL_CHECK_CALL(glAttachShader(iter._programId, iter._vertexShaderId))
        GL_CHECK_CALL(glAttachShader(iter._programId, iter._fragmentShaderId))

        GL_CHECK_CALL(glLinkProgram(iter._programId))

        if(!CheckLinkStatus(iter._programId)){
            GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
            GL_CHECK_CALL(glDeleteShader(iter._fragmentShaderId))
            GL_CHECK_CALL(glDeleteProgram(iter._programId))
            iter.valid = false;
            return;
        }
    }

    GL_CHECK_CALL(glDeleteShader(iter._vertexShaderId))
    GL_CHECK_CALL(glDeleteShader(iter._fragmentShaderId))

    iter._manager = this;
    iter.valid = true;
}

Shader* GLShaderManager::GetShader(ShaderName id){
    auto iter = _shaders.find(id);
    if(iter == _shaders.end())
        SCREAM("Shader %s not found\n", GetShaderName(id));
    return &iter->second;
}


bool CheckCompilerStatus(uint shaderId){
    int32_t success;
    char infoLog[512];
    GL_CHECK_CALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success))
    if(success == GL_FALSE){
        GL_CHECK_CALL(glGetShaderInfoLog(shaderId, 512, nullptr, infoLog))
        LOG(ERROR, "ShaderId: %d failed with error %s\n", shaderId, infoLog);
        return false;
    }
    return true;
}

bool CheckLinkStatus(uint programId){
    int32_t success;
    char infoLog[512];
    GL_CHECK_CALL(glGetProgramiv(programId, GL_LINK_STATUS, &success))
    if(success == GL_FALSE){
        GL_CHECK_CALL(glGetProgramInfoLog(programId, 512, nullptr, infoLog))
        LOG(ERROR,"ProgramId: %d failed with error %s\n", programId, infoLog);
        return false;
    }
    return true;
}


} // namespace tartarus