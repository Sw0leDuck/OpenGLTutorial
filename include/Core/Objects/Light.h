#ifndef LIGHT_H
#define LIGHT_H
#include "GameObject.h"

namespace tartarus {

struct Light : GameObject {
    bool Init() override;
    bool Exit() override;


};

}

#endif