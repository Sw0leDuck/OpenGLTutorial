#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "mesh.h"

#include <cmath>
#include "common/algorithm.h"

namespace graphic {

mesh::~mesh(){
    if(vao != -1)
        glDeleteVertexArrays(1, &vao);
    if(vbo != -1)
        glDeleteBuffers(1, &vbo);
    if(ebo != -1)
        glDeleteBuffers(1, &ebo);
}

void mesh::init(){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void mesh::load2DTriangle_VBO(const float* vert, uint vert_size){
    // bind the Vertex Array first so that the following changes occur in this vao
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this mesh
    glBindVertexArray(0);
    count = (vert_size/sizeof(float))/3;
}

void mesh::load2DTriangle_VBO_Rainbow(const float* vert, uint vert_size){
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

void mesh::load2DRectangle_EBO(const float* vert, uint vert_size, const uint* index, uint index_size){
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vert_size, vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind the VBO, it does not get deleted because it's registered in the VAO context?
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // unbind the Vertex Array in case any calls modify this mesh
    glBindVertexArray(0);
    count = index_size;
}

void mesh::load2DRectangle_2DImage(const float* vert, uint vert_size, const uint* index, uint index_size, uint stride){
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

void mesh::draw2DRectangle_2DImage() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh::draw2DRectangle_EBO(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void mesh::draw2DTriangle_VBO(){
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}

void mesh::draw2DTriangle_VBO_uniform(uint programId){
    float timer = glfwGetTime();
    float redValue = common::clamp(std::sin(timer), 0.5f, 1.0f);
    int uniformColorLocation = glGetUniformLocation(programId, "uniformColor");
    glUniform4f(uniformColorLocation, redValue, 0, 0, 1.0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}


} // namespace graphic