#ifndef MESH_H
#define MESH_H

#include "glsl_compiler.h"
#include "common/types.h"
#include "matrix.h"
#include "texture.h"


namespace graphic {
    struct Mesh3D {
        uint vao = -1; // vertex array ( contains a state of vertices, elementes, attrib etc )
        uint vbo = -1; // buffer ( contain vertices )
        uint ebo = -1; // element buffer

        uint count;

        std::vector<glm::vec3> pts;
        std::vector<glm::vec3> colors;
        std::vector<uint> indices;
        std::vector<glm::vec3> texCoords;

        Matrix model_matrice = {};
        Matrix view_matrice = {};
        Matrix projection_matrice = {};

        std::vector<Texture2D> textures_2D;
        std::vector<Texture3D> textures_3D;

        ~Mesh3D();
    
        void init();
        void exit();
        void load2DTexture(const std::string& filePath, GLenum type);
        void load2DTriangle_VBO(const float* vert, uint vert_size);
        void loadCube_TexCoords(const float* vert, uint vert_size, uint stride);
        void load2DTriangle_VBO_Rainbow(const float* vert, uint vert_size);
        void load2DRectangle_EBO(const float* vert, uint vert_size, const uint* index, uint index_size);
        void load2DRectangle_2DImage(const float* vert, uint vert_size, const uint* index, uint index_size, uint stride);
        void drawIndex(compiler::Program program);
        void drawArray(compiler::Program program);
        void draw10Cubes(compiler::Program program, float time = 0);
        void draw2DRectangle_EBO();
        void draw2DTriangle_VBO();
        void draw2DTriangle_VBO_uniform(uint programId);
        void draw2DRectangle_2DImage();
        void resetMatrices();
    };
}

#endif