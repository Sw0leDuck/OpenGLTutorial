#ifndef LIGHT_H
#define LIGHT_H
#include "GameObject.h"
#include "Common/Types.h"

namespace tartarus {

struct PointLight : GameObject {
    bool Init() override;
    bool Exit() override;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectLight : GameObject {
    bool Init() override;
    bool Exit() override;

    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


}

#endif