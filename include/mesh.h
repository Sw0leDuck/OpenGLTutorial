#ifndef MESH_H
#define MESH_H

#include "common/types.h"

namespace graphic {
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

    static const uint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    struct mesh{
        uint vao = -1; // vertex array ( contains a state of vertices, elementes, attrib etc )
        uint vbo = -1; // buffer ( contain vertices )
        uint ebo = -1; // element buffer

        uint count;

        ~mesh();
    
        void init();
        void load2DTriangle_VBO(const float* vert, uint vert_size);
        void load2DTriangle_VBO_Rainbow(const float* vert, uint vert_size);
        void load2DRectangle_EBO(const float* vert, uint vert_size, const uint* index, uint index_size);
        void draw2DRectangle_EBO();
        void draw2DTriangle_VBO();
        void draw2DTriangle_VBO_uniform(uint programId);
    };
}

#endif