#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include "Core/Objects/GameObject.h"
#include "Common/Types.h"

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

    Material _material;
    vec3 _cameraPosition;
};

}

#endif