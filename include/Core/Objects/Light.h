#ifndef LIGHT_H
#define LIGHT_H
#include "GameObject.h"
#include "Common/Types.h"
#include "RenderObject.h"

namespace tartarus {

struct MaterialLight {
    vec3 _ambient;
    vec3 _diffuse;
    vec3 _specular;
};

struct PointLight : RenderObject {
    bool Init() override;
    bool Exit() override;

    void Update(float val=0) override;
    void Draw(float) override;

    void AttachShader(Shader*);

    void SetIndex(uint);

    void SetPosition(Matrix);
    void SetAttenuation(uint);
    void SetConstant(float);
    void SetLinear(float);
    void SetQuadratic(float);
    void SetAmbient(vec3);
    void SetDiffuse(vec3);
    void SetSpecular(vec3);

    Shader* _attachedShader;

    vec3 _position;
    MaterialLight _lightProperties;

    float _constant;
    float _linear;
    float _quadratic;

    // TODO: remove this
    uint _index = 0;

    bool _update = false;
};

struct DirectLight : GameObject {
    bool Init() override;
    bool Exit() override;

    
    void Draw(float) override {}
    void Update(float delta = 0) override;
    
    void AttachShader(Shader*);
    
    void SetDirection(vec3);
    void SetAmbient(vec3);
    void SetDiffuse(vec3);
    void SetSpecular(vec3);

    // for not we only have 1 giga shader, this
    // will probably change
    Shader* _shaderPtr;

    vec3 _direction;
    MaterialLight _lightProperties;

    bool _update = false;
};


}

#endif