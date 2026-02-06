#ifndef CAMERA_TYPES_H
#define CAMERA_TYPES_H

namespace tartarus {

enum class CAMERA_MOVEMENT {
    kNothing = 0,
    kMoveForward = 1<<0,
    kMoveBackward = 1<<1,
    kMoveLeft = 1<<2,
    kMoveRight = 1<<3,
    kCount = 4
};

struct OffsetCoordinates {
    float xOffset;
    float yOffset;
    float zOffset;
};

} // namespace tartarus

#endif