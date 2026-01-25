#include "Camera/Camera.h"
#include "common/algorithm.h"

namespace tartarus {

    void Camera::Init(glm::vec3 position,
            float yaw,
            float pitch,
            float roll,
            float camera_speed,
            float camera_sensitivity,
            float camera_fov) {
        _type = GameObject::Type::kCamera;
        
        _position = position;
        _upVector = glm::vec3(0.f, 1.f, 0.f);
        _cameraFront = glm::vec3(0.f, 0.f, -1.f);

        _cameraTarget = glm::vec3(0.f, 0.f, 0.f);
        _cameraTarget = glm::vec3(0.f, 0.f, -1.f);

        _cameraZAxis = glm::normalize(_position - _cameraTarget);
        _cameraXAxis = glm::normalize(glm::cross(_upVector, _cameraZAxis));
        _cameraYAxis = glm::cross(_cameraZAxis, _cameraXAxis);

        _cameraSpeed = camera_speed;
        _cameraSensitivity = camera_sensitivity;
        
        _fov = camera_fov;
        _near = 0.1f;
        _far = 100.f;

        _yaw = yaw;
        _pitch = pitch;
        _roll = roll;
    }

    bool Camera::Exit(){
        // TODO:: does it need anything?
        return true;
    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset){
        return; // do nothing
    }

    void Camera::MoveCamera(CAMERA_MOVEMENT value, float delta_time){
        return; // do nothing
    }

    void Camera::ProcessMouseScroll(float zOffset){
        return; // do nothing
    }

    glm::mat4 Camera::CalculateViewMatrix() {
        return glm::lookAt(_position, _position + _cameraFront, _upVector);
    }

    glm::mat4 Camera::CalculateProjectionMatrix() {
        return glm::perspective(glm::radians(_fov), _screenAspect, _near, _far);
    }

    glm::mat4 Camera::LookAt(){
        void(0);
    }

} // namespace view