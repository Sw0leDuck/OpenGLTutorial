#ifndef STATIC_3D_H
#define STATIC_3D_H
#include "API/OpenGL/GLMeshBuffer.h"
#include "Core/Shader.h"
#include "GameObject.h"


namespace tartarus {

struct Static3D : GameObject {
    bool Init() override;
    bool Exit() override;

    void Draw(float) override;
    void Update(float) override;

    GLMeshBuffer* _meshBuffer;
    Shader* _shader;
};

}

#endif