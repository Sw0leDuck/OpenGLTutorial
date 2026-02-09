#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include "Core/Objects/GameObject.h"
#include "Core/Shader.h"
#include "Common/Types.h"
#include "API/OpenGL/GLMeshBuffer.h"
#include "Core/Shader.h"
#include "API/OpenGL/GLTexture.h"

namespace tartarus {

static const char* _uniformNames[3] = {
    "material.diffuse",
    "material.specular",
    "material.emission"
};

struct RenderObject : public GameObject {

    struct Material {
        vec3 _ambient;

        uint _diffuse; // main texture image
        uint _specular; // compute shiness
        uint _emission; // texture image for glowing things

        float _shininess;
    };

    void SetMeshBuffer(GLMeshBuffer* meshBuffer);
    void SetShader(Shader* shader) { _shader = shader; }
    void InsertTexture(GLTexture2D* texture) { 
        _textures.emplace_back(texture);
    }

    GLMeshBuffer* _meshBuffer;
    Shader* _shader;
    std::vector<GLTexture2D*> _textures;

    Material _material;
    vec3 _cameraPosition;
    Shader* _primaryShader;
};

}

#endif