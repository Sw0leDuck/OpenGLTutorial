#ifndef GPU_BACKEND_H
#define GPU_BACKEND_H
#include <stdlib.h>
#include "Common/types.h"

namespace tartarus {

// Is this even worth it?
struct Gpu {
    virtual bool Init() { abort(); }
    virtual bool Exit() { abort(); }
    virtual bool IsValid() { return false; }
    
    virtual void ClearScreen() { abort(); }
    virtual void UpdateViewPort(uint, uint) { abort(); }
};

}

#endif