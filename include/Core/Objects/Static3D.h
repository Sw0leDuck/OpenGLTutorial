#ifndef STATIC_3D_H
#define STATIC_3D_H
#include "API/OpenGL/GLMeshBuffer.h"
#include "Core/Shader.h"
#include "API/OpenGL/GLTexture.h"
#include "RenderObject.h"


namespace tartarus {

struct Static3D : RenderObject {
    bool Init() override;
    bool Exit() override;

    void Draw(float) override;
    void Update(float) override;

    void SetMeshBuffer(GLMeshBuffer* meshBuffer);
    void SetShader(Shader* shader) { _shader = shader; }
    void InsertTexture(GLTexture2D* texture) { 
        _textures.emplace_back(texture);
    }

    GLMeshBuffer* _meshBuffer;
    Shader* _shader;
    std::vector<GLTexture2D*> _textures;
};

}

#endif