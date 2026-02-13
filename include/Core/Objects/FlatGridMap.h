#ifndef FLAT_GRID_MAP_H
#define FLAT_GRID_MAP_H
#include "RenderObject.h"

namespace tartarus {

/**
 * 2D Structure drawing a texture 25 times in a
 * grid map. For now we will use a 5x5
**/
struct FlatGridMap : RenderObject {

    bool Init() override;
    bool Exit() override;
    
    void Draw(float) override;
    void Update(float) override;

    uint _instanceCount;
};


}

#endif