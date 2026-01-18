#include "Camera/fps_camera.h"
#include "common/algorithm.h"

namespace view {

FPSCamera::FPSCamera() : Camera() {}

void FPSCamera::ProcessMouseMovement(float xOffset, float yOffset){
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

void FPSCamera::ProcessMouseScroll(float zOffset){
    return; // do nothing
}

void FPSCamera::MoveCamera(CAMERA_MOVEMENT value, float delta_time){
    float modified_speed = ((float)_cameraSpeed * delta_time);
    float save_value = _cameraFront.y;
    _cameraFront.y = 0;
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
    _cameraFront.y = save_value;
}

}