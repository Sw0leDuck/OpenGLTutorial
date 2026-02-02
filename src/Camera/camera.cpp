#include "Camera/Camera.h"
#include "Common/Algorithm.h"

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

bool Camera::Init(){
    // TODO:: does it need anything?
    return true;
}

bool Camera::Exit(){
    // TODO:: does it need anything?
    return true;
}

void Camera::Update(float delta){
    if(!(_offsets.xOffset == 0.f && _offsets.yOffset == 0.f)){
        _offsets.xOffset *= _cameraSensitivity;
        _offsets.yOffset *= _cameraSensitivity;
        
        _yaw += _offsets.xOffset;
        _pitch += _offsets.yOffset;
        _pitch = clamp(_pitch, -89.f, 89.f);
        
        _direction.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
        _direction.y = sin(glm::radians(_pitch));
        _direction.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
        
        _cameraFront = glm::normalize(_direction);
    }

    if(_movement != CAMERA_MOVEMENT::kNothing){
        float modified_speed = ((float)_cameraSpeed * delta);
        // float save__movement = _cameraFront.y;
        // _cameraFront.y = 0;
        switch(_movement){
            case CAMERA_MOVEMENT::kMoveForward:
                _position += (modified_speed * _cameraFront);
                break;
            case CAMERA_MOVEMENT::kMoveBackward:
                _position -= (modified_speed * _cameraFront);
                break;
            case CAMERA_MOVEMENT::kMoveLeft:
                _position -= (modified_speed * glm::cross(_cameraFront, _upVector));
                break;
            case CAMERA_MOVEMENT::kMoveRight:
                _position += (modified_speed * glm::cross(_cameraFront, _upVector));
                break;
            default:
                break;
        }
    }
    
    _fov -= _offsets.zOffset;
    _fov = clamp(_fov, 1.f, 45.f);

    _viewMatrix = CalculateViewMatrix();
    _projMatrix = CalculateProjectionMatrix();
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt(_position, _position + _cameraFront, _upVector);
}

glm::mat4 Camera::CalculateProjectionMatrix() {
    return glm::perspective(glm::radians(_fov), _screenAspect, _near, _far);
}

glm::mat4 Camera::GetView(){
    return _viewMatrix;
}

glm::mat4 Camera::GetProjection(){
    return _projMatrix;
}

glm::mat4 Camera::LookAt(){
    void(0);
}

} // namespace view