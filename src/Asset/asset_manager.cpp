#include "glad/glad.h"
#include "Asset/asset_manager.h"
#include "glsl_compiler.h"
#include "common/types.h"


namespace asset::manager {

AssetManager g_manager;

bool Init(){
    return g_manager.Init();
}

bool Exit(){
    return g_manager.Exit();
}

std::pair<uint, uint> Load2DTexture(const char *filePath, uint type){
    return g_manager._textureManager.Load2DTexture(filePath, type);
}

compiler::Program* GetProgram(uint id){
    return compiler::GetProgram(id);
}

void LoadMesh(){
    g_manager._meshManager.LoadMesh();
}

graphic::Mesh3D& LoadTestMesh(){
    return g_manager._meshManager.LoadTestMesh();
}

graphic::Mesh3D& LoadLightSourceTest(){
    return g_manager._meshManager.LoadLightSourceTest();
}

void DrawMesh(){
    for(auto& iter : g_manager._meshManager._lightSources){
        iter._program->UseProgram();
        iter.LoadMatrixUniforms();
        iter._program->SetFloat3("lightColor", iter._objectColor);
        iter.DrawArray();
    }
    
    for(auto& iter : g_manager._meshManager._meshes){
        iter.LoadTextures();
        iter._program->UseProgram();
        iter.LoadDefaultUniforms();
        iter.DrawArray();
    }
}

void UpdateMesh(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition){
    [[__maybe_unused__]] static double hack_time = 0;
    hack_time += 0.005f;

    glm::vec3 current_light_pos = glm::vec3(1.2f, 1.0f, 2.0f);
    for(auto& iter : g_manager._meshManager._lightSources){
        iter._modelMatrice.Translate(current_light_pos).
                        Scale(glm::vec3(0.2f));
        iter._viewMatrice._matrix = viewMatrix;
        iter._projectionMatrice._matrix = projectionMatrix;
        // iter._objectColor = lightColor;
    }

    for(auto& iter : g_manager._meshManager._meshes){
        iter._modelInverseTransposeMatrice._matrix = glm::transpose(glm::inverse(iter._modelMatrice._matrix));
        iter._viewMatrice._matrix = viewMatrix;
        iter._projectionMatrice._matrix = projectionMatrix;
        iter._cameraPosition = cameraPosition;
        iter._light._lightPosition = current_light_pos;
    }
}

// TODO: what does this function do?
// - load all glsl shaders ?
bool AssetManager::Init(){
    compiler::Init();

    if(!compiler::CompileShader("../../../shaders/default.vert",
            GL_VERTEX_SHADER, 
            (uint)VertexIdType::kDefault))
        return false;
        
    if(!compiler::CompileShader("../../../shaders/default.frag",
            GL_FRAGMENT_SHADER, 
            (uint)FragmentIdType::kDefault))
        return false;

    if(!compiler::CompileShader("../../../shaders/light_source.frag", 
            GL_FRAGMENT_SHADER,
            (uint)FragmentIdType::kLightSource))
        return false;

    if(!compiler::LinkProgram((uint)ProgramType::kDefault, 
            (uint)VertexIdType::kDefault,
            (uint)FragmentIdType::kDefault))
        return false;

    if(!compiler::LinkProgram((uint)ProgramType::kLightSource, 
            (uint)VertexIdType::kDefault,
            (uint)FragmentIdType::kLightSource))
        return false;
    // delete all the shaders
    compiler::DeleteShaders();

    _textureManager.Init();

    return true;
}

// TODO: what does this function do?
// - delete any used buffer/textures etc?
bool AssetManager::Exit(){
    if(!compiler::Exit())
        return false;

    _textureManager.Exit();

    _meshManager.Exit();

    return true;
}

}