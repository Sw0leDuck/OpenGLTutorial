#ifndef CAMERA_TYPES_H
#define CAMERA_TYPES_H

namespace tartarus {

enum class CAMERA_MOVEMENT {
    kNothing = 0,
    kMoveForward = 1,
    kMoveBackward = 2,
    kMoveLeft = 3,
    kMoveRight = 4
};

struct OffsetCoordinates {
    float xOffset;
    float yOffset;
    float zOffset;
};

} // namespace tartarus

#endif