#ifndef STATIC_3D_H
#define STATIC_3D_H
#include "RenderObject.h"


namespace tartarus {

struct Static3D : RenderObject {
    bool Init() override;
    bool Exit() override;

    void Draw(float) override;
    void Update(float) override;
};

}

#endif