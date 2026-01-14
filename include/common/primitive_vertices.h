#ifndef PRIMITIVES_VERTICES_H
#define PRIMITIVES_VERTICES_H

#include "types.h"
#include "glm/gtc/type_ptr.hpp"

namespace graphic {

    static const glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    static const float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    static const float vert_2DRectangle_VBO[] = {
        -0.5f,  0.5f,  0.0f,
        0.5f ,  0.5f,  0.0f,
        0.5f , -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
        0.5f,  -0.5f,  0.0f
    };

    static const float vert_2DTriangle_VBO_Rainbow[] ={
        -0.5f, -0.5f, 0.0,  1.0f, 0.0f, 0.0f,
        0.5f , -0.5f, 0.0,  0.0f, 1.0f, 0.0f,
        0.0f , 0.5f , 0.0,  0.0f, 0.0f, 1.0f
    };

    static const float vert_2DTriangleUpper[] = {
        -0.5f,  0.5f,  0.0f,
        0.5f ,  0.5f,  0.0f,
        0.5f , -0.5f,  0.0f
    };

    static const float vert_2DTriangleLower[] = {
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
        0.5f,  -0.5f,  0.0f
    };

    static const float vert_2DRectangle[] = {
        -0.5f,  0.5f, 0.0f,
        0.5f ,  0.5f, 0.0f,
        0.5f , -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    static const float vert_2DRectangle_2DImage[] ={
        -0.5f, -0.5f, 0.0,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left = 0
        0.5f , 0.5f , 0.0,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // top right = 1
        0.5f , -0.5f, 0.0,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // bottom right = 2
        -0.5f, 0.5f,  0.0,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f  // top left = 3
    };

    static const uint indices[] = {
        0, 3, 1,
        0, 2, 1
    };

} // graphic

#endif