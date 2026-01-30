#ifndef MESH_H
#define MESH_H

#include "common/types.h"
#include "matrix.h"


namespace tartarus {
    enum class VertexAttribute : uint {
        kPos = 1 << 0,
        kTextCoords = 1 << 1,
        kNormalVector = 1 << 2,
        kLast = kNormalVector,
        kAll = kPos | kTextCoords | kNormalVector
    };

    struct Mesh3D {
        struct Material {
            glm::vec3 _ambient;
            glm::vec3 _diffuse;
            glm::vec3 _specular;
            float _shininess;
        };

        struct Light {
            glm::vec3 _lightPosition;
            glm::vec3 _lightDirection;

            glm::vec3 _ambient;
            glm::vec3 _diffuse;
            glm::vec3 _specular;
        };

        Material _material;
        Light _light;
        glm::vec3 _pointLightPositions[4];

        uint _vao = -1; // vertex array ( contains a state of vertices, elementes, attrib etc )
        uint _vbo = -1; // buffer ( contain vertices )
        uint _ebo = -1; // element buffer

        uint _count;

        std::vector<glm::vec3> _pts;
        std::vector<glm::vec3> _colors;
        std::vector<uint> _indices;
        std::vector<glm::vec3> _texCoords;

        glm::vec3 _cameraPosition;
        glm::vec3 _lightPositions;
        glm::vec3 _objectColor;

        Matrix _modelMatrice = {};
        Matrix _modelInverseTransposeMatrice = {};
        Matrix _viewMatrice = {};
        Matrix _projectionMatrice = {};

        std::vector<std::pair<uint,uint>> _textures2DId;
        std::vector<uint> _textures3DId;

        ~Mesh3D();
    
        void Init();
        void Exit();

        void LoadCube(uint vertexAttributeFlags);
        void LoadTriangle();

        void DrawIndex();
        void DrawArray();

        void LoadTextures();
        void LoadDefaultUniforms();
        void LoadMatrixUniforms();
        
        void Draw10Cubes();
        void ResetMatrices();
    };
}

#endif