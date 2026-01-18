#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#include "camera.h"

namespace view {
    struct FPSCamera : Camera {
        FPSCamera();

        void ProcessMouseMovement(float xOffset, float yOffset) override;
        void ProcessMouseScroll(float zOffset) override;
        void MoveCamera(CAMERA_MOVEMENT value, float delta_time) override;
    };
}

#endif