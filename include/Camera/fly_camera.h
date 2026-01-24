#ifndef CAMERA_FLY_H
#define CAMERA_FLY_H

#include "camera.h"


namespace tartarus {

    struct FlyCamera : public Camera {
        FlyCamera();

        virtual void ProcessMouseMovement(float xOffset, float yOffset) override;
        virtual void ProcessMouseScroll(float zOffset) override;
        virtual void MoveCamera(CAMERA_MOVEMENT value, float delta_time) override;
    };
} // namespace view

#endif