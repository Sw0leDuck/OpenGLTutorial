#include "camera/fly_camera.h"
#include "common/algorithm.h"

namespace view {

FlyCamera::FlyCamera() : Camera() {}

void FlyCamera::ProcessMouseMovement(float xOffset, float yOffset){
    xOffset *= _cameraSensitivity;
    yOffset *= _cameraSensitivity;
    
    _yaw += xOffset;
    _pitch += yOffset;
    _pitch = common::clamp(_pitch, -89.f, 89.f);
    
    _direction.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
    _direction.y = sin(glm::radians(_pitch));
    _direction.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
    
    _cameraFront = glm::normalize(_direction);
}

void FlyCamera::ProcessMouseScroll(float zOffset){
    _fov -= zOffset;
    _fov = common::clamp(_fov, 1.f, 45.f);
}

void FlyCamera::MoveCamera(CAMERA_MOVEMENT value, float delta_time){
    float modified_speed = ((float)_cameraSpeed * delta_time);
    switch(value){
        case view::CAMERA_MOVEMENT::kMoveForward:
            _position += (modified_speed * _cameraFront);
        break;
        case view::CAMERA_MOVEMENT::kMoveBackward:
            _position -= (modified_speed * _cameraFront);
        break;
        case view::CAMERA_MOVEMENT::kMoveLeft:
            _position -= (modified_speed * glm::cross(_cameraFront, _upVector));
        break;
        case view::CAMERA_MOVEMENT::kMoveRight:
            _position += (modified_speed * glm::cross(_cameraFront, _upVector));
        break;
    }
}
} // namespace view