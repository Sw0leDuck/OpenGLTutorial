#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "mesh3D.h"



namespace tartarus {

Mesh3D::~Mesh3D() { }

void Mesh3D::Init(){
    _modelMatrice._matrix = glm::mat4(1.0f);
    _viewMatrice._matrix = glm::mat4(1.0f);
    _projectionMatrice._matrix = glm::mat4(1.0f);

    _material._ambient = glm::vec3(0.2125	, 0.1275,	0.054);
    _material._diffuse = glm::vec3(0.714, 0.4284, 0.18144);
    _material._specular = glm::vec3(0.5f, 0.5f, 0.5f);
    _material._shininess = 32.0f;

    _light._ambient = glm::vec3( 0.1f, 0.1f, 0.1f);
    _light._diffuse = glm::vec3( 0.8f, 0.8f, 0.8f); // darken diffuse light a bit
    _light._specular = glm::vec3(1.0f, 1.0f, 1.0f);

    _objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
}

void Mesh3D::DrawIndex(){
    for(uint32_t i=0; i<_textures2DId.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(_textures2DId[i].second, _textures2DId[i].first);
    }

    // _program->UseProgram();
    // _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));
    // _program->SetMatrix("viewMatrix", glm::value_ptr(_viewMatrice._matrix));
    // _program->SetMatrix("projectionMatrix", glm::value_ptr(_projectionMatrice._matrix));


    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::LoadTextures(){
    for(uint32_t i=0; i<_textures2DId.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(_textures2DId[i].second, _textures2DId[i].first);
    }
}

void Mesh3D::LoadMatrixUniforms(){
    // _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));
    // _program->SetMatrix("viewMatrix", glm::value_ptr(_viewMatrice._matrix));
    // _program->SetMatrix("projectionMatrix", glm::value_ptr(_projectionMatrice._matrix));
    // _program->SetMatrix("modelInverseTransposeMatrix", glm::value_ptr(_modelInverseTransposeMatrice._matrix));
}

void Mesh3D::LoadDefaultUniforms(){
    LoadMatrixUniforms();
    // _program->SetFloat3("viewPos", _cameraPosition);
    
    // _program->SetFloat3("material.ambient", _material._ambient);
    // _program->SetInt("material.diffuse", 0);
    // _program->SetInt("material.specular", 1);
    // _program->SetInt("material.emission", 2);
    // _program->SetFloat("material.shininess", _material._shininess);
    
    // direction light
    // _program->SetFloat3("dirLight.direction", _light._lightDirection);
    // _program->SetFloat3("dirLight.ambient", _light._ambient);
    // _program->SetFloat3("dirLight.diffuse", _light._diffuse);
    // _program->SetFloat3("dirLight.specular", _light._specular);

    // Point Light ( 4 ) - TODO: REFACTOR THIS SHIT
    // _program->SetFloat3("pointLight[0].position", _pointLightPositions[0]);
    // _program->SetFloat3("pointLight[0].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[0].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[0].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[0].constant", 1.0f);
    // _program->SetFloat("pointLight[0].linear", 0.09f);
    // _program->SetFloat("pointLight[0].quadratic", 0.032f);
        // point light 2
    // _program->SetFloat3("pointLight[1].position", _pointLightPositions[1]);
    // _program->SetFloat3("pointLight[1].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[1].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[1].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[1].constant", 1.0f);
    // _program->SetFloat("pointLight[1].linear", 0.09f);
    // _program->SetFloat("pointLight[1].quadratic", 0.032f);
        // point light 3
    // _program->SetFloat3("pointLight[2].position", _pointLightPositions[2]);
    // _program->SetFloat3("pointLight[2].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[2].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[2].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[2].constant", 1.0f);
    // _program->SetFloat("pointLight[2].linear", 0.09f);
    // _program->SetFloat("pointLight[2].quadratic", 0.032f);
        // point light 4
    // _program->SetFloat3("pointLight[3].position", _pointLightPositions[3]);
    // _program->SetFloat3("pointLight[3].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[3].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[3].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[3].constant", 1.0f);
    // _program->SetFloat("pointLight[3].linear", 0.09f);
    // _program->SetFloat("pointLight[3].quadratic", 0.032f);


    // _program->SetFloat("light.cuttOf", glm::cos(glm::radians(12.5f)));
    // _program->SetFloat("light.outerCuttOf", glm::cos(glm::radians(17.5f)));
}

void Mesh3D::DrawArray(){
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _count);
    glBindVertexArray(0);

    
    ResetMatrices();
}

void Mesh3D::Draw10Cubes(){

    // glBindVertexArray(_vao);
    // for(uint index=0; index < std::size(graphic::cubePositions); index++) {
    //     float angle = 20.f * index;
        
    //     _modelMatrice.Translate(graphic::cubePositions[index]);
    //     _modelMatrice.Rotate(angle, {1.f, 0.3f, 0.5f});
    //     _modelInverseTransposeMatrice._matrix = glm::transpose(glm::inverse(_modelMatrice._matrix));


        // _program->SetMatrix("modelMatrix", glm::value_ptr(_modelMatrice._matrix));
        // _program->SetMatrix("modelInverseTransposeMatrix", glm::value_ptr(_modelMatrice._matrix));

    //     glDrawArrays(GL_TRIANGLES, 0, _count);
    //     _modelMatrice.Reset();
    // }
    // glBindVertexArray(0);
}

void Mesh3D::ResetMatrices(){
    _modelMatrice.Reset();
    _modelInverseTransposeMatrice.Reset();
    _viewMatrice.Reset();
    _projectionMatrice.Reset();    
}


} // namespace graphic