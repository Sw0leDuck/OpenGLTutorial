// #include "glad/glad.h"
// #include "Asset/asset_manager.h"
// #include "glsl_compiler.h"
// #include "common/types.h"


// namespace asset::manager {

// AssetManager g_manager;

// bool Init(){
//     return g_manager.Init();
// }

// bool Exit(){
//     return g_manager.Exit();
// }

// std::pair<uint, uint> Load2DTexture(const char *filePath, uint type){
//     return g_manager._textureManager.Load2DTexture(filePath, type);
// }

// compiler::Program* GetProgram(uint id){
//     return compiler::GetProgram(id);
// }

// void LoadMesh(){
//     g_manager._meshManager.LoadMesh();
// }

// graphic::Mesh3D& LoadTestMesh(){
//     return g_manager._meshManager.LoadTestMesh();
// }

// graphic::Mesh3D& LoadLightSourceTest(){
//     return g_manager._meshManager.LoadLightSourceTest();
// }

// void DrawMesh(){
//     for(auto& iter : g_manager._meshManager._lightSources){
//         iter._program->UseProgram();
//         iter.LoadMatrixUniforms();
//         iter._program->SetFloat3("lightColor", iter._objectColor);
//         iter.DrawArray();
//     }
    
//     for(auto& iter : g_manager._meshManager._meshes){
//         iter.LoadTextures();
//         iter._program->UseProgram();
//         iter.LoadDefaultUniforms();
//         iter.Draw10Cubes();
//     }
// }

// void UpdateMesh(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection){
//     [[__maybe_unused__]] static double hack_time = 0;
//     [[__maybe_unused__]] uint counter = 0;
//     hack_time += 0.005f;

//     glm::vec3 pointLightPositions[] = {
// 	    glm::vec3( 0.7f,  0.2f,  2.0f),
// 	    glm::vec3( 2.3f, -3.3f, -4.0f),
// 	    glm::vec3(-4.0f,  2.0f, -12.0f),
// 	    glm::vec3( 0.0f,  0.0f, -3.0f)
//     };

//     for(auto& iter : g_manager._meshManager._lightSources){
//         iter._modelMatrice.Translate(pointLightPositions[counter++]).
//                         Scale(glm::vec3(0.2f));
//         iter._viewMatrice._matrix = viewMatrix;
//         iter._projectionMatrice._matrix = projectionMatrix;
//     }
//     counter = 0;

//     for(auto& iter : g_manager._meshManager._meshes){
//         iter._modelInverseTransposeMatrice._matrix = glm::transpose(glm::inverse(iter._modelMatrice._matrix));
//         iter._viewMatrice._matrix = viewMatrix;
//         iter._projectionMatrice._matrix = projectionMatrix;
//         iter._cameraPosition = cameraPosition;
//         iter._light._lightDirection = cameraDirection;
//         iter._light._lightPosition = cameraPosition;
//         iter._pointLightPositions[0] = pointLightPositions[0];
//         iter._pointLightPositions[1] = pointLightPositions[1];
//         iter._pointLightPositions[2] = pointLightPositions[2];
//         iter._pointLightPositions[3] = pointLightPositions[3];
//     }
// }

// // TODO: what does this function do?
// // - load all glsl shaders ?
// bool AssetManager::Init(){
//     compiler::Init();

//     if(!compiler::CompileShader("../../shaders/default.vert",
//             GL_VERTEX_SHADER, 
//             (uint)VertexIdType::kDefault))
//         return false;
        
//     if(!compiler::CompileShader("../../shaders/default.frag",
//             GL_FRAGMENT_SHADER, 
//             (uint)FragmentIdType::kDefault))
//         return false;

//     if(!compiler::CompileShader("../../shaders/light_source.frag", 
//             GL_FRAGMENT_SHADER,
//             (uint)FragmentIdType::kLightSource))
//         return false;

//     if(!compiler::LinkProgram((uint)ProgramType::kDefault, 
//             (uint)VertexIdType::kDefault,
//             (uint)FragmentIdType::kDefault))
//         return false;

//     if(!compiler::LinkProgram((uint)ProgramType::kLightSource, 
//             (uint)VertexIdType::kDefault,
//             (uint)FragmentIdType::kLightSource))
//         return false;
//     // delete all the shaders
//     compiler::DeleteShaders();

//     _textureManager.Init();

//     return true;
// }

// // TODO: what does this function do?
// // - delete any used buffer/textures etc?
// bool AssetManager::Exit(){
//     if(!compiler::Exit())
//         return false;

//     _textureManager.Exit();

//     _meshManager.Exit();

//     return true;
// }

// }