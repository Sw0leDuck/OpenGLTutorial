#include "common/error_handler.h"
#include "common/primitive_vertices.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "mesh3D.h"

#include <cmath>
#include "common/algorithm.h"
#include "common/primitive_vertices.h"


namespace graphic {

Mesh3D::~Mesh3D() { }

void Mesh3D::Init(){
    glGenVertexArrays(1, &_vao);
    glCheckError();
    glGenBuffers(1, &_vbo);
    glCheckError();
    glGenBuffers(1, &_ebo);
    glCheckError();

    _modelMatrice._matrix = glm::mat4(1.0f);
    _viewMatrice._matrix = glm::mat4(1.0f);
    _projectionMatrice._matrix = glm::mat4(1.0f);

    _material._ambient = glm::vec3(0.2125	, 0.1275,	0.054);
    _material._diffuse = glm::vec3(0.714, 0.4284, 0.18144);
    _material._specular = glm::vec3(0.5f, 0.5f, 0.5f);
    _material._shininess = 64.0f;

    _light._ambient = glm::vec3( 0.2f, 0.2f, 0.2f);
    _light._diffuse = glm::vec3( 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
    _light._specular = glm::vec3(1.0f, 1.0f, 1.0f);

    _objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
}

void Mesh3D::Exit(){
    if(_vao != -1)
        glDeleteVertexArrays(1, &_vao);
    if(_vbo != -1)
        glDeleteBuffers(1, &_vbo);
    if(_ebo != -1)
        glDeleteBuffers(1, &_ebo);

    // TODO: call exit on 3D textures
}

void Mesh3D::LoadCube(uint vertexAttributeFlags){
    LoadCube(graphic::cube_vertices, sizeof(graphic::cube_vertices), cube_vertices_stride, vertexAttributeFlags);
}

void Mesh3D::LoadTriangle(){
    Load2DTriangle_VBO(graphic::vert_2DTriangleLower, sizeof(graphic::vert_2DTriangleLower));
}

void Mesh3D::Load2DTriangle_VBO(const float* vert, uint vert_size){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glCheckError();
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);
    glCheckError();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glCheckError();

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);
    _count = (vert_size/sizeof(float))/3;
}

void Mesh3D::LoadCube_TexCoords(const float* vert, uint vert_size, uint stride){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);
    // every row contains 5 values : 3 pts | 2 texCoords
    _count = (vert_size/stride);
}

void Mesh3D::LoadCube(const float* vert, uint vert_size, uint stride, uint vertexAttributeFlags){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    if(vertexAttributeFlags & (uint)VertexAttribute::kPos){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
    }

    if(vertexAttributeFlags & (uint)VertexAttribute::kNormalVector){
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if(vertexAttributeFlags & (uint)VertexAttribute::kTextCoords){
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);

    _count = (vert_size/stride);
}

void Mesh3D::Load2DTriangle_VBO_Rainbow(const float* vert, uint vert_size){
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    _count = 3;
}

void Mesh3D::Load2DRectangle_EBO(const float* vert, uint vert_size, const uint* index, uint index_size){
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);
    _count = index_size;
}

void Mesh3D::Load2DRectangle_2DImage(const float* vert, uint vert_size, const uint* index, uint index_size, uint stride){
    glBindVertexArray(_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)12);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)24);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    _count = index_size/sizeof(uint);
}

void Mesh3D::Draw2DRectangle_2DImage() {
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::Draw2DRectangle_EBO(){
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::Draw2DTriangle_VBO(){
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _count);
    glBindVertexArray(0);
}

void Mesh3D::Draw2DTriangle_VBO_uniform(uint programId){
    float timer = glfwGetTime();
    float redValue = common::clamp(std::sin(timer), 0.5f, 1.0f);
    int uniformColorLocation = glGetUniformLocation(programId, "uniformColor");
    glUniform4f(uniformColorLocation, redValue, 0, 0, 1.0);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _count);
    glBindVertexArray(0);
}

void Mesh3D::DrawIndex(){
    for(uint32_t i=0; i<_textures2DId.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(_textures2DId[i].second, _textures2DId[i].first);
    }

    _program->UseProgram();
    _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));
    _program->SetMatrix("viewMatrix", glm::value_ptr(_viewMatrice._matrix));
    _program->SetMatrix("projectionMatrix", glm::value_ptr(_projectionMatrice._matrix));


    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::LoadTextures(){
    for(uint32_t i=0; i<_textures2DId.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glCheckError();
        glBindTexture(_textures2DId[i].second, _textures2DId[i].first);
        glCheckError();
    }
}

void Mesh3D::LoadMatrixUniforms(){
    _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));
    _program->SetMatrix("viewMatrix", glm::value_ptr(_viewMatrice._matrix));
    _program->SetMatrix("projectionMatrix", glm::value_ptr(_projectionMatrice._matrix));
    _program->SetMatrix("modelInverseTransposeMatrix", glm::value_ptr(_modelInverseTransposeMatrice._matrix));
}

void Mesh3D::LoadDefaultUniforms(){
    LoadMatrixUniforms();
    glCheckError();
    _program->SetFloat3("viewPos", _cameraPosition);
    
    _program->SetFloat3("material.ambient", _material._ambient);
    _program->SetInt("material.diffuse", 0);
    _program->SetInt("material.specular", 1);
    _program->SetInt("material.emission", 2);
    _program->SetFloat("material.shininess", _material._shininess);
    
    _program->SetFloat3("light.position", _light._lightPosition);
    _program->SetFloat3("light.ambient", _light._ambient);
    _program->SetFloat3("light.diffuse", _light._diffuse);
    _program->SetFloat3("light.specular", _light._specular);

    glCheckError();
}

void Mesh3D::DrawArray(){
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _count);
    glBindVertexArray(0);

    glCheckError();
    
    ResetMatrices();
}

void Mesh3D::Draw10Cubes(){
    // for(uint32_t i=0; i<textures_2D.size(); i++){
    //     glActiveTexture(GL_TEXTURE0+i);
    //     textures_2D[i].bindTexture();
    // }

    _program->UseProgram();
    
    _projectionMatrice.Perspective(45, 640.f/480.f, 0.1, 100.f);
    
    _program->SetMatrix("viewMatrix", glm::value_ptr(_viewMatrice._matrix));
    _program->SetMatrix("projectionMatrix", glm::value_ptr(_projectionMatrice._matrix));

    glBindVertexArray(_vao);
    for(uint index=0; index < std::size(graphic::cubePositions); index++) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(_textures2DId[index%3].second, _textures2DId[index%3].first);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(_textures2DId[(index+1)%3].second, _textures2DId[index%3].first);

        _modelMatrice.Translate(graphic::cubePositions[index]);
        float angle = 20.f * index;
        
        // model_matrice.rotate(time, {1.f, 0.3f, 0.5f});

        _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));

        glDrawArrays(GL_TRIANGLES, 0, _count);
        ResetMatrices();
    }
    glBindVertexArray(0);
}

void Mesh3D::ResetMatrices(){
    _modelMatrice.Reset();
    _modelInverseTransposeMatrice.Reset();
    _viewMatrice.Reset();
    _projectionMatrice.Reset();    
}


} // namespace graphic