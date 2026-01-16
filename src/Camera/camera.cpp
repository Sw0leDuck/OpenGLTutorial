#include "camera/camera.h"
#include "common/algorithm.h"

namespace view {
static constexpr float g_fov = 45.0f;

    void Camera::Init(glm::vec3 position,
            float yaw,
            float pitch,
            float roll,
            float camera_speed,
            float camera_sensitivity) {
        _position = position;
        _up_vector = glm::vec3(0.f, 1.f, 0.f);
        _camera_front = glm::vec3(0.f, 0.f, -1.f);

        _camera_target = glm::vec3(0.f, 0.f, 0.f);
        _camera_target = glm::vec3(0.f, 0.f, -1.f);

        _camera_z_axis = glm::normalize(_position - _camera_target);
        _camera_x_axis = glm::normalize(glm::cross(_up_vector, _camera_z_axis));
        _camera_y_axis = glm::cross(_camera_z_axis, _camera_x_axis);

        _camera_speed = camera_speed;
        _camera_sensitivity = camera_sensitivity;
        _yaw = yaw;
        _pitch = pitch;
        _roll = roll;
    }

    void Camera::Exit(){
        // TODO:: does it need anything?
    }

    void Camera::UpdateCamera(float xOffset, float yOffset){
        xOffset *= _camera_sensitivity;
        yOffset *= _camera_sensitivity;
        
        _yaw += xOffset;
        _pitch += yOffset;

        _pitch = common::clamp(_pitch, -89.f, 89.f);

        _direction.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
        _direction.y = sin(glm::radians(_pitch));
        _direction.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));

        _camera_front = glm::normalize(_direction);
    }

} // namespace view