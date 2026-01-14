#include "common/primitive_vertices.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "mesh3D.h"

#include <cmath>
#include "common/algorithm.h"

namespace graphic {

Mesh3D::~Mesh3D(){
    
}

void Mesh3D::init(){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    model_matrice.matrix = glm::mat4(1.0f);
    view_matrice.matrix = glm::mat4(1.0f);
    projection_matrice.matrix = glm::mat4(1.0f);
}

void Mesh3D::exit(){
    if(vao != -1)
        glDeleteVertexArrays(1, &vao);
    if(vbo != -1)
        glDeleteBuffers(1, &vbo);
    if(ebo != -1)
        glDeleteBuffers(1, &ebo);

    for(auto& iter : textures_2D)
        iter.exit();

    // TODO: call exit on 3D textures
}

void Mesh3D::load2DTexture(const std::string& filePath, GLenum type){
    auto& iter = textures_2D.emplace_back(Texture2D());
    iter.init(filePath, type);
    iter.loadTexture(false);
}

void Mesh3D::load2DTriangle_VBO(const float* vert, uint vert_size){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);
    count = (vert_size/sizeof(float))/3;
}

void Mesh3D::loadCube_TexCoords(const float* vert, uint vert_size, uint stride){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
    count = (vert_size/stride);
}

void Mesh3D::load2DTriangle_VBO_Rainbow(const float* vert, uint vert_size){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    count = 3;
}

void Mesh3D::load2DRectangle_EBO(const float* vert, uint vert_size, const uint* index, uint index_size){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this Mesh3D
    glBindVertexArray(0);
    count = index_size;
}

void Mesh3D::load2DRectangle_2DImage(const float* vert, uint vert_size, const uint* index, uint index_size, uint stride){
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)12);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)24);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    count = index_size/sizeof(uint);
}

void Mesh3D::draw2DRectangle_2DImage() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::draw2DRectangle_EBO(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::draw2DTriangle_VBO(){
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}

void Mesh3D::draw2DTriangle_VBO_uniform(uint programId){
    float timer = glfwGetTime();
    float redValue = common::clamp(std::sin(timer), 0.5f, 1.0f);
    int uniformColorLocation = glGetUniformLocation(programId, "uniformColor");
    glUniform4f(uniformColorLocation, redValue, 0, 0, 1.0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}

void Mesh3D::drawIndex(compiler::Program program){
    for(uint32_t i=0; i<textures_2D.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        textures_2D[i].bindTexture();
    }

    program.useProgram();
    program.setMatrix("modelMatrix", glm::value_ptr(model_matrice.matrix));
    program.setMatrix("viewMatrix", glm::value_ptr(view_matrice.matrix));
    program.setMatrix("projectionMatrix", glm::value_ptr(projection_matrice.matrix));


    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh3D::drawArray(compiler::Program program){
    for(uint32_t i=0; i<textures_2D.size(); i++){
        glActiveTexture(GL_TEXTURE0+i);
        textures_2D[i].bindTexture();
    }

    program.useProgram();
    program.setMatrix("modelMatrix", glm::value_ptr(model_matrice.matrix));
    program.setMatrix("viewMatrix", glm::value_ptr(view_matrice.matrix));
    program.setMatrix("projectionMatrix", glm::value_ptr(projection_matrice.matrix));


    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}

void Mesh3D::draw10Cubes(compiler::Program program, float time){
    // for(uint32_t i=0; i<textures_2D.size(); i++){
    //     glActiveTexture(GL_TEXTURE0+i);
    //     textures_2D[i].bindTexture();
    // }

    program.useProgram();
    
    view_matrice.translate({0, 0, -3.f});
    projection_matrice.perspective(45, 640.f/480.f, 0.1, 100.f);

    program.setMatrix("viewMatrix", glm::value_ptr(view_matrice.matrix));
    program.setMatrix("projectionMatrix", glm::value_ptr(projection_matrice.matrix));

    glBindVertexArray(vao);
    for(uint index=0; index < std::size(graphic::cubePositions); index++) {
        textures_2D[index%3].bindTexture();

        model_matrice.translate(graphic::cubePositions[index]);
        float angle = 20.f * index;
        
        model_matrice.fast_rotate(time, {1.f, 0.3f, 0.5f});

        program.setMatrix("modelMatrix", glm::value_ptr(model_matrice.matrix));

        glDrawArrays(GL_TRIANGLES, 0, count);
        resetMatrices();
    }
    glBindVertexArray(0);
}

void Mesh3D::resetMatrices(){
    model_matrice.reset();
    view_matrice.reset();
    projection_matrice.reset();    
}


} // namespace graphic