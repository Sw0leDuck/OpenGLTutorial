#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "API/Buffer.h"


namespace tartarus {

struct GLBuffer : Buffer {
    bool Init() override;
    bool Exit() override;

    bool IsValid() override { return true; }
};

}

#endif